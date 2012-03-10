# Compiler
CC=g++

# Objects
OBJECTS=main.o MovementFunction.o logger.o Sprite.o

# objects that don't need to be compiled every time. 
STATIC=

# Source Files
SOURCE=main.cpp MovementFunction.cpp logger.cpp Sprite.cpp

# Compiler flags
CPPFLAGS=-Wall $(shell sdl-config --cflags)

# Linker flags
LDFLAGS= $(shell sdl-config --libs)

main: main.cpp
	$(CC) $(CPPFLAGS) -c $(SOURCE)
	$(CC) $(OBJECTS) $(STATIC) $(CPPFLAGS) $(LDFLAGS) -o main

# cleanup
clean:
	rm -rf $(OBJECTS)

# full cleanup
purge:
	rm -rf $(OBJECTS) $(STATIC)

# EOF
