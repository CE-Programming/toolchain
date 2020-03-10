# ----------------------------
# Program Options
# ----------------------------

NAME         ?= DEMO
ICON         ?= icon.png
DESCRIPTION  ?= "CE C SDK Demo"
MAIN_ARGS    ?= NO
COMPRESSED   ?= NO
ARCHIVED     ?= NO

# ----------------------------
# Compile Options
# ----------------------------

OPT_MODE     ?= -Oz
EXTRA_CFLAGS ?= -Wall -Wextra

# ----------------------------
# Debug Options
# ----------------------------

OUTPUT_MAP   ?= NO

# ----------------------------
# FontLib Options
# ----------------------------

FONTPACKNAME ?= DRSANS
FONTDIR ?= $(SRCDIR)/fonts

include $(CEDEV)/include/.makefile

$(BINDIR)/$(FONTPACKNAME).bin: $(FONTDIR)/drsans-06-bold.fnt $(FONTDIR)/drsans-06-normal.fnt $(FONTDIR)/drsans-07-bold.fnt $(FONTDIR)/drsans-07-normal.fnt $(FONTDIR)/drsans-09-bold.fnt $(FONTDIR)/drsans-09-normal.fnt
	$(call MKDIR,$(@D))
	convfont -o fontpack -N "Dr. Sans" -P "Calculator 1252" \
	-D "A font designed for maximum readability" \
	-V "15 April 2019" \
	-f $(FONTDIR)/drsans-09-bold.fnt   -l 11 -x 5 -c 2 -a 1 -b 1 -w bold -s sans-serif -s upright -s proportional \
	-f $(FONTDIR)/drsans-09-normal.fnt -l 11 -x 5 -c 2 -a 1 -b 1 -w normal -s 0 \
	-f $(FONTDIR)/drsans-07-bold.fnt   -l 8  -x 3 -c 1 -a 1 -b 1 -w bold -s 0 \
	-f $(FONTDIR)/drsans-07-normal.fnt -l 8  -x 3 -c 1 -a 1 -b 1 -w normal -s 0 \
	-f $(FONTDIR)/drsans-06-bold.fnt   -l 7  -x 3 -c 1 -a 1 -b 1 -w bold -s 0 \
	-f $(FONTDIR)/drsans-06-normal.fnt -l 7  -x 3 -c 1 -a 1 -b 1 -w normal -s 0 \
	$(BINDIR)/$(FONTPACKNAME).bin

$(BINDIR)/$(FONTPACKNAME).8xv: $(BINDIR)/$(FONTPACKNAME).bin
	$(call MKDIR,$(@D))
	convbin --iformat bin --input $(BINDIR)/$(FONTPACKNAME).bin --oformat 8xv --output $(BINDIR)/$(FONTPACKNAME).8xv --archive --name $(FONTPACKNAME)

all: $(BINDIR)/$(FONTPACKNAME).8xv

.PHONY: clean
