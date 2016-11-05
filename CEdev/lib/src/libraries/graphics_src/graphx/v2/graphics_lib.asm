#include "..\..\..\include\relocation.inc"
#include "..\..\..\include\ti84pce.inc"

 .libraryName		"GRAPHX"          ; Name of library
 .libraryVersion	2                 ; Version information (1-255)
 
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
 .function "gfx_BlitArea",_BlitArea
 .function "gfx_PrintChar",_PrintChar
 .function "gfx_PrintInt",_PrintInt
 .function "gfx_PrintUInt",_PrintUInt
 .function "gfx_PrintString",_PrintString
 .function "gfx_PrintStringXY",_PrintStringXY
 .function "gfx_SetTextXY",_SetTextXY
 .function "gfx_SetTextBGColor",_SetTextBGColorC
 .function "gfx_SetTextFGColor",_SetTextFGColorC
 .function "gfx_SetTextTransparentColor",_SetTextTransparentColorC
 .function "gfx_SetCustomFontData",_SetCustomFontData
 .function "gfx_SetCustomFontSpacing",_SetCustomFontSpacing
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
 .function "gfx_LZDecompress",_LZDecompress
 .function "gfx_AllocSprite",_AllocSprite
 .function "gfx_Sprite",_Sprite
 .function "gfx_TransparentSprite",_TransparentSprite
 .function "gfx_Sprite_NoClip",_Sprite_NoClip
 .function "gfx_TransparentSprite_NoClip",_TransparentSprite_NoClip
 .function "gfx_GetSprite_NoClip",_GetSprite_NoClip
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
; v2 functions
;-------------------------------------------------------------------------------
 .function "gfx_LZDecompressSprite",_LZDecompressSprite
 .function "gfx_SetTextScale",_SetTextScale
;-------------------------------------------------------------------------------

 .beginDependencies
 .endDependencies

;-------------------------------------------------------------------------------
; Used throughout the library
lcdSize                 equ lcdWidth*lcdHeight
currDrawBuffer          equ 0E30014h
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_AllocSprite:
; Allocates space for a new sprite
; Arguments:
;  arg0 : width
;  arg1 : height
;  arg2 : pointer to malloc routine
	ld	iy,0
	add	iy,sp
	ld	l,(iy+3)
	ld	h,(iy+6)
	ld	iy,(iy+9)
	push	hl
	mlt	hl
	inc	hl
	inc	hl
	push	hl
	call	__indcall
	pop	de
	pop	de
	add	hl,de
	or	a,a
	sbc	hl,de
	ret	z
	ld	(hl),e
	inc	hl
	ld	(hl),d
	dec	hl
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
	call	_SetFullScreenClipping_ASM \.r	; clip against the actual LCD screen
	ld	iy,0
	add	iy,sp
	call	_ClipRectangularRegion_ASM \.r	; iy points to the start of the arguments
	lea	hl,iy
	ret	c
	ld	de,_xmin \.r			; copy the variables in
	ld	bc,12
	ldir
	ret

;-------------------------------------------------------------------------------
_SetColor:
; Sets the global color index for all routines
; Arguments:
;  arg0 : Color Index
; Returns:
;  Previous global color index
	pop	hl
	pop	de
	push	de
	push	hl
	ld	hl,color1 \.r
	ld	d,(hl)
	ld	a,e
	ld	(hl),a
	ld	(color2),a \.r
	ld	(color3),a \.r
	ld	(color4),a \.r
	ld	(color5),a \.r
	ld	a,d
	ret

;-------------------------------------------------------------------------------
_Begin:
; Sets up the graphics canvas (8bpp, default palette)
; Arguments:
;  None
; Returns:
;  None
	call	_boot_ClearVRAM			; clear the screen
	ld	hl,tmpWidth
	ld	bc,11
	call	_MemClear
	ld	hl,currDrawBuffer
	ld	a,lcdBpp8
_:	ld	de,vram
	ld	(hl),de				; set the current draw to the screen
	ld	hl,mpLcdCtrl
	ld	(hl),a
	ld	l,mpLcdIcr&$FF
	ld	(hl),4				; allow interrupts status for double buffering
	jr	_SetDefaultPalette		; setup the default palette

;-------------------------------------------------------------------------------
_End:
; Closes the graphics library and sets up for the TI-OS
; Arguments:
;  None
; Returns:
;  None
	call	_boot_ClearVRAM			; clear the screen
	ld	hl,mpLcdBase
	ld	a,lcdBpp16			; restore the screen mode
	jr	-_

;-------------------------------------------------------------------------------
_SetDefaultPalette:
; Sets up the default palette where H=L
; Arguments:
;  None
; Returns:
;  None
	ld	de,mpLcdPalette
	ld	b,e
_:	ld	a,b
	rrca
	xor	a,b
	and	a,%11100000
	xor	a,b
	ld	(de),a
	inc	de
	ld	a,b
	rra
	ld	(de),a
	inc	de
	inc	b
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_FillScreen:
; Fills the screen with the specified color index
; Arguments:
;  arg0 : Color Index
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	a,(hl)				; get the color index to use
	ld	bc,lcdSize-1
	ld	de,(currDrawBuffer)
	sbc	hl,hl
	add	hl,de
	inc	de
	ld	(hl),a
	ldir
	ret

;-------------------------------------------------------------------------------
_SetPalette:
; Sets the palette starting at 0x00 index and onward
; Arguments:
;  arg0 : Pointer to palette
;  arg1 : Size of palette in bytes
;  arg2 : Offset at which to start inserting the palette
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	sbc	hl,hl
	ld	l,(iy+9)			; offset in palette
	add	hl,hl
	ld	de,mpLcdPalette
	add	hl,de
	ex	de,hl
	ld	hl,(iy+3)			; pointer to input palette
	ld	bc,(iy+6)			; size of input palette
	ldir					; copy the palette in
	ret

;-------------------------------------------------------------------------------
_GetPixel:
; Gets the color index of a pixel
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
; Returns:
;  Color index of X,Y Coord
	ld	hl,3
	add	hl,sp
	ld	bc,(hl)				; x coordinate
	inc	hl
	inc	hl
	inc	hl
	ld	de,0
	ld	e,(hl)				; y coordinate
	call	_PixelPtr_ASM \.r
	ret	c
	ld	a,(hl)				; get the actual pixel
	ret

;-------------------------------------------------------------------------------
_SetPixel:
; Sets the color pixel to the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	bc,(hl)				; x coordinate
	inc	hl
	inc	hl
	inc	hl
	ld	de,0
	ld	e,(hl)				; y coordinate
_SetPixel_ASM:
	call	_PixelPtr_ASM \.r
	ret	c
color1 =$+1
	ld	(hl),0				; get the actual pixel
	ret

;-------------------------------------------------------------------------------
_FillRectangle:
; Draws an unclipped rectangle with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+9)			; hl = width
	ld	de,(iy+3)			; de = x coordinate
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(iy+12)			; hl = height
	ld	de,(iy+6)			; de = y coordinate
	add	hl,de		
	ld	(iy+12),hl
	call	_ClipRectangularRegion_ASM \.r
	ret	c				; return if offscreen
	ld	de,(iy+3)
	ld	hl,(iy+9)
	sbc	hl,de				; make sure that the width is not 0
	ret	z
	push	hl
	ld	de,(iy+6)
	ld	hl,(iy+12)
	sbc	hl,de
	pop	bc				; bc = new width
	ret	z
	ld	a,l				; a = new height
	ld	hl,(iy+3)			; hl = new x, de = new y
	jr	_FillRectangle_NoClip_ASM

;-------------------------------------------------------------------------------
_FillRectangle_NoClip:
; Draws an unclipped rectangle with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	a,(iy+12)			; a = height
	or	a,a
	ret	z				; make sure height is not 0
	ld	bc,(iy+9)			; bc = width
	sbc	hl,hl
	adc	hl,bc
	ret	z				; make sure width is not 0
	ld	hl,(iy+3)			; hl = x coordinate
	ld	e,(iy+6)			; e = y coordinate
_FillRectangle_NoClip_ASM:
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de
	ex	de,hl				; de -> place to begin drawing
	push 	de
	ld	(_RectangleWidth1_SMC),bc \.r
	ld	(_RectangleWidth2_SMC),bc \.r
	ld	hl,color1 \.r
	ldi					; check if we only need to draw 1 pixel
	pop	hl
	jp	po,_Rectangle_NoClip_Skip \.r
	ldir
_Rectangle_NoClip_Skip:
	dec 	a
	ret	z
	inc	b
	ld	c,$40				; = slightly faster "ld bc,lcdWidth"
_Rectangle_Loop_NoClip:
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
	jr	nz,_Rectangle_Loop_NoClip
	ret

;-------------------------------------------------------------------------------
_Rectangle:
; Draws an clipped rectangle outline with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	push	ix				; need to use ix because lines use iy
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	push	bc
	push	de
	push	hl
	call	_HorizLine \.r			; top horizontal line
	ld	sp,ix
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	_VertLine \.r			; left vertical line
	ld	sp,ix
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	add	hl,bc				; add x and width
	dec	hl
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	_VertLine \.r			; right vertical line
	ld	sp,ix
	ld	de,(ix+6)
	ld	hl,(ix+9)
	ld	bc,(ix+15)
	add	hl,bc
	dec	hl				; add y and height
	ld	bc,(ix+12)
	push	bc
	push	hl
	push	de
	call	_HorizLine \.r			; bottom horizontal line
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_Rectangle_NoClip:
; Draws an unclipped rectangle outline with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Width
;  arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	e,(iy+6)
	ld	bc,(iy+9)
	ld	d,(iy+12)
	push	bc
	push	hl
	push	de
	call	_RectHoriz_ASM \.r		; top horizontal line
	pop	bc
	push	bc
	call	_RectVert_ASM \.r		; right vertical line
	pop	bc
	pop	hl
	ld	e,c
	call	_VertLine_ASM \.r		; left vertical line
	pop	bc
	or	a,a
	sbc	hl,de
	jp	_MemSet_ASM \.r			; bottom horizontal line

