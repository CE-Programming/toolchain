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

FONTDIR ?= $(SRCDIR)/fonts

include $(CEDEV)/include/.makefile

# This is a roundabout way to tell make that fonts.c depends on testfont.inc.
# It does it by saying the compiled object code depends on the .inc file.
$(OBJDIR)/fonts/fonts.c.src: $(FONTDIR)/testfont.inc

$(FONTDIR)/testfont.inc: $(FONTDIR)/testfont.fnt
	$(call MKDIR,$(@D))
	convfont -o carray -f $^ -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@
