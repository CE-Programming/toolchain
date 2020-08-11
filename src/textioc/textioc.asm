;-------------------------------------------------------------
; Includes
;-------------------------------------------------------------
	include '../include/library.inc'
	include '../include/include_library.inc'

;-------------------------------------------------------------
	library 'TEXTIOC',2
;-------------------------------------------------------------

;-------------------------------------------------------------
; Dependencies
;-------------------------------------------------------------
	include_library '../graphx/graphx.asm'

;-------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------
	export textio_AllocIDS
	export textio_FreeIDS
	export textio_GetDataBufferSize
	export textio_GetDataBufferPtr
	export textio_GetCurrCharPtr
	export textio_GetIDSX
	export textio_GetIDSY
	export textio_SetCursorColor
	export textio_GetCursorColor
	export textio_GetCursorBGColor
	export textio_SetCursorBlinkRate
	export textio_GetCurrCursorX
	export textio_SetCursorDimensions
	export textio_GetCursorWidth
	export textio_GetCursorHeight
	export textio_SetIDSTimer
	export textio_GetIDSTimer
	export textio_SetPrgmNameFlag
	export textio_LockIDS
	export textio_GetIDSLock
	export textio_GetBufferFullFlag
	export textio_ClearDataBuffer
	export textio_AllocKeymap
	export textio_FreeKeymap
	export textio_SetKeymaps
	export textio_GetNumKeymaps
	export textio_SetCurrKeymapNum
	export textio_GetCurrKeymapNum
	export textio_GetCurrKeymapPtr
	export textio_GetCurrKeymapIndicator
	export textio_GetUppercaseLettersKeymap
	export textio_GetLowercaseLettersKeymap
	export textio_GetPrgmNameLettersKeymap
	export textio_GetNumericalKeymap
	export textio_SetClearKey
	export textio_SetBackspaceKey
	export textio_SetCursorLeftKey
	export textio_SetCursorRightKey
	export textio_TimedInput
	export textio_Input

	export textio_SetThetaCodepoint
	export textio_GetThetaCodepoint
	export textio_ConvertProgramAppvarName_TIOS
	export textio_ConvertProgramAppvarName_TextIOC

	export textio_SetPrintFormat
	export textio_GetPrintFormat
	export textio_SetTabSize
	export textio_GetTabSize
	export textio_PrintTab
	export textio_PrintChar
	export textio_GetCharWidth
	export textio_GetLineWidth
	export textio_PrintText
	export textio_GetLinePtr

;-------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------
	export textio_SetLibraryRoutines
	export textio_GetStringWidthL
	export textio_SetCursorY
	export textio_GetCursorY
	export textio_SetDrawThetaCharFunction

	export textio_SetTextWindow
	export textio_GetTextWindowX
	export textio_GetTextWindowY
	export textio_GetTextWindowWidth
	export textio_GetTextWindowHeight
	export textio_SetNewlineCode
	export textio_GetNewlineCode

	export textio_SetLineSpacing
	export textio_GetLineSpacingAbove
	export textio_GetLineSpacingBelow
	export textio_SetFontHeight

;-------------------------------------------------------------
; Global defines
;-------------------------------------------------------------
	arg0	:= 3
	arg1	:= 6
	arg2	:= 9
	arg3	:= 12
	arg4	:= 15

	; These offsets are used for util.GetIDSDataPtr
	curr_char_ptr_offset		:= 0
	xPos_offset			:= 3
	yPos_offset			:= 6
	first_visible_char_ptr_offset	:= 7
	visible_buffer_width_offset	:= 10
	cursor_color_offset		:= 13
	cursor_y_offset			:= 14
	cursor_width_offset		:= 15
	cursor_height_offset		:= 16
	timer_offset			:= 17
	ids_attr_offset			:= 20
	num_keymaps_offset		:= 21
	curr_keymap_num_offset		:= 22
	first_keymap_offset		:= 23

	ids_data_size	:= $1b		; (27 bytes)
	keymap_size	:= $39		; (57 bytes)

	null	:= $00
	tab	:= $09
	space	:= $20
	bPrintLeftMarginFlush	:= 1
	bPrintCentered		:= 2
	bPrintRightMarginFlush	:= 3



macro mOpenDebugger
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),2
	pop	hl
end macro


;=============================================================;
;                                                             ;
;                Library Setup Functions                      ;
;                                                             ;
;=============================================================;


textio_SetLibraryRoutines:
; Arguments:
;   arg0 = pointer to structure
; Returns:
;   None
; Destroys:
;   HL and IY

	ld	hl,arg0
	add	hl,sp
	ld	iy,(hl)
	ld	a,(iy)
	ld	(_LibraryVersion),a
	ld	hl,(iy + 1)
	ld	(_SetTextPosition),hl
	ld	hl,(iy + 4)
	ld	(_GetTextX),hl
	ld	hl,(iy + 7)
	ld	(_GetTextY),hl
	ld	hl,(iy + 10)
	ld	(_DrawChar),hl
	ld	hl,(iy + 13)
	ld	(_GetCharWidth),hl
; If a third version is released that uses more external functions,
; use the following to supply only those functions that the library
; version requires.
;	ld	a,2
;	cp	a,(_LibraryVersion)
;	ret	z
	ret


;=============================================================;
;                                                             ;
;                  Text Input Functions                       ;
;                                                             ;
;=============================================================;


textio_AllocIDS:
; Arguments:
;   arg0 = size of data buffer
;   arg1 = xPos
;   arg2 = yPos
;   arg3 = visible_buffer_width
;   arg4 = number of keymaps
;   arg5 = pointer to malloc routine
; Returns:
;   Pointer to IDS; NULL if failure
; Destroys:
;   All registers and IY

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)				; HL = data buffer size
	push	hl

	ld	hl,arg4 + 3			; Plus 3 for stack local
	add	hl,sp
	ld	hl,(hl)				; L = number of keymaps
	ld	h,3
	mlt	hl				; HL = amount of bytes to allocate for keymap pointers
	push	hl
	pop	bc				; BC = amount of bytes to allocate
	pop	hl				; HL = data buffer size
	add	hl,bc
	ld	bc,ids_data_size		; Add more bytes for other IDS data
	add	hl,bc				; HL = total size of IDS

	push	hl				; Put HL on the stack for malloc routine
	ld	bc,21				; 5 arguments + 1 return vector + 1 local = (7 * 3) = 21 bytes
	push	bc
	pop	hl
	add	hl,sp
	ld	hl,(hl)				; HL -> malloc routine
	call	util.CallHL			; Call malloc routine
	pop	bc				; BC = size of IDS
	add	hl,bc				; This should never carry
	sbc	hl,bc
	ret	z				; Return if malloc routine error (HL == 0)

	push	hl				; Save IDS pointer to stack
	call	util.SetMemNull			; Initialize the IDS memory to NULL

	ld	bc,6				; Remember there is one local on the stack
	push	bc
	pop	hl
	add	hl,sp
	ld	bc,(hl)				; BC = size of data buffer
	pop	hl				; HL -> IDS
	push	hl

	ld	(hl),bc
	inc	bc				; Add one to BC for null-terminating character
	inc	hl
	inc	hl
	inc	hl
	push	hl				; HL -> data buffer's start
	add	hl,bc				; HL -> (IDS + 4 + size of data buffer)
						; HL now points to where the curr_char_ptr should go
	pop	bc				; BC -> data buffer's start
	ld	(hl),bc				; Set the curr_char_ptr to the data buffer's start
	push	hl				; Save HL

	ld	bc,12				; We have two locals on the stack now
	push	bc
	pop	hl
	add	hl,sp
	ld	bc,(hl)				; BC = xPos
	pop	hl				; HL -> curr_char_ptr
	inc	hl
	inc	hl
	inc	hl				; Now HL points to where the IDS xPos should go
	ld	(hl),bc
	push	hl				; Save HL

	ld	bc,15				; We still have two stack locals
	push	bc
	pop	hl
	add	hl,sp
	ld	bc,(hl)				; BC = yPos
	pop	hl				; HL -> IDS xPos slot
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),bc

	ex	de,hl				; DE -> yPos slot
	pop	hl				; HL -> IDS (see current line # - 43)
	push	hl
	inc	hl
	inc	hl
	inc	hl
	ex	de,hl				; HL -> yPos slot | DE -> data buffer start
	inc	hl				; HL -> visible_buffer_ptr slot
	ld	(hl),de				; Initialize the visible_buffer_ptr to the data buffer's start
	push	hl

	ld	bc,18
	push	bc
	pop	hl
	add	hl,sp
	ld	bc,(hl)				; BC = visible_buffer_width
	pop	hl				; HL -> visible_buffer_ptr slot
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),bc

	pop	hl				; HL -> IDS
	ret


;-------------------------------------------------------------
textio_FreeIDS:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = pointer to free_routine
; Returns:
;   None
; Destroys:
;   DE and HL

	ld	hl,arg0
	add	hl,sp
	ld	de,(hl)				; DE -> IDS
	push	de
	inc	hl
	inc	hl
	inc	hl
	ld	hl, (hl)			; HL -> free_routine
	call	util.CallHL			; Call free_routine
	pop	de
	ret


;-------------------------------------------------------------
textio_GetDataBufferSize:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = size of specified IDS's data buffer
; Destroys:
;   BC

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)				; HL -> IDS
assert $= util.GetDataBufferSize


;-------------------------------------------------------------
util.GetDataBufferSize:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL -> data buffer size
; Destroys:
;   None

	ld	hl,(hl)				; HL = data buffer size
	ret


;-------------------------------------------------------------
textio_GetDataBufferPtr:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = pointer to the specified IDS's data buffer
; Destroys:
;   BC

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)				; HL -> IDS
assert $= util.GetDataBufferPtr


;-------------------------------------------------------------
util.GetDataBufferPtr:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL -> data buffer pointer
; Destroys:
;   None

	inc	hl
	inc	hl
	inc	hl				; HL -> data buffer pointer
	ret


;-------------------------------------------------------------
util.GetIDSDataPtr:
; This function only gets data stored after the data buffer in
; memory.
; Arguments:
;   HL = IDS pointer
;   BC = desired data offset
; Returns:
;   HL = pointer to desired data
;   DE = pointer to IDS
;   BC = intact
; Destroys:
;   None

	push	bc				; Save BC to stack
	push	hl
	call	textio_GetDataBufferSize
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	inc	hl				; HL -> curr_char_ptr
	pop	bc
	add	hl,bc
	ret


