#----------------------------

#Change TARGET to specify the output program name
#Change DEBUGMODE to "DEBUG" in order to compile debug.h functions in, and "NDEBUG" to not compile debugging functions
#Change ARCHIVED to "YES" to mark the output as archived, and "NO" to not
#Change APPVAR to "YES" to create the file as an AppVar, otherwise "NO" for programs
#Change ICONPNG to change the name of the png file that should be made into the icon
#Change DESCRIPTION to modify what is displayed within a compatible shell (Not compiled in if icon is not present)

#----------------------------
TARGET ?= GRAPHX8
DEBUGMODE ?= NDEBUG
ARCHIVED ?= NO
APPVAR ?= NO
#----------------------------
ICONPNG ?= iconc.png
DESCRIPTION ?= "C Graphics Demo 8"
#----------------------------

#Add shared library names to the L varible, for instance:
# L := graphx fileioc keypadc
L := graphx

#These directories specify where source and output should go

#----------------------------
SRCDIR := src
OBJDIR := obj
BINDIR := bin
GFXDIR := src/gfx
#----------------------------

#This changes the location of compiled output (Advanced)

#----------------------------
BSSHEAP_LOW := D031F6
BSSHEAP_HIGH := D13FD6
STACK_HIGH := D1A87E
INIT_LOC := D1A87F
#----------------------------

#Use the (slower) OS embedded functions (Advanced)

#----------------------------
USE_FLASH_FUNCTIONS ?= YES
#----------------------------

include $(CEDEV)/bin/main_makefile
