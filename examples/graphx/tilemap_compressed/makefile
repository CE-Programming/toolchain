# ----------------------------
# Program Options
# ----------------------------

NAME         ?= DEMO
ICON         ?= icon.png
DESCRIPTION  ?= "CE C SDK Demo"
MAIN_ARGS    ?= NO
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
	cd src && cd tilemap && convbin --iformat csv -i tilemap.csv --compress zx7 -o tilemap.c --oformat c --name tilemap_map_compressed
