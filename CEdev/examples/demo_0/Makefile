#----------------------------

#Change TARGET to specify the output program name
#Change DEBUGMODE to "DEBUG" in order to compile debug.h functions in, and "NDEBUG" to not compile debugging functions
#Change ARCHIVED to "YES" to mark the output as archived, and "NO" to not
#Change APPVAR to "YES" to create the file as an AppVar, otherwise "NO" for programs
#Change ICONPNG to change the name of the png file that should be made into the icon
#Change DESCRIPTION to modify what is displayed within a compatible shell (Not compiled in if icon is not present)

#----------------------------
TARGET ?= DEMO0
DEBUGMODE ?= NDEBUG
ARCHIVED ?= NO
APPVAR ?= NO
#----------------------------
ICONPNG := iconc.png
DESCRIPTION ?= "C Toolchain Demo 0"
#----------------------------

#Add shared library names to the L varible, for instance:
# L := graphc fileioc keypadc
L := 

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

#----------------------------
#Try not to edit anything below these lines unless you know what you are doing
#----------------------------

#----------------------------

#Define some common makefile things
empty :=
space := $(empty) $(empty)
comma := ,
CD = cd
RM = del /F /Q
CP = copy /Y
NULL = >nul 2>&1

#Generate the default names for input and object files
TARGETHEX := $(TARGET).hex
ICON_ASM := iconc.asm
CSTARTUP_ASM := cstartup.asm
LIBHEADER_ASM := libheader.asm

#Objects
ICON_OBJ := $(ICON_ASM:%.asm=%.obj)
CSTARTUP_OBJ := $(CSTARTUP_ASM:%.asm=%.obj)
LIBHEADER_OBJ := $(LIBHEADER_ASM:%.asm=%.obj)

#Get the locations of the startup modules and LibLoad modules
LIBHEADER_LOC := $(CEDEV)/include/ce/asm/$(LIBHEADER_ASM)
CSTARTUP_LOC := $(CEDEV)/include/ce/asm/$(CSTARTUP_ASM)

