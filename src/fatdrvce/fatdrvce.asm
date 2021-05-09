;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library 'FATDRVCE',1

include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export msd_Open
	export msd_Close
	export msd_Reset
	export msd_Info
	export msd_ReadAsync
	export msd_WriteAsync
;-------------------------------------------------------------------------------

include 'macros.inc'
include 'msd.asm'
