#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$(1))
RMDIR      = call && (if exist $(1) rmdir /s /q $(1))
MKDIR      = call && (if not exist $(1) mkdir $(1))
RM         = del /f /q 2>nul
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
else
NATIVEPATH = $(subst \,/,$(1))
RMDIR      = rm -rf $(1)
MKDIR      = mkdir -p $(1)
RM         = rm -f
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
