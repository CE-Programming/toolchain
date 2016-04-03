#----------------------------

#Change TARGET to specify the output program name
#Change ICONC to "ICON" to include a custom icon, and "NICON" to not use an icon. Icons use the palette located in \include\ce\pal, and is named iconc.png in your project's root directory.
#Change DEBUGMODE to "DEBUG" in order to compile debug.h functions in, and "NDEBUG" to not compile debugging functions
#Change DESCRIPTION to modify what is displayed within a compatible shell
#Change ARCHIVED to "YES" to mark the output as archived, and "NO" to not
#Change APPVAR to "YES" to create the file as an AppVar, otherwise "NO" for programs

#----------------------------
TARGET ?= TEMPLATE
DESCRIPTION ?= "Example C program - Template"
DEBUGMODE ?= NDEBUG
ARCHIVED ?= NO
APPVAR ?= NO
#----------------------------

#These directories specify where source and output should go

#----------------------------
SRCDIR := src
OBJDIR := obj
BINDIR := bin
GFXDIR := src/gfx
#----------------------------

#Add shared library names to the L varible, for instance:
# L := graphc fileioc keypadc
L := 

#----------------------------
#Try not to edit anything below these lines unless you know what you are doing
#----------------------------

#----------------------------
empty :=
space := $(empty) $(empty)
comma := ,
TARGETHEX := $(TARGET).hex

ICON_PNG := iconc.png
ICON_ASM := iconc.asm
CSTARTUP_ASM := cstartup.asm
LIBHEADER_ASM := libheader.asm

ICON_OBJ := $(ICON_ASM:%.asm=%.obj)
CSTARTUP_OBJ := $(CSTARTUP_ASM:%.asm=%.obj)
LIBHEADER_OBJ := $(LIBHEADER_ASM:%.asm=%.obj)

LIBHEADER_LOC := $(CEDEV)/include/ce/asm/$(LIBHEADER_ASM)
CSTARTUP_LOC := $(CEDEV)/include/ce/asm/$(CSTARTUP_ASM)
ICON_LOC := .

