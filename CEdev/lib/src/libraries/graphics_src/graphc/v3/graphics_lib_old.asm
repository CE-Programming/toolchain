#include "..\..\..\include\relocation.inc"
#include "..\..\..\include\ti84pce.inc"

 .libraryName		"GRAPHC"          ; Name of library
 .libraryVersion	3                 ; Version information (1-255)
 
;-------------------------------------------------------------------------------
; v1 functions -- No longer able to insert or move (Can optimize/fix though)
;-------------------------------------------------------------------------------
 .function "gc_InitGraph",_InitGraph
 .function "gc_CloseGraph",_CloseGraph
 .function "gc_SetColorIndex",_SetColorIndex
 .function "gc_SetDefaultPalette",_SetDefaultPalette
 .function "gc_SetPalette",_SetPalette
 .function "gc_FillScrn",_FillScrn
 .function "gc_ClipSetPixel",_ClipSetPixel
 .function "gc_ClipGetPixel",_ClipGetPixel
 .function "gc_GetColor",_GetColor
 .function "gc_SetColor",_SetColor
 .function "gc_NoClipLine",_NoClipLine
 .function "gc_NoClipRectangle",_NoClipRectangle
 .function "gc_NoClipRectangleOutline",_NoClipRectangleOutline
 .function "gc_NoClipHorizLine",_NoClipHorizLine
 .function "gc_NoClipVertLine",_NoClipVertLine
 .function "gc_NoClipCircle",_NoClipCircle
 .function "gc_ClipCircleOutline",_ClipCircleOutline
 .function "gc_DrawBuffer",_DrawBuffer
 .function "gc_DrawScreen",_DrawScreen
 .function "gc_SwapDraw",_SwapDraw
 .function "gc_DrawState",_DrawState
 .function "gc_PrintChar",_PrintChar
 .function "gc_PrintInt",_PrintInt
 .function "gc_PrintUnsignedInt",_PrintUnsignedInt
 .function "gc_PrintString",_PrintString
 .function "gc_PrintStringXY",_PrintStringXY
 .function "gc_StringWidth",_StringWidthC
 .function "gc_CharWidth",_CharWidth
 .function "gc_TextX",_TextX
 .function "gc_TextY",_TextY
 .function "gc_SetTextXY",_SetTextXY
 .function "gc_SetTextColor",_SetTextColor
 .function "gc_SetTransparentColor",_SetTransparentColor
 .function "gc_NoClipDrawSprite",_NoClipDrawSprite
 .function "gc_NoClipDrawTransparentSprite",_NoClipDrawTransparentSprite
 .function "gc_NoClipGetSprite",_NoClipGetSprite
 .function "gc_SetCustomFontData",_SetCustomFontData
 .function "gc_SetCustomFontSpacing",_SetCustomFontSpacing
 .function "gc_SetFontMonospace",_SetFontMonospace
;-------------------------------------------------------------------------------
; v2 functions -- No longer able to insert or move (Can optimize/fix though)
;-------------------------------------------------------------------------------
 .function "gc_SetClipWindow",_SetClipWindow
 .function "gc_ClipRegion",_ClipRegion
 .function "gc_ShiftWindowDown",_ShiftWindowDown
 .function "gc_ShiftWindowUp",_ShiftWindowUp
 .function "gc_ShiftWindowLeft",_ShiftWindowLeft
 .function "gc_ShiftWindowRight",_ShiftWindowRight
 .function "gc_ClipRectangle",_ClipRectangle
 .function "gc_ClipRectangleOutline",_ClipRectangleOutline
 .function "gc_ClipHorizLine",_ClipHorizLine
 .function "gc_ClipVertLine",_ClipVertLine
 .function "gc_ClipDrawSprite",_ClipDrawSprite
 .function "gc_ClipDrawTransparentSprite",_ClipDrawTransparentSprite
 .function "gc_NoClipDrawScaledSprite",_NoClipDrawScaledSprite
 .function "gc_NoClipDrawScaledTransparentSprite",_NoClipDrawScaledTransparentSprite
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
 .function "gc_ClipCircle",_ClipCircle
 .function "gc_ClipLine",_ClipLine
 .function "gc_ClipDrawBGTilemap",_ClipDrawBGTilemap
 .function "gc_ClipDrawFGTilemap",_ClipDrawFGTilemap
 .function "gc_NoClipDrawBGTilemap",_NoClipDrawBGTilemap
 .function "gc_NoClipDrawFGTilemap",_NoClipDrawFGTilemap
 .function "gc_TilePtr",_TilePtr
 .function "gc_TilePtrMapped",_TilePtrMapped
 .function "gc_LZDecompress",_LZDecompress

 .beginDependencies
 .endDependencies

;-------------------------------------------------------------------------------
; Used throughout the library
lcdSize                 equ lcdWidth*lcdHeight
currentDrawingBuffer    equ 0E30014h
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_SetClipWindow:
; Sets the clipping window for clipped routines
; Arguments:
;  __frame_arg0 : Xmin
;  __frame_arg1 : Ymin
;  __frame_arg2 : Xmax
;  __frame_arg3 : Ymax
;  Must be within (0,0,320,240)
; Returns:
;  None
	call	_SetFullScreenClipping_ASM \.r
	ld	iy,0
	add	iy,sp
	call	_ClipRectangularRegion_ASM \.r
	lea	hl,iy
	ret	c
	ld	de,_xmin \.r
	ld	bc,12
	ldir
	ret

;-------------------------------------------------------------------------------
_SetColorIndex:
; Sets the global color index for all routines
; Arguments:
;  __frame_arg0 : Color Index
; Returns:
;  Previous global color index
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,(color1) \.r
	ld	d,a
	ld	a,e
	ld	(color1),a \.r
	ld	(color3),a \.r
	ld	(color4),a \.r
	ld	(color5),a \.r
	ld	(color6),a \.r
	ld	(color7),a \.r
	ld	a,d
	ret

;-------------------------------------------------------------------------------
_InitGraph:
; Sets up the graphics canvas (8bpp, default palette)
; Arguments:
;  None
; Returns:
;  None
	call	$000374
	call	_SetFullScreenClipping_ASM \.r
	ld	hl,currentDrawingBuffer
	ld	a,lcdBpp8
_:	ld	de,vram
	ld	(hl),de
	ld	hl,mpLcdCtrl
	ld	(hl),a
	ld	l,mpLcdIcr&$FF
	ld	(hl),4
	jr	_SetDefaultPalette

