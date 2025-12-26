# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -ffreestanding -Wformat=2 -Wshadow -Oz
CXXFLAGS = -Wall -Wextra -ffreestanding -Wformat=2 -Wshadow -Oz

HAS_MATH_ERRNO = YES
PREFER_CE_LIBC = NO
HAS_PRINTF = YES

# ----------------------------

include $(shell cedev-config --makefile)
