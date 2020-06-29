#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ball printf("dawna\n");

void printarray(int *dawna, int n, int m){
	for(int i=n;i<=m;i++){
		printf("%d ",dawna[i]);
	}
	printf("\n");
}
void swap(int *dawna, int ind1, int ind2){
	int temp = dawna[ind1];
	dawna[ind1] = dawna[ind2];
	dawna[ind2] = temp;
}

int partition(int *dawna, int start, int end){
	int p = start+(rand()%(end-start));
	int pivot = dawna[p];
	swap(dawna, start, p);
	int i = start;
	int j = end;

	while(i<j){
		while(dawna[j]>pivot && i<j){
			j--;
		}
		while(dawna[i]<=pivot && i<j){
			i++;
		}
		if(i<j){
			swap(dawna, i,j);
		}
	}
	swap(dawna, start, i);
	return i;
}
void quicksort(int *dawna, int start, int end){
	// printarray(dawna,start,end);
	if(start<end){
		int p = partition(dawna, start, end);
		quicksort(dawna, start, p-1);
		quicksort(dawna, p+1 ,end);
	}
}

void selectsort(int *dawna, int start, int end){
	for(int i=start;i<=end;i++){
		int j = i;
		while(j>start && dawna[j-1]>dawna[j]){
			swap(dawna, j, j-1);
			j--;
		}
	}
}
double cross(double x1, double y1, double x2, double y2){
	return (x1*y2 - x2*y1);
}

int clockwiseof(int ind1, int ind2, double cx, double cy, int *pointlist){
	double x1 = pointlist[2*ind1] - cx;
	double y1 = pointlist[2*ind1+1] - cy;
	double x2 = pointlist[2*ind2] - cx;
	double y2 = pointlist[2*ind2+1] - cy;
	return cross(x1,y1,x2,y2);
}

int main(){
	int dawnarm[8] = {1,2,3,5,6,10,12,4};
	srand(time(0));
	printf("hello dawna\n");
	printarray(dawnarm,0,7);
	selectsort(dawnarm,0,7);

	printarray(dawnarm,0,7);

	// for(int i=0;i<1000;i++){
	// 	dawnarm[0] = rand()%100;
	// 	dawnarm[1] = rand()%100;
	// 	dawnarm[2] = rand()%100;
	// 	dawnarm[3] = rand()%100;	
	// 	int petarm = cross(dawnarm[0],dawnarm[1],dawnarm[2],dawnarm[3]);
	// 	printf("%f,%f and %f,%f: %d\n",dawnarm[0],dawnarm[1],dawnarm[2],dawnarm[3], petarm);
	// }






	for(int i=0;i<10000;i++){
		dawnarm[0] = rand()%100;
		dawnarm[1] = rand()%100;
		dawnarm[2] = rand()%100;
		dawnarm[3] = rand()%100;
		dawnarm[4] = rand()%100;
		dawnarm[5] = rand()%100;
		dawnarm[6] = rand()%100;
		dawnarm[7] = rand()%100;
		printarray(dawnarm,0,7);
		selectsort(dawnarm,0,7);
		printarray(dawnarm,0,7);
		printf("\n");
		int ok = 0;
		for(int i=0;i<6;i++){
			if(dawnarm[i]>dawnarm[i+1]){
				ok++;
			}
		}
		if(ok == 0){
			printf("good\n");
		}
		else
		{
			printf("bad\n");
		}


	}

	return 0;
}