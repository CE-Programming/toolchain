;-------------------------------------------------------------------------------

include '../include/library.inc'
include '../include/include_library.inc'

;-------------------------------------------------------------------------------

; version number
library GRAPHY, 0

include_library '../lcddrvce/lcddrvce.asm'

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export gfy_Begin		
	export gfy_End
	export gfy_SetColor
	export gfy_SetDefaultPalette
	export gfy_SetPalette
	export gfy_FillScreen
	export gfy_SetPixel
	export gfy_GetPixel
	export gfy_GetDraw
	export gfy_SetDraw
	export gfy_SwapDraw
	export gfy_Blit
	export gfy_BlitColumns
	export gfy_BlitRectangle
	export gfy_PrintChar
	export gfy_PrintInt
	export gfy_PrintUInt
	export gfy_PrintString
	export gfy_PrintStringXY
	export gfy_SetTextXY
	export gfy_SetTextBGColor
	export gfy_SetTextFGColor
	export gfy_SetTextTransparentColor
	export gfy_SetFontData
	export gfy_SetFontSpacing
	export gfy_SetMonospaceFont
	export gfy_GetStringWidth
	export gfy_GetCharWidth
	export gfy_GetTextX
	export gfy_GetTextY
	export gfy_Line
	export gfy_HorizLine
	export gfy_VertLine
	export gfy_Circle
	export gfy_FillCircle
	export gfy_Rectangle
	export gfy_FillRectangle
	export gfy_Line_NoClip
	export gfy_HorizLine_NoClip
	export gfy_VertLine_NoClip
	export gfy_FillCircle_NoClip
	export gfy_Rectangle_NoClip
	export gfy_FillRectangle_NoClip
	export gfy_SetClipRegion
	export gfy_GetClipRegion
	export gfy_ShiftDown
	export gfy_ShiftUp
	export gfy_ShiftLeft
	export gfy_ShiftRight
	export gfy_Tilemap
	export gfy_Tilemap_NoClip
	export gfy_TransparentTilemap
	export gfy_TransparentTilemap_NoClip
	export gfy_TilePtr
	export gfy_TilePtrMapped
	export gfy_AllocSprite
	export gfy_Sprite
	export gfy_TransparentSprite
	export gfy_Sprite_NoClip
	export gfy_TransparentSprite_NoClip
	export gfy_GetSprite
	export gfy_ScaledSprite_NoClip
	export gfy_ScaledTransparentSprite_NoClip
	export gfy_FlipSpriteY
	export gfy_FlipSpriteX
	export gfy_RotateSpriteC
	export gfy_RotateSpriteCC
	export gfy_RotateSpriteHalf
	export gfy_Polygon
	export gfy_Polygon_NoClip
	export gfy_FillTriangle
	export gfy_FillTriangle_NoClip
;-------------------------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------------------------
	export gfy_SetTextScale
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
	export gfy_SetTransparentColor
;	export gfy_ZeroScreen
	export gfy_SetTextConfig
	export gfy_GetSpriteChar
;-------------------------------------------------------------------------------
; v4 functions
;-------------------------------------------------------------------------------
	export gfy_Lighten
	export gfy_Darken
;-------------------------------------------------------------------------------
; v5 functions
;-------------------------------------------------------------------------------
	export gfy_SetFontHeight
	export gfy_ScaleSprite
	export gfy_FloodFill
;-------------------------------------------------------------------------------
; v6 functions
;-------------------------------------------------------------------------------
	export gfy_RLETSprite
	export gfy_RLETSprite_NoClip
	export gfy_ConvertFromRLETSprite
	export gfy_ConvertToRLETSprite
	export gfy_ConvertToNewRLETSprite
;-------------------------------------------------------------------------------
; v7 functions
;-------------------------------------------------------------------------------
	export gfy_RotateScaleSprite
	export gfy_RotatedScaledTransparentSprite_NoClip
	export gfy_RotatedScaledSprite_NoClip
;-------------------------------------------------------------------------------
; v8 functions
;-------------------------------------------------------------------------------
	export gfy_SetCharData
;-------------------------------------------------------------------------------
; v9 functions
;-------------------------------------------------------------------------------
	export gfy_Wait
;-------------------------------------------------------------------------------
; v10 functions
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v11 functions
;-------------------------------------------------------------------------------
	export gfy_CopyRectangle
;-------------------------------------------------------------------------------
; v12 functions
;-------------------------------------------------------------------------------
	export gfy_Ellipse
	export gfy_Ellipse_NoClip
	export gfy_FillEllipse
	export gfy_FillEllipse_NoClip
;-------------------------------------------------------------------------------
; v13 functions
;-------------------------------------------------------------------------------
	export gfy_RotatedScaledTransparentSprite
	export gfy_RotatedScaledSprite

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

;-------------------------------------------------------------------------------
macro mIsHLLessThanDE?
	or	a,a
	sbc	hl,de
	add	hl,hl
	jp	po,$+5
	ccf
end macro
macro mIsHLLessThanBC?
	or	a,a
	sbc	hl,bc
	add	hl,hl
	jp	po,$+5
	ccf
end macro
macro s8 op, imm
	local i
	i = imm
	assert i >= -128 & i < 128
	op, i
end macro

;-------------------------------------------------------------------------------
wait_quick.usages_counter = 0

macro wait_quick?
	call	_WaitQuick
	wait_quick.usages_counter = wait_quick.usages_counter + 1
end macro

postpone
	wait_quick.usages := wait_quick.usages_counter
end postpone

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

;-------------------------------------------------------------------------------
; gfy_Begin:

;-------------------------------------------------------------------------------
gfy_internal_Begin:
; Sets up the graphics canvas
; Arguments:
;  arg0: bpp mode to start in
; Returns:
;  None
	call	ti.boot.ClearVRAM	; clear the screen
lcdGraphxMode := ti.lcdWatermark+ti.lcdIntFront+ti.lcdPwr+ti.lcdBgr+ti.lcdBpp8
	ld	de,lcdGraphxMode
	ld	hl,CurrentBuffer
SetGfy:
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
;	jp	gfy_SetDefaultPalette	; setup the default palette
assert $ = gfy_SetDefaultPalette

;-------------------------------------------------------------------------------
gfy_SetDefaultPalette: ; COPIED_FROM_GRAPHX
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
; gfy_End:

;-------------------------------------------------------------------------------
gfy_internal_End:
; Closes the graphics library and sets up for the TI-OS
; Arguments:
;  None
; Returns:
;  None
	call	ti.boot.ClearVRAM	; clear the screen
	ld	de,ti.lcdNormalMode
	ld	hl,ti.mpLcdBase
	jr	SetGfy			; restore the screen mode

;-------------------------------------------------------------------------------
gfy_AllocSprite: ; COPIED_FROM_GRAPHX
; Allocates space for a new sprite
; Arguments:
;  arg0 : width
;  arg1 : height
;  arg2 : pointer to malloc routine
; Returns:
;  Pointer to allocated sprite, first byte width, second height
	ld	bc,3
	push	bc
	pop	hl
	add	hl,sp
	ld	e,(hl)			; e = width
	add	hl,bc
	ld	d,(hl)			; d = height
	add	hl,bc
	ld	hl,(hl)			; hl = malloc
	push	de
	mlt	de			; de = width * height
	inc	de			; +2 to store width and height
	inc	de			; de = width * height + 2
	push	de
	call	_indcallHL		; hl = malloc(width * height + 2)
	pop	de			; de = width * height + 2
	add	hl,de			; this should never carry
	sbc	hl,de			; check if malloc failed (hl == 0)
	pop	de			; e = width, d = height
	ret	z			; abort if malloc failed
	ld	(hl),de			; store width and height
	ret

;-------------------------------------------------------------------------------
gfy_SetClipRegion: ; COPIED_FROM_GRAPHX
; Sets the clipping region for clipped routines
; Arguments:
;  arg0 : Xmin
;  arg1 : Ymin
;  arg2 : Xmax
;  arg3 : Ymax
; Returns:
;  None
	; clip against the actual LCD screen
	xor	a,a
	sbc	hl,hl
	ld	(_ClipRegion.XMin),hl
	inc	h
	ld	l,ti.lcdWidth-256
	ld	(_ClipRegion.XMax),hl
	ld	(_ClipRegion.YMin),a
	ld	a,ti.lcdHeight
	ld	(_ClipRegion.YMax),a
	ld	iy,0
	add	iy,sp
	call	_ClipRegion		; iy points to the start of the arguments
	ld	hl,(iy+3)
	ld	c,(iy+6)
	ld	de,(iy+9)
	ld	a,(iy+12)
	jr	nc,.apply
	xor	a,a
	ld	c,a
	sbc	hl,hl
	ld	de,ti.lcdWidth
	ld	a,ti.lcdHeight
.apply:
	setSmcWordsInline _XMin
	ex	de,hl
	setSmcWordsInline _XMax
	dec	hl
	setSmcWordsInline _XMaxMinus1
	inc	hl
	sbc	hl,de
	setSmcWordsInline _XSpan
	setSmcBytesInline _YMax
	dec	a
	setSmcBytesInline _YMaxMinus1
	inc	a
	sub	a,c
	setSmcBytesInline _YSpan
	ld	a,c
	setSmcBytesInline _YMin
	ret

;-------------------------------------------------------------------------------
gfy_Lighten: ; COPIED_FROM_GRAPHX
; Lightens a 16 bit 1555 color (0 = white, 255 = same color)
; Arguments:
;  arg0 : 16 bit color
;  arg1 : 8 bit change amount
; Returns:
;  16 bit color value
	pop	de			; de = return vector
	pop	bc			; bc = color
	ex	(sp),hl			; l = amt
	push	bc
	push	de
					; Strategy: lighten(color, amt) = ~darken(~color, amt)
					; Darken the inverted color
	ld	a,c
	cpl
	ld	c,a
	ld	a,b
	cpl
	ld	b,a			; bc = ~color
	call	_Darken			; hl = darken(~color, amt)
	ld	a,l			; Invert the darken result for the lighten result
	cpl
	ld	l,a
	ld	a,h
	cpl
	ld	h,a			; hl = ~darken(~color, amt) = lighten(color, amt)
	ret

;-------------------------------------------------------------------------------
gfy_Darken: ; COPIED_FROM_GRAPHX
; Darkens a 16 bit 1555 color (0 = black, 255 = same color)
; Arguments:
;  arg0 : 16 bit color
;  arg1 : 8 bit change amount
; Returns:
;  16 bit color value
	pop	de			; de = return vector
	pop	bc			; bc = color
	ex	(sp),hl			; l = amt
	push	bc
	push	de			; Comments assume 1555 RGB color
_Darken:
	push	bc			; Calculate the output blue value
	ld	a,c			; a = color & $FF
	ld	c,l			; c = amt
	and	a,31
	ld	h,a			; h = blue
	mlt	hl			; hl = blue * amt
	ld	de,128			; de = 128
	add	hl,de			; hl = blue * amt + 128
	ld	l,h
	ld	h,d			; hl = (blue * amt + 128) / 256 = blue_out
	ex	(sp),hl			; hl = color, tmp1 = blue_out
					; Isolate the input red value
	ld	a,h			; a = color >> 8
	rra				; a = color >> 9
	and	a,62
	ld	b,a			; b = red << 1
					; Calculate the output green value
	add.s	hl,hl
	rla				; a & 1 = green & 1
	add	hl,hl
	add	hl,hl			; hl = color << 3
	rra
	ld	a,h
	rla
	and	a,63
	ld	h,a			; h = green
	ld	l,c			; l = amt
	mlt	hl			; hl = green * amt
	add	hl,de			; hl = green * amt + 128
	ld	l,h			; l = (green * amt + 128) / 256 = green_out
					; Calculate the output red value
	mlt	bc			; bc = red * amt << 1
	inc	b			; b = (red * amt + 128 << 1) / 256
	srl	b			; b = (red * amt + 128) / 256 = red_out
					; Position the output red and green bits
	add	hl,hl
	add	hl,hl			; l = green_out << 2
	ld	h,b			; h = red_out
	add	hl,hl
	add	hl,hl			; hl = (red_out << 10) | (green_out << 4)
	bit	4,l
	jr	z,.out
	set	7,h
	res	4,l			; hl = (green_out & 1 << 15) | (red_out << 10) | (green_out >> 1 << 5)
.out:
					; Add the output blue value (no positioning necessary) for the final output color
	pop	bc			; bc = blue_out
	add	hl,bc			; hl = color_out
	ret

;-------------------------------------------------------------------------------
gfy_SetColor: ; COPIED_FROM_GRAPHX
; Sets the global color index for all routines
; Arguments:
;  arg0 : Global color index
; Returns:
;  Previous global color index
	setSmcBytesFast _Color

;-------------------------------------------------------------------------------
gfy_SetTransparentColor: ; COPIED_FROM_GRAPHX
; Sets the global transparent color index for all routines
; Arguments:
;  arg0 : Transparent color index
; Returns:
;  Previous transparent color index

	setSmcBytes _TransparentColor

;-------------------------------------------------------------------------------
gfy_FillScreen: ; COPIED_FROM_GRAPHX
; Fills the screen with the specified color index
; Arguments:
;  arg0 : Color index
; Returns:
;  None

FillScreen_PushesPerIter := 115		; see fillscreen.xlsx for derivation
FillScreen_NumIters      := (LcdSize-InterruptStackSize)/(FillScreen_PushesPerIter*3)
FillScreen_BytesToPush   := FillScreen_PushesPerIter*3*FillScreen_NumIters
FillScreen_BytesToLddr   := LcdSize-FillScreen_BytesToPush

	ld	iy,0
	add	iy,sp			; iy = original sp
	ld	hl,FillScreen_FastCode_SrcEnd-1
	ld	de,FillScreen_FastCode_DestEnd-1
	ld	bc,FillScreen_FastCode_SrcSize
	lddr				; copy fast code after push run
					; de = pointer second to last push
					; bc = 0
	push	de
	pop	hl
	inc	hl			; hl  = pointer to last push (already copied)
	ld	c,FillScreen_PushesPerIter-1
	lddr				; fill push run
	ld	a,$E1
	ld	(de),a			; write initial pop hl
	ld	hl,(CurrentBuffer)
	ld	de,LcdSize
	add	hl,de			; hl = end (exclusive) of buffer
	ld	de,(iy+1)		; deu = color
	ld	d,(iy+3)		; d = color
	ld	e,d			; e = color
	ld	b,FillScreen_NumIters	; b = number of fast code iterations
	call	gfy_Wait
	ld	sp,hl			; sp = end (exclusive) of buffer
	call	_FillScreen_FastCode_Dest ; do fast fill
	sbc	hl,hl
	add	hl,sp			; hl = pointer to last byte fast-filled
	ld	sp,iy			; sp = original sp
	push	hl
	pop	de
	dec	de			; de = pointer to first byte to slow-fill
	ld	bc,FillScreen_BytesToLddr
	lddr				; finish with slow fill
	ret

_FillScreen_FastCode_Src:
	org	ti.mpLcdCrsrImage
_FillScreen_FastCode_Dest:
	org	$ + 1
.loop:
	push	de
	org	$ + FillScreen_PushesPerIter - 1
	djnz	.loop
	jp	(hl)

FillScreen_FastCode_DestEnd  := $
FillScreen_FastCode_DestSize := FillScreen_FastCode_DestEnd-_FillScreen_FastCode_Dest
FillScreen_FastCode_SrcSize  := FillScreen_FastCode_DestSize-(FillScreen_PushesPerIter-1+1)
	org _FillScreen_FastCode_Src+FillScreen_FastCode_SrcSize
FillScreen_FastCode_SrcEnd   := $

;-------------------------------------------------------------------------------
gfy_ZeroScreen: ; COPIED_FROM_GRAPHX
; Fills the screen with color index 0
; Arguments:
;  None
; Returns:
;  None
	ld	l,0
	push	hl
	call	gfy_FillScreen
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfy_SetPalette: ; COPIED_FROM_GRAPHX
; Sets the palette colors
; Arguments:
;  arg0 : Pointer to palette
;  arg1 : Size of palette in bytes
;  arg2 : Palette index to insert at
; Returns:
;  None
	pop	iy			; iy = return vector
	pop	de			; de = src
	pop	bc			; bc = size
	ex	(sp),hl			; l = offset
	push	bc
	push	de
	ld	a,l
assert ti.mpLcdPalette and 1 = 0
	ld	hl,ti.mpLcdPalette shr 1
	ld	l,a			; hl = (palette >> 1) + offset
	add	hl,hl			; hl = &palette[offset] = dest
	ex	de,hl			; de = dest, hl = src
	ldir
	jp	(iy)

;-------------------------------------------------------------------------------
gfy_GetPixel:	; (uint24_t x, uint8_t y)
; Gets the color index of a pixel
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  Color index of X,Y coordinate
	ld	hl, 3
	add	hl, sp		; hl = &x
	inc.s	de
	ld	c, (hl)
	inc	hl
	ld	b, (hl)		; bc = (uint16_t)x
	inc	hl
	inc	hl		; hl = &y
	ld	e, (hl)		; e = y
	ld	d, 0
_GetPixel:
	; UBC = 0xx
	; E = 00y
	dec	b		; tests if x >= 256
	jr	nz, .x_lt_256
	ld	d, $F0		; ti.lcdHeight * 256
.x_lt_256:
	ld	b, ti.lcdHeight
	mlt	bc
	ld	hl, (CurrentBuffer)
	add	hl, bc		; add x cord
	add	hl, de		; add y cord
; No clipping is necessary, because if the pixel is offscreen, the result is
; undefined. All that is necessary is to ensure that there are no side effects
; of reading outside of the buffer. In this case, the largest possible offset
; into the buffer is (256 + 255) * lcdHeight + 255 = 122895 bytes. Even in the case
; that the current buffer is the second half of VRAM, the largest that this
; pointer can be is $D52C00 + 122895 = $D70C0F. This goes beyond the end of
; mapped RAM, but only into unmapped memory with no read side effects.
	ld	a,(hl)	; a = buffer[y][x]
	ret

;-------------------------------------------------------------------------------
gfy_SetPixel:
; Sets the color pixel to the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  None

	or	a, a
_NoCarry_gfy_SetPixel:
	sbc	hl, hl
_HLZero_gfy_SetPixel:
	ld	de, 3
	add	hl, de
	add	hl, sp
	ld	bc, (hl)	; bc = x coordinate
	add	hl, de		; move to next argument
	ld	e, (hl)		; e = y coordinate		
_SetPixel:
	wait_quick
_SetPixel_NoWait:
	ld	hl, -ti.lcdWidth
	add	hl, bc
	ret	c			; return if out of bounds
	ld	hl, -ti.lcdHeight
	add	hl, de
	ret	c			; return if out of bounds
_SetPixel_NoClip_NoWait:
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
	ret

;-------------------------------------------------------------------------------
gfy_Rectangle_NoClip: ; optimize this
; Draws an unclipped rectangle outline with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	push	ix			; need to use ix because lines use iy
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	push	bc
	push	de
	push	hl
	call	gfy_HorizLine_NoClip	; top horizontal line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	gfy_VertLine_NoClip	; left vertical line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	add	hl,bc			; add x and width
	dec	hl
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	gfy_VertLine_NoClip	; right vertical line
	ld	de,(ix+6)
	ld	hl,(ix+9)
	ld	bc,(ix+15)
	add	hl,bc
	dec	hl			; add y and height
	ld	bc,(ix+12)
	push	bc
	push	hl
	push	de
	call	gfy_HorizLine_NoClip	; bottom horizontal line
	ld	sp,ix
	pop	ix
	ret
;-------------------------------------------------------------------------------
gfy_Rectangle: ; COPIED_FROM_GRAPHX
; Draws an clipped rectangle outline with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	push	ix			; need to use ix because lines use iy
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	push	bc
	push	de
	push	hl
	call	gfy_HorizLine		; top horizontal line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	gfy_VertLine		; left vertical line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	add	hl,bc			; add x and width
	dec	hl
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	gfy_VertLine		; right vertical line
	ld	de,(ix+6)
	ld	hl,(ix+9)
	ld	bc,(ix+15)
	add	hl,bc
	dec	hl			; add y and height
	ld	bc,(ix+12)
	push	bc
	push	hl
	push	de
	call	gfy_HorizLine		; bottom horizontal line
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_FillRectangle: ; COPIED_FROM_GRAPHX
; Draws a clipped rectangle with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+9)		; hl = width
	ld	de,(iy+3)		; de = x coordinate
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(iy+12)		; hl = height
	ld	de,(iy+6)		; de = y coordinate
	add	hl,de
	ld	(iy+12),hl
	call	_ClipRegion
	ret	c			; return if offscreen or degenerate
	ld	de,(iy+3)
	ld	hl,(iy+9)
	sbc	hl,de
	push	hl
	ld	de,(iy+6)
	ld	hl,(iy+12)
	sbc	hl,de
	pop	bc			; bc = new width
	ld	a,l			; a = new height
	ld	hl,(iy+3)		; hl = new x, de = new y
	jr	_FillRectangle_NoClip

;-------------------------------------------------------------------------------
gfy_FillRectangle_NoClip:
; Draws an unclipped rectangle with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy, 0
	add	iy, sp
	ld	a, (iy+12)		; a = height
	or	a, a
	ret	z			; make sure height is not 0
	ld	bc, (iy+9)		; bc = width
	sbc	hl, hl
	adc	hl, bc
	ret	z			; make sure width is not 0
	ld	hl, (iy+3)		; hl = x coordinate
	ld	e, (iy+6)		; e = y coordinate
_FillRectangle_NoClip:
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset
	ex	de, hl			; de -> place to begin drawing
	push	de

	ld	hl, _Color
	; divide (width-1) by 2, and set Z flag
	dec	bc
	srl	b
	rr	c
	ld	iyl, c
	ld	c, a
	ld	b, 0
	; iyl = (width-1)/2
	; carry = (width-1)%2
	; zero = iyl==0
	; a = bc = height
	wait_quick
	ldi				; check if we only need to draw 1 pixel
	pop	hl
	jp	po, .skip
	ldir
.skip:
	jr	z, .final
	push	af	; save carry
.loop:
	ld	c, ti.lcdHeight - 1
	ex	de, hl
	add	hl, bc
	ex	de, hl
	ld	c, a
	lddr
	inc	hl
	ld	c, ti.lcdHeight + 1
	ex	de, hl
	add	hl, bc
	ex	de, hl
	ld	c, a
	ldir
	dec	hl
	dec	iyl
	jr	nz, .loop
	pop	af	; restore carry
.final:
	ret	nc
	ld	c, ti.lcdHeight - 1
	ex	de, hl
	add	hl, bc
	ex	de, hl
	ld	c, a
	lddr
	ret

;-------------------------------------------------------------------------------
gfy_HorizLine:
; Draws an clipped horizontal line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)
	ld	de,ti.lcdHeight
smcWord _YMax
	sbc	hl,de			; subtract maximum y
	ld	de,ti.lcdHeight		; add y bounds span
smcWord _YSpan
	add	hl,de
	ret	nc			; return if not within y bounds
	ld	hl,(iy+9)
	ld	de,(iy+3)
	add	hl,de
	push	hl
	ld	hl,0
smcWord _XMin
	call	_Maximum		; get minimum x
	ex	(sp),hl
	ld	de,ti.lcdWidth
smcWord _XMax
	call	_Minimum		; get maximum x
	pop	de
	scf
	sbc	hl,de
	ret	c
	inc	hl
	push	hl
	pop	bc			; bc = length
	ex	de,hl
	jr	_HorizLine_NoClip_NotDegen_StackY
;-------------------------------------------------------------------------------
gfy_HorizLine_NoClip:
; Draws an unclipped vertical line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy, 0
	add	iy, sp
	ld	bc, (iy+9)		; bc = length
_HorizLine_NoClip_StackXY:
	xor	a, a
	or	a, b
	or	a, c
_HorizLine_NoClip_MaybeDegen_StackXY:
	ret	z			; abort if length == 0
_HorizLine_NoClip_NotDegen_StackXY:
	ld	hl,(iy+3)		; hl = x
_HorizLine_NoClip_NotDegen_StackY:
	ld	e, (iy+6)		; e = y
_HorizLine_NoClip_NotDegen:
	wait_quick
_HorizLine_NoClip_NotDegen_NoWait:
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset
	
_HorizLine_NoClip_Draw_NoWait:
	ld	de, ti.lcdHeight
	; swap b and c
	ld	a, b
	ld	b, c
	ld	c, a

	ld	a, 0
smcByte _Color
.loop:
	ld	(hl), a		; loop for width
	add	hl, de
	djnz	.loop
	dec	c
	ret	nz	; length < 256
	ld	b, 0
	jr	.loop

