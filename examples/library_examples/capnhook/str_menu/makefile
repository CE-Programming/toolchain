all: strmenu.8xp

clean:
	rm -f strmenu.8xp

strmenu.8xp: strmenu.asm ../../src/capnhook.lib
	fasmg strmenu.asm

.PHONY: all clean
