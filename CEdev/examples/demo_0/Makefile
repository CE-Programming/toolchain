TARGET ?= demo0

#Change ICONC to "ICON" to include a custom icon, and "NICON" to not use an icon
ICONC ?= ICON
DESCRIPTION ?= "Demo C Program"

empty :=
space := $(empty) $(empty)
comma := ,

BIN = $(call NATIVEPATH,$(CEDEV)/bin)
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH = $(NATIVEPATH)
CEDEV ?= $(realpath ..\..)
CC = "$(BIN)eZ80cc"
LD = "$(BIN)eZ80link"
CV = "$(BIN)convhex"
PG = "$(BIN)ConvPNG" >nul
RM = del /f 2>nul
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH = $(shell winepath --windows $(1))
CEDEV ?= $(realpath ../..)
CC = wine "$(BIN)eZ80cc"
LD = wine "$(BIN)eZ80link"
CV = "$(BIN)convhex"
PG = "$(BIN)ConvPNG" >/dev/null
RM = rm --force
endif
BIN = $(call NATIVEPATH,$(CEDEV)/bin/)

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
HEADERS := $(subst $(space),;,$(call WINPATH,$(realpath .) $(addprefix $(CEDEV)/,include/ce include/ce/asm include include/std lib/ce lib/ce/asm)))
LIBRARIES := $(call NATIVEPATH,$(addprefix $(CEDEV)/lib/std/,cdebug.lib chelp.lib crt.lib crtS.lib nokernel.lib fplib.lib fplibS.lib))

ASM_FLAGS := \
	-name -define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:eZ80190

CFLAGS :=  \
	-quiet -define:NDEBUG -define:_EZ80190 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:eZ80190 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)" -asm $(ASMSOURCES)

LDFLAGS += GROUP MEMORY = ROM, RAM

all : $(TARGET).8xp

$(TARGET).hex : $(OBJECTS) $(LIBRARIES)
	@$(LD) @Linkcmd $@ = "$(subst $(space),$(comma),$(call WINPATH,$^))" $(LDFLAGS) || @$(RM) $(TARGET).hex

%.8xp : %.hex
	@$(CV) $(@:%.8xp=%)

%.obj : %.c
	@$(PG) $(PNG_FLAGS) $(DESCRIPTION)
	@cd $(dir $@) && \
	 $(CC) $(CFLAGS) $(notdir $<)

%.obj : %.asm
	@$(CC) $(CFLAGS) $<

%.obj : %.src
	@$(CC) $(CFLAGS) $<

clean :
	@$(RM) $(ICONASM) $(OBJECTS:%.obj=%.src) $(OBJECTS) $(TARGET).*

.PHONY : all clean