;-------------------------------------------------------------
textio_GetCurrCharPtr:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   Pointer to current char
; Destroys:
;   BC

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetCurrCharPtr


;-------------------------------------------------------------
util.GetCurrCharPtr:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL -> curr_char_ptr
; Destroys:
;   BC and DE

	ld	bc,curr_char_ptr_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)				; HL = curr_char_ptr
	ret


;-------------------------------------------------------------
util.SetCurrCharPtr:
; Arguments:
;   HL = IDS pointer
;   DE = new curr_char_ptr
; Returns:
;   DE = intact
;   HL -> curr_char_ptr
; Destroys:
;   BC, DE, and HL

	push	de
	ld	bc,curr_char_ptr_offset
	call	util.GetIDSDataPtr
	pop	de
	ld	(hl),de
	ret


;-------------------------------------------------------------
textio_GetIDSX:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = x-position for the specified IDS
; Destroys:
;   BC and DE

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)


;-------------------------------------------------------------
util.GetIDSX:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL = x-position for the specified IDS
; Destroys:
;   BC and DE

	ld	bc,xPos_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)				; HL = original cursor x
	ret


;-------------------------------------------------------------
textio_GetIDSY:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = cursor y-position for specified IDS
; Destroys:
;   BC and DE

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetIDSY


;-------------------------------------------------------------
util.GetIDSY:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL = cursor y-position for specified IDS
; Destroys:
;   BC and DE

	ld	bc,yPos_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)				; a = cursor y
	ret


;-------------------------------------------------------------
util.SetFirstVisibleCharPtr:
; Arguments:
;   HL = IDS pointer
;   DE = new visible_buffer_ptr value
; Returns:
;   HL -> visible_buffer_ptr
;   DE =  intact
; Destroys:
;   BC and DE

	push	de
	ld	bc,first_visible_char_ptr_offset
	call	util.GetIDSDataPtr
	pop	de
	ld	(hl),de				; HL = visible_buffer_ptr
	ret


;-------------------------------------------------------------
util.GetFirstVisibleCharPtr_IDSPtr:
; Necessary for util.DrawDataBufferContents
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL = pointer to the visible_buffer_ptr for the specified IDS
; Destroys:
;   BC and DE

	ld	bc,first_visible_char_ptr_offset
	call	util.GetIDSDataPtr
	ret

util.GetFirstVisibleCharPtr:
	ld	bc,first_visible_char_ptr_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)				; HL = visible_buffer_ptr
	ret


;-------------------------------------------------------------
util.GetVisibleBufferWidth:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL = visible_buffer_width for the specified IDS
; Destroys:
;   BC and DE

	ld	bc,visible_buffer_width_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)				; HL = visible_buffer_width
	ret


;-------------------------------------------------------------
textio_SetCursorColor:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = color
; Returns:
;   None
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	de,(hl)				; DE -> IDS
	push	de
	inc	hl
	inc	hl
	inc	hl
	ld	e,(hl)				; E = cursor color
	pop	hl				; HL -> IDS
	push	de
	push	hl
	push	hl				; Extra push to satisfy util.GetIDSDataPtr requirements
	ld	bc,cursor_color_offset
	call	util.GetIDSDataPtr
	pop	bc
	pop	bc
	pop	de
	ld	(hl),e				; HL -> cursor color slot
	ret


;-------------------------------------------------------------
textio_GetCursorColor:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = cursor color
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetCursorColor


;-------------------------------------------------------------
util.GetCursorColor:
; Arguments:
;   HL = IDS pointer
; Returns:
;   A = cursor color
; Destroys:
;   BC, DE, and HL

	ld	bc,cursor_color_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)				; HL -> cursor color slot
	ret


;-------------------------------------------------------------
textio_GetCursorBGColor:
; Arguments:
;   None
; Returns:
;   A = background color of the cursor in the last IDS used
; Destroys:
;   BC, DE, and HL

	ld	a,(_CursorBGColor)
	ret


;-------------------------------------------------------------
util.GetCursorBGColor:
; Arguments:
;   HL -> IDS
; Returns:
;   A = cursor background color
; Destroys:
;   BC, DE, and HL

	call	util.GetCursorY
	ld	bc,0
	ld	c,a
	push	bc
	ld	hl,(_CurrCursorX)
	push	hl
	call	gfx_GetPixel
	pop	hl
	pop	hl
	ld	(_CursorBGColor),a
	ret


;-------------------------------------------------------------
textio_SetCursorBlinkRate:
; Arguments:
;   arg0 = cursor blink rate (0 - 255)
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	l,(hl)
	ld	h,$ff
	mlt	hl
	ld	(_CursorDisplayTime),hl

; Divide the (_CursorDisplayTime) in half
	srl	h
	push	af
	srl	l
	pop	af
	jr	nc,.return
	ld	a,l
	xor	a,$80				; Carry the lowest bit of H
	ld	l,a				; into the highest bit of L

.return:
	ld	(_HalfCursorDisplayTime),hl
	ret


;-------------------------------------------------------------
textio_GetCurrCursorX:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = Current cursor x-position
; Destroys:
;   None

	ld	hl,(_CurrCursorX)
	ret


;-------------------------------------------------------------
textio_SetCursorY:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = cursor y-position
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	ld	hl,arg1
	add	hl,sp
	ld	a,(hl)
	dec	hl
	dec	hl
	dec	hl
	ld	hl,(hl)
	ld	bc,cursor_y_offset
	call	util.GetIDSDataPtr
	ld	(hl),a
	ret


;-------------------------------------------------------------
textio_GetCursorY:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = cursor y-position
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetCursorY


;-------------------------------------------------------------
util.GetCursorY:
; Arguments:
;   HL -> IDS
; Returns:
;   A = cursor y-position
; Destroys:
;   BC, DE, and HL

	ld	bc,cursor_y_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	ret


;-------------------------------------------------------------
textio_SetCursorDimensions:
; Arguments:
;   arg0 = pointer to IDS
;   arg1 = cursor width
;   arg2 = cursor height
; Returns:
;   True if dimensions set; False, otherwise
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)				; HL -> IDS
	push	hl
	push	hl				; Extra push to satisfy util.GetIDSDataPtr requirements
	ld	bc,cursor_width_offset
	call	util.GetIDSDataPtr
	pop	bc
	pop	bc
	ld	de, (hl)			; Load DE with old dimensions (3rd byte holds
						; the IDS attribute byte)
	push	hl
	ld	hl,arg1 + 3			; Plus 3 for stack local
	add	hl,sp
	ld	e, (hl)				; E = cursor width
	inc	hl
	inc	hl
	inc	hl				; HL -> cursor height
	ld	d,(hl)				; D = cursor height

	push	de
	mlt	de				; If either the width or height is zero, DE will be zero
	xor	a, a
	sbc	hl,hl
	sbc	hl,de
	ret	z				; Return if invalid width or height
	pop	de

	pop	hl				; HL -> cursor width slot
	ld	(hl),de				; Since DE is stored little-endian, E (width) will be
	ld	a,1				; stored before D (height), and the IDS attribute byte
	ret					; will be overwritten with the same value


;-------------------------------------------------------------
textio_GetCursorWidth:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = cursor width of specified IDS
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetCursorWidth


;-------------------------------------------------------------
util.GetCursorWidth:
; Arguments:
;   HL = IDS pointer
; Returns:
;   A = cursor width of specified IDS
; Destroys:
;   BC, DE, and HL

	ld	bc,cursor_width_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)				; HL -> cursor width slot
	ret


;-------------------------------------------------------------
textio_GetCursorHeight:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = cursor height of specified IDS
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetCursorHeight


;-------------------------------------------------------------
util.GetCursorHeight:
; Arguments:
;   HL = IDS pointer
; Returns:
;   A = cursor height of specified IDS
; Destroys:
;   BC, DE, and HL

	ld	bc,cursor_height_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)				; HL -> cursor height slot
	ret


;-------------------------------------------------------------
textio_SetIDSTimer:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = time
; Returns:
;   None
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	bc,(hl)
	push	bc
	ex	de,hl
	ld	bc,timer_offset
	call	util.GetIDSDataPtr
	pop	bc
	ld	(hl),bc
	ret


;-------------------------------------------------------------
textio_GetIDSTimer:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = time
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	ld	bc,timer_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)
	ret


;-------------------------------------------------------------
textio_SetPrgmNameFlag:
; Arguments:
;   arg0 = pointer to specified IDS
;   arg1 = flag state
; Returns:
;   None
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	de,(hl)				; DE -> IDS
	push	de
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)				; A = flag state
	pop	hl
	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	srl	(hl)
	sla	(hl)				; Zero prgm_name flag
	xor	a,(hl)				; Set prgm_name flag to state
	ld	(hl),a				; Store attribute bit again
	ret


;-------------------------------------------------------------
util.GetPrgmNameFlag:
; Arguments:
;   HL = IDS pointer
; Returns:
;   NZ if set; Z, otherwise
; Destroys:
;   BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	bit	0,(hl)				; HL -> IDS attribute byte
	ret


;-------------------------------------------------------------
textio_LockIDS:
; Arguments:
;   arg0 = pointer to IDS
;   arg1 = desired flag state
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	push	hl
	ld	hl,(hl)
	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	pop	de
	push	hl
	ex	de,hl
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)				; A = desired flag state
	pop	hl
	set	1,(hl)				; Set the IDS_Lock flag by default
	cp	a,1
	ret	z				; Return if set was the desired state
	ld	a,$02
	xor	a,(hl)				; Else, reset the IDS_Lock flag
	ld	(hl),a				; Rewrite the attribute byte
	ret

;-------------------------------------------------------------
textio_GetIDSLock:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = state of IDS_Lock flag
; Destroys:
;   A, BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetIDSLock


;-------------------------------------------------------------
util.GetIDSLock:
; Arguments:
;   HL = IDS pointer
; Returns:
;   A = state of IDS_Lock flag
; Destroys:
;   A, BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	ld	b,(hl)				; B = IDS attribute byte
	ld	a,0				; Set A to 0 by default
	bit	1,b				; Find the current IDS_Lock flag state
	ret	z				; Return if it is set
	ld	a,1				; Else, set A to 1 and return
	ret


