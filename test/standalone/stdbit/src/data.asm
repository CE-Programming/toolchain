	assume	adl = 1

	section	.data

	public	_zero_u8
	public	_zero_u16
	public	_zero_u24
	public	_zero_u32
	public	_zero_u48
	public	_zero_u64
_zero_u8:
_zero_u16:
_zero_u24:
_zero_u32:
_zero_u48:
_zero_u64:
	db $00, $00, $00, $00, $00, $00, $00, $00

	public	_one_u8
	public	_one_u16
	public	_one_u24
	public	_one_u32
	public	_one_u48
	public	_one_u64
_one_u8:
_one_u16:
_one_u24:
_one_u32:
_one_u48:
_one_u64:
	db $01, $00, $00, $00, $00, $00, $00, $00

	public	_umax_u8
	public	_umax_u16
	public	_umax_u24
	public	_umax_u32
	public	_umax_u48
	public	_umax_u64
_umax_u8:
_umax_u16:
_umax_u24:
_umax_u32:
_umax_u48:
_umax_u64:
	db $FF, $FF, $FF, $FF, $FF, $FF, $FF, $FF

	public	_smin_u8
	public	_smin_u16
	public	_smin_u24
	public	_smin_u32
	public	_smin_u48
	public	_smin_u64
_smin_u64:
	db $00
	db $00
_smin_u48:
	db $00
	db $00
_smin_u32:
	db $00
_smin_u24:
	db $00
_smin_u16:
	db $00
_smin_u8:
	db $80

	public	_smax_u8
	public	_smax_u16
	public	_smax_u24
	public	_smax_u32
	public	_smax_u48
	public	_smax_u64
_smax_u64:
	db $FF
	db $FF
_smax_u48:
	db $FF
	db $FF
_smax_u32:
	db $FF
_smax_u24:
	db $FF
_smax_u16:
	db $FF
_smax_u8:
	db $7F


	public	_val_0
_val_0:
	db 0
	public	_val_1
_val_1:
	db 1
	public	_val_2
_val_2:
	db 2
	public	_val_7
_val_7:
	db 7
	public	_val_8
_val_8:
	db 8
	public	_val_15
_val_15:
	db 15
	public	_val_16
_val_16:
	db 16
	public	_val_23
_val_23:
	db 23
	public	_val_24
_val_24:
	db 24
	public	_val_31
_val_31:
	db 31
	public	_val_32
_val_32:
	db 32
	public	_val_47
_val_47:
	db 47
	public	_val_48
_val_48:
	db 48
	public	_val_63
_val_63:
	db 63
	public	_val_64
_val_64:
	db 64

; uint8_t byteswap_u8[4] = {
;     0x00,
;     0xFF,
;     0x12,
;     0x43,
; };
; uint16_t byteswap_u16[4] = {
;     0x0000,
;     0xFFFF,
;     0x1234,
;     0x4321,
; };
; uint24_t byteswap_u24[4] = {
;     0x000000,
;     0xFFFFFF,
;     0x123456,
;     0x654321,
; };
; uint32_t byteswap_u32[4] = {
;     0x00000000,
;     0xFFFFFFFF,
;     0x12345678,
;     0x87654321,
; };
; uint48_t byteswap_u48[4] = {
;     0x000000000000,
;     0xFFFFFFFFFFFF,
;     0x123456789ABC,
;     0xCBA987654321,
; };
; uint64_t byteswap_u64[4] = {
;     0x0000000000000000,
;     0xFFFFFFFFFFFFFFFF,
;     0x0123456789ABCDEF,
;     0xFEDCBA9876543210,
; };

	public	_byteswap_u8
_byteswap_u8:
	db	0
	db	255
	db	18
	db	67

	public	_byteswap_u16
_byteswap_u16:
	dw	0
	dw	65535
	dw	4660
	dw	17185

	public	_byteswap_u24
_byteswap_u24:
	dl	0
	dl	16777215
	dl	1193046
	dl	6636321

	public	_byteswap_u32
_byteswap_u32:
	dd	0
	dd	4294967295
	dd	305419896
	dd	2271560481

	public	_byteswap_u48
_byteswap_u48:
	dd	0
	dw	0
	dd	4294967295
	dw	65535
	dd	1450744508
	dw	4660
	dd	2271560481
	dw	52137

	public	_byteswap_u64
_byteswap_u64:
	dq	0
	dq	-1
	dq	81985529216486895
	dq	-81985529216486896

; uint8_t byteswap_i8[4] = {
;     0x00,
;     0xFF,
;     0x12,
;     0x43,
; };
; uint16_t byteswap_i16[4] = {
;     0x0000,
;     0xFFFF,
;     0x3412,
;     0x2143,
; };
; uint24_t byteswap_i24[4] = {
;     0x000000,
;     0xFFFFFF,
;     0x563412,
;     0x214365,
; };
; uint32_t byteswap_i32[4] = {
;     0x00000000,
;     0xFFFFFFFF,
;     0x78563412,
;     0x21436587,
; };
; uint48_t byteswap_i48[4] = {
;     0x000000000000,
;     0xFFFFFFFFFFFF,
;     0xBC9A78563412,
;     0x21436587A9CB,
; };
; uint64_t byteswap_i64[4] = {
;     0x0000000000000000,
;     0xFFFFFFFFFFFFFFFF,
;     0xEFCDAB8967452301,
;     0x1032547698BADCFE,
; };

	public	_byteswap_i8
_byteswap_i8:
	db	0
	db	255
	db	18
	db	67

	public	_byteswap_i16
_byteswap_i16:
	dw	0
	dw	65535
	dw	13330
	dw	8515

	public	_byteswap_i24
_byteswap_i24:
	dl	0
	dl	16777215
	dl	5649426
	dl	2179941

	public	_byteswap_i32
_byteswap_i32:
	dd	0
	dd	4294967295
	dd	2018915346
	dd	558065031

	public	_byteswap_i48
_byteswap_i48:
	dd	0
	dw	0
	dd	4294967295
	dw	65535
	dd	2018915346
	dw	48282
	dd	1703389643
	dw	8515

	public	_byteswap_i64
_byteswap_i64:
	dq	0
	dq	-1
	dq	-1167088121787636991
	dq	1167088121787636990
