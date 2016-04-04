;************************************************************************
;*      ez80Startup: C Runtime Startup for ZDS II
;*	Copyright (c) 2007-2008 Zilog, Inc.
;************************************************************************
	;;
	;; BARE_SYSTEM - Set to 1 if a standalone system and all interrupt
	;; vectors must be captured.
	;; 
BARE_SYSTEM	EQU		0
	;;
	;; RELOCATED_VECTOR TABLE is address of vector table supported
	;; by the ROM monitor
	;; 
RELOCATED_VECTOR_TABLE	EQU		0E000H
	;;
	;; RELOCATED_JUMP_TABLE is address of vector jump table supported
	;; by the ROM monitor
	;; 
RELOCATED_JUMP_TABLE	EQU		0E100H
	;;
	;;  maximum value for NUM_VECTORS is 128
	;;  allows use of single byte register in init loops
	;; 
NUM_VECTORS     EQU             128

SAVEIMASK	macro		; sets a=0 if interrupts disabled else a=1
	ld	a,i		; sets parity bit to value of IEF2
	ld	a,0
	jp	po,$+5		; parity bit is IEF2
	inc	a
	macend

RESTOREIMASK	macro		; restore interrupt state
	bit	0,a
	jr	z,$+3
	ei
				; enable intr if enabled on entry
	macend

;************************************************************************
;* Define global system var _errno. Used by floating point libraries
;* 
;************************************************************************
        .def    _errno
_errno:	
        dw      1     ; extern int _errno;

	;************************************************************************
;* Define number of vectors supported. externed in ez80.h. Can be used
;* to loop through all interrupt vectors calling _set_vector();
;************************************************************************
        .def    __num_vectors
__num_vectors:
        dw      NUM_VECTORS     ; extern unsigned short _num_vectors;

;************************************************************************
;* Define vector table. Each entry is a 16-bit address pointing into
;* the __vecptr segment. This segment must be aligned on a 256 byte
;* boundary or RAM and reside in the lower 64kb of memory.
;************************************************************************
.IF BARE_SYSTEM
	.def    __vector_table
        define  __vectab,space=RAM,align=256
        .sect   "__vectab"
	ORG	RELOCATED_VECTOR_TABLE
__vector_table:
        ds      NUM_VECTORS*2   ; Each vector is a 2-byte address pointing
                                ; into the __vectptr segment

;************************************************************************
;* Define jump table table. Each entry is a JP.LIL to an interrupt
;* handler. This segment must reside in the the lower 64Kb of RAM.
;************************************************************************
        define  __jumptab,space=RAM
        .sect   "__jumptab"     ; __vectors is pre-defined
	ORG	RELOCATED_JUMP_TABLE
__jump_table:
        ds     NUM_VECTORS*4   ; Each entry is a JP.LIL to a handler
.ENDIF

;************************************************************************
;* Startup code. Reset entry point.
;************************************************************************

        define  .startup,space=ROM

	.sect	".startup"	; This should be placed properly

	.ref	_main
        .ref    __low_bss       ; Low address of bss segment
        .ref    __len_bss       ; Length of bss segment
        .ref    __stack         ; Stack start address
_boardstart:	
        jp.lil  _c_int0         ; Jump to startup code and set ADL=1
	.assume	ADL=1
	;;
	;; Make all RST nn's jump to startup code and set ADL=1
	;; 
        ds	3
        jp.lil  _c_int0
	ds	3 
        jp.lil  _c_int0
	ds	3 
        jp.lil  _c_int0
	ds	3 
        jp.lil  _c_int0
	ds	3 
        jp.lil  _c_int0
	ds	3 
        jp.lil  _c_int0
	ds	3 
        jp.lil  _c_int0
	ds	3
__nmiretn:	
	retn	
	ds	24H
;************************************************************************
;* Default NMI interrupt handler
;************************************************************************
__default_NMI_hndlr:
        jp	__nmiretn
; 
; 
;**********************************
; Program entry point
;**********************************
_c_int0:

        ;
        ; At this point we're in ADL mode because we got here
        ; via a jp.lil at the reset location 000000h
        ;

        di                      ; Disable interrupts
.IF BARE_SYSTEM
        im      2               ; Interrtup mode 2
	ld	a,__vector_table >> 8 & 0ffh
        ld      i,a             ; Load interrtup vector base
.ENDIF

        ld      sp,__stack      ; Setup SPL

;------ Initialize the .BSS section to zero

	ld	hl,__len_bss	; Check for non-zero length
	ld	bc,0		; *
	or	a,a		;  clears carry bit
	sbc	hl,bc		; *
	jr	z,_c_bss_done	; .BSS is zero-length ...
