.include "library.inc"
.include "usbdrvce-exports.inc"

library USBDRVCE, USBDRVCE_VERSION
usbdrvce_exports lib_export

.equ DEBUG, 0

.macro msb_index symbol, value:vararg
	.set \symbol, 0
	.irp bit, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
		.if (\value) >= (1 << \bit)
			.set \symbol, \bit
		.endif
	.endr
.endm

.macro mask_instruction op, mask, operand:vararg
	msb_index .Lmask_bit\@, \mask
	assert (\mask) == (1 << .Lmask_bit\@)
	\op .Lmask_bit\@, \operand
.endm
.macro bit_mask mask, operand:vararg
	mask_instruction bit, \mask, \operand
.endm
.macro res_mask mask, operand:vararg
	mask_instruction res, \mask, \operand
.endm
.macro set_mask mask, operand:vararg
	mask_instruction set, \mask, \operand
.endm

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
.struct 0
timer:
timer.tick:	.space 4
timer.next:	.space 3
timer.callback:	.space 3
.equ timer_size, . - timer

; transfer structure
.struct 0
transfer:
transfer.next:	.space 4	; pointer to next transfer structure
.equ transfer.next.dummy, 1 << 0
transfer.altNext:	.space 4	; pointer to alternate next transfer structure
transfer.status:	; transfer status
.equ transfer.status_size, 1
	.space 1
.equ transfer.status.active, 1 << 7
.equ transfer.status.halted, 1 << 6
.equ transfer.status.bufErr, 1 << 5
.equ transfer.status.babble, 1 << 4
.equ transfer.status.xactErr, 1 << 3
.equ transfer.status.ufMiss, 1 << 2
.equ transfer.status.split, 1 << 1
.equ transfer.status.stall, 1 << 0
transfer.type:	.space 1
.equ transfer.type.ioc, 1 << 7
.equ transfer.type.cpage, 7 << 4
.equ transfer.type.cerr, 3 << 2
.equ transfer.type.pid, 3 << 0
transfer.remaining:	.space 2	; transfer remaining length
.equ transfer.remaining.dt, 1 << 15
transfer.buffers:	; transfer buffers
.equ transfer.buffers_size, 20
	.space 3
transfer.length:	.space 3	; original transfer length
transfer.callback:	.space 4	; user callback
transfer.data:	.space 4	; user callback data
transfer.endpoint:	.space 4	; pointer to endpoint structure
transfer.padding:	.space 1
transfer.fifo:	.space 1	; associated fifo mask
.equ transfer_size, . - transfer
assert (transfer_size == 32)

; endpoint structure
.struct 0		; Hardware links are based two bytes before the endpoint pointer.
endpoint.base:
.equ endpoint.base_size, 64
.equ endpoint, .+2
.equ endpoint_overlay_start, .
endpoint.next:	.space 3	; link to next endpoint structure
endpoint.prev:	.space 1	; link to prev endpoint structure
.struct endpoint_overlay_start
	.space 2
endpoint.maxHsSbp:	.space 2
endpoint.addr:	.space 1	; device addr or cancel shl 7
endpoint.info:	.space 1	; ep or speed shl 4 or dtc shl 6
.equ endpoint.info.head, 1 << 7
.equ endpoint.info.dtc, 1 << 6
.equ endpoint.info.eps, 3 << 4
.equ endpoint.info.ep, 0xF
endpoint.maxPktLen:	.space 2	; max packet length or c shl 15 or 1 shl 16
.equ endpoint.maxPktLen.msk, 0x7FF
.equ endpoint.maxPktLen.c, 1 << 11
.equ endpoint.maxPktLen.rl, 0xF << 12
endpoint.smask:	.space 1	; micro-frame s-mask
endpoint.cmask:	.space 1	; micro-frame c-mask
endpoint.hubInfo:	.space 2	; hub addr or port number shl 7 or mult shl 14
endpoint.cur:	.space 4	; current transfer pointer
endpoint.overlay:	.space transfer_size	; current transfer
endpoint.transferInfo:	.space 1	; transfer type or transfer dir shl 7
.equ endpoint.transferInfo.dir, 1 << 7
.equ endpoint.transferInfo.type, 3 << 0
endpoint.flags:	.space 1	; endpoint flags
.equ endpoint.flags.autoTerm, 1 << 0
.equ endpoint.flags.po2Mps, 1 << 1
.equ endpoint.flags.refCnt, 1 << 2
.equ endpoint.flags.freed, 1 << 3
endpoint.interval:	.space 1	; schedule po2 interval
endpoint.offset:	.space 1	; schedule offset shl 1 or 1
endpoint.device:	.space 3	; pointer to device
endpoint.first:	.space 3	; pointer to first scheduled transfer
endpoint.last:	.space 3	; pointer to last dummy transfer
endpoint.data:	.space 3	; user data
.equ endpoint_size, . - endpoint
.equ endpoint.overlay.next, endpoint.overlay + transfer.next - transfer
.equ endpoint.overlay.altNext, endpoint.overlay + transfer.altNext - transfer
.equ endpoint.overlay.status, endpoint.overlay + transfer.status - transfer
.equ endpoint.overlay.status.halted, transfer.status.halted
.equ endpoint.overlay.remaining, endpoint.overlay + transfer.remaining - transfer
.equ endpoint.overlay.remaining.dt, transfer.remaining.dt
.equ endpoint.overlay.fifo, endpoint.overlay + transfer.fifo - transfer
assert (endpoint_size == 62)

.struct 0
setup:
setup.bmRequestType:	.space 1
setup.bRequest:	.space 1
setup.wValue:	.space 2
setup.wIndex:	.space 2
setup.wLength:	.space 2
.equ setup_size, . - setup
assert (setup_size == 8)

.struct 0
descriptor:
descriptor.bLength:	.space 1
descriptor.bDescriptorType:	.space 1
.equ descriptor_size, . - descriptor
assert (descriptor_size == 2)

.struct 0
hubDescriptor:
hubDescriptor.descriptor:	.space descriptor_size
hubDescriptor.bNbrPorts:	.space 1
hubDescriptor.wHubCharacteristics:	.space 2
hubDescriptor.bPwrOn2PwrGood:	.space 1
hubDescriptor.bHubContrCurrent:	.space 1
hubDescriptor.DeviceRemovable:	.space 1	; variable
hubDescriptor.PortPwrCtrlMask:	.space 1	; variable
.equ hubDescriptor_size, . - hubDescriptor
.equ hubDescriptor.descriptor.bLength, hubDescriptor.descriptor + descriptor.bLength - descriptor
.equ hubDescriptor.descriptor.bDescriptorType, hubDescriptor.descriptor + descriptor.bDescriptorType - descriptor
assert (hubDescriptor_size == 9)

; hub structure
.struct 0
hub:
hub.setup:	.space setup_size	; setup
hub.bitmap:	.space 1	; status change bitmap
hub.status:	; wHubStatus or wPortStatus
.equ hub.status_size, 2
	.space 2
hub.change:	; wHubChange or wPortChange
.equ hub.change_size, 2
	.space 2
hub.endpoint:	.space 3	; status change endpoint
hub.device:	.space 3	; current device
hub.desc:	.space hubDescriptor_size
	.space 4	; padding
.equ hub_size, . - hub
.equ hub.desc_size, hubDescriptor_size
.equ hub.setup.bmRequestType, hub.setup + setup.bmRequestType - setup
.equ hub.setup.bRequest, hub.setup + setup.bRequest - setup
.equ hub.setup.wValue, hub.setup + setup.wValue - setup
.equ hub.setup.wIndex, hub.setup + setup.wIndex - setup
.equ hub.setup.wLength, hub.setup + setup.wLength - setup
.equ hub.desc.bNbrPorts, hub.desc + hubDescriptor.bNbrPorts - hubDescriptor
.equ hub.desc.bPwrOn2PwrGood, hub.desc + hubDescriptor.bPwrOn2PwrGood - hubDescriptor
assert (hub_size == 32)

; device structure
.struct 0
device:
device.endpoints:	.space 3	; pointer to array of endpoints
device.addr:	.space 1	; device addr and $7F
device.refcnt:	.space 3	; reference count
device.speed:	.space 1	; device speed shl 4
device.sibling:	.space 3	; next device connected to the same hub
device.back:	.space 3	; update pointer to next pointer to self
device.find:	.space 1	; find flags
device.portNbr:	.space 1	; port number of hub this device is connected to
device.child:	.space 3	; first device connected to this hub
	.space 1	; padding
device.hub:	.space 3	; hub this device is connected to
device.data:	.space 3	; user data
	.space 6	; padding
.equ device_size, . - device
assert (device_size == 32)

.struct 0
deviceDescriptor:
deviceDescriptor.descriptor:	.space descriptor_size
deviceDescriptor.bcdUSB:	.space 2
deviceDescriptor.bDeviceClass:	.space 1
deviceDescriptor.bDeviceSubClass:	.space 1
deviceDescriptor.bDeviceProtocol:	.space 1
deviceDescriptor.bMaxPacketSize0:	.space 1
deviceDescriptor.idVendor:	.space 2
deviceDescriptor.idProduct:	.space 2
deviceDescriptor.bcdDevice:	.space 2
deviceDescriptor.iManufacturer:	.space 1
deviceDescriptor.iProduct:	.space 1
deviceDescriptor.iSerialNumber:	.space 1
deviceDescriptor.bNumConfigurations:	.space 1
.equ deviceDescriptor_size, . - deviceDescriptor
.equ deviceDescriptor.descriptor.bLength, deviceDescriptor.descriptor + descriptor.bLength - descriptor
.equ deviceDescriptor.descriptor.bDescriptorType, deviceDescriptor.descriptor + descriptor.bDescriptorType - descriptor
assert (deviceDescriptor_size == 18)

; reset structure
.struct 0
reset:
reset.next:	.space 3	; next reset
reset.device:	.space 3	; device
reset.setup:	.space setup_size	; setup
reset.desc:	.space deviceDescriptor_size
.equ reset_size, . - reset
.equ reset.setup.bmRequestType, reset.setup + setup.bmRequestType - setup
.equ reset.setup.bRequest, reset.setup + setup.bRequest - setup
.equ reset.setup.wValue, reset.setup + setup.wValue - setup
.equ reset.setup.wIndex, reset.setup + setup.wIndex - setup
.equ reset.setup.wLength, reset.setup + setup.wLength - setup
.equ reset.desc.bDeviceClass, reset.desc + deviceDescriptor.bDeviceClass - deviceDescriptor
.equ reset.desc.bMaxPacketSize0, reset.desc + deviceDescriptor.bMaxPacketSize0 - deviceDescriptor
assert (reset_size == 32)

.struct 0
standardDescriptors:
standardDescriptors.device:	.space 3
standardDescriptors.configurations:	.space 3
standardDescriptors.langids:	.space 3
standardDescriptors.numStrings:	.space 1
standardDescriptors.strings:	.space 3
.equ standardDescriptors_size, . - standardDescriptors

.struct 0
deviceQualifierDescriptor:
deviceQualifierDescriptor.descriptor:	.space descriptor_size
deviceQualifierDescriptor.bcdUSB:	.space 2
deviceQualifierDescriptor.bDeviceClass:	.space 1
deviceQualifierDescriptor.bDeviceSubClass:	.space 1
deviceQualifierDescriptor.bDeviceProtocol:	.space 1
deviceQualifierDescriptor.bMaxPacketSize0:	.space 1
deviceQualifierDescriptor.bNumConfigurations:	.space 1
deviceQualifierDescriptor.bReserved:	.space 1
.equ deviceQualifierDescriptor_size, . - deviceQualifierDescriptor
.equ deviceQualifierDescriptor.descriptor.bLength, deviceQualifierDescriptor.descriptor + descriptor.bLength - descriptor
.equ deviceQualifierDescriptor.descriptor.bDescriptorType, deviceQualifierDescriptor.descriptor + descriptor.bDescriptorType - descriptor
assert (deviceQualifierDescriptor_size == 10)

.struct 0
configurationDescriptor:
configurationDescriptor.descriptor:	.space descriptor_size
configurationDescriptor.wTotalLength:	.space 2
configurationDescriptor.bNumInterfaces:	.space 1
configurationDescriptor.bConfigurationValue:	.space 1
configurationDescriptor.iConfiguration:	.space 1
configurationDescriptor.bmAttributes:	.space 1
configurationDescriptor.bMaxPower:	.space 1
.equ configurationDescriptor_size, . - configurationDescriptor
.equ configurationDescriptor.descriptor.bLength, configurationDescriptor.descriptor + descriptor.bLength - descriptor
.equ configurationDescriptor.descriptor.bDescriptorType, configurationDescriptor.descriptor + descriptor.bDescriptorType - descriptor
assert (configurationDescriptor_size == 9)

.struct 0
interfaceDescriptor:
interfaceDescriptor.descriptor:	.space descriptor_size
interfaceDescriptor.bInterfaceNumber:	.space 1
interfaceDescriptor.bAlternateSetting:	.space 1
interfaceDescriptor.bNumEndpoints:	.space 1
interfaceDescriptor.bInterfaceClass:	.space 1
interfaceDescriptor.bInterfaceSubClass:	.space 1
interfaceDescriptor.bInterfaceProtocol:	.space 1
interfaceDescriptor.iInterface:	.space 1
.equ interfaceDescriptor_size, . - interfaceDescriptor
.equ interfaceDescriptor.descriptor.bLength, interfaceDescriptor.descriptor + descriptor.bLength - descriptor
.equ interfaceDescriptor.descriptor.bDescriptorType, interfaceDescriptor.descriptor + descriptor.bDescriptorType - descriptor
assert (interfaceDescriptor_size == 9)

.struct 0
endpointDescriptor:
endpointDescriptor.descriptor:	.space descriptor_size
endpointDescriptor.bEndpointAddress:	.space 1
endpointDescriptor.bmAttributes:	.space 1
endpointDescriptor.wMaxPacketSize:	.space 2
endpointDescriptor.bInterval:	.space 1
.equ endpointDescriptor_size, . - endpointDescriptor
.equ endpointDescriptor.descriptor.bLength, endpointDescriptor.descriptor + descriptor.bLength - descriptor
.equ endpointDescriptor.descriptor.bDescriptorType, endpointDescriptor.descriptor + descriptor.bDescriptorType - descriptor
assert (endpointDescriptor_size == 7)

.text

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; memory locations
;-------------------------------------------------------------------------------
.struct (ti.saveSScreen+0xFFFF) & ~ 0xFFFF
cHeap:
.struct (ti.saveSScreen+21945) & ~ 0xFF
.equ cHeap_size, . - cHeap
.text
.struct ti.usbArea
.struct (. + (7)) & ~(7)
setupPacket:	.space setup_size
.struct (. + (0x1F)) & ~(0x1F)
rootHub:	.space device_size
usbMem:
.struct ti.usbInited & ~ 0x1FFF
.equ usbMem_size, . - usbMem
.struct (. + (0xFFF)) & ~(0xFFF)
periodicList:
.struct ti.usbInited & ~ 0xFF
.equ periodicList_size, . - periodicList
.struct (. + (0xFF)) & ~(0xFF)
.equ dummyHead, . + endpoint
	.space endpoint.base_size
.struct (. + (0x1F)) & ~(0x1F)
usedAddresses:	.space 0x80 >> 3
.equ usedAddresses_size, . - usedAddresses
eventCallback:	.space 3
eventCallback.data:	.space 3
currentDescriptors:	.space 3
selectedConfiguration:	.space 1
deviceStatus:	.space 1
tempEndpointStatus:	.space 2
.equ tempEndpointStatus_size, . - tempEndpointStatus
currentRole:	.space 3
freeList32Align32:	.space 3
freeList64Align256:	.space 3
timerList:	.space 3
resetList:	.space 3
.irp type, async, intr
	.space 1 ; clobber
\type\()CleanupReady:	.space 1
\type\()CleanupPending:	.space 1
 assert (\type\()CleanupPending+1 == .)
	.space 1 ; always -1
.endr
.if DEBUG
alloc32Align32:	.space 3
alloc64Align256:	.space 3
.endif
	assert (. <= ti.usbInited)
.text
.struct (ti.ramCodeTop+0xFF) & ~ 0xFF
osHeap:
.struct ti.heapTop & ~ 0xFF
.equ osHeap_size, . - osHeap
.text
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; usb constants
;-------------------------------------------------------------------------------
; enum usb_event
.struct 0
USB_ROLE_CHANGED_EVENT:	.space 1
USB_DEVICE_DISCONNECTED_EVENT:	.space 1
USB_DEVICE_CONNECTED_EVENT:	.space 1
USB_DEVICE_DISABLED_EVENT:	.space 1
USB_DEVICE_ENABLED_EVENT:	.space 1
USB_HUB_LOCAL_POWER_GOOD_EVENT:	.space 1
USB_HUB_LOCAL_POWER_LOST_EVENT:	.space 1
USB_DEVICE_RESUMED_EVENT:	.space 1
USB_DEVICE_SUSPENDED_EVENT:	.space 1
USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT:	.space 1
USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT:	.space 1
USB_DEFAULT_SETUP_EVENT:	.space 1
USB_HOST_CONFIGURE_EVENT:	.space 1
	; Temp debug events:
USB_DEVICE_INTERRUPT:	.space 1
USB_DEVICE_CONTROL_INTERRUPT:	.space 1
USB_DEVICE_DEVICE_INTERRUPT:	.space 1
USB_OTG_INTERRUPT:	.space 1
USB_HOST_INTERRUPT:	.space 1
USB_CONTROL_ERROR_INTERRUPT:	.space 1
USB_CONTROL_ABORT_INTERRUPT:	.space 1
USB_FIFO0_SHORT_PACKET_INTERRUPT:	.space 1
USB_FIFO1_SHORT_PACKET_INTERRUPT:	.space 1
USB_FIFO2_SHORT_PACKET_INTERRUPT:	.space 1
USB_FIFO3_SHORT_PACKET_INTERRUPT:	.space 1
USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT:	.space 1
USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT:	.space 1
USB_DEVICE_DMA_FINISH_INTERRUPT:	.space 1
USB_DEVICE_DMA_ERROR_INTERRUPT:	.space 1
USB_DEVICE_IDLE_INTERRUPT:	.space 1
USB_DEVICE_WAKEUP_INTERRUPT:	.space 1
USB_B_SRP_COMPLETE_INTERRUPT:	.space 1
USB_A_SRP_DETECT_INTERRUPT:	.space 1
USB_A_VBUS_ERROR_INTERRUPT:	.space 1
USB_B_SESSION_END_INTERRUPT:	.space 1
USB_OVERCURRENT_INTERRUPT:	.space 1
USB_HOST_PORT_CONNECT_STATUS_CHANGE_INTERRUPT:	.space 1
USB_HOST_PORT_ENABLE_DISABLE_CHANGE_INTERRUPT:	.space 1
USB_HOST_PORT_OVERCURRENT_CHANGE_INTERRUPT:	.space 1
USB_HOST_PORT_FORCE_PORT_RESUME_INTERRUPT:	.space 1
USB_HOST_SYSTEM_ERROR_INTERRUPT:	.space 1
.text

; enum usb_error
.struct 0
USB_SUCCESS:	.space 1
USB_IGNORE:	.space 1
USB_ERROR_SYSTEM:	.space 1
USB_ERROR_INVALID_PARAM:	.space 1
USB_ERROR_SCHEDULE_FULL:	.space 1
USB_ERROR_NO_DEVICE:	.space 1
USB_ERROR_NO_MEMORY:	.space 1
USB_ERROR_NOT_SUPPORTED:	.space 1
USB_ERROR_OVERFLOW:	.space 1
USB_ERROR_TIMEOUT:	.space 1
USB_ERROR_FAILED:	.space 1
.text

; enum usb_transfer_status
.equ USB_TRANSFER_COMPLETED, 0
.equ USB_TRANSFER_STALLED, 1 << 0
.equ USB_TRANSFER_NO_DEVICE, 1 << 1
.equ USB_TRANSFER_HOST_ERROR, 1 << 2
.equ USB_TRANSFER_ERROR, 1 << 3
.equ USB_TRANSFER_OVERFLOW, 1 << 4
.equ USB_TRANSFER_BUS_ERROR, 1 << 5
.equ USB_TRANSFER_FAILED, 1 << 6
.equ USB_TRANSFER_CANCELLED, 1 << 7

; enum usb_device_flags
.equ IS_NONE, 0
.equ IS_DISABLED, 1 << 0
.equ IS_ENABLED, 1 << 1
.equ IS_DEVICE, 1 << 2
.equ IS_HUB, 1 << 3
.equ IS_ATTACHED, 1 << 4

; enum usb_endpoint_flags
.equ MANUAL_TERMINATE, 0 << 0
.equ AUTO_TERMINATE, 1 << 0

; enum usb_role
.struct 0
ROLE_HOST:	.space 1 << 4
ROLE_DEVICE:	.space 1 << 4
.text
.struct 0
ROLE_A:	.space 1 << 5
ROLE_B:	.space 1 << 5
.text

; enum usb_transfer_direction
.struct 0
HOST_TO_DEVICE:	.space 1 << 7
DEVICE_TO_HOST:	.space 1 << 7
.text

; enum usb_request_type
.struct 0
STANDARD_REQUEST:	.space 1 << 5
CLASS_REQUEST:	.space 1 << 5
VENDOR_REQUEST:	.space 1 << 5
.text

; enum usb_recipient
.struct 0
RECIPIENT_DEVICE:	.space 1 << 0
RECIPIENT_INTERFACE:	.space 1 << 0
RECIPIENT_ENDPOINT:	.space 1 << 0
RECIPIENT_OTHER:	.space 1 << 0
.text

; enum usb_request
.struct 0
GET_STATUS_REQUEST:	.space 1
CLEAR_FEATURE_REQUEST:	.space 1
	.space 1
SET_FEATURE_REQUEST:	.space 1
	.space 1
SET_ADDRESS_REQUEST:	.space 1
GET_DESCRIPTOR_REQUEST:	.space 1
SET_DESCRIPTOR_REQUEST:	.space 1
GET_CONFIGURATION_REQUEST:	.space 1
SET_CONFIGURATION_REQUEST:	.space 1
GET_INTERFACE_REQUEST:	.space 1
SET_INTERFACE_REQUEST:	.space 1
SYNC_FRAME_REQUEST:	.space 1
.text

; enum usb_feature
.struct 0
ENDPOINT_HALT_FEATURE:	.space 1
DEVICE_REMOTE_WAKEUP_FEATURE:	.space 1
TEST_MODE_FEATURE:	.space 1
.text

; enum usb_device_status
.equ DEVICE_SELF_POWERED_STATUS, 1 << 0
.equ DEVICE_REMOTE_WAKEUP_STATUS, 1 << 1

; enum usb_endpoint_status
.equ ENDPOINT_HALT_STATUS, 1 << 0

; enum usb_descriptor_type
.struct 1
DEVICE_DESCRIPTOR:	.space 1
CONFIGURATION_DESCRIPTOR:	.space 1
STRING_DESCRIPTOR:	.space 1
INTERFACE_DESCRIPTOR:	.space 1
ENDPOINT_DESCRIPTOR:	.space 1
	.space 35
HUB_DESCRIPTOR:	.space 1
.text

; enum usb_class
.struct 9
HUB_CLASS:	.space 1
.text

; enum usb_transfer_type
.struct 0
CONTROL_TRANSFER:	.space 1
ISOCHRONOUS_TRANSFER:	.space 1
BULK_TRANSFER:	.space 1
INTERRUPT_TRANSFER:	.space 1
.text

