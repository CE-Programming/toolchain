;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'USBDRVCE', 0

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export usb_Init
	export usb_Cleanup
	export usb_HandleEvents
	export usb_WaitForEvents
	export usb_WaitForInterrupt
	export usb_GetDeviceHub
	export usb_SetDeviceData
	export usb_GetDeviceData
	export usb_FindDevice
	export usb_ResetDevice
	export usb_DisconnectDevice
	export usb_GetDeviceAddress
	export usb_GetDeviceSpeed
	export usb_GetConfigurationDescriptorTotalLength
	export usb_GetDescriptor
	export usb_SetDescriptor
	export usb_GetStringDescriptor
	export usb_SetStringDescriptor
	export usb_GetConfiguration
	export usb_SetConfiguration
	export usb_GetInterfaceAlternateSetting
	export usb_SetInterfaceAlternateSetting
	export usb_GetDeviceEndpoint
	export usb_GetEndpointDevice
	export usb_SetEndpointData
	export usb_GetEndpointData
	export usb_GetEndpointMaxPacketSize
	export usb_GetEndpointTransferType
	export usb_SetEndpointFlags
	export usb_GetEndpointFlags
	export usb_ClearEndpointHalt
	export usb_ControlTransfor
	export usb_Transfer
	export usb_ScheduleControlTransfer
	export usb_ScheduleTransfer
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
struc transfer			; transfer structure
	label .: 32
	.next		rd 1	; pointer to next transfer structure
	.altNext	rd 1	; pointer to alternate next transfer structure
	.status		rb 1	; transfer status
	.type		rb 1	; transfer type or 3 shl 2 or last shl 7
	.remaining	rw 1	; transfer remaining length
	label .buffers: 20	; transfer buffers
			rw 1
	.length		rd 1	; original transfer length
	.callback	rd 1	; user callback
	.data		rd 1	; user callback data
	.endpoint	rd 1	; pointer to endpoint structure
			rw 1
	assert $-. = 32
end struc
struc endpoint			; endpoint structure
	label .base: 64
	label .: 64 at $+2
	.next		rd 1	; link to next endpoint structure
	.addr		rb 1	; device addr or cancel shl 7
	.info		rb 1	; ep or speed shl 4 or dtc shl 6
	.maxPktLen	rw 1	; max packet length or c shl 15 or 1 shl 16
	.cur		rd 1	; current transfer pointer
	.overlay	transfer; current transfer

	.type		rb 1	; transfer type
	.dir		rb 1	; transfer dir
	.flags		rb 1	; endpoint flags
	.internalFlags	rb 1	; internal endpoint flags
	.first		rl 1	; pointer to first scheduled transfer
	.last		rl 1	; pointer to last dummy transfer
	.device		rl 1	; pointer to device
	.data		rl 1	; user data
	assert $-. <= 64
end struc
struc device			; device structure
	label .: 32
	.hub		rl 1	; hub this device is connected to
	.find		rb 1	; find flags
	.hubPorts	rb 1	; number of ports in this hub
	.addr		rb 1	; device addr
	.speed		rb 1	; device speed shl 4
	.endpoints	rl 1	; pointer to array of endpoints
		        rb 1
	.info		rw 1	; hub addr or port number shl 7 or 1 shl 14
	.child		rl 1	; first device connected to this hub
	.sibling	rl 1	; next device connected to the same hub
	.data		rl 1	; user data
	assert $-. <= 32
end struc
struc setup
	label .: 8
	.bmRequestType	rb 1
	.bRequest	rb 1
	.wValue		rw 1
	.wIndex		rw 1
	.wLength	rw 1
	assert $-. = 8
end struc
struc stdDesc
	local size
	label .: size
	.device		rl 1
	.configurations	rl 1
	.langids	rl 1
	.numStrings	rb 1
	.strings	rl 1
	size := $-.
end struc
iterate type, transfer, endpoint, device, setup, stdDesc
 iterate <base,name>, 0,, ix-type,x, iy-type,y
  virtual at base
	name#type type
  end virtual
 end iterate
end iterate
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; memory locations
;-------------------------------------------------------------------------------
virtual at (saveSScreen+$FFFF) and not $FFFF
	cHeap			dbx (saveSScreen+21945) and not $FF - $: ?
end virtual
virtual at usbArea
				rb (-$) and 7
	setupPacket		setup
				rb (-$) and 31
	rootDevice		device
				rb (-$) and $FFF
	periodicList		dbx $400: ?
	usbMem			dbx usbInited and not $FF - $: ?
				rb (-$) and 31
	fakeEndpoint		endpoint
	eventCallback		rl 1
	eventCallback.data	rl 1
	standardDescriptors	rl 1
	selectedConfiguration	rb 1
	freeList32Align32	rl 1
	freeList64Align256	rl 1
	assert $ <= usbInited
end virtual
virtual at (ramCodeTop+$FF) and not $FF
	osHeap			dbx heapTop and not $FF - $: ?
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
	USB_ERROR_TIMEOUT	rb 1
	USB_ERROR_FAILED	rb 1
end virtual

; enum usb_event
virtual at 0
	USB_DEVICE_DISCONNECTED_EVENT				rb 1
	USB_DEVICE_CONNECTED_EVENT				rb 1
	USB_DEVICE_DISABLED_EVENT				rb 1
	USB_DEVICE_ENABLED_EVENT				rb 1
	USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT		rb 1
	USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT			rb 1
	USB_DEFAULT_SETUP_EVENT					rb 1
	; Temp debug events:
	USB_DEVICE_INTERRUPT					rb 1
	USB_DEVICE_CONTROL_INTERRUPT				rb 1
	USB_DEVICE_FIFO_INTERRUPT				rb 1
	USB_DEVICE_DEVICE_INTERRUPT				rb 1
	USB_OTG_INTERRUPT					rb 1
	USB_HOST_INTERRUPT					rb 1
	USB_CONTROL_INPUT_INTERRUPT				rb 1
	USB_CONTROL_OUTPUT_INTERRUPT				rb 1
	USB_CONTROL_END_INTERRUPT				rb 1
	USB_CONTROL_ERROR_INTERRUPT				rb 1
	USB_CONTROL_ABORT_INTERRUPT				rb 1
	USB_FIFO0_INPUT_INTERRUPT				rb 1
	USB_FIFO0_OUTPUT_INTERRUPT				rb 1
	USB_FIFO0_SHORT_PACKET_INTERRUPT			rb 1
	USB_FIFO1_INPUT_INTERRUPT				rb 1
	USB_FIFO1_OUTPUT_INTERRUPT				rb 1
	USB_FIFO1_SHORT_PACKET_INTERRUPT			rb 1
	USB_FIFO2_INPUT_INTERRUPT				rb 1
	USB_FIFO2_OUTPUT_INTERRUPT				rb 1
	USB_FIFO2_SHORT_PACKET_INTERRUPT			rb 1
	USB_FIFO3_INPUT_INTERRUPT				rb 1
	USB_FIFO3_OUTPUT_INTERRUPT				rb 1
	USB_FIFO3_SHORT_PACKET_INTERRUPT			rb 1
	USB_DEVICE_RESET_INTERRUPT				rb 1
	USB_DEVICE_SUSPEND_INTERRUPT				rb 1
	USB_DEVICE_RESUME_INTERRUPT				rb 1
	USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT			rb 1
	USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT			rb 1
	USB_DEVICE_ZERO_LENGTH_PACKET_TRANSMIT_INTERRUPT	rb 1
	USB_DEVICE_ZERO_LENGTH_PACKET_RECEIVE_INTERRUPT		rb 1
	USB_DEVICE_DMA_FINISH_INTERRUPT				rb 1
	USB_DEVICE_DMA_ERROR_INTERRUPT				rb 1
	USB_DEVICE_IDLE_INTERRUPT				rb 1
	USB_DEVICE_WAKEUP_INTERRUPT				rb 1
	USB_B_SRP_COMPLETE_INTERRUPT				rb 1
	USB_B_SRP_DETECT_INTERRUPT				rb 1
	USB_A_VBUS_ERROR_INTERRUPT				rb 1
	USB_B_SESSION_END_INTERRUPT				rb 1
	USB_ROLE_CHANGED_INTERRUPT				rb 1
	USB_ID_CHANGED_INTERRUPT				rb 1
	USB_OVERCURRENT_INTERRUPT				rb 1
	USB_B_PLUG_REMOVED_INTERRUPT				rb 1
	USB_A_PLUG_REMOVED_INTERRUPT				rb 1
	USB_INTERRUPT						rb 1
	USB_HOST_ERROR_INTERRUPT				rb 1
	USB_HOST_PORT_CHANGE_DETECT_INTERRUPT			rb 1
	USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT			rb 1
	USB_HOST_SYSTEM_ERROR_INTERRUPT				rb 1
	USB_HOST_ASYNC_ADVANCE_INTERRUPT			rb 1
