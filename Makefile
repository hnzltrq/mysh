# Compiler settings, C23 with POSIX/GNU extensions enabeld
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu23 -Isrc

# Name of the final executable
TARGET = mysh

# Find all .c files in the current directory
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)