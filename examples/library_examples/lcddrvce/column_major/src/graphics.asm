	assume	adl=1

	section	.data

;-------------------------------------------------------------------------------
	; include 'ti84pceg.inc'
define ti? ti
namespace ti?

; Hardware Defines
?lcdWidth		:= 320
?lcdHeight		:= 240
?vRam			:= 0D40000h
?vRamEnd		:= 0D65800h
; System Calls
?boot.ClearVRAM		:= 0000374h
;LCD Ports
?pLcdRange		:= 04000h
?mpLcdRange		:= 0E30000h

?lcdTiming0		:= 0000h
?pLcdTiming0		:= pLcdRange + lcdTiming0
?mpLcdTiming0		:= mpLcdRange + lcdTiming0
?lcdTiming1		:= 0004h
?pLcdTiming1		:= pLcdRange + lcdTiming1
?mpLcdTiming1		:= mpLcdRange + lcdTiming1
?lcdTiming2		:= 0008h
?pLcdTiming2		:= pLcdRange + lcdTiming2
?mpLcdTiming2		:= mpLcdRange + lcdTiming2
?lcdTiming3		:= 000Ch
?pLcdTiming3		:= pLcdRange + lcdTiming3
?mpLcdTiming3		:= mpLcdRange + lcdTiming3

?lcdBase			:= 0010h
?pLcdBase		:= pLcdRange + lcdBase
?mpLcdBase		:= mpLcdRange + lcdBase
?lcdUpbase		:= 0010h
?pLcdUpbase		:= pLcdRange + lcdUpbase
?mpLcdUpbase		:= mpLcdRange + lcdUpbase
?lcdLpbase		:= 0014h
?pLcdLpbase		:= pLcdRange + lcdLpbase
?mpLcdLpbase		:= mpLcdRange + lcdLpbase

?lcdCtrl			:= 0018h
?pLcdCtrl		:= pLcdRange + lcdCtrl
?mpLcdCtrl		:= mpLcdRange + lcdCtrl
?lcdEn			:= 01h
?lcdTft			:= 20h
?lcdBpp1			:= 0000b or lcdTft or lcdEn
?lcdBpp2			:= 0010b or lcdTft or lcdEn
?lcdBpp4			:= 0100b or lcdTft or lcdEn
?lcdBpp8			:= 0110b or lcdTft or lcdEn
?lcdBpp16Alt		:= 1000b or lcdTft or lcdEn
?lcdBpp24		:= 1010b or lcdTft or lcdEn
?lcdBpp16		:= 1100b or lcdTft or lcdEn ; Default LCD mode
?lcdBpp12		:= 1110b or lcdTft or lcdEn
?lcdBgr			:= 100h
?lcdBigEndian		:= 200h
?lcdBigEndianPixels	:= 400h
?lcdPwr			:= 800h
?lcdIntVSync		:= 0000h
?lcdIntBack		:= 1000h
?lcdIntActiveVideo	:= 2000h
?lcdIntFront		:= 3000h
?lcdWatermark		:= 10000h
?lcdNormalMode		:= lcdPwr or lcdBgr or lcdBpp16

?lcdImsc			:= 001Ch
?pLcdImsc		:= pLcdRange + lcdImsc
?mpLcdImsc		:= mpLcdRange + lcdImsc
?lcdRis			:= 0020h
?pLcdRis			:= pLcdRange + lcdRis
?mpLcdRis		:= mpLcdRange + lcdRis
?lcdMis			:= 0024h
?pLcdMis			:= pLcdRange + lcdMis
?mpLcdMis		:= mpLcdRange + lcdMis
?lcdIcr			:= 0028h
?pLcdIcr			:= pLcdRange + lcdIcr
?mpLcdIcr		:= mpLcdRange + lcdIcr

?bLcdIntFuf		:= 1
?lcdIntFuf		:= 1 shl bLcdIntFuf
?bLcdIntLNBU		:= 2
?lcdIntLNBU		:= 1 shl bLcdIntLNBU
?bLcdIntVcomp		:= 3
?lcdIntVcomp		:= 1 shl bLcdIntVcomp
?bLcdIntMbErr		:= 4
?lcdIntMbErr		:= 1 shl bLcdIntMbErr

?lcdCurr			:= 002Ch
?pLcdCurr		:= pLcdRange + lcdCurr
?mpLcdCurr		:= mpLcdRange + lcdCurr
?lcdUpcurr		:= 002Ch
?pLcdUpcurr		:= pLcdRange + lcdUpcurr
?mpLcdUpcurr		:= mpLcdRange + lcdUpcurr
?lcdLpcurr		:= 0030h
?pLcdLpcurr		:= pLcdRange + lcdLpcurr
?mpLcdLpcurr		:= mpLcdRange + lcdLpcurr
?lcdPalette		:= 0200h
?pLcdPalette		:= pLcdRange + lcdPalette
?mpLcdPalette		:= mpLcdRange + lcdPalette