end virtual

; enum usb_find_flag
SKIP_NONE		:= 0
SKIP_DISABLED		:= 1 shl 0
SKIP_ENABLED		:= 1 shl 1
SKIP_DEVICES		:= 1 shl 2
SKIP_HUBS		:= 1 shl 3
SKIP_ATTACHED		:= 1 shl 4

; enum usb_endpoint_flag
MANUAL_TERMINATE	:= 0 shl 0
AUTO_TERMINATE		:= 1 shl 0

; enum usb_internal_endpoint_flag
PO2_MPS			:= 1 shl 0

; enum usb_transfer_direction
virtual at 0
	HOST_TO_DEVICE				rb 1 shl 7
	DEVICE_TO_HOST				rb 1 shl 7
end virtual

;enum usb_request_type
virtual at 0
	STANDARD_REQUEST			rb 1 shl 5
	CLASS_REQUEST				rb 1 shl 5
	VENDOR_REQUEST				rb 1 shl 5
end virtual

;enum usb_reciipent
virtual at 0
	RECIPIENT_DEVICE			rb 1 shl 0
	RECIPIENT_INTERFACE			rb 1 shl 0
	RECIPIENT_ENDPOINT			rb 1 shl 0
	RECIPIENT_OTHER				rb 1 shl 0
end virtual

; enum usb_request
virtual at 0
	GET_STATUS				rb 1
	CLEAR_FEATURE				rb 1
						rb 1
	SET_FEATURE				rb 1
						rb 1
	SET_ADDRESS				rb 1
	GET_DESCRIPTOR				rb 1
	SET_DESCRIPTOR				rb 1
	GET_CONFIGURATION			rb 1
	SET_CONFIGURATION			rb 1
	GET_INTERFACE				rb 1
	SET_INTERFACE				rb 1
	SYNC_FRAME				rb 1
end virtual

; enum usb_descriptor_type
virtual at 1
	DEVICE_DESCRIPTOR			rb 1
	CONFIGURATION_DESCRIPTOR		rb 1
	STRING_DESCRIPTOR			rb 1
	INTERFACE_DESCRIPTOR			rb 1
	ENDPOINT_DESCRIPTOR			rb 1
end virtual

; enum usb_transfer_type
virtual at 0
	USB_CONTROL_TRANSFER			rb 1
	USB_ISOCHRONOUS_TRANSFER		rb 1
	USB_BULK_TRANSFER			rb 1
	USB_INTERRUPT_TRANSFER			rb 1
end virtual

USB_DEFAULT_RETRIES := 10
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
usb_Init:
	call	_ChkIfOSInterruptAvailable
	rrca
	ld	hl,_DefaultStandardDescriptors.string83
	jq	c,.gotModel
	ld	hl,_DefaultStandardDescriptors.string84
.gotModel:
	ld	(_DefaultStandardDescriptors.model),hl
	ld	a,1
	call	_Init
	set	5,(hl)
	xor	a,a
	sbc	hl,hl
	ld	(rootDevice.data),hl
	ld	l,3
	add	hl,sp
	ld	de,eventCallback
	ld	c,9
	ldir
	ld	e,(hl)
	dec	bc
	ld	hl,(standardDescriptors)
	add	hl,bc
	jq	c,.nonDefaultStandardDescriptors
	ld	hl,_DefaultStandardDescriptors
	ld	(standardDescriptors),hl
.nonDefaultStandardDescriptors:
	ld	hl,mpUsbIdle
	ld	(hl),7
	ld	l,h;usbDevCtrl+1-$100
	ld	(hl),bmUsbDevForceFullSpd shr 8
	dec	l;usbDevCtrl-$100
	ld	(hl),bmUsbDevReset or bmUsbDevEn or bmUsbGirqEn or bmUsbRemoteWake
	ld	l,usbPhyTmsr-$100
	ld	(hl),bmUsbUnplug
	ld	l,usbGimr-$100
	ld	(hl),bmUsbDevIntFifo
	ld	l,usbCxImr-$100
	ld	(hl),a;0
	ld	l,usbFifoRxImr-$100
	ld	(hl),a;0
	ld	l,usbFifoTxImr-$100
	ld	(hl),a;0
	ld	l,usbDevImr-$100
	ld	(hl),a;0
	inc	l;usbDevImr+1-$100
	ld	(hl),bmUsbIntDevIdle shr 8
	dec	h
	ld	l,usbIntEn
	ld	(hl),bmUsbInt or bmUsbIntErr or bmUsbIntPortChgDetect or bmUsbIntFrameListOver or bmUsbIntHostSysErr or bmUsbIntAsyncAdv
	ld	l,usbOtgIer
	ld	(hl),bmUsbIntBSrpComplete or bmUsbIntASrpDetect or bmUsbIntAVbusErr ;or bmUsbIntBSessEnd
	inc	l;usbOtgIer+1
	ld	(hl),(bmUsbIntRoleChg or bmUsbIntIdChg or bmUsbIntOvercurr or bmUsbIntBPlugRemoved or bmUsbIntAPlugRemoved) shr 8
	ld	l,usbImr
	ld	(hl),usbIntLevelHigh
	ld	hl,rootDevice.find
	ld	(hl),SKIP_HUBS or SKIP_ENABLED
	ld	hl,USB_ERROR_INVALID_PARAM
	ld	c,e
	ld	e,1
	ld	d,a;(cHeap-$D10000) shr 8
	ld	b,sizeof cHeap shr 8
	rrc	c
	call	c,.initFreeList
	ld	d,(usbMem-$D10000) shr 8
	ld	b,sizeof usbMem shr 8
	rrc	c
	call	c,.initFreeList
	ld	d,(osHeap-$D10000) shr 8
	ld	b,sizeof osHeap shr 8
	rrc	c
	call	c,.initFreeList
	rrc	c
	ret	nc
	; TODO: disable things here
	ld	d,(periodicList-$D10000) shr 8
	ld	b,sizeof periodicList shr 8
.initFreeList:
	sbc	hl,hl
	add	hl,de
.outer:
	call	_Free64Align256
.inner:
	sub	a,-32
	ld	l,a
	call	c,_Free32Align32
	jq	c,.inner
	inc	h
	djnz	.outer
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_Cleanup:
	xor	a,a
	ld	hl,mpUsbGimr
	ld	(hl),a
	ld	l,usbDevImr+1-$100
	ld	(hl),a
	call	_Init
	res	5,(hl)
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
	ld	hl,mpIntMask+1
	di
	set	bIntUsb-8,(hl)
	ei
	halt
	jq	usb_HandleEvents

