;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library USBDRVCE, 0

DEBUG := 0

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export usb_Init
	export usb_Cleanup
	export usb_PollTransfers
	export usb_HandleEvents
	export usb_WaitForEvents
	export usb_WaitForInterrupt
	export usb_RefDevice
	export usb_UnrefDevice
	export usb_GetDeviceHub
	export usb_SetDeviceData
	export usb_GetDeviceData
	export usb_GetDeviceFlags
	export usb_FindDevice
	export usb_ResetDevice
	export usb_DisableDevice
	export usb_GetDeviceAddress
	export usb_GetDeviceSpeed
	export usb_GetConfigurationDescriptorTotalLength
	export usb_GetDescriptor
	export usb_SetDescriptor
	export usb_GetStringDescriptor
	export usb_SetStringDescriptor
	export usb_GetConfiguration
	export usb_SetConfiguration
	export usb_GetInterface
	export usb_SetInterface
	export usb_SetEndpointHalt
	export usb_ClearEndpointHalt
	export usb_GetDeviceEndpoint
	export usb_GetEndpointDevice
	export usb_SetEndpointData
	export usb_GetEndpointData
	export usb_GetEndpointAddress
	export usb_GetEndpointTransferType
	export usb_GetEndpointMaxPacketSize
	export usb_GetEndpointInterval
	export usb_SetEndpointFlags
	export usb_GetEndpointFlags
	export usb_GetRole
	export usb_GetFrameNumber
	export usb_ControlTransfer
	export usb_Transfer
	export usb_ScheduleControlTransfer
	export usb_ScheduleTransfer
	export usb_MsToCycles
	export usb_GetCycleCounter
	export usb_GetCycleCounterHigh
	export usb_StopTimer
	export usb_StartTimerCycles
	export usb_RepeatTimerCycles

