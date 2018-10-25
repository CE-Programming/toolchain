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
	export usb_GetDeviceHub
	export usb_SetDeviceUserData
	export usb_GetDeviceUserData
	export usb_GetDeviceAddress
	export usb_GetDeviceSpeed
	export usb_GetEndpointMaxPacketSize
	export usb_GetEndpointTransferType
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
struc transfer			; transfer structure
	local size
	label .: size
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
	size := $-.
end struc
struc endpoint			; endpoint structure
	local size
	label .: size at $-2
	.next		rd 1	; link to next endpoint structure
	.addr		rb 1	; device addr or cancel shl 7
	.info		rb 1	; ep or speed shl 4 or dtc shl 6
	.maxPktLen	rw 1	; max packet length or c shl 15 or 1 shl 16
	.cur		rd 1	; current transfer pointer
	.overlay	transfer; current transfer
	.first		rl 1	; pointer to first scheduled transfer
	.last		rl 1	; pointer to last dummy transfer
	.device		rl 1	; pointer to device
	.data		rl 1	; user data
	size := $-.
end struc
struc device			; device structure
	local size
	label .: size
	.hub		rl 1	; hub this device is connected to
	.hubPorts	rb 1	; number of ports in this hub
	.addr		rb 1	; device addr
	.speed		rb 1	; device speed shl 4
	.endpoints	rl 1	; pointer to array of endpoints
		        rb 1
	.info		rw 1	; hub addr or port number shl 7 or 1 shl 14
	.child		rl 1	; first device connected to this hub
	.sibling	rl 1	; next device connected to the same hub
	.data		rl 1	; user data
	size := $-.
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
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
usb_Init:
	ld	a,1
	call	usb_Cleanup.init
	ld	hl,mpUsbIdle
	ld	(hl),7
	ld	l,(usbDevCtrl+1) and $FF
	xor	a,a
	ld	(hl),a
	dec	l;usbDevCtrl and $FF
	ld	(hl),bmUsbDevReset or bmUsbDevEn
	sbc	hl,hl
	ld	(rootDevice.data),hl
	ld	l,3
	add	hl,sp
	ld	de,eventCallback
	ld	c,6
	ldir
	ld	c,(hl)
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
	jr	c,.inner
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
	jr	z,.wait
	scf
	sbc	hl,hl
	add	hl,de
	ex	de,hl
	lddr
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceHub:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(ydevice.hub)
	bit	0,l
	ret	z
.returnZero:
	or	a,a
.returnCarry:
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_SetDeviceUserData:
	pop	de
	pop	iy
	ex	(sp),hl
	push	hl
	ld	(ydevice.data),hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
usb_GetDeviceUserData:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(ydevice.data)
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
usb_GetEndpointMaxPacketSize:
	call	_LookupDeviceEndpointFromStack
	jr	c,usb_GetDeviceHub.returnZero
	ld	l,endpoint.maxPktLen+1-endpoint
	ld	a,(hl)
	dec	l
	ld	l,(hl)
	and	a,111b
	ld	h,a
	ret

;-------------------------------------------------------------------------------
usb_GetEndpointTransferType:
	call	_LookupDeviceEndpointFromStack
	ex	de,hl
	sbc	hl,hl
	ret	c
	inc	de
	ld	a,(de)
	and	a,11b
	ld	l,a
	ret

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

; Input:
;  (sp+6) = device
;  (sp+9) = endpoint
; Output:
;  cf = unused endpoint
;  hl = endpoint structure
_LookupDeviceEndpointFromStack:
	pop	de
	pop	bc
	pop	iy
	ex	(sp),hl
	push	hl
	push	bc
	push	de
	ld	a,l
; Input:
;  iy = device
;  a = endpoint
; Output:
;  cf = unused endpoint
;  hl = endpoint structure
_LookupDeviceIYEndpointA:
	and	a,$8F
.masked:
	ld	hl,(ydevice.endpoints)
	bit	0,l
	ret	nz
	rlca
	or	a,l
	ld	l,a
	ld	h,(hl)
	ld	l,endpoint
	ld	a,h
	add	a,l
	ccf
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
