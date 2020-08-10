#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$1)
RM         = ( del /f /q $1 2>nul || call )
RMDIR      = ( rmdir /s /q $1 2>nul || call )
MKDIR      = ( mkdir $1 2>nul || call )
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
else
NATIVEPATH = $(subst \,/,$1)
RM         = rm -f $1
RMDIR      = rm -rf $1
MKDIR      = mkdir -p $1
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
endif
EZCC       = ez80-clang

EZCFLAGS  := -S -Wall -Wextra -Oz -ffreestanding -isystem .. -isystem ../../fileioc -isystem ../../ce -Dinterrupt="__attribute__((__interrupt__))" -D__rom=const -Dreentrant= -D_EZ80

EZC       := $(wildcard *.c)
EZSRC     := $(addprefix build/,$(EZC:%.c=%.src))

all: $(EZSRC)

build/%.src: %.c
	@$(call MKDIR,build)
	@$(EZCC) $(EZCFLAGS) $< -o $@

clean:
	$(call RMDIR,build)

.PHONY: all clean
