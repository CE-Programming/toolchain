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
	export usb_GetDeviceEndpoint
	export usb_GetEndpointDevice
	export usb_SetEndpointData
	export usb_GetEndpointData
	export usb_GetEndpointMaxPacketSize
	export usb_GetEndpointTransferType
	export usb_SetEndpointFlags
	export usb_GetEndpointFlags
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
	.callback	rd 1	; user callback
	.data		rd 1	; user callback data
	.length		rd 1	; original transfer length
	.endpoint	rd 1	; pointer to endpoint structure
			rw 1
	assert $-. = 32
end struc
struc endpoint			; endpoint structure
	label .: 64 at $-2
	.next		rd 1	; link to next endpoint structure
	.addr		rb 1	; device addr or cancel shl 7
	.info		rb 1	; ep or speed shl 4 or dtc shl 6
	.maxPktLen	rw 1	; max packet length or c shl 15 or 1 shl 16
	.cur		rd 1	; current transfer pointer
	.overlay	transfer; current transfer

	.type		rb 1	; transfer type
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
iterate type, endpoint, device, setup, stdDesc
 iterate <base,name>, 0,, ix,x, iy,y
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
AUTO_TERMINATE		:= 0 shl 0
MANUAL_TERMINATE	:= 1 shl 0

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

;-------------------------------------------------------------------------------
usb_WaitForInterrupt:
	ld	hl,mpIntMask+1
	di
	set	bIntUsb-8,(hl)
	ei
	halt

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
	ex	(sp),iy
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
	pop	de,iy
	ex	(sp),hl
	push	hl
	ld	(ydevice.data),hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceData:
	pop	de
	ex	(sp),iy
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
	ex	(sp),iy
	ld	a,(ydevice.addr)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceSpeed:
	pop	de
	ex	(sp),iy
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
usb_GetDeviceEndpoint:
	pop	de,iy
	ex	(sp),hl
	push	hl,de
	ld	a,l
	ld	hl,(ydevice.endpoints)
	bit	0,l
	jq	nz,usb_GetDeviceHub.returnZero
	rlca
	and	a,$1F
	or	a,l
	ld	l,a
	ld	h,(hl)
	ld	l,endpoint
	ld	a,h
	inc	a
	ret	nz
	jq	usb_GetDeviceHub.returnCarry

;-------------------------------------------------------------------------------
usb_GetEndpointDevice:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(yendpoint.device)
	jq	usb_GetDeviceHub.maybeReturnNull

;-------------------------------------------------------------------------------
usb_SetEndpointData:
	pop	de,iy
	ex	(sp),hl
	push	hl
	ld	(yendpoint.data),hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointData:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(yendpoint.data)
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointMaxPacketSize:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(yendpoint.maxPktLen)
	ld	a,h
	and	a,111b
	ld	h,a
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointTransferType:
	pop	hl
	ex	(sp),iy
	ld	a,(yendpoint.type)
	jp	(hl)

;-------------------------------------------------------------------------------
usb_SetEndpointFlags:
	pop	de,iy
	ex	(sp),hl
	push	hl
	ld	(yendpoint.flags),l
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetEndpointFlags:
	pop	hl
	ex	(sp),iy
	ld	a,(yendpoint.flags)
	jp	(hl)

_Check:
	call	.check
	ret	z
	pop	hl
	ld	hl,USB_ERROR_SYSTEM
	ret
.check:
	ld	a,(mpIntMask)
	and	a,intTmr3
	ret	nz
	ld	a,(mpUsbSts)
	and	a,bmUsbIntHostSysErr
	ret	nz
	ld	a,(usbInited)
	dec	a
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

_PowerVbus:
	call	$21B70
	ld	hl,mpUsbOtgCsr
	res	5,(hl)
	set	4,(hl)
	ret

_UnpowerVbus:
	ld	hl,mpUsbOtgCsr
	res	7,(hl)
	set	5,(hl)
	res	4,(hl)
	ret

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
	ld	l,usbDmaCtrl-$100
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
	jp	po,.noEI
	ei
.noEI:
	ld	(hl),b;bmUsbDmaNoFifo
	ld	bc,(ysetup.bmRequestType)
	inc	b
	djnz	.notGetStatus
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
iterate type, Dev, Fifo, Cx
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
