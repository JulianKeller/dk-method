/*
Julian Keller
julian.keller@wsu.edu
Durand-Kerner Method

Press ctrl+D once you are finished entering input
*/

// Remember how to use debugger and visual debugger 


#include <stdio.h>
#include <stdlib.h>
#include <complex.h>	// complex numbers
#include "dk.h"	


/*
From the .pdf
R = the largest absolute value coefficient plus 1
Zj = is which root I am guessing. z[0] = first root, z[1] = second root... where j=0,1...
k = the iteration we are on

*/


// This algorithm is taken from the slides
double horner(double complex x, double * a, int degree){
	// a contains degree+1 values
	double complex p = a[degree];
	for(int i = degree - 1; i >= 0; i--){
		p = a[i] + x * p;
	}
	return p;
}


// // TODO fix all compile errors, as I'm sure there are many
// // TODO add these to .h file
// // Takes coefficient array, n number of coefficients
// int durandKerner(double * coef, int n){

// 	// double eps = 10^-6 // or is it 10e-6 // make sure this is correct way to do the exponent
// 	double *z = calloc(20, sizeof(double));
// 	double *deltaz = calloc(20, sizeof(double));

	
// 	double cmax = coef[0];
// 	// get max abs value in z
// 	for (int i = 1; i < n; i++){
// 		if (abs(coef[i]) >= cmax){		// TODO is the actually absolute value?
// 			cmax = abs(coef[i]);
// 		}	
// 	}

// 	// get initial z guess values
// 	double R = 1 + cmax
// 	for (int j = 0; j < n; j++){
// 		// TODO is this the correct j???
// 		double theta = (j(2*pi)/n);
// 		z[i] = R*cos(theta) + R*I*sin(theta); 		// this is imaginary number I = sqrt(-1)
// 	}

// 	// K is max number of iterations
// 	for (int k = 0; k < 50; k++){
// 		int zmax = 0;
// 		for (int j = 0; j < n; j++){
// 			// compute Qj
// 			// begin with Q = 1
// 			// Q = Q * (z[j] - zi), don't know what 'i' is yet

// 			// detlaz = -f(z[j])/Qj  <--- use horners method for -f(z[j])

// 			// if (abs(deltaz) > zmax){ zmax = abs(deltaz) }

// 		}
// 		for (int j = 0; j < n; j++){
// 			// z[j] = z[j] + deltaz[j]
// 	}

// 	// if(deltaz <= eps){
// 		// return
// 	// }
// 	return 0;
// }


// Method for printing each iteration
void printIterations(double * coef, int n){

	// For now it just prints the list
	for (int i = 0; i < n; i++){
		printf("Got:(%.1f + %.1f I)\n", creal(coef[i]), cimag(coef[i]));
	}
	printf("\n");
}


// TODO will need to use Horners Rule at some point
int main(){

	int n = 0;
	double real ='0'; 
	double imag ='0'; 

	double *coef = calloc(20, sizeof(double complex));		// initialize array of size 20 for coefficient of complex doubles

	// Read input from the user, and add complex numbers to the coefficient list
	while(scanf("%lf %lf", &real, &imag) == 2){
		coef[n] = (real + imag * I);
		n++;
	}

	// array is normalized, add 1 to the end of it
	coef[n] = 1 + 0 * I;

	printIterations(coef, n);
	// double horner(double complex x, double * a, int degree)
	double complex a = horner(3 + 0 * I, coef, n);

	printf("Horner :(%.1f + %.1f I)\n", creal(a), cimag(a));
	free(coef);		// free the memory for the coefficient array
	return 0;
}

