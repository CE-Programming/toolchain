# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= DEMO
COMPRESSED  ?= NO
ICON        ?= iconc.png
DESCRIPTION ?= "C SDK Demo"

# ----------------------------

include $(CEDEV)/include/.makefile

tilemap: src/tilemap/tilemap.csv
	cd src && cd tilemap && convcsv --format c --name tilemap_map --input tilemap.csv --output tilemap.c