;-------------------------------------------------------------------------------
_CloseGraph:
; Closes the graphics library and sets up for the TI-OS
; Arguments:
;  None
; Returns:
;  None
	ld	hl,mpLcdBase
	ld	a,lcdBpp16
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
_FillScrn:
; Fills the screen with the specified color index
; Arguments:
;  __frame_arg0 : Color Index
; Returns:
;  None
	pop	hl
	pop	bc
	push	bc
	push	hl
	ld	a,c
	ld	bc,lcdSize
	ld	hl,(currentDrawingBuffer)
	jp	_MemSet_ASM \.r

;-------------------------------------------------------------------------------
_SetPalette:
; Sets the palette starting at 0x00 index and onward
; Arguments:
;  __frame_arg0 : Pointer to palette
;  __frame_arg1 : Size of palette in bytes
; Returns:
;  None
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	ld	de,mpLcdPalette
	ldir
	ret

;-------------------------------------------------------------------------------
_GetColor:
; Gets the color of a given pallete entry
; Arguments:
;  __frame_arg0 : Color index
; Returns:
;  16 bit color palette entry
	ld	hl,3
	add	hl,sp
	ld	de,mpLcdPalette/2
	ld	e,(hl)
	ex	de,hl
	add	hl,hl
	ld	hl,(hl)
	ret

;-------------------------------------------------------------------------------
_SetColor:
; Sets the color of a given pallete entry
; Arguments:
;  __frame_arg0 : Palette index
;  __frame_arg1 : 1555 color entry
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	de,mpLcdPalette/2
	ld	e,(hl)
	inc	hl
	inc	hl
	inc	hl
	ex	de,hl
	add	hl,hl
	ex	de,hl
	ldi
	ldi
	ret

;-------------------------------------------------------------------------------
_ClipGetPixel:
; Gets the color index of a pixel
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
; Returns:
;  Color index of X,Y Coord
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+3)
	ld	de,(iy+6)
	xor	a,a
	call	_PixelPtr_ASM \.r
	ret	c
	ld	a,(hl)
	ret

;-------------------------------------------------------------------------------
_ClipSetPixel:
; Sets the color pixel to the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+3)
	ld	de,(iy+6)
_ClipSetPixel_ASM:
	call	_PixelPtr_ASM \.r
	ret	c
color1 =$+1
	ld	(hl),0
	ret

;-------------------------------------------------------------------------------
_NoClipSetPixel_ASM:
; Sets the color pixel to the global color index
; Arguments:
;  bc : X Coord
;   e : Y Coord
; Returns:
;  None
	ld	hl,(currentDrawingBuffer)
	add	hl,bc
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
color5 =$+1
	ld	(hl),0
	ret

;-------------------------------------------------------------------------------
_ClipRectangle:
; Draws an unclipped rectangle with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Width
;  __frame_arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+9)
	ld	de,(iy+3)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(iy+12)
	ld	de,(iy+6)
	add	hl,de
	ld	(iy+12),hl
	call	_ClipRectangularRegion_ASM \.r
	ret	c
	ld	de,(iy+3)
	ld	hl,(iy+9)
	sbc	hl,de
	ret	z
	push	hl
	ld	de,(iy+6)
	ld	hl,(iy+12)
	or	a,a
	sbc	hl,de
	ld	a,l
	ld	hl,(iy+3)
	pop	bc
	ret	z
	jp	_NoClipRectangle_ASM \.r

;-------------------------------------------------------------------------------
_NoClipRectangle:
; Draws an unclipped rectangle with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Width
;  __frame_arg3 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)
	dec	bc
	inc.s	bc
	ld	a,b
	or	a,c
	ret	z
	ld	a,(iy+12)
	or	a,a
	ret	z
	ld	hl,(iy+3)
	ld	e,(iy+6)
_NoClipRectangle_ASM:
	ld	d,lcdWidth/2
	mlt	de
	add.s	hl,de
	add	hl,de
	ld	de,(currentDrawingBuffer)
	add	hl,de
	ex	de,hl
	ld	iy,0
	add	iy,de
NoClipRectangle_Loop:
	push	bc
	ld	hl,color1 \.r
	ldi
	jp	po,NoClipRectangle_Skip \.r
	scf
	sbc	hl,hl
	add	hl,de
	ldir
NoClipRectangle_Skip:
	ld	de,lcdWidth
	add	iy,de
	lea	de,iy
	pop	bc
	dec	a
	jr	nz,NoClipRectangle_Loop
	ret

;-------------------------------------------------------------------------------
_ClipRectangleOutline:
; Draws an clipped rectangle outline with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Width
;  __frame_arg3 : Height
; Returns:
;  None
	push	ix
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	push	bc
	push	de
	push	hl
	call	_ClipHorizLine \.r
	ld	hl,9
	add	hl,sp
	ld	sp,hl
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	_ClipVertLine \.r
	ld	hl,9
	add	hl,sp
	ld	sp,hl
	ld	hl,(ix+6)
	ld	de,(ix+9)
	ld	bc,(ix+12)
	add	hl,bc
	dec	hl
	ld	bc,(ix+15)
	push	bc
	push	de
	push	hl
	call	_ClipVertLine \.r
	ld	hl,9
	add	hl,sp
	ld	sp,hl
	ld	de,(ix+6)
	ld	hl,(ix+9)
	ld	bc,(ix+15)
	add	hl,bc
	dec	hl
	ld	bc,(ix+12)
	push	bc
	push	hl
	push	de
	call	_ClipHorizLine \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_NoClipRectangleOutline:
; Draws an unclipped rectangle outline with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Width
;  __frame_arg3 : Height
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
	call	_RectOutlineHoriz_ASM \.r
	pop	bc
	push	bc
	call	_RectOutlineVert_ASM \.r
	pop	bc
	pop	hl
	ld	e, c
	call	_NoClipVertLine_ASM \.r
	pop	bc
	inc	bc
	dec.s	bc
	jp	_MemSet_ASM \.r

;-------------------------------------------------------------------------------
_ClipHorizLine:
; Draws an clipped horizontal line with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(_ymin) \.r
	ld	hl,(iy+6)
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(_ymax) \.r
	ld	de,(iy+6)
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(iy+9)
	ld	de,(iy+3)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_xmin) \.r
	call	_Max_ASM \.r
	ld	(iy+3),hl
	ld	hl,(_xmax) \.r
	ld	de,(iy+9)
	call	_Min_ASM \.r
	ld	(iy+9),hl
	ld	de,(iy+3)
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(iy+9)
	or	a,a
	sbc	hl,de
	ld	b,h
	ld	c,l
	ld	e,(iy+6)
	ld	hl,(iy+3)
	jr	_RectOutlineHoriz_ASM

