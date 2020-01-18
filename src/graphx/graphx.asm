;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'GRAPHX', 11

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export gfx_Begin
	export gfx_End
	export gfx_SetColor
	export gfx_SetDefaultPalette
	export gfx_SetPalette
	export gfx_FillScreen
	export gfx_SetPixel
	export gfx_GetPixel
	export gfx_GetDraw
	export gfx_SetDraw
	export gfx_SwapDraw
	export gfx_Blit
	export gfx_BlitLines
	export gfx_BlitRectangle
	export gfx_PrintChar
	export gfx_PrintInt
	export gfx_PrintUInt
	export gfx_PrintString
	export gfx_PrintStringXY
	export gfx_SetTextXY
	export gfx_SetTextBGColor
	export gfx_SetTextFGColor
	export gfx_SetTextTransparentColor
	export gfx_SetFontData
	export gfx_SetFontSpacing
	export gfx_SetMonospaceFont
	export gfx_GetStringWidth
	export gfx_GetCharWidth
	export gfx_GetTextX
	export gfx_GetTextY
	export gfx_Line
	export gfx_HorizLine
	export gfx_VertLine
	export gfx_Circle
	export gfx_FillCircle
	export gfx_Rectangle
	export gfx_FillRectangle
	export gfx_Line_NoClip
	export gfx_HorizLine_NoClip
	export gfx_VertLine_NoClip
	export gfx_FillCircle_NoClip
	export gfx_Rectangle_NoClip
	export gfx_FillRectangle_NoClip
	export gfx_SetClipRegion
	export gfx_GetClipRegion
	export gfx_ShiftDown
	export gfx_ShiftUp
	export gfx_ShiftLeft
	export gfx_ShiftRight
	export gfx_Tilemap
	export gfx_Tilemap_NoClip
	export gfx_TransparentTilemap
	export gfx_TransparentTilemap_NoClip
	export gfx_TilePtr
	export gfx_TilePtrMapped
	export gfx_Reserved
	export gfx_AllocSprite
	export gfx_Sprite
	export gfx_TransparentSprite
	export gfx_Sprite_NoClip
	export gfx_TransparentSprite_NoClip
	export gfx_GetSprite
	export gfx_ScaledSprite_NoClip
	export gfx_ScaledTransparentSprite_NoClip
	export gfx_FlipSpriteY
	export gfx_FlipSpriteX
	export gfx_RotateSpriteC
	export gfx_RotateSpriteCC
	export gfx_RotateSpriteHalf
	export gfx_Polygon
	export gfx_Polygon_NoClip
	export gfx_FillTriangle
	export gfx_FillTriangle_NoClip
;-------------------------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------------------------
	export gfx_Deprecated
	export gfx_SetTextScale
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
	export gfx_SetTransparentColor
	export gfx_ZeroScreen
	export gfx_SetTextConfig
	export gfx_GetSpriteChar
;-------------------------------------------------------------------------------
; v4 functions
;-------------------------------------------------------------------------------
	export gfx_Lighten
	export gfx_Darken
;-------------------------------------------------------------------------------
; v5 functions
;-------------------------------------------------------------------------------
	export gfx_SetFontHeight
	export gfx_ScaleSprite
	export gfx_FloodFill
;-------------------------------------------------------------------------------
; v6 functions
;-------------------------------------------------------------------------------
	export gfx_RLETSprite
	export gfx_RLETSprite_NoClip
	export gfx_ConvertFromRLETSprite
	export gfx_ConvertToRLETSprite
	export gfx_ConvertToNewRLETSprite
;-------------------------------------------------------------------------------
; v7 functions
;-------------------------------------------------------------------------------
	export gfx_RotateScaleSprite
	export gfx_RotatedScaledTransparentSprite_NoClip
	export gfx_RotatedScaledSprite_NoClip
;-------------------------------------------------------------------------------
; v8 functions
;-------------------------------------------------------------------------------
	export gfx_SetCharData
;-------------------------------------------------------------------------------
; v9 functions
;-------------------------------------------------------------------------------
	export gfx_Wait
;-------------------------------------------------------------------------------
; v10 functions
;-------------------------------------------------------------------------------
	export gfx_CopyRectangle

;-------------------------------------------------------------------------------
LcdSize            := LcdWidth*LcdHeight
; minimum stack size to provide for interrupts if moving the stack
InterruptStackSize := 4000
CurrentBuffer      := mpLcdLpbase
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

macro smcByte name*, addr: $-1
	local link
	link := addr
	name equ link
end macro

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
gfx_Begin:
; Sets up the graphics canvas
; Arguments:
;  arg0: bpp mode to start in
; Returns:
;  None
	call	_boot_ClearVRAM		; clear the screen
lcdGraphxMode := lcdWatermark+lcdIntFront+lcdPwr+lcdBgr+lcdBpp8
	ld	de,lcdGraphxMode
	ld	hl,CurrentBuffer
SetGfx:
	ld	bc,VRAM
	ld	(hl),bc			; set the current draw to the screen
assert CurrentBuffer and -$100 = mpLcdRange
	ld	l,lcdCtrl
	ld	(hl),de			; set lots of control parameters
	ld	l,lcdTiming0+1
	ld	de,_LcdTiming
assert VRAM and $FF = 0
	ld	b,8+1			; +1 because c = 0, so first ldi will
					; decrement b
.ExchangeTimingLoop:			; exchange stored and active timing
	ld	a,(de)
	ldi
	dec	hl
	ld	(hl),a
	inc	hl
	djnz	.ExchangeTimingLoop
;	jp	gfx_SetDefaultPalette	; setup the default palette
assert $ = gfx_SetDefaultPalette

;-------------------------------------------------------------------------------
gfx_SetDefaultPalette:
; Sets up the default palette where H=L
; Arguments:
;  None
; Returns:
;  None
	ld	de,mpLcdPalette		; address of mmio palette
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
gfx_End:
; Closes the graphics library and sets up for the TI-OS
; Arguments:
;  None
; Returns:
;  None
	call	_boot_ClearVRAM		; clear the screen
	ld	de,lcdNormalMode
	ld	hl,mpLcdBase
	jr	SetGfx			; restore the screen mode

;-------------------------------------------------------------------------------
gfx_AllocSprite:
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
gfx_SetClipRegion:
; Sets the clipping region for clipped routines
; Arguments:
;  arg0 : Xmin
;  arg1 : Ymin
;  arg2 : Xmax
;  arg3 : Ymax
; Returns:
;  None
	ld	hl,_ClipRegion_Full	; clip against the actual LCD screen
	call	.copy
	ld	iy,0
	add	iy,sp
	call	_ClipRegion		; iy points to the start of the arguments
	ret	c
	lea	hl,iy+3
.copy:
	ld	de,_XMin
	ld	bc,4*3
	ldir
	ret

;-------------------------------------------------------------------------------
gfx_Lighten:
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
gfx_Darken:
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
gfx_SetColor:
; Sets the global color index for all routines
; Arguments:
;  arg0 : Global color index
; Returns:
;  Previous global color index
	setSmcBytesFast _Color

;-------------------------------------------------------------------------------
gfx_SetTransparentColor:
; Sets the global transparent color index for all routines
; Arguments:
;  arg0 : Transparent color index
; Returns:
;  Previous transparent color index
	setSmcBytes _TransparentColor

;-------------------------------------------------------------------------------
gfx_FillScreen:
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
	call	gfx_Wait
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
	org mpLcdCrsrImage
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
gfx_ZeroScreen:
; Fills the screen with color index 0
; Arguments:
;  None
; Returns:
;  None
	ld	l,0
	push	hl
	call	gfx_FillScreen
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfx_SetPalette:
; Sets the palette colors
; Arguments:
;  arg0 : Pointer to palette
;  arg1 : Size of palette in bytes
;  arg2 : Offset at which to start inserting the palette
; Returns:
;  None
	pop	iy			; iy = return vector
	pop	de			; de = src
	pop	bc			; bc = size
	ex	(sp),hl			; l = offset
	push	bc
	push	de
	ld	a,l
assert mpLcdPalette and 1 = 0
	ld	hl,mpLcdPalette shr 1
	ld	l,a			; hl = (palette >> 1) + offset
	add	hl,hl			; hl = &palette[offset] = dest
	ex	de,hl			; de = dest, hl = src
	ldir
	jp	(iy)

;-------------------------------------------------------------------------------
gfx_GetPixel:
; Gets the color index of a pixel
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  Color index of X,Y coordinate
	ld	hl,3
	add	hl,sp			; hl = &x
	inc.s	bc
	ld	c,(hl)
	inc	hl
	ld	b,(hl)			; bc = (uint16_t)x
	inc	hl
	inc	hl			; hl = &y
	ld	e,(hl)			; e = y
_GetPixel:
	ld	d,LcdWidth/2
	mlt	de			; de = y * (lcdWidth / 2)
	ld	hl,(CurrentBuffer)	; hl = buffer
	add	hl,bc
	add	hl,de
	add	hl,de			; hl = buffer + y * (lcdWidth / 2)*2 + (uint16_t)x
					;    = buffer + y * lcdWidth + (uint16_t)x
					;    = &buffer[y][x]
; No clipping is necessary, because if the pixel is offscreen, the result is
; undefined. All that is necessary is to ensure that there are no side effects
; of reading outside of the buffer. In this case, the largest possible offset
; into the buffer is 255 * lcdWidth + 65535 = 147135 bytes. Even in the case
; that the current buffer is the second half of VRAM, the largest that this
; pointer can be is $D52C00 + 147135 = $D76ABF. This goes beyond the end of
; mapped RAM, but only into unmapped memory with no read side effects.
	ld	a,(hl)			; a = buffer[y][x]
	ret

;-------------------------------------------------------------------------------
gfx_SetPixel:
; Sets the color pixel to the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	bc,(hl)			; bc = x coordinate
	ld	de,3
	add	hl,de			; move to next argument
	ld	e,(hl)			; e = y coordinate
_SetPixel:
	wait_quick
_SetPixel_NoWait:
	ld	hl,-LcdWidth
	add	hl,bc
	ret	c			; return if out of bounds
	ld	hl,-LcdHeight
	add	hl,de
	ret	c			; return if out of bounds
	ld	hl,(CurrentBuffer)
	add	hl,bc
	ld	d,LcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	(hl),0			; get the actual pixel
smcByte _Color
	ret

;-------------------------------------------------------------------------------
gfx_FillRectangle:
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
gfx_FillRectangle_NoClip:
; Draws an unclipped rectangle with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	a,(iy+12)		; a = height
	or	a,a
	ret	z			; make sure height is not 0
	ld	bc,(iy+9)		; bc = width
	sbc	hl,hl
	adc	hl,bc
	ret	z			; make sure width is not 0
	ld	hl,(iy+3)		; hl = x coordinate
	ld	e,(iy+6)		; e = y coordinate
_FillRectangle_NoClip:
	ld	d,LcdWidth / 2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(CurrentBuffer)
	add	hl,de
	ex	de,hl			; de -> place to begin drawing
	push	de
	ld	(.width1),bc
	ld	(.width2),bc
	ld	hl,_Color
	wait_quick
	ldi				; check if we only need to draw 1 pixel
	pop	hl
	jp	po,.skip
	ldir
.skip:
	dec	a
	ret	z
	inc	b
	ld	c,$40			; = slightly faster "ld bc,LcdWidth"
.loop:
	add	hl,bc
	dec	de
	ex	de,hl
.width1 = $ + 1
	ld	bc,0
	lddr
	dec	a
	ret	z
	ld	bc,(2 * LcdWidth) + 1
	add	hl,bc
	inc	de
	ex	de,hl
.width2 = $ + 1
	ld	bc,0
	ldir
	ld	bc,(2 * LcdWidth) - 1
	dec	a
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
gfx_Rectangle:
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
	call	gfx_HorizLine		; top horizontal line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	gfx_VertLine		; left vertical line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	add	hl,bc			; add x and width
	dec	hl
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	gfx_VertLine		; right vertical line
	ld	de,(ix+6)
	ld	hl,(ix+9)
	ld	bc,(ix+15)
	add	hl,bc
	dec	hl			; add y and height
	ld	bc,(ix+12)
	push	bc
	push	hl
	push	de
	call	gfx_HorizLine		; bottom horizontal line
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_Rectangle_NoClip:
; Draws an unclipped rectangle outline with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	a,(iy+12)		; a = height
	or	a,a
	ret	z			; abort if height == 0
	ld	bc,(iy+9)		; bc = width
	sbc	hl,hl
	adc	hl,bc
	ret	z			; abort if width == 0
	push	bc
	call	_HorizLine_NoClip_NotDegen_StackXY ; draw top horizontal line
						   ; hl = &buf[y][x+width-1]
	ld	b,a			; b = height
	call	_VertLine_NoClip_Draw	; draw right vertical line
	ld	b,(iy+12)		; b = height
	ld	e,(iy+6)		; e = y
	call	_VertLine_NoClip_NotDegen_StackX ; draw left vertical line
						 ; hl = &buf[y+height][x]
						 ; de = LcdWidth
	sbc	hl,de			; hl = &buf[y+height-1][x]
	pop	bc			; bc = width
	jp	_HorizLine_NoClip_Draw	; draw bottom horizontal line

;-------------------------------------------------------------------------------
gfx_HorizLine:
; Draws an clipped horizontal line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(_YMin)
	ld	hl,(iy+6)
	mIsHLLessThanDE			; compare y coordinate <-> ymin
	ret	c
	ld	hl,(_YMax)
	dec	hl			; inclusive
	ld	de,(iy+6)
	mIsHLLessThanDE			; compare y coordinate <-> ymax
	ret	c
	ld	hl,(iy+9)
	ld	de,(iy+3)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_XMin)
	call	_Maximum
	ld	(iy+3),hl		; save maximum x value
	ld	hl,(_XMax)
	ld	de,(iy+9)
	call	_Minimum
	ld	(iy+9),hl		; save minimum x value
	ld	de,(iy+3)
	mIsHLLessThanDE
	ret	c
	ld	hl,(iy+9)
	sbc	hl,de
	push	hl
	pop	bc			; bc = length
	jr	_HorizLine_NoClip_StackXY

;-------------------------------------------------------------------------------
gfx_HorizLine_NoClip:
; Draws an unclipped horizontal line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)		; bc = length
_HorizLine_NoClip_StackXY:
	sbc	hl,hl
	adc	hl,bc
	ret	z			; abort if length == 0
_HorizLine_NoClip_NotDegen_StackXY:
	ld	e,(iy+6)		; e = y
	ld	hl,(iy+3)		; hl = x
_HorizLine_NoClip_NotDegen:
	wait_quick
_HorizLine_NoClip_NotDegen_NoWait:
	ld	d,LcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(CurrentBuffer)
	add	hl,de			; hl -> place to draw
_HorizLine_NoClip_Draw:
	ld	(hl),0
smcByte _Color
	cpi
	ret	po
	ex	de,hl
	ld	hl,-1
	add	hl,de
	ldir
	ret

;-------------------------------------------------------------------------------
gfx_VertLine:
; Draws an clipped vertical line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(_XMax)
	dec	hl			; inclusive
	ld	de,(iy+3)
	mIsHLLessThanDE
	ret	c			; return if x > xmax
	ld	hl,(_XMin)
	ex	de,hl
	mIsHLLessThanDE
	ret	c			; return if x < xmin
	ld	hl,(iy+9)
	ld	de,(iy+6)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_YMin)
	call	_Maximum		; get minimum y
	ld	(iy+6),hl
	ld	hl,(_YMax)
	ld	de,(iy+9)
	call	_Minimum		; get maximum y
	ld	(iy+9),hl
	ld	de,(iy+6)
	mIsHLLessThanDE
	ret	c			; return if not within y bounds
	ld	hl,(iy+9)
	sbc	hl,de
	ld	b,l
	jr	_VertLine_NoClip_StackX	; jump to unclipped version

;-------------------------------------------------------------------------------
gfx_VertLine_NoClip:
; Draws an unclipped vertical line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	e,(iy+6)		; e = y
	ld	b,(iy+9)		; b = length
