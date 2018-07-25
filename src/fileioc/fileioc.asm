;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'FILEIOC', 4

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export ti_CloseAll
	export ti_Open
	export ti_OpenVar
	export ti_Close
	export ti_Write
	export ti_Read
	export ti_GetC
	export ti_PutC
	export ti_Delete
	export ti_DeleteVar
	export ti_Seek
	export ti_Resize
	export ti_IsArchived
	export ti_SetArchiveStatus
	export ti_Tell
	export ti_Rewind
	export ti_GetSize
;-------------------------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------------------------
	export ti_GetTokenString
	export ti_GetDataPtr
	export ti_Detect
	export ti_DetectVar
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
	export ti_SetVar
	export ti_StoVar
	export ti_RclVar
	export ti_AllocString
	export ti_AllocList
	export ti_AllocMatrix
	export ti_AllocCplxList
	export ti_AllocEqu
;-------------------------------------------------------------------------------
; v4 functions
;-------------------------------------------------------------------------------
	export ti_DetectAny
	export ti_GetVATPtr
	export ti_GetName
	export ti_Rename
	export ti_RenameVar

;-------------------------------------------------------------------------------
resizeBytes := $E30C0C
currSlot := $E30C11
charIn := $E30C12
;-------------------------------------------------------------------------------
VATPtr0 := $D0244E
VATPtr1 := $D0257B
VATPtr2 := $D0257E
VATPtr3 := $D02581
VATPtr4 := $D02584

DataPtr0 := $D0067E
DataPtr1 := $D00681
DataPtr2 := $D01FED
DataPtr3 := $D01FF3
DataPtr4 := $D01FF9
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
ti_AllocString:
ti_AllocEqu:
; Allocates space for a string/equation
; Arguments:
;  arg0 : len
;  arg1 : pointer to malloc routine
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	iy,(iy+6)
	push	hl
	inc	hl
	inc	hl
	call	__indcall
	pop	de
	ld	(hl),e
	inc	hl
	ld	(hl),d
	dec	hl
	ret

;-------------------------------------------------------------------------------
ti_AllocCplxList:
; Allocates space for a complex list
; Arguments:
;  arg0 : dim
;  arg1 : pointer to malloc routine
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	iy,(iy+6)
	push	hl
	add	hl,hl
	jr	_AllocVar

;-------------------------------------------------------------------------------
ti_AllocList:
; Allocates space for a real list
; Arguments:
;  arg0 : dim
;  arg1 : pointer to malloc routine
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	iy,(iy+6)
	push	hl
	jr	_AllocVar

;-------------------------------------------------------------------------------
ti_AllocMatrix:
	ld	iy,0
	add	iy,sp
	ld	h,(iy+3)
	ld	l,(iy+6)
	ld	iy,(iy+9)
	push	hl
	mlt	hl
_AllocVar:
	call	_HLTimes9
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
ti_CloseAll:
; Closes all open file handles
; Arguments:
;  None
; Returns:
;  None
	ld	a,$40
	ld	(VATPtr0+2),a
	ld	(VATPtr1+2),a
	ld	(VATPtr2+2),a
	ld	(VATPtr3+2),a
	ld	(VATPtr4+2),a
	ret

;-------------------------------------------------------------------------------
ti_Resize:
; Resizes a variable
; Arguments:
;  arg0 : New size
;  arg1 : Slot number
; Returns:
;  Resized size if no failure
	pop	de
	pop	hl				; hl = new size
	pop	bc				; c = slot
	push	bc
	push	hl
	push	de
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
	push	hl
	call	_IsInRAM
	pop	hl
	jp	c,_ReturnNull
	ld	de,$FFFF-30
	or	a,a
	sbc	hl,de
	add	hl,de
	push	af
	push	hl
	ld	bc,0
	call	_SetSlotOffset
	pop	hl
	pop	af
	jp	nc,_ReturnNull	; return if too big
	push	hl
	call	_GetSlotSize
	pop	hl
	or	a,a
	sbc	hl,bc
	ld	(resizeBytes),hl
	jr	z,NoResize
	jr	c,DecreaseSize
IncreaseSize:
	call	_EnoughMem
	jp	c,_ReturnNull
	ex	de,hl
	call	_AddMemoryToVar
	jr	NoResize
