//------------------------------------------------------------------------------
// Configuration
//------------------------------------------------------------------------------

/**
 * @remarks don't set this above 40, or there is a chance that
 * frameset will exceed 127 (generating slower code).
 */
#define NANOPRINTF_CONVERSION_BUFFER_SIZE 24

// custom nanoprintf flag to enable/disable long double formatting
#define NANOPRINTF_USE_LONG_DOUBLE_PRECISION 1

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_ALT_FORM_FLAG 1
#define NANOPRINTF_USE_FLOAT_HEX_FORMAT_SPECIFIER 0

#include "nanoprintf_impl.h"
