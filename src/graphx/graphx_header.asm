 define .graphx_header,space=ram
 define .graphx,space=ram
 segment .graphx_header
 .assume adl=1
 db 192,"GRAPHX",0,5
 end

