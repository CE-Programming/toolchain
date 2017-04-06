#-----------------------------------------------
# This makefile builds all the example projects
#-----------------------------------------------

DIRS = $(wildcard */makefile)

all clean .PHONY: $(DIRS)

$(DIRS):
	$(MAKE) -C $(dir $@) $(MAKECMDGOALS)

.PHONY: all clean