$$:
	ld	hl,__low_bss	; [hl]=.bss
	ld	bc,__len_bss
	ld	(hl),0
	dec	bc		; 1st byte's taken care of
	ld	hl,0
	sbc	hl,bc	
	jr	z,_c_bss_done	; Just 1 byte ...
	ld	hl,__low_bss	; reset hl
	ld	de,__low_bss+1	; [de]=.bss+1
	ldir			; Load Increment with Repeat
_c_bss_done:


	.ref    __low_data	; Address of initialized data section
	.ref    __low_romdata	; Addr of initialized data section in ROM
	.ref    __len_data	; Length of initialized data section

;------ Copy the initialized data section
	
	ld	hl,__len_data	; Check for non-zero length
	ld	bc,0		; *
	or	a,a		; Clears carry flag
	sbc	hl,bc		; *
	jr	z,_c_data_done	; __len_data is zero-length ...
$$:
	ld	hl,__low_romdata; [hl]=.data_copy
	ld	de,__low_data	; [de]=.data
	ld	bc,__len_data	; [bc]= data length
	ldir			; Copy the data section
_c_data_done:

;----- Copy CODE (which may be in FLASH) to RAM if the
;----- copy_code_to_ram symbol is set in the link control file
;
        .ref    __copy_code_to_ram
        .ref    __len_code,__low_code,__low_romcode
        ld      a,__copy_code_to_ram
        or      a,a
        jr      z,_copy_code_to_ram_done

        ld      hl,__len_code   ; Check for non-zero length
	ld	bc,0		; *
	or	a,a		; Clears carry flag
	sbc	hl,bc		; *
        jr      z,_copy_code_to_ram_done  ; __len_code is zero-length ...

        ld      hl,__low_romcode; [hl]=.code_copy
        ld      de,__low_code   ; [de]=.code
        ld      bc,__len_code   ; [bc]= code length
        ldir                    ; Copy the code section

_copy_code_to_ram_done:
.IF BARE_SYSTEM        
        call    __init_default_vectors
.ENDIF
        ei                      ; enable interrupts

;------ main()
	call	_main		; main()
	jmp	$		; Don't fall into following code
				; if main returns

;************************************************************************
;* Default interrupt handler
;************************************************************************
__default_hndlr:
        reti

;************************************************************************
;* Define __init_default_vectors to initialize all vectors to a known
;* default handler.
;*
;*      void _init_default_vectors(void);
;*
;************************************************************************
.IF BARE_SYSTEM
	.def    __init_default_vectors
__init_default_vectors:
        ;
        ; Place vectors into __vector_table that
        ; point to __vector_ptr table
        ;
	push	af
	SAVEIMASK
	di			; disable interrupts while loading table
        ld      hl,__vector_table
        ld      b,NUM_VECTORS
        ld      iy,__jump_table
$1:
        ld.sis  (hl),iy       ; store vector
        inc     hl
        inc     hl            ; next vector address
        lea     iy,iy+4       ; next jp.lil address
        dec     b
        jr      nz,$1

        ;
        ; Place call  __default_hndlr into __vector_ptr table
        ;

        ld      hl,__jump_table
        ld      b,NUM_VECTORS
        ld      iy,__default_hndlr
$2:
        ld      (hl),0cdh     ; call
        inc     hl
        ld      (hl),iy       ; __default_hndlr
        inc     hl
        inc     hl
        inc     hl
        djnz	$2
	RESTOREIMASK
	pop	af
        ret
.ENDIF

;************************************************************************
;* Define __set_vector to install a user interrupt handler
;*
;*      void _set_vector(unsigned short vector,void (*hndlr)(void));
;*
;*      NOTE: THIS CODE DOES NOT INSERT THE JP BECAUSE IT ASSUMES
;*            THAT __init_default_vectors HAS ALREADY BEEN CALLED.
;*
;*      (IX+9)  hndlr - address of user interrupt handler
;*      (IX+6)  vector - defined in ez80.h. Actually an index into
;*                       __jump_table
;*
;************************************************************************
        .def    __set_vector
__set_vector:
        push    ix
        ld      ix,0
        add     ix,sp           ; Standard prologue
	push	af
	SAVEIMASK
        ld      hl,0            ; Clear UHL
        ld.sis  hl,(ix+6)       ; Vector offset
.IF BARE_SYSTEM 	
        ld      bc,__jump_table
.ELSE
	ld	bc,RELOCATED_JUMP_TABLE
.ENDIF	
        add     hl,bc           ; hl is address of jp
        inc     hl              ; hl is address of handler
        ld      bc,(ix+9)       ; handler
        ld      (hl),bc         ; store new vector address

	RESTOREIMASK
	pop	af
        ld      sp,ix           ; Standard epilogue
        pop     ix
        ret

	end	_boardstart