;-------------------------------------------------------------------------------
_HorizLine:
; Draws an clipped horizontal line with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(_ymin) \.r
	ld	hl,(iy+6)
	call	_SignedCompare_ASM \.r		; compare y coordinate <-> ymin
	ret	c
	ld	hl,(_ymax) \.r
	ld	de,(iy+6)
	call	_SignedCompare_ASM \.r		; compare y coordinate <-> ymax
	ret	c
	ret	z
	ld	hl,(iy+9)
	ld	de,(iy+3)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_xmin) \.r
	call	_Max_ASM \.r
	ld	(iy+3),hl			; save maximum x value
	ld	hl,(_xmax) \.r
	ld	de,(iy+9)
	call	_Min_ASM \.r
	ld	(iy+9),hl			; save minimum x value
	ld	de,(iy+3)
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(iy+9)
	sbc	hl,de
	push	hl
	pop	bc				; bc = length
	ld	e,(iy+6)			; e = y coordinate
	jr	_RectHoriz_ASM

;-------------------------------------------------------------------------------
_HorizLine_NoClip:
; Draws an unclipped horizontal line with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	e,(iy+6)			; y coordinate
	ld	bc,(iy+9)			; x coordinate
_RectHoriz_ASM:
	sbc	hl,hl
	adc	hl,bc
	ret	z				; make sure the width is not 0
	ld	hl,(iy+3)
_HorizLine_NoClip_ASM:
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de				; hl -> place to draw
color2 =$+1
	ld	a,0				; color index to use
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
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(_xmax) \.r
	ld	de,(iy+3)
	inc	de
	call	_SignedCompare_ASM \.r
	ret	c				; return if x > xmax
	ld	hl,(iy+3)
	ld	de,(_xmin) \.r
	call	_SignedCompare_ASM \.r
	ret	c				; return if x < xmin
	ld	hl,(iy+9)
	ld	de,(iy+6)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_ymin) \.r
	call	_Max_ASM \.r			; get minimum y
	ld	(iy+6),hl
	ld	hl,(_ymax) \.r
	ld	de,(iy+9)
	call	_Min_ASM \.r			; get maximum y
	ld	(iy+9),hl
	ld	de,(iy+6)
	call	_SignedCompare_ASM \.r
	ret	c				; return if not within y bounds
	ld	hl,(iy+9)
	sbc	hl,de
	ld	b,l
	ld	hl,(iy+3)
	jr	_VertLine_ASM			; jump to unclipped version

;-------------------------------------------------------------------------------
_VertLine_NoClip:
; Draws an unclipped vertical line with the global color index
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)			; x
	ld	e,(iy+6)			; y
	ld	b,(iy+9)			; length
_VertLine_ASM:
	xor	a,a
	or	a,b
	ret	z
	ld	d,lcdWidth/2
	mlt	de
	add.s	hl,de
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de				; hl -> drawing location
_RectVert_ASM:
	ld	de,lcdWidth
color3 =$+1
	ld 	a,0
_:	ld	(hl),a				; loop for height
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
	pop	hl
	pop	bc
	push	bc
	push	hl
	ld	hl,(mpLcdBase)
	ld	de,vram
	ld	a,c
	or	a,a
	jr	z,+++_
	sbc	hl,de
	jr	nz,++_				; if not the same, swap
_:	ld	de,vram+lcdSize
_:	ld	(currDrawBuffer),de
	ret
_:	sbc	hl,de
	jr	z,--_				; if the same, swap
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
_:	ld	(currDrawBuffer),de		; set up the new buffer location
	ld	(mpLcdBase),hl			; set the new pointer location
	ld	hl,mpLcdIcr
	set	2,(hl)				; clear the previous intrpt set
	ld	l,mpLcdRis&$ff
_:	bit	2,(hl)				; wait until the interrupt triggers
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
	ret	z				; drawing to screen
	inc	a
	ret					; drawing to buffer

;-------------------------------------------------------------------------------
_Circle:
; Draws a clipped circle outline
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Radius
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	lea	hl,iy+-9
	ld	sp,hl
	sbc	hl,sp
	ld	(iy+-3),hl
	ld	bc,(iy+9)
	ld	(iy+-6),bc
	inc	hl
	sbc	hl,bc
	ld	(iy+-9),hl
	jp	l_4 \.r
