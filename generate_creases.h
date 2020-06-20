#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void write_poly(int n, int xrange, int yrange, char* filename);
struct triangulateio *init_in(int n);
struct triangulateio *init_out(struct triangulateio *in);