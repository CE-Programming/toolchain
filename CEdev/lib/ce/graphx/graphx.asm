 define .GRAPHX_HEADER,space=ram
 define .GRAPHX,space=ram
 segment .GRAPHX_HEADER
 .assume ADL=1
 db 192,"GRAPHX",0,4
 end
