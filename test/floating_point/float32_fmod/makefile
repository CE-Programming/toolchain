# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Wshadow -ffreestanding -Wfloat-conversion -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz -std=c17
CXXFLAGS = -Wall -Wextra -Wshadow -ffreestanding -Wfloat-conversion -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz -std=c++17

HAS_MATH_ERRNO = YES
PREFER_OS_LIBC = NO
PREFER_OS_CRT = NO

# ----------------------------

include $(shell cedev-config --makefile)
