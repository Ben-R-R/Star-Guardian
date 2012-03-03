# Compiler
CC=g++

# Objects
OBJECTS=main.o MovementFunction.o 

# objects that don't need to be compiled every time. 
STATIC=

# Source Files
SOURCE=main.cpp MovementFunction.cpp 

# Compiler flags
CPPFLAGS=-Wall  

# Linker flags
LDFLAGS=

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
