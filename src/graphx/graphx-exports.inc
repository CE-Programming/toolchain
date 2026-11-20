.equ GRAPHX_VERSION, 14

; Export order defines the LibLoad ABI. Append new entries at the end.
.macro graphx_exports emit

; v1 functions
	\emit gfx_Begin
	\emit gfx_End
	\emit gfx_SetColor
	\emit gfx_SetDefaultPalette
	\emit gfx_SetPalette
	\emit gfx_FillScreen
	\emit gfx_SetPixel
	\emit gfx_GetPixel
	\emit gfx_GetDraw
	\emit gfx_SetDraw
	\emit gfx_SwapDraw
	\emit gfx_Blit
	\emit gfx_BlitLines
	\emit gfx_BlitRectangle
	\emit gfx_PrintChar
	\emit gfx_PrintInt
	\emit gfx_PrintUInt
	\emit gfx_PrintString
	\emit gfx_PrintStringXY
	\emit gfx_SetTextXY
	\emit gfx_SetTextBGColor
	\emit gfx_SetTextFGColor
	\emit gfx_SetTextTransparentColor
	\emit gfx_SetFontData
	\emit gfx_SetFontSpacing
	\emit gfx_SetMonospaceFont
	\emit gfx_GetStringWidth
	\emit gfx_GetCharWidth
	\emit gfx_GetTextX
	\emit gfx_GetTextY
	\emit gfx_Line
	\emit gfx_HorizLine
	\emit gfx_VertLine
	\emit gfx_Circle
	\emit gfx_FillCircle
	\emit gfx_Rectangle
	\emit gfx_FillRectangle
	\emit gfx_Line_NoClip
	\emit gfx_HorizLine_NoClip
	\emit gfx_VertLine_NoClip
	\emit gfx_FillCircle_NoClip
	\emit gfx_Rectangle_NoClip
	\emit gfx_FillRectangle_NoClip
	\emit gfx_SetClipRegion
	\emit gfx_GetClipRegion
	\emit gfx_ShiftDown
	\emit gfx_ShiftUp
	\emit gfx_ShiftLeft
	\emit gfx_ShiftRight
	\emit gfx_Tilemap
	\emit gfx_Tilemap_NoClip
	\emit gfx_TransparentTilemap
	\emit gfx_TransparentTilemap_NoClip
	\emit gfx_TilePtr
	\emit gfx_TilePtrMapped
	\emit gfx_Reserved
	\emit gfx_AllocSprite
	\emit gfx_Sprite
	\emit gfx_TransparentSprite
	\emit gfx_Sprite_NoClip
	\emit gfx_TransparentSprite_NoClip
	\emit gfx_GetSprite
	\emit gfx_ScaledSprite_NoClip
	\emit gfx_ScaledTransparentSprite_NoClip
	\emit gfx_FlipSpriteY
	\emit gfx_FlipSpriteX
	\emit gfx_RotateSpriteC
	\emit gfx_RotateSpriteCC
	\emit gfx_RotateSpriteHalf
	\emit gfx_Polygon
	\emit gfx_Polygon_NoClip
	\emit gfx_FillTriangle
	\emit gfx_FillTriangle_NoClip

; v2 functions
	\emit gfx_Deprecated
	\emit gfx_SetTextScale

; v3 functions
	\emit gfx_SetTransparentColor
	\emit gfx_ZeroScreen
	\emit gfx_SetTextConfig
	\emit gfx_GetSpriteChar

; v4 functions
	\emit gfx_Lighten
	\emit gfx_Darken

; v5 functions
	\emit gfx_SetFontHeight
	\emit gfx_ScaleSprite
	\emit gfx_FloodFill

; v6 functions
	\emit gfx_RLETSprite
	\emit gfx_RLETSprite_NoClip
	\emit gfx_ConvertFromRLETSprite
	\emit gfx_ConvertToRLETSprite
	\emit gfx_ConvertToNewRLETSprite

; v7 functions
	\emit gfx_RotateScaleSprite
	\emit gfx_RotatedScaledTransparentSprite_NoClip
	\emit gfx_RotatedScaledSprite_NoClip

; v8 functions
	\emit gfx_SetCharData

; v9 functions
	\emit gfx_Wait

; v10 functions

; v11 functions
	\emit gfx_CopyRectangle

; v12 functions
	\emit gfx_Ellipse
	\emit gfx_Ellipse_NoClip
	\emit gfx_FillEllipse
	\emit gfx_FillEllipse_NoClip

; v13 functions
	\emit gfx_RotatedScaledTransparentSprite
	\emit gfx_RotatedScaledSprite
.endm