l_5:	ld	bc,(iy+3)
	ld	hl,(iy+-6)
	add	hl,bc
	push	hl
	push	hl
	pop	bc
	ld	de,(iy+6)
	ld	hl,(iy+-3)
	add	hl,de
	ex	de,hl
	push	de
	call	_SetPixel_ASM \.r
	ld	bc,(iy+6)
	ld	hl,(iy+-6)
	add	hl,bc
	ex	de,hl
	push	de
	ld	bc,(iy+3)
	ld	hl,(iy+-3)
	add	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_ASM \.r
	ld	bc,(iy+-6)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_SetPixel_ASM \.r
	pop	de
	ld	bc,(iy+-3)
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
	ld	bc,(iy+-6)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_SetPixel_ASM \.r
	ld	bc,(iy+-3)
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
	ld	bc,(iy+-3)
	inc	bc
	ld	(iy+-3),bc
	ld	bc,(iy+-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,l__2 \.r
	jp	pe,l_3 \.r
	jr	l__3
l__2:	jp	po,l_3 \.r
l__3:	ld	hl,(iy+-3)
	add	hl,hl
	inc	hl
	ld	bc,(iy+-9)
	add	hl,bc
	ld	(iy+-9),hl
	jr	l_4
l_3:	ld	bc,(iy+-6)
	dec	bc
	ld	(iy+-6),bc
	ld	hl,(iy+-3)
	ld	de,(iy+-9)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	add	hl,de
	ld	(iy+-9),hl
l_4:	ld	bc,(iy+-3)
	ld	hl,(iy+-6)
	or	a,a
	sbc	hl,bc
	jp	p,l__4 \.r
	jp	pe,l_5 \.r
	jr	+_
l__4:	jp	po,l_5 \.r
_:	ld	sp,iy
	ret

;-------------------------------------------------------------------------------
_FillCircle:
; Draws an clipped circle
; Arguments:
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Radius
; Returns:
;  None
	push	ix
	ld	ix,0
	add	ix,sp
	lea	hl,ix+-9
	ld	sp,hl
	sbc	hl,hl
	ld	(ix+-3),hl
	ld	bc,(ix+12)
	ld	(ix+-6),bc
	inc	hl
	sbc	hl,bc
	ld	(ix+-9),hl
	jp	b_4 \.r
_FillCircleSectors:
	ld	hl,(ix+-3)
	add	hl,hl
	push	hl
	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	add	hl,bc
	push	hl
	ld	bc,(ix+-3)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	push	hl
	call	_HorizLine \.r
	lea	hl,ix+-9
	ld	sp,hl
	ld	hl,(ix+-3)
	add	hl,hl
	push	hl
	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	push	hl
	ld	bc,(ix+-3)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	push	hl
	call	_HorizLine \.r
	lea	hl,ix+-9
	ld	sp,hl
	ld	hl,(ix+-6)
	add	hl,hl
	push	hl
	ld	bc,(ix+-3)
	ld	hl,(ix+9)
	add	hl,bc
	push	hl
	ld	bc,(ix+-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	push	hl
	call	_HorizLine \.r
	lea	hl,ix+-9
	ld	sp,hl
	ld	hl,(ix+-6)
	add	hl,hl
	push	hl
	ld	bc,(ix+-3)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	push	hl
	ld	bc,(ix+-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	push	hl
	call	_HorizLine \.r
	lea	hl,ix+-9
	ld	sp,hl
	ld	bc,(ix+-3)
	inc	bc
	ld	(ix+-3),bc
	ld	bc,(ix+-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,b__2 \.r
	jp	pe,b_3 \.r
	jr	b__3
b__2:	jp	po,b_3 \.r
b__3:	ld	hl,(ix+-3)
	add	hl,hl
	inc	hl
	ld	bc,(ix+-9)
	add	hl,bc
	ld	(ix+-9),hl
	jr	b_4
b_3:	ld	bc,(ix+-6)
	dec	bc
	ld	(ix+-6),bc
	ld	hl,(ix+-3)
	ld	de,(ix+-9)
	or	a,a
	sbc	hl,bc
	add	hl,hl
	inc	hl
	add	hl,de
	ld	(ix+-9),hl
b_4:	ld	bc,(ix+-3)
	ld	hl,(ix+-6)
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
;  arg0 : X Coord
;  arg1 : Y Coord
;  arg2 : Radius
; Returns:
;  None
	ld 	iy,0
	add	iy,sp
	ld 	a,(iy+9)		; Radius
	or	a,a
	ret	z
	ld	bc,0
	ld	c,a
	ld 	hl,(currDrawBuffer)
	ld 	d,lcdWidth/2
	ld 	e,(iy+6)		; Yc (circle center pos)
	mlt 	de
	add	hl,de
	add	hl,de
	ld	d,b
	ld 	e,(iy+3)		; Xc (circle center pos)
	add	hl,de
	ld 	(circle_center_pos),hl \.r
	sbc 	hl,bc
	ld 	(circle_datcol_ldirpos),hl \.r
	ex 	de,hl			; de = Xc - Radius
	ld 	hl,color1 \.r
	push	de
	ldi
	pop	hl
	ret 	po
	rlc 	c
	inc	c
	ldir
	ld 	(circle_datcol_lddrpos),hl \.r
	ld 	b,a
	inc	a
	ld 	d,a
	ld 	e,a
	mlt 	de
	ld 	iy,0
	add	iy,de
	ld 	c,a
Fory:	lea	hl,iy+0			; kind of For(y,R,1,-1
	ld 	a,c
	ld 	d,b
	ld 	e,b
	mlt 	de			; de = y²
	sbc 	hl,de
	ex 	de,hl			; de = (R²-y²)
Forx:	ld 	h,a			; kind of For(x,R,y,-1
	ld 	l,a
	mlt 	hl			; hl = x²
	sbc 	hl,de			; x² < (R² - y²) ?
	dec	a
	jr 	nc,Forx 		; no?..then loop
	push	bc			; Yes?..Here we go!
circle_center_pos =$+1
	ld 	hl,0			; hl = 'on-screen' center pos
	ld 	c,lcdWidth/2
	mlt 	bc
	push	bc			; bc = 160*y
	add	hl,bc
	add	hl,bc
	ld 	b,0
	ld 	c,a			; bc = x
	add	hl,bc
	ex 	de,hl			; de = 'on-screen' horizontal drawing beginning address
circle_datcol_lddrpos =$+1
	ld 	hl,0			; hl = pointer to color data
	ld 	b,0
	inc	a
	rlca
	ld 	c,a			; bc = drawing length
	lddr				; trace 1st horizontal line (bottom)
	pop	hl			; Now, calculs for mirrored position...
	add	hl,hl
	add	hl,hl			; hl = 160*y*4
	inc	de
	ex 	de,hl
	sbc 	hl,de
	ex 	de,hl			; de = 'on-screen' horizontal drawing beginning address
circle_datcol_ldirpos =$+1
	ld 	hl,0			; hl = pointer to color data
	ld 	c,a			; bc = drawing length
	ldir				; trace 2nd horizontal line (top)
	pop	bc
	djnz 	Fory
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
	ld	hl,_xmax \.r
	ld	de,(hl)
	dec	de
	ld	(hl),de
	ld	hl,_ymax \.r
	dec	(hl)
	ld	iy,0
	add	iy,sp
	lea	hl,iy+-10
	ld	sp,hl
	ld	de,(iy+6)
	ld	hl,(iy+3)
	call	_ComputeOutcode_ASM \.r
	ld	(iy+-1),a
	ld	de,(iy+12)
	ld	hl,(iy+9)
	call	_ComputeOutcode_ASM \.r
	ld	(iy+-3),a
m_28:	ld	a,(iy+-1)
	and	a,(iy+-3)
	jp	nz,m_31 \.r
	or	a,(iy+-1)
	jr	nz,+_
	or	a,(iy+-3)
	jp	z,m_30 \.r
_:	ld	(iy+-2),a
	rra
	jr	nc,m_19
	ld	hl,(_ymax) \.r
	jr	_ComputeNewX_ASM
m_19:	rra
	jr	nc,m_17
	ld	hl,(_ymin) \.r
_ComputeNewX_ASM:
	ld	(iy+-6),hl
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc
	push	hl
	ld	hl,(iy+9)
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc
	ex	(sp),hl
	pop	bc
	call	__imuls_ASM \.r
	ex	de,hl
	ld	hl,(iy+12)
	ld	bc,(iy+6)
	or	a,a
	sbc	hl,bc
	push	hl
	pop	bc
	ex	de,hl
	call	__idivs_ASM \.r
	ld	bc,(iy+3)
	add	hl,bc
	ld	(iy+-9),hl
	jr	m_22
m_17:	rra
	jr	nc,m_15
	ld	hl,(_xmax) \.r
	jr	_ComputeNewY_ASM
m_15:	rra
	jr	nc,m_22
	ld	hl,(_xmin) \.r
_ComputeNewY_ASM:
	ld	(iy+-9),hl
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	ld	hl,(iy+12)
	ld	bc,(iy+6)
	sbc	hl,bc
	ex	(sp),hl
	pop	bc
	call	__imuls_ASM \.r
	ex	de,hl
	ld	hl,(iy+9)
	ld	bc,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	pop	bc
	ex	de,hl
	call	__idivs_ASM \.r
	ld	bc,(iy+6)
	add	hl,bc
	ld	(iy+-6),hl
m_22:	ld	a,(iy+-2)
	cp	a,(iy+-1)
	jr	nz,+_
	ld	hl,(iy+-9)
	ld	(iy+3),hl
	ld	de,(iy+-6)
	ld	(iy+6),de
	call	_ComputeOutcode_ASM \.r
	ld	(iy+-1),a
	jp	m_28 \.r
_:	ld	hl,(iy+-9)
	ld	(iy+9),hl
	ld	de,(iy+-6)
	ld	(iy+12),de
	call	_ComputeOutcode_ASM \.r
	ld	(iy+-3),a
	jp	m_28 \.r
m_30:	ld	c,(iy+12)
	ld	hl,(iy+9)
	ld	b,(iy+6)
	ld	de,(iy+3)
	call	_Line_NoClip_ASM \.r
m_31:	ld	sp,iy
	ld	hl,_xmax \.r
	ld	de,(hl)
	inc	de
	ld	(hl),de
	ld	hl,_ymax \.r
	inc	(hl)
	ret

;-------------------------------------------------------------------------------
_Line_NoClip:
; Draws an unclipped arbitrary line
; Arguments:
;  arg0 : X0 Coord (hl)
;  arg1 : Y0 Coord (b)
;  arg2 : X1 Coord (de)
;  arg3 : Y1 Coord (c)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(iy+3)
	ld	hl,(iy+9)
	ld	b,(iy+6)
	ld	c,(iy+12)
_Line_NoClip_ASM:
	ld	a,c
	ld	(y1),a \.r
	ld	(nde),hl \.r
	push	de
	push	bc
	or	a,a
	sbc	hl,de
	ld	a,$03
	jr	nc,+_
	ld	a,$0B
_:	ld	(xStep),a \.r
	ld	(xStep2),a \.r
	ex	de,hl
	or	a,a
	sbc	hl,hl
	sbc	hl,de
	jp	p,+_ \.r
	ex	de,hl
_:	ld	(dx),hl \.r
	push	hl
	add	hl,hl
	ld	(dx1),hl \.r
	ld	(dx12),hl \.r
	or	a,a
	sbc	hl,hl
	ex	de,hl
	sbc	hl,hl
	ld	e,b
	ld	l,c
	sbc	hl,de
	ld	a,30
	adc	a,a
	ld	(yStep),a \.r
	ld	(yStep2),a \.r
	ex	de,hl
	or	a,a
	sbc	hl,hl
	sbc	hl,de
	jp	p,+_ \.r
	ex	de,hl
_:	ld	(dy),hl \.r
	add	hl,hl
	ld	(dy1),hl \.r
	ld	(dy12),hl \.r
	pop	de
	pop	af
	srl	h
	rr	l
	sbc	hl,de
	pop	bc
	ld	hl,0
	jr	nc,changeYLoop
changeXLoop:
	push	hl
	ld	l,a
	ld	h,lcdWidth/2 
	mlt	hl
	add	hl,hl
	add	hl,bc
	ld	de,(currDrawBuffer)
	add	hl,de
color4 =$+1
	ld	(hl),0
	sbc	hl,hl
	ld	h,b
	ld	l,c
	or	a,a
nde =$+1
	ld	de,0
	sbc	hl,de
	pop	hl
	ret	z
xStep	nop
dy1 =$+1
	ld	de,0
	or	a,a
	adc	hl,de
	jp	m,changeXLoop \.r
dx =$+1
	ld	de,0
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	c,changeXLoop
yStep	nop
dx1 =$+1
	ld	de,0
	sbc	hl,de
	jr	changeXLoop
changeYLoop:
	push	hl
	ld	l,a
	ld	h,lcdWidth/2 
	mlt	hl
	add	hl,hl
	add	hl,bc
	ld	de,(currDrawBuffer)
	add	hl,de
color5 =$+1
	ld	(hl),0
	pop	hl
y1 =$+1
	cp	a,0
	ret	z
yStep2	nop
dx12 =$+1
	ld	de,0
	or	a,a
	adc	hl,de
	jp	m,changeYLoop \.r
dy =$+1
	ld	de,0
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	c,changeYLoop
xStep2	nop
dy12 =$+1
	ld	de,0
	sbc	hl,de
	jr	changeYLoop

;-------------------------------------------------------------------------------
_CheckBlit_ASM:
	ld	hl,vram+lcdSize
	ld	de,(mpLcdBase)
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nz,+_
	ld	hl,vram
_:	or	a,a				; if 0, copy buffer to screen
	ret	nz
	ex	de,hl
	ret

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
	ld	a,l				; this is a uint8_t
	call	_CheckBlit_ASM \.r
	ld	bc,lcdSize
	ldir
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
	ld	l,(iy+9)			; l = y coordinate
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	push	hl
	ld	l,(iy+6)
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	push	hl
	ld	a,(iy+3)
	call	_CheckBlit_ASM \.r
	pop	bc
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	pop	bc				; number of lines to copy
	ldir
	ret

;-------------------------------------------------------------------------------
_BlitArea:
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
	ld	de,(iy+6)			; de = x coordinate
	ld	l,(iy+9)			; l = y coordinate
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de
	push	hl				; save amount to increment
	ld	a,(iy+3)
	call	_CheckBlit_ASM \.r
	pop	bc
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	ld	bc,(iy+12)
	ld	(_BlitAreaWidth_SMC),bc \.r
	push	hl
	ld	hl,lcdWidth
	or	a,a
	sbc	hl,bc
	ld	(_BlitAreaDelta_SMC),hl \.r
	pop	hl
	ld	a,(iy+15)
	ld	iy,0
_:	add	iy,de
	lea	de,iy
_BlitAreaWidth_SMC =$+1
	ld	bc,0				; smc for speedz
	ldir
_BlitAreaDelta_SMC =$+1
	ld	bc,0				; increment to next line
	add	hl,bc
	ld	de,lcdWidth			; increment to next line
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_ShiftLeft:
; Shifts whatever is in the clip left by some pixels
; Arguments:
;  arg0 : Amount to shift by
; Returns:
;  None
	.db	$F6

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
	jr	z,_
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
	.db	$F6

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
	call	_ClipRectangularRegion_ASM \.r
	sbc	a,a
	inc	a
	ret

;-------------------------------------------------------------------------------
_ScaledSprite_NoClip:
; Draws a scaled sprite to the screen
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X Coord
;  arg2 : Y Coord
;  arg5 : Width Scale (integer)
;  arg6 : Height Scale (integer)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)				; hl = x coordinate
	ld	c,(iy+9)				; c = y coordniate
	ld	de,(currDrawBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl					; de -> start draw location
	ld	hl,lcdWidth
	ld	a,(iy+15)
	ld	(NoClipSprHeightScale),a \.r
	ld	a,(iy+12)
	ld	(NoClipSprScaledWidth),a \.r		; SMC faster inner loop
	ld	iy,(iy+3)				; iy -> start of sprite struct
	ld	c,(iy+0)
	ld	b,a
	ld	a,c
	mlt	bc					; width * width scale
	ld	(NoClipSprScaledCopyAmt),bc \.r
	sbc	hl,bc					; find x offset next
	ld	(NoClipSprScaledMoveAmt),hl \.r
	ld	(NoClipSprScaledLineNext),a \.r
	ld	a,(iy+1)
	lea	hl,iy+2					; hl -> sprite data
	push	ix					; save ix sp
	ld	ixh,a					; ixh = height
NoClipSprScaledLineNext =$+1
_:	ld	c,0
	push	de					; push dest
NoClipSprScaledWidth =$+1
_:	ld	b,0
	ld	a,(hl)
_:	ld	(de),a
	inc	de
	djnz	-_					; plot width scale pixels
	inc	hl
	dec	c
	jr	nz,--_
	ex	de,hl
	ld	iy,0
	add	iy,de					; save hl location
NoClipSprScaledMoveAmt =$+1
	ld	bc,0
	add	hl,bc
NoClipSprHeightScale =$+1
	ld	a,0
	ex	de,hl					; swap dest/src
	pop	hl
_:	dec	a
	jr	z,+_
	push	bc
NoClipSprScaledCopyAmt = $+1
	ld	bc,0
	ldir						; copy previous line data
	pop	bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	add	hl,bc					; move to previous and next row
	jr	-_
_:	lea	hl,iy					; restore hl location
	dec	ixh
	jr	nz,-----_
	pop	ix					; restore ix sp
	ret

;-------------------------------------------------------------------------------
_ScaledTransparentSprite_NoClip:
; Draws a scaled sprite to the screen with transparency
; Arguments:
;  arg0 : Pointer to sprite structure
;  arg1 : X Coord
;  arg2 : Y Coord
;  arg5 : Width Scale (integer)
;  arg6 : Height Scale (integer)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)			; hl = x coordinate
	ld	c,(iy+9)			; c = y coordniate
	ld	de,(currDrawBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl				; de -> start draw location
	ld	hl,lcdWidth
	ld	a,(iy+15)
	ld	(NoClipSprTransHeightScale),a \.r
	ld	a,(iy+12)
	ld	(NoClipSprTransScaledWidth),a \.r	; SMC faster inner loop
	ld	iy,(iy+3)				; iy -> start of sprite struct
	ld	c,(iy+0)				; c = width
	ld	b,a
	ld	a,c
	mlt	bc
	sbc	hl,bc					; find x offset next
	ld	(NoClipSprTransScaledMoveAmt),hl \.r
	ld	(NoClipSprTransWidth),a \.r
	ld	a,(iy+1)
	lea	hl,iy+2					; hl -> sprite data
	push	ix					; save ix sp
	ld	ixh,a					; ixh = height
NoClipSprTransHeightScale =$+2
_:	ld	ixl,0					; ixl = height scale
_:	push	hl
NoClipSprTransWidth =$+1
	ld	c,0
NoClipSprTransScaledWidth =$+1
_:	ld	b,0
	ld	a,(hl)				; get sprite pixel
	or	a,a
	jr	nz,++_				; is transparent?
_:	inc	de
	djnz	-_
	jr	++_				; loop for next pixel
_:	ld	(de),a
	inc	de
	djnz	-_				; set and loop for next pixel
_:	inc	hl
	dec	c
	jr	nz,----_			; loop for width
	ex	de,hl
	ld	iy,0
	add	iy,de				; save hl
NoClipSprTransScaledMoveAmt =$+1
	ld	bc,0
	add	hl,bc				; get next draw location
	ex	de,hl
	pop	hl
	dec	ixl				; loop height scale
	jr	nz,-----_
	lea	hl,iy				; restore hl
	dec	ixh				; loop height
	jr	nz,------_
	pop	ix				; restore ix sp
	ret

;-------------------------------------------------------------------------------
_TransparentSprite:
; Draws a transparent sprite with clipping
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X Coord
;  arg2 : Y Coord
; Returns:
;  None
	push	ix				; save ix sp
	call	_ClipDraw_ASM \.r
	pop	ix				; restore ix sp
	ret	nc
	ld	(ClipSprTransNextAmt),a \.r
	ld	a,(iy+0)			; tmpWidth
	ld	(ClipSprTransNextLine),a \.r
	ld	a,(iy+3)			; tmpHeight
	ld	h,lcdWidth/2
	mlt	hl
	ld	bc,0				; zero ubc
	add	hl,hl
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+6)			; hl -> sprite data
	pop	iy
	push	ix
	ld	ixh,a
ClipSprTransNextLine =$+1
_:	ld	c,0
	lea	de,iy
	xor	a,a
	call	_TransparentPlot_ASM \.r	; call the transparent routine
ClipSprTransNextAmt =$+1
	ld	c,0
	add	hl,bc
	ld	de,lcdWidth			; move to next row
	add	iy,de
	dec	ixh
	jr	nz,-_
	pop	ix
	ret

_TransparentPlot_ASM_Opaque:
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
;  arg1 : X Coord
;  arg2 : Y Coord
;  arg3 : Width -- 8bits
;  arg4 : Height -- 8bits
; Returns:
;  None
	push	ix				; save ix sp
	call	_ClipDraw_ASM \.r
	pop	ix				; restore ix sp
	ret	nc
	ld	(ClipSprNextAmt),a \.r
	ld	a,(iy+0)			; tmpWidth
	ld	(ClipSprLineNext),a \.r
	ld	a,(iy+3)			; tmpHeight
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de
	ld	de,(currDrawBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+6)			; hl -> sprite data
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
	add	hl,bc
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_Sprite_NoClip:
; Places an sprite on the screen as fast as possible
; Arguments:
;  arg0 : Pointer to sprite
;  arg1 : X Coord
;  arg2 : Y Coord
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(currDrawBuffer) \.r
	ld	bc,(iy+6)			;  x coordinate
	add	hl,bc
	ld	d,lcdWidth/2
	ld	e,(iy+9)			;  y coordinate
	mlt	de
	add	hl,de
	add	hl,de
	ex	de,hl				; de = start draw location
	ld	iy,(iy+3)			; iy = sprite structure
	ld	a,(iy+1)			; sprite height
	push	af
	ld	b,0
	ld	c,(iy+0)			; sprite width
	ld	hl,lcdWidth
	sbc	hl,bc
	rr	h
	ld	a,l
	rra	
	lea	hl,iy+2				; hl = sprite data
	ld	iyh,c				; sprite width
	ld	iyl,a				; = (lcdWidth-SpriteWidth)/2
	ld	a,$f3
	sbc	a,b
	ld	(SprNcJrStep+1),a \.r	
SprNcSprHcnt:
	pop	af				; a = sprite height
	jr	SprNcLpStart
	inc	de				; needed if sprite width is odd
SprNcLpEvenW:
	ld	c,iyl				; = (lcdWidth-SpriteWidth)/2
	ex	de,hl
	add	hl,bc
	add	hl,bc
	ex	de,hl
	ld	c,iyh				; sprite width
SprNcLpStart:
	ldir
	dec	a
SprNcJrStep:	
	jr	nz,SprNcLpEvenW
	ret

;-------------------------------------------------------------------------------
_GetSprite_NoClip:
;_GetSprite:
; Grabs the data from the current draw buffer and stores it in another buffer
; Arguments:
;  arg0 : Pointer to storage buffer
;  arg1 : X Coord
;  arg2 : Y Coord
; Returns:
;  Pointer to resultant sprite
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)
	bit	0,b
	ld	b,lcdWidth/2
	mlt	bc
	ld	hl,(currDrawBuffer)
	add	hl,bc
	add	hl,bc
	jr	z,_
	ld	de,-lcdWidth*256
	add	hl,de
_:	ld	de,(iy+6)
	add	hl,de
	ld	de,(iy+3)
	push	de
	ld	a,(de)
	inc	de
	ld	(GetSprCpyAmt),a \.r
	ld	c,a
	ld	a,lcdWidth&$ff
	sub	a,c
	ld	c,a
	sbc	a,a
	inc	a
	ld	b,a
	ld	(GetSprLineOff),bc \.r
	ld	a,(de)
	inc	de
GetSprCpyAmt =$+1
_:	ld	bc,0
	ldir
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
;  arg1 : X Coord
;  arg2 : Y Coord
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)			; hl = x coordinate
	ld	c,(iy+9)			; c = y coordinate
	ld	iy,(iy+3)			; iy -> sprite struct
	ld	de,(currDrawBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	push	hl
	ld	a,(iy+0)
	ld	(NoClipSprTransNextLine),a \.r
	ld	a,(iy+1)
	lea	hl,iy+2
	pop	iy
	push	ix
	ld	ixh,a
	xor	a,a
	ld	b,a
NoClipSprTransNextLine =$+1
_:	ld	c,0
	lea	de,iy
	call	_TransparentPlot_ASM \.r
	ld	de,lcdWidth
	add	iy,de
	dec	ixh
	jr	nz,-_
	pop	ix
	ret

;-------------------------------------------------------------------------------
_ClipDraw_ASM:
; Clipping stuff
; Arguments:
;  arg0 : Pointer to sprite structure
;  arg1 : X Coord
;  arg2 : Y Coord
; Returns:
;  A  : How much to add to the sprite per iteration
;  L  : New Y coordinate
;  DE : New X coordinate
;  NC : If offscreen
	ld	ix,6					; get pointer to arguments
	add	ix,sp
	ld	hl,(ix+3)
	ld	a,(hl)
	ld	de,tmpWidth \.r
	ld	(de),a					; save tmpWidth
	ld	(tmpSpriteWidth),a \.r			; save tmpSpriteWidth
	ld	iy,0
	add	iy,de
	inc	hl
	ld	a,(hl)
	ld	(iy+3),a				; save tmpHeight
	inc	hl
	ld	(iy+6),hl				; save a ptr to the sprite data to change offsets
	ld	de,(ix+9)
	ld	hl,(_ymin) \.r
	sbc	hl,de
	jp	m,NoTopClipNeeded_ASM \.r		; check clipping against the top
	jr	z,NoTopClipNeeded_ASM
	ld	a,l					; save the clipped distance
	ld	hl,(iy+3)				; hl = tmpHeight
	or	a,a
	add	hl,de					; y coordinate - tmpHeight
	ret	nc					; return if offscreen
	ld	(iy+3),hl				; store new tmpHeight
	ld	l,a					; restore clipped amount
	ld	h,(iy+0)				; h = tmpWidth
	mlt	hl					; hl = amount of lines clipped off
	ld	de,(iy+6)				; de -> sprite data
	add	hl,de
	ld	(iy+6),hl				; store new ptr
	ld	de,(_ymin) \.r
	ld	(ix+9),de				; new y location ymin
NoTopClipNeeded_ASM:
	ex	de,hl					; hl = y coordinate
	ld	de,(_ymax) \.r
	call	_SignedCompare_ASM \.r
	ret	nc					; return if offscreen on bottom
	ld	de,(ix+9)				; de = y coordinate
	ld	hl,(iy+3)				; hl = tmpHeight
	add	hl,de
	ld	de,(_ymax) \.r
	call	_SignedCompare_ASM \.r
	jr	c,NoBottomClipNeeded_ASM		; is partially clipped bottom?
	ex	de,hl					; hl = ymax
	ld	de,(ix+9)				; de = y coordinate
	sbc	hl,de
	ld	(iy+3),hl				; store new tmpHeight
NoBottomClipNeeded_ASM:
	ld	hl,(ix+6)				; hl = x coordinate
	ld	de,(_xmin) \.r
	call	_SignedCompare_ASM \.r
	ld	hl,(ix+6)				; hl = x coordinate
	jr	nc,NoLeftClip_ASM			; is partially clipped left?
	ld	de,(iy+0)				; de = tmpWidth
	add	hl,de					
	ld	de,(_xmin) \.r
	ex	de,hl
	call	_SignedCompare_ASM \.r
	ret	nc					; return if offscreen
	ld	de,(ix+6)				; de = x coordinate
	ld	hl,(iy+6)				; hl -> sprite data
	ccf
	sbc	hl,de
	ld	(iy+6),hl				; save new ptr
	ld	hl,(iy+0)				; hl = tmpWidth
	add	hl,de
	ld	(iy+0),hl				; save new width
	ld	hl,(_xmin) \.r
	ld	(ix+6),hl				; save min x coordinate
NoLeftClip_ASM:
	ld	de,(_xmax) \.r				; de = xmax
	call	_SignedCompare_ASM \.r
	ret	nc					; return if offscreen
	ld	hl,(ix+6)				; hl = x coordinate
	ld	de,(iy+0)				; de = tmpWidth
	add	hl,de
	ld	de,(_xmax) \.r
	ex	de,hl
	call	_SignedCompare_ASM \.r			; is partially clipped right?
	jr	nc,NoRightClip_ASM
	ld	hl,(_xmax) \.r				; clip on the right
	ld	de,(ix+6)
	ccf
	sbc	hl,de
	ld	(iy+0),hl				; save new tmpWidth
NoRightClip_ASM:
	ld	a,(iy+3)
	or	a,a
	ret	z					; quit if new tmpHeight is 0 (edge case)
tmpSpriteWidth =$+1
	ld	a,0
	ld	de,(ix+6)				; de = x coordinate
	ld	l,(ix+9)				; l = y coordinate
	sub	a,(iy+0)				; compute new x width
	scf						; set carry for success
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
;      x_offset = x_offset % tilemap->tile_width;
;      y_offset = y_offset % tilemap->tile_height;
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
	ld	hl,_Sprite \.r
_:	ld	(_DrawTile_SMC),hl \.r
	push	ix
	ld	ix,0
	lea	bc,ix
	add	ix,sp
	lea	hl,ix+-12
	ld	sp,hl
	ld	iy,(ix+6)
	
	ld	b,(iy+11)
	ld	hl,(ix+12)
	ld	c,(iy+6)
	dec	c
	ld	a,l
	and	a,c
	ld	c,a
_:	srl	h
	rr	l
	djnz	-_
	ld	(ix+-4),l   ; y = y_offset / tilemap->tile_height
	ld	(ix+12),bc  ; y_offset = y_offset % tilemap->tile_height;
	
	ld	b,(iy+10)
	ld	hl,(ix+9)
	ld	c,(iy+7)
	dec	c
	ld	a,l
	and	a,c
	ld	c,a
_:	srl	h
	rr	l
	djnz	-_
	ld	a,l
	ld	(_X_Res_SMC),a \.r
	ld	hl,(iy+15)
	sbc	hl,bc
	ld	(_X_Draw_SMC),hl \.r ; x_draw = tilemap->x_loc-x_offset;
	
	or	a,a
	sbc	hl,hl
	ld	l,(iy+14)
	ld	bc,(ix+12)
	sbc	hl,bc
	ld	(ix+-12),hl
	ld	(ix+-3),0
	jp	_Y_Loop_ASM \.r

_X_Res_SMC =$+3
n_8:	ld	(ix+-1),0
	ld	(ix+-2),0
_X_Draw_SMC =$+1
	ld	hl,0
	ld	(ix+-7),hl
	ld	l,(iy+13)
	ld	h,(ix+-4)
	mlt	hl
	ld	(_Y_Next_SMC),hl \.r
	jr	_X_Loop_ASM

_InLoop_ASM:
	sbc	hl,hl
	ld	l,(ix+-1)
	ld	bc,(iy+0)
	add	hl,bc
_Y_Next_SMC =$+1
	ld	bc,0
	add	hl,bc
	ld	a,(hl)
	ld	l,a
	inc	a
	jr	z,_BlankTile_ASM
	ld	h,3
	mlt	hl
	ld	de,(iy+3)
	add	hl,de
	ld	bc,(ix+-12)
	push	bc
	ld	bc,(ix+-7)
	push	bc
	ld	bc,(hl)
	push	bc
_DrawTile_SMC =$+1
	call	0
	lea	hl,ix+-12
	ld	sp,hl
	ld	iy,(ix+6)
_BlankTile_ASM:
	or	a,a
	sbc	hl,hl
	ld	l,(iy+7)
	ld	bc,(ix+-7)
	add	hl,bc
	ld	(ix+-7),hl
	inc	(ix+-1)
	inc	(ix+-2)

_X_Loop_ASM:
	ld	a,(iy+9)
	cp	a,(ix+-2)
	jr	nz,_InLoop_ASM
	or	a,a
	sbc	hl,hl
	ld	l,(iy+6)
	ld	bc,(ix+-12)
	add	hl,bc
	ld	(ix+-12),hl
	inc	(ix+-4)
	inc	(ix+-3)

_Y_Loop_ASM:
	ld	a,(iy+8)
	cp	a,(ix+-3)
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
;  arg3 : New Tile Index
; Returns:
;  A pointer to an indexed tile in the tilemap (so it can be looked at or changed)
; C Function:
;  uint8_t *gfx_TilePtr(gfx_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset, uint8_t tile) {
;      return &tilemap->map[(x_offset/tilemap->tile_width)+((y_offset/tilemap->tile_height)*tilemap->width)];
;  }
	push	ix
	ld	ix,0
	add	ix,sp
	ld	iy,(ix+6)
	ld	b,(iy+14)
	ld	hl,(ix+9)
_:	srl	h
	rr	l
	djnz	-_
	ex	de,hl
	ld	b,(iy+15)
	ld	hl,(ix+12)
_:	srl	h
	rr	l
	djnz	-_
	ld	h,(iy+9)
	mlt	hl
	add	hl,de
	ld	de,(iy+0)
	add	hl,de
	pop	ix
	ret

;-------------------------------------------------------------------------------
_TilePtrMapped:
; Returns a direct pointer to the input tile
; Arguments:
;  arg0 : Tilemap Struct
;  arg1 : X Map Offset (uint8_t)
;  arg2 : Y Map Offset (uint8_t)
; Returns:
;  A pointer to the indexed tile in the tilemap (so it can be looked at or changed)
	push	ix
	ld	ix,0
	add	ix,sp
	ld	iy,(ix+6)
	ld	h,(ix+12)	; y offset
	ld	l,(iy+13)
	mlt	hl
	ex	de,hl
	sbc	hl,hl
	ld	l,(ix+9)	; x offset
	ld	bc,(iy+0)	; pointer to map
	add	hl,de
	add	hl,bc
	pop	ix
	ret

;-------------------------------------------------------------------------------
_GetTextX:
; Gets the X position of the text cursor
; Arguments:
;  None
; Returns:
;  X Text cursor posistion
	ld	hl,(TextXPos_SMC) \.r
	ret

;-------------------------------------------------------------------------------
_GetTextY:
; Gets the Y position of the text cursor
; Arguments:
;  None
; Returns:
;  Y Text cursor posistion
	ld	a,(TextYPos_SMC) \.r
	ret

;-------------------------------------------------------------------------------
_SetTextBGColorC:
; Sets the background text color for text routines
; Arguments:
;  arg0 : Color index to set BG to
; Returns:
;  Previous text color palette index
	pop	hl
	pop	de
	push	de
	push	hl
	ld	hl,TextBGColor_SMC \.r
	ld	a,(hl)
	ld	(hl),e
	ret

;-------------------------------------------------------------------------------
_SetTextFGColorC:
; Sets the foreground text color for text routines
; Arguments:
;  arg0 : Color index to set FG to
; Returns:
;  Previous text color palette index
	pop	hl
	pop	de
	push	de
	push	hl
	ld	hl,TextFGColor_SMC \.r
	ld	a,(hl)
	ld	(hl),e
	ret

;-------------------------------------------------------------------------------
_SetTextTransparentColorC:
; Sets the transparency text color for text routines
; Arguments:
;  arg0 : Color index to set transparent text to
; Returns:
;  Previous text color palette index
	pop	hl
	pop	de
	push	de
	push	hl
	ld	hl,TextTransColor_1_SMC \.r
	ld	a,(hl)
	ld	(hl),e
	ld	hl,TextTransColor_2_SMC \.r
	ld	(hl),e
	ret
	
;-------------------------------------------------------------------------------
_SetTextXY:
; Sets the transparency text color for text routines
; Arguments:
;  arg0 : Text X Pos
;  arg1 : Text Y Pos
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	de,TextXPos_SMC \.r
	ldi
	ldi
	inc	hl
	ld	a,(hl)
	ld	(TextYPos_SMC),a \.r
	ret

;-------------------------------------------------------------------------------
_PrintStringXY:
; Places a string at the given coordinates
; Arguments:
;  arg0 : Pointer to string
;  arg1 : Text X Pos
;  arg2 : Text Y Pos
; Returns:
;  None
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
	jr	+_

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
_:	ld	a,(hl)
	or	a,a
	ret	z
	call	_PrintChar_ASM \.r
	inc	hl
	jr	-_

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
	ld	hl,UseLargeFont_SMC \.r
	cp	a,c
	jr	z,+_
	jr	++_
_:	dec	a
	jr	z,_BothAreOne
	inc	a
_:	or	a,a
	ret	z
	ld	(de),a
	ld	a,c
	or	a,a
	ret	z
	ld	(TextHeightScale_SMC),a \.r
	ld	(hl),1
	ret
_BothAreOne:
	ld	(hl),a
	ld	a,1
	ld	(de),a
	ret

;-------------------------------------------------------------------------------
_PrintChar:
; Places a character at the current cursor position
; Arguments:
;  arg0 : Character to draw
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	a,(iy+3)
_PrintChar_ASM:
	push	ix				; save stack pointer
	push	hl				; save hl pointer if string
	ld	e,a				; e = char
MonoFlag_SMC =$+1
	ld	a,0
	or	a,a
	jr	nz,+_
	sbc	hl,hl
	ld	l,e				; hl = character
	ld	bc,(CharSpacing_ASM) \.r
	add	hl,bc
	ld	a,(hl)				; a = char width
TextXPos_SMC = $+1
_:	ld	bc,0
	sbc	hl,hl
	ld	l,a
	ld	ixh,a				; ixh = char width
	ld	a,(TextWidthScale_SMC) \.r
	ld	h,a
	mlt	hl
	add	hl,bc
	ld	(TextXPos_SMC),hl \.r
TextYPos_SMC = $+1
	ld	l,0
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,bc
	ld	bc,(currDrawBuffer)
	add	hl,bc
	ex	de,hl				; de = draw location
	ld	a,l				; l = character
	sbc	hl,hl
	ld	l,a				; hl = character
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(TextData_ASM) \.r		; get text data array
	add	hl,bc
	ld	iy,0
	ld	ixl,8
UseLargeFont_SMC =$+1
	ld	a,0
	or	a,a
	jr	nz,_PrintLargeFont_ASM
_:	ld	c,(hl)				; c = 8 pixels
	add	iy,de				; get draw location
	lea	de,iy
	ld	b,ixh
TextBGColor_SMC =$+1
_:	ld	a,255
	rlc	c
	jr	nc,+_
TextFGColor_SMC =$+1
	ld	a,0
TextTransColor_1_SMC =$+1
_:	cp	a,255				; check if transparent
	jr	z,+_
	ld	(de),a
_:	inc	de				; move to next pixel
	djnz	---_
	ld	de,lcdwidth
	inc	hl
	dec	ixl
	jr	nz,----_
	pop	hl				; restore hl and stack pointer
	pop	ix
	ret

;-------------------------------------------------------------------------------
_PrintLargeFont_ASM:
; Prints in scaled font for prosperity
; This is so that way unscaled font can still be reasonably fast
; Returns:
;  None
TextHeightScale_SMC =$+1
_:	ld	b,1
	push	hl
	ld	c,(hl)				; c = 8 pixels
_hscale:
	push	bc
	add	iy,de				; get draw location
	lea	de,iy
	ld	b,ixh
_:	ld	a,(TextBGColor_SMC) \.r
TextWidthScale_SMC =$+1
	ld	l,1
	rlc	c
	jr	nc,+_
	ld	a,(TextFGColor_SMC) \.r
TextTransColor_2_SMC =$+1
_:	cp	a,255				; check if transparent
	jr	z,+_
	
wscale1:	
	ld	(de),a
	inc	de
	dec	l
	jr	nz,wscale1
	djnz	--_
	jr	_done
_:
wscale2:
	inc	de
	dec	l
	jr	nz,wscale2			; move to next pixel
	djnz	---_
_done:
	ld	de,lcdwidth
	
	pop	bc
	djnz	_hscale
	
	pop	hl
	inc	hl
	dec	ixl
	
	jr	nz,----_
	pop	hl				; restore hl and stack pointer
	pop	ix
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
	ld	hl,(iy+3)
	ld	c,(iy+6)
_PrintUInt_ASM:
	ld	a,8
	sub	a,c
	ret	c
	ld	c,a
	ld	b,8
	mlt	bc
	ld	a,c
	ld	(Offset_SMC),a \.r
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
	jp	_PrintChar_ASM \.r
 
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
	ld	c,(iy+6)
	ld	hl,(iy+3)
	bit	7,(iy+5)
	jr	z,+_
	push	bc
	push	hl
	pop	bc
	sbc	hl,hl
	sbc	hl,bc
	ld	a,'-'
	call	_PrintChar_ASM \.r
	pop	bc
_:	jp	_PrintUInt_ASM \.r

;-------------------------------------------------------------------------------
_GetStringWidth:
; Gets the width of a string
; Arguments:
;  arg0 : Pointer to string
; Returns:
;  Width of string in pixels
	pop	de
	pop	hl
	push	hl
	push	de
	ld	de,0
_:	ld	a,(hl)
	or	a,a
	jr	z,+_
	push	hl
	call	_GetCharWidth_ASM \.r
	pop	hl
	inc	hl
	jr	-_
_:	ex	de,hl
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
	ld	a,(iy+3)
_GetCharWidth_ASM:
	sbc	hl,hl
	ld	l,a
	ld	a,(MonoFlag_SMC) \.r
	or	a,a
	jr	nz,+_
	ld	bc,(CharSpacing_ASM) \.r
	add	hl,bc
	ld	a,(hl)
_:	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	a,(TextWidthScale_SMC) \.r
	ld	h,a
	mlt	hl
	add	hl,de
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
_SetCustomFontData:
; Sets the font to be custom
; Arguments:
;  arg0 : Pointer to font data
;  Set Pointer to NULL to use default font
; Returns:
;  None
	pop	de
	pop	hl
	push	hl
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	nz,+_
	ld	hl,Char000 \.r
_:	ld	(TextData_ASM),hl \.r
	ret

;-------------------------------------------------------------------------------
_SetCustomFontSpacing:
; Sets the font to be custom spacing
; Arguments:
;  arg0 : Pointer to font spacing
;  Set Pointer to NULL to use default font spacing
; Returns:
;  None
	pop	de
	pop	hl
	push	hl
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	nz,+_
	ld	hl,DefaultCharSpacing_ASM \.r
_:	ld	(CharSpacing_ASM),hl \.r
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
	ld	a,e
	ld	(MonoFlag_SMC),a \.r
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
	lea	hl,ix+-39
	ld	sp,hl
	sbc	hl,hl
	ld	(ix+-15),hl
	ld	(ix+-18),hl
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
	ld	(ix+-24),hl
	ld	de,(ix+6)
	ld	hl,(ix+12)
	or	a,a
	sbc	hl,de
	ld	(ix+-39),hl
	ld	de,(ix+9)
	ld	hl,(ix+15)
	or	a,a
	sbc	hl,de
	ld	(ix+-36),hl
	ld	de,(ix+6)
	ld	hl,(ix+18)
	or	a,a
	sbc	hl,de
	ld	(ix+-21),hl
	ld	de,(ix+9)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,de
	ld	(ix+-30),hl
	ld	de,(ix+15)
	ld	hl,(ix+21)
	or	a,a
	sbc	hl,de
	ld	(ix+-33),hl
	ld	de,(ix+21)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	jp	nz,t_17 \.r
	ld	hl,(ix+6)
	ld	(ix+-6),hl
	ld	(ix+-3),hl
	ld	de,(ix+12)
	call	_SignedCompare_ASM \.r
	jr	c,t_8
	ld	(ix+-3),de
	jr	t_12
t_8:	ld	hl,(ix+12)
	ld	de,(ix+-6)
	call	_SignedCompare_ASM \.r
	jr	c,t_12
	ld	de,(ix+12)
	ld	(ix+-6),de
t_12:	ld	hl,(ix+-3)
	ld	de,(ix+18)
	call	_SignedCompare_ASM \.r
	jr	c,t_11	
	ld	(ix+-3),de
	jr	t_13
t_11:	ld	hl,(ix+18)
	ld	de,(ix+-6)
	call	_SignedCompare_ASM \.r
	jr	c,t_13
	ld	de,(ix+18)
	ld	(ix+-6),de
t_13:	ld	bc,(ix+-3)
	ld	de,(ix+9)
	ld	hl,(ix+-6)
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
	ld	(ix+-27),hl
	jr	t_27
t_19:	dec	hl
	ld	(ix+-27),hl
t_27:	ld	bc,(ix+9)
	ld	(ix+-12),bc
	jp	t_26 \.r
t_24:	ld	hl,(ix+-15)
	ld	bc,(ix+-36)
	call	__idivs_ASM \.r
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix+-3),hl
	ld	hl,(ix+-18)
	ld	bc,(ix+-30)
	call	__idivs_ASM \.r
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix+-6),hl
	ex	de,hl
	ld	bc,(ix+-39)
	ld	hl,(ix+-15)
	add	hl,bc
	ld	(ix+-15),hl
	ld	bc,(ix+-21)
	ld	hl,(ix+-18)
	add	hl,bc
	ld	(ix+-18),hl
	ex	de,hl
	ld	de,(ix+-3)
	or	a,a
	sbc	hl,de
	add	hl,de
	jp	p,t__31 \.r
	jp	pe,t_23 \.r
	jr	t__32
t__31:	jp	po,t_23 \.r
t__32:	ex	de,hl
	ld	(ix+-3),de
	ld	(ix+-6),hl
t_23:	ld	de,(ix+-3)
	ld	hl,(ix+-6)
	or	a,a
	sbc	hl,de
	ld	bc,(ix+-12)
	inc	hl
	push	hl
	push	bc
	push	de
HLine1_SMC =$+1
	call	0
	lea	hl,ix+-39
	ld	sp,hl
	ld	bc,(ix+-12)
	inc	bc
	ld	(ix+-12),bc
t_26:	ld	hl,(ix+-27)
	or	a,a
	sbc	hl,bc
	jp	p,+_ \.r
	jp	pe,t_24 \.r
	jr	++_
_:	jp	po,t_24 \.r
_:	ld	bc,(ix+15)
	ld	hl,(ix+-12)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix+-24)
	call	__imuls_ASM \.r
	ld	(ix+-15),hl
	ld	bc,(ix+9)
	ld	hl,(ix+-12)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix+-21)
	call	__imuls_ASM \.r
	ld	(ix+-18),hl
	jp	t_34 \.r