;-------------------------------------------------------------
util.SetBufferFullFlag:
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	bit	2,a
	ret	nz
	xor	a,$04
	ld	(hl),a
	ret


;-------------------------------------------------------------
util.ResetBufferFullFlag:
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	bit	2,a
	ret	z
	xor	a,$04
	ld	(hl),a
	ret


;-------------------------------------------------------------
textio_GetBufferFullFlag:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = state of buffer_full flag
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetBufferFullFlag


;-------------------------------------------------------------
util.GetBufferFullFlag:
; Arguments:
;   HL = IDS pointer
; Returns:
;   A = state of buffer_full flag
; Destroys:
;   BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	ld	b,(hl)
	ld	a,0
	bit	2,b
	ret	z
	ld	a,1
	ret


;-------------------------------------------------------------
util.GetIDSTimerFlag:
; Arguments:
;   HL = IDS pointer
; Returns:
;   NZ if flag is set; Z otherwise
; Destroys:
;   BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	bit	3,(hl)
	ret


;-------------------------------------------------------------
util.SetIDSTimerFlag:
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   BC, DE, and HL

	ld	bc,ids_attr_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	bit	3,a
	ret	nz
	ld	b,8
	xor	a,b
	ld	(hl),a
	ret


;-------------------------------------------------------------
textio_ClearDataBuffer:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   None
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)				; HL -> IDS
	push	hl
	call textio_GetDataBufferSize
	pop	bc
	push	hl				; HL = data buffer size
	push	bc				; BC -> IDS
	call	textio_GetDataBufferPtr
	pop	bc				; HL -> data buffer
	pop	bc				; BC = data buffer size
	call	util.SetMemNull
	ret


;-------------------------------------------------------------
textio_AllocKeymap:
; Arguments:
;   arg0 = keymap indicator
;   arg1 = keymap data pointer
;   arg2 = pointer to malloc routine
; Returns:
;   Pointer to keymap, if successful; NULL, otherwise
; Destroys:
;   All

; Allocate bytes for keymap
	ld	hl,arg2
	add	hl,sp
	ld	hl,(hl)				; HL -> malloc routine
	ld	bc,keymap_size
	push	bc
	call	util.CallHL			; Call malloc routine
	pop	bc
	add	hl,bc
	sbc	hl,bc
	ret	z				; Return if malloc routine returned NULL

; Write keymap data to allocated memory
	push	hl
	ld	hl,arg0 + 3			; Plus 3 for stack local
	add	hl,sp
	ld	a,(hl)				; A = keymap indicator
	inc	hl
	inc	hl
	inc	hl
	ld	de,(hl)				; DE -> keymap data
	pop	hl
	push	hl
	ld	(hl),a				; Store keymap indicator to new keymap
	inc	hl
	ld	bc,keymap_size - 1		; Minus one for indicator
	ex	de,hl				; After exchange, HL -> keymap data and DE -> byte after
						; indicator
	ldir

; Return pointer to keymap data
	pop	hl
	ret


;-------------------------------------------------------------
textio_FreeKeymap:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = pointer to free_routine
; Returns:
;   None
; Destroys:
;   All

	ld	hl,arg0
	add	hl,sp
	ld	de,(hl)				; DE -> IDS
	push	de
	inc	hl
	inc	hl
	inc	hl
	ld	hl,(hl)				; HL -> free_routine
	call	util.CallHL			; Call free_routine
	pop	de
	ret


;-------------------------------------------------------------
textio_SetKeymaps:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = number of keymaps
;   arg2 = pointer to first keymap
;   ...
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	de,(hl)				; DE -> IDS
	inc	hl
	inc	hl
	inc	hl
	push	hl				; HL -> number of keymaps
	ex	de,hl

; Seek to the num_keymaps_offset
	ld	bc,num_keymaps_offset
	call	util.GetIDSDataPtr
	pop	de				; DE -> number of keymaps

; Write num_keymaps to offset
	ex	de,hl				; After exchange, DE -> number of keymaps slot | HL ->
						; number of keymaps
	ld	a,(hl)
	dec	a				; Decrement number of keymaps because the first keymap
						; number is zero, not one
	ld	(de),a
	ld	b,(hl)				; Setup counter

; Get pointer to first keymap
	ex	de,hl
	inc	hl				; HL -> current keymap number
	ld	(hl),0
	inc	hl				; HL -> first keymap slot
	inc	de
	inc	de
	inc	de				; DE -> first keymap pointer


.loop:
; Write keymap pointer to slot
	push	de				; Save DE which points to keymap pointers on the stack
	push	hl				; Save HL which points to the IDS keymap slots
	ex	de,hl
	ld	hl,(hl)				; HL -> keymap
	ex	de,hl				; After exchange, DE -> keymap | HL -> keymap pointer
	pop	hl				; HL -> keymap slot
	ld	(hl),de				; Write the keymap pointer to the slot
	pop	de				; Recover pointer to keymap pointers
	push	bc				; Save counter to stack
	ld	bc,3
	add	hl,bc				; Increment the keymap slot pointer
	ex	de,hl
	add	hl,bc				; Increment the pointer to the keymap pointer
	ex	de,hl				; And store it to its register again
	pop	bc				; Recover counter
	djnz	.loop

	ret



;-------------------------------------------------------------
textio_GetNumKeymaps:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = number of available keymaps for specified IDS
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	ld	bc,num_keymaps_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	ret


;-------------------------------------------------------------
textio_SetCurrKeymapNum:
; Arguments:
;   arg0 = IDS pointer
;   arg1 = Keymap index
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	push	hl
	ld	hl,(hl)				; HL -> IDS
	ld	bc,curr_keymap_num_offset
	call	util.GetIDSDataPtr
	pop	de				; DE -> arg0
	inc	de
	inc	de
	inc	de
	ex	de,hl				; After exchange: DE -> current keymap offset | HL -> keymap index
	ld	a,(hl)
	ld	(de),a
	ret


;-------------------------------------------------------------
textio_GetCurrKeymapNum:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = Current keymap number
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	ld	bc,curr_keymap_num_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	ret


;-------------------------------------------------------------
textio_GetCurrKeymapPtr:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   HL = Pointer to current keymap
; Destroys:
;   A, BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
assert $= util.GetCurrKeymapPtr


;-------------------------------------------------------------
util.GetCurrKeymapPtr:
; Arguments:
;   HL = IDS pointer
; Returns:
;   HL = Pointer to current keymap
; Destroys:
;   A, BC, DE, and HL

	ld	bc,curr_keymap_num_offset
	call	util.GetIDSDataPtr
	ld	a,(hl)
	inc	hl
	cp	a,0
	jr	z,.return
	ld	b,a
.loop:
	inc	hl
	inc	hl
	inc	hl
	djnz	.loop
.return:
	ld	hl,(hl)
	ret


;-------------------------------------------------------------
textio_GetCurrKeymapIndicator:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = keymap indicator
; Destroys:
;   BC, DE, and HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	call	util.GetCurrKeymapPtr
	ld	a,(hl)
	ret


;-------------------------------------------------------------
textio_GetUppercaseLettersKeymap:
; Arguments:
;   None
; Returns:
;   HL = Pointer to keymap
; Destroys:
;   None

	ld	hl,_UppercaseLettersKeymap
	ret


;-------------------------------------------------------------
textio_GetLowercaseLettersKeymap:
; Arguments:
;   None
; Returns:
;   HL = Pointer to keymap
; Destroys:
;   None

	ld	hl,_LowercaseLettersKeymap
	ret


;-------------------------------------------------------------
textio_GetPrgmNameLettersKeymap:
; Arguments:
;   None
; Returns:
;   HL = Pointer to keymap
; Destroys:
;   None

	ld	hl,_PrgmNameLettersKeymap
	ret


;-------------------------------------------------------------
textio_GetNumericalKeymap:
; Arguments:
;   None
; Returns:
;   HL = Pointer to keymap
; Destroys:
;   None

	ld	hl,_NumericalKeymap
	ret


;-------------------------------------------------------------
textio_SetClearKey:
; Arguments:
;   arg0 = key
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	(_ClearKey),a
	ret


;-------------------------------------------------------------
textio_SetBackspaceKey:
; Arguments:
;   arg0 = key
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	(_BackspaceKey),a
	ret


;-------------------------------------------------------------
textio_SetCursorLeftKey:
; Arguments:
;   arg0 = key
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	(_CursorLeftKey),a
	ret


;-------------------------------------------------------------
textio_SetCursorRightKey:
; Arguments:
;   arg0 = key
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	(_CursorRightKey),a
	ret


;-------------------------------------------------------------
util.EraseVisibleBufferContents:
; Arguments:
;   HL -> IDS
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	push	hl
	ld	hl,(_CursorBGColor)
	push	hl
	call	gfx_SetColor
	pop	hl
	pop	hl

	ld	bc,cursor_height_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)
	push	hl

; Get the cursor width and add it to the visible_buffer_width to take care of any
; cursor overdraw
	ex	de,hl
	call	util.GetCursorWidth
	push	af				; A = cursor width
	ex	de,hl
	call	util.GetVisibleBufferWidth
	pop	af
	ld	bc,0
	ld	c,a
	add	hl,bc
	push	hl
	ex	de,hl

	ld	bc,cursor_y_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)
	push	hl
	ex	de,hl
	ld	bc,xPos_offset
	call	util.GetIDSDataPtr
	ld	hl,(hl)
	push	hl
	call	gfx_FillRectangle_NoClip
	pop	hl
	pop	hl
	pop	hl
	pop	hl
	ret


;-------------------------------------------------------------
util.DrawDataBufferContents:
; Draws visible portion of data buffer
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

; Erase any already drawn chars
	push	hl
	call	util.EraseVisibleBufferContents
	pop	hl

; Set the glyph drawing coordinates
	push	hl
	call	util.GetIDSY
	ld	bc,0
	ld	c,a
	push	bc
	ex	de,hl
	call	util.GetIDSX
	inc	hl				; Increment xPos so that the char doesn't overdraw the cursor
	push	hl
	call	util.SetTextPosition
	pop	hl
	pop	hl
	pop	hl

	call	util.GetFirstVisibleCharPtr

	ld	bc,0

.loop:

; If the char being processed is the char pointed to by curr_char_ptr, set cursor xPos
	push	bc
	push	hl
	ex	de,hl
	call	util.GetCurrCharPtr
	pop	bc				; BC -> char being processed
	xor	a,a
	sbc	hl,bc
	push	bc
	pop	hl				; HL -> char being processed
	pop	bc				; DE -> IDS | BC = temp width
	jr	nz,.cont1

	push	hl
	ex	de,hl
	push	bc
	call	util.GetIDSX
	pop	bc
	add	hl,bc				; HL = cursor xPos
	push	de				; DE -> IDS
	ex	de,hl
	ld	hl,_CurrCursorX
	ld	(hl),de
	pop	de
	pop	hl				; HL -> char being processed

.cont1:
; State of registers:
; HL -> char being processed
; DE -> IDS
; BC =  width of visible chars
; Nothing on the stack

; Return if char being processed is NULL
; Set the buffer_full flag if the char being processed is the null-terminator
; Reset it otherwise
	xor	a,a
	cp	a,(hl)
	jr	nz,.cont2
	ret

.cont2:
; Get the width of the char being processed and add it to BC
	push	de				; DE -> IDS
	push	hl				; HL -> char being processed
	push	bc				; BC =  width of visible chars
	ld	de,0
	ld	e,(hl)
	push	de
	call	util.GetCharWidth
	pop	de
	pop	bc
	add	hl,bc
	push	hl
	pop	bc
	pop	de				; DE -> char being processed
	pop	hl				; HL -> IDS

; If the width of the visible chars > visible_buffer_width:
; 	Set the last_visible_char_ptr
; 	Return
	push	de
	push	bc
	call	util.GetVisibleBufferWidth
	pop	bc
	xor	a,a
	sbc	hl,bc
	pop	hl
	jr	nc,.cont3

	dec	hl				; Now HL points to the last char that fit
	ld	(_LastVisibleCharPtr),hl
	ret

.cont3:
; State of registers:
; HL -> char being processed
; DE -> IDS
; BC =  width of visible chars
; Nothing on the stack

	push	bc
	push	de
	push	hl
	ld	de,0
	ld	e,(hl)

; If the character being processed is the theta codepoint set by the programmer,
; call a programmer-defined function that draws the theta character instead of
; printing the character automatically. This compensates for not being able to edit
; the GraphX font like you can a FontLibC font.
	call	textio_GetThetaCodepoint
	cp	a,e
	jr	nz,.drawNormal

	ld	hl,(_DrawThetaChar)
	call	util.CallHL
	jr	.cont4

.drawNormal:
	push	de
	call	util.DrawChar
	pop	de
.cont4:
	pop	hl				; HL -> char being processed
	pop	de				; DE -> IDS
	pop	bc				; BC =  width of visible chars
	inc	hl
	jp	.loop


;-------------------------------------------------------------
util.AddAtoBC_2byte:
; NOTE: This function will only work if BC < 2^16 - A
; Arguments:
;   BC and A
; Returns:
;   BC = BC + A

	add	a,c
	ld	c,a
	ret	nc
	inc	b
	ret


;-------------------------------------------------------------
util.ResumeTimer:
; Sets up timer_3
	ld	hl,$f20030			; timer_Control
	ld	a,(hl)
	xor	a,$40				; TIMER3_DISABLE
	ld	(hl),a
	ld	hl,$f20024			; timer_3_ReloadValue
	ld	de,(_TimerCounter)
	ld	(hl),de
	ld	hl,$f20020			; timer_3_Counter
	ld	(hl),de
	ld	hl,$f20030
	ld	(hl),$c0
	inc	hl
	ld	(hl),$01			; TIMER3_ENABLE | TIMER3_32K | TIMER3_0INT | TIMER3_DOWN
	ret


;-------------------------------------------------------------
util.HasOneSecondPast:
; Returns NZ if true; Z otherwise
	ld	hl,$f20034			; timer_IntStatus
	bit	6,(hl)				; TIMER3_MATCH1
	ret


;-------------------------------------------------------------
util.AckInt:
; Acknowledges timer interrupt
	ld	hl,$f20034			; timer_IntStatus
	ld	(hl),$40			; TIMER3_MATCH1
	ret


;-------------------------------------------------------------
util.UpdateBufferFullFlag:
; Sets the buffer_full flag if the data buffer is full.
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	push	hl
	ld	bc,(hl)
	inc	hl
	inc	hl
	add	hl,bc				; HL -> last char in data buffer
	xor	a,a
	cp	a,(hl)
	pop	hl
	jr	z,.resetFlag
	call	util.SetBufferFullFlag
	ret
.resetFlag:
	call	util.ResetBufferFullFlag
	ret


;-------------------------------------------------------------
util.UpdateCursorBlinkCounter:
; Arguments:
;   None
; Returns:
;   C if first part of counter has expired; NC otherwise


	ld	hl,(_CursorDisplayCounter)
	dec	hl
	ld	(_CursorDisplayCounter),hl
	ld	de,(_HalfCursorDisplayTime)
	xor	a,a
	sbc	hl,de
	ret	nc
	add	hl,de
	ld	de,0
	xor	a,a
	sbc	hl,de
	scf
	ret	nz
	ld	hl,(_CursorDisplayTime)
	ld	(_CursorDisplayCounter),hl	; Reset the cursor display counter if it has reached zero
	ret


;-------------------------------------------------------------
util.DrawCursor:
; Arguments:
;   HL = IDS pointer
;   A  = color of cursor
; Returns:
;   None
; Destroys:
;   All

	push	hl				; Save IDS pointer
	ld	hl,0
	ld	l,a
	push	hl
	call	gfx_SetColor
	pop	hl				; Set color
	pop	hl

	ld	bc,cursor_height_offset
	call	util.GetIDSDataPtr		; util.GetIDSDataPtr will return the IDS pointer in DE
	ld	bc,0
	ld	c,(hl)
	push	bc

	dec	hl				; HL -> cursor width
	ld	c,(hl)
	push	bc
	ex	de,hl

	ld	bc,cursor_y_offset
	call	util.GetIDSDataPtr
	ld	c,(hl)
	push	bc

	ld	hl,(_CurrCursorX)
	push	hl
	call	gfx_FillRectangle_NoClip
	pop	hl
	pop	hl
	pop	hl
	pop	hl
	ret


;-------------------------------------------------------------
util.GetKey:
; Arguments:
;   HL = IDS pointer
; Returns:
;   A = sk_key_t keycode
; Destroys:
;   BC, DE, and HL

	push	hl
	call	util.UpdateBufferFullFlag
	pop	hl
	push	hl
	call	util.GetIDSTimerFlag
	pop	hl
	jr	z,.notTimed
	push	hl
	ld	hl,$f20028			; timer_3_MatchValue_1
	ld	de,0
	ld	(hl),de
	call	util.ResumeTimer
	pop	hl				; HL -> IDS
.timed:
; If this is a timed input function, decrement the IDS timer if one second has elapsed
	push	hl
	call	util.HasOneSecondPast
	pop	hl
	jr	z,.notTimed			; If one second hasn't elapsed, skip decrementation
	push	hl
	ld	bc,timer_offset
	call	util.GetIDSDataPtr
	ld	de,(hl)				; DE = timer amount
	dec	de
	ld	(hl),de
	ld	de,$008000			; Reset the timer_3_Counter
	ld	(_TimerCounter),de
	call	util.ResumeTimer
	call	util.AckInt
	pop	hl				; HL -> IDS
	xor	a,a				; Zero A so that the "keycode" returned will be zero
	ret

.notTimed:
; Do not draw cursor if curr_char_ptr == the null-terminator
	push	hl
	call	util.GetCurrCharPtr
	ex	de,hl				; After exchange: DE = curr_char_ptr
	pop	hl
	push	hl
	ld	bc,(hl)
	inc	hl
	inc	hl
	inc	hl
	add	hl,bc				; HL -> null-terminator
	xor	a,a
	sbc	hl,de
	pop	hl
	push	hl
	jr	z,.skipCursorDraw

	call	util.UpdateCursorBlinkCounter
	jr	c,.setDrawCursorColorToBG
	pop	hl
	push	hl
	call	util.GetCursorColor
	jr	.drawCursor
.setDrawCursorColorToBG:
	ld	a,(_CursorBGColor)
.drawCursor:
	pop	hl
	push	hl
	call	util.DrawCursor			; Temporary arrangement for testing purposes

.skipCursorDraw:
	call	_GetCSC
	ld	hl,($f20020)			; Save the timer_3_Counter in case of function exit
	ld	(_TimerCounter),hl		; This is to improve timer accuracy
	pop	hl
	cp	a,0
	ret	nz
	push	hl
	call	util.GetIDSTimerFlag
	pop	hl
	jr	z,.notTimed
	jr	.timed


;-------------------------------------------------------------
util.ShiftCharsRightByOne:
; Arguments:
;   HL -> IDS
;   DE -> start of char string to shift
; Returns:
;   Shifts chars in data buffer to the right by one
;   Returns A = 1 if successful; A = 0, otherwise
; Destroys:
;   A, BC, DE, and HL

	ld	bc,(hl)				; BC = data buffer size
	inc	hl
	inc	hl
	add	hl,bc				; HL -> last char of data buffer
	xor	a,a
	cp	a,(hl)
	ret	nz				; Return if buffer is full

	push	de
	pop	hl				; HL -> start of string to shift
.loop:
	inc	hl
	cp	a,(hl)				; A is still NULL
	jr	nz,.loop

	push	hl				; HL -> first NULL character
	sbc	hl,de				; Make sure C is reset
	push	hl
	pop	bc				; BC = number of characters to shift
	pop	de				; DE -> first NULL character
	ld	hl,0
	add	hl,de
	dec	hl				; HL -> last non-null character
	lddr
	ld	a,1
	ret


;-------------------------------------------------------------
util.InsertChar:
; Arguments:
;   HL = IDS pointer
;   A  = keycode/keymap offset
; Returns:
;   Inserts character at the curr_char_ptr
; Destroys:
;   A, BC, DE, and HL

	push	hl				; Save IDS pointer and keymap offset
	push	af

; Return if the IDS is locked
	call	util.GetIDSLock
	ld	b,a
	pop	af
	pop	hl
	bit	0,b
	ret	nz

	push	hl
	push	af
	call	util.GetCurrKeymapPtr		; This does affect A
	inc	hl
	pop	af				; Recover the keymap offset
	add	a,l				; HL -> first keymap codepoint
	jr	nc,.doNotIncH
	inc	h