.equ DEFAULT_RETRIES, 10

; SAFE_FS_BT = 83.54e-9 ; safe full-speed bit time (USB 2.0 spec section 5.11.3)
; SAFE_FS_SBT = SAFE_FS_BT * 7 / 6 ; safe full-speed stuffed bit time
; SAFE_FS_SBPT = SAFE_FS_SBT * 2 ; safe full-speed stuffed bit pair time
; FS_FT = 1e-3 ; full-speed frame time
; FS_SFT = FS_FT * 0.90 ; full-speed schedulable frame time
.equ FS_SBP_PER_FRAME, 4617 ; full-speed stuffed bit pairs per frame

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
.equ setupPacket.bmRequestType, setupPacket + setup.bmRequestType - setup
.equ setupPacket.wValue, setupPacket + setup.wValue - setup
.equ setupPacket.wLength, setupPacket + setup.wLength - setup
.equ rootHub.addr, rootHub + device.addr - device
.equ rootHub.refcnt, rootHub + device.refcnt - device
.equ rootHub.speed, rootHub + device.speed - device
.equ rootHub.find, rootHub + device.find - device
.equ rootHub.child, rootHub + device.child - device
.equ rootHub.data, rootHub + device.data - device
.equ dummyHead.next, dummyHead + endpoint.next - endpoint
.equ dummyHead.smask, dummyHead + endpoint.smask - endpoint

; Instruction encodings used for overlapping instructions and self-modifying code.
.equ LD_HL_IMM, 0x21
.equ LD_A_IMM, 0x3e
.equ JR_NZ, 0x20
.equ JP_NC, 0xd2
.equ IY_PREFIX, 0xfd
.equ NOP_OPCODE, 0x00
.equ RET_OPCODE, 0xc9
.equ RET_NZ, 0xc0
.equ RET_Z, 0xc8
.equ SCF_RET, 0xc937	; scf; ret
.equ EXCHANGE_CODE, 0xc9704e	; ld c,(hl); ld (hl),b; ret
.equ SCHEDULE_ENDPOINT_START, 0x292919	; add hl,de; add hl,hl; add hl,hl

msb_index FS_SBP_PER_FRAME_msb, FS_SBP_PER_FRAME
msb_index endpoint_info_eps_msb, endpoint.info.eps
.equ endpoint_info_eps_lsb, endpoint_info_eps_msb - 1
msb_index transfer_type_pid_msb, transfer.type.pid
msb_index transfer_status_halted_msb, transfer.status.halted
msb_index transfer_next_dummy_msb, transfer.next.dummy
msb_index UsbEndpointStride_msb, (ti.usbInEp2-ti.usbInEp1)
msb_index transfer_status_active_msb, transfer.status.active

usb_Init:
	call	ti.usb_DisableTimer
	call	ti.os.GetSystemInfo
.rept 4
	inc	hl
.endr
	bit	0, (hl)
	jr	z, usb_Init.84pce
	ld	a, 0x60
	ld	(_DefaultStandardDescriptors.device+deviceDescriptor.bcdDevice), a
	ld	hl, _DefaultStandardDescriptors.string83
	ld	(_DefaultStandardDescriptors.model), hl
usb_Init.84pce:
	ld	a, 1 ; mark pointers as invalid
	call	_Init
	set	5, (hl)	;ti.flags+$1B
	ld	hl, ti.mpTmr2Load
	ld	c, 12
	call	ti.MemClear
	ld	l, ti.tmrCtrl+1
	set	ti.bTmr2CountUp-8, (hl)
	dec	l	;ti.tmrCtrl
	res	ti.bTmr2Crystal, (hl)
	res	ti.bTmr2Overflow, (hl)
	set	ti.bTmr2Enable, (hl)
assert (ti.usbHandleKeys & 0x1F >= 3)
	ld	(ti.usbHandleKeys), a	;0
	sbc	hl, hl
assert (endpoint.smask+1 == endpoint.cmask)
assert (endpoint.smask+2 == endpoint.hubInfo)
	ld	(dummyHead.smask), hl
assert (deviceStatus+1 == tempEndpointStatus)
	ld	(deviceStatus), hl	;0
	ld	(timerList), hl	;0
	dec	hl
	ld	(asyncCleanupReady), hl	;-1
	ld	(intrCleanupReady), hl	;-1
	inc	hl
	ld	(rootHub.addr), a	;0
assert (rootHub.refcnt+3 == rootHub.speed)
	ld	(rootHub.refcnt+1), hl	;0
	ld	(rootHub.data), hl	;0
	ld	de, usedAddresses+1
	ld	b, usedAddresses_size-1
usb_Init.freeAddresses:
	ld	(de), a	;0
	inc	de
	djnz	usb_Init.freeAddresses
	ld	l, 3
	ld	(currentRole), hl
	add	hl, sp
;	ld	de,eventCallback;eventCallback.data,currentDescriptors
	ld	c, 9
	ldir
	ld	de, (hl)
	ld	(_ResetHostControllerFromUnknown.init), de
	dec	bc
	ld	hl, (currentDescriptors)
	add	hl, bc
	jr	c, usb_Init.nonDefaultStandardDescriptors
	ld	hl, _DefaultStandardDescriptors
	ld	(currentDescriptors), hl
usb_Init.nonDefaultStandardDescriptors:
	ld	hl, ti.mpUsbFifo0Cfg
	ld	(hl), a	;0
	inc	l	;ti.usbFifo1Cfg-$100
	inc	bc
	ld	(hl), bc	;0
	ld	l, ti.usbFifo0Map-0x100
	ld	(hl), 0x01
	inc	l	;ti.usbFifo1Map-$100
	ld	bc, 0x040302
	ld	(hl), bc
	ld	l, ti.usbEp1Map-0x100
	ld	(hl), a	;$00
	inc	l	;ti.usbEp2Map-$100
	ld	bc, 0x332211
	ld	(hl), bc
	ld	l, ti.usbIdle-0x100
	ld	(hl), 7
	ld	l, h	;ti.usbDevCtrl+1-$100
	ld	(hl), ti.bmUsbDevForceFullSpd >> 8
	dec	l	;usbDevCtrl-$100
	ld	(hl), ti.bmUsbDevReset | ti.bmUsbDevEn | ti.bmUsbGirqEn | ti.bmUsbRemoteWake
	ld	l, ti.usbPhyTmsr-0x100
	ld	(hl), ti.bmUsbUnplug
	ld	l, ti.usbGimr-0x100
	ld	(hl), a	;0
	ld	l, ti.usbCxImr-0x100
	ld	(hl), a	;0
	ld	l, ti.usbFifoRxImr-0x100
	ld	(hl), a	;0
	ld	l, ti.usbFifoTxImr-0x100
	ld	(hl), ti.bmUsbFifoTxInts
	ld	l, ti.usbDevImr-0x100
	ld	(hl), a	;0
	inc	l	;ti.usbDevImr+1-$100
	ld	(hl), ti.bmUsbIntDevIdle >> 8
	dec	h
	ld	l, ti.usbOtgIer
	ld	(hl), ti.bmUsbIntBSrpComplete | ti.bmUsbIntASrpDetect | ti.bmUsbIntAVbusErr ;or ti.bmUsbIntBSessEnd
	inc	l	;ti.usbOtgIer+1
	ld	(hl), (ti.bmUsbIntRoleChg | ti.bmUsbIntIdChg | ti.bmUsbIntOvercurr | ti.bmUsbIntBPlugRemoved | ti.bmUsbIntAPlugRemoved) >> 8
	ld	l, ti.usbImr
	ld	(hl), ti.usbIntLevelHigh
	call	_ResetHostControllerFromUnknown
	ld	(hl), hl
	ld	(hl), endpoint - endpoint.base
	ld	l, endpoint.prev
	ld	(hl), h
	ld	l, endpoint.info
	ld	(hl), endpoint.info.head
	ld	l, endpoint.overlay.status
	ld	(hl), endpoint.overlay.status.halted
	ld	hl, rootHub.find
	ld	(hl), IS_HUB | IS_ENABLED
assert (cHeap == 0xD10000)
	ld	l, a	;(cHeap-$D10000) and $FF
	ld	h, a	;(cHeap-$D10000) shr 8
	ld	b, cHeap_size >> 8
	srl	e
	call	c, usb_Init.initFreeList
	ld	h, +(osHeap-0xD10000) >> 8
	ld	b, osHeap_size >> 8
	srl	e
	call	c, usb_Init.initFreeList
	ld	h, +(usbMem-0xD10000) >> 8
	ld	b, usbMem_size >> 8
	call	usb_Init.initFreeList
assert (ti.usbHandleKeys & 0xFF >= 0x40 + 0x20 && ti.usbHandleKeys & 0xFF < 0x100 - 0x20)
	ld	a, +(ti.usbHandleKeys & ~ 0x1F - 0x20) & 0xFF
	ld	(ti.usbHandleKeys & ~ 0x1F + 0x20), a
assert (usbMem+usbMem_size == periodicList)
assert (~periodicList & 0xFF)
	ld	c, l	;0
	ld	a, e
	cpl
	and	a, 3
	ld	b, usb_PollTransfers.disable
	ld	de, _ScheduleEndpoint.disable
	jr	z, usb_Init.noPeriodicList
	ld	de, (0xD10000 & 0x70000 | (~FS_SBP_PER_FRAME << (31-FS_SBP_PER_FRAME_msb) & 0xffffffff)) >> 8 | 0xFF
	ld	b, a
	ld	a, 1 << 1
usb_Init.shift:
	rlca
	djnz	usb_Init.shift
	ld	(_ScheduleEndpoint.frameListSize+1), a
	ld	b, a
	dec.s	bc
	inc	l
	ld	(hl), de
	ld	de, periodicList+1+4
	ldir
	ld	a, h
	dec	a
	rrca
	ld	(_CleanupEndpoint.frameListEndSub1Shr1+1), a
	ld	b, usb_PollTransfers.enable
	ld	de, _ScheduleEndpoint.enable
usb_Init.noPeriodicList:
	ld	a, b
	ld	(usb_PollTransfers.enabled), a
	ld	(_ScheduleEndpoint.enabled), de
	ld	a, +(periodicList+periodicList_size-0xD10000) >> 8
	sub	a, h
	ld	b, a
	call	usb_Init.initFreeList
	ld	hl, ti.mpUsbOtgIsr+1
	call	_HandleRoleChgInt
	ret	nz
	or	a, a
	sbc	hl, hl
.if DEBUG
	ld	(alloc32Align32), hl	;0
	ld	(alloc64Align256), hl	;0
.endif
	ret
usb_Init.initFreeList:
	call	_Free64Align256.uninit
	ld	a, 32
usb_Init.loop:
	add	a, 32
	ld	l, a
	call	nz, _Free32Align32.uninit
	jr	nz, usb_Init.loop
	inc	h
	djnz	usb_Init.initFreeList
	ret

;-------------------------------------------------------------------------------
usb_Cleanup:
.if DEBUG
	ld	de, alloc32Align32
	ld	a, 99
	call	_DispatchEvent
.endif
	ld	hl, ti.mpUsbCmd
	call	_DisableSchedulesAndResetHostController.enter
;	xor	a,a
	ld	hl, ti.mpUsbGimr
	ld	(hl), a
	ld	l, ti.usbDevImr+1-0x100
	ld	(hl), a
;	ld	hl,ti.mpUsbDevIsr
;	ld	(hl),ti.bmUsbIntDevResume or ti.bmUsbIntDevSuspend
;	ld	l,ti.usbDevImr+1-$100
;	set	ti.bUsbIntDevDmaErr-8,(hl)
;	dec	l;ti.usbDevImr-$100
;	set	ti.bUsbIntDevDmaFin,(hl)
	ld	l, ti.usbFifoRxImr-0x100
	ld	(hl), ti.bmUsbFifoRxInts
	ld	l, ti.usbFifoTxImr-0x100
	ld	(hl), ti.bmUsbFifoTxInts
;	ld	l,a;ti.usbDevCtrl-$100
;	set	ti.bUsbDevReset,(hl)
;	res	ti.bUsbDevReset,(hl)
;	ld	l,ti.usbDevTest-$100
;	set	ti.bUsbTstClrFifo,(hl)
;	ld	l,h;ti.usbDevCtrl+1-$100
;	set	ti.bUsbDevForceFullSpd-8,(hl)
;	dec	l;ti.usbDevCtrl-$100
;	set	ti.bUsbGirqEn,(hl)
;	set	ti.bUsbDevEn,(hl)
;	set	7,(hl)
	call	_Init
	res	5, (hl)	;ti.flags+$1B
	ld	hl, ti.mpTmrCtrl+1
	res	ti.bTmr2CountUp-8, (hl)
	ret

;-------------------------------------------------------------------------------
usb_WaitForEvents.wait:
	ret	nz
usb_WaitForEvents:
	ld	hl, usb_WaitForEvents.wait
	push	hl

;-------------------------------------------------------------------------------
usb_WaitForInterrupt:
	ld	hl, ti.mpIntMask+1
	di
	set	ti.bIntUsb-8, (hl)
	ei
	halt

;-------------------------------------------------------------------------------
usb_HandleEvents:
;	xor	a,a
;	ld	hl,ti.mpUsbSts+1
;	bit	ti.bUsbHcHalted-8,(hl)
;	jq	z,.notHalted
;	;jq	nz,.halted
;	;bit	ti.bUsbRunStop,(hl)
;	;jq	nz,.notHalted
;;.halted:
;	; reset host controller (EHCI spec section 2.3)
;	ld	l,ti.usbCmd
;	ld	(hl),2 shl ti.bUsbFrameListSize
;	set	ti.bUsbHcReset,(hl)
;	ld	b,(48000000*250/1000-.resetPreCycles+.resetCycles-1)/.resetCycles
;.resetPreCycles := 8
;.waitForReset:
;	bit	ti.bUsbHcReset,(hl)	;12
;	jq	z,.reset		;+8
;.waitForReset.outer:
;	ld	c,a			;+(4
;.waitForReset.inner:
;	dec	c			;  +(4
;	jq	nz,.waitForReset.inner	;    +13)256-5
;	dec	a			;  +4
;	jq	nz,.waitForReset.outer	;  +13)256-5
;	djnz	.waitForReset		;+13
;.resetCycles := 12+8+(4+(4+13)*256-5+4+13)*256-5+13
;	inc	a ; zf = false
;	jq	usb_Init.timeout
;.reset:
;
;	ld	(hl),ti.bmUsbAsyncSchedEn or 2 shl ti.bUsbFrameListSize or ti.bmUsbRunStop; or ti.bmUsbPeriodicSchedEn
;.notHalted:
	or	a, a
	sbc	hl, hl
	ld	a, (ti.mpIntStat+1)
	and	a, ti.intUsb >> 8
	ret	z
	ld	hl, ti.mpUsbSts
	ld	a, (hl)
	ld	(_HandleHostInt.hack), a
	ld	l, ti.usbIsr
.irp type, Dev, Host, Otg
	bit	ti.bUsbInt\type\(), (hl)
	call	nz, _Handle\type\()Int
	ret	nz
.endr
	ld	a, ti.intUsb >> 8
	ld	(ti.mpIntAck+1), a
	ex	de, hl	; hl = 0
	or	a, a	; zf = false
	ret

;-------------------------------------------------------------------------------
usb_RefDevice:
	pop	bc
	ex	(sp), hl
	push	bc
	dec	l
	inc	l
	ret	z
usb_RefDevice.enter:
	set_mask	device.refcnt, l
	ld	bc, (hl)
	inc	bc
	ld	(hl), bc
	res_mask	device.refcnt, l
	ret

;-------------------------------------------------------------------------------
usb_UnrefDevice:
	pop	de
	ex	(sp), hl
	push	de
	dec	l
usb_UnrefDevice.recurse:
	inc	l
	ret	z
usb_UnrefDevice.enter:
	set_mask	device.refcnt, l
usb_UnrefDevice.refcnt:
	ld	de, (hl)
	ex	de, hl
	add	hl, de
	scf
	sbc	hl, de
	ex	de, hl
	ld	(hl), de
	jr	nz, usb_UnrefDevice.return
	set_mask	device.hub-device.refcnt, l
	ld	de, (hl)
	res_mask	device.hub-device.refcnt, l
	res_mask	device.refcnt, l
	call	_Free32Align32
	ex	de, hl
	dec	l
	jr	nz, usb_UnrefDevice.recurse
usb_UnrefDevice.return:
	ld	de, ti.mpUsbRange
usb_UnrefDevice.returnZero:
	or	a, a
usb_UnrefDevice.returnCarry:
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceHub:
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	sbc	hl, hl
	cp	a, iyl
	ret	z
	ld	de, (iy + device.hub)
usb_GetDeviceHub.returnDEIfValid:
	bit	0, e
	ret	nz
	ex	de, hl
	ret

;-------------------------------------------------------------------------------
usb_SetDeviceData:
	pop	de
	pop	iy
	ex	(sp), hl
	push	hl
	push	de
	xor	a, a
	cp	a, iyl
	ret	z
	ld	(iy + device.data), hl
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceData:
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	sbc	hl, hl
	cp	a, iyl
	ret	z
	ld	hl, (iy + device.data)
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceFlags:
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	sbc	hl, hl
	cp	a, iyl
	ret	z
	ld	l, (iy + device.find)
	ret

;-------------------------------------------------------------------------------
usb_FindDevice:
	pop	de
	pop	hl
	pop	iy
	pop	bc
	push	bc
	push	hl
	push	hl
	push	de
usb_FindDevice.enter:
	ld	de, -1
	add	iy, de
	inc	iy
	ex	de, hl
	jr	c, usb_FindDevice.child
	add	hl, de
	jr	c, usb_FindDevice.forceChild
	ld	iy, rootHub
	jr	usb_FindDevice.check
usb_FindDevice.child:
	bit_mask	IS_ATTACHED, c
	jr	nz, usb_FindDevice.sibling
usb_FindDevice.forceChild:
	bit	0, (iy + device.child)
	jr	nz, usb_FindDevice.sibling
	ld	iy, (iy + device.child)
usb_FindDevice.check:
	ld	a, (iy + device.find)
	and	a, c
	jr	nz, usb_FindDevice.child
	lea	hl, iy+0
	ret
usb_FindDevice.hub:
	ld	iy, (iy + device.hub)
	lea	hl, iy+0
	ld	a, l
	rrca
	jp	c, usb_UnrefDevice.returnZero
	sbc	hl, de
	ret	z
usb_FindDevice.sibling:
	bit	0, (iy + device.sibling)
	jr	nz, usb_FindDevice.hub
	ld	iy, (iy + device.sibling)
	jr	usb_FindDevice.check

;-------------------------------------------------------------------------------
usb_ResetDevice:
	call	_Error.check
	ld	de, (ix+6)
	ld	a, e
	or	a, a
	jp	z, _Error.INVALID_PARAM
	ld	hl, currentRole
	bit	ti.bUsbRole-16, (hl)
	jp	nz, _Error.NOT_SUPPORTED
	ld	hl, (rootHub.child)
	sbc	hl, de
	jr	nz, usb_ResetDevice.hub
	ld	a, 12 ; WARNING: This assumes flash wait states port is 3, to get at least 100ms!
	call	ti.DelayTenTimesAms
	ld	hl, ti.mpUsbPortStsCtrl+1
	set	ti.bUsbPortReset-8, (hl)
	ld	a, 6 ; WARNING: This assumes flash wait states port is 3, to get at least 50ms!
	call	ti.DelayTenTimesAms
	res	ti.bUsbPortReset-8, (hl)
	ld	a, 12 ; WARNING: This assumes flash wait states port is 3, to get at least 10ms per spec... jk 100ms for non-conforming devices!
	jp	ti.DelayTenTimesAms
usb_ResetDevice.hub:
	call	_Alloc32Align32
	jp	nz, _Error.NO_MEMORY
	ld	iy, usb_ResetDevice.resetListInd-reset.next
usb_ResetDevice.skip:
	ld	iy, (iy + reset.next)
	bit	0, (iy + reset.next)
	jr	z, usb_ResetDevice.skip
	ld	(hl), 1
	ld	(iy + reset.next), hl
.rept reset.device-reset.next
	inc	l
.endr
	ld	(hl), de
usb_ResetDevice.next:
	ld	a, iyl
assert (resetList & 0x1F != reset.next)
	cp	a, resetList & 0xFF
	ret	nz
	ld	hl, (resetList)
.equ usb_ResetDevice.resetListInd, .-3
.equ usb_ResetDevice.resetList, resetList
assert (usb_ResetDevice.resetList == resetList)
	bit	0, l
	ret	nz
	ld	bc, usb_ResetDevice.handler
	push	hl
	push	bc
.rept reset.device
	inc	l
.endr
	ld	iy, (hl)
.rept reset.setup-reset.device
	inc	l
.endr
	push	hl
	push	hl
	ld	c, (iy + device.portNbr)
	xor	a, a
.macro write_setup_byte iteration, value
 .if \iteration != 1
	inc	l
 .endif
	ld	(hl), \value
.endm
write_setup_byte 1, HOST_TO_DEVICE | CLASS_REQUEST | RECIPIENT_OTHER
write_setup_byte 2, SET_FEATURE_REQUEST
write_setup_byte 3, 4
write_setup_byte 4, a
write_setup_byte 5, c
write_setup_byte 6, a
write_setup_byte 7, a
write_setup_byte 8, a
.purgem write_setup_byte
	ld	hl, (iy + device.hub)
	jp	usb_SetConfiguration.schedule
usb_ResetDevice.handler:
	call	_Error.check
	ld	a, (ix+12)
	or	a, (ix+9)
	ret	z
usb_ResetDevice.abort:
	ld	iy, resetList
usb_ResetDevice.free:
	call	z, _Error.check
	ld	hl, (iy)
	ld	de, (hl)
	ld	(iy), de
	call	_Free32Align32
	jr	usb_ResetDevice.next
; Input:
;  cf = false
;  de = device
; Output:
;  af = ?
;  bc = ?
;  de = ?
;  hl = ?
;  iy = ?
usb_ResetDevice.enabled:
	ld	iy, (resetList)
usb_ResetDevice.enabled.enter:
	dec	iyl
	ret	z
	ld	hl, (iy + reset.device+1)
	sbc	hl, de
assert (hub.setup.wValue+0+1 == hub.setup.wValue+1)
assert (hub.setup.wValue+0+2 == hub.setup.wIndex+0)
	ld	h, DEVICE_DESCRIPTOR
	ld	(iy + reset.setup.wValue+0+1), hl
assert (hub.setup.wIndex+1+1 == hub.setup.wLength+0)
assert (hub.setup.wIndex+1+2 == hub.setup.wLength+1)
	ld	h, 8
	ld	(iy + reset.setup.wIndex+1+1), hl
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE) << 0 | GET_DESCRIPTOR_REQUEST << 8 | 0 << 16
	ld	(iy + reset.setup.bmRequestType+1), hl
	ld	hl, usb_ResetDevice.descriptor
	pea	iy+1
	push	hl
	pea	iy + reset.desc+1
	pea	iy + reset.setup+1
	ld	iy, (iy + reset.device+1)
	call	z, _CreateDefaultControlEndpoint.enable
	push	iy
	call	z, usb_ScheduleControlTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ret
usb_ResetDevice.descriptor:
	call	_Error.check
	ld	a, (ix+12)
	xor	a, 8
	or	a, (ix+9)
	jr	nz, usb_ResetDevice.abort
	ld	hl, usedAddresses
	ld	b, usedAddresses_size
	scf
