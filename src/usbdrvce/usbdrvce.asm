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
iterate type, endpoint, device
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
	setupPacket		dbx 8: ?
				rb (-$) and 31
	rootDevice		device
				rb (-$) and $FFF
	periodicList		dbx $400: ?
	usbMem			dbx usbInited and not $FF - $: ?
				rb (-$) and 31
	fakeEndpoint		endpoint
	eventCallback		rl 1
	eventCallback.data	rl 1
	fullSpeedDescriptors	rl 1
	highSpeedDescriptors	rl 1
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

USB_SKIP_NONE     := 0
USB_SKIP_DISABLED := 1 shl 0
USB_SKIP_ENABLED  := 1 shl 1
USB_SKIP_DEVICES  := 1 shl 2
USB_SKIP_HUBS     := 1 shl 3
USB_SKIP_ATTACHED := 1 shl 4
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
usb_Init:
	ld	a,1
	call	usb_Cleanup.init
	call	_ChkIfOSInterruptAvailable
	rrca
	ld	hl,_DefaultFullSpeedDescriptors.str83
	jq	nc,.gotModel
	ld	hl,_DefaultFullSpeedDescriptors.str84
.gotModel:
	ld	(_DefaultFullSpeedDescriptors.model),hl
	ld	hl,mpUsbIdle
	ld	(hl),7
	ld	l,(usbDevCtrl+1) and $FF
	xor	a,a
	ld	(hl),a
	dec	l;usbDevCtrl and $FF
	ld	(hl),bmUsbDevReset or bmUsbDevEn
	ld	hl,rootDevice.find
	ld	(hl),USB_SKIP_HUBS or USB_SKIP_ENABLED
	sbc	hl,hl
	ld	(rootDevice.data),hl
	ld	l,3
	add	hl,sp
	ld	de,eventCallback
	ld	c,12
	ldir
	ld	a,(hl)
	dec	bc
iterate <speed,Speed>, full,Full, high,High
	ld	hl,(speed#SpeedDescriptors)
	add	hl,bc
 if % = 2
	inc	hl
 end if
	jq	c,.nonDefault#Speed#SpeedDescriptors
	ld	hl,_Default#Speed#SpeedDescriptors
	ld	(speed#SpeedDescriptors),hl
.nonDefault#Speed#SpeedDescriptors:
end iterate
	ld	hl,(hl)
	add	hl,bc
	ld	c,a
	ld	hl,USB_ERROR_INVALID_PARAM
	ld	e,1
	ld	d,a;(cHeap-$D10000) shr 8
	ld	b,sizeof cHeap shr 8
	rrc	c
	call	c,.initFreeList
	ld	d,(periodicList-$D10000) shr 8
	ld	b,sizeof periodicList shr 8
	rrc	c
	call	c,.initFreeList
	ld	d,(usbMem-$D10000) shr 8
	ld	b,sizeof usbMem shr 8
	rrc	c
	call	c,.initFreeList
	rrc	c
	ret	nc
	ld	d,(osHeap-$D10000) shr 8
	ld	b,sizeof osHeap shr 8
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
.init:
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
	ret

;-------------------------------------------------------------------------------
usb_WaitForEvents:
	scf
.wait:
	ret	nc
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
	ld	hl,mpIntStat+1
	bit	bIntUsb-8,(hl)
	ld	hl,mpUsbIsr
iterate type, Dev, Otg, Host
	bit	bUsbInt#type,(hl)
	call	nz,_Handle#type#Int
end iterate
	ld	hl,mpIntAck+1
	ld	(hl),intUsb shr 8
	or	a,a
	jq	usb_HandleEvents

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
	pop	de, iy
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
	pop	de, hl, iy, bc
	push	bc, hl, hl, de
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
	bit	bsf USB_SKIP_ATTACHED,c
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
	pop	de, iy
	ex	(sp),hl
	push	hl, de
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
	pop	de, iy
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
	pop	de, iy
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

_HandleDevInt:
	push	hl
	pop	hl
	ld	(hl),bmUsbIntDev
	ret

_HandleOtgInt:
	push	hl
	pop	hl
	ld	(hl),bmUsbIntOtg
	ret

_HandleHostInt:
	push	hl
	pop	hl
	ld	(hl),bmUsbIntHost
	ret

_DefaultFullSpeedDescriptors: dl .device, .confs, .langids
                              db 2
                              dl .str1
.model			      dl 0
.device emit $12: $1201000200000040510408E0200201020003 bswap $12
.confs dl .conf1, .conf2, .conf3
.conf1 emit $23: $0902230001010080FA0904000002FF0100000705810240000007050202400000030903 bswap $23
.conf2 emit $23: $09022300010200C0000904000002FF0100000705810240000007050202400000030903 bswap $23
.conf3 emit $23: $0902230001030080320904000002FF0100000705810240000007050202400000030903 bswap $23
.langids dw $0304, $0409
.str1 dw $033E, 'T','e','x','a','s',' ','I','n','s','t','r','u','m','e','n','t','s',' ','I','n','c','o','r','p','o','r','a','t','e','d'
.str83 dw $0322, 'T','I','-','8','3',' ','P','r','e','m','i','u','m',' ','C','E'
.str84 dw $031C, 'T','I','-','8','4',' ','P','l','u','s',' ','C','E'
_DefaultHighSpeedDescriptors dl 0
