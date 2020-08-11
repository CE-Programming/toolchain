#-----------------------------------------------
# This makefile builds all the example projects
#-----------------------------------------------

# source: http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2),$d))

DIRS = $(call rwildcard,,*/makefile)

all clean gfx .PHONY: $(DIRS)

$(DIRS):
	$(MAKE) -C $(dir $@) $(MAKECMDGOALS)

.PHONY: all clean gfx

