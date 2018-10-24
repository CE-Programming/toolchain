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
	rootDev			dbx 32: ?
				rb (-$) and $FFF
	periodicList		dbx $400: ?
	usbMem			dbx usbInited and not $FF - $: ?
	eventCallback		rl 1
	eventCallbackData	rl 1
	freeList32Align32	rl 1
	freeList64Align256	rl 1
	assert $ <= usbInited
end virtual
virtual at (ramCodeTop+$FF) and not $FF
	osHeap			dbx heapTop and not $FF - $: ?
end virtual
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
virtual at 0			; device structure
	devHub		rl 1	; hub this device is connected to
	devHubPorts	rb 1	; number of ports in this hub
	devAddr		rb 1	; device addr and $7F
	devSpeed	rb 1	; device speed shl 4
	devEps		rl 1	; pointer to array of endpoints
		        rb 1
	devHubInfo	rw 1	; hub addr or port number shl 7 or 1 shl 14
	devChild	rl 1	; first device connected to this hub
	devSibling	rl 1	; next device connected to the same hub
	devUserData	rl 1	; user data
	devSize:
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
	ld	(rootDev+devUserData),hl
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

;-------------------------------------------------------------------------------
usb_GetDeviceHub:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(iy+devHub)
	bit	0,l
	ret	z
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
usb_GetDeviceUserData:
	pop	de
	ex	(sp),iy
	push	de
	ld	hl,(iy+devUserData)
	ret

;-------------------------------------------------------------------------------
usb_SetDeviceUserData:
	pop	de
	pop	iy
	ex	(sp),hl
	push	hl
	ld	(iy+devUserData),hl
	ex	de,hl
	jp	(hl)