_VertLine_NoClip_StackX:
	xor	a,a
	or	a,b
	ret	z			; abort if length == 0
_VertLine_NoClip_NotDegen_StackX:
	ld	hl,(iy+3)		; hl = x
	ld	d,LcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(CurrentBuffer)
	add	hl,de			; hl -> drawing location
_VertLine_NoClip_Draw:
	ld	de,LcdWidth
	ld	a,0
smcByte _Color
	wait_quick
.loop:
	ld	(hl),a			; loop for height
	add	hl,de
	djnz	.loop
	ret

;-------------------------------------------------------------------------------
gfx_SetDraw:
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
	ld	hl,(mpLcdBase)		; get current base
	ld	bc,vram
	jr	z,.match
	sbc	hl,bc
	jr	nz,.swap		; if not the same, swap
.set:
	ld	bc,vram+LcdSize
.swap:
	ld	(CurrentBuffer),bc
	ex	de,hl
	jp	(hl)
.match:
	sbc	hl,bc
	jr	z,.swap			; if the same, swap
	jr	.set

;-------------------------------------------------------------------------------
gfx_GetDraw:
; Gets the current drawing state
; Arguments:
;  None
; Returns:
;  Returns true if drawing on the buffer
	ld	a,(mpLcdBase+2)		; comparing upper byte only is sufficient
	ld	hl,CurrentBuffer+2
	xor	a,(hl)			; always 0 or 1
	ret

;-------------------------------------------------------------------------------
_WaitQuick:
	ex	(sp),hl			; hl saved, hl = return vector
	push	de			; de saved
	ld	de,gfx_Wait
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
; Fall through to gfx_Wait, but don't let it return immediately. Even if it ends
; up not waiting, it will re-write the quick wait SMC, including for the callee.
	push	hl
;	jr	gfx_Wait+1		; emulated by dummifying next instruction:
	db	$2E			; ret || push hl -> ld l,*

;-------------------------------------------------------------------------------
gfx_Wait:
; Waits for the screen buffer to finish being displayed after gfx_SwapDraw
; Arguments:
;  None
; Returns:
;  None
	ret				; will be SMC'd into push hl
	push	af
	ld	a,(mpLcdRis)
	bit	bLcdIntVcomp,a
	jr	nz,.WaitDone
	push	de
.WaitLoop:
.ReadLcdCurr:
	ld	a,(mpLcdCurr+2)		; a = *mpLcdCurr>>16
	ld	hl,(mpLcdCurr+1)	; hl = *mpLcdCurr>>8
	sub	a,h
	jr	nz,.ReadLcdCurr		; nz ==> lcdCurr may have updated
					;        mid-read; retry read
	ld	de,(CurrentBuffer+1)
	sbc	hl,de
	ld	de,-LcdSize shr 8
	add	hl,de
	jr	nc,.WaitLoop
	pop	de
.WaitDone:
	ld	a,$C9			; ret
	ld	(gfx_Wait),a		; disable wait logic
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
gfx_SwapDraw:
; Swaps the roles of the screen and drawing buffers
; Arguments:
;  None
; Returns:
;  None
	ld	iy,mpLcdRange
.WaitLoop:
	bit	bLcdIntLNBU,(iy+lcdRis)
	jr	z,.WaitLoop
assert vRam and $FF = 0
assert LcdSize and $FF = 0
	ld	bc,(iy-mpLcdRange+CurrentBuffer+1) ; bc = old_draw>>8
.LcdSizeH := (LcdSize shr 8) and $FF
assert .LcdSizeH and lcdIntVcomp
assert .LcdSizeH and lcdIntLNBU
	ld	a,.LcdSizeH		; a = LcdSize>>8
	ld	(iy+lcdBase+1),bc	; screen = old_draw
	ld	(iy+lcdIcr),a		; clear interrupt statuses to wait for
	xor	a,c			; a = (old_draw>>8)^(LcdSize>>8)
	ld	c,a			; c = (old_draw>>8)^(LcdSize>>8)
	inc	b
	res	1,b			; b = (old_draw>>16)+1&-2
					; assuming !((old_draw>>16)&2):
					;   = (old_draw>>16)^1
					;   = (old_draw>>16)^(LcdSize>>16)
					; bc = (old_draw>>8)^(LcdSize>>8)
					;    = new_draw>>8
	ld	(iy-mpLcdRange+CurrentBuffer+1),bc
	ld	hl,gfx_Wait
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
gfx_Circle:
; Draws a clipped circle outline
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	lea	hl,iy-9
	ld	sp,hl
	ld	bc,(iy+9)
	ld	(iy-6),bc
	sbc	hl,hl
	ld	(iy-3),hl
	adc	hl,bc
	jp	z,.exit
	ld	hl,1
	or	a,a
	sbc	hl,bc
	call	gfx_Wait
	jp	.next
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

;-------------------------------------------------------------------------------
gfx_FillCircle:
; Draws an clipped circle
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	push	ix
	ld	ix,0
	add	ix,sp
	lea	hl,ix-9
	ld	sp,hl
	ld	bc,(ix+12)
	ld	(ix-6),bc
	sbc	hl,hl
	ld	(ix-3),hl
	adc	hl,bc
	jp	z,_ResetStack
	ld	hl,1
	or	a,a
	sbc	hl,bc
	jp	.cmp3
.fillsectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(.circle0),hl
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(.circle1),hl
	push	hl
	call	gfx_HorizLine
	ld	hl,0
.circle0 := $-3
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	push	hl
	ld	hl,0
.circle1 := $-3
	push	hl
	call	gfx_HorizLine
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(.circle2),hl
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+9)
	add	hl,bc
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(.circle3),hl
	push	hl
	call	gfx_HorizLine
	ld	hl,0
.circle2 := $-3
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	push	hl
	ld	hl,0
.circle3 := $-3
	push	hl
	call	gfx_HorizLine
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
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_FillCircle_NoClip:
; Draws an unclipped circle
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Radius
; Returns:
;  None
	push	ix
	ld	ix,0
	add	ix,sp
	lea	hl,ix-9
	ld	sp,hl
	ld	bc,(ix+12)
	ld	(ix-6),bc
	sbc	hl,hl
	ld	(ix-3),hl
	adc	hl,bc
	jp	z,_ResetStack
	ld	hl,1
	or	a,a
	sbc	hl,bc
	call	gfx_Wait
	jp	.loop
.fillsectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(.circle0),hl
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	ld	e,l
	ld	bc,(ix-3)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(.circle1),hl
	pop	bc
	call	_HorizLine_NoClip_NotDegen_NoWait
	ld	bc,0
.circle0 := $-3
	ld	de,(ix-6)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	ld	e,l
	ld	hl,0
.circle1 := $-3
	call	_HorizLine_NoClip_NotDegen_NoWait
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(.circle2),hl
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+9)
	add	hl,bc
	ld	e,l
	ld	bc,(ix-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(.circle3),hl
	pop	bc
	call	_HorizLine_NoClip_NotDegen_NoWait
	ld	bc,0
.circle2 := $-3
	ld	de,(ix-3)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	ld	e,l
	ld	hl,0
.circle3 := $-3
	call	_HorizLine_NoClip_NotDegen_NoWait
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
_ResetStack:
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_Line:
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
	ld	b,(iy-1)		; b = outcode0
	ld	a,(iy-2)		; a = outcode1
	tst	a,b
	jp	nz,TrivialReject	; if(outcode0|outcode1)
	or	a,a
	jr	nz,GetOutOutcode
	or	a,b
	jp	z,TrivialAccept
GetOutOutcode:				; select correct outcode
	push	af			; a = outoutcode
	rra
	jr	nc,.notop		; if (outcodeOut & TOP)
	ld	hl,(_YMax)
	dec	hl			; inclusive
	jr	ComputeNewX
.notop:
	rra
	jr	nc,NotBottom		; if (outcodeOut & BOTTOM)
	ld	hl,(_YMin)
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
	ld	hl,(_XMax)
	dec	hl			; inclusive
	jr	ComputeNewY
NotRight:
	rra
	jr	nc,FinishComputations	; if (outcodeOut & LEFT)
	ld	hl,(_XMin)
ComputeNewY:
	push	hl
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc			; xmax_XMin - x0
	ex	de,hl
	ld	hl,(iy+12)
	ld	bc,(iy+6)
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
	jp	CohenSutherlandLoop
TrivialReject:
	inc	sp
	inc	sp
	inc	sp
	ret
TrivialAccept:
	inc	sp
	inc	sp
	inc	sp
;	jr	_Line_NoClip		; line routine handler

;-------------------------------------------------------------------------------
gfx_Line_NoClip:
; Draws an unclipped arbitrary line
; Arguments:
;  arg0 : X1 coordinate (hl)
;  arg1 : Y1 coordinate (b)
;  arg2 : X2 coordinate (de)
;  arg3 : Y2 coordinate (c)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	de,(iy+9)
	ld	b,(iy+6)
	ld	c,(iy+12)		; line from hl,b to de,c
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	c,+_			; draw left to right
	ex	de,hl
	ld	a,b
	ld	b,c
	ld	c,a
_:	push	bc
	pop	iy
	push	hl
	ld	hl,(CurrentBuffer)
	ld	c,160
	mlt	bc
	add	hl,bc
	add	hl,bc			; y0 * screenwidth
	pop	bc
	add	hl,bc			; y0 * screenwidth + x0
	push	hl			; save buffer
	ex	de,hl
	or	a,a
	sbc	hl,bc			; xe - xs
	push	hl
	pop	bc			; bc = dx
	ld	a,iyh
	or	a,a
	sbc	hl,hl
	ld	l,a			; y1
	ex	de,hl
	ld	a,iyl
	sbc	hl,hl
	ld	l,a			; y0
	sbc	hl,de
	jr	nc,$+9
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	inc	hl			; abs(dy)
	ld	a,iyl
	sub	a,iyh
	ld	iy,-320
	jr	c,$+7
	ld	iy,320
	or	a,a
	sbc	hl,bc
	add	hl,bc			; hl = dy
	jr	nc,dl_vertical
dl_horizontal:
	ld	a,l
	or	a,h
	ld	a,$38
	jr	nz,$+4
	xor	a,$20
	ld	(_smc_dl_jr_0 + 0),a ; write smc
	ld	(_smc_dl_width_1 + 1),iy ; write smc
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	inc	hl
	ex	de,hl			; de = -dy
	pop	hl			; restore buffer
	ld	(_smc_dl_dx_1 + 1),bc ; write smc
	ld	(_smc_dl_dy_1 + 1),de ; write smc
	push	bc
	srl	b
	rr	c
	push	bc
	pop	iy			; iy = dx / 2
	pop	bc
	inc	bc
	ld	a,0
smcByte _Color
	wait_quick
dl_hloop:
	ld	(hl),a			; write pixel
	cpi
	ret	po
	add	iy,de			; dy
_smc_dl_jr_0:
	jr	c,dl_hloop
_smc_dl_width_1:
	ld	de,0
	add	hl,de			; y inc
_smc_dl_dx_1:
	ld	de,0			; dx
	add	iy,de
_smc_dl_dy_1:
	ld	de,0			; dy
	jr	dl_hloop
dl_vertical:
	lea	de,iy
	ld	b,c
	ld	a,l
	ld	iyl,a
	ld	c,a
	srl	a			; a = dy / 2
	inc	c
	pop	hl
	wait_quick
dl_vloop:
	ld	(hl),0			; write pixel
smcByte _Color
	dec	c
	ret	z
	add	hl,de			; y inc
	sub	a,b			; dx
	jr	nc,dl_vloop
	inc	hl
	add	a,iyl			; dy
	jr	dl_vloop

;-------------------------------------------------------------------------------
gfx_Blit:
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
	call	gfx_Wait
	ldir				; just do it
	jp	(iy)

;-------------------------------------------------------------------------------
gfx_BlitLines:
; Copies the buffer image to the screen and vice versa line wise
; Arguments:
;  arg0 : Buffer to copy from (screen = 0, buffer = 1)
;  arg1 : Y coordinate
;  arg2 : Number of lines to copy
; Returns:
;  None
	pop	iy			; iy = return vector
	pop	bc
	ld	a,c			; a = buffer to blit from
	pop	de			; e = number of lines to copy
	ex	(sp),hl			; l = y coordinate
	push	de
	push	bc
	ld	h,LcdWidth/2
	ld	d,h
	mlt	hl
	add	hl,hl			; hl -> number of bytes to copy
	push	hl
	ex	de,hl
	mlt	hl
	add	hl,hl			; hl -> offset to start at
	push	hl
	call	util.getbuffer		; determine blit buffers
	pop	bc
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	pop	bc			; number of bytes to copy
	jr	util.blit

;-------------------------------------------------------------------------------
gfx_BlitRectangle:
; Copies the buffer image to the screen and vice versa rectangularly
; Arguments:
;  arg0 : Buffer to copy from (screen = 0, buffer = 1)
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Width
;  arg4 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(iy+6)		; de = x coordinate
	ld	l,(iy+9)		; l = y coordinate
	ld	h,LcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de			; hl = amount to increment
	push	hl			; save amount to increment
	ld	a,(iy+3)		; a = buffer to blit from
	call	util.getbuffer		; determine blit buffers
	pop	bc
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	ld	bc,(iy+12)		; the width of things
	ld	(.width),bc
	push	hl
	ld	hl,LcdWidth
	or	a,a
	sbc	hl,bc			; change in width for rectangle
	ld	(.delta),hl
	pop	hl
	ld	a,(iy+15)
	ld	iy,0
	add	iy,de
	call	gfx_Wait
.loop:
	ld	bc,0			; smc for speedz
.width := $-3
	ldir
	inc	b
	ld	c,$40			; increment to next line
	add	iy,bc
	lea	de,iy
	ld	bc,0			; increment to next line
.delta := $-3
	add	hl,bc
	dec	a
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
gfx_CopyRectangle:
; Copies a rectangle between graphics buffers or to the same graphics buffer.
; Arguments:
;  arg0 : Graphics buffer to copy from.
;  arg1 : Graphics buffer to copy to.
;  arg2 : X coordinate on src.
;  arg3 : Y coordinate on src.
;  arg4 : X coordinate on dst.
;  arg5 : Y coordinate on dst.
;  arg6 : Width of rectangle.
;  arg7 : Height of rectangle.
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 9)		; de = x coordinate src
	ld	l,(iy + 12)		; l = y coordinate src
	ld	h,LcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de			; hl = offset in src
	push	hl
	ld	a,(iy + 3)		; a = buffer src
	call	util.getbuffer
	pop	bc
	add	hl,bc			; hl = start of copy src
	push	hl
	ld	de,(iy + 15)		; de = x coordinate dst
	ld	l,(iy + 18)		; l = y coordinate dst
	ld	h,LcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de			; hl = offset in dst
	push	hl
	ld	a,(iy + 6)		; a = buffer dst
	call	util.getbuffer
	pop	bc
	add	hl,bc
	ex	de,hl			; de = start of copy dst
	ld	bc,(iy + 21)		; rectangle width
	ld	(.width),bc
	ld	hl,LcdWidth
	or	a,a
	sbc	hl,bc			; rectangle stride
	ld	(.stride),hl
	pop	hl			; hl = start of copy src
	ld	a,(iy + 24)
	ld	iy,0
	add	iy,de
	call	gfx_Wait
.loop:
	ld	bc,0			; smc for speedz
.width := $-3
	ldir
	inc	b
	ld	c,$40
	add	iy,bc
	lea	de,iy
	ld	bc,0			; increment to next line
.stride := $-3
	add	hl,bc
	dec	a
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
gfx_ShiftLeft:
; Shifts whatever is in the clip left by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	db	$F6			; magic byte

;-------------------------------------------------------------------------------
gfx_ShiftUp:
; Shifts whatever is in the clip up by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	scf
	ld	a,$B0
	call	_ShiftCalculate
	ld	(ShiftAmountOffset),hl
	jr	z,.next
	sbc	hl,hl
