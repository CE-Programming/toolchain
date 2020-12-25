#-----------------------------------------------
# This makefile builds all the example projects
#-----------------------------------------------

DIRS = hello_world/makefile $(wildcard */*/makefile)

all clean gfx .PHONY: $(DIRS)

$(DIRS):
	$(MAKE) -C $(dir $@) $(MAKECMDGOALS)

.PHONY: all clean gfx

