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
#include <math.h>
#include "dk.h"	


/*
From the .pdf
R = the largest cabsolute value coefficient plus 1
Zj = is which root I am guessing. z[0] = first root, z[1] = second root... where j=0,1...
k = the iteration we are on

*/


// This algorithm is taken from the slides and modified for array pointers 
double complex horner(double complex x, double complex * a, int degree){
	// a contains degree+1 values
	double complex p;
	for(int i = degree - 1; i >= 0; i--){
		p = a[i] + x * p;
	}
	return p;
	// TODO will need to free p at some point
}


// TODO fix all compile errors, as I'm sure there are many
// TODO change deltaz name
// Takes coefficient array, n number of coefficients
double complex * durandKerner(double complex * coef, double complex * z, int n){

	double eps = 10e-6; 		// 10^-6 precision
	double complex deltaz = 0;
	double complex cmax = coef[0];

	// get max abs value using cabs()
	for (int i = 1; i < n; i++){
		if (cabs(coef[i] - cmax) >= eps){		
			cmax = cabs(coef[i]);
		}	
	}

	// get initial z guess values
	double complex R = 1 + cabs(cmax);
	for (int j = 0; j < n; j++){
		// TODO is this the correct j???
		double complex theta = (j * (2 * PI)/n);
		z[j] = (R * cos(theta)) + (R * sin(theta) * I); 		// this is imaginary number I = sqrt(-1)
	}

	// K is max number of iterations
	for (int k = 0; k < 50; k++){
		double zmax = 0;
		for (int j = 0; j < n; j++){
			double complex Q;				// TODO might need to initialize this
			for (int i = 0; i < n; i++){ 	// compute Qj
				if (cabs(z[i] - z[j]) <= eps){		// if their difference is less than or equal to epsilon they are basically equal
					continue;
				}
				Q = Q * (z[j] - z[i]);
			}
			
			// f(z[j])/Qj
			deltaz = horner(z[j], coef, n)/Q;		// TODO double check this gives correct result
			

			if (cabs(deltaz) > zmax){
				zmax = cabs(deltaz);
			}


			for (int j = 0; j < n; j++){
				z[j] = z[j] + deltaz;
			}

			if(zmax <= eps){
				return z; 			// TODO this might need to be a pointer
			}
			printIterations(z, n);
		}
	}
	return z;
}


// Method for printing each iteration
void printIterations(double complex * z, int n){

	// For now it just prints the list
	for (int i = 0; i < n; i++){
		printf("z[%i] = %.1f + %.1f i)\n", i, creal(z[i]), cimag(z[i]));
	}
	printf("\n");
}


// TODO will need to use Horners Rule at some point
int main(){

	int n = 0;
	double real ='0'; 
	double imag ='0'; 

	double complex *coef = calloc(20, sizeof(double complex));		// initialize array of size 20 for coefficient of complex doubles

	double complex *z = calloc(20, sizeof(double complex));

	// Read input from the user, and add complex numbers to the coefficient list
	while(scanf("%lf %lf", &real, &imag) == 2){
		coef[n] = (real + imag * I);
		n++;
	}

	// array is normalized, add 1 to the end of it
	coef[n] = 1 + 0 * I;

	durandKerner(coef, z, n);

	
	// printIterations(coef, n);
	// double horner(double complex x, double * a, int degree)
	// double complex a = horner(3 + 0 * I, coef, n);

	// printf("Horner :(%.1f + %.1f I)\n", creal(a), cimag(a));
	// printf("eps: %lf", 10e-6);

	free(coef);		// free the memory for the coefficient array
	free(z);

	return 0;
}


