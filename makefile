CC=/usr/bin/gcc
CFLAGS = -Wall -std=c99 -pedantic -g -framework OpenGL -framework GLUT -Wno-deprecated-declarations -fsanitize=address 

fold: main.c creases.c
	$(CC) $(CFLAGS) -o fold main.c triangle.o creases.c 

test: test.c
	$(CC) -std=c99 -pedantic -g -o test test.c