t_32:	ld	hl,(ix+-15)
	ld	bc,(ix+-33)
	call	__idivs_ASM \.r
	ld	bc,(ix+12)
	add	hl,bc
	ld	(ix+-3),hl
	ld	hl,(ix+-18)
	ld	bc,(ix+-30)
	call	__idivs_ASM \.r
	ld	bc,(ix+6)
	add	hl,bc
	ld	(ix+-6),hl
	ex	de,hl
	ld	bc,(ix+-21)
	ld	hl,(ix+-18)
	add	hl,bc
	ld	(ix+-18),hl
	ld	bc,(ix+-24)
	ld	hl,(ix+-15)
	add	hl,bc
	ld	(ix+-15),hl
	ex	de,hl
	ld	de,(ix+-3)
	or	a,a
	sbc	hl,de
	add	hl,de
	jp	p,+_ \.r
	jp	pe,+++_ \.r
	jr	++_
_:	jp	po,+++_ \.r
_:	ex	de,hl
	ld	(ix+-3),de
	ld	(ix+-6),hl
_:	or	a,a
	sbc	hl,de
	ld	bc,(ix+-12)
	inc	hl
	push	hl
	push	bc
	push	de
HLine2_SMC =$+1
	call	0
	lea	hl,ix+-39
	ld	sp,hl
	ld	bc,(ix+-12)
	inc	bc
	ld	(ix+-12),bc
