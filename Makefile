CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

SRCS = $(wildcard src/*.c)

nano-x: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o nano-x

clean:
	rm -f nano-x

.PHONY: clean
