;	        Copyright 1992-2008 Zilog, Inc. 
	.assume adl=1
	.def	__frameset0
	
__frameset0:
  EX (SP),IX   ; (sp)=ix and ix=return address
  LEA HL,IX+0  ; hl = return address
  LD IX,0
  ADD IX,SP  ; ix=sp
  JP (HL)  ; jump to return address