t_34:	ld	bc,(ix+-12)
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

_Polygon_NoClip:
	ld	hl,_Line_NoClip \.r
	jr	+_
_Polygon:
	ld	hl,_Line \.r
_:	ld	(_LineType0_SMC),hl \.r
	ld	(_LineType1_SMC),hl \.r
	push	ix
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+9)
	dec	hl
	ld	(ix+9),hl			; decrement the number of points
	sbc	hl,hl
	ld	(tmpWidth),hl \.r		; set the for loop counter to 0 (tmpWidth is used as a temp variable)
	jr	p_3
p_1:
	ld	hl,(tmpWidth) \.r
	add	hl,hl
	inc	hl
	inc	hl
	inc	hl
	push	hl
	pop	bc
	add	hl,hl
	add	hl,hl
	sbc	hl,bc
	ld	bc,(ix+6)
	add	hl,bc
	ld	bc,(hl)
	push	bc			; push the last argument
	dec	hl
	dec	hl
	dec	hl
	ld	bc,(hl)
	push	bc			; push the third argument
	dec	hl
	dec	hl
	dec	hl
	ld	bc,(hl)
	push	bc			; push the second argument
	dec	hl
	dec	hl
	dec	hl
	ld	bc,(hl)
	push	bc			; push the first argument