DecreaseSize:
	push	hl
	pop	bc
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	ld	(resizeBytes),hl
	call	_DeleteMemoryFromVar
NoResize:
	ld	hl,(resizeBytes)
	ret

;-------------------------------------------------------------------------------
ti_IsArchived:
; Checks if a variable is archived
; Arguments:
;  arg0 : Slot number
; Returns:
;  0 if not archived
	pop	de
	pop	bc
	push	bc
	push	de
	call	_IsSlotOpen
	jp	z,_ReturnNull
_IsInRAM:
	call	_GetSlotVATPtr
	ld	hl,(hl)
	dec	hl
	dec	hl
	dec	hl
	dec	hl
	dec	hl
	ld	a,(hl)
	or	a,a
	sbc	hl,hl
	cp	a,$d0
	ret	nc
	inc	hl
	ret

;-------------------------------------------------------------------------------
ti_OpenVar:
; Opens a variable
; Arguments:
;  arg0 : Pointer to variable name
;  arg1 : Opening flags
;  arg2 : variable Type
; Returns:
;  Slot number if no error
	ld	iy,0
	add	iy,sp
	ld	a,(iy+9)
;	jr	_Open			; emulated by dummifying next instruction:
	db	$FE			; ld a,appVarObj -> cp a,$3E \ dec d
assert appVarObj = $15
;-------------------------------------------------------------------------------
ti_Open:
; Opens an AppVar
; Arguments:
;  arg0 : Pointer to variable name
;  arg1 : Opening flags
; Returns:
;  Slot number if no error
	ld	a,appVarObj
_Open:
	ld	(varTypeOpen),a
	ld	(op1),a
	ld	iy,flags
	push	ix
	ld	ix,0
	add	ix,sp
	xor	a,a
	ld	hl,(VATPtr0)
	inc	a
	add	hl,hl
	jr	nc,.slot
	ld	hl,(VATPtr1)
	inc	a
	add	hl,hl
	jr	nc,.slot
	ld	hl,(VATPtr2)
	inc	a
	add	hl,hl
	jr	nc,.slot
	ld	hl,(VATPtr3)
	inc	a
	add	hl,hl
	jr	nc,.slot
	ld	hl,(VATPtr4)
	inc	a
	add	hl,hl
	jp	c,_ReturnNull_IX
.slot:
	ld	(currSlot),a
	ld	hl,(ix+6)
	ld	de,op1+1
	ld	bc,8
	ldir
	xor	a,a
	ld	(de),a
	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'w'
	ld	iy,flags
	jr	nz,.nooverwite
	call	_PushOP1
	call	_ChkFindSym
	call	nc,_DelVarArc
	call	_PopOP1
.nooverwite:
	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'r'
	jr	z,.mode
	cp	a,'a'
	jr	z,.mode
	cp	a,'w'
	jp	nz,_ReturnNull_IX
.mode:
	inc	hl
	ld	a,(hl)
	cp	a,'+'
	jr	nz,.noappend
.archivevar:
	call	_PushOP1
	call	_ChkFindSym
	call	_ChkInRam
	jr	z,.inram
	or	a,a
	sbc	hl,hl
	ex	de,hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex	de,hl
	call	_EnoughMem
	push	af
	call	_PopOP1
	pop	af
	jp	c,_ReturnNull_IX
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	.archivevar
.inram:
	call	_PopOP1
.noappend:
	call	_ChkFindSym
	jr	c,.notfound
	call	_ChkInRam
	jr	z,.saveptrs
	push	hl
	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'r'
	pop	hl
	jp	nz,_ReturnNull_IX
	push	hl
	push	de
	pop	iy
	ld	a,10
	add	a,(iy+9)
	sbc	hl,hl
	ld	l,a
	add	hl,de
	ex	de,hl
	pop	hl
	jr	.saveptrs
.notfound:
	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'r'
	jp	z,_ReturnNull_IX
	or	a,a
	sbc	hl,hl
varTypeOpen := $+1
	ld	a,0
	ld	iy,flags
	call	_CreateVar
