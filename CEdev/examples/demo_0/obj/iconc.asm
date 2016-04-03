 define .icon,space=ram
 segment .icon
 xdef __icon_begin
 xdef __icon_end
 xdef __program_description
 xdef __program_description_end

 db 1
 db 16,16
__icon_begin:
 db 
 db 0FFh,0FFh,0FFh,0FFh,002h,002h,002h,002h,002h,002h,002h,002h,0FFh,0FFh,0FFh,0FFh
 db 0FFh,0FFh,002h,002h,002h,023h,023h,023h,023h,023h,023h,002h,002h,002h,0FFh,0FFh
 db 0FFh,002h,002h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,002h,002h,0FFh
 db 0FFh,002h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,002h,0FFh
 db 002h,002h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,002h
 db 002h,023h,023h,023h,023h,023h,023h,0FFh,0FFh,0FFh,023h,023h,023h,023h,023h,002h
 db 002h,023h,023h,023h,023h,023h,0FFh,002h,002h,002h,023h,023h,023h,023h,023h,002h
 db 002h,023h,023h,023h,023h,023h,0FFh,002h,023h,023h,023h,023h,023h,023h,023h,002h
 db 002h,023h,023h,023h,023h,023h,0FFh,002h,023h,023h,023h,023h,023h,023h,023h,002h
 db 002h,023h,023h,023h,023h,023h,002h,0FFh,0FFh,0FFh,023h,023h,023h,023h,023h,002h
 db 002h,023h,023h,023h,023h,023h,023h,002h,002h,002h,023h,023h,023h,023h,023h,002h
 db 002h,002h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,002h,002h
 db 0FFh,002h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,002h,0FFh
 db 0FFh,002h,002h,023h,023h,023h,023h,023h,023h,023h,023h,023h,023h,002h,002h,0FFh
 db 0FFh,0FFh,002h,002h,002h,023h,023h,023h,023h,023h,023h,002h,002h,002h,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0FFh,002h,002h,002h,002h,002h,002h,002h,002h,0FFh,0FFh,0FFh,0FFh
__icon_end:
__program_description:
 db "Example C program - Demo 0",0
__program_description_end:
