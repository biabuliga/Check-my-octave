CC = gcc
CFLAGS = -Wall -Wextra -g

build:
	$(CC) $(CFLAGS) main.c memory_matrix.c -o my_octave

clean:
	rm -f my_octave
