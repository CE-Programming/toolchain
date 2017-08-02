#include "..\include\relocation.inc"
#include "..\include\ti84pce.inc"

 .libraryAppVar     "GRAPHX"          ; Name of library on the calc
 .libraryName       "graphx"          ; Name of library
 .libraryVersion    7                 ; Version information (1-255)

;-------------------------------------------------------------------------------
; v1 functions - Can no longer move/delete
;-------------------------------------------------------------------------------
 .function "gfx_Begin",_Begin
 .function "gfx_End",_End
 .function "gfx_SetColor",_SetColor
 .function "gfx_SetDefaultPalette",_SetDefaultPalette
 .function "gfx_SetPalette",_SetPalette
 .function "gfx_FillScreen",_FillScreen
 .function "gfx_SetPixel",_SetPixel
 .function "gfx_GetPixel",_GetPixel
 .function "gfx_GetDraw",_GetDraw
 .function "gfx_SetDraw",_SetDraw
 .function "gfx_SwapDraw",_SwapDraw
 .function "gfx_Blit",_Blit
 .function "gfx_BlitLines",_BlitLines
 .function "gfx_BlitRectangle",_BlitRectangle
 .function "gfx_PrintChar",_PrintChar
 .function "gfx_PrintInt",_PrintInt
 .function "gfx_PrintUInt",_PrintUInt
 .function "gfx_PrintString",_PrintString
 .function "gfx_PrintStringXY",_PrintStringXY
 .function "gfx_SetTextXY",_SetTextXY
 .function "gfx_SetTextBGColor",_SetTextBGColorC
 .function "gfx_SetTextFGColor",_SetTextFGColorC
 .function "gfx_SetTextTransparentColor",_SetTextTransparentColorC
 .function "gfx_SetFontData",_SetFontData
 .function "gfx_SetFontSpacing",_SetFontSpacing
 .function "gfx_SetMonospaceFont",_SetMonospaceFont
 .function "gfx_GetStringWidth",_GetStringWidth
 .function "gfx_GetCharWidth",_GetCharWidth
 .function "gfx_GetTextX",_GetTextX
 .function "gfx_GetTextY",_GetTextY
 .function "gfx_Line",_Line
 .function "gfx_HorizLine",_HorizLine
 .function "gfx_VertLine",_VertLine
 .function "gfx_Circle",_Circle
 .function "gfx_FillCircle",_FillCircle
 .function "gfx_Rectangle",_Rectangle
 .function "gfx_FillRectangle",_FillRectangle
 .function "gfx_Line_NoClip",_Line_NoClip
 .function "gfx_HorizLine_NoClip",_HorizLine_NoClip
 .function "gfx_VertLine_NoClip",_VertLine_NoClip
 .function "gfx_FillCircle_NoClip",_FillCircle_NoClip
 .function "gfx_Rectangle_NoClip",_Rectangle_NoClip
 .function "gfx_FillRectangle_NoClip",_FillRectangle_NoClip
 .function "gfx_SetClipRegion",_SetClipRegion
 .function "gfx_GetClipRegion",_GetClipRegion
 .function "gfx_ShiftDown",_ShiftDown
 .function "gfx_ShiftUp",_ShiftUp
 .function "gfx_ShiftLeft",_ShiftLeft
 .function "gfx_ShiftRight",_ShiftRight
 .function "gfx_Tilemap",_Tilemap
 .function "gfx_Tilemap_NoClip",_Tilemap_NoClip
 .function "gfx_TransparentTilemap",_TransparentTilemap
 .function "gfx_TransparentTilemap_NoClip",_TransparentTilemap_NoClip
 .function "gfx_TilePtr",_TilePtr
 .function "gfx_TilePtrMapped",_TilePtrMapped
 .function "gfx_Reserved",_Reserved
 .function "gfx_AllocSprite",_AllocSprite
 .function "gfx_Sprite",_Sprite
 .function "gfx_TransparentSprite",_TransparentSprite
 .function "gfx_Sprite_NoClip",_Sprite_NoClip
 .function "gfx_TransparentSprite_NoClip",_TransparentSprite_NoClip
 .function "gfx_GetSprite",_GetSprite
 .function "gfx_ScaledSprite_NoClip",_ScaledSprite_NoClip
 .function "gfx_ScaledTransparentSprite_NoClip",_ScaledTransparentSprite_NoClip
 .function "gfx_FlipSpriteY",_FlipSpriteY
 .function "gfx_FlipSpriteX",_FlipSpriteX
 .function "gfx_RotateSpriteC",_RotateSpriteC
 .function "gfx_RotateSpriteCC",_RotateSpriteCC
 .function "gfx_RotateSpriteHalf",_RotateSpriteHalf
 .function "gfx_Polygon",_Polygon
 .function "gfx_Polygon_NoClip",_Polygon_NoClip
 .function "gfx_FillTriangle",_FillTriangle
 .function "gfx_FillTriangle_NoClip",_FillTriangle_NoClip
;-------------------------------------------------------------------------------
; v2 functions - Can no longer move/delete
;-------------------------------------------------------------------------------
 .function "gfx_LZDecompressSprite_Deprecated",_LZDecompressSprite_Deprecated
 .function "gfx_SetTextScale",_SetTextScale
;-------------------------------------------------------------------------------
; v3 functions - Can no longer move/delete
;-------------------------------------------------------------------------------
 .function "gfx_SetTransparentColor",_SetTransparentColor
 .function "gfx_ZeroScreen",_ZeroScreen
 .function "gfx_SetTextConfig",_SetTextConfig
 .function "gfx_GetSpriteChar",_GetSpriteChar
;-------------------------------------------------------------------------------
; v4 functions - Can no longer move/delete
;-------------------------------------------------------------------------------
 .function "gfx_Lighten",_Lighten
 .function "gfx_Darken",_Darken
;-------------------------------------------------------------------------------
; v5 functions - Can no longer move/delete
;-------------------------------------------------------------------------------
 .function "gfx_SetFontHeight",_SetFontHeight
 .function "gfx_ScaleSprite",_ScaleSprite
 .function "gfx_FloodFill",_FloodFill
;-------------------------------------------------------------------------------
; v6 functions - Can no longer move/delete
;-------------------------------------------------------------------------------
 .function "gfx_RLETSprite",_RLETSprite
 .function "gfx_RLETSprite_NoClip",_RLETSprite_NoClip
 .function "gfx_ConvertFromRLETSprite",_ConvertFromRLETSprite
 .function "gfx_ConvertToRLETSprite",_ConvertToRLETSprite
 .function "gfx_ConvertToNewRLETSprite",_ConvertToNewRLETSprite
;-------------------------------------------------------------------------------
; v7 functions
;-------------------------------------------------------------------------------
 .function "gfx_RotateScaleSprite",_RotateScaleSprite
 .function "gfx_RotatedScaledTransparentSprite_NoClip",_RotatedScaledTransparentSprite_NoClip
 .function "gfx_RotatedScaledSprite_NoClip",_RotatedScaledSprite_NoClip
 
 .beginDependencies
 .endDependencies

;-------------------------------------------------------------------------------
; Used throughout the library
lcdSize                 equ lcdWidth*lcdHeight
currDrawBuffer          equ 0E30014h
DEFAULT_TP_COLOR        equ 0
DEFAULT_TEXT_FG_COLOR   equ 0
DEFAULT_TEXT_BG_COLOR   equ 255
DEFAULT_TEXT_TP_COLOR   equ 255
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Useful Macros
#define mIsHLLessThanDE() or a,a \ sbc hl,de \ add hl,hl \ jp po,$+5 \.r \ ccf \
#define mIsHLLessThanBC() or a,a \ sbc hl,bc \ add hl,hl \ jp po,$+5 \.r \ ccf \
#define s8(x) 1*((x)|(((x)&80h)<<1))
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_AllocSprite:
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
	ld	e,(hl)                      ; e = width
	add	hl,bc
	ld	d,(hl)                      ; d = height
	add	hl,bc
	ld	hl,(hl)                     ; hl = malloc
	push	de
	mlt	de                          ; de = width * height
	inc	de                          ; +2 to store width and height
	inc	de                          ; de = width * height + 2
	push	de
	call	_indcallHL_ASM \.r          ; hl = malloc(width * height + 2)
	pop	de                          ; de = width * height + 2
	add	hl,de                       ; this should never carry
	sbc	hl,de                       ; check if malloc failed (hl == 0)
	pop	de                          ; e = width, d = height
	ret	z                           ; abort if malloc failed
	ld	(hl),de                     ; store width and height
	ret

;-------------------------------------------------------------------------------
_SetClipRegion:
; Sets the clipping  for clipped routines
; Arguments:
;  arg0 : Xmin
;  arg1 : Ymin
;  arg2 : Xmax
;  arg3 : Ymax
;  Must be within (0,0,320,240)
; Returns:
;  None
	call	_SetFullScrnClip_ASM \.r    ; clip against the actual LCD screen
	ld	iy,0
	lea	bc,iy+12
	add	iy,sp
	call	_ClipRectRegion_ASM \.r     ; iy points to the start of the arguments
	ret	c
	lea	hl,iy+3
	ld	de,_xmin \.r                ; copy the variables in
	ldir                                ; copy in the new structure
	ret

;-------------------------------------------------------------------------------
_Lighten:
; Lightens a 16 bit 1555 color (0 = white, 255 = same color)
; Arguments:
;  arg0 : 16 bit color
;  arg1 : 8 bit change amount
; Returns:
;  16 bit color value
	pop	de                          ; de = return vector
	pop	bc                          ; bc = color
	ex	(sp),hl                     ; l = amt
	push	bc
	push	de
                                            ; Strategy: lighten(color, amt) = ~darken(~color, amt)
                                            ; Darken the inverted color
	ld	a,c
	cpl
	ld	c,a
	ld	a,b
	cpl
	ld	b,a                         ; bc = ~color
	call	_Darken_ASM \.r	            ; hl = darken(~color, amt)
	ld	a,l                         ; Invert the darken result for the lighten result
	cpl
	ld	l,a
	ld	a,h
	cpl
	ld	h,a                         ; hl = ~darken(~color, amt) = lighten(color, amt)
	ret

;-------------------------------------------------------------------------------
_Darken:
; Darkens a 16 bit 1555 color (0 = black, 255 = same color)
; Arguments:
;  arg0 : 16 bit color
;  arg1 : 8 bit change amount
; Returns:
;  16 bit color value

; Read params
	pop	de                          ; de = return vector
	pop	bc                          ; bc = color
	ex	(sp),hl                     ; l = amt
	push	bc
	push	de                          ; Comments assume 1555 RGB color
_Darken_ASM:
                                            ; Calculate the output blue value
	push	bc
	ld	a,c                         ; a = color & $FF
	ld	c,l                         ; c = amt
	and	a,%00011111
	ld	h,a                         ; h = blue
	mlt	hl                          ; hl = blue * amt
	ld	de,128                      ; de = 128
	add	hl,de                       ; hl = blue * amt + 128
	ld	l,h
	ld	h,d                         ; hl = (blue * amt + 128) / 256 = blue_out
	ex	(sp),hl                     ; hl = color, tmp1 = blue_out
                                            ; Isolate the input red value
	ld	a,h                         ; a = color >> 8
	rra                                 ; a = color >> 9
	and	a,%00111110
	ld	b,a                         ; b = red << 1
                                            ; Calculate the output green value
	add.s	hl,hl
	rla                                 ; a & 1 = green & 1
	add	hl,hl
	add	hl,hl                       ; hl = color << 3
	rra
	ld	a,h
	rla
	and	a,%00111111
	ld	h,a                         ; h = green
	ld	l,c                         ; l = amt
	mlt	hl                          ; hl = green * amt
	add	hl,de                       ; hl = green * amt + 128
	ld	l,h                         ; l = (green * amt + 128) / 256 = green_out
                                            ; Calculate the output red value
	mlt	bc                          ; bc = red * amt << 1
	inc	b                           ; b = (red * amt + 128 << 1) / 256
	srl	b                           ; b = (red * amt + 128) / 256 = red_out
                                            ; Position the output red and green bits
	add	hl,hl
	add	hl,hl                       ; l = green_out << 2
	ld	h,b                         ; h = red_out
	add	hl,hl
	add	hl,hl                       ; hl = (red_out << 10) | (green_out << 4)
	bit	4,l
	jr	z,+_
	set	7,h
	res	4,l
_:                                          ; hl = (green_out & 1 << 15) | (red_out << 10) | (green_out >> 1 << 5)
                                            ; Add the output blue value (no positioning necessary) for the final output color
	pop	bc                          ; bc = blue_out
	add	hl,bc                       ; hl = color_out
	ret

;-------------------------------------------------------------------------------
_SetColor:
; Sets the global color index for all routines
; Arguments:
;  arg0 : Global color index
; Returns:
;  Previous global color index
	pop	de                          ; de = return vetor
	ex	(sp),hl                     ; l = color
	ld	a,l                         ; a = color
	ld	hl,Color_SMC_1 \.r
	ld	c,(hl)                      ; c = old color
	ld	(hl),a                      ; store all the new color values
	ld	(Color_SMC_2),a \.r
	ld	(Color_SMC_3),a \.r
	ld	(Color_SMC_4),a \.r
	ld	(Color_SMC_5),a \.r
_SetColor_Ret:
	ld	a,c                         ; a = old color
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
_SetTransparentColor:
; Sets the global transparent color index for all routines
; Arguments:
;  arg0 : Transparent color index
; Returns:
;  Previous transparent color index
	pop	de                          ; de = return vetor
	ex	(sp),hl                     ; l = color
	ld	a,l                         ; a = color
	ld	hl,TColor_SMC_1 \.r
	ld	c,(hl)                      ; c = old color
	ld	(hl),a                      ; store all the new color values
	ld	(TColor_SMC_2),a \.r
	ld	(TColor_SMC_3),a \.r
	ld	(TColor_SMC_4),a \.r
	ld	(TColor_SMC_5),a \.r
	ld	(TColor_SMC_6),a \.r
	ld	(TColor_SMC_7),a \.r
	jr	_SetColor_Ret
    
;-------------------------------------------------------------------------------
_End:
; Closes the graphics library and sets up for the TI-OS
; Arguments:
;  None
; Returns:
;  None
	call	_boot_ClearVRAM             ; clear the screen
	ld	hl,mpLcdBase
	ld	a,lcdBpp16                  ; restore the screen mode
	jr	+_

;-------------------------------------------------------------------------------
_Begin:
; Sets up the graphics canvas
; Arguments:
;  arg0: bpp mode to start in
; Returns:
;  None
	ld	hl,LargeFontJump_SMC \.r
	ld	a,(hl)
	ld	(UseLargeFont_SMC),a \.r    ; store the jump offset for later
	ld	(hl),0                      ; jump nowhere if false
	call	_boot_ClearVRAM             ; clear the screen
	ld	a,lcdBpp8
	ld	hl,currDrawBuffer
_:	ld	de,vram
	ld	(hl),de                     ; set the current draw to the screen
	ld	(mpLcdCtrl),a
	ld	l,mpLcdIcr&$FF
	ld	(hl),4                      ; allow interrupts status for double buffering

;-------------------------------------------------------------------------------
_SetDefaultPalette:
; Sets up the default palette where H=L
; Arguments:
;  None
; Returns:
;  None
	ld	de,mpLcdPalette             ; address of mmio palette
	ld	b,e                         ; b = 0
_:	ld	a,b
	rrca
	xor	a,b
	and	a,%11100000
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
	jr	nz,-_                       ; loop for 256 times to fill palette
	ret

;-------------------------------------------------------------------------------
_FillScreen:
; Fills the screen with the specified color index
; Arguments:
;  arg0 : Color index
; Returns:
;  None
	pop	bc
	ex	(sp),hl			; l = color
	push	bc
	ld	a,l			; a = color
	ld	hl,(currDrawBuffer)	; hl = buffer
	push	hl
	pop	de			; de = buffer
_	ld	(de),a			; *buffer = color
	inc	de			; de = buffer+1
	ld	bc,lcdSize-1
	ldir				; fill the rest of the buffer
	ret

;-------------------------------------------------------------------------------
_ZeroScreen:
; Fills the current screen with a bunch of zeros
; Arguments:
;  None
; Returns:
;  None
	ld	hl,$E40000		; E40000-EFFFFF: reads as 0, 1 waitstate
	ld	de,(currDrawBuffer)
	xor	a,a
	jr	-_

;-------------------------------------------------------------------------------
_SetPalette:
; Sets the palette colors
; Arguments:
;  arg0 : Pointer to palette
;  arg1 : Size of palette in bytes
;  arg2 : Offset at which to start inserting the palette
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,mpLcdPalette>>1
	ld	l,(iy+9)                    ; offset in palette
	add	hl,hl
	ex	de,hl
	ld	hl,(iy+3)                   ; pointer to input palette
	ld	bc,(iy+6)                   ; size of input palette
	ldir                                ; copy the palette in
	ret

;-------------------------------------------------------------------------------
_GetPixel:
; Gets the color index of a pixel
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  Color index of X,Y coordinate
	ld	hl,3
	add	hl,sp
	ld	bc,(hl)                     ; bc = x coordinate
	inc	hl
	inc	hl
	inc	hl                          ; move to next argument
	ld	e,(hl)                      ; e = y coordinate
	call	_PixelPtr_ASM \.r
	ret	c                           ; return if out of bounds
	ld	a,(hl)                      ; get the actual pixel
	ret

;-------------------------------------------------------------------------------
_SetPixel:
; Sets the color pixel to the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	bc,(hl)                     ; bc = x coordinate
	inc	hl
	inc	hl
	inc	hl                          ; move to next argument
	ld	e,(hl)                      ; e = y coordinate
_SetPixel_ASM:
	call	_PixelPtr_ASM \.r
	ret	c                           ; return if out of bounds
Color_SMC_1 =$+1
	ld	(hl),0                      ; get the actual pixel
	ret

;-------------------------------------------------------------------------------
_FillRectangle:
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
	ld	hl,(iy+9)                   ; hl = width
	ld	de,(iy+3)                   ; de = x coordinate
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(iy+12)                  ; hl = height
	ld	de,(iy+6)                   ; de = y coordinate
	add	hl,de
	ld	(iy+12),hl
	call	_ClipRectRegion_ASM \.r
	ret	c                           ; return if offscreen or degenerate
	ld	de,(iy+3)
	ld	hl,(iy+9)
	sbc	hl,de
	push	hl
	ld	de,(iy+6)
	ld	hl,(iy+12)
	sbc	hl,de
	pop	bc                          ; bc = new width
	ld	a,l                         ; a = new height
	ld	hl,(iy+3)                   ; hl = new x, de = new y
	jr	_FillRectangle_NoClip_ASM

