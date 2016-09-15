;----------------------------------------------------------------
;
; 	        Dumy floating point entry points
;		for the Zilog eZ80 C Compiler
;
;	        Copyright 1992-2008 Zilog, Inc. 
;
;----------------------------------------------------------------
;
;
;	Code entry points
;
		XDEF __fadd, __fppack
        XDEF __fsub,__fmul,__fdiv
        XDEF __ultof,__ltof,__ftol,__fneg,__fcmp,_asin,_acos,_atan2
        XDEF _atan,_floor,_ceil,_cosh,_sinh,_exp
        XDEF _fabs,_fmod,_ldexp,_log10,_log
        XDEF _pow,_sqrt,_tan,_tanh
        XDEF __u_flt_info,__u_flt_rnd
        XDEF __u_dtoe,__u_dtof,__u_dtog,__huge_val
__fadd:
__fdiv:
__fmul:
__fppack:	
__fsub:
__ultof:
__ltof:
__ftol:
__fneg:
__fcmp:
_asin:
_acos:
_atan2:
_atan:
_atof:
_floor:
_ceil:
_cosh:
_sinh:
_exp:
_fabs:
_fmod:
_frexp:
_ldexp:
_log10:
_log:
_modf:
_pow:
_sqrt:
_tan:
_tanh:
__u_dtoe:
__u_dtof:
__u_dtog:
__u_flt_info:
__u_flt_rnd:
_strtod:
__huge_val:     ; No need to have a legimate value here, just a valid address
		RET
		END
