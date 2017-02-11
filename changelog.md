## Toolchain

#### Version 7.0
 + Add scripts to build/clean libraries and examples easily
 + Move spasm to /bin rather than /lib/src/include
 + Fix demo 11 readme
 
#### Version 6.95
 + Modify cstartup.asm to disable usb timers and reset them on exit
 + Characters 0x01-0x1F are considered printable rather than control

## Libraries

#### Version 6.95
  + `graphx` Optimize gfx_Darken to be about 25% faster
  + `graphx` Optimize gfx_Lighten to be about 19% faster
  + `graphx` Add support for width/height of tiles not powers of 2
  + `graphx` Fix bug with tile index 255
