TARGET ?= demo1

#Change ICONC to "ICON" to include a custom icon, and "NICON" to not use an icon
ICONC ?= NICON
DESCRIPTION ?= "Demo C Program"
ARCHIVED ?= NO
APPVAR ?= NO

empty :=
space := $(empty) $(empty)
comma := ,
suffix := .asm$(empty) $(empty)
TARGETHEX = $(TARGET).hex
TARGET8XP = $(TARGET).8xp

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
WINPATH = $(shell winepath --windows $(1))
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
ASMSOURCES += $(call NATIVEPATH,$(addprefix $(CEDEV)/include/ce/asm/,cstartup.asm))
ifdef L
ASMSOURCES += $(call NATIVEPATH,$(addprefix $(CEDEV)/include/ce/asm/,libheader.asm))
OBJECTS += libheader.obj
endif
LIBS := $(call NATIVEPATH,$(addprefix $(CEDEV)/lib/ce/,$(addsuffix $(suffix),$(L))))
ASMSOURCES += $(LIBS)
OBJECTS += $(notdir $(LIBS:%.asm=%.obj))
OBJECTS += cstartup.obj
HEADERS := $(subst $(space),;,$(call WINPATH,$(realpath .) $(addprefix $(CEDEV)/,include/ce/asm include/ce/c include include/std lib/std/ce lib/ce)))
LIBRARIES := $(call NATIVEPATH,$(addprefix $(CEDEV)/lib/std/,ce/ctice.lib ce/cdebug.lib chelp.lib crt.lib crtS.lib nokernel.lib fplib.lib fplibS.lib))

ASM_FLAGS := \
	-define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:EZ80F91

CFLAGS :=  \
	-quiet -define:NDEBUG -define:_EZ80F91 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:EZ80F91 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)" -asm $(ASMSOURCES)

LDFLAGS += GROUP MEMORY = ROM, RAM

all : $(TARGET8XP)

$(TARGETHEX) : $(OBJECTS) $(LIBRARIES)
	@$(LD) @Linkcmd $@ = "$(subst $(space),$(comma),$(call WINPATH,$^))" $(LDFLAGS) || @$(RM) $(OBJECTS) $(TARGET).hex
	@$(RM) $(ICONASM)
	@$(RM) $(OBJECTS)

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
	@$(RM) $(ICONASM) $(OBJECTS:%.obj=%.src) $(OBJECTS) $(TARGET).*

.PHONY : all clean