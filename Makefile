# C23 with warnings, extra warnings and POSIX/GNU extensions enabeld
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu23 -Isrc

# Name of the final executable
TARGET = mysh

# Find all .c files in the src directory
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# Links the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# deletes generated obj files
clean:
	rm -f $(OBJS) $(TARGET)