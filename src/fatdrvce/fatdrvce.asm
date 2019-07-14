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
	ld	de,(iy + 9)		; user-supplied buffer

.error:
	or	a,a
	sbc	hl,hl
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
