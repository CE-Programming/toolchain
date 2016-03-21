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
DESCRIPTION ?= "Example C program - Demo 0"
ARCHIVED ?= NO
APPVAR ?= NO
#----------------------------

#Add shared library names to the L varible, i.e.
# L := graphc fileioc keypadc

#----------------------------

empty :=
space := $(empty) $(empty)
comma := ,
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
RM = rm -f
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
ASMSOURCES += $(call WINPATH,$(CEDEV)/include/ce/asm/cstartup.asm)
ifdef L
ASMSOURCES += $(call WINPATH,$(CEDEV)/include/ce/asm/libheader.asm)
OBJECTS += libheader.obj
endif
LIBLOC := $(foreach var,$(L),lib/ce/$(var))
LIBS := $(call WINPATH,$(foreach var,$(L),$(CEDEV)/lib/ce/$(var)/$(var).asm))
ASMSOURCES += $(LIBS)
OBJECTS += $(notdir $(LIBS:%.asm=%.obj))
OBJECTS += cstartup.obj
HEADERS := $(subst $(space),;,$(call WINPATH,. $(addprefix $(CEDEV)/,. include/ce/asm include/ce/c include include/std lib/std/ce lib/ce $(LIBLOC))))
LIBRARIES := $(call WINPATH,$(addprefix $(CEDEV)/lib/std/,ce/ctice.lib ce/cdebug.lib chelp.lib crt.lib crtS.lib nokernel.lib fplib.lib fplibS.lib))
LIBRARIES += $(call WINPATH,$(foreach var,$(L),$(CEDEV)/lib/ce/$(var)/$(var).lib))

ASM_FLAGS := \
	-define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:EZ80F91

CFLAGS := \
	-quiet -define:$(DEBUGMODE) -define:_EZ80F91 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:EZ80F91 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)" -asm $(ASMSOURCES)

LDFLAGS := \
	-FORMAT=INTEL32 \
	-map -maxhexlen=64 -quiet -warnoverlap -xref -unresolved=fatal \
	-sort ADDRESS=ascending -warn -NOdebug -NOigcase \
	define __copy_code_to_ram = 0 \
	range rom $$000000 : $$FFFFFF \
	range ram $$D00000 : $$FFFFFF \
	range bss $$D031F6 : $$D13FD6 \
	change code is ram \
	change data is ram \
	change text is ram \
	change strsect is text \
	define __low_bss = base of bss \
	define __len_bss = length of bss \
	define __heaptop = (highaddr of bss) \
	define __heapbot = (top of bss)+1 \
	define __stack = $$D1A87E \
	locate .header at $$D1A87F \
	locate .icon at (top of .header)+1 \
	locate .launcher at (top of .icon)+1 \
	locate .libs at (top of .launcher)+1

ifdef L
#Define library absolute location
LIBNUM := $(words $(L))
LDLIBS := locate .$(word 1,$(L))_header at (top of .libs)+1
#Make library headers relative to library functions
LDLIBS += locate .$(word 1,$(L)) at (top of .$(word 1,$(L))_header)+1
ifneq ($(LIBNUM),1)
LDLIBS += locate .$(word 2,$(L))_header at (top of .$(word 1,$(L))+1)
LDLIBS += locate .$(word 2,$(L)) at (top of .$(word 2,$(L))_header)+1
ifneq ($(LIBNUM),2)
LDLIBS += locate .$(word 3,$(L))_header at (top of .$(word 2,$(L))+1)
LDLIBS += locate .$(word 3,$(L)) at (top of .$(word 3,$(L))_header)+1
ifneq ($(LIBNUM),3)
LDLIBS += locate .$(word 4,$(L))_header at (top of .$(word 3,$(L))+1)
LDLIBS += locate .$(word 4,$(L)) at (top of .$(word 4,$(L))_header)+1
ifneq ($(LIBNUM),4)
LDLIBS += locate .$(word 5,$(L))_header at (top of .$(word 4,$(L))+1)
LDLIBS += locate .$(word 5,$(L)) at (top of .$(word 5,$(L))_header)+1
ifneq ($(LIBNUM),5)
LDLIBS += locate .$(word 6,$(L))_header at (top of .$(word 5,$(L))+1)
LDLIBS += locate .$(word 6,$(L)) at (top of .$(word 6,$(L))_header)+1
ifneq ($(LIBNUM),6)
LDLIBS += locate .$(word 7,$(L))_header at (top of .$(word 6,$(L))+1)
LDLIBS += locate .$(word 7,$(L)) at (top of .$(word 7,$(L))_header)+1
ifneq ($(LIBNUM),7)
LDLIBS += locate .$(word 8,$(L))_header at (top of .$(word 7,$(L))+1)
LDLIBS += locate .$(word 8,$(L)) at (top of .$(word 8,$(L))_header)+1
ifneq ($(LIBNUM),8)
LDLIBS += locate .$(word 9,$(L))_header at (top of .$(word 8,$(L))+1)
LDLIBS += locate .$(word 9,$(L)) at (top of .$(word 9,$(L))_header)+1
ifneq ($(LIBNUM),9)
LDLIBS += locate .$(word 10,$(L))_header at (top of .$(word 9,$(L))+1)
LDLIBS += locate .$(word 10,$(L)) at (top of .$(word 10,$(L))_header)+1
endif
endif
endif
endif
endif
endif
endif
endif
endif
#Chain each library one after another
LDFLAGS += $(LDLIBS)
LDLAST := .$(word $(words $(L)),$(L))
else
LDLAST := .libs
endif

LDFLAGS += \
	locate .startup at (top of $(LDLAST))+1 \
	locate code at (top of .startup)+1 \
	locate data at (top of code)+1 \
	locate text at (top of data)+1

all : $(TARGETTYPE)

$(TARGETHEX) : $(OBJECTS) $(LIBRARIES)
	@$(LD) $(LDFLAGS) $@ = "$(subst $(space),$(comma),$(call WINPATH,$^))" || @$(RM) $(TARGETTYPE) $(TARGETHEX)

%.8xv : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xv=%)
	
%.8xp : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xp=%)

%.obj : %.c
	@$(PG) $(PNG_FLAGS) $(DESCRIPTION)
	@cd $(dir $@) && \
	 $(CC) $(CFLAGS) $(notdir $<)

clean :
	@$(RM) $(ICONASM) $(OBJECTS) $(OBJECTS:%.obj=%.src) $(TARGETTYPE) $(TARGETHEX) $(TARGET).map

.PHONY : all clean