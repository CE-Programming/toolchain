# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
# Strict floating-point comparisons make the raw program exceed one variable.
# Keep the original comparison expressions and compress this test in both CI modes.
override COMPRESSED = YES

CFLAGS = -Wall -Wextra -Wshadow -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz
CXXFLAGS = -Wall -Wextra -Wshadow -Wimplicit-float-conversion -Wimplicit-int-float-conversion -std=c++20 -Oz

HAS_MATH_ERRNO = YES
PREFER_OS_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
