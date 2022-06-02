/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @author Einar Saukas
 * @brief Optimized (de)compression routines
 */

#ifndef COMPRESSION_H
#define COMPRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Decompress a block of ZX7 encoded data.
 *
 * @param[in] dst Uncompressed data destination.
 * @param[in] src Compressed data source.
*/
void zx7_Decompress(void *dst, const void *src);

/**
 * Decompress a block of ZX0 encoded data.
 *
 * @param[in] dst Uncompressed data destination.
 * @param[in] src Compressed data source.
*/
void zx0_Decompress(void *dst, const void *src);

#ifdef __cplusplus
}
#endif

#endif

