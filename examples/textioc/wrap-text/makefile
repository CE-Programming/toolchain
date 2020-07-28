# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= DEMO
COMPRESSED  ?= NO
ICON        ?= icon.png
DESCRIPTION ?= "CE C SDK Demo"

# ----------------------------

FONTDIR ?= $(SRCDIR)/fonts

include $(CEDEV)/include/.makefile

# This is a roundabout way to tell make that fonts.c depends on testfont.inc.
# It does it by saying the compiled object code depends on the .inc file.
$(OBJDIR)/fonts/fonts.src: $(FONTDIR)/testfont.inc

$(FONTDIR)/testfont.inc: $(FONTDIR)/testfont.fnt
	$(call MKDIR,$(@D))
	convfont -o carray -f $^ -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@