.doNotIncH:
	ld	l,a
	ld	a,(hl)				; HL -> keymap offset
	cp	a,null				; A  =  codepoint
	pop	hl
	ret	z				; Return early if A is NULL
	call	util.GetCurrCharPtr		; This does not affect A | DE -> IDS
	ld	c,a				; Save A in C
	xor	a,a
	cp	a,(hl)
	jr	z,.writeChar

; If there is a character at the curr_char_ptr, move the characters in front
; of the cursor right

	ex	de,hl				; After exchange: HL -> IDS | DE = curr_char_ptr
	push	bc
	push	de
	push	hl
	call	util.ShiftCharsRightByOne
	pop	de				; DE -> IDS
	pop	hl				; HL = curr_char_ptr
	pop	bc				; C = codepoint
	cp	a,0
	ret	z				; Return without writing char if shift failed
.writeChar:

; If the character being added is the first in the data buffer and it is a numeral and the prgm_name flag
; is set, do not write the character.
	push	bc
	push	hl
	push	de
	ex	de,hl
	inc	hl
	inc	hl
	inc	hl
	pop	de
	ex	de,hl
	push	de
	call	util.GetCurrCharPtr
	pop	bc
	xor	a,a
	sbc	hl,bc
	pop	hl				; HL = curr_char_ptr
	pop	bc
	ld	a,c
	jr	nz,.cont

	cp	a,$3a
	jr	nc,.cont
	cp	a,$30
	jr	c,.cont

	ld	c,a
	push	bc
	ex	de,hl
	push	de
	call	util.GetPrgmNameFlag
	pop	hl				; HL = curr_char_ptr
	pop	bc
	ld	a,c
	jr	z,.cont
	ret

.cont:
	ld	(hl),a				; Write the character at the current offset

; If the curr_char_ptr points to the null terminator, do not increment it

	ex	de,hl				; After exchange: HL -> IDS | DE = curr_char_ptr
	ld	bc,(hl)				; BC = data buffer size
	push	hl				; Save IDS pointer
	inc	hl
	inc	hl
	inc	hl
	add	hl,bc				; This should never carry
	sbc	hl,de				; DE = curr_char_ptr
	pop	hl				; Recover IDS pointer
	ret	z

	push	hl
	inc	de
	call	util.SetCurrCharPtr		; Increment the curr_char_ptr
	pop	hl
	call	util.ScrollVisibleCharsRight
	ret


;-------------------------------------------------------------
util.ClearKeyHandler:
;      If curr_char_ptr > data buffer start, all chars left of the curr_char_ptr
;   are deleted and any chars to the right of the curr_char_ptr are shifted left
;      If curr_char_ptr = data buffer start, all chars right of the curr_char_ptr
;   are deleted
; Arguments:
;   HL -> IDS
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

; If the curr_char_ptr == data buffer start, jump to zeroChars
	call	util.GetCurrCharPtr
	push	de
	push	hl
	inc	de
	inc	de
	inc	de
	xor	a,a
	sbc	hl,de
	pop	hl				; HL =  curr_char_ptr
	pop	bc				; BC -> IDS
	jr	z,.zeroChars

	push	hl
	push	bc
	push	de				; DE -> data buffer start
	push	hl

	push	bc
	pop	hl
	ld	bc,(hl)
	ex	de,hl
	add	hl,bc
	pop	bc
	sbc	hl,bc
	push	hl
	pop	bc				; BC = end of data buffer - curr_char_ptr
	pop	de				; DE -> data buffer start
	pop	hl				; HL -> IDS

; If the curr_char_ptr == end of data buffer, do not shift any chars
	push	bc
	push	hl
	call	util.SetCurrCharPtr
	pop	hl
	call	util.SetFirstVisibleCharPtr
	pop	bc
	ld	hl, 0
	xor	a,a
	sbc	hl, bc
	pop	hl				; HL -> previous curr_char_ptr
	ex	de, hl
	jr	z,.zeroChars

; Copy data from the temporary pointer to the curr_char_ptr
; When code execution reaches here, DE -> data buffer start
	ex	de, hl
	ldir
	ex	de, hl

.zeroChars:
; HL -> start of data to zero
.loop:
	ld	(hl),a
	inc	hl
	cp	a,(hl)
	jr	nz,.loop
	ret


;-------------------------------------------------------------
util.BackspaceKeyHandler:
;   Shifts chars in front of target char left one byte and zeros the trailing
;   char after the shift is complete
; Arguments:
;   HL -> IDS
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

; Verify that the curr_char_ptr > start of data buffer
; If not, return early

	call	util.GetCurrCharPtr
	push	de				; DE -> IDS
	inc	de
	inc	de
	inc	de
	xor	a,a
	push	hl
	sbc	hl,de
	pop	de				; DE -> curr_char_ptr
	pop	hl				; HL -> IDS
	ret	z

	push	hl
	dec	de				; DE -> char to be deleted
	call	util.SetCurrCharPtr		; Decrement the curr_char_ptr

; If first_visible_char_ptr > data buffer start:
; 	Decrement the first_visible_char_ptr
	pop	hl				; HL -> IDS
	push	de				; DE =  curr_char_ptr
	call	util.GetFirstVisibleCharPtr
	push	de
	pop	bc				; BC -> IDS
	pop	de
	ex	de,hl				; After exchange: DE = first_visible_char_ptr | HL ->
						; curr_char_ptr
	push	bc				; BC -> IDS
	inc	bc
	inc	bc
	inc	bc
	ex	de,hl
	push	hl				; HL = first_visible_char_ptr
	xor	a,a
	sbc	hl,bc
	pop	hl
	ex	de,hl
	pop	bc
	push	hl				; HL = curr_char_ptr
	jr	z,.loop

	push	bc
	pop	hl				; HL -> IDS
	dec	de				; DE =  New first_visible_char_ptr
	call	util.SetFirstVisibleCharPtr
	pop	hl
	push	hl				; HL = curr_char_ptr

; When code execution reaches here, HL needs to be on the stack as well as in the register
.loop:
	inc	hl				; Increment HL until it points to a NULL
	cp	a,(hl)				; A is still NULL
	jr	nz,.loop
	pop	de				; DE = curr_char_ptr
	sbc	hl,de				; Carry flag is reset when loop breaks
	push	hl
	pop	bc				; BC = number of characters to shift

	push	de
	pop	hl
	inc	hl				; HL = curr_char_ptr + 1
	ldir					; Shift all of the characters left
	ret					; The LDIR will overwrite the trailing character
						; by copying the next null into it


;-------------------------------------------------------------
util.CursorLeftKeyHandler:
;   Moves cursor left (decrements curr_char_ptr)
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

; Return early if the curr_char_ptr == start of data buffer
	call	util.GetCurrCharPtr		; DE -> IDS | HL = curr_char_ptr
	push	de
	push	hl
	inc	de
	inc	de
	inc	de
	xor	a,a
	sbc	hl,de
	pop	de				; DE = curr_char_ptr
	pop	hl				; HL -> IDS
	ret	z

; If the curr_char_ptr == first_visible_char_ptr, decrement first_visible_char_ptr
	push	de
	call	util.GetFirstVisibleCharPtr_IDSPtr
	pop	bc				; BC = curr_char_ptr
	push	de				; DE -> IDS
	push	hl
	ld	hl,(hl)
	xor	a,a
	sbc	hl,bc
	push	bc
	pop	de				; DE = curr_char_ptr
	pop	bc				; BC -> first_visible_char_ptr
	pop	hl				; HL -> IDS
	jr	nz,.cont

	push	hl
	push	de
	push	bc
	pop	de
	ld	hl,0
	add	hl,de
	ld	hl,(hl)
	dec	hl
	ex	de,hl
	ld	(hl),de
	pop	de
	pop	hl

.cont:
	dec	de
	call	util.SetCurrCharPtr
	ret


;-------------------------------------------------------------
util.ScrollVisibleCharsRight:
; Arguments:
;   HL -> IDS
;   DE =  curr_char_ptr
; Returns:
;   None
; Destroys:

; Get the width of the visible chars plus the width of char to the right of them
	push	hl
	push	de
	call	util.GetFirstVisibleCharPtr
	pop	de
	ex	de,hl
	xor	a,a
	sbc	hl,de				; HL = curr_char_ptr | DE = first_visible_char_ptr
	inc	hl
	push	hl
	push	de
	call	textio_GetStringWidthL
	ex	de,hl				; After exchange: DE = width of (visible chars + char to the
						; right of the last visible one)
	pop	hl
	pop	hl
	pop	hl				; HL -> IDS

; While the width obtained above > visible_buffer_width:
; 	Subtract the width of the first visible char from the obtained width
; 	Increment the first_visible_char_ptr
.loop:
	push	de
	call	util.GetVisibleBufferWidth
	pop	bc
	xor	a,a
	sbc	hl,bc
	ret	nc

	push	de				; DE -> IDS
	push	bc				; BC =  width of visible chars
	ex	de,hl
	call	util.GetFirstVisibleCharPtr
	ld	bc,0
	ld	c,(hl)
	push	bc
	call	util.GetCharWidth
	ex	de,hl				; After exchange: DE = character width
	pop	bc
	pop	hl				; HL =  width of visible chars
	xor	a,a
	sbc	hl,de
	ex	de,hl
	pop	hl				; HL -> IDS
	push	de				; DE = width of visible chars
	call	util.GetFirstVisibleCharPtr_IDSPtr
	ld	bc,(hl)
	inc	bc
	ld	(hl),bc
	ex	de,hl
	pop	de
	jr	.loop


;-------------------------------------------------------------
util.CursorRightKeyHandler:
;   Moves cursor right (increments curr_char_ptr)
; Arguments:
;   HL = IDS pointer
; Returns:
;   None
; Destroys:
;   A, BC, DE, and HL

	call	util.GetCurrCharPtr
	xor	a,a
	cp	a,(hl)
	ret	z
	ex	de,hl				; After exchange: HL -> IDS | DE = curr_char_ptr
	inc	de
	push	hl
	call	util.SetCurrCharPtr

