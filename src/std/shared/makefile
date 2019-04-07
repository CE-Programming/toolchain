#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$(1))
RMDIR      = call && (if exist $(1) rmdir /s /q $(1))
MKDIR      = call && (if not exist $(1) mkdir $(1))
RM         = del /f 2>nul
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
CC         = $(call NATIVEPATH,$(BIN)/ez80cc.exe)
else
NATIVEPATH = $(subst \,/,$(1))
RMDIR      = rm -rf $(1)
MKDIR      = mkdir -p $(1)
RM         = rm -f
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
ifeq ($(shell uname -r | grep Microsoft),)
WINE       =wine
endif
CC         = $(call NATIVEPATH,$(WINE) $(BIN)/ez80cc.exe)
endif

CCFLGS    := -noasm -nodebug -nogenprint -nokeeplst -keepasm -promote -quiet -fplib -optsize -cpu:EZ80F91 -stdinc:"..\\..;..\\..\\..\\fileioc;..\\..\\..\\ce" -define:_EZ80F91 -define:_EZ80

EZC       := $(wildcard *.c)
EZSRC     := $(addprefix build/,$(EZC:%.c=%.src))

all: $(EZSRC)

build/%.src: %.c
	@$(call MKDIR,build) && \
	cd build && \
	$(CC) $(CCFLGS) ..\\$<

clean:
	$(call RMDIR,build)

.PHONY: all clean