.saveptrs:
	push	hl
	call	_GetSlotVATPtr
	pop	bc
	ld	(hl),bc
	call	_GetSlotDataPtr
	ld	(hl),de
	ld	bc,0
	ld	hl,(ix+9)
	ld	a,'a'
	cp	a,(hl)
	call	z,_GetSlotSize
	call	_SetSlotOffset
	pop	ix
	or	a,a
	sbc	hl,hl
	ld	a,(currSlot)
	ld	l,a
	ret

;-------------------------------------------------------------------------------
ti_SetArchiveStatus:
; Sets the archive status of a slot
; Arguments:
;  arg0 : Boolean value
;  arg1 : Slot number
; Returns:
;  None
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	call	_IsSlotOpen
	jp	z,_ReturnNull
	ld	a,c
	push	af
	call	_GetSlotVATPtr
	ld	hl,(hl)
	ld	a,(hl)
	ld	(OP1),a
	ld	bc,-6
	add	hl,bc
	ld	b,(hl)
	ld	de,OP1+1
	dec	hl
.storename:
	ld	a,(hl)
	ld	(de),a
	inc	de
	dec	hl
	djnz	.storename
	xor	a,a
	ld	(de),a
	call	_PushOP1
	ld	iy,flags
	call	_ChkFindSym
	call	_ChkInRam
	push	af
	pop	bc
	pop	af
	or	a,a
	jr	z,.set_not_archived
.set_archived:
	push	bc
	pop	af
	call	z,_Arc_Unarc
	jr	.relocate_var
.set_not_archived:
	push	bc
	pop	af
	call	nz,_Arc_Unarc
.relocate_var:
	call	_PopOP1
	call	_ChkFindSym
	jp	c,_ReturnNegativeOne
	push	hl
	call	_GetSlotVATPtr
	pop	bc
	ld	(hl),bc
	call	_GetSlotDataPtr
	ld	(hl),de
	ret

;-------------------------------------------------------------------------------
ti_Write:
; Performs an fwrite to an AppVar
; Arguments:
;  arg0 : Pointer to data to write
;  arg1 : Size of entries (bytes)
;  arg2 : Number of entries
;  arg3 : Slot number
; Returns:
;  Number of chunks written if success
	ld	iy,0
	add	iy,sp
	ld	c,(iy+12)
	call	_IsSlotOpen
	jr	z,_ReturnNull_Close
	call	_IsInRAM
	jr	z,_ReturnNull_Close
	ld	bc,(iy+6)
	ld	hl,(iy+9)
	call	__smulu
	add	hl,de
	xor	a,a
	sbc	hl,de
	ret	z
	ld	(CopySize_SMC),hl
	push	hl
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	push	hl
	call	_GetSlotSize			; bc = size of file
	pop	hl				; hl = needed size
	or	a,a
	inc	bc
	sbc	hl,bc
	jr	c,NoCoreNeeded
	inc	hl
	ld	(resizeBytes),hl
	call	_AddMemoryToVar
	or	a,a
	jr	z,_ReturnNull_Close
NoCoreNeeded:
	call	_GetSlotCurrentDataPtr
	ex	de,hl
	ld	hl,(iy+3)
CopySize_SMC := $+1
	ld	bc,0
	push	bc
	ldir
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	ex	de,hl
	call	_GetSlotOffsetPtr
	ld	(hl),de
	ld	hl,(iy+9)
	ret

_ReturnNull_Close_HL:
	pop	hl
_ReturnNull_Close:
	xor	a,a
	sbc	hl,hl
	ret

_GetSlotCurrentDataPtr:
	call	_GetSlotDataPtr
	ld	hl,(hl)
	push	hl
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	inc	hl
	inc	hl
	ret

;-------------------------------------------------------------------------------
ti_Read:
; Performs an fread to an AppVar
; Arguments:
;  arg0 : Pointer to data to read into
;  arg1 : Size of entries (bytes)
;  arg2 : Number of entries
;  arg3 : Slot number
; Returns:
;  Number of chunks read if success
	ld	iy,0
	add	iy,sp
	ld	c,(iy+12)
	call	_IsSlotOpen
	jr	z,_ReturnNull_Close
	ld	bc,(iy+6)
	ld	hl,(iy+9)
	push	hl
	call	__smulu
	add	hl,de
	xor	a,a
	sbc	hl,de
	jr	z,_ReturnNull_Close_HL
	push	hl
	call	_GetSlotCurrentDataPtr
	ld	de,(iy+3)
	pop	bc
	push	bc
	ldir
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	ex	de,hl
	call	_GetSlotOffsetPtr
	ld	(hl),de
	pop	hl
	ret