;-------------------------------------------------------------------------------
usb_HandleEvents:
.loop:
	or	a,a
	sbc	hl,hl
	ld	a,(mpIntStat+1)
	and	a,intUsb shr 8
	ret	z
	ld	hl,mpUsbIsr
iterate type, Dev, Otg, Host
	bit	bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	ld	a,intUsb shr 8
	ld	(mpIntAck+1),a
	ex	de,hl	; hl = 0
	or	a,a	; zf = 0
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceHub:
	pop	de
	ex	(sp),ydevice
	push	de
	ld	hl,(ydevice.hub)
.maybeReturnNull:
	bit	0,l
	ret	z
.returnZero:
	or	a,a
.returnCarry:
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_SetDeviceData:
	pop	de,ydevice
	ex	(sp),hl
	push	hl
	ld	(ydevice.data),hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceData:
	pop	de
	ex	(sp),ydevice
	push	de
	ld	hl,(ydevice.data)
	ret

;-------------------------------------------------------------------------------
usb_FindDevice:
	pop	de,hl,iy,bc
	push	bc,hl,hl,de
	ld	de,-1
	add	iy,de
	inc	iy
	ex	de,hl
	jq	c,.child
	add	hl,de
	jq	c,.forceChild
	ld	iy,rootDevice
	jq	.check
.child:
	bit	bsf SKIP_ATTACHED,c
	jq	nz,.sibling
.forceChild:
	bit	0,(ydevice.child)
	jq	nz,.sibling
	lea	iy,ydevice.child-device.sibling
	jq	.forceSibling
.hub:
	ld	iy,(ydevice.hub)
	lea	hl,iy
	ld	a,l
	rrca
	jq	c,usb_GetDeviceHub.returnZero
	sbc	hl,de
	ret	z
.sibling:
	bit	0,(ydevice.sibling)
	jq	nz,.hub
.forceSibling:
	ld	iy,(ydevice.sibling)
.check:
	ld	a,(ydevice.find)
	and	a,c
	jq	nz,.child
	lea	hl,iy
	ret

;-------------------------------------------------------------------------------
usb_ResetDevice:
	ld	hl,USB_ERROR_NOT_SUPPORTED
	ret

;-------------------------------------------------------------------------------
usb_DisconnectDevice:
	ld	hl,USB_ERROR_NOT_SUPPORTED
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceAddress:
	pop	hl
	ex	(sp),ydevice
	ld	a,(ydevice.addr)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceSpeed:
	pop	de
	ex	(sp),ydevice
	push	de
	ld	a,(ydevice.speed)
	rrca
	sbc	hl,hl
	ret	c
	rrca
	rrca
	rrca
	ld	l,a
	ret

;-------------------------------------------------------------------------------
usb_GetConfigurationDescriptorTotalLength:
	call	_Error.check
	ret

;-------------------------------------------------------------------------------
usb_GetDescriptor:
	call	_Error.check
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl
	ld	bc,(ix+21)
	push	bc
	ld	bc,USB_DEFAULT_RETRIES
	push	bc
	ld	bc,(ix+15)
	push	bc
	push	hl
	ld	(hl),USB_DEVICE_TO_HOST or USB_STANDARD_REQUEST or USB_RECIPIENT_DEVICE
	inc	l
	ld	(hl),USB_GET_DESCRIPTOR
	inc	l
	ld	a,(ix+12)
	ld	(hl),a
	inc	l
	ld	a,(ix+9)
	ld	(hl),a
	inc	l
	xor	a,a
	ld	(hl),a
	inc	l
	ld	(hl),a
	inc	l
	ld	bc,(ix+18)
	ld	(hl),bc
	ld	iy,(ix+6)
	call	usb_GetDeviceEndpoint.enter
	push	hl
	call	usb_ControlTransfer
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
usb_SetDescriptor:
	call	_Error.check
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl
	ld	bc,0
	push	bc
	ld	c,USB_DEFAULT_RETRIES
	push	bc
	ld	bc,(ix+15)
	push	bc
	push	hl
	ld	(hl),USB_HOST_TO_DEVICE or USB_STANDARD_REQUEST or USB_RECIPIENT_DEVICE
	inc	l
	ld	(hl),USB_SET_DESCRIPTOR
	inc	l
	ld	a,(ix+12)
	ld	(hl),a
	inc	l
	ld	a,(ix+9)
	ld	(hl),a
	inc	l
	xor	a,a
	ld	(hl),a
	inc	l
	ld	(hl),a
	inc	l
	ld	bc,(ix+18)
	ld	(hl),bc
	ld	iy,(ix+6)
	call	usb_GetDeviceEndpoint.enter
	push	hl
	call	usb_ControlTransfer
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
usb_GetStringDescriptor:
	call	_Error.check
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl
	ld	bc,(ix+21)
	push	bc
	ld	bc,USB_DEFAULT_RETRIES
	push	bc
	ld	bc,(ix+15)
	push	bc
	push	hl
	ld	(hl),USB_DEVICE_TO_HOST or USB_STANDARD_REQUEST or USB_RECIPIENT_DEVICE
	inc	l
	ld	(hl),USB_GET_DESCRIPTOR
	inc	l
	ld	a,(ix+9)
	ld	(hl),a
	inc	l
	ld	a,USB_STRING_DESCRIPTOR
	ld	(hl),a
	inc	l
	ld	bc,(ix+12)
	ld	(hl),c
	inc	l
	ld	(hl),b
	inc	l
	ld	bc,(ix+18)
	ld	(hl),bc
	ld	iy,(ix+6)
	xor	a,a
	call	usb_GetDeviceEndpoint.enter
	push	hl
	call	usb_ControlTransfer
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
usb_SetStringDescriptor:
	call	_Error.check
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl
	ld	bc,0
	push	bc
	ld	c,USB_DEFAULT_RETRIES
	push	bc
	ld	bc,(ix+9)
	push	bc
	push	hl
	ld	(hl),USB_DEVICE_TO_HOST or USB_STANDARD_REQUEST or USB_RECIPIENT_DEVICE
	inc	l
	ld	(hl),USB_GET_CONFIGURATION
	inc	l
	xor	a,a
	ld	(hl),a
	inc	l
	ld	(hl),a
	inc	l
	ld	(hl),a
	inc	l
	ld	(hl),a
	inc	l
	ld	(hl),1
	inc	l
	ld	(hl),a
	ld	iy,(ix+6)
	call	usb_GetDeviceEndpoint.enter
	push	hl
	call	usb_ControlTransfer
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
usb_GetConfiguration:
	call	_Error.check
	call	_Alloc32Align32
	jq	nz,_Error.NO_MEMORY
	push	hl
	ld	bc,0
	push	bc
	ld	c,USB_DEFAULT_RETRIES
	push	bc
	ld	de,(ix+15)
	push	de
	push	hl
	ld	(hl),USB_DEVICE_TO_HOST or USB_STANDARD_REQUEST or USB_RECIPIENT_DEVICE
	inc	l
	ld	(hl),USB_GET_CONFIGURATION
	inc	l
	ld	a,(ix+9)
	ld	(hl),a
	inc	l
	ld	a,USB_STRING_DESCRIPTOR
	ld	(hl),a
	inc	l
	ld	bc,(ix+12)
	ld	(hl),c
	inc	l
	ld	(hl),b
	inc	l
	ld	bc,(ix+18)
	ld	(hl),bc
	ld	iy,(ix+6)
	xor	a,a
	call	usb_GetDeviceEndpoint.enter
	push	hl
	call	usb_ControlTransfer
	ex	de,hl
	ld	hl,(ix-6)
	call	_Free32Align32
	ex	de,hl
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
usb_SetConfiguration:
	call	_Error.check
	jq	_Error.NOT_SUPPORTED

