.nolist
;---------------------------------------------

#macro libraryName(name)
 #define numfunctions 0
 #define numrelocations 0
 
 clr()
 wr("#define asmname ",name,".asm")
 run()
 clr()
 wr("#define totname ",name,".jmp")
 run()
 
 #define noextname eval(name)
 
 .echo > relocation_table ""
 .echo > totname " .db 192,\"",noextname,"\",0,"
 .echo > asmname " define .",noextname,"_HEADER,space=ram\n define .",noextname,",space=ram\n segment .",noextname,"_HEADER\n .assume ADL=1\n db 192,\"",noextname,"\",0,"
 .db 192,192
#endmacro
#define .libraryName libraryName(

;---------------------------------------------

#macro libraryVersion(version)
 #define libversion eval(version)
 .echo >> asmname libversion,"\n"
 .echo >> totname libversion,"\n"
 .db libversion
#endmacro
#define .libraryVersion libraryVersion(

;---------------------------------------------

#macro function(funcname, funclabel)
  clr()
  wr("#define modulename ",funcname,".src")
  run()
 
 .echo >> totname "_",funcname,":\n"
 .echo >> totname " jp ",numfunctions*3,"\n"
 .echo >  modulename " define .",noextname,",space=ram\n segment .",noextname,"\n .assume ADL=1\n"
 .echo >> modulename " .def _",funcname,"\n"
 .echo >> modulename "_",funcname,":\n"
 .echo >> modulename " jp ",numfunctions*3,"\n"
 .echo >> modulename " end"
 .dl funclabel

 #define numfunctions numfunctions+1
#endmacro
#define .function function(

;---------------------------------------------

#macro endLibrary()
 clr()
 wr("_libendaddr:")
 wr("_reloc_table:")
 run()
 #include "relocation_table"
 .dl _depend_start			; ptr
 .dl _libendaddr			; size

 .echo "Total library size:\t",6+numrelocations*3+numfunctions*3+_libendaddr
 .echo "Extracted library size:\t",_libendaddr
 .echo "Relocation table size:\t",numrelocations*3
 .echo "Functions vector size:\t",numfunctions*3
 .echo "Success!"
 .echo >> asmname " end\n"
#endmacro
#define .endLibrary endLibrary()

;---------------------------------------------

#macro relocate()
 #define numrelocations numrelocations+1
 
 #define offset eval($-3)
 .echo >> relocation_table " .dl ",offset,"\n"
#endmacro
#define .r relocate()

;--------------------------------------------

#macro beginDependencies()
 clr()
 wr("_depend_start:")
 run()
 .org $000000
#endmacro
#define .beginDependencies beginDependencies()
;--------------------------------------------

#macro endDependencies()
 clr()
 wr("_depend_end:")
 run()
#endmacro
#define .endDependencies endDependencies()
;--------------------------------------------

#macro comment()
 ;
#endmacro
#define .c comment()
;--------------------------------------------

; ZDS sillyness
#define db .db
#define dl .dl
#define dw .dw

; stack frame locations
#define __frame_arg0 6
#define __frame_arg1 9
#define __frame_arg2 12
#define __frame_arg3 15
#define __frame_arg4 18
#define __frame_arg5 21
#define __frame_arg6 24
#define __frame_arg7 27
#define __frame_arg8 30
#define __frame_arg9 33

.list