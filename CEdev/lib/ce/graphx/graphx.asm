 .assume ADL=1
 define .GRAPHX_HEADER,space=ram
 define .GRAPHX,space=ram
 segment .GRAPHX_HEADER
 db 192,"GRAPHX",0,4
 end