; If the curr_char_ptr < the last visible char + 1:
; 	Do not scroll the visible chars
	push	de				; DE = curr_char_ptr
	ld	hl,(_LastVisibleCharPtr)
	inc	hl
	sbc	hl,de
	pop	de
	pop	hl				; HL -> IDS
	ret	nc

; Otherwise, scroll them
	call	util.ScrollVisibleCharsRight
	ret


;-------------------------------------------------------------
textio_TimedInput:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   None
; Destroys:
;   All

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	call	util.SetIDSTimerFlag
assert $= textio_Input


;-------------------------------------------------------------
textio_Input:
; Arguments:
;   arg0 = IDS pointer
; Returns:
;   A = keycode
; Destroys:
;   All

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)

; Erase any previously drawn characters
	push	hl
	call	util.GetCursorBGColor
	pop	hl
	push	hl
	call	util.DrawDataBufferContents
	pop	hl
	call	util.GetKey
	push	af				; Save the keycode
	ex	de,hl				; Save IDS pointer in DE

	ld	hl,_ClearKey
	cp	a,(hl)
	jr	z,.clear_key_pressed

	ld	hl,_BackspaceKey
	cp	a,(hl)
	jr	z,.backspace_key_pressed

; If the prgm_name flag is set and the CursorLeftKey is pressed,
; bypass the CursorLeftKeyHandler and activate the BackspaceKeyHandler.
	ld	hl,_CursorLeftKey
	cp	a,(hl)
	jr	nz,.skipFlagTest
	ex	de,hl
	call	util.GetPrgmNameFlag		; This will leave DE -> IDS
	jr	nz,.backspace_key_pressed
	jr	.cursor_left_key_pressed

.skipFlagTest:
	ld	hl,_CursorRightKey
	cp	a,(hl)
	jr	z,.cursor_right_key_pressed

; Default case: Add keymap character to data buffer
	ex	de,hl
	push	hl
; If the curr_char_ptr == end of data buffer, do not add char
	call	util.GetCurrCharPtr
	ex	de,hl				; After exchange: DE = curr_char_ptr | HL -> IDS
	ld	bc,(hl)				; BC = data buffer size
	inc	hl
	inc	hl
	inc	hl
	add	hl,bc				; This should not carry | HL -> end of data buffer
	sbc	hl,de
	jr	z,.exit
	pop	hl				; Recover HL for util.InsertChar
	push	hl
	call	util.InsertChar
	jr	.exit

.clear_key_pressed:
	ex	de,hl
	push	hl
	call	util.ClearKeyHandler
	jr	.exit
.backspace_key_pressed:
	ex	de,hl
	push	hl
	call	util.BackspaceKeyHandler
	jr	.exit
.cursor_left_key_pressed:
	ex	de,hl
	push	hl
	call	util.CursorLeftKeyHandler
	jr	.exit
.cursor_right_key_pressed:
	ex	de,hl
	push	hl
	call	util.CursorRightKeyHandler
	jr	.exit

.exit:
	pop	hl				; The IDS pointer needs to be on the stack
	call	util.DrawDataBufferContents
	pop	af				; As well as the keycode
	ret


;-------------------------------------------------------------
textio_SetThetaCodepoint:
; Sets the codepoint that will stand for the theta character
; for the current font.
; Arguments:
;   arg0 = codepoint
; Returns:
;   None
; Destroys:
;   A, BC, and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	hl,_PrgmNameLettersKeymap
	ld	(hl),a
	ld	bc,19
	add	hl,bc
	ld	(hl),a
	ret


;-------------------------------------------------------------
textio_GetThetaCodepoint:
; Gets the current font's codepoint for the theta character.
; Arguments:
;   None
; Returns:
;   A = codepoint
; Destroys:
;   HL

	ld	a,(_PrgmNameLettersKeymap)
	ret


;-------------------------------------------------------------
textio_SetDrawThetaCharFunction:
; Arguments:
;   arg0 = Pointer to function that draws the theta character
; Returns:
;   None
; Destroys:
;   HL

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	ld	(_DrawThetaChar),hl
	ret


;-------------------------------------------------------------
textio_ConvertProgramAppvarName_TIOS:
; Converts any codepoints in the specified name that correspond
; to the codepoint set by textio_SetThetaCodepoint() into the
; TI_OS theta codepoint (0x5B).
; Arguments:
;   arg0 = program/appvar name
; Returns:
;   HL = Pointer to converted name
; Destroys:
;   A and BC

	call	textio_GetThetaCodepoint
	ld	c,a

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	push	hl

.loop:
	xor	a,a
	cp	a,(hl)
	jr	z,.return

	ld	a,c
	cp	a,(hl)
	jr	nz,.cont
	ld	(hl),$5b
.cont:
	inc	hl
	jr	.loop

.return:
	pop	hl
	ret


;-------------------------------------------------------------
textio_ConvertProgramAppvarName_TextIOC:
; Converts any codepoints in the specified name that correspond
; to the TI-OS theta codepoint into the codepoint set by
; textio_SetThetaCodepoint().
; Arguments:
;   arg0 = program/appvar name
; Returns:
;   HL = Pointer to converted name
; Destroys:
;   A and BC

	call	textio_GetThetaCodepoint
	ld	c,a

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	push	hl

.loop:
	xor	a,a
	cp	a,(hl)
	jr	z,.return

	ld	a,$5b
	cp	a,(hl)
	jr	nz,.cont
	ld	(hl),c
.cont:
	inc	hl
	jr	.loop

.return:
	pop	hl
	ret



;=============================================================;
;                                                             ;
;                 Text Output Functions                       ;
;                                                             ;
;=============================================================;


textio_SetTextWindow:
; Arguments:
;   arg0 = x-position
;   arg1 = y-position
;   arg2 = width
;   arg3 = height
; Returns:
;   None
; Destroys:
;   IY, A, and HL

	ld	iy,0
	add	iy,sp
	push	iy
	ld	hl,(iy + arg1)
	ld	(_TextWindowY),hl
	push	hl
	ld	a,(iy + arg0)
	ld	(_TextWindowX),a
	ld	hl,0
	ld	l,a
	push	hl
	call	util.SetTextPosition
	pop	hl
	pop	hl
	pop	iy
	ld	hl,(iy + arg2)
	ld	(_TextWindowWidth),hl
	ld	a,(iy + arg3)
	ld	(_TextWindowHeight),a
	ret


;-------------------------------------------------------------
textio_GetTextWindowX:
; Arguments:
;   None
; Returns:
;   HL = x-position of text window
; Destroys:
;   None

	ld	hl,(_TextWindowX)
	ret


;-------------------------------------------------------------
textio_GetTextWindowY:
; Arguments:
;   None
; Returns:
;   A = y-position of text window
; Destroys:
;   None

	ld	a,(_TextWindowY)
	ret


;-------------------------------------------------------------
textio_GetTextWindowWidth:
; Arguments:
;   None
; Returns:
;   HL = width of text window
; Destroys:
;   None

	ld	hl,(_TextWindowWidth)
	ret


;-------------------------------------------------------------
textio_GetTextWindowHeight:
; Arguments:
;   None
; Returns:
;   A = height of text window
; Destroys:
;   None

	ld	a,(_TextWindowHeight)
	ret


;-------------------------------------------------------------
textio_SetLineSpacing:
; Arguments:
;   arg0 = space above line
;   arg1 = space below line
; Returns:
;   None
; Destroys:
;   DE and HL

	pop	de
	pop	hl
	ld	(_LineSpacingAbove),hl
	ex	(sp),hl
	ld	(_LineSpacingBelow),hl
	push	hl
	ex	de,hl
	jp	(hl)

;-------------------------------------------------------------
textio_GetLineSpacingAbove:
; Arguments:
;   None
; Returns:
;   A = spacing above line
; Destroys:
;   None

	ld	a,(_LineSpacingAbove)
	ret


;-------------------------------------------------------------
textio_GetLineSpacingBelow:
; Arguments:
;   None
; Returns:
;   A = spacing below line
; Destroys:
;   None

	ld	a,(_LineSpacingBelow)
	ret


;-------------------------------------------------------------
textio_SetFontHeight:
; Arguments:
;   arg0 = height of font
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	(_FontHeight),a
	ret


;-------------------------------------------------------------
textio_SetPrintFormat:
; Arguments:
;   arg0 = format code
; Returns:
;   A = 0 if invalid format code passed; A > 0 otherwise
; Destroys:
;   A
;   DE
;   HL

	ld	hl,arg0
	add	hl,sp
	ld	a,bPrintRightMarginFlush
	sub	a,(hl)
	jr	c,.invalidValue
	ld	a,0
	cp	a,(hl)
	jr	z,.invalidValue
	ld	a,(hl)
	ld	(_PrintFormat),a
	ret

.invalidValue:
	xor	a,a
	ret


;-------------------------------------------------------------
textio_GetPrintFormat:
; Arguments:
;   None
; Returns:
;   Current print format code
; Destroys:
;   None

	ld	a,(_PrintFormat)
	ret


;-------------------------------------------------------------
textio_SetNewlineCode:
; Arguments:
;   arg0 = character
; Returns:
;   None
; Destroys:
;   A and HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	ld	(_NewlineCode),a
	ret


;-------------------------------------------------------------
textio_GetNewlineCode:
; Arguments:
;   None
; Returns:
;   A = newline character
; Destroys:
;   None

	ld	a,(_NewlineCode)
	ret


;-------------------------------------------------------------
textio_SetTabSize:
; Arguments:
;   arg0 = width
; Returns:
;   None
; Destroys:
;   HL

	ld	hl,arg0
	add	hl,sp
	ld	a,(hl)
	cp	a,0
	ret	z
	ld	(_TabWidth),a
	ret


;-------------------------------------------------------------
textio_GetTabSize:
; Arguments:
;   None
; Returns:
;   A = width of tab
; Destroys:
;   None

	ld	a,(_TabWidth)
	ret


;-------------------------------------------------------------
textio_PrintChar:
; Arguments:
;   arg0 = char
; Returns:
;   None
; Destroys:
;   All registers and possibly shadow registers as well

	ld	hl,arg0
	add	hl,sp
	ld	a,tab
	cp	a,(hl)
	jr	z,.printTab
	ld	hl,(hl)
	push	hl
	call	util.DrawChar
	pop	hl
	ret
.printTab:
assert $= textio_PrintTab


