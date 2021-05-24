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
	export msd_Read
	export msd_Write
	export msd_ReadAsync
	export msd_WriteAsync
	export fat_FindPartitions
	export fat_OpenPartition
	export fat_ClosePartition
	export fat_DirList
	export fat_GetVolumeLabel
	export fat_Open
	export fat_Close
	export fat_SetSize
	export fat_GetSize
	export fat_SetAttrib
	export fat_GetAttrib
	export fat_SetPos
	export fat_Read
	export fat_Write
	export fat_ReadAsync
	export fat_WriteAsync
	export fat_Create
	export fat_Delete
;-------------------------------------------------------------------------------

include 'macros.inc'
include 'fat.asm'
include 'msd.asm'
