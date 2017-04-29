#include "..\include\relocation.inc"
#include "..\include\ti84pce.inc"

 .libraryAppVar     "FILEIOC"       ; Name of library on the calc
 .libraryName       "fileioc"       ; Name of library
 .libraryVersion    3               ; Version information (1-255)
 
;-------------------------------------------------------------------------------
; v1 functions -- Cannot move/delete/insert (Can fix/optimize though)
;-------------------------------------------------------------------------------
 .function "ti_CloseAll",_CloseAll
 .function "ti_Open",_Open
 .function "ti_OpenVar",_OpenVar
 .function "ti_Close",_Close
 .function "ti_Write",_Write
 .function "ti_Read",_Read
 .function "ti_GetC",_GetChar
 .function "ti_PutC",_PutChar
 .function "ti_Delete",_Delete
 .function "ti_DeleteVar",_DeleteVar
 .function "ti_Seek",_Seek
 .function "ti_Resize",_Resize
 .function "ti_IsArchived",_IsArchived
 .function "ti_SetArchiveStatus",_SetArchiveStatus
 .function "ti_Tell",_Tell
 .function "ti_Rewind",_Rewind
 .function "ti_GetSize",_GetSize
;-------------------------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------------------------
 .function "ti_GetTokenString",_GetTokenString
 .function "ti_GetDataPtr",_GetDataPtr
 .function "ti_Detect",_Detect
 .function "ti_DetectVar",_DetectVar
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
 .function "ti_SetVar",_SetVar
 .function "ti_StoVar",_StoVar
 .function "ti_RclVar",_RclVar
 .function "ti_AllocString",_AllocString
 .function "ti_AllocList",_AllocList
 .function "ti_AllocMatrix",_AllocMatrix
 .function "ti_AllocCplxList",_AllocCplxList
 .function "ti_AllocEqu",_AllocEqu

 .beginDependencies
 .endDependencies

resizeBytes	equ 0E30C0Ch
currSlot	equ 0E30C11h
charIn		equ 0E30C12h

;-------------------------------------------------------------------------------
#define VATPtr0 $D0244E
#define VATPtr1 $D0257B
#define VATPtr2 $D0257E
#define VATPtr3 $D02581
#define VATPtr4 $D02584

#define DataPtr0 $D0067E
#define DataPtr1 $D00681
#define DataPtr2 $D01FED
#define DataPtr3 $D01FF3
#define DataPtr4 $D01FF9
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
_AllocString:
_AllocEqu:
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
_AllocCplxList:
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
	jr	_AllocVar_ASM

;-------------------------------------------------------------------------------
; Allocates space for a real list
; Arguments:
;  arg0 : dim
;  arg1 : pointer to malloc routine
_AllocList:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+3)
	ld	iy,(iy+6)
	push	hl
	jr	_AllocVar_ASM

;-------------------------------------------------------------------------------
_AllocMatrix:
	ld	iy,0
	add	iy,sp
	ld	h,(iy+3)
	ld	l,(iy+6)
	ld	iy,(iy+9)
	push	hl
	mlt	hl
_AllocVar_ASM:
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
_CloseAll:
; Initializes the File IO library
; Arguments:
;  None
; Returns:
;  None
	or	a,a
	sbc	hl,hl
	ld	(VATPtr0),hl
	ld	(VATPtr1),hl
	ld	(VATPtr2),hl
	ld	(VATPtr3),hl
	ld	(VATPtr4),hl
	ret

;-------------------------------------------------------------------------------
_Resize:
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
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
	push	hl
	call	_CheckInRAM_ASM \.r
	pop	hl
	jp	c,_ReturnNULL \.r
	ld	de,$FFFF-30
	or	a,a
	sbc	hl,de
	add	hl,de
	push	af
	push	hl
	ld	bc,0
	call	_SetSlotOffset_ASM \.r
	pop	hl
	pop	af
	jp	nc,_ReturnNULL \.r	; return if too big
	push	hl
	call	_GetSlotSize_ASM \.r
	pop	hl
	or	a,a
	sbc	hl,bc
	ld	(resizeBytes),hl
	jr	z,NoResize
	jr	c,DecreaseSize
IncreaseSize:
	call	_EnoughMem
	jp	c,_ReturnNULL \.r
	ex	de,hl
	call	AddMemoryToVar \.r
	jr	NoResize