usb_ResetDevice.address.search:
	ld	c, (hl)
	adc	a, c
	jr	c, usb_ResetDevice.address.next
	or	a, c
	ld	(hl), a
	xor	a, c
	ld	c, 8
	mlt	bc
usb_ResetDevice.address.shift:
	dec	c
	rrca
	jr	nc, usb_ResetDevice.address.shift
	sbc	a, c
	ld	iy, (ix+15)
assert (~HOST_TO_DEVICE | STANDARD_REQUEST | RECIPIENT_DEVICE)
	ld	(iy + reset.setup.bmRequestType), b
assert (GET_DESCRIPTOR_REQUEST-1 == SET_ADDRESS_REQUEST)
	dec	(iy + reset.setup.bRequest)
	ld	(iy + reset.setup.wValue+0), a
	ld	(iy + reset.setup.wValue+1), b
	ld	(iy + reset.setup.wLength+0), b
	ld	a, (iy + reset.desc.bDeviceClass)
	ld	c, (iy + reset.desc.bMaxPacketSize0)
	ld	hl, usb_ResetDevice.enable
	push	iy
	push	hl
	push	hl
	pea	iy + reset.setup
	ld	iy, (ix+6)
	ld	(iy + (endpoint.maxPktLen - endpoint)), c
	push	iy
	cp	a, HUB_CLASS
	jr	nz, usb_ResetDevice.notHub
	ld	iy, (iy + (endpoint.device - endpoint))
	lea	hl, iy + device.find
assert (HUB_CLASS >> 1 == IS_HUB-IS_DEVICE)
	rra
	add	a, (hl)
	ld	(hl), a
usb_ResetDevice.notHub:
	call	usb_ScheduleControlTransfer
	ld	a, l
	or	a, a
	jp	z, usb_Transfer.return
.equ usb_ResetDevice.ld_hl, LD_HL_IMM
	.db	usb_ResetDevice.ld_hl
usb_ResetDevice.address.next:
	inc	l
	djnz	usb_ResetDevice.address.search
usb_ResetDevice.address.abort:
	jp	usb_ResetDevice.abort
usb_ResetDevice.enable:
	call	_Error.check
	ld	a, (ix+9)
	or	a, a
	jp	nz, usb_ResetDevice.abort
	ld	iy, (ix+15)
	ld	a, (iy + reset.setup.wValue+0)
	ld	iy, (ix+6)
	ld	(iy + (endpoint.addr - endpoint)), a
	ld	iy, (iy + (endpoint.device - endpoint))
	ld	(iy + device.addr), a
	lea	de, iy+0
	ld	a, USB_DEVICE_ENABLED_EVENT
	call	_DispatchEvent
	jp	nz, usb_Transfer.return
	inc	e
	jp	usb_ResetDevice.abort

;-------------------------------------------------------------------------------
usb_DisableDevice:
	call	_Error.check
	ld	de, (ix+6)
	ld	a, e
	or	a, a
	jp	z, _Error.INVALID_PARAM
	ld	hl, (rootHub.child)
	sbc	hl, de
	jp	z, _HandlePortPortEnInt.disable
	jp	_Error.NOT_SUPPORTED

;-------------------------------------------------------------------------------
usb_GetDeviceAddress:
	pop	hl
	ex	(sp), iy
	xor	a, a
	cp	a, iyl
	sbc	a, a
	and	a, (iy + device.addr)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceSpeed:
	pop	hl
	ex	(sp), iy
	xor	a, a
	cp	a, iyl
	sbc	a, a
	cpl
	or	a, (iy + device.speed)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetConfigurationDescriptorTotalLength:
	call	_Error.check
	call	_Alloc32Align32
	ret	nz
	push	hl
	push	hl
	ld	(hl), a
	set_mask	4, l
	ld	de, DEFAULT_RETRIES
	push	de
	push	hl
	set_mask	12 ^ 4, l
	push	hl
	ld	c, (ix+9)
.irp value, "DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE", GET_DESCRIPTOR_REQUEST, c, CONFIGURATION_DESCRIPTOR, a, a, 4
	ld	(hl), \value
	inc	l
.endr
	ld	(hl), a
	ld	hl, (ix+6)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
	ld	iy, (ix-6)
	ld	a, (iy+0)
	ld	de, (iy+6)
	lea	hl, iy+0
	call	_Free32Align32
	ex.s	de, hl
	xor	a, 4
	jr	z, usb_GetDescriptor.return
	sbc	hl, hl
	jr	usb_GetDescriptor.return

;-------------------------------------------------------------------------------
usb_GetDescriptor:
	call	_Error.check
	ld	c, GET_DESCRIPTOR_REQUEST
	ld	de, (ix+21)
	call	_Alloc32Align32
	ld	(hl), DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE
usb_GetDescriptor.enter:
	jp	nz, _Error.NO_MEMORY
	push	hl
	push	de
	ld	de, DEFAULT_RETRIES
	push	de
	ld	de, (ix+15)
	push	de
	push	hl
	inc	l
	ld	(hl), c
	inc	l
	ld	c, (ix+12)
	ld	(hl), c
	inc	l
	ld	c, (ix+9)
	ld	(hl), c
	inc	l
	ld	(hl), a
	inc	l
	ld	(hl), a
usb_GetDescriptor.length:
	inc	l
	ld	de, (ix+18)
	ld	(hl), de
usb_GetDescriptor.endpoint:
	ld	hl, (ix+6)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
usb_GetDescriptor.free:
	ex	de, hl
	ld	hl, (ix-6)
	call	_Free32Align32
	ex	de, hl
usb_GetDescriptor.return:
	jp	usb_Transfer.return

;-------------------------------------------------------------------------------
usb_SetDescriptor:
	call	_Error.check
	ld	c, SET_DESCRIPTOR_REQUEST
	sbc	hl, hl
	ex	de, hl
	call	_Alloc32Align32
	ld	(hl), d	;HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	jr	usb_GetDescriptor.enter

;-------------------------------------------------------------------------------
usb_GetStringDescriptor:
	call	_Error.check
	ld	c, GET_DESCRIPTOR_REQUEST
	ld	de, (ix+21)
	call	_Alloc32Align32
	ld	(hl), DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE
usb_GetStringDescriptor.enter:
	jp	nz, _Error.NO_MEMORY
	push	hl
	push	de
	ld	de, DEFAULT_RETRIES
	push	de
	ld	de, (ix+15)
	push	de
	push	hl
	inc	l
	ld	(hl), c
	inc	l
	ld	c, (ix+9)
	ld	(hl), c
	inc	l
	ld	(hl), STRING_DESCRIPTOR
	inc	l
	ld	de, (ix+12)
	ld	(hl), e
	inc	l
	ld	(hl), d
	jr	usb_GetDescriptor.length

;-------------------------------------------------------------------------------
usb_SetStringDescriptor:
	call	_Error.check
	ld	c, SET_DESCRIPTOR_REQUEST
	sbc	hl, hl
	ex	de, hl
	call	_Alloc32Align32
	ld	(hl), d	;HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	jr	usb_GetStringDescriptor.enter

;-------------------------------------------------------------------------------
usb_GetConfiguration:
	call	_Error.check
	sbc	hl, hl
	ex	de, hl
	call	_Alloc32Align32
	jp	nz, _Error.NO_MEMORY
	push	hl
	push	de
	ld	e, DEFAULT_RETRIES
	push	de
	ld	de, (ix+9)
	push	de
	push	hl
	ld	(hl), DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE
	inc	l
	ld	(hl), GET_CONFIGURATION_REQUEST
.rept 3
	inc	l
	ld	(hl), a
.endr
usb_GetConfiguration.length:
	inc	l
	ld	(hl), a
	inc	l
	ld	(hl), 1
	inc	l
	ld	(hl), a
	jp	usb_GetDescriptor.endpoint

;-------------------------------------------------------------------------------
usb_SetConfiguration:
	call	_Error.check
	ld	de, (ix+12)
	ld	iy, (ix+6)
	push	ix
	ld	ix, (ix+9)
assert (configurationDescriptor.bNumInterfaces+1 == configurationDescriptor.bConfigurationValue)
	ld	bc, (ix + configurationDescriptor.bNumInterfaces)
	push	bc
	ld	b, c
	call	_ParseInterfaceDescriptors.host
	pop	bc
	pop	ix
	jp	nz, _Error.INVALID_PARAM
	call	_Alloc32Align32
	jp	nz, _Error.NO_MEMORY
	ld	e, d
	push	hl
	push	de
	ld	e, DEFAULT_RETRIES
	push	de
	push	de
	push	hl
	ld	(hl), d	;HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	inc	l
	ld	(hl), SET_CONFIGURATION_REQUEST
	inc	l
	ld	(hl), b
.rept 2
	inc	l
	ld	(hl), a
.endr
usb_SetConfiguration.length:
.rept 3
	inc	l
	ld	(hl), a
.endr
	ld	hl, (ix+6)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
	add	hl, de
	xor	a, a
	sbc	hl, de
	jr	nz, usb_SetConfiguration.free
	ld	iy, (ix+6)
	bit_mask	IS_DEVICE, (iy + device.find)
usb_SetConfiguration.free:
	jp	nz, usb_GetDescriptor.free
	lea	hl, iy+0
	ld	de, _HubHandler.descriptor
	ld	iy, (ix-6)
	push	iy
	push	de
	pea	iy + hub.desc
	push	iy
	ld	b, 32
usb_SetConfiguration.clear:
	ld	(iy), a
	inc	iy
	djnz	usb_SetConfiguration.clear
	ld	(iy + hub.setup.bmRequestType-32), DEVICE_TO_HOST | CLASS_REQUEST | RECIPIENT_DEVICE
	ld	(iy + hub.setup.bRequest-32), GET_DESCRIPTOR_REQUEST
	ld	(iy + hub.setup.wValue+1-32), HUB_DESCRIPTOR
	ld	(iy + hub.setup.wLength+0-32), hub.desc_size
usb_SetConfiguration.schedule:
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ScheduleControlTransfer
	jp	usb_Transfer.return

;-------------------------------------------------------------------------------
usb_GetInterface:
	call	_Error.check
	sbc	hl, hl
	ex	de, hl
	call	_Alloc32Align32
	jp	nz, _Error.NO_MEMORY
	push	hl
	push	de
	ld	e, DEFAULT_RETRIES
	push	de
	ld	de, (ix+12)
	push	de
	push	hl
	ld	(hl), DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_INTERFACE
	inc	l
	ld	(hl), GET_INTERFACE_REQUEST
.rept 2
	inc	l
	ld	(hl), a
.endr
	inc	l
	ld	e, (ix+9)
	ld	(hl), e
	jp	usb_GetConfiguration.length

;-------------------------------------------------------------------------------
usb_SetInterface:
	call	_Error.check
	ld	de, (ix+12)
	ld	iy, (ix+6)
	push	ix
	ld	ix, (ix+9)
assert (interfaceDescriptor.bInterfaceNumber+1 == interfaceDescriptor.bAlternateSetting)
	ld	bc, (ix + interfaceDescriptor.bInterfaceNumber)
	push	bc
	ld	a, b
	ld	b, 2
	call	_ParseInterfaceDescriptors.dec
	pop	bc
	pop	ix
	jp	nz, _Error.INVALID_PARAM
	call	_Alloc32Align32
	jp	nz, _Error.NO_MEMORY
	ld	e, d
	push	hl
	push	de
	ld	e, DEFAULT_RETRIES
	push	de
	push	de
	push	hl
.irp value, "HOST_TO_DEVICE | STANDARD_REQUEST | RECIPIENT_INTERFACE", SET_INTERFACE_REQUEST, b, a
	ld	(hl), \value
	inc	l
.endr
	ld	(hl), c
	jp	usb_SetConfiguration.length

;-------------------------------------------------------------------------------
usb_SetEndpointHalt:
	ld	b, SET_FEATURE_REQUEST
	jr	usb_ClearEndpointHalt.enter

;-------------------------------------------------------------------------------
usb_ClearEndpointHalt:
	ld	b, CLEAR_FEATURE_REQUEST
usb_ClearEndpointHalt.enter:
	call	_Error.check
	ld	iy, (ix+6)
	bit_mask	BULK_TRANSFER & INTERRUPT_TRANSFER, (iy + (endpoint.transferInfo - endpoint))
	jp	z, _Error.INVALID_PARAM
	call	usb_GetEndpointAddress.enter
	ld	hl, currentRole
	bit	ti.bUsbRole-16, (hl)
	jr	nz, usb_ClearEndpointHalt.device
	ld	hl, (iy + (endpoint.first - endpoint))
	bit_mask	transfer.next.dummy, (hl)
	jp	z, _Error.NOT_SUPPORTED
	call	_Alloc32Align32
	jp	nz, _Error.NO_MEMORY
	inc	de	;0
	push	hl
	push	de
	ld	e, DEFAULT_RETRIES
	push	de
	push	hl
	push	hl
assert (~ENDPOINT_HALT_FEATURE)
.irp value, "HOST_TO_DEVICE | STANDARD_REQUEST | RECIPIENT_ENDPOINT", b, d, d, a, d, d
	ld	(hl), \value
	inc	l
.endr
	ld	(hl), d
	xor	a, a
	ld	hl, (iy + (endpoint.device - endpoint)+1)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
	ld	iy, (ix+6)
	ex	de, hl
	ld	hl, (ix-6)
	call	_Free32Align32
	ex	de, hl
	res_mask	(transfer.remaining.dt >> 8), (iy + (endpoint.overlay.remaining + 1 - endpoint))
usb_ClearEndpointHalt.return:
	jp	usb_Transfer.return
usb_ClearEndpointHalt.device:
	or	a, a
	jp	z, _Error.INVALID_PARAM
	call	_HandleCxSetupInt.lookupEndpointRegister
	ld	a, (hl)
	or	a, (ti.bmUsbEpReset | ti.bmUsbEpStall) >> 8
	djnz	usb_ClearEndpointHalt.set
	and	a, ~ ti.bmUsbEpStall >> 8
	ld	(hl), a
	ret
usb_ClearEndpointHalt.set:
	and	a, ~ ti.bmUsbEpReset >> 8
	ld	(hl), a
	ld	bc, USB_TRANSFER_CANCELLED | USB_TRANSFER_STALLED
	lea	ix, iy+0
	call	_FlushEndpoint
	ret	c
	pop	bc
	pop	ix
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceEndpoint:
	pop	bc
	pop	hl
	pop	de
	push	de
	push	hl
	push	bc
usb_GetDeviceEndpoint.check:
	inc	l
	dec	l
	ret	z
	ld	a, e
usb_GetDeviceEndpoint.enter:
	and	a, endpoint.transferInfo.dir | endpoint.info.ep
usb_GetDeviceEndpoint.masked:
	ld	hl, (hl)
	bit	0, l
	jr	nz, usb_GetDeviceEndpoint.returnCarry
	rlca
	or	a, l
	ld	l, a
	ld	h, (hl)
	ld	l, endpoint
	ld	a, h
	inc	a
	ret	nz
usb_GetDeviceEndpoint.returnCarry:
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointDevice:
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	sbc	hl, hl
	cp	a, iyl
	ret	z
	ld	de, (iy + (endpoint.device - endpoint))
	jp	usb_GetDeviceHub.returnDEIfValid

;-------------------------------------------------------------------------------
usb_SetEndpointData:
	pop	de
	pop	iy
	ex	(sp), hl
	push	hl
	push	de
	xor	a, a
	cp	a, iyl
	ret	z
	ld	(iy + (endpoint.data - endpoint)), hl
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointData:
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	sbc	hl, hl
	cp	a, iyl
	ret	z
	ld	hl, (iy + (endpoint.data - endpoint))
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointAddress:
	pop	hl
	ex	(sp), iy
	push	hl
usb_GetEndpointAddress.enter:
	ld	de, -1
	add	iy, de
	ld	a, e
	ret	nc
	ld	a, (iy + (endpoint.transferInfo - endpoint)+1)
	rlca
	ld	a, (iy + (endpoint.info - endpoint)+1)
	rla
	rrca
	and	a, endpoint.transferInfo.dir | endpoint.info.ep
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointTransferType:
	pop	hl
	ex	(sp), iy
	ld	a, (iy + (endpoint.transferInfo - endpoint))
	and	a, endpoint.transferInfo.type
	ld	c, a
	xor	a, a
	cp	a, iyl
	sbc	a, a
	cpl
	or	a, c
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointInterval:
	pop	hl
	ex	(sp), iy
	xor	a, a
	cp	a, iyl
	sbc	a, a
	and	a, (iy + (endpoint.interval - endpoint))
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointMaxPacketSize:
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	cp	a, iyl
	ret	z
	ld	de, (iy + (endpoint.maxPktLen - endpoint))
	ld	a, d
	and	a, 0b111
	ld	d, a
	ex.s	de, hl
	ret

;-------------------------------------------------------------------------------
usb_SetEndpointFlags:
	pop	de
	pop	iy
	ex	(sp), hl
	push	hl
	push	de
	xor	a, a
	cp	a, iyl
	ret	z
	ld	a, (iy + (endpoint.flags - endpoint))
	xor	a, l
	and	a, ~ endpoint.flags.autoTerm
	xor	a, l
	ld	(iy + (endpoint.flags - endpoint)), a
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointFlags:
	pop	hl
	ex	(sp), iy
	xor	a, a
	cp	a, iyl
	rla
	and	a, (iy + (endpoint.flags - endpoint))
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetRole:
	ld	hl, (currentRole)
	ret

;-------------------------------------------------------------------------------
usb_GetFrameNumber:
	ld	hl, ti.mpUsbOtgCsr+2
	bit	ti.bUsbRole-16, (hl)
	ld	l, ti.usbFrameIdx
	jr	z, usb_GetFrameNumber.load
	ld	l, ti.usbSofFrNum-0x100
	inc	h
usb_GetFrameNumber.load:
	ld	de, (hl)
	ld	a, (hl)
	cp	a, e
	jr	c, usb_GetFrameNumber.load
	ld	e, a
	dec	h
	ex	de, hl
	ret	nz
.rept 3
	add	hl, hl
.endr
	ret

;-------------------------------------------------------------------------------
usb_ControlTransfer:
	ld	hl, usb_ScheduleControlTransfer.enter
	jr	usb_Transfer.enter

;-------------------------------------------------------------------------------
usb_Transfer:
	ld	hl, usb_ScheduleTransfer.enter
usb_Transfer.enter:
	ld	(usb_Transfer.dispatch), hl
	call	_Error.check
	ld	hl, (ix+15)
	push	hl
	ld	hl, (ix+18)
	push	hl
	sbc	hl, hl
	inc	l
	push	hl
	ld	hl, usb_Transfer.callback
	ld	(ix+15), hl
	ld	(ix+18), ix
	call	0
.equ usb_Transfer.dispatch, .-3
usb_Transfer.wait:
	call	usb_WaitForEvents
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	nz, usb_Transfer.return
	ld	l, (ix-12)
	dec	l
	jr	z, usb_Transfer.wait
	inc	l
usb_Transfer.return:
	ld	sp, ix
	pop	ix
	ret

usb_Transfer.callback:
	ld	hl, 12
	add	hl, sp
	ld	iy, (hl)
.rept 3
	dec	hl
.endr
	ld	bc, (hl)
.rept 3
	dec	hl
.endr
	ld	a, (hl)
	sbc	hl, hl
	or	a, a	;USB_TRANSFER_COMPLETED
	jr	z, usb_Transfer.complete
	ld	e, a
.irp error, NO_DEVICE, OVERFLOW
	ld	a, USB_ERROR_\error\()
	bit_mask	USB_TRANSFER_\error\(), e
	jr	nz, usb_Transfer.complete
.endr
	ld	a, e
	and	a, USB_TRANSFER_CANCELLED | USB_TRANSFER_STALLED
	ld	a, USB_ERROR_FAILED
	jr	nz, usb_Transfer.complete
	ld	de, (iy-6)
	inc	l
	add	hl, de
	inc	l
	ret	c
	sbc	hl, hl
	dec	hl
	adc	hl, de
	ld	(iy-6), hl
	ld	hl, 1
	ret	nz
assert (USB_ERROR_TIMEOUT == USB_ERROR_FAILED-1)
	dec	a	;USB_ERROR_TIMEOUT
	dec	hl
	or	a, a
usb_Transfer.complete:
	ld	(iy-12), a
	ld	de, (iy-9)
	adc	hl, de
	ret	z
	ld	(hl), bc
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
usb_ScheduleControlTransfer.deviceControl:
	cp	a, a
usb_ScheduleControlTransfer.notControl:
	ld	iy, (ix+9)
	ld	bc, (iy + setup.wLength)
	inc	bc
	dec.s	bc
	ld	de, (ix+12)
	ld	iy, (ix+6)
	jp	nz, usb_ScheduleTransfer.notControl
usb_ScheduleTransfer.deviceControl:
	ld	hl, (setupPacket.wLength)
	inc	hl
	dec.s	hl
	sbc	hl, bc
	jr	nc, usb_ScheduleControlTransfer.min
	add	hl, bc
	push	hl
	pop	bc
usb_ScheduleControlTransfer.min:
	ld	a, c
	or	a, b
	jr	z, usb_ScheduleControlTransfer.zlp
	ld	a, (setupPacket.bmRequestType)
	rlca
	push	af
	ld	a, transfer.type.ioc >> 1
	rla
	call	_QueueTransfer
	pop	af
	ret	nc
	xor	a, a
	call	_ExecuteDma
	ret	nc
	jp	usb_Transfer.return
usb_ScheduleControlTransfer.zlp:
	ld	hl, ti.mpUsbCxFifo
	ld	(hl), ti.bmCxFifoFin
	ld	de, (ix+18)
	ld	hl, usb_Transfer.return
	push	iy
	push	bc
	push	bc
	push	de
	push	hl
	ld	hl, (ix+15)
_DispatchEvent.dispatch:
	jp	(hl)
usb_ScheduleControlTransfer:
	call	_Error.check
usb_ScheduleControlTransfer.enter:
	call	usb_ScheduleControlTransfer.check
	ld	iy, (ix+6)
	ld	a, (iy + (endpoint.transferInfo - endpoint))
	and	a, endpoint.transferInfo.type
assert (~CONTROL_TRANSFER)
	jr	nz, usb_ScheduleControlTransfer.notControl
	ld	hl, currentRole
	bit	ti.bUsbRole-16, (hl)
	jr	nz, usb_ScheduleControlTransfer.deviceControl
usb_ScheduleControlTransfer.control:
	ld	a, 0b00001110
	ld	bc, 8
	ld	de, (ix+9)
	call	usb_ScheduleControlTransfer.queueStage
	ld	iy, (ix+9)
	ld	a, (iy + setup.bmRequestType)
	and	a, DEVICE_TO_HOST
	ld	bc, (iy + setup.wLength)
	inc.s	bc
	cpi.s
	ld	de, (ix+12)
	rlca
	push	af
	call	pe, _QueueTransfer
	pop	af
	xor	a, 0b10001101
	ld	bc, transfer.remaining.dt
usb_ScheduleControlTransfer.queueStage:
	call	_CreateDummyTransfer
assert ((endpoint-1) & 1)
	dec	iy
	jp	z, _FillTransfer
	jp	_Error.NO_MEMORY
usb_ScheduleControlTransfer.check:
	ld	hl, (ix+9)
	add	hl, de
	or	a, a
	sbc	hl, de