;-------------------------------------------------------------------------------
_FillRectangle_NoClip:
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
	ld	a,(iy+12)                   ; a = height
	or	a,a
	ret	z                           ; make sure height is not 0
	ld	bc,(iy+9)                   ; bc = width
	sbc	hl,hl
	adc	hl,bc
	ret	z                           ; make sure width is not 0
	ld	hl,(iy+3)                   ; hl = x coordinate
	ld	e,(iy+6)                    ; e = y coordinate
_FillRectangle_NoClip_ASM:
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de
	ex	de,hl                       ; de -> place to begin drawing
	push 	de
	ld	(_RectangleWidth1_SMC),bc \.r
	ld	(_RectangleWidth2_SMC),bc \.r
	ld	hl,Color_SMC_1 \.r
	ldi                                 ; check if we only need to draw 1 pixel
	pop	hl
	jp	po,_Rectangle_NoClip_Skip \.r
	ldir
_Rectangle_NoClip_Skip:
	dec 	a
	ret	z
	inc	b
	ld	c,$40                       ; = slightly faster "ld bc,lcdWidth"
_RectangleLoop_NoClip:
	add	hl,bc
	dec	de
	ex	de,hl
_RectangleWidth1_SMC =$+1
	ld	bc,0
	lddr
	dec	a
	ret	z
	ld      bc,2*lcdWidth+1
	add     hl,bc
        inc     de
        ex      de,hl
_RectangleWidth2_SMC =$+1
        ld      bc,0
        ldir
        ld      bc,2*lcdWidth-1
	dec	a
	jr	nz,_RectangleLoop_NoClip
	ret

;-------------------------------------------------------------------------------
_Rectangle:
; Draws an clipped rectangle outline with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	push	ix                          ; need to use ix because lines use iy
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	push	bc
	push	de
	push	hl
	call	_HorizLine \.r              ; top horizontal line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	_VertLine \.r               ; left vertical line
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	add	hl,bc                       ; add x and width
	dec	hl
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	_VertLine \.r               ; right vertical line
	ld	de,(ix+6)
	ld	hl,(ix+9)
	ld	bc,(ix+15)
	add	hl,bc
	dec	hl                          ; add y and height
	ld	bc,(ix+12)
	push	bc
	push	hl
	push	de
	call	_HorizLine \.r              ; bottom horizontal line
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_Rectangle_NoClip:
; Draws an unclipped rectangle outline with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,-1
	add	iy,sp
	ld	hl,(iy+4)                   ; hl = x
	ld	e,(iy+7)                    ; e = y
	ld	bc,(iy+10)                  ; bc = width
	ld	d,(iy+13)                   ; d = height
	push	bc
	push	hl
	push	de
	call	_RectHoriz_ASM \.r          ; top horizontal line
	pop	bc
	push	bc
	call	_RectVert_ASM \.r           ; right vertical line
	pop	bc
	pop	hl
	ld	e,c
	call	_VertLine_ASM \.r           ; left vertical line
	pop	bc
	or	a,a
	sbc	hl,de
	jp	_MemSet_ASM \.r             ; bottom horizontal line

;-------------------------------------------------------------------------------
_HorizLine:
; Draws an clipped horizontal line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,-1
	add	iy,sp
	ld	de,(_ymin) \.r
	ld	hl,(iy+7)
	mIsHLLessThanDE()                  ; compare y coordinate <-> ymin
	ret	c
	ld	hl,(_ymax) \.r
	dec	hl                          ; inclusive
	ld	de,(iy+7)
	mIsHLLessThanDE()                  ; compare y coordinate <-> ymax
	ret	c
	ld	hl,(iy+10)
	ld	de,(iy+4)
	add	hl,de
	ld	(iy+10),hl
	ld	hl,(_xmin) \.r
	call	_Max_ASM \.r
	ld	(iy+4),hl                   ; save maximum x value
	ld	hl,(_xmax) \.r
	ld	de,(iy+10)
	call	_Min_ASM \.r
	ld	(iy+10),hl                  ; save minimum x value
	ld	de,(iy+4)
	mIsHLLessThanDE()
	ret	c
	ld	hl,(iy+10)
	sbc	hl,de
	push	hl
	pop	bc                          ; bc = length
	ld	e,(iy+7)                    ; e = y coordinate
	scf
	jr	_RectHoriz_ASM

;-------------------------------------------------------------------------------
_HorizLine_NoClip:
; Draws an unclipped horizontal line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,-1
	add	iy,sp
	ld	e,(iy+7)                    ; e = y coordinate
	ld	bc,(iy+10)                  ; bc = width
_RectHoriz_ASM:
	sbc	hl,hl
	add	hl,bc
	ret	nc                          ; make sure the width is not 0
	ld	hl,(iy+4)
_HorizLine_NoClip_ASM:
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de                       ; hl -> place to draw
Color_SMC_2 =$+1
	ld	a,0                         ; color index to use
_MemSet_ASM:
	ld	(hl),a
	push	hl
	cpi
	ex	de,hl
	pop	hl
	ret	po
	ldir
	ret

;-------------------------------------------------------------------------------
_VertLine:
; Draws an clipped vertical line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(_xmax) \.r
	dec	hl                          ; inclusive
	ld	de,(iy+3)
	mIsHLLessThanDE()
	ret	c                           ; return if x > xmax
	ld	hl,(_xmin) \.r
	ex	de,hl
	mIsHLLessThanDE()
	ret	c                           ; return if x < xmin
	ld	hl,(iy+9)
	ld	de,(iy+6)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_ymin) \.r
	call	_Max_ASM \.r                ; get minimum y
	ld	(iy+6),hl
	ld	hl,(_ymax) \.r
	ld	de,(iy+9)
	call	_Min_ASM \.r                ; get maximum y
	ld	(iy+9),hl
	ld	de,(iy+6)
	mIsHLLessThanDE()
	ret	c                           ; return if not within y bounds
	ld	hl,(iy+9)
	sbc	hl,de
	ld	b,l
	ld	hl,(iy+3)
	jr	_VertLine_ASM               ; jump to unclipped version

;-------------------------------------------------------------------------------
_VertLine_NoClip:
; Draws an unclipped vertical line with the global color index
; Arguments:
;  arg0 : X coordinate
;  arg1 : Y coordinate
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)                   ; hl = x
	ld	e,(iy+6)                    ; e = y
	ld	b,(iy+9)                    ; b = length
_VertLine_ASM:
	xor	a,a
	or	a,b
	ret	z                           ; check if length is 0
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de                       ; hl -> drawing location
_RectVert_ASM:
	ld	de,lcdWidth
Color_SMC_3 =$+1
	ld 	a,0
_:	ld	(hl),a                      ; loop for height
	add	hl,de
	djnz	-_
	ret

;-------------------------------------------------------------------------------
_SetDraw:
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
	ld	hl,(mpLcdBase)              ; get current base
	ld	bc,vram
	jr	z,+++_
	sbc	hl,bc
	jr	nz,++_                      ; if not the same, swap
_:	ld	bc,vram+lcdSize
_:	ld	(currDrawBuffer),bc
	ex	de,hl
	jp	(hl)
_:	sbc	hl,bc
	jr	z,--_                       ; if the same, swap
	jr	---_

;-------------------------------------------------------------------------------
_SwapDraw:
; Safely swap the vram buffer pointers for double buffered output
; Arguments:
;  None
; Returns:
;  None
	ld	hl,vram
	ld	de,(mpLcdBase)
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nz,+_
	ld	hl,vram+lcdSize
_:	ld	(currDrawBuffer),de         ; set up the new buffer location
	ld	(mpLcdBase),hl              ; set the new pointer location
	ld	hl,mpLcdIcr
	set	2,(hl)                      ; clear the previous intrpt set
	ld	l,mpLcdRis&$ff
_:	bit	2,(hl)                      ; wait until the interrupt triggers
	jr	z,-_
	ret

;-------------------------------------------------------------------------------
_GetDraw:
; Gets the current drawing state
; Arguments:
;  None
; Returns:
;  Returns true if drawing on the buffer
	ld	hl,(currDrawBuffer)
	ld	de,(mpLcdBase)
	xor	a,a
	sbc	hl,de
	ret	z                           ; drawing to screen
	inc	a
	ret                                 ; drawing to buffer

;-------------------------------------------------------------------------------
_Circle:
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
	jp	z,_Circle_Exit \.r
	ld	hl,1
	or	a,a
	sbc	hl,bc
	jp	l_4 \.r
