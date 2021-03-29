;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'KEYPADC', 3

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export kb_Scan
	export kb_ScanGroup
	export kb_AnyKey
	export kb_Reset

;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
	export kb_GetKeyCode
	export kb_QueueKeys
	export kb_UnqueueKey
	export kb_ClearQueue

;-------------------------------------------------------------------------------
kb_Scan:
; Scans the keypad and updates data registers
; Note: Disables interrupts during execution, and restores on exit
; Arguments:
;  None
; Returns:
;  None
	di
	ld	hl,$f50200		; DI_Mode = $f5xx00
	ld	(hl),h
	xor	a,a
.loop:
	cp	a,(hl)
	jr	nz,.loop
	ret

;-------------------------------------------------------------------------------
kb_Reset:
; Resets the keypad (Only use if modified)
; Arguments:
;  None
; Returns:
;  None
	ld	hl,$000f00		; 0/Wait 15*256 APB cycles before scanning each row/Mode 0/
	ld	(ti.DI_Mode),hl
	ld	hl,$08080f		; (nb of columns,nb of row) to scan/Wait 15 APB cycles before each scan
	ld	(ti.DI_Mode+3),hl
	ret

;-------------------------------------------------------------------------------
kb_ScanGroup:
; Scans a keypad group
; Note: Disables interrupts during execution
; Arguments:
;  arg0 : Keypad group number
; Returns:
;  Value of entire group (Keys ORd)
	ld	hl,3
	add	hl,sp
	ld	a,(hl)
	cp	a,8
	jr	nc,.found
	add	a,a
	add	a,$10
	ld	c,a
	di
	ld	hl,$f50200		; DI_Mode = $f5xx00
	ld	(hl),h
	xor	a,a
.loop:
	cp	a,(hl)
	jr	nz,.loop
	ld	l,c
.found:
	xor	a,(hl)
	ret

;-------------------------------------------------------------------------------
kb_AnyKey:
; Scans the keypad and updates data registers; checking if a key was pressed
; Note: Disables interrupts during execution
; Arguments:
;  None
; Returns:
;  0 if no key is pressed
	di
	ld	bc,2
	ld	hl,$f51200		; DI_Mode = $f5xx00
	ld	(hl),c
	xor	a,a
.loop:
	cp	a,(hl)
	jr	nz,.loop
	ld	l,h			; kbdG1 = $f5xx12
	or	a,(hl)
	add	hl,bc
	or	a,(hl)
	add	hl,bc
	or	a,(hl)
	add	hl,bc
	or	a,(hl)
	add	hl,bc
	or	a,(hl)
	add	hl,bc
	or	a,(hl)
	add	hl,bc
	or	a,(hl)
	ret

;-------------------------------------------------------------------------------
kb_GetKeyCode:
; Scans the keypad and returns the currently pressed key's keycode
; Arguments:
;  None
; Returns:
;  The same as GetCSC
	call kb_Scan
	ld hl,$F50012
	ld b,7
	ld c,49
.scanloop:
	ld a,(hl)
	or a,a
	jr nz,.keyispressed
	inc hl
	inc hl
	ld a,c
	sub a,8
	ld c,a
	djnz .scanloop
	xor a,a
	ret
.keyispressed:
	ld b,8
.keybitloop:
	rrca
	jr c,.this
	inc c
	djnz .keybitloop
.this:
	ld a,c
	ret

;-------------------------------------------------------------------------------
kb_QueueKeys:
; Scans the keypad, queuing found keycodes for later processing
; Arguments:
;  arg0: pointer to kb_queue_t queue
; Returns:
;  0 if no keys pressed
	pop bc
	ex (sp),ix
	push bc
	call kb_AnyKey
	jq z,.returnzero ;return if no keys pressed
	ld de,$F50012
	ld b,7
	ld c,56
	dec ix
.loop:
	ld a,(de)
.bitsloop:
	inc ix
	dec c
	add a,a
	jq nc,.checkisz
	inc c
	ld (ix),c ;c is current keycode
	dec c
.checkisz:
	jq nz,.bitsloop
.next:
	ld a,c        ;get next row of keys' last keycode
	and a,$F8
	ld c,a
	inc de   ;get next keypad group
	inc de
	djnz .loop
.done:
	db $3E ;ld a,...
.returnzero:
	xor a,a
	pop hl
	ex (sp),ix
	jp (hl)


;-------------------------------------------------------------------------------
kb_UnqueueKey:
; Unqueues a key from the key buffer
; Arguments:
;  arg0: pointer to kb_queue_t queue
	pop bc
	ex (sp),hl
	push bc
	ld bc,56
	add hl,bc
	dec hl
	xor a,a
.findkeyloop:
	cpd
	ret po
	jq z,.findkeyloop
	inc hl
	ld a,(hl)
	ld (hl),b ;remove key from queue
	ret

;-------------------------------------------------------------------------------
kb_ClearQueue:
; Clears all keycodes from a queue.
; Arguments:
;  arg0: pointer to kb_queue_t queue to clear
	pop de
	ex (sp),hl
	ld bc,56
	xor a,a
.clearloop:
	ld (hl),a
	inc hl
	djnz .clearloop
	ex hl,de
	jp (hl)

;-------------------------------------------------------------------------------
; TODO
;kb_SetQueueRepeatDelay:
;	
;	ret