;-------------------------------------------------------------------------------
gfy_VertLine:
; Draws an clipped vertical line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	de,ti.lcdWidth
smcWord _XMax
	sbc	hl,de			; subtract maximum x
	ld	de,ti.lcdWidth
smcWord _XSpan
	add	hl,de			; add x bounds span
	ret	nc			; return if not within x bounds
	ld	hl,(iy+9)
	ld	de,(iy+6)
	add	hl,de
	push	hl
	ld	hl,0
smcWord _YMin
	call	_Maximum		; get minimum y
	ex	(sp),hl
	ld	de,ti.lcdHeight
smcWord _YMax
	call	_Minimum		; get maximum y
	pop	de
	ld	a,l
	sub	a,e
	ret	c			; return if not within y bounds
	ld	bc, 0
	ld	c, a
	jr	_VertLine_NoClip_MaybeDegen_StackX	; from GraphX
;-------------------------------------------------------------------------------
gfy_VertLine_NoClip:
; Draws an unclipped horizontal line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy, 0
	add	iy, sp
	ld	bc, 0
	ld	c, (iy+9)		; bc = length
_VertLine_NoClip_StackXY:
	sbc	hl, hl
	ex	de, hl
	sbc	hl, hl
	adc	hl, bc
	ld	e, (iy+6)		; e = y
_VertLine_NoClip_MaybeDegen_StackX:
	ret	z			; abort if length == 0
_VertLine_NoClip_NotDegen_StackX:
	ld	hl, (iy+3)		; hl = x
_VertLine_NoClip_NotDegen:
	wait_quick
_VertLine_NoClip_NotDegen_NoWait:
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset

_VertLine_NoClip_Draw:
	ld	(hl), 0
smcByte _Color
	cpi
	ex	de, hl
	ld	hl, -1
	add	hl, de
; Delay 1-wide early return for consistent register output values.
	ret	po
	ldir
	ret

;-------------------------------------------------------------------------------
gfy_SetDraw: ; COPIED_FROM_GRAPHX
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
gfy_GetDraw: ; COPIED_FROM_GRAPHX
; Gets the current drawing state
; Arguments:
;  None
; Returns:
;  Returns true if drawing on the buffer
	ld	a,(ti.mpLcdBase+2)	; comparing upper byte only is sufficient
	ld	hl,CurrentBuffer+2
	xor	a,(hl)			; always 0 or 1
	ret

;-------------------------------------------------------------------------------
_WaitQuick:
	ex	(sp),hl			; hl saved, hl = return vector
	push	de			; de saved
	ld	de,gfy_Wait
	dec	hl
	dec	hl
	dec	hl
	ld	(hl),de			; call _WaitQuick -> call _Wait
	dec	hl			; hl = callee
	ex	de,hl			; de = callee
	ld	hl,_WriteWaitQuickSMC
.WriteWaitsTail = $-3
	ld	(hl),$22		; ld (callee),hl
	inc	hl
	ld	(hl),de
	inc	hl
	inc	hl
	inc	hl
	ld	(.WriteWaitsTail),hl
	ex	de,hl			; hl = callee
	pop	de			; de restored
	ex	(sp),hl			; return vector = callee, hl restored
; Fall through to gfy_Wait, but don't let it return immediately. Even if it ends
; up not waiting, it will re-write the quick wait SMC, including for the callee.
	push	hl
;	jr	gfy_Wait+1		; emulated by dummifying next instruction:
	db	$2E			; ret || push hl -> ld l,*

;-------------------------------------------------------------------------------
gfy_Wait: ; COPIED_FROM_GRAPHX
; Waits for the screen buffer to finish being displayed after gfy_SwapDraw
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
	ld	(gfy_Wait),a		; disable wait logic
	pop	af
	ld	hl,$0218		; jr $+4
_WriteWaitQuickSMC:
repeat wait_quick.usages
; Each call _WaitQuick will replace the next unmodified 4-byte entry with
; ld (_WaitQuick_callee_x),hl.
	pop	hl
	ret
	nop
	nop
end repeat
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfy_SwapDraw: ; COPIED_FROM_GRAPHX
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
	ld	hl,gfy_Wait
	ld	(hl),$E5		; push hl; enable wait logic
	push	hl
	dec	sp
	pop	hl
	ld	l,$CD			; call *
					; hl = first 3 bytes of call _Wait
	dec	sp
	dec	sp			; sp -= 3 to match pop hl later
	jr	_WriteWaitQuickSMC

;-------------------------------------------------------------------------------
gfy_FillEllipse_NoClip: ; COPIED_FROM_GRAPHX
	ld	hl,gfy_HorizLine_NoClip
	db	$FD			; ld hl,* -> ld iy,*

;-------------------------------------------------------------------------------
gfy_FillEllipse: ; COPIED_FROM_GRAPHX
	ld	hl,gfy_HorizLine
	ld	(_ellipse_line_routine_1),hl
	ld	(_ellipse_line_routine_2),hl
	ld	hl,_ellipse_draw_line
	ld	(_ellipse_loop_draw_2),hl
	ld	(_ellipse_loop_draw_3),hl
	ld	hl,_ellipse_ret
	ld	(_ellipse_loop_draw_1),hl
	jr	_Ellipse
	
;-------------------------------------------------------------------------------
gfy_Ellipse_NoClip: ; COPIED_FROM_GRAPHX
	ld	hl,_SetPixel_NoClip_NoWait
	db	$FD		; ld hl,* -> ld iy,*

;-------------------------------------------------------------------------------
gfy_Ellipse: ; COPIED_FROM_GRAPHX
	ld	hl,_SetPixel_NoWait
	ld	(_ellipse_pixel_routine_1),hl
	ld	(_ellipse_pixel_routine_2),hl
	ld	(_ellipse_pixel_routine_3),hl
	ld	(_ellipse_pixel_routine_4),hl
	ld	hl,_ellipse_draw_pixels
	ld	(_ellipse_loop_draw_1),hl
	ld	(_ellipse_loop_draw_3),hl
	ld	hl,_ellipse_ret
	ld	(_ellipse_loop_draw_2),hl

el_x		:= 3		; Current X coordinate of the ellipse
el_y		:= 6		; Current Y coordinate of the ellipse
el_a2		:= 9		; X radius squared
el_b2		:= 12		; Y radius squared
el_fa2		:= 15		; X radius squared * 4
el_fb2		:= 18		; Y radius squared * 4
el_sigma	:= 21		; Sigma
el_sigma_1	:= 24		; Offset to be added to sigma in loop 1
el_sigma_2	:= 27		; Offset to be added to sigma in loop 2
el_temp1	:= 30		; X radius as "int" instead of "uint8_t"
el_comp_a	:= 33		; b2 * x
el_comp_b	:= 36		; a2 * y
el_sigma_diff1	:= 39		; Offset to be added to sigma in loop 1
el_sigma_diff2	:= 42		; Offset to be added to sigma in loop 2

_Ellipse:
; Draws an ellipse, either filled or not, either clipped or not
; Arguments:
;  arg0 : X coordinate (ix+6)
;  arg1 : Y coordinate (ix+9)
;  arg2 : X radius (ix+12)
;  arg3 : Y radius (ix+15)
; Returns:
;  None
	push	ix
	ld	ix,0
	add	ix,sp
	lea	hl,ix - 42
	ld	sp,hl
	
; First, setup all the variables
	ld	a,(ix + 12)
	or	a,a
	jr	nz,.valid_x_radius
.return:
	ld	sp,ix
	pop	ix
	ret
.valid_x_radius:
	ld	l,a
	ld	h,a
	mlt	hl
	ld	(ix - el_a2),hl		; int a2 = a * a;
	add	hl,hl
	ld	(ix - el_sigma_diff2),hl; Save a2 * 2 for later
	add	hl,hl
	ld	(ix - el_fa2),hl	; int fa2 = 4 * a2;
	ld	a,(ix + 15)
	or	a,a
	jr	z,.return		; Make sure Y radius is not 0
	ld	e,a
	ld	d,1
	mlt	de
	ld	(ix - el_y),de		; int y = b;
	ld	hl,(ix - el_a2)
	ld	d,l
	ld	l,e
	mlt	de
	mlt	hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,de
	add	hl,hl
	add	hl,hl
	ex	de,hl
	ld	hl,(ix - el_fa2)
	or	a,a
	sbc	hl,de
	ld	(ix - el_sigma_1),hl	; int sigma_add_1 = fa2 * (1 - b);
	ld	l,a
	ld	h,a
	mlt	hl
	ld	(ix - el_b2),hl		; int b2 = b * b;
	add	hl,hl
	ld	(ix - el_sigma_diff1),hl	; Save b2 * 2 for later
	add	hl,hl
	ld	(ix - el_fb2),hl	; int fb2 = 4 * b2;
	ld	c,a
	ld	b,2
	mlt	bc
	or	a,a
	sbc	hl,hl
	ld	(ix - el_x),hl		; int x = 0;
	ld	(ix - el_comp_a),hl
	inc	hl
	sbc	hl,bc
	ld	de,(ix - el_a2)
	call	_MultiplyHLDE
	ld	bc,(ix - el_b2)
	add	hl,bc
	add	hl,bc
	ld	(ix - el_sigma),hl	; int sigma = 2 * b2 + a2 * (1 - 2 * b);
	ld	e,(ix + 12)
	ld	d,1
	mlt	de
	ld	(ix - el_temp1),de	; Save int a for later
	or	a,a
	sbc	hl,hl
	inc	hl
	sbc	hl,de
	ld	de,(ix - el_fb2)
	call	_MultiplyHLDE
	ld	(ix - el_sigma_2),hl	; int sigma_add_2 = fb2 * (1 - a);

	ld	hl,(ix - el_a2)
	ld	de,(ix - el_y)
	call	_MultiplyHLDE
	ld	(ix - el_comp_b),hl
	
	wait_quick

.main_loop1:
	call	0
_ellipse_loop_draw_1 := $-3

; Eventually change sigma and y
	ld	hl,(ix - el_sigma)
	add	hl,hl
	jr	c,.loop1_jump		; if (sigma >= 0) {

	call	0
_ellipse_loop_draw_2 := $-3

	ld	hl,(ix - el_sigma)	; sigma += sigma_add_1;
	ld	de,(ix - el_sigma_1)
	add	hl,de
	ld	(ix - el_sigma),hl
	ld	hl,(ix - el_fa2)
	add	hl,de
	ld	(ix - el_sigma_1),hl	; sigma_add_1 += fa2;
	ld	hl, (ix - el_y)
	dec	hl
	ld	(ix - el_y),hl		; y--;
	ld	hl,(ix - el_comp_b)
	ld	de,(ix - el_a2)
	or	a,a
	sbc	hl,de
	ld	(ix - el_comp_b),hl
.loop1_jump:				; }
; Change sigma and increment x
	ld	hl,(ix - el_sigma_diff1)
	ld	de,(ix - el_fb2)
	add	hl,de
	ld	(ix - el_sigma_diff1),hl
	ld	de,(ix - el_sigma)
	add	hl,de
	ld	(ix - el_sigma),hl	; sigma += b2 * (4 * x + 6);
	ld	hl,(ix - el_x)
	inc	hl
	ld	(ix - el_x),hl		; x++;

; Update the comparison operands
	ld	hl,(ix - el_comp_a)
	ld	de,(ix - el_b2)
	add	hl,de
	ld	(ix - el_comp_a),hl
	ld	de,(ix - el_comp_b)

; And compare
	ld	bc,0x800000		; b2 * x <= a2 * y so hl <= de
	add	hl,bc
	ex	de,hl			; de <= hl
	add	hl,bc
	or	a,a
	sbc	hl,de
	jq	nc,.main_loop1

; Update few variables for the next loop
	ld	hl, (ix - el_temp1)
	ld	(ix - el_x),hl		; x = a
	ld	e,l
	or	a,a
	sbc	hl,hl
	ld	(ix - el_y),hl		; y = 0
	ld	(ix - el_comp_a),hl
	ld	d,2
	mlt	de
	inc	hl
	sbc	hl,de
	ld	de,(ix - el_b2)
	call	_MultiplyHLDE
	ld	de,(ix - el_a2)
	add	hl,de
	add	hl,de
	ld	(ix - el_sigma), hl

	ld	hl,(ix - el_b2)
	ld	de,(ix - el_temp1)
	call	_MultiplyHLDE
	ld	(ix - el_comp_b),hl

.main_loop2:
	call	0
_ellipse_loop_draw_3 := $-3