DecreaseSize:
	push	hl
	pop	bc
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	ld	(resizeBytes),hl
	call	DeleteMemoryFromVar \.r
NoResize:
	ld	hl,(resizeBytes)
	ret
 
;-------------------------------------------------------------------------------
_IsArchived:
; Checks if a varaible is archived
; Arguments:
;  arg0 : Slot number
; Returns:
;  0 if not archived
	pop	de
	pop	bc
	push	bc
	push	de
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNULL \.r
_CheckInRAM_ASM:
	call	_GetSlotVATPtr_ASM \.r
	ld	hl,(hl)
	dec	hl
	dec	hl
	dec	hl
	dec	hl
	dec	hl
	ld	a,(hl)
	or	a,a
	sbc	hl,hl
	cp	a,$D0
	ret	nc
	inc	hl
	ret
 
;-------------------------------------------------------------------------------
_OpenVar:
; Opens a variable
; Arguments:
;  arg0 : Pointer to varaible name
;  arg1 : Opening flags
;  arg2 : Varaible Type
; Returns:
;  Slot number if no error
	ld	iy,0
	add	iy,sp
	ld	a,(iy+9)
	jr	+_
;-------------------------------------------------------------------------------
_Open:
; Opens an AppVar
; Arguments:
;  arg0 : Pointer to varaible name
;  arg1 : Opening flags
; Returns:
;  Slot number if no error
	ld	a,appVarObj
_:	ld	(varTypeOpen),a \.r
	ld	(op1),a
	ld	iy,flags
	push	ix
	ld	ix,0
	add	ix,sp
	xor	a,a
	ld	hl,(VATPtr0)
	add	hl,de
	inc	a
	sbc	hl,de
	jr	z,+_
	ld	hl,(VATPtr1)
	add	hl,de
	inc	a
	sbc	hl,de
	jr	z,+_
	ld	hl,(VATPtr2)
	add	hl,de
	inc	a
	sbc	hl,de
	jr	z,+_
	ld	hl,(VATPtr3)
	add	hl,de
	inc	a
	sbc	hl,de
	jr	z,+_
	ld	hl,(VATPtr4)
	add	hl,de
	inc	a
	sbc	hl,de
	jr	z,+_
	jp	_ReturnNULL_PopIX \.r
_:	ld	(currSlot),a
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
	jr	nz,nooverwite
	call	_PushOP1
	call	_ChkFindSym
	call	nc,_DelVarArc
	call	_PopOP1
nooverwite:
	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'r'
	jr	z,+_
	cp	a,'a'
	jr	z,+_
	cp	a,'w'
	jp	nz,_ReturnNULL_PopIX \.r
_:	inc	hl
	ld	a,(hl)
	cp	a,'+'
	jr	nz,++_
archivevar:
	call	_PushOP1
	call	_ChkFindSym
	call	_ChkInRam
	jr	z,+_
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
	jp	c,_ReturnNULL_PopIX \.r
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	archivevar
_:	call	_PopOP1
_:	call	_ChkFindSym
	jr	c,+_
	call	_ChkInRam
	jr	z,_SavePtrs_ASM
	push	hl
	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'r'
	pop	hl
	jp	nz,_ReturnNULL_PopIX \.r
        ex	de,hl				; skip vat entry in archive
	push	de
	push	hl
	pop	iy
	ld	a,10
	add	a,(iy+9)
	ld	de,0
	ld	e,a
	add	hl,de
	ex	de,hl
	pop	hl
	jr	_SavePtrs_ASM
_:	ld	hl,(ix+9)
	ld	a,(hl)
	cp	a,'r'
	jp	z,_ReturnNULL_PopIX \.r
	or	a,a
	sbc	hl,hl
varTypeOpen =$+1
	ld	a,0
	ld	iy,flags
	call	_CreateVar
_SavePtrs_ASM:
	push	hl
	call	_GetSlotVATPtr_ASM \.r
	pop	bc
	ld	(hl),bc
	call	_GetSlotDataPtr_ASM \.r
	ld	(hl),de
	ld	bc,0
	ld	hl,(ix+9)
	ld	a,'a'
	cp	a,(hl)
	call	z,_GetSlotSize_ASM \.r
	call	_SetSlotOffset_ASM \.r
	pop	ix
	or	a,a
	sbc	hl,hl
	ld	a,(currSlot)
	ld	l,a
	ret

