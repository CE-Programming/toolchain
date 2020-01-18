ifeq ($(OS),Windows_NT)
SHELL = cmd.exe
NATIVEPATH = $(subst /,\,$1)
FASMG := $(call NATIVEPATH,../../tools/fasmg/fasmg.exe)
RM := del /f 2>nul
else
NATIVEPATH = $(subst \,/,$1)
FASMG := $(call NATIVEPATH,../../tools/fasmg/fasmg)
RM := rm -f
endif

all:
	python3 ./devlib.py
	$(FASMG) devlib.asm devlib.8xv

clean:
	$(RM) devlib.asm devlib.8xv