usb_ScheduleControlTransfer.invalidParam:
	jp	z, _Error.INVALID_PARAM
usb_ScheduleTransfer.check:
	ld	hl, (ix+6)
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	z, usb_ScheduleControlTransfer.invalidParam
	ld	l, endpoint.device
	ld	iy, (hl)
	bit_mask	IS_ENABLED, (iy + device.find)
	jp	z, _Error.NO_DEVICE
	ld	hl, (ix+15)
	add	hl, de
	or	a, a
	sbc	hl, de
	ret	nz
	ld	hl, _DefaultHandler
	ld	(ix+15), hl
	ret

;-------------------------------------------------------------------------------
usb_ScheduleTransfer.control:
	bit	ti.bUsbRole-16, l
	jp	nz, usb_ScheduleTransfer.deviceControl
	ld	iy, (ix+9)
	lea	de, iy+setup_size
	ld	(ix+12), de
	jr	usb_ScheduleControlTransfer.control
usb_ScheduleTransfer:
	call	_Error.check
usb_ScheduleTransfer.enter:
	call	usb_ScheduleTransfer.check
	ld	bc, (ix+12)
	ld	de, (ix+9)
	ld	iy, (ix+6)
	ld	hl, (currentRole)
	ld	a, (iy + (endpoint.transferInfo - endpoint))
	ld	h, a
	and	a, endpoint.transferInfo.type
assert (~CONTROL_TRANSFER)
	jr	z, usb_ScheduleTransfer.control
usb_ScheduleTransfer.notControl:
	rlc	h
	bit	ti.bUsbRole-16, l
	jr	nz, usb_ScheduleTransfer.device
assert (~ISOCHRONOUS_TRANSFER-1)
	dec	a
	jr	nz, usb_ScheduleTransfer.queue
	jp	_Error.NOT_SUPPORTED
usb_ScheduleTransfer.device:
	jr	nc, usb_ScheduleTransfer.queue
	ld	a, (iy + (endpoint.overlay.fifo - endpoint))
	cpl
	ld	hl, ti.mpUsbFifoTxImr
	and	a, (hl)
	ld	(hl), a
assert (ti.mpUsbFifoTxImr >> 8 & 0xFF == 1)
usb_ScheduleTransfer.queue:
	ld	a, h
	and	a, 1
	or	a, transfer.type.ioc

; Input:
;  a = ioc shl 7 or dir
;  bc = length
;  de = buffer
;  (ix+6) = endpoint
;  (ix+15) = handler
;  (ix+18) = data
_QueueTransfer:
	call	_CreateDummyTransfer
	jp	nz, _Error.NO_MEMORY
	ld	(_QueueTransfer.dummy), hl
	or	a, transfer.type.cerr
	push	af
	sbc	hl, hl
	sbc	hl, bc
	jp	z, _QueueTransfer.zlp
_QueueTransfer.next:
	push	de
	ld	a, d
	and	a, 0xF
	ld	d, a
	ld	hl, 0x5000
	sbc.s	hl, de
	sbc	hl, bc
	jr	c, _QueueTransfer.notEnd
	sbc	hl, hl
	bit_mask	endpoint.flags.autoTerm, (iy + (endpoint.flags - endpoint))
_QueueTransfer.notEnd:
	add	hl, bc
	jr	z, _QueueTransfer.last
	ld	de, (iy + (endpoint.maxPktLen - endpoint))
	ex.s	de, hl
	bit_mask	endpoint.flags.po2Mps, (iy + (endpoint.flags - endpoint))
	jr	nz, _QueueTransfer.modPo2
	ld	a, h
	and	a, 7
	ld	h, a
	or	a, l
	jp	z, _Error.INVALID_PARAM
	push	bc
	push	de
	ld	b, -1
_QueueTransfer.modShift:
	inc	b
	add.s	hl, hl
	jr	nc, _QueueTransfer.modShift
	ex	de, hl
_QueueTransfer.modLoop:
	rr	d
	rr	e
	sbc	hl, de
	jr	nc, _QueueTransfer.modSkip
	add	hl, de
	or	a, a
_QueueTransfer.modSkip:
	djnz	_QueueTransfer.modLoop
	pop	de
	pop	bc
	jr	_QueueTransfer.modDone
_QueueTransfer.modPo2:
	ld	a, l
	add	a, a
	jr	nz, _QueueTransfer.modPo2Byte
	ld	a, h
	adc	a, a
	and	a, 0xF
	dec	a
	and	a, d
	ld	h, a
	ld	l, e
	jr	_QueueTransfer.modDone
_QueueTransfer.modPo2Byte:
	dec	a
	and	a, e
	ld	l, a
	ld	h, 0
_QueueTransfer.modDone:
	ex	de, hl
	sbc	hl, bc
	add	hl, bc
	jr	nz, _QueueTransfer.notLast
	ld	a, d
	or	a, e
	jr	nz, _QueueTransfer.last
_QueueTransfer.notLast:
	or	a, a
	sbc	hl, de
	pop	de
	pop	af
	push	af
	push	bc
	push	de
	push	hl
	call	_CreateDummyTransfer.enter
	jp	nz, _Error.NO_MEMORY
	and	a, 0b00001101
	pop	bc
	push	bc
	call	_QueueTransfer.queue
	pop	bc
	pop	hl
	pop	de
	add	hl, bc
	ex	de, hl
	sbc	hl, bc
	push	hl
	pop	bc
	jp	nz, _QueueTransfer.next
.equ _QueueTransfer.jr_nz, JR_NZ
	.db	_QueueTransfer.jr_nz
_QueueTransfer.last:
	pop	de
_QueueTransfer.zlp:
	pop	af
	and	a, 0b10001101
	push	hl
	pop	bc
.equ _QueueTransfer.iyPrefix, IY_PREFIX
	ld	iyl, _QueueTransfer.iyPrefix
.equ _QueueTransfer.queue, .-1
	ld	hl, 0
.equ _QueueTransfer.dummy, .-3
_QueueTransfer.fill:
	set	7, b

; Input:
;  a = ioc shl 7 or transfer.type.cerr or pid
;  bc = dt shl 15 or length
;  de = buffer
;  hl = next
;  iy = alt next
;  (ix+6) = endpoint
;  (ix+15) = handler
;  (ix+18) = data
_FillTransfer:
	ex	de, hl
	push	hl
	push	iy
	ld	iy, (ix+6)
	ld	hl, (iy + (endpoint.last - endpoint))
	ld	(hl), de
	ld	(iy + (endpoint.last - endpoint)), de
	set_mask	transfer.altNext, l
	pop	de
	ld	(hl), de
.rept transfer.type-transfer.altNext
	inc	l
.endr
	ld	(hl), a
.rept transfer.remaining-transfer.type
	inc	l
.endr
	ld	(hl), c
	inc	l	;transfer.remaining+1
	ld	(hl), b
	pop	de
	inc	l	;transfer.buffers
	ld	(hl), de
	dec	sp
	push	de
	inc	sp
	pop	de
.rept transfer.length-transfer.buffers
	inc	l
.endr
	ld	(hl), c
	inc	l	;transfer.length+1
	ld	(hl), b
	call	_FillTransfer.packHalf
	ld	bc, (ix+15)
	call	_FillTransfer.pack
	ld	bc, (ix+18)
	call	_FillTransfer.pack
	lea	bc, iy+0
	call	_FillTransfer.pack
	ld	(hl), d
	ld	a, l
	sub	a, transfer.padding-transfer.status
	ld	l, a
	ld	(hl), transfer.status.active
	ld	hl, ti.mpUsbCmd
	bit	0, (iy + (endpoint.transferInfo - endpoint))
assert (INTERRUPT_TRANSFER & 1)
	jr	nz, _FillTransfer.periodic
	bit	ti.bUsbAsyncSchedEn, (hl)
	ret	nz
	ld	l, ti.usbSts+1
	ld	b, (48000000*20/1000-_FillTransfer.async.sync.cycles.pre+_FillTransfer.async.sync.cycles-1)/_FillTransfer.async.sync.cycles
.equ _FillTransfer.async.sync.cycles.pre, 16+12+5+8+8
_FillTransfer.async.sync.wait:
	bit	ti.bUsbAsyncSchedSts-8, (hl)	;12
	jr	nz, _FillTransfer.async.sync			;+8
	ld	l, ti.usbCmd
	set	ti.bUsbAsyncSchedEn, (hl)
	ret
_FillTransfer.async.sync:
	xor	a, a				;+4
_FillTransfer.async.sync.loop:
	dec	a				;+(4
	jr	nz, _FillTransfer.async.sync.loop		;  +13)*256-5
	djnz	_FillTransfer.async.sync.wait		;+13
	jr	_Error.TIMEOUT
.equ _FillTransfer.async.sync.cycles, 12+8+4+(4+13)*256-5+13
_FillTransfer.periodic:
	bit	ti.bUsbPeriodicSchedEn, (hl)
	ret	nz
	ld	l, ti.usbSts+1
	ld	b, (48000000*20/1000-_FillTransfer.periodic.sync.cycles.pre+_FillTransfer.periodic.sync.cycles-1)/_FillTransfer.periodic.sync.cycles
.equ _FillTransfer.periodic.sync.cycles.pre, 16+12+5+8+8
_FillTransfer.periodic.sync.wait:
	bit	ti.bUsbPeriodicSchedSts-8, (hl)	;12
	jr	nz, _FillTransfer.periodic.sync		;+8
	ld	l, ti.usbCmd
	set	ti.bUsbPeriodicSchedEn, (hl)
	ret
_FillTransfer.periodic.sync:
	xor	a, a				;+4
_FillTransfer.periodic.sync.loop:
	dec	a				;+(4
	jr	nz, _FillTransfer.periodic.sync.loop		;  +13)*256-5
	djnz	_FillTransfer.periodic.sync.wait		;+13
	jr	_Error.TIMEOUT
.equ _FillTransfer.periodic.sync.cycles, 12+8+4+(4+13)*256-5+13
_FillTransfer.pack:
	ld	a, d
	xor	a, c
	and	a, 0xF
	xor	a, c
	ld	(hl), bc
	ld	(hl), a
	inc	l
	inc	l
_FillTransfer.packHalf:
	inc	l
	ld	a, e
	or	a, 0xF
	ld	e, a
	inc	de
	ld	a, c
	xor	a, e
	and	a, 0xF
	xor	a, e
	ld	(hl), a
	inc	l
	ret

;-------------------------------------------------------------------------------

 .irp error, SYSTEM, INVALID_PARAM, SCHEDULE_FULL, NO_DEVICE, NO_MEMORY, NOT_SUPPORTED, TIMEOUT, OVERFLOW, FAILED

_Error.\error:
	ld	a, USB_ERROR_\error\()
	jr	_Error.return

 .endr

_Error.check:
	pop	de
	call	ti._frameset0
	ld	a, (ti.mpIntMask)
	and	a, ti.intTmr3
	jr	nz, _Error.SYSTEM
	ld	a, (ti.mpUsbSts)
	and	a, ti.bmUsbIntHostSysErr
	jr	nz, _Error.SYSTEM
	ld	a, (ti.usbInited)
	dec	a
	jr	nz, _Error.SYSTEM
	ex	de, hl
	call	_DispatchEvent.dispatch

_Error.success:
	xor	a, a

_Error.return:
	or	a, a
	sbc	hl, hl
	ld	l, a
	jp	usb_Transfer.return

; Input:
;  a = fill
; Output:
;  bc = 0
;  hl = ti.flags+$1B
_Init:
	ld	de, ti.usbInited
	ld	(de), a
;	ld	hl,ti.mpUsbCmd
;	ld	(hl),2 shl ti.bUsbFrameListSize
;	call	ti.Delay10ms
;	ld	l,ti.usbSts+1
;	bit	ti.bUsbHcHalted-8,(hl)
;	jq	z,.notHalted
;	ld	l,ti.usbCmd
;	ld	(hl),2 shl ti.bUsbFrameListSize or ti.bmUsbHcReset
;.waitForReset:
;	bit	ti.bUsbHcReset,(hl)
;	jq	nz,.waitForReset
;.notHalted: ; rip memory?
	ld	hl, ti.usbInited
	dec	de
	ld	bc, ti.usbInited-ti.usbArea
	lddr
	ld	hl, ti.flags+0x1B
	ret

;-------------------------------------------------------------------------------
; Input:
;  hl = ti.mpUsbRange xor (? and $FF)
; Output:
;  a = 0
;  bc = ?
;  d = ?
;  hl = dummyHead.next
_DisableSchedulesAndResetHostController:
	; stop schedules
	ld	l, ti.usbCmd
_DisableSchedulesAndResetHostController.enter:
	ld	a, (hl)
	and	a, ti.bmUsbAsyncSchedEn | ti.bmUsbPeriodicSchedEn
assert (ti.bUsbAsyncSchedSts-8-ti.bUsbAsyncSchedEn == ti.bUsbPeriodicSchedSts-8-ti.bUsbPeriodicSchedEn)
.rept ti.bUsbAsyncSchedSts-8-ti.bUsbAsyncSchedEn
	rlca
.endr
	ld	d, a
	ld	l, ti.usbSts+1
	ld	b, (48000000*20/1000-_DisableSchedulesAndResetHostController.sync.cycles.pre+_DisableSchedulesAndResetHostController.sync.cycles-1)/_DisableSchedulesAndResetHostController.sync.cycles
.equ _DisableSchedulesAndResetHostController.sync.cycles.pre, 8+8+8+4*2+4+8+8
_DisableSchedulesAndResetHostController.sync.wait:
	ld	a, (hl)								;8
	and	a, (ti.bmUsbAsyncSchedSts | ti.bmUsbPeriodicSchedSts) >> 8	;+8
	sub	a, d								;+4
	jr	nz, _DisableSchedulesAndResetHostController.sync							;+13
_DisableSchedulesAndResetHostController.sync.fail:

; Input:
;  a = 0
;  hl = ti.mpUsbRange xor (? and $FF)
; Output:
;  a = 0
;  bc = ?
;  hl = dummyHead.next
_ResetHostControllerFromUnknown:
	; halt host controller (EHCI spec section 2.3)
	ld	l, ti.usbIntEn
	ld	(hl), a	;0
	ld	l, ti.usbCmd
	ld	(hl), a	;0
	ld	l, ti.usbSts+1
	ld	b, (48000000*2/1000-_ResetHostControllerFromUnknown.halt.cycles.pre+_ResetHostControllerFromUnknown.halt.cycles-1)/_ResetHostControllerFromUnknown.halt.cycles
.equ _ResetHostControllerFromUnknown.halt.cycles.pre, 16
_ResetHostControllerFromUnknown.halt.wait:
	bit	ti.bUsbHcHalted-8, (hl)	;12
	jr	z, _ResetHostControllerFromUnknown.halt			;+13
_ResetHostControllerFromUnknown.halt.fail:

	; reset host controller (EHCI spec section 2.3)
	ld	l, ti.usbCmd
	ld	(hl), ti.bmUsbHcReset
	ld	b, (48000000*250/1000-_ResetHostControllerFromUnknown.reset.cycles.pre+_ResetHostControllerFromUnknown.reset.cycles-1)/_ResetHostControllerFromUnknown.reset.cycles
.equ _ResetHostControllerFromUnknown.reset.cycles.pre, 8
_ResetHostControllerFromUnknown.reset.wait:
	bit	ti.bUsbHcReset, (hl)	;12
	jr	nz, _ResetHostControllerFromUnknown.reset		;+13
_ResetHostControllerFromUnknown.reset.fail:

	ld	bc, 0
.equ _ResetHostControllerFromUnknown.init, .-3
	ld	a, c
	and	a, ti.bmUsbFrameListSize
	; initialize host controller from halt (EHCI spec section 4.1)
	ld	(hl), a
	ld	l, ti.usbMisc
	ld	(hl), b
	ld	l, ti.usbIntEn
	ld	(hl), ti.bmUsbInt | ti.bmUsbIntErr | ti.bmUsbIntPortChgDetect | ti.bmUsbIntFrameListOver | ti.bmUsbIntHostSysErr | ti.bmUsbIntAsyncAdv
	ld	hl, periodicList
	ld	(ti.mpUsbPeriodicListBase), hl
	ld	hl, dummyHead.next
	ld	(ti.mpUsbAsyncListAddr), hl
	ret ; defer actual start until plug

_DisableSchedulesAndResetHostController.sync:
	xor	a, a							;+4
_DisableSchedulesAndResetHostController.sync.loop:
	dec	a							;+(4
	jr	nz, _DisableSchedulesAndResetHostController.sync.loop						;  +13)*256-5
	djnz	_DisableSchedulesAndResetHostController.sync.wait							;+13
.equ _DisableSchedulesAndResetHostController.sync.cycles, 8+8+4+13+4+(4+13)*256-5+13
	jr	_DisableSchedulesAndResetHostController.sync.fail

_ResetHostControllerFromUnknown.halt:
	dec	a			;+(4
	jr	nz, _ResetHostControllerFromUnknown.halt		;  +13)256-5
	djnz	_ResetHostControllerFromUnknown.halt.wait		;+13
.equ _ResetHostControllerFromUnknown.halt.cycles, 12+13+(4+13)*256-5+13
	jr	_ResetHostControllerFromUnknown.halt.fail

_ResetHostControllerFromUnknown.reset:
	ld	d, a			;+(4
_ResetHostControllerFromUnknown.reset.loop:
	dec	d			;  +(4
	jr	nz, _ResetHostControllerFromUnknown.reset.loop		;    +13)256-5
	dec	a			;  +4
	jr	nz, _ResetHostControllerFromUnknown.reset		;  +13)256-5
	djnz	_ResetHostControllerFromUnknown.reset.wait		;+13
.equ _ResetHostControllerFromUnknown.reset.cycles, 12+13+(4+(4+13)*256-5+4+13)*256-5+13
	jr	_ResetHostControllerFromUnknown.reset.fail

;-------------------------------------------------------------------------------
; Input:
;  a = role
;  hl = ti.mpUsbRange xor (? and $FF)
; Output:
;  zf = success
;  a = ?
;  bc = ?
;  hl = ti.mpUsbRange xor (? and $FF) | error code
;  iy = ?
_PowerVbusForRole:
	ld	l, ti.usbOtgCsr
	bit_mask	ROLE_DEVICE, a
	jr	nz, _PowerVbusForRole.unpower
_PowerVbusForRole.power:
	call	0x021B70
	res	ti.bUsbABusDrop, (hl)
	set	ti.bUsbABusReq, (hl)
	ld	l, ti.usbSts+1
	bit	ti.bUsbHcHalted-8, (hl)
	jr	z, _PowerVbusForRole.notHalted
	ld	l, ti.usbCmd
	set	ti.bUsbRunStop, (hl)
_PowerVbusForRole.notHalted:
	or	a, a	;ROLE_B
	ret	z
	ld	l, ti.usbOtgCsr
	res	ti.bUsbBHnp, (hl)
	res	ti.bUsbBVbusDisc, (hl)
	ret
_PowerVbusForRole.unpower:
	res	ti.bUsbASrpEn, (hl)
	push	hl
	push	de
	call	_DisableSchedulesAndResetHostController
	ld	de, ti.mpIntRange-1 ; disable doorbell
	call	_HandleAsyncAdvInt.cleanup.de
	call	_HandleAsyncAdvInt.cleanup.hl
	call	_HandleFrameListOverInt.cleanup
	call	_HandleFrameListOverInt.cleanup
	pop	de
	pop	hl
	set	ti.bUsbABusDrop, (hl)
	res	ti.bUsbABusReq, (hl)
	jp	0x021C68

;-------------------------------------------------------------------------------
_DefaultHandler:
	ld	hl, USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
; Input:
;  zf = reuse for hub
;  (sp+12) = block
;  iy = hub device | ?
; Output:
;  f = ?
;  cf = false
;  bc = ?
;  de = ?
;  hl = ?
;  iy = hub device | ?
_FreeTransferData:
	ld	hl, 3+12
	add	hl, sp
	ld	hl, (hl)

.macro define_memory_pool size, align

; Frees an <align> byte aligned <size> byte block.
; Input:
;  hl = allocated memory to be freed.
_Free\size\()Align\align\():
_Free\size\()Align\align\().uninit:
	push	de
.if DEBUG
	ld	de, (alloc\size\()Align\align\())
	dec	de
	ld	(alloc\size\()Align\align\()), de
.endif
	ld	de, (freeList\size\()Align\align\())
	ld	(hl), de
	ld	(freeList\size\()Align\align\()), hl
	pop	de
	ret

; Allocates an <align> byte aligned <size> byte block.
; Output:
;  zf = enough memory
;  hl = allocated memory
_Alloc\size\()Align\align\():
	ld	hl, (freeList\size\()Align\align\())
	bit	0, l
	ret	nz
	push	hl
	ld	hl, (hl)
	ld	(freeList\size\()Align\align\()), hl
.if DEBUG
	ld	hl, (alloc\size\()Align\align\())
	inc	hl
	ld	(alloc\size\()Align\align\()), hl
.endif
	pop	hl
	ret

.endm
define_memory_pool 32, 32
define_memory_pool 64, 256
.purgem define_memory_pool

; Input:
;  (ix+6) = endpoint
; Output:
;  zf = enough memory
;  hl = transfer
;  iy = (ix+6)
_CreateDummyTransfer:
	ld	iy, (ix+6)
_CreateDummyTransfer.enter:
	call	_Alloc32Align32
	ret	nz
	set_mask	transfer.status, l
	ld	(hl), transfer.status.halted
	res_mask	transfer.status, l
	ld	(hl), 1
	ret

; Input:
;  ix = device-1
; Output:
;  zf = success
;  a = ?
;  bc = ?
;  de = ?
;  hl = ti.mpUsbRange | error
;  ix = ?
;  iy = ?
_DeviceDisabled:
	ld	hl, _HandleAsyncAdvInt.scheduleCleanup.hl
	push	hl
	ld	b, USB_DEVICE_DISABLED_EVENT
_DeviceDisabled.recurse:
	ld	a, (ix + device.find+1)
	ld	c, a
	and	a, ~ (IS_ENABLED | IS_DISABLED)
assert (IS_DISABLED == 1)
	inc	a	;IS_DISABLED
	ld	(ix + device.find+1), a
	jr	_DeviceDisabled.start
_DeviceDisabled.recursed:
	pop	ix
	pop	bc
	ret	nz
_DeviceDisabled.start:
	push	bc
	push	ix
	ld	de, (ix + device.endpoints+1)
	ld	ix, (ix + device.child+1)
	ld	hl, _DeviceDisabled.recursed
	dec	ixl
	jr	nz, _DeviceDisconnected.recurse
_DeviceDisabled.loop:
	call	_CleanupEndpoint
	jr	nz, _DeviceDisabled.pop2return
	inc	e
	ld	a, e
	and	a, 31
	jr	nz, _DeviceDisabled.loop
	pop	bc
	push	bc
	ld	iy, resetList-1
_DeviceDisabled.reset.find:
	lea	de, iy + reset.next+1
	ld	iy, (iy + reset.next+1)
	dec	iyl
	jr	z, _DeviceDisabled.reset.done
	ld	hl, (iy + reset.device+1)
	scf
	sbc	hl, bc
	jr	nz, _DeviceDisabled.reset.find
	push	de
	pop	iy
	call	usb_ResetDevice.free
_DeviceDisabled.reset.done:
	pop	ix
	pop	af
	ld	hl, ti.mpUsbRange
	lea	de, ix+1