;-------------------------------------------------------------------------------
; macros
;-------------------------------------------------------------------------------
macro ?!
 macro assertpo2? value*
  local val
  val = value
  if ~val | val <> 1 shl bsr val
   err '"', `value, '" is not a power of two'
  end if
 end macro

 iterate op, bit, res, set
  macro op#msk? index*, value
   local idx, val, rest
   idx = index
   assertpo2 idx
   match @, value
    val equ value
   else
    val equ
    rest equ index
    while 1
     match car.cdr, rest
      match any, val
       val equ any.car
      else
       val equ car
      end match
      rest equ cdr
     else
      val equ (val)
      break
     end match
    end while
   end match
   match v, val
	op	bsr idx,v
   end match
  end macro
 end iterate

 macro struct? name*
  macro end?.struct?!
      iterate base, ., .base
       if defined base
        assert base+sizeof base=$
       end if
      end iterate
    end namespace
   end struc
   iterate <base,prefix>, 0,, ix-name,x, iy-name,y
    virtual at base
	prefix#name	name
    end virtual
   end iterate
   purge end?.struct?
  end macro
  struc name
   namespace .
 end macro

 purge ?
end macro

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
struct timer
	local size
	label .: size
	tick		rd 1
	next		rl 1
	callback	rl 1
	size := $-.
end struct
struct transfer			; transfer structure
	label .: 32
	next		rd 1	; pointer to next transfer structure
 namespace next
	dummy		:= 1 shl 0
 end namespace
	altNext		rd 1	; pointer to alternate next transfer structure
	status		rb 1	; transfer status
 namespace status
	active		:= 1 shl 7
	halted		:= 1 shl 6
	bufErr		:= 1 shl 5
	babble		:= 1 shl 4
	xactErr		:= 1 shl 3
	ufMiss		:= 1 shl 2
	split		:= 1 shl 1
	stall		:= 1 shl 0
 end namespace
	type		rb 1
 namespace type
	ioc		:= 1 shl 7
	cpage		:= 7 shl 4
	cerr		:= 3 shl 2
	pid		:= 3 shl 0
 end namespace
	remaining	rw 1	; transfer remaining length
 namespace remaining
	?dt		:= 1 shl 15
 end namespace
	label buffers: 20	; transfer buffers
			rl 1
	length		rl 1	; original transfer length
	callback	rd 1	; user callback
	data		rd 1	; user callback data
	endpoint	rd 1	; pointer to endpoint structure
	padding		rb 1
	fifo		rb 1	; associated fifo mask
end struct
struct endpoint			; endpoint structure
	label base: 64
	label .: 62 at $+2
 virtual
	next		rl 1	; link to next endpoint structure
	prev		rb 1	; link to prev endpoint structure
 end virtual
			rw 1
	maxHsSbp	rw 1
	addr		rb 1	; device addr or cancel shl 7
	info		rb 1	; ep or speed shl 4 or dtc shl 6
 namespace info
	head		:= 1 shl 7
	dtc		:= 1 shl 6
	eps		:= 3 shl 4
	ep		:= $F
 end namespace
	maxPktLen	rw 1	; max packet length or c shl 15 or 1 shl 16
 namespace maxPktLen
	?msk		:= $7FF
	?c		:= 1 shl 11
	?rl		:= $F shl 12
 end namespace
	smask		rb 1	; micro-frame s-mask
	cmask		rb 1	; micro-frame c-mask
	hubInfo		rw 1	; hub addr or port num shl 7 or mult shl 14
	cur		rd 1	; current transfer pointer
	overlay		transfer; current transfer
	transferInfo	rb 1	; transfer type or transfer dir shl 7
 namespace transferInfo
	?dir		:= 1 shl 7
	?type		:= 3 shl 0
 end namespace
	flags		rb 1	; endpoint flags
 namespace flags
	autoTerm	:= 1 shl 0
 end namespace
	internalFlags	rb 1	; internal endpoint flags
 namespace internalFlags
	po2Mps		:= 1 shl 0
	refCnt		:= 1 shl 1
	freed		:= 1 shl 2
 end namespace
	interval	rb 1	; transfer po2 interval
	device		rl 1	; pointer to device
	first		rl 1	; pointer to first scheduled transfer
	last		rl 1	; pointer to last dummy transfer
	data		rl 1	; user data
end struct
struct device			; device structure
	label .: 32
	endpoints	rl 1	; pointer to array of endpoints
	find		rb 1	; find flags
	refcnt		rl 1	; reference count
	hubPorts	rb 1	; number of ports in this hub
	sibling		rl 1	; next device connected to the same hub
	speed		rb 1	; device speed shl 4
	back		rl 1	; update pointer to next pointer to self
	addr		rb 1	; device addr and $7F
	child		rl 1	; first device connected to this hub
	hub		rl 1	; hub this device is connected to
	data		rl 1	; user data
			rb 7	; padding
end struct
struct setup
	label .: 8
	bmRequestType	rb 1
	bRequest	rb 1
	wValue		rw 1
	wIndex		rw 1
	wLength		rw 1
end struct
struct standardDescriptors
	local size
	label .: size
	device		rl 1
	configurations	rl 1
	langids		rl 1
	numStrings	rb 1
	strings		rl 1
	size := $-.
end struct
struct descriptor
	label .: 2
	bLength			rb 1
	bDescriptorType		rb 1
end struct
struct deviceDescriptor
	label .: 18
	descriptor		descriptor
	bcdUSB			rw 1
	bDeviceClass		rb 1
	bDeviceSubClass		rb 1
	bDeviceProtocol		rb 1
	bMaxPacketSize0		rb 1
	idVendor		rw 1
	idProduct		rw 1
	bcdDevice		rw 1
	iManufacturer		rb 1
	iProduct		rb 1
	iSerialNumber		rb 1
	bNumConfigurations	rb 1
end struct
struct deviceQualifierDescriptor
	label .: 10
	descriptor		descriptor
	bcdUSB			rw 1
	bDeviceClass		rb 1
	bDeviceSubClass		rb 1
	bDeviceProtocol		rb 1
	bMaxPacketSize0		rb 1
	bNumConfigurations	rb 1
	bReserved		rb 1
end struct
struct configurationDescriptor
	label .: 9
	descriptor		descriptor
	wTotalLength		rw 1
	bNumInterfaces		rb 1
	bConfigurationValue	rb 1
	iConfiguration		rb 1
	bmAttributes		rb 1
	bMaxPower		rb 1
end struct
otherSpeedConfigurationDescriptor equ configurationDescriptor
struct interfaceDescriptor
	label .: 9
	descriptor		descriptor
	bInterfaceNumber	rb 1
	bAlternateSetting	rb 1
	bNumEndpoints		rb 1
	bInterfaceClass		rb 1
	bInterfaceSubClass	rb 1
	bInterfaceProtocol	rb 1
	iInterface		rb 1
end struct
struct endpointDescriptor
	label .: 7
	descriptor		descriptor
	bEndpointAddress	rb 1
	bmAttributes		rb 1
	wMaxPacketSize		rw 1
	bInterval		rb 1
end struct
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; memory locations
;-------------------------------------------------------------------------------
virtual at (ti.saveSScreen+$FFFF) and not $FFFF
	cHeap			dbx (ti.saveSScreen+21945) and not $FF - $: ?
end virtual
virtual at ti.usbArea
				rb (-$) and 7
	?setupPacket		setup
				rb (-$) and $1F
	?rootHub		device
	?usbMem			dbx ti.usbInited and not $1FFF - $: ?
				rb (-$) and $FFF
	?periodicList		dbx ti.usbInited and not $FF - $: ?
				rb (-$) and $FF
	?dummyHead		endpoint
				rb (-$) and $1F
	?usedAddresses		dbx 128/8: ?
	?eventCallback		rl 1
	?eventCallback.data	rl 1
	?currentDescriptors	rl 1
	?selectedConfiguration	rb 1
	?deviceStatus		rb 1
	?tempEndpointStatus	rw 1
	?currentRole		rl 1
	?freeList32Align32	rl 1
	?freeList64Align256	rl 1
	?timerList		rl 1
assert $+1 = cleanupListReady
				rb 1 ; clobber
	?cleanupListReady	rb 1
assert cleanupListReady+1 = cleanupListPending
	?cleanupListPending	rb 1
assert cleanupListPending+1 = $
				rb 1 ; always -1
if DEBUG
	?alloc32Align32		rl 1
	?alloc64Align256	rl 1
end if
	assert $ <= ti.usbInited
end virtual
virtual at (ti.ramCodeTop+$FF) and not $FF
	osHeap			dbx ti.heapTop and not $FF - $: ?
end virtual
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; usb constants
;-------------------------------------------------------------------------------
; enum usb_error
virtual at 0
	USB_SUCCESS		rb 1
	USB_IGNORE		rb 1
	USB_ERROR_SYSTEM	rb 1
	USB_ERROR_INVALID_PARAM	rb 1
	USB_ERROR_SCHEDULE_FULL	rb 1
	USB_ERROR_NO_DEVICE	rb 1
	USB_ERROR_NO_MEMORY	rb 1
	USB_ERROR_NOT_SUPPORTED	rb 1
	USB_ERROR_OVERFLOW	rb 1
	USB_ERROR_TIMEOUT	rb 1
	USB_ERROR_FAILED	rb 1
end virtual

; enum usb_transfer_status
?USB_TRANSFER_COMPLETED		:= 0
?USB_TRANSFER_STALLED		:= 1 shl 0
?USB_TRANSFER_NO_DEVICE		:= 1 shl 1
?USB_TRANSFER_HOST_ERROR	:= 1 shl 2
?USB_TRANSFER_ERROR		:= 1 shl 3
?USB_TRANSFER_OVERFLOW		:= 1 shl 4
?USB_TRANSFER_BUS_ERROR		:= 1 shl 5
?USB_TRANSFER_FAILED		:= 1 shl 6
?USB_TRANSFER_CANCELLED		:= 1 shl 7

; enum usb_event
virtual at 0
	USB_ROLE_CHANGED_EVENT					rb 1
	USB_DEVICE_DISCONNECTED_EVENT				rb 1
	USB_DEVICE_CONNECTED_EVENT				rb 1
	USB_DEVICE_DISABLED_EVENT				rb 1
	USB_DEVICE_ENABLED_EVENT				rb 1
	USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT		rb 1
	USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT			rb 1
	USB_DEFAULT_SETUP_EVENT					rb 1
	USB_HOST_CONFIGURE_EVENT				rb 1
	; Temp debug events:
	USB_DEVICE_INTERRUPT					rb 1
	USB_DEVICE_CONTROL_INTERRUPT				rb 1
	USB_DEVICE_DEVICE_INTERRUPT				rb 1
	USB_OTG_INTERRUPT					rb 1
	USB_HOST_INTERRUPT					rb 1
	USB_CONTROL_ERROR_INTERRUPT				rb 1
	USB_CONTROL_ABORT_INTERRUPT				rb 1
	USB_FIFO0_SHORT_PACKET_INTERRUPT			rb 1
	USB_FIFO1_SHORT_PACKET_INTERRUPT			rb 1
	USB_FIFO2_SHORT_PACKET_INTERRUPT			rb 1
	USB_FIFO3_SHORT_PACKET_INTERRUPT			rb 1
	USB_DEVICE_SUSPEND_INTERRUPT				rb 1
	USB_DEVICE_RESUME_INTERRUPT				rb 1
	USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT			rb 1
	USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT			rb 1
	USB_DEVICE_DMA_FINISH_INTERRUPT				rb 1
	USB_DEVICE_DMA_ERROR_INTERRUPT				rb 1
	USB_DEVICE_IDLE_INTERRUPT				rb 1
	USB_DEVICE_WAKEUP_INTERRUPT				rb 1
	USB_B_SRP_COMPLETE_INTERRUPT				rb 1
	USB_A_SRP_DETECT_INTERRUPT				rb 1
	USB_A_VBUS_ERROR_INTERRUPT				rb 1
	USB_B_SESSION_END_INTERRUPT				rb 1
	USB_OVERCURRENT_INTERRUPT				rb 1
	USB_HOST_PORT_CONNECT_STATUS_CHANGE_INTERRUPT		rb 1
	USB_HOST_PORT_ENABLE_DISABLE_CHANGE_INTERRUPT		rb 1
	USB_HOST_PORT_OVERCURRENT_CHANGE_INTERRUPT		rb 1
	USB_HOST_PORT_FORCE_PORT_RESUME_INTERRUPT		rb 1
	USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT			rb 1
	USB_HOST_SYSTEM_ERROR_INTERRUPT				rb 1
end virtual

; enum usb_find_flag
?IS_NONE					:= 0
?IS_DISABLED					:= 1 shl 0
?IS_ENABLED					:= 1 shl 1
?IS_DEVICE					:= 1 shl 2
?IS_HUB						:= 1 shl 3
?IS_ATTACHED					:= 1 shl 4

; enum usb_endpoint_flag
?MANUAL_TERMINATE				:= 0 shl 0
?AUTO_TERMINATE					:= 1 shl 0

; enum usb_role
virtual at 0
	?ROLE_HOST				rb 1 shl 4
	?ROLE_DEVICE				rb 1 shl 4
end virtual
virtual at 0
	?ROLE_A					rb 1 shl 5
	?ROLE_B					rb 1 shl 5
end virtual

; enum usb_transfer_direction
virtual at 0
	?HOST_TO_DEVICE				rb 1 shl 7
	?DEVICE_TO_HOST				rb 1 shl 7
end virtual

; enum usb_request_type
virtual at 0
	?STANDARD_REQUEST			rb 1 shl 5
	?CLASS_REQUEST				rb 1 shl 5
	?VENDOR_REQUEST				rb 1 shl 5
end virtual

; enum usb_recipient
virtual at 0
	?RECIPIENT_DEVICE			rb 1 shl 0
	?RECIPIENT_INTERFACE			rb 1 shl 0
	?RECIPIENT_ENDPOINT			rb 1 shl 0
	?RECIPIENT_OTHER			rb 1 shl 0
end virtual

; enum usb_request
virtual at 0
	?GET_STATUS_REQUEST			rb 1
	?CLEAR_FEATURE_REQUEST			rb 1
						rb 1
	?SET_FEATURE_REQUEST			rb 1
						rb 1
	?SET_ADDRESS_REQUEST			rb 1
	?GET_DESCRIPTOR_REQUEST			rb 1
	?SET_DESCRIPTOR_REQUEST			rb 1
	?GET_CONFIGURATION_REQUEST		rb 1
	?SET_CONFIGURATION_REQUEST		rb 1
	?GET_INTERFACE_REQUEST			rb 1
	?SET_INTERFACE_REQUEST			rb 1
	?SYNC_FRAME_REQUEST			rb 1
end virtual

; enum usb_feature
virtual at 0
	?ENDPOINT_HALT_FEATURE			rb 1
	?DEVICE_REMOTE_WAKEUP_FEATURE		rb 1
	?TEST_MODE_FEATURE			rb 1
end virtual

; enum usb_device_status
DEVICE_SELF_POWERED_STATUS			:= 1 shl 0
DEVICE_REMOTE_WAKEUP_STATUS			:= 1 shl 1

; enum usb_endpoint_status
ENDPOINT_HALT_STATUS				:= 1 shl 0

; enum usb_descriptor_type
virtual at 1
	?DEVICE_DESCRIPTOR			rb 1
	?CONFIGURATION_DESCRIPTOR		rb 1
	?STRING_DESCRIPTOR			rb 1
	?INTERFACE_DESCRIPTOR			rb 1
	?ENDPOINT_DESCRIPTOR			rb 1
end virtual

; enum usb_transfer_type
virtual at 0
	?CONTROL_TRANSFER			rb 1
	?ISOCHRONOUS_TRANSFER			rb 1
	?BULK_TRANSFER				rb 1
	?INTERRUPT_TRANSFER			rb 1
end virtual

DEFAULT_RETRIES := 10


SAFE_FS_BT := 83.54e-9 ; safe full-speed bit time (USB 2.0 spec section 5.11.3)
SAFE_FS_SBT := SAFE_FS_BT * 7 / 6 ; safe full-speed stuffed bit time
SAFE_FS_SBPT := SAFE_FS_SBT * 2 ; safe full-speed stuffed bit pair time
FS_FT := 1e-3 ; full-speed frame time
FS_SFT := FS_FT * 0.90 ; full-speed schedulable frame time
FS_SBP_PER_FRAME := trunc (FS_SFT / SAFE_FS_SBPT) ; full-speed stuffed bit pairs per frame

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
usb_Init:
	call	ti.usb_DisableTimer
	call	ti.os.GetSystemStats
repeat 4
	inc	hl
end repeat
	bit	0,(hl)
	jq	z,.84pce
	ld	a,$60
	ld	(_DefaultStandardDescriptors.device+deviceDescriptor.bcdDevice),a
	ld	hl,_DefaultStandardDescriptors.string83
	ld	(_DefaultStandardDescriptors.model),hl
.84pce:
	ld	a,1 ; mark pointers as invalid
	call	_Init
	set	5,(hl);ti.flags+$1B
	ld	hl,ti.mpTmr2Load
	ld	c,12
	call	ti.MemClear
	ld	l,ti.tmrCtrl+1
	set	ti.bTmr2CountUp-8,(hl)
	dec	l;ti.tmrCtrl
	res	ti.bTmr2Crystal,(hl)
	res	ti.bTmr2Overflow,(hl)
	set	ti.bTmr2Enable,(hl)
assert ti.usbHandleKeys and $1F >= long
	ld	(ti.usbHandleKeys),a;0
	sbc	hl,hl
assert endpoint.smask+1 = endpoint.cmask
assert endpoint.smask+2 = endpoint.hubInfo
	ld	(dummyHead.smask), hl
assert deviceStatus+1 = tempEndpointStatus
	ld	(deviceStatus),hl;0
	ld	(timerList),hl;0
	dec	hl
	ld	(cleanupListReady),hl;-1
	inc	hl
	ld	(rootHub.addr),a;0
	ld	(rootHub.data),hl;0
	ld	de,usedAddresses+1
	ld	b,sizeof usedAddresses-1
.freeAddresses:
	ld	(de),a;0
	inc	de
	djnz	.freeAddresses
	ld	l,3
	ld	(currentRole),hl
	add	hl,sp
;	ld	de,eventCallback;eventCallback.data,currentDescriptors
	ld	c,9
	ldir
	ld	de,(hl)
	ld	hl,_ResetHostControllerFromUnknown.misc
	ld	(hl),d
	dec	bc
	ld	hl,(currentDescriptors)
	add	hl,bc
	jq	c,.nonDefaultStandardDescriptors
	ld	hl,_DefaultStandardDescriptors
	ld	(currentDescriptors),hl
.nonDefaultStandardDescriptors:
	ld	hl,ti.mpUsbFifo0Cfg
	ld	(hl),a;0
	inc	l;ti.usbFifo1Cfg-$100
	inc	bc
	ld	(hl),bc;0
	ld	l,ti.usbFifo0Map-$100
	ld	(hl),$01
	inc	l;ti.usbFifo1Map-$100
	ld	bc,$040302
	ld	(hl),bc
	ld	l,ti.usbEp1Map-$100
	ld	(hl),a;$00
	inc	l;ti.usbEp2Map-$100
	ld	bc,$332211
	ld	(hl),bc
	ld	l,ti.usbIdle-$100
	ld	(hl),7
	ld	l,h;ti.usbDevCtrl+1-$100
	ld	(hl),ti.bmUsbDevForceFullSpd shr 8
	dec	l;usbDevCtrl-$100
	ld	(hl),ti.bmUsbDevReset or ti.bmUsbDevEn or ti.bmUsbGirqEn or ti.bmUsbRemoteWake
	ld	l,ti.usbPhyTmsr-$100
	ld	(hl),ti.bmUsbUnplug
	ld	l,ti.usbGimr-$100
	ld	(hl),a;0
	ld	l,ti.usbCxImr-$100
	ld	(hl),a;0
	ld	l,ti.usbFifoRxImr-$100
	ld	(hl),a;0
	ld	l,ti.usbFifoTxImr-$100
	ld	(hl),ti.bmUsbFifoTxInts
	ld	l,ti.usbDevImr-$100
	ld	(hl),a;0
	inc	l;ti.usbDevImr+1-$100
	ld	(hl),ti.bmUsbIntDevIdle shr 8
	dec	h
	ld	l,ti.usbOtgIer
	ld	(hl),ti.bmUsbIntBSrpComplete or ti.bmUsbIntASrpDetect or ti.bmUsbIntAVbusErr ;or ti.bmUsbIntBSessEnd
	inc	l;ti.usbOtgIer+1
	ld	(hl),(ti.bmUsbIntRoleChg or ti.bmUsbIntIdChg or ti.bmUsbIntOvercurr or ti.bmUsbIntBPlugRemoved or ti.bmUsbIntAPlugRemoved) shr 8
	ld	l,ti.usbImr
	ld	(hl),ti.usbIntLevelHigh
	call	_ResetHostControllerFromUnknown
	ld	(hl+endpoint.next),hl+endpoint.next
	ld	(hl+endpoint.next),endpoint
	ld	l,endpoint.prev
	ld	(hl),h
	ld	l,endpoint.info
	ld	(hl),endpoint.info.head
	ld	l,endpoint.overlay.status
	ld	(hl),endpoint.overlay.status.halted
	ld	hl,rootHub.find
	ld	(hl),IS_HUB or IS_ENABLED
	ld	a,e
	and	a,ti.bmUsbFrameListSize
	ld	(_ResetHostControllerFromUnknown.frameListSize),a
assert cHeap = $D10000
	ld	l,a;(cHeap-$D10000) and $FF
	ld	h,a;(cHeap-$D10000) shr 8
	ld	b,sizeof cHeap shr 8
	srl	e
	call	c,.initFreeList
	ld	h,(osHeap-$D10000) shr 8
	ld	b,sizeof osHeap shr 8
	srl	e
	call	c,.initFreeList
	ld	h,(usbMem-$D10000) shr 8
	ld	b,sizeof usbMem shr 8
	call	.initFreeList
assert ti.usbHandleKeys and $FF > $40
	ld	a,(ti.usbHandleKeys and not $1F - $20) and $FF
	ld	(ti.usbHandleKeys and not $1F + $20),a
assert usbMem+sizeof usbMem = periodicList
assert ~periodicList and $FF
	ld	c,l;0
	ld	a,e
	cpl
	and	a,3
	ld	c,usb_PollTransfers.disable
	ld	de,_ScheduleEndpoint.disable
	jq	z,.noPeriodicList
	ld	de,($D10000 and $70000 or not FS_SBP_PER_FRAME shl (31-bsr FS_SBP_PER_FRAME)) shr 8 or $FF
	ld	b,a
	ld	a,1 shl 1
.shift:
	rlca
	djnz	.shift
	ld	(_ScheduleEndpoint.frameListSize+1),a
	ld	b,a
	dec.s	bc
	inc	l
	ld	(hl),de
	ld	de,periodicList+1+dword
	ldir
	ld	c,usb_PollTransfers.enable
	ld	de,_ScheduleEndpoint.enable
.noPeriodicList:
	ld	a,c
	ld	(usb_PollTransfers.enabled),a
	ld	(_ScheduleEndpoint.enabled),de
	ld	a,(periodicList+sizeof periodicList-$D10000) shr 8
	sub	a,h
	ld	b,a
	call	.initFreeList
	ld	hl,ti.mpUsbOtgIsr+1
	call	_HandleRoleChgInt
	ret	nz
	or	a,a
	sbc	hl,hl
if DEBUG
	ld	(alloc32Align32),hl;0
	ld	(alloc64Align256),hl;0
end if
	ret
.initFreeList:
	call	_Free64Align256.uninit
	ld	a,32
.loop:
	add	a,32
	ld	l,a
	call	nz,_Free32Align32.uninit
	jq	nz,.loop
	inc	h
	djnz	.initFreeList
	ret

;-------------------------------------------------------------------------------
usb_Cleanup:
if DEBUG
	ld	de,alloc32Align32
	ld	a,99
	call	_DispatchEvent
end if
	ld	hl,ti.mpUsbCmd
	call	_DisableSchedulesAndResetHostController.enter
;	xor	a,a
	ld	hl,ti.mpUsbGimr
	ld	(hl),a
	ld	l,ti.usbDevImr+1-$100
	ld	(hl),a
;	ld	hl,ti.mpUsbDevIsr
;	ld	(hl),ti.bmUsbIntDevResume or ti.bmUsbIntDevSuspend
;	ld	l,ti.usbDevImr+1-$100
;	set	ti.bUsbIntDevDmaErr-8,(hl)
;	dec	l;ti.usbDevImr-$100
;	set	ti.bUsbIntDevDmaFin,(hl)
	ld	l,ti.usbFifoRxImr-$100
	ld	(hl),ti.bmUsbFifoRxInts
	ld	l,ti.usbFifoTxImr-$100
	ld	(hl),ti.bmUsbFifoTxInts
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
	res	5,(hl);ti.flags+$1B
	ret

;-------------------------------------------------------------------------------
usb_WaitForEvents.wait:
	ret	nz
usb_WaitForEvents:
	ld	hl,.wait
	push	hl
	jq	usb_WaitForInterrupt

;-------------------------------------------------------------------------------
usb_WaitForInterrupt:
	ld	hl,ti.mpIntMask+1
	di
	set	ti.bIntUsb-8,(hl)
	ei
	halt
	jq	usb_HandleEvents

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
	or	a,a
	sbc	hl,hl
	ld	a,(ti.mpIntStat+1)
	and	a,ti.intUsb shr 8
	ret	z
	ld	hl,ti.mpUsbSts
	ld	a,(hl)
	ld	(_HandleHostInt.hack),a
	ld	l,ti.usbIsr
iterate type, Dev, Host, Otg
	bit	ti.bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	ld	a,ti.intUsb shr 8
	ld	(ti.mpIntAck+1),a
	ex	de,hl	; hl = 0
	or	a,a	; zf = false
	ret

;-------------------------------------------------------------------------------
usb_RefDevice:
	pop	de
	ex	(sp),hl
	push	de
	inc	l
	dec	l
	ret	z
.enter:
	setmsk	device.refcnt,hl
	ld	de,(hl)
	inc	de
	ld	(hl),de
	resmsk	device.refcnt,hl
	ret

;-------------------------------------------------------------------------------
usb_UnrefDevice:
	pop	de
	ex	(sp),hl
	push	de
	inc	l
	dec	l
	ret	z
.enter:
	setmsk	device.refcnt,hl
.refcnt:
	ld	de,(hl)
	ex	de,hl
	add	hl,de
	scf
	sbc	hl,de
	ex	de,hl
	ld	(hl),de
	resmsk	device.refcnt,hl
	call	z,_Free32Align32
	ld	de,ti.mpUsbRange
.returnZero:
	or	a,a
.returnCarry:
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceHub:
	pop	de
	ex	(sp),ydevice
	push	de
	xor	a,a
	sbc	hl,hl
	cp	a,iyl
	ret	z
	ld	de,(ydevice.hub)
.returnDEIfValid:
	bit	0,de
	ret	nz
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
usb_SetDeviceData:
	pop	de,ydevice
	ex	(sp),hl
	push	hl,de
	xor	a,a
	cp	a,iyl
	ret	z
	ld	(ydevice.data),hl
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceData:
	pop	de
	ex	(sp),ydevice
	push	de
	xor	a,a
	sbc	hl,hl
	cp	a,iyl
	ret	z
	ld	hl,(ydevice.data)
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceFlags:
	pop	de
	ex	(sp),ydevice
	push	de
	xor	a,a
	sbc	hl,hl
	cp	a,iyl
	ret	z
	ld	l,(ydevice.find)
	ret

;-------------------------------------------------------------------------------
usb_FindDevice:
	pop	de,hl,iy,bc
	push	bc,hl,hl,de
.enter:
	ld	de,-1
	add	iy,de
	inc	iy
	ex	de,hl
	jq	c,.child
	add	hl,de
	jq	c,.forceChild
	ld	iy,rootHub
	jq	.check
.child:
	bitmsk	IS_ATTACHED,c
	jq	nz,.sibling
.forceChild:
	bit	0,(ydevice.child)
	jq	nz,.sibling
	ld	iy,(ydevice.child)
	jq	.check
.check:
	ld	a,(ydevice.find)
	and	a,c
	jq	nz,.child
	lea	hl,iy
	ret
.hub:
	ld	iy,(ydevice.hub)
	lea	hl,iy
	ld	a,l
	rrca
	jq	c,usb_UnrefDevice.returnZero
	sbc	hl,de
	ret	z
.sibling:
	bit	0,(ydevice.sibling)
	jq	nz,.hub
	ld	iy,(ydevice.sibling)
	jq	.check

;-------------------------------------------------------------------------------
usb_ResetDevice:
	call	_Error.check
	ld	de,(ix+6)
	ld	a,e
	or	a,a
	jq	z,_Error.INVALID_PARAM
	ld	hl,currentRole
	bit	ti.bUsbRole-16,(hl)
	jq	nz,.notSupported
	ld	hl,(rootHub.child)
	sbc	hl,de
.notSupported:
	jq	nz,_Error.NOT_SUPPORTED
	ld	a,12 ; WARNING: This assumes flash wait states port is 3, to get at least 100ms!
	call	ti.DelayTenTimesAms
	ld	hl,ti.mpUsbPortStsCtrl+1
	set	ti.bUsbPortReset-8,(hl)
	ld	a,6 ; WARNING: This assumes flash wait states port is 3, to get at least 50ms!
	call	ti.DelayTenTimesAms
	res	ti.bUsbPortReset-8,(hl)
	ld	a,2 ; WARNING: This assumes flash wait states port is 3, to get at least 10ms!
	jq	ti.DelayTenTimesAms

;-------------------------------------------------------------------------------
usb_DisableDevice:
	call	_Error.check
	ld	de,(ix+6)
	ld	a,e
	or	a,a
	jq	z,_Error.INVALID_PARAM
	ld	hl,(rootHub.child)
	sbc	hl,de
	jq	z,_HandlePortPortEnInt.disable
	jq	_Error.NOT_SUPPORTED

;-------------------------------------------------------------------------------
usb_GetDeviceAddress:
	pop	hl
	ex	(sp),ydevice
	xor	a,a
	cp	a,iyl
	sbc	a,a
	and	a,(ydevice.addr)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceSpeed:
	pop	hl
	ex	(sp),ydevice
	xor	a,a
	cp	a,iyl
	sbc	a,a
	cpl
	or	a,(ydevice.speed)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetConfigurationDescriptorTotalLength:
	call	_Error.check
	call	_Alloc32Align32
	ret	nz
	push	hl,hl
	ld	(hl),a
	setmsk	4,hl
	ld	de,DEFAULT_RETRIES
	push	de,hl
	setmsk	12 xor 4,hl
	push	hl
	ld	c,(ix+9)
iterate value, DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE, GET_DESCRIPTOR_REQUEST, c, CONFIGURATION_DESCRIPTOR, a, a, 4, a
	ld	(hl),value
 if % <> %%
	inc	l
 end if
end iterate
	ld	hl,(ix+6)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
	ld	iy,(ix-6)
	ld	a,(iy+0)
	ld	de,(iy+6)
	lea	hl,iy
	call	_Free32Align32
	ex.s	de,hl
	xor	a,4
	jq	z,usb_GetDescriptor.return
	sbc	hl,hl
	jq	usb_GetDescriptor.return

;-------------------------------------------------------------------------------
usb_GetDescriptor:
	call	_Error.check
	ld	c,GET_DESCRIPTOR_REQUEST
	ld	de,(ix+21)
	call	_Alloc32Align32
	ld	(hl),DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE
.enter:
	jq	nz,_Error.NO_MEMORY
	push	hl,de
	ld	de,DEFAULT_RETRIES
	push	de
	ld	de,(ix+15)
	push	de,hl
	inc	l
	ld	(hl),c
	inc	l
	ld	c,(ix+12)
	ld	(hl),c
	inc	l
	ld	c,(ix+9)
	ld	(hl),c
	inc	l
	ld	(hl),a
	inc	l
	ld	(hl),a
.length:
	inc	l
	ld	de,(ix+18)
	ld	(hl),de
.endpoint:
	ld	hl,(ix+6)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
.return:
	jq	usb_Transfer.return

;-------------------------------------------------------------------------------
usb_SetDescriptor:
	call	_Error.check
	ld	c,SET_DESCRIPTOR_REQUEST
	sbc	hl,hl
	ex	de,hl
	call	_Alloc32Align32
	ld	(hl),d;HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	jq	usb_GetDescriptor.enter

;-------------------------------------------------------------------------------
usb_GetStringDescriptor:
	call	_Error.check
	ld	c,GET_DESCRIPTOR_REQUEST
	ld	de,(ix+21)
	call	_Alloc32Align32
	ld	(hl),DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE
.enter:
	jq	nz,_Error.NO_MEMORY
	push	hl,de
	ld	de,DEFAULT_RETRIES
	push	de
	ld	de,(ix+15)
	push	de,hl
	inc	l
	ld	(hl),c
	inc	l
	ld	c,(ix+9)
	ld	(hl),c
	inc	l
	ld	(hl),STRING_DESCRIPTOR
	inc	l
	ld	de,(ix+12)
	ld	(hl),e
	inc	l
	ld	(hl),d
	jq	usb_GetDescriptor.length

;-------------------------------------------------------------------------------
usb_SetStringDescriptor:
	call	_Error.check
	ld	c,SET_DESCRIPTOR_REQUEST
	sbc	hl,hl
	ex	de,hl
	call	_Alloc32Align32
	ld	(hl),d;HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	jq	usb_GetStringDescriptor.enter

;-------------------------------------------------------------------------------
usb_GetConfiguration:
	call	_Error.check
	sbc	hl,hl
	ex	de,hl
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl,de
	ld	e,DEFAULT_RETRIES
	push	de
	ld	de,(ix+9)
	push	de,hl
	ld	(hl),DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE
	inc	l
	ld	(hl),GET_CONFIGURATION_REQUEST
repeat 3
	inc	l
	ld	(hl),a
end repeat
.length:
	inc	l
	ld	(hl),a
	inc	l
	ld	(hl),1
	inc	l
	ld	(hl),a
	jq	usb_GetDescriptor.endpoint

;-------------------------------------------------------------------------------
usb_SetConfiguration:
	call	_Error.check
	ld	de,(ix+12)
	ld	ydevice,(ix+6)
	push	ix
	ld	xconfigurationDescriptor,(ix+9)
assert xconfigurationDescriptor.bNumInterfaces+1 = xconfigurationDescriptor.bConfigurationValue
	ld	bc,(xconfigurationDescriptor.bNumInterfaces)
	push	bc
	ld	b,c
	call	_ParseInterfaceDescriptors.host
	pop	bc,ix
	jq	nz,_Error.INVALID_PARAM
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	ld	e,d
	push	hl,de
	ld	e,DEFAULT_RETRIES
	push	de,de,hl
	ld	(hl),d;HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	inc	l
	ld	(hl),SET_CONFIGURATION_REQUEST
	inc	l
	ld	(hl),b
repeat 2
	inc	l
	ld	(hl),a
end repeat
.length:
repeat 3
	inc	l
	ld	(hl),a
end repeat
	jq	usb_GetDescriptor.endpoint

;-------------------------------------------------------------------------------
usb_GetInterface:
	call	_Error.check
	sbc	hl,hl
	ex	de,hl
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl,de
	ld	e,DEFAULT_RETRIES
	push	de
	ld	de,(ix+12)
	push	de,hl
	ld	(hl),DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_INTERFACE
	inc	l
	ld	(hl),GET_INTERFACE_REQUEST
repeat 2
	inc	l
	ld	(hl),a
end repeat
	inc	l
	ld	e,(ix+9)
	ld	(hl),e
	jq	usb_GetConfiguration.length

;-------------------------------------------------------------------------------
usb_SetInterface:
	call	_Error.check
	ld	de,(ix+12)
	ld	ydevice,(ix+6)
	push	ix
	ld	xconfigurationDescriptor,(ix+9)
assert xinterfaceDescriptor.bInterfaceNumber+1 = xinterfaceDescriptor.bAlternateSetting
	ld	bc,(xinterfaceDescriptor.bInterfaceNumber)
	push	bc
	ld	a,b
	ld	b,2
	call	_ParseInterfaceDescriptors.dec
	pop	bc,ix
	jq	nz,_Error.INVALID_PARAM
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	ld	e,d
	push	hl,de
	ld	e,DEFAULT_RETRIES
	push	de,de,hl
iterate value, HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_INTERFACE, SET_INTERFACE_REQUEST, b, a, c
	ld	(hl),value
 if % <> %%
	inc	l
 end if
end iterate
	jq	usb_SetConfiguration.length

;-------------------------------------------------------------------------------
usb_SetEndpointHalt:
	ld	b,SET_FEATURE_REQUEST
	jq	usb_ClearEndpointHalt.enter

;-------------------------------------------------------------------------------
usb_ClearEndpointHalt:
	ld	b,CLEAR_FEATURE_REQUEST
.enter:
	call	_Error.check
	ld	yendpoint,(ix+6)
	bitmsk	BULK_TRANSFER and INTERRUPT_TRANSFER,(yendpoint.transferInfo)
	jq	z,_Error.INVALID_PARAM
	call	usb_GetEndpointAddress.enter
	ld	hl,currentRole
	bit	ti.bUsbRole-16,(hl)
	jq	nz,.device
	ld	hl,(yendpoint.first)
	bitmsk	transfer.next.dummy,(hl+transfer.next)
	jq	z,_Error.NOT_SUPPORTED
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	inc	de;0
	push	hl,de
	ld	e,DEFAULT_RETRIES
	push	de,hl,hl
assert ~ENDPOINT_HALT_FEATURE
iterate value, HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_ENDPOINT, b, d, d, a, d, d, d
	ld	(hl),value
 if % <> %%
	inc	l
 end if
end iterate
	xor	a,a
	ld	hl,(yendpoint.device+1)
	call	usb_GetDeviceEndpoint.masked
	push	hl
	call	usb_ControlTransfer
	ld	yendpoint,(ix+6)
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
	resmsk	yendpoint.overlay.remaining.dt
.return:
	jq	usb_Transfer.return
.device:
	or	a,a
	jq	z,_Error.INVALID_PARAM
	call	_HandleCxSetupInt.lookupEndpointRegister
	ld	a,(hl)
	or	a,(ti.bmUsbEpReset or ti.bmUsbEpStall) shr 8
	djnz	.set
	and	a,not ti.bmUsbEpStall shr 8
	ld	(hl),a
	ret
.set:
	and	a,not ti.bmUsbEpReset shr 8
	ld	(hl),a
	ld	bc,USB_TRANSFER_CANCELLED or USB_TRANSFER_STALLED
	lea	xendpoint,yendpoint
	call	_FlushEndpoint
	ret	c
.pop2return:
	pop	bc,ix
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceEndpoint:
	pop	bc,hl,de
	push	de,hl,bc
.check:
	inc	l
	dec	l
	ret	z
	ld	a,e
.enter:
	and	a,endpoint.transferInfo.dir or endpoint.info.ep
.masked:
	ld	hl,(hl+device.endpoints)
	bit	0,hl
	jq	nz,.returnCarry
	rlca
	or	a,l
	ld	l,a
	ld	h,(hl)
	ld	l,endpoint
	ld	a,h
	inc	a
	ret	nz
.returnCarry:
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointDevice:
	pop	de
	ex	(sp),yendpoint
	push	de
	xor	a,a
	sbc	hl,hl
	cp	a,iyl
	ret	z
	ld	de,(yendpoint.device)
	jq	usb_GetDeviceHub.returnDEIfValid

;-------------------------------------------------------------------------------
usb_SetEndpointData:
	pop	de,yendpoint
	ex	(sp),hl
	push	hl,de
	xor	a,a
	cp	a,iyl
	ret	z
	ld	(yendpoint.data),hl
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointData:
	pop	de
	ex	(sp),yendpoint
	push	de
	xor	a,a
	sbc	hl,hl
	cp	a,iyl
	ret	z
	ld	hl,(yendpoint.data)
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointAddress:
	pop	hl
	ex	(sp),yendpoint
	push	hl
.enter:
	ld	de,-1
	add	yendpoint,de
	ld	a,e
	ret	nc
	ld	a,(yendpoint.transferInfo+1)
	rlca
	ld	a,(yendpoint.info+1)
	rla
	rrca
	and	a,endpoint.transferInfo.dir or endpoint.info.ep
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointTransferType:
	pop	hl
	ex	(sp),yendpoint
	ld	a,(yendpoint.transferInfo)
	and	a,endpoint.transferInfo.type
	ld	c,a
	xor	a,a
	cp	a,iyl
	sbc	a,a
	cpl
	or	a,c
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointInterval:
	pop	hl
	ex	(sp),yendpoint
	xor	a,a
	cp	a,iyl
	sbc	a,a
	and	a,(yendpoint.interval)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointMaxPacketSize:
	pop	de
	ex	(sp),yendpoint
	push	de
	xor	a,a
	cp	a,iyl
	ret	z
	ld	de,(yendpoint.maxPktLen)
	ld	a,d
	and	a,111b
	ld	d,a
	ex.s	de,hl
	ret

;-------------------------------------------------------------------------------
usb_SetEndpointFlags:
	pop	de,yendpoint
	ex	(sp),hl
	push	hl,de
	xor	a,a
	cp	a,iyl
	ret	z
	ld	(yendpoint.flags),l
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointFlags:
	pop	hl
	ex	(sp),yendpoint
	xor	a,a
	cp	a,iyl
	sbc	a,a
	and	a,(yendpoint.flags)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetRole:
	ld	hl,(currentRole)
	ret

;-------------------------------------------------------------------------------
usb_GetFrameNumber:
	ld	hl,ti.mpUsbOtgCsr+2
	bit	ti.bUsbRole-16,(hl)
	ld	l,ti.usbFrameIdx
	jq	z,.load
	ld	l,ti.usbSofFrNum-$100
	inc	h
.load:
	ld	de,(hl)
	ld	a,(hl)
	cp	a,e
	jq	c,.load
	ld	e,a
	dec	h
	ex	de,hl
	ret	nz
repeat bsr 8
	add	hl,hl
end repeat
	ret

;-------------------------------------------------------------------------------
usb_ControlTransfer:
	ld	hl,usb_ScheduleControlTransfer.enter
	jq	usb_Transfer.enter

;-------------------------------------------------------------------------------
usb_Transfer:
	ld	hl,usb_ScheduleTransfer.enter
.enter:
	ld	(.dispatch),hl
	call	_Error.check
	ld	hl,(ix+15)
	push	hl
	ld	hl,(ix+18)
	push	hl
	sbc	hl,hl
	inc	l
	push	hl
	ld	hl,.callback
	ld	(ix+15),hl
	ld	(ix+18),ix
	call	0
label .dispatch at $-long
.wait:
	call	usb_WaitForEvents
	add	hl,de
	or	a,a
	sbc	hl,de
	jq	nz,.return
	ld	l,(ix-12)
	dec	l
	jq	z,.wait
	inc	l
.return:
	ld	sp,ix
	pop	ix
	ret

.callback:
	ld	hl,12
	add	hl,sp
	ld	iy,(hl)
repeat long
	dec	hl
end repeat
	ld	bc,(hl)
repeat long
	dec	hl
end repeat
	ld	a,(hl)
	sbc	hl,hl
	or	a,a;USB_TRANSFER_COMPLETED
	jq	z,.complete
	ld	e,a
iterate error, NO_DEVICE, OVERFLOW
	ld	a,USB_ERROR_#error
	bitmsk	USB_TRANSFER_#error,e
	jq	nz,.complete
end iterate
	ld	a,e
	and	a,USB_TRANSFER_CANCELLED or USB_TRANSFER_STALLED
	ld	a,USB_ERROR_FAILED
	jq	nz,.complete
	ld	de,(iy-6)
	inc	l
	add	hl,de
	inc	l
	ret	c
	sbc	hl,hl
	dec	hl
	adc	hl,de
	ld	(iy-6),hl
	ld	hl,1
	ret	nz
assert USB_ERROR_TIMEOUT = USB_ERROR_FAILED-1
	dec	a;USB_ERROR_TIMEOUT
	dec	hl
	or	a,a
.complete:
	ld	(iy-12),a
	ld	de,(iy-9)
	adc	hl,de
	ret	z
	ld	(hl),bc
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_ScheduleControlTransfer.deviceControl:
	cp	a,a
usb_ScheduleControlTransfer.notControl:
	ld	ysetup,(ix+9)
	ld	bc,(ysetup.wLength)
	inc	bc
	dec.s	bc
	ld	de,(ix+12)
	ld	yendpoint,(ix+6)
	jq	nz,usb_ScheduleTransfer.notControl
usb_ScheduleTransfer.deviceControl:
	ld	hl,(setupPacket.wLength)
	inc	hl
	dec.s	hl
	sbc	hl,bc
	jq	nc,usb_ScheduleControlTransfer.min
	add	hl,bc
	push	hl
	pop	bc
usb_ScheduleControlTransfer.min:
	ld	a,c
	or	a,b
	jq	z,usb_ScheduleControlTransfer.zlp
	ld	a,(setupPacket.bmRequestType)
	rlca
	push	af
	ld	a,transfer.type.ioc shr 1
	rla
	call	_QueueTransfer
	pop	af
	ret	nc
	xor	a,a
	call	_ExecuteDma
	ret	nc
	jq	usb_Transfer.return
usb_ScheduleControlTransfer.zlp:
	ld	hl,ti.mpUsbCxFifo
	ld	(hl),ti.bmCxFifoFin
	ld	de,(ix+18)
	ld	hl,usb_Transfer.return
	push	yendpoint,bc,bc,de,hl
	ld	hl,(ix+15)
_DispatchEvent.dispatch:
	jp	(hl)
usb_ScheduleControlTransfer:
	call	_Error.check
.enter:
	call	.check
	ld	yendpoint,(ix+6)
	ld	a,(yendpoint.transferInfo)
	and	a,endpoint.transferInfo.type
assert ~CONTROL_TRANSFER
	jq	nz,.notControl
	ld	hl,currentRole
	bit	ti.bUsbRole-16,(hl)
	jq	nz,.deviceControl
.control:
	ld	a,00001110b
	ld	bc,8
	ld	de,(ix+9)
	call	.queueStage
	ld	ysetup,(ix+9)
	ld	a,(ysetup.bmRequestType)
	and	a,DEVICE_TO_HOST
	ld	bc,(ysetup.wLength)
	inc.s	bc
	cpi.s
	ld	de,(ix+12)
	rlca
	push	af
	call	pe,_QueueTransfer
	pop	af
	xor	a,10001101b
	ld	bc,transfer.remaining.dt
	jq	.queueStage
.queueStage:
	call	_CreateDummyTransfer
assert (endpoint-1) and 1
	dec	yendpoint
	jq	z,_FillTransfer
	jq	_Error.NO_MEMORY
.check:
	ld	hl,(ix+9)
	add	hl,de
	or	a,a
	sbc	hl,de
.invalidParam:
	jq	z,_Error.INVALID_PARAM
usb_ScheduleTransfer.check:
	ld	hl,(ix+6)
	add	hl,de
	or	a,a
	sbc	hl,de
	jq	z,usb_ScheduleControlTransfer.invalidParam
	ld	l,endpoint.device
	ld	ydevice,(hl)
	bitmsk	IS_ENABLED,(ydevice.find)
	jq	z,_Error.NO_DEVICE
	ld	hl,(ix+15)
	add	hl,de
	or	a,a
	sbc	hl,de
	ret	nz
	ld	hl,_DefaultHandler
	ld	(ix+15),hl
	ret

;-------------------------------------------------------------------------------
usb_ScheduleTransfer.control:
	bit	ti.bUsbRole-16,l
	jq	nz,usb_ScheduleTransfer.deviceControl
	ld	ysetup,(ix+9)
	lea	de,ysetup+sizeof ysetup
	ld	(ix+12),de
	jq	usb_ScheduleControlTransfer.control
usb_ScheduleTransfer:
	call	_Error.check
.enter:
	call	.check
	ld	bc,(ix+12)
	ld	de,(ix+9)
	ld	yendpoint,(ix+6)
	ld	hl,(currentRole)
	ld	a,(yendpoint.transferInfo)
	ld	h,a
	and	a,endpoint.transferInfo.type
assert ~CONTROL_TRANSFER
	jq	z,.control
.notControl:
	rlc	h
	bit	ti.bUsbRole-16,l
	jq	nz,.device
assert ~ISOCHRONOUS_TRANSFER-1
	dec	a
	jq	nz,.queue
	jq	_Error.NOT_SUPPORTED
.device:
	jq	nc,.queue
	ld	a,(yendpoint.overlay.fifo)
	cpl
	ld	hl,ti.mpUsbFifoTxImr
	and	a,(hl)
	ld	(hl),a
assert ti.mpUsbFifoTxImr shr 8 and $FF = 1
.queue:
	ld	a,h
	and	a,1
	or	a,transfer.type.ioc
	jq	_QueueTransfer

; Input:
;  a = ioc shl 7 or dir
;  bc = length
;  de = buffer
;  (ix+6) = endpoint
;  (ix+15) = handler
;  (ix+18) = data
_QueueTransfer:
	call	_CreateDummyTransfer
	jq	nz,_Error.NO_MEMORY
	ld	(.dummy),hl
	or	a,transfer.type.cerr
	push	af
	sbc	hl,hl
	sbc	hl,bc
	jq	z,.zlp
.next:
	push	de
	ld	a,d
	and	a,$F
	ld	d,a
	ld	hl,$5000
	sbc.s	hl,de
	sbc	hl,bc
	jq	c,.notEnd
	sbc	hl,hl
	bitmsk	yendpoint.flags.autoTerm
.notEnd:
	add	hl,bc
	jq	z,.last
	ld	de,(yendpoint.maxPktLen)
	ex.s	de,hl
	bitmsk	yendpoint.internalFlags.po2Mps
	jq	nz,.modPo2
	ld	a,h
	and	a,7
	ld	h,a
	or	a,l
	jq	z,_Error.INVALID_PARAM
	push	bc,de
	ld	b,-1
.modShift:
	inc	b
	add.s	hl,hl
	jq	nc,.modShift
	ex	de,hl
.modLoop:
	rr	d
	rr	e
	sbc	hl,de
	jq	nc,.modSkip
	add	hl,de
	or	a,a
.modSkip:
	djnz	.modLoop
	pop	de,bc
	jq	.modDone
.modPo2:
	ld	a,l
	add	a,a
	jq	nz,.modPo2Byte
	ld	a,h
	adc	a,a
	and	a,$F
	dec	a
	and	a,d
	ld	h,a
	ld	l,e
	jq	.modDone
.modPo2Byte:
	dec	a
	and	a,e
	ld	l,a
	ld	h,0
.modDone:
	ex	de,hl
	sbc	hl,bc
	add	hl,bc
	jq	nz,.notLast
	ld	a,d
	or	a,e
	jq	nz,.last
.notLast:
	or	a,a
	sbc	hl,de
	pop	de,af
	push	af,bc,de,hl
	call	_CreateDummyTransfer.enter
	jq	nz,_Error.NO_MEMORY
	and	a,00001101b
	pop	bc
	push	bc
	call	.queue
	pop	bc,hl,de
	add	hl,bc
	ex	de,hl
	sbc	hl,bc
	push	hl
	pop	bc
	jq	nz,.next
virtual
	jr	nz,$$
 assert $ = .zlp
 load .jr_nz: byte from $$
end virtual
	db	.jr_nz
.last:
	pop	de
.zlp:
	pop	af
	and	a,10001101b
	push	hl
	pop	bc
virtual at .queue
	ld	iy,0
 assert $ = .fill
 load .iyPrefix: byte from $$
end virtual
	ld	iyl,.iyPrefix
label .queue at $-byte
	ld	hl,0
label .dummy at $-long
.fill:
	set	7,b
	jq	_FillTransfer

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
	ex	de,hl
	push	hl,iy
	ld	yendpoint,(ix+6)
	ld	hl+transfer,(yendpoint.last)
	ld	(hl+transfer.next),de
	ld	(yendpoint.last),de
	setmsk	transfer.altNext,hl
	pop	de
	ld	(hl),de
repeat transfer.type-transfer.altNext
	inc	l
end repeat
	ld	(hl),a
repeat transfer.remaining-transfer.type
	inc	l
end repeat
	ld	(hl),c
	inc	l;transfer.remaining+1
	ld	(hl),b
	pop	de
	inc	l;transfer.buffers
	ld	(hl),de
	dec	sp
	push	de
	inc	sp
	pop	de
repeat transfer.length-transfer.buffers
	inc	l
end repeat
	ld	(hl),c
	inc	l;transfer.length+1
	ld	(hl),b
	call	.packHalf
	ld	bc,(ix+15)
	call	.pack
	ld	bc,(ix+18)
	call	.pack
	lea	bc,yendpoint
	call	.pack
	ld	(hl),d
	ld	a,l
	sub	a,transfer.padding-transfer.status
	ld	l,a
	ld	(hl),transfer.status.active
	ld	hl,ti.mpUsbCmd
	bit	bsf yendpoint.transferInfo.type,(yendpoint.transferInfo)
assert INTERRUPT_TRANSFER and 1
	jq	nz,.periodic
	bit	ti.bUsbAsyncSchedEn,(hl)
	ret	nz
	ld	l,ti.usbSts+1
	ld	b,(48000000*20/1000-.async.sync.cycles.pre+.async.sync.cycles-1)/.async.sync.cycles
.async.sync.cycles.pre := 16+12+5+8+8
.async.sync.wait:
	bit	ti.bUsbAsyncSchedSts-8,(hl)	;12
	jq	nz,.async.sync			;+8
	ld	l,ti.usbCmd
	set	ti.bUsbAsyncSchedEn,(hl)
	ret
.async.sync:
	xor	a,a				;+4
.async.sync.loop:
	dec	a				;+(4
	jq	nz,.async.sync.loop		;  +13)*256-5
	djnz	.async.sync.wait		;+13
	jq	_Error.TIMEOUT
.async.sync.cycles := 12+8+4+(4+13)*256-5+13
.periodic:
	bit	ti.bUsbPeriodicSchedEn,(hl)
	ret	nz
	ld	l,ti.usbSts+1
	ld	b,(48000000*20/1000-.periodic.sync.cycles.pre+.periodic.sync.cycles-1)/.periodic.sync.cycles
.periodic.sync.cycles.pre := 16+12+5+8+8
.periodic.sync.wait:
	bit	ti.bUsbPeriodicSchedSts-8,(hl)	;12
	jq	nz,.periodic.sync		;+8
	ld	l,ti.usbCmd
	set	ti.bUsbPeriodicSchedEn,(hl)
	ret
.periodic.sync:
	xor	a,a				;+4
.periodic.sync.loop:
	dec	a				;+(4
	jq	nz,.periodic.sync.loop		;  +13)*256-5
	djnz	.periodic.sync.wait		;+13
	jq	_Error.TIMEOUT
.periodic.sync.cycles := 12+8+4+(4+13)*256-5+13
.pack:
	ld	a,d
	xor	a,c
	and	a,$F
	xor	a,c
	ld	(hl),bc
	ld	(hl),a
	inc	l
	inc	l
.packHalf:
	inc	l
	ld	a,e
	or	a,$F
	ld	e,a
	inc	de
	ld	a,c
	xor	a,e
	and	a,$F
	xor	a,e
	ld	(hl),a
	inc	l
	ret

;-------------------------------------------------------------------------------
element error
label _Error at error

iterate error, SYSTEM, INVALID_PARAM, SCHEDULE_FULL, NO_DEVICE, NO_MEMORY, NOT_SUPPORTED, TIMEOUT, OVERFLOW, FAILED

.error:
	ld	a,USB_ERROR_#error
	jq	.return

end iterate

.check:
	pop	de
	call	ti._frameset0
	ld	a,(ti.mpIntMask)
	and	a,ti.intTmr3
	jq	nz,.SYSTEM
	ld	a,(ti.mpUsbSts)
	and	a,ti.bmUsbIntHostSysErr
	jq	nz,.SYSTEM
	ld	a,(ti.usbInited)
	dec	a
	jq	nz,.SYSTEM
	ex	de,hl
	call	_DispatchEvent.dispatch
	jq	.success

.success:
	xor	a,a
	jq	.return

.return:
	or	a,a
	sbc	hl,hl
	ld	l,a
	jq	usb_Transfer.return

; Input:
;  a = fill
; Output:
;  bc = 0
;  hl = ti.flags+$1B
_Init:
	ld	de,ti.usbInited
	ld	(de),a
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
	ld	hl,ti.usbInited
	dec	de
	ld	bc,ti.usbInited-ti.usbArea
	lddr
	ld	hl,ti.flags+$1B
	ret

;-------------------------------------------------------------------------------
; Input:
;  hl = ti.mpUsbRange xor (? and $FF)
; Output:
;  a = 0
;  b = ?
;  d = ?
;  hl = dummyHead.next
_DisableSchedulesAndResetHostController:
	; stop schedules
	ld	l,ti.usbCmd
.enter:
	ld	a,(hl)
	and	a,ti.bmUsbAsyncSchedEn or ti.bmUsbPeriodicSchedEn
assert ti.bUsbAsyncSchedSts-8-ti.bUsbAsyncSchedEn = ti.bUsbPeriodicSchedSts-8-ti.bUsbPeriodicSchedEn
repeat ti.bUsbAsyncSchedSts-8-ti.bUsbAsyncSchedEn
	rlca
end repeat
	ld	d,a
	ld	l,ti.usbSts+1
	ld	b,(48000000*20/1000-.sync.cycles.pre+.sync.cycles-1)/.sync.cycles
.sync.cycles.pre := 8+8+8+4*2+4+8+8
.sync.wait:
	ld	a,(hl)								;8
	and	a,(ti.bmUsbAsyncSchedSts or ti.bmUsbPeriodicSchedSts) shr 8	;+8
	sub	a,d								;+4
	jq	nz,.sync							;+13
.sync.fail:
	jq	_ResetHostControllerFromUnknown

; Input:
;  a = 0
;  hl = ti.mpUsbRange xor (? and $FF)
; Output:
;  a = 0
;  b = ?
;  hl = dummyHead.next
_ResetHostControllerFromUnknown:
	; halt host controller (EHCI spec section 2.3)
	ld	l,ti.usbIntEn
	ld	(hl),a;0
	ld	l,ti.usbCmd
	ld	(hl),a;0
	ld	l,ti.usbSts+1
	ld	b,(48000000*2/1000-.halt.cycles.pre+.halt.cycles-1)/.halt.cycles
.halt.cycles.pre := 16
.halt.wait:
	bit	ti.bUsbHcHalted-8,(hl)	;12
	jq	z,.halt			;+13
.halt.fail:

	; reset host controller (EHCI spec section 2.3)
	ld	l,ti.usbCmd
	ld	(hl),ti.bmUsbHcReset
	ld	b,(48000000*250/1000-.reset.cycles.pre+.reset.cycles-1)/.reset.cycles
.reset.cycles.pre := 8
.reset.wait:
	bit	ti.bUsbHcReset,(hl)	;12
	jq	nz,.reset		;+13
.reset.fail:

	; initialize host controller from halt (EHCI spec section 4.1)
	ld	(hl),0
label .frameListSize at $-byte
	ld	l,ti.usbMisc
	ld	(hl),0
label .misc at $-byte
	ld	l,ti.usbIntEn
	ld	(hl),ti.bmUsbInt or ti.bmUsbIntErr or ti.bmUsbIntPortChgDetect or ti.bmUsbIntFrameListOver or ti.bmUsbIntHostSysErr or ti.bmUsbIntAsyncAdv
	ld	hl,periodicList
	ld	(ti.mpUsbPeriodicListBase),hl
	ld	hl,dummyHead.next
	ld	(ti.mpUsbAsyncListAddr),hl
	ret ; defer actual start until plug

namespace _DisableSchedulesAndResetHostController
?sync:
	xor	a,a							;+4
.loop:
	dec	a							;+(4
	jq	nz,.loop						;  +13)*256-5
	djnz	.wait							;+13
.cycles := 8+8+4+13+4+(4+13)*256-5+13
	jq	.fail
end namespace

.halt:
	dec	a			;+(4
	jq	nz,.halt		;  +13)256-5
	djnz	.halt.wait		;+13
.halt.cycles := 12+13+(4+13)*256-5+13
	jq	.halt.fail

.reset:
	ld	d,a			;+(4
.reset.loop:
	dec	d			;  +(4
	jq	nz,.reset.loop		;    +13)256-5
	dec	a			;  +4
	jq	nz,.reset		;  +13)256-5
	djnz	.reset.wait		;+13
.reset.cycles := 12+13+(4+(4+13)*256-5+4+13)*256-5+13
	jq	.reset.fail

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
	ld	l,ti.usbOtgCsr
	bitmsk	ROLE_DEVICE,a
	jq	nz,.unpower
.power:
	call	$21B70
	res	ti.bUsbABusDrop,(hl)
	set	ti.bUsbABusReq,(hl)
	ld	l,ti.usbSts+1
	bit	ti.bUsbHcHalted-8,(hl)
	jq	z,.notHalted
	ld	l,ti.usbCmd
	set	ti.bUsbRunStop,(hl)
.notHalted:
	or	a,a;ROLE_B
	ret	z
	ld	l,ti.usbOtgCsr
	res	ti.bUsbBHnp,(hl)
	res	ti.bUsbBVbusDisc,(hl)
	ret
.unpower:
	res	ti.bUsbASrpEn,(hl)
	push	hl,de
	call	_DisableSchedulesAndResetHostController
	ld	de,$D7FFFF ; disable doorbell
	call	_HandleAsyncAdvInt.cleanup.de
	call	_HandleAsyncAdvInt.cleanup.hl
	pop	de,hl
	set	ti.bUsbABusDrop,(hl)
	res	ti.bUsbABusReq,(hl)
	jq	$21C68

;-------------------------------------------------------------------------------
_DefaultHandler:
	ld	hl,USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
; Input:
;  (sp+12) = block
; Output:
;  hl = ?
_FreeTransferData:
	ld	hl,3+12
	add	hl,sp
	ld	hl,(hl)
	jq	_Free32Align32

iterate <size,align>, 32,32, 64,256

; Frees an <align> byte aligned <size> byte block.
; Input:
;  hl = allocated memory to be freed.
_Free#size#Align#align:
.uninit:
	push	de
if DEBUG
	ld	de,(alloc#size#Align#align)
	dec	de
	ld	(alloc#size#Align#align),de
end if
	ld	de,(freeList#size#Align#align)
	ld	(hl),de
	ld	(freeList#size#Align#align),hl
	pop	de
	ret

; Allocates an <align> byte aligned <size> byte block.
; Output:
;  zf = enough memory
;  hl = allocated memory
_Alloc#size#Align#align:
	ld	hl,(freeList#size#Align#align)
	bit	0,hl
	ret	nz
	push	hl
	ld	hl,(hl)
	ld	(freeList#size#Align#align),hl
if DEBUG
	ld	hl,(alloc#size#Align#align)
	inc	hl
	ld	(alloc#size#Align#align),hl
end if
	pop	hl
	ret

end iterate

; Input:
;  (ix+6) = endpoint
; Output:
;  zf = enough memory
;  hl = transfer
;  iy = (ix+6)
_CreateDummyTransfer:
	ld	yendpoint,(ix+6)
.enter:
	call	_Alloc32Align32
	ret	nz
	setmsk	transfer.status,hl
	ld	(hl),transfer.status.halted
	resmsk	transfer.status,hl
	ld	(hl),1
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
	ld	hl,_HandleAsyncAdvInt.scheduleCleanup.hl
	push	hl
	ld	b,USB_DEVICE_DISABLED_EVENT
.recurse:
	ld	a,(xdevice.find+1)
	ld	c,a
	and	a,not (IS_ENABLED or IS_DISABLED)
assert IS_DISABLED = 1
	inc	a;IS_DISABLED
	ld	(xdevice.find+1),a
	jq	.start
.recursed:
	pop	xdevice,bc
	ret	nz
.start:
	push	xdevice,bc
	ld	de,(xdevice.endpoints+1)
	ld	xdevice,(xdevice.child+1)
	ld	hl,.recursed
	dec	ixl
	jq	nz,_DeviceDisconnected.recurse
	ld	xendpoint,dummyHead
	ld	bc,USB_TRANSFER_CANCELLED or USB_TRANSFER_NO_DEVICE
.loop:
	ld	a,(de)
	ld	ixh,a
	inc	a
	jq	z,.next
	ld	a,(xendpoint.transferInfo)
	and	a,endpoint.transferInfo.type
	ld	a,-1
	ld	(de),a
	jq	nz,.notControl
	inc	e
	ld	(de),a
.notControl:
	push	de
	call	_FlushEndpoint
	pop	de
	jq	nc,usb_ClearEndpointHalt.pop2return
	lea	hl,xendpoint.next
	ld	h,(xendpoint.prev)
	ld	yendpoint,(xendpoint.next)
	ld	(hl+endpoint.next),yendpoint
	ld	(yendpoint.prev),h
	ld	hl,cleanupListPending
	ld	a,(hl)
	ld	(xendpoint.prev),a
	ld	a,ixh
	ld	(hl),a
.next:
	inc	e
	ld	a,e
	and	a,31
	jq	nz,.loop
	pop	af,xdevice
	ld	hl,ti.mpUsbRange
	lea	de,xdevice+1
assert IS_DISABLED = 1 shl 0
	jq	nc,.event
	cp	a,USB_DEVICE_DISABLED_EVENT
	ret	z
.event:
	jq	_DispatchEvent

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
_DeviceDisconnected:
	ld	hl,_HandleAsyncAdvInt.scheduleCleanup.de
.recurse:
	push	hl
	ld	b,USB_DEVICE_DISCONNECTED_EVENT
	call	_DeviceDisabled.recurse
	ret	nz
	ld	bc,(xdevice.sibling+1)
	ld	hl,(xdevice.back+1)
	ld	(hl),bc
	ld	hl,(xdevice.endpoints+1)
	ld	(xdevice.endpoints+1),xdevice
	call	_Free32Align32
	lea	hl,xdevice.refcnt+1
	jq	usb_UnrefDevice.refcnt

; Input:
;  b = interval
;  hl + de = max full-speed stuffed bit times needed
;  iy = endpoint
; Output:
;  cf = schedule full
;  af = ?
;  bc = ?
;  de = endpoint | ?
;  hl = ?
;  iy = ?
_ScheduleEndpoint:
label .enabled
virtual
	scf
	ret
 load .disable: $-$$ from $$
end virtual
	add	hl,de
repeat 15-bsr FS_SBP_PER_FRAME
	add	hl,hl
end repeat
load .enable: long from .enabled
	ld	(.maxHsSbp),hl
	inc	l
	ld	(yendpoint.maxHsSbp+0),l
	ld	(yendpoint.maxHsSbp+1),h
	ld	a,1
.log:
	rrca
	rl	b
	jq	nc,.log
	ld	(yendpoint.interval),a
	sbc	hl,hl
	push	yendpoint,hl,hl
	ld	b,a
	cpl
	ld	(.notInterval),a
	inc	a
	ld	l,a
	add	hl,hl
	add	hl,hl
	ld	(.stride),hl
	ld	iy,periodicList
.check:
repeat (1 shl 7*dword) shr 8
	inc	iyh
end repeat
	lea	iy,iy-dword
	push	bc
	ld	de,periodicList shr 8 and $FF-1
	ld	a,e
.sum:
	ld	hl,(iy+endpoint.maxHsSbp)
	ld	bc,0
label .maxHsSbp at $-long
	add.s	hl,bc
	jq	nc,.valid
	ld	de,1 shl 23
.valid:
	add	hl,de
	ex	de,hl
	ld	bc,0
label .stride at $-long
	add	iy,bc
	cp	a,iyh
	jq	c,.sum
	pop	bc,hl
	sbc	hl,de
	jq	c,.min
	pop	hl
	push	iy
	sbc	hl,hl
.min:
	add	hl,de
	push	hl
	djnz	.check
	pop	hl,iy,de
	add	hl,hl
	ret	c
	ld	bc,4-1
label .frameListSize at $-long
	add	iy,bc
.link:
	push	iy,de
	inc	iy
	ld	bc,(iy-4+endpoint.maxHsSbp)
	ld	hl,(.maxHsSbp)
	add	hl,bc
	ld	(iy-4+endpoint.maxHsSbp),hl
virtual
	ld	hl,0
 load .ld_hl: byte from $$
end virtual
	db	.ld_hl
.skip:
	ld	iyh,b
	ld	iyl,c
	ld	bc,(iy-4)
	bit	2,c
	jq	nz,.skip
	ld	e,endpoint.interval
	db	.ld_hl
.find:
	ld	iyh,d
	ld	iyl,endpoint.base+4
	ld	d,(iy-4+endpoint.next+1)
	bit	0,(iy-4+endpoint.next+0)
	jq	nz,.found
	ld	a,(de)
	add	a,0
label .notInterval at $-byte
	jq	c,.find
.found:
	pop	hl,bc
	ld	e,l;endpoint
	ld	a,d
	cp	a,h
	jq	z,.linked
assert endpoint-2 = endpoint.next
	dec	l
	ld	(hl),d
	dec	l
	ld	a,(iy-4+endpoint.next+0)
	ld	(hl),a
	ld	(iy-4+endpoint.next+1),h
	ld	(iy-4+endpoint.next+0),e
.linked:
	ld	d,h
	ld	iy,(.stride)
	add	iy,bc
	ld	a,periodicList shr 8 and $FF-1
	cp	a,iyh
	jq	c,.link
	ret

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
	resmsk	IS_DISABLED,(ydevice.find)
	setmsk	IS_ENABLED,(ydevice.find)
_CreateDefaultControlEndpoint:
	ld	de,_DefaultControlEndpointDescriptor
	jq	_CreateEndpoint

; Input:
;  de = endpoint descriptor
;  iy = device
; Output:
;  af = ?
;  zf = success
;  bc = ?
;  de = ?
;  hl = ? | error
;  iy = endpoint | ?
_CreateEndpoint:
	call	_Alloc64Align256
	jq	nz,.nomem
repeat endpointDescriptor.bEndpointAddress-endpointDescriptor
	inc	de
end repeat
	ld	a,(de)
	and	a,endpoint.transferInfo.dir or endpoint.info.ep
	ld	c,a
	and	a,endpoint.info.ep
	ld	b,a
assert endpointDescriptor.bEndpointAddress+1 = endpointDescriptor.bmAttributes
	inc	de
	ld	a,(de)
	and	a,ti.bmUsbFifoType
	push	bc,af
	rlc	c
	rla
	rrca
	ld	l,endpoint.transferInfo
	ld	(hl),a
	ld	a,(ydevice.addr)
	ld	l,endpoint.addr
	ld	(hl),a
	ld	a,b
	or	a,(ydevice.speed)
assert endpoint.addr+1 = endpoint.info
	inc	l
	ld	(hl),a
	ld	a,c
	ld	bc,(ydevice.endpoints)
	or	a,c
	ld	c,a
	ld	a,h
	ld	(bc),a
	pop	af
	ld	a,endpoint.maxPktLen.rl shr 8
	jq	nz,.notControl
	ld	a,c
	xor	a,1
	ld	c,a
	ld	a,h
	ld	(bc),a
	setmsk	endpoint.info.dtc,(hl)
	ld	a,(endpoint.maxPktLen.rl or endpoint.maxPktLen.c) shr 8
.notControl:
	ld	c,a
assert endpointDescriptor.bmAttributes+1 = endpointDescriptor.wMaxPacketSize
	inc	de
	ld	a,(de)
assert endpoint.info+1 = endpoint.maxPktLen
	inc	l
	ld	(hl),a
	inc	de
	ld	a,(de)
	and	a,endpoint.maxPktLen.msk shr 8
	or	a,c
	inc	l
.l = endpoint.maxPktLen+1
	ld	(hl),a
	ld	bc,1 shl 22 or 1 shl 15 or 0 shl 8 or 0
assert endpoint.cmask+1 = endpoint.hubInfo
iterate <field,value>, smask,c, cmask,bc, \
                       overlay.altNext,1, overlay.status,c, \
                       flags,c, internalFlags,c, interval,c, device,ydevice
 if .l+1 = endpoint.field
	inc	l
 else
	ld	l,endpoint.field
 end if
 .l = endpoint.field
	ld	(hl),value
end iterate
	ld	l,endpoint
	push	hl
	pop	yendpoint
	sbc	hl,hl
	ld	(yendpoint.data),hl
	call	_CreateDummyTransfer.enter
	jq	z,.mem
	lea	hl,yendpoint.base
	call	_Free64Align256
	pop	bc
.nomem:
	ld	hl,USB_ERROR_NO_MEMORY
	ret
.mem:
	ld	(yendpoint.overlay.next),hl
	ld	(yendpoint.first),hl
	ld	(yendpoint.last),hl
	ex	de,hl
	ld	d,(hl)
	dec	hl
	ld	e,(hl)
	ld	a,e
	or	a,d
	dec	de
	jq	z,.notPo2Mps
	ld	a,e
	and	a,(hl)
	ld	c,a
	inc	hl
	ld	a,d
	and	a,(hl)
	or	a,c
	jq	nz,.notPo2Mps
assert endpoint.internalFlags.po2Mps = 1 shl 0
	inc	(yendpoint.internalFlags)
.notPo2Mps:
	pop	bc
	ld	a,(currentRole)
	and	a,ti.bmUsbRole shr 16
	jq	nz,.async
	ld	a,(yendpoint.transferInfo)
assert ~(CONTROL_TRANSFER or BULK_TRANSFER) and 1
	rrca
	jq	nc,.async
assert endpointDescriptor.wMaxPacketSize+2 = endpointDescriptor.bInterval
	inc	hl
	ld	b,(hl)
	inc	b
	djnz	.validInterval
	jq	.invalidParam
.validInterval:
	ex	de,hl
	inc.s	hl
repeat bsr 4
	add	hl,hl
end repeat
	rrca
assert INTERRUPT_TRANSFER and 1
	jq	c,.intr
	djnz	.isoc.validInterval
.invalidParam:
	ld	hl,USB_ERROR_INVALID_PARAM
	ret
.isoc.validInterval:
	inc	b
; full-speed out isoc: 4*bytes + 39 fs sbp
; full-speed  in isoc: 4*bytes + 44 fs sbp
	bitmsk	yendpoint.transferInfo.dir
	ld	de,39
	jq	z,.isoc.schedule
	ld	e,44
.isoc.schedule:
;	call	.schedule
assert USB_ERROR_INVALID_PARAM
	ld	hl,USB_ERROR_INVALID_PARAM-1
	inc	l
	ret
.intr:
;  full-speed other: 4*bytes + 54 fs sbp
;     low-speed  in: 32*bytes + 348 fs sbp
;     low-speed out: 32*bytes + 350 fs sbp
	inc	(yendpoint.smask); 00000001b
	ld	(yendpoint.cmask), 00011100b
	bit	bsf yendpoint.info.eps,(yendpoint.info)
	ld	de,54
	jq	z,.schedule
repeat bsr 32-bsr 4
	add	hl,hl
end repeat
	ld	e,348-$100
	inc	d
	bitmsk	yendpoint.transferInfo.dir
	jq	z,.schedule
	ld	e,350-$100
.schedule:
	call	_ScheduleEndpoint
	push	de
	pop	yendpoint
	ld	hl,USB_ERROR_SCHEDULE_FULL
	sbc	a,a
	ret
.async:
	ld	hl,(dummyHead.next)
	ld	(yendpoint.next),hl
assert endpoint+1 = endpoint.prev
	inc	hl
	ld	e,iyh
	ld	(hl),e
	ld	(yendpoint.prev),dummyHead shr 8 and $FF
	ld	(dummyHead.next),yendpoint
	ret	z
	inc	b
	dec	b
assert ti.bmUsbRole shr 16 = ti.bmUsbDmaCxFifo
	jq	z,.defaultControl
	rlc	c
	ld	c,a
	sbc	a,a
assert ti.bmUsbRole shr 16 = ti.usbFifoIn
	and	a,c
	ld	c,a
	ld	hl,ti.mpUsbFifo0Map-1
	ld	a,l
	add	a,b
	ld	l,a
	ld	a,(hl)
	and	a,not ti.bmUsbFifoDir
	or	a,c
	ld	(hl),a
assert ti.usbFifo0Cfg > ti.usbFifo0Map
	setmsk	ti.usbFifo0Cfg xor ti.usbFifo0Map,hl
	ld	a,(yendpoint.transferInfo)
	and	a,endpoint.transferInfo.type
	or	a,ti.bmUsbFifoEn
	ld	(hl),a
	ld	a,ti.usbOutEp1+1-4-$100
assert ti.usbOutEp1 > ti.usbInEp1
repeat 2
	sub	a,c
end repeat
repeat 4
	add	a,b
end repeat
	ld	l,a
	ld	(hl),ti.bmUsbEpReset shr 8
	ld	de,(yendpoint.maxPktLen)
	ld	a,d
	and	a,ti.bmUsbEpMaxPktSz shr 8
	ld	(hl),a
	dec	l
	ld	(hl),e
	xor	a,a
	scf
.shift:
	rla
	djnz	.shift
.defaultControl:
	ld	(yendpoint.overlay.fifo),a
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
	xor	a,a
	ld	c,iyl
	bit	0,c
	ret	nz
.valid:
	ld	hl,ti.mpUsbDevTest
	set	ti.bUsbTstClrFifo,(hl)
	res	ti.bUsbTstClrFifo,(hl)
.host:
	inc	b
.dec:
	ld	(.alt),a
	or	a,a
	sbc	hl,hl
	ex.s	de,hl
	ld	c,e
	jq	.enter
.endpoint:
	cp	a,c
	jq	z,.next
	ld	a,e
	cp	a,sizeof xendpointDescriptor
	ret	c
	push	bc,de,hl,ydevice
	lea	de,xendpointDescriptor
	call	_CreateEndpoint
	pop	ydevice,hl,de,bc
	ret	nz
	dec	c
.next:
	add	xdescriptor,de
.enter:
	add	hl,de
	xor	a,a
	sbc	hl,de
	ret	z
	ld	a,(xdescriptor.bLength)
	cp	a,sizeof xdescriptor
	ret	c
	ld	e,a
	sbc	hl,de
	ret	c
	ld	a,(xdescriptor.bDescriptorType)
	sub	a,ENDPOINT_DESCRIPTOR
	jq	z,.endpoint
repeat ENDPOINT_DESCRIPTOR-INTERFACE_DESCRIPTOR
	inc	a
end repeat
	jq	nz,.next
	ld	c,a
	ld	a,e
	cp	a,sizeof xinterfaceDescriptor
	ret	c
	ld	a,(xinterfaceDescriptor.bAlternateSetting)
	sub	a,0
label .alt at $-byte
	jq	nz,.next
	ld	c,(xinterfaceDescriptor.bNumEndpoints)
	djnz	.next
	ret

;-------------------------------------------------------------------------------
; Input:
;  a = endpoint
;  bc = ? | bytes or ? shl 16
; Output:
;  cf = error
;  zf = ? | false
_ExecuteDma:
	ld	hl,(rootHub.child)
	call	usb_GetDeviceEndpoint.enter
	ld	l,endpoint.overlay.next
	bit	0,(hl)
	ret	nz
	ld	ytransfer,(hl)
	bitmsk	ytransfer.status.active
	ret	z
	ld	de,(ytransfer.remaining)
	resmsk	ytransfer.remaining.dt,de
	ld	a,i
	push	af
	ld	l,endpoint.overlay.fifo
	ld	a,(hl)
	ld	l,endpoint.maxPktLen+1
	di
	ld	(ti.mpUsbDmaFifo),a
	ld	a,(hl)
	dec	l;endpoint.maxPktLen
	ld	l,(hl)
	and	a,7
	ld	h,a
	push	hl
	sbc.s	hl,de
	jq	c,.mpsLess
	sbc	hl,hl
.mpsLess:
	add.s	hl,de
	ld	a,b
	and	a,7
	ld	b,a
	ld	a,(ytransfer.type)
repeat ti.bUsbDmaDir-bsf ytransfer.type.pid
	rlca
end repeat
	and	a,ti.bmUsbDmaClrFifo or ti.usbDmaMem2Fifo
	jq	pe,.in
	inc	bc
	dec.s	bc
	sbc	hl,bc
	jq	c,.babble
	sbc	hl,hl
	add	hl,bc
.in:
	add	hl,bc
	sbc	hl,bc
	jq	z,.zlp
	ld	(ti.mpUsbDmaLen),hl
	ex	de,hl
	sbc	hl,de
	ld	(ytransfer.remaining),hl
	ex	(sp),hl
	sbc.s	hl,de
	ex	(sp),hl
	ex	de,hl
	ld	bc,(ytransfer.buffers)
	add	hl,bc
	ld	(ytransfer.buffers),hl
.flush:
	ld	hl,ti.mpUsbDmaAddr
	ld	(hl),bc
	ld	l,ti.usbDmaCtrl-$100
	ld	(hl),a
	inc	a;ti.bmUsbDmaStart
	ld	(hl),a
.waitDma:
	ld	a,(hl)
	ld	l,ti.usbDevIsr-$100
	bit	ti.bUsbIntDevDmaFin,(hl)
	jq	nz,.dmaFinished
	inc	l
	bit	ti.bUsbIntDevDmaErr-8,(hl)
	jq	z,.waitDma
	ld	a,(ytransfer.status)
	and	a,not ytransfer.status.active
	or	a,ytransfer.status.halted or ytransfer.status.bufErr
	ld	(ytransfer.status),a
	ld	(hl),ti.bmUsbIntDevDmaErr shr 8
	dec	l
.dmaFinished:
	ld	(hl),ti.bmUsbIntDevDmaFin
.finishZlp:
	pop	bc
	ld	a,e
	or	a,d
	ld	de,(ytransfer.endpoint)
	ld	a,(ytransfer.status)
repeat 8-bsr ytransfer.status.halted
	rlca
end repeat
	jq	c,.continue
	jq	z,.next
	ld	a,c
	or	a,b
	jq	z,.continue
	ld	bc,(ytransfer.altNext)
	bit	0,bc
	jq	z,.alt
.next:
	ld	bc,(ytransfer.next)
.alt:
	ld	e,endpoint.overlay.next
	ex	de,hl
	ld	(hl),bc
	ex	de,hl
	resmsk	ytransfer.status.active
	ld	a,(ytransfer.altNext)
	rrca
	jq	nc,.continue
	ld	l,ti.usbDmaFifo-$100
	bit	ti.bUsbDmaCxFifo,(hl)
	jq	nz,.cx
assert bsr transfer.next.dummy = bsf ytransfer.type.pid
	ld	a,(bc+transfer.next)
	and	a,(ytransfer.type)
repeat bsr transfer.next.dummy+1
	rrca
end repeat
	sbc	a,a
	and	a,(hl)
	ld	l,ti.usbFifoTxImr-$100
	or	a,(hl)
	ld	(hl),a
	scf
virtual
	jp	nc,0
 assert $ = .continue
 load .jp_nc: byte from $$
end virtual
	db	.jp_nc
.cx:
	ld	l,ti.usbCxFifo-$100
assert ti.usbCxFifo shr 8 = ti.bmCxFifoFin
	ld	(hl),h ; Must happen before restoring interrupts!
.continue:
	ld	l,ti.usbDmaFifo-$100
	ld	(hl),ti.bmUsbDmaNoFifo ; Must happen before restoring interrupts!
	pop	bc
	bit	2,c ; p/v flag
	jq	z,.noEi
	ei
.noEi:
	ret	nc
	ld	e,endpoint
	push	de
	ex	(sp),ix
	call	_RetireTransfers
	ccf
	pop	ix
	ret
.babble:
	ld	a,(ytransfer.status)
	and	a,not ytransfer.status.active
	or	a,ytransfer.status.halted or ytransfer.status.babble
	ld	(ytransfer.status),a
	ld	a,ti.bmUsbDmaClrFifo or ti.usbDmaFifo2Mem
	ld	(ti.mpUsbDmaLen),bc
	ld	bc,ti.vRamEnd
	jq	.flush
.zlp:
	ld	hl,ti.mpUsbCxFifo
	and	a,ti.usbDmaMem2Fifo
	jq	z,.finishZlp
	bit	ti.bUsbDmaCxFifo,(hl)
	jq	nz,.finishZlp
	ld	bc,(ytransfer.endpoint)
	ld	c,endpoint.info
	ld	a,(bc)
	and	a,endpoint.info.ep
repeat bsr (ti.usbInEp2-ti.usbInEp1)
	add	a,a
end repeat
	add	a,ti.usbInEp1 shl 1-ti.usbInEp2+1-$100
	ld	l,a
	set	ti.bUsbInEpSendZlp-8,(hl)
	jq	.finishZlp

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
	or	a,a
.nc:
	sbc	hl,hl
	inc.s	bc
.loop:
	lea	ytransfer.next,xendpoint.first
.continue:
	ld	ytransfer,(ytransfer.next)
	ld	a,(ytransfer.next)
repeat bsr ytransfer.next.dummy+1
	rrca
end repeat
	ret	c
assert ytransfer.status+1 = ytransfer.type
	ld	de,(ytransfer.status)
	ld	a,e
repeat 8-bsr ytransfer.status.active
	add	a,a
end repeat
	ret	c
repeat bsr ytransfer.status.active-bsr ytransfer.status.halted
	rlca
end repeat
	jq	c,.halted
	bit	bsr ytransfer.type.pid,d ; setup
	jq	nz,.continue
	ld	c,(ytransfer.length+0)
	ld	b,(ytransfer.length+1)
	resmsk	ytransfer.remaining.dt,bc
	add	hl,bc
	ld	c,(ytransfer.remaining+0)
	ld	a,(ytransfer.remaining+1)
	and	a,not (ytransfer.remaining.dt shr 8)
	ld	b,a
	sbc	hl,bc
	or	a,c
	jq	nz,.partial
	bitmsk	ytransfer.type.ioc,d
	jq	z,.continue
.partial:
virtual
	nop
	load .nop: $-$$ from $$
end virtual
assert .nop = 0
	xor	a,a
	ld	c,a
	call	_RetireFirstTransfer
	ret	nc
	bitmsk	xendpoint.internalFlags.freed
	jq	z,.loop
	jq	.dangling
.halted:
	ld	a,d
	and	a,ytransfer.type.cerr
	ld	c,e
	jq	z,.noStall
	bitmsk	ytransfer.status.babble,e
	jq	nz,.noStall
	inc	c
.noStall:
virtual
	ret	z
	load .ret_z: $-$$ from $$
end virtual
	ld	a,.ret_z
	call	_RetireFirstTransfer
	jq	nz,_FlushEndpoint.check
	bitmsk	xendpoint.internalFlags.freed
.dangling:
	jq	nz,_FlushEndpoint.dangling
	ld	ytransfer,(xendpoint.first)
	ld	(xendpoint.overlay.next),ytransfer
	ld	(xendpoint.overlay.altNext),ytransfer
.restart:
	ld	de,(ytransfer.length)
	ld	(ytransfer.remaining+0),e
	ld	(ytransfer.remaining+1),d
	ld	a,(ytransfer.type)
	and	a,not ytransfer.type.cpage
	or	a,ytransfer.type.cerr
	ld	(ytransfer.type),a
	bitmsk	ytransfer.status.halted
	ld	(ytransfer.status),ytransfer.status.active
	ld	ytransfer,(ytransfer.next)
	jq	z,.restart
	ld	(xendpoint.overlay.status),h;0
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
;  de = ?
;  hl = ? | error
;  iy = ?
_FlushEndpoint.loop:
virtual
	nop
	load .nop: $-$$ from $$
end virtual
assert .nop = 0
	xor	a,a
	sbc	hl,hl
	call	_RetireFirstTransfer
	ret	nc
_FlushEndpoint.check:
	bitmsk	xendpoint.internalFlags.freed
	jq	nz,_FlushEndpoint.dangling
	jq	_FlushEndpoint
_FlushEndpoint:
	ld	ytransfer,(xendpoint.first)
	ld	a,(ytransfer.next)
repeat bsr ytransfer.next.dummy+1
	rrca
end repeat
	jq	nc,.loop
assert endpoint.overlay.altNext+2 = endpoint.overlay.status-2
	ld	(xendpoint.overlay.status-2),bc
	ld	(xendpoint.overlay.next),ytransfer
	ld	(xendpoint.overlay.altNext),ytransfer
	bitmsk	USB_TRANSFER_STALLED,bc
	ret	z
	ld	a,(currentRole)
	cpl
	bit	ti.bUsbRole-16,a
	ret	z
	bitmsk	BULK_TRANSFER and INTERRUPT_TRANSFER,(xendpoint.transferInfo)
	ret	z
	push	xendpoint
	call	usb_ClearEndpointHalt
	pop	af
	ex	de,hl
	scf
	sbc	hl,hl
	adc	hl,de
	ret
.dangling:
	bitmsk	xendpoint.internalFlags.refCnt
	ret	nz
	lea	yendpoint,xendpoint
.free:
	ld	hl,(yendpoint.last)
	call	_Free32Align32
	lea	hl,yendpoint.base
	jq	_Free64Align256

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
	bitmsk	xendpoint.internalFlags.refCnt
	setmsk	xendpoint.internalFlags.refCnt
	ld	de,(xendpoint.first)
	push	af,de,bc
.loop:
	push	de
	pop	ytransfer
	ld	de,(ytransfer.altNext)
	bit	0,de
	jq	z,.alt
	ld	de,(ytransfer.next)
.alt:
	bitmsk	ytransfer.type.ioc
	jq	z,.loop
	ld	(xendpoint.first),de
	ld	de,(ytransfer.data+0)
	ld	a,(ytransfer.data+3)
	xor	a,e
	and	a,$F
	xor	a,e
	ld	e,a
	ld	b,0
	push	de,hl,bc,xendpoint
	ld	hl,(ytransfer.callback+0)
	ld	a,(ytransfer.callback+3)
	xor	a,l
	and	a,$F
	xor	a,l
	ld	l,a
	call	_DispatchEvent.dispatch
	pop	bc,bc,bc,bc,bc,ytransfer,af
	ld	(.smc),a
	jq	nz,.restored
	resmsk	xendpoint.internalFlags.refCnt
.restored:
	add	hl,de
	scf
	sbc	hl,de
label .smc
	ret	z
	ex	de,hl
.free:
	lea	hl,ytransfer
	bitmsk	ytransfer.type.ioc
	ld	ytransfer,(hl+transfer.next)
	call	_Free32Align32
	jq	z,.free
	ld	hl,1
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_HandleCxSetupInt:
	ld	b,4
	ld	de,setupPacket+4
	ld	l,ti.usbDmaFifo-$100
	ld	a,i
	di
	ld	(hl),ti.bmUsbDmaCxFifo
	ld	l,ti.usbEp0Data+4-$100
.fetch:
	dec	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	setmsk	4,de
	ld	a,(hl)
	ld	(de),a
	resmsk	4,de
	djnz	.fetch
	ld	l,ti.usbDmaFifo-$100
	jq	po,.noEi
	ei
.noEi:
	ld	(hl),b;ti.bmUsbDmaNoFifo
	ld	l,ti.usbCxFifo-$100
	set	ti.bCxFifoClr,(hl)
	ld	a,USB_DEFAULT_SETUP_EVENT
	call	_DispatchEvent
	jq	z,.defaultHandler
	xor	a,a
	add	hl,de
	scf
	sbc	hl,de
	inc	hl
	ex	de,hl
	jq	.return
.defaultHandler:
	ld	ysetup,setupPacket
	ld	hl,(ysetup.wValue)
	ld	de,(ysetup.wIndex)
	ld	bc,(ysetup.bmRequestType)
	ld	a,c
	inc	b
	djnz	.notGetStatus
	sub	a,DEVICE_TO_HOST or STANDARD_REQUEST-1
	ld	b,a
	ld	a,d
	or	a,l
	or	a,h
	jq	nz,.unhandled
	ld	c,sizeof tempEndpointStatus
	or	a,e
	djnz	.notGetDeviceStatus
	jq	nz,.unhandled
	scf
	jq	.sendStatus
.notGetDeviceStatus:
	djnz	.notGetInterfaceStatus
	xor	a,a
.sendBitStatus:
assert sizeof tempEndpointStatus = 1 shl 1
	and	a,c
	rrca
.sendStatus:
	ld	de,tempEndpointStatus
	ld	(de),a
	jq	nc,.sendGetStatusDataStage
assert tempEndpointStatus-1 = deviceStatus
	dec	de
.sendGetStatusDataStage:
	jq	.sendDataStage
.notGetInterfaceStatus:
	djnz	.notGetEndpointStatus
	jq	z,.sendStatus
	call	.lookupEndpointA
	ld	a,(hl)
repeat ti.bUsbEpStall-8-1
	rrca
end repeat
	jq	nz,.sendBitStatus
.notGetEndpointStatus:
.notClearDeviceRemoteWakeupFeature:
.notClearEndpointFeature:
.notSetDeviceTestModeFeature:
.notSetEndpointFeature:
	jq	.unhandled
.notGetStatus:
	djnz	.notClearFeature
assert ~HOST_TO_DEVICE or STANDARD_REQUEST
	inc	a
	ld	b,a
	ld	a,d
	or	a,h
	or	a,(ysetup.wLength+0)
	or	a,(ysetup.wLength+1)
	djnz	.notClearDeviceFeature
	or	a,e
	jq	nz,.unhandled
	ld	b,l
	djnz	.notClearDeviceRemoteWakeupFeature
	ld	hl,deviceStatus
	resmsk	DEVICE_REMOTE_WAKEUP_STATUS,(hl)
	jq	.handled
.notClearDeviceFeature:
	dec	b
	djnz	.notClearEndpointFeature
assert ~ENDPOINT_HALT_FEATURE
	or	a,l
	jq	nz,.unhandled
	call	.lookupEndpoint
	jq	z,.unhandled
	ld	a,(hl)
	or	a,ti.bmUsbEpReset shr 8
	and	a,not ti.bmUsbEpStall shr 8
	ld	(hl),a
	jq	.handled
.notClearFeature:
	dec	b
	djnz	.notSetFeature
assert ~HOST_TO_DEVICE or STANDARD_REQUEST
	inc	a
	ld	b,a
	ld	a,h
	or	a,(ysetup.wLength+0)
	or	a,(ysetup.wLength+1)
	djnz	.notSetDeviceFeature
	or	a,e
	ld	b,l
	djnz	.notSetDeviceRemoteWakeupFeature
	or	a,d
	jq	nz,.unhandled
	ld	hl,deviceStatus
	setmsk	DEVICE_REMOTE_WAKEUP_STATUS,(hl)
	jq	.handled
.notSetDeviceRemoteWakeupFeature:
	djnz	.notSetDeviceTestModeFeature
	jq	nz,.unhandled
	ld	b,d
	ld	a,1
.shift:
	rlca
	and	a,$F shl 1
	jq	z,.unhandled
	djnz	.shift
	ld	hl,ti.mpUsbPhyTmsr
	or	a,(hl)
	ld	(hl),a
	jq	.handled
.notSetDeviceFeature:
	dec	b
	djnz	.notSetEndpointFeature
	or	a,d
assert ~ENDPOINT_HALT_FEATURE
	or	a,l
	jq	nz,.unhandled
	call	.lookupEndpoint
	jq	z,.unhandled
	ld	a,(hl)
	and	a,not ti.bmUsbEpReset shr 8
	or	a,ti.bmUsbEpStall shr 8
	ld	(hl),a
	call	.handled
	push	hl,de
	ex	(sp),ix
assert HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_ENDPOINT-1 = USB_TRANSFER_STALLED
	dec	c
	call	_FlushEndpoint
	pop	ix,de
	ret	nc
	ex	de,hl
	cp	a,a
	ret
.notSetFeature:
	dec	b
	djnz	.notSetAddress
	ld	a,l
	and	a,$80
	or	a,h
	or	a,e
	or	a,d
assert ~HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	or	a,c
	ld	de,(ysetup.wLength)
	or	a,e
	or	a,d
	jq	nz,.unhandled
	ld	(ti.mpUsbDevAddr),hl
	jq	.handled
.handled:
	ld	a,ti.bmCxFifoFin
	jq	.success
.success:
	cp	a,a
.return:
	ld	hl,ti.mpUsbCxFifo
	ld	(hl),a
	ld	l,ti.usbCxIsr-$100
	ld	(hl),ti.bmUsbIntCxSetup
	ret	z
	ex	de,hl
	ret
.notSetAddress:
	djnz	.notGetDescriptor
	xor	a,DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE
	jq	z,.getDescriptor
.notGetDescriptor:
	djnz	.notSetDescriptor
.notSetDescriptor:
	djnz	.notGetConfiguration
	xor	a,DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE
	or	a,l
	or	a,h
	or	a,e
	or	a,d
	jq	nz,.unhandled
	ld	c,1
	ld	de,selectedConfiguration
	jq	.sendDataStage
.notGetConfiguration:
	djnz	.notSetConfiguration
assert ~HOST_TO_DEVICE or STANDARD_REQUEST or RECIPIENT_DEVICE
	or	a,h
	or	a,e
	or	a,d
	ld	bc,(ysetup.wLength)
	or	a,c
	or	a,b
	jq	nz,.unhandled
	or	a,l
	jq	z,.setConfigured
	push	ix
	ld	xstandardDescriptors,(currentDescriptors)
	ld	ydeviceDescriptor,(xstandardDescriptors.device)
	ld	b,(ydeviceDescriptor.bNumConfigurations)
	ld	hl,(xstandardDescriptors.configurations)
.findConfigurationDescriptor:
	ld	xconfigurationDescriptor,(hl)
	cp	a,(xconfigurationDescriptor.bConfigurationValue)
	jq	z,.foundConfigurationDescriptor
repeat long
	inc	hl
end repeat
	ld	a,e
	djnz	.findConfigurationDescriptor
.foundConfigurationDescriptor:
	ld	ydevice,(rootHub.child)
	ld	de,(xconfigurationDescriptor.wTotalLength)
	ld	b,(xconfigurationDescriptor.bNumInterfaces)
	push	xconfigurationDescriptor
	call	z,_ParseInterfaceDescriptors
	pop	de,ix
	jq	nz,.unhandled
	ld	a,(setupPacket.wValue)
	scf
.setConfigured:
	ld	(selectedConfiguration),a
	ld	hl,ti.mpUsbDevAddr
	ld	a,(hl)
	rla
	rrca
	ld	(hl),a
	call	.handled
	ld	a,USB_HOST_CONFIGURE_EVENT
	jq	_DispatchEvent
.notSetConfiguration:
	djnz	.notGetInterface
.notGetInterface:
	djnz	.notSetInterface
.notSetInterface:
.unhandled:
	ld	a,ti.bmCxFifoStall
	jq	.success
.getDescriptor:
	push	hl
	pop	bc
	ld	ystandardDescriptors,(currentDescriptors)
	djnz	.notDevice;DEVICE_DESCRIPTOR
	or	a,c
	or	a,e
	or	a,d
	jq	nz,.unhandled
.sendSingleDescriptorIYind:
	ld	b,a
	ld	hl,(ystandardDescriptors.device)
.sendSingleDescriptorHL:
	ld	c,(hl)
	ex	de,hl
	jq	.sendDataStage
.notDevice:
	djnz	.notConfiguration;CONFIGURATION_DESCRIPTOR
	or	a,e
	or	a,d
	jq	nz,.unhandled
	ld	hl,(ystandardDescriptors.configurations)
	ld	ydeviceDescriptor,(ystandardDescriptors.device)
	ld	a,c
	cp	a,(ydeviceDescriptor.bNumConfigurations)
	jq	nc,.unhandled
repeat long
	add	hl,bc
end repeat
	ld	yconfigurationDescriptor,(hl)
	ld	bc,(yconfigurationDescriptor.wTotalLength)
	ld	de,(hl)
	jq	.sendDataStage
.notConfiguration:
	djnz	.notString;STRING_DESCRIPTOR
	ld	hl,(ystandardDescriptors.langids)
	cp	a,c
	jq	z,.langids
	ld	a,(ystandardDescriptors.numStrings)
	cp	a,c
	jq	c,.unhandled
	ld	iy,(ystandardDescriptors.strings)
	ld	a,(hl)
	rra
	dec	a
	ld	b,a
	dec	c
	mlt	bc
repeat long
	add	iy,bc
end repeat
	ld	b,a
	inc	hl
.findLangId:
	inc	hl
	ld	a,(hl)
	inc	hl
	sub	a,e
	jq	nz,.nextLangId
	ld	a,(hl)
	sub	a,d
	jq	z,.sendSingleDescriptorIYind
.nextLangId:
	lea	iy,iy+3
	djnz	.findLangId
.langids:
	or	a,e
	or	a,d
	jq	z,.sendSingleDescriptorHL
.notString:
	jq	.unhandled
.sendDataStage:
	ld	hl,ti.mpUsbDmaFifo
	ld	(hl),ti.bmUsbDmaCxFifo
	ld	l,ti.usbDmaAddr-$100
	ld	(hl),de
	ld	l,ti.usbDmaCtrl-$100
	ld	a,(setupPacket.bmRequestType)
	rlca
	rlca
	xor	a,(hl)
	and	a,ti.usbDmaMem2Fifo
	xor	a,(hl)
	ld	(hl),a
	inc	l;ti.usbDmaLen-$100
	ex	de,hl
	ld	hl,(setupPacket.wLength)
	sbc.s	hl,bc
	jq	c,.min
	sbc	hl,hl
.min:
	add.s	hl,bc
	ex	de,hl
	ld	(hl),de
	dec	l;ti.usbDmaCtrl-$100
	set	ti.bUsbDmaStart,(hl)
	ld	l,ti.usbDevIsr-$100
.wait:
	bit	ti.bUsbIntDevDmaFin,(hl)
	jq	z,.wait
	ld	(hl),ti.bmUsbIntDevDmaFin
	xor	a,a
	ld	l,ti.usbDmaFifo-$100
	ld	(hl),a
	jq	.handled
; Input:
;  e = endpoint address
; Output:
;  zf = invalid endpoint address or default control address
;  a = ?
;  de = endpoint | de
;  hl = endpoint register+1 | ?
.lookupEndpoint:
	ld	a,e
.lookupEndpointA:
	add	a,a
	dec	a
	cp	a,1 shl 5-1
	sbc	a,a
	ld	hl,(rootHub.child)
	call	nz,usb_GetDeviceEndpoint.check
	ret	z
	ld	a,e
.lookupEndpointRegister:
	add	a,a
	ld	de,ti.mpUsbInEp1+1-4
	jq	c,.in
assert ti.usbInEp1 < ti.usbOutEp1
	setmsk	(ti.usbInEp1+1-4) xor (ti.usbOutEp1+1-4),de
.in:
	add	a,a
	add	a,e
	ld	e,a
	ex	de,hl
	ret

_HandleDeviceDescriptor:
	ld	hl,3
	add	hl,sp
	ld	yendpoint,(hl)
repeat long
	inc	hl
end repeat
	ld	b,(hl)
repeat long
	inc	hl
end repeat
	ld	a,(hl)
	xor	a,8
	or	a,b
	jq	nz,.free
repeat long
	inc	hl
end repeat
	ld	de,(hl)
	ld	(de),a
	ld	hl,usedAddresses
	ld	b,sizeof usedAddresses
	scf
.search:
	ld	c,(hl)
	adc	a,c
	jq	c,.next
	or	a,c
	ld	(hl),a
	xor	a,c
	ld	c,8
	mlt	bc
.shift:
	dec	c
	rrca
	jq	nc,.shift
	sbc	a,c
	ex	de,hl
	ld	bc,_HandleDeviceEnable
	push	hl,bc,bc,hl,yendpoint
	inc	l
	ld	(hl),SET_ADDRESS_REQUEST
	ld	b,6
.zero:
	inc	l
	ld	c,(hl)
	ld	(hl),a
	xor	a,a
	djnz	.zero
	ld	(yendpoint.maxPktLen),c
	call	usb_ScheduleControlTransfer
	ld	a,l
	pop	bc,bc,bc,bc,bc
	or	a,a
	ret	z
virtual
	ld	hl,0
 assert $ = .free
 load .ld_hl: byte from $$
end virtual
	db	.ld_hl
.next:
	inc	l
	djnz	.search
.free:
	call	_FreeTransferData
.disable:
	call	_HandlePortPortEnInt.disable
	ret	nz
	or	a,a
	sbc	hl,hl
	ret

_HandleDeviceEnable:
	ld	hl,12
	add	hl,sp
	ld	hl,(hl)
	setmsk	2,hl
	ld	c,(hl)
	call	_FreeTransferData
	ld	hl,3
	add	hl,sp
	ld	yendpoint,(hl)
repeat long
	inc	hl
end repeat
	ld	a,(hl)
	or	a,a
	jq	nz,_HandleDeviceDescriptor.disable
	sbc	hl,hl
	ld	de,(yendpoint.device)
	ld	(yendpoint.addr),c
	ld	ydevice,(yendpoint.device)
	ld	(ydevice.addr),c
	ld	a,USB_DEVICE_ENABLED_EVENT
	jq	_DispatchEvent

_HandleDevInt:
	ld	l,ti.usbGisr-$100
	inc	h
iterate type, Cx, Fifo, Dev
	bit	ti.bUsbDevInt#type,(hl)
	call	nz,_HandleDev#type#Int
	ret	nz
end iterate
	ld	l,ti.usbIsr
	dec	h
	ld	(hl),ti.bmUsbIntDev
	ld	a,USB_DEVICE_INTERRUPT
	jq	_DispatchEvent

_HandleDevCxInt:
	ld	l,ti.usbCxIsr-$100
iterate type, Setup, In, Out, End, Err, Abort
	bit	ti.bUsbIntCx#type,(hl)
	call	nz,_HandleCx#type#Int
	ret	nz
end iterate
	ld	l,ti.usbGisr-$100
	ld	(hl),ti.bmUsbDevIntCx
	ld	a,USB_DEVICE_CONTROL_INTERRUPT
	jq	_DispatchEvent

_HandleDevFifoInt:
	ld	l,ti.usbFifoTxImr-$100
	ld	a,(hl)
	cpl
	ld	l,ti.usbFifoTxIsr-$100
	and	a,(hl)
	ld	c,a
repeat 4, fifo: 0
 iterate type, In
	push	bc
	bit	ti.bUsbIntFifo#fifo#type,c
	call	nz,_HandleFifo#fifo#type#Int
	pop	bc
	ret	nz
 end iterate
end repeat
	ld	l,ti.usbFifoRxIsr-$100
repeat 4, fifo: 0
 iterate type, Spk, Out
	bit	ti.bUsbIntFifo#fifo#type,(hl)
	call	nz,_HandleFifo#fifo#type#Int
	ret	nz
 end iterate
end repeat
	ld	l,ti.usbGisr-$100
	ld	(hl),ti.bmUsbDevIntFifo
	ret

_HandleDevDevInt:
	ld	l,ti.usbDevIsr-$100
iterate type, Reset, Suspend, Resume, IsocErr, IsocAbt, ZlpTx, ZlpRx, DmaFin
	bit	ti.bUsbIntDev#type,(hl)
	call	nz,_HandleDev#type#Int
	ret	nz
end iterate
	inc	l;ti.usbDevIsr+1-$100
iterate type, DmaErr, Idle, Wakeup
	bit	ti.bUsbIntDev#type-8,(hl)
	call	nz,_HandleDev#type#Int
	ret	nz
end iterate
	ld	l,ti.usbGisr-$100
	ld	(hl),ti.bmUsbDevIntDev
	ld	a,USB_DEVICE_DEVICE_INTERRUPT
	jq	_DispatchEvent

_HandleOtgInt:
	ld	l,ti.usbOtgIsr
iterate type, BSrpComplete, ASrpDetect, AVbusErr, BSessEnd
	bit	ti.bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	inc	l;ti.usbOtgIsr+1
iterate type, RoleChg, IdChg, Overcurr, BPlugRemoved, APlugRemoved
	bit	ti.bUsbInt#type-8,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	ld	l,ti.usbIsr
	ld	(hl),ti.bmUsbIntOtg
	ld	a,USB_OTG_INTERRUPT
	jq	_DispatchEvent

_HandleHostInt:
	ld	l,ti.usbSts
	ld	a,0
label .hack at $-byte
	and	a,ti.bmUsbIntErr or ti.bmUsbInt
	call	nz,_HandleCompletionInt
	ret	nz
	ld	hl,ti.mpUsbSts
iterate type, PortChgDetect, FrameListOver, HostSysErr, AsyncAdv
	bit	ti.bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	ld	l,ti.usbIsr
	ld	(hl),ti.bmUsbIntHost
	ld	a,USB_HOST_INTERRUPT
	jq	_DispatchEvent

_HandleCxInInt:
_HandleCxOutInt:
	ld	l,ti.usbCxFifoBytes-$100
	ld	c,(hl)
	xor	a,a
	ld	b,a
	call	_ExecuteDma
	ret	c
	ld	hl,ti.mpUsbCxIsr
	ld	(hl),ti.bmUsbIntCxOut or ti.bmUsbIntCxIn
	cp	a,a
	ret

_HandleCxEndInt:
	ld	l,ti.usbCxFifo-$100
	ld	(hl),ti.bmCxFifoFin
	ld	l,ti.usbCxIsr-$100
	ld	(hl),ti.bmUsbIntCxEnd
	cp	a,a
	ret

_HandleCxErrInt:
	ld	(hl),ti.bmUsbIntCxErr
	ld	a,USB_CONTROL_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleCxAbortInt:
	ld	(hl),ti.bmUsbIntCxAbort
	ld	a,USB_CONTROL_ABORT_INTERRUPT
	jq	_DispatchEvent

repeat 4, fifo: 0
_HandleFifo#fifo#OutInt:
	ld	l,ti.usbFifo#fifo#Csr-$100
	ld	bc,(hl)
	ld	a,fifo+$01
	call	_ExecuteDma
	ret	c
	ld	hl,ti.mpUsbFifoRxIsr
	ld	(hl),ti.bmUsbIntFifo#fifo#Out
	cp	a,a
	ret

_HandleFifo#fifo#SpkInt:
	ld	(hl),ti.bmUsbIntFifo#fifo#Spk
	ld	a,USB_FIFO#fifo#_SHORT_PACKET_INTERRUPT
	jq	_DispatchEvent

_HandleFifo#fifo#InInt:
	ld	a,fifo+$81
	call	_ExecuteDma
	ret	c
	ld	hl,ti.mpUsbFifoTxIsr
	ld	(hl),ti.bmUsbIntFifo#fifo#In
	cp	a,a
	ret
end repeat

_HandleDevResetInt:
	call	_RootDeviceDisconnected
	ret	nz
	xor	a,a
	ld	l,ti.usbDevAddr-$100
	ld	(hl),a
	ld	(selectedConfiguration),a
	inc	a
	ld	(deviceStatus),a
	ld	l,ti.usbDmaCtrl-$100
	ld	(hl),ti.bmUsbDmaClrFifo or ti.bmUsbDmaAbort
	ld	l,ti.usbCxFifo-$100
	set	ti.bCxFifoClr,(hl)
	ld	c,IS_DEVICE or IS_ENABLED
	ld	l,ti.usbDevCtrl-$100
	call	_CreateDevice.root
	call	z,_CreateDefaultControlEndpoint
	ret	nz
	ld	hl,(currentDescriptors)
	ld	hl,(hl)
	ld	de,7
	add	hl,de
	ld	a,(hl)
	ld	(yendpoint.maxPktLen),a
	ld	hl,ti.mpUsbDevIsr
	ld	(hl),ti.bmUsbIntDevReset
	ret

_HandleDevSuspendInt:
	ld	(hl),ti.bmUsbIntDevSuspend
	ld	a,USB_DEVICE_SUSPEND_INTERRUPT
	jq	_DispatchEvent

_HandleDevResumeInt:
	ld	(hl),ti.bmUsbIntDevResume
	ld	a,USB_DEVICE_RESUME_INTERRUPT
	jq	_DispatchEvent

_HandleDevIsocErrInt:
	ld	(hl),ti.bmUsbIntDevIsocErr
	ld	a,USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleDevIsocAbtInt:
	ld	(hl),ti.bmUsbIntDevIsocAbt
	ld	a,USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT
	jq	_DispatchEvent

_HandleDevZlpTxInt:
	ld	l,ti.usbTxZlp-$100
	xor	a,a
	ld	(hl),a
	ld	l,ti.usbDevIsr-$100
	ld	(hl),ti.bmUsbIntDevZlpTx
	ret

_HandleDevZlpRxInt:
	ld	l,ti.usbRxZlp-$100
	call	.almostMostAtomicExchangePossible
.loop:
	inc	b
	srl	c
	push	bc
	ld	a,b
	ld	b,0
	ld	c,b
	call	c,_ExecuteDma
	pop	bc
	ret	c
	inc	c
	dec	c
	jq	nz,.loop
	ld	hl,ti.mpUsbDevIsr
	ld	(hl),ti.bmUsbIntDevZlpRx
	ret

.almostMostAtomicExchangePossible:
	ld	a,i
virtual at ti.mpLcdLpbase+1
	ld	c,(hl)
	ld	(hl),b
	ret
 load .exchange $-$$ from $$
end virtual
	ld	iy,ti.mpLcdRange
	ld	bc,.exchange
	di
	ld	de,(iy+ti.lcdLpbase+1)
	ld	(iy+ti.lcdLpbase+1),bc
	ld	b,0
	call	ti.mpLcdLpbase+1
	ld	(iy+ti.lcdLpbase+1),de
	ret	po
	ei
	ret

_HandleDevDmaFinInt:
	ld	(hl),ti.bmUsbIntDevDmaFin
	ld	a,USB_DEVICE_DMA_FINISH_INTERRUPT
	jq	_DispatchEvent

_HandleDevDmaErrInt:
	ld	(hl),ti.bmUsbIntDevDmaErr shr 8
	ld	a,USB_DEVICE_DMA_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleDevIdleInt:
	ld	(hl),ti.bmUsbIntDevIdle shr 8
	ld	a,USB_DEVICE_IDLE_INTERRUPT
	jq	_DispatchEvent

_HandleDevWakeupInt:
	ld	l,ti.usbPhyTmsr-$100
	res	ti.bUsbUnplug,(hl)
	ld	l,ti.usbDevIsr+1-$100
	ld	(hl),ti.bmUsbIntDevWakeup shr 8
	ld	a,USB_DEVICE_WAKEUP_INTERRUPT
	jq	_DispatchEvent

_HandleBSrpCompleteInt:
	ld	(hl),ti.bmUsbIntBSrpComplete
	ld	a,USB_B_SRP_COMPLETE_INTERRUPT
	jq	_DispatchEvent

_HandleASrpDetectInt:
	ld	(hl),ti.bmUsbIntASrpDetect
	ld	a,USB_A_SRP_DETECT_INTERRUPT
	jq	_DispatchEvent

_HandleAVbusErrInt:
	ld	(hl),ti.bmUsbIntAVbusErr
	ld	a,USB_A_VBUS_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleBSessEndInt:
	ld	(hl),ti.bmUsbIntBSessEnd
	ld	a,USB_B_SESSION_END_INTERRUPT
	jq	_DispatchEvent

_HandleRoleChgInt:
_HandleIdChgInt:
	ld	de,currentRole
	ld	a,(de)
	ld	c,a
	ld	(hl),(ti.bmUsbIntRoleChg or ti.bmUsbIntIdChg) shr 8
	ld	a,(ti.mpUsbOtgCsr+2)
	and	a,(ti.bmUsbRole or ti.bmUsbId) shr 16
	cp	a,c
	ret	z
	ld	(de),a
	call	_PowerVbusForRole
assert ~USB_ROLE_CHANGED_EVENT
	xor	a,a;USB_ROLE_CHANGED_EVENT
	ld	l,ti.usbOtgIsr+1
	jq	_DispatchEvent

_HandleOvercurrInt:
	ld	(hl),ti.bmUsbIntOvercurr shr 8
	ld	a,USB_OVERCURRENT_INTERRUPT
	jq	_DispatchEvent

_HandleAPlugRemovedInt:
_HandleBPlugRemovedInt:
	ld	(hl),(ti.bmUsbIntAPlugRemoved or ti.bmUsbIntBPlugRemoved) shr 8
	jq	_RootDeviceDisconnected

; Output:
;  zf = success
;  de = ? | hl
;  hl = hl | error
;  iy = ?
_RootDeviceDisconnected:
	ld	de,_DeviceDisconnected
.enter:
	ex	de,hl
	push	de,ix
	ld	xdevice,(rootHub.child)
	dec	ixl
	call	nz,_DispatchEvent.dispatch
	pop	ix,de
	ret	nz
	ex	de,hl
	ret

_HandleCompletionInt:
	ld	(hl),a
usb_PollTransfers:
	push	ix
.async.restart:
	ld	xendpoint,dummyHead
.async:
	bitmsk	xendpoint.internalFlags.freed
	jq	nz,.async.restart
	ld	xendpoint,(xendpoint.next)
	or	a,a
	sbc	hl,hl
	ld	a,ixh
	xor	a,dummyHead shr 8 and $FF
	call	nz,_RetireTransfers.nc
	jq	c,.async
	pop	ix
label .enabled
	ret	nz
load .enable: byte from .enabled
virtual
	ret
 load .disable: byte from $$
end virtual
	push	ix
	ld	ix,periodicList
	ld	b,1 shl 7
.periodic:
	lea	ix,ix+4
.periodic.restart:
	push	ix
.isoc:
	ld	de,(ix-4)
	ld	ixh,d
	ld	ixl,e
	bit	2,e
	jq	nz,.isoc
.intr:
	srl	e
	jq	c,.periodic.done
	ld	a,(xendpoint.interval)
	cp	a,b
	jq	c,.periodic.done
	push	bc
	call	_RetireTransfers.nc
	pop	bc
	jq	nc,.periodic.error
	bitmsk	xendpoint.internalFlags.freed
	ld	xendpoint,(xendpoint.next)
	ld	e,ixl
	jq	z,.intr
	or	a,a
.periodic.done:
	pop	ix
	jq	nc,.periodic.restart
	djnz	.periodic
	or	a,a
	sbc	hl,hl
virtual
	ld	a,0
 load .ld_a: byte from $$
end virtual
	db	.ld_a
.periodic.error:
	pop	bc,ix
	ret

_HandlePortChgDetectInt:
	ld	(hl),ti.bmUsbIntPortChgDetect
	ld	l,ti.usbPortStsCtrl
iterate type, ConnSts, PortEn, Overcurr
	bit	ti.bUsb#type#Chg, (hl)
	call	nz,_HandlePort#type#Int
	ret	nz
end iterate
	ld	l,ti.usbSts
	ret

_HandlePortConnStsInt:
	call	_RootDeviceDisconnected
	ret	nz
	ld	a,(hl)
	and	a,not (ti.bmUsbOvercurrChg or ti.bmUsbPortEnChg or ti.bmUsbPortEn)
	ld	(hl),a
	bit	ti.bUsbCurConnSts,(hl)
	ret	z
	ld	c,IS_DEVICE or IS_DISABLED
	ld	l,ti.usbOtgCsr+2
	jq	_CreateDevice.root

; Input:
;  c = find flags
;  de = parent hub
;  hl = pointer to device speed shl 2
; Output:
;  zf = success
;  a = ?
;  bc = ?
;  de = ?
;  hl = ti.mpUsbPortStsCtrl | error
;  iy = device
_CreateDevice.root:
	ld	de,rootHub
_CreateDevice:
	ld	a,(hl)
	call	_Alloc32Align32
	jq	nz,.error
	push	hl
	pop	ydevice
	call	_Alloc32Align32
	jq	nz,.nomem
	ld	(ydevice.endpoints),hl
	ex	de,hl
	ld	(ydevice.hub),hl
	ld	(ydevice.find),c
assert ti.bUsbSpd-16 = ti.bUsbDevSpd
	and	a,ti.bmUsbSpd shr 16
	rrca
	rrca
	ld	(ydevice.speed),a
	setmsk	device.child,hl
	ld	(hl),ydevice
	ld	(ydevice.back),hl
	ld	bc,32-1
	push	de
	inc	de
	pop	hl
	ld	(hl),-1
	ldir
	ld	(ydevice.hubPorts),b;0
	ld	(ydevice.addr),b;0
	ld	(ydevice.data),bc;0
	inc	c;1
	ld	(ydevice.refcnt),bc;1
	ld	(ydevice.child),c;1
	ld	(ydevice.sibling),c;1
	ld	hl,ti.mpUsbPortStsCtrl
	ld	a,USB_DEVICE_CONNECTED_EVENT
	ld	c,(ydevice.find)
.enabled:
	lea	de,ydevice
	push	bc,de
	call	_DispatchEvent
	pop	ydevice,bc
	ret	nz
	bitmsk	IS_ENABLED,c
	ret	z
	ld	a,USB_DEVICE_ENABLED_EVENT
assert ~USB_DEVICE_ENABLED_EVENT and IS_ENABLED
	ld	c,a
	jq	.enabled
.nomem:
	lea	hl,ydevice
	call	_Free32Align32
.error:
	ld	hl,USB_ERROR_NO_MEMORY
	ret

_HandlePortPortEnInt:
	ld	a,(hl)
	and	a,not (ti.bmUsbOvercurrChg or ti.bmUsbConnStsChg)
	ld	(hl),a
	bit	ti.bUsbPortEn,(hl)
	jq	z,.disabled
	ld	ydevice,(rootHub.child)
	ld	c,iyl
	bit	0,c
	call	z,_CreateDefaultControlEndpoint.enable
	call	z,_Alloc32Align32
	jq	nz,.disable
	ld	bc,_HandleDeviceDescriptor
	ld	de,_GetDeviceDescriptor8
	push	hl,bc,hl,de,yendpoint
	call	usb_ScheduleControlTransfer
	pop	de,de,de,de,de
	ld	a,l
	ld	hl,ti.mpUsbPortStsCtrl
	or	a,a
	ret	z
	ex	de,hl
	call	_Free32Align32
.disable:
	ld	hl,ti.mpUsbPortStsCtrl
	ld	a,(hl)
	and	a,not (ti.bmUsbOvercurrChg or ti.bmUsbPortEnChg or ti.bmUsbPortEn or ti.bmUsbConnStsChg)
	ld	(hl),a
.disabled:
	ld	de,_DeviceDisabled
	jq	_RootDeviceDisconnected.enter

_HandlePortOvercurrInt:
	ld	a,(hl)
	and	a,not (ti.bmUsbPortEnChg or ti.bmUsbConnStsChg)
	ld	(hl),a
	ld	a,(hl)
	and	a,ti.bmUsbOvercurrActive
	cp	a,ti.bmUsbOvercurrActive
	sbc	a,a
assert USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT - 1 = USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT
	add	a,USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT;USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT
	jq	_DispatchEvent

_HandleFrameListOverInt:
	ld	(hl),ti.bmUsbIntFrameListOver
	ld	a,USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT
	jq	_DispatchEvent

_HandleHostSysErrInt:
	ld	(hl),ti.bmUsbIntHostSysErr
	ld	a,USB_HOST_SYSTEM_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleAsyncAdvInt:
	ld	(hl),ti.bmUsbIntAsyncAdv
.cleanup.hl:
	ex	de,hl
.cleanup.de:
	ld	a,(cleanupListReady)
	ld	yendpoint,dummyHead
	jq	.enter
.loop:
	ld	a,(yendpoint.prev)
	setmsk	yendpoint.internalFlags.freed
	bitmsk	yendpoint.internalFlags.refCnt
	call	z,_FlushEndpoint.free
.enter:
	ld	iyh,a
	inc	a
	jq	nz,.loop
	scf
.scheduleCleanup.de:
	ret	nz
	ex	de,hl
.scheduleCleanup.hl:
	ret	nz
	sbc	a,a
	ld	de,(cleanupListReady)
	scf
	adc	a,e
	sbc	a,a
	ret	z
	ld	(cleanupListReady-1),de
	inc	d
	ret	z
	ld	a,l
	ld	l,ti.usbCmd
	set	ti.bUsbIntAsyncAdvDrbl,(hl)
	ld	l,a
	cp	a,a
	ret

;-------------------------------------------------------------------------------
; Dispatch a global usb event.
; Input:
;  a = event
;  de = event data
; Output:
;  zf = success
;  a = ?
;  bc = ?
;  de = 0 | hl
;  hl = hl | error
;  iy = ?
_DispatchEvent:
	push	hl
	ld	hl,(eventCallback.data)
	push	hl,de
	or	a,a
	sbc	hl,hl
	ld	l,a
	push	hl
	ld	l,h
	ex	de,hl
	ld	hl,(eventCallback)
	sbc	hl,de
	call	nz,.dispatch
	pop	de,de,de,de
	add	hl,de
	or	a,a
	sbc	hl,de
	ret	nz
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
usb_MsToCycles:
	pop	de
	ex	(sp), hl
	push	de
.enter:
assert 48000 and $FF = $80
	dec.s	bc
.zbcu:
	ld	c, l
	ld	b, h
	xor	a, a
	srl	b
	rr	c
	rra
	ld	e, 48000 shr 8
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
	pop	hl, de
	ld	l, a
	ret

;-------------------------------------------------------------------------------
usb_GetCycleCounter:
	call	usb_GetCycleCounterHigh
	dec	sp
	dec	sp
	push	hl
	dec	sp
	pop	hl,de
	ld	l,a
	ret

;-------------------------------------------------------------------------------
usb_GetCycleCounterHigh:
	ld	hl,(ti.mpIntInvert+$20) or (ti.intLatch+$20) shl 8
	ld	a,i
	di
	ld	a,(hl)
	push	af
	ld	(hl),.ret
	ld	l,h;ti.intLatch+$20
	ld	de,(hl)
	push	de
	ld	de,.ld_auhl_tmr2Counter
	ld	(hl),de
	ld	iy,ti.mpTmr2Counter+1
.tmrBase := iy-ti.tmr2Counter-1
	lea	hl,.tmrBase+ti.tmr2Counter
virtual at ti.mpIntLatch+$20
	ld	a,(hl)
	ld	hl,(.tmrBase+ti.tmr2Counter+1)
 load .ld_auhl_tmr2Counter: $-$$ from $$
 assert .ld_auhl_tmr2Counter < 1 shl 22
end virtual
virtual at ti.mpIntInvert+$20
	ret
 load .ret: $-$$ from $$
 assert .ret < 1 shl 8
end virtual
	call	ti.mpIntLatch+$20
	ld	iy,ti.mpIntRange+$20
	pop	de
	ld	(iy+ti.intLatch),de
	pop	de
	ld	(iy+ti.intInvert),d
	bit	2,e ; p/v flag
	jq	z,.noEi
	ei
.noEi:
	add	a,3 shl 2
	add	a,3 shl 1
	ret	nc
	inc	l
	ret	nz
	cp	a,3 shl 0
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
	db 7, ENDPOINT_DESCRIPTOR, 0, 0
	dw 8
	db 0
_GetDeviceDescriptor8:
	db DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE, GET_DESCRIPTOR_REQUEST, 0, DEVICE_DESCRIPTOR
	dw 0, 8
_DefaultStandardDescriptors:
	dl .device, .configurations, .langids
	db 2
	dl .strings
.device emit $12: $1201000200000040510408E0200201020003 bswap $12
.configurations dl .configuration1, .configuration2, .configuration3
.configuration1 emit $23: $0902230001010080FA0904000002FF0100000705810240000007050202400000030903 bswap $23
.configuration2 emit $23: $09022300010200C0000904000002FF0100000705810240000007050202400000030903 bswap $23
.configuration3 emit $23: $0902230001030080320904000002FF0100000705810240000007050202400000030903 bswap $23
.langids dw $0304, $0409
.strings dl .string1
.model dl .string84
.string1 dw $033E, 'T','e','x','a','s',' ','I','n','s','t','r','u','m','e','n','t','s',' ','I','n','c','o','r','p','o','r','a','t','e','d'
.string83 dw $0322, 'T','I','-','8','3',' ','P','r','e','m','i','u','m',' ','C','E'
.string84 dw $031C, 'T','I','-','8','4',' ','P','l','u','s',' ','C','E'