?lcdCrsrImage		:= 0800h
?pLcdCrsrImage		:= pLcdRange + lcdCrsrImage
?mpLcdCrsrImage		:= mpLcdRange + lcdCrsrImage
?lcdCrsrCtrl		:= 0C00h
?pLcdCrsrCtrl		:= pLcdRange + lcdCrsrCtrl
?mpLcdCrsrCtrl		:= mpLcdRange + lcdCrsrCtrl
?lcdCrsrConfig		:= 0C04h
?pLcdCrsrConfig		:= pLcdRange + lcdCrsrConfig
?mpLcdCrsrConfig		:= mpLcdRange + lcdCrsrConfig
?lcdCrsrPalette0		:= 0C08h
?pLcdCrsrPalette0	:= pLcdRange + lcdCrsrPalette0
?mpLcdCrsrPalette0	:= mpLcdRange + lcdCrsrPalette0
?lcdCrsrPalette1		:= 0C0Ch
?pLcdCrsrPalette1	:= pLcdRange + lcdCrsrPalette1
?mpLcdCrsrPalette1	:= mpLcdRange + lcdCrsrPalette1
?lcdCrsrXY		:= 0C10h
?pLcdCrsrXY		:= pLcdRange + lcdCrsrXY
?mpLcdCrsrXY		:= mpLcdRange + lcdCrsrXY
?lcdCrsrClip		:= 0C14h
?pLcdCrsrClip		:= pLcdRange + lcdCrsrClip
?mpLcdCrsrClip		:= mpLcdRange + lcdCrsrClip
?lcdCrsrImsc		:= 0C20h
?pLcdCrsrImsc		:= pLcdRange + lcdCrsrImsc
?mpLcdCrsrImsc		:= mpLcdRange + lcdCrsrImsc
?lcdCrsrIcr		:= 0C24h
?pLcdCrsrIcr		:= pLcdRange + lcdCrsrIcr
?mpLcdCrsrIcr		:= mpLcdRange + lcdCrsrIcr
?lcdCrsrRis		:= 0C28h
?pLcdCrsrRis		:= pLcdRange + lcdCrsrRis
?mpLcdCrsrRis		:= mpLcdRange + lcdCrsrRis
?lcdCrsrMis		:= 0C2Ch
?pLcdCrsrMis		:= pLcdRange + lcdCrsrMis
?mpLcdCrsrMis		:= mpLcdRange + lcdCrsrMis

end namespace

;-------------------------------------------------------------------------------
LcdSize            := ti.lcdWidth*ti.lcdHeight
; minimum stack size to provide for interrupts if moving the stack
InterruptStackSize := 4000
CurrentBuffer      := ti.mpLcdLpbase
TRASPARENT_COLOR   := 0
TEXT_FG_COLOR      := 0
TEXT_BG_COLOR      := 255
TEXT_TP_COLOR      := 255

;-------------------------------------------------------------------------------

macro s8 op, imm
	local i
 	i = imm
	assert i >= -128 & i < 128
	op, i
end macro

;-------------------------------------------------------------------------------
macro setSmcBytes name*
	local addr, data
	postpone
		virtual at addr
			irpv each, name
				if % = 1
					db %%
				end if
				assert each >= addr + 1 + 2*%%
				dw each - $ - 2
			end irpv
			load data: $-$$ from $$
		end virtual
	end postpone

	call	_SetSmcBytes
addr	db	data
end macro

macro setSmcBytesFast name*
	local temp, list
	postpone
		temp equ each
		irpv each, name
			temp equ temp, each
		end irpv
		list equ temp
	end postpone

	pop	de			; de = return vetor
	ex	(sp),hl			; l = byte
	ld	a,l			; a = byte
	match expand, list
		iterate expand
			if % = 1
				ld	hl,each
				ld	c,(hl)
				ld	(hl),a
			else
				ld	(each),a
			end if
		end iterate
	end match
	ld	a,c			; a = old byte
	ex	de,hl			; hl = return vector
	jp	(hl)
end macro

macro setSmcBytesInline name*
	local temp, list
	postpone
		temp equ each
		irpv each, name
			temp equ temp, each
		end irpv
		list equ temp
	end postpone

	match expand, list
		iterate expand
			ld	(each),a
		end iterate
	end match
end macro