assert (IS_DISABLED == 1 << 0)
	jr	nc, _DeviceDisabled.event
	cp	a, USB_DEVICE_DISABLED_EVENT
	ret	z
_DeviceDisabled.event:
	jp	_DispatchEvent
_DeviceDisabled.pop2return:
	pop	bc
	pop	ix
	ret

; Input:
;  ix = device-1
; Output:
;  af = ?
;  zf = success
;  bc = ?
;  de = ?
;  hl = ti.mpUsbRange | error
;  ix = ?
;  iy = ?
_DeviceDisconnected:
	ld	hl, _HandleAsyncAdvInt.scheduleCleanup.de
_DeviceDisconnected.recurse:
	push	hl
	ld	b, USB_DEVICE_DISCONNECTED_EVENT
	call	_DeviceDisabled.recurse
	ret	nz
	ld	iy, (ix + device.sibling+1)
	ld	hl, (ix + device.back+1)
	ld	(hl), iy
	dec	iyl
	jr	z, _DeviceDisconnected.sibling
	ld	(iy + device.back+1), hl
_DeviceDisconnected.sibling:
	ld	hl, (ix + device.endpoints+1)
	ld	(ix + device.endpoints+1), ix
	bit	0, l
	call	z, _Free32Align32
	lea	hl, ix + device.refcnt+1
	jp	usb_UnrefDevice.refcnt

; Input:
;  b = interval
;  hl + de = max full-speed stuffed bit times needed
;  iy = endpoint
; Output:
;  cf = schedule full
;  f = ?
;  a = 1 - offset shr 6 | ?
;  bc = ?
;  de = endpoint | ?
;  hl = ?
;  iyl = offset shl 2 | ?
;  iy = ?
_ScheduleEndpoint:
_ScheduleEndpoint.enabled:
.equ _ScheduleEndpoint.disable, SCF_RET
	add	hl, de
.rept 15-FS_SBP_PER_FRAME_msb
	add	hl, hl
.endr
.equ _ScheduleEndpoint.enable, SCHEDULE_ENDPOINT_START
	ld	(_ScheduleEndpoint.maxHsSbp), hl
	inc	l
	ld	(iy + (endpoint.maxHsSbp - endpoint)+0), l
	ld	(iy + (endpoint.maxHsSbp - endpoint)+1), h
	ld	a, 1
_ScheduleEndpoint.log:
	rrca
	rl	b
	jr	nc, _ScheduleEndpoint.log
	ld	(iy + (endpoint.interval - endpoint)), a
	sbc	hl, hl
	push	iy
	push	hl
	push	hl
	ld	b, a
	cpl
	ld	(_ScheduleEndpoint.notInterval), a
	inc	a
	ld	l, a
	add	hl, hl
	add	hl, hl
	ld	(_ScheduleEndpoint.stride), hl
	ld	iy, periodicList
_ScheduleEndpoint.check:
.rept (1 << 7*4) >> 8
	inc	iyh
.endr
	lea	iy, iy-4
	push	bc
	ld	de, periodicList >> 8 & 0xFF-1
	ld	a, e
_ScheduleEndpoint.sum:
	ld	hl, (iy+endpoint.maxHsSbp)
	ld	bc, 0
.equ _ScheduleEndpoint.maxHsSbp, .-3
	add.s	hl, bc
	jr	nc, _ScheduleEndpoint.valid
	ld	de, 1 << 23
_ScheduleEndpoint.valid:
	add	hl, de
	ex	de, hl
	ld	bc, 0
.equ _ScheduleEndpoint.stride, .-3
	add	iy, bc
	cp	a, iyh
	jr	c, _ScheduleEndpoint.sum
	pop	bc
	pop	hl
	sbc	hl, de
	jr	c, _ScheduleEndpoint.min
	pop	hl
	push	iy
	sbc	hl, hl
_ScheduleEndpoint.min:
	add	hl, de
	push	hl
	djnz	_ScheduleEndpoint.check
	pop	hl
	pop	iy
	pop	de
	add	hl, hl
	ret	c
	ld	bc, 4-1
.equ _ScheduleEndpoint.frameListSize, .-3
_ScheduleEndpoint.link:
	add	iy, bc
	ld	a, periodicList >> 8 & 0xFF-1
	sub	a, iyh
	ret	nc
	push	iy
	push	de
	inc	iy
	ld	bc, (iy-2)
	ld	hl, (_ScheduleEndpoint.maxHsSbp)
	add	hl, bc
	ld	(iy-2), hl
.equ _ScheduleEndpoint.ld_hl, LD_HL_IMM
	.db	_ScheduleEndpoint.ld_hl
_ScheduleEndpoint.skip:
	ld	iyh, b
	ld	iyl, c
	ld	bc, (iy-4)
	bit	2, c
	jr	nz, _ScheduleEndpoint.skip
	ld	e, endpoint.interval
	.db	_ScheduleEndpoint.ld_hl
_ScheduleEndpoint.find:
	ld	iyh, d
	ld	iyl, endpoint.base+4
	ld	d, (iy-4+endpoint.next+1)
	bit	0, (iy-4+endpoint.next+0)
	jr	nz, _ScheduleEndpoint.found
	ld	a, (de)
	add	a, 0
.equ _ScheduleEndpoint.notInterval, .-1
	jr	c, _ScheduleEndpoint.find
_ScheduleEndpoint.found:
	pop	hl
	pop	bc
	ld	e, l	;endpoint
	ld	a, d
	cp	a, h
	jr	z, _ScheduleEndpoint.linked
assert (endpoint-2 == endpoint.next)
	dec	l
	ld	(hl), d
	dec	l
	ld	a, (iy-4+endpoint.next+0)
	ld	(hl), a
	ld	(iy-4+endpoint.next+1), h
	ld	(iy-4+endpoint.next+0), e
_ScheduleEndpoint.linked:
	ld	d, h
	ld	iy, (_ScheduleEndpoint.stride)
	jr	_ScheduleEndpoint.link

; Input:
;  iy = device
; Output:
;  af = ?
;  zf = success
;  bc = ?
;  de = ?
;  hl = ? | error
;  iy = endpoint | ?
_CreateDefaultControlEndpoint.enable:
assert (IS_DISABLED+1 == IS_ENABLED)
	inc	(iy + device.find)
_CreateDefaultControlEndpoint:
	ld	de, _DefaultControlEndpointDescriptor

; Input:
;  de = endpoint descriptor
;  iy = device
; Output:
;  zf = success
;  af = ?
;  bc = ?
;  de = ?
;  hl = ? | error
;  iy = endpoint | ?
_CreateEndpoint:
	call	_Alloc64Align256
	jp	nz, _CreateEndpoint.nomem
.rept endpointDescriptor.bEndpointAddress-endpointDescriptor
	inc	de
.endr
	ld	a, (de)
	and	a, endpoint.transferInfo.dir | endpoint.info.ep
	ld	c, a
	and	a, endpoint.info.ep
	ld	b, a
assert (endpointDescriptor.bEndpointAddress+1 == endpointDescriptor.bmAttributes)
	inc	de
	ld	a, (de)
	and	a, ti.bmUsbFifoType
	push	bc
	push	de
	push	af
	rlc	c
	rla
	rrca
	ld	l, endpoint.transferInfo
	ld	(hl), a
	ld	a, (iy + device.addr)
	ld	l, endpoint.addr
	ld	(hl), a
	ld	a, b
	or	a, (iy + device.speed)
assert (endpoint.addr+1 == endpoint.info)
	inc	l
	ld	(hl), a
	push	hl
	ld	de, (iy + device.endpoints)
	ld	a, c
	or	a, e
	ld	e, a
	push	iy
	call	_CleanupEndpoint
	pop	iy
	jr	nz, _CreateEndpoint.cleanupFailed
	pop	hl
	ld	a, h
	ld	(de), a
	pop	af
	ld	c, 0
	jr	nz, _CreateEndpoint.notControl
	ld	a, e
	xor	a, 1
	ld	e, a
	ld	a, h
	ld	(de), a
	set_mask	endpoint.info.dtc, (hl)
	ld	c, +(endpoint.maxPktLen.rl | endpoint.maxPktLen.c) >> 8
_CreateEndpoint.notControl:
	rrca
	sbc	a, a
	cpl
	and	a, endpoint.maxPktLen.rl >> 8
	or	a, c
	ld	c, a
assert (endpointDescriptor.bmAttributes+1 == endpointDescriptor.wMaxPacketSize)
	pop	de
	inc	de
	ld	a, (de)
assert (endpoint.info+1 == endpoint.maxPktLen)
	inc	l
	ld	(hl), a
	inc	de
	ld	a, (de)
	and	a, endpoint.maxPktLen.msk >> 8
	or	a, c
	inc	l
.set _CreateEndpoint.l, endpoint.maxPktLen+1
	ld	(hl), a
	ld	bc, 0
assert (endpoint.smask+1 == endpoint.cmask)
assert (endpoint.smask+2 == endpoint.hubInfo+0)
assert (endpoint.flags+1 == endpoint.interval)
assert (endpoint.flags+2 == endpoint.offset)
.macro init_endpoint_field field, value
 .if _CreateEndpoint.l+1 == endpoint.\field
	inc	l
 .else
	ld	l, endpoint.\field
 .endif
 .set _CreateEndpoint.l, endpoint.\field
	ld	(hl), \value
.endm
init_endpoint_field smask, bc
init_endpoint_field hubInfo+1, 1 << 6
init_endpoint_field overlay.altNext, 1
init_endpoint_field overlay.status, c
init_endpoint_field flags, bc
init_endpoint_field device, iy
.purgem init_endpoint_field
	ld	l, endpoint
	push	hl
	pop	iy
	sbc	hl, hl
	ld	(iy + (endpoint.data - endpoint)), hl
	call	_CreateDummyTransfer.enter
	jr	z, _CreateEndpoint.mem
	lea	hl, iy + (endpoint.base - endpoint)
	call	_Free64Align256
	pop	bc
_CreateEndpoint.nomem:
	ld	hl, USB_ERROR_NO_MEMORY
	ret
_CreateEndpoint.cleanupFailed:
	ex	(sp), hl
	ld	l, endpoint
	call	_Free64Align256
	pop	hl
	pop	bc
	pop	bc
	pop	bc
	ret
_CreateEndpoint.mem:
	ld	(iy + (endpoint.overlay.next - endpoint)), hl
	ld	(iy + (endpoint.first - endpoint)), hl
	ld	(iy + (endpoint.last - endpoint)), hl
	ex	de, hl
	ld	d, (hl)
	dec	hl
	ld	e, (hl)
	ld	a, e
	or	a, d
	dec	de
	jr	z, _CreateEndpoint.notPo2Mps
	ld	a, e
	and	a, (hl)
	ld	c, a
	inc	hl
	ld	a, d
	and	a, (hl)
	or	a, c
	jr	nz, _CreateEndpoint.notPo2Mps
	set_mask	endpoint.flags.po2Mps, (iy + (endpoint.flags - endpoint))
_CreateEndpoint.notPo2Mps:
	pop	bc
	ld	a, (currentRole)
	and	a, ti.bmUsbRole >> 16
	jr	nz, _CreateEndpoint.async
	ld	a, (iy + (endpoint.transferInfo - endpoint))
assert (~(CONTROL_TRANSFER | BULK_TRANSFER) & 1)
	rrca
	jr	nc, _CreateEndpoint.async
assert (endpointDescriptor.wMaxPacketSize+2 == endpointDescriptor.bInterval)
	inc	hl
	ld	b, (hl)
	inc	b
	dec	b
	jr	z, _CreateEndpoint.invalidParam
_CreateEndpoint.validInterval:
	ex	de, hl
	inc.s	hl
.rept 2
	add	hl, hl
.endr
	rrca
assert (INTERRUPT_TRANSFER & 1)
	jr	c, _CreateEndpoint.intr
	djnz	_CreateEndpoint.isoc.validInterval
_CreateEndpoint.invalidParam:
	ld	hl, USB_ERROR_INVALID_PARAM
	ret
_CreateEndpoint.isoc.validInterval:
	inc	b
; full-speed out isoc: 4*bytes + 39 fs sbp
; full-speed  in isoc: 4*bytes + 44 fs sbp
	bit_mask	endpoint.transferInfo.dir, (iy + (endpoint.transferInfo - endpoint))
	ld	de, 39
	jr	z, _CreateEndpoint.isoc.schedule
	ld	e, 44
_CreateEndpoint.isoc.schedule:
;	call	.schedule
assert (USB_ERROR_INVALID_PARAM)
	ld	hl, USB_ERROR_INVALID_PARAM-1
	inc	l
	ret
_CreateEndpoint.intr:
;  full-speed other: 4*bytes + 54 fs sbp
;     low-speed  in: 32*bytes + 348 fs sbp
;     low-speed out: 32*bytes + 350 fs sbp
	inc	(iy + (endpoint.smask - endpoint))	;00000001b
	ld	(iy + (endpoint.cmask - endpoint)), 0b00011100
	bit	endpoint_info_eps_lsb, (iy + (endpoint.info - endpoint))
	ld	de, 54
	jr	z, _CreateEndpoint.schedule
.rept 5-2
	add	hl, hl
.endr
	ld	e, 348-0x100
	inc	d
	bit_mask	endpoint.transferInfo.dir, (iy + (endpoint.transferInfo - endpoint))
	jr	z, _CreateEndpoint.schedule
	ld	e, 350-0x100
_CreateEndpoint.schedule:
	call	_ScheduleEndpoint
	rr	a
	ld	a, iyl
	ccf
	rra
	push	de
	pop	iy
	ld	(iy + (endpoint.offset - endpoint)), a
	ld	hl, USB_ERROR_SCHEDULE_FULL
	ret
_CreateEndpoint.async:
	ld	hl, (dummyHead.next)
	ld	(iy + (endpoint.next - endpoint)), hl
assert (endpoint+1 == endpoint.prev)
	inc	hl
	ld	e, iyh
	ld	(hl), e
	ld	(iy + (endpoint.prev - endpoint)), dummyHead >> 8 & 0xFF
	ld	(dummyHead.next), iy
	ret	z
	inc	b
	dec	b
assert (ti.bmUsbRole >> 16 == ti.bmUsbDmaCxFifo)
	jr	z, _CreateEndpoint.defaultControl
	rlc	c
	ld	c, a
	sbc	a, a
assert (ti.bmUsbRole >> 16 == ti.usbFifoIn)
	and	a, c
	ld	c, a
	ld	hl, ti.mpUsbFifo0Map-1
	ld	a, l
	add	a, b
	ld	l, a
	ld	a, (hl)
	and	a, ~ ti.bmUsbFifoDir
	or	a, c
	ld	(hl), a
assert (ti.usbFifo0Cfg > ti.usbFifo0Map)
	set_mask	ti.usbFifo0Cfg ^ ti.usbFifo0Map, l
	ld	a, (iy + (endpoint.transferInfo - endpoint))
	and	a, endpoint.transferInfo.type
	or	a, ti.bmUsbFifoEn
	ld	(hl), a
	ld	a, ti.usbOutEp1+1-4-0x100
assert (ti.usbOutEp1 > ti.usbInEp1)
.rept 2
	sub	a, c
.endr
.rept 4
	add	a, b
.endr
	ld	l, a
	ld	(hl), ti.bmUsbEpReset >> 8
	ld	de, (iy + (endpoint.maxPktLen - endpoint))
	ld	a, d
	and	a, ti.bmUsbEpMaxPktSz >> 8
	ld	(hl), a
	dec	l
	ld	(hl), e
	xor	a, a
	scf
_CreateEndpoint.shift:
	rla
	djnz	_CreateEndpoint.shift
_CreateEndpoint.defaultControl:
	ld	(iy + (endpoint.overlay.fifo - endpoint)), a
	ret

;-------------------------------------------------------------------------------
; Input:
;  de = endpoint pointer
; Output:
;  zf = success
;  af = ?
;  bc = ?
;  hl = ?
;  iy = ?
_CleanupEndpoint:
	ld	a, (de)
	inc	a
	ret	z
	dec	a
	ld	bc, USB_TRANSFER_CANCELLED | USB_TRANSFER_NO_DEVICE
	push	ix
	ld	ix, dummyHead
	ld	ixh, a
	push	de
	ld	a, (ix + (endpoint.transferInfo - endpoint))
	and	a, endpoint.transferInfo.type
	ld	a, -1
	ld	(de), a
	jr	nz, _CleanupEndpoint.notControl
	ld	a, e
	xor	a, 1
	ld	e, a
	ld	a, -1
	ld	(de), a
_CleanupEndpoint.notControl:
	call	_FlushEndpoint
	jp	nc, _CleanupEndpoint.popreturn
	ld	a, (ix + (endpoint.transferInfo - endpoint))
	rrca
assert (~(CONTROL_TRANSFER | BULK_TRANSFER) & 1 << 0)
	jr	nc, _CleanupEndpoint.async
	rrca
assert (~ISOCHRONOUS_TRANSFER & 1 << 1)
	jr	nc, _CleanupEndpoint.isoc
assert (endpoint.interval+1 == endpoint.offset)
	ld	bc, (ix + (endpoint.interval - endpoint))
	sbc	hl, hl
	xor	a, a
	sub	a, c
	ld	l, a
	add	hl, hl
	add	hl, hl
	ex	de, hl
	ld	iy, periodicList >> 1
.equ _CleanupEndpoint.frameListEndSub1Shr1, .-3
	ld	iyl, b
	add	iy, iy
_CleanupEndpoint.intr.unlink:
	ld	bc, (ix + (endpoint.maxHsSbp - endpoint))
	dec.s	bc
	ld	hl, (iy)
	sbc	hl, bc
	ld	(iy), hl
	push	iy
	lea	iy, iy+2
.equ _CleanupEndpoint.ld_hl, LD_HL_IMM
	.db	_CleanupEndpoint.ld_hl
_CleanupEndpoint.intr.skip:
	ld	iyh, b
	ld	iyl, c
	ld	bc, (iy-4)
	bit	2, c
	jr	nz, _CleanupEndpoint.intr.skip
	.db	_CleanupEndpoint.ld_hl
_CleanupEndpoint.intr.find:
	ld	iyh, a
	ld	iyl, endpoint.base+4
	bit	0, (iy-4+endpoint.next+0)
	jr	nz, _CleanupEndpoint.intr.gone
	ld	a, (iy-4+endpoint.next+1)
	cp	a, ixh
	jr	nz, _CleanupEndpoint.intr.find
	ld	hl, (ix + (endpoint.next - endpoint))
	ld	(iy-4+endpoint.next+0), l
	ld	(iy-4+endpoint.next+1), h
_CleanupEndpoint.intr.gone:
	pop	iy
	add	iy, de
	ld	a, iyh
	cp	a, periodicList >> 8 & 0xFF
	jr	nc, _CleanupEndpoint.intr.unlink
	ld	hl, intrCleanupPending
	jr	_CleanupEndpoint.cleanup
_CleanupEndpoint.isoc:
	cp	a, a
	lea	hl, ix + (endpoint.base - endpoint)
	pop	de
	pop	ix
	jp	_Free64Align256
_CleanupEndpoint.async:
	lea	hl, ix + (endpoint.next - endpoint)
	ld	h, (ix + (endpoint.prev - endpoint))
	ld	iy, (ix + (endpoint.next - endpoint))
	ld	(hl), iy
	ld	(iy + (endpoint.prev - endpoint)), h
	ld	hl, asyncCleanupPending
_CleanupEndpoint.cleanup:
	ld	a, (hl)
	ld	(ix + (endpoint.prev - endpoint)), a
	ld	a, ixh
	ld	(hl), a
	cp	a, a
_CleanupEndpoint.popreturn:
	pop	de
	pop	ix
	ret

;-------------------------------------------------------------------------------
; Input:
;  a = alt
;  b = num interfaces
;  de = length or ? shl 16
;  ix = descriptors
;  iy = device
; Output:
;  zf = valid
;  a = 0 | ?
;  bc = ?
;  de = ? and $FFFF
;  hl = ? and $FFFF
;  ix = ?
;  iy = device
_ParseInterfaceDescriptors:
	xor	a, a
	ld	c, iyl
	bit	0, c
	ret	nz
_ParseInterfaceDescriptors.valid:
	ld	hl, ti.mpUsbDevTest
	set	ti.bUsbTstClrFifo, (hl)
	res	ti.bUsbTstClrFifo, (hl)
_ParseInterfaceDescriptors.host:
	inc	b
_ParseInterfaceDescriptors.dec:
	ld	(_ParseInterfaceDescriptors.alt), a
	or	a, a
	sbc	hl, hl
	ex.s	de, hl
	ld	c, e
	jr	_ParseInterfaceDescriptors.enter
_ParseInterfaceDescriptors.endpoint:
	cp	a, c
	jr	z, _ParseInterfaceDescriptors.next
	ld	a, e
	cp	a, endpointDescriptor_size
	ret	c
	push	bc
	push	de
	push	hl
	push	iy
	lea	de, ix+0
	call	_CreateEndpoint
	pop	iy
	pop	hl
	pop	de
	pop	bc
	ret	nz
	dec	c
_ParseInterfaceDescriptors.next:
	add	ix, de
_ParseInterfaceDescriptors.enter:
	add	hl, de
	xor	a, a
	sbc	hl, de
	ret	z
	ld	a, (ix + descriptor.bLength)
	cp	a, descriptor_size
	ret	c
	ld	e, a
	sbc	hl, de
	ret	c
	ld	a, (ix + descriptor.bDescriptorType)
	sub	a, ENDPOINT_DESCRIPTOR
	jr	z, _ParseInterfaceDescriptors.endpoint
.rept ENDPOINT_DESCRIPTOR-INTERFACE_DESCRIPTOR
	inc	a
.endr
	jr	nz, _ParseInterfaceDescriptors.next
	ld	c, a
	ld	a, e
	cp	a, interfaceDescriptor_size
	ret	c
	ld	a, (ix + interfaceDescriptor.bAlternateSetting)
	sub	a, 0
.equ _ParseInterfaceDescriptors.alt, .-1
	jr	nz, _ParseInterfaceDescriptors.next
	ld	c, (ix + interfaceDescriptor.bNumEndpoints)
	djnz	_ParseInterfaceDescriptors.next
	ret

;-------------------------------------------------------------------------------
; Input:
;  a = endpoint
;  bc = ? | bytes or ? shl 16
; Output:
;  cf = error
;  zf = ? | false
_ExecuteDma:
	ld	hl, (rootHub.child)
	call	usb_GetDeviceEndpoint.enter
	ld	l, endpoint.overlay.next
	bit	0, (hl)
	ret	nz
	ld	iy, (hl)
	bit_mask	transfer.status.active, (iy + transfer.status)
	ret	z
	ld	de, (iy + transfer.remaining)
	res_mask	(transfer.remaining.dt >> 8), d
	ld	a, i
	push	af
	ld	l, endpoint.overlay.fifo
	ld	a, (hl)
	ld	l, endpoint.maxPktLen+1
	di
	ld	(ti.mpUsbDmaFifo), a
	ld	a, (hl)
	dec	l	;endpoint.maxPktLen
	ld	l, (hl)
	and	a, 7
	ld	h, a
	push	hl
	sbc.s	hl, de
	jr	c, _ExecuteDma.mpsLess
	sbc	hl, hl
_ExecuteDma.mpsLess:
	add.s	hl, de
	ld	a, b
	and	a, 7
	ld	b, a
	ld	a, (iy + transfer.type)
.rept ti.bUsbDmaDir-0
	rlca