;-------------------------------------------------------------------------------
usb_GetInterfaceAlternateSetting:
	call	_Error.check
	jq	_Error.NOT_SUPPORTED

;-------------------------------------------------------------------------------
usb_SetInterfaceAlternateSetting:
	call	_Error.check
	jq	_Error.NOT_SUPPORTED

;-------------------------------------------------------------------------------
usb_GetDeviceEndpoint:
	pop	de,ydevice
	ex	(sp),hl
	push	hl,de
	ld	a,l
	and	a,$8F
.enter:
	ld	hl,(ydevice.endpoints)
	bit	0,l
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
	ld	hl,(yendpoint.device)
	jq	usb_GetDeviceHub.maybeReturnNull

;-------------------------------------------------------------------------------
usb_SetEndpointData:
	pop	de,yendpoint
	ex	(sp),hl
	push	hl
	ld	(yendpoint.data),hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointData:
	pop	de
	ex	(sp),yendpoint
	push	de
	ld	hl,(yendpoint.data)
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointMaxPacketSize:
	pop	de
	ex	(sp),yendpoint
	push	de
	ld	hl,(yendpoint.maxPktLen)
	ld	a,h
	and	a,111b
	ld	h,a
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointTransferType:
	pop	hl
	ex	(sp),yendpoint
	ld	a,(yendpoint.type)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_SetEndpointFlags:
	pop	de,yendpoint
	ex	(sp),hl
	push	hl
	ld	(yendpoint.flags),l
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointFlags:
	pop	hl
	ex	(sp),yendpoint
	ld	a,(yendpoint.flags)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_ClearEndpointHalt:
	call	_Error.check
	jq	_Error.NOT_SUPPORTED

;-------------------------------------------------------------------------------
usb_ControlTransfor:
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
	ld	hl,.callback
	ld	(ix+15),hl
	ld	(ix+18),ix
	call	0
label .dispatch at $-long
load .noBreak from .break
	ld	a,.noBreak
	ld	(.break),a
.wait:
	call	usb_WaitForEvents
	add	hl,de
	or	a,a
	sbc	hl,de
	jq	z,.wait
label .break at $-byte
	ret

.callback:
	ld	hl,12
	add	hl,sp
	ld	iy,(hl)
repeat long
	dec	hl
end repeat
	ld	bc,(hl)
	ex	de,hl
	ld	hl,(iy-9)
	add	hl,de
	or	a,a
	sbc	hl,de
	jq	z,.null
	ld	(hl),bc
.null:
	ex	de,hl
repeat long
	dec	hl
end repeat
	ld	hl,(hl)
	ld	de,-1
	add	hl,de
	jq	c,.fail
	inc	hl
	xor	a,a
	ld	(.break),a
	ret
.fail:
	dec	de
	add	hl,de
	inc	de
	ld	a,USB_ERROR_FAILED
	jq	c,.noRetry
	ld	hl,(iy-6)
	sbc	hl,de
	ret	z
	add	hl,de
	add	hl,de
	ld	(iy-6),hl
	add	hl,de
	sbc	a,a
	cpl
	and	a,USB_ERROR_TIMEOUT
.noRetry:
	ex	de,hl
	inc	hl
	ld	l,a
	ret

;-------------------------------------------------------------------------------
usb_ScheduleControlTransfer.notControl:
	ld	ysetup,(ix+9)
	ld	bc,(ysetup.wLength)
	inc	bc
	dec.s	bc
	ld	de,(ix+12)
	ld	yendpoint,(ix+6)
	jq	usb_ScheduleTransfer.notControl
usb_ScheduleControlTransfer:
	call	_Error.check
.enter:
	ld	yendpoint,(ix+6)
	or	a,(yendpoint.type);USB_CONTROL_TRANSFER
	jq	nz,.notControl
.control:
	ld	a,00001110b
	ld	bc,8
	ld	de,(ix+9)
	call	.queueStage
	ld	ysetup,(ix+9)
	ld	a,(ysetup.bRequest)
	and	a,1 shl 7
	ld	bc,(ysetup.wLength)
	inc.s	bc
	cpi.s
	ld	de,(ix+12)
	rlca
	push	af
	call	pe,_QueueTransfer
	pop	af
	xor	a,10001101b
	ld	bc,1 shl 15
	jq	.queueStage
.queueStage:
	call	_AllocDummyTransfer
	ex	de,hl
	ld	iyl,1
	jq	z,_FillTransfer
	jq	_Error.NO_MEMORY

;-------------------------------------------------------------------------------
usb_ScheduleTransfer.control:
	ld	ysetup,(ix+9)
	lea	de,ysetup+sizeof ysetup
	ld	(ix+12),de
	jq	usb_ScheduleControlTransfer.control
usb_ScheduleTransfer:
	call	_Error.check
.enter:
	ld	yendpoint,(ix+6)
	or	a,(yendpoint.type);USB_CONTROL_TRANSFER
	jq	z,.control
	ld	de,(ix+9)
	ld	bc,(ix+12)
.notControl:
repeat USB_ISOCHRONOUS_TRANSFER
	dec	a
end repeat
	jq	z,_Error.NOT_SUPPORTED
	ld	a,(yendpoint.dir)
	jq	_QueueTransfer

; Input:
;  a = ioc shl 7 or dir
;  bc = length
;  de = buffer
;  (ix+6) = endpoint
;  (ix+15) = handler
;  (ix+18) = data
_QueueTransfer:
	call	_AllocDummyTransfer
	jq	nz,_Error.NO_MEMORY
	ld	(.dummy),hl
	or	a,3 shl 2
	push	af
	sbc	hl,hl
	sbc	hl,bc
	jq	z,.zlp
.next:
	push	de
	ld	a,d
	and	a,$f
	ld	d,a
	ld	hl,$5000
	sbc.s	hl,de
	sbc	hl,bc
	jq	c,.notEnd
	sbc	hl,hl
	bit	bsf AUTO_TERMINATE,(yendpoint.flags)
.notEnd:
	add	hl,bc
	jq	z,.last
	bit	bsf PO2_MPS,(yendpoint.internalFlags)
	jq	nz,.modPo2
	ld	hl,(yendpoint.maxPktLen)
	add	hl,hl
	ld	a,h
	and	a,$f
	ld	h,a
	or	a,l
	jq	z,_Error.INVALID_PARAM
	push	bc,de
	ld	b,0
.modShift:
	inc	b
	add.s	hl,hl
	jq	nc,.modShift
	ex	de,hl
	rr	d
.modLoop:
	rr	e
	or	a,a
	sbc	hl,de
	jq	nc,.modSkip
	add	hl,de
.modSkip:
	srl	d
	djnz	.modLoop
	pop	de,bc
	ex	de,hl
	jq	.modDone
.modPo2:
	inc.s	de
	ld	a,(yendpoint.maxPktLen+0)
	add	a,a
	jq	nz,.modPo2Byte
	ld	a,(yendpoint.maxPktLen+1)
	adc	a,a
	and	a,$f
	dec	a
	and	a,h
	ld	d,a
	ld	e,l
	jq	.modDone
.modPo2Byte:
	dec	a
	and	a,l
	ld	e,a
	ld	d,0
.modDone:
	; hl = transfer length
	; de = transfer length % max packet length
	; bc = total length
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
	call	_AllocDummyTransfer.enter
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
.last:
	pop	de