l_5:	ld	bc,(iy+3)
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
	call	_SetPixel_ASM \.r
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
	call	_SetPixel_ASM \.r
	ld	bc,(iy-6)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_SetPixel_ASM \.r
	pop	de
	ld	bc,(iy-3)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_ASM \.r
	pop	bc
	pop	de
	call	_SetPixel_ASM \.r
	pop	de
	ld	bc,(iy-6)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_ASM \.r
	ld	bc,(iy-3)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_SetPixel_ASM \.r
	pop	de
	pop	bc
	call	_SetPixel_ASM \.r
	ld	bc,(iy-3)
	inc	bc
	ld	(iy-3),bc
	ld	bc,(iy-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,l__2 \.r
	jp	pe,l_3 \.r
	jr	l__3
l__2:	jp	po,l_3 \.r
l__3:	ld	hl,(iy-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	l_4
l_3:	ld	bc,(iy-6)
	dec	bc
	ld	(iy-6),bc
	ld	hl,(iy-3)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	ld	de,(iy-9)
	add	hl,de
l_4:	ld	(iy-9),hl
	ld	bc,(iy-3)
	ld	hl,(iy-6)
	or	a,a
	sbc	hl,bc
	jp	p,l__4 \.r
	jp	pe,l_5 \.r
	jr	+_
l__4:	jp	po,l_5 \.r
_Circle_Exit:
_:	ld	sp,iy
	ret

;-------------------------------------------------------------------------------
_FillCircle:
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
	jp	z,_RstStack \.r
	ld	hl,1
	or	a,a
	sbc	hl,bc
	jp	b_4 \.r
_FillCircleSectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(FCircle0_SMC),hl \.r
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(FCircle1_SMC),hl \.r
	push	hl
	call	_HorizLine \.r
FCircle0_SMC: =$+1
	ld	hl,0
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	push	hl
FCircle1_SMC: =$+1
	ld	hl,0
	push	hl
	call	_HorizLine \.r
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(FCircle2_SMC),hl \.r
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+9)
	add	hl,bc
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(FCircle3_SMC),hl \.r
	push	hl
	call	_HorizLine \.r
FCircle2_SMC: =$+1
	ld	hl,0
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	push	hl
FCircle3_SMC: =$+1
	ld	hl,0
	push	hl
	call	_HorizLine \.r
	lea	hl,ix-9
	ld	sp,hl
	ld	bc,(ix-3)
	inc	bc
	ld	(ix-3),bc
	ld	bc,(ix-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,b__2 \.r
	jp	pe,b_3 \.r
	jr	b__3
b__2:	jp	po,b_3 \.r
b__3:	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	b_4
b_3:	ld	bc,(ix-6)
	dec	bc
	ld	(ix-6),bc
	ld	hl,(ix-3)
	ld	de,(ix-9)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	add	hl,de
b_4:	ld	(ix-9),hl
	ld	bc,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	jp	p,+_ \.r
	jp	pe,_FillCircleSectors \.r
	ld	sp,ix
	pop	ix
	ret
_:	jp	po,_FillCircleSectors \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_FillCircle_NoClip:
; Draws an unclipped circle
; Arguments:
;  arg0 : X coordinate   (24b)
;  arg1 : Y coordinate   (8b)
;  arg2 : Radius         (8b)
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
	jp	z,_RstStack \.r
	ld	hl,1
	or	a,a
	sbc	hl,bc
	jp	_FillCircleNC_Loop \.r
_FillCircle_NoClipSectors:
	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	ld	(FCircleNC0_SMC),hl \.r
	push	hl
	ld	bc,(ix-6)
	ld	hl,(ix+9)
	add	hl,bc
	ld	e,l
	ld	bc,(ix-3)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(FCircleNC1_SMC),hl \.r
	pop	bc
	call	_HorizLine_NoClip_ASM \.r
FCircleNC0_SMC: =$+1
	ld	bc,0
	ld	de,(ix-6)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	ld	e,l
FCircleNC1_SMC: =$+1
	ld	hl,0
	call	_HorizLine_NoClip_ASM \.r
	ld	hl,(ix-6)
	add	hl,hl
	inc	hl
	ld	(FCircleNC3_SMC),hl \.r
	push	hl
	ld	bc,(ix-3)
	ld	hl,(ix+9)
	add	hl,bc
	ld	e,l
	ld	bc,(ix-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	ld	(FCircleNC4_SMC),hl \.r
	pop	bc
	call	_HorizLine_NoClip_ASM \.r
FCircleNC3_SMC: =$+1
	ld	bc,0
	ld	de,(ix-3)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	ld	e,l
FCircleNC4_SMC: =$+1
	ld	hl,0
	call	_HorizLine_NoClip_ASM \.r
	ld	bc,(ix-3)
	inc	bc
	ld	(ix-3),bc
	ld	bc,(ix-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,+_ \.r
	jp	pe,+++_ \.r
	jr	++_
_:	jp	po,++_ \.r
_:	ld	hl,(ix-3)
	add	hl,hl
	inc	hl
	add	hl,bc
	jr	_FillCircleNC_Loop
_:	ld	bc,(ix-6)
	dec	bc
	ld	(ix-6),bc
	ld	hl,(ix-3)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	ld	de,(ix-9)
	add	hl,de
_FillCircleNC_Loop:
	ld	(ix-9),hl
	ld	bc,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	jp	nc,_FillCircle_NoClipSectors \.r
_RstStack:
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_Line:
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
	push	hl                          ; temp storage
	ld	hl,(iy+3)                   ; x0
	ld	de,(iy+6)                   ; y0
	call	_ComputeOutcode_ASM \.r
	ld	(iy-1),a
	ld	hl,(iy+9)                   ; x1
	ld	de,(iy+12)                  ; y1
	call	_ComputeOutcode_ASM \.r
	ld	(iy-2),a
CohenSutherlandLoop:
	ld	b,(iy-1)                    ; b = outcode0
	ld	a,(iy-2)                    ; a = outcode1
	tst	a,b
	jp	nz,TrivialReject \.r        ; if(outcode0|outcode1)
	or	a,a
	jr	nz,GetOutOutcode
	or	a,b
	jp	z,TrivialAccept \.r
GetOutOutcode:                              ; select correct outcode
	push	af                          ; a = outoutcode
	rra
	jr	nc,NotTop                   ; if (outcodeOut & TOP)
	ld	hl,(_ymax) \.r
	dec	hl                          ; inclusive
	jr	ComputeNewX
NotTop:
	rra
	jr	nc,NotBottom                ; if (outcodeOut & BOTTOM)
	ld	hl,(_ymin) \.r
ComputeNewX:
	push	hl
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc                       ; ymax_ymin - y0
	ex	de,hl
	ld	hl,(iy+9)
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc                       ; x0 - x1
	call	__imulsDE_ASM \.r
	ex	de,hl                       ; (x0 - x1)*(ymax_ymin - y0)
	ld	hl,(iy+12)
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc                       ; y1 - y0
	push	hl
	pop	bc
	ex	de,hl
	call	__idivs_ASM \.r             ; ((x0 - x1)*(ymax_ymin - y0))/(y1 - y0)
	ld	bc,(iy+3)
	add	hl,bc                       ; (x) hl = x0 + ((x0 - x1)*(ymax_ymin - y0))/(y1 - y0)
	pop	de                          ; (y) de = ymax_ymin
	jr	FinishComputations
NotBottom:
	rra
	jr	nc,NotRight                 ; if (outcodeOut & RIGHT)
	ld	hl,(_xmax) \.r
	dec	hl                          ; inclusive
	jr	ComputeNewY
NotRight:
	rra
	jr	nc,FinishComputations       ; if (outcodeOut & LEFT)
	ld	hl,(_xmin) \.r
ComputeNewY:
	push	hl
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc                       ; xmax_xmin - x0
	ex	de,hl
	ld	hl,(iy+12)
	ld	bc,(iy+6)
	sbc	hl,bc                       ; x1 - x0
	call	__imulsDE_ASM \.r
	ex	de,hl                       ; (x1 - x0)*(xmax_xmin - x0)
	ld	hl,(iy+9)
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc                       ; y1 - y0
	push	hl
	pop	bc
	ex	de,hl
	call	__idivs_ASM \.r             ; ((x1 - x0)*(xmax_xmin - x0))/(y1 - y0)
	ld	bc,(iy+6)
	add	hl,bc
	ex	de,hl                       ; (y) de = y0 + ((x1 - x0)*(xmax_xmin - x0))/(y1 - y0)
	pop	hl                          ; (x) hl = ymax_ymin
FinishComputations:
	pop	af
	cp	a,(iy-1)
	jr	nz,OutcodeOutOutcode1
	ld	(iy+3),hl
	ld	(iy+6),de
	call	_ComputeOutcode_ASM \.r
	ld	(iy-1),a                    ; b = outcode0
	jp	CohenSutherlandLoop \.r
OutcodeOutOutcode1:
	ld	(iy+9),hl
	ld	(iy+12),de
	call	_ComputeOutcode_ASM \.r
	ld	(iy-2),a                    ; c = outcode1
	jp	CohenSutherlandLoop \.r
TrivialReject:
	inc	sp
	inc	sp
	inc	sp
	ret
TrivialAccept:
	inc	sp
	inc	sp
	inc	sp
	;jr	_Line_NoClip                ; line routine handler

;-------------------------------------------------------------------------------
_Line_NoClip:
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
	ld	c,(iy+12)			; line from hl,b to de,c
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	c,+_				; draw left to right
	ex	de,hl
	ld	a,b
	ld	b,c
	ld	c,a
_:	push	bc
	pop	iy
	push	hl
	ld	hl,(currDrawBuffer)
	ld	c,160
	mlt	bc
	add	hl,bc
	add	hl,bc				; y0 * screenwidth
	pop	bc
	add	hl,bc				; y0 * screenwidth + x0
	push	hl				; save buffer
	ex	de,hl
	or	a,a
	sbc	hl,bc				; xe - xs
	push	hl
	pop	bc				; bc = dx
	ld	a,iyh
	or	a,a
	sbc	hl,hl
	ld	l,a				; y1
	ex	de,hl
	ld	a,iyl
	sbc	hl,hl
	ld	l,a				; y0
	sbc	hl,de
	jr	nc,$+9
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	inc	hl				; abs(dy)
	ld	a,iyl
	sub	a,iyh
	ld	iy,-320
	jr	c,$+7
	ld	iy,320
	or	a,a
	sbc	hl,bc
	add	hl,bc				; hl = dy
	jr	nc,dl_vertical
dl_horizontal:
	ld	a,l
	or	a,h
	ld	a,$38
	jr	nz,$+4
	xor	a,$20
	ld	(_smc_dl_jr_0 + 0),a \.r	; write smc
	ld	(_smc_dl_width_1 + 1),iy \.r	; write smc
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	inc	hl
	ex	de,hl				; de = -dy
	pop	hl				; restore buffer
	ld	(_smc_dl_dx_1 + 1),bc \.r	; write smc
	ld	(_smc_dl_dy_1 + 1),de \.r	; write smc
	push	bc
	srl	b
	rr	c
	push	bc
	pop	iy				; iy = dx / 2
	pop	bc
	inc	bc
Color_SMC_4 =$+1
	ld	a,$00
dl_hloop:
	ld	(hl),a				; write pixel
	cpi
	ret	po
	add	iy,de				; dy
_smc_dl_jr_0:
	jr	c,dl_hloop
_smc_dl_width_1:
	ld	de,$000000
	add	hl,de				; y inc
_smc_dl_dx_1:
	ld	de,$000000			; dx
	add	iy,de
_smc_dl_dy_1:
	ld	de,$000000			; dy
	jr	dl_hloop
dl_vertical:
	lea	de,iy
	ld	b,c
	ld	a,l
	ld	iyl,a
	ld	c,a
	srl	a				; a = dy / 2
	inc	c
	pop	hl
dl_vloop:
Color_SMC_5 =$+1
	ld	(hl),$00			; write pixel
	dec	c
	ret	z
	add	hl,de				; y inc
	sub	a,b				; dx
	jr	nc,dl_vloop
	inc	hl
	add	a,iyl				; dy
	jr	dl_vloop

;-------------------------------------------------------------------------------
_Blit:
; Copies the buffer image to the screen and vice versa
; Arguments:
;  arg0 : Buffer to copy to (screen = 0, buffer = 1)
; Returns:
;  None
	pop	de
	pop	hl
	push	hl
	push	de
	ld	a,l                         ; a = buffer to blit to
	call	_CheckBlit_ASM \.r          ; figure out which one to blit
	ld	bc,lcdSize
	ldir                                ; just do it
	ret

;-------------------------------------------------------------------------------
_BlitLines:
; Copies the buffer image to the screen and vice versa line wise
; Arguments:
;  arg0 : Buffer to copy to (screen = 0, buffer = 1)
;  arg1 : Y coordinate
;  arg2 : Number of lines to copy
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	l,(iy+9)                    ; l = y coordinate
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl                       ; hl -> place to end
	push	hl
	ld	l,(iy+6)
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl                       ; hl -> place to start
	push	hl
	ld	a,(iy+3)
	call	_CheckBlit_ASM \.r          ; find pointers to current buffer
	pop	bc
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	pop	bc                          ; number of lines to copy
	ldir                                ; blit it
	ret

;-------------------------------------------------------------------------------
_BlitRectangle:
; Copies the buffer image to the screen and vice versa rectangularly
; Arguments:
;  arg0 : Buffer to copy to (screen = 0, buffer = 1)
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Width
;  arg4 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(iy+6)                   ; de = x coordinate
	ld	l,(iy+9)                    ; l = y coordinate
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de                       ; hl = amount to increment
	push	hl                          ; save amount to increment
	ld	a,(iy+3)
	call	_CheckBlit_ASM \.r          ; get pointers to buffer
	pop	bc
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	ld	bc,(iy+12)                  ; the width of things
	ld	(BlitRectWidth_SMC),bc \.r
	push	hl
	ld	hl,lcdWidth
	or	a,a
	sbc	hl,bc                       ; change in width for rectangle
	ld	(BlitRectDelta_SMC),hl \.r
	pop	hl
	ld	a,(iy+15)
	ld	iy,0
_:	add	iy,de
	lea	de,iy
BlitRectWidth_SMC =$+1
	ld	bc,0                        ; smc for speedz
	ldir
BlitRectDelta_SMC =$+1
	ld	bc,0                        ; increment to next line
	add	hl,bc
	ld	de,lcdWidth                 ; increment to next line
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_CheckBlit_ASM:
	ld	hl,vram+lcdSize
	ld	de,(mpLcdBase)
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nz,+_
	ld	hl,vram
_:	or	a,a                         ; if 0, copy buffer to screen
	ret	nz
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
_ShiftLeft:
; Shifts whatever is in the clip left by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	.db	$F6                         ; magic byte

;-------------------------------------------------------------------------------
_ShiftUp:
; Shifts whatever is in the clip up by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	scf
	ld	a,$B0
	call	_ShiftCalculate_ASM \.r
	ld	(ShiftAmtOff_SMC),hl \.r
	jr	z,+_
	sbc	hl,hl
_:	ex	de,hl
	ld	hl,(_xmax) \.r
	ld	bc,(_xmin) \.r
	sbc	hl,bc
	sbc	hl,de
	ld	(ShiftCpyAmt_SMC),hl \.r
	ex	de,hl
	ld	hl,lcdWidth
	sbc	hl,de
	ld	(ShiftLineOff_SMC),hl \.r
	ld	hl,_ymax \.r
	sub	a,(hl)
	ld	hl,_ymin \.r
	ld	e,(hl)
	add	a,e
	jr	_Shift_ASM

;-------------------------------------------------------------------------------
_ShiftRight:
; Shifts whatever is in the clip right by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	.db	$F6                         ; magic byte

;-------------------------------------------------------------------------------
_ShiftDown:
; Shifts whatever is in the clip down by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	scf
	ld	a,$B8
	call	_ShiftCalculate_ASM \.r
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
	ld	(ShiftAmtOff_SMC),hl \.r
	or	a,a
	jr	z,_
	sbc	hl,hl
_:	ld	bc,(_xmax) \.r
	add	hl,bc
	dec	bc
	ld	e,a
	ld	a,(_ymin) \.r
	add	a,e
	ld	de,(_xmin) \.r
	sbc	hl,de
	ld	(ShiftCpyAmt_SMC),hl \.r
	ld	de,-lcdWidth
	add	hl,de
	ld	(ShiftLineOff_SMC),hl \.r
	ld	hl,_ymax \.r
	ld	e,(hl)
	sub	a,e
	dec	e
_Shift_ASM:
	ld	d,lcdWidth/2
	mlt	de
	ld	hl,(currDrawBuffer)
	add	hl,de
	add	hl,de
	add	hl,bc
ShiftCpyAmt_SMC =$+1
_:	ld	bc,0
	ex	de,hl
ShiftAmtOff_SMC =$+1
	ld	hl,0
	add	hl,de
ShiftCpyDir_SMC =$+1
	ldir
ShiftLineOff_SMC =$+1
	ld	hl,0
	add	hl,de
	inc	a
	jr	nz,-_
	ret

_ShiftCalculate_ASM:
	ld	(ShiftCpyDir_SMC),a \.r
	sbc	a,a
	ld	hl,6
	add	hl,sp
	ld	hl,(hl)
	and	a,l
	ret	z
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	ret

;-------------------------------------------------------------------------------
_GetClipRegion:
; Arguments:
;  Pointer to struct
; Returns:
;  False if offscreen
	ld	hl,3
	add	hl,sp
	ld	iy,(hl)
	call	_ClipRectRegion_ASM \.r     ; get the clipping region
	sbc	a,a                         ; return false if offscreen (0)
	inc	a
	ret

;-------------------------------------------------------------------------------
_ScaledSprite_NoClip:
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
	ld	h,lcdWidth/2
	ld	l,(iy+15)                   ; height of scale
	ld	a,l
	ld	(NcSprHscl+1),a \.r
	mlt	hl
	add	hl,hl
	ld	(NcSprHscl320+1),hl \.r
	ld	de,(iy+6)                   ; x coordinate
	ld	c,(iy+9)                    ; y coordinate
	ld	a,(iy+12)                   ; width of scale
	ld	h,a
	ld	ixl,a
	ld	iy,(iy+3)                   ; start of sprite structure
	ld	l,(iy+0)
	ld	a,l
	ld	(NcSprWidth+1),a \.r
	mlt	hl
	ld	(SprWxSclW1+1),hl \.r
	ld	(SprWxSclW2+1),hl \.r
	ld	a,(iy+1)
	ld	ixh,a                       ; height of sprite
	ld	hl,(currDrawBuffer)
	add	hl,de
	inc	hl
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
NcSprBigLoop:
	add	hl,bc
	ex	de,hl
	sbc	hl,hl
	ld	b,l
	add	hl,de
	dec	hl
	push	de
NcSprWidth:
	ld	a,0                         ; width of sprite
	jr	NcSprLpEntry
NcSprWlp:
	ldir
NcSprLpEntry:
	ld	c,(iy+2)
	inc	iy
	ld	(hl),c
	ld	c,ixl                       ; width of scale
	dec	a
	jr	nz,NcSprWlp
	dec	c
	jr	z,NcSprHscl
	ldir
NcSprHscl:
	ld	a,0                         ; height of scale
	dec	a
	jr	z,NcSprW_end
	inc	b
	ld	c,$40                       ; bc = lcdWidth
NcSprLineCopy:
	add	hl,bc
	dec	de
	ex	de,hl
SprWxSclW1:
	ld	bc,0                        ; widthSprite x widthScale
	lddr
	dec	a
	jr	z,NcSprW_end
	ld	bc,641
	add	hl,bc
	inc	de
	ex 	de,hl
SprWxSclW2:
	ld	bc,0                        ; widthSprite x widthScale
	ldir
	ld	bc,639
	dec	a
	jr	nz,NcSprLineCopy
NcSprW_end:
	pop	hl
NcSprHscl320:
	ld	bc,0                        ; lcdWidth x heightScale
	dec	ixh
	jr	nz,NcSprBigLoop
	pop	ix                          ; restore ix sp
	ret

;-------------------------------------------------------------------------------
_ScaledTransparentSprite_NoClip:
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
	ld	hl,(iy+6)                   ; hl = x coordinate
	ld	c,(iy+9)                    ; c = y coordniate
	ld	de,(currDrawBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl                       ; de -> start draw location
	ld	hl,lcdWidth
	ld	a,(iy+15)
	ld	(NcSprTHeightScale),a \.r
	ld	a,(iy+12)
	ld	(NcSprTScaledWidth),a \.r   ; SMC faster inner loop
	ld	iy,(iy+3)                   ; iy -> start of sprite struct
	ld	c,(iy+0)                    ; c = width
	ld	b,a
	ld	a,c
	mlt	bc
	sbc	hl,bc                       ; find x offset next
	ld	(NoClipSprTransScaledMoveAmt),hl \.r
	ld	(NoClipSprTransWidth),a \.r
	ld	a,(iy+1)
	lea	hl,iy+2                     ; hl -> sprite data
	push	ix                          ; save ix sp
	ld	ixh,a                       ; ixh = height
NcSprTHeightScale =$+2
_:	ld	ixl,0                       ; ixl = height scale
_:	push	hl
NoClipSprTransWidth =$+1
	ld	c,0
NcSprTScaledWidth =$+1
_:	ld	b,0
	ld	a,(hl)                      ; get sprite pixel
TColor_SMC_2 =$+1
	cp	a,DEFAULT_TP_COLOR
	jr	nz,++_                      ; is transparent?
_:	inc	de
	djnz	-_
	jr	++_                         ; loop for next pixel
_:	ld	(de),a
	inc	de
	djnz	-_                          ; set and loop for next pixel
_:	inc	hl
	dec	c
	jr	nz,----_                    ; loop for width
	ex	de,hl
	ld	iy,0
	add	iy,de                       ; save hl
NoClipSprTransScaledMoveAmt =$+1
	ld	bc,0
	add	hl,bc                       ; get next draw location
	ex	de,hl
	pop	hl
	dec	ixl                         ; loop height scale
	jr	nz,-----_
	lea	hl,iy                       ; restore hl
	dec	ixh                         ; loop height
	jr	nz,------_
	pop	ix                          ; restore ix sp
	ret

;-------------------------------------------------------------------------------
_TransparentSprite:
; Draws a transparent sprite with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	push	ix                          ; save ix sp
	call	_ClipDraw_ASM \.r
	pop	ix                          ; restore ix sp
	ret	nc
	ld	(ClipSprTransNextAmt),a \.r
	ld	a,(iy+0)                    ; tmpWidth
	ld	(ClipSprTransNextLine),a \.r
	ld	a,(iy+3)                    ; tmpHeight
	ld	h,lcdWidth/2
	mlt	hl
	ld	bc,0                        ; zero ubc
	add	hl,hl
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+6)                   ; hl -> sprite data
	pop	iy
	push	ix
	ld	ixh,a
TColor_SMC_1 =$+1
	ld	a,DEFAULT_TP_COLOR
ClipSprTransNextLine =$+1
_:	ld	c,0
	lea	de,iy
	call	_TransparentPlot_ASM \.r    ; call the transparent routine
ClipSprTransNextAmt =$+1
	ld	c,0
	add	hl,bc
	ld	de,lcdWidth                 ; move to next row
	add	iy,de
	dec	ixh
	jr	nz,-_
	pop	ix
	ret

_TransparentPlot_ASM_Opaque:                ; routine to handle transparent plotting
	ldi
	ret	po
	cp	a,(hl)
	jr	z,_TransparentPlot_ASM_Transparent
	ldi
	ret	po
	cp	a,(hl)
	jr	z,_TransparentPlot_ASM_Transparent
	ldi
	ret	po
	cp	a,(hl)
	jr	z,_TransparentPlot_ASM_Transparent
	ldi
	ret	po
	cp	a,(hl)
	jr	nz,_TransparentPlot_ASM_Opaque
_TransparentPlot_ASM_Transparent:
	inc	de
	inc	hl
	dec	c
	ret	z
_TransparentPlot_ASM:
	cp	a,(hl)
	jr	nz,_TransparentPlot_ASM_Opaque
	inc	de
	inc	hl
	dec	c
	ret	z
	cp	a,(hl)
	jr	nz,_TransparentPlot_ASM_Opaque
	inc	de
	inc	hl
	dec	c
	ret	z
	cp	a,(hl)
	jr	nz,_TransparentPlot_ASM_Opaque
	inc	de
	inc	hl
	dec	c
	ret	z
	cp	a,(hl)
	jr	z,_TransparentPlot_ASM_Transparent
	jr	_TransparentPlot_ASM_Opaque

;-------------------------------------------------------------------------------
_Sprite:
; Places an sprite on the screen as fast as possible with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
;  arg3 : Width -- 8bits
;  arg4 : Height -- 8bits
; Returns:
;  None
	push	ix                          ; save ix sp
	call	_ClipDraw_ASM \.r
	pop	ix                          ; restore ix sp
	ret	nc
	ld	(ClipSprNextAmt),a \.r
	ld	a,(iy+0)                    ; a = tmpWidth
	ld	(ClipSprLineNext),a \.r
	ld	a,(iy+3)                    ; a = tmpHeight
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+6)                   ; hl -> sprite data
	pop	iy
	ld	bc,0
ClipSprLineNext =$+1
_:	ld	c,0
	lea	de,iy
	ldir
	ld	de,lcdWidth
	add	iy,de
ClipSprNextAmt =$+1
	ld	c,0
	add	hl,bc                       ; move to next line
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_Sprite_NoClip:
; Places an sprite on the screen as fast as possible
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(currDrawBuffer)
	ld	bc,(iy+6)			;  x coordinate
	add	hl,bc
	ld	d,lcdWidth/2
	ld	e,(iy+9)			;  y coordinate
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl				; de = start draw location
	ld	hl,(iy+3)			; hl = sprite structure
	ld	c,(hl)				; spriteWidth
	inc	hl
	ld	iyh,c
	xor	a,a
	ld	b,a
	srl	c
	sbc	a,SprNcJrStep-SprNcLpEvenW
	ld	(SprNcJrStep-1),a \.r
	ld	a,lcdWidth/2
	sub	a,c
	ld	iyl,a				; (lcdWidth/2)-(spriteWidth/2)
	ld	a,(hl)				; spriteHeight
	inc	hl
	jr	SprNcLpStart
SprNcLpOddW:
	dec	de				; needed if sprite width is odd
SprNcLpEvenW:
	ld	c,iyl				; (lcdWidth/2)-(spriteWidth/2)
	ex	de,hl
	add	hl,bc
	add	hl,bc
	ex	de,hl
SprNcLpStart:
	ld	c,iyh				; spriteWidth
	ldir
	dec	a
	jr	nz,SprNcLpOddW
SprNcJrStep:
	ret

;-------------------------------------------------------------------------------
_GetSprite:
; Grabs the data from the current draw buffer and stores it in another buffer
; Arguments:
;  arg0 : Pointer to storage buffer
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  Pointer to resultant sprite
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)                   ; bc = y coordinate
	bit	0,b                         ; check if negative y
	ld	b,lcdWidth/2
	mlt	bc
	ld	hl,(currDrawBuffer)
	add	hl,bc
	add	hl,bc                       ; hl -> place to begin drawing
	jr	z,_
	ld	de,-lcdWidth*256
	add	hl,de                       ; fix if negative
_:	ld	de,(iy+6)
	add	hl,de
	ld	de,(iy+3)
	push	de
	ld	a,(de)
	inc	de
	ld	(GetSprCpyAmt),a \.r        ; amount to copy per line
	ld	c,a
	ld	a,lcdWidth&$ff
	sub	a,c
	ld	c,a
	sbc	a,a
	inc	a
	ld	b,a                         ; the amount to add to get to the next line
	ld	(GetSprLineOff),bc \.r
	ld	a,(de)
	inc	de
GetSprCpyAmt =$+1
_:	ld	bc,0
	ldir                                ; copy the data into the struct data
GetSprLineOff =$+1
	ld	bc,0
	add	hl,bc
	dec	a
	jr	nz,-_
	pop	hl
	ret

;-------------------------------------------------------------------------------
_TransparentSprite_NoClip:
; Draws a transparent sprite to the current buffer
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X coordinate
;  arg2 : Y coordinate
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)                   ; hl = x coordinate
	ld	c,(iy+9)                    ; c = y coordinate
	ld	iy,(iy+3)                   ; iy -> sprite struct
	ld	de,(currDrawBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc                       ; hl -> place to draw
	push	hl
	ld	a,(iy+0)
	ld	(NoClipSprTransNextLine),a \.r
	ld	a,(iy+1)
	lea	hl,iy+2
	pop	iy
	push	ix
	ld	ixh,a                       ; ixh = height of sprite
	ld	b,0                         ; zero mid byte
	ld	a,DEFAULT_TP_COLOR
TColor_SMC_3 =$-1
_:	ld	c,0
NoClipSprTransNextLine =$-1
	lea	de,iy
	call	_TransparentPlot_ASM \.r    ; call the plotter
	ld	de,lcdWidth
	add	iy,de
	dec	ixh                         ; loop for height
	jr	nz,-_
	pop	ix                          ; restore stack pointer
	ret

;-------------------------------------------------------------------------------
_ClipDraw_ASM:
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
	ld	ix,6                        ; get pointer to arguments
	lea	iy,ix-6
	add	ix,sp
	ld	hl,(ix+3)
	ld	a,(hl)
	ld	de,tmpWidth \.r
	ld	(de),a                      ; save tmpWidth
	ld	(tmpSpriteWidth),a \.r      ; save tmpSpriteWidth
	add	iy,de
	inc	hl
	ld	a,(hl)
	ld	(iy+3),a                    ; save tmpHeight
	inc	hl
	ld	(iy+6),hl                   ; save a ptr to the sprite data to change offsets
	ld	bc,(ix+9)
	ld	hl,(_ymin) \.r
	mIsHLLessThanBC()
	jr	c,NoTopClipNeeded_ASM
	ld	hl,(iy+3)
	add	hl,bc
	ex	de,hl
	ld	hl,(_ymin) \.r
	mIsHLLessThanDE()
	ret	nc                          ; bc = y location
	ld	hl,(_ymin) \.r              ; ymin
	or	a,a
	sbc	hl,bc
	ld	a,(iy+3)
	sub	a,l
	ld	(iy+3),a
	ld	h,(iy+0)                    ; h = tmpWidth
	mlt	hl                          ; hl = amount of lines clipped off
	ld	de,(iy+6)                   ; de -> sprite data
	add	hl,de
	ld	(iy+6),hl                   ; store new ptr
	ld	bc,(_ymin) \.r              ; new y location ymin
NoTopClipNeeded_ASM:
	push	bc
	pop	hl                          ; hl = y coordinate
	ld	de,(_ymax) \.r
	mIsHLLessThanDE()
	ret	nc                          ; return if offscreen on bottom
	                                    ; bc = y coordinate
	ld	hl,(iy+3)                   ; hl = tmpHeight
	add	hl,bc
	ld	de,(_ymax) \.r
	mIsHLLessThanDE()
	jr	c,NoBottomClipNeeded_ASM    ; is partially clipped bottom?
	ex	de,hl                       ; hl = ymax
	                                    ; bc = y coordinate
	sbc	hl,bc
	ld	(iy+3),hl                   ; store new tmpHeight
NoBottomClipNeeded_ASM:
	ld	hl,(ix+6)                   ; hl = x coordinate
	ld	de,(_xmin) \.r
	mIsHLLessThanDE()
	ld	hl,(ix+6)                   ; hl = x coordinate
	jr	nc,NoLeftClip_ASM           ; is partially clipped left?
	ld	de,(iy+0)                   ; de = tmpWidth
	add	hl,de
	ld	de,(_xmin) \.r
	ex	de,hl
	mIsHLLessThanDE()
	ret	nc                          ; return if offscreen
	ld	de,(ix+6)                   ; de = x coordinate
	ld	hl,(_xmin) \.r
	or	a,a
	sbc	hl,de
	ex	de,hl                       ; calculate new offset
	ld	hl,(iy+6)                   ; hl -> sprite data
	add	hl,de
	ld	(iy+6),hl                   ; save new ptr
	ld	hl,(iy+0)                   ; hl = tmpWidth
	or	a,a
	sbc	hl,de
	ld	(iy+0),hl                   ; save new width
	ld	hl,(_xmin) \.r
	ld	(ix+6),hl                   ; save min x coordinate
NoLeftClip_ASM:
	ld	de,(_xmax) \.r              ; de = xmax
	mIsHLLessThanDE()
	ret	nc                          ; return if offscreen
	ld	hl,(ix+6)                   ; hl = x coordinate
	ld	de,(iy+0)                   ; de = tmpWidth
	add	hl,de
	ld	de,(_xmax) \.r
	ex	de,hl
	mIsHLLessThanDE()
	jr	nc,NoRightClip_ASM          ; is partially clipped right?
	ld	hl,(_xmax) \.r              ; clip on the right
	ld	de,(ix+6)
	ccf
	sbc	hl,de
	ld	(iy+0),hl                   ; save new tmpWidth
NoRightClip_ASM:
	ld	a,(iy+3)
	or	a,a
	ret	z                           ; quit if new tmpHeight is 0 (edge case)
tmpSpriteWidth =$+1
	ld	a,0
	ld	de,(ix+6)                   ; de = x coordinate
	ld	l,c                         ; l = y coordinate
	sub	a,(iy+0)                    ; compute new x width
	scf                                 ; set carry for success
	ret

;-------------------------------------------------------------------------------
_TransparentTilemap_NoClip:
; Tilemapping subsection
	ld	hl,_TransparentSprite_NoClip \.r
	jr	+_
;-------------------------------------------------------------------------------
_Tilemap_NoClip:
; Tilemapping subsection
	ld	hl,_Sprite_NoClip \.r
	jr	+_
;-------------------------------------------------------------------------------
_TransparentTilemap:
; Tilemapping subsection
	ld	hl,_TransparentSprite \.r
	jr	+_
;-------------------------------------------------------------------------------
_Tilemap:
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
t_data        .equ 0
t_type_width  .equ 10
t_type_height .equ 11
t_height      .equ 12
t_width       .equ 13
t_tile_height .equ 6
t_tile_width  .equ 7
t_draw_height .equ 8
t_draw_width  .equ 9
t_x_loc       .equ 15

x_offset      .equ 9
y_offset      .equ 12
	ld	hl,_Sprite \.r
_:	ld	(DrawTile_SMC),hl \.r
	push	ix
	ld	ix,0
	lea	bc,ix
	add	ix,sp
	lea	hl,ix-12
	ld	sp,hl
	ld	iy,(ix+6)                   ; iy -> tilemap structure

	ld	hl,(ix+y_offset)
	ld	c,(iy+t_tile_height)
	ld	a,(iy+t_type_height)
	or	a,a
	jr	nz,_height_is_pow2
	call	__idvrmu
	ex	de,hl
	push	de
	pop	bc
	jr	_height_is_not_pow2
_height_is_pow2:                            ; compute as power of 2 height using shifts
	ld	b,a
	dec	c
	ld	a,l
	and	a,c
	ld	c,a
_:	srl	h
	rr	l
	djnz	-_
_height_is_not_pow2:
	ld	(ix-4),l                    ; y = y_offset / tilemap->tile_height
	ld	(ix+y_offset),bc            ; y_offset = y_offset % tilemap->tile_height;

	ld	c,(iy+t_tile_width)
	ld	hl,(ix+x_offset)            ; x offset
	ld	a,(iy+t_type_width)
	or	a,a
	jr	nz,_width_is_pow2
	call	__idvrmu
	ex	de,hl
	push	de
	pop	bc
	jr	_width_is_not_pow2
_width_is_pow2:
	ld	b,a
	dec	c
	ld	a,l
	and	a,c
	ld	c,a
_:	srl	h
	rr	l
	djnz	-_
_width_is_not_pow2:
	ld	a,l
	ld	(x_res_smc),a \.r
	ld	hl,(iy+t_x_loc)
	or	a,a
	sbc	hl,bc
	ld	(x_offset_smc),hl \.r       ; x_offset_smc = tilemap->x_loc - x_offset;

	or	a,a
	sbc	hl,hl
	ld	l,(iy+14)
	ld	bc,(ix+y_offset)
	ld	(ix-3),h
	sbc	hl,bc
	ld	(ix-12),hl
	jp	Y_Loop \.r

x_res_smc =$+3
n_8:	ld	(ix-1),0
x_offset_smc =$+1
	ld	hl,0
	ld	(ix-7),hl
	ld	l,(iy+t_width)
	ld	h,(ix-4)
	mlt	hl
	ld	(y_next_smc),hl \.r
	xor	a,a
	jr	X_Loop

_xLoop_inner:
	or	a,a
	sbc	hl,hl
	ld	l,(ix-1)
	ld	bc,(iy+t_data)              ; iy -> tilemap data
	add	hl,bc
y_next_smc =$+1
	ld	bc,0
	add	hl,bc
	ld	a,(hl)
	ld	l,a
	inc	a
	jr	z,BlankTile
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
DrawTile_SMC =$+1
	call	0                           ; call sprite drawing routine
	lea	hl,ix-12
	ld	sp,hl
BlankTile:
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

X_Loop:
	ld	(ix-2),a
	cp	a,(iy+t_draw_width)
	jr	nz,_xLoop_inner
	ld	h,0
	ld	l,(iy+6)
	ld	bc,(ix-12)
	add	hl,bc
	ld	(ix-12),hl
	inc	(ix-4)
	inc	(ix-3)

Y_Loop:
	ld	a,(iy+t_draw_height)
	cp	a,(ix-3)
	jp	nz,n_8 \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_TilePtr:
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
	ld	hl,(ix+x_offset)
	ld	a,(iy+t_type_width)
	or	a,a
	jr	nz,+_
	ld	bc,0
	ld	c,(iy+t_tile_width)
	call	__idvrmu
	ex	de,hl
	jr	_width_no_pow2
_:	ld	b,a
_:	srl	h
	rr	l
	djnz	-_
_width_no_pow2:
	ex	de,hl
	ld	hl,(ix+y_offset)
	ld	a,(iy+t_type_height)
	or	a,a
	jr	nz,+_
	ld	bc,0
	ld	c,(iy+t_tile_height)
	push	de
	call	__idvrmu
	ex	de,hl
	pop	de
	jr	_height_no_pow2
_:	ld	b,a
_:	srl	h
	rr	l
	djnz	-_
_height_no_pow2:
	ld	h,(iy+t_width)
	mlt	hl
	add	hl,de
	ld	de,(iy+t_data)
	add	hl,de
	pop	ix
	ret

;-------------------------------------------------------------------------------
_TilePtrMapped:
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
	push	bc
	push	bc
	ld	h,(iy+13)		; tilemap width
	mlt	hl
	ld	b,0
	add.s	hl,bc
	ld	bc,(iy+0)		; tilemap data
	add	hl,bc
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
_GetTextX:
; Gets the X position of the text cursor
; Arguments:
;  None
; Returns:
;  X Text cursor posistion
	ld	hl,(TextXPos_SMC) \.r       ; return x pos
	ret

;-------------------------------------------------------------------------------
_GetTextY:
; Gets the Y position of the text cursor
; Arguments:
;  None
; Returns:
;  Y Text cursor posistion
	ld	hl,(TextYPos_SMC) \.r       ; return y pos
	ret

;-------------------------------------------------------------------------------
_SetTextBGColorC:
; Sets the background text color for text routines
; Arguments:
;  arg0 : Color index to set BG to
; Returns:
;  Previous text color palette index
	pop	de
	ex	(sp),hl
	ld	a,l
	ld	hl,TBGColor_SMC_1 \.r
	ld	c,(hl)                      ; c = old bg color
	ld	(hl),a
	ld	(TBGColor_SMC_2),a \.r
	ld	(TBGColor_SMC_3),a \.r
	ld	a,c
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
_SetTextFGColorC:
; Sets the foreground text color for text routines
; Arguments:
;  arg0 : Color index to set FG to
; Returns:
;  Previous text color palette index
	pop	de
	ex	(sp),hl
	ld	a,l
	ld	hl,TFGColor_SMC_1 \.r
	ld	c,(hl)                      ; c = old fg color
	ld	(hl),a                      ; a = new fg color
	ld	(TFGColor_SMC_2),a \.r
	ld	(TFGColor_SMC_3),a \.r
	ld	a,c
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
_SetTextTransparentColorC:
; Sets the transparency text color for text routines
; Arguments:
;  arg0 : Color index to set transparent text to
; Returns:
;  Previous text color palette index
	pop	de
	ex	(sp),hl
	ld	a,l
	ld	hl,TTPColor_SMC_1 \.r
	ld	c,(hl)                      ; c = old transparent color
	ld	(hl),a                      ; a = new transparent color
	ld	(TTPColor_SMC_2),a \.r
	ld	(TTPColor_SMC_3),a \.r
	ld	a,c
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
_SetTextXY:
; Sets the text X and Y positions
; Arguments:
;  arg0 : Text X Pos
;  arg1 : Text Y Pos
; Returns:
;  None
	pop	de			; de=return address, sp=&xpos
	pop	hl			; hl=xpos, sp=&ypos
	ld	(TextXPos_SMC),hl \.r
	ex	(sp),hl			; hl=ypos, ypos=don't care
	ld	(TextYPos_SMC),hl \.r
	push	hl			; xpos=don't care, sp=&xpos
	ex	de,hl			; hl=return address
;-------------------------------------------------------------------------------
_indcallHL_ASM:
; Calls HL
; Inputs:
;  HL : Address to call
	jp	(hl)

;-------------------------------------------------------------------------------
_PrintStringXY_Clip_ASM:
; Places a string at the given coordinates
; Arguments:
;  arg0 : Pointer to string
;  arg1 : Text X Pos
;  arg2 : Text Y Pos
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	de,(hl)
	push	de
	inc	hl
	inc	hl
	inc	hl
	ld	de,TextXPos_SMC \.r
	ldi
	ldi
	ldi                                 ; copy in the y location
	ld	hl,(hl)
	ld	(TextYPos_SMC),hl \.r       ; set new y pos
	pop	hl
	jr	NextCharLoop                ; jump to the main string handler

;-------------------------------------------------------------------------------
_PrintStringXY:
; Places a string at the given coordinates
; Arguments:
;  arg0 : Pointer to string
;  arg1 : Text X Pos
;  arg2 : Text Y Pos
; Returns:
;  None
	jp	_PrintStringXY_ASM \.r
PrintStringXY_SMC =$-3
_PrintStringXY_ASM:
	ld	hl,9
	add	hl,sp
	ld	a,(hl)
	ld	(TextYPos_SMC),a \.r
	dec	hl
	dec	hl
	ld	de,TextXPos_SMC+1 \.r
	ldd
	ldd
	dec	hl
	dec	hl
	ld	hl,(hl)
	jr	NextCharLoop

;-------------------------------------------------------------------------------
_PrintString:
; Places a string at the current cursor position
; Arguments:
;  arg0 : Pointer to string
; Returns:
;  None
	pop	de
	pop	hl
	push	hl
	push	de
NextCharLoop:
	ld	a,(hl)                      ; get the current character
	or	a,a
	ret	z
	call	_PrintChar_ASM \.r
PrintChar_SMC_3 =$-3
	inc	hl                          ; move to the next one
	jr	NextCharLoop

;-------------------------------------------------------------------------------
_SetTextScale:
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
	ld	de,TextWidthScale_SMC \.r
	ld	hl,LargeFontJump_SMC \.r
	cp	a,c
	jr	z,AreTheSame
	jr	NotTheSame
AreTheSame:
	dec	a
	jr	z,BothAreOne                ; if they are both one; just use normal drawing
	inc	a
NotTheSame:
	or	a,a
	ret	z                           ; null check
	ld	(de),a
	ld	a,c
	or	a,a
	ret	z                           ; null check
	ld	(TextHeightScale_SMC),a \.r
	ld	(hl),0                      ; modified at boot to SM the jump
UseLargeFont_SMC =$-1
	ret
BothAreOne:
	ld	(hl),a                      ; store a 0, which means no (literal) jump
	inc	a
	ld	(de),a
	ret

;-------------------------------------------------------------------------------
; Definitions for gfx_SetTextConfig
#define TEXT_CLIP   1
#define TEXT_NOCLIP 2
;-------------------------------------------------------------------------------
_SetTextConfig:
; Configures text depending on the arguments
; Arguments:
;  arg0 : Configuration numbers
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,e                         ; a = argument
	dec	a                           ; TEXT_CLIP
	jr	z,SetClipText
	dec	a                           ; TEXT_NOCLIP
	ret	nz
	ld	de,_PrintChar_ASM \.r
	ld	bc,_PrintStringXY_ASM \.r
	jr	SetCharSMC                  ; set unclipped character routine
SetClipText:
	ld	de,_PrintChar_Clip_ASM \.r
	ld	bc,_PrintStringXY_Clip_ASM \.r
SetCharSMC:
	ld	hl,PrintChar_SMC_0 \.r
	ld	(hl),de                     ; holy crap what a hack
	ld	hl,PrintChar_SMC_1 \.r
	ld	(hl),de
	ld	hl,PrintChar_SMC_2 \.r
	ld	(hl),de
	ld	hl,PrintChar_SMC_3 \.r
	ld	(hl),de                     ; modify all the interal routines to use the clipped text routine
	push	bc
	pop	hl
	ld	(PrintStringXY_SMC),hl \.r ; change which text routines we want to use
	or	a,a
	sbc	hl,hl
	ld	(TextYPos_SMC),hl \.r
	ld	(TextXPos_SMC),hl \.r       ; reset the current posistions
	ret

;-------------------------------------------------------------------------------
_PrintChar:
; Places a character at the current cursor position
; Arguments:
;  arg0 : Character to draw
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,e                         ; a = char
	jp	_PrintChar_ASM \.r          ; this is SMC'd to use as a grappling hook into the clipped version
PrintChar_SMC_0 =$-3
_PrintChar_ASM:
	push	ix                          ; save stack pointer
	push	hl                          ; save hl pointer if string
	ld	e,a                         ; e = char
FixedWidthFont_SMC =$+1
	ld	a,0
	or	a,a
	jr	nz,HasFixedWidth
	sbc	hl,hl
	ld	l,e                         ; hl = character
	ld	bc,(CharSpacing_ASM) \.r
	add	hl,bc
	ld	a,(hl)                      ; a = char width
HasFixedWidth:
TextXPos_SMC = $+1
	ld	bc,0
	sbc	hl,hl
	ld	l,a
	ld	ixh,a                       ; ixh = char width
	ld	a,(TextWidthScale_SMC) \.r
	ld	h,a
	mlt	hl
	add	hl,bc
	ld	(TextXPos_SMC),hl \.r
TextYPos_SMC = $+1
	ld	hl,0
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,bc
	ld	bc,(currDrawBuffer)
	add	hl,bc
	ex	de,hl                       ; de = draw location
	ld	a,l                         ; l = character
	sbc	hl,hl
	ld	l,a                         ; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(TextData_ASM) \.r       ; get text data array
	add	hl,bc
	ld	iy,0
FONT_HEIGHT_SMC_3 =$+2
	ld	ixl,8
	jr	_PrintLargeFont_ASM         ; SMC the jump
LargeFontJump_SMC =$-1
CharLoop:
	ld	c,(hl)                      ; c = 8 pixels
	add	iy,de                       ; get draw location
	lea	de,iy
	ld	b,ixh
NextPixel:
	ld	a,DEFAULT_TEXT_BG_COLOR
TBGColor_SMC_1 =$-1
	rlc	c
	jr	nc,IsBGColor
	ld	a,DEFAULT_TEXT_FG_COLOR
TFGColor_SMC_1 =$-1
IsBGColor:
	cp	a,DEFAULT_TEXT_TP_COLOR     ; check if transparent
TTPColor_SMC_1 =$-1
	jr	z,IsTransparent
	ld	(de),a
IsTransparent:
	inc	de                          ; move to next pixel
	djnz	NextPixel
	ld	de,lcdwidth
	inc	hl
	dec	ixl
	jr	nz,CharLoop
	pop	hl                          ; restore hl and stack pointer
	pop	ix
	ret

;-------------------------------------------------------------------------------
_PrintLargeFont_ASM:
; Prints in scaled font for prosperity
; This is so that way unscaled font can still be reasonably fast
; Returns:
;  None
LargeFontLoop:
	ld	b,1
TextHeightScale_SMC =$-1
	push	hl
	ld	c,(hl)                      ; c = 8 pixels
HScale:
	push	bc
	add	iy,de                       ; get draw location
	lea	de,iy
	ld	b,ixh
_:	ld	a,DEFAULT_TEXT_BG_COLOR
TBGColor_SMC_3 =$-1
	ld	l,1
TextWidthScale_SMC =$-1
	rlc	c
	jr	nc,+_
	ld	a,DEFAULT_TEXT_FG_COLOR
TFGColor_SMC_3 =$-1
_:	cp	a,DEFAULT_TEXT_TP_COLOR     ; check if transparent
TTPColor_SMC_2 =$-1
	jr	z,+_

WScale1:
	ld	(de),a
	inc	de
	dec	l
	jr	nz,WScale1
	djnz	--_
	jr	CharDone
_:
WScale2:
	inc	de
	dec	l
	jr	nz,WScale2                  ; move to next pixel
	djnz	---_
CharDone:
	ld	de,lcdWidth

	pop	bc
	djnz	HScale

	pop	hl
	inc	hl
	dec	ixl
	jr	nz,LargeFontLoop
	pop	hl                          ; restore hl and stack pointer
	pop	ix
	ret

;-------------------------------------------------------------------------------
_PrintChar_Clip_ASM:
; Clipped text for characters printing routine
; Arguments:
;  arg0 : Character to draw
; Returns:
;  None
	push	hl                          ; save hl pointer if string

	ld	e,a                         ; e = char

	ld	a,(FixedWidthFont_SMC) \.r
	or	a,a
	jr	nz,CHasFixedWidth
	sbc	hl,hl
	ld	l,e                         ; hl = character
	ld	bc,(CharSpacing_ASM) \.r
	add	hl,bc
	ld	a,(hl)                      ; a = char width
CHasFixedWidth:
	or	a,a
	sbc	hl,hl
	ld	l,e                         ; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(TextData_ASM) \.r       ; get text data array
	add	hl,bc                       ; de = draw location
	ld	de,tmpCharData \.r          ; store pixel data into temporary sprite
FONT_HEIGHT_SMC_2 =$+2
	ld	iyl,8
	ld	iyh,a                       ; ixh = char width
	ld	(tmpCharDataSprite),a \.r   ; store width of character we are drawing
	call	GetChar_ASM \.r             ; store the character data
	ld	bc,(TextYPos_SMC) \.r
	push	bc
	ld	bc,(TextXPos_SMC) \.r       ; compute the new locations
	push	bc
	or	a,a
	sbc	hl,hl
	ld	a,iyh
	ld	l,a
	add	hl,bc
	ld	(TextXPos_SMC),hl \.r       ; move the text x posisition by the character width
	ld	bc,tmpCharDataSprite \.r
	push	bc
	call	_TransparentSprite \.r
	pop	bc
	pop	bc
	pop	bc

	pop	hl                          ; restore hl and stack pointer
	ret

;-------------------------------------------------------------------------------
_PrintUInt:
; Places an unsigned int at the current cursor position
; Arguments:
;  arg0 : Number to print
;  arg1 : Number of characters to print
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)                   ; hl = uint
	ld	c,(iy+6)                    ; c = num chars
_PrintUInt_ASM:
	ld	a,8
	sub	a,c
	ret	c                           ; make sure less than 8
	rla
	rla
	rla
	ld	(Offset_SMC),a \.r          ; select the jump we need
Offset_SMC =$+1
	jr	$
	ld	bc,-10000000
	call	Num1 \.r
	ld	bc,-1000000
	call	Num1 \.r
	ld	bc,-100000
	call	Num1 \.r
	ld	bc,-10000
	call	Num1 \.r
	ld	bc,-1000
	call 	Num1 \.r
	ld	bc,-100
	call	Num1 \.r
	ld	bc,-10
	call	Num1 \.r
	ld	bc,-1
Num1:	ld	a,'0'-1
Num2:	inc	a
	add	hl,bc
	jr	c,Num2
	sbc	hl,bc
	jp	_PrintChar_ASM \.r          ; print the actual character needed
PrintChar_SMC_1 =$-3

;-------------------------------------------------------------------------------
_PrintInt:
; Places an int at the current cursor position
; Arguments:
;  arg0 : Number to print
;  arg1 : Number of characters to print
; Returns:
;  None
	ld	iy,0
	lea	bc,iy
	add	iy,sp
	ld	c,(iy+6)                    ; c = num chars
	ld	hl,(iy+3)                   ; hl = int
	bit	7,(iy+5)                    ; if negative
	jr	z,+_
	push	bc
	push	hl
	pop	bc
	sbc	hl,hl
	sbc	hl,bc
	ld	a,'-'
	call	_PrintChar_ASM \.r          ; place negative symbol
PrintChar_SMC_2 =$-3
	pop	bc
_:	jp	_PrintUInt_ASM \.r          ; handle integer

;-------------------------------------------------------------------------------
_GetStringWidth:
; Gets the width of a string
; Arguments:
;  arg0 : Pointer to string
; Returns:
;  Width of string in pixels
	pop	de
	pop	hl
	push	hl                          ; hl -> string
	push	de
	ld	de,0
_:	ld	a,(hl)
	or	a,a
	jr	z,+_                        ; loop until null byte
	push	hl
	call	_GetCharWidth_ASM \.r
	ex	de,hl
	pop	hl
	inc	hl
	jr	-_
_:	ex	de,hl                       ; return width of string
	ret

;-------------------------------------------------------------------------------
_GetCharWidth:
; Gets the width of a character
; Arguments:
;  arg0 : Character
; Returns:
;  Width of character in pixels
	ld	iy,0
	lea	de,iy
	add	iy,sp
	ld	a,(iy+3)                    ; a = character
_GetCharWidth_ASM:
	sbc	hl,hl
	ld	l,a
	ld	a,(FixedWidthFont_SMC) \.r  ; is fixed width
	or	a,a
	jr	nz,IsFixedMono
	ld	bc,(CharSpacing_ASM) \.r    ; lookup spacing
	add	hl,bc
	ld	a,(hl)
IsFixedMono:
	ld	l,a
	ld	a,(TextWidthScale_SMC) \.r  ; add scaling factor
	ld	h,a
	mlt	hl
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_GetSpriteChar:
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
	ld	a,(FixedWidthFont_SMC) \.r
	or	a,a
	jr	nz,GetHasFixedWidth
	sbc	hl,hl
	ld	l,e                         ; hl = character
	ld	bc,(CharSpacing_ASM) \.r
	add	hl,bc
	ld	a,(hl)                      ; a = char width
GetHasFixedWidth:
	or	a,a
	sbc	hl,hl
	ld	l,e                         ; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(TextData_ASM) \.r       ; get text data array
	add	hl,bc                       ; de = draw location
	ld	de,tmpCharDataSprite \.r
	ex	de,hl
	push	hl                          ; save pointer to sprite
FONT_HEIGHT_SMC_1 =$+2
	ld	a,8
	ld	iyh,a                       ; ixh = char width
	ld	(hl),a                      ; store width of character we are drawing
	inc	hl
	ld	iyl,a                       ; height of char
	inc	hl
	ex	de,hl
	call	GetChar_ASM \.r             ; read the character into the array
	pop	hl
	ret

;-------------------------------------------------------------------------------
GetChar_ASM:
; Places a character data into a nice buffer
; Inputs:
;  HL : Points to character pixmap
;  DE : Points to output buffer
; Outputs:
;  Stored pixmap image
;  Uses IY
GetCharLoop:
	ld	c,(hl)                      ; c = 8 pixels (or width based)
	ld	b,iyh
GetNextPixel:
	ld	a,DEFAULT_TEXT_BG_COLOR
TBGColor_SMC_2 =$-1
	rlc	c
	jr	nc,GetIsBGColor
	ld	a,DEFAULT_TEXT_FG_COLOR
TFGColor_SMC_2 =$-1
GetIsBGColor:
	cp	a,DEFAULT_TEXT_TP_COLOR     ; check if transparent
TTPColor_SMC_3 =$-1
	jr	z,GetIsTransparent
	ld	(de),a
	inc	de
	djnz	GetNextPixel
	inc	hl
	dec	iyl
	jr	nz,GetCharLoop
	ret
GetIsTransparent:
	ld	a,0
TColor_SMC_4 =$-1
	ld	(de),a
	inc	de                          ; move to next pixel
	djnz	GetNextPixel
	inc	hl
	dec	iyl
	jr	nz,GetCharLoop              ; okay we stored the character sprite now draw it
	ret

;-------------------------------------------------------------------------------
_SetFontHeight:
; Sets the height of the font in pixels
; Arguments:
;  arg0 : New font height
; Returns:
;  Previous font height
	pop	hl
	pop	de
	push	de
	push	hl
	ld	hl,FONT_HEIGHT_SMC_1 \.r
	ld	a,(hl)                      ; a = old height
	ld	(hl),e
	ld	hl,FONT_HEIGHT_SMC_2 \.r
	ld	(hl),e
	ld	hl,FONT_HEIGHT_SMC_3 \.r
	ld	(hl),e                      ; store new height
	ret

;-------------------------------------------------------------------------------
_SetFontData:
; Sets the font to be custom
; Arguments:
;  arg0 : Pointer to font data
;  Set Pointer to NULL to use default font
; Returns:
;  None
	pop	de
	pop	hl
	push	hl                          ; hl -> custom font data
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	nz,+_                       ; if null make default font
	ld	hl,Char000 \.r
_:	ld	(TextData_ASM),hl \.r       ; save pointer to custom font
	ret

;-------------------------------------------------------------------------------
_SetFontSpacing:
; Sets the font to be custom spacing
; Arguments:
;  arg0 : Pointer to font spacing
;  Set Pointer to NULL to use default font spacing
; Returns:
;  None
	pop	de
	pop	hl
	push	hl                          ; hl -> custom font width
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	nz,+_                       ; if null make default font width
	ld	hl,DefaultCharSpacing_ASM \.r
_:	ld	(CharSpacing_ASM),hl \.r    ; save pointer to custom widths
	ret

;-------------------------------------------------------------------------------
_SetMonospaceFont:
; Sets the font to be monospace
; Arguments:
;  arg0 : Monospace spacing amount
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,e                         ; a = width
	ld	(FixedWidthFont_SMC),a \.r  ; store the value of the monospace width
	ret

;-------------------------------------------------------------------------------
_FillTriangle_NoClip:
; Draws a filled triangle without clipping
; Arguments:
;  arg0-5 : x0,y0,x1,y1,x2,y2
; Returns:
;  None
	ld	hl,_HorizLine_NoClip \.r
	jr	+_
;-------------------------------------------------------------------------------
_FillTriangle:
; Draws a filled triangle with clipping
; Arguments:
;  arg0-5 : x0,y0,x1,y1,x2,y2
; Returns:
;  None
	ld	hl,_HorizLine \.r
_:	ld	(HLine0_SMC),hl \.r
	ld	(HLine1_SMC),hl \.r
	ld	(HLine2_SMC),hl \.r
	push	ix
	ld	ix,0
	add	ix,sp
	lea	hl,ix-39
	ld	sp,hl
	sbc	hl,hl
	ld	(ix-15),hl
	ld	(ix-18),hl
	ld	hl,(ix+9)
	ld	de,(ix+15)
	call	_SignedCompare_ASM \.r
	jr	c,+_
	ld	hl,(ix+9)
	ld	(ix+9),de
	ld	(ix+15),hl
	ld	hl,(ix+6)
	ld	de,(ix+12)
	ld	(ix+6),de
	ld	(ix+12),hl
_:	ld	hl,(ix+15)
	ld	de,(ix+21)
	call	_SignedCompare_ASM \.r
	jr	c,+_
	ld	hl,(ix+15)
	ld	(ix+15),de
	ld	(ix+21),hl
	ld	hl,(ix+12)
	ld	de,(ix+18)
	ld	(ix+12),de
	ld	(ix+18),hl
_:	ld	hl,(ix+9)
	ld	de,(ix+15)
	call	_SignedCompare_ASM \.r
	jr	c,+_
	ld	hl,(ix+9)
	ld	(ix+9),de
	ld	(ix+15),hl
	ld	hl,(ix+6)
	ld	de,(ix+12)
	ld	(ix+6),de
	ld	(ix+12),hl
_:	ld	de,(ix+12)
	ld	hl,(ix+18)
	or	a,a
	sbc	hl,de
	ld	(ix-24),hl
	ld	de,(ix+6)
	ld	hl,(ix+12)
	or	a,a
	sbc	hl,de
	ld	(ix-39),hl
	ld	de,(ix+9)
	ld	hl,(ix+15)
	or	a,a
	sbc	hl,de
	ld	(ix-36),hl
	ld	de,(ix+6)
	ld	hl,(ix+18)
	or	a,a
	sbc	hl,de
	ld	(ix-21),hl
	ld	de,(ix+9)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,de
	ld	(ix-30),hl
	ld	de,(ix+15)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,de
	ld	(ix-33),hl
	ld	de,(ix+21)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	jp	nz,t_17 \.r
	ld	hl,(ix+6)
	ld	(ix-6),hl
	ld	(ix-3),hl
	ld	de,(ix+12)
	call	_SignedCompare_ASM \.r
	jr	c,t_8
	ld	(ix-3),de
	jr	t_12
t_8:	ld	hl,(ix+12)
	ld	de,(ix-6)
	call	_SignedCompare_ASM \.r
	jr	c,t_12
	ld	de,(ix+12)
	ld	(ix-6),de
t_12:	ld	hl,(ix-3)
	ld	de,(ix+18)
	call	_SignedCompare_ASM \.r
	jr	c,t_11
	ld	(ix-3),de
	jr	t_13
t_11:	ld	hl,(ix+18)
	ld	de,(ix-6)
	call	_SignedCompare_ASM \.r
	jr	c,t_13
	ld	de,(ix+18)
	ld	(ix-6),de
t_13:	ld	bc,(ix-3)
	ld	de,(ix+9)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,bc
	inc	hl
	push	hl
	push	de
	push	bc
HLine0_SMC =$+1
	call	0
	ld	sp,ix
	pop	ix
	ret
t_17:	ld	de,(ix+21)
	ld	hl,(_ymax) \.r
	or	a,a
	sbc	hl,de
	add	hl,de
	jp	p,t__29 \.r
	jp	pe,t_20 \.r
	jr	t__30
t__29:	jp	po,t_20 \.r
t__30:	ld	(ix+21),hl
t_20:	ld	hl,(ix+15)
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nz,t_19
	ld	(ix-27),hl
	jr	t_27
t_19:	dec	hl
	ld	(ix-27),hl
t_27:	ld	bc,(ix+9)
	ld	(ix-12),bc
	jp	t_26 \.r
t_24:	ld	hl,(ix-15)
	ld	bc,(ix-36)
	call	__idivs_ASM \.r
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix-3),hl
	ld	hl,(ix-18)
	ld	bc,(ix-30)
	call	__idivs_ASM \.r
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix-6),hl
	ex	de,hl
	ld	bc,(ix-39)
	ld	hl,(ix-15)
	add	hl,bc
	ld	(ix-15),hl
	ld	bc,(ix-21)
	ld	hl,(ix-18)
	add	hl,bc
	ld	(ix-18),hl
	ex	de,hl
	ld	de,(ix-3)
	or	a,a
	sbc	hl,de
	add	hl,de
	jp	p,t__31 \.r
	jp	pe,t_23 \.r
	jr	t__32
