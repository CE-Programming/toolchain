#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
RM         = del /f 2>nul
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
CC         = $(call NATIVEPATH,$(BIN)/ez80cc.exe)
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm -f
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
CC         = $(call NATIVEPATH,wine $(BIN)/ez80cc.exe)
endif

CCFLGS    := -noasm -nodebug -nogenprint -nokeeplst -keepasm -promote -quiet -fplib -optsize -cpu:EZ80F91 -stdinc:"..;..\\..\\fileioc;..\\..\\ce" -define:_EZ80F91 -define:_EZ80

EZC       := $(wildcard *.c)
EZSRC     := $(EZC:%.c=%.src)

all: $(EZSRC)

%.src: %.c
	$(CC) $(CCFLGS) $(call WINPATH,$<)

clean:
	$(RM) $(EZSRC)
	
.PHONY: all clean
