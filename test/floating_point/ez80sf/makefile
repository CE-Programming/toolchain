# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

COMMON_FLAGS = -Wall -Wextra -Wshadow -Wformat=2 -Wconversion -Wimplicit-float-conversion -Wimplicit-int-float-conversion
COMMON_FLAGS += -Oz -ffreestanding

CFLAGS = ${COMMON_FLAGS} -std=c17
CXXFLAGS = ${COMMON_FLAGS} -std=c++20

PREFER_OS_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
