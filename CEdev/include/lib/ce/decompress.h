#ifndef DECOMPRESS_H
#define DECOMPRESS_H

/**
 * Decompress a block of zx7 encoded data
 */
void dzx7_Standard(void *src, void *dst);

/**
 * Decompress a block of zx7 encoded data fast
 */
void dzx7_Turbo(void *src, void *dst);

#endif
