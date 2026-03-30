# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Wshadow -Wimplicit-float-conversion -Wimplicit-int-float-conversion -std=c17 -Oz
CXXFLAGS = -Wall -Wextra -Wshadow -Wimplicit-float-conversion -Wimplicit-int-float-conversion -std=c++20 -Oz

HAS_MATH_ERRNO = YES
PREFER_OS_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