;-------------------------------------------------------------------------------
_SetArchiveStatus:
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
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNULL \.r
	ld	a,c
	push	af
	call	_GetSlotVATPtr_ASM \.r
	ld	hl,(hl)
	ld	a,(hl)
	ld	(OP1),a
	ld	bc,-6
	add	hl,bc
	ld	b,(hl)
	ld	de,OP1+1
	dec	hl
_:	ld	a,(hl)
	ld	(de),a
	inc	de
	dec	hl
	djnz	-_
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
	jr	z,SetNotArchived
SetArchived:
	push	bc
	pop	af
	call	z,_Arc_Unarc
	jr	RelocateVar
SetNotArchived:
	push	bc
	pop	af
	call	nz,_Arc_Unarc
RelocateVar:
	call	_PopOP1
	call	_ChkFindSym
	jp	c,_ReturnNEG1L \.r
	push	hl
	call	_GetSlotVATPtr_ASM \.r
	pop	bc
	ld	(hl),bc
	call	_GetSlotDataPtr_ASM \.r
	ld	(hl),de
	ret
 
;-------------------------------------------------------------------------------
_Write:
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
	call	_CheckIfSlotOpen \.r
	jr	z,_ReturnNULL_Close
	call	_CheckInRAM_ASM \.r
	jr	z,_ReturnNULL_Close
	ld	bc,(iy+6)
	ld	hl,(iy+9)
	call	__smulu
	ld	(CopySize_SMC),hl \.r
	push	hl
	call	_GetSlotOffset_ASM \.r
	pop	hl
	add	hl,bc
	push	hl
	call	_GetSlotSize_ASM \.r	; bc = size of file
	pop	hl			; hl = needed size
	or	a,a
	inc	bc
	sbc	hl,bc
	jr	c,NoCoreNeeded
	inc	hl
	ld	(resizeBytes),hl
	call	AddMemoryToVar \.r
	or	a,a
	jr	z,_ReturnNULL_Close
NoCoreNeeded:
	call	_GetSlotCurrDataPtr_ASM \.r
	ex	de,hl
	ld	hl,(iy+3)
CopySize_SMC =$+1
	ld	bc,0
	push	bc
	ldir
	call	_GetSlotOffset_ASM \.r
	pop	hl
	add	hl,bc
	ex	de,hl
	call	_GetSlotOffsetPtr_ASM \.r
	ld	(hl),de
	ld	hl,(iy+9)
	ret

_ReturnNULL_Close:
	xor	a,a
	sbc	hl,hl
	ret

_GetSlotCurrDataPtr_ASM:
	call	_GetSlotDataPtr_ASM \.r
	ld	hl,(hl)
	push	hl
	call	_GetSlotOffset_ASM \.r
	pop	hl
	add	hl,bc
	inc	hl
	inc	hl
	ret

;-------------------------------------------------------------------------------
_Read:
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
	call	_CheckIfSlotOpen \.r
	jr	z,_ReturnNULL_Close
	ld	bc,(iy+6)
	ld	hl,(iy+9)
	push	hl
	call	__smulu
	push	hl
	call	_GetSlotCurrDataPtr_ASM \.r
	ld	de,(iy+3)
	pop	bc
	push	bc
	ldir
	call	_GetSlotOffset_ASM \.r
	pop	hl
	add	hl,bc
	ex	de,hl
	call	_GetSlotOffsetPtr_ASM \.r
	ld	(hl),de
	pop	hl
	ret

;-------------------------------------------------------------------------------
_GetChar:
; Performs an fgetc to an AppVar
; Arguments:
;  arg0 : Slot number
; Returns:
;  Character read if success
	pop	de
	pop	bc
	push	bc
	push	de
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
_GetChar_ASM:
	call	_GetSlotSize_ASM \.r
	push	bc
	call	_GetSlotOffset_ASM \.r
	pop	hl
	dec	hl
	or	a,a
	sbc	hl,bc				; size-offset
	jp	c,_ReturnNEG1L \.r
	push	bc
	call	_GetSlotDataPtr_ASM \.r
	ld	hl,(hl)
	add	hl,bc
	inc	hl
	inc	hl				; bypass size bytes
	pop	bc
	inc	bc
	ld	a,(hl)
	call	_SetSlotOffset_ASM \.r
	or	a,a
	sbc	hl,hl
	ld	l,a
	ret

;-------------------------------------------------------------------------------
_Seek:
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
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
	ld	a,(iy+6)
	or	a,a
	jr	z,SeekSet
	dec	a
	jr	z,SeekCur
	dec	a
	jp	nz,_ReturnNEG1L \.r
