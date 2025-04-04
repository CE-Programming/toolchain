	assume	adl = 1

	section	.data

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