.next:
	ex	de,hl
	ld	hl,(_XMax)
	ld	bc,(_XMin)
	sbc	hl,bc
	sbc	hl,de
	ld	(ShiftCopyAmount),hl
	ex	de,hl
	ld	hl,LcdWidth
	sbc	hl,de
	ld	(ShiftLineOff),hl
	ld	hl,_YMax
	sub	a,(hl)
	ld	hl,_YMin
	ld	e,(hl)
	add	a,e
	jr	_Shift

;-------------------------------------------------------------------------------
gfx_ShiftRight:
; Shifts whatever is in the clip right by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	db	$F6			; magic byte

;-------------------------------------------------------------------------------
gfx_ShiftDown:
; Shifts whatever is in the clip down by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	scf
	ld	a,$B8
	call	_ShiftCalculate
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
	ld	(ShiftAmountOffset),hl
	or	a,a
	jr	z,.next
	sbc	hl,hl
.next:
	ld	bc,(_XMax)
	add	hl,bc
	dec	bc
	ld	e,a
	ld	a,(_YMin)
	add	a,e
	ld	de,(_XMin)
	sbc	hl,de
	ld	(ShiftCopyAmount),hl
	ld	de,0 - LcdWidth
	add	hl,de
	ld	(ShiftLineOff),hl
	ld	hl,_YMax
	ld	e,(hl)
	sub	a,e
	dec	e

_Shift:
	ld	d,LcdWidth/2
	mlt	de
	ld	hl,(CurrentBuffer)
	add	hl,de
	add	hl,de
	add	hl,bc
	call	gfx_Wait
ShiftCopyAmount :=$+1
.loop:
	ld	bc,0
	ex	de,hl
ShiftAmountOffset :=$+1
	ld	hl,0
	add	hl,de
ShiftCopyDirection :=$+1
	ldir
ShiftLineOff :=$+1
	ld	hl,0
	add	hl,de
	inc	a
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
gfx_GetClipRegion:
; Arguments:
;  Pointer to struct
; Returns:
;  False if offscreen
	ld	hl,3
	add	hl,sp
	ld	iy,(hl)
	dec	iy
	dec	iy
	dec	iy
	call	_ClipRegion		; get the clipping region
	sbc	a,a			; return false if offscreen (0)
	inc	a
	ret

;-------------------------------------------------------------------------------
gfx_ScaledSprite_NoClip:
; Draws a scaled sprite to the screen
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg5 : Width Scale (integer)
;  arg6 : Height Scale (integer)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	push	ix
	ld	h,LcdWidth/2
	ld	l,(iy+15)		; height of scale
	ld	a,l
	ld	(NcSprHscl+1),a
	mlt	hl
	add	hl,hl
	ld	(NcSprHscl320+1),hl
	ld	de,(iy+6)		; x coordinate
	ld	c,(iy+9)		; y coordinate
	ld	a,(iy+12)		; width of scale
	ld	h,a
	ld	ixl,a
	ld	iy,(iy+3)		; start of sprite structure
	ld	l,(iy+0)
	ld	a,l
	ld	(NcSprWidth+1),a
	mlt	hl
	ld	(SprWxSclW1+1),hl
	ld	(SprWxSclW2+1),hl
	ld	a,(iy+1)
	ld	ixh,a			; height of sprite
	ld	hl,(CurrentBuffer)
	add	hl,de
	inc	hl
	ld	b,LcdWidth/2
	mlt	bc
	add	hl,bc
	call	gfx_Wait
NcSprBigLoop:
	add	hl,bc
	ex	de,hl
	sbc	hl,hl
	ld	b,l
	add	hl,de
	dec	hl
	push	de
NcSprWidth:
	ld	a,0			; width of sprite
	jr	NcSprLpEntry
NcSprWlp:
	ldir
NcSprLpEntry:
	ld	c,(iy+2)
	inc	iy
	ld	(hl),c
	ld	c,ixl			; width of scale
	dec	a
	jr	nz,NcSprWlp
	dec	c
	jr	z,NcSprHscl
	ldir
NcSprHscl:
	ld	a,0			; height of scale
	dec	a
	jr	z,NcSprW_end
	inc	b
	ld	c,$40			; bc = LcdWidth
NcSprLineCopy:
	add	hl,bc
	dec	de
	ex	de,hl
SprWxSclW1:
	ld	bc,0			; widthSprite x widthScale
	lddr
	dec	a
	jr	z,NcSprW_end
	ld	bc,641
	add	hl,bc
	inc	de
	ex	de,hl
SprWxSclW2:
	ld	bc,0			; widthSprite x widthScale
	ldir
	ld	bc,639
	dec	a
	jr	nz,NcSprLineCopy
NcSprW_end:
	pop	hl
NcSprHscl320:
	ld	bc,0			; LcdWidth x heightScale
	dec	ixh
	jr	nz,NcSprBigLoop
	pop	ix			; restore ix sp
	ret

;-------------------------------------------------------------------------------
gfx_ScaledTransparentSprite_NoClip:
; Draws a scaled sprite to the screen with transparency
; Arguments:
;  arg0 : Pointer to sprite structure
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg5 : Width Scale (integer)
;  arg6 : Height Scale (integer)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)		; hl = x coordinate
	ld	c,(iy+9)		; c = y coordniate
	ld	de,(CurrentBuffer)
	add	hl,de
	ld	b,LcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl			; de -> start draw location
	ld	hl,LcdWidth
	ld	a,(iy+15)
	ld	(.heightscale),a
	ld	a,(iy+12)
	ld	(.widthscale),a		; smc faster inner loop
	ld	iy,(iy+3)		; iy -> start of sprite struct
	ld	c,(iy+0)		; c = width
	ld	b,a
	ld	a,c
	mlt	bc
	sbc	hl,bc			; find x offset next
	ld	(.amount),hl
	ld	(.width),a
	ld	a,(iy+1)
	lea	hl,iy+2			; hl -> sprite data
	push	ix			; save ix sp
	ld	ixh,a			; ixh = height
	call	gfx_Wait
.loop:
	ld	ixl,0			; ixl = height scale
.heightscale := $-1
.loopheight:
	push	hl
	ld	c,0
.width := $-1
.loopwidth:
	ld	b,0
.widthscale := $-1
	ld	a,(hl)			; get sprite pixel
	cp	a,TRASPARENT_COLOR
smcByte _TransparentColor
	jr	nz,.next		; is transparent?
.skip:
	inc	de
	djnz	.skip
	jr	.locate			; loop for next pixel
.next:
	ld	(de),a
	inc	de
	djnz	.next			; set and loop for next pixel
.locate:
	inc	hl
	dec	c
	jr	nz,.loopwidth		; loop for width
	ex	de,hl
	ld	iy,0
	add	iy,de			; save hl
	ld	bc,0
.amount := $-3
	add	hl,bc			; get next draw location
	ex	de,hl
	pop	hl
	dec	ixl			; loop height scale
	jr	nz,.loopheight
	lea	hl,iy			; restore hl
	dec	ixh			; loop height
	jr	nz,.loop
	pop	ix			; restore ix sp
	ret

;-------------------------------------------------------------------------------
gfx_TransparentSprite:
; Draws a transparent sprite with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	push	ix			; save ix sp
	call	_ClipCoordinates
	pop	ix			; restore ix sp
	ret	nc
	ld	(.amount),a
	ld	a,(iy+0)		; _TmpWidth
	ld	(.next),a
	ld	a,(iy+3)		; tmpHeight
	ld	h,LcdWidth/2
	mlt	hl
	ld	bc,0			; zero ubc
	add	hl,hl
	add	hl,de
	ld	de,(CurrentBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+6)		; hl -> sprite data
	pop	iy
	push	ix
	ld	ixh,a
	ld	a,TRASPARENT_COLOR
smcByte _TransparentColor
	wait_quick
.loop:
	ld	c,0
.next := $-1
	lea	de,iy
	call	_TransparentPlot	; call the transparent routine
	ld	c,0
.amount := $-1
	add	hl,bc
	ld	de,LcdWidth		; move to next row
	add	iy,de
	dec	ixh
	jr	nz,.loop
	pop	ix
	ret

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
gfx_Sprite:
; Places an sprite on the screen as fast as possible with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Width -- 8bits
;  arg4 : Height -- 8bits
; Returns:
;  None
	push	ix			; save ix sp
	call	_ClipCoordinates
	pop	ix			; restore ix sp
	ret	nc
	ld	(.amount),a
	ld	a,(iy+0)		; a = _TmpWidth
	ld	(.next),a
	ld	a,(iy+3)		; a = tmpHeight
	ld	h,LcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de
	ld	de,(CurrentBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+6)		; hl -> sprite data
	pop	iy
	ld	bc,0
	wait_quick
.loop:
	ld	c,0
.next := $-1
	lea	de,iy
	ldir
	ld	de,LcdWidth
	add	iy,de
	ld	c,0
.amount := $-1
	add	hl,bc			; move to next line
	dec	a
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
gfx_Sprite_NoClip:
; Places an sprite on the screen as fast as possible
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(CurrentBuffer)
	ld	bc,(iy+6)		;  x coordinate
	add	hl,bc
	ld	d,LcdWidth/2
	ld	e,(iy+9)		;  y coordinate
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl			; de = start draw location
	ld	hl,(iy+3)		; hl = sprite structure
	ld	c,(hl)			; spriteWidth
	inc	hl
	ld	iyh,c
	xor	a,a
	ld	b,a
	srl	c
	sbc	a,.step - .evenw
	ld	(.step - 1),a
	ld	a,LcdWidth/2
	sub	a,c
	ld	iyl,a			; (LcdWidth/2)-(spriteWidth/2)
	ld	a,(hl)			; spriteHeight
	inc	hl
	wait_quick
	jr	.start
.loop:
	dec	de			; needed if sprite width is odd
.evenw:
	ld	c,iyl			; (LcdWidth/2)-(spriteWidth/2)
	ex	de,hl
	add	hl,bc
	add	hl,bc
	ex	de,hl
.start:
	ld	c,iyh			; spriteWidth
	ldir
	dec	a
	jr	nz,.loop
.step:
	ret

;-------------------------------------------------------------------------------
gfx_GetSprite:
; Grabs the data from the current draw buffer and stores it in another buffer
; Arguments:
;  arg0 : Pointer to storage buffer
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  Pointer to resultant sprite
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)		; bc = y coordinate
	bit	0,b			; check if negative y
	ld	b,LcdWidth/2
	mlt	bc
	ld	hl,(CurrentBuffer)
	add	hl,bc
	add	hl,bc			; hl -> place to begin drawing
	jr	z,.next
	ld	de,(-LcdWidth)*256
	add	hl,de			; fix if negative
.next:
	ld	de,(iy+6)
	add	hl,de
	ld	de,(iy+3)
	push	de
	ld	a,(de)
	inc	de
	ld	(.amount),a		; amount to copy per line
	ld	c,a
	ld	a,LcdWidth and $ff
	sub	a,c
	ld	c,a
	sbc	a,a
	inc	a
	ld	b,a			; the amount to add to get to the next line
	ld	(.offset),bc
	ld	a,(de)
	inc	de
.loop:
	ld	bc,0
.amount := $-3
	ldir				; copy the data into the struct data
	ld	bc,0
.offset := $-3
	add	hl,bc
	dec	a
	jr	nz,.loop
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfx_TransparentSprite_NoClip:
; Draws a transparent sprite to the current buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)		; hl = x coordinate
	ld	c,(iy+9)		; c = y coordinate
	ld	iy,(iy+3)		; iy -> sprite struct
	ld	de,(CurrentBuffer)
	add	hl,de
	ld	b,LcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc			; hl -> place to draw
	push	hl
	ld	a,(iy+0)
	ld	(.next),a
	ld	a,(iy+1)
	lea	hl,iy+2
	pop	iy
	push	ix
	ld	ixh,a			; ixh = height of sprite
	ld	b,0			; zero mid byte
	ld	a,TRASPARENT_COLOR
smcByte _TransparentColor
	wait_quick
.loop:
	ld	c,0
.next := $-1
	lea	de,iy
	call	_TransparentPlot	; call the plotter
	ld	de,LcdWidth
	add	iy,de
	dec	ixh			; loop for height
	jr	nz,.loop
	pop	ix			; restore stack pointer
	ret

;-------------------------------------------------------------------------------
_ClipCoordinates:
; Clipping stuff
; Arguments:
;  arg0 : Pointer to sprite structure
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  A  : How much to add to the sprite per iteration
;  L  : New Y coordinate
;  DE : New X coordinate
;  NC : If offscreen
	ld	ix,6			; get pointer to arguments
	lea	iy,ix-6
	add	ix,sp
	ld	hl,(ix+3)
	ld	a,(hl)
	ld	de,_TmpWidth
	ld	(de),a			; save _TmpWidth
	ld	(.width),a		; save tmpSpriteWidth
	add	iy,de
	inc	hl
	ld	a,(hl)
	ld	(iy+3),a		; save tmpHeight
	inc	hl
	ld	(iy+6),hl		; save a ptr to the sprite data to change offsets
	ld	bc,(ix+9)
	ld	hl,(_YMin)
	mIsHLLessThanBC
	jr	c,.notop
	ld	hl,(iy+3)
	add	hl,bc
	ex	de,hl
	ld	hl,(_YMin)
	mIsHLLessThanDE
	ret	nc			; bc = y location
	ld	hl,(_YMin)		; ymin
	or	a,a
	sbc	hl,bc
	ld	a,(iy+3)
	sub	a,l
	ld	(iy+3),a
	ld	h,(iy+0)		; h = _TmpWidth
	mlt	hl			; hl = amount of lines clipped off
	ld	de,(iy+6)		; de -> sprite data
	add	hl,de
	ld	(iy+6),hl		; store new ptr
	ld	bc,(_YMin)		; new y location ymin
.notop:
	push	bc
	pop	hl			; hl = y coordinate
	ld	de,(_YMax)
	mIsHLLessThanDE
	ret	nc			; return if offscreen on bottom
					; bc = y coordinate
	ld	hl,(iy+3)		; hl = tmpHeight
	add	hl,bc
	ld	de,(_YMax)
	mIsHLLessThanDE
	jr	c,.notbottom		; is partially clipped bottom?
	ex	de,hl			; hl = ymax
					; bc = y coordinate
	sbc	hl,bc
	ld	(iy+3),hl		; store new tmpHeight
.notbottom:
	ld	hl,(ix+6)		; hl = x coordinate
	ld	de,(_XMin)
	mIsHLLessThanDE
	ld	hl,(ix+6)		; hl = x coordinate
	jr	nc,.noleft		; is partially clipped left?
	ld	de,(iy+0)		; de = _TmpWidth
	add	hl,de
	ld	de,(_XMin)
	ex	de,hl
	mIsHLLessThanDE
	ret	nc			; return if offscreen
	ld	de,(ix+6)		; de = x coordinate
	ld	hl,(_XMin)
	or	a,a
	sbc	hl,de
	ex	de,hl			; calculate new offset
	ld	hl,(iy+6)		; hl -> sprite data
	add	hl,de
	ld	(iy+6),hl		; save new ptr
	ld	hl,(iy+0)		; hl = _TmpWidth
	or	a,a
	sbc	hl,de
	ld	(iy+0),hl		; save new width
	ld	hl,(_XMin)
	ld	(ix+6),hl		; save min x coordinate
.noleft:
	ld	de,(_XMax)		; de = xmax
	mIsHLLessThanDE
	ret	nc			; return if offscreen
	ld	hl,(ix+6)		; hl = x coordinate
	ld	de,(iy+0)		; de = _TmpWidth
	add	hl,de
	ld	de,(_XMax)
	ex	de,hl
	mIsHLLessThanDE
	jr	nc,.noright		; is partially clipped right?
	ld	hl,(_XMax)		; clip on the right
	ld	de,(ix+6)
	ccf
	sbc	hl,de
	ld	(iy+0),hl		; save new _TmpWidth