_LineType0_SMC =$+1
	call	0
	ld	sp,ix
	ld	hl,(tmpWidth) \.r
	inc	hl
	ld	(tmpWidth),hl \.r		; increment the counter
p_3:	ld	bc,(ix+9)
	or	a,a
	sbc	hl,bc
	jr	c,p_1			; check if drawn all the points
	ld	de,(ix+6)
	add	hl,bc
	inc	hl
	add	hl,hl
	dec	hl
	push	hl
	pop	bc
	add	hl,hl
	add	hl,hl
	sbc	hl,bc
	add	hl,de
	ld	bc,(hl)
	push	bc			; push the last argument
	dec	hl
	dec	hl
	dec	hl
	ld	bc,(hl)
	push	bc			; push the third argument
	ex	de,hl
	inc	hl
	inc	hl
	inc	hl
	ld	bc,(hl)
	push	bc			; push the second argument
	dec	hl
	dec	hl
	dec	hl
	ld	bc,(hl)
	push	bc			; push the first argument
_LineType1_SMC =$+1
	call	0
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_LZDecompress:
; Decompresses in lz77 format the input data into the output buffer
; Arguments:
;  arg0 : Pointer to Input Buffer
;  arg1 : Pointer to Output Buffer
;  arg2 : Input Buffer Size
; Returns:
;  None
	push	ix
	ld	ix,0
	lea	bc,ix
	add	ix,sp
	lea	hl,ix+-20
	ld	sp,hl
	inc	bc
	ld	hl,(ix+12)
	or	a,a
	sbc	hl,bc
	jp	c,l_19 \.r
	ld	hl,(ix+6)
	ld	a,(hl)
	ld	(ix+-7),a
	ld	(ix+-3),bc
	dec	bc
	ld	(ix+-6),bc