macro setSmcWordsInline name*
	local temp, list
	postpone
		temp equ each
		irpv each, name
			temp equ temp, each
		end irpv
		list equ temp
	end postpone

	match expand, list
		iterate expand
			ld	(each),hl
		end iterate
	end match
end macro

macro smcByte name*, addr: $-1
	local link
	link := addr
	name equ link
end macro

macro smcWord name*, addr: $-3
	local link
	link := addr
	name equ link
end macro

;-------------------------------------------------------------------------------
	public	_graphics_Begin
_graphics_Begin:
; Sets up the graphics canvas
; Arguments:
;  arg0: bpp mode to start in
; Returns:
;  None
	call	ti.boot.ClearVRAM	; clear the screen
lcdGraphxMode := ti.lcdWatermark+ti.lcdIntFront+ti.lcdPwr+ti.lcdBgr+ti.lcdBpp8
	ld	de,lcdGraphxMode
	ld	hl,CurrentBuffer
SetGraphics:
	ld	bc,ti.vRam
	ld	(hl),bc			; set the current draw to the screen
assert CurrentBuffer and -$100 = ti.mpLcdRange
	ld	l,ti.lcdCtrl
	ld	(hl),de			; set lots of control parameters
	ld	l,ti.lcdTiming0+1
	ld	de,_LcdTiming
assert ti.vRam and $FF = 0
	ld	b,8+1			; +1 because c = 0, so first ldi will
					; decrement b
.ExchangeTimingLoop:			; exchange stored and active timing
	ld	a,(de)
	ldi
	dec	hl
	ld	(hl),a
	inc	hl
	djnz	.ExchangeTimingLoop
;	jp	_graphics_SetDefaultPalette	; setup the default palette

;-------------------------------------------------------------------------------
	private	_graphics_SetDefaultPalette
_graphics_SetDefaultPalette:
; Sets up the default palette where H=L
; Arguments:
;  None
; Returns:
;  None
	ld	de,ti.mpLcdPalette	; address of mmio palette
	ld	b,e			; b = 0
.loop:
	ld	a,b
	rrca
	xor	a,b
	and	a,224
	xor	a,b
	ld	(de),a
	inc	de
	ld	a,b
	rla
	rla
	rla
	ld	a,b
	rra
	ld	(de),a
	inc	de
	inc	b
	jr	nz,.loop		; loop for 256 times to fill palette
	ret

;-------------------------------------------------------------------------------
	public	_graphics_End
_graphics_End:
; Closes the graphics library and sets up for the TI-OS
; Arguments:
;  None
; Returns:
;  None
	call	ti.boot.ClearVRAM	; clear the screen
	ld	de,ti.lcdNormalMode
	ld	hl,ti.mpLcdBase
	jr	SetGraphics		; restore the screen mode

;-------------------------------------------------------------------------------
	public	_graphics_SetColor
_graphics_SetColor:
; Sets the global color index for all routines
; Arguments:
;  arg0 : Global color index
; Returns:
;  Previous global color index
	setSmcBytesFast _Color

;-------------------------------------------------------------------------------
	public	_graphics_SetPixel
_graphics_SetPixel:
; Sets the color pixel to the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  None
	call	_graphics_Wait
	or	a, a
	sbc	hl, hl
	ld	de, 3
	add	hl, de
	add	hl, sp
	ld	bc, (hl)	; bc = x coordinate
	add	hl, de		; move to next argument
	ld	e, (hl)		; e = y coordinate
	ld	hl, -ti.lcdWidth
	add	hl, bc
	ret	c			; return if out of bounds
	ld	hl, -ti.lcdHeight
	add	hl, de
	ret	c			; return if out of bounds
	ld	hl, (CurrentBuffer)
	
	dec	b		; tests if x >= 256
	jr	nz, .x_lt_256
	ld	d, $F0		; ti.lcdHeight * 256
.x_lt_256:
	ld	b, ti.lcdHeight
	mlt	bc
	ld	hl, (CurrentBuffer)
	add	hl, bc		; add x cord
	add	hl, de		; add y cord
	ld	(hl), 0		; get the actual pixel
smcByte _Color
	public	_graphics_Color
_graphics_Color := $-1
	ret

;-------------------------------------------------------------------------------
	public	_graphics_SetDraw
_graphics_SetDraw:
; Forces drawing routines to operate on the offscreen buffer
; or to operate on the visible screen
; Arguments:
;  arg0: buffer or screen
; Returns:
;  None
	pop	de
	ex	(sp),hl
	ld	a,l
	or	a,a
	ld	hl,(ti.mpLcdBase)	; get current base
	ld	bc,ti.vRam
	jr	z,.match
	sbc	hl,bc
	jr	nz,.swap		; if not the same, swap
