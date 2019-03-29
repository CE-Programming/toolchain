;-------------------------------------------------------------------------------
msd_Init:
	pop	hl
	pop	de
	push	de
	push	hl
	push	ix
	push	iy
	call	msdInit				; attempt to initialize mass storage device
	jr	nc,.fail
	xor	a,a
.ret:
	pop	iy
	pop	ix
	ret
.fail:
	call	usbCleanup
	xor	a,a
	inc	a
	jr	.ret

;-------------------------------------------------------------------------------
msd_Find:
	ret

;-------------------------------------------------------------------------------
msd_Select:
	ret

;-------------------------------------------------------------------------------
msd_KeepAlive:
	ld	hl,scsiTestUnitReady
	jp	scsiDefaultRequest

;-------------------------------------------------------------------------------
msd_ReadSector:
	call	__frameset0
	ld	a,(ix + 9)
	ld	(scsiRead10Lba + 3),a
	ld	a,(ix + 10)
	ld	(scsiRead10Lba + 2),a
	ld	a,(ix + 11)
	ld	(scsiRead10Lba + 1),a
	ld	a,(ix + 12)
	ld	(scsiRead10Lba + 0),a
	ld	de,(ix + 6)
	call	scsiRequestRead
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_WriteSector:
	call	__frameset0
	ld	a,(ix + 9)
	ld	(scsiWrite10Lba + 3),a
	ld	a,(ix + 10)
	ld	(scsiWrite10Lba + 2),a
	ld	a,(ix + 11)
	ld	(scsiWrite10Lba + 1),a
	ld	a,(ix + 12)
	ld	(scsiWrite10Lba + 0),a
	ld	de,(ix + 6)
	call	scsiRequestWrite
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_SetJmpBuf:
	pop	de
	ex	(sp),hl		; hl -> buffer
	push	de
	ld	(fat.setjmpbuf),hl
	ret

;-------------------------------------------------------------------------------
msd_Deinit:
	push	ix
	push	iy
	call	usbCleanup
	pop	iy
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd.detached:
	call	usbCleanup		; restore setjmp buffer to return to
	ld	hl,1			; MSD_EVENT_DETACHED
	jr	msd.event
msd.xfererror:
	call	usbCleanup		; restore setjmp buffer to return to
	ld	hl,2			; MSD_EVENT_XFER_ERROR
msd.event:
	push	hl
	ld	hl,(fat.setjmpbuf)
	push	hl
	call	__longjmp

;-------------------------------------------------------------------------------
usbConfigureFirstDevice:
; de = milliseconds to wait for plug
; returns nz if successfull
	call    usbInit				; init usb
	ld	a,(usbInited)
	or	a,a
	ret	z				; timeout most likely
	call    devFirst
	ld	(device),iy			; use first device
	ld      hl,xferDataPtrDefault		; get dev desc
	ld      de,reqDevDesc18
	call    usbSetupPacket
	ld      hl,xferDataPtrDefault + 18	; get langids
	ld      de,reqGetStrDesc
	call    usbSetupPacket
	ld      hl,xferDataPtrDefault + 18 + 2
	ld      de,reqGetStrDesc+4
	ldi
	ldi					; use first langid
;	ld      hl,(xferDataPtrDefault + 8)	; get vendor
;	ld      hl,(xferDataPtrDefault + 10)	; get product
;	ld      hl,(xferDataPtrDefault + 12)	; get release
;	ld      a,(xferDataPtrDefault + 14)	; get manufacturer
;	ld      a,(xferDataPtrDefault + 15)	; get product
;	ld      a,(xferDataPtrDefault + 16)	; get serial number
	ld	iy,(device)			; get configuration descriptor
	xor     a,a
	call    getConfigDescTotalLength	; total length of config
	ld      (reqConfDesc + wLength),hl
	push    hl
	ld      hl,xferDataPtrDefault
	ld      de,reqConfDesc
	call    usbSetupPacket
	pop	bc
	ld      hl,xferDataPtrDefault
	ld	(msd_config_start),hl
	add	hl,bc
	ld	(msd_config_end),hl		; used by the msd driver
	ld	iy,(device)			; select config
	ld      ix,xferDataPtrDefault
	call	devSelectConfig
	xor	a,a
	inc	a
	ret

usbSetupPacket:
	ld	iy,0
device := $ - 3
	call	controlDefaultTransfer
	ld	b,0
	jp	qhRetry

reqDevDesc18:
	db	$80,6,0,1,0,0,18,0
reqConfDesc:
	db	$80,6,0,2,0,0,0,0,0