.endr
	and	a, ti.bmUsbDmaClrFifo | ti.usbDmaMem2Fifo
	jp	pe, _ExecuteDma.in
	inc	bc
	dec.s	bc
	sbc	hl, bc
	jp	c, _ExecuteDma.babble
	sbc	hl, hl
	add	hl, bc
_ExecuteDma.in:
	add	hl, bc
	sbc	hl, bc
	jp	z, _ExecuteDma.zlp
	ld	(ti.mpUsbDmaLen), hl
	ex	de, hl
	sbc	hl, de
	ld	(iy + transfer.remaining), hl
	ex	(sp), hl
	sbc.s	hl, de
	ex	(sp), hl
	ex	de, hl
	ld	bc, (iy + transfer.buffers)
	add	hl, bc
	ld	(iy + transfer.buffers), hl
_ExecuteDma.flush:
	ld	hl, ti.mpUsbDmaAddr
	ld	(hl), bc
	ld	l, ti.usbDmaCtrl-0x100
	ld	(hl), a
	inc	a	;ti.bmUsbDmaStart
	ld	(hl), a
_ExecuteDma.waitDma:
	ld	a, (hl)
	ld	l, ti.usbDevIsr-0x100
	bit	ti.bUsbIntDevDmaFin, (hl)
	jr	nz, _ExecuteDma.dmaFinished
	inc	l
	bit	ti.bUsbIntDevDmaErr-8, (hl)
	jr	z, _ExecuteDma.waitDma
	ld	a, (iy + transfer.status)
	and	a, ~ transfer.status.active
	or	a, transfer.status.halted | transfer.status.bufErr
	ld	(iy + transfer.status), a
	ld	(hl), ti.bmUsbIntDevDmaErr >> 8
	dec	l
_ExecuteDma.dmaFinished:
	ld	(hl), ti.bmUsbIntDevDmaFin
_ExecuteDma.finishZlp:
	pop	bc
	ld	a, e
	or	a, d
	ld	de, (iy + transfer.endpoint)
	ld	a, (iy + transfer.status)
.rept 8-transfer_status_halted_msb
	rlca
.endr
	jr	c, _ExecuteDma.continue
	jr	z, _ExecuteDma.next
	ld	a, c
	or	a, b
	jr	z, _ExecuteDma.continue
	ld	bc, (iy + transfer.altNext)
	bit	0, c
	jr	z, _ExecuteDma.alt
_ExecuteDma.next:
	ld	bc, (iy + transfer.next)
_ExecuteDma.alt:
	ld	e, endpoint.overlay.next
	ex	de, hl
	ld	(hl), bc
	ex	de, hl
	res_mask	transfer.status.active, (iy + transfer.status)
	ld	a, (iy + transfer.altNext)
	rrca
	jr	nc, _ExecuteDma.continue
	ld	l, ti.usbDmaFifo-0x100
	bit	ti.bUsbDmaCxFifo, (hl)
	jr	nz, _ExecuteDma.cx
assert (transfer_next_dummy_msb == 0)
	ld	a, (bc)
	and	a, (iy + transfer.type)
.rept transfer_next_dummy_msb+1
	rrca
.endr
	sbc	a, a
	and	a, (hl)
	ld	l, ti.usbFifoTxImr-0x100
	or	a, (hl)
	ld	(hl), a
	scf
.equ _ExecuteDma.jp_nc, JP_NC
	.db	_ExecuteDma.jp_nc
_ExecuteDma.cx:
	ld	l, ti.usbCxFifo-0x100
assert (ti.usbCxFifo >> 8 == ti.bmCxFifoFin)
	ld	(hl), h ; Must happen before restoring interrupts!
_ExecuteDma.continue:
	ld	l, ti.usbDmaFifo-0x100
	ld	(hl), ti.bmUsbDmaNoFifo ; Must happen before restoring interrupts!
	pop	bc
	bit	2, c ; p/v flag
	jr	z, _ExecuteDma.noEi
	ei
_ExecuteDma.noEi:
	ret	nc
	ld	e, endpoint
	push	de
	ex	(sp), ix
	call	_RetireTransfers
	ccf
	pop	ix
	ret
_ExecuteDma.babble:
	ld	a, (iy + transfer.status)
	and	a, ~ transfer.status.active
	or	a, transfer.status.halted | transfer.status.babble
	ld	(iy + transfer.status), a
	ld	a, ti.bmUsbDmaClrFifo | ti.usbDmaFifo2Mem
	ld	(ti.mpUsbDmaLen), bc
	ld	bc, ti.vRamEnd
	jp	_ExecuteDma.flush
_ExecuteDma.zlp:
	ld	hl, ti.mpUsbCxFifo
	and	a, ti.usbDmaMem2Fifo
	jr	z, _ExecuteDma.finishZlp
	bit	ti.bUsbDmaCxFifo, (hl)
	jp	nz, _ExecuteDma.finishZlp
	ld	bc, (iy + transfer.endpoint)
	ld	c, endpoint.info
	ld	a, (bc)
	and	a, endpoint.info.ep
.rept UsbEndpointStride_msb
	add	a, a
.endr
	add	a, ti.usbInEp1 << 1-ti.usbInEp2+1-0x100
	ld	l, a
	set	ti.bUsbInEpSendZlp-8, (hl)
	jp	_ExecuteDma.finishZlp

;-------------------------------------------------------------------------------
; Input:
;  ix = endpoint
; Output:
;  cf = success
;  zf = ? | false
;  a = ?
;  bc = ?
;  de = ?
;  hl = ? | error
;  ix = endpoint (maybe just freed)
;  iy = ?
_RetireTransfers:
	or	a, a
_RetireTransfers.nc:
	sbc	hl, hl
	inc.s	bc
_RetireTransfers.loop:
	lea	iy, ix + (endpoint.first - endpoint)
_RetireTransfers.continue:
	ld	iy, (iy + transfer.next)
	ld	a, (iy + transfer.next)
.rept transfer_next_dummy_msb+1
	rrca
.endr
	ret	c
assert (transfer.status+1 == transfer.type)
	ld	de, (iy + transfer.status)
	ld	a, e
.rept 8-transfer_status_active_msb
	add	a, a
.endr
	ret	c
.rept transfer_status_active_msb-transfer_status_halted_msb
	rlca
.endr
	jr	c, _RetireTransfers.halted
	bit	transfer_type_pid_msb, d ; setup
	jr	nz, _RetireTransfers.continue
	ld	c, (iy + transfer.length+0)
	ld	b, (iy + transfer.length+1)
	res_mask	(transfer.remaining.dt >> 8), b
	add	hl, bc
	ld	c, (iy + transfer.remaining+0)
	ld	a, (iy + transfer.remaining+1)
	and	a, ~ (transfer.remaining.dt >> 8)
	ld	b, a
	sbc	hl, bc
	or	a, c
	jr	nz, _RetireTransfers.partial
	bit_mask	transfer.type.ioc, d
	jr	z, _RetireTransfers.continue
_RetireTransfers.partial:
.equ _RetireTransfers.nop, NOP_OPCODE
assert (_RetireTransfers.nop == 0)
	xor	a, a
	ld	c, a
	call	_RetireFirstTransfer
	ret	nc
	bit_mask	endpoint.flags.freed, (ix + (endpoint.flags - endpoint))
	jr	z, _RetireTransfers.loop
	jr	_RetireTransfers.dangling
_RetireTransfers.halted:
	ld	a, d
	and	a, transfer.type.cerr
	ld	c, e
	jr	z, _RetireTransfers.failed
	bit_mask	transfer.status.babble, e
	jr	nz, _RetireTransfers.failed
assert (USB_TRANSFER_STALLED == 1)
	inc	c
	bit_mask	(endpoint.maxPktLen.c >> 8), (ix + (endpoint.maxPktLen + 1 - endpoint))
	jr	z, _RetireTransfers.failed
	xor	a, a
	call	_RetireFirstTransfer
	ret	nc
	bit_mask	endpoint.flags.freed, (ix + (endpoint.flags - endpoint))
	jr	nz, _RetireTransfers.dangling
	ld	(ix + (endpoint.overlay.next - endpoint)), iy
assert (USB_TRANSFER_STALLED & 1)
	ld	(ix + (endpoint.overlay.altNext - endpoint)), c
	ld	(ix + (endpoint.overlay.status - endpoint)), l	;0
	jr	_RetireTransfers.loop
_RetireTransfers.failed:
.equ _RetireTransfers.ret_z, RET_Z
	ld	a, _RetireTransfers.ret_z
	call	_RetireFirstTransfer
	jr	nz, _FlushEndpoint.check
	bit_mask	endpoint.flags.freed, (ix + (endpoint.flags - endpoint))
_RetireTransfers.dangling:
	jr	nz, _FlushEndpoint.dangling
	ld	iy, (ix + (endpoint.first - endpoint))
	ld	(ix + (endpoint.overlay.next - endpoint)), iy
	ld	(ix + (endpoint.overlay.altNext - endpoint)), iy
_RetireTransfers.restart:
	ld	de, (iy + transfer.length)
	ld	(iy + transfer.remaining+0), e
	ld	(iy + transfer.remaining+1), d
	ld	a, (iy + transfer.type)
	and	a, ~ transfer.type.cpage
	or	a, transfer.type.cerr
	ld	(iy + transfer.type), a
	bit_mask	transfer.status.halted, (iy + transfer.status)
	ld	(iy + transfer.status), transfer.status.active
	ld	iy, (iy + transfer.next)
	jr	z, _RetireTransfers.restart
	ld	(ix + (endpoint.overlay.status - endpoint)), h	;0
	scf
	ret

; Input:
;  c = status
;  bcu = 0
;  ix = endpoint
; Output:
;  cf = success
;  zf = ? | false
;  af = ?
;  bc = ?
;  de = ?
;  hl = ? | error
;  iy = ?
_FlushEndpoint.loop:
.equ _FlushEndpoint.loop.nop, NOP_OPCODE
assert (_FlushEndpoint.loop.nop == 0)
	xor	a, a
	sbc	hl, hl
	call	_RetireFirstTransfer
	ret	nc
_FlushEndpoint.check:
	bit_mask	endpoint.flags.freed, (ix + (endpoint.flags - endpoint))
	jr	nz, _FlushEndpoint.dangling
_FlushEndpoint:
	ld	iy, (ix + (endpoint.first - endpoint))
	ld	a, (iy + transfer.next)
.rept transfer_next_dummy_msb+1
	rrca
.endr
	jr	nc, _FlushEndpoint.loop
assert (endpoint.overlay.altNext+2 == endpoint.overlay.status-2)
	ld	(ix + (endpoint.overlay.status - endpoint)-2), bc
	ld	(ix + (endpoint.overlay.next - endpoint)), iy
	ld	(ix + (endpoint.overlay.altNext - endpoint)), iy
	bit_mask	USB_TRANSFER_STALLED, c
	ret	z
	ld	a, (currentRole)
	cpl
	bit	ti.bUsbRole-16, a
	ret	z
	bit_mask	BULK_TRANSFER & INTERRUPT_TRANSFER, (ix + (endpoint.transferInfo - endpoint))
	ret	z
	push	ix
	call	usb_ClearEndpointHalt
	pop	af
	ex	de, hl
	scf
	sbc	hl, hl
	adc	hl, de
	ret
_FlushEndpoint.dangling:
	bit_mask	endpoint.flags.refCnt, (ix + (endpoint.flags - endpoint))
	ret	nz
	lea	iy, ix+0
_FlushEndpoint.free:
	ld	hl, (iy + (endpoint.last - endpoint))
	call	_Free32Align32
	lea	hl, iy + (endpoint.base - endpoint)
	jp	_Free64Align256

; Input:
;  a = ignorable smc
;  c = status
;  bcu = 0
;  hl = transferred
;  ix = endpoint
; Output:
;  zf = ignored
;  cf = ? | success
;  af = ?
;  de = ?
;  hl = 0 | error
;  ix = endpoint (maybe just freed)
;  iy = ignored transfer | ?
_RetireFirstTransfer:
	bit_mask	endpoint.flags.refCnt, (ix + (endpoint.flags - endpoint))
	set_mask	endpoint.flags.refCnt, (ix + (endpoint.flags - endpoint))
	ld	de, (ix + (endpoint.first - endpoint))
	push	af
	push	de
	push	bc
_RetireFirstTransfer.loop:
	push	de
	pop	iy
	ld	de, (iy + transfer.altNext)
	bit	0, e
	jr	z, _RetireFirstTransfer.alt
	ld	de, (iy + transfer.next)
_RetireFirstTransfer.alt:
	ld	a, (ix + (endpoint.transferInfo - endpoint))
	and	a, endpoint.transferInfo.type
assert (~CONTROL_TRANSFER)
	jr	nz, _RetireFirstTransfer.notControl
	bit_mask	transfer.type.ioc, (iy + transfer.type)
	jr	z, _RetireFirstTransfer.loop
_RetireFirstTransfer.notControl:
	ld	(ix + (endpoint.first - endpoint)), de
	ld	de, (iy + transfer.data+0)
	ld	a, (iy + transfer.data+3)
	xor	a, e
	and	a, 0xF
	xor	a, e
	ld	e, a
	ld	b, 0
	push	de
	push	hl
	push	bc
	push	ix
	ld	hl, (iy + transfer.callback+0)
	ld	a, (iy + transfer.callback+3)
	xor	a, l
	and	a, 0xF
	xor	a, l
	ld	l, a
	call	_DispatchEvent.dispatch
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	pop	af
	ld	(_RetireFirstTransfer.smc), a
	jr	nz, _RetireFirstTransfer.restored
	res_mask	endpoint.flags.refCnt, (ix + (endpoint.flags - endpoint))
_RetireFirstTransfer.restored:
	add	hl, de
	scf
	sbc	hl, de
_RetireFirstTransfer.smc:
	ret	z
	ex	de, hl
_RetireFirstTransfer.free:
	lea	hl, iy+0
	bit_mask	transfer.type.ioc, (iy + transfer.type)
	ld	iy, (hl)
	call	_Free32Align32
	jr	z, _RetireFirstTransfer.free
	ld	hl, 1
	add	hl, de
	ret

;-------------------------------------------------------------------------------
_HandleCxSetupInt:
	ld	b, 4
	ld	de, setupPacket+4
	ld	l, ti.usbDmaFifo-0x100
	ld	a, i
	di
	ld	(hl), ti.bmUsbDmaCxFifo
	ld	l, ti.usbEp0Data+4-0x100
_HandleCxSetupInt.fetch:
	dec	hl
	dec	de
	ld	a, (hl)
	ld	(de), a
	set_mask	4, e
	ld	a, (hl)
	ld	(de), a
	res_mask	4, e
	djnz	_HandleCxSetupInt.fetch
	ld	l, ti.usbDmaFifo-0x100
	jp	po, _HandleCxSetupInt.noEi
	ei
_HandleCxSetupInt.noEi:
	ld	(hl), b	;ti.bmUsbDmaNoFifo
	ld	l, ti.usbCxFifo-0x100
	set	ti.bCxFifoClr, (hl)
	ld	a, USB_DEFAULT_SETUP_EVENT
	call	_DispatchEvent
	jr	z, _HandleCxSetupInt.defaultHandler
	xor	a, a
	add	hl, de
	scf
	sbc	hl, de
	inc	hl
	ex	de, hl
	jp	_HandleCxSetupInt.return
_HandleCxSetupInt.defaultHandler:
	ld	iy, setupPacket
	ld	hl, (iy + setup.wValue)
	ld	de, (iy + setup.wIndex)
	ld	bc, (iy + setup.bmRequestType)
	ld	a, c
	inc	b
	djnz	_HandleCxSetupInt.notGetStatus
	sub	a, DEVICE_TO_HOST | STANDARD_REQUEST-1
	ld	b, a
	ld	a, d
	or	a, l
	or	a, h
	jp	nz, _HandleCxSetupInt.unhandled
	ld	c, tempEndpointStatus_size
	or	a, e
	djnz	_HandleCxSetupInt.notGetDeviceStatus
	jp	nz, _HandleCxSetupInt.unhandled
	scf
	jr	_HandleCxSetupInt.sendStatus
_HandleCxSetupInt.notGetDeviceStatus:
	djnz	_HandleCxSetupInt.notGetInterfaceStatus
	xor	a, a
_HandleCxSetupInt.sendBitStatus:
assert (tempEndpointStatus_size == 1 << 1)
	and	a, c
	rrca
_HandleCxSetupInt.sendStatus:
	ld	de, tempEndpointStatus
	ld	(de), a
	jr	nc, _HandleCxSetupInt.sendGetStatusDataStage
assert (tempEndpointStatus-1 == deviceStatus)
	dec	de
_HandleCxSetupInt.sendGetStatusDataStage:
	jp	_HandleCxSetupInt.sendDataStage
_HandleCxSetupInt.notGetInterfaceStatus:
	djnz	_HandleCxSetupInt.notGetEndpointStatus
	jr	z, _HandleCxSetupInt.sendStatus
	call	_HandleCxSetupInt.lookupEndpointA
	ld	a, (hl)
.rept ti.bUsbEpStall-8-1
	rrca
.endr
	jr	nz, _HandleCxSetupInt.sendBitStatus
_HandleCxSetupInt.notGetEndpointStatus:
_HandleCxSetupInt.notClearDeviceRemoteWakeupFeature:
_HandleCxSetupInt.notClearEndpointFeature:
_HandleCxSetupInt.notSetDeviceTestModeFeature:
_HandleCxSetupInt.notSetEndpointFeature:
	jp	_HandleCxSetupInt.unhandled
_HandleCxSetupInt.notGetStatus:
	djnz	_HandleCxSetupInt.notClearFeature
assert (~HOST_TO_DEVICE | STANDARD_REQUEST)
	inc	a
	ld	b, a
	ld	a, d
	or	a, h
	or	a, (iy + setup.wLength+0)
	or	a, (iy + setup.wLength+1)
	djnz	_HandleCxSetupInt.notClearDeviceFeature
	or	a, e
	jp	nz, _HandleCxSetupInt.unhandled
	ld	b, l
	djnz	_HandleCxSetupInt.notClearDeviceRemoteWakeupFeature
	ld	hl, deviceStatus
	res_mask	DEVICE_REMOTE_WAKEUP_STATUS, (hl)
	jp	_HandleCxSetupInt.handled
_HandleCxSetupInt.notClearDeviceFeature:
	dec	b
	djnz	_HandleCxSetupInt.notClearEndpointFeature
assert (~ENDPOINT_HALT_FEATURE)
	or	a, l
	jp	nz, _HandleCxSetupInt.unhandled
	call	_HandleCxSetupInt.lookupEndpoint
	jp	z, _HandleCxSetupInt.unhandled
	ld	a, (hl)
	or	a, ti.bmUsbEpReset >> 8
	and	a, ~ ti.bmUsbEpStall >> 8
	ld	(hl), a
	jr	_HandleCxSetupInt.handled
_HandleCxSetupInt.notClearFeature:
	dec	b
	djnz	_HandleCxSetupInt.notSetFeature
assert (~HOST_TO_DEVICE | STANDARD_REQUEST)
	inc	a
	ld	b, a
	ld	a, h
	or	a, (iy + setup.wLength+0)
	or	a, (iy + setup.wLength+1)
	djnz	_HandleCxSetupInt.notSetDeviceFeature
	or	a, e
	ld	b, l
	djnz	_HandleCxSetupInt.notSetDeviceRemoteWakeupFeature
	or	a, d
	jp	nz, _HandleCxSetupInt.unhandled
	ld	hl, deviceStatus
	set_mask	DEVICE_REMOTE_WAKEUP_STATUS, (hl)
	jr	_HandleCxSetupInt.handled
_HandleCxSetupInt.notSetDeviceRemoteWakeupFeature:
	djnz	_HandleCxSetupInt.notSetDeviceTestModeFeature
	jp	nz, _HandleCxSetupInt.unhandled
	ld	b, d
	ld	a, 1
_HandleCxSetupInt.shift:
	rlca
	and	a, 0xF << 1
	jp	z, _HandleCxSetupInt.unhandled
	djnz	_HandleCxSetupInt.shift
	ld	hl, ti.mpUsbPhyTmsr
	or	a, (hl)
	ld	(hl), a
	jr	_HandleCxSetupInt.handled
_HandleCxSetupInt.notSetDeviceFeature:
	dec	b
	djnz	_HandleCxSetupInt.notSetEndpointFeature
	or	a, d
assert (~ENDPOINT_HALT_FEATURE)
	or	a, l
	jp	nz, _HandleCxSetupInt.unhandled
	call	_HandleCxSetupInt.lookupEndpoint
	jp	z, _HandleCxSetupInt.unhandled
	ld	a, (hl)
	and	a, ~ ti.bmUsbEpReset >> 8
	or	a, ti.bmUsbEpStall >> 8
	ld	(hl), a
	call	_HandleCxSetupInt.handled
	push	hl
	push	de
	ex	(sp), ix
assert (HOST_TO_DEVICE | STANDARD_REQUEST | RECIPIENT_ENDPOINT-1 == USB_TRANSFER_STALLED)
	dec	c
	call	_FlushEndpoint
	pop	ix
	pop	de
	ret	nc
	ex	de, hl
	cp	a, a
	ret
_HandleCxSetupInt.notSetFeature:
	dec	b
	djnz	_HandleCxSetupInt.notSetAddress
	ld	a, l
	and	a, 0x80
	or	a, h
	or	a, e
	or	a, d
assert (~HOST_TO_DEVICE | STANDARD_REQUEST | RECIPIENT_DEVICE)
	or	a, c
	ld	de, (iy + setup.wLength)
	or	a, e
	or	a, d
	jp	nz, _HandleCxSetupInt.unhandled
	ld	(ti.mpUsbDevAddr), hl
_HandleCxSetupInt.handled:
	ld	a, ti.bmCxFifoFin
_HandleCxSetupInt.success:
	cp	a, a
_HandleCxSetupInt.return:
	ld	hl, ti.mpUsbCxFifo
	ld	(hl), a
	ld	l, ti.usbCxIsr-0x100
	ld	(hl), ti.bmUsbIntCxSetup
	ret	z
	ex	de, hl
	ret
_HandleCxSetupInt.notSetAddress:
	djnz	_HandleCxSetupInt.notGetDescriptor
	xor	a, DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE
	jr	z, _HandleCxSetupInt.getDescriptor
_HandleCxSetupInt.notGetDescriptor:
	djnz	_HandleCxSetupInt.notSetDescriptor
_HandleCxSetupInt.notSetDescriptor:
	djnz	_HandleCxSetupInt.notGetConfiguration
	xor	a, DEVICE_TO_HOST | STANDARD_REQUEST | RECIPIENT_DEVICE
	or	a, l
	or	a, h
	or	a, e
	or	a, d
	jr	nz, _HandleCxSetupInt.unhandled
	ld	c, 1
	ld	de, selectedConfiguration
	jp	_HandleCxSetupInt.sendDataStage
_HandleCxSetupInt.notGetConfiguration:
	djnz	_HandleCxSetupInt.notSetConfiguration
assert (~HOST_TO_DEVICE | STANDARD_REQUEST | RECIPIENT_DEVICE)
	or	a, h
	or	a, e
	or	a, d
	ld	bc, (iy + setup.wLength)
	or	a, c
	or	a, b
	jr	nz, _HandleCxSetupInt.unhandled
	or	a, l
	jr	z, _HandleCxSetupInt.setConfigured
	push	ix
	ld	ix, (currentDescriptors)
	ld	iy, (ix + standardDescriptors.device)
	ld	b, (iy + deviceDescriptor.bNumConfigurations)
	ld	hl, (ix + standardDescriptors.configurations)
