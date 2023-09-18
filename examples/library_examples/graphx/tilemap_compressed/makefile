# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

EXTRA_C_SOURCES = src/tilemap/tilemap.c

# ----------------------------

include $(shell cedev-config --makefile)

# rule to convert CSV tilemap to C source file
src/tilemap/tilemap.c: src/tilemap/tilemap.csv
	@convbin -j csv -i $< -k c -c zx7 -o $@ -n tilemap_map_compressed

