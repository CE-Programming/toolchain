 define .FILEIOC_HEADER,space=ram
 define .FILEIOC,space=ram
 segment .FILEIOC_HEADER
 .assume ADL=1
 db 192,"FILEIOC",0,3
 end