.zlp:
	pop	af
	and	a,10001101b
	push	hl
	pop	bc
virtual
	ld	iy,0
 load .iyPrefix from $$
end virtual
	ld	iyl,.iyPrefix
label .queue at $-byte
	ld	hl,0
label .dummy at $-long
	set	7,b
	jq	_FillTransfer

; Input:
;  a = ioc shl 7 or 3 shl 2 or pid
;  bc = dt shl 15 or length
;  de = next
;  hl = buffer
;  iy = alt next
;  (ix+6) = endpoint
;  (ix+15) = handler
;  (ix+18) = data
_FillTransfer:
	push	hl,iy
	ld	yendpoint,(ix+6)
	ld	hl,(yendpoint.last)
	ld	(hl),de
assert ~transfer.altNext and (transfer.altNext-1)
	set	bsf transfer.altNext, hl
	pop	de
	ld	(hl),de
repeat transfer.type-transfer.altNext
	inc	hl
end repeat
	ld	(hl),a
repeat transfer.remaining-transfer.type
	inc	hl
end repeat
	ld	(hl),c
	inc	hl
	ld	(hl),b
	inc	hl
	pop	de
	ld	(hl),de
	dec	sp
	push	de
	inc	sp
	pop	de
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),c
	inc	hl
	ld	(hl),b
	call	.packHalf
	ld	bc,(ix+15)
	call	.pack
	ld	bc,(ix+18)
	call	.pack
	lea	bc,iy
	call	.pack
	ld	(hl),d
	ld	a,l
	sub	a,transfer.status-transfer.endpoint-1
	ld	l,a
	ld	(hl),1 shl 7
	ret
.pack:
	ld	a,d
	xor	a,c
	and	a,$f
	xor	a,c
	ld	(hl),bc
	ld	(hl),a
	inc	hl
	inc	hl
.packHalf:
	inc	hl
	ld	a,e
	or	a,$f
	ld	e,a
	inc	de
	ld	a,c
	xor	a,e
	and	a,$f
	xor	a,e
	ld	(hl),a
	inc	hl
	ret

;-------------------------------------------------------------------------------
element error
label _Error at error

iterate error, SYSTEM, INVALID_PARAM, SCHEDULE_FULL, NO_DEVICE, NO_MEMORY, NOT_SUPPORTED, TIMEOUT, FAILED

.error:
	ld	a,USB_ERROR_#error
	jq	.return

end iterate

.check:
	pop	de
	call	__frameset0
	ld	a,(mpIntMask)
	and	a,intTmr3
	jq	nz,.SYSTEM
	ld	a,(mpUsbSts)
	and	a,bmUsbIntHostSysErr
	jq	nz,.SYSTEM
	ld	a,(usbInited)
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
	ld	sp,ix
	pop	ix
	ret

_Init:
	ld	bc,usbInited-usbArea
	ld	de,usbInited
	ld	hl,mpUsbCmd
	ld	(de),a
	ld	(hl),h
	ld	l,usbSts+1
.wait:
	bit	bUsbHcHalted-8,(hl)
	jq	z,.wait
	scf
	sbc	hl,hl
	add	hl,de
	ex	de,hl
	lddr
	ld	hl,flags+$1B
	ret

;-------------------------------------------------------------------------------
_PowerVbus:
	call	$21B70
	ld	hl,mpUsbOtgCsr
	res	5,(hl)
	set	4,(hl)
	ret

;-------------------------------------------------------------------------------
_UnpowerVbus:
	ld	hl,mpUsbOtgCsr
	res	7,(hl)
	set	5,(hl)
	res	4,(hl)
	ret

;-------------------------------------------------------------------------------
_DefaultEventCallback:
	ld	hl,USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
iterate <size,align>, 32,32, 64,256

