; Note - this file does not contain actual functions, only equates.
; Include "include_library.inc" and then include the LibLoad library by
; doing `include_library 'capnhook.lib'` in order to use capnhook functions.

; A negative flag location that should be set before returning if you want
; to ignore event that triggered the hook.
; Returning with this bit reset will return a value to TI-OS, and no other
; hooks will be called afterwards.
; Returning with this bit set will restore the processor registers to their
; previous values, and the hook with the next lowest priority value will be
; called.
; If there are no hooks after yours, and you return with this bit set, capnhook
; will call a "no-op" hook that behaves as though no hook was called in the
; first place. In effect, this means that you can return with this bit set if
; you wish to ignore a hook that is not called with a particular condition,
; without requiring you to handle other conditions.
;
; Unless you want to return a value to TI-OS, you should *always* set this bit
; by doing `set	0,(iy-flag_continue)`.
flag_continue	equ	10

; Hook types
virtual at 0
	HOOK_TYPE_CURSOR	rb	1
	HOOK_TYPE_LIBRARY	rb	1
	HOOK_TYPE_RAW_KEY	rb	1
	HOOK_TYPE_GET_CSC	rb	1
	HOOK_TYPE_HOMESCREEN	rb	1
	HOOK_TYPE_WINDOW	rb	1
	HOOK_TYPE_GRAPH		rb	1
	HOOK_TYPE_Y_EQUALS	rb	1
	HOOK_TYPE_FONT		rb	1
	HOOK_TYPE_REGRAPH	rb	1
	HOOK_TYPE_GRAPHICS	rb	1
	HOOK_TYPE_TRACE		rb	1
	HOOK_TYPE_PARSER	rb	1
	HOOK_TYPE_APP_CHANGE	rb	1
	HOOK_TYPE_CATALOG1	rb	1
	HOOK_TYPE_HELP		rb	1
	HOOK_TYPE_CX_REDISP	rb	1
	HOOK_TYPE_MENU		rb	1
	HOOK_TYPE_CATALOG2	rb	1
	HOOK_TYPE_TOKEN		rb	1
	HOOK_TYPE_LOCALIZE	rb	1
	HOOK_TYPE_SILENT_LINK	rb	1
	HOOK_TYPE_USB_ACTIVITY	rb	1
end virtual
