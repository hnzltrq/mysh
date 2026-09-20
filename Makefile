# C23 with warnings, extra warnings and POSIX/GNU extensions enabeld
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu23 -Isrc


TARGET = mysh

# Find all .c files in the src directory
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# Links the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# deletes generated obj files and final binary
clean:
	rm -f $(OBJS) $(TARGET)