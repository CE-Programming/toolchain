 define .fileioc_header,space=ram
 define .fileioc,space=ram
 segment .fileioc_header
 .assume adl=1
 db 192,"FILEIOC",0,3
 end

