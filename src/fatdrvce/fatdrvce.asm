;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library 'FATDRVCE',1

;-------------------------------------------------------------------------------
; Dependencies
;-------------------------------------------------------------------------------
include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export msd_Find
	export msd_SetupDevice
	export msd_Read
	export msd_Write
	export msd_ScheduleRead
	export msd_ScheduleWrite
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
macro compare_hl_zero?
	add	hl,de
	or	a,a
	sbc	hl,de
end macro

macro compare_hl_de?
	or	a,a
	sbc	hl,de
	add	hl,de
end macro
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
msd_Find:
	pop	de
	ex	(sp),hl
	push	de
	ld	bc,1 shl 3		; USB_SKIP_HUBS
	push	bc
	push	hl			; get previous device
	or	a,a
	sbc	hl,hl
	push	hl
	call	usb_FindDevice
	pop	bc
	pop	bc
	pop	bc
	compare_hl_zero
	ret	z			; if no more devices, end
	ld	bc,msd_xfer_size
	push	bc
	ld	bc,18			; descriptor size to fetch
	push	bc
	ld	bc,msd_descriptor_buffer
	push	bc
	ld	bc,0			; index
	push	bc
	ld	c,1			; USB_DEVICE_DESCRIPTOR
	push	bc
	push	hl			; device
	call	usb_GetDescriptor
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	or	a,a
	jr	nz,.error
	ld	de,18
	ld	hl,(msd_xfer_size)
	compare_hl_de			; ensure enough bytes were fetched
	jr	nz,.error

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
msd_SetupDevice:
; Setup MSD handles for multiple support
; Arguments:
;  arg0: msd device
;  arg1: msd buffer
; Returns:
;  n/a
	
	ret

;-------------------------------------------------------------------------------
msd_Read:
	ret

;-------------------------------------------------------------------------------
msd_Write:
	ret

;-------------------------------------------------------------------------------
msd_ScheduleRead:
	ret

;-------------------------------------------------------------------------------
msd_ScheduleWrite:
	ret

msd_descriptor_buffer:
	rb	18
msd_xfer_size:
	dl	0

