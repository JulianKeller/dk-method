/*
Julian Keller
julian.keller@wsu.edu
Durand-Kerner Method


This program is used to find the roots of a polynomial using the Durand-Kerner Method. The program accepts
complex numbers as floating point pairs. The input -5 0 represents -5.0 + 0i. This input will be the coefficient
of a normalized polynomial. The first coefficient of 1 is not needed to be entered as it is assumed.

Press ctrl+D once you are finished entering input to let the console know you have finished entering input.
*/



#include <stdio.h>
#include <stdlib.h>
#include <complex.h>	// complex numbers
#include <math.h>
#include "dk.h"	



// Compute the function for the given value of x using Horners Method. This algorithm is taken from 
// the slides and modified for array pointers 
double complex horner(double complex x, double complex * a, int degree){
	// a contains degree+1 values
	double complex p = a[degree];
	for(int i = degree - 1; i >= 0; i--){
		p = a[i] + (x * p);
	}
	return p;
}


// Finds the roots of the function using the Durand-Kerner Method
double complex * durandKerner(double complex * coef, double complex * z, int n){

	double complex *deltaz = calloc(20, sizeof(double complex));
	double eps = 10e-7; 		// 10^-6 precision
	double complex cmax = coef[0];

	// get max absolute value using cabs()
	for (int i = 1; i < n; i++){		
		if (cabs(coef[i]) >= cabs(cmax)){	
			cmax = cabs(coef[i]);
		}	
	}

	// Compute initial guess values
	double complex R = 1 + cabs(cmax);
	for (int j = 0; j < n; j++){
		double complex theta = (j * (2 * PI)/n);
		z[j] = (R * cos(theta)) + (R * sin(theta) * I); 		// this is imaginary number I = sqrt(-1)
	}

	// K is max number of iterations
	for (int k = 1; k <= 50; k++){
		double zmax = 0;
		printf("iter %i\n", k);
		
		for (int j = 0; j < n; j++){

			// Compute the Denominator
			double complex Q = 1;				
			for (int i = 0; i < n; i++){
				if (z[j] == z[i]){continue;
				}
				if (Q == 0){
					Q = (z[j] - z[i]);
				}
				else{
					Q = Q * (z[j] - z[i]);
				}	
			}

			// Compute the next iteration, deltaz[j] = z[j] - (f(z[j])/Qj)
			deltaz[j] = z[j] -(horner(z[j], coef, n)/Q);		

			// get the largest difference between z[j] and next iteration of z[j]
			if (cabs(z[j] - deltaz[j]) > zmax){
				zmax = cabs(z[j] - deltaz[j]);
			}
		}

		printIterations(z, n);
		// update the values for the next iteration
		for (int j = 0; j < n; j++){
			z[j] = deltaz[j];
		}

		// if the maximum difference is less than epsilon return
		if(eps >= zmax){
			return z; 			
		}
		
	}
	free(deltaz);
	return z;
}


// Method for printing each iteration of z values
void printIterations(double complex * z, int n){
	for (int i = 0; i < n; i++){
		printf("z[%i] = %.10f + %.10f i\n", i, creal(z[i]), cimag(z[i]));	// prints 10 digits after decimal point
	}
}

// TODO check for memory leaks
// TODO finish README
int main(){

	int n = 0;
	double real ='0'; 
	double imag ='0'; 
	double complex *coef = calloc(20, sizeof(double complex));
	double complex *z = calloc(20, sizeof(double complex));

	// Read input from the user, and add complex numbers to the coefficient list
	while(scanf("%lf %lf", &real, &imag) == 2){
		coef[n] = (real + imag * I);
		n++;
	}

	// array is normalized, so 1 needs to be added the end of it
	coef[n] = 1;

	durandKerner(coef, z, n);
	
	// free the memory for the arrays
	free(coef);		
	free(z);

	return 0;
}
