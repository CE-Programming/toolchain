#-----------------------------------------------
# This makefile builds all the example projects
#-----------------------------------------------

MAKEFILES = hello_world/makefile  $(wildcard */*/makefile) $(wildcard */*/*/makefile)

all clean gfx .PHONY: $(MAKEFILES)

$(MAKEFILES):
	$(MAKE) -C $(dir $@) $(or $(MAKECMDGOALS),$(findstring debug,$@))

.PHONY: all clean gfx