;-------------------------------------------------------------------------------
_NoClipHorizLine:
; Draws an unclipped horizontal line with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	de,(iy+3)
	ld	l,(iy+6)
	ld	bc,(iy+9)
	ex.s	de,hl
_RectOutlineHoriz_ASM:
	inc	bc
	dec.s	bc
_NoClipHorizLine_ASM:
	ld	a,b
	or	a,c
	ret	z
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	de,(currentDrawingBuffer)
	add	hl,de
color3 =$+1
	ld	a,0
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
_ClipVertLine:
; Draws an clipped horizontal line with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(_xmax) \.r
	ld	de,(iy+3)
	inc	de
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(iy+3)
	ld	de,(_xmin) \.r
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(iy+9)
	ld	de,(iy+6)
	add	hl,de
	ld	(iy+9),hl
	ld	hl,(_ymin) \.r
	call	_Max_ASM \.r
	ld	(iy+6),hl
	ld	hl,(_ymax) \.r
	ld	de,(iy+9)
	call	_Min_ASM \.r
	ld	(iy+9),hl
	ld	de,(iy+6)
	call	_SignedCompare_ASM \.r
	ret	c
	ld	hl,(iy+9)
	ld	de,(iy+6)
	or	a,a
	sbc	hl,de
	ld	b,l
	inc	b
	ld	hl,(iy+3)
	jr	_NoClipVertLine_ASM

;-------------------------------------------------------------------------------
_NoClipVertLine:
; Draws an unclipped vertical line with the global color index
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Length
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)		; x
	ld	e,(iy+6)		; y
	ld	b,(iy+9)		; length
_NoClipVertLine_ASM:
	dec	b
	ret	z
	ld	d,lcdWidth/2
	mlt	de
	add.s	hl,de
	add	hl,de
	ld	de,(currentDrawingBuffer)
	add	hl,de
_RectOutlineVert_ASM:
	ld	de,lcdWidth
color4 =$+1
_:	ld	(hl),0
	add	hl,de
	djnz	-_
	ret

;-------------------------------------------------------------------------------
_DrawBuffer:
; Forces drawing routines to operate on the offscreen buffer
; Arguments:
;  None
; Returns:
;  None
	ld	hl,(mpLcdBase)
	ld	de,vram
	or	a,a 
	sbc	hl,de
	jr	nz,++_
_:	ld	de,vram+lcdSize
_:	ld	(currentDrawingBuffer),de
	ret

;-------------------------------------------------------------------------------
_DrawScreen:
; Forces drawing routines to operate on the visible screen
; Arguments:
;  None
; Returns:
;  None
	ld	hl,(mpLcdBase)
	ld	de,vram
	or	a,a
	sbc	hl,de
	jr	z,-_
	jr	--_

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
_:	ld	(currentDrawingBuffer),de
	ld	(mpLcdBase),hl
	ld	hl,mpLcdIcr
	set	2,(hl)
	ld	l,mpLcdRis&$ff
_:	bit	2,(hl)
	jr	z,-_
	ret

;-------------------------------------------------------------------------------
_DrawState:
; Gets the current drawing state
; Arguments:
;  None
; Returns:
;  Returns 0 if drawing on the visible screen
	ld	hl,(currentDrawingBuffer)
	ld	de,(mpLcdBase)
	xor	a,a
	sbc	hl,de
	ret	z
	inc	a
	ret

;-------------------------------------------------------------------------------
_SetTransparentColor:
; Sets the transparency color for routines
; Arguments:
;  __frame_arg0 : Transparent color index
; Returns:
;  Previous transparent color index
	pop	hl
	pop	de
	push	de
	ld	a,(TransparentTextColor) \.r
	ld	d,a
	ld	a,e
	ld	(TransparentTextColor),a \.r
	ld	(NoClipSprTransColor),a \.r
	ld	(ClipSprTransColor),a \.r
	ld	(NoClipSprTransScaledTransColor),a \.r
	ld	a,d
	jp	(hl)

;-------------------------------------------------------------------------------
_ClipCircleOutline:
; Draws a clipped circle outline
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Radius
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,-9
	add	hl,sp
	ld	sp,hl
	ld	bc,0
	ld	(iy+-3),bc
	ld	bc,(iy+9)
	ld	(iy+-6),bc
	ld	hl,1
	or	a,a
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
	call	_ClipSetPixel_ASM \.r
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
	call	_ClipSetPixel_ASM \.r
	ld	bc,(iy+-6)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_ClipSetPixel_ASM \.r
	pop	de
	ld	bc,(iy+-3)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_ClipSetPixel_ASM \.r
	pop	bc
	pop	de
	call	_ClipSetPixel_ASM \.r
	pop	de
	ld	bc,(iy+-6)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	call	_ClipSetPixel_ASM \.r
	ld	bc,(iy+-3)
	ld	hl,(iy+6)
	or	a,a
	sbc	hl,bc
	ex	de,hl
	pop	bc
	push	de
	call	_ClipSetPixel_ASM \.r
	pop	de
	pop	bc
	call	_ClipSetPixel_ASM \.r
	ld	bc,(iy+-3)
	inc	bc
	ld	(iy+-3),bc
	ld	bc,(iy+-9)
	or	a,a
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
_ClipCircle:
; Draws an clipped circle
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Radius
; Returns:
;  None
	ld	hl,-9
	call	__frameset_ASM \.r
	ld	bc,0
	ld	(ix+-3),bc
	ld	bc,(ix+12)
	ld	(ix+-6),bc
	ld	hl,1
	or	a,a
	sbc	hl,bc
	ld	(ix+-9),hl
	jp	b_4 \.r
_ClipCircleSectors:
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
	call	_ClipHorizLine \.r
	ld	hl,9
	add	hl,sp
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
	call	_ClipHorizLine \.r
	ld	hl,9
	add	hl,sp
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
	call	_ClipHorizLine \.r
	ld	hl,9
	add	hl,sp
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
	call	_ClipHorizLine \.r
	ld	hl,9
	add	hl,sp
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
	jp	pe,_ClipCircleSectors \.r
	ld	sp,ix
	pop	ix
	ret
_:	jp	po,_ClipCircleSectors \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_NoClipCircle:
; Draws an unclipped circle
; Arguments:
;  __frame_arg0 : X Coord
;  __frame_arg1 : Y Coord
;  __frame_arg2 : Radius
; Returns:
;  None
	ld	hl,-9
	call	__frameset_ASM \.r
	ld	bc,0
	ld.s	(ix+7),bc
	ld.s	(ix+10),bc
	ld	(ix+-3),bc
	ld	bc,(ix+12)
	ld	(ix+-6),bc
	ld	hl,1
	or	a,a
	sbc	hl,bc
	ld	(ix+-9),hl
	jp	k_4 \.r