reqGetStrDesc:
	db	$80,6,0,3,0,0,0,1
reqClrInStall:
	db	$02,1,0,0,0,0,0,0
reqClrOutStall:
	db	$02,1,0,0,0,0,0,0

;-------------------------------------------------------------------------------
return_nc:
	scf
	ccf
	ret

;-------------------------------------------------------------------------------
msdInit:
; returns c if successfull
	di
	call	usbConfigureFirstDevice
	jr	z,return_nc
	call	findFirstMsdInterface
	call	c,findScsiEndpoints
	ret	nc
	call	msdReset
	call	msdMaxLun
	call	msdSetLun
;	jr	scsiInit

;-------------------------------------------------------------------------------
scsiInit:
	ld	a,(ep_in)
	ld	(reqClrInStall + wIndex),a
	ld	a,(ep_out)
	ld	(reqClrOutStall + wIndex),a
	ld	hl,scsiInquiry
	call	scsiDefaultRequest
.unitattention:
	ld	hl,scsiTestUnitReady
	call	scsiDefaultRequest
	cp	a,6
	jr	z,.unitattention
	ld	hl,scsiReadCapacity
	ld	de,msdLBAddr
	call	scsiRequest		; store the logical block address/size
	ld	hl,scsiTestUnitReady	; test if ready again
	call	scsiDefaultRequest
	ld	hl,(msdBlockSize)
	ld	de,512
	or	a,a
	sbc	hl,de
	scf
	ret	z			; ensure sector size is 512 bytes
	ccf
	ret

; scsi format:
; <[1] in/out>,<[3] i/o length>,<[1] cdb length>,<[n] cdb>

scsiInquiry:
	db	$80,$24,$00,$00,$06,$12,$00,$00,$00,$24,$00

scsiTestUnitReady:
	db	$00,$00,$00,$00,$06,$00,$00,$00,$00,$00,$00

scsiModeSense6:
	db	$80,$fc,$00,$00,$06,$1a,$00,$3f,$00,$fc,$00

scsiReqestSense:
	db	$80,$12,$00,$00,$06,$03,$00,$00,$00,$12,$00

scsiReadCapacity:
	db	$80,$08,$00,$00,$0a,$25,$00,$00,$00,$00,$00,$00,$00,$00,$00

scsiRead10:
	db	$80,$00,$02,$00,$0a,$28,$00
scsiRead10Lba:
	db	$00,$00,$00,$00
scsiRead10GroupNum:
	db	$00
scsiRead10Length:
	db	$00,$01
scsiRead10Ctrl:
	db	$00

scsiWrite10:
	db	$00,$00,$02,$00,$0a,$2a,$00
scsiWrite10Lba:
	db	$00,$00,$00,$00
scsiWrite10GroupNum:
	db	$00
scsiWrite10Length:
	db	$00,$01
scsiWrite10Ctrl:
	db	$00

; Input:
;  scsiRead10Lba = logical block address
;  de -> buffer
; Output:
;  buffer loaded
scsiRequestDefaultRead:
	ld	de,xferDataPtrDefault
scsiRequestRead:
	ld	hl,scsiRead10
	jr	scsiRequest

; Input:
;  scsiWriteiRead10Lba = logical block address
;  de -> buffer
; Output:
;  buffer loaded
scsiRequestDefaultWrite:
	ld	de,xferDataPtrDefault
scsiRequestWrite:
	ld	hl,scsiWrite10
	jr	scsiRequest

; Input:
;  hl = ptr to xfer
;  de = ptr to storage
; Output;
;   z = success
;  nz = failure
scsiDefaultRequest:
	ld	de,xferDataPtrDefault
scsiRequest:
	push	ix
	push	iy
	ld	(xferDataPtr),de
	ld	a,(hl)
	ld	(xferDataEp),a
	inc	hl
	ld	bc,(hl)
	ld	(xferDataLen),bc
	inc	hl
	inc	hl
	inc	hl
	ld	(xferCdbPtr),hl
.resendCbw:
	call	msdCommandTransport
	call	msdDataTransport
	call	msdStatusTransport
	jr	nz,.resendCbw
	pop	iy
	pop	ix
	ret

;-------------------------------------------------------------------------------

msdPerformResetRecovery:
	call	msdReset		; perform reset recovery
	call	msdClrInStall
;	jr	msdClrOutStall
msdClrOutStall:
	ld	de,reqClrOutStall
	jr	msdClrStall
msdClrInStall:
	ld	de,reqClrInStall
