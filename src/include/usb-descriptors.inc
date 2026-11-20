; Emit an ASCII string as a USB UTF-16LE string descriptor without a terminator.
.macro usb_string_descriptor text
.Lusb_string\@:
	.db .Lusb_string_end\@ - .Lusb_string\@, STRING_DESCRIPTOR
	.irpc text_byte, "\text"
		.db "\text_byte", 0
	.endr
.Lusb_string_end\@:
	.if .Lusb_string_end\@ - .Lusb_string\@ > 255
		.error "USB string descriptor exceeds 255 bytes"
	.endif
.endm
