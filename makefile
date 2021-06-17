CC=/usr/bin/gcc
CFLAGS = -Wall -std=c99 -pedantic -g -framework OpenGL -framework GLUT -Wno-deprecated-declarations -fsanitize=address 

fold: main.c creases.c generate_creases.h
	$(CC) $(CFLAGS) -o fold main.c triangle.o creases.c 

test: test.c
	$(CC) -std=c99 -pedantic -g -o test test.c

lagrange: lagrangetest.c
	$(CC) -std=c99 -pedantic -lgsl -lgslcblas -g -o lagrange lagrangetest.c

angle: angletest.c
	$(CC) $(CFLAGS) -std=c99 -pedantic -lgsl -lgslcblas -g -o angle angletest.c triangle.o creases.c 

sangle: smallerangletest.c
	$(CC) $(CFLAGS) -std=c99 -pedantic -lgsl -lgslcblas -g -o sangle smallerangletest.c triangle.o creases.c 