;-------------------------------------------------------------
textio_PrintTab:
; Arguments:
;   None
; Returns:
;   None
; Destroys:
;   BC and HL

	call	textio_GetTabSize
	ld	b,a
	ld	hl,space

.loop:
	push	bc
	push	hl
	call	util.DrawChar
	pop	hl
	pop	bc
	djnz	.loop
	ret


;-------------------------------------------------------------
textio_GetCharWidth:
; Arguments:
;   arg0 = char
; Returns:
;   HL = width of char
; Destroys:
;   All

	ld	hl,arg0
	add	hl,sp
	ld	b,(hl)
	ld	a,tab
	cp	a,b
	jr	z,.getTabWidth
	or	a,a
	sbc	hl,hl
	ld	l,b
	push	hl
	call	util.GetCharWidth
	pop	de
	ret
.getTabWidth:
	ld	hl,0
	push	hl
	ld	l,space
	push	hl
	call	util.GetCharWidth
	pop	de
	pop	de
	call	textio_GetTabSize
	ld	bc,0
	ld	c,a
	call	util.MultiplyHLBC
	ret


;-------------------------------------------------------------
textio_GetLineWidth:
; Arguments:
;   arg0  =  pointer to line
;   arg1  =  pointer to end of line
; Returns:
;   HL = Width of line
; Destroys:
;   All working registers and iy

	ld	iy,0
	add	iy,sp
	ld	de,(iy + arg0)			; hl -> line
	ld	hl,(iy + arg1) 			; bc -> eol
	xor	a,a
	sbc	hl,de
	push	hl
	pop	bc				; Number of characters in line
	inc	bc
	ex	de,hl
	push	bc
	push	hl
	call	textio_GetStringWidthL
	pop	bc
	pop	bc
	ret

;-------------------------------------------------------------
textio_GetStringWidthL:
; Arguments:
;   arg0 = pointer to string
;   arg1 = number of characters
; Returns:
;   HL = width of characters
; Destroys:
;   All

	ld	hl,arg1
	add	hl,sp
	ld	bc,(hl)
	dec	hl
	dec	hl
	dec	hl
	ld	hl,(hl)
	ld	de,0				; DE = width of characters
.loop:
; Return if BC == 0
	push	hl
	dec	bc
	push	bc
	push	bc
	pop	hl
	ld	bc,0
	xor	a,a
	sbc	hl,bc
	pop	bc
	pop	hl
	jr	z,.exit

	call	textio_GetNewlineCode
	cp	a,(hl)
	jr	z,.exit

	ld	a,(hl)
	cp	a,null
	jr	z,.exit

	push	hl
	push	bc
	push	de
	ld	de,0
	ld	e,(hl)
	push	de
	call	textio_GetCharWidth
	pop	de
	pop	de
	add	hl,de
	ex	de,hl
	pop	bc
	pop	hl
	inc	hl				; HL should be pointer to line
	jr	.loop

.exit:
	ex	hl,de
	ret


;-------------------------------------------------------------
textio_PrintText:
; Arguments:
;   arg0 = pointer to text
;   arg1 = yPos
; Returns:
;   None
; Destroys:
;   All registers and iy

; Load text pointer into HL
	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
; Set the desired yPos
	push	hl
	or	a,a
	sbc	hl,hl
	ex	de,hl
	ld	hl,9
	add	hl,sp
	ld	de,(hl)
	call	textio_GetTextWindowX
	push	de
	push	hl
	call	util.SetTextPosition
	pop	hl
	pop	hl
	pop	hl

.outerLoop:
; Verify that the char that HL points to is not NULL
	ld	a,null
	cp	a,(hl)
	ret z

; Get the next line pointer
	push	hl
	or	a,a
	sbc	hl,hl
	ex	de,hl
	ld	e,1
	pop	hl
	push	de
	push	hl
	call	textio_GetLinePtr
	pop	de			; DE holds pointer to start of current line
	pop	bc
	ex	de,hl
	push	de
	push	hl

; If we are printing centered or RMF, get the line width
; and set the cursor's xPos accordingly.
	ld	a,(_PrintFormat)
	cp	a,bPrintLeftMarginFlush
	jr	nz,.testForCentered
	call	util.GetTextY
	push	hl
	call	textio_GetTextWindowX
	push	hl
	call	util.SetTextPosition
	pop	hl
	pop	hl
	jr	.finishTest

.testForCentered:
	cp	a,bPrintCentered
	jr	nz,.testForPrintRMF
	call	textio_GetLineWidth
	ld	bc,0
	ld	c,2
	call	util.DivideHLBC
	push	hl
	call	textio_GetTextWindowWidth
	ld	bc,0
	ld	c,2
	call	util.DivideHLBC
	pop	de
	or	a,a
	sbc	hl,de
	push	hl
	call	textio_GetTextWindowX
	pop	de
	add	hl,de
	push	hl
	call	util.GetTextY
	pop	de
	push	hl
	push	de
	call	util.SetTextPosition
	pop	hl
	pop	hl
	jr	.finishTest

.testForPrintRMF:
	cp	a,bPrintRightMarginFlush
	jr	nz,.finishTest
	call	textio_GetLineWidth
	ex	de,hl
	call	textio_GetTextWindowWidth
	or	a,a
	sbc	hl,de
	ex	de,hl
	call	textio_GetTextWindowX
	add	hl,de
	push	hl
	call	util.GetTextY
	pop	de
	push	hl
	push	de
	call	util.SetTextPosition
	pop	hl
	pop	hl

.finishTest:
	pop	hl
	pop	de

.innerLoop:
; If current char != printable glyph, jump to getNextLine
	call	textio_GetNewlineCode
	cp	a,(hl)
	jr	z,.testForNextLine
	push	de
	push	hl
	or	a,a
	sbc	hl,hl
	ex	de,hl
	pop	hl
	ld	e,(hl)
	push	hl
	push	de
	call	textio_PrintChar
	pop	hl
	pop	hl
	pop	de

; If current char pointer == next line pointer, jump to outerLoop
.testForNextLine:
	inc	hl
	push	de
	ex	de,hl
	or	a,a
	sbc	hl,de
	ex	de,hl
	pop	de
	jr	nz,.innerLoop

	push	de
	call	util.Newline
	pop	hl

; Return if util.Newline detected that the bottom margin of the
; text window has been exceeded
	ret	c
	jp	.outerLoop


;-------------------------------------------------------------
textio_GetLinePtr:
; Arguments:
;   arg0 = text
;   arg1 = yPos
; Returns:
;   Pointer to next line; NULL if error
; Destroys:
;

; Set line width to zero
	or	a,a
	sbc	hl,hl
	ld	(_LineWidth),hl

; Set the current line number to zero
	ld	a,0
	ld	(_CurrLineNum),a
; Load the desired line number into _LineNum
	ld	hl,arg1
	add	hl,sp
	ld	a,(hl)
	ld	(_LineNum),a

; Load the current char pointer and the current line pointer
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + arg0)
	ld	bc,(iy + arg0)
	push	bc

.outerLoop:
; If current line number == desired line number, return line pointer
	pop	bc
	push	hl
	ld	hl,_CurrLineNum
	ld	a,(_LineNum)
	cp	a,(hl)
	pop	hl
	ret	z

; If current char pointer == null, return line pointer
	ld	a,null
	cp	a,(hl)
	ret	z

	push	bc				; Save pointer to start or line
	call	util.GetApproximateLinePtr
	pop	de
	push	de
	cp	a,null
	jr	z,.testForPrintFormat		; This is necessary since DE must be on the stack
	push	hl
	pop	bc				; BC = approximated pointer
.innerLoop:
	call	textio_GetNewlineCode
	cp	a,(hl)
	jr	z,.testForPrintFormat

	push	hl
	or	a,a
	sbc	hl,de
	pop	hl
	jr	z,.breakString

	dec	hl
	ld	a,space
	cp	a,(hl)
	jr	c,.innerLoop

;	push	de
;	push	hl				; If after the first DEC HL, (HL) is a space, this will force
;	ex	de,hl
;	push	bc
;	pop	hl
;	xor	a,a				; the algorithm to continue decrementing until the start of
;	sbc	hl,de				; the word before the space.
;	ld	a,l
;	cp	a,1
;	pop	hl
;	pop	de
;	jr	z,.innerLoop

	jr	.testForPrintFormat

.breakString:
	push	hl
	or	a,a
	sbc	hl,hl
	ld	(_LineWidth),hl
	pop	hl
	call	util.breakString
.testForPrintFormat:
	ld	a,(_PrintFormat)
	cp	a,bPrintLeftMarginFlush
	jr	z,.incHL
	cp	a,bPrintCentered
	jr	z,.incHL
	call	textio_GetNewlineCode
	cp	a,(hl)
	jr	z,.incHL
	jr	.startNewLine
.incHL:
; Do not increment HL if it points to a NULL
	pop	bc
	ld	a,null
	cp	a,(hl)
	ret	z
	push	bc
	inc	hl
.startNewLine:
	pop	bc
; If the newline is at the start of a line and we are printing RMF, increment HL so that the next
; line will be (address of newline) + 1.
	call	util.startNewLine		; This expects BC to be the line pointer
	push	bc
	jr	.outerLoop


;-------------------------------------------------------------
util.GetApproximateLinePtr:
; Arguments:
;   HL = pointer to start of line
; Returns:
;   HL = approximated pointer to next line
;   A = 0 if function found a NULL
; Destroys:
;   All working registers

; Save pointer to start of line
	push	hl
.loop:
	pop	de
	push	hl
	push	de
	call	textio_GetLineWidth
	ex	de,hl
	pop	bc				; BC = pointer to start of line
	pop	hl				; HL = pointer to current character
	push	bc
	push	hl
	call	textio_GetTextWindowWidth
	or	a,a
	sbc	hl,de
	pop	hl				; HL = pointer to current character
	pop	de				; DE = pointer to start of line
	ld	a,1
	ret	c

	call	textio_GetNewlineCode
	cp	a,(hl)
	ret	z

	ld	a,null
	cp	a,(hl)
	ret	z

	ld	bc,0
	ld	c,(hl)
	push	de
	push	hl
	push	bc
	call	textio_GetCharWidth

; Add character width to line width and increment HL
	pop	bc
	ex	de,hl
	ld	hl,(_LineWidth)
	add	hl,de
	ld	(_LineWidth),hl
	pop	hl
	inc	hl
	jr	.loop


