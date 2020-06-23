#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void write_poly(int n, int xrange, int yrange, char* filename);

struct triangulateio *init_in(int n);

struct triangulateio *init_out(struct triangulateio *in);

int **edgelist_to_matrix(struct triangulateio *to);

void *replace_edgelist_using_matrix(struct triangulateio *t, int **matrix);

void free_t(struct triangulateio *t);

void evenize(int **matrix, int start);