;-------------------------------------------------------------------------------
ti_GetC:
; Performs an fgetc to an AppVar
; Arguments:
;  arg0 : Slot number
; Returns:
;  Character read if success
	pop	de
	pop	bc
	push	bc
	push	de
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
_GetChar_ASM:
	call	_GetSlotSize
	push	bc
	call	_GetSlotOffset
	pop	hl
	scf
	sbc	hl,bc				; size-offset
	jp	c,_ReturnNegativeOne
	push	bc
	call	_GetSlotDataPtr
	ld	hl,(hl)
	add	hl,bc
	inc	hl
	inc	hl				; bypass size bytes
	pop	bc
	inc	bc
	ld	a,(hl)
	call	_SetSlotOffset
	or	a,a
	sbc	hl,hl
	ld	l,a
	ret

;-------------------------------------------------------------------------------
ti_Seek:
; Performs an fseek on an AppVar
; Arguments:
;  arg0 : Posistion to seek to
;  arg1 : Origin position
;  arg2 : Slot number
; Returns:
;  -1 if failure
	ld	iy,0
	add	iy,sp
	ld	de,(iy+3)
	ld	c,(iy+9)
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
	ld	a,(iy+6)
	or	a,a
	jr	z,.seek_set
	dec	a
	jr	z,.seek_curr
	dec	a
	jp	nz,_ReturnNegativeOne
.seek_end:
	push	de
	call	_GetSlotSize
.seek_set_asm:
	pop	hl
	add	hl,bc
	ex	de,hl
.seek_set:
	call	_GetSlotSize
	push	bc
	pop	hl
	or	a,a
	sbc	hl,de
	push	de
	pop	bc
	jp	c,_ReturnNegativeOne
	jp	_SetSlotOffset
.seek_curr:
	push	de
	call	_GetSlotOffset
	jr	.seek_set_asm

;-------------------------------------------------------------------------------
ti_PutC:
; Performs an fputc on an AppVar
; Arguments:
;  arg0 : Character to place
;  arg1 : Slot number
; Returns:
;  Character written if no failure
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	ld	a,l
	ld	(charIn),a
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
	push	hl
	call	_IsInRAM
	pop	hl
	jp	c,_ReturnNegativeOne
_PutChar:
	call	_GetSlotSize
	push	bc
	call	_GetSlotOffset
	pop	hl
	or	a,a
	sbc	hl,bc
	jp	c,_ReturnNegativeOne
	jr	nz,.no_increment
.increment:
	push	bc
	inc	hl
	ld	(resizeBytes),hl
	call	_EnoughMem
	pop	bc
	jp	c,_ReturnNegativeOne
	push	bc
	ex	de,hl
	call	_AddMemoryToVar
	pop	bc
	or	a,a
	jp	z,_ReturnNegativeOne
.no_increment:
	call	_GetSlotDataPtr
	ld	hl,(hl)
	add	hl,bc
	inc	hl
	inc	hl
	ld	a,(charIn)
	ld	(hl),a
	inc	bc
	push	af
	call	_SetSlotOffset
	pop	af
	or	a,a
	sbc	hl,hl
	ld	l,a
	ret

;-------------------------------------------------------------------------------
ti_DeleteVar:
; Deletes an arbitrary variable
; Arguments:
;  arg0 : Pointer to variable name
;  arg1 : Variable type
; Returns:
;  0 if failure
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	ld	a,c
;	jr	_Delete			; emulated by dummifying next instruction:
	db	$FE			; ld a,appVarObj -> cp a,$3E \ dec d
assert appVarObj = $15

;-------------------------------------------------------------------------------
ti_Delete:
; Deletes an AppVar
; Arguments:
;  arg0 : Pointer to AppVar name
; Returns:
;  0 if failure
	ld	a,appVarObj