_NoClipCircleSectors:
	ld	hl,(ix+-3)
	add	hl,hl
	push	hl
	ld	hl,(ix+9)
	ld	bc,(ix+-6)
	add	hl,bc
	ld	e,l
	ld	hl,(ix+6)
	ld	bc,(ix+-3)
	or	a,a
	sbc	hl,bc
	pop	bc
	push	bc
	push	hl
	call	_NoClipHorizLine_ASM \.r
	ld	hl,(ix+-6)
	add	hl,hl
	push	hl
	ld	bc,(ix+-3)
	ld	hl,(ix+9)
	add	hl,bc
	ld	e,l
	ld	bc,(ix+-6)
	ld	hl,(ix+6)
	or	a,a
	sbc	hl,bc
	pop	bc
	push	bc
	push	hl
	call	_NoClipHorizLine_ASM \.r
	ld	bc,(ix+-3)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	ld	e,l
	pop	hl
	pop	bc
	call	_NoClipHorizLine_ASM \.r
	ld	bc,(ix+-6)
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,bc
	ld	e,l
	pop	hl
	pop	bc
	call	_NoClipHorizLine_ASM \.r
	ld	bc,(ix+-3)
	inc	bc
	ld	(ix+-3),bc
	ld	bc,(ix+-9)
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jp	m,k__2 \.r
	jp	pe,k_3 \.r
	jr	k__3
k__2:	jp	po,k_3 \.r
k__3:	ld	hl,(ix+-3)
	add	hl,hl
	inc	hl
	ld	bc,(ix+-9)
	add	hl,bc
	ld	(ix+-9),hl
	jr	k_4
k_3:	ld	bc,(ix+-6)
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
k_4:	ld	bc,(ix+-3)
	ld	hl,(ix+-6)
	or	a,a
	sbc	hl,bc
	jp	p,+_ \.r
	jp	pe,_NoClipCircleSectors \.r
	ld	sp,ix
	pop	ix
	ret
_:	jp	po,_NoClipCircleSectors \.r
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
_ClipLine:
; Draws an arbitrarily clipped line
; Arguments:
;  __frame_arg0: x0
;  __frame_arg0: y0
;  __frame_arg0: x1
;  __frame_arg0: y1
; Returns:
;  true if drawn, false if offscreen
	ld	iy,0
	add	iy,sp
	ld	hl,-10
	add	hl,sp
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
	call	_NoClipLine_ASM \.r
m_31:	ld	sp,iy
	ret

;-------------------------------------------------------------------------------
_NoClipLine:
; Draws an unclipped arbitrary line
; Arguments:
;  __frame_arg0 : X0 Coord (hl)
;  __frame_arg1 : Y0 Coord (b)
;  __frame_arg2 : X1 Coord (de)
;  __frame_arg3 : Y1 Coord (c)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	de,(iy+9)
	ex.s	de,hl
	ld	b,(iy+6)
	ld	c,(iy+12)
_NoClipLine_ASM:
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
	or	a,a
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
	ld	de,(currentDrawingBuffer)
	add	hl,de
color6 =$+1
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
	ld	de,(currentDrawingBuffer)
	add	hl,de
color7 =$+1
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
_ShiftWindowDown:
; Shifts whatever is in the clip window down by some pixels
; Arguments:
;  __frame_arg0 : Amount to shift by
; Returns:
;  None
	call	_DownRightShiftCalculate_ASM \.r
	ex	de,hl
	ld	hl,3
	add	hl,sp
	ld	l,(hl)
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de
	ex	de,hl
	jr	+_

;-------------------------------------------------------------------------------
_ShiftWindowRight:
; Shifts whatever is in the clip window right by some pixels
; Arguments:
;  __frame_arg0 : Amount to shift by
; Returns:
;  None
	call	_DownRightShiftCalculate_ASM \.r
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	pop	de
	sbc	hl,bc
	dec	hl
	dec	de
	inc	a
XDeltaDownRight_ASM =$+1
_:	ld	bc,0
	lddr
PosOffsetDownRight_ASM =$+1
	ld	bc,0
	sbc	hl,bc
	ex	de,hl
	or	a,a
	sbc	hl,bc
	ex	de,hl
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_ShiftWindowUp:
; Shifts whatever is in the clip window up by some pixels
; Arguments:
;  __frame_arg0 : Amount to shift by
; Returns:
;  None
	call	_UpLeftShiftCalculate_ASM \.r
	ex	de,hl
	ld	hl,3
	add	hl,sp
	ld	l,(hl)
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	add	hl,de
	jr	+_

;-------------------------------------------------------------------------------
_ShiftWindowLeft:
; Shifts whatever is in the clip window left by some pixels
; Arguments:
;  __frame_arg0 : Amount to shift by
; Returns:
;  None
	call	_UpLeftShiftCalculate_ASM \.r
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	pop	de
	add	hl,bc
	dec	hl
	dec	de
	inc	a
XDeltaUpLeft_ASM =$+1
_:	ld	bc,0
	ldir
PosOffsetUpLeft_ASM =$+1
	ld	bc,0
	add	hl,bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_ClipRegion:
; Arguments:
;  Pointer to struct
; Returns:
;  False if offscreen
	ld	hl,3
	add	hl,sp
	ld	iy,(hl)
	call	_ClipRectangularRegion_ASM
	sbc	a,a
	inc	a
	ret

