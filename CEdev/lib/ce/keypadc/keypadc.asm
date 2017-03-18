 define .KEYPADC_HEADER,space=ram
 define .KEYPADC,space=ram
 segment .KEYPADC_HEADER
 .assume ADL=1
 db 192,"KEYPADC",0,2
 end
