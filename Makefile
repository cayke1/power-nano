CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

nano-x:
	$(CC) $(CFLAGS) src/*.c -o nano-x
