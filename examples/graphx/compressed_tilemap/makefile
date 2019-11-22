# ----------------------------
# Program Options
# ----------------------------

NAME         ?= DEMO
ICON         ?= iconc.png
DESCRIPTION  ?= "C SDK Demo"
COMPRESSED   ?= NO
ARCHIVED     ?= NO

# ----------------------------
# Compile Options
# ----------------------------

OPT_MODE     ?= -Oz
EXTRA_CFLAGS ?= -Wall -Wextra

# ----------------------------
# Debug Options
# ----------------------------

OUTPUT_MAP   ?= NO

include $(CEDEV)/include/.makefile

tilemap: src/tilemap/tilemap.csv
	cd src && cd tilemap && convcsv --format c --compress zx7 --name tilemap_map_compressed --input tilemap.csv --output tilemap.c