_Delete:
	pop	de
	pop	hl
	push	hl
	push	de
	dec	hl
	push	af
	call	_Mov9ToOP1
	pop	af
	ld	(OP1),a
	call	_ChkFindSym
	jp	c,_ReturnNull
	ld	iy,flags
	call	_DelVarArc
	scf
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
ti_Rewind:
; Performs an frewind on a variable
; Arguments:
;  arg0 : Slot number
; Returns:
;  -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
	ld	bc,0
	call	_SetSlotOffset
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
ti_Tell:
; Performs an ftell on a variable
; Arguments:
;  arg0 : Slot number
; Returns:
;  -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
	call	_GetSlotOffset
	push	bc
	pop	hl
	ret

;-------------------------------------------------------------------------------
ti_GetSize:
; Gets the size of an AppVar
; Arguments:
;  arg0 : Slot number
; Returns:
;  -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	_IsSlotOpen
	jp	z,_ReturnNegativeOne
	call	_GetSlotSize
	push	bc
	pop	hl
	ret

;-------------------------------------------------------------------------------
ti_Close:
; Closes an open slot variable
; Arguments:
;  arg0 : Slot number
; Returns:
;  None
	pop	hl
	pop	bc
	push	bc
	push	hl
	ld	a,c
	ld	(currSlot),a
	call	_GetSlotVATPtr
	inc	hl
	inc	hl
	ld	(hl),$40
	ret

;-------------------------------------------------------------------------------
ti_DetectAny:
; Finds a variable that starts with some data
; Arguments:
;  arg0 : address of pointer to being search
;  arg1 : pointer to null terminated string of data to search for
;  arg2 : pointer storage of type of variable found
	ld	a,$ff
	jr	_DetectJump

;-------------------------------------------------------------------------------
ti_DetectVar:
; Finds a variable that starts with some data
; Arguments:
;  arg0 : address of pointer to being search
;  arg1 : pointer to null terminated string of data to search for
;  arg2 : type of variable to search for
	ld	hl,9
	add	hl,sp
	ld	a,(hl)
;	jr	_Detect			; emulated by dummifying next instruction:
	db	$FE			; ld a,appVarObj -> cp a,$3E \ dec d
assert appVarObj = $15

;-------------------------------------------------------------------------------
ti_Detect:
; Finds an AppVar that starts with some data
;  arg0 : address of pointer to being search
;  arg1 : pointer to null terminated string of data to search for
	ld	a,appVarObj
_Detect:
	ld	(_DetectType),a
	xor	a,a
_DetectJump:
	ld	(_DetectFlag),a
	push	ix
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+9)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	nz,.detectall		; if null, then detect everything
	ld	hl,.fdetectall
	ld	(ix+9),hl
.detectall:
	ld	hl,(ix+6)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	z,.fstart
	ld	hl,(hl)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	nz,.fdetect
.fstart:
	ld	hl,(progPtr)
.fdetect:
	ld	de,(pTemp)
	or	a,a
	sbc	hl,de
	jr	c,.finish
	jr	z,.finish
	add	hl,de
	jr	.fcontinue

.finish:
	xor	a,a
	sbc	hl,hl
	pop	ix
	ret

.fcontinue:
	push	hl
	ld	a,(_DetectFlag)
	or	a,a
	ld	a,(hl)
	jr	z,.fdetectnormal
	ld	(ix+12),a
	jr	.fgoodtype
.fdetectnormal:
_DetectType := $+1
	cp	a,appVarObj
	jr	nz,.fskip
.fgoodtype:
	dec	hl
	dec	hl
	dec	hl
	ld	e,(hl)
	dec	hl
	ld	d,(hl)
	dec	hl
	ld	a,(hl)
	call	_SetDEUToA
	ex	de,hl
	cp	a,$D0
	jr	nc,.finram
	ld	de,9
	add	hl,de			; skip archive VAT stuff
	ld	e,(hl)
	add	hl,de
	inc	hl
.finram:
	inc	hl
	inc	hl			; hl -> data
	ld	bc,(ix+9)
.fcmp:
	ld	a,(bc)
	or	a,a
	jr	z,.ffound
	cp	a,(hl)
	inc	bc
	inc	de
	inc	hl
	jr	z,.fcmp			; check the string at the memory
