# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

WARN_FLAGS = -Wall -Wextra -Wshadow -Wfloat-conversion -Wimplicit-float-conversion -Wimplicit-int-float-conversion
OPT_FLAGS = -Oz

CFLAGS = $(WARN_FLAGS) $(OPT_FLAGS) -std=c11
CXXFLAGS = $(WARN_FLAGS) $(OPT_FLAGS) -std=c++11

HAS_MATH_ERRNO = YES
PREFER_OS_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