; Eventually update sigma and x
	ld	hl,(ix - el_sigma)
	add	hl,hl
	jr	c,.loop2_jump		; if (sigma >= 0) {
	ld	hl,(ix - el_sigma)
	ld	de,(ix - el_sigma_2)
	add	hl,de
	ld	(ix - el_sigma),hl	; sigma += sigma_add_2;
	ld	hl,(ix - el_fb2)
	add	hl,de
	ld	(ix - el_sigma_2),hl	; sigma_add_2 += fb2;
	ld	hl, (ix - el_x)
	dec	hl
	ld	(ix - el_x),hl		; x--;
	ld	hl,(ix - el_comp_b)
	ld	de,(ix - el_b2)
	or	a,a
	sbc	hl,de
	ld	(ix - el_comp_b),hl
.loop2_jump:
; Change sigma and increment y
	ld	hl,(ix - el_sigma_diff2)
	ld	de,(ix - el_fa2)
	add	hl,de
	ld	(ix - el_sigma_diff2),hl
	ld	de,(ix - el_sigma)
	add	hl,de
	ld	(ix - el_sigma),hl	; sigma += a2 * (4 * y + 6);
	ld	hl,(ix - el_y)
	inc	hl
	ld	(ix - el_y),hl		; y++;
	ld	hl,(ix - el_comp_a)
	ld	de,(ix - el_a2)
	add	hl,de
	ld	(ix - el_comp_a),hl

; Compare the boolean operators
	ld	de,(ix - el_comp_b)
	ld	bc,0x800000
	add	hl,bc
	ex	de,hl
	add	hl,bc
	or	a,a
	sbc	hl,de
	jq	nc,.main_loop2

	ld	sp,ix
	pop	ix
_ellipse_ret:
	ret

_ellipse_draw_pixels:
; bc = x coordinate
; e = y coordinate
	ld	hl,(ix + 9)
	ld	de,(ix - el_y)
	add	hl,de
	ex	de,hl
	push	de
	ld	hl,(ix + 6)
	ld	bc,(ix - el_x)
	add	hl,bc
	push	hl
	pop	bc
	call	_SetPixel_NoWait	; xc + x, yc + y
_ellipse_pixel_routine_1 := $-3
	pop	de
	ld	hl,(ix + 6)
	ld	bc,(ix - el_x)
	or	a,a
	sbc	hl,bc
	push	hl
	pop	bc
	push	bc
	call	_SetPixel_NoWait	; xc - x, yc + y
_ellipse_pixel_routine_2 := $-3
	pop	bc
	ld	hl,(ix + 9)
	ld	de,(ix - el_y)
	or	a,a
	sbc	hl,de
	ex	de,hl
	push	de
	call	_SetPixel_NoWait	; xc - x, yc - y
_ellipse_pixel_routine_3 := $-3
	pop	de
	ld	hl,(ix + 6)
	ld	bc,(ix - el_x)
	add	hl,bc
	push	hl
	pop	bc
	jp	_SetPixel_NoWait	; xc + x, yc - y
_ellipse_pixel_routine_4 := $-3

_ellipse_draw_line:
	ld	hl,(ix - el_x)
	add	hl,hl
	push	hl
	ld	hl,(ix + 9)
	ld	de,(ix - el_y)
	or	a,a
	sbc	hl,de
	push	hl
	ld	hl,(ix + 6)
	ld	de,(ix - el_x)
	or	a,a
	sbc	hl,de
	push	hl
	call	0
_ellipse_line_routine_1 := $-3
	pop	hl
	pop	hl
	pop	hl
	ld	hl,(ix - el_x)
	add	hl,hl
	push	hl
	ld	hl,(ix + 9)
	ld	de,(ix - el_y)
	add	hl,de
	push	hl
	ld	hl,(ix + 6)
	ld	de,(ix - el_x)
	or	a,a
	sbc	hl,de
	push	hl
	call	0
_ellipse_line_routine_2 := $-3
	pop	hl
	pop	hl
	pop	hl
	ret
	

;-------------------------------------------------------------------------------
_Circle:
.sectors:
	ld	bc,(iy+3)
	ld	hl,(iy-6)
	add	hl,bc
	push	hl
	push	hl
	pop	bc
	ld	de,(iy+6)
	ld	hl,(iy-3)
	add	hl,de
	ex	de,hl
	push	de
	call	_SetPixel_NoWait
	ld	bc,(iy+6)
	ld	hl,(iy-6)
	add	hl,bc
	ex	de,hl
	push	de
	ld	bc,(iy+3)
	ld	hl,(iy-3)
	add	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_NoWait
	ld	bc,(iy-6)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_SetPixel_NoWait
	pop	de
	ld	bc,(iy-3)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_NoWait
	pop	bc
	pop	de
	call	_SetPixel_NoWait
	pop	de
	ld	bc,(iy-6)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_NoWait
	ld	bc,(iy-3)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_SetPixel_NoWait
	pop	de
	pop	bc
	call	_SetPixel_NoWait
	ld	bc,(iy-3)
	inc	bc
	ld	(iy-3),bc
	ld	bc,(iy-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,.cmp0
	jp	pe,.cmp1
	jr	.cmp2
.cmp0:
	jp	po,.cmp1
.cmp2:
	ld	hl,(iy-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	.next
.cmp1:
	ld	bc,(iy-6)
	dec	bc
	ld	(iy-6),bc
	ld	hl,(iy-3)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	ld	de,(iy-9)
	add	hl,de
.next:
	ld	(iy-9),hl
	ld	bc,(iy-3)
	ld	hl,(iy-6)
	or	a,a
	sbc	hl,bc
	jp	p,.check
	jp	pe,.sectors
	jr	.exit
.check:
	jp	po,.sectors
.exit:
	ld	sp,iy
	ret
gfy_Circle: ; COPIED_FROM_GRAPHX
; Draws a clipped circle outline
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	ld	iy, 0
	add	iy, sp
	lea	hl, iy - 9
	ld	sp, hl
	ld	bc, (iy + 9)
	sbc	hl, hl
	adc	hl, bc	; carry won't be set since HL is zero here
	jr	z, _Circle.exit
	ld	(iy - 6), bc
	sbc	hl, hl
	ld	(iy - 3), hl
	inc	hl
	sbc	hl, bc	; HL = 1 - BC
	call	gfy_Wait
	jr	_Circle.next

;-------------------------------------------------------------------------------
fc_x := 9
fc_y := 6
_FillCircle:
.fillsectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(.circle0),hl
	push	hl	; len
	ld	bc,(ix-3)
	ld	hl, (ix + fc_x)
	or	a,a
	sbc	hl,bc
	ld	(.circle1),hl
	push	hl	; x
	ld	bc,(ix-6)
	ld	hl, (ix + fc_y)
	add	hl,bc
	push	hl	; y
	call	gfy_VertLine
	ld	hl,0
.circle0 := $-3
	push	hl	; len
	ld	hl,0
.circle1 := $-3
	push	hl	; x
	ld	bc,(ix-6)
	ld	hl, (ix + fc_y)
	or	a,a
	sbc	hl,bc
	push	hl	; y
	call	gfy_VertLine
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(.circle2),hl
	push	hl	; len
	ld	bc,(ix-6)
	ld	hl, (ix + fc_x)
	or	a,a
	sbc	hl,bc
	ld	(.circle3),hl
	push	hl	; x
	ld	bc,(ix-3)
	ld	hl, (ix + fc_y)
	add	hl,bc
	push	hl	; y
	call	gfy_VertLine
	ld	hl,0
.circle2 := $-3
	push	hl	; len
	ld	hl,0
.circle3 := $-3
	push	hl	; x
	ld	bc,(ix-3)
	ld	hl, (ix + fc_y)
	or	a,a
	sbc	hl,bc
	push	hl	; y
	call	gfy_VertLine
	lea	hl,ix-9
	ld	sp,hl
	ld	bc,(ix-3)
	inc	bc
	ld	(ix-3),bc
	ld	bc,(ix-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,.cmp0
	jp	pe,.cmp2
	jr	.cmp1
.cmp0:
	jp	po,.cmp2
.cmp1:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	.cmp3
.cmp2:
	ld	bc,(ix-6)
	dec	bc
	ld	(ix-6),bc
	ld	hl,(ix-3)
	ld	de,(ix-9)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	add	hl,de
.cmp3:
	ld	(ix-9),hl
	ld	bc,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	jp	p,.check
	jp	pe,.fillsectors
	ld	sp,ix
	pop	ix
	ret
.check:
	jp	po,.fillsectors
.ResetStack:
	ld	sp,ix
	pop	ix
	ret
gfy_FillCircle: ; MODIFIED_FROM_GRAPHX
; Draws an clipped circle
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 9
	ld	sp, hl
	ld	bc, (ix + 12)
	sbc	hl, hl
	adc	hl, bc	; carry won't be set since HL is zero here
	jr	z, _FillCircle.ResetStack
	ld	(ix - 6), bc
	sbc	hl, hl
	ld	(ix - 3), hl
	inc	hl
	sbc	hl, bc	; HL = 1 - BC
	jr	_FillCircle.cmp3

;-------------------------------------------------------------------------------
; not working at the moment
if 0

fcnc_x := 6
fcnc_y := 9
_FillCircle_NoClip:
.fillsectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(.circle0),hl
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+fcnc_y)
	add	hl,bc
	ld	e,l
	ld	bc,(ix-3)
	ld	hl,(ix+fcnc_x)
	or	a,a
	sbc	hl,bc
	ld	(.circle1),hl
	pop	bc
	ex	de, hl
	call	_VertLine_NoClip_NotDegen_NoWait
	ex	de, hl
	ld	bc,0
.circle0 := $-3
	ld	de,(ix-6)
	ld	hl,(ix+fcnc_y)
	or	a,a
	sbc	hl,de
	ld	e,l
	ld	hl,0
.circle1 := $-3
	ex	de, hl
	call	_VertLine_NoClip_NotDegen_NoWait
	ex	de, hl
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(.circle2),hl
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+fcnc_y)
	add	hl,bc
	ld	e,l
	ld	bc,(ix-6)
	ld	hl,(ix+fcnc_x)
	or	a,a
	sbc	hl,bc
	ld	(.circle3),hl
	pop	bc
	call	_VertLine_NoClip_NotDegen_NoWait
	ld	bc,0
.circle2 := $-3
	ld	de,(ix-3)
	ld	hl,(ix+fcnc_y)
	or	a,a
	sbc	hl,de
	ld	e,l
	ld	hl,0
.circle3 := $-3
	call	_VertLine_NoClip_NotDegen_NoWait
	ld	bc,(ix-3)
	inc	bc
	ld	(ix-3),bc
	ld	bc,(ix-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,.cmp0
	jp	pe,.cmp2
	jr	.cmp1
.cmp0:
	jp	po,.cmp2
.cmp1:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	.loop
.cmp2:
	ld	bc,(ix-6)
	dec	bc
	ld	(ix-6),bc
	ld	hl,(ix-3)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	ld	de,(ix-9)
	add	hl,de
.loop:
	ld	(ix-9),hl
	ld	bc,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	jp	nc,.fillsectors
.ResetStack:
	ld	sp,ix
	pop	ix
	ret
gfy_FillCircle_NoClip: ; MODIFIED_FROM_GRAPHX
; Draws an unclipped circle
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 9
	ld	sp, hl

	; ensure that Y is zeroed out
	xor	a, a
	ld	(ix + 10), a
	ld	(ix + 11), a

	ld	bc, (ix + 12)
	sbc	hl, hl
	adc	hl, bc	; carry won't be set since HL is zero here
	jr	z, _FillCircle_NoClip.ResetStack
	ld	(ix - 6), bc
	sbc	hl, hl
	ld	(ix - 3), hl
	inc	hl
	sbc	hl, bc	; HL = 1 - BC
	call	gfy_Wait
	jr	_FillCircle_NoClip.loop

else

_FillCircle_NoClip:
.fillsectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(.circle0),hl
	push	hl	; len
	ld	bc,(ix-3)
	ld	hl, (ix + fc_x)
	or	a,a
	sbc	hl,bc
	ld	(.circle1),hl
	push	hl	; x
	ld	bc,(ix-6)
	ld	hl, (ix + fc_y)
	add	hl,bc
	push	hl	; y
	call	gfy_VertLine_NoClip
	ld	hl,0
.circle0 := $-3
	push	hl	; len
	ld	hl,0
.circle1 := $-3
	push	hl	; x
	ld	bc,(ix-6)
	ld	hl, (ix + fc_y)
	or	a,a
	sbc	hl,bc
	push	hl	; y
	call	gfy_VertLine_NoClip
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(.circle2),hl
	push	hl	; len
	ld	bc,(ix-6)
	ld	hl, (ix + fc_x)
	or	a,a
	sbc	hl,bc
	ld	(.circle3),hl
	push	hl	; x
	ld	bc,(ix-3)
	ld	hl, (ix + fc_y)
	add	hl,bc
	push	hl	; y
	call	gfy_VertLine_NoClip
	ld	hl,0
.circle2 := $-3
	push	hl	; len
	ld	hl,0
.circle3 := $-3
	push	hl	; x
	ld	bc,(ix-3)
	ld	hl, (ix + fc_y)
	or	a,a
	sbc	hl,bc
	push	hl	; y
	call	gfy_VertLine_NoClip
	lea	hl,ix-9
	ld	sp,hl
	ld	bc,(ix-3)
	inc	bc
	ld	(ix-3),bc
	ld	bc,(ix-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,.cmp0
	jp	pe,.cmp2
	jr	.cmp1
.cmp0:
	jp	po,.cmp2
.cmp1:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	.cmp3
.cmp2:
	ld	bc,(ix-6)
	dec	bc
	ld	(ix-6),bc
	ld	hl,(ix-3)
	ld	de,(ix-9)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	add	hl,de
.cmp3:
	ld	(ix-9),hl
	ld	bc,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	jp	p,.check
	jp	pe,.fillsectors
	ld	sp,ix
	pop	ix
	ret
.check:
	jp	po,.fillsectors
.ResetStack:
	ld	sp,ix
	pop	ix
	ret
; reuse the implementation from gfy_FillCircle for now
gfy_FillCircle_NoClip: ; MODIFIED_FROM_GRAPHX
; Draws an clipped circle
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 9
	ld	sp, hl
	ld	bc, (ix + 12)
	sbc	hl, hl
	adc	hl, bc	; carry won't be set since HL is zero here
	jr	z, _FillCircle_NoClip.ResetStack
	ld	(ix - 6), bc
	sbc	hl, hl
	ld	(ix - 3), hl
	inc	hl
	sbc	hl, bc	; HL = 1 - BC
	jr	_FillCircle_NoClip.cmp3

end if

;-------------------------------------------------------------------------------
gfy_Line: ; COPIED_FROM_GRAPHX
; Draws an arbitrarily clipped line
; Arguments:
;  arg0: x0
;  arg0: y0
;  arg0: x1
;  arg0: y1
; Returns:
;  true if drawn, false if offscreen
	ld	iy,0
	add	iy,sp
	push	hl			; temp storage
	ld	hl,(iy+3)		; x0
	ld	de,(iy+6)		; y0
	call	_ComputeOutcode
	ld	(iy-1),a
	ld	hl,(iy+9)		; x1
	ld	de,(iy+12)		; y1
	call	_ComputeOutcode
	ld	(iy-2),a
CohenSutherlandLoop:
	ld	a,(iy-2)		; a = outcode1
.skip_ld_A:
	ld	b,(iy-1)		; b = outcode0
	tst	a,b
	jr	nz,TrivialReject	; if(outcode0|outcode1)
	or	a,a
	jr	nz,GetOutOutcode
	or	a,b
	jr	z,TrivialAccept
GetOutOutcode:				; select correct outcode
	push	af			; a = outoutcode
	rra
	jr	nc,.notop		; if (outcodeOut & TOP)
	ld	hl,ti.lcdHeight-1
smcWord _YMaxMinus1
	jr	ComputeNewX
.notop:
	rra
	jr	nc,NotBottom		; if (outcodeOut & BOTTOM)
	ld	hl,0
smcWord _YMin
ComputeNewX:
	push	hl
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc			; ymax_YMin - y0
	ex	de,hl
	ld	hl,(iy+9)
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc			; x0 - x1
	call	_MultiplyHLDE
	ex	de,hl			; (x0 - x1)*(ymax_YMin - y0)
	ld	hl,(iy+12)
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc			; y1 - y0
	push	hl
	pop	bc
	ex	de,hl
	call	_DivideHLBC		; ((x0 - x1)*(ymax_YMin - y0))/(y1 - y0)
	ld	bc,(iy+3)
	add	hl,bc			; (x) hl = x0 + ((x0 - x1)*(ymax_YMin - y0))/(y1 - y0)
	pop	de			; (y) de = ymax_YMin
	jr	FinishComputations
NotBottom:
	rra
	jr	nc,NotRight		; if (outcodeOut & RIGHT)
	ld	hl,ti.lcdWidth-1
smcWord _XMaxMinus1
	jr	ComputeNewY

TrivialReject:
	ld	sp, iy
	ret
TrivialAccept:
	ld	sp, iy
;	jr	_Line_NoClip		; line routine handler
	jp	gfy_Line_NoClip

NotRight:
	rra
	jr	nc,FinishComputations	; if (outcodeOut & LEFT)
	ld	hl,0
smcWord _XMin
ComputeNewY:
	push	hl
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc			; xmax_XMin - x0
	ex	de,hl
	ld	hl,(iy+12)
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc			; x1 - x0
	call	_MultiplyHLDE
	ex	de,hl			; (x1 - x0)*(xmax_XMin - x0)
	ld	hl,(iy+9)
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc			; y1 - y0
	push	hl
	pop	bc
	ex	de,hl
	call	_DivideHLBC		; ((x1 - x0)*(xmax_XMin - x0))/(y1 - y0)
	ld	bc,(iy+6)
	add	hl,bc
	ex	de,hl			; (y) de = y0 + ((x1 - x0)*(xmax_XMin - x0))/(y1 - y0)
	pop	hl			; (x) hl = ymax_YMin
FinishComputations:
	pop	af
	cp	a,(iy-1)
	jr	nz,OutcodeOutOutcode1
	ld	(iy+3),hl
	ld	(iy+6),de
	call	_ComputeOutcode
	ld	(iy-1),a		; b = outcode0
	jp	CohenSutherlandLoop
OutcodeOutOutcode1:
	ld	(iy+9),hl
	ld	(iy+12),de
	call	_ComputeOutcode
	ld	(iy-2),a		; c = outcode1
	jp	CohenSutherlandLoop.skip_ld_A

;-------------------------------------------------------------------------------
; gfy_Line_NoClip:

;-------------------------------------------------------------------------------
gfy_Blit: ; COPIED_FROM_GRAPHX
; Copies the buffer image to the screen and vice versa
; Arguments:
;  arg0 : Buffer to copy from (screen = 0, buffer = 1)
; Returns:
;  None
	pop	iy			; iy = return vector
	ex	(sp),hl
	ld	a,l			; a = buffer to blit from
	call	util.getbuffer		; determine blit buffers
	ld	bc,LcdSize
util.blit:
	call	gfy_Wait
	ldir				; just do it
	jp	(iy)

;-------------------------------------------------------------------------------
gfy_BlitColumns:
; Copies the buffer image to the screen and vice versa column wise
; Arguments:
;  arg0 : Buffer to copy from (screen = 0, buffer = 1)
;  arg1 : X coordinate
;  arg2 : Number of columns to copy
; Returns:
;  None
if 0

	pop	iy	; return address
	pop	bc
	ld	a, c	; A = buffer to blit from
	pop	de	; DE = num_columns
	ex	(sp), hl	; HL = x_loc
	push	de
	push	bc

	ld	bc, ti.lcdHeight * 256

	dec	d
	ld	d, b	; ti.lcdHeight
	mlt	de
	jr	nz, .DE_lt_256
	ex	de, hl
	add	hl, bc
	ex	de, hl
.DE_lt_256:
	push	de	; bytes to copy

	dec	h
	ld	h, b	; ti.lcdHeight
	mlt	hl
	jr	nz, .HL_lt_256
	add	hl, bc
.HL_lt_256:
	push	hl	; offset

	call	util.getbuffer		; determine blit buffers

	pop	bc	; offset
	add	hl, bc
	ex	de, hl
	add	hl, bc
	ex	de, hl
	pop	bc	; bytes to copy
	jr	util.blit

else
; This version saves 2F and 2 bytes

	pop	iy	; return address
	pop	bc
	ld	a, c	; A = buffer to blit from
	pop	hl	; HL = num_columns

	ld	bc, ti.lcdHeight * 256

	dec	h
	ld	h, b	; ti.lcdHeight
	mlt	hl
	jr	nz, .Columns_lt_256
	add	hl, bc
.Columns_lt_256:
	ex	(sp), hl	; HL = x_loc, (SP) = bytes to copy

	dec	h
	ld	h, b	; ti.lcdHeight
	mlt	hl
	jr	nz, .X_lt_256
	add	hl, bc
.X_lt_256:
	push	hl	; offset

	call	util.getbuffer		; determine blit buffers

	pop	bc	; offset
	add	hl, bc
	ex	de, hl
	add	hl, bc
	ex	de, hl
	pop	bc	; bytes to copy
	push	af, af, af	; restore SP :(
	jr	util.blit

end if

;-------------------------------------------------------------------------------
gfy_BlitRectangle:
; Copies the buffer image to the screen and vice versa rectangularly
; Arguments:
;  arg0 : Buffer to copy from (screen = 0, buffer = 1)
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Width
;  arg4 : Height
; Returns:
;  None

	ld	iy, 0
	add	iy, sp

	ld	bc, ti.lcdHeight * 256

	ld	hl, (iy + 6) ; x coordinate
	dec	h
	ld	h, b	; ti.lcdHeight
	mlt	hl
	jr	nz, .x_lt_256
	add	hl, bc
.x_lt_256:
	push	hl	; offset

	ld	a, (iy + 3)	; a = buffer to blit from
	call	util.getbuffer	; determine blit buffers
	
	; buffers will be 0xD40000 or 0xD52C00
	ld	a, (iy + 9) ; y coordinate
	; adds A to HL and DE
	ld	l, a
	ld	e, a

	pop	bc
	add	hl, bc
	ex	de, hl
	add	hl, bc
	ex	de, hl

	ld	bc, (iy + 12)	; width
	ld	a, (iy + 15)	; height
	ld	iyl, a
	; A = 240 - A
	sub	a, ti.lcdHeight
	neg
	ld	iyh, a	; jump

	ld	a, c	; width % 256
	or	a, a	; does with = 256?
	jr	nz, .not_256
	ld	b, a	; ld b, 0
.not_256:
	push	bc
	ld	bc, 0

	; IYL = height
	; IYH = jump
	; A = width % 256

	call	gfy_Wait
.loop:
	ld	c, iyl
	ldir
	ld	c, iyh
	add	hl, bc
	ex	de, hl
	add	hl, bc
	ex	de, hl
	dec	a
	jr	nz, .loop
	pop	af
	dec	a	; A = width % 256
	ret	nz
	push	af
	jr	.loop

;-------------------------------------------------------------------------------
; gfy_CopyRectangle:

;-------------------------------------------------------------------------------
; gfy_ShiftLeft:

;-------------------------------------------------------------------------------
; gfy_ShiftUp:

;-------------------------------------------------------------------------------
; gfy_ShiftRight:

;-------------------------------------------------------------------------------
; gfy_ShiftDown:

;-------------------------------------------------------------------------------
gfy_GetClipRegion: ; COPIED_FROM_GRAPHX
; Arguments:
;  Pointer to struct
; Returns:
;  False if offscreen
	ld	hl,3
	add	hl,sp
	ld	iy,(hl)
	lea	iy, iy - 3
	call	_ClipRegion		; get the clipping region
	sbc	a,a			; return false if offscreen (0)
	inc	a
	ret

;-------------------------------------------------------------------------------
; gfy_ScaledSprite_NoClip:

;-------------------------------------------------------------------------------
; gfy_ScaledTransparentSprite_NoClip:

; ...

	cp	a,TRASPARENT_COLOR
smcByte _TransparentColor

;-------------------------------------------------------------------------------
gfy_TransparentSprite:
; Draws a transparent sprite with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	push	ix			; save ix sp
	call	_ClipCoordinates
	jr	nc, .culled
.transparent_color := $+1
	ld	a, TRASPARENT_COLOR
smcByte _TransparentColor
	wait_quick
.loop:
	ld	c, iyh	; (.next)

	call	_TransparentPlot	; call the transparent routine
	ld	c, ixl	; (.amount)
	add	hl, bc	; move to next line
	
	ld	c, ixh	; (.jump)
	ex	de, hl
	add	hl, bc	; move to next column
	ex	de, hl

	dec	iyl
	jr	nz, .loop
.culled:
	pop	ix
	ret

; Opaque unrolled 4 times
; Transparent unrolled 4 times
_TransparentPlot_Opaque:		; routine to handle transparent plotting
	ldi
	ret	po
	cp	a,(hl)
	jr	z,_TransparentPlot_Transparent
	ldi
	ret	po
	cp	a,(hl)
	jr	z,_TransparentPlot_Transparent
	ldi
	ret	po
	cp	a,(hl)
	jr	z,_TransparentPlot_Transparent
	ldi
	ret	po
	cp	a,(hl)
	jr	nz,_TransparentPlot_Opaque
_TransparentPlot_Transparent:
	inc	de
	inc	hl
	dec	c
	ret	z
_TransparentPlot:
	cp	a,(hl)
	jr	nz,_TransparentPlot_Opaque
	inc	de
	inc	hl
	dec	c
	ret	z
	cp	a,(hl)
	jr	nz,_TransparentPlot_Opaque
	inc	de
	inc	hl
	dec	c
	ret	z
	cp	a,(hl)
	jr	nz,_TransparentPlot_Opaque
	inc	de
	inc	hl
	dec	c
	ret	z
	cp	a,(hl)
	jr	z,_TransparentPlot_Transparent
	jr	_TransparentPlot_Opaque

;-------------------------------------------------------------------------------
gfy_Sprite:
; Places an sprite on the screen as fast as possible with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	push	ix			; save ix sp
	call	_ClipCoordinates
	jr	nc, .culled
	ld	a, iyl	; new width
	wait_quick
.loop:
	ld	c, iyh	; (.next)
	ldir

	ld	c, ixl	; (.amount)
	add	hl, bc	; move to next line

	ld	c, ixh	; (.jump)
	ex	de, hl
	add	hl, bc	; move to next column
	ex	de, hl

	dec	a
	jr	nz, .loop
.culled:
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_Sprite_NoClip:
; Places an sprite on the screen as fast as possible
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	ld	iy, 0
	lea	bc, iy + 0
	add	iy, sp
	ld	hl, (iy + 6)	; hl = x
	ld	e, (iy + 9)	; e = y
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset
	ex	de, hl		; de = start draw location

	ld	hl, (iy + 3)	; hl = sprite structure
	ld	c, (hl)		; sprite width
	inc	hl
	ld	a, (hl)		; sprite height
	ld	iyh, a
	inc	hl
	; calculate jump
	ld	a, ti.lcdHeight
	sub	a, iyh
	ld	iyl, c
	wait_quick
	; A = jump
	; IYH = height
	; IYL = width
.loop:
	ld	c, iyh	; height
	ldir
	ld	c, a	; jump
	ex	de, hl
	add	hl, bc	; next column
	ex	de, hl
	dec	iyl
	jr	nz, .loop
	ret

;-------------------------------------------------------------------------------
; gfy_GetSprite:
; ; Grabs the data from the current draw buffer and stores it in another buffer
; ; Arguments:
; ;  arg0 : Pointer to storage buffer
; ;  arg1 : X coordinate
; ;  arg2 : Y coordinate
; ; Returns:
; ;  Pointer to resultant sprite
; 	ld	iy, 0
; 	lea	bc, iy + 0
; 	add	iy, sp

; 	bit	1, (iy + 7)
; 	jr	z,.next_x
; 	ld	hl, (iy + 6)
; 	ld	de, (-ti.lcdHeight)*512
; 	add	hl, de
; 	ld	(iy + 6), hl
; .next_x:

; 	ld	hl, (iy + 6)	; hl = x
; 	ld	e, (iy + 9)	; e = y
; 	ld	d, h		; maybe ld d, 0
; 	dec	h		; tests if x >= 256
; 	ld	h, ti.lcdHeight
; 	jr	nz, .x_lt_256
; 	ld	d, h		; ld d, ti.lcdHeight * 256
; .x_lt_256:
; 	mlt	hl
; 	ex.s	de, hl		; clear upper byte of DE
; 	add	hl, de		; add y cord
; 	ld	de, (CurrentBuffer)
; 	add	hl, de		; add buffer offset

; 	bit	0, (iy + 10)
; 	jr	z,.next_y
; 	ld	de,-256
; 	add	hl,de			; fix if negative
; .next_y:

; 	ld	de,(iy+3)
; 	push	de
; 	inc	de
; 	ld	a,(de)
; 	ld	(.amount),a		; amount to copy per line
; 	ld	c,a
; 	ld	a,ti.lcdHeight
; 	sub	a,c
; 	ld	c,a
; 	ld	(.offset),bc	; the amount to add to get to the next line
; 	dec	de
; 	ld	a,(de)
; 	inc	de
; 	inc	de
; .loop:
; 	ld	bc,0
; .amount := $-3
; 	ldir				; copy the data into the struct data
; 	ld	bc,0
; .offset := $-3
; 	add	hl,bc
; 	dec	a
; 	jr	nz,.loop
; 	pop	hl
; 	ret

if 0
gfy_GetSprite:
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	de, ti.lcdHeight
	ld	hl, (iy + 6)	; x
	; don't want to deal with sign extension problems so I will just use
	; the 24bit multiply routine for now.
	call	_MultiplyHLDE
	ld	de, (iy + 9)	; y
	add	hl, de
	ld	de, (CurrentBuffer)
	add	hl, de
	push	hl
	ld	iy, (iy + 3)	; sprite pointer
	ld	hl, ti.lcdHeight
	ld	bc, 0
	ld	a, (iy + 0)
	ld	c, (iy + 1)
	or	a, a
	sbc	hl, bc
	push	hl
	pop	ix
	lea	de, iy + 2
	pop	hl
	push	iy		; return value
	ld	iy, 0
	ld	iyl, c
.loop:
	lea	bc, iy
	ldir
	lea	bc, ix
	add	hl, bc
	dec	a
	jr	nz, .loop
	pop	hl
	pop	ix
	ret
else
gfy_GetSprite:
	ld	iy, 0
	add	iy, sp
	ld	de, ti.lcdHeight
	ld	hl, (iy + 6)	; x
	; don't want to deal with sign extension problems so I will just use
	; the 24bit multiply routine for now.
	call	_MultiplyHLDE
	ld	de, (iy + 9)	; y
	add	hl, de
	ld	de, (CurrentBuffer)
	add	hl, de
	push	hl		; (iy - 3), dst
	ex	de, hl
	ld	hl, (iy + 3)	; sprite pointer
	ld	a, ti.lcdHeight
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	inc	hl
	sub	a, c
	ex	de, hl
	sbc	hl, hl
	ld	l, a
	ld	a, b
	ex	(sp), hl	; (iy - 3), jump | dst , (iy - 3)
	ex	(sp), ix	; (iy - 3), ix   | jump, (iy - 3)
	push	iy		; (iy - 6), return value
	ld	iy, 0
	ld	iyl, c
.loop:
	lea	bc, iy
	ldir
	lea	bc, ix
	add	hl, bc
	dec	a
	jr	nz, .loop
	pop	hl	; return value, (iy - 6)
	pop	ix	; ix, (iy - 3)
	ret
end if

;-------------------------------------------------------------------------------
gfy_TransparentSprite_NoClip:
; Draws a transparent sprite to the current buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	ld	iy, 0
	lea	bc, iy + 0
	add	iy, sp
	ld	hl, (iy + 6)	; hl = x
	ld	e, (iy + 9)	; e = y
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset
	ex	de, hl		; de -> place to draw
	ld	hl,(iy+3)

	ld	a,(hl)
	ld	iyh, a		; iyh = width of sprite
	inc	hl

	ld	a,(hl)
	ld	(.next),a
	cpl
	add	a, ti.lcdHeight + 1
	ld	iyl, a		; jump

	inc	hl		; hl -> sprite_data

	ld	a,TRASPARENT_COLOR
smcByte _TransparentColor
	wait_quick
.loop:
	ld	c,0
.next := $-1
	call	_TransparentPlot	; call the plotter
	ld	c, iyl
	ex	de, hl
	add	hl, bc			; next column
	ex	de, hl
	dec	iyh			; loop for width
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
_ClipCoordinates:
; Clipping stuff
; Arguments:
;  arg0 : Pointer to sprite structure
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  IXL : How much to add to the sprite per iteration
;  IXH : Column increment
;  IYL : New sprite width
;  IYH : New sprite height
;  BCU : 0
;  B   : 0
;  HL  : Sprite pixel pointer
;  DE  : Buffer pixel pointer
;  NC  : If offscreen
	ld	ix, 6			; get pointer to arguments
	add	ix, sp
	ld	hl, (ix + 3)		; hl -> sprite data
	ld	iy, (hl)		; iyl = width, iyh = height

; CLIP X COORDINATE
	ld	bc,0
smcWord _XMin
	ld	hl,(ix+6)		; hl = x coordinate
;	or	a,a
	sbc	hl,bc
	ex	de,hl			; de = x coordinate relative to min x
	ld	hl,ti.lcdWidth		; hl = clip_width
smcWord _XSpan
	xor	a,a
	ld	b,a			; UBC and B are zero here
	ld	c,iyl			; bc = width
	sbc	hl,bc			; get difference between clip_width and width
	dec	c			; bc = width - 1
	jr	nc,.notwider
	or	a,a
	sbc	hl,de			; is partially clipped both left and right?
	jr	nc,.xclip
	sub	a,e			; a = negated relative x
	add	hl,de			; use clip_width as the draw width, and clip left
	jr	.clipleft
.notwider:
	sbc	hl,de			; is fully onscreen horizontally?	
	jr	nc,.xclipped		; a = 0 for bytes to add per iteration
.xclip:
	add	hl,bc			; is partially clipped right?
	ex	de,hl			; e = new width - 1, hl = relative x
	jr	c,.clipright
	sub	a,l			; a = negated relative x
.clipleft:
	add	hl,bc			; is partially clipped left?
	ret	nc			; return if offscreen
	ex	de,hl			; e = new width - 1

	ld	c,a			; bc = negated relative x
	ld	b,iyh			; b = height
	mlt	bc			; bc = amount of bytes clipped off
	ld	hl,(ix+3)		; hl -> sprite data
	add	hl,bc
	ld	(ix+3),hl

	ld	b, 0			; Set B to zero again

	ld	hl,0
smcWord _XMin
	ld	(ix+6),hl		; save min x coordinate
.clipright:
	inc	e
	ld	iyl,e			; save new width
	or	a,a
.xclipped:	; <-- carry already cleared on this path

; CLIP Y COORDINATE
	ld	c,0
smcByte _YMin
	ld	hl,(ix+9)		; hl = y coordinate
	sbc	hl,bc
	ex	de,hl			; de = y coordinate relative to min y
	ld	a,ti.lcdHeight		; a = clip_height
smcByte _YSpan
	ld	c,iyh			; bc = height
	sub	a,c			; get difference between clip_height and height
	sbc	hl,hl
	ld	l,a
	dec	c			; bc = height - 1
	jr	nc,.nottaller
	xor	a,a
	sbc	hl,de			; is partially clipped both top and bottom?
	jr	nc,.yclip
	sub	a,e			; a = negated relative y
	add	hl,de			; use clip_height as the draw height, and clip top
	jr	.cliptop
.nottaller:
	; HL = y_span - height && HL >= 0 
	; DE = y_pos - y_min
	; if HL - DE has no carry, then we can skip clearing UDE since it is already zero
	xor	a,a
	sbc	hl,de			; is fully onscreen vertically?
	jr	nc,.yclipped
.yclip:
	add	hl,bc			; is partially clipped bottom?
	ex	de,hl			; e = new height - 1, hl = relative y
	jr	c,.clipbottom
	sub	a,l			; a = negated relative y
.cliptop:
	add	hl,bc			; is partially clipped top?
	ret	nc
	ex	de,hl			; e = new height - 1

	ld	c,a			; c = negated relative y
	ld	hl,(ix+3)		; hl -> sprite data
	add	hl,bc
	ld	(ix+3),hl		; store new ptr

	ld	(ix+9),0		; save min y coordinate
smcByte _YMin

.clipbottom:
	inc.s	de			; inc e and it clears UDE
	ld	a,iyh			; get old height
	ld	iyh,e			; save new height
	sub	a,e			; calculate bytes to add per iteration
.yclipped:	; <-- UDE is zero on this path
; CALCULATE OFFSETS
	ld	hl, (ix + 6)	; x
	ld	e, (ix + 9)	; y
	ld	d, b		; ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	add	hl, de		; add y cord (result is 17 bits)

	ld	de, (CurrentBuffer)
	add	hl, de
	ex	de, hl			; de -> buffer pointer 

	ld	hl, (ix + 3)		; hl -> sprite data
	inc	hl
	inc	hl

	ld	ixl, a			; (.amount)
	ld	a, iyh			; new height (.next)
	cpl
	add	a, ti.lcdHeight + 1
	ld	ixh, a			; (.jump)
	scf				; set carry for success
	ret

;-------------------------------------------------------------------------------
gfy_TransparentTilemap_NoClip: ; COPIED_FROM_GRAPHX
; Tilemapping subsection
	ld	hl,gfy_TransparentSprite_NoClip
;	jr	_Tilemap		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfy_Tilemap_NoClip: ; COPIED_FROM_GRAPHX
; Tilemapping subsection
	ld	hl,gfy_Sprite_NoClip
;	jr	_Tilemap		; emulated by dummifying next instruction:
if 0
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfy_TransparentTilemap: ; COPIED_FROM_GRAPHX
; Tilemapping subsection
	ld	hl,gfy_TransparentSprite
;	jr	_Tilemap		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfy_Tilemap: ; COPIED_FROM_GRAPHX
	ld	hl,gfy_Sprite
end if
; Draws a tilemap given a tile map structure and some offsets
; Arguments:
;  arg0 : Tilemap Struct
;  arg1 : X Pixel Offset (Unsigned)
;  arg2 : Y Pixel Offset (Unsigned)
; Returns:
;  None
; C Function:
;  void DrawBGTilemap(gfy_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset) {
;      int x_draw, y_draw;
;      uint8_t x, x_tile, y_tile, y_next;
;      uint8_t x_res = x_offset/tilemap->tile_width;
;      uint8_t y = y_offset/tilemap->tile_height;
;
;      x_offset = x_offset%tilemap->tile_width;
;      y_offset = y_offset%tilemap->tile_height;
;
;      y_draw = tilemap->y_loc-y_offset;
;      for(y_tile = 0; y_tile <= tilemap->draw_height; y_tile++) {
;          x = x_res;
;          y_next = y*tilemap->width;
;          x_draw = tilemap->x_loc-x_offset;
;          for(x_tile = 0; x_tile <= tilemap->draw_width; x_tile++) {
;              gfy_Sprite(tilemap->tiles[tilemap->map[x+y_next]], x_draw, y_draw, tilemap->tile_width, tilemap->tile_height);
;              x_draw += tilemap->tile_width;
;              x++;
;          }
;          y_draw += tilemap->tile_height;
;          y++;
;      }
;  }
;
t_data        := 0
t_type_width  := 10
t_type_height := 11
t_height      := 12
t_width       := 13
t_tile_height := 6
t_tile_width  := 7
t_draw_height := 8
t_draw_width  := 9
t_x_loc       := 15
x_offset      := 9
y_offset      := 12

_Tilemap:
	ld	(.tilemethod),hl
	push	ix
	ld	ix,0
	lea	bc,ix
	add	ix,sp
	lea	hl,ix-12
	ld	sp,hl
	ld	iy,(ix+6)		; iy -> tilemap structure

	ld	hl,(ix+y_offset)
	ld	c,(iy+t_tile_height)
	ld	a,(iy+t_type_height)
	or	a,a
	jr	nz,.heightpow2
	call	ti._idvrmu
	ex	de,hl
	push	de
	pop	bc
	jr	.heightnotpow2
.heightpow2:				; compute as power of 2 height using shifts
	ld	b,a
	dec	c
	ld	a,l
	and	a,c
	ld	c,a
.div0:
	srl	h
	rr	l
	djnz	.div0
.heightnotpow2:
	ld	(ix-4),l		; y = y_offset / tilemap->tile_height
	ld	(ix+y_offset),bc	; y_offset = y_offset % tilemap->tile_height;

	ld	c,(iy+t_tile_width)
	ld	hl,(ix+x_offset)	; x offset
	ld	a,(iy+t_type_width)
	or	a,a
	jr	nz,.widthpow2
	call	ti._idvrmu
	ex	de,hl
	push	de
	pop	bc
	jr	.widthnotpow2
.widthpow2:
	ld	b,a
	dec	c
	ld	a,l
	and	a,c
	ld	c,a
.div1:
	srl	h
	rr	l
	djnz	.div1
.widthnotpow2:
	ld	a,l
	ld	(.xres),a
	ld	hl,(iy+t_x_loc)
	or	a,a
	sbc	hl,bc
	ld	(.xoffset),hl		; tilemap->x_loc - x_offset;

	or	a,a
	sbc	hl,hl
	ld	l,(iy+14)
	ld	bc,(ix+y_offset)
	ld	(ix-3),h
	sbc	hl,bc
	ld	(ix-12),hl
	jr	.yloop

.xloopinner:
	or	a,a
	sbc	hl,hl
	ld	l,(ix-1)
	ld	bc,(iy+t_data)		; iy -> tilemap data
	add	hl,bc
	ld	bc,0
.ynext := $-3
	add	hl,bc
	ld	a,(hl)
	ld	l,a
	inc	a
	jr	z,.blanktile
	ld	h,3
	mlt	hl
	ld	de,(iy+3)
	add	hl,de
	ld	bc,(ix-12)
	push	bc
	ld	bc,(ix-7)
	push	bc
	ld	bc,(hl)
	push	bc
	call	0			; call sprite drawing routine
.tilemethod := $-3
	lea	hl,ix-12
	ld	sp,hl
.blanktile:
	or	a,a
	sbc	hl,hl
	ld	iy,(ix+6)
	ld	l,(iy+7)
	ld	bc,(ix-7)
	add	hl,bc
	ld	(ix-7),hl
	inc	(ix-1)
	ld	a,(ix-2)
	inc	a

.xloop:
	ld	(ix-2),a
	cp	a,(iy+t_draw_width)
	jr	nz,.xloopinner
	ld	h,0
	ld	l,(iy+6)
	ld	bc,(ix-12)
	add	hl,bc
	ld	(ix-12),hl
	inc	(ix-4)
	inc	(ix-3)

.yloop:
	ld	a,(iy+t_draw_height)
	cp	a,(ix-3)
	jr	z,.finish_loop
.xres := $+3
; .loop:
	ld	(ix-1),0
	ld	hl,0
.xoffset := $-3
	ld	(ix-7),hl
	ld	l,(iy+t_width)
	ld	h,(ix-4)
	mlt	hl
	ld	(.ynext),hl
	xor	a,a
	jr	.xloop
.finish_loop:
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_TilePtr: ; COPIED_FROM_GRAPHX
; Returns a pointer to a tile given the pixel offsets
; Arguments:
;  arg0 : Tilemap Struct
;  arg1 : X Pixel Offset (Unsigned)
;  arg2 : Y Pixel Offset (Unsigned)
; Returns:
;  A pointer to an indexed tile in the tilemap (so it can be looked at or changed)
; C Function:
;  uint8_t *gfy_TilePtr(gfy_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset) {
;      return &tilemap->map[(x_offset/tilemap->tile_width)+((y_offset/tilemap->tile_height)*tilemap->width)];
;  }
	push	ix
	ld	ix,0
	add	ix,sp
	ld	iy,(ix+6)
	ld	hl,(ix+9)
	ld	a,(iy+t_type_width)
	or	a,a
	jr	nz,.fastdiv0
	ld	bc,0
	ld	c,(iy+t_tile_width)
	call	ti._idvrmu
	ex	de,hl
	jr	.widthnotpow2
.fastdiv0:
	ld	b,a
.div0:
	srl	h
	rr	l
	djnz	.div0
.widthnotpow2:
	ex	de,hl
	ld	hl,(ix+12)
	ld	a,(iy+t_type_height)
	or	a,a
	jr	nz,.fastdiv1
	ld	bc,0
	ld	c,(iy+t_tile_height)
	push	de
	call	ti._idvrmu
	ex	de,hl
	pop	de
	jr	.heightnotpow2
.fastdiv1:
	ld	b,a
.div1:	srl	h
	rr	l
	djnz	.div1
.heightnotpow2:
	ld	h,(iy+t_width)
	mlt	hl
	add	hl,de
	ld	de,(iy+t_data)
	add	hl,de
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_TilePtrMapped: ; COPIED_FROM_GRAPHX
; Returns a direct pointer to the input tile
; Arguments:
;  arg0 : Tilemap Struct
;  arg1 : X Map Offset
;  arg2 : Y Map Offset
; Returns:
;  A pointer to the indexed tile in the tilemap (so it can be looked at or changed)
	pop	de			; return vector
	pop	iy			; tilemap struct
	pop	bc			; x offset
	ex	(sp),hl			; y offset
	push	de
	push	de
	push	de
	ld	h,(iy+13)		; tilemap width
	mlt	hl
	ld	b,0
	add.s	hl,bc
	ld	bc,(iy+0)		; tilemap data
	add	hl,bc
	ret

;-------------------------------------------------------------------------------
gfy_GetTextX: ; COPIED_FROM_GRAPHX
; Gets the X position of the text cursor
; Arguments:
;  None
; Returns:
;  X Text cursor posistion
	ld	hl,(_TextXPos)		; return x pos
	ret

;-------------------------------------------------------------------------------
gfy_GetTextY: ; COPIED_FROM_GRAPHX
; Gets the Y position of the text cursor
; Arguments:
;  None
; Returns:
;  Y Text cursor posistion
	ld	hl,(_TextYPos)		; return y pos
	ret

;-------------------------------------------------------------------------------
gfy_SetTextXY: ; COPIED_FROM_GRAPHX
; Sets the text X and Y positions
; Arguments:
;  arg0 : Text X Pos
;  arg1 : Text Y Pos
; Returns:
;  None
	pop	de			; de=return address, sp=&xpos
	pop	hl			; hl=xpos, sp=&ypos
	ld	(_TextXPos),hl
	ex	(sp),hl			; hl=ypos, ypos=don't care
	ld	(_TextYPos),hl
	push	hl			; xpos=don't care, sp=&xpos
	ex	de,hl			; hl=return address
;-------------------------------------------------------------------------------
_indcallHL: ; COPIED_FROM_GRAPHX
; Calls HL
; Inputs:
;  HL : Address to call
	jp	(hl)

;-------------------------------------------------------------------------------
gfy_SetTextBGColor: ; COPIED_FROM_GRAPHX
; Sets the background text color for text routines
; Arguments:
;  arg0 : Color index to set BG to
; Returns:
;  Previous text color palette index
	setSmcBytes _TextBGColor

;-------------------------------------------------------------------------------
gfy_SetTextFGColor: ; COPIED_FROM_GRAPHX
; Sets the foreground text color for text routines
; Arguments:
;  arg0 : Color index to set FG to
; Returns:
;  Previous text color palette index
	setSmcBytes _TextFGColor

;-------------------------------------------------------------------------------
gfy_SetTextTransparentColor: ; COPIED_FROM_GRAPHX
; Sets the transparency text color for text routines
; Arguments:
;  arg0 : Color index to set transparent text to
; Returns:
;  Previous text color palette index
	setSmcBytes _TextTPColor

;-------------------------------------------------------------------------------
gfy_SetFontHeight: ; COPIED_FROM_GRAPHX
; Sets the height of the font in pixels
; Arguments:
;  arg0 : New font height
; Returns:
;  Previous font height
	setSmcBytes _TextHeight

;-------------------------------------------------------------------------------
gfy_PrintStringXY: ; COPIED_FROM_GRAPHX
; Places a string at the given coordinates
; Arguments:
;  arg0 : Pointer to string
;  arg1 : Text X Pos
;  arg2 : Text Y Pos
; Returns:
;  None
	pop	iy			; iy = return vector
	pop	bc			; bc = str
	call	gfy_SetTextXY
	push	bc
	ex	(sp),hl			; hl = str
	push	iy
;	jr	_DrawCharacters		; emulated by dummifying next instructions:
	db	$01			; pop de \ ex (sp),hl \ push de -> ld bc,*

;-------------------------------------------------------------------------------
gfy_PrintString: ; COPIED_FROM_GRAPHX
; Places a string at the current cursor position
; Arguments:
;  arg0 : Pointer to string
; Returns:
;  None
	pop	de
	ex	(sp),hl
	push	de
_DrawCharacters:
	ld	a,(hl)			; get the current character
	or	a,a
	ret	z
	call	_PrintChar
PrintChar_2 = $-3
	inc	hl			; move to the next one
	jr	_DrawCharacters

;-------------------------------------------------------------------------------
gfy_SetTextScale: ; MODIFIED_FROM_GRAPHX
; Changes the amount of text scaling (note that height and width are independent)
; Arguments:
;  arg0 : Width scale (1 is default)
;  arg1 : Height scale (1 is default)
; Returns:
;  None
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	ld	a,l
	ld	de,_TextWidthScale
	ld	hl,_TextScaleJump
	cp	a,c
	jr	z,.match
	jr	.nomatch
.match:
	dec	a
	jr	z,.bothone		; if they are both one; just use normal drawing
	inc	a
.nomatch:
	or	a,a
	ret	z			; null check
	ld	(de),a
	ld	a,c
	or	a,a
	ret	z			; null check
	ld	(_TextHeightScale),a
	ld	(hl),_PrintLargeFont - _PrintNormalFont
	ret
.bothone:
	ld	(hl),a			; store a 0, which means no (literal) jump
	inc	a
	ld	(de),a
	ret

;-------------------------------------------------------------------------------
gfy_SetTextConfig: ; COPIED_FROM_GRAPHX
; Configures text depending on the arguments
; Arguments:
;  arg0 : Configuration numbers
; Returns:
;  None
	pop	de
	ex	(sp),hl			; hl = config
	push	de
	dec	l			; l = config - 1
	ld	hl,_PrintChar_Clip
	jr	z,.writesmc		; z ==> config == gfy_text_clip
; config == gfy_text_noclip
	ld	hl,_PrintChar
.writesmc:				; hl = PrintChar routine
	ld	(PrintChar_0),hl
	ld	(PrintChar_1),hl
	ld	(PrintChar_2),hl
	ret

;-------------------------------------------------------------------------------
gfy_PrintChar:
; Places a character at the current cursor position
; Arguments:
;  arg0 : Character to draw
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,e			; a = char
	jp	_PrintChar		; this is SMC'd to use as a grappling hook into the clipped version
PrintChar_0 := $-3
_PrintChar:
	push	ix			; save stack pointer
	push	hl			; save hl pointer if string
	ld	e,a			; e = char
	ld	a,0
_TextFixedWidth = $-1
	or	a,a
	jr	nz,.fixed
	sbc	hl,hl
	ld	l,e			; hl = character
	ld	bc,(_CharSpacing)
	add	hl,bc
	ld	a,(hl)			; a = char width
.fixed:
	ld	bc,0
_TextXPos := $-3
	push	bc	; preserve the old _TextXPos
	sbc	hl,hl
	ld	l,a
	ld	ixl,a			; ixh = char width
	ld	a,(_TextWidthScale)
	ld	h,a
	mlt	hl
	add	hl,bc
	ld	(_TextXPos),hl

	ld	c, e	; preserve character

	pop	hl	; restore the old _TextXPos
	ld	de,0
_TextYPos := $-3
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset	
	ex	de,hl		; DE = draw location

	ld	a, c			; C = character
	or	a, a
	sbc	hl, hl
	ld	l, a			; hl = character
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc, (_TextData)		; get text data array
	add	hl, bc

	ld	iy,0
	ld	ixh,8
smcByte _TextHeight
	wait_quick
	jr	_PrintLargeFont		; SMC the jump
_TextScaleJump := $ - 1
_PrintNormalFont:
.loop:
	ld	c,(hl)			; c = 8 pixels
	add	iy,de			; get draw location
	lea	de,iy
	ld	b,ixh
.nextpixel:
	ld	a,TEXT_BG_COLOR
smcByte _TextBGColor
	rlc	c
	jr	nc,.bgcolor
	ld	a,TEXT_FG_COLOR
smcByte _TextFGColor
.bgcolor:
	cp	a,TEXT_TP_COLOR		; check if transparent
gfy_PrintChar.transparent_color := $-1
smcByte _TextTPColor
	jr	z,.transparent
	ld	(de),a
.transparent:
	inc	de			; move to next pixel
	djnz	.nextpixel
	ld	de,ti.lcdHeight
	inc	hl
	dec	ixl
	jr	nz,.loop
	pop	hl			; restore hl and stack pointer
	pop	ix
	ret

;-------------------------------------------------------------------------------
_PrintLargeFont:
; Prints in scaled font for prosperity
; This is so that way unscaled font can still be reasonably fast
; Returns:
;  None
.loop:
;	ld	c,(hl)			; c = 8 pixels
	ld	a,(hl)
	ld	(_DebugLargeFontPixel), a
	push	hl
	ld	h,1
_TextWidthScale := $-1
.wscale:
	ld	c,0
_DebugLargeFontPixel := $-1
	add	iy,de			; get draw location
	lea	de,iy
	ld	b,ixh
.inner:
	ld	a,TEXT_BG_COLOR
smcByte _TextBGColor
	ld	l,1
_TextHeightScale := $-1
	rlc	c
	jr	nc,.bgcolor
	ld	a,TEXT_FG_COLOR
smcByte _TextFGColor
.bgcolor:
	cp	a,TEXT_TP_COLOR		; check if transparent
smcByte _TextTPColor
	jr	z,.fgcolor

.hscale0:
	ld	(de),a
	inc	de
	dec	l
	jr	nz,.hscale0
	djnz	.inner
	jr	.done

.fgcolor:
.hscale1:
	inc	de
	dec	l
	jr	nz,.hscale1		; move to next pixel
	djnz	.inner
.done:
	ld	de,ti.lcdHeight

	dec	h
	jr	nz, .wscale

	pop	hl
	inc	hl
	dec	ixl
	jr	nz,.loop
	pop	hl			; restore hl and stack pointer
	pop	ix
	ret

;-------------------------------------------------------------------------------
_PrintChar_Clip:
; Clipped text for characters printing routine
; Arguments:
;  arg0 : Character to draw
; Returns:
;  None
	push	hl			; save hl pointer if string

	ld	e,a			; e = char

	ld	a,(_TextFixedWidth)
	or	a,a
	jr	nz,.fixedwidth
	sbc	hl,hl
	ld	l,e			; hl = character
	ld	bc,(_CharSpacing)
	add	hl,bc
	ld	a,(hl)			; a = char width
.fixedwidth:
	or	a,a
	sbc	hl,hl
	ld	l,e			; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(_TextData)		; get text data array
	add	hl,bc			; de = draw location
	ld	de,_TmpCharData		; store pixel data into temporary sprite
	ld	iyl,a			; ixh = char width
	ld	(_TmpCharSprite),a
	ld	a,8
smcByte _TextHeight
	ld	iyh,a
	ld	(_TmpCharSprite + 1),a	; store width of character we are drawing
	call	_GetChar		; store the character data

	ld	hl, gfy_TransparentSprite.transparent_color
	ld	a,(hl)
	push	af
	ld	a,(gfy_PrintChar.transparent_color)
	ld	(hl),a

	ld	bc,(_TextYPos)
	push	bc
	ld	bc,(_TextXPos)		; compute the new locations
	push	bc
	or	a,a
	sbc	hl,hl

	; ld	a,iyl	; iyl was decremented to zero
	ld	a, (_TmpCharSprite)

	ld	l,a
	add	hl,bc
	ld	(_TextXPos),hl		; move the text x posisition by the character width
	ld	bc,_TmpCharSprite
	push	bc
	call	gfy_TransparentSprite	; use the actual routine
	pop	bc
	pop	bc
	pop	bc

	pop	af
	ld	(gfy_TransparentSprite.transparent_color),a

	pop	hl			; restore hl and stack pointer
	ret

;-------------------------------------------------------------------------------
gfy_PrintInt: ; COPIED FROM GRAPHX
; Places an int at the current cursor position
; Arguments:
;  arg0 : Number to print
;  arg1 : Number of characters to print
; Returns:
;  None
	pop	de
	pop	hl
	push	hl
	push	de
	add	hl,hl
	db	$3E			; xor a,a -> ld a, $AF

;-------------------------------------------------------------------------------
gfy_PrintUInt: ; COPIED FROM GRAPHX
; Places an unsigned int at the current cursor position
; Arguments:
;  arg0 : Number to print
;  arg1 : Minimum number of characters to print
; Returns:
;  None
	xor	a,a
	pop	de
	pop	hl			; hl = uint
	pop	bc			; c = min num chars
	push	bc
	push	hl
	push	de
	jr	nc,.begin		; c ==> actually a negative int
	ex	de,hl
	or	a,a
	sbc	hl,hl
	sbc	hl,de			; hl = -int
	ld	a,'-'
	call	.printchar
	dec	c
	jr	nz,.begin
	inc	c
.begin:
	ld	de,-10000000
	call	.num1
	ld	de,-1000000
	call	.num1
	ld	de,-100000
	call	.num1
	ld	de,-10000
	call	.num1
	ld	de,-1000
	call	.num1
	ld	de,-100
	call	.num1
	ld	de,-10
	call	.num1
	ld	de,-1
.num1:
	xor	a,a
.num2:
	inc	a
	add	hl,de
	jr	c,.num2
	sbc	hl,de
	dec	a			; a = next digit
	jr	nz,.printdigit		; z ==> digit is zero, maybe don't print
	ld	a,c
	inc	c
	cp	a,8
	ret	c			; nc ==> a digit has already been
					;        printed, or must start printing
					;        to satisfy min num chars
	xor	a,a
.printdigit:
	add	a,'0'
	ld	c,a			; mark that a digit has been printed
.printchar:
	push	bc
	call	_PrintChar
PrintChar_1 := $-3
	pop	bc
	ret

;-------------------------------------------------------------------------------
gfy_GetStringWidth: ; COPIED_FROM_GRAPHX
; Gets the width of a string
; Arguments:
;  arg0 : Pointer to string
; Returns:
;  Width of string in pixels
	pop	de
	ex	(sp), hl		; hl -> string		
	push	de
	ld	de,0
.loop:
	ld	a,(hl)
	or	a,a
	jr	z,.done			; loop until null byte
	push	hl
	call	_GetCharWidth
	ex	de,hl
	pop	hl
	inc	hl
	jr	.loop
.done:
	ex	de,hl			; return width of string
	ret

;-------------------------------------------------------------------------------
gfy_GetCharWidth: ; COPIED_FROM_GRAPHX
; Gets the width of a character
; Arguments:
;  arg0 : Character
; Returns:
;  Width of character in pixels
	ld	hl, 3
	add	hl, sp
	ld	a, (hl)			; a = character
	sbc	hl, hl
	ex	de, hl
_GetCharWidth:
	sbc	hl,hl
	ld	l,a
	ld	a,(_TextFixedWidth)	; is fixed width
	or	a,a
	jr	nz,.fixed
	ld	bc,(_CharSpacing)	; lookup spacing
	add	hl,bc
	ld	a,(hl)
.fixed:
	ld	l,a
	ld	a,(_TextWidthScale)	; add scaling factor
	ld	h,a
	mlt	hl
	add	hl,de
	ret

;-------------------------------------------------------------------------------
gfy_GetSpriteChar: ; COPIED_FROM_GRAPHX
; Sets the data in char_sprite (must have previously allocated an 8x8 width sprite)
; the pixel map of the character c
; Arguments:
;  arg0 : Pointer to allocated sprite
;  arg1 : Character
; Returns:
;  Pointer to sprite
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,(_TextFixedWidth)
	or	a,a
	jr	nz,.fixed
	sbc	hl,hl
	ld	l,e			; hl = character
	ld	bc,(_CharSpacing)
	add	hl,bc
	ld	a,(hl)			; a = char width
.fixed:
	or	a,a
	sbc	hl,hl
	ld	l,e			; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(_TextData)		; get text data array
	add	hl,bc			; de = draw location
	ld	de,_TmpCharSprite
	ex	de,hl
	push	hl			; save pointer to sprite
	inc	hl
	ld	(hl),a			; store width of character we are drawing
	dec	hl
	ld	iyl,a			; ixh = char width
	ld	a,8
smcByte _TextHeight
	ld	(hl),a
	inc	hl
	ld	iyh,a			; height of char

	inc	hl
	ex	de,hl
	call	_GetChar		; read the character into the array
	pop	hl
	ret

;-------------------------------------------------------------------------------
_GetChar: ; MODIFIED_FROM_GRAPHX
; Places a character data into a nice buffer
; Inputs:
;  HL : Points to character pixmap
;  DE : Points to output buffer
; Outputs:
;  Stored pixmap image
;  Uses IY
.loop:
	ld	c,(hl)			; c = 8 pixels (or width based)
	ld	b,iyh
.nextpixel:
	ld	a,TEXT_BG_COLOR
smcByte _TextBGColor
	rlc	c
	jr	nc,.bgcolor
	ld	a,TEXT_FG_COLOR
smcByte _TextFGColor
.bgcolor:
	cp	a,TEXT_TP_COLOR		; check if transparent
smcByte _TextTPColor
	jr	z,.transparent
	ld	(de),a
	inc	de
	djnz	.nextpixel
	inc	hl
	dec	iyl
	jr	nz,.loop
	ret
.transparent:
	ld	a,0
smcByte _TextTPColor
	ld	(de),a
	inc	de			; move to next pixel
	djnz	.nextpixel
	inc	hl
	dec	iyl
	jr	nz,.loop		; okay we stored the character sprite now draw it
	ret

;-------------------------------------------------------------------------------
gfy_SetFontData: ; COPIED_FROM_GRAPHX
; Sets the font to be custom
; Arguments:
;  arg0 : Pointer to font data
;  Set Pointer to NULL to use default font
; Returns:
;  Pointer to previous font data
	pop	de
	ex	(sp), hl		; hl -> custom font data
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	ld	de,(_TextData)
	jr	nz,.nonnull		; if null make default font
	ld	hl,_DefaultTextData
.nonnull:
	ld	(_TextData),hl		; save pointer to custom font
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
gfy_SetCharData: ; COPIED_FROM_GRAPHX
; Sets a custom font for a specific character
; Arguments:
;  arg1 : Character index to change (0-127 or 0-255)
;  arg0 : Pointer to character data; if null returns current data
; Returns:
;  Pointer to character data if null, otherwise pointer to next character
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)		; de -> custom character data
	add	hl,de
	or	a,a
	sbc	hl,de			; sets z flag if null
	ret	z
	ex	de,hl
	or	a,a
	sbc	hl,hl
	ld	l,(iy+3)		; hl = index
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(_TextData)
	add	hl,bc
	ex	de,hl
	ld	bc,8
	ldir
	ret

;-------------------------------------------------------------------------------
gfy_SetFontSpacing: ; COPIED_FROM_GRAPHX
; Sets the font to be custom spacing
; Arguments:
;  arg0 : Pointer to font spacing
;  Set Pointer to NULL to use default font spacing
; Returns:
;  None
	pop	de
	ex	(sp), hl		; hl -> custom font width
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	nz,.notnull		; if null make default font width
	ld	hl,_DefaultCharSpacing
.notnull:
	ld	(_CharSpacing),hl	; save pointer to custom widths
	ret

;-------------------------------------------------------------------------------
gfy_SetMonospaceFont: ; COPIED_FROM_GRAPHX
; Sets the font to be monospace
; Arguments:
;  arg0 : Monospace spacing amount
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	ld	a,e			; a = width
	ld	(_TextFixedWidth),a	; store the value of the monospace width
	jp	(hl)

;-------------------------------------------------------------------------------
gfy_FillTriangle_NoClip: ; COPIED_FROM_GRAPHX
; Draws a filled triangle without clipping
; Arguments:
;  arg0-5 : x0,y0,x1,y1,x2,y2
; Returns:
;  None
	ld	hl,gfy_VertLine_NoClip
;	jr	_FillTriangle		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfy_FillTriangle: ; MODIFIED_FROM_GRAPHX
; Draws a filled triangle with clipping
; Arguments:
;  arg0-5 : x0, y0, x1, y1, x2, y2
; Returns:
;  None

if 0
ft_x0 := 6
ft_y0 := 9
ft_x1 := 12
ft_y1 := 15
ft_x2 := 18
ft_y2 := 21
else
; swap x and y
ft_y0 := 6
ft_x0 := 9
ft_y1 := 12
ft_x1 := 15
ft_y2 := 18
ft_x2 := 21
end if

	ld	hl, gfy_VertLine
_FillTriangle:
	ld	(.line0), hl
	ld	(.line1), hl
	ld	(.line2), hl
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 39
	ld	sp, hl
	sbc	hl, hl
	ld	(ix - 15), hl
	ld	(ix - 18), hl		; int sa = 0, sb = 0;
	ld	hl, (ix + ft_y0)		; sort coordinates by y order (y2 >= y1 >= y0)
	ld	de, (ix + ft_y1)		; if (y0 > y1)
	call	_SignedCompare
	jr	c, .cmp0
	ld	hl, (ix + ft_y0)
	ld	(ix + ft_y0), de
	ld	(ix + ft_y1), hl
	ld	hl, (ix + ft_x0)
	ld	de, (ix + ft_x1)
	ld	(ix + ft_x0), de
	ld	(ix + ft_x1), hl
.cmp0:
	ld	hl, (ix + ft_y1)
	ld	de, (ix + ft_y2)
	call	_SignedCompare
	jr	c, .cmp1
	ld	hl, (ix + ft_y1)
	ld	(ix + ft_y1), de
	ld	(ix + ft_y2), hl
	ld	hl, (ix + ft_x1)
	ld	de, (ix + ft_x2)
	ld	(ix + ft_x1), de
	ld	(ix + ft_x2), hl
.cmp1:
	ld	hl, (ix + ft_y0)
	ld	de, (ix + ft_y1)
	call	_SignedCompare
	jr	c, .cmp2
	ld	hl, (ix + ft_y0)
	ld	(ix + ft_y0), de
	ld	(ix + ft_y1), hl
	ld	hl, (ix + ft_x0)
	ld	de, (ix + ft_x1)
	ld	(ix + ft_x0), de
	ld	(ix + ft_x1), hl
.cmp2:
	ld	de, (ix + ft_y2)		; if(y0 == y2) - handle awkward all-on-same-line case as its own thing
	ld	hl, (ix + ft_y0)
	or	a, a
	sbc	hl, de
	jr	nz, .notflat
	ld	bc, (ix + ft_x0)		; x0
	ld	(ix - 6), bc		; a = x0
	ld	(ix - 3), bc		; b = x0;
	ld	hl, (ix + ft_x1)		; if (x1 < a) { a = x1; }
	or	a, a
	sbc	hl, bc
	jp	p, .cmp00
	jp	pe, .cmp01
	jr	.cmp02
.cmp00:
	jp	po, .cmp01
.cmp02:
	ld	bc, (ix + ft_x1)
	ld	(ix-3), bc
	jr	.cmp11
.cmp01:
	ld	bc, (ix + ft_x1)
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, bc			; else if (x1 > b) { b = x1; }
	jp	p, .cmp10
	jp	pe, .cmp11
	jr	.cmp12
.cmp10:
	jp	po, .cmp11
.cmp12:
	ld	bc, (ix + ft_x1)
	ld	(ix - 6), bc
.cmp11:
	ld	bc, (ix - 3)
	ld	hl, (ix + ft_x2)
	or	a, a
	sbc	hl, bc			; if (x2 < a) { a = x2; }
	jp	p, .cmp20
	jp	pe, .cmp21
	jr	.cmp22
.cmp20:
	jp	po, .cmp21
.cmp22:
	ld	bc, (ix + ft_x2)
	ld	(ix-3), bc
	jr	.cmp31
.cmp21:
	ld	bc, (ix + ft_x2)
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, bc			; else if (x2 > b) { b = x2; }
	jp	p, .cmp30
	jp	pe, .cmp31
	jr	.cmp32
.notflat:
	ld	bc, (ix + ft_x0)		; x0
	ld	hl, (ix + ft_x1)
	or	a, a
	sbc	hl, bc
	ld	(ix - 36), hl		; dx01 = x1 - x0;
	ld	hl, (ix + ft_x2)
	or	a, a
	sbc	hl, bc
	ld	(ix - 21), hl		; dx02 = x2 - x0;
	ld	bc, (ix + ft_y0)		; y0
	ld	hl, (ix + ft_y1)
	or	a, a
	sbc	hl, bc
	ld	(ix - 33), hl		; dy01 = y1 - y0;
	ld	hl, (ix + ft_y2)
	or	a, a
	sbc	hl, bc
	ld	(ix - 27), hl		; dy02 = y2 - y0;
	ld	bc, (ix + ft_x1)
	ld	hl, (ix + ft_x2)
	or	a, a
	sbc	hl, bc
	ld	(ix - 30), hl		; dx12 = x2 - x1;
	ld	bc, (ix + ft_y1)
	ld	hl, (ix + ft_y2)
	or	a, a
	sbc	hl, bc
	ld	(ix - 39), hl		; dy12 = y2 - y1;
	jr	nz, .elselast		; if (y1 == y2) { last = y1; }
	ld	(ix - 24), bc
	jr	.sublast
.cmp30:
	jp	po, .cmp31
.cmp32:
	ld	bc, (ix + ft_x2)
	ld	(ix - 6), bc
.cmp31:
	ld	de, (ix - 3)
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, de
	inc	hl
if 0
	push	hl
	ld	bc, (ix + ft_y0)
	push	bc
	push	de
else
	push	hl	; len
	ld	bc, (ix + ft_y0)
	push	de	; x
	push	bc	; y
end if
	call	0			; horizline(a, y0, b-a+1);
.line0 := $-3
	pop	bc
	pop	bc
	pop	bc
	ld	sp, ix
	pop	ix
	ret				; return;
.elselast:
	ld	bc, (ix + ft_y1)		; else { last = y1-1; }
	dec	bc
	ld	(ix - 24), bc
.sublast:
	ld	bc, (ix + ft_y0)
	ld	(ix - 12), bc		; for (y = y0; y <= last; y++)
	jr	.firstloopstart
.firstloop:
	ld	hl, (ix - 15)
	ld	bc, (ix - 33)
	call	_DivideHLBC
	ld	bc, (ix + ft_x0)
	add	hl, bc
	ld	(ix - 3), hl		; a = x0 + sa / dy01;
	ld	hl, (ix - 18)
	ld	bc, (ix - 27)
	call	_DivideHLBC
	ld	bc, (ix + ft_x0)
	add	hl, bc
	ld	(ix - 6), hl		; b = x0 + sb / dy02;
	ld	bc, (ix - 36)
	ld	hl, (ix - 15)
	add	hl, bc
	ld	(ix - 15), hl		; sa += dx01;
	ld	bc, (ix - 21)
	ld	hl, (ix - 18)
	add	hl, bc
	ld	(ix - 18), hl		; sb += dx02;
	ld	de, (ix - 3)
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, de			; if (b < a) { swap(a, b); }
	jp	p, .cmp40
	jp	pe, .cmp41
	jr	.cmp42
.cmp40:
	jp	po, .cmp41
.cmp42:
	ld	hl, (ix - 3)
	ld	de, (ix - 6)
	ld	(ix - 3), de
	ld	(ix - 6), hl
.cmp41:
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, de
	inc	hl
if 0
	push	hl
	ld	bc, (ix - 12)
	push	bc
	push	de
else
	push	hl	; len
	ld	bc, (ix - 12)
	push	de	; x
	push	bc	; y
end if
	call	0			; horizline(a, y, b-a+1);
.line1 := $-3
	pop	bc
	pop	bc
	pop	bc
	ld	bc, (ix - 12)
	inc	bc
	ld	(ix - 12), bc
.firstloopstart:
	ld	hl, (ix - 24)
	or	a, a
	sbc	hl, bc
	jp	p, .cmp50
	jp	pe, .firstloop
	jr	.cmp52
.cmp50:
	jp	po, .firstloop
.cmp52:
	ld	bc, (ix + ft_y1)
	ld	hl, (ix - 12)
	or	a, a
	sbc	hl, bc
	ld	de, (ix - 30)
	call	_MultiplyHLDE		; sa = dx12 * (y - y1);
	ld	(ix - 15), hl
	ld	bc, (ix + ft_y0)
	ld	hl, (ix - 12)
	or	a, a
	sbc	hl, bc
	ld	de, (ix - 21)
	call	_MultiplyHLDE		; sb = dx02 * (y - y0);
	ld	(ix - 18), hl
	jr	.secondloopstart	; for(; y <= y2; y++)
.secondloop:
	ld	hl, (ix - 15)
	ld	bc, (ix - 39)
	call	_DivideHLBC
	ld	bc, (ix + ft_x1)
	add	hl, bc
	ld	(ix - 3), hl		; a = x1 + sa / dy12;
	ld	hl, (ix - 18)
	ld	bc, (ix - 27)
	call	_DivideHLBC
	ld	bc, (ix + ft_x0)
	add	hl, bc
	ld	(ix - 6), hl		; b = x0 + sb / dy02;
	ld	bc, (ix - 30)
	ld	hl, (ix - 15)
	add	hl, bc
	ld	(ix - 15), hl		; sa += dx12;
	ld	bc, (ix - 21)
	ld	hl, (ix - 18)
	add	hl, bc
	ld	(ix - 18), hl		; sb += dx02;
	ld	de, (ix - 3)
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, de			; if (b < a) { swap(a, b); }
	jp	p, .cmp60
	jp	pe, .cmp61
	jr	.cmp62
.cmp60:
	jp	po, .cmp61
.cmp62:
	ld	hl, (ix - 3)
	ld	de, (ix - 6)
	ld	(ix-3), de
	ld	(ix-6), hl
.cmp61:
	ld	hl, (ix - 6)
	or	a, a
	sbc	hl, de
	inc	hl
if 0
	push	hl
	ld	bc, (ix - 12)
	push	bc
	push	de
else
	push	hl	; len
	ld	bc, (ix - 12)
	push	de	; x
	push	bc	; y
end if
	call	0			; horizline(a, y, b-a+1);
.line2 := $-3
	pop	bc
	pop	bc
	pop	bc
	ld	bc, (ix - 12)
	inc	bc
	ld	(ix - 12), bc
.secondloopstart:
	ld	bc, (ix - 12)
	ld	hl, (ix + ft_y2)
	or	a, a
	sbc	hl, bc
	jp	p, .cmp70
	jp	pe, .secondloop
	ld	sp, ix
	pop	ix
	ret
.cmp70:
	jp	po, .secondloop
	ld	sp, ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_Polygon_NoClip: ; COPIED FROM GRAPHX
; Draws a clipped polygon outline
; Arguments:
;  arg0 : Pointer to polygon points
;  arg1 : length of polygon point array
; Returns:
;  None
	ld	hl,gfy_Line_NoClip
;	jr	_Polygon		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfy_Polygon: ; COPIED FROM GRAPHX
; Draws a clipped polygon outline
; Arguments:
;  arg0 : Pointer to polygon points
;  arg1 : length of polygon point array
; Returns:
;  None
	ld	hl,gfy_Line
_Polygon:
	ld	(.line0),hl
	ld	(.line1),hl
	push	ix
	ld	ix,-3
	add	ix,sp
	ld	iy,(ix+9)
	jr	.startloop
.loop:
	pea	iy + 6
	ld	bc,(iy+9)
	push	bc
	ld	bc,(iy+6)
	push	bc
	ld	bc,(iy+3)
	push	bc
	ld	bc,(iy+0)
	push	bc
	call	0
.line0 := $-3
	ld	sp, ix
	pop	iy	; iy += 6
.startloop:
	ld	hl,(ix+12)
	dec	hl
	ld	(ix+12),hl
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	nz,.loop
	ld	bc,(iy+3)
	push	bc
	ld	bc,(iy+0)
	push	bc
	ld	iy,(ix+9)
	ld	bc,(iy+3)
	push	bc
	ld	bc,(iy+0)
	push	bc
	call	0
.line1 := $-3
	lea	hl, ix + 3
	ld	sp, hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_FlipSpriteX: ; MODIFIED_FROM_GRAPHX gfx_FlipSpriteY
; Flips a sprite vertically about the center horizontal axis
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	inc.s	bc		; clear UBC
	ld	iy,0
	add	iy,sp
	ld	de,(iy+3)
	ld	a,(de)		; a = width of sprite
	ld	b, a
	inc	de
	ld	a,(de)		; a = height of sprite

	sbc	hl,hl
	ld	l,a
	ld	c,a

	inc	de
	
	add	hl,de
	ld	de,(iy+6)	; de -> sprite data
	push	de
	ex	de, hl
	ld	(hl),b		; store width
	ex	de, hl
	inc	de
	ld	(de),a		; store height
	ld	iyh, b
;	inc	de		; use the inc de inside the loop instead
.loop:
	ld	b,c	; height
.pixelloop:
	dec	hl
	inc	de
	ld	a,(hl)
	ld	(de),a			; store the new pixel data
	djnz	.pixelloop
	; hl += delta * 2
	add	hl,bc
	add	hl,bc
	dec	iyh
	jr	nz,.loop
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfy_FlipSpriteY: ; MODIFIED_FROM_GRAPHX gfx_FlipSpriteX
; Flips a sprite horizontally about the center vertical axis
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy, 6
	lea	hl, iy
	add	hl, sp
	ld	de, (hl)
	push	de	; return value
	dec	hl
	dec	hl
	dec	hl
	ld	hl, (hl)

	ld	a, (hl)
	ldi		; copy width
	ld	c, a

	xor	a, a
	ld	b, (hl)
	sub	a, b
	ld	(.delta), a
	ld	iyl, b	; (.height) 
	ld	a, c
	ldi		; copy height (and decrement C)

	mlt	bc
	add	hl, bc
.loop:
	lea	bc, iy	; (.height)
	ldir
	dec	bc	; ld bc, -1
	ld	c, -1
.delta := $-1
	add	hl, bc
	add	hl, bc
	dec	a
	jr	nz, .loop
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfy_RotateSpriteCC: ; MODIFIED_FROM_GRAPHX gfy_RotateSpriteC
; Rotates a sprite 90 degrees counter clockwise
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	add	iy,sp
	push	ix
	ld	hl,(iy+6)
	ld	iy,(iy+3)
	ld	ix,(iy+0)		; ixl = width  ,  ixh = height
	lea	bc,ix
	ld	(hl),b
	inc	hl
	ld	(hl),c
	mlt	bc
	add	hl,bc
	ex	de,hl
	ld	c,ixh
	ld	b,0
	inc	bc
.outer:
	lea	hl,iy
	dec	iy
	ld	a,ixl
.inner:
	add	hl,bc
	inc	bc
	ldd
	dec	a
	jr	nz,.inner
	dec	ixh
	jr	nz,.outer
	dec	de
	ex	de,hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_RotateSpriteC: ; MODIFIED_FROM_GRAPHX gfy_RotateSpriteCC
; Rotates a sprite 90 degress clockwise
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	lea	bc,iy
	add	iy,sp
	push	ix
	ld	hl,(iy+6)
	push	hl
	ld	iy,(iy+3)
	ld	ix,(iy+0)		; ixl = width  ,  ixh = height
	lea	de,ix
	ld	(hl),d
	inc	hl
	ld	(hl),e
	inc	hl
	dec	d
	ld	c,d
	ex	de,hl
.outer:
	lea	hl,iy+2
	dec	iy
	ld	a,ixl
.inner:
	add	hl,bc
	inc	c
	ldi
	dec	a
	jr	nz,.inner
	dec	ixh
	jr	nz,.outer
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_RotateSpriteHalf: ; COPIED_FROM_GRAPHX
; Rotates a sprite 180 degrees
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	hl, 6
	add	hl, sp
	ld	de, (hl)	; output sprite
	dec	hl
	dec	hl
	dec	hl
	ld	hl, (hl)	; input sprite
	ld	c, (hl)		; c = width
	inc	hl
	ld	b, (hl)		; b = height
	ex	de, hl
	ld	(hl), bc
	ex	de, hl
	mlt	bc
	add	hl, bc
	push	de
.loop:
	inc	de
	inc	de
	ldd
	jp	pe, .loop
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfy_ScaleSprite: ; MODIFIED_FROM_GRAPHX
; Scale an image using an output buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	lea	bc,iy
	add	iy,sp
	push	ix
	ld	hl,(iy+6)

	push	hl

	inc	hl
	ld	a,(hl)
	dec	hl
	ld	ixh,a			; target_width
	ld	(ScaleWidth),a
	
	xor	a,a
	sub	a,(hl)
	ld	ixl,a			; -target_height

	inc	hl
	inc	hl

	push	hl			; hl->tgt_data
	ld	hl,(iy+3)
	ld	c,(hl)			; src_height
	inc	hl
	ld	e,(hl)			; src_width
	inc	hl
	push	hl			; hl->src_data
	push	de			; e = src_width
	call	_UCDivA			; ca = dv = (source_height*256)/target_height
	pop	hl			; l = src_width
	ld	(dv_shl_16),a
	ld	h,c
	ld	c,l
	mlt	hl
	ld	(dv_shr_8_times_width),hl
	add	hl,bc
	ld	(dv_shr_8_times_width_plus_width),hl
	xor	a,a
	sub	a,ixh			; -target_width
	call	_UCDivA			; ca = du = (source_width*256)/target_width
	pop	hl			; hl->src_data
	pop	de			; de->tgt_data
	ld	iy,0
	ld	iyl,a
	ld	ixh,c			; (.du) = bc:iyl, ixl = target_height

; b = out_loop_times
; de = target buffer adress
.outer:
	push	hl
ScaleWidth := $+2
	ld	iyh, 0
	xor	a,a
	ld	b,a
	ld	c,ixh	; (.du)
.loop:
	ldi
	add	a,iyl
	adc	hl,bc			; xu += du
	inc	bc			; bc:iyl is du
	dec	iyh
	jr	nz,.loop
	pop	hl			; add up to hla
	ld	bc,0			; dv<<16
dv_shl_16 := $-1
	add	iy,bc
	ld	bc,0			; dv>>8*src_width
dv_shr_8_times_width := $-3
	jr	nc,.skip
	ld	bc,0			; dv>>8*src_width+src_width
dv_shr_8_times_width_plus_width := $-3
.skip:
	add	hl,bc
	inc	ixl
	jr	nz,.outer
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfy_RotatedScaledSprite_NoClip: ; MODIFIED_FROM_GRAPHX
; Rotate and scale an unclipped sprite drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Rotation angle as an integer
;  arg4 : Scale factor (64 = 100%)
; Returns:
;  The size of the sprite after scaling
	ld	h, $21	; ld hl, *
	db	$FD	; ld h, * --> ld iyh, *
;-------------------------------------------------------------------------------
gfy_RotatedScaledSprite: ; MODIFIED_FROM_GRAPHX
; Rotate and scale a clipped sprite drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Rotation angle as an integer
;  arg4 : Scale factor (64 = 100%)
; Returns:
;  The unclipped size of the sprite after scaling
	ld	h, $CD	; call *
	ld	a, -1 + _RSS_NC.inner_opaque - _RSS_NC.dsrs_jump_1
	; jr .inner_opaque_hijack \ inc l
	ld	bc, ($2C0018) or (((-1 + _RSS_NC.inner_opaque_hijack - _RSS_NC.dsrs_jump_2) and $FF) shl 8)
	jr	_RotatedScaledSprite
;-------------------------------------------------------------------------------
gfy_RotatedScaledTransparentSprite_NoClip: ; MODIFIED_FROM_GRAPHX
; Rotate and scale an unclipped transparent sprite drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Rotation angle as an integer
;  arg4 : Scale factor (64 = 100%)
; Returns:
;  The size of the sprite after scaling
	ld	h, $21	; ld hl, *
	db	$FD	; ld h, * --> ld iyh, *
;-------------------------------------------------------------------------------
gfy_RotatedScaledTransparentSprite: ; MODIFIED_FROM_GRAPHX
; Rotate and scale a clipped transparent sprite drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Rotation angle as an integer
;  arg4 : Scale factor (64 = 100%)
; Returns:
;  The unclipped size of the sprite after scaling
	ld	h, $CD	; call *
	ld	a, -1 + _RSS_NC.inner_transparent - _RSS_NC.dsrs_jump_1
	; push hl \ ld l, a \ inc l
	ld	bc, $2C6FE5
_RotatedScaledSprite:
_RSS_NC:
	ld	iy, .dsrs_base_address
	ld	(iy + (.dsrs_jump_1 - .dsrs_base_address)), a
	ld	(iy + (.dsrs_jump_2 - .dsrs_base_address - 1)), bc
	ld	(iy + (.dsrs_clip_call - .dsrs_base_address)), h
	push	ix
	ld	ix, 0
	lea	bc, ix + 0	; ld bc, 0
	add	ix, sp
	; iy +  0 : -(size * scale / 128)
	; ix -  9 : size128_1_minus_dys_0
	; ix -  6 : dyc_0
	; ix -  3 : dys_0
	; ix -  0 : IX
	; ix +  3 : return address
	; ix +  6 : sprite pointer
	; ix +  9 : x position
	; ix + 12 : y position
	; ix + 15 : angle
	; ix + 16 : width that was clipped
	; ix + 17 : height that was clipped
	; ix + 18 : scale
	; ix + 19 : sprite size

	ld	hl, (ix + 6)		; sprite pointer
	ld	b, (hl)
	ld	(ix + 19), b		; store sprite size
	inc	hl
	inc	hl

	; or	a, a	; carry already cleared
	dec	b
	sbc	hl, bc	; offset the sprite pointer by (size - 1) * 256

	ld	(iy + (.dsrs_sprptr_0A - .dsrs_base_address)), hl	; write smc
	ld	(iy + (.dsrs_sprptr_0B - .dsrs_base_address)), hl	; write smc

	; sinf = _SineTable[angle] * 128 / scale;
	xor	a, a
	sub	a, (ix + 15)		; angle (negative for graphy reasons)
	call	calcSinCosSMC
	ld	(iy + (.dsrs_sinf_1_plus_offset_ix - .dsrs_base_address)), hl	; write smc

	; The previous code does ~HL instead of -HL. Unsure if intentional.
	ex	de, hl
	sbc	hl, hl
	ccf
	sbc	hl, de
	ld	(iy + (.dsrs_sinf_0A - .dsrs_base_address)), hl	; write smc
	ld	(iy + (.dsrs_sinf_0B - .dsrs_base_address)), hl	; write smc

	; dxs = sinf * -(size * scale / 128);
	call	_CalcDXS	; uses (iy + 0)
	push	hl	; ld (ix - 3), dsrs_dys_0

	; cosf = _SineTable[angle + 64] * 128 / scale
	call	calcSinCosSMC_loadCosine
	ld	(iy + (.dsrs_cosf_0A - .dsrs_base_address)), hl	; write smc
	ld	(iy + (.dsrs_cosf_0B - .dsrs_base_address)), hl	; write smc
	; ld	(.dsrs_cosf_1), hl	; write smc

	; dxc = cosf * -(size * scale / 128);
	ld	bc,(iy + 0)		; -(size * scale / 128)
	call	_16Mul16SignedNeg	; cosf * -(size * scale / 128)
	push	hl	; ld (ix - 6), dsrs_dyc_0

	ld	bc, (ix + 18)	; B = size, C = scale
	or	a, a
	sbc	hl, hl
	ld	h, b
	; BC = size * scale
	mlt	bc
	; HL = size / 2
	srl	h
	; rr	l
	or	a, a	; truncate

	; carry is cleared here
	ld	de, (ix - 3)	; dsrs_dys_0
	sbc	hl, de
	; ld	(iy + (.dsrs_size128_1_minus_dys_0 - .dsrs_base_address)), hl	; write smc
	push	hl	; ld (ix - 9), dsrs_size128_1_minus_dys_0
	add	hl, de		; restore HL
	ld	de, (ix - 6)	; dsrs_dyc_0
	add.s	hl, de		; make sure UHL is zero
	ld	(iy + (.dsrs_size128_0_plus_dyc_0 - .dsrs_base_address)), hl	; write smc

	; carry might be set, but that shouldn't matter for rl c

	ld	a, b
	rl	c
	adc	a, a
	rl	c
	adc	a, a			; size * scale / 64
	jr	nz, .hax
	inc	a			; hax for scale = 1?
.hax:
	ld	b, a	; render height
	ld	c, a	; render width

	; changes from call * to ld hl, *
	.dsrs_clip_call := $+0
	call	_RotatedScaled_ClipAdjust

	ld	(iy + (.dsrs_size_1 - .dsrs_base_address)), b	; write smc

	or	a, a
	sbc	hl, hl
	ld	l, b
	ld	de, ti.lcdHeight
	ex	de, hl
	sbc	hl, de
	ld	(iy + (.line_add - .dsrs_base_address)), hl

	; calculate y-loop offset for IX
	ld	hl, (iy + (.dsrs_cosf_0A - .dsrs_base_address))
	; DE = HL * C(width)
	call	_set_DE_to_HL_mul_B
	ld	hl, (iy + (.dsrs_sinf_1_plus_offset_ix - .dsrs_base_address))
	or	a, a
	sbc.s	hl, de	; make sure UHL is zero
	ld	(iy + (.dsrs_sinf_1_plus_offset_ix - .dsrs_base_address)), hl

	; calculate y-loop offset for HL
	ld	hl, (iy + (.dsrs_sinf_0A - .dsrs_base_address))
	; DE = HL * C(width)
	call	_set_DE_to_HL_mul_B
	ld	hl, (iy + (.dsrs_cosf_0A - .dsrs_base_address))
	or	a, a
	sbc	hl, de
	ld	(iy + (.dsrs_cosf_1_plus_offset_hl - .dsrs_base_address)), hl

	; _set_DE_to_HL_mul_B sets UHL and UDE to zero
	ld	e, (ix + 12)		; y
	ld	hl, (ix + 9)		; x
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	; ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset
	ex	de, hl			; de = buffer pointer

	; note that A is preserved throughout the loop
	ld	a, (ix + 19)	; scale
	dec	a		; scale - 1 for comparison flags to work correctly

	; by popping these off the stack in a werid way, we can reduce SMC useage

	pop	hl			; dsrs_size128_1_minus_dys_0
	ld	ixh, b
	ld	iyh, c			; size * scale / 64
	pop	bc			; smc = dxc start
	ex	(sp), ix		; smc = dxs start	

	; ys = (dxc - dys) + (size * 128)
	add	hl, bc	; HL = (dxc - dys) + (size * 128)
	
	ld	bc, 0	; xs = (dxs + dyc) + (size * 128)
.dsrs_size128_0_plus_dyc_0 := $-3
.dsrs_base_address := .dsrs_size128_0_plus_dyc_0
	add	ix, bc	; IX = (dxs + dyc) + (size * 128)

	call	gfy_Wait
	jr	.begin_loop

;-------------------------------------------------------------------------------

.inner_opaque:
	cp	a, h
	jr	c, .skip_pixel
	ld	c, ixh
	cp	a, c
	jr	c, .skip_pixel
.inner_opaque_hijack:
	; get pixel and draw to buffer
	push	hl			; xs
	ld	l, a
	inc	l
	mlt	hl
	ld	b, a	; A is a known constant that we can compensate for
	; result is at most 255 * 255 + 255 or 65279. Make sure UBC is zero
	add	hl, bc			; y * size + x

	ld	bc, 0
.dsrs_sprptr_0B := $-3
	add	hl, bc
	ldi
	pop	hl

	ld	bc, 0			; smc = -sinf
.dsrs_sinf_0B := $-3
	add	hl, bc			; ys += -sinf

	ld	bc, 0			; smc = cosf
.dsrs_cosf_0B := $-3
	add	ix, bc			; xs += cosf

	dec	iyl
	jr	nz, .inner_opaque	; x loop

	dec	iyh	
	jr	z, .finish		; y loop
.outer:
	; restore and increment dxc
	ld	bc, 0			; smc = cosf
.dsrs_cosf_1_plus_offset_hl := $-3
	add	hl, bc			; dxc += cosf

	; restore and increment dxs
	ld	bc, 0			; smc = sinf
.dsrs_sinf_1_plus_offset_ix := $-3
	add	ix, bc			; dxs += sinf + offset

	ld	bc, 0
.line_add := $-3
	; y++
	ex	de, hl
	add	hl, bc
	ex	de, hl
.begin_loop:
.dsrs_size_1 := $+2			; smc = size * scale / 64
	ld	iyl, 0
.inner_transparent:
	cp	a, h
	jr	c, .skip_pixel
	ld	c, ixh
	cp	a, c
	jr	c, .skip_pixel
	; get pixel and draw to buffer
	; SMC: push hl \ ld l, a --> jr inner_opaque_hijack
	push	hl			; xs
	ld	l, a
.dsrs_jump_2 := $-1
	inc	l
	mlt	hl
	ld	b, a	; A is a known constant that we can compensate for
	; result is at most 255 * 255 + 255 or 65279. Make sure UBC is zero
	add	hl, bc			; y * size + x

	ld	bc, 0
.dsrs_sprptr_0A := $-3
	add	hl, bc
	ld	b, a	; preserve A
	ld	a, (hl)
	cp	a, TRASPARENT_COLOR
smcByte _TransparentColor
	jr	z, .transparent_pixel
	ld	(de), a
.transparent_pixel:
	ld	a, b	; restore A
	pop	hl			; ys
.skip_pixel:
	inc	de			; x++s
	ld	bc, 0			; smc = -sinf
.dsrs_sinf_0A := $-3
	add	hl, bc			; ys += -sinf

	ld	bc, 0			; smc = cosf
.dsrs_cosf_0A := $-3
	add	ix, bc			; xs += cosf

	dec	iyl
	jr	nz, .inner_transparent	; x loop
.dsrs_jump_1 := $-1

	dec	iyh
	jr	nz, .outer		; y loop
.finish:
	pop	af			; sprite out size
	pop	ix
	ret

;-------------------------------------------------------------------------------
_rss_not_culled:
	; offscreen
	ld	a, iyh	; sprite out size (iyh/height should remain untouched)
	ld	sp, ix
	pop	ix
	ret
_RotatedScaled_ClipAdjust:
; modified version of _ClipCoordinates
	push	iy
	ld	iyh, b	; height
	ld	iyl, c	; width
	xor	a, a
	ld	(ix + 16), a	; width that was clipped
	ld	(ix + 17), a	; height that was clipped
; Clipping stuff
; Arguments:
;  arg0 : Pointer to sprite structure
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  IYH: New sprite height
;  IYL: New sprite width
;  NC : If offscreen

; CLIP X COORDINATE
	ld	bc,0
smcWord _XMin
	ld	hl, (ix + 9)		; hl = x coordinate
;	or	a,a
	sbc	hl,bc
	ex	de,hl			; de = x coordinate relative to min x
	ld	hl,ti.lcdWidth		; hl = clip_width
smcWord _XSpan
	xor	a,a
	ld	b,a
	ld	c,iyl			; bc = width
	sbc	hl,bc			; get difference between clip_width and width
	dec	c			; bc = width - 1
	jr	nc,.notwider
	or	a,a
	sbc	hl,de			; is partially clipped both left and right?
	jr	nc,.xclip
	sub	a,e			; a = negated relative x
	add	hl,de			; use clip_width as the draw width, and clip left
	jr	.clipleft
.notwider:
	sbc	hl,de			; is fully onscreen horizontally?	
	jr	nc,.xclipped		; a = 0 for bytes to add per iteration
.xclip:
	add	hl,bc			; is partially clipped right?
	ex	de,hl			; e = new width - 1, hl = relative x
	jr	c,.clipright
	sub	a,l			; a = negated relative x
.clipleft:
	add	hl,bc			; is partially clipped left?
	jr	nc, _rss_not_culled	; return if offscreen
	ld	(ix + 16), a		; store width that was clipped
	ex	de,hl			; e = new width - 1
	ld	hl,0
smcWord _XMin
	ld	(ix + 9), hl		; save min x coordinate
.clipright:
	inc	e
	ld	iyl,e			; save new width
.xclipped:

; CLIP Y COORDINATE
	ld	bc,0
smcWord _YMin
	ld	hl, (ix + 12)		; hl = y coordinate
	or	a,a
	sbc	hl,bc
	ex	de,hl			; de = y coordinate relative to min y
	ld	a,ti.lcdHeight		; a = clip_height
smcByte _YSpan
	ld	c,iyh			; bc = height
	sub	a,c			; get difference between clip_height and height
	sbc	hl,hl
	ld	l,a
	dec	c			; bc = height - 1
	jr	nc,.nottaller
	xor	a,a
	sbc	hl,de			; is partially clipped both top and bottom?
	jr	nc,.yclip
	sub	a,e			; a = negated relative y
	add	hl,de			; use clip_height as the draw height, and clip top
	jr	.cliptop
.nottaller:
	xor	a,a
	sbc	hl,de			; is fully onscreen vertically?
	jr	nc,.yclipped
.yclip:
	add	hl,bc			; is partially clipped bottom?
	ex	de,hl			; e = new height - 1, hl = relative y
	jr	c,.clipbottom
	sub	a,l			; a = negated relative y
.cliptop:
	add	hl,bc			; is partially clipped top?
	jr	nc, _rss_not_culled	; return if offscreen
	ex	de,hl			; e = new height - 1
	ld	(ix + 17), a		; store height that was clipped
	ld	(ix + 12), 0		; save min y coordinate
smcByte _YMin
.clipbottom:
	inc	e
	ld	iyh,e			; save new height
.yclipped:

	; width and height are on the stack
	ex	(sp), iy

	ld	bc, (ix + 16)

	; Starting IX offset X
	ld	hl, (iy + (_RSS_NC.dsrs_cosf_0A - _RSS_NC.dsrs_base_address))
	; DE = HL * B(height)
	call	_set_DE_to_HL_mul_B
	ld	hl, (iy + (_RSS_NC.dsrs_size128_0_plus_dyc_0 - _RSS_NC.dsrs_base_address))
	add	hl, de
	push	hl

	; Starting HL offset X
	ld	hl, (iy + (_RSS_NC.dsrs_sinf_0A - _RSS_NC.dsrs_base_address))
	; DE = HL * B(height)
	call	_set_DE_to_HL_mul_B
	; ld	hl, (iy + (_RSS_NC.dsrs_size128_1_minus_dys_0 - _RSS_NC.dsrs_base_address))
	ld	hl, (ix - 9)	; dsrs_size128_1_minus_dys_0
	add	hl, de
	push	hl

	ld	b, c

	; Starting HL offset Y
	ld	hl, (iy + (_RSS_NC.dsrs_cosf_0A - _RSS_NC.dsrs_base_address))
	; DE = HL * C(width)
	call	_set_DE_to_HL_mul_B
	pop	hl
	add	hl, de	
	; ld	(iy + (_RSS_NC.dsrs_size128_1_minus_dys_0 - _RSS_NC.dsrs_base_address)), hl
	ld	(ix - 9), hl	; dsrs_size128_1_minus_dys_0

	; Starting IX offset Y
	ld	hl, (iy + (_RSS_NC.dsrs_sinf_1_plus_offset_ix - _RSS_NC.dsrs_base_address))
	; DE = HL * C(width)
	call	_set_DE_to_HL_mul_B
	pop	hl
	add.s	hl, de	; make sure UHL is zero
	ld	(iy + (_RSS_NC.dsrs_size128_0_plus_dyc_0 - _RSS_NC.dsrs_base_address)), hl

	pop	bc	; B = height, C = width
	ret

_set_DE_to_HL_mul_B:
	; UHL = zero
	; UDE = zero
	; graphx uses C(width) and graphy uses B(height)
	ld	d, b
	ld	e, l
	ld	l, d
	mlt	hl
	mlt	de
	ld	a, d
	add	a, l
	ld	d, a
	ret

;-------------------------------------------------------------------------------
gfy_RotateScaleSprite: ; MODIFIED_FROM_GRAPHX
; Rotate and scale an image using an output buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
;  arg2 : Rotation angle as an integer
;  arg3 : Scale factor (64 = 100%)
; Returns:
;  arg1 : Pointer to sprite struct output
	push	ix
	; aligning ix with gfy_RotatedScaledSprite allows for code sharing
	ld	ix, -3
	lea	bc, ix + 3	; ld bc, 0
	add	ix, sp
	; iy +  0 : -(size * scale / 128)
	; ix - 12 : size128_0_plus_dyc_0
	; ix -  9 : size128_1_minus_dys_0
	; ix -  6 : dyc_0
	; ix -  3 : dys_0
	; ix -  0 : _smc_dsrs_sinf_1_plus_offset_ixX
	; ix +  3 : IX
	; ix +  6 : return address
	; ix +  9 : input sprite pointer
	; ix + 12 : output sprite pointer
	; ix + 15 : angle
	; ix + 18 : scale
	; ix + 19 : sprite size

	ld	iy, _smc_dsrs_base_address
	ld	hl, (ix + 9)		; sprite pointer
	ld	b, (hl)
	ld	(ix + 19), b		; store sprite size
	inc	hl
	inc	hl

	or	a, a
	dec	b
	sbc	hl, bc	; offset the sprite pointer by (size - 1) * 256

	ld	(iy + (_smc_dsrs_sprptr_0 - _smc_dsrs_base_address)), hl ; write smc

	; sinf = _SineTable[angle] * 128 / scale;
	xor	a, a
	sub	a, (ix + 15)		; angle (negative for graphy reasons)
	call	calcSinCosSMC
	push	hl	; ld (ix - 0), _smc_dsrs_sinf_1_plus_offset_ix
	; ld	(_smc_dsrs_sinf_1_plus_offset_ix),hl ; write smc

	; The previous code does ~HL instead of -HL. Unsure if intentional.
	ex	de, hl
	sbc	hl, hl
	ccf
	sbc	hl, de
	ld	(iy + (_smc_dsrs_sinf_0A - _smc_dsrs_base_address)), hl ; write smc
	ld	(iy + (_smc_dsrs_sinf_0B - _smc_dsrs_base_address)), hl ; write smc

	; dxs = sinf * -(size * scale / 128);
	call	_CalcDXS	; uses (iy + 0)
	push	hl		; ld (ix - 3), _smc_dsrs_dys_0

	; cosf = _SineTable[angle + 64] * 128 / scale
	call	calcSinCosSMC_loadCosine
	ld	(iy + (_smc_dsrs_cosf_0A - _smc_dsrs_base_address)), hl ; write smc
	ld	(iy + (_smc_dsrs_cosf_0B - _smc_dsrs_base_address)), hl ; write smc
	; ld	(_smc_dsrs_cosf_1_plus_offset_hl),hl ; write smc

	; dxc = cosf * -(size * scale / 128);
	ld	bc, (iy + 0)		; -(size * scale / 128)
	call	_16Mul16SignedNeg	; cosf * -(size * scale / 128)
	push	hl	; ld (ix - 6), _smc_dsrs_dyc_0

	ld	bc, (ix + 18)	; B = size, C = scale
	or	a, a
	sbc	hl, hl
	ld	h, b
	; BC = size * scale
	mlt	bc
	; HL = size / 2
	srl	h
	; rr	l
	or	a, a	; truncate

	; carry is cleared here
	ld	de, (ix - 3)	; dsrs_dys_0
	sbc	hl, de
	push	hl	; ld (ix - 9), _smc_dsrs_size128_1_minus_dys_0
	add	hl, de		; restore HL
	ld	de, (ix - 6)	; dsrs_dyc_0
	add	hl, de
	push	hl	; ld (ix - 12), _smc_dsrs_size128_0_plus_dyc_0
	; carry might be set, but that shouldn't matter for rl c

	ld	a, b
	rl	c
	adc	a, a
	rl	c
	adc	a, a			; size * scale / 64
	jr	nz, .hax
	inc	a			; hax for scale = 1?
.hax:
	ld	(iy + (_smc_dsrs_size_1 - _smc_dsrs_base_address)), a ; write smc
	ld	b, a

	; calculate y-loop offset for IX
	ld	hl, (iy + (_smc_dsrs_cosf_0A - _smc_dsrs_base_address))
	; DE = HL * B
	call	_set_DE_to_HL_mul_B
	ld	hl, (ix - 0)	; _smc_dsrs_sinf_1_plus_offset_ix
	or	a, a
	sbc.s	hl, de	; make sure UHL is zero
	ld	(iy + (_smc_dsrs_sinf_1_plus_offset_ix - _smc_dsrs_base_address)), hl

	; calculate y-loop offset for HL
	ld	hl, (iy + (_smc_dsrs_sinf_0A - _smc_dsrs_base_address))
	; DE = HL * B
	call	_set_DE_to_HL_mul_B
	ld	hl, (iy + (_smc_dsrs_cosf_0A - _smc_dsrs_base_address))
	or	a, a
	sbc	hl, de
	ld	(iy + (_smc_dsrs_cosf_1_plus_offset_hl - _smc_dsrs_base_address)), hl

	; note that A is preserved throughout the loop
	ld	a, (ix + 19)	; scale
	dec	a		; scale - 1 for comparison flags to work correctly

	ld	iy, (ix + 12)		; sprite storing to
	ld	c, b
	ld	(iy + 0), bc

	; by popping these off the stack in a werid way, we can reduce SMC useage

	pop	ix	; _smc_dsrs_size128_0_plus_dyc_0
	pop	de	; _smc_dsrs_size128_1_minus_dys_0
	pop	hl			; smc = dxc start

	; ys = (dxc - dys) + (size * 128)
	add	hl, de	; HL = (dxc - dys) + (size * 128)

	pop	de			; smc = dxs start

	; xs = (dxs + dyc) + (size * 128)
	add	ix, de	; IX = (dxs + dyc) + (size * 128)

	lea	de, iy + 2

	ex	(sp), iy		; pop reg24 \ push iy

	ld	iyh, b			; size * scale / 64

	; UBC was set to zero from mlt bc awhile back
	jr	drawSpriteRotateScale_Begin

;-------------------------------------------------------------------------------
_yloop:
 	ld	bc, $000000		; smc = cosf
_smc_dsrs_cosf_1_plus_offset_hl := $-3
_smc_dsrs_base_address := _smc_dsrs_cosf_1_plus_offset_hl
	add	hl, bc			; dxc += cosf

	ld	bc, $000000		; smc = sinf
_smc_dsrs_sinf_1_plus_offset_ix := $-3
	add	ix, bc			; dxs += sinf

drawSpriteRotateScale_Begin:
_smc_dsrs_size_1 := $+2			; smc = size * scale / 64
	ld	iyl, $00
_xloop:
	cp	a, h
	jr	c, drawSpriteRotateScale_SkipPixel
	ld	c, ixh
	cp	a, c
	jr	c, drawSpriteRotateScale_SkipPixel
	; get pixel and draw to buffer
	push	hl			; xs
	ld	l, a
	inc	l
	mlt	hl
	ld	b, a	; A is a known constant that we can compensate for
	; result is at most 255 * 255 + 255 or 65279. Make sure UBC is zero
	add	hl, bc			; y * size + x

	ld	bc, 0
_smc_dsrs_sprptr_0 := $-3
	add	hl, bc
	; ld	a, (hl)
	; ld	(de), a			; write pixel
	; inc	de			; x++s
	ldi

	pop	hl			; ys
	ld	bc, $000000		; smc = -sinf
_smc_dsrs_sinf_0A := $-3
	add	hl, bc			; ys += -sinf

	ld	bc, $000000		; smc = cosf
_smc_dsrs_cosf_0A := $-3
	add	ix, bc			; xs += cosf

	dec	iyl
	jr	nz, _xloop	; x loop

	dec	iyh
	jr	nz, _yloop		; y loop
	pop	hl			; sprite out ptr
	pop	ix
	ret

drawSpriteRotateScale_SkipPixel:
	ld	b, a	; preserve A
	ld	a,TRASPARENT_COLOR
smcByte _TransparentColor
	ld	(de), a			; write pixel
	inc	de			; x++s
	ld	a, b	; restore A

	ld	bc, 0			; smc = -sinf
_smc_dsrs_sinf_0B := $-3
	add	hl, bc			; ys += -sinf

	ld	bc, 0			; smc = cosf
_smc_dsrs_cosf_0B := $-3
	add	ix, bc			; xs += cosf

	dec	iyl
	jr	nz, _xloop		; x loop
	; We are here because the right edge of the sprite was transparent.
	dec	iyh
	jr	nz, _yloop		; y loop
	pop	hl			; sprite out ptr
	pop	ix
	ret

;-------------------------------------------------------------------------------

calcSinCosSMC_loadCosine:
	ld	a, 64
	add	a, (ix + 15)
calcSinCosSMC:
	ld	e, (ix + 18)
; inputs:
; A = angle
; E = scale
; outputs:
; HL = 16bit quotient
; UHL = 0
	; getSinCos:
	; returns a = sin/cos(a) * 128
	ld	bc, $80
	ld	d, a
	bit	7, a
	jr	z, .bit7
	sub	a, c	; sub a, 128
.bit7:
	bit	6, a
	jr	z, .bit6
	;	A = 128 - A
	neg
	add	a, c	; add a, 128
.bit6:
	ld	c, a
	ld	hl, _SineTable
	add	hl, bc
	ld	h, (hl)
	ld	l, b	; ld l, 0
	; hl = _SineTable[angle + 64] * 128
	; H is [0, 127]
	; HL <<= 7
	add.s	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl

	; _16Div8Signed:
	; hl = _SineTable[angle + 64] * 128 / scale (cos)
	ld	b, 16
	xor	a, a
.div:
	add	hl, hl
	rla
	jr	c, .overflow	; this path is only used when E >= 128
	cp	a, e
	jr	c, .check
.overflow:
	sub	a, e
	inc	l
.check:
	djnz	.div
	bit	7, d
	; UHL is zero here
	ret	z
	; negate
	; carry is reset here
	ex	de, hl
	sbc	hl, hl
	sbc.s	hl, de	; clear UHL
	ret

_SineTable:
	; sin(x) * 128
	;    0|  1|  2|  3|  4|  5|  6|  7|  8|  9|  A|  B|  C|  D|  E|  F
	db   0,  3,  6,  9, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46
	db  49, 52, 55, 58, 60, 63, 66, 68, 71, 74, 76, 79, 81, 84, 86, 88
	db  91, 93, 95, 97, 99,101,103,105,106,108,110,111,113,114,116,117
	db 118,119,121,122,122,123,124,125,126,126,127,127,127,127,127,127,127

_CalcDXS:
	ex	de, hl
	ld	bc, (ix + 18)
	; inputs:
	; DE = sinf
	; B = size
	; C = scale
	; assumes iy is set to smc base address
	; sinf * -(size * scale / 128)
	mlt	bc			; size * scale
	rl	c
	rl	b
	ld	c, b			; (size * scale / 128)
	xor	a, a
	sub	a, c
	ld	c, a
	sbc	a, a
	ld	b, a			; -(size * scale / 128)
	ld	(iy + 0), bc		; smc base address
_16Mul16SignedNeg:
	; outputs to HL
	; UHL = 0
	ld	d, b
	ld	e, l
	ld	b, h
	ld	h, c
	mlt	bc
	mlt	de
	mlt	hl
	ld	a, h
	add	a, c
	add	a, e
	ld	h, a
	ret

;-------------------------------------------------------------------------------
; gfy_FloodFill:

;-------------------------------------------------------------------------------
; gfy_RLETSprite:

;-------------------------------------------------------------------------------
gfy_RLETSprite_NoClip: ; MODIFIED_FROM_GRAPHX
	ld	iy, 0
	lea	bc, iy + 0
	add	iy, sp
	ld	e, (iy + 9)
	ld	hl, (iy + 6)
	ld	d, h		; maybe ld d, 0
	dec	h		; tests if x >= 256
	ld	h, ti.lcdHeight
	ld	a, h	; ld a, ti.lcdHeight
	jr	nz, .x_lt_256
	ld	d, h		; ld d, ti.lcdHeight * 256
.x_lt_256:
	mlt	hl
	ex.s	de, hl		; clear upper byte of DE
	add	hl, de		; add y cord
	ld	de, (CurrentBuffer)
	add	hl, de		; add buffer offset
	ex	de, hl		; de = top-left corner of sprite in buffer

; Read the sprite width and height.
	ld	hl,(iy+3)		; hl = sprite struct
	ld	iy,(hl)			; iyh = height, iyl = width
	inc	hl
	;	ld	a, ti.lcdHeight
	sub	a, (hl)
	inc	hl			; hl = sprite data
; Initialize values for looping.
_RLETSprite_NoClip_Begin:
; Generate the code to advance the buffer pointer to the start of the next row.
	ld	(_RLETSprite_NoClip_ColumnDelta_SMC), a
	wait_quick
; Column loop
_RLETSprite_NoClip_Column:
	ld	a,iyh			; a = height
;; Data loop {
_RLETSprite_NoClip_Trans:
;;; Read the length of a transparent run and skip that many bytes in the buffer.
	ld	c,(hl)			; bc = trans run length
	inc	hl
	sub	a,c			; a = height remaining after trans run
	ex	de,hl			; de = sprite, hl = buffer
_RLETSprite_NoClip_TransSkip:
	add	hl,bc			; skip trans run
;;; Break out of data loop if height remaining == 0.
	jr	z,_RLETSprite_NoClip_ColumnEnd ; z ==> height remaining == 0
	ex	de,hl			; de = buffer, hl = sprite
_RLETSprite_NoClip_Opaque:
;;; Read the length of an opaque run and copy it to the buffer.
	ld	c,(hl)			; bc = opaque run length
	inc	hl
	sub	a,c			; a = height remaining after opqaue run
_RLETSprite_NoClip_OpaqueCopy:
	ldir				; copy opaque run
;;; Continue data loop while height remaining != 0.
	jr	nz,_RLETSprite_NoClip_Trans ; nz ==> height remaining != 0
	ex	de,hl			; de = sprite, hl = buffer
;; }
_RLETSprite_NoClip_ColumnEnd:
;; Advance buffer pointer to the next column
	ld	c,0			; c = (lcdHeight-height)
_RLETSprite_NoClip_ColumnDelta_SMC := $-1
	add	hl,bc			; advance buffer to next column
	ex	de,hl			; de = buffer, hl = sprite
;; Decrement width remaining. Continue column loop while not zero.
	dec	iyl			; decrement width remaining
	jr	nz,_RLETSprite_NoClip_Column ; nz ==> width remaining != 0
; }
; Done.
	ret

;-------------------------------------------------------------------------------
gfy_ConvertFromRLETSprite: ; MODIFIED_FROM_GRAPHX
; Converts a sprite with RLE transpareny to a sprite with normal transparency.
; Arguments:
;  arg0 : pointer to gfy_rletsprite_t input
;  arg1 : pointer to gfy_sprite_t output
; Returns:
;  arg1 : pointer to gfy_sprite_t output
	pop	bc
	pop	de			; de = gfy_rletsprite_t *input
	ex	(sp),hl			; hl = gfy_sprite_t *output
	push	de
	push	bc
	ex	de,hl			; de = output, hl = input
; Save output to return.
	push	de
; Read and copy the sprite width and height.
	ld	iy,(hl)			; iyh = height, iyl = width
	ldi				; output height = height
	ldi				; output width = width, hl = input data
; Initialize values for looping.
	inc.s	bc			; bcu = 0
; Row loop {
_ConvertFromRLETSprite_Row:
	ld	a,iyh			; a = height
;; Data loop {
_ConvertFromRLETSprite_Trans:
;;; Read the length of a transparent run.
	ld	b,(hl)			; b = trans run length
	inc	hl
	inc	b
	dec	b
;;; Skip the transparent run if the length is zero.
	jr	z,_ConvertFromRLETSprite_Opaque ; z ==> trans run length == 0
;;; Write <transparent run length> zeros to the output.
	sub	a,b			; a = height remaining after trans run
	ld	c,0			; c = trans color
smcByte _TransparentColor
	ex	de,hl			; de = input data, hl = output data
_ConvertFromRLETSprite_TransLoop:
	ld	(hl),c			; write trans color to output
	inc	hl
	djnz	_ConvertFromRLETSprite_TransLoop ; decrement trans run length remaining,
						 ; nz ==> trans run length remaining != 0
	ex	de,hl			; de = output data, hl = input data
;;; Break out of data loop if height remaining == 0.
	jr	z,_ConvertFromRLETSprite_RowEnd ; z ==> height remaining == 0
_ConvertFromRLETSprite_Opaque:
;;; Read the length of an opaque run and copy it to the output.
	ld	c,(hl)			; bc = opaque run length
	inc	hl
	sub	a,c			; a = height remaining after opqaue run
	ldir				; copy opaque run
;;; Continue data loop while height remaining != 0.
	jr	nz,_ConvertFromRLETSprite_Trans ; nz ==> height remaining != 0
;; }
_ConvertFromRLETSprite_RowEnd:
;; Decrement width remaining. Continue row loop while not zero.
	dec	iyl			; decrement width remaining
	jr	nz,_ConvertFromRLETSprite_Row ; nz ==> width remaining != 0
; }
; Return output.
	pop	hl			; hl = output
	ret

;-------------------------------------------------------------------------------
gfy_ConvertToNewRLETSprite: ; MODIFIED_FROM_GRAPHX
; Converts a sprite with normal transpareny to a sprite with RLE transparency,
; allocating the exact amount of necessary space for the converted sprite.
; Arguments:
;  arg0 : pointer to gfy_sprite_t input
;  arg1 : pointer to malloc
; Returns:
;  arg1 : pointer to gfy_rletsprite_t output
	pop	bc
	pop	de			; de = gfy_sprite_t *input
	ex	(sp),hl			; hl = malloc
	push	de
	push	bc
	ld	(_ConvertToNewRLETSprite_Malloc_SMC),hl
	ex	de,hl			; hl = input
; Save input to copy after allocating output.
	push	hl
; Read the sprite width and height.
	ld	iy,(hl)			; iyh = height, iyl = width
	inc	hl			; hl = <input data>-1
; Initialize values for looping.
	ld	de,2			; de = 2 = output size
	ld	a,0			; a = trans color
smcByte _TransparentColor
; Row loop {
_ConvertToNewRLETSprite_Row:
	ld	b,iyh			; b = height
	inc	de			; increment output size for first trans run
;; Transparent loop {
_ConvertToNewRLETSprite_TransLoop:
	inc	hl
	cp	a,(hl)			; compare an input pixel to trans color
	inc	de			; increment output size for potential opaque run
	jr	nz,_ConvertToNewRLETSprite_OpaquePixel ; nz ==> not transparent
	dec	de			; revert output size, not opaque run
_ConvertToNewRLETSprite_TransPixel:
;;; Continue while height remaining != 0.
	djnz	_ConvertToNewRLETSprite_TransLoop ; decrement height remaining,
						  ; nz ==> height remaining != 0
;; }
;; Finish row.
	jr	_ConvertToNewRLETSprite_RowEnd
;; Opaque loop {
_ConvertToNewRLETSprite_OpaqueLoop:
	inc	hl
	cp	a,(hl)			; compare an input pixel to trans color
_ConvertToNewRLETSprite_OpaquePixel:
	inc	de			; increment output length
	jr	z,_ConvertToNewRLETSprite_TransPixel ; z ==> transparent
;;; Continue while height remaining != 0.
	djnz	_ConvertToNewRLETSprite_OpaqueLoop ; decrement height remaining,
						   ; nz ==> height remaining != 0
;; }
_ConvertToNewRLETSprite_RowEnd:
;; Decrement width remaining. Continue row loop while not zero.
	dec	iyl			; decrement width remaining
	jr	nz,_ConvertToNewRLETSprite_Row ; nz ==> width remaining != 0
; }
; Allocate output.
	push	de
	call	0			; malloc(output size), hl = output
_ConvertToNewRLETSprite_Malloc_SMC := $-3
	pop	de
; Convert sprite.
	pop	de			; de = input
	jr	_ConvertToRLETSprite_ASM

;-------------------------------------------------------------------------------
gfy_ConvertToRLETSprite: ; MODIFIED_FROM_GRAPHX
; Converts a sprite with normal transpareny to a sprite with RLE transparency.
; Arguments:
;  arg0 : pointer to gfy_sprite_t input
;  arg1 : pointer to gfy_rletsprite_t output
; Returns:
;  arg1 : pointer to gfy_rletsprite_t output
	pop	bc
	pop	de			; de = gfy_sprite_t *input
	ex	(sp),hl			; hl = gfy_rletsprite_t *output
	push	de
	push	bc
_ConvertToRLETSprite_ASM:
	ex	de,hl			; de = output, hl = input
; Save output to return.
	push	de
; Read and copy the sprite width and height.
	ld	iy,(hl)			; iyh = height, iyl = width
	ldi				; output height = height
	ldi				; output width = width, hl = input data
; Initialize values for looping.
	inc.s	bc			; bcu = 0
	ld	a,0			; a = trans color
smcByte _TransparentColor
; Row loop {
_ConvertToRLETSprite_Row:
	ld	b,iyh			; b = height
;; Data loop {
_ConvertToRLETSprite_Trans:
;;; Calculate the length of a transparent run.
	ld	c,0			; c = 0 = trans run length
;;; Transparent loop {
_ConvertToRLETSprite_TransLoop:
	cp	a,(hl)			; compare an input pixel to trans color
	jr	nz,_ConvertToRLETSprite_TransEnd ; nz ==> not transparent
	inc	hl
	inc	bc			; increment trans run length
;;;; Continue transparent loop while height remaining != 0.
	djnz	_ConvertToRLETSprite_TransLoop ; decrement height remaining,
					       ; nz ==> height remaining != 0
;;; }
;;; Write the length of the transparent run to the output.
_ConvertToRLETSprite_TransEnd:
	ex	de,hl			; de = input data, hl = output data
	ld	(hl),c			; write trans run length
	inc	hl
	ex	de,hl			; de = output data, hl = input data
;;; Break out of data loop if height remaining == 0.
	jr	z,_ConvertToRLETSprite_RowEnd ; z ==> last pixel was transparent
					      ;   ==> height remaining == 0
;;; Copy an opaque run to the output.
_ConvertToRLETSprite_Opaque:
	ld	c,0			; c = 0 = opaque run length
	push	de			; (sp) = location to write opaque run length
	inc	de
;;; Opaque loop {
_ConvertToRLETSprite_OpaqueLoop:
	cp	a,(hl)			; compare an input pixel to trans color
	jr	z,_ConvertToRLETSprite_OpaqueEnd ; z ==> transparent
	inc	bc			; cancel dec bc from upcoming ldi
	ldi				; copy opaque pixel
	inc	bc			; increment opaque run length
;;;; Continue opaque/data loop while height remaining != 0.
	djnz	_ConvertToRLETSprite_OpaqueLoop ; decrement height remaining,
						; nz ==> height remaining != 0
_ConvertToRLETSprite_OpaqueEnd:
	ex	(sp),hl			; (sp) = input data, hl = location to write opaque run length
	ld	(hl),c			; write opaque run length
	pop	hl			; hl = input data
;;; Continue data loop if height remaining != 0.
	jr	z,_ConvertToRLETSprite_Trans ; z ==> last pixel was transparent
					     ;   ==> height remaining != 0
;;; }
;; }
_ConvertToRLETSprite_RowEnd:
;; Decrement width remaining. Continue row loop while not zero.
	dec	iyl			; decrement width remaining
	jr	nz,_ConvertToRLETSprite_Row ; nz ==> width remaining != 0
; }
; Return output.
	pop	hl			; hl = output
	ret

;-------------------------------------------------------------------------------
; Inner library routines
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_Maximum: ; COPIED_FROM_GRAPHX
; Calculate the resut of a signed comparison
; Inputs:
;  DE,HL=numbers
; Oututs:
;  HL=max number
	or	a,a
.no_carry:
	sbc	hl,de
	add	hl,de
	jp	p,.skip
	ret	pe
	ex	de,hl
.skip:
	ret	po
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
_Minimum: ; COPIED_FROM_GRAPHX
; Calculate the resut of a signed comparison
; Inputs:
;  DE,HL=numbers
; Oututs:
;  HL=min number
	or	a,a
.no_carry:
	sbc	hl,de
	ex	de,hl
	jp	p,.skip
	ret	pe
	add	hl,de
.skip:
	ret	po
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_ClipRegion: ; COPIED_FROM_GRAPHX
; Calculates the new coordinates given the clip  and inputs
; Inputs:
;  None
; Outputs:
;  Modifies data registers
;  Sets C flag if offscreen
	ld	hl,0
smcWord _XMin
.XMin := $-3
	ld	de,(iy+3)
	call	_Maximum
	ld	(iy+3),hl
	ld	hl,ti.lcdWidth
smcWord _XMax
.XMax := $-3
	ld	de,(iy+9)
	call	_Minimum
	ld	(iy+9),hl
	ld	de,(iy+3)
	call	.compare
	ret	c
	ld	hl,0
smcWord _YMin
.YMin := $-3
	ld	de,(iy+6)
	call	_Maximum.no_carry
	ld	(iy+6),hl
	ld	hl,ti.lcdHeight
smcWord _YMax
.YMax := $-3
	ld	de,(iy+12)
	call	_Minimum
	ld	(iy+12),hl
	ld	de,(iy+6)
.compare:
	dec	hl
_SignedCompare:
	or	a,a
	sbc	hl,de
	add	hl,hl
	ret	po
	ccf
	ret

;-------------------------------------------------------------------------------
_UCDivA: ; COPIED_FROM_GRAPHX
	sbc	hl,hl
	ld	h,a
	xor	a,a
	ld	l,a
	ex	de,hl
	sbc	hl,hl
	ld	l,c
	call	.load
	ld	c,a
.load:
	ld	b,8
.loop:	add	hl,hl
	add	hl,de
	jr	c,.skip
	sbc	hl,de
.skip:	rla
	djnz	.loop
	ret				; ca = c*256/a, h = c*256%a

;-------------------------------------------------------------------------------
_DivideHLBC: ; COPIED_FROM_GRAPHX
; Performs signed integer division, rounding towards negative
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = floor(HL/BC)
	ld	a,23
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,bc
	jp	m,.positive
	add	hl,bc
	inc	hl
	sbc	hl,de
	jp	po,.signcheck
	inc	a
	jr	.overflowed
.positive:
	inc	hl
	push	hl
	pop	bc
	ex	de,hl
.signcheck:
	add	hl,hl
	ex	de,hl
	sbc	hl,hl
	jr	nc,.loop
	inc	hl
	sbc	hl,bc
.loop:
	ex	de,hl
.overflowed:
	adc	hl,hl
	ex	de,hl
	adc	hl,hl
	add	hl,bc
	jr	c,.spill
	sbc	hl,bc
.spill:
	dec	a
	jr	nz,.loop
	ex	de,hl
	adc	hl,hl
	ret

;-------------------------------------------------------------------------------
if 0
_MultiplyHLBC:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = HL*BC
	push	bc
	pop	de

;-------------------------------------------------------------------------------
; identical to __imulu_fast, but BC and DE are swapped
_MultiplyHLDE:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  DE : Operand 2
; Outputs:
;  HL = HL*DE
	ld	b, d
	ld	c, h
	mlt	bc
	ld	a, c
	dec	sp
	push	hl
	push	de
	inc	sp
	pop	bc
	ld	c, l
	mlt	bc
	add	a, c
	pop	bc
	ld	c, e
	mlt	bc
	add	a, c
	ld	b, e
	ld	c, l
	ld	l, b
	ld	e, c
	mlt	de
	mlt	bc
	mlt	hl
	add	hl, de
	add	a, h
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ret
else
_MultiplyHLDE:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  DE : Operand 2
; Outputs:
;  HL = HL*DE
	push	de
	pop	bc

;-------------------------------------------------------------------------------
; identical to __imulu
_MultiplyHLBC:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = HL*BC
__imulu:
	push	af
	push	de
	ld	d, b
	ld	e, h
	mlt	de
	ld	a, e
	dec	sp
	push	hl
	push	bc
	inc	sp
	pop	de
	ld	e, l
	mlt	de
	add	a, e
	pop	de
	ld	e, c
	mlt	de
	add	a, e
	ld	e, l
	ld	l, c
	mlt	hl
	add	a, h
	ld	h, a
	ld	a, e
	ld	d, b
	mlt	de
	add	hl, de
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	d, a
	ld	e, c
	mlt	de
	add	hl, de
	pop	de
	pop	af
	ret

end if

;-------------------------------------------------------------------------------
_ComputeOutcode:
; Compute the bitcode for a point (x, y) using the clip rectangle
; bounded diagonally by (xmin, ymin), and (xmax, ymax)
; Inputs:
;  HL : X Argument
;  DE : Y Argument
; Outputs:
;   A : Bitcode
	ld	bc,0
smcWord _XMin
	push	hl
	xor	a,a
	sbc	hl,bc
	pop	bc
	add	hl,hl
	jp	po,.skip1
	ccf
.skip1:
	rla
	ld	hl,ti.lcdWidth-1
smcWord _XMaxMinus1
	sbc	hl,bc
	add	hl,hl
	jp	po,.skip2
	ccf
.skip2:
	rla
	ld	hl,0
smcWord _YMin
	scf
	sbc	hl,de
	add	hl,hl
	jp	pe,.skip3
	ccf
.skip3:
	rla
	ld	hl,ti.lcdHeight-1
smcWord _YMaxMinus1
	sbc	hl,de
	add	hl,hl
	rla
	ret	po
	xor	a,1
	ret

;-------------------------------------------------------------------------------
util.getbuffer: ; COPIED_FROM_GRAPHX
	ld	hl,ti.vRam + LcdSize
	ld	de,(ti.mpLcdBase)
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nz,.check
	ld	hl,ti.vRam
.check:
	or	a,a			; if 0, copy buffer to screen
	ret	nz
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
; _ShiftCalculate:

;-------------------------------------------------------------------------------
_SetSmcBytes: ; COPIED_FROM_GRAPHX
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
; Internal library data
;-------------------------------------------------------------------------------

_CharSpacing:
	dl	_DefaultCharSpacing
_TextData:
	dl	_DefaultTextData

_DefaultCharSpacing: ; COPIED_FROM_GRAPHX
	;	0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	3,4,6,8,8,8,8,5,5,5,8,7,4,7,3,8
	db	8,7,8,8,8,8,8,8,8,8,3,4,6,7,6,7
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,5,8,5,8,8
	db	4,8,8,8,8,8,8,8,8,5,8,8,5,8,8,8
	db	8,8,8,8,7,8,8,8,8,8,8,7,3,7,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8

if 0
_DefaultTextData: ; row-major
	db	$00,$00,$00,$00,$00,$00,$00,$00 ;  
	db	$7E,$81,$A5,$81,$BD,$BD,$81,$7E ; ☺
	db	$7E,$FF,$DB,$FF,$C3,$C3,$FF,$7E ; ☻
	db	$6C,$FE,$FE,$FE,$7C,$38,$10,$00 ; ♥
	db	$10,$38,$7C,$FE,$7C,$38,$10,$00 ; ♦
	db	$38,$7C,$38,$FE,$FE,$10,$10,$7C ; ♣
	db	$00,$18,$3C,$7E,$FF,$7E,$18,$7E ; ♠
	db	$00,$00,$18,$3C,$3C,$18,$00,$00 ; •
	db	$FF,$FF,$E7,$C3,$C3,$E7,$FF,$FF ; ◘
	db	$00,$3C,$66,$42,$42,$66,$3C,$00 ; ○
	db	$FF,$C3,$99,$BD,$BD,$99,$C3,$FF ; ◙
	db	$0F,$07,$0F,$7D,$CC,$CC,$CC,$78 ; ♂
	db	$3C,$66,$66,$66,$3C,$18,$7E,$18 ; ♀
	db	$3F,$33,$3F,$30,$30,$70,$F0,$E0 ; ♪
	db	$7F,$63,$7F,$63,$63,$67,$E6,$C0 ; ♫
	db	$99,$5A,$3C,$E7,$E7,$3C,$5A,$99 ; *
	db	$80,$E0,$F8,$FE,$F8,$E0,$80,$00 ; ►
	db	$02,$0E,$3E,$FE,$3E,$0E,$02,$00 ; ◄
	db	$18,$3C,$7E,$18,$18,$7E,$3C,$18 ; ↕
	db	$66,$66,$66,$66,$66,$00,$66,$00 ; ‼
	db	$7F,$DB,$DB,$7B,$1B,$1B,$1B,$00 ; ¶
	db	$3F,$60,$7C,$66,$66,$3E,$06,$FC ; §
	db	$00,$00,$00,$00,$7E,$7E,$7E,$00 ; ▬
	db	$18,$3C,$7E,$18,$7E,$3C,$18,$FF ; ↨
	db	$18,$3C,$7E,$18,$18,$18,$18,$00 ; ↑
	db	$18,$18,$18,$18,$7E,$3C,$18,$00 ; ↓
	db	$00,$18,$0C,$FE,$0C,$18,$00,$00 ; →
	db	$00,$30,$60,$FE,$60,$30,$00,$00 ; ←
	db	$00,$00,$C0,$C0,$C0,$FE,$00,$00 ; └
	db	$00,$24,$66,$FF,$66,$24,$00,$00 ; ↔
	db	$00,$18,$3C,$7E,$FF,$FF,$00,$00 ; ▲
	db	$00,$FF,$FF,$7E,$3C,$18,$00,$00 ; ▼
	db	$00,$00,$00,$00,$00,$00,$00,$00 ;
	db	$C0,$C0,$C0,$C0,$C0,$00,$C0,$00 ; !
	db	$D8,$D8,$D8,$00,$00,$00,$00,$00 ; "
	db	$6C,$6C,$FE,$6C,$FE,$6C,$6C,$00 ; #
	db	$18,$7E,$C0,$7C,$06,$FC,$18,$00 ; $
	db	$00,$C6,$CC,$18,$30,$66,$C6,$00 ; %
	db	$38,$6C,$38,$76,$DC,$CC,$76,$00 ; &
	db	$30,$30,$60,$00,$00,$00,$00,$00 ; '
	db	$30,$60,$C0,$C0,$C0,$60,$30,$00 ; (
	db	$C0,$60,$30,$30,$30,$60,$C0,$00 ; )
	db	$00,$66,$3C,$FF,$3C,$66,$00,$00 ; *
	db	$00,$30,$30,$FC,$FC,$30,$30,$00 ; +
	db	$00,$00,$00,$00,$00,$60,$60,$C0 ; ,
	db	$00,$00,$00,$FC,$00,$00,$00,$00 ; -
	db	$00,$00,$00,$00,$00,$C0,$C0,$00 ; .
	db	$06,$0C,$18,$30,$60,$C0,$80,$00 ; /
	db	$7C,$CE,$DE,$F6,$E6,$C6,$7C,$00 ; 0
	db	$30,$70,$30,$30,$30,$30,$FC,$00 ; 1
	db	$7C,$C6,$06,$7C,$C0,$C0,$FE,$00 ; 2
	db	$FC,$06,$06,$3C,$06,$06,$FC,$00 ; 3
	db	$0C,$CC,$CC,$CC,$FE,$0C,$0C,$00 ; 4
	db	$FE,$C0,$FC,$06,$06,$C6,$7C,$00 ; 5
	db	$7C,$C0,$C0,$FC,$C6,$C6,$7C,$00 ; 6
	db	$FE,$06,$06,$0C,$18,$30,$30,$00 ; 7
	db	$7C,$C6,$C6,$7C,$C6,$C6,$7C,$00 ; 8
	db	$7C,$C6,$C6,$7E,$06,$06,$7C,$00 ; 9
	db	$00,$C0,$C0,$00,$00,$C0,$C0,$00 ; :
	db	$00,$60,$60,$00,$00,$60,$60,$C0 ; ;
	db	$18,$30,$60,$C0,$60,$30,$18,$00 ; <
	db	$00,$00,$FC,$00,$FC,$00,$00,$00 ; =
	db	$C0,$60,$30,$18,$30,$60,$C0,$00 ; >
	db	$78,$CC,$18,$30,$30,$00,$30,$00 ; ?
	db	$7C,$C6,$DE,$DE,$DE,$C0,$7E,$00 ; @
	db	$38,$6C,$C6,$C6,$FE,$C6,$C6,$00 ; A
	db	$FC,$C6,$C6,$FC,$C6,$C6,$FC,$00 ; B
	db	$7C,$C6,$C0,$C0,$C0,$C6,$7C,$00 ; C
	db	$F8,$CC,$C6,$C6,$C6,$CC,$F8,$00 ; D
	db	$FE,$C0,$C0,$F8,$C0,$C0,$FE,$00 ; E
	db	$FE,$C0,$C0,$F8,$C0,$C0,$C0,$00 ; F
	db	$7C,$C6,$C0,$C0,$CE,$C6,$7C,$00 ; G
	db	$C6,$C6,$C6,$FE,$C6,$C6,$C6,$00 ; H
	db	$7E,$18,$18,$18,$18,$18,$7E,$00 ; I
	db	$06,$06,$06,$06,$06,$C6,$7C,$00 ; J
	db	$C6,$CC,$D8,$F0,$D8,$CC,$C6,$00 ; K
	db	$C0,$C0,$C0,$C0,$C0,$C0,$FE,$00 ; L
	db	$C6,$EE,$FE,$FE,$D6,$C6,$C6,$00 ; M
	db	$C6,$E6,$F6,$DE,$CE,$C6,$C6,$00 ; N
	db	$7C,$C6,$C6,$C6,$C6,$C6,$7C,$00 ; O
	db	$FC,$C6,$C6,$FC,$C0,$C0,$C0,$00 ; P
	db	$7C,$C6,$C6,$C6,$D6,$DE,$7C,$06 ; Q
	db	$FC,$C6,$C6,$FC,$D8,$CC,$C6,$00 ; R
	db	$7C,$C6,$C0,$7C,$06,$C6,$7C,$00 ; S
	db	$FF,$18,$18,$18,$18,$18,$18,$00 ; T
	db	$C6,$C6,$C6,$C6,$C6,$C6,$FE,$00 ; U
	db	$C6,$C6,$C6,$C6,$C6,$7C,$38,$00 ; V
	db	$C6,$C6,$C6,$C6,$D6,$FE,$6C,$00 ; W
	db	$C6,$C6,$6C,$38,$6C,$C6,$C6,$00 ; X
	db	$C6,$C6,$C6,$7C,$18,$30,$E0,$00 ; Y
	db	$FE,$06,$0C,$18,$30,$60,$FE,$00 ; Z
	db	$F0,$C0,$C0,$C0,$C0,$C0,$F0,$00 ; [
	db	$C0,$60,$30,$18,$0C,$06,$02,$00 ; \
	db	$F0,$30,$30,$30,$30,$30,$F0,$00 ; ]
	db	$10,$38,$6C,$C6,$00,$00,$00,$00 ; ^
	db	$00,$00,$00,$00,$00,$00,$00,$FF ; _
	db	$C0,$C0,$60,$00,$00,$00,$00,$00 ; `
	db	$00,$00,$7C,$06,$7E,$C6,$7E,$00 ; a
	db	$C0,$C0,$C0,$FC,$C6,$C6,$FC,$00 ; b
	db	$00,$00,$7C,$C6,$C0,$C6,$7C,$00 ; c
	db	$06,$06,$06,$7E,$C6,$C6,$7E,$00 ; d
	db	$00,$00,$7C,$C6,$FE,$C0,$7C,$00 ; e
	db	$1C,$36,$30,$78,$30,$30,$78,$00 ; f
	db	$00,$00,$7E,$C6,$C6,$7E,$06,$FC ; g
	db	$C0,$C0,$FC,$C6,$C6,$C6,$C6,$00 ; h
	db	$60,$00,$E0,$60,$60,$60,$F0,$00 ; i
	db	$06,$00,$06,$06,$06,$06,$C6,$7C ; j
	db	$C0,$C0,$CC,$D8,$F8,$CC,$C6,$00 ; k
	db	$E0,$60,$60,$60,$60,$60,$F0,$00 ; l
	db	$00,$00,$CC,$FE,$FE,$D6,$D6,$00 ; m
	db	$00,$00,$FC,$C6,$C6,$C6,$C6,$00 ; n
	db	$00,$00,$7C,$C6,$C6,$C6,$7C,$00 ; o
	db	$00,$00,$FC,$C6,$C6,$FC,$C0,$C0 ; p
	db	$00,$00,$7E,$C6,$C6,$7E,$06,$06 ; q
	db	$00,$00,$FC,$C6,$C0,$C0,$C0,$00 ; r
	db	$00,$00,$7E,$C0,$7C,$06,$FC,$00 ; s
	db	$30,$30,$FC,$30,$30,$30,$1C,$00 ; t
	db	$00,$00,$C6,$C6,$C6,$C6,$7E,$00 ; u
	db	$00,$00,$C6,$C6,$C6,$7C,$38,$00 ; v
	db	$00,$00,$C6,$C6,$D6,$FE,$6C,$00 ; w
	db	$00,$00,$C6,$6C,$38,$6C,$C6,$00 ; x
	db	$00,$00,$C6,$C6,$C6,$7E,$06,$FC ; y
	db	$00,$00,$FE,$0C,$38,$60,$FE,$00 ; z
	db	$1C,$30,$30,$E0,$30,$30,$1C,$00 ; {
	db	$C0,$C0,$C0,$00,$C0,$C0,$C0,$00 ; |
	db	$E0,$30,$30,$1C,$30,$30,$E0,$00 ; }
	db	$76,$DC,$00,$00,$00,$00,$00,$00 ; ~
	db	$00,$10,$38,$6C,$C6,$C6,$FE,$00 ; Δ
else
_DefaultTextData: ; column-major
	db	$00,$00,$00,$00,$00,$00,$00,$00 ;  
	db	$7E,$81,$AD,$8D,$8D,$AD,$81,$7E ; ☺
	db	$7E,$FF,$D3,$F3,$F3,$D3,$FF,$7E ; ☻
	db	$70,$F8,$FC,$7E,$FC,$F8,$70,$00 ; ♥
	db	$10,$38,$7C,$FE,$7C,$38,$10,$00 ; ♦
	db	$18,$59,$F9,$FF,$F9,$59,$18,$00 ; ♣
	db	$08,$1D,$3D,$7F,$7F,$3D,$1D,$08 ; ♠
	db	$00,$00,$18,$3C,$3C,$18,$00,$00 ; •
	db	$FF,$FF,$E7,$C3,$C3,$E7,$FF,$FF ; ◘
	db	$00,$3C,$66,$42,$42,$66,$3C,$00 ; ○
	db	$FF,$C3,$99,$BD,$BD,$99,$C3,$FF ; ◙
	db	$0E,$1F,$11,$11,$BF,$FE,$E0,$F0 ; ♂
	db	$00,$72,$FA,$8F,$8F,$FA,$72,$00 ; ♀
	db	$03,$07,$FF,$FE,$A0,$A0,$E0,$E0 ; ♪
	db	$03,$FF,$FE,$A0,$A0,$A6,$FE,$FC ; ♫
	db	$99,$5A,$3C,$E7,$E7,$3C,$5A,$99 ; *
	db	$FE,$7C,$7C,$38,$38,$10,$10,$00 ; ►
	db	$10,$10,$38,$38,$7C,$7C,$FE,$00 ; ◄
	db	$00,$24,$66,$FF,$FF,$66,$24,$00 ; ↕
	db	$00,$FA,$FA,$00,$00,$FA,$FA,$00 ; ‼
	db	$60,$F0,$90,$FE,$FE,$80,$FE,$FE ; ¶
	db	$01,$79,$FD,$A5,$A5,$BF,$9E,$80 ; §
	db	$00,$0E,$0E,$0E,$0E,$0E,$0E,$00 ; ▬
	db	$01,$29,$6D,$FF,$FF,$6D,$29,$01 ; ↨
	db	$00,$20,$60,$FE,$FE,$60,$20,$00 ; ↑
	db	$00,$08,$0C,$FE,$FE,$0C,$08,$00 ; ↓
	db	$10,$10,$10,$54,$7C,$38,$10,$00 ; →
	db	$10,$38,$7C,$54,$10,$10,$10,$00 ; ←
	db	$3C,$3C,$04,$04,$04,$04,$04,$00 ; └
	db	$10,$38,$7C,$10,$10,$7C,$38,$10 ; ↔
	db	$0C,$1C,$3C,$7C,$7C,$3C,$1C,$0C ; ▲
	db	$60,$70,$78,$7C,$7C,$78,$70,$60 ; ▼
	db	$00,$00,$00,$00,$00,$00,$00,$00 ;
	db	$FA,$FA,$00,$00,$00,$00,$00,$00 ; !
	db	$E0,$E0,$00,$E0,$E0,$00,$00,$00 ; "
	db	$28,$FE,$FE,$28,$FE,$FE,$28,$00 ; #
	db	$24,$74,$54,$D6,$D6,$5C,$48,$00 ; $
	db	$62,$66,$0C,$18,$30,$66,$46,$00 ; %
	db	$0C,$5E,$F2,$BA,$EC,$5E,$12,$00 ; &
	db	$00,$20,$E0,$C0,$00,$00,$00,$00 ; '
	db	$38,$7C,$C6,$82,$00,$00,$00,$00 ; (
	db	$82,$C6,$7C,$38,$00,$00,$00,$00 ; )
	db	$10,$54,$7C,$38,$38,$7C,$54,$10 ; *
	db	$18,$18,$7E,$7E,$18,$18,$00,$00 ; +
	db	$01,$07,$06,$00,$00,$00,$00,$00 ; ,
	db	$10,$10,$10,$10,$10,$10,$00,$00 ; -
	db	$06,$06,$00,$00,$00,$00,$00,$00 ; .
	db	$06,$0C,$18,$30,$60,$C0,$80,$00 ; /
	db	$7C,$FE,$9A,$B2,$E2,$FE,$7C,$00 ; 0
	db	$02,$42,$FE,$FE,$02,$02,$00,$00 ; 1
	db	$4E,$DE,$92,$92,$92,$F2,$62,$00 ; 2
	db	$82,$82,$92,$92,$92,$FE,$6C,$00 ; 3
	db	$78,$78,$08,$08,$FE,$FE,$08,$00 ; 4
	db	$E4,$E6,$A2,$A2,$A2,$BE,$9C,$00 ; 5
	db	$7C,$FE,$92,$92,$92,$9E,$0C,$00 ; 6
	db	$80,$80,$86,$8E,$98,$F0,$E0,$00 ; 7
	db	$6C,$FE,$92,$92,$92,$FE,$6C,$00 ; 8
	db	$60,$F2,$92,$92,$92,$FE,$7C,$00 ; 9
	db	$66,$66,$00,$00,$00,$00,$00,$00 ; :
	db	$01,$67,$66,$00,$00,$00,$00,$00 ; ;
	db	$10,$38,$6C,$C6,$82,$00,$00,$00 ; <
	db	$28,$28,$28,$28,$28,$28,$00,$00 ; =
	db	$82,$C6,$6C,$38,$10,$00,$00,$00 ; >
	db	$40,$C0,$9A,$BA,$E0,$40,$00,$00 ; ?
	db	$7C,$FE,$82,$BA,$BA,$FA,$7A,$00 ; @
	db	$3E,$7E,$C8,$88,$C8,$7E,$3E,$00 ; A
	db	$FE,$FE,$92,$92,$92,$FE,$6C,$00 ; B
	db	$7C,$FE,$82,$82,$82,$C6,$44,$00 ; C
	db	$FE,$FE,$82,$82,$C6,$7C,$38,$00 ; D
	db	$FE,$FE,$92,$92,$92,$82,$82,$00 ; E
	db	$FE,$FE,$90,$90,$90,$80,$80,$00 ; F
	db	$7C,$FE,$82,$82,$8A,$CE,$4C,$00 ; G
	db	$FE,$FE,$10,$10,$10,$FE,$FE,$00 ; H
	db	$00,$82,$82,$FE,$FE,$82,$82,$00 ; I
	db	$04,$06,$02,$02,$02,$FE,$FC,$00 ; J
	db	$FE,$FE,$10,$38,$6C,$C6,$82,$00 ; K
	db	$FE,$FE,$02,$02,$02,$02,$02,$00 ; L
	db	$FE,$FE,$70,$38,$70,$FE,$FE,$00 ; M
	db	$FE,$FE,$60,$30,$18,$FE,$FE,$00 ; N
	db	$7C,$FE,$82,$82,$82,$FE,$7C,$00 ; O
	db	$FE,$FE,$90,$90,$90,$F0,$60,$00 ; P
	db	$7C,$FE,$82,$8E,$86,$FF,$7D,$00 ; Q
	db	$FE,$FE,$90,$98,$9C,$F6,$62,$00 ; R
	db	$64,$F6,$92,$92,$92,$DE,$4C,$00 ; S
	db	$80,$80,$80,$FE,$FE,$80,$80,$80 ; T
	db	$FE,$FE,$02,$02,$02,$FE,$FE,$00 ; U
	db	$F8,$FC,$06,$06,$06,$FC,$F8,$00 ; V
	db	$FC,$FE,$06,$0C,$06,$FE,$FC,$00 ; W
	db	$C6,$EE,$38,$10,$38,$EE,$C6,$00 ; X
	db	$E2,$F2,$16,$1C,$18,$F0,$E0,$00 ; Y
	db	$82,$86,$8E,$9A,$B2,$E2,$C2,$00 ; Z
	db	$FE,$FE,$82,$82,$00,$00,$00,$00 ; [
	db	$80,$C0,$60,$30,$18,$0C,$06,$00 ; \
	db	$82,$82,$FE,$FE,$00,$00,$00,$00 ; ]
	db	$10,$30,$60,$C0,$60,$30,$10,$00 ; ^
	db	$01,$01,$01,$01,$01,$01,$01,$01 ; _
	db	$C0,$E0,$20,$00,$00,$00,$00,$00 ; `
	db	$04,$2E,$2A,$2A,$2A,$3E,$1E,$00 ; a
	db	$FE,$FE,$12,$12,$12,$1E,$0C,$00 ; b
	db	$1C,$3E,$22,$22,$22,$36,$14,$00 ; c
	db	$0C,$1E,$12,$12,$12,$FE,$FE,$00 ; d
	db	$1C,$3E,$2A,$2A,$2A,$3A,$18,$00 ; e
	db	$00,$12,$7E,$FE,$92,$C0,$40,$00 ; f
	db	$19,$3D,$25,$25,$25,$3F,$3E,$00 ; g
	db	$FE,$FE,$20,$20,$20,$3E,$1E,$00 ; h
	db	$22,$BE,$BE,$02,$00,$00,$00,$00 ; i
	db	$02,$03,$01,$01,$01,$BF,$BE,$00 ; j
	db	$FE,$FE,$08,$18,$3C,$26,$02,$00 ; k
	db	$82,$FE,$FE,$02,$00,$00,$00,$00 ; l
	db	$3E,$3E,$18,$1E,$38,$3E,$1E,$00 ; m
	db	$3E,$3E,$20,$20,$20,$3E,$1E,$00 ; n
	db	$1C,$3E,$22,$22,$22,$3E,$1C,$00 ; o
	db	$3F,$3F,$24,$24,$24,$3C,$18,$00 ; p
	db	$18,$3C,$24,$24,$24,$3F,$3F,$00 ; q
	db	$3E,$3E,$20,$20,$20,$30,$10,$00 ; r
	db	$12,$3A,$2A,$2A,$2A,$2E,$24,$00 ; s
	db	$20,$20,$FC,$FE,$22,$22,$00,$00 ; t
	db	$3C,$3E,$02,$02,$02,$3E,$3E,$00 ; u
	db	$38,$3C,$06,$06,$06,$3C,$38,$00 ; v
	db	$3C,$3E,$06,$0C,$06,$3E,$3C,$00 ; w
	db	$22,$36,$1C,$08,$1C,$36,$22,$00 ; x
	db	$39,$3D,$05,$05,$05,$3F,$3E,$00 ; y
	db	$22,$26,$2E,$2A,$3A,$32,$22,$00 ; z
	db	$10,$10,$7C,$EE,$82,$82,$00,$00 ; {
	db	$EE,$EE,$00,$00,$00,$00,$00,$00 ; |
	db	$82,$82,$EE,$7C,$10,$10,$00,$00 ; }
	db	$40,$C0,$80,$C0,$40,$C0,$80,$00 ; ~
	db	$0E,$1E,$32,$62,$32,$1E,$0E,$00 ; Δ
end if

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

_TmpCharSprite:
	db	8,8
_TmpCharData:
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0

;-------------------------------------------------------------------------------

	ld a, 0
gfy_Color := $-1
smcByte _Color

	ld	a, TRASPARENT_COLOR
gfy_Transparent_Color := $-1
smcByte _TransparentColor

	ld	a, TEXT_FG_COLOR
gfy_Text_FG_Color := $-1
smcByte _TextFGColor

	ld	a, TEXT_BG_COLOR
gfy_Text_BG_Color := $-1
smcByte _TextBGColor

	ld	a, TEXT_TP_COLOR
gfy_Text_TP_Color := $-1
smcByte _TextTPColor

	ld	a, 8
gfy_FontHeight := $-1
smcByte _TextHeight

;-------------------------------------------------------------------------------

	ld	hl, 0
gfy_ClipXMin := $-3
smcWord _XMin

	ld	a, 0
gfy_ClipYMin := $-1
smcByte _YMin

	ld	hl, ti.lcdWidth
gfy_ClipXMax := $-3
smcWord _XMax

	ld	a, ti.lcdHeight
gfy_ClipYMax := $-1
smcByte _YMax

	ld	hl, ti.lcdWidth
gfy_ClipXSpan := $-3
smcWord _XSpan

	ld	a, ti.lcdHeight
gfy_ClipYSpan := $-1
smcByte _YSpan

	ld	hl, ti.lcdWidth-1
gfy_ClipXMaxMinus1 := $-3
smcWord _XMaxMinus1

	ld	a, ti.lcdHeight-1
gfy_ClipYMaxMinus1 := $-1
smcByte _YMaxMinus1

;-------------------------------------------------------------------------------

; export	gfy_DefaultCharSpacing
; export	gfy_DefaultTextData
; export	gfy_CharSpacing
; export	gfy_TextData

; export	gfy_TextXPos
; export	gfy_TextYPos
; export	gfy_TextWidthScale
; export	gfy_TextHeightScale
; export	gfy_FontHeight
; export	gfy_MonospaceFont
; export	gfy_TmpCharSprite

; export	gfy_Color
; export	gfy_Transparent_Color
; export	gfy_Text_FG_Color
; export	gfy_Text_BG_Color
; export	gfy_Text_TP_Color

; export	gfy_ClipXMin
; export	gfy_ClipYMin
; export	gfy_ClipXMax
; export	gfy_ClipYMax
; export	gfy_ClipXSpan
; export	gfy_ClipYSpan
; export	gfy_ClipXMaxMinus1
; export	gfy_ClipYMaxMinus1

gfy_DefaultCharSpacing := _DefaultCharSpacing
gfy_DefaultTextData    := _DefaultTextData
gfy_CharSpacing        := _CharSpacing
gfy_TextData           := _TextData

gfy_TextXPos        := _TextXPos
gfy_TextYPos        := _TextYPos
gfy_TextWidthScale  := _TextWidthScale
gfy_TextHeightScale := _TextHeightScale
; gfy_FontHeight      := _TextHeight
gfy_MonospaceFont   := _TextFixedWidth
gfy_TmpCharSprite   := _TmpCharSprite

; gfy_Color             := _Color
; gfy_Transparent_Color := _TransparentColor
; gfy_Text_FG_Color     := _TextFGColor
; gfy_Text_BG_Color     := _TextBGColor
; gfy_Text_TP_Color     := _TextTPColor

; gfy_ClipXMin := _XMin
; gfy_ClipYMin := _YMin
; gfy_ClipXMax := _XMax
; gfy_ClipYMax := _YMax
; gfy_ClipXSpan := _XSpan
; gfy_ClipYSpan := _YSpan
; gfy_ClipXMaxMinus1 := _XMaxMinus1
; gfy_ClipYMaxMinus1 := _YMaxMinus1

gfy_SineTable := _SineTable

;-------------------------------------------------------------------------------
; libc
;-------------------------------------------------------------------------------

; __bremu     := 
; _memcpy     := $0000A4
__idivs     := $00013C
__idivu     := $000140
__ixor      := $000198
__sremu     := $00023C
__ineg      := $000160
; __indcallhl := 
_memmove    := $0000A8
; __imulu     := $000154
__ishl      := $000174
__setflag   := $000218
__iand      := $000134
; _memset     := $0000AC
__frameset  := $00012C
__frameset0 := $000130
__iremu     := $000170
__bshl      := $000100
__land      := $0001A4
__ior       := $000168
__ishru     := $000184
__lshru     := $0001EC

; __fcmp      := $000274
; __fneg      := $00028C
; __fadd      := $000270
; __fsub      := $000290
; __fmul      := $000288
; __fdiv      := $000278
; __ftol      := $00027C
; __ftoul     := __ftol
; __ltof      := $000284
; __ultof     := $000280
; _sinf       := $022118
; _cosf       := $02211C

; for debugging
_boot_sprintf := $0000BC

__indcallhl := _indcallHL

;-------------------------------------------------------------------------------
; inlined routines
;-------------------------------------------------------------------------------

_memcpy:
	ld	iy, -1
	add	iy, sp
	ld	bc, (iy + 10)  ; Load count
	sbc	hl, hl
	add	hl, bc
	jr	nc, .zero
	ld	de, (iy + 4)  ; Load destination
	ld	hl, (iy + 7)  ; Load source
	ldir
.zero:
	ld	hl, (iy + 4)  ; Return the destination pointer
	ret

__set_bc_and_mul_hl_by_240:
	push	hl
	pop	bc
	add	hl, hl	; 2
	add	hl, bc	; 3
	add	hl, hl	; 6
	add	hl, bc	; 7
	add	hl, hl	; 14
	add	hl, bc	; 15
	add	hl, hl	; 30
	add	hl, hl	; 60
	add	hl, hl	; 120
	add	hl, hl	; 240
	ld	bc, 240
	ret

_memset:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	bc, (iy + 9)
	cpi
	add	hl, bc
	ret	c
	dec	hl
	ld	e, (iy + 6)
	ld	(hl), e
	ret	po
	push	hl
	pop	de
	dec	de
	lddr
	ret

;-------------------------------------------------------------------------------
; graphy.c.src
;-------------------------------------------------------------------------------

include 'graphy.c.src'