;-------------------------------------------------------------------------------
_NoClipDrawScaledSprite:
; Draws a scaled sprite to the screen
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width -- 8bits
;  __frame_arg4 : Height -- 8bits
;  __frame_arg5 : Width Scale (integer)
;  __frame_arg6 : Height Scale (integer)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)
	ld	c,(iy+9)
	ex.s	de,hl
	ld	hl,(currentDrawingBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl
	ld	hl,lcdWidth
	ld	c,(iy+12)
	ld	b,(iy+18)
	ld	a,b
	ld	(NoClipSprScaledWidth),a \.r
	ld	a,c
	mlt	bc
	ld	(NoClipSprScaledCopyAmt),bc \.r
	or	a,a
	sbc	hl,bc
	ld	(NoClipSprScaledMoveAmt),hl \.r
	ld	(NoClipSprScaledLineNext),a \.r
	ld	a,(iy+21)
	ld	(NoClipSprHeightScale),a \.r
	ld	b,(iy+15)
	ld	hl,(iy+3)
_:	push	bc
NoClipSprScaledLineNext =$+1
	ld	c,0
	push	de
NoClipSprScaledWidth =$+1
_:	ld	b,0
	ld	a,(hl)
_:	ld	(de),a
	inc	de
	djnz	-_
	inc	hl
	dec	c
	jr	nz,--_
	ex	de,hl
NoClipSprScaledMoveAmt =$+1
	ld	bc,0
	add	hl,bc
	ex	de,hl
NoClipSprHeightScale =$+1
	ld	a,0
	push	hl
	pop	iy
	pop	hl
_:	dec	a
	jr	z,+_
	push	bc
NoClipSprScaledCopyAmt = $+1
	ld	bc,0
	ldir
	pop	bc
	ex	de,hl
	add	hl,bc
	ex	de,hl
	add	hl,bc
	jr	-_
_:	lea	hl,iy
	pop	bc
	djnz	-----_
	ret

;-------------------------------------------------------------------------------
_NoClipDrawScaledTransparentSprite:
; Draws a scaled sprite to the screen with transparency
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width -- 8bits
;  __frame_arg4 : Height -- 8bits
;  __frame_arg5 : Width Scale (integer)
;  __frame_arg6 : Height Scale (integer)
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)
	ld	c,(iy+9)
	ex.s	de,hl
	ld	hl,(currentDrawingBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl
	ld	hl,lcdWidth
	ld	c,(iy+12)
	ld	b,(iy+18)
	ld	a,b
	ld	(NoClipSprTransScaledWidth),a \.r
	ld	a,c
	mlt	bc
	or	a,a
	sbc	hl,bc
	ld	(NoClipSprTransScaledMoveAmt),hl \.r
	ld	(NoClipSprTransScaledLineNext),a \.r
	ld	b,(iy+15)
	ld	hl,(iy+3)
	ld	a,(iy+21)
	ld	(NoClipSprTransHeightScale),a \.r
_:	push	bc
NoClipSprTransHeightScale =$+1
	ld	a,0
_:	push	af
	push	hl
NoClipSprTransScaledLineNext =$+1
	ld	c,0
NoClipSprTransScaledWidth =$+1
_:	ld	b,0
	ld	a,(hl)
NoClipSprTransScaledTransColor =$+1
	cp	a,0
	jr	z,++++_	
_:	ld	(de),a
	inc	de
	djnz	-_
_:	inc	hl
	dec	c
	jr	nz,---_
	ex	de,hl
NoClipSprTransScaledMoveAmt =$+1
	ld	bc,0
	add	hl,bc
	ex	de,hl
	push	hl
	pop	iy
	pop	hl
	pop	af
	dec	a
	jr	z,+_
	jr	----_
_:	lea	hl,iy
	pop	bc
	djnz	------_
	ret
_:	inc	de
	djnz	-_
	jr	---_

;-------------------------------------------------------------------------------
_ClipDrawTransparentSprite:
; Draws a transparent sprite with clipping
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width -- 8bits
;  __frame_arg4 : Height -- 8bits
; Returns:
;  None
	call	_ClipDraw_ASM \.r
	ret	nc
	ld	(ClipSprTransNextAmt),a \.r
	xor	a,a
	or	a,(iy+15)
	ret	z
	ld	bc,0
	ld	hl,lcdWidth
	ld	a,(iy+12)
	ld	(ClipSprTransNextLine),a \.r
	ld	l,(iy+9)
	ld	h,lcdWidth/2
	mlt	hl
	ld	de,(iy+6)
	add	hl,hl
	add	hl,de
	ld	de,(currentDrawingBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+3)
	ld	a,(iy+15)
	pop	iy
	push	ix
	ld	ixh,a
ClipSprTransNextLine =$+1
_:	ld	b,0
	lea	de,iy
_:	ld	a,(hl)
ClipSprTransColor =$+1
	cp	a,0
	jr	z,+_
	ld	(de),a
_:	inc	de
	inc	hl
	djnz	--_
ClipSprTransNextAmt =$+1
	ld	c,0
	add	hl,bc
	ld	de,lcdWidth
	add	iy,de
	dec	ixh
	jr	nz,---_
	pop	ix
	ret

;-------------------------------------------------------------------------------
_ClipDrawSprite:
; Places an sprite on the screen as fast as possible with clipping
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width -- 8bits
;  __frame_arg4 : Height -- 8bits
; Returns:
;  None
	call	_ClipDraw_ASM \.r
	ret	nc
	ld	(ClipSprNextAmt),a \.r
	ld	a,(iy+12)
	ld	(ClipSprLineNext),a \.r
	ld	a,(iy+15)
	or	a,a
	ret	z
	ld	l,(iy+9)
	ld	h,lcdWidth/2
	mlt	hl
	ld	bc,(iy+6)
	add	hl,hl
	add	hl,bc
	ld	bc,(currentDrawingBuffer)
	add	hl,bc
	push	hl
	ld	hl,(iy+3)
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
_NoClipDrawSprite:
; Places an sprite on the screen as fast as possible
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width
;  __frame_arg4 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
_NoClipDrawSprite_ASM:
	ld	hl,(iy+6)
	ld	c,(iy+9)
	ex.s	de,hl
	ld	hl,(currentDrawingBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ld	b,0
	push	hl
	ld	a,(iy+12)
	ld	(NoClipSprLineNext),a \.r
	ld	a,(iy+15)
	ld	hl,(iy+3)
	pop	iy
NoClipSprLineNext =$+1
_:	ld	c,0
	lea	de,iy
	ldir
	ld	de,lcdWidth
	add	iy,de
	dec	a
	jr	nz,-_
	ret

;-------------------------------------------------------------------------------
_NoClipGetSprite:
; Grabs the data from the current draw buffer and stores it in another buffer
; Arguments:
;  __frame_arg0 : Pointer to storage buffer
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width
;  __frame_arg4 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)
	ld	c,(iy+9)
	ex.s	de,hl
	ld	hl,(currentDrawingBuffer)
	add	hl,de
	ld	b,lcdWidth/2
	mlt	bc
	add	hl,bc
	add	hl,bc
	ex	de,hl
	ld	hl,lcdWidth
	ld	bc,0
	ld	c,(iy+12)
	ld	a,c
	sbc	hl,bc
	ld	(NoClipSprGrabMoveAmt),hl \.r
	ld	(NoClipSprGrabNextLine),a \.r
	ld	a,(iy+15)
	ld	hl,(iy+3)
	ex	de,hl
NoClipSprGrabNextLine =$+1
_:	ld	bc,0
	ldir
NoClipSprGrabMoveAmt =$+1
	ld	bc,0
	add	hl,bc
	dec	a
	jr	nz,-_
	ld	hl,(iy+3)
	ret

;-------------------------------------------------------------------------------
_NoClipDrawTransparentSprite:
; Draws a transparent sprite to the current buffer
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width
;  __frame_arg4 : Height
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	bc,0
	ld	hl,lcdWidth
	ld	a,(iy+12)
	ld	(NoClipSprTransNextLine),a \.r
	ld	l,(iy+9)
	ld	h,lcdWidth/2
	mlt	hl
	ld	de,(iy+6)
	add	hl,hl
	add	hl,de
	ld	de,(currentDrawingBuffer)
	add	hl,de
	push	hl
	ld	hl,(iy+3)
	ld	a,(iy+15)
	pop	iy
	push	ix
	ld	ixh,a
NoClipSprTransNextLine =$+1
_:	ld	b,0
	lea	de,iy
_:	ld	a,(hl)
NoClipSprTransColor =$+1
	cp	a,0
	jr	z,+_
	ld	(de),a
_:	inc	de
	inc	hl
	djnz	--_
	ld	de,lcdWidth
	add	iy,de
	dec	ixh
	jr	nz,---_
	pop	ix
	ret

;-------------------------------------------------------------------------------
_ClipDraw_ASM:
; Clipping stuff
; Arguments:
;  __frame_arg0 : Pointer to sprite
;  __frame_arg1 : X Coord
;  __frame_arg2 : Y Coord
;  __frame_arg3 : Width -- 8bits
;  __frame_arg4 : Height -- 8bits
; Returns:
;  How much to add to the sprite per iteration, NC if offscreen
	ld	iy,3
	add	iy,sp
	ld	a,(iy+12)
	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	(iy+12),hl
	ld	l,(iy+15)
	ld	(iy+15),hl
	ld	(tmpSpriteWidth_ASM),a \.r
	ld	de,(iy+9)
	ld	hl,(_ymin) \.r
	sbc	hl,de
	jp	m,NoTopClipNeeded_ASM \.r
	jr	z,NoTopClipNeeded_ASM
	ld	a,l
	ld	hl,(iy+15)
	or	a,a
	add	hl,de
	bit	7,h
	ret	nz
	ld	(iy+15),hl
	ld	l,a
	ld	h,(iy+12)
	mlt	hl
	ld	de,(iy+3)
	add	hl,de
	ld	(iy+3),hl
	ld	de,(_ymin) \.r
	ld	(iy+9),de
NoTopClipNeeded_ASM:
	ex	de,hl
	ld	de,(_ymax) \.r
	call	_SignedCompare_ASM \.r
	ret	nc
	ld	de,(iy+9)
	ld	hl,(iy+15)
	add	hl,de
	ld	de,(_ymax) \.r
	call	_SignedCompare_ASM \.r
	jr	c,NoBottomClipNeeded_ASM
	ex	de,hl
	ld	de,(iy+9)
	or	a,a
	sbc	hl,de
	ld	(iy+15),hl
NoBottomClipNeeded_ASM:
	ld	hl,(iy+6)
	ld	de,(_xmin) \.r
	call	_SignedCompare_ASM \.r
	ld	hl,(iy+6)
	jr	nc,NoLeftClip_ASM
	ld	de,(iy+12)
	add	hl,de
	ld	de,(_xmin) \.r
	ex	de,hl
	call	_SignedCompare_ASM \.r
	ret	nc
	ld	de,(iy+6)
	ld	hl,(iy+3)
	or	a,a
	sbc	hl,de
	ld	(iy+3),hl
	ld	hl,(iy+12)
	add	hl,de
	ld	(iy+12),hl
	ld	hl,(_xmin) \.r
	ld	(iy+6),hl
NoLeftClip_ASM:
	ld	de,(_xmax) \.r
	call	_SignedCompare_ASM \.r
	ret	nc
	ld	hl,(iy+6)
	ld	de,(iy+12)
	add	hl,de
	ld	de,(_xmax) \.r
	ex	de,hl
	call	_SignedCompare_ASM \.r
	jr	nc,NoRightClip_ASM
	ld	hl,(_xmax) \.r
	ld	de,(iy+6)
	or	a,a
	sbc	hl,de
	ld	(iy+12),hl
NoRightClip_ASM:
tmpSpriteWidth_ASM =$+1
	ld	a,0
	sub	a,(iy+12)
	scf
	ret

;-------------------------------------------------------------------------------
_NoClipDrawFGTilemap:
; Tilemapping subsection
	ld	hl,_NoClipDrawTransparentSprite \.r
	jr	+_
;-------------------------------------------------------------------------------
_NoClipDrawBGTilemap:
; Tilemapping subsection
	ld	hl,_NoClipDrawSprite \.r
	jr	+_
;-------------------------------------------------------------------------------
_ClipDrawFGTilemap:
; Tilemapping subsection
	ld	hl,_ClipDrawTransparentSprite \.r
	jr	+_
;-------------------------------------------------------------------------------
_ClipDrawBGTilemap:
; Draws a tilemap given a tile map structure and some offsets
; Arguments:
;  __frame_arg0 : Tilemap Struct
;  __frame_arg1 : X Pixel Offset (Unsigned)
;  __frame_arg2 : Y Pixel Offset (Unsigned)
; Returns:
;  None
; C Function:
;  void DrawBGTilemap(gc_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset) {
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
;              gc_Sprite(tilemap->tiles[tilemap->map[x+y_next]], x_draw, y_draw, tilemap->tile_width, tilemap->tile_height);
;              x_draw += tilemap->tile_width;
;              x++;
;          }
;          y_draw += tilemap->tile_height;
;          y++;
;      }
;  }
;
	ld	hl,_ClipDrawSprite \.r
