/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @brief Optimized decompression routines
 */

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#ifdef __cplusplus
extern "C" {
#endif

#warning compatibility defines (do not use)
void dzx7_Turbo(void *src, void *dst);
void dzx7_Standard(void *src, void *dst);

#ifdef __cplusplus
}
#endif

#endif

