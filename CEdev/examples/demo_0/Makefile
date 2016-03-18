#----------------------------

#Change TARGET to specify the output program name
#Change ICONC to "ICON" to include a custom icon, and "NICON" to not use an icon. Icons use the palette located in \include\ce\pal, and is named iconc.png in your project's root directory.
#Change DEBUGMODE to "DEBUG" in order to compile debug.h functions in, and "NDEBUG" to not compile debugging functions
#Change DESCRIPTION to modify what is displayed within a compatible shell
#Change ARCHIVED to "YES" to mark the output as archived, and "NO" to not
#Change APPVAR to "YES" to create the file as an AppVar, otherwise "NO" for programs

#----------------------------
TARGET ?= DEMO0
ICONC ?= ICON
DEBUGMODE ?= NDEBUG
DESCRIPTION ?= "CE C SDK program - Demo 0"
ARCHIVED ?= NO
APPVAR ?= NO
#----------------------------

#Add shared library names to the L varible, i.e.
# L := graphc fileioc keypadc

#----------------------------

empty :=
space := $(empty) $(empty)
comma := ,
suffix := .asm$(empty) $(empty)
TARGETHEX := $(TARGET).hex

BIN = $(call NATIVEPATH,$(CEDEV)/bin)
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH = $(NATIVEPATH)
CEDEV ?= $(realpath ..\..)
CC = "$(BIN)eZ80cc"
LD = "$(BIN)eZ80link"
CV = "$(BIN)convhex"
PG = "$(BIN)convpng" >nul
RM = del /f 2>nul
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH = $(subst \,\\,$(shell winepath --windows $(1)))
CEDEV ?= $(realpath ../..)
CC = wine "$(BIN)eZ80cc"
LD = wine "$(BIN)eZ80link"
CV = wine "$(BIN)convhex"
PG = wine "$(BIN)convpng" >/dev/null
RM = rm --force
endif
BIN = $(call NATIVEPATH,$(CEDEV)/bin/)

ifneq ($(ARCHIVED),NO)
CVFLAGS := -a
endif
ifneq ($(APPVAR),NO)
CVFLAGS += -v
TARGETTYPE := $(TARGET).8xv
else
TARGETTYPE := $(TARGET).8xp
endif

SOURCES := $(wildcard *.c)
ASMSOURCES := $(wildcard *.asm)
ICONASM := iconc.asm
ifeq ($(ICONC),ICON)
ASMSOURCES := $(wildcard *.asm)
ASMSOURCES += $(ICONASM)
PNG_FLAGS := -c
else
ASMSOURCES := $(filter-out iconc.asm, $(wildcard *.asm))
PNG_FLAGS := -h
endif
OBJECTS := $(SOURCES:%.c=%.obj) $(ASMSOURCES:%.asm=%.obj)
ASMSOURCES += $(call WINPATH,$(addprefix $(CEDEV)/include/ce/asm/,cstartup.asm))
ifdef L
ASMSOURCES += $(call WINPATH,$(addprefix $(CEDEV)/include/ce/asm/,libheader.asm))
OBJECTS += libheader.obj
endif
LIBS := $(call WINPATH,$(addprefix $(CEDEV)/lib/ce/,$(addsuffix $(suffix),$(L))))
ASMSOURCES += $(LIBS)
OBJECTS += $(notdir $(LIBS:%.asm=%.obj))
OBJECTS += cstartup.obj
HEADERS := $(subst $(space),;,$(call WINPATH,. $(addprefix $(CEDEV)/,. include/ce/asm include/ce/c include include/std lib/std/ce lib/ce)))
LIBRARIES := $(call WINPATH,$(addprefix $(CEDEV)/lib/std/,ce/ctice.lib ce/cdebug.lib chelp.lib crt.lib crtS.lib nokernel.lib fplib.lib fplibS.lib))

ASM_FLAGS := \
	-define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:EZ80F91

CFLAGS :=  \
	-quiet -define:DEBUG -define:_EZ80F91 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:EZ80F91 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)" -asm $(ASMSOURCES)

LDFLAGS += GROUP MEMORY = ROM, RAM

all : $(TARGETTYPE)

$(TARGETHEX) : $(OBJECTS) $(LIBRARIES)
	@$(LD) @Linkcmd $@ = "$(subst $(space),$(comma),$(call WINPATH,$^))" $(LDFLAGS) || @$(RM) $(TARGETTYPE) $(TARGETHEX)

%.8xv : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xv=%)
	
%.8xp : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xp=%)

%.obj : %.c
	@$(PG) $(PNG_FLAGS) $(DESCRIPTION)
	@cd $(dir $@) && \
	 $(CC) $(CFLAGS) $(notdir $<)

%.obj : %.asm
	@$(CC) $(CFLAGS) $<

%.obj : %.src
	@$(CC) $(CFLAGS) $<

clean :
	@$(RM) $(ICONASM) $(OBJECTS) $(OBJECTS:%.obj=%.src) $(TARGETTYPE) $(TARGETHEX) $(TARGET).map

.PHONY : all clean