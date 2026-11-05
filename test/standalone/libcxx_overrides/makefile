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
PREFER_OS_LIBC = NO

# The override detector runs inside the separately compiled libc++ archive.
# Combining weak and strong definitions in one LTO module discards the weak body
# before the assembler can bind its local alias. Match the library build here.
LTO = NO

# ----------------------------

include $(shell cedev-config --makefile)