.fskip:
	pop	hl
	call	.fbypassname
	jr	.fdetect

.ffound:
	pop	hl
	call	.fbypassname
	ex	de,hl
	ld	hl,(ix+6)
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	z,.isnull
	ld	(hl),de
.isnull:
	ld	hl,OP6
	pop	ix
	ret

.fbypassname:				; bypass the name in the VAT (also used for setting the string name)
	ld	de,OP6
	ld	bc,-6
	add	hl,bc
	ld	b,(hl)
	dec	hl
.loop:
	ld	a,(hl)
	ld	(de),a
	dec	hl
	inc	de
	djnz	.loop
	xor	a,a
	ld	(de),a
	ret

.fdetectall:
	db	0
_DetectFlag:
	db	0

;-------------------------------------------------------------------------------
ti_GetTokenString:
; Returns pointer to next token string
; Arguments:
;  arg0 : Slot number
; Returns:
;  Pointer to string to display
	ld	iy,0
	add	iy,sp
	ld	a,1
	ld	(_TokenLength),a
	ld	hl,(iy+3)
	ld	hl,(hl)
	push	hl
	ld	a,(hl)
	call	_Isa2ByteTok
	ex	de,hl
	jr	nz,.not2byte
	inc	de
	ld	hl,_TokenLength
	inc	(hl)
.not2byte:
	inc	de
	ld	hl,(iy+3)
	ld	(hl),de
	pop	hl
	push	iy
	ld	iy,flags
	call	_Get_Tok_Strng
	pop	iy
	ld	hl,(iy+9)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	z,.skip
	ld	(hl),bc
.skip:
	ld	hl,(iy+6)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	z,.skipstore
_TokenLength := $+1
	ld	(hl),1
.skipstore:
	ld	hl,OP3
	ret

;-------------------------------------------------------------------------------
ti_GetDataPtr:
; Returns a pointer to the current location in the given variable
; Arguments:
;  arg0 : Slot number
; Returns:
;  Pointer to current offset data
	pop	de
	pop	bc
	push	bc
	push	de
	call	_IsSlotOpen
	jp	z,_ReturnNull
	call	_GetSlotSize
	inc	hl
	push	hl
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	ret

;-------------------------------------------------------------------------------
ti_GetVATPtr:
; Returns a pointer to the VAT location in the given variable
; Arguments:
;  arg0 : Slot number
; Returns:
;  VAT location of variable
	pop	de
	pop	bc
	push	bc
	push	de
	call	_IsSlotOpen
	jp	z,_ReturnNull
	call	_GetSlotVATPtr
	ld	hl,(hl)
	ret

;-------------------------------------------------------------------------------
ti_GetName:
; Gets the variable name of an open slot
; Arguments:
;  arg0 : Name buffer
;  arg1 : Slot number
; Returns:
;  None
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	push	hl
	call	_IsSlotOpen
	pop	de
	ret	z
	call	_GetSlotVATPtr
	ld	hl,(hl)
	ld	bc,-6
	add	hl,bc
	ld	b,(hl)			; length of name
	dec	hl
.copy:
	ld	a,(hl)
	ld	(de),a
	inc	de
	dec	hl
	djnz	.copy
	xor	a,a
	ld	(de),a			; terminate the string
	ret

;-------------------------------------------------------------------------------
ti_RenameVar:
; Renames a variable with a new name
; Arguments:
;  arg0 : Old name pointer
;  arg1 : New name pointer
;  arg2 : Variable type
; Returns:
;  0 if success
;  1 if new file already exists
;  2 if old file does not exist
;  3 if other error
	ld	iy,0
	add	iy,sp
	ld	a,(iy+9)
	ld	iy,flags		; probably not needed
	jr	ti_Rename.start

;-------------------------------------------------------------------------------
ti_Rename:
; Renames an appvar with a new name
; Arguments:
;  arg0 : Old name pointer
;  arg1 : New name pointer
; Returns:
;  0 if success
;  1 if new file already exists
;  2 if old file does not exist
;  3 if other error
	ld	a,appVarObj		; file type
