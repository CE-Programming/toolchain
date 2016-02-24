TARGET ?= demo1

#Change ICONC to "ICON" to include a custom icon, and "NICON" to not use an icon
ICONC ?= ICON
DESCRIPTION ?= "Template C Program"

REALWINPATH := $(subst /,\,$(realpath $(1)))
CEDEV ?= $(call REALWINPATH,..\..)
BIN := $(CEDEV)\bin
INCLUDE := $(CEDEV)\include

CC := @ "$(BIN)\eZ80cc"
LD := @ "$(BIN)\eZ80link"
CV := @ "$(BIN)\convhex"
PG := @ "$(BIN)\convpng"
RM := del /f

SOURCES := $(wildcard *.c)
ASMSOURCES := $(wildcard *.asm)
ICONASM := iconc.asm
ifeq ($(ICONC),ICON)
ASMSOURCES := $(wildcard *.asm)
ASMSOURCES += $(ICONASM)
PNG_FLAGS := -c
else
ASMSOURCES = $(filter-out iconc.asm, $(wildcard *.asm))
PNG_FLAGS := -h
endif
OBJECTS := $(SOURCES:%.c=%.obj) $(ASMSOURCES:%.asm=%.obj)
HEADERS := .;$(CEDEV)\include\ce;$(CEDEV)\include\ce\asm;$(CEDEV)\include;$(CEDEV)\include\std;$(CEDEV)\lib\ce;$(CEDEV)\lib\ce\asm
LIBRARIES := $(CEDEV)\lib\std\cdebug.lib $(CEDEV)\lib\std\chelp.lib $(CEDEV)\lib\std\crt.lib $(CEDEV)\lib\std\crtS.lib $(CEDEV)\lib\std\nokernel.lib $(CEDEV)\lib\std\fplib.lib $(CEDEV)\lib\std\fplibS.lib

ASM_FLAGS := \
	-name -define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:eZ80190

CFLAGS :=  \
	-quiet -define:NDEBUG -define:_EZ80190 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:eZ80190 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)" -asm $(ASMSOURCES)

LDFLAGS += GROUP MEMORY = ROM, RAM

empty :=
space := $(empty) $(empty)
comma := ,

all : $(TARGET).8xp

$(TARGET).hex : $(OBJECTS) $(LIBRARIES)
	$(LD) @Linkcmd $@ = $(subst $(space),$(comma),$^) $(LDFLAGS)

%.8xp : %.hex
	$(CV) $(@:%.8xp=%)

%.obj : %.c
	$(PG) $(PNG_FLAGS) $(DESCRIPTION) > nul
	@ cd $(dir $@) && \
	$(CC) $(CFLAGS) $(notdir $<)

%.obj : %.asm
	$(CC) $(CFLAGS) $<

%.obj : %.src
	$(CC) $(CFLAGS) $<

clean :
	$(RM) $(ICONASM) $(OBJECTS:%.obj=%.src) $(OBJECTS) $(TARGET).*

.PHONY : all clean