msdClrStall:
	ld	hl,xferDataPtrDefault
	ld	iy,(device)
	jp	controlDefaultTransfer

; hl = data to transfer
; de = buffer to recieve
msdCommandTransport:
	ld	hl,0
xferCdbPtr := $ - 3
	ld	iy,packetCBW
	ld	a,(xferDataEp)
	ld	(iy+12),a		; direction flag
	ld	bc,(xferDataLen)	; get the length -- only use 3/4 bytes
	ld	(iy + 8),bc		; i/o length
	ld	bc,0
	ld	c,(hl)			; cdb length
	inc	c
	lea	de,iy + 14		; cdb location
	ldir
	ld	hl,(iy + 4)		; increment tag
	inc	hl
	ld	(iy + 4),hl
	call	msdDeviceEpOut
	ld	de,packetCBW		; de -> packetCBW
	ld	bc,packetCBWLen
	call	bulkTransfer
	ld	b,0
	call	qhRetry
	or	a,a
	ret	z			; check the command was accepted
	cp	a,1
	jp	z,msd.detached
	add	a,a			; check if stall
	call	nz,msd.xfererror
.resendCbw:
	call	msdPerformResetRecovery
	jr	msdCommandTransport

; bc = length of transfer
msdDataTransport:
	ld	bc,0
xferDataLen := $ - 3
	sbc	hl,hl
	adc	hl,bc
	ret	z			; no bulk if 0 length req
	ld	a,0
xferDataEp := $ - 1
	ld	de,0
xferDataPtr := $ - 3
	or	a,a
	jr	z,msdDataOut
msdDataIn:
	call	msdDeviceEpIn
	call	bulkTransfer
	ld	b,0
	call	qhRetry
	or	a,a
	ret	z
	cp	a,1
	jp	z,msd.detached
	cp	a,$80
	call	nz,msd.xfererror
	jq	msdClrInStall

msdDataOut:
	call	msdDeviceEpOut
	call	bulkTransfer
	ld	b,0
	call	qhRetry
	or	a,a
	ret	z
	cp	a,1
	jp	z,msd.detached
	add	a,a
	call	nz,msd.xfererror
	jq	msdClrOutStall

msdStatusTransport:
	call	msdStatusXfer
	or	a,a
	jr	z,msdCheckValidCsw
	cp	a,1
	jp	z,msd.detached
	add	a,a
	call	nz,msd.xfererror
msdStatusStall:
	call	msdClrInStall		; clear stall
	call	msdStatusXfer		; attempt to read csw again
	or	a,a
	jr	z,msdCheckValidCsw
	cp	a,1
	jp	z,msd.detached
	add	a,a
	call	nz,msd.xfererror
	call	msdPerformResetRecovery
	xor	a,a
	inc	a
	ret
msdCheckValidCsw:
	ld	a,(packetCSW+12)
	or	a,a			; check for good status of transfer
	jr	nz,msdInvalidCsw
msdValidCsw:
	ld	hl,(packetCSW + 8)
	ld	a,(packetCSW + 8 + 3)
	add	hl,de
	or	a,a
	ld	a,$10
	ret	nz
	sbc	hl,de
	ret	nz			; if residue != 0, fail
	xor	a,a
	ret
msdInvalidCsw:
	dec	a			; check for phase error (we can recover)
	jr	z,msdSenseError		; handle command fail
msdPhaseError:
	call	msdPerformResetRecovery
	xor	a,a
	inc	a
	ret
msdSenseError:
	ld	hl,msdSenseCount
	or	a,(hl)
	call	nz,msd.xfererror
	inc	(hl)
	ld	de,xferDataPtrSense
	ld	hl,scsiReqestSense
	call	scsiRequest
	xor	a,a
	ld	(xferDataPtrSense),a
	ld	a,(xferDataPtrSense + 2)
	ret

msdSenseCount:
	db	0

msdStatusXfer:
	call	msdDeviceEpIn
	ld	de,packetCSW
	ld	bc,packetCSWLen
	call	bulkTransfer
	ld	b,0
	jp	qhRetry

; Input:
;  hl = ptr in config
;   a = type
; Output:
;  nc = not found
;   c = found
getDescriptor:
	push	de
	push	bc
	ld	de,0
msd_config_end := $ - 3
	ld	bc,0
findDescriptor:
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nc,notFoundDescriptor
	push	hl
	pop	iy
	ld	c,(hl)			; length of descriptor
	cp	a,(iy + bDescriptorType)
	jr	z,foundDescriptor
	add	hl,bc
	jr	findDescriptor