.start:
	pop	bc
	pop	hl
	pop	de
	push	de			; de -> new name
	push	hl			; hl -> old name
	push	bc

	push	af
	call	ti_CloseAll
	pop	af

	push	de			; new
	push	de			; new
	ld	de,OP1
	ld	(de),a
	inc	de
	call	_Mov8b
	call	_PushOP1		; save old name

	ld	hl,_Arc_Unarc
	ld	(.smc_archive),hl

	pop	hl			; new name
	ld	de,OP1+1
	call	_Mov8b
	call	_ChkFindSym
	push	af
	call	_PopOP1
	pop	af
	jr	nc,.return_1		; check if name already exists
.locate_program:
	call	_ChkFindSym		; find old name
	jr	c,.return_2
	call	_ChkInRam
	jr	nz,.in_archive
	ld	hl,$f8			; $f8 = ret
	ld	(.smc_archive),hl
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	.locate_program
.in_archive:
	ex	de,hl
	ld	de,9
	add	hl,de			; skip vat stuff
	ld	e,(hl)
	add	hl,de
	inc	hl			; size of name
	call	_LoadDEInd_s
	pop	bc			; bc -> new name
	push	hl
	push	de
	push	bc
	call	_PushOP1		; old name

	pop	hl
	ld	de,OP1+1
	call	_Mov8b
	call	_PushOP1		; new name
	pop	hl
	push	hl
	ld	a,(OP1)
	call	_CreateVar
	inc	de
	inc	de
	pop	bc
	pop	hl
	call	_ChkBCIs0
	jr	z,.is_zero
	ldir
.is_zero:
	call	_PopOP1
	call	_Arc_Unarc
.smc_archive := $-3
	call	_PopOP1
	call	_ChkFindSym
	call	_DelVarArc
	xor	a,a
	ret
.return_1:
	pop	de			; new name
	ld	a,1
	ret
.return_2:
	pop	de			; new name
	ld	a,2
	ret

;-------------------------------------------------------------------------------
ti_SetVar:
; Sets a variable
; Gets a pointer to a variable data structure
; Arguments:
;  arg0 : Pointer to name of variable
;  arg1 : Pointer to data to set
;  arg2 : Type of variable to set
; Returns:
;  Any error codes returned when storing
	push	ix
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+9)			; pointer to var string
	ld	a,(ix+6)
	call	_SetVarStr
	call	_ChkFindSym
	call	nc,_DelVarArc
	ld	a,(ix+6)
	ld	hl,(ix+12)
	and	a,03Fh
	call	_DataSize
	pop	ix
	push	hl
	ex	de,hl
	dec	hl
	dec	hl
	call	_CreateVar
	inc	bc
	inc	bc
	pop	hl
	ldir
	xor	a,a
	ret

;-------------------------------------------------------------------------------
ti_StoVar:
; Stores a variable
; Gets a pointer to a variable data structure
; Arguments:
;  arg0 : Type of variable to store to
;  arg1 : Pointer to data to store to
;  arg2 : Type of variable to get from
;  arg3 : Pointer to data to get from
; Returns:
;  Any error codes returned when storing
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+12)			; pointer to var string
	call	_SetVarStr
	ld	a,(iy+9)
	or	a,a				; if a real we have to look up the variable
	jr	z,_iscr
	cp	a,0Ch				; if a cplx we have to look up the variable
	jr	nz,_notcr
_iscr:
	call	_FindSym
	jp	c,_notcr			; just fill it with zero
	and	a,03Fh
	ex	de,hl
	call	_Mov9OP1OP2
_notcr:
	call	_PushOP1
	ld	hl,(iy+6)			; pointer to var string
	ld	a,(iy+3)
	call	_SetVarStr
	ld	iy,flags
	ld	hl,_ReturnNegativeOneC
	call	_PushErrorHandler
	call	_StoOther
	call	_PopErrorHandler
	xor	a,a
	ret

;-------------------------------------------------------------------------------
ti_RclVar:
; Gets a pointer to a variable data struct
; Arguments:
;  arg0 : Pointer to variable name string
;  arg1 : Pointer to data structure pointer
; Returns:
;  Type of variable returned
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6)			; pointer to var string
	ld	a,(iy+3)			; var type
	call	_SetVarStr
	call	_FindSym
	jp	c,_ReturnNegativeOneC
	call	_ChkInRAM
	jp	nz,_ReturnNegativeOneC
	ld	iy,0
	add	iy,sp
	and	a,03Fh
	cp	a,(iy+3)			; var type
	jp	nz,_ReturnNegativeOneC
	ld	hl,(iy+9)
	ld	(hl),de
	ret

