NAME = DIVSIGN
DESCRIPTION = "Signed div OS CRT regression"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -ffreestanding -Wall -Wextra -Wshadow -Oz
PREFER_OS_LIBC = NO
# This test must exercise the preferred OS unsigned-divider entry point.
override PREFER_OS_CRT = YES

include $(shell cedev-config --makefile)
