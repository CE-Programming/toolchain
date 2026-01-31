/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @author Einar Saukas
 * @brief Optimized (de)compression routines
 */

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stddef.h>

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

/**
 * Decompress a length-prefixed block of LZ4 encoded data.
 *
 * @param[in] dst Uncompressed data destination.
 * @param[in] src Compressed data source.
*/
void lz4_Decompress(void *dst, const void *src);

/**
 * Decompress a raw block of LZ4 encoded data.
 *
 * @param[in] dst Uncompressed data destination.
 * @param[in] src Compressed data source start.
 * @param[in] size Compressed data source size.
 *
 * @returns The uncompressed data size.
*/
size_t lz4_Decompress_Block(void *dst, const void *src, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* COMPRESSION_H */
