#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate_creases.h"
#include "triangle.h"


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

struct triangulateio *init_in(int n){
	if(n<4){
		printf("too few\n");
		return NULL;
	}
	struct triangulateio *in;
	srand(time(0)); 

	in = (struct triangulateio*) malloc(sizeof(struct triangulateio));

	in->numberofpoints = n;
	in->numberofpointattributes = 0;
	in->numberofholes = 0;
	in->numberofregions = 0;
	in->numberofsegments = 0;
	in->numberoftriangles = 0;

	in->pointlist = (REAL*) malloc(in->numberofpoints*2*sizeof(REAL));
	in->pointattributelist = NULL;
	in->pointmarkerlist = NULL;
	in->segmentmarkerlist = NULL;
	in->segmentlist = NULL;
	in->holelist = NULL;
	in->regionlist = NULL;

	in->pointlist[0] = 0;
	in->pointlist[1] = 0;
	in->pointlist[2] = 0;
	in->pointlist[3] = 100;
	in->pointlist[4] = 100;
	in->pointlist[5] = 100;
	in->pointlist[6] = 100;
	in->pointlist[7] = 0;
	for(int i=8;i<2*n;i++){
		in->pointlist[i] = rand()%100;
	}
	return in;
}

struct triangulateio *init_out(struct triangulateio *in){
	struct triangulateio *out;
	out = (struct triangulateio*) malloc(sizeof(struct triangulateio));
	out->pointlist = in->pointlist;
	out->pointmarkerlist = NULL;
	out->trianglelist = NULL;
	out->segmentlist = NULL;
	out->segmentmarkerlist = NULL;
	out->edgelist = NULL;
	out->edgemarkerlist = NULL;
	return out;
}
