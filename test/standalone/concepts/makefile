# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Wconversion -Wformat=2 -std=c17 -Oz
CXXFLAGS = -Wall -Wextra -Wconversion -Wformat=2 -std=c++20 -Oz

HAS_MATH_ERRNO = YES
PREFER_CE_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