t__31:	jp	po,t_23 \.r
t__32:	ex	de,hl
	ld	(ix-3),de
	ld	(ix-6),hl
t_23:	ld	de,(ix-3)
	ld	hl,(ix-6)
	or	a,a
	sbc	hl,de
	ld	bc,(ix-12)
	inc	hl
	push	hl
	push	bc
	push	de
HLine1_SMC =$+1
	call	0
	lea	hl,ix-39
	ld	sp,hl
	ld	bc,(ix-12)
	inc	bc
	ld	(ix-12),bc
t_26:	ld	hl,(ix-27)
	or	a,a
	sbc	hl,bc
	jp	p,+_ \.r
	jp	pe,t_24 \.r
	jr	++_
_:	jp	po,t_24 \.r
_:	ld	bc,(ix+15)
	ld	hl,(ix-12)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix-24)
	call	__imuls_ASM \.r
	ld	(ix-15),hl
	ld	bc,(ix+9)
	ld	hl,(ix-12)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix-21)
	call	__imuls_ASM \.r
	ld	(ix-18),hl
	jp	t_34 \.r
t_32:	ld	hl,(ix-15)
	ld	bc,(ix-33)
	call	__idivs_ASM \.r
	ld	bc,(ix+12)
	add	hl,bc
	ld	(ix-3),hl
	ld	hl,(ix-18)
	ld	bc,(ix-30)
	call	__idivs_ASM \.r
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix-6),hl
	ex	de,hl
	ld	bc,(ix-21)
	ld	hl,(ix-18)
	add	hl,bc
	ld	(ix-18),hl
	ld	bc,(ix-24)
	ld	hl,(ix-15)
	add	hl,bc
	ld	(ix-15),hl
	ex	de,hl
	ld	de,(ix-3)
	or	a,a
	sbc	hl,de
	add	hl,de
	jp	p,+_ \.r
	jp	pe,+++_ \.r
	jr	++_
