#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

double f(double x){
	return (x*x + 3*x + 2);
}

double fprime(double x){
	return (2*x +3);
}

void newton(double (*f)(double), double (*fprime)(double), double tolerance, double *x){
	while(f(*x) < (-1*tolerance) || f(*x)>tolerance){
		printf("%f\n",*x);
		*x = *x - (f(*x)/fprime(*x));
	}
}

void printMatrix(gsl_matrix *m, int r, int c){
	int i, j; 

	for (i = 0; i < r; i++)  /* OUT OF RANGE ERROR */
		for (j = 0; j < c; j++)
			printf ("m(%d,%d) = %g\n", i, j, 
			gsl_matrix_get (m, i, j));
}

void calcf(gsl_vector *f, double x1, double x2){
	gsl_vector_set (f, 0, -(x1*x1*x1 -5*x1 - x2));
	gsl_vector_set (f, 1, -(x1 + sin(x1) +3 -x2));
}
void calcDf(gsl_matrix *Df, double x1, double x2){
	gsl_matrix_set (Df, 0, 0, 3*x1*x1);
	gsl_matrix_set (Df, 0, 1, -1.0);
	gsl_matrix_set (Df, 1, 0, 1.0 + cos(x1));
	gsl_matrix_set (Df, 1, 1, -1.0);
}

void calcf1(gsl_vector *f, double x, double y, double l){
	gsl_vector_set (f, 0, -(16*x + 2*x*l));
	gsl_vector_set (f, 1, -(2*l*y -2));
	gsl_vector_set (f, 1, -(x*x + y*y - 1));
}

void calcDf1(gsl_matrix *Df, double x, double y, double l){
	gsl_matrix_set (Df, 0, 0, 16 + 2*l);
	gsl_matrix_set (Df, 0, 1, 0);
	gsl_matrix_set (Df, 0, 2, 2*x);
	gsl_matrix_set (Df, 1, 0, 0);
	gsl_matrix_set (Df, 1, 1, 2*l);
	gsl_matrix_set (Df, 1, 2, 2*y);
	gsl_matrix_set (Df, 2, 0, 2*x);
	gsl_matrix_set (Df, 2, 1, 2*y);
	gsl_matrix_set (Df, 2, 2, 0);
}

void newtonize2(gsl_matrix *Df, gsl_vector *f, gsl_vector *v, void (*calcf)(*gsl_vector, double, double), void (*calcDf)(*gsl_matrix, double, double), double *guess, int iter){
	for(int i=0;i<8;i++){
		calcf(f,guess[0],guess[1]);
		calcDf(Df, guess[0],guess[1]);
		// printf("NEW INTER\n");
		// printf("guess: %f,%f\n",guess[0],guess[1]);
		// printf ("\nA = \n");
		// gsl_matrix_fprintf (stdout, Df, "%g");	
		// printf ("\nb = \n");
		// gsl_vector_fprintf (stdout, f, "%g");	

		int s;
		gsl_permutation *p = gsl_permutation_alloc (2);
		gsl_linalg_LU_decomp (Df, p, &s);
		gsl_linalg_LU_solve (Df, p, f, v);
		// printf ("\nSolution vector v = \n");
		// gsl_vector_fprintf (stdout, v, "%g");	
		guess[0] = guess[0] + gsl_vector_get(v, 0);
		guess[1] = guess[1] + gsl_vector_get(v, 1);	
		gsl_permutation_free (p);
	}
		printf("\n\nfinal solution: %f,%f\n",guess[0],guess[1]);
}
void newtonize3(gsl_matrix *Df, gsl_vector *f, gsl_vector *v, void (*calcf)(*gsl_vector, double, double), void (*calcDf)(*gsl_matrix, double, double), double *guess, int iter){
	for(int i=0;i<8;i++){
		calcf1(f,guess[0],guess[1],guess[2]);
		calcDf1(Df, guess[0],guess[1],guess[2]);
		// printf("NEW INTER\n");
		// printf("guess: %f,%f\n",guess[0],guess[1]);
		// printf ("\nA = \n");
		// gsl_matrix_fprintf (stdout, Df, "%g");	
		// printf ("\nb = \n");
		// gsl_vector_fprintf (stdout, f, "%g");	

		int s;
		gsl_permutation *p = gsl_permutation_alloc (3);
		gsl_linalg_LU_decomp (Df, p, &s);
		gsl_linalg_LU_solve (Df, p, f, v);
		// printf ("\nSolution vector v = \n");
		// gsl_vector_fprintf (stdout, v, "%g");	
		guess[0] = guess[0] + gsl_vector_get(v, 0);
		guess[1] = guess[1] + gsl_vector_get(v, 1);	
		guess[2] = guess[2] + gsl_vector_get(v, 2);	

		gsl_permutation_free (p);
	}
		printf("\n\nfinal solution: %f,%f\n",guess[0],guess[1],guess[2]);

}

int main(){


	printf("hi Dawna\n");



	gsl_matrix *f = gsl_vector_alloc (2);
	gsl_matrix *Df = gsl_matrix_alloc (2, 2);
	gsl_matrix *v = gsl_vector_alloc (2);
	double guess[2] = {-1,1};
	/*
		given a guess, this finds a solution to:
		x^3 - 5x - y = 0
		x + sin(x) - y + 3 = 0;

	*/
	newtonize2(Df, f, v, calcf, calcDf, guess, 200);









	// gsl_matrix *f1 = gsl_vector_alloc (3);
	// gsl_matrix *Df1 = gsl_matrix_alloc (3, 3);
	// gsl_matrix *v1 = gsl_vector_alloc (3);

	// double guess3[3] = {-12,-12,1};

	// for(int i=0;i<2000;i++){
	// 	calcf1(f1,guess3[0],guess3[1],guess3[2]);
	// 	calcDf1(Df1, guess3[0],guess3[1],guess3[2]);
	// 	int s;
	// 	gsl_permutation *p1 = gsl_permutation_alloc (3);
	// 	gsl_linalg_LU_decomp (Df1, p1, &s);
	// 	gsl_linalg_LU_solve (Df1, p1, f1, v1);
	// 	guess3[0] = guess3[0] + gsl_vector_get(v1, 0);
	// 	guess3[1] = guess3[1] + gsl_vector_get(v1, 1);
	// 	guess3[2] = guess3[2] + gsl_vector_get(v1, 2);
	// 	gsl_permutation_free (p1);
	// }

	// printf("\n\nfinal solution: %g,%g,%g\n",guess3[0],guess3[1],guess3[2]);
	// calcf1(f1,guess3[0],guess3[1],guess3[2]);
	// 	printf ("\nb = \n");
	// 	gsl_vector_fprintf (stdout, f1, "%g\n");	
	// printf("%g\n",(8*guess3[0]*guess3[0] - 2*guess3[1]));

	// gsl_matrix_free (Df);
	// gsl_vector_free (v);
	// gsl_vector_free (f);
	return 0;
}