.noright:
	ld	a,(iy+3)
	or	a,a
	ret	z			; quit if new tmpHeight is 0 (edge case)
	ld	a,0
.width := $-1
	ld	de,(ix+6)		; de = x coordinate
	ld	l,c			; l = y coordinate
	sub	a,(iy+0)		; compute new x width
	scf				; set carry for success
	ret

;-------------------------------------------------------------------------------
gfx_TransparentTilemap_NoClip:
; Tilemapping subsection
	ld	hl,gfx_TransparentSprite_NoClip
;	jr	_Tilemap		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfx_Tilemap_NoClip:
; Tilemapping subsection
	ld	hl,gfx_Sprite_NoClip
;	jr	_Tilemap		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfx_TransparentTilemap:
; Tilemapping subsection
	ld	hl,gfx_TransparentSprite
;	jr	_Tilemap		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfx_Tilemap:
; Draws a tilemap given a tile map structure and some offsets
; Arguments:
;  arg0 : Tilemap Struct
;  arg1 : X Pixel Offset (Unsigned)
;  arg2 : Y Pixel Offset (Unsigned)
; Returns:
;  None
; C Function:
;  void DrawBGTilemap(gfx_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset) {
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
;              gfx_Sprite(tilemap->tiles[tilemap->map[x+y_next]], x_draw, y_draw, tilemap->tile_width, tilemap->tile_height);
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

	ld	hl,gfx_Sprite
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
	call	__idvrmu
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
	call	__idvrmu
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
	jp	.yloop

.xres := $+3
.loop:
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
	jp	nz,.loop
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_TilePtr:
; Returns a pointer to a tile given the pixel offsets
; Arguments:
;  arg0 : Tilemap Struct
;  arg1 : X Pixel Offset (Unsigned)
;  arg2 : Y Pixel Offset (Unsigned)
; Returns:
;  A pointer to an indexed tile in the tilemap (so it can be looked at or changed)
; C Function:
;  uint8_t *gfx_TilePtr(gfx_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset) {
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
	call	__idvrmu
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
	call	__idvrmu
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
gfx_TilePtrMapped:
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
gfx_GetTextX:
; Gets the X position of the text cursor
; Arguments:
;  None
; Returns:
;  X Text cursor posistion
	ld	hl,(_TextXPos)		; return x pos
	ret

;-------------------------------------------------------------------------------
gfx_GetTextY:
; Gets the Y position of the text cursor
; Arguments:
;  None
; Returns:
;  Y Text cursor posistion
	ld	hl,(_TextYPos)		; return y pos
	ret

;-------------------------------------------------------------------------------
gfx_SetTextXY:
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
_indcallHL:
; Calls HL
; Inputs:
;  HL : Address to call
	jp	(hl)

;-------------------------------------------------------------------------------
gfx_SetTextBGColor:
; Sets the background text color for text routines
; Arguments:
;  arg0 : Color index to set BG to
; Returns:
;  Previous text color palette index
	setSmcBytes _TextBGColor

;-------------------------------------------------------------------------------
gfx_SetTextFGColor:
; Sets the foreground text color for text routines
; Arguments:
;  arg0 : Color index to set FG to
; Returns:
;  Previous text color palette index
	setSmcBytes _TextFGColor

;-------------------------------------------------------------------------------
gfx_SetTextTransparentColor:
; Sets the transparency text color for text routines
; Arguments:
;  arg0 : Color index to set transparent text to
; Returns:
;  Previous text color palette index
	setSmcBytes _TextTPColor

;-------------------------------------------------------------------------------
gfx_SetFontHeight:
; Sets the height of the font in pixels
; Arguments:
;  arg0 : New font height
; Returns:
;  Previous font height
	setSmcBytes _TextHeight

;-------------------------------------------------------------------------------
gfx_PrintStringXY:
; Places a string at the given coordinates
; Arguments:
;  arg0 : Pointer to string
;  arg1 : Text X Pos
;  arg2 : Text Y Pos
; Returns:
;  None
	pop	iy			; iy = return vector
	pop	bc			; bc = str
	call	gfx_SetTextXY
	push	bc
	ex	(sp),hl			; hl = str
	push	iy
;	jr	_DrawCharacters		; emulated by dummifying next instructions:
	db	$01			; pop de \ ex (sp),hl \ push de -> ld bc,*

;-------------------------------------------------------------------------------
gfx_PrintString:
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
gfx_SetTextScale:
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
gfx_SetTextConfig:
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
	jr	z,.writesmc		; z ==> config == gfx_text_clip
; config == gfx_text_noclip
	ld	hl,_PrintChar
.writesmc:				; hl = PrintChar routine
	ld	(PrintChar_0),hl
	ld	(PrintChar_1),hl
	ld	(PrintChar_2),hl
	ret

;-------------------------------------------------------------------------------
gfx_PrintChar:
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
	sbc	hl,hl
	ld	l,a
	ld	ixh,a			; ixh = char width
	ld	a,(_TextWidthScale)
	ld	h,a
	mlt	hl
	add	hl,bc
	ld	(_TextXPos),hl
	ld	hl,0
_TextYPos := $-3
	ld	h,LcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,bc
	ld	bc,(CurrentBuffer)
	add	hl,bc
	ex	de,hl			; de = draw location
	ld	a,l			; l = character
	sbc	hl,hl
	ld	l,a			; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(_TextData)		; get text data array
	add	hl,bc
	ld	iy,0
	ld	ixl,8
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
smcByte _TextTPColor
	jr	z,.transparent
	ld	(de),a
.transparent:
	inc	de			; move to next pixel
	djnz	.nextpixel
	ld	de,LcdWidth
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
	ld	b,1
_TextHeightScale := $-1
	push	hl
	ld	c,(hl)			; c = 8 pixels
.hscale:
	push	bc
	add	iy,de			; get draw location
	lea	de,iy
	ld	b,ixh
.inner:
	ld	a,TEXT_BG_COLOR
smcByte _TextBGColor
	ld	l,1
_TextWidthScale := $-1
	rlc	c
	jr	nc,.bgcolor
	ld	a,TEXT_FG_COLOR
smcByte _TextFGColor
.bgcolor:
	cp	a,TEXT_TP_COLOR		; check if transparent
smcByte _TextTPColor
	jr	z,.fgcolor

.wscale0:
	ld	(de),a
	inc	de
	dec	l
	jr	nz,.wscale0
	djnz	.inner
	jr	.done

.fgcolor:
.wscale1:
	inc	de
	dec	l
	jr	nz,.wscale1		; move to next pixel
	djnz	.inner
.done:
	ld	de,LcdWidth

	pop	bc
	djnz	.hscale

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
	ld	iyl,8
smcByte _TextHeight
	ld	iyh,a			; ixh = char width
	ld	(_TmpCharSprite),a	; store width of character we are drawing
	call	_GetChar		; store the character data
	ld	bc,(_TextYPos)
	push	bc
	ld	bc,(_TextXPos)		; compute the new locations
	push	bc
	or	a,a
	sbc	hl,hl
	ld	a,iyh
	ld	l,a
	add	hl,bc
	ld	(_TextXPos),hl		; move the text x posisition by the character width
	ld	bc,_TmpCharSprite
	push	bc
	call	gfx_TransparentSprite	; use the actual routine
	pop	bc
	pop	bc
	pop	bc

	pop	hl			; restore hl and stack pointer
	ret

;-------------------------------------------------------------------------------
gfx_PrintInt:
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
	db	$3E			; xor a,a -> ld a,*

;-------------------------------------------------------------------------------
gfx_PrintUInt:
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
gfx_GetStringWidth:
; Gets the width of a string
; Arguments:
;  arg0 : Pointer to string
; Returns:
;  Width of string in pixels
	pop	de
	pop	hl
	push	hl			; hl -> string
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
gfx_GetCharWidth:
; Gets the width of a character
; Arguments:
;  arg0 : Character
; Returns:
;  Width of character in pixels
	ld	iy,0
	lea	de,iy
	add	iy,sp
	ld	a,(iy+3)		; a = character
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
gfx_GetSpriteChar:
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
	ld	a,8
smcByte _TextHeight
	ld	iyh,a			; ixh = char width
	ld	(hl),a			; store width of character we are drawing
	inc	hl
	ld	iyl,a			; height of char
	inc	hl
	ex	de,hl
	call	_GetChar		; read the character into the array
	pop	hl
	ret

;-------------------------------------------------------------------------------
_GetChar:
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
smcByte _TransparentColor
	ld	(de),a
	inc	de			; move to next pixel
	djnz	.nextpixel
	inc	hl
	dec	iyl
	jr	nz,.loop		; okay we stored the character sprite now draw it
	ret

;-------------------------------------------------------------------------------
gfx_SetFontData:
; Sets the font to be custom
; Arguments:
;  arg0 : Pointer to font data
;  Set Pointer to NULL to use default font
; Returns:
;  Pointer to previous font data
	pop	de
	pop	hl
	push	hl			; hl -> custom font data
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
gfx_SetCharData:
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
gfx_SetFontSpacing:
; Sets the font to be custom spacing
; Arguments:
;  arg0 : Pointer to font spacing
;  Set Pointer to NULL to use default font spacing
; Returns:
;  None
	pop	de
	pop	hl
	push	hl			; hl -> custom font width
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
gfx_SetMonospaceFont:
; Sets the font to be monospace
; Arguments:
;  arg0 : Monospace spacing amount
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,e			; a = width
	ld	(_TextFixedWidth),a	; store the value of the monospace width
	ret

;-------------------------------------------------------------------------------
gfx_FillTriangle_NoClip:
; Draws a filled triangle without clipping
; Arguments:
;  arg0-5 : x0,y0,x1,y1,x2,y2
; Returns:
;  None
	ld	hl,gfx_HorizLine_NoClip
;	jr	_FillTriangle		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfx_FillTriangle:
; Draws a filled triangle with clipping
; Arguments:
;  arg0-5 : x0,y0,x1,y1,x2,y2
; Returns:
;  None
	ld	hl,gfx_HorizLine
_FillTriangle:
	ld	(.line0),hl
	ld	(.line1),hl
	ld	(.line2),hl
	push	ix
	ld	ix,0
	add	ix,sp
	lea	hl,ix-39
	ld	sp,hl
	sbc	hl,hl
	ld	(ix-15),hl
	ld	(ix-18),hl		; int sa = 0, sb = 0;
	ld	hl,(ix+9)		; sort coordinates by y order (y2 >= y1 >= y0)
	ld	de,(ix+15)		; if (y0 > y1)
	call	_SignedCompare
	jr	c,.cmp0
	ld	hl,(ix+9)
	ld	(ix+9),de
	ld	(ix+15),hl
	ld	hl,(ix+6)
	ld	de,(ix+12)
	ld	(ix+6),de
	ld	(ix+12),hl
.cmp0:
	ld	hl,(ix+15)
	ld	de,(ix+21)
	call	_SignedCompare
	jr	c,.cmp1
	ld	hl,(ix+15)
	ld	(ix+15),de
	ld	(ix+21),hl
	ld	hl,(ix+12)
	ld	de,(ix+18)
	ld	(ix+12),de
	ld	(ix+18),hl
.cmp1:
	ld	hl,(ix+9)
	ld	de,(ix+15)
	call	_SignedCompare
	jr	c,.cmp2
	ld	hl,(ix+9)
	ld	(ix+9),de
	ld	(ix+15),hl
	ld	hl,(ix+6)
	ld	de,(ix+12)
	ld	(ix+6),de
	ld	(ix+12),hl
.cmp2:
	ld	de,(ix+21)		; if(y0 == y2) - handle awkward all-on-same-line case as its own thing
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	jp	nz,.notflat
	ld	bc,(ix+6)		; x0
	ld	(ix-6),bc		; a = x0
	ld	(ix-3),bc		; b = x0;
	ld	hl,(ix+12)		; if (x1 < a) { a = x1; }
	or	a,a
	sbc	hl,bc
	jp	p,.cmp00
	jp	pe,.cmp01
	jr	.cmp02
.cmp00:
	jp	po,.cmp01
.cmp02:
	ld	bc,(ix+12)
	ld	(ix-3),bc
	jr	.cmp11
.cmp01:
	ld	bc,(ix+12)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc			; else if (x1 > b) { b = x1; }
	jp	p,.cmp10
	jp	pe,.cmp11
	jr	.cmp12
.cmp10:
	jp	po,.cmp11
.cmp12:
	ld	bc,(ix+12)
	ld	(ix-6),bc
.cmp11:
	ld	bc,(ix-3)
	ld	hl,(ix+18)
	or	a,a
	sbc	hl,bc			; if (x2 < a) { a = x2; }
	jp	p,.cmp20
	jp	pe,.cmp21
	jr	.cmp22
.cmp20:
	jp	po,.cmp21
.cmp22:
	ld	bc,(ix+18)
	ld	(ix-3),bc
	jr	.cmp31
.cmp21:
	ld	bc,(ix+18)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc			; else if (x2 > b) { b = x2; }
	jp	p,.cmp30
	jp	pe,.cmp31
	jr	.cmp32
.cmp30:
	jp	po,.cmp31
.cmp32:
	ld	bc,(ix+18)
	ld	(ix-6),bc
.cmp31:
	ld	de,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,de
	inc	hl
	push	hl
	ld	bc,(ix+9)
	push	bc
	push	de
	call	0			; horizline(a, y0, b-a+1);
.line0 := $-3
	pop	bc
	pop	bc
	pop	bc
	ld	sp,ix
	pop	ix
	ret				; return;
.notflat:
	ld	bc,(ix+6)		; x0
	ld	hl,(ix+12)
	or	a,a
	sbc	hl,bc
	ld	(ix-36),hl		; dx01 = x1 - x0;
	ld	hl,(ix+18)
	or	a,a
	sbc	hl,bc
	ld	(ix-21),hl		; dx02 = x2 - x0;
	ld	bc,(ix+9)		; y0
	ld	hl,(ix+15)
	or	a,a
	sbc	hl,bc
	ld	(ix-33),hl		; dy01 = y1 - y0;
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,bc
	ld	(ix-27),hl		; dy02 = y2 - y0;
	ld	bc,(ix+12)
	ld	hl,(ix+18)
	or	a,a
	sbc	hl,bc
	ld	(ix-30),hl		; dx12 = x2 - x1;
	ld	bc,(ix+15)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,bc
	ld	(ix-39),hl		; dy12 = y2 - y1;
	jr	nz,.elselast		; if (y1 == y2) { last = y1; }
	ld	(ix-24),bc
	jr	.sublast
.elselast:
	ld	bc,(ix+15)		; else { last = y1-1; }
	dec	bc
	ld	(ix-24),bc
.sublast:
	ld	bc,(ix+9)
	ld	(ix-12),bc		; for (y = y0; y <= last; y++)
	jp	.firstloopstart
.firstloop:
	ld	hl,(ix-15)
	ld	bc,(ix-33)
	call	_DivideHLBC
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix-3),hl		; a = x0 + sa / dy01;
	ld	hl,(ix-18)
	ld	bc,(ix-27)
	call	_DivideHLBC
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix-6),hl		; b = x0 + sb / dy02;
	ld	bc,(ix-36)
	ld	hl,(ix-15)
	add	hl,bc
	ld	(ix-15),hl		; sa += dx01;
	ld	bc,(ix-21)
	ld	hl,(ix-18)
	add	hl,bc
	ld	(ix-18),hl		; sb += dx02;
	ld	de,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,de			; if (b < a) { swap(a,b); }
	jp	p,.cmp40
	jp	pe,.cmp41
	jr	.cmp42
.cmp40:
	jp	po,.cmp41
.cmp42:
	ld	hl,(ix-3)
	ld	de,(ix-6)
	ld	(ix-3),de
	ld	(ix-6),hl
.cmp41:
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,de
	inc	hl
	push	hl
	ld	bc,(ix-12)
	push	bc
	push	de
	call	0			; horizline(a, y, b-a+1);
.line1 := $-3
	pop	bc
	pop	bc
	pop	bc
	ld	bc,(ix-12)
	inc	bc
	ld	(ix-12),bc