#Find all the directories in the source input
ALLDIRS := $(sort $(dir $(wildcard $(SRCDIR)/*/)))

#Assume Windows; it is a simple matter to run make under wine
NATIVEPATH = $(subst /,\,$(1))
WINPATH = $(NATIVEPATH)
CEDEV ?= $(realpath ..\..)

#Locations of needed compiling/assembling/linking programs
CC = "$(BIN)eZ80cc"
AS = "$(BIN)eZ80asm"
LD = "$(BIN)eZ80link"
CV = "$(BIN)convhex"
PG = "$(BIN)convpng"
BIN := $(call NATIVEPATH,$(CEDEV)/bin/)

#Determine if output should be archived or an AppVar
ifneq ($(ARCHIVED),NO)
CVFLAGS := -a
endif
ifneq ($(APPVAR),NO)
CVFLAGS += -v
TARGETTYPE := $(TARGET).8xv
else
TARGETTYPE := $(TARGET).8xp
endif
TARGETMAP := $(TARGET).map

#Find all of the available C and ASM files (Remeber, you can create C <-> assembly routines easily this way)
SOURCES := $(call WINPATH,$(foreach dir,$(ALLDIRS),$(wildcard $(dir)*.c)))
ASMSOURCES := $(call WINPATH,$(foreach dir,$(ALLDIRS),$(wildcard $(dir)*.asm)))

#Figure out what the names of the sources will become once made into objects
OBJECTS := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:%.c=%.obj)))
OBJECTS += $(addprefix $(OBJDIR)/,$(notdir $(ASMSOURCES:%.asm=%.obj)))
OBJECTS += $(OBJDIR)/$(CSTARTUP_OBJ)

#Check if there is an icon present that we can convert; if so, generate a recipe to build it properly
ifneq ("$(wildcard $(ICON_PNG))","")
ICON_CONV := $(PG) -c $(ICON_PNG)$(comma)$(DESCRIPTION) && \
             $(CP) $(ICON_ASM) $(OBJDIR) $(NULL) && \
	     $(RM) $(ICON_ASM) $(NULL)
OBJECTS += $(OBJDIR)/$(ICON_OBJ)
ICONC := ICON
else
ICON_CONV :=
endif

#Are there any shared libraries that we need to find? If so, add in the proper objects and sources and header files
ifdef L
LIBLOC := $(foreach var,$(L),lib/ce/$(var))
LIBS := $(call WINPATH,$(foreach var,$(L),$(CEDEV)/lib/ce/$(var)/$(var).asm))
OBJECTS += $(addprefix $(OBJDIR)/,$(notdir $(LIBS:%.asm=%.obj)))
OBJECTS += $(OBJDIR)/$(LIBHEADER_OBJ)
endif

#Define the nesassary headers, along with any the user may have defined, where modification should just trigger a build
USERHEADERS := $(call WINPATH,$(foreach dir,$(ALLDIRS),$(wildcard $(dir)*.h)))
HEADERS := $(subst $(space),;,$(call WINPATH,. $(ALLDIRS) $(addprefix $(CEDEV)/,. include/ce/asm include/ce/c include include/std lib/std/ce lib/ce $(LIBLOC))))
LIBRARIES := $(call WINPATH,$(addprefix $(CEDEV)/lib/std/,ce/ctice.lib ce/cdebug.lib chelp.lib crt.lib crtS.lib nokernel.lib fplib.lib fplibS.lib))
LIBRARIES += $(call WINPATH,$(foreach var,$(L),$(CEDEV)/lib/ce/$(var)/$(var).lib))

#Define the assembler flags used by the Zilog assembler
ASM_FLAGS := \
	-define:_EZ80=1 -define:_SIMULATE=1 -define:$(ICONC) -include:$(HEADERS) -NOlist -NOlistmac \
	-pagelen:250 -pagewidth:132 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:EZ80F91

#Define the C flags used by the Zilog compiler
CFLAGS := \
	-quiet -define:$(DEBUGMODE) -define:_EZ80F91 -define:_EZ80 -define:$(ICONC) -define:_SIMULATE -NOlistinc -NOmodsect -cpu:EZ80F91 -keepasm \
	-optspeed -NOreduceopt -NOgenprintf -stdinc:"$(HEADERS)" -usrinc:"." -NOdebug \
	-asmsw:"$(ASM_FLAGS)"

#This is a giant mess, but basically it is just repeated code to properly align all of the nesasary libraries and
#their header information. Kind of annoying, but this is the only certain way ZDS is able to organize things properly
#Currently 11 libraries are supported; more can be added later if needed (probably not)
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
LDLAST := .$(word $(words $(L)),$(L))
else
LDLAST := .libs
endif

#These are the linker flags, basically organized to properly set up the enviornment
LDFLAGS := \
	-FORMAT=INTEL32 \
	-map -maxhexlen=64 -quiet -warnoverlap -xref -unresolved=fatal \
	-sort ADDRESS=ascending -warn -NOdebug -NOigcase \
	define __copy_code_to_ram = 0 \
	range rom $$000000 : $$FFFFFF \
	range ram $$D00000 : $$FFFFFF \
	range bss $$$(BSSHEAP_LOW) : $$$(BSSHEAP_HIGH) \
	change code is ram \
	change data is ram \
	change text is ram \
	change strsect is text \
	define __low_bss = base of bss \
	define __len_bss = length of bss \
	define __heaptop = (highaddr of bss) \
	define __heapbot = (top of bss)+1 \
	define __stack = $$$(STACK_HIGH) \
	locate .header at $$$(INIT_LOC) \
	locate .icon at (top of .header)+1 \
	locate .launcher at (top of .icon)+1 \
	locate .libs at (top of .launcher)+1 \
	locate .startup at (top of $(LDLAST))+1 \
	locate code at (top of .startup)+1 \
	locate data at (top of code)+1 \
	locate text at (top of data)+1 \
	$(LDLIBS)

#The rules to build all of the different sorts of files

#This rule is trigged to build everything
all : $(BINDIR)/$(TARGETTYPE)

#This rule builds the Intel HEX file
$(BINDIR)/$(TARGETHEX) : $(OBJECTS) $(LIBRARIES) $(USERHEADERS)
	@$(LD) $(LDFLAGS) $@ = "$(subst $(space),$(comma),$(call WINPATH,$^))"

#These rules use ConvHEX to convert the Intel HEX file to a calculator format
%.8xv : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xv=%)
%.8xp : %.hex
	@$(CV) $(CVFLAGS) $(@:%.8xp=%)

#This rule handles conversion of the icon, if it is ever updated
$(OBJDIR)/$(ICON_OBJ) : $(ICON_PNG)
	@$(ICON_CONV) && \
	@$(CD) $(OBJDIR) && \
	@$(AS) $(ASM_FLAGS) $(ICON_ASM)

#This rule builds the assembly files and places them in the object directory
$(OBJDIR)/%.obj : $(SRCDIR)/%.asm
	@$(CD) $(OBJDIR) && \
	@$(AS) $(ASM_FLAGS) $(call WINPATH,$(addprefix $(CURDIR)/,$<))

#These rules compile the source files into object files
$(OBJDIR)/%.obj : $(SRCDIR)/%.c
	@$(CD) $(OBJDIR) && \
	@$(CC) $(CFLAGS) $(call WINPATH,$(addprefix $(CURDIR)/,$<))

$(OBJDIR)/%.obj : $(GFXDIR)/%.c
	@$(CD) $(OBJDIR) && \
	@$(CC) $(CFLAGS) $(call WINPATH,$(addprefix $(CURDIR)/,$<))
	
#This rule builds the standard startup module (Which is nice, because then it is completely customizable)
$(OBJDIR)/$(CSTARTUP_OBJ) : $(CSTARTUP_LOC)
	@$(CD) $(OBJDIR) && \
	@$(AS) $(ASM_FLAGS) $(call WINPATH,$<)

#This rule builds the LibLoad library locater object
$(OBJDIR)/$(LIBHEADER_OBJ) : $(LIBHEADER_LOC)
	@$(CD) $(OBJDIR) && \
	@$(AS) $(ASM_FLAGS) $(call WINPATH,$<)
	@$(CD) $(OBJDIR) && \
	@$(CC) $(CFLAGS) -asm $(LIBS)

#This is just a silly rule needed for the icon conversion to work properly
$(OBJDIR)/%.obj :

#This rule cleans up everything
clean :
	@$(RM) $(call WINPATH,$(BINDIR)/$(TARGETHEX) $(BINDIR)/$(TARGETTYPE) $(BINDIR)/$(TARGETMAP) $(OBJECTS) $(OBJDIR)/*.src $(OBJDIR)/$(ICON_ASM)) $(NULL)
	@echo Cleaned build files.
	
.PHONY : all clean