_:	jp	po,+++_ \.r
_:	ex	de,hl
	ld	(ix-3),de
	ld	(ix-6),hl
_:	or	a,a
	sbc	hl,de
	ld	bc,(ix-12)
	inc	hl
	push	hl
	push	bc
	push	de
HLine2_SMC =$+1
	call	0
	lea	hl,ix-39
	ld	sp,hl
	ld	bc,(ix-12)
	inc	bc
	ld	(ix-12),bc
t_34:	ld	bc,(ix-12)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,bc
	jp	p,+_ \.r
	jp	pe,t_32 \.r
	ld	sp,ix
	pop	ix
	ret
_:	jp	po,t_32 \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_Polygon_NoClip:
; Draws a clipped polygon outline
; Arguments:
;  arg0 : Pointer to polygon points
;  arg1 : length of polygon point array
; Returns:
;  None
	ld	hl,_Line_NoClip \.r
	jr	+_
;-------------------------------------------------------------------------------
_Polygon:
; Draws a clipped polygon outline
; Arguments:
;  arg0 : Pointer to polygon points
;  arg1 : length of polygon point array
; Returns:
;  None
	ld	hl,_Line \.r
_:	ld	(LineType0_SMC),hl \.r
	ld	(LineType1_SMC),hl \.r
	push	ix
	ld	ix,0
	add	ix,sp
	ld	sp,hl
	ld	iy,(ix+6)
	jr	StartPolygonLoop