.set:
	ld	bc,ti.vRam + LcdSize
.swap:
	ld	(CurrentBuffer),bc
	ex	de,hl
	jp	(hl)
.match:
	sbc	hl,bc
	jr	z,.swap			; if the same, swap
	jr	.set

;-------------------------------------------------------------------------------
	public	_graphics_Wait
_graphics_Wait:
; Waits for the screen buffer to finish being displayed after _graphics_SwapDraw
; Arguments:
;  None
; Returns:
;  None
	ret				; will be SMC'd into push hl
	push	af
	ld	a,(ti.mpLcdRis)
	bit	ti.bLcdIntVcomp,a
	jr	nz,.WaitDone
	push	de
.WaitLoop:
.ReadLcdCurr:
	ld	a,(ti.mpLcdCurr + 2)	; a = *mpLcdCurr>>16
	ld	hl,(ti.mpLcdCurr + 1)	; hl = *mpLcdCurr>>8
	sub	a,h
	jr	nz,.ReadLcdCurr		; nz ==> lcdCurr may have updated
					;        mid-read; retry read
	ld	de,(CurrentBuffer + 1)
	sbc	hl,de
	ld	de,-LcdSize shr 8
	add	hl,de
	jr	nc,.WaitLoop
	pop	de
.WaitDone:
	ld	a,$C9			; ret
	ld	(_graphics_Wait),a		; disable wait logic
	pop	af
	pop	hl
	ret

;-------------------------------------------------------------------------------
	public	_graphics_SwapDraw
_graphics_SwapDraw:
; Swaps the roles of the screen and drawing buffers
; Arguments:
;  None
; Returns:
;  None
	ld	iy,ti.mpLcdRange
.WaitLoop:
	bit	ti.bLcdIntLNBU,(iy + ti.lcdRis)
	jr	z,.WaitLoop
assert ti.vRam and $FF = 0
assert LcdSize and $FF = 0
	ld	bc,(iy-ti.mpLcdRange+CurrentBuffer+1) ; bc = old_draw>>8
.LcdSizeH := (LcdSize shr 8) and $FF
assert .LcdSizeH and ti.lcdIntVcomp
assert .LcdSizeH and ti.lcdIntLNBU
	ld	a,.LcdSizeH		; a = LcdSize>>8
	ld	(iy+ti.lcdBase+1),bc	; screen = old_draw
	ld	(iy+ti.lcdIcr),a	; clear interrupt statuses to wait for
	xor	a,c			; a = (old_draw>>8)^(LcdSize>>8)
	ld	c,a			; c = (old_draw>>8)^(LcdSize>>8)
	inc	b
	res	1,b			; b = (old_draw>>16)+1&-2
					; assuming !((old_draw>>16)&2):
					;   = (old_draw>>16)^1
					;   = (old_draw>>16)^(LcdSize>>16)
					; bc = (old_draw>>8)^(LcdSize>>8)
					;    = new_draw>>8
	ld	(iy-ti.mpLcdRange+CurrentBuffer+1),bc
	ld	hl,_graphics_Wait
	ld	(hl),$E5		; push hl; enable wait logic
	push	hl
	dec	sp
	pop	hl
	ld	l,$CD			; call *
					; hl = first 3 bytes of call _Wait
	dec	sp
	dec	sp			; sp -= 3 to match pop hl later
	pop	hl
	ret

;-------------------------------------------------------------------------------
	private	_SetSmcBytes
_SetSmcBytes:
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	ld	b,(hl)
.loop:
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex	de,hl
	inc.s	hl
	add	hl,de
	ld	a,(hl)
	ld	(hl),c
	ex	de,hl
	djnz	.loop
	ret

;-------------------------------------------------------------------------------
	private	_LcdTiming
_LcdTiming:
;	db	14 shl 2		; PPL shl 2
	db	7			; HSW
	db	87			; HFP
	db	63			; HBP
	dw	(0 shl 10)+319		; (VSW shl 10)+LPP
	db	179			; VFP
	db	0			; VBP
	db	(0 shl 6)+(0 shl 5)+0	; (ACB shl 6)+(CLKSEL shl 5)+PCD_LO
;  H = ((PPL+1)*16)+(HSW+1)+(HFP+1)+(HBP+1) = 240+8+88+64 = 400
;  V = (LPP+1)+(VSW+1)+VFP+VBP = 320+1+179+0 = 500
; CC = H*V*PCD*2 = 400*500*2*2 = 800000
; Hz = 48000000/CC = 60
