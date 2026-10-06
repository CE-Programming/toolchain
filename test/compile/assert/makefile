C_STANDARDS = c99 c11 c17
CXX_STANDARDS = c++11 c++17 c++20
STANDARDS = $(C_STANDARDS) $(CXX_STANDARDS)

ENABLED = $(addprefix enabled-,$(STANDARDS))
CASSERT = $(addprefix cassert-,$(CXX_STANDARDS))
CONSTEXPR = $(addprefix constexpr-,c++14 c++17 c++20)
EXPRESSIONS = $(addprefix expression-,$(STANDARDS))
CONSTEXPR_EXPRESSIONS = $(addprefix constexpr-expression-,$(CXX_STANDARDS))
DISABLED = $(addprefix disabled-,$(STANDARDS))
WARNINGS = $(addprefix warning-,c11 c++20)
STACK = $(addprefix stack-,c11 c++20)
EVALUATION = $(addprefix evaluation-,c11 c++20)
DISABLED_EVALUATION = $(addprefix disabled-evaluation-,c11 c++20)
CHECKS = $(ENABLED) $(CASSERT) $(CONSTEXPR) $(EXPRESSIONS) $(CONSTEXPR_EXPRESSIONS)
CHECKS += $(DISABLED) $(WARNINGS) $(STACK) $(EVALUATION) $(DISABLED_EVALUATION)

# Reuse the usual SDK tools and Windows/Unix helpers, with compiler checks
# instead of linking a calculator program. This also routes make debug here.
override BUILD := $(CHECKS)
.DEFAULT_GOAL := all
include $(shell cedev-config --makefile)

LIBC_INCLUDE ?= $(CEDEV_TOOLCHAIN)/include
LIBCXX_INCLUDE ?= $(CEDEV_TOOLCHAIN)/include/c++
COMPILER ?= $(CC)
EZLIBCINCLUDE = -isystem $(call QUOTE_ARG,$(call FORWARD_PATH,$(LIBC_INCLUDE)))
EZLIBCXXINCLUDE = -isystem $(call QUOTE_ARG,$(call FORWARD_PATH,$(LIBCXX_INCLUDE)))

CHECKFLAGS = $(if $(findstring ++,$1),$(EZCXXFLAGS),$(EZCFLAGS))
CHECKFLAGS += -x $(if $(findstring ++,$1),c++,c) -std=$1
CHECKFLAGS += -UNDEBUG -fno-color-diagnostics
VERIFYFLAGS = -Xclang -verify -Xclang -verify-ignore-unexpected=note

all: $(CHECKS)

$(OBJDIR):
	$(Q)$(call MKDIR,$@)

$(ENABLED): enabled-%: fixtures/enabled.c
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -fsyntax-only $(call QUOTE_ARG,$<)

$(CASSERT): cassert-%: fixtures/enabled.cpp
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -fsyntax-only $(call QUOTE_ARG,$<)

$(CONSTEXPR): constexpr-%: fixtures/constexpr.cpp
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -fsyntax-only $(call QUOTE_ARG,$<)

$(EXPRESSIONS): expression-%: fixtures/expression.c
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -fsyntax-only $(VERIFYFLAGS) $(call QUOTE_ARG,$<)

$(CONSTEXPR_EXPRESSIONS): constexpr-expression-%: fixtures/constexpr_expression.cpp
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -fsyntax-only $(VERIFYFLAGS) $(call QUOTE_ARG,$<)

$(DISABLED): disabled-%: fixtures/disabled.c
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -DNDEBUG -fsyntax-only $(call QUOTE_ARG,$<)

$(WARNINGS): warning-%: fixtures/assignment.c
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -fsyntax-only $(VERIFYFLAGS) $(call QUOTE_ARG,$<)

$(STACK): stack-%: fixtures/enabled.c | $(OBJDIR)
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -Oz -S -Wframe-larger-than=0 -Werror=frame-larger-than -Werror=unknown-warning-option $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$(OBJDIR)/$@.s)

$(EVALUATION): evaluation-%: fixtures/single_evaluation.c | $(OBJDIR)
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -Oz -S -Werror=unknown-attributes $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$(OBJDIR)/$@.s)

$(DISABLED_EVALUATION): disabled-evaluation-%: fixtures/single_evaluation.c | $(OBJDIR)
	$(Q)$(call QUOTE_ARG,$(COMPILER)) $(call CHECKFLAGS,$*) -DNDEBUG -Oz -S -Werror=unknown-attributes $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$(OBJDIR)/$@.s)

.PHONY: all $(CHECKS)