;-------------------------------------------------------------------------------
; Internal library routines
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_SetVarStr:
; hl - String pointer
;  a - Type
	ld	de,OP1+1
	call	_Mov9b
	and	a,$3f
	ld	(OP1),a
	ret

;-------------------------------------------------------------------------------
_AddMemoryToVar:
	call	_GetSlotDataPtr
	push	hl
	ld	hl,(hl)
	push	hl
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	inc	hl				; bypass size bytes
	inc	hl
	ex	de,hl
	ld	hl,(resizeBytes)
	push	hl
	push	de
	call	_EnoughMem
	pop	de
	pop	hl
	jr	c,_ReturnNullC
	call	_InsertMem
	pop	hl
	ld	hl,(hl)
	push	hl
	ld	de,0
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex	de,hl
	ld	bc,(resizeBytes)
	add	hl,bc				; increase by 5
	jr	SaveSize
_DeleteMemoryFromVar:
	call	_GetSlotDataPtr
	push	hl
	ld	hl,(hl)
	push	hl
	call	_GetSlotOffset
	pop	hl
	add	hl,bc
	inc	hl
	inc	hl
	ld	de,(resizeBytes)
	call	_DelMem
	pop	hl
	ld	hl,(hl)
	push	hl
	ld	de,0
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex	de,hl
	ld	bc,(resizeBytes)
	or	a,a
	sbc	hl,bc				; decrease amount
SaveSize:
	ex	de,hl
	pop	hl				; pointer to size bytes location
	ld	(hl),e
	inc	hl
	ld	(hl),d				; write new size
_ReturnNegativeOneC:
	ld	a,255
	ret
_ReturnNullC:
	xor	a,a
	ret

_ReturnNull_IX:
	pop	ix
_ReturnNull:
	xor	a,a
	sbc	hl,hl
	ret
_ReturnNegativeOne:
	scf
	sbc	hl,hl
	ret

_IsSlotOpen:
	ld	a,c
	ld	(currSlot),a
	push	hl
	call	_GetSlotVATPtr
	inc	hl
	inc	hl
	bit	7,(hl)
	pop	hl
	ret
_GetSlotVATPtr:
	ld	a,(currSlot)
	ld	hl,VATPtr0 		; VATPtr0 = $D0244E
	dec	a
	ret	z
	inc	h
	ld	l,$7b			; VATPtr1 = $D0257B
	dec	a
	ret	z
	ld	l,$7e			; VATPtr2 = $D0257E
	dec	a
	ret	z
	ld	l,$81			; VATPtr3 = $D02581
	dec	a
	ret	z
	ld	l,$84			; VATPtr4 = $D02584
	ret
_GetSlotDataPtr:
	ld	a,(currSlot)
	ld	hl,DataPtr0		; DataPtr0 = $D0067E
	dec	a
	ret	z
	ld	l,$81			; DataPtr1 = $D00681
	dec	a
	ret	z
	ld	hl,DataPtr2		; DataPtr2 = $D01FED
	dec	a
	ret	z
	ld	l,$f3			; DataPtr3 = $D01FF3
	dec	a
	ret	z
	ld	l,$f9			; DataPtr4 = $D01FF9
	ret
_GetSlotOffsetPtr:
	push	bc
	ld	hl,(currSlot)
	dec	l
	ld	h,3
	mlt	hl
	ld	bc,VarOffset0
	add	hl,bc
	pop	bc
	ret
_GetSlotSize:
	call	_GetSlotDataPtr
	ld	hl,(hl)
	ld	bc,0
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ret
_GetSlotOffset:
	call	_GetSlotOffsetPtr
	ld	bc,(hl)
	ret
_SetSlotOffset:
	call	_GetSlotOffsetPtr
	ld	(hl),bc
	ret

;-------------------------------------------------------------------------------
; Internal library data
;-------------------------------------------------------------------------------

VarOffset0:
	dl	0, 0, 0, 0, 0
