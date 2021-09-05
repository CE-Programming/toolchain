#-------------------------------------------
# This makefile builds all the test projects
#-------------------------------------------

MAKEFILES = $(wildcard */*/makefile)

all clean gfx .PHONY: $(MAKEFILES)

$(MAKEFILES):
	$(MAKE) -C $(dir $@) $(or $(MAKECMDGOALS),$(findstring debug,$@))

.PHONY: all clean gfx