l_17:	ld	bc,(ix+-3)
	ld	hl,(ix+6)
	add	hl,bc
	ld	a,(hl)
	ld	(ix+-8),a
	ld	bc,(ix+-3)
	inc	bc
	ld	(ix+-3),bc
	ld	a,(ix+-8)
	cp	a,(ix+-7)
	jp	nz,l_16 \.r
	ld	bc,(ix+-3)
	ld	hl,(ix+6)
	add	hl,bc
	ld	(ix+-14),hl
	ld	a,(hl)
	or	a,a
	jr	nz,l_13
	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	add	hl,bc
	ld	a,(ix+-7)
	ld	(hl),a
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
	ld	bc,(ix+-3)
	inc	bc
	ld	(ix+-3),bc
	jr	l_18
l_13:	ld	bc,(ix+-14)
	push	bc
	pea	ix+-17
	call	_LZ_ReadVarSize_ASM \.r
	pop	bc
	pop	bc
	ld	bc,(ix+-3)
	add	hl,bc
	ld	(ix+-3),hl
	ld	bc,(ix+6)
	add	hl,bc
	push	hl
	pea	ix+-20
	call	_LZ_ReadVarSize_ASM \.r
	pop	bc
	pop	bc
	ld	bc,(ix+-3)
	add	hl,bc
	ld	(ix+-3),hl
	ld	bc,0
	ld	(ix+-11),bc
	jr	l_11
