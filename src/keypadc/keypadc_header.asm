 define .keypadc_header,space=ram
 define .keypadc,space=ram
 segment .keypadc_header
 .assume adl=1
 db 192,"KEYPADC",0,2
 end