.firstloopstart:
	ld	hl,(ix-24)
	or	a,a
	sbc	hl,bc
	jp	p,.cmp50
	jp	pe,.firstloop
	jr	.cmp52
.cmp50:
	jp	po,.firstloop
.cmp52:
	ld	bc,(ix+15)
	ld	hl,(ix-12)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix-30)
	call	_MultiplyHLBC		; sa = dx12 * (y - y1);
	ld	(ix-15),hl
	ld	bc,(ix+9)
	ld	hl,(ix-12)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix-21)
	call	_MultiplyHLBC		; sb = dx02 * (y - y0);
	ld	(ix-18),hl
	jp	.secondloopstart	; for(; y <= y2; y++)
.secondloop:
	ld	hl,(ix-15)
	ld	bc,(ix-39)
	call	_DivideHLBC
	ld	bc,(ix+12)
	add	hl,bc
	ld	(ix-3),hl		; a = x1 + sa / dy12;
	ld	hl,(ix-18)
	ld	bc,(ix-27)
	call	_DivideHLBC
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix-6),hl		; b = x0 + sb / dy02;
	ld	bc,(ix-30)
	ld	hl,(ix-15)
	add	hl,bc
	ld	(ix-15),hl		; sa += dx12;
	ld	bc,(ix-21)
	ld	hl,(ix-18)
	add	hl,bc
	ld	(ix-18),hl		; sb += dx02;
	ld	de,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,de			; if (b < a) { swap(a,b); }
	jp	p,.cmp60
	jp	pe,.cmp61
	jr	.cmp62
.cmp60:
	jp	po,.cmp61
.cmp62:
	ld	hl,(ix-3)
	ld	de,(ix-6)
	ld	(ix-3),de
	ld	(ix-6),hl
.cmp61:
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,de
	inc	hl
	push	hl
	ld	bc,(ix-12)
	push	bc
	push	de
	call	0			; horizline(a, y, b-a+1);
.line2 := $-3
	pop	bc
	pop	bc
	pop	bc
	ld	bc,(ix-12)
	inc	bc
	ld	(ix-12),bc
.secondloopstart:
	ld	bc,(ix-12)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,bc
	jp	p,.cmp70
	jp	pe,.secondloop
	ld	sp,ix
	pop	ix
	ret
.cmp70:
	jp	po,.secondloop
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_Polygon_NoClip:
; Draws a clipped polygon outline
; Arguments:
;  arg0 : Pointer to polygon points
;  arg1 : length of polygon point array
; Returns:
;  None
	ld	hl,gfx_Line_NoClip
;	jr	_Polygon		; emulated by dummifying next instruction:
	db	$FD			; ld hl,* -> ld iy,*
;-------------------------------------------------------------------------------
gfx_Polygon:
; Draws a clipped polygon outline
; Arguments:
;  arg0 : Pointer to polygon points
;  arg1 : length of polygon point array
; Returns:
;  None
	ld	hl,gfx_Line
_Polygon:
	ld	(.line0),hl
	ld	(.line1),hl
	push	ix
	ld	ix,0
	add	ix,sp
	ld	sp,hl
	ld	iy,(ix+6)
	jr	.startloop
.loop:
	push	iy
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
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	lea	iy,iy+6
.startloop:
	ld	hl,(ix+9)
	dec	hl
	ld	(ix+9),hl
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	nz,.loop
	ld	bc,(iy+3)
	push	bc
	ld	bc,(iy+0)
	push	bc
	ld	iy,(ix+6)
	ld	bc,(iy+3)
	push	bc
	ld	bc,(iy+0)
	push	bc
	call	0
.line1 := $-3
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_Reserved:
; Deprecated unused function (available for use)
	ret

;-------------------------------------------------------------------------------
gfx_Deprecated:
; Decompresses a sprite that is LZ77 compressed from ConvPNG (Deprecated)
	ld	hl,-23
	call	__frameset
	ld	hl,(ix+6)
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex.s	de,hl
	inc	hl
	inc	hl
	ld	(ix-17),hl
	ld	bc,3
	ld	(ix-3),bc
	ld	iy,(ix+6)
	ld	a,(iy+2)
	ld	(ix-8),a
	or	a,a
	sbc	hl,hl
	ld	(ix-6),hl
d_17:	ld	bc,(ix-3)
	ld	hl,(ix+6)
	add	hl,bc
	inc	bc
	ld	(ix-3),bc
	ld	a,(hl)
	ld	(ix-7),a
	cp	a,(ix-8)
	jp	nz,d_16
	ld	bc,(ix-3)
	ld	hl,(ix+6)
	add	hl,bc
	ld	(ix-14),hl
	ld	a,(hl)
	or	a,a
	jr	nz,d_13
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	inc	bc
	ld	(ix-6),bc
	ld	a,(ix-8)
	ld	(hl),a
	ld	bc,(ix-3)
	inc	bc
	ld	(ix-3),bc
	jr	d_18
d_13:	ld	bc,(ix-14)
	push	bc
	pea	ix-20
	call	_LZ_ReadVarSize
	pop	bc
	pop	bc
	ld	bc,(ix-3)
	add	hl,bc
	ld	(ix-3),hl
	ld	bc,(ix+6)
	add	hl,bc
	push	hl
	pea	ix-23
	call	_LZ_ReadVarSize
	pop	bc
	pop	bc
	ld	bc,(ix-3)
	add	hl,bc
	ld	(ix-3),hl
	or	a,a
	sbc	hl,hl
	ld	(ix-11),hl
	jr	d_11
d_9:	ld	bc,(ix-23)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix+9)
	add	hl,bc
	push	hl
	pop	iy
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	inc	bc
	ld	(ix-6),bc
	ld	a,(iy)
	ld	(hl),a
	ld	bc,(ix-11)
	inc	bc
	ld	(ix-11),bc
d_11:	ld	bc,(ix-20)
	ld	hl,(ix-11)
	or	a,a
	sbc	hl,bc
	jr	c,d_9
	jr	d_18
d_16:	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	inc	bc
	ld	(ix-6),bc
	ld	a,(ix-7)
	ld	(hl),a
d_18:	ld	bc,(ix-17)
	ld	hl,(ix-3)
	or	a,a
	sbc	hl,bc
	jp	c,d_17
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_FlipSpriteY:
; Flips an array horizontally about the center vertical axis
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	ld	a,(ix+0)		; a = width of sprite
	sbc	hl,hl
	ld	l,a
	ld	c,a
	push	hl
	ld	(.width),a
	add	hl,hl
	ld	(.delta),hl		; width*2
	ld	a,(ix+1)		; a = height of sprite
	pop	hl
	lea	de,ix+2
	add	hl,de
	ld	ix,(iy+6)
	ld	(ix+1),a		; store height to width
	ld	(ix+0),c		; store width to height
	lea	de,ix+2			; de -> sprite data
	ex	(sp),ix			; restore stack frame
.loop:
	ld	b,0
.width := $-1
	ld	c,a
.pixelloop:
	dec	hl
	ld	a,(hl)
	ld	(de),a			; store the new pixel data
	inc	de
	djnz	.pixelloop
	ld	a,c
	ld	bc,0
.delta := $-3
	add	hl,bc
	dec	a
	jr	nz,.loop
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfx_FlipSpriteX:
; Flip a sprite vertically about the center horizontal axis
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	xor	a,a
	sub	a,(ix+0)
	ld	(.delta),a
	neg
	ld	(.width),a
	ld	l,(ix+1)
	ld	c,l
	dec	l
	ld	h,a
	mlt	hl
	lea	de,ix+2
	add	hl,de
	ld	ix,(iy+6)
	ld	(ix+0),a
	ld	(ix+1),c
	lea	de,ix+2
	push	ix
.loop:
	ld	bc,0
.width := $-3
	ldir
	ld	bc,-1
.delta := $-3
	add	hl,bc
	add	hl,bc
	dec	a
	jr	nz,.loop
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_RotateSpriteC:
; Rotates an array 90 degress clockwise
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
	ld	c,ixl
	ld	b,0
	inc	bc
.outer:
	lea	hl,iy
	dec	iy
	ld	a,ixh
.inner:
	add	hl,bc
	inc	bc
	ldd
	dec	a
	jr	nz,.inner
	dec	ixl
	jr	nz,.outer
	dec	de
	ex	de,hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_RotateSpriteCC:
; Rotates a sprite 90 degrees counter clockwise
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
	dec	e
	ld	c,e
	ex	de,hl
.outer:
	lea	hl,iy+2
	dec	iy
	ld	a,ixh
.inner:
	add	hl,bc
	inc	c
	ldi
	dec	a
	jr	nz,.inner
	dec	ixl
	jr	nz,.outer
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_RotateSpriteHalf:
; Rotates an array 180 degrees
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	c,(hl)			; c = width
	inc	hl
	ld	b,(hl)			; b = height
	ld	iy,(iy+6)
	ld	(iy+0),bc
	mlt	bc
	add	hl,bc
	lea	de,iy
	push	de
.loop:
	inc	de
	inc	de
	ldd
	jp	pe,.loop
	pop	hl
	ret

;-------------------------------------------------------------------------------
gfx_ScaleSprite:
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
	ld	a,(hl)
	ld	ixh,a			; target_width
	ld	(ScaleWidth),a
	inc	hl
	xor	a,a
	sub	a,(hl)
	ld	ixl,a			; -target_height
	inc	hl
	push	hl			; hl->tgt_data
	ld	hl,(iy+3)
	ld	e,(hl)			; src_width
	inc	hl
	ld	c,(hl)			; src_height
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
	ld	a,c			; du = bc:iyl
	ld	(du),a			; ixl = target_height

; b = out_loop_times
; de = target buffer adress
.outer:
	push	hl
ScaleWidth := $+2
	ld	iyh, 0
	xor	a,a
	ld	b,a
	ld	c,0
du := $-1
.loop:	ldi
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
gfx_RotatedScaledSprite_NoClip:
; Rotate and scale an image drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
;  arg2 : Rotation angle as an integer
;  arg3 : Scale factor (64 = 100%)
; Returns:
;  arg1 : Pointer to sprite struct output
	xor	a,a
;	jr	_RotatedScaledSprite	; emulated by dummifying next instruction:
	db	$FE			; ld a,3 -> cp a,$3E \ inc bc

;-------------------------------------------------------------------------------
gfx_RotatedScaledTransparentSprite_NoClip:
; Rotate and scale an image drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
;  arg2 : Rotation angle as an integer
;  arg3 : Scale factor (64 = 100%)
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	a,3

_RotatedScaledSprite:
	ld	(.rotatescale),a
	push	ix
	ld	ix,0
	add	ix,sp
	push	hl
	ld	iy,(ix+6)		; sprite pointer
	lea	hl,iy+2
	ld	(.dsrs_sprptr_0),hl	; write smc

	ld	l,(ix+12)		; y
	ld	h,160
	mlt	hl
	add	hl,hl
	ld	de,(ix+9)		; x
	add	hl,de
	ex	de,hl
	ld	hl,(CurrentBuffer)
	add	hl,de			; offset buffer
	push	hl

	; sinf = _SineTable[angle] * 128 / scale;
	ld	a,(ix+15)		; angle
	call	getSinCos
	ld	l,0
	ld	h,a
	rlca
	rr	h			; hl = _SineTable[angle] * 128
	ld	c,(ix+18)
	ld	b,0
	call	_16Div8Signed		; hl = _SineTable[angle] * 128 / scale (sin)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(.dsrs_sinf_1),hl	; write smc
	push	hl
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	ld	(.dsrs_sinf_0),hl	; write smc
	pop	hl

	; dxs = sinf * -(size * scale / 128);
	ld	c,(ix+18)
	ld	b,(iy)
	mlt	bc			; size * scale
	rl	c
	rl	b
	ld	c,b			; (size * scale / 128)
	xor	a,a
	sub	a,c
	ld	c,a
	sbc	a,a
	ld	b,a			; -(size * scale / 128)
	ld	(ix-3),bc
	call	_16Mul16SignedNeg	; sinf * -(size * scale / 128)
	ld	(.dsrs_dys_0),hl	; write smc
	push	hl

	; cosf = _SineTable[angle + 64] * 128 / scale
	ld	a,64
	add	a,(ix+15)		; angle + 64
	call	getSinCos
	ld	l,0
	ld	h,a
	rlca
	rr	h			; hl = _SineTable[angle + 64] * 128
	ld	c,(ix+18)
	ld	b,0
	call	_16Div8Signed		; hl = _SineTable[angle + 64] * 128 / scale (cos)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(.dsrs_cosf_0),hl	; write smc
	ld	(.dsrs_cosf_1),hl	; write smc

	; dxc = cosf * -(size * scale / 128);
	ld	bc,(ix-3)		; -(size * scale / 128)
	call	_16Mul16SignedNeg	; cosf * -(size * scale / 128)
	ld	(.dsrs_dyc_0),hl	; write smc
	push	hl

	ld	a,(iy)			; size
	ld	(.dsrs_ssize_1),a	; write smc
	dec	a
	ld	(.dsrs_ssize_0),a	; write smc
	inc	a
	ld	b,a
	ld	c,(ix+18)
	mlt	bc			; size * scale
	srl	a			; size / 2
	or	a,a
	sbc	hl,hl
	ld	h,a
	ld	(.dsrs_size128_0),hl	; write smc
	ld	(.dsrs_size128_1),hl	; write smc
	ld	a,b
	rl	c
	adc	a,a
	rl	c
	adc	a,a			; size * scale / 64
	jr	nz,.hax
	inc	a			; hax for scale = 1?
.hax:
	ld	(.dsrs_size_1),a	; write smc

	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	de,LcdWidth
	ex	de,hl
	sbc	hl,de
	ld	(.line_add),hl

	pop	de			; smc = dxc start
	pop	hl			; smc = dxs start
	pop	ix

	push	af
	ld	iyh,a			; size * scale / 64
	call	gfx_Wait
.outer:
	push	hl			; dxs
	push	de			; dxc

	; xs = (dxs + dyc) + (size * 128);
	ld	bc,0
.dsrs_dyc_0 := $-3
	add	hl,bc
	ld	bc,0
.dsrs_size128_0 := $-3
	add	hl,bc
	ex	de,hl			; de = (dxs + dyc) + (size * 128)
	; ys = (dxc - dys) + (size * 128);
	ld	bc,0
.dsrs_dys_0 := $-3
	or	a,a
	sbc	hl,bc
	ld	bc,0
.dsrs_size128_1 := $-3
	add	hl,bc			; hl = (dxc - dys) + (size * 128)

.dsrs_size_1 := $+2			; smc = size * scale / 64
	ld	iyl,0
.inner:
	push	hl			; xs

	ld	a,d
	or	a,h
	rlca
	jr	c,.skip
	ld	a,0
.dsrs_ssize_0 := $-1
	cp	a,d
	jr	c,.skip
	cp	a,h
	jr	c,.skip

	; get pixel and draw to buffer
	ld	c,0
.dsrs_ssize_1 := $-1
	ld	b,h
	mlt	bc
	sbc	hl,hl
	ld	l,d
	add	hl,bc			; y * size + x
	ld	bc,0
.dsrs_sprptr_0 := $-3
	add	hl,bc
	ld	a,(hl)
	cp	a,TRASPARENT_COLOR
smcByte _TransparentColor
	jr	z,$+5
.rotatescale := $-1
	ld	(ix),a			; write pixel
.skip:
	inc	ix			; x++s
	ld	hl,0			; smc = cosf
.dsrs_cosf_0 := $-3
	add	hl,de			; xs += cosf
	ex	de,hl
	pop	hl			; ys
	ld	bc,0			; smc = -sinf
.dsrs_sinf_0 := $-3
	add	hl,bc			; ys += -sinf
	dec	iyl
	jr	nz,.inner		; x loop

	pop	hl			; dxc
	ld	bc,0			; smc = cosf
