CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -fPIE -O3 -flto
LDFLAGS = -flto

SOURCES = convfont.c parse_fnt.c serialize_font.c
DEPS = convfont.h parse_fnt.h serialize_font.h

ifeq ($(OS),Windows_NT)
SHELL = cmd.exe
RM = del /f 2>nul
EXECUTABLE = convfont.exe
else
EXECUTABLE = convfont
RM = rm -f
endif

OBJECTS := $(SOURCES:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(DEPS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

.PHONY: clean