_HandleCxSetupInt.findConfigurationDescriptor:
	ld	ix, (hl)
	cp	a, (ix + configurationDescriptor.bConfigurationValue)
	jr	z, _HandleCxSetupInt.foundConfigurationDescriptor
.rept 3
	inc	hl
.endr
	ld	a, e
	djnz	_HandleCxSetupInt.findConfigurationDescriptor
_HandleCxSetupInt.foundConfigurationDescriptor:
	ld	iy, (rootHub.child)
	ld	de, (ix + configurationDescriptor.wTotalLength)
	ld	b, (ix + configurationDescriptor.bNumInterfaces)
	push	ix
	call	z, _ParseInterfaceDescriptors
	pop	de
	pop	ix
	jr	nz, _HandleCxSetupInt.unhandled
	ld	a, (setupPacket.wValue)
	scf
_HandleCxSetupInt.setConfigured:
	ld	(selectedConfiguration), a
	ld	hl, ti.mpUsbDevAddr
	ld	a, (hl)
	rla
	rrca
	ld	(hl), a
	call	_HandleCxSetupInt.handled
	ld	a, USB_HOST_CONFIGURE_EVENT
	jp	_DispatchEvent
_HandleCxSetupInt.notSetConfiguration:
	djnz	_HandleCxSetupInt.notGetInterface
_HandleCxSetupInt.notGetInterface:
	djnz	_HandleCxSetupInt.notSetInterface
_HandleCxSetupInt.notSetInterface:
_HandleCxSetupInt.unhandled:
	ld	a, ti.bmCxFifoStall
	jp	_HandleCxSetupInt.success
_HandleCxSetupInt.getDescriptor:
	push	hl
	pop	bc
	ld	iy, (currentDescriptors)
	djnz	_HandleCxSetupInt.notDevice	;DEVICE_DESCRIPTOR
	or	a, c
	or	a, e
	or	a, d
	jr	nz, _HandleCxSetupInt.unhandled
_HandleCxSetupInt.sendSingleDescriptorIYind:
	ld	b, a
	ld	hl, (iy + standardDescriptors.device)
_HandleCxSetupInt.sendSingleDescriptorHL:
	ld	c, (hl)
	ex	de, hl
	jr	_HandleCxSetupInt.sendDataStage
_HandleCxSetupInt.notDevice:
	djnz	_HandleCxSetupInt.notConfiguration	;CONFIGURATION_DESCRIPTOR
	or	a, e
	or	a, d
	jr	nz, _HandleCxSetupInt.unhandled
	ld	hl, (iy + standardDescriptors.configurations)
	ld	iy, (iy + standardDescriptors.device)
	ld	a, c
	cp	a, (iy + deviceDescriptor.bNumConfigurations)
	jr	nc, _HandleCxSetupInt.unhandled
.rept 3
	add	hl, bc
.endr
	ld	iy, (hl)
	ld	bc, (iy + configurationDescriptor.wTotalLength)
	ld	de, (hl)
	jr	_HandleCxSetupInt.sendDataStage
_HandleCxSetupInt.notConfiguration:
	djnz	_HandleCxSetupInt.notString	;STRING_DESCRIPTOR
	ld	hl, (iy + standardDescriptors.langids)
	cp	a, c
	jr	z, _HandleCxSetupInt.langids
	ld	a, (iy + standardDescriptors.numStrings)
	cp	a, c
	jr	c, _HandleCxSetupInt.unhandled
	ld	iy, (iy + standardDescriptors.strings)
	ld	a, (hl)
	rra
	dec	a
	ld	b, a
	dec	c
	mlt	bc
.rept 3
	add	iy, bc
.endr
	ld	b, a
	inc	hl
_HandleCxSetupInt.findLangId:
	inc	hl
	ld	a, (hl)
	inc	hl
	sub	a, e
	jr	nz, _HandleCxSetupInt.nextLangId
	ld	a, (hl)
	sub	a, d
	jr	z, _HandleCxSetupInt.sendSingleDescriptorIYind
_HandleCxSetupInt.nextLangId:
	lea	iy, iy+3
	djnz	_HandleCxSetupInt.findLangId
_HandleCxSetupInt.langids:
	or	a, e
	or	a, d
	jr	z, _HandleCxSetupInt.sendSingleDescriptorHL
_HandleCxSetupInt.notString:
	jr	_HandleCxSetupInt.unhandled
_HandleCxSetupInt.sendDataStage:
	ld	hl, ti.mpUsbDmaFifo
	ld	(hl), ti.bmUsbDmaCxFifo
	ld	l, ti.usbDmaAddr-0x100
	ld	(hl), de
	ld	l, ti.usbDmaCtrl-0x100
	ld	a, (setupPacket.bmRequestType)
	rlca
	rlca
	xor	a, (hl)
	and	a, ti.usbDmaMem2Fifo
	xor	a, (hl)
	ld	(hl), a
	inc	l	;ti.usbDmaLen-$100
	ex	de, hl
	ld	hl, (setupPacket.wLength)
	sbc.s	hl, bc
	jr	c, _HandleCxSetupInt.min
	sbc	hl, hl
_HandleCxSetupInt.min:
	add.s	hl, bc
	ex	de, hl
	ld	(hl), de
	dec	l	;ti.usbDmaCtrl-$100
	set	ti.bUsbDmaStart, (hl)
	ld	l, ti.usbDevIsr-0x100
_HandleCxSetupInt.wait:
	bit	ti.bUsbIntDevDmaFin, (hl)
	jr	z, _HandleCxSetupInt.wait
	ld	(hl), ti.bmUsbIntDevDmaFin
	xor	a, a
	ld	l, ti.usbDmaFifo-0x100
	ld	(hl), a
	jp	_HandleCxSetupInt.handled
; Input:
;  e = endpoint address
; Output:
;  zf = invalid endpoint address or default control address
;  a = ?
;  de = endpoint | de
;  hl = endpoint register+1 | ?
_HandleCxSetupInt.lookupEndpoint:
	ld	a, e
_HandleCxSetupInt.lookupEndpointA:
	add	a, a
	dec	a
	cp	a, 1 << 5-1
	sbc	a, a
	ld	hl, (rootHub.child)
	call	nz, usb_GetDeviceEndpoint.check
	ret	z
	ld	a, e
_HandleCxSetupInt.lookupEndpointRegister:
	add	a, a
	ld	de, ti.mpUsbInEp1+1-4
	jr	c, _HandleCxSetupInt.in
assert (ti.usbInEp1 < ti.usbOutEp1)
	set_mask	(ti.usbInEp1+1-4) ^ (ti.usbOutEp1+1-4), e
_HandleCxSetupInt.in:
	add	a, a
	add	a, e
	ld	e, a
	ex	de, hl
	ret

_HubHandler.0:
	xor	a, a
	jr	_HubHandler
_HubHandler.status:
	ld	a, hub.status_size+hub.change_size
_HubHandler:
;	ld	c,$FF
_HubHandler.any:
	pop	hl
	push	ix
	ld	ix, 0
	lea	de, ix+0
	add	ix, sp
	xor	a, (ix+12)
;	and	a,c
	or	a, (ix+9)
	jr	nz, _HubHandler.free
	ld	iy, (ix+15)
	ld	bc, (ix+6)
	jp	(hl)
_HubHandler.free:
	sbc	hl, hl
_HubHandler.error:
	pop	ix
	ex	de, hl
	call	_FreeTransferData
	ex	de, hl
	ret
_HubHandler.descriptor:
	ld	a, hub.desc_size
	call	_HubHandler.any
	ld	(iy + hub.setup.wLength-1), de
	ld	d, (iy + hub.desc.bNbrPorts)
	ld	a, d
	dec	a
	cp	a, 7
	jr	nc, _HubHandler.free
	ld	(iy + hub.setup.wIndex-1), de
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (HOST_TO_DEVICE | CLASS_REQUEST | RECIPIENT_OTHER) << 0 | SET_FEATURE_REQUEST << 8 | 8 << 16
	ld	(iy + hub.setup.bmRequestType), hl
_HubHandler.power:
	call	_HubHandler.control
	call	_HubHandler.0
	dec	(iy + hub.setup.wIndex+0)
	jr	nz, _HubHandler.power
	ld	a, (iy + hub.desc.bPwrOn2PwrGood)
	add	a, 3
	rra
	srl	a ; WARNING: This assumes flash wait states port is 3, to get at least a*8ms!
	call	nz, ti.DelayTenTimesAms
	ex	de, hl
	add	hl, bc
	ld	l, endpoint.device
	ld	hl, (hl)
	ld	de, (hl)
	bit	0, e
	jr	nz, _HubHandler.free
	ld	l, endpoint.transferInfo
	inc	e
	ld	b, 0x10-1
_HubHandler.find:
	inc	e
	inc	e
	ld	a, (de)
	ld	h, a
	inc	a
	jr	z, _HubHandler.notfound
	ld	a, (hl)
assert (~(INTERRUPT_TRANSFER+1) & INTERRUPT_TRANSFER)
	cpl
	and	a, INTERRUPT_TRANSFER
	jr	z, _HubHandler.found
_HubHandler.notfound:
	djnz	_HubHandler.find
	jr	_HubHandler.free
_HubHandler.found:
	ld	l, endpoint
	ld	(iy + hub.endpoint), hl
_HubHandler.change:
	ld	de, _HubHandler.changed
	ld	bc, 1
;	ld	c,(iy.hub.desc.bNbrPorts)
;	srl	c
;	srl	c
;	srl	c
;	inc	c
	push	iy
	push	de
	push	bc
	pea	iy + hub.bitmap
	push	hl
	call	usb_ScheduleTransfer
	ld	sp, ix
	pop	ix
	ret
_HubHandler.changed:
;	ld	hl,12
;	add	hl,sp
;	ld	iy.hub,(hl)
;	ld	a,(iy.hub.desc.bNbrPorts)
;	rra
;	srl	a
;	srl	a
;	inc	a
	ld	a, 1
	call	_HubHandler.any
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (DEVICE_TO_HOST | CLASS_REQUEST | RECIPIENT_DEVICE) << 0 | GET_STATUS_REQUEST << 8 | 0 << 16
	ld	(iy + hub.setup.bmRequestType), hl
	ld	(iy + hub.setup.wIndex+0), a
	ld	(iy + hub.setup.wLength+0), hub.status_size+hub.change_size
	ex	de, hl
	add	hl, bc
	ld	l, endpoint.device
	ld	hl, (hl)
	call	usb_RefDevice.enter
	ld	(iy + hub.device), hl
	call	usb_GetDeviceEndpoint.masked
	jp	z, _HubHandler.free
	push	hl
	pop	bc
	xor	a, a
	srl	(iy + hub.bitmap)
	jr	nc, _HubHandler.old
	call	_HubHandler.control
	call	_HubHandler.status
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (HOST_TO_DEVICE | CLASS_REQUEST | RECIPIENT_DEVICE) << 0 | CLEAR_FEATURE_REQUEST << 8 | 0 << 16
	ld	(iy + hub.setup.bmRequestType), hl
	ld	(iy + hub.setup.wLength+0), a
assert (USB_HUB_LOCAL_POWER_GOOD_EVENT+1 == USB_HUB_LOCAL_POWER_LOST_EVENT)
assert (USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT+1 == USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT)
.macro report_hub_change iteration, event
 .if \iteration != 1
	inc	(iy + hub.setup.wValue+0)
 .endif
	srl	(iy + hub.change+0)
	jr	nc, .Lhub_change_done\@
	call	_HubHandler.control
	call	_HubHandler.0
	ld	a, (iy + hub.status+0)
 .rept \iteration-1
	rrca
 .endr
	and	a, 1
	add	a, USB_\event\()_EVENT
	ld	de, (iy + hub.device)
	push	bc
	call	_DispatchEvent
	pop	bc
	jp	nz, _HubHandler.error
	ld	iy, (ix+15)
.Lhub_change_done\@:
.endm
report_hub_change 1, HUB_LOCAL_POWER_GOOD
report_hub_change 2, DEVICE_OVERCURRENT_DEACTIVATED
.purgem report_hub_change
_HubHandler.old:
	scf
_HubHandler.old.loop:
	ld	hl, (iy + hub.device)
	set_mask	device.child, l
	jp	c, _HubHandler.old.enter
assert (device.child-1 == device.portNbr)
	dec	l
	ld	e, (hl)
	ld	(iy + hub.setup.wIndex+0), e
	ld	a, 0x80
_HubHandler.old.shift:
	rlca
	dec	e
	jr	nz, _HubHandler.old.shift
	and	a, (iy + hub.bitmap)
	jp	z, _HubHandler.old.skip
	cpl
	and	a, (iy + hub.bitmap)
	ld	(iy + hub.bitmap), a
	; TODO: clear change before getting status
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (DEVICE_TO_HOST | CLASS_REQUEST | RECIPIENT_OTHER) << 0 | GET_STATUS_REQUEST << 8 | 0 << 16
	ld	(iy + hub.setup.bmRequestType), hl
	ld	(iy + hub.setup.wLength+0), hub.status_size+hub.change_size
	call	_HubHandler.control
	call	_HubHandler.status
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (HOST_TO_DEVICE | CLASS_REQUEST | RECIPIENT_OTHER) << 0 | CLEAR_FEATURE_REQUEST << 8 | 16 << 16
	ld	(iy + hub.setup.bmRequestType), hl
	ld	(iy + hub.setup.wLength+0), a
_HubHandler.old.changed:
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.old.16
	bit	0, (iy + hub.status+0)
	jr	nz, _HubHandler.old.reconnected
	call	_HubHandler.control
	call	_HubHandler.0
_HubHandler.old.reconnected:
	push	bc
	push	ix
	ld	ix, (iy + hub.device)
	dec	ixl
	call	nz, _DeviceDisconnected
	pop	ix
	pop	bc
	jp	nz, _HubHandler.error
	ld	iy, (ix+15)
	jp	_HubHandler.old.disconnected
_HubHandler.old.16:
	inc	(iy + hub.setup.wValue+0)
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.old.17
	call	_HubHandler.control
	call	_HubHandler.0
	push	bc
	push	ix
	ld	ix, (iy + hub.device)
	dec	ixl
	call	nz, _DeviceDisabled
	pop	ix
	pop	bc
	jp	nz, _HubHandler.error
	ld	iy, (ix+15)
_HubHandler.old.17:
	inc	(iy + hub.setup.wValue+0)
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.old.18
	call	_HubHandler.control
	call	_HubHandler.0
	ld	a, (iy + hub.status+0)
 .rept 2
	rrca
 .endr
	and	a, 1
assert (USB_DEVICE_RESUMED_EVENT+1 == USB_DEVICE_SUSPENDED_EVENT)
	add	a, USB_DEVICE_RESUMED_EVENT
	ld	de, (iy + hub.device)
	push	bc
	call	_DispatchEvent
	pop	bc
	jp	nz, _HubHandler.error
	ld	iy, (ix+15)
_HubHandler.old.18:
	inc	(iy + hub.setup.wValue+0)
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.old.19
	call	_HubHandler.control
	call	_HubHandler.0
	ld	a, (iy + hub.status+0)
 .rept 3
	rrca
 .endr
	and	a, 1
assert (USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT+1 == USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT)
	add	a, USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT
	ld	de, (iy + hub.device)
	push	bc
	call	_DispatchEvent
	pop	bc
	jp	nz, _HubHandler.error
	ld	iy, (ix+15)
_HubHandler.old.19:
	inc	(iy + hub.setup.wValue+0)
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.old.20
	call	_HubHandler.control
	call	_HubHandler.0
	push	bc
	ld	de, (iy + hub.device)
	call	usb_ResetDevice.enabled
	pop	bc
_HubHandler.old.disconnected:
	ld	iy, (ix+15)
_HubHandler.old.20:
_HubHandler.old.skip:
	ld	hl, (iy + hub.device)
	set_mask	device.sibling, l
_HubHandler.old.enter:
	push	bc
	ld	hl, (hl)
	bit	0, l
	call	z, usb_RefDevice.enter
	ld	de, (iy + hub.device)
	ld	(iy + hub.device), hl
	ex	de, hl
	call	usb_UnrefDevice.enter
	pop	bc
	bit	0, (iy + hub.device)
	jp	z, _HubHandler.old.loop
	ld	(iy + hub.setup.wIndex+0), a
_HubHandler.new.loop:
	inc	(iy + hub.setup.wIndex+0)
	srl	(iy + hub.bitmap)
	jr	nc, _HubHandler.new.skip
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (DEVICE_TO_HOST | CLASS_REQUEST | RECIPIENT_OTHER) << 0 | GET_STATUS_REQUEST << 8 | 0 << 16
	ld	(iy + hub.setup.bmRequestType), hl
	ld	(iy + hub.setup.wLength+0), hub.status_size+hub.change_size
	call	_HubHandler.control
	call	_HubHandler.status
assert (hub.setup.bmRequestType+1 == hub.setup.bRequest)
assert (hub.setup.bmRequestType+2 == hub.setup.wValue+0)
	ld	hl, (HOST_TO_DEVICE | CLASS_REQUEST | RECIPIENT_OTHER) << 0 | CLEAR_FEATURE_REQUEST << 8 | 16 << 16
	ld	(iy + hub.setup.bmRequestType), hl
	ld	(iy + hub.setup.wLength+0), a
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.new.unchanged
	call	_HubHandler.control
	call	_HubHandler.0
	bit	0, (iy + hub.status+0)
	jr	z, _HubHandler.new.changed
	ex	de, hl
	add	hl, bc
	ld	l, endpoint.device
	ld	de, (hl)
	ld	c, IS_DEVICE | IS_DISABLED
	ld	b, (iy + hub.setup.wIndex+0)
	ld	a, (iy + hub.status+1)
	and	a, 3 << 1
	rlca
	rlca
	rlca
	call	_CreateDevice
	ld	iy, (ix+15)
	ld	bc, (ix+6)
	jr	z, _HubHandler.new.loop
	jp	_HubHandler.error
_HubHandler.new.changed:
	inc	(iy + hub.setup.wValue+0)
	srl	(iy + hub.change+0)
	jr	nc, _HubHandler.new.unchanged
	call	_HubHandler.control
	call	_HubHandler.0
	inc	e
_HubHandler.new.unchanged:
	jr	nz, _HubHandler.new.changed
	inc	d
_HubHandler.new.skip:
	jr	nz, _HubHandler.new.loop
	ld	hl, (iy + hub.endpoint)
	jp	_HubHandler.change
_HubHandler.control:
	pop	hl
	push	iy
	push	hl
	pea	iy + hub.status
	push	iy
	push	bc
	call	usb_ScheduleControlTransfer
	ld	sp, ix
	pop	ix
	ret

_HandleDevInt:
	ld	l, ti.usbGisr-0x100
	inc	h
.irp type, Cx, Fifo, Dev
	bit	ti.bUsbDevInt\type\(), (hl)
	call	nz, _HandleDev\type\()Int
	ret	nz
.endr
	ld	l, ti.usbIsr
	dec	h
	ld	(hl), ti.bmUsbIntDev
	ld	a, USB_DEVICE_INTERRUPT
	jp	_DispatchEvent

_HandleDevCxInt:
	ld	l, ti.usbCxIsr-0x100
.irp type, Setup, In, Out, End, Err, Abort
	bit	ti.bUsbIntCx\type\(), (hl)
	call	nz, _HandleCx\type\()Int
	ret	nz
.endr
	ld	l, ti.usbGisr-0x100
	ld	(hl), ti.bmUsbDevIntCx
	ld	a, USB_DEVICE_CONTROL_INTERRUPT
	jp	_DispatchEvent

_HandleDevFifoInt:
	ld	l, ti.usbFifoTxImr-0x100
	ld	a, (hl)
	cpl
	ld	l, ti.usbFifoTxIsr-0x100
	and	a, (hl)
	ld	c, a
.irp fifo, 0, 1, 2, 3
	push	bc
	bit	ti.bUsbIntFifo\fifo\()In, c
	call	nz, _HandleFifo\fifo\()InInt
	pop	bc
	ret	nz
.endr
	ld	l, ti.usbFifoRxIsr-0x100
.irp fifo, 0, 1, 2, 3
	bit	ti.bUsbIntFifo\fifo\()Spk, (hl)
	call	nz, _HandleFifo\fifo\()SpkInt
	ret	nz
	bit	ti.bUsbIntFifo\fifo\()Out, (hl)
	call	nz, _HandleFifo\fifo\()OutInt
	ret	nz
.endr
	ld	l, ti.usbGisr-0x100
	ld	(hl), ti.bmUsbDevIntFifo
	ret

_HandleDevDevInt:
	ld	l, ti.usbDevIsr-0x100
.irp type, Reset, Suspend, Resume, IsocErr, IsocAbt, ZlpTx, ZlpRx, DmaFin
	bit	ti.bUsbIntDev\type\(), (hl)
	call	nz, _HandleDev\type\()Int
	ret	nz
.endr
	inc	l	;ti.usbDevIsr+1-$100
.irp type, DmaErr, Idle, Wakeup
	bit	ti.bUsbIntDev\type\()-8, (hl)
	call	nz, _HandleDev\type\()Int
	ret	nz
.endr
	ld	l, ti.usbGisr-0x100
	ld	(hl), ti.bmUsbDevIntDev
	ld	a, USB_DEVICE_DEVICE_INTERRUPT
	jp	_DispatchEvent

_HandleOtgInt:
	ld	l, ti.usbOtgIsr
.irp type, BSrpComplete, ASrpDetect, AVbusErr, BSessEnd
	bit	ti.bUsbInt\type\(), (hl)
	call	nz, _Handle\type\()Int
	ret	nz
.endr
	inc	l	;ti.usbOtgIsr+1
.irp type, RoleChg, IdChg, Overcurr, BPlugRemoved, APlugRemoved
	bit	ti.bUsbInt\type\()-8, (hl)
	call	nz, _Handle\type\()Int
	ret	nz
.endr
	ld	l, ti.usbIsr
	ld	(hl), ti.bmUsbIntOtg
	ld	a, USB_OTG_INTERRUPT
	jp	_DispatchEvent

_HandleHostInt:
	ld	l, ti.usbSts
	ld	a, 0
.equ _HandleHostInt.hack, .-1
	and	a, ti.bmUsbIntErr | ti.bmUsbInt
	call	nz, _HandleCompletionInt
	ret	nz
	ld	hl, ti.mpUsbSts
.irp type, PortChgDetect, FrameListOver, HostSysErr, AsyncAdv
	bit	ti.bUsbInt\type\(), (hl)
	call	nz, _Handle\type\()Int
	ret	nz
.endr
	ld	l, ti.usbIsr
	ld	(hl), ti.bmUsbIntHost
	ld	a, USB_HOST_INTERRUPT
	jp	_DispatchEvent

_HandleCxInInt:
_HandleCxOutInt:
	ld	l, ti.usbCxFifoBytes-0x100
	ld	c, (hl)
	xor	a, a
	ld	b, a
	call	_ExecuteDma
	ret	c
	ld	hl, ti.mpUsbCxIsr
	ld	(hl), ti.bmUsbIntCxOut | ti.bmUsbIntCxIn
	cp	a, a
	ret

_HandleCxEndInt:
	ld	l, ti.usbCxFifo-0x100
	ld	(hl), ti.bmCxFifoFin
	ld	l, ti.usbCxIsr-0x100
	ld	(hl), ti.bmUsbIntCxEnd
	cp	a, a
	ret

