 define .GRAPHC_HEADER,space=ram
 define .GRAPHC,space=ram
 segment .GRAPHC_HEADER
 .assume ADL=1
 db 192,"GRAPHC",0,3
 end
