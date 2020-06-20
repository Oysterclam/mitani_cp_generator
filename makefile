CC=/usr/bin/gcc
CFLAGS = -Wall -std=c99 -pedantic -g -framework OpenGL -framework GLUT -Wno-deprecated-declarations -fsanitize=address 

fold: main.c random_points.c
	$(CC) $(CFLAGS) -o fold main.c triangle.o random_points.c 

