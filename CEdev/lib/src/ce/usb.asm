; C USB Functions present in the CE OS and Bootcode

; --- External Definitions -------------------
	.assume ADL=1
	.def _usb_BusPowered
	.def _usb_SelfPowered
	.def _usb_ResetChip
	.def _usb_DisableTimer
	.def _usb_EnableTimer
	.def _usb_ResetTimer
; --------------------------------------------

; --- Location Equates -----------------------
_usb_BusPowered                 equ 000080h
_usb_SelfPowered                equ 000084h
_usb_ResetChip                  equ 00008Ch
_usb_DisableTimer               equ 0000B4h
_usb_EnableTimer                equ 000374h
_usb_ResetTimer                 equ 000388h
; --------------------------------------------

	end
