# ----------------------------
# Program Options
# ----------------------------

NAME         ?= DEMO
ICON         ?= iconc.png
DESCRIPTION  ?= "C SDK Demo"
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

include $(CEDEV)/include/.makefile

# This is a roundabout way to tell make that fonts.c depends on testfont.inc.
# It does it by saying the compiled object code depends on the .inc file.
$(OBJDIR)/fonts.src: $(SRCDIR)/testfont.inc

$(SRCDIR)/testfont.inc: $(SRCDIR)/testfont.fnt
	convfont -o carray -f $(SRCDIR)/testfont.fnt -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $(SRCDIR)/testfont.inc
