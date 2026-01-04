# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -std=c17 -Oz
CXXFLAGS = -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -std=c++17 -Oz

PREFER_CE_LIBC = NO

# ----------------------------

include $(shell cedev-config --makefile)
