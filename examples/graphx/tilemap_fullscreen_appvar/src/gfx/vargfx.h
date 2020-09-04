#ifndef vargfx_appvar_include_file
#define vargfx_appvar_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define sizeof_global_palette 512
#define global_palette (vargfx_appvar[0])
#define image_tile_width 80
#define image_tile_height 80
#define image_compressed vargfx_appvar[1]
#define image_tiles_num 12
extern unsigned char *image_tiles_compressed[12];
#define image_tile_0_compressed image_tiles_compressed[0]
#define image_tile_1_compressed image_tiles_compressed[1]
#define image_tile_2_compressed image_tiles_compressed[2]
#define image_tile_3_compressed image_tiles_compressed[3]
#define image_tile_4_compressed image_tiles_compressed[4]
#define image_tile_5_compressed image_tiles_compressed[5]
#define image_tile_6_compressed image_tiles_compressed[6]
#define image_tile_7_compressed image_tiles_compressed[7]
#define image_tile_8_compressed image_tiles_compressed[8]
#define image_tile_9_compressed image_tiles_compressed[9]
#define image_tile_10_compressed image_tiles_compressed[10]
#define image_tile_11_compressed image_tiles_compressed[11]
#define vargfx_entries_num 2
extern unsigned char *vargfx_appvar[2];
unsigned char vargfx_init(void);

#ifdef __cplusplus
}
#endif

#endif
