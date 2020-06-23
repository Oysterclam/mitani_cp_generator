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

int **edgelist_to_matrix(struct triangulateio *t){
	int edges = t->numberofedges;
	int points = t->numberofpoints;
	int **matrix = (int**) calloc(points,sizeof(int*));
	for(int i=0;i<points;i++){
		matrix[i] = (int*) calloc(points,sizeof(int));
	}
	for(int i=0;i<2*edges;i+=2){
		int ind1 = t->edgelist[i];
		int ind2 = t->edgelist[i+1];
		matrix[ind1][ind2]=1;
		matrix[ind2][ind1]=1;
	}
	return matrix;
}

void *replace_edgelist_using_matrix(struct triangulateio *t, int **matrix){
	int points = t->numberofpoints;
	int *edgelist = (int*) malloc(2*t->numberofedges*sizeof(int));
	int cur = 0;
	for(int i=0;i<points;i++){
		for(int j=i;j<points;j++){
			if(matrix[i][j]==1){
				edgelist[cur*2]=i;
				edgelist[cur*2+1]=j;
				cur++;
			}
		}
	}
	t->edgelist = edgelist;
	t->numberofedges = cur;
}
void free_t(struct triangulateio *t){
	free(t->pointlist);
	free(t->pointattributelist);
	free(t->pointmarkerlist);
	free(t->regionlist);
	free(t->trianglelist);
	free(t->segmentlist);
	free(t->segmentmarkerlist);
	free(t->edgelist);
	free(t->edgemarkerlist);
}

void evenize(int **matrix, int n){
/*
removes 1's so that the number of 1's in each row/column is even
I think this is O(n^2)
*/
	int sum;
	int skip = 0;
	int evens[n];
	for(int i=0;i<n;i++){
		sum = 0;
		for(int j=0;j<n;j++){
			sum+=matrix[i][j];
		}
		if(sum%2==0){
			evens[i]=1;
		}
		else{
			for(int p=i;p<n;p++){
				if(matrix[i][p]==1 && evens[p]!=1) {
					matrix[i][p]=0;
					matrix[p][i]=0;
					evens[p]=1;
					break;
				}
			}
			evens[i]=1;
		}
	}
}


























