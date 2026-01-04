	.assume	adl = 1

	.section	.data

	.global	_zero_u8
	.global	_zero_u16
	.global	_zero_u24
	.global	_zero_u32
	.global	_zero_u48
	.global	_zero_u64
_zero_u8:
_zero_u16:
_zero_u24:
_zero_u32:
_zero_u48:
_zero_u64:
	.db $00, $00, $00, $00, $00, $00, $00, $00

	.global	_one_u8
	.global	_one_u16
	.global	_one_u24
	.global	_one_u32
	.global	_one_u48
	.global	_one_u64
_one_u8:
_one_u16:
_one_u24:
_one_u32:
_one_u48:
_one_u64:
	.db $01, $00, $00, $00, $00, $00, $00, $00

	.global	_umax_u8
	.global	_umax_u16
	.global	_umax_u24
	.global	_umax_u32
	.global	_umax_u48
	.global	_umax_u64
_umax_u8:
_umax_u16:
_umax_u24:
_umax_u32:
_umax_u48:
_umax_u64:
	.db $FF, $FF, $FF, $FF, $FF, $FF, $FF, $FF

	.global	_smin_u8
	.global	_smin_u16
	.global	_smin_u24
	.global	_smin_u32
	.global	_smin_u48
	.global	_smin_u64
_smin_u64:
	.db $00
	.db $00
_smin_u48:
	.db $00
	.db $00
_smin_u32:
	.db $00
_smin_u24:
	.db $00
_smin_u16:
	.db $00
_smin_u8:
	.db $80

	.global	_smax_u8
	.global	_smax_u16
	.global	_smax_u24
	.global	_smax_u32
	.global	_smax_u48
	.global	_smax_u64
_smax_u64:
	.db $FF
	.db $FF
_smax_u48:
	.db $FF
	.db $FF
_smax_u32:
	.db $FF
_smax_u24:
	.db $FF
_smax_u16:
	.db $FF
_smax_u8:
	.db $7F


	.global	_val_0
_val_0:
	.db 0
	.global	_val_1
_val_1:
	.db 1
	.global	_val_2
_val_2:
	.db 2
	.global	_val_7
_val_7:
	.db 7
	.global	_val_8
_val_8:
	.db 8
	.global	_val_15
_val_15:
	.db 15
	.global	_val_16
_val_16:
	.db 16
	.global	_val_23
_val_23:
	.db 23
	.global	_val_24
_val_24:
	.db 24
	.global	_val_31
_val_31:
	.db 31
	.global	_val_32
_val_32:
	.db 32
	.global	_val_47
_val_47:
	.db 47
	.global	_val_48
_val_48:
	.db 48
	.global	_val_63
_val_63:
	.db 63
	.global	_val_64
_val_64:
	.db 64

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

	.global	_byteswap_u8
_byteswap_u8:
	.db	0
	.db	255
	.db	18
	.db	67

	.global	_byteswap_u16
_byteswap_u16:
	.word	0
	.word	65535
	.word	4660
	.word	17185

	.global	_byteswap_u24
_byteswap_u24:
	.d24	0
	.d24	16777215
	.d24	1193046
	.d24	6636321

	.global	_byteswap_u32
_byteswap_u32:
	.long	0
	.long	4294967295
	.long	305419896
	.long	2271560481

	.global	_byteswap_u48
_byteswap_u48:
	.long	0
	.word	0
	.long	4294967295
	.word	65535
	.long	1450744508
	.word	4660
	.long	2271560481
	.word	52137

	.global	_byteswap_u64
_byteswap_u64:
	.quad	0
	.quad	-1
	.quad	81985529216486895
	.quad	-81985529216486896

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

	.global	_byteswap_i8
_byteswap_i8:
	.db	0
	.db	255
	.db	18
	.db	67

	.global	_byteswap_i16
_byteswap_i16:
	.word	0
	.word	65535
	.word	13330
	.word	8515

	.global	_byteswap_i24
_byteswap_i24:
	.d24	0
	.d24	16777215
	.d24	5649426
	.d24	2179941

	.global	_byteswap_i32
_byteswap_i32:
	.long	0
	.long	4294967295
	.long	2018915346
	.long	558065031

	.global	_byteswap_i48
_byteswap_i48:
	.long	0
	.word	0
	.long	4294967295
	.word	65535
	.long	2018915346
	.word	48282
	.long	1703389643
	.word	8515

	.global	_byteswap_i64
_byteswap_i64:
	.quad	0
	.quad	-1
	.quad	-1167088121787636991
	.quad	1167088121787636990
