CEDEV ?= ..
BIN = $(CEDEV)\bin
INCLUDE = $(CEDEV)\include
WORKDIR ?= .\src
OUTDIR ?= .\src

TARGET ?= template
 
CC = @$(BIN)\eZ80cc
LD = @$(BIN)\eZ80link
CV = @$(BIN)\convhex

ASMSOURCES = $(wildcard *.asm)
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.obj)
OBJECTSLD = $(SOURCES:.c=.obj,)
OBJECTSLD += $(ASMSOURCES:.asm=.obj,)

HEADERS = ".;$(CEDEV)\include\ce;$(CEDEV)\include;$(CEDEV)\include\std;$(CEDEV)\lib\ce\include;$(CEDEV)\lib\ce\include\asm"
LIBRARIES = "$(CEDEV)\lib\std\chelp.lib,$(CEDEV)\lib\std\crt.lib,$(CEDEV)\lib\std\crtS.lib,$(CEDEV)\lib\std\nokernel.lib,$(CEDEV)\lib\std\fplib.lib,$(CEDEV)\lib\std\fplibS.lib"
STARTUPMODULE = "$(CEDEV)\include\startup\cstartup.obj,"

ASM_FLAGS = \
        -name -define:_EZ80=1 -define:_SIMULATE=1 -include:$(HEADERS) -NOlist -NOlistmac \
        -pagelen:250 -pagewidth:100 -quiet -sdiopt -warn -NOdebug -NOigcase -cpu:eZ80190

CFLAGS =  \
        -quiet -define:NDEBUG -define:_EZ80190 -define:_EZ80 -define:_SIMULATE -NOlistinc -NOmodsect -cpu:eZ80190 -keepasm \
        -optspeed -NOreduceopt -stdinc:$(HEADERS) -usrinc:"." -NOdebug \
        -asmsw:"$(ASM_FLAGS)" -asm $(ASMSOURCES)
 
LDFLAGS = @.\Linkcmd
LDFLAGS += $(TARGET)= $(OBJECTSLD) $(STARTUPMODULE) $(LIBRARIES)
LDFLAGS += GROUP MEMORY = ROM, RAM

%.obj : %.c
	$(CC) $(CFLAGS) $< 
 
$(TARGET) : $(OBJECTS)
	$(LD) $(LDFLAGS)
	$(CV) $(TARGET)
	
all : $(TARGET)