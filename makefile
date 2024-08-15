# Compiler to use
CC = gcc

# Directories
INCLUDES = -I.\\bib
RUNNER_DIR = .\\runner
SENDER_DIR = .\\sender
EXEC_DIR = .\\exec

# Source files for runner and sender
RUNNER_SRCS = $(RUNNER_DIR)\\runner.c
SENDER_SRCS = $(SENDER_DIR)\\sender.c

# Object files
RUNNER_OBJS = $(RUNNER_DIR)\\runner.o
SENDER_OBJS = $(SENDER_DIR)\\sender.o

# Executable names
RUNNER_EXEC = $(EXEC_DIR)\\runner.exe
SENDER_EXEC = $(EXEC_DIR)\\sender.exe

# Compiler flags
CFLAGS = -Wall -Wextra $(INCLUDES)

# Linker flags
LDFLAGS =

# Default target compiles both projects
all: $(RUNNER_EXEC) $(SENDER_EXEC) clean_objs

# Rule to create runner executable
$(RUNNER_EXEC): $(RUNNER_OBJS)
	@if not exist $(EXEC_DIR) mkdir $(EXEC_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to create sender executable
$(SENDER_EXEC): $(SENDER_OBJS)
	@if not exist $(EXEC_DIR) mkdir $(EXEC_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to compile .c files into .o files for runner
$(RUNNER_DIR)\\%.o: $(RUNNER_DIR)\\%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to compile .c files into .o files for sender
$(SENDER_DIR)\\%.o: $(SENDER_DIR)\\%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up object files after build (Windows version using del)
clean_objs:
	del /Q $(RUNNER_DIR)\\runner.o $(SENDER_DIR)\\sender.o

# Clean up all build files (Windows version using del)
clean:
	del /Q $(RUNNER_DIR)\\runner.o $(SENDER_DIR)\\sender.o $(RUNNER_EXEC) $(SENDER_EXEC)

# Phony targets
.PHONY: all clean clean_objs