_:	ld	(_DrawTile_SMC),hl \.r
	push	ix
	ld	hl,-12
	ld	ix,0
	add	ix,sp
	add	hl,sp
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
	ld	(_X_Res_ASM),a \.r
	ld	hl,(iy+15)
	sbc	hl,bc
	ld	(_X_Draw_ASM),hl \.r ; x_draw = tilemap->x_loc-x_offset;
	
	or	a,a
	sbc	hl,hl
	ld	l,(iy+14)
	ld	bc,(ix+12)
	sbc	hl,bc
	ld	(ix+-12),hl
	ld	(ix+-3),0
	jp	_Y_Loop_ASM \.r

_X_Res_ASM =$+3
n_8:	ld	(ix+-1),0
	ld	(ix+-2),0
_X_Draw_ASM =$+1
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
	ld	b,0
	ld	c,(iy+6)
	push	bc
	ld	c,(iy+7)
	push	bc
	ld	bc,(ix+-12)
	push	bc
	ld	bc,(ix+-7)
	push	bc
	ld	bc,(hl)
	push	bc
_DrawTile_SMC =$+1
	call	0
	ld	hl,15
	add	hl,sp
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
;  __frame_arg0 : Tilemap Struct
;  __frame_arg1 : X Pixel Offset (Unsigned)
;  __frame_arg2 : Y Pixel Offset (Unsigned)
;  __frame_arg3 : New Tile Index
; Returns:
;  A pointer to an indexed tile in the tilemap (so it can be looked at or changed)
; C Function:
;  uint8_t *gc_TilePtr(gc_tilemap_t *tilemap, unsigned x_offset, unsigned y_offset, uint8_t tile) {
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
;  __frame_arg0 : Tilemap Struct
;  __frame_arg1 : X Map Offset (uint8_t)
;  __frame_arg2 : Y Map Offset (uint8_t)
; Returns:
;  A pointer to the indexed tile in the tilemap (so it can be looked at or changed)
	push	ix
	ld	ix,0
	add	ix,sp
	ld	iy,(ix+6)
	ld	h,(ix+12)
	ld	l,(iy+9)
	mlt	hl
	ex	de,hl
	or	a,a
	sbc	hl,hl
	ld	l,(ix+9)
	ld	bc,(iy+0)
	add	hl,de
	add	hl,bc
	pop	ix
	ret

;-------------------------------------------------------------------------------
_TextX:
; Gets the X position of the text cursor
; Arguments:
;  None
; Returns:
;  X Text cursor posistion
	ld	hl,(TextXPos_ASM) \.r
	ret

;-------------------------------------------------------------------------------
_TextY:
; Gets the Y position of the text cursor
; Arguments:
;  None
; Returns:
;  Y Text cursor posistion
	ld	a,(TextYPos_ASM) \.r
	ret

;-------------------------------------------------------------------------------
_SetTextColor:
; Sets the transparency text color for text routines
; Arguments:
;  __frame_arg0 : High 8 bits is background, Low 8 bits is foreground
;  These refer to color palette indexes
; Returns:
;  Previous text color palette indexes
	pop	hl
	pop	de
	push	de
	push	hl
	ld	hl,(TextColor_ASM) \.r
	ld	(TextColor_ASM),de \.r
	ret

;-------------------------------------------------------------------------------
_SetTextXY:
; Sets the transparency text color for text routines
; Arguments:
;  __frame_arg0 : Text X Pos
;  __frame_arg1 : Text Y Pos
; Returns:
;  None
	ld	hl,3
	add	hl,sp
	ld	de,TextXPos_ASM \.r
	ldi
	ldi
	inc	hl
	ld	a,(hl)
	ld	(TextYPos_ASM),a \.r
	ret

;-------------------------------------------------------------------------------
_PrintStringXY:
; Places a string at the given coordinates
; Arguments:
;  __frame_arg0 : Pointer to string
;  __frame_arg1 : Text X Pos
;  __frame_arg2 : Text Y Pos
; Returns:
;  None
	ld	hl,9
	add	hl,sp
	ld	a,(hl)
	ld	(TextYPos_ASM),a \.r
	dec	hl
	dec	hl
	ld	de,TextXPos_ASM+1 \.r
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
;  __frame_arg0 : Pointer to string
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
_PrintChar:
; Places a character at the current cursor position
; Arguments:
;  __frame_arg0 : Character to draw
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	a,(iy+3)
_PrintChar_ASM:
	push hl
TextXPos_ASM = $+1
	ld	bc,0
	push	af
	ld	e,a
	ld	a,(MonoFlag_ASM) \.r
	or	a,a
	jr	nz,+_
	sbc	hl,hl
	ld	l,e
	ld	de,(CharSpacing_ASM) \.r
	add	hl,de
	ld	a,(hl)
	inc	a
_:	push	bc
	ld	(CharWidthChange_ASM),a \.r
	sbc	hl,hl
	ld	l,a
	neg
	ld	(CharWidthDelta_ASM),a \.r
	add	hl,bc
	ld	(TextXPos_ASM),hl \.r
CharWidthDelta_ASM =$+1
	ld	de,-1
	ld	hl,lcdWidth
	add	hl,de
	ld	(CharLineDelta_ASM),hl \.r
TextYPos_ASM = $+1
	ld	l,0
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	ld	de,(currentDrawingBuffer)
	add	hl,de
	pop	de
	add	hl,de
	pop	af
	ex	de,hl
	or	a,a
	sbc	hl,hl
	ld	l,a
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(TextData_ASM) \.r
	add	hl,bc
	ld	b,8
iloop:	push	bc
	ld	c,(hl)
CharWidthChange_ASM =$+1
	ld	b,0
	ex	de,hl
	push	de
TextColor_ASM =$+1
	ld	de,$FF00
cloop:	ld	a,d
	rlc	c
	jr	nc,+_
	ld	a,e
TransparentTextColor =$+1
_:	cp	a,$FF
	jr	nz,+_
	ld	a,(hl)
_:	ld	(hl),a
	inc	hl
	djnz	cloop
CharLineDelta_ASM =$+1
	ld	bc,0
	add	hl,bc
	pop	de
	ex	de,hl
	inc	hl
	pop	bc
	djnz	iloop
	pop	hl
	ret

;-------------------------------------------------------------------------------
_PrintUnsignedInt:
; Places an unsigned int at the current cursor position
; Arguments:
;  __frame_arg0 : Number to print
;  __frame_arg1 : Number of characters to print
; Returns:
;  None
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	c,(iy+6)
_PrintUnsignedInt_ASM:
	ld	a,8
	sub	a,c
	ret	c
	ld	c,a
	ld	b,8
	mlt	bc
	ld	a,c
	ld	(offset0),a \.r
offset0 =$+1
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
;  __frame_arg0 : Number to print
;  __frame_arg1 : Number of characters to print
; Returns:
;  None
	ld	iy,0
	ld	bc,0
	add	iy,sp
	ld	c,(iy+6)
	ld	hl,(iy+3)
	bit	7,(iy+5)
	jr	z,+_
	push	bc
	push	hl
	pop	bc
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	ld	a,'-'
	call	_PrintChar_ASM \.r
	pop	bc
_:	jp	_PrintUnsignedInt_ASM \.r

;-------------------------------------------------------------------------------
_StringWidthC:
; Gets the width of a string
; Arguments:
;  __frame_arg0 : Pointer to string
; Returns:
;  Width of string in pixels
	pop	de
	pop	hl
	push	hl
	push	de
	ld	bc,0
_:	ld	a,(hl)
	or	a,a
	jr	z,+_
	push	hl
	call	_CharWidth_ASM \.r
	pop	hl
	inc	hl
	ld	a,(hl)
	or	a,a
	jr	z,+_
	inc	bc
	jr	-_
_:	push	bc
	pop	hl
	ret

;-------------------------------------------------------------------------------	
_CharWidth:
; Gets the width of a character
; Arguments:
;  __frame_arg0 : Character
; Returns:
;  Width of character in pixels
	pop	de
	pop	hl
	push	hl
	push	de
	ld	bc,0
	ld	a,l
_CharWidth_ASM:
	ld	l,a
	ld	a,(MonoFlag_ASM) \.r
	or	a,a
	jr	nz,+_
	ld	a,l
	or	a,a
	sbc	hl,hl
	ld	l,a
	ld	de,(CharSpacing_ASM) \.r
	add	hl,de
	ld	a,(hl)
	or	a,a
	sbc	hl,hl
	ld	l,a
	add	hl,bc
	push	hl
	pop	bc
	ret
_:	or	a,a
	sbc	hl,hl
	ld	l,a
	add	hl,bc
	ret

;-------------------------------------------------------------------------------
_SetCustomFontData:
; Sets the font to be custom
; Arguments:
;  __frame_arg0 : Pointer to font data
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
;  __frame_arg0 : Pointer to font spacing
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
_SetFontMonospace:
; Sets the font to be monospace
; Arguments:
;  __frame_arg0 : Monospace spacing amount
; Returns:
;  None
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,e
	ld	(MonoFlag_ASM),a \.r
	ret

;-------------------------------------------------------------------------------
_LZDecompress:
; Decompresses in lz77 format the input data into the output buffer
; Arguments:
;  __frame_arg0 : Pointer to Input Buffer
;  __frame_arg1 : Pointer to Output Buffer
;  __frame_arg2 : Pointer to Input Buffer Size
; Returns:
;  None
	ld	hl,-20
	call	__frameset_ASM \.r
	ld	bc,1
	ld	hl,(ix+12)
	or	a,a
	sbc	hl,bc
	jp	c,l_19 \.r
	ld	hl,(ix+6)
	ld	a,(hl)
	ld	(ix+-7),a
	ld	(ix+-3),bc
	ld	bc,0
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
; Inner library routines
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_LZ_ReadVarSize_ASM:
; LZ Compression Subroutine
	ld	hl,-12
	call	__frameset_ASM \.r
	ld	bc,0
	ld	(ix+-3),bc
	ld	(ix+-6),bc
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
	res	7,a
	or	a,a
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
	or	a,a
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
	ld	hl,(currentDrawingBuffer)
	add	hl,bc
	ld	d,lcdWidth/2
	mlt	de
	add	hl,de
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_UpLeftShiftCalculate_ASM:
; Calculates the position to shift the window for up/left
; Inputs:
;  None
; Outputs:
;  HL->Place to draw
	ld	hl,(_xmax) \.r
	ld	de,(_xmin) \.r
	push	de
	or	a,a
	sbc	hl,de
	ld	(XDeltaUpLeft_ASM),hl \.r
	ex	de,hl
	ld	hl,lcdWidth
	or	a,a
	sbc	hl,de
	ld	(PosOffsetUpLeft_ASM),hl \.r
	ld	a,(_ymin) \.r
	ld	c,a
	ld	a,(_ymax) \.r
	ld	l,c
_:	sub	a,c
	ld	h,lcdWidth/2
	mlt	hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	de,vram
	add	hl,de
	ret

;-------------------------------------------------------------------------------
_DownRightShiftCalculate_ASM:
; Calculates the position to shift the window for dowm/right
; Inputs:
;  None
; Outputs:
;  HL->Place to draw
	ld	hl,(_xmax) \.r
	ld	de,(_xmin) \.r
	push	hl
	or	a,a
	sbc	hl,de
	ld	(XDeltaDownRight_ASM),hl \.r
	ex	de,hl
	ld	hl,lcdWidth
	or	a,a
	sbc	hl,de
	ld	(PosOffsetDownRight_ASM),hl \.r
	ld	a,(_ymin) \.r
	ld	c,a
	ld	a,(_ymax) \.r
	ld	l,a
	jr	-_

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
; Calculates the new coordinates given the clip window and inputs
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
; Sets the clipping window to the entire screen
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
_:
	or	a,a
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
	push	bc
	push	hl
	ex	de,hl
	ld	hl,2
	add	hl,sp
	ld	b,(hl)
	mlt	bc
	inc	hl
	inc	hl
	inc	hl
	ld	a,d
	ld	d,(hl)
	mlt	de
	dec	hl
	ld	l,(hl)
	ld	h,a
	mlt	hl
	ld	a,l
	add	a,e
	add	a,c
	pop	de
	pop	bc
	push	bc
	or	a,a
	sbc	hl,hl
	add.s	hl,de
	ex	de,hl
	ld	h,b
	mlt	hl
	ld	b,d
	mlt	bc
	add	hl,bc
	add	a,h
	ld	h,a
	pop	bc
	ld	d,c
	mlt	de
	push	hl
	dec	sp
	pop	hl
	inc	sp
	ld	l,0
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
	jp	po,m__1 \.r
	ccf
m__1:	rla
	ld	hl,(_xmax) \.r
	sbc	hl,bc
	add	hl,hl
	jp	po,m__2 \.r
	ccf
m__2:	rla
	ld	hl,(_ymin) \.r
	scf
	sbc	hl,de
	add	hl,hl
	jp	pe,m__3 \.r
	ccf
m__3:	rla
	ld	hl,(_ymax) \.r
	sbc	hl,de
	add	hl,hl
	rla
	ret	po
	xor	1
	ret

;-------------------------------------------------------------------------------
__frameset_ASM:
; Inits the stack frame using ix
; Arguments:
;  HL : Negative, amount of stack space to allocate
; Returns:
;  None
	ex	(sp),ix
	lea	de,ix
	ld	ix,0
	add	ix,sp
	add	hl,sp
	ld	sp,hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------------------------
MonoFlag_ASM:
	.db 0
CharSpacing_ASM:
	.dl DefaultCharSpacing_ASM \.r
TextData_ASM:
	.dl DefaultTextData_ASM \.r
	
DefaultCharSpacing_ASM:
	;   0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	.db 7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7
	.db 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
	.db 2,3,5,7,7,7,7,4,4,4,7,6,3,6,2,7
	.db 7,6,7,7,7,7,7,7,7,7,2,3,5,6,5,6
	.db 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
	.db 7,7,7,7,7,7,7,7,7,7,7,4,7,4,7,7
	.db 3,7,7,7,7,7,7,7,7,4,7,7,4,7,7,7
	.db 7,7,7,7,6,7,7,7,7,7,7,6,2,6,7,7
	.db 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
	.db 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
 
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

 .endLibrary
