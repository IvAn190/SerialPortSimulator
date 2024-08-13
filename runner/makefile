# Compiler to use
CC = gcc

# Directories
INCLUDES = -I../bib

# Source files
SRCS = runner.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = runner.exe

# Compiler flags
CFLAGS = -Wall -Wextra $(INCLUDES)

# Linker flags
LDFLAGS =

# Default target
all: $(EXEC) clean_objs

# Rule to create the executable
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up object files after build (Windows version using del)
clean_objs:
	del /Q $(OBJS)

# Clean up all build files (Windows version using del)
clean:
	del /Q $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean clean_objs
