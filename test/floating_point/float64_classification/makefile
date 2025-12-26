# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Wshadow -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz -std=c11
CXXFLAGS = -Wall -Wextra -Wshadow -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz -std=c++11

HAS_MATH_ERRNO = YES
PREFER_CE_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
