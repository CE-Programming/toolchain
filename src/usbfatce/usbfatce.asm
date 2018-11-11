;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'USBFATCE', 0

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export fat_Init
	export fat_Find
	export fat_Select
	export fat_Open
	export fat_Close
	export fat_GetFileSize
	export fat_SetFileSize
	export fat_Tell
	export fat_SetBuffer
	export fat_ReadSector
	export fat_WriteSector
	export fat_Delete
	export fat_Create
	export fat_GetAttrib
	export fat_SetAttrib
	export fat_DirList
	export msd_Init
	export msd_Find
	export msd_Select
	export msd_KeepAlive
	export msd_ReadSector
	export msd_WriteSector
	export msd_SetJmp
	export msd_Cleanup
;-------------------------------------------------------------------------------

include 'debug.inc'
include 'host.inc'
include 'msd.inc'

;-------------------------------------------------------------------------------
fat_Init:
	ret

;-------------------------------------------------------------------------------
fat_Find:
	ret

;-------------------------------------------------------------------------------
fat_Select:
	ret

;-------------------------------------------------------------------------------
fat_Open:
	ret

;-------------------------------------------------------------------------------
fat_Close:
	ret

;-------------------------------------------------------------------------------
fat_GetFileSize:
	ret

;-------------------------------------------------------------------------------
fat_SetFileSize:
	ret

;-------------------------------------------------------------------------------
fat_Tell:
	ret

;-------------------------------------------------------------------------------
fat_SetBuffer:
	ret

;-------------------------------------------------------------------------------
fat_ReadSector:
	ret

;-------------------------------------------------------------------------------
fat_WriteSector:
	ret

;-------------------------------------------------------------------------------
fat_Delete:
	ret

;-------------------------------------------------------------------------------
fat_Create:
	ret

;-------------------------------------------------------------------------------
fat_GetAttrib:
	ret

;-------------------------------------------------------------------------------
fat_SetAttrib:
	ret

;-------------------------------------------------------------------------------
fat_DirList:
	ret

;-------------------------------------------------------------------------------
msd_Init:
	push	ix
	push	iy
	call	msdInit			; attempt to initialize mass storage device
	jr	nc,.fail
	xor	a,a
	inc	a
.ret:
	pop	iy
	pop	ix
	ret
.fail:
	call	usbCleanup
	xor	a,a
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
	ld	a,(ix+9)
	ld	(scsiRead10Lba + 3),a
	ld	a,(ix+10)
	ld	(scsiRead10Lba + 2),a
	ld	a,(ix+11)
	ld	(scsiRead10Lba + 1),a
	ld	a,(ix+12)
	ld	(scsiRead10Lba + 0),a
	ld	de,(ix+6)
	call	scsiRequestRead
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_WriteSector:
	call	__frameset0
	ld	a,(ix+9)
	ld	(scsiWrite10Lba + 3),a
	ld	a,(ix+10)
	ld	(scsiWrite10Lba + 2),a
	ld	a,(ix+11)
	ld	(scsiWrite10Lba + 1),a
	ld	a,(ix+12)
	ld	(scsiWrite10Lba + 0),a
	ld	de,(ix+6)
	call	scsiRequestWrite
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_SetJmp:
	ret

;-------------------------------------------------------------------------------
msd_Cleanup:
	push	ix
	push	iy
	call	usbCleanup
	pop	iy
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_Detached:
	call	usbCleanup		; restore setjmp buffer to return to
	ret