; Allocates an <align> byte aligned <size> byte block.
; Output:
;  zf = enough memory
;  hl = allocated memory
_Alloc#size#Align#align:
	ld	hl,(freeList#size#Align#align)
	bit	0,l
	ret	nz
	push	hl
	ld	hl,(hl)
	ld	(freeList#size#Align#align),hl
	pop	hl
	ret

; Frees an <align> byte aligned <size> byte block.
; Input:
;  hl = allocated memory to be freed.
_Free#size#Align#align:
	push	de
	ld	de,(freeList#size#Align#align)
	ld	(hl),de
	ld	(freeList#size#Align#align),hl
	pop	de
	ret

end iterate

; Input:
;  (ix+6) = endpoint
; Output:
;  zf = enough memory
;  hl = transfer
_AllocDummyTransfer:
	ld	iy,(ix+6)
.enter:
	call	_Alloc32Align32
	ret	nz
assert ~transfer.status and (transfer.status - 1)
	set	bsf transfer.status,hl
	ld	(hl),1 shl 6
	res	bsf transfer.status,hl
	ret

;-------------------------------------------------------------------------------
_FunData:
repeat 256
	db % and $FF
end repeat

_HandleTestOutRequest:
	ld	hl,_FunData
	ld	bc,256
	call	_MemClear
	ld	bc,64
	ld	de,_FunData
	ld	hl,mpUsbCxFifo
	set	bCxFifoClr,(hl)
	ld	l,usbCxIsr-$100
.waitOut:
	bit	bUsbIntCxOut,(hl)
	jq	z,.waitOut
	ld	(hl),bmUsbIntCxOut
	ld	l,usbCxFifo+3-$100
	ld	bc,0
	ld	c,(hl)
	ld	de,_FunData
	ld	l,usbDmaCtrl-$100
	ld	(hl),usbDmaFifo2Mem or bmUsbDmaClrFifo
	inc	l;usbDmaLen-$100
	ld	(hl),bc
	ld	l,usbDmaFifo-$100
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbDmaAddr-$100
	ld	(hl),de
	ld	l,usbDmaCtrl-$100
	set	bUsbDmaStart,(hl)
	ld	l,usbDevIsr-$100
.waitDma:
	inc	l
	bit	bUsbIntDevDmaErr-8,(hl)
	jq	nz,.waitDmaDone
	dec	l
	bit	bUsbIntDevDmaFin,(hl)
	jq	z,.waitDma
.waitDmaDone:
	ld	(hl),bmUsbIntDevDmaFin
	inc	l
	ld	(hl),bmUsbIntDevDmaErr shr 8
	xor	a,a
	ld	l,usbDmaFifo-$100
	ld	(hl),a;bmUsbDmaNoFifo
	ld	l,usbCxIsr-$100
.waitEnd:
	bit	bUsbIntCxEnd,(hl)
	jq	nz,.waitEndDone
	bit	bUsbIntCxErr,(hl)
	jq	z,.waitEnd
.waitEndDone:
	ld	(hl),bmUsbIntCxEnd or bmUsbIntCxErr
	ld	l,usbCxFifo-$100
	set	bCxFifoFin,(hl)
	ld	l,usbCxIsr-$100
	ld	(hl),bmUsbIntCxSetup
	ld	a,102
	jq	_DispatchEvent

_HandleTestInRequest:
	push	ix
	ld	ix,0
	ld	iy,mpTmrRange
	ld	bc,64
	ld	de,_FunData
	ld	hl,mpUsbCxFifo
	set	bCxFifoClr,(hl)
	ld	l,usbDmaCtrl-$100
	ld	(hl),usbDmaMem2Fifo or bmUsbDmaClrFifo
	inc	l;usbDmaLen-$100
	ld	(hl),bc
	ld	l,usbDmaFifo-$100
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbDmaAddr-$100
	ld	(hl),de
	ld	l,usbDmaCtrl-$100
	set	bUsbDmaStart,(hl)
	ld	l,usbDevIsr-$100
.waitDma:
	bit	bUsbIntDevDmaFin,(hl)
	jq	z,.waitDma
	ld	(hl),bmUsbIntDevDmaFin
	xor	a,a
	ld	l,usbDmaFifo-$100
	ld	(hl),a;bmUsbDmaNoFifo
if 0 ; Single packet
	ld	l,usbCxFifo-$100
	set	bCxFifoFin,(hl)
else
	ld	l,usbCxIsr-$100
.waitIn:
	bit	bUsbIntCxIn,(hl)
	jq	z,.waitIn
	ld	(hl),bmUsbIntCxIn
	; second packet
	ld	bc,64
	ld	de,_FunData+64
	ld	l,usbDmaCtrl-$100
	ld	(hl),usbDmaMem2Fifo or bmUsbDmaClrFifo
	inc	l;usbDmaLen-$100
	ld	(hl),bc
	ld	l,usbDmaFifo-$100
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbDmaAddr-$100
	ld	(hl),de
	ld	l,usbDmaCtrl-$100
	set	bTmr2Enable,(iy+tmrCtrl)
	set	bUsbDmaStart,(hl)
	ld	l,usbDevIsr-$100
.waitDma2:
	bit	bUsbIntDevDmaFin,(hl)
	jq	z,.waitDma2
	res	bTmr2Enable,(iy+tmrCtrl)
	ld	(hl),bmUsbIntDevDmaFin
	ld	l,usbCxFifo-$100
	set	bCxFifoFin,(hl)
	xor	a,a
	ld	l,usbDmaFifo-$100
	ld	(hl),a;bmUsbDmaNoFifo
;	ld	l,usbCxIsr-$100
;.waitIn2:
;	bit	bUsbIntCxIn,(hl)
;	jq	z,.waitIn2
;	ld	(hl),bmUsbIntCxIn
end if
	ld	l,usbCxIsr-$100
	ld	(hl),bmUsbIntCxSetup
	pop	ix
	ld	a,101
	jq	_DispatchEvent
	ret

	ld	l,usbCxIsr-$100
.wait:
	bit	bUsbIntCxIn,(hl)
	jq	z,.wait
	ld	(hl),bmUsbIntCxIn
	ld	l,usbCxIsr-$100
	ld	(hl),bmUsbIntCxSetup
	xor	a,a
	ret

second:
	ld	bc,30
	ld	de,_FunData+64

	ld	hl,mpUsbCxFifo
	set	bCxFifoClr,(hl)
	ld	l,usbDmaFifo-$100
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbDmaAddr-$100
	ld	(hl),de
	ld	l,usbDmaCtrl-$100
	ld	a,(setupPacket.bmRequestType)
	rlca
	rlca
	xor	a,(hl)
	and	a,usbDmaMem2Fifo
	xor	a,(hl)
	ld	(hl),a
	inc	l;usbDmaLen-$100
;	ex	de,hl
;	ld	hl,(setupPacket.wLength)
;	sbc.s	hl,bc
;	jq	c,.min
;	sbc	hl,hl
;.min:
;	add.s	hl,bc
;	ex	de,hl
	ld	(hl),bc
	dec	l;usbDmaCtrl-$100
	set	bUsbDmaStart,(hl)

	ld	l,usbCxFifo-$100
	set	bCxFifoFin,(hl)
	ld	l,usbCxIsr-$100
	ld	(hl),bmUsbIntCxSetup
	xor	a,a
	ret

	ld	l,usbCxIsr-$100
.wait:
	bit	bUsbIntCxIn,(hl)
	jq	z,.wait
	ld	(hl),bmUsbIntCxIn
	xor	a,a
	ld	l,usbDmaFifo-$100
	ld	(hl),a

	ld	l,usbCxFifo-$100
	set	bCxFifoFin,(hl)
	ld	l,usbCxIsr-$100
	ld	(hl),bmUsbIntCxSetup
	ret

sendDescriptor:
	ld	hl,mpUsbCxFifo
	set	bCxFifoClr,(hl)
	ld	l,usbDmaFifo-$100
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbDmaAddr-$100
	ld	(hl),de
	ld	l,usbDmaCtrl-$100
	ld	a,(setupPacket.bmRequestType)
	rlca
	rlca
	xor	a,(hl)
	and	a,usbDmaMem2Fifo
	xor	a,(hl)
	ld	(hl),a
	inc	l;usbDmaLen-$100
	ex	de,hl
	ld	hl,(setupPacket.wLength)
	sbc.s	hl,bc
	jq	c,.min
	sbc	hl,hl
.min:
	add.s	hl,bc
	ex	de,hl
	ld	(hl),de
	dec	l;usbDmaCtrl-$100
	set	bUsbDmaStart,(hl)
	ld	l,usbCxIsr-$100
.wait:
	bit	bUsbIntCxIn,(hl)
	jq	z,.wait
	ld	(hl),bmUsbIntCxIn
	xor	a,a
	ld	l,usbDmaFifo-$100
	ld	(hl),a
	ret

;-------------------------------------------------------------------------------
_HandleGetDescriptor:
	ld	de,(ysetup.wIndex)
	ld	bc,(ysetup.wValue)
	inc	bc
	dec.s	bc
	ld	iy,(standardDescriptors)
	djnz	.notDevice;DEVICE_DESCRIPTOR
	or	a,c
	or	a,e
	or	a,d
	jq	nz,_HandleCxSetupInt.unhandled
.sendSingleDescriptorIYind:
	ld	b,a
	ld	hl,(iy);(ystdDesc.device)
.sendSingleDescriptorHL:
	ld	c,(hl)
	ex	de,hl
	jq	.sendDescriptor
.notDevice:
	djnz	.notConfiguration;CONFIGURATION_DESCRIPTOR
	or	a,e
	or	a,d
	jq	nz,_HandleCxSetupInt.unhandled
	ld	hl,(ystdDesc.configurations)
	ld	iy,(ystdDesc.device)
	ld	a,c
	cp	a,(iy+17)
	jq	nc,_HandleCxSetupInt.unhandled
repeat 3
	add	hl,bc
end repeat
	ld	iy,(hl)
	ld	bc,(iy+2)
	ld	de,(hl)
	jq	.sendDescriptor
.notConfiguration:
	djnz	.notString;STRING_DESCRIPTOR
	ld	hl,(ystdDesc.langids)
	cp	a,c
	jq	z,.langids
	ld	a,(ystdDesc.numStrings)
	cp	a,c
	jq	c,_HandleCxSetupInt.unhandled
	ld	iy,(ystdDesc.strings)
	ld	a,(hl)
	rra
	dec	a
	ld	b,a
	dec	c
	mlt	bc
repeat 3
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
	jq	_HandleCxSetupInt.unhandled

;	ld	hl,(standardDescriptors)
;	ld	iy,(hl+stdDesc.device)
;	ld	a,(iy+7);bMaxPacketSize0
.sendDescriptor:
	ld	hl,mpUsbCxFifo
	set	bCxFifoClr,(hl)
	ld	l,usbDmaFifo-$100
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbDmaAddr-$100
	ld	(hl),de
	ld	l,usbDmaCtrl-$100
	ld	a,(setupPacket.bmRequestType)
	rlca
	rlca
	xor	a,(hl)
	and	a,usbDmaMem2Fifo
	xor	a,(hl)
	ld	(hl),a
	inc	l;usbDmaLen-$100
	ex	de,hl
	ld	hl,(setupPacket.wLength)
	sbc.s	hl,bc
	jq	c,.min
	sbc	hl,hl
.min:
	add.s	hl,bc
	ex	de,hl
	ld	(hl),de
	dec	l;usbDmaCtrl-$100
	set	bUsbDmaStart,(hl)
	ld	l,usbDevIsr-$100
.wait:
	bit	bUsbIntDevDmaFin,(hl)
	jq	z,.wait
	ld	(hl),bmUsbIntDevDmaFin
	xor	a,a
	ld	l,usbDmaFifo-$100
	ld	(hl),a
	jq	_HandleCxSetupInt.handled

_HandleCxSetupInt:
	ld	iy,setupPacket-4
	ld	l,usbDmaFifo-$100
	ld	b,4
	ld	a,i
	di
	ld	(hl),bmUsbDmaCxFifo
	ld	l,usbEp0Data-$100
.fetch:
	ld	a,(hl)
	ld	(iy+4),a
	ld	a,(hl)
	ld	(iy+8),a
	inc	hl
	inc	iy
	djnz	.fetch
	ld	l,usbDmaFifo-$100
	jp	po,.noEi
	ei
.noEi:
	ld	(hl),b;bmUsbDmaNoFifo
	ld	bc,(ysetup.bmRequestType)
	inc	b
	djnz	.notGetStatus
	ld	a,c
	sub	a,DEVICE_TO_HOST or VENDOR_REQUEST or RECIPIENT_DEVICE
	jq	z,_HandleTestInRequest
	ld	a,c
	sub	a,HOST_TO_DEVICE or VENDOR_REQUEST or RECIPIENT_DEVICE
	jq	z,_HandleTestOutRequest
.notGetStatus:
	djnz	.notClearFeature
.notClearFeature:
	dec	b
	djnz	.notSetFeature
.notSetFeature:
	dec	b
	djnz	.notSetAddress
	ld	de,(ysetup.wValue)
	ld	a,e
	and	a,$80
	or	a,d
	or	a,c
	ld	bc,(ysetup.wIndex)
	or	a,c
	or	a,b
	ld	bc,(ysetup.wLength)
	or	a,c
	or	a,b
	jq	nz,_HandleCxSetupInt.unhandled
	ld	l,usbDevAddr-$100
	ld	(hl),e
	jq	_HandleCxSetupInt.handled
.notSetAddress:
	djnz	.notGetDescriptor
	ld	a,c
	sub	a,DEVICE_TO_HOST or STANDARD_REQUEST or RECIPIENT_DEVICE
	jq	z,_HandleGetDescriptor
.notGetDescriptor:
	djnz	.notSetDescriptor
.notSetDescriptor:
	djnz	.notGetConfiguration
.notGetConfiguration:
	djnz	.notSetConfiguration
	ld	de,(ysetup.wValue)
	ld	a,d
	or	a,c
	ld	bc,(ysetup.wIndex)
	or	a,c
	or	a,b
	ld	bc,(ysetup.wLength)
	or	a,c
	or	a,b
	jq	nz,_HandleCxSetupInt.unhandled
	cpl
	add	a,e
	ld	l,usbDevAddr-$100
	ld	a,(hl)
	rla
	rrca
	ld	(hl),a
	jq	_HandleCxSetupInt.handled
.notSetConfiguration:
	djnz	.notGetInterface
.notGetInterface:
	djnz	.notSetInterface
.notSetInterface:
.unhandled:
	ld	de,setupPacket
	ld	a,USB_DEFAULT_SETUP_EVENT
	call	_DispatchEvent
	jq	z,.handled
	add	hl,de
	scf
	sbc	hl,de
	inc	hl
	ret	nz
	add	hl,de
	ld	hl,mpUsbCxFifo
	set	bCxFifoStall,(hl)
	jq	.return
.handled:
	ld	l,usbCxFifo-$100
	set	bCxFifoFin,(hl)
.return:
	ld	l,usbCxIsr-$100
	ld	(hl),bmUsbIntCxSetup
	ret

_HandleDevInt:
	ld	l,usbGisr-$100
	inc	h
iterate type, Cx, Dev; Dev, Fifo, Cx
	bit	bUsbDevInt#type,(hl)
	call	nz,_HandleDev#type#Int
	ret	nz
end iterate
	ld	l,usbIsr
	dec	h
	ld	(hl),bmUsbIntDev
	ld	a,USB_DEVICE_INTERRUPT
	jq	_DispatchEvent

_HandleDevCxInt:
	ld	l,usbCxIsr-$100
iterate type, Setup, In, Out, End, Err, Abort
	bit	bUsbIntCx#type,(hl)
	call	nz,_HandleCx#type#Int
	ret	nz
end iterate
	ld	l,usbGisr-$100
	ld	(hl),bmUsbDevIntCx
	ld	a,USB_DEVICE_CONTROL_INTERRUPT
	jq	_DispatchEvent

_HandleDevFifoInt:
	ld	l,usbFifoRxIsr-$100
repeat 4, fifo: 0
 iterate type, Out, Spk
	bit	bUsbIntFifo#fifo#type,(hl)
	call	nz,_HandleFifo#fifo#type#Int
	ret	nz
 end iterate
end repeat
	ld	l,usbFifoTxIsr-$100
repeat 4, fifo: 0
 iterate type, In
	bit	bUsbIntFifo#fifo#type,(hl)
	call	nz,_HandleFifo#fifo#type#Int
	ret	nz
 end iterate
end repeat
	ld	l,usbGisr-$100
	ld	(hl),bmUsbDevIntFifo
	ld	a,USB_DEVICE_FIFO_INTERRUPT
	jq	_DispatchEvent

_HandleDevDevInt:
	ld	l,usbDevIsr-$100
iterate type, Reset, Suspend, Resume, IsocErr, IsocAbt, ZlpTx, ZlpRx, DmaFin
	bit	bUsbIntDev#type,(hl)
	call	nz,_HandleDev#type#Int
	ret	nz
end iterate
	inc	l;usbDevIsr+1-$100
iterate type, DmaErr, Idle, Wakeup
	bit	bUsbIntDev#type-8,(hl)
	call	nz,_HandleDev#type#Int
	ret	nz
end iterate
	ld	l,usbGisr-$100
	ld	(hl),bmUsbDevIntDev
	ld	a,USB_DEVICE_DEVICE_INTERRUPT
	jq	_DispatchEvent

_HandleOtgInt:
	ld	l,usbOtgIsr
iterate type, BSrpComplete, ASrpDetect, AVbusErr, BSessEnd
	bit	bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	inc	l;usbOtgIsr+1
iterate type, RoleChg, IdChg, Overcurr, BPlugRemoved, APlugRemoved
	bit	bUsbInt#type-8,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	ld	l,usbIsr
	ld	(hl),bmUsbIntOtg
	ld	a,USB_OTG_INTERRUPT
	jq	_DispatchEvent

_HandleHostInt:
	ld	l,usbSts
iterate type, , Err, PortChgDetect, FrameListOver, HostSysErr
	bit	bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
	ret	nz
end iterate
	ld	l,usbIsr
	ld	(hl),bmUsbIntHost
	ld	a,USB_HOST_INTERRUPT
	jq	_DispatchEvent

_HandleCxInInt:
	ld	(hl),bmUsbIntCxIn
	ld	a,USB_CONTROL_INPUT_INTERRUPT
	jq	_DispatchEvent

_HandleCxOutInt:
	ld	(hl),bmUsbIntCxOut
	ld	a,USB_CONTROL_OUTPUT_INTERRUPT
	jq	_DispatchEvent

_HandleCxEndInt:
	ld	(hl),bmUsbIntCxEnd
	ld	a,USB_CONTROL_END_INTERRUPT
	jq	_DispatchEvent

_HandleCxErrInt:
	ld	(hl),bmUsbIntCxErr
	ld	a,USB_CONTROL_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleCxAbortInt:
	ld	(hl),bmUsbIntCxAbort
	ld	a,USB_CONTROL_ABORT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo0OutInt:
	ld	(hl),bmUsbIntFifo0Out
	ld	a,USB_FIFO0_OUTPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo0SpkInt:
	ld	(hl),bmUsbIntFifo0Spk
	ld	a,USB_FIFO0_SHORT_PACKET_INTERRUPT
	jq	_DispatchEvent

_HandleFifo1OutInt:
	ld	(hl),bmUsbIntFifo1Out
	ld	a,USB_FIFO1_OUTPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo1SpkInt:
	ld	(hl),bmUsbIntFifo1Spk
	ld	a,USB_FIFO1_SHORT_PACKET_INTERRUPT
	jq	_DispatchEvent

_HandleFifo2OutInt:
	ld	(hl),bmUsbIntFifo2Out
	ld	a,USB_FIFO2_OUTPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo2SpkInt:
	ld	(hl),bmUsbIntFifo2Spk
	ld	a,USB_FIFO2_SHORT_PACKET_INTERRUPT
	jq	_DispatchEvent

_HandleFifo3OutInt:
	ld	(hl),bmUsbIntFifo3Out
	ld	a,USB_FIFO3_OUTPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo3SpkInt:
	ld	(hl),bmUsbIntFifo3Spk
	ld	a,USB_FIFO3_SHORT_PACKET_INTERRUPT
	jq	_DispatchEvent

_HandleFifo0InInt:
	ld	(hl),bmUsbIntFifo0In
	ld	a,USB_FIFO0_INPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo1InInt:
	ld	(hl),bmUsbIntFifo1In
	ld	a,USB_FIFO1_INPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo2InInt:
	ld	(hl),bmUsbIntFifo2In
	ld	a,USB_FIFO2_INPUT_INTERRUPT
	jq	_DispatchEvent

_HandleFifo3InInt:
	ld	(hl),bmUsbIntFifo3In
	ld	a,USB_FIFO3_INPUT_INTERRUPT
	jq	_DispatchEvent

_HandleDevResetInt:
	xor	a,a
	ld	(selectedConfiguration),a
	ld	(mpUsbDevAddr),a
	ld	l,usbDmaCtrl-$100
	ld	(hl),bmUsbDmaClrFifo or bmUsbDmaAbort
	ld	l,usbCxFifo-$100
	set	bCxFifoClr,(hl)
	ld	l,usbDevIsr-$100
	ld	(hl),bmUsbIntDevReset
	ld	a,USB_DEVICE_RESET_INTERRUPT
	jq	_DispatchEvent

_HandleDevSuspendInt:
	ld	(hl),bmUsbIntDevSuspend
	ld	a,USB_DEVICE_SUSPEND_INTERRUPT
	jq	_DispatchEvent

_HandleDevResumeInt:
	ld	(hl),bmUsbIntDevResume
	ld	a,USB_DEVICE_RESUME_INTERRUPT
	jq	_DispatchEvent

_HandleDevIsocErrInt:
	ld	(hl),bmUsbIntDevIsocErr
	ld	a,USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleDevIsocAbtInt:
	ld	(hl),bmUsbIntDevIsocAbt
	ld	a,USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT
	jq	_DispatchEvent

_HandleDevZlpTxInt:
	ld	(hl),bmUsbIntDevZlpTx
	ld	a,USB_DEVICE_ZERO_LENGTH_PACKET_TRANSMIT_INTERRUPT
	jq	_DispatchEvent

_HandleDevZlpRxInt:
	ld	(hl),bmUsbIntDevZlpRx
	ld	a,USB_DEVICE_ZERO_LENGTH_PACKET_RECEIVE_INTERRUPT
	jq	_DispatchEvent

_HandleDevDmaFinInt:
	ld	(hl),bmUsbIntDevDmaFin
	ld	a,USB_DEVICE_DMA_FINISH_INTERRUPT
	jq	_DispatchEvent

_HandleDevDmaErrInt:
	ld	(hl),bmUsbIntDevDmaErr shr 8
	ld	a,USB_DEVICE_DMA_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleDevIdleInt:
	ld	(hl),bmUsbIntDevIdle shr 8
	ld	a,USB_DEVICE_IDLE_INTERRUPT
	jq	_DispatchEvent

_HandleDevWakeupInt:
	ld	l,usbPhyTmsr-$100
	res	bUsbUnplug,(hl)
	ld	l,usbDevIsr+1-$100
	ld	(hl),bmUsbIntDevWakeup shr 8
	ld	a,USB_DEVICE_WAKEUP_INTERRUPT
	jq	_DispatchEvent

_HandleBSrpCompleteInt:
	ld	(hl),bmUsbIntBSrpComplete
	ld	a,USB_B_SRP_COMPLETE_INTERRUPT
	jq	_DispatchEvent

_HandleASrpDetectInt:
	ld	(hl),bmUsbIntASrpDetect
	ld	a,USB_B_SRP_DETECT_INTERRUPT
	jq	_DispatchEvent

_HandleAVbusErrInt:
	ld	(hl),bmUsbIntAVbusErr
	ld	a,USB_A_VBUS_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleBSessEndInt:
	ld	(hl),bmUsbIntBSessEnd
	ld	a,USB_B_SESSION_END_INTERRUPT
	jq	_DispatchEvent

_HandleRoleChgInt:
	ld	(hl),bmUsbIntRoleChg shr 8
	ld	a,USB_ROLE_CHANGED_INTERRUPT
	jq	_DispatchEvent

_HandleIdChgInt:
	ld	(hl),bmUsbIntIdChg shr 8
	ld	a,USB_ID_CHANGED_INTERRUPT
	jq	_DispatchEvent

_HandleOvercurrInt:
	ld	(hl),bmUsbIntOvercurr shr 8
	ld	a,USB_OVERCURRENT_INTERRUPT
	jq	_DispatchEvent

_HandleBPlugRemovedInt:
	ld	(hl),bmUsbIntBPlugRemoved shr 8
	ld	a,USB_B_PLUG_REMOVED_INTERRUPT
	jq	_DispatchEvent

_HandleAPlugRemovedInt:
	ld	(hl),bmUsbIntAPlugRemoved shr 8
	ld	a,USB_A_PLUG_REMOVED_INTERRUPT
	jq	_DispatchEvent

_HandleInt:
	ld	(hl),bmUsbInt
	ld	a,USB_INTERRUPT
	jq	_DispatchEvent

_HandleErrInt:
	ld	(hl),bmUsbIntErr
	ld	a,USB_HOST_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandlePortChgDetectInt:
	ld	(hl),bmUsbIntPortChgDetect
	ld	a,USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT
	jq	_DispatchEvent

_HandleFrameListOverInt:
	ld	(hl),bmUsbIntFrameListOver
	ld	a,USB_HOST_SYSTEM_ERROR_INTERRUPT
	jq	_DispatchEvent

_HandleHostSysErrInt:
	ld	(hl),bmUsbIntHostSysErr
	ld	a,USB_HOST_ASYNC_ADVANCE_INTERRUPT
	jq	_DispatchEvent

;-------------------------------------------------------------------------------
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
.dispatch:
	jp	(hl)

;-------------------------------------------------------------------------------
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
.model dl 0
.string1 dw $033E, 'T','e','x','a','s',' ','I','n','s','t','r','u','m','e','n','t','s',' ','I','n','c','o','r','p','o','r','a','t','e','d'
.string83 dw $0322, 'T','I','-','8','3',' ','P','r','e','m','i','u','m',' ','C','E'
.string84 dw $031C, 'T','I','-','8','4',' ','P','l','u','s',' ','C','E'