SeekEnd:
	push	de
	call	_GetSlotSize_ASM \.r
SeekSet_ASM:
	pop	hl
	add	hl,bc
	ex	de,hl
SeekSet:
	call	_GetSlotSize_ASM \.r
	push	bc
	pop	hl
	or	a,a
	sbc	hl,de
	push	de
	pop	bc
	jp	c,_ReturnNEG1L \.r
	jp	_SetSlotOffset_ASM \.r
SeekCur:
	push	de
	call	_GetSlotOffset_ASM \.r
	jr	SeekSet_ASM
	
;-------------------------------------------------------------------------------
_PutChar:
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
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
	push	hl
	call	_CheckInRAM_ASM \.r
	pop	hl
	jp	c,_ReturnNEG1L \.r
_PutChar_ASM:
	call	_GetSlotSize_ASM \.r
	push	bc
	call	_GetSlotOffset_ASM \.r
	pop	hl
	or	a,a
	sbc	hl,bc
	jp	c,_ReturnNEG1L \.r
	jr	nz,noIncrement
Increment:
	push	bc
	inc	hl
	ld	(resizeBytes),hl
	call	_EnoughMem
	pop	bc
	jp	c,_ReturnNEG1L \.r
	push	bc
	ex	de,hl
	call	AddMemoryToVar \.r
	pop	bc
	or	a,a
	jp	z,_ReturnNEG1L \.r
noIncrement:
	call	_GetSlotDataPtr_ASM \.r
	ld	hl,(hl)
	add	hl,bc
	inc	hl
	inc	hl
	ld	a,(charIn)
	ld	(hl),a
	inc	bc
	push	af
	call	_SetSlotOffset_ASM \.r
	pop	af
	or	a,a
	sbc	hl,hl
	ld	l,a
	ret
 
;-------------------------------------------------------------------------------
_DeleteVar:
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
	jr	+_

;-------------------------------------------------------------------------------
_Delete:
; Deletes an AppVar
; Arguments:
;  arg0 : Pointer to AppVar name
; Returns:
;  0 if failure
	ld	a,appVarObj
_:	pop	de
	pop	hl
	push	hl
	push	de
	dec	hl
	push	af
	call	_Mov9ToOP1
	pop	af
	ld	(OP1),a
	call	_ChkFindSym
	jp	c,_ReturnNULL \.r
	ld	iy,flags
	call	_DelVarArc
	scf
	sbc	hl,hl
	ret
 
;-------------------------------------------------------------------------------
_Rewind:
; Performs an frewind on a varaible
; Arguments:
;  arg0 : Slot number
; Returns:
;  -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
	ld	bc,0
	call	_SetSlotOffset_ASM \.r
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
_Tell:
; Performs an ftell on a varaible
; Arguments:
;  arg0 : Slot number
; Returns:
;  -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
	call	_GetSlotOffset_ASM \.r
	push	bc
	pop	hl
	ret

;-------------------------------------------------------------------------------
_GetSize:
; Gets the size of an AppVar
; Arguments:
;  arg0 : Slot number
; Returns:
;  -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNEG1L \.r
	call	_GetSlotSize_ASM \.r
	push	bc
	pop	hl
	ret

;-------------------------------------------------------------------------------
_Close:
; Closes an open slot varaible
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
	call	_GetSlotVATPtr_ASM \.r
	ld	de,0
	ld	(hl),de
	ret

;-------------------------------------------------------------------------------
_DetectVar:
; Finds a variable that starts with some data
; Arguments:
;  arg0 : address of pointer to being search
;  arg1 : pointer to null terminated string of data to search for
;  arg2 : type of varaible to search for
	ld	hl,9
	add	hl,sp
	ld	a,(hl)
	jr	+_

;-------------------------------------------------------------------------------
_Detect:
; Finds an AppVar that starts with some data
;  arg0 : address of pointer to being search
;  arg1 : pointer to null terminated string of data to search for
	ld	a,appVarObj
_:	ld	(DetectType_SMC),a \.r
	push	ix
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+9)
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	z,finish
	ld	hl,(ix+6)
	ld	hl,(hl)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	nz,fdetect
	ld	hl,(progPtr)
fdetect:
	ld	de,(pTemp)
	or	a,a
	sbc	hl,de
	jr	c,finish
	jr	z,finish
	add	hl,de
	jr	fcontinue