ALLDIRS := $(sort $(dir $(wildcard $(SRCDIR)/*/)))

BIN = $(call NATIVEPATH,$(CEDEV)/bin)
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH = $(NATIVEPATH)
CEDEV ?= $(realpath ..\..)
CC = "$(BIN)eZ80cc"
AS = "$(BIN)eZ80asm"
LD = "$(BIN)eZ80link"
CV = "$(BIN)convhex"
PG = "$(BIN)convpng"
CD = cd
RM = del /F /Q
CP = copy /Y
NULL = >nul 2>&1
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH = $(subst \,\\,$(shell winepath --windows $(1)))
CEDEV ?= $(realpath ../..)
CC = wine "$(BIN)eZ80cc"
LD = wine "$(BIN)eZ80link"
CV = "$(BIN)convhex_linux"
PG = "$(BIN)convpng_linux"
CD = cd
RM = rm -f
CP = cp -f
NULL = >/dev/null
endif
BIN := $(call NATIVEPATH,$(CEDEV)/bin/)

ifneq ($(ARCHIVED),NO)
CVFLAGS := -a
endif
ifneq ($(APPVAR),NO)
CVFLAGS += -v
TARGETTYPE := $(TARGET).8xv
else
TARGETTYPE := $(TARGET).8xp
endif

ifneq ("$(wildcard $(ICON_PNG))","")
ICONC := ICON
endif

SOURCES := $(call WINPATH,$(foreach dir,$(ALLDIRS),$(wildcard $(dir)*.c)))
ASMSOURCES := $(call WINPATH,$(foreach dir,$(ALLDIRS),$(wildcard $(dir)*.asm)))
SOURCES := $(call WINPATH,$(addprefix $(CURDIR)/,$(SOURCES)))
ASMSOURCES := $(call WINPATH,$(addprefix $(CURDIR)/,$(ASMSOURCES)))

OBJECTS := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:%.c=%.obj)))
OBJECTS += $(addprefix $(OBJDIR)/,$(notdir $(ASMSOURCES:%.asm=%.obj)))
OBJECTS += $(OBJDIR)/$(CSTARTUP_OBJ)

ifeq ($(ICONC),ICON)
ICON_CONV := $(PG) -c $(DESCRIPTION) && $(CP) $(ICON_ASM) $(OBJDIR) $(NULL) && $(RM) $(ICON_ASM) $(NULL)
OBJECTS += $(OBJDIR)/$(ICON_OBJ)
else
ICON_CONV :=
endif

ifdef L
OBJECTS += $(OBJDIR)/$(LIBHEADER_OBJ)
LIBLOC := $(foreach var,$(L),lib/ce/$(var))
LIBS := $(call WINPATH,$(foreach var,$(L),$(CEDEV)/lib/ce/$(var)/$(var).asm))
OBJECTS += $(OBJDIR)/$(notdir $(LIBS:%.asm=%.obj))
endif

LIBS := $(subst $(space),;,$(LIBS))
HEADERS := $(subst $(space),;,$(call WINPATH,. $(ALLDIRS) $(addprefix $(CEDEV)/,. include/ce/asm include/ce/c include include/std lib/std/ce lib/ce $(LIBLOC))))
LIBRARIES := $(call WINPATH,$(addprefix $(CEDEV)/lib/std/,ce/ctice.lib ce/cdebug.lib chelp.lib crt.lib crtS.lib nokernel.lib fplib.lib fplibS.lib))
LIBRARIES += $(call WINPATH,$(foreach var,$(L),$(CEDEV)/lib/ce/$(var)/$(var).lib))

ASM_FLAGS := \
	-define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:EZ80F91

CFLAGS := \
	-quiet -define:$(DEBUGMODE) -define:_EZ80F91 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:EZ80F91 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)"

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
LIBNUM := $(words $(L))
LDLIBS := locate .$(word 1,$(L))_header at (top of .libs)+1
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
ifneq ($(LIBNUM),10)
LDLIBS += locate .$(word 11,$(L))_header at (top of .$(word 10,$(L))+1)
LDLIBS += locate .$(word 11,$(L)) at (top of .$(word 11,$(L))_header)+1
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
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

all : $(BINDIR)/$(TARGETTYPE)

$(BINDIR)/$(TARGETHEX) : $(OBJECTS) $(LIBRARIES)
	@$(LD) $(LDFLAGS) $@ = "$(subst $(space),$(comma),$(call WINPATH,$^))" || @$(RM) $(BINDIR)/$(TARGETTYPE) $(BINDIR)/$(TARGETHEX) $(NULL)

%.8xv : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xv=%)

%.8xp : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xp=%)

$(OBJDIR)/$(ICON_OBJ) : $(ICON_PNG)
	@$(ICON_CONV) && \
	@$(CD) $(OBJDIR) && \
	$(AS) $(ASM_FLAGS) $(ICON_ASM)
	
$(OBJDIR)/%.obj : $(SRCDIR)/%.asm
	@$(CD) $(OBJDIR) && \
        $(AS) $(ASM_FLAGS) $(call WINPATH,$(addprefix $(CURDIR)/,$<))

$(OBJDIR)/%.obj : $(SRCDIR)/%.c
	@$(CD) $(OBJDIR) && \
	 $(CC) $(CFLAGS) $(call WINPATH,$(addprefix $(CURDIR)/,$<))

$(OBJDIR)/%.obj : $(GFXDIR)/%.c
	@$(CD) $(OBJDIR) && \
	 $(CC) $(CFLAGS) $(call WINPATH,$(addprefix $(CURDIR)/,$<))

$(OBJDIR)/$(CSTARTUP_OBJ) : $(CSTARTUP_LOC)
	@$(CD) $(OBJDIR) && \
	$(AS) $(ASM_FLAGS) $(call WINPATH,$<)

$(OBJDIR)/$(LIBHEADER_OBJ) : $(LIBHEADER_LOC)
	@$(CD) $(OBJDIR) && \
	$(AS) $(ASM_FLAGS) $(call WINPATH,$<)
	@$(CD) $(OBJDIR) && \
	$(AS) $(ASM_FLAGS) $(LIBS)

clean :
	@$(RM) $(OBJDIR)\* $(BINDIR)\* $(NULL)

.PHONY : all clean
