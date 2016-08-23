; Edited from original built version to include gfx_palette and gfx_vram segment spaces

 .assume ADL=1
 .def _gfx_palette
 .def _gfx_vram
 define ___gfx_palette_segment,space=ram,org=%e30200
 segment ___gfx_palette_segment
_gfx_palette:
 ds 512
 define ___gfx_vram_segment,space=ram,org=%d40000
 segment ___gfx_vram_segment
_gfx_vram:
 ds 153600
 define .GRAPHX_HEADER,space=ram
 define .GRAPHX,space=ram
 segment .GRAPHX_HEADER
 db 192,"GRAPHX",0,2
 end