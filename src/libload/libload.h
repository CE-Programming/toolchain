#ifndef LIBLOAD_H
#define LIBLOAD_H

/**
 * Verifies that a LibLoad library has been successfully relocated and loaded.
 * This function must be called before using any optionally loaded libraries.
 *
 * @param name On-calc name of the library, e.g. `GRAPHX`. This should
 * <b>not</b> be quoted.
 * @returns \c false if the library is not loaded.
 * @note See the Makefile option `LIBLOAD_OPTIONAL` for more information.
 */
#define libload_IsLibLoaded(name) __extension__({         \
        extern const unsigned char libload_Library_##name \
            __asm__("lib."#name);                         \
        libload_Library_##name;                           \
    })

#endif