.dsrs_cosf_1 := $-3
	add	hl,bc			; dxc += cosf
	ex	de,hl
	pop	hl			; dxs
	ld	bc,0			; smc = sinf
.dsrs_sinf_1 := $-3
	add	hl,bc			; dxs += sinf

	ld	bc,0
.line_add := $-3
	add	ix,bc			; y++

	dec	iyh
	jp	nz,.outer		; y loop
	pop	af			; sprite out ptr
	pop	de
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_RotateScaleSprite:
; Rotate and scale an image using an output buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
;  arg2 : Rotation angle as an integer
;  arg3 : Scale factor (64 = 100%)
; Returns:
;  arg1 : Pointer to sprite struct output
	push	ix
	ld	ix,0
	add	ix,sp
	push	hl
	ld	iy,(ix+6)		; sprite pointer
	lea	hl,iy+2
	ld	(_smc_dsrs_sprptr_0 + 1),hl ; write smc

	; sinf = _SineTable[angle] * 128 / scale;
	ld	a,(ix+12)		; angle
	call	getSinCos
	ld	l,0
	ld	h,a
	rlca
	rr	h			; hl = _SineTable[angle] * 128
	ld	c,(ix+15)
	ld	b,0
	call	_16Div8Signed		; hl = _SineTable[angle] * 128 / scale (sin)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(_smc_dsrs_sinf_1 + 1),hl ; write smc
	push	hl
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	ld	(_smc_dsrs_sinf_0 + 1),hl ; write smc
	pop	hl

	; dxs = sinf * -(size * scale / 128);
	ld	c,(ix+15)
	ld	b,(iy)
	mlt	bc			; size * scale
	rl	c
	rl	b
	ld	c,b			; (size * scale / 128)
	xor	a,a
	sub	a,c
	ld	c,a
	sbc	a,a
	ld	b,a			; -(size * scale / 128)
	ld	(ix-3),bc
	call	_16Mul16SignedNeg	; sinf * -(size * scale / 128)
	ld	(_smc_dsrs_dys_0 + 1),hl ; write smc
	push	hl

	; cosf = _SineTable[angle + 64] * 128 / scale
	ld	a,64
	add	a,(ix+12)		; angle + 64
	call	getSinCos
	ld	l,0
	ld	h,a
	rlca
	rr	h			; hl = _SineTable[angle + 64] * 128
	ld	c,(ix+15)
	ld	b,0
	call	_16Div8Signed		; hl = _SineTable[angle + 64] * 128 / scale (cos)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(_smcdsrs_cosf_0 + 1),hl ; write smc
	ld	(_smc_dsrs_cosf_1 + 1),hl ; write smc

	; dxc = cosf * -(size * scale / 128);
	ld	bc,(ix-3)		; -(size * scale / 128)
	call	_16Mul16SignedNeg	; cosf * -(size * scale / 128)
	ld	(_smcdsrs_dyc_0 + 1),hl ; write smc
	push	hl

	ld	a,(iy)			; size
	ld	(_smcdsrs_ssize_1 + 1),a ; write smc
	dec	a
	ld	(_smcdsrs_ssize_0 + 1),a ; write smc
	inc	a
	ld	b,a
	ld	c,(ix+15)
	mlt	bc			; size * scale
	srl	a			; size / 2
	or	a,a
	sbc	hl,hl
	ld	h,a
	ld	(_smc_dsrs_size128_0 + 1),hl ; write smc
	ld	(_smc_dsrs_size128_1 + 1),hl ; write smc
	ld	a,b
	rl	c
	adc	a,a
	rl	c
	adc	a,a			; size * scale / 64
	jr	nz,.skip
	inc	a			; hax for scale = 1?
.skip:
	ld	(_smc_dsrs_size_1 + 2),a ; write smc

	pop	de			; smc = dxc start
	pop	hl			; smc = dxs start

	ld	iy,(ix+9)		; sprite storing to
	push	iy
	ld	(iy+0),a
	ld	(iy+1),a
	lea	ix,iy+2

	ld	iyh,a			; size * scale / 64
_yloop:
	push	hl			; dxs
	push	de			; dxc

	; xs = (dxs + dyc) + (size * 128);
_smcdsrs_dyc_0:
	ld	bc,$000000
	add	hl,bc
_smc_dsrs_size128_0:
	ld	bc,$000000
	add	hl,bc
	ex	de,hl			; de = (dxs + dyc) + (size * 128)
	; ys = (dxc - dys) + (size * 128);
_smc_dsrs_dys_0:
	ld	bc,$000000
	or	a,a
	sbc	hl,bc
_smc_dsrs_size128_1:
	ld	bc,$000000
	add	hl,bc			; hl = (dxc - dys) + (size * 128)

_smc_dsrs_size_1:			; smc = size * scale / 64
	ld	iyl,$00
_xloop:
	push	hl			; xs

	ld	a,d
	or	a,h
	rlca
	ld	c,TRASPARENT_COLOR
smcByte _TransparentColor
	jr	c,drawSpriteRotateScale_SkipPixel
_smcdsrs_ssize_0:
	ld	a,0
	cp	a,d
	jr	c,drawSpriteRotateScale_SkipPixel
	cp	a,h
	jr	c,drawSpriteRotateScale_SkipPixel

	; get pixel and draw to buffer
_smcdsrs_ssize_1:
	ld	c,0
	ld	b,h
	mlt	bc
	sbc	hl,hl
	ld	l,d
	add	hl,bc			; y * size + x
_smc_dsrs_sprptr_0:
	ld	bc,0
	add	hl,bc
	ld	c,(hl)
drawSpriteRotateScale_SkipPixel:
	ld	(ix),c			; write pixel
	inc	ix			; x++s
_smcdsrs_cosf_0:			; smc = cosf
	ld	hl,0
	add	hl,de			; xs += cosf
	ex	de,hl
	pop	hl			; ys
_smc_dsrs_sinf_0:			; smc = -sinf
	ld	bc,0
	add	hl,bc			; ys += -sinf
	dec	iyl
	jr	nz,_xloop		; x loop

	pop	hl			; dxc
_smc_dsrs_cosf_1:			; smc = cosf
	ld	bc,0
	add	hl,bc			; dxc += cosf
	ex	de,hl
	pop	hl			; dxs
_smc_dsrs_sinf_1:			; smc = sinf
	ld	bc,0
	add	hl,bc			; dxs += sinf

	dec	iyh
	jp	nz,_yloop		; y loop
	pop	hl			; sprite out ptr
	pop	de
	pop	ix
	ret

getSinCos:
	; returns a = sin/cos(a) * 128
	ld	c,a
	bit	7,a
	jr	z,$+4
	sub	a,128
	bit	6,a
	jr	z,$+6
	ld	e,a
	ld	a,128
	sub	a,e
	ld	de,0
	ld	e,a
	ld	hl,_SineTable
	add	hl,de
	ld	a,(hl)
	bit	7,c
	ret	z
	neg
	ret

_SineTable:
	; sin(x) * 128
	db 0,3,6,9,13,16,19,22,25,28,31,34,37,40,43,46
	db 49,52,55,58,60,63,66,68,71,74,76,79,81,84,86,88
	db 91,93,95,97,99,101,103,105,106,108,110,111,113,114,116,117
	db 118,119,121,122,122,123,124,125,126,126,127,127,127,127,127,127,127

_16Div8Signed:
	ld	a,h
	xor	a,c
	push	af
	bit	7,h
	jr	z,.next0
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
.next0:
	xor	a,a
	sub	a,c
	jp	m,.next1
	ld	c,a
.next1:
	push	hl
	dec	sp
	pop	hl
	inc	sp
	ld	b,16
	xor	a,a
.div:	add	hl,hl
	rla
	cp	a,c
	jr	c,.check
	sub	a,c
	inc	l
.check:
	djnz	.div
	pop	af
	ret	p
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
	ret

_16Mul16SignedNeg:
	ld	d,b
	ld	e,l
	ld	b,h
	ld	h,c
	mlt	bc
	mlt	de
	mlt	hl
	ld	a,h
	add	a,c
	add	a,e
	ld	h,a
	ex	de,hl
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ret

;-------------------------------------------------------------------------------
gfx_FloodFill:
; Implements a flood fill so no one hopefully crashes the stack
; Maximum stack depth is 3224 bytes
; Arguments:
;  arg0 : X Coordinate
;  arg1 : Y Coordinate
;  arg2 : New Color Index
; Returns:
;  None
	ld	hl,-3224
	call	__frameset

	ld	e,(ix+9)
	ld	bc,(ix+6)
	call	_GetPixel		; ov = p(x, y);

	ld	(.oldcolor0),a
	ld	(.oldcolor1),a
	ld	(.oldcolor2),a

	ld	a,(ix+12)
	ld	(.newcolor0),a
	ld	(.newcolor1),a

	ld	hl,(_XMax)		; smc to gain speedz in inner loops
	ld	(.xmax),hl
	ld	hl,(_XMin)
	ld	(.xmin),hl

	lea	iy,ix
	ld	bc,-3224
	add	iy,bc
	ld	(.stack),iy

	ld	a,(ix+9)
	ld	hl,(ix+6)
	ld	(iy+0),hl		; sp->xl = x;
	ld	(iy+3),hl		; sp->xr = x;
	ld	(iy+6),a		; sp->y  = y;
	ld	(iy+7),1		; sp->dy = 1;
	lea	iy,iy+8			; sp++;

	inc	a
	ld	(iy+6),a		; sp->y  = y+1;
	ld	(iy+0),hl		; sp->xl = x;
	ld	(iy+3),hl		; sp->xr = x;
	ld	(iy+7),255		; sp->dy = -1;
	lea	iy,iy+8			; sp++;

	call	gfx_Wait

.dowhileloop:				; do {
	lea	iy,iy-8			; sp--;
	ld	a,(iy+7)
	ld	(ix-4),a		; dy = sp->dy;
	add	a,(iy+6)		; y  = sp->y+dy;
	ld	(ix+9),a
	ld	bc,(iy+3)
	ld	(ix-15),bc		; x2 = sp->xr;
	ld	bc,(iy+0)
	ld	(ix-8),bc		; x1 = sp->xl;

	ld	hl,(CurrentBuffer)
	add	hl,bc
	ld	e,a
	ld	d,LcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,0
.xmin = $-3
	ld	a,0
.oldcolor0 = $-1

	jr	.begin
.forloop0:				; for (x=x1; !(x & 0x8000) && x>=xmin && p(x, y) == ov; x--) { s(x, y); }
	ld	(hl),0
.newcolor0 = $-1
	dec	hl
	dec	bc
.begin:
	bit	7,b
	jr	nz,.nonnegative
	or	a,a
	sbc	hl,de
	jr	c,.nonnegative
	add	hl,de
	cp	a,(hl)
	jr	z,.forloop0

.nonnegative:
	ld	(ix+6),bc
	ld	bc,(ix-8)
	ld	hl,(ix+6)
	bit	7,h
	jr	nz,.check
	or	a,a
	sbc	hl,bc
	jp	nc,.skip		; if (!(x & 0x8000) && (unsigned)x>=x1) goto skip;
	add	hl,bc
.check:
	inc	hl
	ld	(ix-11),hl		; l = x+1;
	or	a,a
	sbc	hl,bc
	jr	nc,.badpush0		; if (l<x1) { push(y, l, x1-1, -dy); }
	lea	de,ix-24
	lea	hl,iy
	or	a,a
	sbc	hl,de
	jr	nc,.badpush0		; check stack limit
	ld	a,(_YMin)
	ld	e,a
	ld	a,(ix-4)
	neg
	add	a,(ix+9)
	cp	a,e
	jr	c,.badpush0
	ld	e,a
	ld	a,(_YMax)
	cp	a,e
	jr	c,.badpush0		; compare y values
	ld	a,(ix+9)
	ld	(iy+6),a
	ld	bc,(ix-11)
	ld	(iy+0),bc
	ld	bc,(ix-8)
	dec	bc
	ld	(iy+3),bc
	ld	a,(ix-4)
	neg
	ld	(iy+7),a
	lea	iy,iy+8
.badpush0:
	ld	bc,(ix-8)
	inc	bc			; x = x1+1;

	ld	hl,(CurrentBuffer)
	add	hl,bc
	ld	e,(ix+9)
	ld	d,LcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl			; de -> draw location
					; do {
.forloop1start:
	ld	hl,0
.xmax = $-3
	jr	.atov			; for (; (unsigned)x<=xmax && p(x, y) == ov; x++) { s(x, y); }
.forloop1:
	ld	a,0
.newcolor1 = $-1
	ld	(de),a
	inc	de
	inc	bc
.atov:
	or	a,a
	sbc	hl,bc
	jr	c,.ovat
	add	hl,bc
	ld	a,(de)
	cp	a,0
.oldcolor1 = $-1
	jr	z,.forloop1

.ovat:
	ld	(ix+6),bc
	lea	de,ix-24		; push(y, l, x-1, dy);
	lea	hl,iy
	or	a,a
	sbc	hl,de
	jr	nc,.badpush1
	ld	a,(_YMin)
	ld	e,a
	ld	a,(ix-4)
	add	a,(ix+9)
	cp	a,e
	jr	c,.badpush1
	ld	e,a
	ld	a,(_YMax)
	cp	a,e
	jr	c,.badpush1		; compare y values
	dec	bc
	ld	(iy+3),bc
	ld	a,(ix+9)
	ld	(iy+6),a
	ld	bc,(ix-11)
	ld	(iy+0),bc
	ld	a,(ix-4)
	ld	(iy+7),a
	lea	iy,iy+8
.badpush1:
	ld	hl,(ix-15)		; if (x>x2+1) { push(y, x2+1, x-1, -dy); }
	ld	bc,(ix+6)
	inc	hl
	or	a,a
	sbc	hl,bc
	jr	nc,.skip
	lea	de,ix-24
	lea	hl,iy
	or	a,a
	sbc	hl,de
	jr	nc,.badpush2
	ld	a,(_YMin)
	ld	e,a
	ld	a,(ix-4)
	neg
	add	a,(ix+9)
	cp	a,e
	jr	c,.badpush2
	ld	e,a
	ld	a,(_YMax)
	cp	a,e
	jr	c,.badpush2		; compare y values
	dec	bc
	ld	(iy+3),bc
	ld	bc,(ix-15)
	inc	bc
	ld	(iy+0),bc
	ld	a,(ix-4)
	neg
	ld	(iy+7),a
	ld	a,(ix+9)
	ld	(iy+6),a
	lea	iy,iy+8
.skip:
.badpush2:				; skip: for (x++; (unsigned)x<=x2 && p(x, y) != ov; x++);
	ld	bc,(ix+6)
	inc	bc

	ld	hl,(CurrentBuffer)
	add	hl,bc
	ld	e,(ix+9)
	ld	d,LcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl			; de -> draw location
	ld	hl,(ix-15)

	jr	.whileloop
.forloop2:
	inc	bc
	inc	de
.whileloop:
	or	a,a
	sbc	hl,bc
	add	hl,bc
	jr	c,.done
	ld	a,(de)
	cp	a,0
.oldcolor2 = $-1
	jr	nz,.forloop2

.done:
	ld	(ix+6),bc
	ld	(ix-11),bc		; l = x;
	or	a,a
	sbc	hl,bc
	jp	nc,.forloop1start	; } while ((unsigned)x<=x2);

	ld	hl,0
.stack = $-3
	lea	de,iy
	or	a,a
	sbc	hl,de
	jp	c,.dowhileloop		; } while (sp>stack);

	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
gfx_RLETSprite:
; Draws a sprite with RLE transparency with clipping.
; Arguments:
;  arg0 : pointer to sprite structure
;  arg1 : x-coordinate
;  arg2 : y-coordinate
; Returns:
;  None
	ld	iy,0
	lea	bc,iy			; bc = 0
	add	iy,sp			; iy = frame
