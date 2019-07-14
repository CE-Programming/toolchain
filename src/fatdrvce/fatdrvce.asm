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
	export msd_Init
	export msd_GetBlockSize
	export msd_GetSectorCount
	export msd_GetSectorSize
	export msd_ReadSectors
	export msd_WriteSectors
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
; memory structures
;-------------------------------------------------------------------------------
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

struct msd_device
	label .: 12
	dev		rl 1
	epin		rl 1
	epout		rl 1
	buffer		rl 1
end struct

struct tmp_data
	label .: 21
	size		rl 1
	descriptor	rb 18
end struct

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
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Initialize a USB connected Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : usb device to initialize as msd
;  sp + 9  : internal user-supplied buffer
; return:
;  a = error status
msd_Init:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)		; usb device
	push	iy
	ld	bc,tmp.size		; storage for size of descriptor
	push	bc
	ld	bc,18			; size of device descriptor
	push	bc
	ld	bc,tmp.descriptor	; storage for descriptor
	push	bc
	ld	bc,0
	push	bc
	inc	bc			; USB_DEVICE_DESCRIPTOR = 1
	push	bc
	push	hl
	call	usb_GetDescriptor
	pop	iy
	ld	sp,iy
	or	a,a
	ret	nz			; return if error
	ld	de,18
	ld	hl,(tmp.size)
	compare_hl_de			; ensure enough bytes were fetched
	jr	nz,.error

	ld	a,USB_SUCCESS		; return success
	ret

.error:
	ld	a,USB_ERROR_NO_DEVICE
	ret

;-------------------------------------------------------------------------------
; Gets the block size from the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store block size to
; return:
;  a = error status
msd_GetBlockSize:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Gets the sector count of the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector count to
; return:
;  a = error status
msd_GetSectorCount:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Gets the sector size of each sector on the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector size to
; return:
;  a = error status
msd_GetSectorSize:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Reads sectors from a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : lba of starting sector to read
;  sp + 9  : number of sectors to read
;  sp + 12 : user buffer to read into
; return:
;  a = error status
msd_ReadSectors:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Writes sectors to a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : lba of starting sector to write
;  sp + 9  : number of sectors to write
;  sp + 12 : user buffer to write from
; return:
;  a = error status
msd_WriteSectors:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------


;-------------------------------------------------------------------------------
; library data
;-------------------------------------------------------------------------------

tmp tmp_data
