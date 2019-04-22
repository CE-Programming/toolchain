# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= DEMO
COMPRESSED  ?= NO
ICON        ?= iconc.png
DESCRIPTION ?= "C SDK Demo"
FONTPACKNAME?=DrSans

# ----------------------------

include $(CEDEV)/include/.makefile

$(BINDIR)/$(FONTPACKNAME).bin: $(SRCDIR)/drsans-06-bold.fnt $(SRCDIR)/drsans-06-normal.fnt $(SRCDIR)/drsans-07-bold.fnt $(SRCDIR)/drsans-07-normal.fnt $(SRCDIR)/drsans-09-bold.fnt $(SRCDIR)/drsans-09-normal.fnt
	convfont -o fontpack -N "Dr. Sans" -P "Calculator 1252" \
	-D "A font designed for maximum readability" \
	-V "15 April 2019" \
	-f $(SRCDIR)/drsans-09-bold.fnt   -l 11 -x 5 -c 2 -a 1 -b 1 -w 0xC0 -s 0 \
	-f $(SRCDIR)/drsans-09-normal.fnt -l 11 -x 5 -c 2 -a 1 -b 1 -w 0x80 -s 0 \
	-f $(SRCDIR)/drsans-07-bold.fnt   -l 8  -x 3 -c 1 -a 1 -b 1 -w 0xC0 -s 0 \
	-f $(SRCDIR)/drsans-07-normal.fnt -l 8  -x 3 -c 1 -a 1 -b 1 -w 0x80 -s 0 \
	-f $(SRCDIR)/drsans-06-bold.fnt   -l 7  -x 3 -c 1 -a 1 -b 1 -w 0xC0 -s 0 \
	-f $(SRCDIR)/drsans-06-normal.fnt -l 7  -x 3 -c 1 -a 1 -b 1 -w 0x80 -s 0 \
	$(BINDIR)/$(FONTPACKNAME).bin

$(BINDIR)/$(FONTPACKNAME).8xv: $(BINDIR)/$(FONTPACKNAME).bin
	convhex -a -v -n $(FONTPACKNAME) $(BINDIR)/$(FONTPACKNAME).bin $(BINDIR)/$(FONTPACKNAME).8xv

all: $(BINDIR)/$(FONTPACKNAME).8xv

.PHONY: clean