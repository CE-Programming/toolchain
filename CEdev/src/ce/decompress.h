/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @brief Optimized decompression routines
 */

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

/**
 * Decompress a block of zx7 encoded data
 *
 * @param src Pointer to compressed source block
 * @param dst Pointer to destination block
 */
void dzx7_Standard(void *src, void *dst);

/**
 * Decompress a block of zx7 encoded data fast
 *
 * @param src Pointer to compressed source block
 * @param dst Pointer to destination block
 */
void dzx7_Turbo(void *src, void *dst);

#endif