; Clip bottom
	ld	hl,(iy+3)		; hl = sprite struct
	inc	hl
	ld	c,(hl)			; bc = height
	ld	hl,(_YMax)		; hl = ymax
	ld	de,(iy+9)		; de = y
	sbc	hl,de			; hl = ymax-y
	ret	m			; m ==> ymax < y || y ~ int_min ==> fully off-screen
	ret	z			; z ==> ymax == y ==> fully off-screen
	xor	a,a			; a = 0
	sbc	hl,bc			; hl = ymax-y-height = -(height off-screen)
	jr	nc,_RLETSprite_SkipClipBottom ; nc ==> height-off-screen <= 0 ==> fully on-screen
	add	hl,bc			; hl = ymax-y = height on-screen
	ld	c,l			; bc = height on-screen
	or	a,a
_RLETSprite_SkipClipBottom:
; ymax-y did not overflow ==> y-ymin will not overflow
; Clip top
	ld	hl,(_YMin)		; hl = ymin
	ex	de,hl			; de = ymin
					; hl = y
	sbc	hl,de			; hl = y-ymin
	jp	p,_RLETSprite_SkipClipTop ; p ==> y >= ymin ==> fully on-screen
	add	hl,bc			; hl = y-ymin+height = height on-screen
	ret	nc			; nc ==> height on-screen < 0 ==> fully off-screen
	or	a,l			; a = height on-screen
	ret	z			; z ==> height on-screen == 0 ==> fully off-screen
	ld	a,c			; a = height
	sub	a,l			; a = height - height on-screen = height off-screen
	ld	b,a			; b = height off-screen
	ld	c,l			; c = height on-screen
	sbc	hl,hl			; y = ymin (after add hl,de)
_RLETSprite_SkipClipTop:
	ld	(_RLETSprite_Heights_SMC),bc
	add	hl,de			; hl = y (clipped)
	ld	(iy+9),l		; write back clipped y
; de = ymin => d = deu = 0
; Clip left
	ld	hl,(iy+3)		; hl = sprite struct
	ld	e,(hl)			; de = width
	ld	hl,(iy+6)		; hl = x
	ld	bc,(_XMin)		; bc = xmin
	sbc	hl,bc			; hl = x-xmin
	ret	pe			; v ==> x ~ int_min ==> fully off-screen
	jp	p,_RLETSprite_SkipClipLeft ; p ==> x >= xmin ==> fully on-screen
	add	hl,de			; hl = x-xmin+width = width on-screen
	ret	nc			; nc ==> width on-screen < 0 ==> fully off-screen
	ld	a,l			; a = width on-screen
	or	a,a
	ret	z			; z ==> width on-screen == 0 ==> fully off-screen
	ld	a,e			; a = width
	sub	a,l			; a = width - width on-screen = width off-screen
	ld	(_RLETSprite_ClipLeft_Width_SMC),a
	ld	e,l			; e = width on-screen
	inc	d			; d[0] = 1
	sbc	hl,hl			; x = xmin (after add hl,bc)
_RLETSprite_SkipClipLeft:
; x >= xmin ==> x >= 0
; Clip right
	add	hl,bc			; hl = x (clipped)
	ld	(iy+6),hl		; write back clipped x
	ld	bc,(_XMax)		; bc = xmax
	sbc	hl,bc			; hl = x-xmax
	ret	nc			; nc ==> x >= xmax ==> fully off-screen
	ld	a,d			; a[0] = clip left?
	ld	d,0			; de = width
	add	hl,de			; hl = x-xmax+width = width off-screen
	ld	d,a			; d[0] = clip left?
	jr	nc,_RLETSprite_SkipClipRight ; nc ==> width off-screen < 0 ==> fully on-screen
	ld	a,l			; a = width off-screen
	or	a,a
	jr	z,_RLETSprite_SkipClipRight ; z ==> width off-screen == 0 ==> fully on-screen
	ld	(_RLETSprite_ExitRight_Opaque_Width_SMC),a
	ld	(_RLETSprite_ExitRight_Trans_Width_SMC),a
	ld	a,e			; a = width
	sub	a,l			; a = width - width off-screen = width on-screen
	ld	e,a			; e = width on-screen
	set	1,d			; d[1] = 1
_RLETSprite_SkipClipRight:
; Calculate the pointer to the top-left corner of the sprite in the buffer
	ld	hl,(CurrentBuffer)
	ld	bc,(iy+6)		; bc = x (clipped)
	add	hl,bc
	ld	c,(iy+9)		; c = y (clipped)
	ld	b,lcdWidth/2
	mlt	bc			; bc = y*160
	add	hl,bc
	add	hl,bc
; Get the pointer to the start of the sprite data, clipping the top if necessary
	push	hl			; (sp) = top-left corner of sprite in buffer
	push	de			;   (sp) = (x clip bits)<<8|(width on-screen)
	ld	bc,0			; b = height off-screen (top), c = height on-screen
_RLETSprite_Heights_SMC := $-3
	ld	d,c
	push	de			;     (sp) = (height on-screen)<<8|(width on-screen)
	ld	hl,(iy+3)		; hl = sprite struct
	ld	c,(hl)			; c = width
	inc	hl
	inc	hl			; hl = start of sprite data
	xor	a,a			; a = 0
	ld	d,a			; d = deu = 0
	or	a,b			; a = height off-screen
	jr	z,_RLETSprite_ClipTop_End ; z => height off-screen == 0
_RLETSprite_ClipTop_Row:
	ld	a,c			; a = width
_RLETSprite_ClipTop_Trans:
	sub	a,(hl)			; a = width remaining after trans run
	inc	hl
	jr	z,_RLETSprite_ClipTop_RowEnd ; z ==> width remaining == 0
_RLETSprite_ClipTop_Opaque:
	ld	e,(hl)			; de = opaque run length
	inc	hl
	sub	a,e			; a = width remaining after opaque run
	add	hl,de			; skip opaque run
	jr	nz,_RLETSprite_ClipTop_Trans ; nz ==> width remaining != 0
_RLETSprite_ClipTop_RowEnd:
	djnz	_RLETSprite_ClipTop_Row	; decrement height remaining off-screen,
					; nz => still off-screen
_RLETSprite_ClipTop_End:		; a = 0, hl = start of (clipped) sprite data
; Do stuff
	pop	iy			;     iyh = height on-screen, iyl = width on-screen
	pop	bc			;   bcu = 0, b = x clip bits
	pop	de			; de = buffer
	dec	de			; decrement buffer pointer (negate inc)
	or	a,b
	ld	a,iyl			; a = width on-screen
	jp	z,_RLETSprite_NoClip_Begin
	cpl				; a = 255-(width on-screen)
	add	a,lcdWidth-255		; a = (lcdWidth-(width on-screen))&0FFh
	rra				; a = (lcdWidth-(width on-screen))/2
	dec	b
	wait_quick
	jr	z,_RLETSprite_ClipLeftMiddle
	ld	(_RLETSprite_ClipRight_HalfRowDelta_SMC),a
	sbc	a,a
	djnz	_RLETSprite_ClipLeftMiddleClipRight
_RLETSprite_MiddleClipRight:
	s8	sub a,_RLETSprite_ClipRight_LoopJr_SMC+1-_RLETSprite_Middle_Row_WidthEven
	ld	(_RLETSprite_ClipRight_LoopJr_SMC),a
_RLETSprite_Middle_Row_WidthOdd:
	inc	de			; increment buffer pointer
_RLETSprite_Middle_Row_WidthEven:
	ld	a,iyl			; a = width on-screen
	jr	_RLETSprite_Middle_Trans
_RLETSprite_Middle_OpaqueCopy_:
	inc	hl
_RLETSprite_Middle_OpaqueCopy:
	ldir				; copy opaque run
_RLETSprite_Middle_Trans:
	ld	c,(hl)			; bc = trans run length
	sub	a,c			; a = width remaining on-screen after trans run
	ex	de,hl			; de = sprite, hl = buffer
	jr	c,_RLETSprite_ExitRight_Trans ; c ==> width remaining on-screen < 0
	inc	de
_RLETSprite_Middle_TransSkip:
	add	hl,bc			; skip trans run
	ex	de,hl			; de = buffer, hl = sprite
_RLETSprite_Middle_Opaque:
	ld	c,(hl)			; bc = opaque run length
	sub	a,c			; a = width remaining on-screen after opqaue run
	jr	nc,_RLETSprite_Middle_OpaqueCopy_ ; nc ==> width remaining on-screen >= 0
_RLETSprite_ExitRight_Opaque:
	add	a,c			; a = width remaining on-screen before opaque run
	ld	c,a			; bc = width remaining on-screen before opaque run
	ld	a,(hl)			; a = opaque run length
	inc	hl
	jr	z,_RLETSprite_ExitRight_Opaque_SkipCopy ; z ==> width remaining on-screen == 0
	sub	c			; a = opaque run length off-screen
	ldir				; copy on-screen part of opaque run
_RLETSprite_ExitRight_Opaque_SkipCopy:
	ld	c,a			; bc = opaque run length off-screen
	ld	a,0			; a = width off-screen
_RLETSprite_ExitRight_Opaque_Width_SMC := $-1
	jr	_RLETSprite_ClipRight_OpaqueSkip

_RLETSprite_ExitRight_Trans:
	add	a,c			; a = width remaining on-screen before trans run
	ld	c,a			; bc = width remaining on-screen before trans run
	add	hl,bc			; skip on-screen part of trans run
	ex	de,hl			; de = buffer, hl = sprite
	add	a,0			; a = width remaining on-screen before trans run + width off-screen
_RLETSprite_ExitRight_Trans_Width_SMC := $-1
_RLETSprite_ClipRight_Trans:
	sub	a,(hl)			; a = width remaining off-screen after trans run
	inc	hl
	jr	z,_RLETSprite_ClipRight_RowEnd ; z ==> width remaining off-screen == 0
_RLETSprite_ClipRight_Opaque:
	ld	c,(hl)			; bc = opaque run length
	inc	hl
_RLETSprite_ClipRight_OpaqueSkip:
	sub	a,c			; a = width remaining off-screen after opaque run
	add	hl,bc			; skip opaque run
	jr	nz,_RLETSprite_ClipRight_Trans ; nz ==> width remaining off-screen != 0
_RLETSprite_ClipRight_RowEnd:
	ex	de,hl			; de = sprite, hl = buffer
	ld	c,0			; c = (lcdWidth-(width on-screen))/2
_RLETSprite_ClipRight_HalfRowDelta_SMC := $-1
	add	hl,bc			; advance buffer to next row
	add	hl,bc
	ex	de,hl			; de = buffer, hl = sprite
	dec	iyh			; decrement height remaining
	jr	nz,_RLETSprite_Middle_Trans ; nz ==> height remaining != 0
_RLETSprite_ClipRight_LoopJr_SMC := $-1
	ret

_RLETSprite_ClipLeftMiddleClipRight:
	dec	b			; b = 0
	s8	sub a,_RLETSprite_ClipRight_LoopJr_SMC+1-_RLETSprite_ClipLeft_Row_WidthEven
	ld	(_RLETSprite_ClipRight_LoopJr_SMC),a
	s8	ld a,_RLETSprite_Middle_OpaqueCopy-(_RLETSprite_EnterLeft_Opaque_Jr_SMC+1)
	s8	ld c,_RLETSprite_Middle_TransSkip-(_RLETSprite_EnterLeft_Trans_Jr_SMC+1)
	jr	_RLETSprite_ClipLeftMiddle_DoSMC

_RLETSprite_ClipLeftMiddle:
	ld	(_RLETSprite_NoClip_HalfRowDelta_SMC),a
	sbc	a,a
	s8	sub a,_RLETSprite_NoClip_LoopJr_SMC+1-_RLETSprite_ClipLeft_Row_WidthEven
	ld	(_RLETSprite_NoClip_LoopJr_SMC),a
	s8	ld a,_RLETSprite_NoClip_OpaqueCopy-(_RLETSprite_EnterLeft_Opaque_Jr_SMC+1)
	s8	ld c,_RLETSprite_NoClip_TransSkip-(_RLETSprite_EnterLeft_Trans_Jr_SMC+1)
_RLETSprite_ClipLeftMiddle_DoSMC:
	ld	(_RLETSprite_EnterLeft_Opaque_Jr_SMC),a
	ld	a,c
	ld	(_RLETSprite_EnterLeft_Trans_Jr_SMC),a
_RLETSprite_ClipLeft_Row_WidthOdd:
	inc	de			; increment buffer pointer
_RLETSprite_ClipLeft_Row_WidthEven:
	ld	a,0			; a = width off-screen
_RLETSprite_ClipLeft_Width_SMC = $-1
	jr	_RLETSprite_ClipLeft_Trans
_RLETSprite_ClipLeft_OpaqueSkip:
	ld	c,(hl)			; bc = opaque run length
	inc	hl
	add	hl,bc			; skip opaque run
_RLETSprite_ClipLeft_Trans:
	sub	a,(hl)			; a = width remaining off-screen after trans run
	inc	hl
	jr	c,_RLETSprite_EnterLeft_Trans ; c ==> partially on-screen
_RLETSprite_ClipLeft_Opaque:
	ld	c,a			; bc = width remaining off-screen before opaque run
	sub	a,(hl)			; a = width remaining off-screen after opaque run
	jr	nc,_RLETSprite_ClipLeft_OpaqueSkip ; nc ==> still off-screen
_RLETSprite_EnterLeft_Opaque:
	inc	hl
	add	hl,bc			; skip off-screen part of opaque run
	neg				; a = opaque run length on-screen
	ld	c,a			; bc = opaque run length on-screen
	ld	a,iyl			; a = width on-screen
	sub	a,c			; a = width remaining on-screen after opaque run
	jr	_RLETSprite_NoClip_OpaqueCopy
_RLETSprite_EnterLeft_Opaque_Jr_SMC := $-1

_RLETSprite_EnterLeft_Trans:
	neg				; a = trans run length on-screen
	ld	c,a			; bc = trans run length on-screen
	ld	a,iyl			; a = width on-screen
	sub	a,c			; a = width remaining on-screen after trans run
	ex	de,hl			; de = sprite, hl = buffer
	jr	_RLETSprite_NoClip_TransSkip
_RLETSprite_EnterLeft_Trans_Jr_SMC := $-1

;-------------------------------------------------------------------------------
gfx_RLETSprite_NoClip:
; Draws a sprite with RLE transparency without clipping.
; Arguments:
;  arg0 : pointer to sprite structure
;  arg1 : x-coordinate
;  arg2 : y-coordinate
; Returns:
;  None
	ld	iy,0
	add	iy,sp
; Calculate the pointer to the top-left corner of the sprite in the buffer.
	ld	hl,(CurrentBuffer)
	ld	bc,(iy+6)		; bc = x
	add	hl,bc
	ld	c,(iy+9)		; c = y
	ld	b,lcdWidth/2
	mlt	bc			; bc = y*160
	add	hl,bc
	add	hl,bc
	ex	de,hl			; de = top-left corner of sprite in buffer
; Read the sprite width and height.
	ld	hl,(iy+3)		; hl = sprite struct
	ld	iy,(hl)			; iyh = height, iyl = width
	ld	a,(hl)			; a = width
	inc	hl
	inc	hl			; hl = sprite data
; Initialize values for looping.
	ld	b,0			; b = 0
	dec	de			; decrement buffer pointer (negate inc)
_RLETSprite_NoClip_Begin:
; Generate the code to advance the buffer pointer to the start of the next row.
	cpl				; a = 255-width
	add	a,lcdWidth-255		; a = (lcdWidth-width)&0FFh
	rra				; a = (lcdWidth-width)/2
	ld	(_RLETSprite_NoClip_HalfRowDelta_SMC),a
	sbc	a,a
	s8	sub a,_RLETSprite_NoClip_LoopJr_SMC+1-_RLETSprite_NoClip_Row_WidthEven
	ld	(_RLETSprite_NoClip_LoopJr_SMC),a
	wait_quick
; Row loop (if sprite width is odd)
_RLETSprite_NoClip_Row_WidthOdd:
	inc	de			; increment buffer pointer