PolygonLoop:
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
LineType0_SMC =$-3
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	lea	iy,iy+6
StartPolygonLoop:
	ld	hl,(ix+9)
	dec	hl
	ld	(ix+9),hl
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	nz,PolygonLoop
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
LineType1_SMC =$-3
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_Reserved:
; Deprecated unused function (available for use)
	ret

;-------------------------------------------------------------------------------
_LZDecompressSprite_Deprecated:
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
	jp	nz,d_16 \.r
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
	call	_LZ_ReadVarSize_ASM \.r
	pop	bc
	pop	bc
	ld	bc,(ix-3)
	add	hl,bc
	ld	(ix-3),hl
	ld	bc,(ix+6)
	add	hl,bc
	push	hl
	pea	ix-23
	call	_LZ_ReadVarSize_ASM \.r
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
	jp	c,d_17 \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_FlipSpriteY:
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
	ld	a,(ix+0)                    ; a = width of sprite
	sbc	hl,hl
	ld	l,a
	ld	c,a
	push	hl
	ld	(FlipHorizWidth_SMC),a \.r
	add	hl,hl
	ld	(FlipHorizDelta_SMC),hl \.r ; width*2
	ld	a,(ix+1)                    ; a = height of sprite
	pop	hl
	lea	de,ix+2
	add	hl,de
	ld	ix,(iy+6)
	ld	(ix+1),a                    ; store height to width
	ld	(ix+0),c                    ; store width to height
	lea	de,ix+2                     ; de -> sprite data
	ex	(sp),ix                     ; restore stack frame
FixupNextLine:
FlipHorizWidth_SMC =$+1
	ld	b,0
	ld	c,a
FixupNextPixel:
	dec	hl
	ld	a,(hl)
	ld	(de),a                      ; store the new pixel data
	inc	de
	djnz	FixupNextPixel
	ld	a,c
FlipHorizDelta_SMC =$+1
	ld	bc,0
	add	hl,bc
	dec 	a
	jr	nz,FixupNextLine
	pop	hl
	ret

;-------------------------------------------------------------------------------
_FlipSpriteX:
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
	ld	(FlipVertDelta_SMC),a \.r
	neg
	ld	(FlipVertWidth_SMC),a \.r
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
FlipVertWidth_SMC =$+1
_:	ld	bc,0
	ldir
FlipVertDelta_SMC =$+1
	ld	bc,-1
	add	hl,bc
	add	hl,bc
	dec 	a
	jr	nz,-_
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
_RotateSpriteC:
; Rotates an array 90 degress clockwise
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	lea	de,iy
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	ld	a,(ix+0)                    ; a = width
	ld	e,(ix+1)                    ; c = height
	ld	(RotateCWidth_SMC),a \.r
	lea	hl,ix+2
	ld	ix,(iy+6)
	ld	(ix+0),e
	ld	(ix+1),a
	lea	iy,ix+1
	add	iy,de
	ld	c,e
	push	ix
RotateCWidth_SMC =$+1
_:	ld	b,0
	lea	ix,iy
_:	ld	a,(hl)
	ld	(iy),a
	inc	hl
	add	iy,de
	djnz	-_
	lea	iy,ix
	dec	iy
	dec 	c
	jr	nz,--_
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
_RotateSpriteCC:
; Rotates a sprite 90 degrees counter clockwise
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	lea	de,iy
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	ld	a,(ix+0)                    ; a = width
	ld	e,(ix+1)                    ; e = height
	ld	(RotateCCWidth_SMC),a \.r
	lea	hl,ix+1
	ld	ix,(iy+6)
	ld	(ix+0),e
	ld	(ix+1),a
	ld	c,e
	ld	b,a
	mlt	bc
	add	hl,bc
	lea	iy,ix+1
	add	iy,de
	ld	c,e
	push	ix
RotateCCWidth_SMC =$+1
_:	ld	b,0
	lea	ix,iy
_:	ld	a,(hl)
	ld	(iy),a
	dec	hl
	add	iy,de
	djnz	-_
	lea	iy,ix
	dec	iy
	dec 	c
	jr	nz,--_
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
_RotateSpriteHalf:
; Rotates an array 180 degrees
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	ld	c,(ix+0)                    ; c = width
	ld	b,(ix+1)                    ; b = height
	lea	de,ix+2
	ld	ix,(iy+6)
	ld	(ix+0),c
	ld	(ix+1),b
	mlt	bc
	lea	hl,ix+1
	add	hl,bc
	push	ix
_:	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	dec	bc
	ld	a,b
	or	a,c
	jr	nz,-_
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
_ScaleSprite:
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
	ld	ixh,a                       ; target_width
	ld	(targetwidth),a \.r
	inc	hl
	xor	a,a
	sub	a,(hl)
	ld	ixl,a                       ; -target_height
	inc	hl
	push	hl                          ; hl->tgt_data
	ld	hl,(iy+3)
	ld	e,(hl)                      ; src_width
	inc	hl
	ld	c,(hl)                      ; src_height
	inc	hl
	push	hl                          ; hl->src_data
	push	de                          ; e = src_width
	call	_UCDivA_ASM \.r             ; ca = dv = (source_height*256)/target_height
	pop	hl                          ; l = src_width
	ld	(dv_shl_16+2),a \.r
	ld	h,c
        ld	c,l
	mlt	hl
	ld	(dv_shr_8_times_width),hl \.r
	add	hl,bc
	ld	(dv_shr_8_times_width_plus_width),hl \.r
	xor	a,a
	sub	a,ixh                       ; -target_width
	call	_UCDivA_ASM \.r             ; ca = du = (source_width*256)/target_width
	pop	hl                          ; hl->src_data
	pop	de                          ; de->tgt_data
	ld	iy,0
	ld	iyl,a
	ld	a,c                         ; du = bc:iyl
	ld	(du),a \.r                  ; ixl = target_height

; b = out_loop_times
; de = target buffer adress
out:
	push	hl
targetwidth =$+2
	ld	iyh, 0
	xor	a,a
	ld	b,a
du =$+1
	ld	c,0
loop:	ldi
	add	a,iyl
	adc	hl,bc                       ; xu += du
	inc	bc                          ; bc:iyl is du
	dec	iyh
	jr	nz,loop
	pop	hl                          ; add up to hla
dv_shl_16 =$+1
	ld	bc,0                        ; dv<<16
	add	iy,bc
dv_shr_8_times_width =$+1
	ld	bc,0                        ; dv>>8*src_width
	jr	nc,+_
dv_shr_8_times_width_plus_width =$+1
	ld	bc,0                        ; dv>>8*src_width+src_width
_:	add	hl,bc
	inc	ixl
	jr	nz,out
	pop	hl
	pop	ix
	ret

_UCDivA_ASM:
	sbc	hl,hl
	ld	h,a
	xor	a,a
	ld	l,a
	ex	de,hl
	sbc	hl,hl
	ld	l,c
	call	+_ \.r
	ld	c,a
_:	ld	b,8
_:	add	hl,hl
	add	hl,de
	jr	c,+_
	sbc	hl,de
_:	rla
	djnz	--_
	ret                                 ; ca = c*256/a, h = c*256%a

;-------------------------------------------------------------------------------
_RotatedScaledSprite_NoClip:
; Rotate and scale an image drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
;  arg2 : Rotation angle as an integer
;  arg3 : Scale factor (64 = 100%)
; Returns:
;  arg1 : Pointer to sprite struct output
	xor	a,a
	jr	_RotatedScaled_ASM
	
;-------------------------------------------------------------------------------
_RotatedScaledTransparentSprite_NoClip:
; Rotate and scale an image drawn directly to the screen buffer
; Arguments:
;  arg0 : Pointer to sprite struct input
;  arg1 : Pointer to sprite struct output
;  arg2 : Rotation angle as an integer
;  arg3 : Scale factor (64 = 100%)
; Returns:
;  arg1 : Pointer to sprite struct output
	ld	a,3
	
_RotatedScaled_ASM:
	ld	(_smc_tp),a \.r
	push	ix
	ld	ix,0
	add	ix,sp
	push	hl
	ld	iy,(ix+6)				; sprite pointer
	lea	hl,iy+2
	ld	(_dsrs_sprptr_0 + 1),hl \.r		; write smc
	
	ld	l,(ix+12)				; y
	ld	h,160
	mlt	hl
	add	hl,hl
	ld	de,(ix+9)				; x
	add	hl,de
	ex	de,hl
	ld	hl,(currDrawBuffer)
	add	hl,de					; offset buffer
	push	hl
	
	; sinf = sinTable[angle] * 128 / scale;
	ld	a,(ix+15)				; angle
	call	getSinCos \.r
	ld	l,0
	ld	h,a
	rlca
	rr	h					; hl = sinTable[angle] * 128
	ld	c,(ix+18)
	ld	b,0
	call	_16Div8Signed \.r			; hl = sinTable[angle] * 128 / scale (sin)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(_dsrs_sinf_1 + 1),hl \.r		; write smc
	push	hl
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	ld	(_dsrs_sinf_0 + 1),hl \.r		; write smc
	pop	hl

	; dxs = sinf * -(size * scale / 128);
	ld	c,(ix+18)
	ld	b,(iy)
	mlt	bc					; size * scale
	rl	c
	rl	b
	ld	c,b					; (size * scale / 128)
	xor	a,a
	sub	a,c
	ld	c,a
	sbc	a,a
	ld	b,a					; -(size * scale / 128)
	ld	(ix-3),bc
	call	_16Mul16SignedNeg \.r			; sinf * -(size * scale / 128)
	ld	(_dsrs_dys_0 + 1),hl \.r		; write smc
	push	hl
	
	; cosf = sinTable[angle + 64] * 128 / scale
	ld	a,64
	add	a,(ix+15)				; angle + 64
	call	getSinCos \.r
	ld	l,0
	ld	h,a
	rlca
	rr	h					; hl = sinTable[angle + 64] * 128
	ld	c,(ix+18)
	ld	b,0
	call	_16Div8Signed \.r			; hl = sinTable[angle + 64] * 128 / scale (cos)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(_dsrs_cosf_0 + 1),hl \.r		; write smc
	ld	(_dsrs_cosf_1 + 1),hl \.r		; write smc

	; dxc = cosf * -(size * scale / 128);
	ld	bc,(ix-3)				; -(size * scale / 128)
	call	_16Mul16SignedNeg \.r			; cosf * -(size * scale / 128)
	ld	(_dsrs_dyc_0 + 1),hl \.r		; write smc
 	push	hl
	
	ld	a,(iy)					; size
	ld	(_dsrs_ssize_1 + 1),a \.r		; write smc
	dec	a
	ld	(_dsrs_ssize_0 + 1),a \.r		; write smc
	inc	a
	ld	b,a
	ld	c,(ix+18)
	mlt	bc					; size * scale
	srl	a					; size / 2
	or	a,a
	sbc	hl,hl
	ld	h,a
	ld	(_dsrs_size128_0 + 1),hl \.r		; write smc
	ld	(_dsrs_size128_1 + 1),hl \.r		; write smc
	ld	a,b
	rl	c
	adc	a,a
	rl	c
	adc	a,a					; size * scale / 64
	jr	nz,+_
	inc	a					; hax for scale = 1?
_:	ld	(_dsrs_size_1 + 2),a \.r		; write smc

 	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	de,lcdWidth
	ex	de,hl
	sbc	hl,de
	ld	(_line_add + 1),hl \.r
	
	pop	de					; smc = dxc start
	pop	hl					; smc = dxs start
	pop	ix
	
	push	af
	ld	iyh,a					; size * scale / 64
drawSpriteRotatedScaled_Loop1:
	push	hl					; dxs
	push	de					; dxc

	; xs = (dxs + dyc) + (size * 128);
_dsrs_dyc_0:
	ld	bc,$000000
	add	hl,bc
_dsrs_size128_0:
	ld	bc,$000000
	add	hl,bc
	ex	de,hl					; de = (dxs + dyc) + (size * 128)
	; ys = (dxc - dys) + (size * 128);
_dsrs_dys_0:
	ld	bc,$000000
	or	a,a
	sbc	hl,bc
_dsrs_size128_1:
	ld	bc,$000000
	add	hl,bc					; hl = (dxc - dys) + (size * 128)

_dsrs_size_1:						; smc = size * scale / 64
	ld	iyl,$00
drawSpriteRotatedScaled_Loop2:
	push	hl					; xs
 
	ld	a,d
	or	a,h
	rlca
	jr	c,drawSpriteRotatedScaled_SkipPixel
_dsrs_ssize_0:
	ld	a,$00
	cp	a,d
	jr	c,drawSpriteRotatedScaled_SkipPixel
	cp	a,h
	jr	c,drawSpriteRotatedScaled_SkipPixel

	; get pixel and draw to buffer
_dsrs_ssize_1:
	ld	c,$00
	ld	b,h
	mlt	bc
	sbc	hl,hl
	ld	l,d
	add	hl,bc					; y * size + x
_dsrs_sprptr_0:
	ld	bc,$000000
	add	hl,bc
	ld	a,(hl)
	cp	a,DEFAULT_TP_COLOR
TColor_SMC_6 =$-1
	jr	z,$+5
_smc_tp =$-1
	ld	(ix),a					; write pixel
drawSpriteRotatedScaled_SkipPixel:
	inc	ix					; x++s
_dsrs_cosf_0:						; smc = cosf
	ld	hl,$000000
	add	hl,de					; xs += cosf
	ex	de,hl
	pop	hl					; ys
_dsrs_sinf_0:						; smc = -sinf
	ld	bc,$000000
	add	hl,bc					; ys += -sinf
	dec	iyl
	jr	nz,drawSpriteRotatedScaled_Loop2		; x loop

	pop	hl					; dxc
_dsrs_cosf_1:						; smc = cosf
	ld	bc,$000000
	add	hl,bc					; dxc += cosf
	ex	de,hl
	pop	hl					; dxs
_dsrs_sinf_1:						; smc = sinf
	ld	bc,$000000
	add	hl,bc					; dxs += sinf

_line_add:
	ld	bc,$000000
	add	ix,bc					; y++
	
	dec	iyh
	jp	nz,drawSpriteRotatedScaled_Loop1 \.r	; y loop
	pop	af					; sprite out ptr
	pop	de
	pop	ix
	ret

;-------------------------------------------------------------------------------
_RotateScaleSprite:
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
	ld	iy,(ix+6)				; sprite pointer
	lea	hl,iy+2
	ld	(_smc_dsrs_sprptr_0 + 1),hl \.r		; write smc
	
_ScaleRotateSprite_ASM:
	; sinf = sinTable[angle] * 128 / scale;
	ld	a,(ix+12)				; angle
	call	getSinCos \.r
	ld	l,0
	ld	h,a
	rlca
	rr	h					; hl = sinTable[angle] * 128
	ld	c,(ix+15)
	ld	b,0
	call	_16Div8Signed \.r			; hl = sinTable[angle] * 128 / scale (sin)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(_smc_dsrs_sinf_1 + 1),hl \.r		; write smc
	push	hl
	ex	de,hl
	sbc	hl,hl
	ccf
	sbc	hl,de
	ld	(_smc_dsrs_sinf_0 + 1),hl \.r		; write smc
	pop	hl

	; dxs = sinf * -(size * scale / 128);
	ld	c,(ix+15)
	ld	b,(iy)
	mlt	bc					; size * scale
	rl	c
	rl	b
	ld	c,b					; (size * scale / 128)
	xor	a,a
	sub	a,c
	ld	c,a
	sbc	a,a
	ld	b,a					; -(size * scale / 128)
	ld	(ix-3),bc
	call	_16Mul16SignedNeg \.r			; sinf * -(size * scale / 128)
	ld	(_smc_dsrs_dys_0 + 1),hl \.r		; write smc
	push	hl
	
	; cosf = sinTable[angle + 64] * 128 / scale
	ld	a,64
	add	a,(ix+12)				; angle + 64
	call	getSinCos \.r
	ld	l,0
	ld	h,a
	rlca
	rr	h					; hl = sinTable[angle + 64] * 128
	ld	c,(ix+15)
	ld	b,0
	call	_16Div8Signed \.r			; hl = sinTable[angle + 64] * 128 / scale (cos)
	ex	de,hl
	ld	a,d
	rlca
	sbc	hl,hl
	ld	l,e
	ld	h,d
	ld	(_smc_dsrs_cosf_0 + 1),hl \.r		; write smc
	ld	(_smc_dsrs_cosf_1 + 1),hl \.r		; write smc

	; dxc = cosf * -(size * scale / 128);
	ld	bc,(ix-3)				; -(size * scale / 128)
	call	_16Mul16SignedNeg \.r			; cosf * -(size * scale / 128)
	ld	(_smc_dsrs_dyc_0 + 1),hl \.r		; write smc
 	push	hl
	
	ld	a,(iy)					; size
	ld	(_smc_dsrs_ssize_1 + 1),a \.r		; write smc
	dec	a
	ld	(_smc_dsrs_ssize_0 + 1),a \.r		; write smc
	inc	a
	ld	b,a
	ld	c,(ix+15)
	mlt	bc					; size * scale
	srl	a					; size / 2
	or	a,a
	sbc	hl,hl
	ld	h,a
	ld	(_smc_dsrs_size128_0 + 1),hl \.r	; write smc
	ld	(_smc_dsrs_size128_1 + 1),hl \.r	; write smc
	ld	a,b
	rl	c
	adc	a,a
	rl	c
	adc	a,a					; size * scale / 64
	jr	nz,+_
	inc	a					; hax for scale = 1?
_:	ld	(_smc_dsrs_size_1 + 2),a \.r		; write smc

	pop	de					; smc = dxc start
	pop	hl					; smc = dxs start
	
	ld	iy,(ix+9)				; sprite storing to
	push	iy
	ld	(iy+0),a
	ld	(iy+1),a
	lea	ix,iy+2
	
	ld	iyh,a					; size * scale / 64
drawSpriteRotateScale_Loop1:
	push	hl					; dxs
	push	de					; dxc

	; xs = (dxs + dyc) + (size * 128);
_smc_dsrs_dyc_0:
	ld	bc,$000000
	add	hl,bc
_smc_dsrs_size128_0:
	ld	bc,$000000
	add	hl,bc
	ex	de,hl					; de = (dxs + dyc) + (size * 128)
	; ys = (dxc - dys) + (size * 128);
_smc_dsrs_dys_0:
	ld	bc,$000000
	or	a,a
	sbc	hl,bc
_smc_dsrs_size128_1:
	ld	bc,$000000
	add	hl,bc					; hl = (dxc - dys) + (size * 128)