finish:	xor	a,a
	sbc	hl,hl
	pop	ix
	ret

fcontinue:
	push	hl
	ld	a,(hl)
DetectType_SMC =$+1
	cp	a,appVarObj
	jr	nz,fskip
fgoodtype:
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
	jr	nc,finRAM
	ld	de,9
	add	hl,de				; skip archive VAT stuff
	ld	e,(hl)
	add	hl,de
	inc	hl
finRAM:	inc	hl
	inc	hl				; hl -> data
	ld	bc,(ix+9)
_:	ld	a,(bc)
	or	a,a
	jr	z,ffound
	cp	a,(hl)
	inc	bc
	inc	de
	inc	hl
	jr	z,-_				; check the string at the memory
fskip:	pop	hl
	call	fbypassname \.r
	jr	fdetect
	
ffound:	pop	hl
	call	fbypassname \.r
	ex	de,hl
	ld	hl,(ix+6)
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	z,finish
	ld	(hl),de
	ld	hl,OP6
	pop	ix
	ret

fbypassname:					; bypass the name in the VAT (also used for setting the string name)
	ld	de,OP6
	ld	bc,-6
	add	hl,bc
	ld	b,(hl)
	dec	hl
_:	ld	a,(hl)
	ld	(de),a
	dec	hl
	inc	de
	djnz	-_
	xor	a,a
	ld	(de),a
	ret

;-------------------------------------------------------------------------------
_GetTokenString:
; Returns pointer to next token string
; Arguments:
;  arg0 : Slot number
; Returns:
;  Pointer to string to display
	ld	iy,0
	add	iy,sp
	ld	a,1
	ld	(TokLen_SMC),a \.r
	ld	hl,(iy+3)
	ld	hl,(hl)
	push	hl
	ld	a,(hl)
	call	_Isa2ByteTok
	ex	de,hl
	jr	nz,+_
	inc	de
	ld	hl,TokLen_SMC \.r
	inc	(hl)
_:	inc	de
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
	jr	z,+_
	ld	(hl),bc
_:	ld	hl,(iy+6)
	add	hl,bc
	or	a,a
	sbc	hl,bc
	jr	z,+_
TokLen_SMC =$+1
	ld	(hl),1
_:	ld	hl,OP3
	ret

;-------------------------------------------------------------------------------
_GetDataPtr:
; Returns a pointer to the current location in the given variable
; Arguments:
;  arg0 : Slot number
; Returns:
;  Pointer to current offset data
	pop	de
	pop	bc
	push	bc
	push	de
	call	_CheckIfSlotOpen \.r
	jp	z,_ReturnNULL \.r
	call	_GetSlotSize_ASM \.r
	inc	hl
	push	hl
	call	_GetSlotOffset_ASM \.r
	pop	hl
	add	hl,bc
	ret

;-------------------------------------------------------------------------------
_SetVar:
; Sets a varaible
; Gets a pointer to a varaible data struct
; Arguments:
;  arg0 : Pointer to variable name string
;  arg1 : Pointer to data structure pointer
; Returns:
;  Any error codes returned when storing
	push	ix
	ld	ix,0
	add	ix,sp
	ld	hl,(ix+9) ; pointer to var string
	ld	a,(ix+6)
	call	_SetVarStr \.r
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
_StoVar:
; Stores a varaible
; Gets a pointer to a varaible data struct
; Arguments:
;  arg0 : Pointer to variable name string
;  arg1 : Pointer to data structure pointer
; Returns:
;  Any error codes returned when storing
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+12) ; pointer to var string
	call	_SetVarStr \.r
	ld	a,(iy+9)
	or	a,a         ; if a real we have to look up the varaible
	jr	z,_iscr
	cp	a,0Ch       ; if a cplx we have to look up the varaible
	jr	nz,_notcr
_iscr:	call	_FindSym
	jp	c,_notcr     ; just fill it with zero
	and	a,03Fh
	ex	de,hl
	call	_Mov9OP1OP2
_notcr:	call	_PushOP1
	ld	hl,(iy+6) ; pointer to var string
	ld	a,(iy+3)
	call	_SetVarStr \.r
	ld	iy,flags
	ld	hl,_ReturnNEG1C \.r
	call	_PushErrorHandler
	call	_StoOther
	call	_PopErrorHandler
	xor	a,a
	ret

