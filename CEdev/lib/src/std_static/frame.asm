;	        Copyright 1992-2008 Zilog, Inc. 
	.assume adl=1
	.def	__frameset0, __frameset
	
__frameset0:
  EX (SP),IX   ; (sp)=ix and ix=return address
  LEA HL,IX+0  ; hl = return address
  LD IX,0
  ADD IX,SP  ; ix=sp
  JP (HL)  ; jump to return address

__frameset:
  EX (SP),IX  ; (sp)=ix and ix=return address
  LEA DE,IX+0 ; hl=return address
  LD IX,0
  ADD IX,SP ; ix=sp
  ADD HL,SP
  LD SP,HL  ; allocate stack
  EX DE,HL  ; hl=return address
  JP (HL) ; jump to return address
