# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "CE C Toolchain Demo"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# font options
FONTPACKNAME = DRSANS
FONTDIR = $(SRCDIR)/fonts

DEPS = $(BINDIR)/$(FONTPACKNAME).bin $(BINDIR)/$(FONTPACKNAME).8xv

# ----------------------------

include $(shell cedev-config --makefile)

# ----------------------------

# Font metrics (space above, weight, &c.) passed on the command line override those present in the file itself.
$(BINDIR)/$(FONTPACKNAME).bin: $(FONTDIR)/drsans-06-bold.convfont $(FONTDIR)/drsans-06-normal.convfont $(FONTDIR)/drsans-07-bold.convfont $(FONTDIR)/drsans-07-normal.convfont $(FONTDIR)/drsans-09-bold.convfont $(FONTDIR)/drsans-09-normal.convfont
	$(Q)$(call MKDIR,$(@D))
	$(Q)convfont -o fontpack -N "Dr. Sans" -P "Calculator 1252" \
	-D "A font designed for maximum readability" \
	-V "15 April 2019" \
	-t $(FONTDIR)/drsans-09-bold.convfont   -l 11 -x 5 -c 2 -a 1 -b 1 -w bold -s sans-serif -s upright -s proportional \
	-t $(FONTDIR)/drsans-09-normal.convfont \
	-t $(FONTDIR)/drsans-07-bold.convfont   \
	-t $(FONTDIR)/drsans-07-normal.convfont \
	-t $(FONTDIR)/drsans-06-bold.convfont   \
	-t $(FONTDIR)/drsans-06-normal.convfont \
	$(BINDIR)/$(FONTPACKNAME).bin

$(BINDIR)/$(FONTPACKNAME).8xv: $(BINDIR)/$(FONTPACKNAME).bin
	$(Q)$(call MKDIR,$(@D))
	$(Q)convbin --iformat bin --input $(BINDIR)/$(FONTPACKNAME).bin --oformat 8xv --output $(BINDIR)/$(FONTPACKNAME).8xv --archive --name $(FONTPACKNAME)
