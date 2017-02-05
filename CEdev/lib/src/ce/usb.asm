; C USB Functions present in the CE OS and Bootcode

; --- External Definitions -------------------
	.assume ADL=1
	.def _usb_BusPowered
	.def _usb_SelfPowered
	.def _usb_ResetChip
	.def _usb_DisableTimers
	.def _usb_EnableTimers
	.def _usb_ResetTimers
; --------------------------------------------

; --- Location Equates -----------------------
_usb_BusPowered                 equ 0003E4h
_usb_SelfPowered                equ 0003E8h
_usb_ResetChip                  equ 0003F4h
_usb_DisableTimers              equ 0004F4h
_usb_EnableTimers               equ 0004F8h
_usb_ResetTimers                equ 0004F0h
; --------------------------------------------

	end