foundDescriptor:
	scf
notFoundDescriptor:
	pop	bc
	pop	de
	ret

; Input:
;  hl = interface ptr
; Output:
;  nc = not found
;   c = found
findScsiEndpoints:
	ld	bc,6 or ($50 shl 8)	; check scsi bot
	call	checkSubclassProtocol
	jr	nz,endpointFail
	push	hl
	pop	iy
	ld	b,(iy+4)
	ld	c,0
	ld	de,0
findScsiEndpointsLoop:
	ld	a,5			; endpoint descriptor type
	call	getDescriptor
	ret	nc
	ld	a,(iy+2)
	bit	7,a
	jr	z,endpointOut
	bit	0,c
	jr	nz,endpointSkip
	ld	(ep_in),a
;	call	debugStr
;	db	'in: ',0
;	call	debugHexA
;	call	debugNewLine
	set	0,c
	jr	endpointSkip
endpointOut:
	bit	1,c
	jr	nz,endpointSkip
	ld	(ep_out),a
;	call	debugStr
;	db	'out: ',0
;	call	debugHexA
;	call	debugNewLine
	set	1,c
endpointSkip:
	ld	e,(iy+0)
	add	hl,de
	djnz	findScsiEndpointsLoop
	ld	a,c
	cp	a,2
	jr	z,endpointFail
;	call	debugStr
;	db	'valid endpoints',0
;	call	debugNewLine
	scf
	ret
endpointFail:
	scf
	ccf
	ret

; Input:
;  none
; Output:
;  hl = interface ptr
;  nc = not found
;   c = found
findFirstMsdInterface:
	ld	hl,0
msd_config_start := $ - 3
findMsdInterface:
	ld	a,4			; interface descriptor type
	call	getDescriptor
	ret	nc
	ld	a,(iy+0)		; bLength
	cp	a,9
	jr	c,findMsdInterface	; ensure interface length >= 9
	ld	a,(iy+5)
	cp	a,8			; bInterfaceClass == 8
	jr	nz,findMsdInterface
;	call	debugStr
;	db	'interface: ',0
	ld	a,(iy+2)
	ld	(packetMSDReset+4),a	; store the interface number
	ld	(packetMSDMaxLUN+4),a	; store the interface number
;	call	debugHexA
;	call	debugNewLine
	scf
	ret

; Input:
;   c = subclass
;   b = protocol
checkSubclassProtocol:
	ld	a,(iy+6)
	cp	a,c			; scsi subclass
	ret	nz
	ld	a,(iy+7)
	cp	a,b			; bot protocol
	ret

msdSetLun:
	ld	a,(msdLun)
	ld	(packetCBW+13),a
	ret
msdMaxLun:
	ld	hl,msdMaxLuns
	ld	de,packetMSDMaxLUN
	jp	usbSetupPacket
msdReset:
	or	a,a
	sbc	hl,hl
	ld	(packetCBW + 4),hl
	ld	(packetCBW + 5),hl
	ld	de,packetMSDReset
	jp	usbSetupPacket

; Output:
;  flags are unaffected
msdDeviceEpOut:
ep_out := $ + 1
	ld	a,0
	jr	msdDeviceEpIn.set
msdDeviceEpIn:
ep_in := $ + 1
	ld	a,0
.set:
	ld	iy,(device)
	ret

msdMaxLuns:
	db	0
msdLun:
	db	0

msdLBAddr:
	db	0,0,0,0
	db	0		; technically part of block size, but meh
msdBlockSize:
	db	0,0,0

packetMSDReset:
	db	$21,$FF,$00,$00,$00,$00,$00,$00
packetMSDMaxLUN:
	db	$A1,$FE,$00,$00,$00,$00,$01,$00

packetCSW:
	db	$00,$00,$00,$00	; signature
	db	$00,$00,$00,$00	; tag
	db	$00,$00,$00,$00	; residue
	db	$00		; status
packetCSWLen := $ - packetCSW

packetCBW:
	db	$55,$53,$42,$43	; signature
	db	$00,$00,$00,$00	; tag
	db	$00,$00,$00,$00	; length
	db	$00		; flags
	db	$00		; lun
packetCBWCBD:
	db	$00		; command block length
	db	$00		; command block opcode
	db	$00,$00,$00	; command block
	db	$00,$00,$00,$00	; command block
	db	$00,$00,$00,$00	; command block
	db	$00,$00,$00,$00	; command block
packetCBWLen := $ - packetCBW

xferDataPtrDefault:
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

xferDataPtrSense:
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