_smc_dsrs_size_1:					; smc = size * scale / 64
	ld	iyl,$00
drawSpriteRotateScale_Loop2:
	push	hl					; xs
 
	ld	a,d
	or	a,h
	rlca
	ld	c,DEFAULT_TP_COLOR
TColor_SMC_7 =$-1
	jr	c,drawSpriteRotateScale_SkipPixel
_smc_dsrs_ssize_0:
	ld	a,$00
	cp	a,d
	jr	c,drawSpriteRotateScale_SkipPixel
	cp	a,h
	jr	c,drawSpriteRotateScale_SkipPixel

	; get pixel and draw to buffer
_smc_dsrs_ssize_1:
	ld	c,$00
	ld	b,h
	mlt	bc
	sbc	hl,hl
	ld	l,d
	add	hl,bc					; y * size + x
_smc_dsrs_sprptr_0:
	ld	bc,$000000
	add	hl,bc
	ld	c,(hl)
drawSpriteRotateScale_SkipPixel:
	ld	(ix),c					; write pixel
	inc	ix					; x++s
_smc_dsrs_cosf_0:					; smc = cosf
	ld	hl,$000000
	add	hl,de					; xs += cosf
	ex	de,hl
	pop	hl					; ys
_smc_dsrs_sinf_0:					; smc = -sinf
	ld	bc,$000000
	add	hl,bc					; ys += -sinf
	dec	iyl
	jr	nz,drawSpriteRotateScale_Loop2		; x loop

	pop	hl					; dxc
_smc_dsrs_cosf_1:					; smc = cosf
	ld	bc,$000000
	add	hl,bc					; dxc += cosf
	ex	de,hl
	pop	hl					; dxs
_smc_dsrs_sinf_1:					; smc = sinf
	ld	bc,$000000
	add	hl,bc					; dxs += sinf

	dec	iyh
	jp	nz,drawSpriteRotateScale_Loop1 \.r	; y loop
	pop	hl					; sprite out ptr
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
	ld	hl,sinTable \.r
	add	hl,de
	ld	a,(hl)
	bit	7,c
	ret	z
	neg
	ret

sinTable:
	; sin(x) * 128
	.db 0,3,6,9,13,16,19,22,25,28,31,34,37,40,43,46
	.db 49,52,55,58,60,63,66,68,71,74,76,79,81,84,86,88
	.db 91,93,95,97,99,101,103,105,106,108,110,111,113,114,116,117
	.db 118,119,121,122,122,123,124,125,126,126,127,127,127,127,127,127,127

_16Div8Signed:
	ld	a,h
	xor	a,c
	push	af
	bit	7,h
	jr	z,+_
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
_:	xor	a,a
	sub	a,c
	jp	m,+_ \.r
	ld	c,a
_:	push	hl
	dec	sp
	pop	hl
	inc	sp
	ld	b,16
	xor	a,a
_:	add	hl,hl
	rla
	cp	a,c
	jr	c,+_
	sub	a,c
	inc	l
_:	djnz	--_
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
_FloodFill:
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
	call	_PixelPtrNoChks_ASM \.r     ; ov = p(x, y);
	ld	a,(hl)

	ld	(ff_oldcolor0_smc),a \.r
	ld	(ff_oldcolor1_smc),a \.r
	ld	(ff_oldcolor2_smc),a \.r

	ld	a,(ix+12)
	ld	(ff_newcolor0_smc),a \.r
	ld	(ff_newcolor1_smc),a \.r

	ld	hl,(_xmax) \.r              ; smc to gain speedz in inner loops
	ld	(ff_xmax_smc),hl \.r
	ld	hl,(_xmin) \.r
	ld	(ff_xmin_smc),hl \.r

	lea	iy,ix
	ld	bc,-3224
	add	iy,bc
	ld	(ff_stacktop_smc),iy \.r

	ld	a,(ix+9)
	ld	hl,(ix+6)
	ld	(iy+0),hl                   ; sp->xl = x;
	ld	(iy+3),hl                   ; sp->xr = x;
	ld	(iy+6),a                    ; sp->y  = y;
	ld	(iy+7),1                    ; sp->dy = 1;
	lea	iy,iy+8                     ; sp++;

	inc	a
	ld	(iy+6),a                    ; sp->y  = y+1;
	ld	(iy+0),hl                   ; sp->xl = x;
	ld	(iy+3),hl                   ; sp->xr = x;
	ld	(iy+7),255                  ; sp->dy = -1;
	lea	iy,iy+8                     ; sp++;

ff_doloop:                                  ; do {
	lea	iy,iy-8                     ; sp--;
	ld	a,(iy+7)
	ld	(ix-4),a                    ; dy = sp->dy;
	add	a,(iy+6)                    ; y  = sp->y+dy;
	ld	(ix+9),a
	ld	bc,(iy+3)
	ld	(ix-15),bc                  ; x2 = sp->xr;
	ld	bc,(iy+0)
	ld	(ix-8),bc                   ; x1 = sp->xl;

	ld	hl,(currDrawBuffer)
	add	hl,bc
	ld	e,a
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
ff_xmin_smc =$+1
	ld	de,0
ff_oldcolor0_smc =$+1
	ld	a,0

	jr	+_
ff_forloop0:                                ; for (x=x1; !(x & 0x8000) && x>=xmin && p(x, y) == ov; x--) { s(x, y); }
ff_newcolor0_smc =$+1
	ld	(hl),0
	dec	hl
	dec	bc
_:	bit	7,b
	jr	nz,+_
	or	a,a
	sbc	hl,de
	jr	c,+_
	add	hl,de
	cp	a,(hl)
	jr	z,ff_forloop0

_:	ld	(ix+6),bc
	ld	bc,(ix-8)
	ld	hl,(ix+6)
	bit	7,h
	jr	nz,+_
	or	a,a
	sbc	hl,bc
	jp	nc,ff_skip \.r              ; if (!(x & 0x8000) && (unsigned)x>=x1) goto skip;
	add	hl,bc
_:	inc	hl
	ld	(ix-11),hl                  ; l = x+1;
	or	a,a
	sbc	hl,bc
	jr	nc,ff_badpush0              ; if (l<x1) { push(y, l, x1-1, -dy); }
	lea	de,ix-24
	lea	hl,iy
	or	a,a
	sbc	hl,de
	jr	nc,ff_badpush0              ; check stack limit
	ld	a,(_ymin) \.r
	ld	e,a
	ld	a,(ix-4)
	neg
	add	a,(ix+9)
	cp	a,e
	jr	c,ff_badpush0
	ld	e,a
	ld	a,(_ymax) \.r
	cp	a,e
	jr	c,ff_badpush0               ; compare y values
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
ff_badpush0:
	ld	bc,(ix-8)
	inc	bc                          ; x = x1+1;

	ld	hl,(currDrawBuffer)
	add	hl,bc
	ld	e,(ix+9)
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl                       ; de -> draw location
                                            ; do {
ff_forloop1start:
ff_xmax_smc =$+1
	ld	hl,0

	jr	+_                          ; for (; (unsigned)x<=xmax && p(x, y) == ov; x++) { s(x, y); }
ff_forloop1:
ff_newcolor1_smc =$+1
	ld	a,0
	ld	(de),a
	inc	de
	inc	bc
_:	or	a,a
	sbc	hl,bc
	jr	c,+_
	add	hl,bc
	ld	a,(de)
ff_oldcolor1_smc =$+1
	cp	a,0
	jr	z,ff_forloop1

_:	ld	(ix+6),bc
	lea	de,ix-24                    ; push(y, l, x-1, dy);
	lea	hl,iy
	or	a,a
	sbc	hl,de
	jr	nc,ff_badpush1
	ld	a,(_ymin) \.r
	ld	e,a
	ld	a,(ix-4)
	add	a,(ix+9)
	cp	a,e
	jr	c,ff_badpush1
	ld	e,a
	ld	a,(_ymax) \.r
	cp	a,e
	jr	c,ff_badpush1               ; compare y values
	dec	bc
	ld	(iy+3),bc
	ld	a,(ix+9)
	ld	(iy+6),a
	ld	bc,(ix-11)
	ld	(iy+0),bc
	ld	a,(ix-4)
	ld	(iy+7),a
	lea	iy,iy+8
ff_badpush1:
	ld	hl,(ix-15)                  ; if (x>x2+1) { push(y, x2+1, x-1, -dy); }
	ld	bc,(ix+6)
	inc	hl
	or	a,a
	sbc	hl,bc
	jr	nc,ff_skip
	lea	de,ix-24
	lea	hl,iy
	or	a,a
	sbc	hl,de
	jr	nc,ff_badpush2
	ld	a,(_ymin) \.r
	ld	e,a
	ld	a,(ix-4)
	neg
	add	a,(ix+9)
	cp	a,e
	jr	c,ff_badpush2
	ld	e,a
	ld	a,(_ymax) \.r
	cp	a,e
	jr	c,ff_badpush2               ; compare y values
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
ff_skip:
ff_badpush2:                                ; skip: for (x++; (unsigned)x<=x2 && p(x, y) != ov; x++);
	ld	bc,(ix+6)
	inc	bc

	ld	hl,(currDrawBuffer)
	add	hl,bc
	ld	e,(ix+9)
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl                       ; de -> draw location
	ld	hl,(ix-15)

	jr	+_
ff_forloop2:
	inc	bc
	inc	de
_:	or	a,a
	sbc	hl,bc
	add	hl,bc
	jr	c,+_
	ld	a,(de)
ff_oldcolor2_smc =$+1
	cp	a,0
	jr	nz,ff_forloop2

_:	ld	(ix+6),bc
	ld	(ix-11),bc                  ; l = x;
	or	a,a
	sbc	hl,bc
	jp	nc,ff_forloop1start \.r     ; } while ((unsigned)x<=x2);

ff_stacktop_smc =$+1
	ld	hl,0
	lea	de,iy
	or	a,a
	sbc	hl,de
	jp	c,ff_doloop \.r             ; } while (sp>stack);

	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_RLETSprite:
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
	ld	hl,(_ymax) \.r		; hl = ymax
	ld	de,(iy+9)		; de = y
	sbc	hl,de			; hl = ymax-y
	ret	m			; m ==> ymax < y || y ~ int_min ==> fully off-screen
	ret	z			; z ==> ymax == y ==> fully off-screen
	sbc	hl,bc			; hl = ymax-y-height = -(height off-screen)
	jr	nc,_RLETSprite_SkipClipBottom ; nc ==> height-off-screen <= 0 ==> fully on-screen
	add	hl,bc			; hl = ymax-y = height on-screen
	ld	c,l			; bc = height on-screen
_RLETSprite_SkipClipBottom:
; ymax-y did not overflow ==> y-ymin will not overflow
; Clip top
	ld	hl,(_ymin) \.r		; hl = ymin
	ex	de,hl			; de = ymin
					; hl = y
	xor	a,a
	sbc	hl,de			; hl = y-ymin
	jp	p,_RLETSprite_SkipClipTop \.r ; p ==> y >= ymin ==> fully on-screen
	add	hl,bc			; hl = y-ymin+height = height on-screen
	ret	nc			; nc ==> height on-screen < 0 ==> fully off-screen
	ld	a,l			; a = height on-screen
	or	a,a
	ret	z			; z ==> height on-screen == 0 ==> fully off-screen
	ld	a,c
	sub	a,l			; a = height off-screen
	ld	b,a			; b = height off-screen
	ld	c,l			; c = height on-screen
	sbc	hl,hl			; y = ymin (after add hl,de)
_RLETSprite_SkipClipTop:
	ld	(_RLETSprite_Heights_SMC),bc \.r
	add	hl,de			; hl = y (clipped)
	ld	(iy+9),l		; write back clipped y
; de = ymin => d = deu = 0
; Clip left
	ld	hl,(iy+3)		; hl = sprite struct
	ld	e,(hl)			; de = width
	ld	hl,(iy+6)		; hl = x
	ld	bc,(_xmin) \.r		; bc = xmin
	sbc	hl,bc			; hl = x-xmin
	ret	pe			; v ==> x ~ int_min ==> fully off-screen
	jp	p,_RLETSprite_SkipClipLeft \.r ; p ==> x >= xmin ==> fully on-screen
	add	hl,de			; hl = x-xmin+width = width on-screen
	ret	nc			; nc ==> width on-screen < 0 ==> fully off-screen
	ld	a,l			; a = width on-screen
	or	a,a
	ret	z			; z ==> width on-screen == 0 ==> fully off-screen
	ld	h,a			; h = width on-screen
	ld	a,e			; a = width
	ld	e,h			; de = width on-screen
	sub	a,l			; a = width - width on-screen = width off-screen
	ld	(_RLETSprite_ClipLeft_Width_SMC),a \.r
	inc	d			; d[0] = 1
	sbc	hl,hl			; x = xmin (after add hl,bc)
_RLETSprite_SkipClipLeft:
; x >= xmin ==> x >= 0
; Clip right
	add	hl,bc			; hl = x (clipped)
	ld	(iy+6),hl		; write back clipped x
	ld	bc,(_xmax) \.r		; bc = xmax
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
	ld	(_RLETSprite_ExitRight_Opaque_Width_SMC),a \.r
	ld	(_RLETSprite_ExitRight_Trans_Width_SMC),a \.r
	ld	a,e			; a = width
	sub	a,l			; a = width - width off-screen = width on-screen
	ld	e,a			; e = width on-screen
	set	1,d			; d[1] = 1
_RLETSprite_SkipClipRight:
; Calculate the pointer to the top-left corner of the sprite in the buffer
	ld	hl,(currDrawBuffer)
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
_RLETSprite_Heights_SMC = $-3
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
	jp	z,_RLETSprite_NoClip_Begin \.r
	cpl				; a = 255-(width on-screen)
	add	a,lcdWidth-255		; a = (lcdWidth-(width on-screen))&0FFh
	rra				; a = (lcdWidth-(width on-screen))/2
	dec	b
	jr	z,_RLETSprite_ClipLeftMiddle
	ld	(_RLETSprite_ClipRight_HalfRowDelta_SMC),a \.r
	sbc	a,a
	djnz	_RLETSprite_ClipLeftMiddleClipRight
_RLETSprite_MiddleClipRight:
	sub	a,s8(_RLETSprite_ClipRight_LoopJr_SMC+1-_RLETSprite_Middle_Row_WidthEven)
	ld	(_RLETSprite_ClipRight_LoopJr_SMC),a \.r
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
_RLETSprite_ExitRight_Opaque_Width_SMC = $-1
	jr	_RLETSprite_ClipRight_OpaqueSkip

_RLETSprite_ExitRight_Trans:
	add	a,c			; a = width remaining on-screen before trans run
	ld	c,a			; bc = width remaining on-screen before trans run
	add	hl,bc			; skip on-screen part of trans run
	ex	de,hl			; de = buffer, hl = sprite
	add	a,0			; a = width remaining on-screen before trans run + width off-screen
_RLETSprite_ExitRight_Trans_Width_SMC = $-1
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
_RLETSprite_ClipRight_HalfRowDelta_SMC = $-1
	add	hl,bc			; advance buffer to next row
	add	hl,bc
	ex	de,hl			; de = buffer, hl = sprite
	dec	iyh			; decrement height remaining
	jr	nz,_RLETSprite_Middle_Trans ; nz ==> height remaining != 0
_RLETSprite_ClipRight_LoopJr_SMC = $-1
	ret

_RLETSprite_ClipLeftMiddleClipRight:
	dec	b			; b = 0
	sub	a,s8(_RLETSprite_ClipRight_LoopJr_SMC+1-_RLETSprite_ClipLeft_Row_WidthEven)
	ld	(_RLETSprite_ClipRight_LoopJr_SMC),a \.r
	ld	a,s8(_RLETSprite_Middle_OpaqueCopy-(_RLETSprite_EnterLeft_Opaque_Jr_SMC+1))
	ld	c,s8(_RLETSprite_Middle_TransSkip-(_RLETSprite_EnterLeft_Trans_Jr_SMC+1))
	jr	_RLETSprite_ClipLeftMiddle_DoSMC

_RLETSprite_ClipLeftMiddle:
	ld	(_RLETSprite_NoClip_HalfRowDelta_SMC),a \.r
	sbc	a,a
	sub	a,s8(_RLETSprite_NoClip_LoopJr_SMC+1-_RLETSprite_ClipLeft_Row_WidthEven)
	ld	(_RLETSprite_NoClip_LoopJr_SMC),a \.r
	ld	a,s8(_RLETSprite_NoClip_OpaqueCopy-(_RLETSprite_EnterLeft_Opaque_Jr_SMC+1))
	ld	c,s8(_RLETSprite_NoClip_TransSkip-(_RLETSprite_EnterLeft_Trans_Jr_SMC+1))
_RLETSprite_ClipLeftMiddle_DoSMC:
	ld	(_RLETSprite_EnterLeft_Opaque_Jr_SMC),a \.r
	ld	a,c
	ld	(_RLETSprite_EnterLeft_Trans_Jr_SMC),a \.r
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
_RLETSprite_EnterLeft_Opaque_Jr_SMC = $-1

_RLETSprite_EnterLeft_Trans:
	neg				; a = trans run length on-screen
	ld	c,a			; bc = trans run length on-screen
	ld	a,iyl			; a = width on-screen
	sub	a,c			; a = width remaining on-screen after trans run
	ex	de,hl			; de = sprite, hl = buffer
	jr	_RLETSprite_NoClip_TransSkip
_RLETSprite_EnterLeft_Trans_Jr_SMC = $-1

;-------------------------------------------------------------------------------
_RLETSprite_NoClip:
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
	ld	hl,(currDrawBuffer)
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
	ld	(_RLETSprite_NoClip_HalfRowDelta_SMC),a \.r
	sbc	a,a
	sub	a,s8(_RLETSprite_NoClip_LoopJr_SMC+1-_RLETSprite_NoClip_Row_WidthEven)
	ld	(_RLETSprite_NoClip_LoopJr_SMC),a \.r
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
_RLETSprite_NoClip_HalfRowDelta_SMC = $-1
	add	hl,bc			; advance buffer to next row
	add	hl,bc
	ex	de,hl			; de = buffer, hl = sprite
;; Decrement height remaining. Continue row loop while not zero.
	dec	iyh			; decrement height remaining
	jr	nz,_RLETSprite_NoClip_Row_WidthEven ; nz ==> height remaining != 0
_RLETSprite_NoClip_LoopJr_SMC = $-1
; }
; Done.
	ret

;-------------------------------------------------------------------------------
_ConvertFromRLETSprite:
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
TColor_SMC_5 = $-1
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
_ConvertToNewRLETSprite:
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
	ld	(_ConvertToNewRLETSprite_Malloc_SMC),hl \.r
	ex	de,hl			; hl = input
; Save input to copy after allocating output.
	push	hl