l_9:	ld	bc,(ix+-20)
	ld	hl,(ix+-6)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix+9)
	add	hl,bc
	ex	de,hl
	ld	hl,(ix+9)
	ld	bc,(ix+-6)
	add	hl,bc
	ld	a,(de)
	ld	(hl),a
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
	ld	bc,(ix+-11)
	inc	bc
	ld	(ix+-11),bc
l_11:	ld	bc,(ix+-17)
	ld	hl,(ix+-11)
	or	a,a
	sbc	hl,bc
	jr	c,l_9
	jr	l_18
l_16:	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	add	hl,bc
	ld	a,(ix+-8)
	ld	(hl),a
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
l_18:	ld	bc,(ix+12)
	ld	hl,(ix+-3)
	or	a,a
	sbc	hl,bc
	jp	c,l_17 \.r
l_19:	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_LZDecompressSprite:
; Decompresses a sprite that is LZ77 compressed from ConvPNG
	ld	hl,-23
	call	__frameset
	ld	hl,(ix+6)
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex.s	de,hl
	ld	(ix+-17),hl
	or	a,a
	ld	bc,1
	sbc	hl,bc
	jp	c,d_19 \.r
	ld	iy,(ix+6)
	ld	a,(iy+2)
	ld	(ix+-8),a
	dec	bc
	ld	(ix+-6),bc
	ld	bc,3
	ld	(ix+-3),bc
d_17:	ld	bc,(ix+-3)
	ld	hl,(ix+6)
	add	hl,bc
	ld	a,(hl)
	ld	(ix+-7),a
	ld	bc,(ix+-3)
	inc	bc
	ld	(ix+-3),bc
	ld	a,(ix+-7)
	cp	a,(ix+-8)
	jp	nz,d_16 \.r
	ld	bc,(ix+-3)
	ld	hl,(ix+6)
	add	hl,bc
	ld	(ix+-14),hl
	ld	a,(hl)
	or	a,a
	jr	nz,d_13
	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	add	hl,bc
	ld	a,(ix+-8)
	ld	(hl),a
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
	ld	bc,(ix+-3)
	inc	bc
	ld	(ix+-3),bc
	jr	d_18
d_13:	ld	bc,(ix+-14)
	push	bc
	pea	ix+-20
	call	_LZ_ReadVarSize_ASM \.r
	pop	bc
	pop	bc
	ld	bc,(ix+-3)
	add	hl,bc
	ld	(ix+-3),hl
	ld	bc,(ix+6)
	add	hl,bc
	push	hl
	pea	ix+-23
	call	_LZ_ReadVarSize_ASM \.r
	pop	bc
	pop	bc
	ld	bc,(ix+-3)
	add	hl,bc
	ld	(ix+-3),hl
	ld	bc,0
	ld	(ix+-11),bc
	jr	d_11
d_9:	ld	bc,(ix+-23)
	ld	hl,(ix+-6)
	or	a,a
	sbc	hl,bc
	ld	bc,(ix+9)
	add	hl,bc
	push	hl
	pop	iy
	ld	hl,(ix+9)
	ld	bc,(ix+-6)
	add	hl,bc
	ld	a,(iy)
	ld	(hl),a
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
	ld	bc,(ix+-11)
	inc	bc
	ld	(ix+-11),bc
d_11:	ld	bc,(ix+-20)
	ld	hl,(ix+-11)
	or	a,a
	sbc	hl,bc
	jr	c,d_9
	jr	d_18
d_16:	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	add	hl,bc
	ld	a,(ix+-7)
	ld	(hl),a
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
d_18:	ld	bc,(ix+-17)
	ld	hl,(ix+-3)
	or	a,a
	sbc	hl,bc
	jp	c,d_17 \.r
d_19:	ld	sp,ix
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
	ld	a,(ix+0)
	sbc	hl,hl
	ld	l,a
	ld	c,a
	push	hl
	ld	(_FlipHorizWidth_SMC),a \.r
	add	hl,hl
	ld	(_FlipHorizDelta_SMC),hl \.r
	ld	a,(ix+1)
	pop	hl
	lea	de,ix+2
	add	hl,de
	ld	ix,(iy+6)
	ld	(ix+1),a
	ld	(ix+0),c
	lea	de,ix+2
	ex	(sp),ix
_FlipHorizWidth_SMC =$+1
_:	ld	b,0
	ld	c,a
_:	dec	hl
	ld	a,(hl)
	ld	(de),a
	inc	de
	djnz	-_
	ld	a,c
_FlipHorizDelta_SMC =$+1
	ld	bc,0
	add	hl,bc
	dec 	a
	jr	nz,--_
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
	ld	(_FlipVertDelta_SMC),a \.r
	neg
	ld	(_FlipVertWidth_SMC),a \.r
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
_FlipVertWidth_SMC =$+1
_:	ld	bc,0
	ldir
_FlipVertDelta_SMC =$+1
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
	ld	a,(ix+0) 			; a = width
	ld	e,(ix+1)			; c = height
	ld	(_RotateCWidth_SMC),a \.r
	lea	hl,ix+2
	ld	ix,(iy+6)
	ld	(ix+0),e
	ld	(ix+1),a
	lea	iy,ix+1
	add	iy,de
	ld	c,e
	push	ix
_RotateCWidth_SMC =$+1
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
	ld	a,(ix+0) 			; a = width
	ld	e,(ix+1)			; c = height
	ld	(_RotateCCWidth_SMC),a \.r
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
_RotateCCWidth_SMC =$+1
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
	ld	c,(ix+0) 			; a = width
	ld	b,(ix+1)			; c = height
	lea	de,ix+2
	ld	ix,(iy+6)
	ld	(ix+0),c 			; a = width
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
; Inner library routines
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_LZ_ReadVarSize_ASM:
; LZ Decompression Subroutine
	push	ix
	ld	ix,0
	lea	de,ix
	add	ix,sp
	lea	hl,ix+-12
	ld	sp,hl
	ld	(ix+-3),de
	ld	(ix+-6),de
_:	ld	de,0
	ld	hl,(ix+9)
	ld	a,(hl)
	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	(ix+-9),hl
	ld	bc,(ix+9)
	inc	bc
	ld	(ix+9),bc
	ld	a,(ix+-9)
	and	a,127
	sbc	hl,hl
	ld	l,a
	ld	(ix+-12),hl
	ld	hl,(ix+-3)
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	push	hl
	pop	bc
	ld	hl,(ix+-12)
	call	__ior
	ld	(ix+-3),hl
	ld	bc,(ix+-6)
	inc	bc
	ld	(ix+-6),bc
	ld	a,(ix+-9)
	and	a,128
	sbc	hl,hl
	ld	l,a
	sbc	hl,de
	jr	nz,-_
	ld	hl,(ix+6)
	ld	bc,(ix+-3)
	ld	(hl),bc
	ld	hl,(ix+-6)
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
	ld	hl,-lcdHeight
	add	hl,de
	ret	c
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
	jp	p,_ \.r
	ret	pe
	add	hl,de
_:	ret	po
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_ClipRectangularRegion_ASM:
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
	call	_SignedCompare_ASM \.r
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
_SignedCompare_ASM:
	or	a,a
	sbc	hl,de
	add	hl,hl
	ret	po
	ccf
	ret

;-------------------------------------------------------------------------------
_SetFullScreenClipping_ASM:
; Sets the clipping  to the entire screen
; Inputs:
;  None
; Outputs:
;  HL=0
	ld	hl,lcdWidth
	ld	(_xmax),hl \.r
	ld	hl,lcdHeight
	ld	(_ymax),hl \.r
	ld	l,0
	ld	(_xmin),hl \.r
	ld	(_ymin),hl \.r
	ret

;-------------------------------------------------------------------------------
__idivs_ASM:
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
__imuls_ASM:
__imulu_ASM:
; Performs (un)signed integer multiplication
; Inputs:
;  HL : Operand 1
;  BC : Operand 2
; Outputs:
;  HL = HL*BC

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

 .endLibrary