_HandleCxErrInt:
	ld	(hl), ti.bmUsbIntCxErr
	ld	a, USB_CONTROL_ERROR_INTERRUPT
	jp	_DispatchEvent

_HandleCxAbortInt:
	ld	(hl), ti.bmUsbIntCxAbort
	ld	a, USB_CONTROL_ABORT_INTERRUPT
	jp	_DispatchEvent

.irp fifo, 0, 1, 2, 3
_HandleFifo\fifo\()OutInt:
	ld	l, ti.usbFifo\fifo\()Csr-0x100
	ld	bc, (hl)
	ld	a, \fifo+0x01
	call	_ExecuteDma
	ret	c
	ld	hl, ti.mpUsbFifoRxIsr
	ld	(hl), ti.bmUsbIntFifo\fifo\()Out
	cp	a, a
	ret

_HandleFifo\fifo\()SpkInt:
	ld	(hl), ti.bmUsbIntFifo\fifo\()Spk
	ld	a, USB_FIFO\fifo\()_SHORT_PACKET_INTERRUPT
	jp	_DispatchEvent

_HandleFifo\fifo\()InInt:
	ld	a, \fifo+0x81
	call	_ExecuteDma
	ret	c
	ld	hl, ti.mpUsbFifoTxIsr
	ld	(hl), ti.bmUsbIntFifo\fifo\()In
	cp	a, a
	ret
.endr

_HandleDevResetInt:
	call	_RootDeviceDisconnected
	ret	nz
	xor	a, a
	ld	l, ti.usbDevAddr-0x100
	ld	(hl), a
	ld	(selectedConfiguration), a
	inc	a
	ld	(deviceStatus), a
	ld	l, ti.usbDmaCtrl-0x100
	ld	(hl), ti.bmUsbDmaClrFifo | ti.bmUsbDmaAbort
	ld	l, ti.usbCxFifo-0x100
	set	ti.bCxFifoClr, (hl)
	ld	c, IS_DEVICE | IS_ENABLED
	ld	l, ti.usbDevCtrl-0x100
	ld	a, (hl)
	and	a, ti.bmUsbDevSpd
	call	_CreateDevice.root
	call	z, _CreateDefaultControlEndpoint
	ret	nz
	ld	hl, (currentDescriptors)
	ld	hl, (hl)
	ld	de, 7
	add	hl, de
	ld	a, (hl)
	ld	(iy + (endpoint.maxPktLen - endpoint)), a
	ld	hl, ti.mpUsbDevIsr
	ld	(hl), ti.bmUsbIntDevReset
	ret

_HandleDevSuspendInt:
	ld	(hl), ti.bmUsbIntDevSuspend
	ld	de, (rootHub.child)
	cp	a, a
	ld	a, e
	rrca
	ret	c
	ld	a, USB_DEVICE_SUSPENDED_EVENT
	jp	_DispatchEvent

_HandleDevResumeInt:
	ld	(hl), ti.bmUsbIntDevResume
	ld	de, (rootHub.child)
	cp	a, a
	ld	a, e
	rrca
	ret	c
	ld	a, USB_DEVICE_RESUMED_EVENT
	jp	_DispatchEvent

_HandleDevIsocErrInt:
	ld	(hl), ti.bmUsbIntDevIsocErr
	ld	a, USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT
	jp	_DispatchEvent

_HandleDevIsocAbtInt:
	ld	(hl), ti.bmUsbIntDevIsocAbt
	ld	a, USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT
	jp	_DispatchEvent

_HandleDevZlpTxInt:
	ld	l, ti.usbTxZlp-0x100
	xor	a, a
	ld	(hl), a
	ld	l, ti.usbDevIsr-0x100
	ld	(hl), ti.bmUsbIntDevZlpTx
	ret

_HandleDevZlpRxInt:
	ld	l, ti.usbRxZlp-0x100
	call	_HandleDevZlpRxInt.almostMostAtomicExchangePossible
_HandleDevZlpRxInt.loop:
	inc	b
	srl	c
	push	bc
	ld	a, b
	ld	b, 0
	ld	c, b
	call	c, _ExecuteDma
	pop	bc
	ret	c
	inc	c
	dec	c
	jr	nz, _HandleDevZlpRxInt.loop
	ld	hl, ti.mpUsbDevIsr
	ld	(hl), ti.bmUsbIntDevZlpRx
	ret

_HandleDevZlpRxInt.almostMostAtomicExchangePossible:
	ld	a, i
.equ _HandleDevZlpRxInt.exchange, EXCHANGE_CODE
	ld	iy, ti.mpLcdRange
	ld	bc, _HandleDevZlpRxInt.exchange
	di
	ld	de, (iy+ti.lcdLpbase+1)
	ld	(iy+ti.lcdLpbase+1), bc
	ld	b, 0
	call	ti.mpLcdLpbase+1
	ld	(iy+ti.lcdLpbase+1), de
	ret	po
	ei
	ret

_HandleDevDmaFinInt:
	ld	(hl), ti.bmUsbIntDevDmaFin
	ld	a, USB_DEVICE_DMA_FINISH_INTERRUPT
	jp	_DispatchEvent

_HandleDevDmaErrInt:
	ld	(hl), ti.bmUsbIntDevDmaErr >> 8
	ld	a, USB_DEVICE_DMA_ERROR_INTERRUPT
	jp	_DispatchEvent

_HandleDevIdleInt:
	ld	(hl), ti.bmUsbIntDevIdle >> 8
	ld	a, USB_DEVICE_IDLE_INTERRUPT
	jp	_DispatchEvent

_HandleDevWakeupInt:
	ld	l, ti.usbPhyTmsr-0x100
	res	ti.bUsbUnplug, (hl)
	ld	l, ti.usbDevIsr+1-0x100
	ld	(hl), ti.bmUsbIntDevWakeup >> 8
	ld	a, USB_DEVICE_WAKEUP_INTERRUPT
	jp	_DispatchEvent

_HandleBSrpCompleteInt:
	ld	(hl), ti.bmUsbIntBSrpComplete
	ld	a, USB_B_SRP_COMPLETE_INTERRUPT
	jp	_DispatchEvent

_HandleASrpDetectInt:
	ld	(hl), ti.bmUsbIntASrpDetect
	ld	a, USB_A_SRP_DETECT_INTERRUPT
	jp	_DispatchEvent

_HandleAVbusErrInt:
	ld	(hl), ti.bmUsbIntAVbusErr
	ld	a, USB_A_VBUS_ERROR_INTERRUPT
	jp	_DispatchEvent

_HandleBSessEndInt:
	ld	(hl), ti.bmUsbIntBSessEnd
	ld	a, USB_B_SESSION_END_INTERRUPT
	jp	_DispatchEvent

_HandleRoleChgInt:
_HandleIdChgInt:
	ld	de, currentRole
	ld	a, (de)
	ld	c, a
	ld	(hl), (ti.bmUsbIntRoleChg | ti.bmUsbIntIdChg) >> 8
	ld	a, (ti.mpUsbOtgCsr+2)
	and	a, (ti.bmUsbRole | ti.bmUsbId) >> 16
	cp	a, c
	ret	z
	ld	(de), a
	call	_PowerVbusForRole
assert (~USB_ROLE_CHANGED_EVENT)
	xor	a, a	;USB_ROLE_CHANGED_EVENT
	ld	l, ti.usbOtgIsr+1
	jp	_DispatchEvent

_HandleOvercurrInt:
	ld	(hl), ti.bmUsbIntOvercurr >> 8
	ld	a, USB_OVERCURRENT_INTERRUPT
	jp	_DispatchEvent

_HandleAPlugRemovedInt:
_HandleBPlugRemovedInt:
	ld	(hl), (ti.bmUsbIntAPlugRemoved | ti.bmUsbIntBPlugRemoved) >> 8

; Output:
;  af = ?
;  zf = success
;  de = ? | hl
;  hl = hl | error
;  iy = ?
_RootDeviceDisconnected:
	ld	de, _DeviceDisconnected
_RootDeviceDisconnected.enter:
	ex	de, hl
	push	de
	push	ix
	ld	ix, (rootHub.child)
	dec	ixl
	call	nz, _DispatchEvent.dispatch
	pop	ix
	pop	de
	ret	nz
	ex	de, hl
	ret

_HandleCompletionInt:
	ld	(hl), a
usb_PollTransfers:
	push	ix
usb_PollTransfers.async.restart:
	ld	ix, dummyHead
usb_PollTransfers.async:
	bit_mask	endpoint.flags.freed, (ix + (endpoint.flags - endpoint))
	jr	nz, usb_PollTransfers.async.restart
	ld	ix, (ix + (endpoint.next - endpoint))
	or	a, a
	sbc	hl, hl
	ld	a, ixh
	xor	a, dummyHead >> 8 & 0xFF
	call	nz, _RetireTransfers.nc
	jr	c, usb_PollTransfers.async
	pop	ix
usb_PollTransfers.enabled:
	ret	nz
.equ usb_PollTransfers.enable, RET_NZ
.equ usb_PollTransfers.disable, RET_OPCODE
	push	ix
	ld	ix, periodicList
	ld	b, 1 << 7
usb_PollTransfers.periodic:
	lea	ix, ix+4
usb_PollTransfers.periodic.restart:
	push	ix
usb_PollTransfers.isoc:
	ld	de, (ix-4)
	ld	ixh, d
	ld	ixl, e
	bit	2, e
	jr	nz, usb_PollTransfers.isoc
usb_PollTransfers.intr:
	srl	e
	jr	c, usb_PollTransfers.periodic.done
	ld	a, (ix + (endpoint.interval - endpoint))
	cp	a, b
	jr	c, usb_PollTransfers.periodic.done
	push	bc
	call	_RetireTransfers.nc
	pop	bc
	jr	nc, usb_PollTransfers.periodic.error
	bit_mask	endpoint.flags.freed, (ix + (endpoint.flags - endpoint))
	ld	ix, (ix + (endpoint.next - endpoint))
	ld	e, ixl
	jr	z, usb_PollTransfers.intr
	or	a, a
usb_PollTransfers.periodic.done:
	pop	ix
	jr	nc, usb_PollTransfers.periodic.restart
	djnz	usb_PollTransfers.periodic
	or	a, a
	sbc	hl, hl
.equ usb_PollTransfers.ld_a, LD_A_IMM
	.db	usb_PollTransfers.ld_a
usb_PollTransfers.periodic.error:
	pop	bc
	pop	ix
	ret

_HandlePortChgDetectInt:
	ld	(hl), ti.bmUsbIntPortChgDetect
	ld	l, ti.usbPortStsCtrl
.irp type, ConnSts, PortEn, Overcurr
	bit	ti.bUsb\type\()Chg, (hl)
	call	nz, _HandlePort\type\()Int
	ret	nz
.endr
	ld	l, ti.usbSts
	ret

_HandlePortConnStsInt:
	call	_RootDeviceDisconnected
	ret	nz
	ld	a, (hl)
	and	a, ~ (ti.bmUsbOvercurrChg | ti.bmUsbPortEnChg | ti.bmUsbPortEn)
	ld	(hl), a
	bit	ti.bUsbCurConnSts, (hl)
	ret	z
	ld	c, IS_DEVICE | IS_DISABLED
	ld	l, ti.usbOtgCsr+2
	ld	a, (hl)
	and	a, ti.bmUsbSpd >> 16
	rrca

; Input:
;  a = device speed shl 4
;  c = find flags
;  b = port
;  de = parent hub
; Output:
;  zf = success
;  a = ?
;  bc = ?
;  de = ?
;  hl = ti.mpUsbPortStsCtrl | error
;  iy = device
_CreateDevice.root:
	rrca
	ld	de, rootHub
	ld	b, 0
_CreateDevice:
	call	_Alloc32Align32
	jr	nz, _CreateDevice.error
	push	hl
	pop	iy
	call	_Alloc32Align32
	jr	nz, _CreateDevice.nomem
	ld	(iy + device.endpoints), hl
	ex	de, hl
	ld	(iy + device.hub), hl
assert (device.find+1 == device.portNbr)
assert (device.find+2 == device.child)
	ld	(iy + device.find), bc
	ld	(iy + device.speed), a
	call	usb_RefDevice.enter
	set_mask	device.child, l
	jr	_CreateDevice.enter
_CreateDevice.skip:
	ld	hl, (hl)
	set_mask	device.sibling, l
_CreateDevice.enter:
	bit	0, (hl)
	jr	z, _CreateDevice.skip
	ld	(iy + device.back), hl
	ld	(hl), iy
	ld	bc, 32-1
	push	de
	inc	de
	pop	hl
	ld	(hl), -1
	ldir
	ld	(iy + device.addr), b	;0
	ld	(iy + device.data), bc	;0
	inc	c	;1
	ld	(iy + device.refcnt), bc	;1
	ld	(iy + device.sibling), c	;1
	ld	(iy + device.child), c	;1
	ld	hl, ti.mpUsbPortStsCtrl
	ld	a, USB_DEVICE_CONNECTED_EVENT
	ld	c, (iy + device.find)
_CreateDevice.enabled:
	lea	de, iy+0
	push	bc
	push	de
	call	_DispatchEvent
	pop	iy
	pop	bc
	ret	nz
	bit_mask	IS_ENABLED, c
	ret	z
	ld	a, USB_DEVICE_ENABLED_EVENT
assert (~USB_DEVICE_ENABLED_EVENT & IS_ENABLED)
	ld	c, a
	jr	_CreateDevice.enabled
_CreateDevice.nomem:
	lea	hl, iy+0
	call	_Free32Align32
_CreateDevice.error:
	ld	hl, USB_ERROR_NO_MEMORY
	ret

_HandlePortPortEnInt:
	ld	a, (hl)
	and	a, ~ (ti.bmUsbOvercurrChg | ti.bmUsbConnStsChg)
	ld	(hl), a
	call	_HandlePortPortEnInt.disabled
	ret	nz
	bit	ti.bUsbPortEn, (hl)
	ret	z
	ld	de, (rootHub.child)
	dec	e
	jr	z, _HandlePortPortEnInt.disable
	call	_Alloc32Align32
	jr	nz, _HandlePortPortEnInt.disable
	push	hl
	pop	iy
	ld	hl, resetList
	ld	bc, (hl)
	ld	(iy + reset.next), bc
	inc	e
	ld	(iy + reset.device), de
	ld	(hl), iy
	or	a, a
	call	usb_ResetDevice.enabled.enter
	ld	hl, ti.mpUsbPortStsCtrl
	cp	a, a
	ret
_HandlePortPortEnInt.disable:
	ld	hl, ti.mpUsbPortStsCtrl
	ld	a, (hl)
	and	a, ~ (ti.bmUsbOvercurrChg | ti.bmUsbPortEnChg | ti.bmUsbPortEn | ti.bmUsbConnStsChg)
	ld	(hl), a
_HandlePortPortEnInt.disabled:
	ld	de, _DeviceDisabled
	jp	_RootDeviceDisconnected.enter

_HandlePortOvercurrInt:
	ld	a, (hl)
	and	a, ~ (ti.bmUsbPortEnChg | ti.bmUsbConnStsChg)
	ld	(hl), a
	ld	a, (hl)
	and	a, ti.bmUsbOvercurrActive
	cp	a, ti.bmUsbOvercurrActive
	sbc	a, a
assert (USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT - 1 == USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT)
	add	a, USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT	;USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT
	jr	_DispatchEvent

_HandleFrameListOverInt:
	ld	(hl), ti.bmUsbIntFrameListOver
	ex	de, hl
_HandleFrameListOverInt.cleanup:
	ld	hl, intrCleanupReady
	ld	bc, (hl)
	dec	hl
	ld	(hl), bc

; Input:
;  c = cleanup list head
; Output:
;  zf = true
;  cf = cf
;  f = ?
;  c = 0
;  de = ?
;  hl = de
;  iy = ?
_CleanupEndpoints:
	ld	iy, dummyHead
_CleanupEndpoints.loop:
	ld	iyh, c
	ex	de, hl
	inc	c
	ret	z
	ex	de, hl
	ld	c, (iy + (endpoint.prev - endpoint))
	set_mask	endpoint.flags.freed, (iy + (endpoint.flags - endpoint))
	bit_mask	endpoint.flags.refCnt, (iy + (endpoint.flags - endpoint))
	call	z, _FlushEndpoint.free
	jr	_CleanupEndpoints.loop

_HandleHostSysErrInt:
	ld	(hl), ti.bmUsbIntHostSysErr
	ld	a, USB_HOST_SYSTEM_ERROR_INTERRUPT
	jr	_DispatchEvent

_HandleAsyncAdvInt:
	ld	(hl), ti.bmUsbIntAsyncAdv
_HandleAsyncAdvInt.cleanup.hl:
	ex	de, hl
_HandleAsyncAdvInt.cleanup.de:
	ld	hl, asyncCleanupReady
	ld	bc, (hl)
	call	_CleanupEndpoints
	jr	_HandleAsyncAdvInt.ready
_HandleAsyncAdvInt.scheduleCleanup.de:
	ret	nz
	ex	de, hl
_HandleAsyncAdvInt.scheduleCleanup.hl:
	ret	nz
	ld	bc, (asyncCleanupReady)
	inc	c
	jr	nz, _HandleAsyncAdvInt.success
_HandleAsyncAdvInt.ready:
	ld	(asyncCleanupReady-1), bc
	inc	b
	ret	z
	ld	c, l
	ld	l, ti.usbCmd
	set	ti.bUsbIntAsyncAdvDrbl, (hl)
	ld	l, c
_HandleAsyncAdvInt.success:
	cp	a, a
	ret

;-------------------------------------------------------------------------------
; Dispatch a global usb event.
; Input:
;  a = event
;  de = event data
; Output:
;  af = ?
;  zf = success
;  bc = ?
;  de = 0 | hl
;  hl = hl | error
;  iy = ?
_DispatchEvent:
	push	hl
	ld	hl, (eventCallback.data)
	push	hl
	push	de
	or	a, a
	sbc	hl, hl
	ld	l, a
	push	hl
	ld	l, h
	ex	de, hl
	ld	hl, (eventCallback)
	sbc	hl, de
	call	nz, _DispatchEvent.dispatch
	pop	de
	pop	de
	pop	de
	pop	de
	add	hl, de
	or	a, a
	sbc	hl, de
	ret	nz
	ex	de, hl
	ret

;-------------------------------------------------------------------------------
usb_MsToCycles:
	pop	de
	ex	(sp), hl
	push	de
usb_MsToCycles.enter:
assert (48000 & 0xFF == 0x80)
	dec.s	bc
usb_MsToCycles.zbcu:
	ld	c, l
	ld	b, h
	xor	a, a
	srl	b
	rr	c
	rra
	ld	e, 48000 >> 8
	ld	d, h
	ld	h, e
	mlt	hl
	add	hl, bc
	mlt	de
	push	de
	dec	sp
	pop	de
	ld	e, 0
	add	hl, de
	dec	sp
	push	hl
	dec	sp
	pop	hl
	pop	de
	ld	l, a
	ret

;-------------------------------------------------------------------------------
usb_GetCycleCounter:
	call	usb_GetCounter
	dec	sp
	dec	sp
	push	hl
	dec	sp
	pop	hl
	pop	de
	ld	l, a
	ret

;-------------------------------------------------------------------------------
usb_GetCounter:
	ld	iy, ti.mpTmrRange
	lea	hl, iy+ti.tmr2Counter
	lea	de, iy+ti.tmr2Match2
	ld	bc, 4
	ld	a, i
	di
	jp	pe, usb_GetCounter.ei
	ldir
.equ usb_GetCounter.ld_hl, LD_HL_IMM
	.db	usb_GetCounter.ld_hl
usb_GetCounter.ei:
	ldir
	ei
usb_GetCounter.di:
	ld	a, (iy+ti.tmr2Match2+0)
	ld	hl, (iy+ti.tmr2Match2+1)
	add	a, 7 << 0
	add	a, 7 << 1
	ret	nc
	inc	l
	ret	nz
	cp	a, 7 << 0
	ret	nc
	inc	h
	ret

;-------------------------------------------------------------------------------
usb_StopTimer:
	ret

;-------------------------------------------------------------------------------
usb_StartTimerCycles:
	ret

;-------------------------------------------------------------------------------
usb_RepeatTimerCycles:
	ret

;-------------------------------------------------------------------------------
_DefaultControlEndpointDescriptor:
	.db	7, ENDPOINT_DESCRIPTOR, 0, 0
	.dw	8
	.db	0
_DefaultStandardDescriptors:
	.d24	_DefaultStandardDescriptors.device, _DefaultStandardDescriptors.configurations, _DefaultStandardDescriptors.langids
	.db	2
	.d24	_DefaultStandardDescriptors.strings
_DefaultStandardDescriptors.device:
	.db 0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40, 0x51, 0x04, 0x08, 0xE0, 0x20, 0x02, 0x01, 0x02
	.db 0x00, 0x03
_DefaultStandardDescriptors.configurations:
	.d24	_DefaultStandardDescriptors.configuration1, _DefaultStandardDescriptors.configuration2, _DefaultStandardDescriptors.configuration3
_DefaultStandardDescriptors.configuration1:
	.db 0x09, 0x02, 0x23, 0x00, 0x01, 0x01, 0x00, 0x80, 0xFA, 0x09, 0x04, 0x00, 0x00, 0x02, 0xFF, 0x01
	.db 0x00, 0x00, 0x07, 0x05, 0x81, 0x02, 0x40, 0x00, 0x00, 0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00
	.db 0x03, 0x09, 0x03
_DefaultStandardDescriptors.configuration2:
	.db 0x09, 0x02, 0x23, 0x00, 0x01, 0x02, 0x00, 0xC0, 0x00, 0x09, 0x04, 0x00, 0x00, 0x02, 0xFF, 0x01
	.db 0x00, 0x00, 0x07, 0x05, 0x81, 0x02, 0x40, 0x00, 0x00, 0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00
	.db 0x03, 0x09, 0x03
_DefaultStandardDescriptors.configuration3:
	.db 0x09, 0x02, 0x23, 0x00, 0x01, 0x03, 0x00, 0x80, 0x32, 0x09, 0x04, 0x00, 0x00, 0x02, 0xFF, 0x01
	.db 0x00, 0x00, 0x07, 0x05, 0x81, 0x02, 0x40, 0x00, 0x00, 0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00
	.db 0x03, 0x09, 0x03
_DefaultStandardDescriptors.langids:
	.dw	0x0304, 0x0409
_DefaultStandardDescriptors.strings:
	.d24	_DefaultStandardDescriptors.string1
_DefaultStandardDescriptors.model:
	.d24	_DefaultStandardDescriptors.string84
_DefaultStandardDescriptors.string1:
	.dw	0x033E, 0x54, 0x65, 0x78, 0x61, 0x73, 0x20, 0x49, 0x6e, 0x73, 0x74, 0x72, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x49, 0x6e, 0x63, 0x6f, 0x72, 0x70, 0x6f, 0x72, 0x61, 0x74, 0x65, 0x64
_DefaultStandardDescriptors.string83:
	.dw	0x0322, 0x54, 0x49, 0x2d, 0x38, 0x33, 0x20, 0x50, 0x72, 0x65, 0x6d, 0x69, 0x75, 0x6d, 0x20, 0x43, 0x45
_DefaultStandardDescriptors.string84:
	.dw	0x031C, 0x54, 0x49, 0x2d, 0x38, 0x34, 0x20, 0x50, 0x6c, 0x75, 0x73, 0x20, 0x43, 0x45
