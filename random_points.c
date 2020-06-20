#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate_points.h"


void write_poly(int n, int xrange, int yrange, char* filename){
	srand(time(0)); 
	FILE *fp;
	fp = fopen(filename, "w+");
	fprintf(fp, "%d %d %d %d\n", n+4, 2, 0, 0);
	for(int i=1;i<=n;i++){
		fprintf(fp, "%d, %d, %d\n", i, rand()%xrange, rand()%yrange);
	}
	fprintf(fp, "%d, %d, %d\n", n+1, 0, 0);
	fprintf(fp, "%d, %d, %d\n", n+2, xrange, 0);
	fprintf(fp, "%d, %d, %d\n", n+3, xrange, yrange);
	fprintf(fp, "%d, %d, %d\n", n+4, 0, yrange);
	fputs("0 0\n",fp);
	fputs("0\n",fp);
}
