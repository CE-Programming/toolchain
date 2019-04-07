# Dead-simple makefile for Linux building
CC=gcc
CFLAGS=-I.
# The MS Windows SDK doesn't have getopt, but Linux/Unix does, so we're not including it on Linux
#DEPS = convfont.h getopt.h parse_fnt.h serialize_font.h
DEPS = convfont.h parse_fnt.h serialize_font.h
#OBJ = convfont.o getopt.o parse_fnt.o serialize_font.o
OBJ = convfont.o parse_fnt.o serialize_font.o

ifeq ($(OS),Windows_NT)
RM = del /f 2>nul
EXECUTABLE = convfont.exe
else
EXECUTABLE = convfont
RM = rm -f
endif

all: $(EXECUTABLE)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) *.o $(EXECUTABLE)