; Read the sprite width and height.
	ld	iy,(hl)			; iyh = height, iyl = width
	inc	hl			; hl = <input data>-1
; Initialize values for looping.
	inc.s	bc			; bcu = 0
	ld	de,2			; de = 2 = output size
	ld	a,(TColor_SMC_5) \.r	; a = trans color
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
_ConvertToNewRLETSprite_Malloc_SMC = $-3
	pop	de
; Convert sprite.
	pop	de			; de = input
	jr	_ConvertToRLETSprite_ASM

;-------------------------------------------------------------------------------
_ConvertToRLETSprite:
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
	ld	a,(TColor_SMC_5) \.r	; a = trans color
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
_LZ_ReadVarSize_ASM:
; LZ Decompression Subroutine (This should no longer be accessible by the API)
	push	ix
	ld	ix,0
	lea	de,ix
	add	ix,sp
	lea	hl,ix-12
	ld	sp,hl
	ld	(ix-3),de
	ld	(ix-6),de
LZDoWhileLoop:
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
	jr	nz,LZDoWhileLoop
	ld	hl,(ix+6)
	ld	bc,(ix-3)
	ld	(hl),bc
	ld	hl,(ix-6)
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_PixelPtr_ASM:
; Gets the address of a pixel
; Inputs:
;  BC=X
;   E=Y
; Outputs:
;  HL->address of pixel
	ld	hl,-lcdWidth
	add	hl,bc
	ret	c
	ld	a,256-lcdHeight
	add	a,e
	ret	c
_PixelPtrNoChks_ASM:
	ld	hl,(currDrawBuffer)
	add	hl,bc
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_Max_ASM:
; Calculate the resut of a signed comparison
; Inputs:
;  DE,HL=numbers
; Oututs:
;  HL=max number
	or	a,a
	sbc	hl,de
	add	hl,de
	jp	p,+_ \.r
	ret	pe
	ex	de,hl
_:	ret	po
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
_Min_ASM:
; Calculate the resut of a signed comparison
; Inputs:
;  DE,HL=numbers
; Oututs:
;  HL=min number
	or	a,a
	sbc	hl,de
	ex	de,hl
	jp	p,+_ \.r
	ret	pe
	add	hl,de
_:	ret	po
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_ClipRectRegion_ASM:
; Calculates the new coordinates given the clip  and inputs
; Inputs:
;  None
; Outputs:
;  Modifies data registers
;  Sets C flag if offscreen
	ld	hl,(_xmin) \.r
	ld	de,(iy+3)
	call	_Max_ASM \.r
	ld	(iy+3),hl
	ld	hl,(_xmax) \.r
	ld	de,(iy+9)
	call	_Min_ASM \.r
	ld	(iy+9),hl
	ld	de,(iy+3)
	call	_ClipRectRegion_Compare_ASM \.r
	ret	c
	ld	hl,(_ymin) \.r
	ld	de,(iy+6)
	call	_Max_ASM \.r
	ld	(iy+6),hl
	ld	hl,(_ymax) \.r
	ld	de,(iy+12)
	call	_Min_ASM \.r
	ld	(iy+12),hl
	ld	de,(iy+6)
_ClipRectRegion_Compare_ASM:
	dec	hl
_SignedCompare_ASM:
	or	a,a
	sbc	hl,de
	add	hl,hl
	ret	po
	ccf
	ret

;-------------------------------------------------------------------------------
_SetFullScrnClip_ASM:
; Sets the clipping  to the entire screen
; Inputs:
;  None
; Outputs:
;  HL=lcdWidth
	ld	a,lcdHeight
	ld	(_ymax),a \.r
	xor	a,a
	ld	(_ymin),a \.r
	sbc	hl,hl
	ld	(_xmin),hl \.r
	inc	h
	ld	l,lcdWidth&$ff
	ld	(_xmax),hl \.r
	ret

;-------------------------------------------------------------------------------
__idivs_ASM:
; Performs signed integer division
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = HL/BC
	ex	de,hl
	xor	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	p,+_ \.r
	push	hl
	pop	bc
	inc	a

_:	or	a,a
	sbc	hl,hl
	sbc	hl,de
	jp	m,+_ \.r
	ex	de,hl
	inc	a

_:	add	hl,de
	rra
	ld	a,24

_:	ex	de,hl
	adc	hl,hl
	ex	de,hl
	adc	hl,hl
	add	hl,bc
	jr	c,+_
	sbc	hl,bc
_:	dec	a
	jr	nz,--_

	ex	de,hl
	adc	hl,hl
	ret	c
	ex	de,hl
	sbc	hl,hl
	sbc	hl,de
	ret

;-------------------------------------------------------------------------------
__imulsDE_ASM:
__imuluDE_ASM:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  DE : Operand 2
; Outputs:
;  HL = HL*DE
	push	de
	pop	bc
;-------------------------------------------------------------------------------
__imuls_ASM:
__imulu_ASM:
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
	mlt 	hl
	add	a,l
	pop	hl
	inc	sp
	mlt 	hl
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
_ComputeOutcode_ASM:
; Compute the bitcode for a point (x, y) using the clip rectangle
; bounded diagonally by (xmin, ymin), and (xmax, ymax)
; Inputs:
;  HL : X Argument
;  DE : Y Argument
; Outputs:
;   A : Bitcode
	ld	bc,(_xmin) \.r
	push	hl
	xor	a,a
	sbc	hl,bc
	pop	bc
	add	hl,hl
	jp	po,+_ \.r
	ccf
_:	rla
	ld	hl,(_xmax) \.r
	dec	hl                          ; inclusive
	sbc	hl,bc
	add	hl,hl
	jp	po,+_ \.r
	ccf
_:	rla
	ld	hl,(_ymin) \.r
	scf
	sbc	hl,de
	add	hl,hl
	jp	pe,+_ \.r
	ccf
_:	rla
	ld	hl,(_ymax) \.r
	dec	hl                          ; inclusive
	sbc	hl,de
	add	hl,hl
	rla
	ret	po
	xor	a,1
	ret

;-------------------------------------------------------------------------------
CharSpacing_ASM:
	.dl DefaultCharSpacing_ASM \.r
TextData_ASM:
	.dl DefaultTextData_ASM \.r

DefaultCharSpacing_ASM:
	;   0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	.db 8,8,8,8,8,8,8,8,8,8,8,8,8,2,8,8
	.db 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	.db 3,4,6,8,8,8,8,5,5,5,8,7,4,7,3,8
	.db 8,7,8,8,8,8,8,8,8,8,3,4,6,7,6,7
	.db 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	.db 8,8,8,8,8,8,8,8,8,8,8,5,8,5,8,8
	.db 4,8,8,8,8,8,8,8,8,5,8,8,5,8,8,8
	.db 8,8,8,8,7,8,8,8,8,8,8,7,3,7,8,8
	.db 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	.db 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8

;-------------------------------------------------------------------------------
DefaultTextData_ASM:
Char000: .db $00,$00,$00,$00,$00,$00,$00,$00	; .
Char001: .db $7E,$81,$A5,$81,$BD,$BD,$81,$7E	; .
Char002: .db $7E,$FF,$DB,$FF,$C3,$C3,$FF,$7E	; .
Char003: .db $6C,$FE,$FE,$FE,$7C,$38,$10,$00	; .
Char004: .db $10,$38,$7C,$FE,$7C,$38,$10,$00	; .
Char005: .db $38,$7C,$38,$FE,$FE,$10,$10,$7C	; .
Char006: .db $00,$18,$3C,$7E,$FF,$7E,$18,$7E	; .
Char007: .db $00,$00,$18,$3C,$3C,$18,$00,$00	; .
Char008: .db $FF,$FF,$E7,$C3,$C3,$E7,$FF,$FF	; .
Char009: .db $00,$3C,$66,$42,$42,$66,$3C,$00	; .
Char010: .db $FF,$C3,$99,$BD,$BD,$99,$C3,$FF	; .
Char011: .db $0F,$07,$0F,$7D,$CC,$CC,$CC,$78	; .
Char012: .db $3C,$66,$66,$66,$3C,$18,$7E,$18	; .
Char013: .db $3F,$33,$3F,$30,$30,$70,$F0,$E0	; .
Char014: .db $7F,$63,$7F,$63,$63,$67,$E6,$C0	; .
Char015: .db $99,$5A,$3C,$E7,$E7,$3C,$5A,$99	; .
Char016: .db $80,$E0,$F8,$FE,$F8,$E0,$80,$00	; .
Char017: .db $02,$0E,$3E,$FE,$3E,$0E,$02,$00	; .
Char018: .db $18,$3C,$7E,$18,$18,$7E,$3C,$18	; .
Char019: .db $66,$66,$66,$66,$66,$00,$66,$00	; .
Char020: .db $7F,$DB,$DB,$7B,$1B,$1B,$1B,$00	; .
Char021: .db $3F,$60,$7C,$66,$66,$3E,$06,$FC	; .
Char022: .db $00,$00,$00,$00,$7E,$7E,$7E,$00	; .
Char023: .db $18,$3C,$7E,$18,$7E,$3C,$18,$FF	; .
Char024: .db $18,$3C,$7E,$18,$18,$18,$18,$00	; .
Char025: .db $18,$18,$18,$18,$7E,$3C,$18,$00	; .
Char026: .db $00,$18,$0C,$FE,$0C,$18,$00,$00	; .
Char027: .db $00,$30,$60,$FE,$60,$30,$00,$00	; .
Char028: .db $00,$00,$C0,$C0,$C0,$FE,$00,$00	; .
Char029: .db $00,$24,$66,$FF,$66,$24,$00,$00	; .
Char030: .db $00,$18,$3C,$7E,$FF,$FF,$00,$00	; .
Char031: .db $00,$FF,$FF,$7E,$3C,$18,$00,$00	; .
Char032: .db $00,$00,$00,$00,$00,$00,$00,$00	;
Char033: .db $C0,$C0,$C0,$C0,$C0,$00,$C0,$00	; !
Char034: .db $D8,$D8,$D8,$00,$00,$00,$00,$00	; "
Char035: .db $6C,$6C,$FE,$6C,$FE,$6C,$6C,$00	; #
Char036: .db $18,$7E,$C0,$7C,$06,$FC,$18,$00	; $
Char037: .db $00,$C6,$CC,$18,$30,$66,$C6,$00	; %
Char038: .db $38,$6C,$38,$76,$DC,$CC,$76,$00	; &
Char039: .db $30,$30,$60,$00,$00,$00,$00,$00	; '
Char040: .db $30,$60,$C0,$C0,$C0,$60,$30,$00	; (
Char041: .db $C0,$60,$30,$30,$30,$60,$C0,$00	; )
Char042: .db $00,$66,$3C,$FF,$3C,$66,$00,$00	; *
Char043: .db $00,$30,$30,$FC,$FC,$30,$30,$00	; +
Char044: .db $00,$00,$00,$00,$00,$60,$60,$C0	; ,
Char045: .db $00,$00,$00,$FC,$00,$00,$00,$00	; -
Char046: .db $00,$00,$00,$00,$00,$C0,$C0,$00	; .
Char047: .db $06,$0C,$18,$30,$60,$C0,$80,$00	; /
Char048: .db $7C,$CE,$DE,$F6,$E6,$C6,$7C,$00	; 0
Char049: .db $30,$70,$30,$30,$30,$30,$FC,$00	; 1
Char050: .db $7C,$C6,$06,$7C,$C0,$C0,$FE,$00	; 2
Char051: .db $FC,$06,$06,$3C,$06,$06,$FC,$00	; 3
Char052: .db $0C,$CC,$CC,$CC,$FE,$0C,$0C,$00	; 4
Char053: .db $FE,$C0,$FC,$06,$06,$C6,$7C,$00	; 5
Char054: .db $7C,$C0,$C0,$FC,$C6,$C6,$7C,$00	; 6
Char055: .db $FE,$06,$06,$0C,$18,$30,$30,$00	; 7
Char056: .db $7C,$C6,$C6,$7C,$C6,$C6,$7C,$00	; 8
Char057: .db $7C,$C6,$C6,$7E,$06,$06,$7C,$00	; 9
Char058: .db $00,$C0,$C0,$00,$00,$C0,$C0,$00	; :
Char059: .db $00,$60,$60,$00,$00,$60,$60,$C0	; ;
Char060: .db $18,$30,$60,$C0,$60,$30,$18,$00	; <
Char061: .db $00,$00,$FC,$00,$FC,$00,$00,$00	; =
Char062: .db $C0,$60,$30,$18,$30,$60,$C0,$00	; >
Char063: .db $78,$CC,$18,$30,$30,$00,$30,$00	; ?
Char064: .db $7C,$C6,$DE,$DE,$DE,$C0,$7E,$00	; @
Char065: .db $38,$6C,$C6,$C6,$FE,$C6,$C6,$00	; A
Char066: .db $FC,$C6,$C6,$FC,$C6,$C6,$FC,$00	; B
Char067: .db $7C,$C6,$C0,$C0,$C0,$C6,$7C,$00	; C
Char068: .db $F8,$CC,$C6,$C6,$C6,$CC,$F8,$00	; D
Char069: .db $FE,$C0,$C0,$F8,$C0,$C0,$FE,$00	; E
Char070: .db $FE,$C0,$C0,$F8,$C0,$C0,$C0,$00	; F
Char071: .db $7C,$C6,$C0,$C0,$CE,$C6,$7C,$00	; G
Char072: .db $C6,$C6,$C6,$FE,$C6,$C6,$C6,$00	; H
Char073: .db $7E,$18,$18,$18,$18,$18,$7E,$00	; I
Char074: .db $06,$06,$06,$06,$06,$C6,$7C,$00	; J
Char075: .db $C6,$CC,$D8,$F0,$D8,$CC,$C6,$00	; K
Char076: .db $C0,$C0,$C0,$C0,$C0,$C0,$FE,$00	; L
Char077: .db $C6,$EE,$FE,$FE,$D6,$C6,$C6,$00	; M
Char078: .db $C6,$E6,$F6,$DE,$CE,$C6,$C6,$00	; N
Char079: .db $7C,$C6,$C6,$C6,$C6,$C6,$7C,$00	; O
Char080: .db $FC,$C6,$C6,$FC,$C0,$C0,$C0,$00	; P
Char081: .db $7C,$C6,$C6,$C6,$D6,$DE,$7C,$06	; Q
Char082: .db $FC,$C6,$C6,$FC,$D8,$CC,$C6,$00	; R
Char083: .db $7C,$C6,$C0,$7C,$06,$C6,$7C,$00	; S
Char084: .db $FF,$18,$18,$18,$18,$18,$18,$00	; T
Char085: .db $C6,$C6,$C6,$C6,$C6,$C6,$FE,$00	; U
Char086: .db $C6,$C6,$C6,$C6,$C6,$7C,$38,$00	; V
Char087: .db $C6,$C6,$C6,$C6,$D6,$FE,$6C,$00	; W
Char088: .db $C6,$C6,$6C,$38,$6C,$C6,$C6,$00	; X
Char089: .db $C6,$C6,$C6,$7C,$18,$30,$E0,$00	; Y
Char090: .db $FE,$06,$0C,$18,$30,$60,$FE,$00	; Z
Char091: .db $F0,$C0,$C0,$C0,$C0,$C0,$F0,$00	; [
Char092: .db $C0,$60,$30,$18,$0C,$06,$02,$00	; \
Char093: .db $F0,$30,$30,$30,$30,$30,$F0,$00	; ]
Char094: .db $10,$38,$6C,$C6,$00,$00,$00,$00	; ^
Char095: .db $00,$00,$00,$00,$00,$00,$00,$FF	; _
Char096: .db $C0,$C0,$60,$00,$00,$00,$00,$00	; `
Char097: .db $00,$00,$7C,$06,$7E,$C6,$7E,$00	; a
Char098: .db $C0,$C0,$C0,$FC,$C6,$C6,$FC,$00	; b
Char099: .db $00,$00,$7C,$C6,$C0,$C6,$7C,$00	; c
Char100: .db $06,$06,$06,$7E,$C6,$C6,$7E,$00	; d
Char101: .db $00,$00,$7C,$C6,$FE,$C0,$7C,$00	; e
Char102: .db $1C,$36,$30,$78,$30,$30,$78,$00	; f
Char103: .db $00,$00,$7E,$C6,$C6,$7E,$06,$FC	; g
Char104: .db $C0,$C0,$FC,$C6,$C6,$C6,$C6,$00	; h
Char105: .db $60,$00,$E0,$60,$60,$60,$F0,$00	; i
Char106: .db $06,$00,$06,$06,$06,$06,$C6,$7C	; j
Char107: .db $C0,$C0,$CC,$D8,$F8,$CC,$C6,$00	; k
Char108: .db $E0,$60,$60,$60,$60,$60,$F0,$00	; l
Char109: .db $00,$00,$CC,$FE,$FE,$D6,$D6,$00	; m
Char110: .db $00,$00,$FC,$C6,$C6,$C6,$C6,$00	; n
Char111: .db $00,$00,$7C,$C6,$C6,$C6,$7C,$00	; o
Char112: .db $00,$00,$FC,$C6,$C6,$FC,$C0,$C0	; p
Char113: .db $00,$00,$7E,$C6,$C6,$7E,$06,$06	; q
Char114: .db $00,$00,$FC,$C6,$C0,$C0,$C0,$00	; r
Char115: .db $00,$00,$7E,$C0,$7C,$06,$FC,$00	; s
Char116: .db $30,$30,$FC,$30,$30,$30,$1C,$00	; t
Char117: .db $00,$00,$C6,$C6,$C6,$C6,$7E,$00	; u
Char118: .db $00,$00,$C6,$C6,$C6,$7C,$38,$00	; v
Char119: .db $00,$00,$C6,$C6,$D6,$FE,$6C,$00	; w
Char120: .db $00,$00,$C6,$6C,$38,$6C,$C6,$00	; x
Char121: .db $00,$00,$C6,$C6,$C6,$7E,$06,$FC	; y
Char122: .db $00,$00,$FE,$0C,$38,$60,$FE,$00	; z
Char123: .db $1C,$30,$30,$E0,$30,$30,$1C,$00	; {
Char124: .db $C0,$C0,$C0,$00,$C0,$C0,$C0,$00	; |
Char125: .db $E0,$30,$30,$1C,$30,$30,$E0,$00	; }
Char126: .db $76,$DC,$00,$00,$00,$00,$00,$00	; ~
Char127: .db $00,$10,$38,$6C,$C6,$C6,$FE,$00	; .

;-------------------------------------------------------------------------------
; Inner library data
;-------------------------------------------------------------------------------

_xmin:
	.dl 0
_ymin:
	.dl 0
_xmax:
	.dl lcdWidth
_ymax:
	.dl lcdHeight

tmpWidth:
	.dl 0,0,0

tmpCharDataSprite:
	.db 8,8
tmpCharData:
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0

 .endLibrary