; Row loop (if sprite width is even) {
_RLETSprite_NoClip_Row_WidthEven:
	ld	a,iyl			; a = width
;; Data loop {
_RLETSprite_NoClip_Trans:
;;; Read the length of a transparent run and skip that many bytes in the buffer.
	ld	c,(hl)			; bc = trans run length
	inc	hl
	sub	a,c			; a = width remaining after trans run
	ex	de,hl			; de = sprite, hl = buffer
_RLETSprite_NoClip_TransSkip:
	add	hl,bc			; skip trans run
;;; Break out of data loop if width remaining == 0.
	jr	z,_RLETSprite_NoClip_RowEnd ; z ==> width remaining == 0
	ex	de,hl			; de = buffer, hl = sprite
_RLETSprite_NoClip_Opaque:
;;; Read the length of an opaque run and copy it to the buffer.
	ld	c,(hl)			; bc = opaque run length
	inc	hl
	sub	a,c			; a = width remaining after opqaue run
_RLETSprite_NoClip_OpaqueCopy:
	ldir				; copy opaque run
;;; Continue data loop while width remaining != 0.
	jr	nz,_RLETSprite_NoClip_Trans ; nz ==> width remaining != 0
	ex	de,hl			; de = sprite, hl = buffer
;; }
_RLETSprite_NoClip_RowEnd:
;; Advance buffer pointer to the next row (minus one if width is odd).
	ld	c,0			; c = (lcdWidth-width)/2
_RLETSprite_NoClip_HalfRowDelta_SMC := $-1
	add	hl,bc			; advance buffer to next row
	add	hl,bc
	ex	de,hl			; de = buffer, hl = sprite
;; Decrement height remaining. Continue row loop while not zero.
	dec	iyh			; decrement height remaining
	jr	nz,_RLETSprite_NoClip_Row_WidthEven ; nz ==> height remaining != 0
_RLETSprite_NoClip_LoopJr_SMC := $-1
; }
; Done.
	ret

;-------------------------------------------------------------------------------
gfx_ConvertFromRLETSprite:
; Converts a sprite with RLE transpareny to a sprite with normal transparency.
; Arguments:
;  arg0 : pointer to gfx_rletsprite_t input
;  arg1 : pointer to gfx_sprite_t output
; Returns:
;  arg1 : pointer to gfx_sprite_t output
	pop	bc
	pop	de			; de = gfx_rletsprite_t *input
	ex	(sp),hl			; hl = gfx_sprite_t *output
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
	ld	a,iyl			; a = width
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
	sub	a,b			; a = width remaining after trans run
	ld	c,0			; c = trans color
smcByte _TransparentColor
	ex	de,hl			; de = input data, hl = output data
_ConvertFromRLETSprite_TransLoop:
	ld	(hl),c			; write trans color to output
	inc	hl
	djnz	_ConvertFromRLETSprite_TransLoop ; decrement trans run length remaining,
						 ; nz ==> trans run length remaining != 0
	ex	de,hl			; de = output data, hl = input data
;;; Break out of data loop if width remaining == 0.
	jr	z,_ConvertFromRLETSprite_RowEnd ; z ==> width remaining == 0
_ConvertFromRLETSprite_Opaque:
;;; Read the length of an opaque run and copy it to the output.
	ld	c,(hl)			; bc = opaque run length
	inc	hl
	sub	a,c			; a = width remaining after opqaue run
	ldir				; copy opaque run
;;; Continue data loop while width remaining != 0.
	jr	nz,_ConvertFromRLETSprite_Trans ; nz ==> width remaining != 0
;; }
_ConvertFromRLETSprite_RowEnd:
;; Decrement height remaining. Continue row loop while not zero.
	dec	iyh			; decrement height remaining
	jr	nz,_ConvertFromRLETSprite_Row ; nz ==> height remaining != 0
; }
; Return output.
	pop	hl			; hl = output
	ret

;-------------------------------------------------------------------------------
gfx_ConvertToNewRLETSprite:
; Converts a sprite with normal transpareny to a sprite with RLE transparency,
; allocating the exact amount of necessary space for the converted sprite.
; Arguments:
;  arg0 : pointer to gfx_sprite_t input
;  arg1 : pointer to malloc
; Returns:
;  arg1 : pointer to gfx_rletsprite_t output
	pop	bc
	pop	de			; de = gfx_sprite_t *input
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
	ld	b,iyl			; b = width
	inc	de			; increment output size for first trans run
;; Transparent loop {
_ConvertToNewRLETSprite_TransLoop:
	inc	hl
	cp	a,(hl)			; compare an input pixel to trans color
	inc	de			; increment output size for potential opaque run
	jr	nz,_ConvertToNewRLETSprite_OpaquePixel ; nz ==> not transparent
	dec	de			; revert output size, not opaque run
_ConvertToNewRLETSprite_TransPixel:
;;; Continue while width remaining != 0.
	djnz	_ConvertToNewRLETSprite_TransLoop ; decrement width remaining,
						  ; nz ==> width remaining != 0
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
;;; Continue while width remaining != 0.
	djnz	_ConvertToNewRLETSprite_OpaqueLoop ; decrement width remaining,
						   ; nz ==> width remaining != 0
;; }
_ConvertToNewRLETSprite_RowEnd:
;; Decrement height remaining. Continue row loop while not zero.
	dec	iyh			; decrement height remaining
	jr	nz,_ConvertToNewRLETSprite_Row ; nz ==> height remaining != 0
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
gfx_ConvertToRLETSprite:
; Converts a sprite with normal transpareny to a sprite with RLE transparency.
; Arguments:
;  arg0 : pointer to gfx_sprite_t input
;  arg1 : pointer to gfx_rletsprite_t output
; Returns:
;  arg1 : pointer to gfx_rletsprite_t output
	pop	bc
	pop	de			; de = gfx_sprite_t *input
	ex	(sp),hl			; hl = gfx_rletsprite_t *output
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
	ld	b,iyl			; b = width
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
;;;; Continue transparent loop while width remaining != 0.
	djnz	_ConvertToRLETSprite_TransLoop ; decrement width remaining,
					       ; nz ==> width remaining != 0
;;; }
;;; Write the length of the transparent run to the output.
_ConvertToRLETSprite_TransEnd:
	ex	de,hl			; de = input data, hl = output data
	ld	(hl),c			; write trans run length
	inc	hl
	ex	de,hl			; de = output data, hl = input data
;;; Break out of data loop if width remaining == 0.
	jr	z,_ConvertToRLETSprite_RowEnd ; z ==> last pixel was transparent
					      ;   ==> width remaining == 0
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
;;;; Continue opaque/data loop while width remaining != 0.
	djnz	_ConvertToRLETSprite_OpaqueLoop ; decrement width remaining,
						; nz ==> width remaining != 0
_ConvertToRLETSprite_OpaqueEnd:
	ex	(sp),hl			; (sp) = input data, hl = location to write opaque run length
	ld	(hl),c			; write opaque run length
	pop	hl			; hl = input data
;;; Continue data loop if width remaining != 0.
	jr	z,_ConvertToRLETSprite_Trans ; z ==> last pixel was transparent
					     ;   ==> width remaining != 0
;;; }
;; }
_ConvertToRLETSprite_RowEnd:
;; Decrement height remaining. Continue row loop while not zero.
	dec	iyh			; decrement height remaining
	jr	nz,_ConvertToRLETSprite_Row ; nz ==> height remaining != 0
; }
; Return output.
	pop	hl			; hl = output
	ret

;-------------------------------------------------------------------------------
; Inner library routines
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_LZ_ReadVarSize:
; LZ Decompression Subroutine (DEPRECATED)
	push	ix
	ld	ix,0
	lea	de,ix
	add	ix,sp
	lea	hl,ix-12
	ld	sp,hl
	ld	(ix-3),de
	ld	(ix-6),de
.loop:
	or	a,a
	sbc	hl,hl
	ex	de,hl
	ld	hl,(ix+9)
	ld	a,(hl)
	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	(ix-9),hl
	ld	bc,(ix+9)
	inc	bc
	ld	(ix+9),bc
	ld	a,(ix-9)
	and	a,127
	sbc	hl,hl
	ld	l,a
	ld	(ix-12),hl
	ld	hl,(ix-3)
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	push	hl
	pop	bc
	ld	hl,(ix-12)
	call	__ior
	ld	(ix-3),hl
	ld	bc,(ix-6)
	inc	bc
	ld	(ix-6),bc
	ld	a,(ix-9)
	and	a,128
	sbc	hl,hl
	ld	l,a
	sbc	hl,de
	jr	nz,.loop
	ld	hl,(ix+6)
	ld	bc,(ix-3)
	ld	(hl),bc
	ld	hl,(ix-6)
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_Maximum:
; Calculate the resut of a signed comparison
; Inputs:
;  DE,HL=numbers
; Oututs:
;  HL=max number
	or	a,a
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
_Minimum:
; Calculate the resut of a signed comparison
; Inputs:
;  DE,HL=numbers
; Oututs:
;  HL=min number
	or	a,a
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
_ClipRegion:
; Calculates the new coordinates given the clip  and inputs
; Inputs:
;  None
; Outputs:
;  Modifies data registers
;  Sets C flag if offscreen
	ld	hl,(_XMin)
	ld	de,(iy+3)
	call	_Maximum
	ld	(iy+3),hl
	ld	hl,(_XMax)
	ld	de,(iy+9)
	call	_Minimum
	ld	(iy+9),hl
	ld	de,(iy+3)
	call	.compare
	ret	c
	ld	hl,(_YMin)
	ld	de,(iy+6)
	call	_Maximum
	ld	(iy+6),hl
	ld	hl,(_YMax)
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
_UCDivA:
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
_DivideHLBC:
; Performs signed interger division
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = HL/BC
	ex	de,hl
	xor	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	p,.next0
	push	hl
	pop	bc
	inc	a
.next0:
	or	a,a
	sbc	hl,hl
	sbc	hl,de
	jp	m,.next1
	ex	de,hl
	inc	a
.next1:
	add	hl,de
	rra
	ld	a,24
.loop:
	ex	de,hl
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
	ret	c
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
	ret

;-------------------------------------------------------------------------------
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
_MultiplyHLBC:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = HL*BC
	push	iy
	push	hl
	push	bc
	push	hl
	ld	iy,0
	ld	d,l
	ld	e,b
	mlt	de
	add	iy,de
	ld	d,c
	ld	e,h
	mlt	de
	add	iy,de
	ld	d,c
	ld	e,l
	mlt	de
	ld	c,h
	mlt	bc
	ld	a,c
	inc	sp
	inc	sp
	pop	hl
	mlt	hl
	add	a,l
	pop	hl
	inc	sp
	mlt	hl
	add	a,l
	ld	b,a
	ld	c,0
	lea	hl,iy+0
	add	hl,bc
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,de
	pop	iy
	ret

;-------------------------------------------------------------------------------
_ComputeOutcode:
; Compute the bitcode for a point (x, y) using the clip rectangle
; bounded diagonally by (xmin, ymin), and (xmax, ymax)
; Inputs:
;  HL : X Argument
;  DE : Y Argument
; Outputs:
;   A : Bitcode
	ld	bc,(_XMin)
	push	hl
	xor	a,a
	sbc	hl,bc
	pop	bc
	add	hl,hl
	jp	po,.skip1
	ccf
.skip1:
	rla
	ld	hl,(_XMax)
	dec	hl			; inclusive
	sbc	hl,bc
	add	hl,hl
	jp	po,.skip2
	ccf
.skip2:
	rla
	ld	hl,(_YMin)
	scf
	sbc	hl,de
	add	hl,hl
	jp	pe,.skip3
	ccf
.skip3:
	rla
	ld	hl,(_YMax)
	dec	hl			; inclusive
	sbc	hl,de
	add	hl,hl
	rla
	ret	po
	xor	a,1
	ret

;-------------------------------------------------------------------------------
util.getbuffer:
	ld	hl,vram + LcdSize
	ld	de,(mpLcdBase)
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nz,.check
	ld	hl,vram
.check:
	or	a,a			; if 0, copy buffer to screen
	ret	nz
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
_ShiftCalculate:
	ld	(ShiftCopyDirection),a
	sbc	a,a
	ld	hl,6
	add	hl,sp
	ld	hl,(hl)
	and	a,l
	ret	z
	ld	h,LcdWidth/2
	mlt	hl
	add	hl,hl
	ret

;-------------------------------------------------------------------------------
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
; Internal library data
;-------------------------------------------------------------------------------

_CharSpacing:
	dl	_DefaultCharSpacing
_TextData:
	dl	_DefaultTextData

_DefaultCharSpacing:
	;	0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,2,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	3,4,6,8,8,8,8,5,5,5,8,7,4,7,3,8
	db	8,7,8,8,8,8,8,8,8,8,3,4,6,7,6,7
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,5,8,5,8,8
	db	4,8,8,8,8,8,8,8,8,5,8,8,5,8,8,8
	db	8,8,8,8,7,8,8,8,8,8,8,7,3,7,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	db	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8

_DefaultTextData:
	db	$00,$00,$00,$00,$00,$00,$00,$00 ; .
	db	$7E,$81,$A5,$81,$BD,$BD,$81,$7E ; .
	db	$7E,$FF,$DB,$FF,$C3,$C3,$FF,$7E ; .
	db	$6C,$FE,$FE,$FE,$7C,$38,$10,$00 ; .
	db	$10,$38,$7C,$FE,$7C,$38,$10,$00 ; .
	db	$38,$7C,$38,$FE,$FE,$10,$10,$7C ; .
	db	$00,$18,$3C,$7E,$FF,$7E,$18,$7E ; .
	db	$00,$00,$18,$3C,$3C,$18,$00,$00 ; .
	db	$FF,$FF,$E7,$C3,$C3,$E7,$FF,$FF ; .
	db	$00,$3C,$66,$42,$42,$66,$3C,$00 ; .
	db	$FF,$C3,$99,$BD,$BD,$99,$C3,$FF ; .
	db	$0F,$07,$0F,$7D,$CC,$CC,$CC,$78 ; .
	db	$3C,$66,$66,$66,$3C,$18,$7E,$18 ; .
	db	$3F,$33,$3F,$30,$30,$70,$F0,$E0 ; .
	db	$7F,$63,$7F,$63,$63,$67,$E6,$C0 ; .
	db	$99,$5A,$3C,$E7,$E7,$3C,$5A,$99 ; .
	db	$80,$E0,$F8,$FE,$F8,$E0,$80,$00 ; .
	db	$02,$0E,$3E,$FE,$3E,$0E,$02,$00 ; .
	db	$18,$3C,$7E,$18,$18,$7E,$3C,$18 ; .
	db	$66,$66,$66,$66,$66,$00,$66,$00 ; .
	db	$7F,$DB,$DB,$7B,$1B,$1B,$1B,$00 ; .
	db	$3F,$60,$7C,$66,$66,$3E,$06,$FC ; .
	db	$00,$00,$00,$00,$7E,$7E,$7E,$00 ; .
	db	$18,$3C,$7E,$18,$7E,$3C,$18,$FF ; .
	db	$18,$3C,$7E,$18,$18,$18,$18,$00 ; .
	db	$18,$18,$18,$18,$7E,$3C,$18,$00 ; .
	db	$00,$18,$0C,$FE,$0C,$18,$00,$00 ; .
	db	$00,$30,$60,$FE,$60,$30,$00,$00 ; .
	db	$00,$00,$C0,$C0,$C0,$FE,$00,$00 ; .
	db	$00,$24,$66,$FF,$66,$24,$00,$00 ; .
	db	$00,$18,$3C,$7E,$FF,$FF,$00,$00 ; .
	db	$00,$FF,$FF,$7E,$3C,$18,$00,$00 ; .
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
	db	$00,$10,$38,$6C,$C6,$C6,$FE,$00 ; .

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

_XMin:
	dl	0
_YMin:
	dl	0
_XMax:
	dl	LcdWidth
_YMax:
	dl	LcdHeight

_ClipRegion_Full:
	dl	0
	dl	0
	dl	LcdWidth
	dl	LcdHeight

_TmpWidth:
	dl	0,0,0

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
