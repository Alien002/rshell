CC=g++ -std=c++11
CC_FLAGS =-Wall -Werror -ansi -pedantic

EXECUTABLE = rshell
SOURCEDIR = src
BUILDDIR = bin

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all:	
	mkdir -p $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(BUILDDIR)/$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
	rm -rf $(BUILDDIR)