;-------------------------------------------------------------
util.breakString:
; Arguments:
;   HL = pointer to start of string
; Returns:
;   Pointer to the remainder of the string
; Destroys:
;   A, BC, DE, and HL

; General register values:
; BC = number of chars in string
; DE = width of string
; HL = pointer to current char in string being processed


; Set B to zero
	ld	b,0

.loop:
; Determine if the current char is a NULL
	push	hl
	ld	a,null
	cp	a,(hl)
	pop	hl
	ret	z
; Determine if the current char is a tab or glyph
; If printing RMF, spaces and tabs are appended to the start of
; the string
	ld	a,tab
	cp	a,(hl)
	jr	nz,.getGlyphWidth
	push	de
	push	hl
	or	a,a
	sbc	hl,hl
	ld	l,tab
	push	hl
	call	textio_GetCharWidth
	pop	hl
	pop	hl
	pop	de
	jr	.addToStrWidth
.getGlyphWidth:
	push	hl
	or	a,a
	sbc	hl,hl
	ex	de,hl
	pop	hl
	ld	e,(hl)
	push	hl
	push	de
	call	textio_GetCharWidth
	pop	de
	pop	hl
.addToStrWidth:
; Add tab or glyph width to string width (DE)
	push	hl
	push	af
	or	a,a
	sbc	hl,hl
	pop	af
	ld	de,(_LineWidth)
	ld	l,a
	add	hl,de
	ex	de,hl
; If line width + fragment width < window width, jump to loop
	call	textio_GetTextWindowWidth
	or	a,a
	sbc	hl,de
	pop	hl
	ret	c
; Since char was successfully added, add its width to the line width
	ld	(_LineWidth),de
; Increment current char pointer and current char number
	inc	hl
	inc	b
	jr	.loop


;-------------------------------------------------------------
util.startNewLine:
; Arguments:
;   HL = pointer to current character being processed in the line
; Returns:
;   Adds one to _CurrLineNum
;   Sets BC equal to HL
;   Zeros the _LineWidth

; Increment the current line number
	ld	a,(_CurrLineNum)
	inc	a
	ld	(_CurrLineNum),a
; Set the current line pointer to the current char pointer
	ex	de,hl
	xor	a,a
	sbc	hl,hl
	ld	(_LineWidth),hl
	ex	de,hl
	push	hl
	pop	bc
	ret




;-------------------------------------------------------------
; Internal Library Functions
;-------------------------------------------------------------


util.CallHL:
; Calls HL
; Inputs:
;   HL = address to jump to
; Outputs:
;   None

; Return if HL == 0
	push	bc
	ld	bc,0
	xor	a,a
	sbc	hl,bc
	pop	bc
	ret	z

	jp	(hl)
	ret

util.AddAToDE:
; Inputs:
;   A  = Operand 1
;   HL = Operand 2
; Ouputs:
;   DE = DE + A

	push	hl
	ex	de,hl
	ld	de,0
	ld	e,a
	add	hl,de
	ex	de,hl
	pop	hl
	ret


;-------------------------------------------------------------
util.SetMemNull:
; Inputs:
;   BC = number of bytes to set
;   HL = pointer to memory
; Outputs:
;   Memory set to value in A
; Destroys:
;   BC and HL

	xor	a,a				; Resets the carry flag

.loop:
	ld	(hl),a
	dec	bc
	inc	hl
	push	hl				; Save pointer to stack
	sbc	hl,hl
	adc	hl,bc				; If 0 + BC == 0, then BC is 0
	pop	hl
	jr	nz,.loop
	ret



;-------------------------------------------------------------
util.DivideHLBC:
; Performs signed integer division
; Designed by the CE Programming SDK Team. Copied from graphx.asm
; URL: https://github.com/CE-Programming/toolchain/blob/master/src/graphx/graphx.asm
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


;-------------------------------------------------------------
util.MultiplyHLDE:
; Performs (un)signed integer multiplication
; Designed by the CE Programming SDK Team. Copied from graphx.asm
; URL: https://github.com/CE-Programming/toolchain/blob/master/src/graphx/graphx.asm
; Inputs:
;  HL = Operand 1
;  DE = Operand 2
; Outputs:
;  HL = HL * DE

	push	de
	pop	bc

;-------------------------------------------------------------
util.MultiplyHLBC:
; Performs (un)signed integer multiplication
; Designed by the CE Programming SDK Team. Copied from graphx.asm
; URL: https://github.com/CE-Programming/toolchain/blob/master/src/graphx/graphx.asm
; Inputs:
;  HL = Operand 1
;  BC = Operand 2
; Outputs:
;  HL = HL * BC

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


;-------------------------------------------------------------
util.SetTextPosition:
; Sets the cursor position using the external function
; whose address is in _SetTextPosition
; Arguments:
;   arg0 = xPos
;   arg1 = yPos
; Returns:
;   None
; Destroys:
;   All

	ld	hl,arg1
	add	hl,sp
	ld	de,(hl)
	push	de
	dec	hl
	dec	hl
	dec	hl
	ld	de,(hl)
	push	de
	ld	hl,(_SetTextPosition)
	call	util.CallHL
	pop	hl
	pop	hl
	ret


;-------------------------------------------------------------
util.GetTextX:
; Arguments:
;   None
; Returns:
;   HL = cursor x-position
; Destroys:
;   All

	ld	hl,(_GetTextX)
	call	util.CallHL
	ret


;-------------------------------------------------------------
util.GetTextY:
; Arguments:
;   None
; Returns:
;   HL = cursor y-position
; Destroys:
;   All

	ld	hl,(_GetTextY)
	call	util.CallHL
	ret


;-------------------------------------------------------------
util.Newline:
; Adds the line spacing above and below to the font height
; and adds it to the current text y-position to set the new
; text y-position. Sets the text x-position to the text window
; x-position.
; Arguments:
;   None
; Returns:
;   NC if the current text y-position is less than the bottom
;   margin of the text window; C, otherwise.
; Destroys:
;   All

	call	util.GetTextY
	ld	de,0
	ld	a,(_LineSpacingAbove)
	add	a,e
	ld	e,a
	ld	a,(_FontHeight)
	add	a,e
	ld	e,a
	ld	a,(_LineSpacingBelow)
	add	a,e
	ld	e,a
	add	hl,de
	push	hl
	ld	hl,(_TextWindowX)
	push	hl
	call	util.SetTextPosition
	pop	hl
	ld	a,(_TextWindowY)
	ld	e,a
	ld	a,(_TextWindowHeight)
	add	a,e
	pop	de				; E = new text y-position
	sub	a,e
	ret	nz
	scf					; If A == E, set carry flag
	ret


;-------------------------------------------------------------
util.DrawChar:
; Draws a character using the external function
; whose address is in _DrawChar
; Arguments:
;   arg0 = character
; Returns:
;   None
; Destroys:
;   All

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	push	hl
	ld	hl,(_DrawChar)
	call	util.CallHL
	pop	hl
	ret


;-------------------------------------------------------------
util.GetCharWidth:
; Gets the width of a character using the external
; function whose address is in _GetCharWidth
; Arguments:
;   arg0 = character
; Returns:
;   HL = width of character
; Destroys:
;   All

	ld	hl,arg0
	add	hl,sp
	ld	hl,(hl)
	push	hl
	ld	hl,(_GetCharWidth)
	call	util.CallHL
	pop	de
	ret


;-------------------------------------------------------------
; Internal Library Data
;-------------------------------------------------------------


_LibraryVersion:
	db	2

; Pointers for external library function implementations
_SetTextPosition:
	dl	0
_GetTextX:
	dl	0
_GetTextY:
	dl	0
_DrawChar:
	dl	0
_GetCharWidth:
	dl	0
_DrawThetaChar:
	dl	0

; Action key defaults
_ClearKey:
	db	$0f			; sk_Clear
_BackspaceKey:
	db	$38			; sk_Del
_CursorLeftKey:
	db	$02			; sk_Left
_CursorRightKey:
	db	$03			; sk_Right

_LastVisibleCharPtr:
	dl	0

_CursorBGColor:
	db	0
_CurrCursorX:
	dl	0

; Initially set to 1 so the counter will reset immediately when it is first called
_CursorDisplayCounter:
	dl	1

; This time is equilvalent to a cursor blink rate value of 16.
_CursorDisplayTime:
	dl	4080
_HalfCursorDisplayTime:
	dl	2040

_TimerCounter:
	dl	32768

_UppercaseLettersKeymap:
	db	'A'
	db	0,0,0,0,0,0,0,0,0
	db	0,0,"WRMH",0,0
	db	0,0,"VQLG",0,0
	db	0,"ZUPKFC",0
	db	$20,"YTOJEB",0
	db	0,"XSNIDA",0
	db	0,0,0,0,0,0,0,0

_LowercaseLettersKeymap:
	db	'a'
	db	0,0,0,0,0,0,0,0,0
	db	0,0,"wrmh",0,0
	db	0,0,"vqlg",0,0
	db	0,"zupkfc",0
	db	$20,"ytojeb",0
	db	0,"xsnida",0
	db	0,0,0,0,0,0,0,0

; textio_SetThetaCodepoint modifies this keymap
_PrgmNameLettersKeymap:
	db	0
	db	0,0,0,0,0,0,0,0,0
	db	0,0,"WRMH",0,0
	db	0,0,"VQLG",0,0
	db	0,"ZUPKFC",0
	db	0,"YTOJEB",0
	db	0,"XSNIDA",0
	db	0,0,0,0,0,0,0,0

_NumericalKeymap:
	db	$31
	db	0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,$33,$36,$39,0,0,0,0
	db	0,$32,$35,$38,0,0,0,0
	db	$30,$31,$34,$37,0,0,0,0
	db	0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0

; Data for text output functions
_TabWidth:
	db	4
_PrintFormat:
	db	1
_NewlineCode:
	db	$0a

; Data for textio_GetLinePtr
_LineWidth:
	dl	0
_CurrLineNum:
	db	0
_LineNum:
	db	0

; Data for TextIOC text window
_TextWindowX:
	dl	0
_TextWindowY:
	db	0
_TextWindowWidth:
	dl	320
_TextWindowHeight:
	db	240

_FontHeight:
	db	0
_LineSpacingAbove:
	db	1
_LineSpacingBelow:
	db	1