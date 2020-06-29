#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <string.h>
#include <math.h>


void write_poly(int n, int xrange, int yrange, char* filename);

struct triangulateio *init_in(int n);

struct triangulateio *init_out(struct triangulateio *in);

int **edgelist_to_matrix(struct triangulateio *to);

void replace_edgelist_using_matrix(struct triangulateio *t, int **matrix);

void free_t(struct triangulateio *t);

void evenize(int **matrix, int start);

double cross(double x1, double y1, double x2, double y2);

void clockwisesort(int *indices, REAL *pointlist, int center_index, int start, int end);

void drawstring(int x, int y, int z, const char *s);

void printrows(int **dawna);

void printevens(int **dawna);

void printrowsandevens(int **dawna);

REAL anglebetween(REAL x1, REAL y1, REAL xc, REAL yc, REAL x2, REAL y2);

REAL *angles(int *indices, REAL *pointlist, int center_index, int points);

void clockwiseSelect(int *indices, REAL *pointlist, int center_index, int start, int end);