;-------------------------------------------------------------------------------
_RclVar
; Gets a pointer to a varaible data struct
; Arguments:
;  arg0 : Pointer to variable name string
;  arg1 : Pointer to data structure pointer
; Returns:
;  Type of variable returned
	ld	iy,0
	add	iy,sp
	ld	hl,(iy+6) ; pointer to var string
	ld	a,(iy+3)  ; var type
	call	_SetVarStr \.r
	call	_FindSym
	jp	c,_ReturnNEG1C \.r
	call	_ChkInRAM
	jp	nz,_ReturnNEG1C \.r
	ld	iy,0
	add	iy,sp
	and	a,03Fh
	cp	a,(iy+3)  ; var type
	jp	nz,_ReturnNEG1C \.r
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
	and	a,03Fh
	ld	(OP1),a
	ret

;-------------------------------------------------------------------------------
AddMemoryToVar:
	call	_GetSlotDataPtr_ASM \.r
	push	hl
	ld	hl,(hl)
	push	hl
	call	_GetSlotOffset_ASM \.r
	pop	hl
	add	hl,bc
	inc	hl					; bypass size bytes
	inc	hl
	ex	de,hl
	ld	hl,(resizeBytes)
	push	hl
	push	de
	call	_EnoughMem
	pop	de
	pop	hl
	jr	c,_ReturnNULLC
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
	add	hl,bc					; increase by 5
	jr	SaveSize
DeleteMemoryFromVar:
	call	_GetSlotDataPtr_ASM \.r
	push	hl
	ld	hl,(hl)
	push	hl
	call	_GetSlotOffset_ASM \.r
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
	sbc	hl,bc					; decrease amount
SaveSize:
	ex	de,hl
	pop	hl					; pointer to size bytes location
	ld	(hl),e
	inc	hl
	ld	(hl),d					; write new size
_ReturnNEG1C:
	ld	a,255
	ret
_ReturnNULLC:
	xor	a,a
	ret

_ReturnNULL_PopIX:
	pop	ix
_ReturnNULL:
	xor	a,a
	sbc	hl,hl
	ret
_ReturnNEG1L:
	scf
	sbc	hl,hl
	ret
_CheckIfSlotOpen:
	ld	a,c
	ld	(currSlot),a
	push	hl
	push	bc
	call	_GetSlotVATPtr_ASM \.r
	ld	hl,(hl)
	add	hl,de 
	or	a,a 
	sbc	hl,de
	pop	bc
	pop	hl
	ret
_GetSlotVATPtr_ASM:
	ld	a,(currSlot)
	ld	hl,VATPtr0 	; VATPtr0 = $D0244E
	dec	a
	ret	z
	inc	h
	ld	l,$7b		; VATPtr1 = $D0257B
	dec	a
	ret	z
	ld	l,$7e		; VATPtr2 = $D0257E
	dec	a
	ret	z
	ld	l,$81		; VATPtr3 = $D02581
	dec	a
	ret	z
	ld	l,$84		; VATPtr4 = $D02584
	ret
_GetSlotDataPtr_ASM:
	ld	a,(currSlot)
	ld	hl,DataPtr0	; DataPtr0 = $D0067E
	dec	a
	ret	z
	ld	l,$81		; DataPtr1 = $D00681
	dec	a
	ret	z
	ld	hl,DataPtr2	; DataPtr2 = $D01FED
	dec	a
	ret	z
	ld	l,$f3		; DataPtr3 = $D01FF3
	dec	a
	ret	z
	ld	l,$f9		; DataPtr4 = $D01FF9
	ret
_GetSlotOffsetPtr_ASM:
	push	bc
	ld	hl,(currSlot)
	dec	l
	ld	h,3
	mlt	hl
	ld	bc,VarOffset0 \.r
	add	hl,bc
	pop	bc
	ret
_GetSlotSize_ASM:
	call	_GetSlotDataPtr_ASM \.r
	ld	hl,(hl)
	ld	bc,0
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ret
_GetSlotOffset_ASM:
	call	_GetSlotOffsetPtr_ASM \.r
	ld	bc,(hl)
	ret
_SetSlotOffset_ASM:
	call	_GetSlotOffsetPtr_ASM \.r
	ld	(hl),bc
	ret

;-------------------------------------------------------------------------------
; Internal library data
;-------------------------------------------------------------------------------

VarOffset0:
	.dl 0,0,0,0,0

 .endLibrary
