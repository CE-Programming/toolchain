; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Comparison
; Input:
;	Operand1: 
;                 EHL : 32 bits
;		  
;	Operand2: 
;                 ABC : 32 bits
;
; Output:
;	Result:   F : S,V flags from EHL - ABC
; Registers Used:
;	None
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lcmps

SILICON_BUG     EQU     0       ; Remove for non-simulation or fix simulator

__lcmps:
        push    bc
        push    hl
        push    de

        ld      d,a             ; preserve a

        or      a,a             ; clear carry
        sbc     hl,bc

        ld      b,a
        ld      a,e
        ld      e,b
        jr      z,maybe_zero    ; First sbc sets z flag

        ; definitely not zero
        sbc     a,e
        push    af
        pop     bc
        res     6,c             ; force z flag to zero, all others untouched
        push    bc
        pop     af
        jr      next

maybe_zero:
        ; This sbc dictates the value of all flags
        sbc     a,e

next:


;       if ( V != 0)
;         S = S xor V

IF      SILICON_BUG
        push    af
        pop     bc              ; b <- flags

        bit     2,b             ; if (v == 1)
        jr      z,.done         ; else go to .done
        ld      a,b             ; b <- b xor %80
        xor     a,%80           ; invert sign bit
        ld      b,a
ELSE
        push    af
        pop     bc              ; c <- flags

        bit     2,c             ; if (v == 1)
        jr      z,.done         ; else go to .done
        ld      a,c             ; c <- c xor %80
        xor     a,%80           ; invert sign bit
        ld      c,a
ENDIF

.done:
        push    bc
        pop     af              ; flags <- b

        ld      a,d             ; restore a

	pop	de
	pop	hl
	pop	bc
        ret

