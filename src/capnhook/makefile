#----------------------------
# Makefile
#----------------------------

include $(CURDIR)/../common.mk

LIB_SRC := capnhook.asm
LIB_LIB := capnhook.lib
LIB_8XV := capnhook.8xv
LIB_H := capnhook.h

all: $(LIB_8XV)

$(LIB_8XV): $(LIB_SRC)
	$(Q)$(FASMG) $< $@

clean:
	$(Q)$(call REMOVE,$(LIB_LIB) $(LIB_8XV))

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIB))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call COPY,$(LIB_LIB),$(INSTALL_LIB))
	$(Q)$(call COPY,$(LIB_H),$(INSTALL_H))

.PHONY: all clean install

