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
	double complex p = a[degree];
	for(int i = degree - 1; i >= 0; i--){
		// printf("a[%i]: %.10f + %.10f i\n", i, creal(a[i]), cimag(a[i]));
		p = a[i] + (x * p);
		// printf("p: %.10f + %.10f i\n", creal(p), cimag(p));
	}
	return p;
}



// TODO change deltaz name
// Takes coefficient array, n number of coefficients
double complex * durandKerner(double complex * coef, double complex * z, int n){

	double eps = 10e-6; 		// 10^-6 precision
	double complex deltaz = 0;
	double complex cmax = coef[0];

	// get max abs value using cabs()
	for (int i = 1; i < n; i++){		
		if (cabs(coef[i]) >= cabs(cmax)){	
			cmax = cabs(coef[i]);
		}	
	}

	

	// get initial z guess values
	double complex R = 1 + cabs(cmax);
	for (int j = 0; j < n; j++){
		// TODO is this the correct j???
		double complex theta = (j * (2 * PI)/n);
		z[j] = (R * cos(theta)) + (R * sin(theta) * I); 		// this is imaginary number I = sqrt(-1)
		// printf("z[j]: %.10f + %.10f i\n", creal(z[j]), cimag(z[j]));
	}

	// printIterations(z, n);

	

	// K is max number of iterations
	for (int k = 1; k <= 50; k++){
		double zmax = 0;
		printf("iter %i\n", k);
		for (int j = 0; j < n; j++){

			// Compute Denominator
			double complex Q = 1;				
			for (int i = 0; i < n; i++){
				if (z[j] == z[i]){
					// printf("Skipped z[j] == z[i]\n");
					// printf("Skip! zj[%i]: %.10f + %.10fi, zi[%i]: %.10f + %.10fi\n",j, creal(z[j]), cimag(z[j]), i, creal(z[i]), cimag(z[i]));
					continue;
				}
				if (Q == 0){
					Q = (z[j] - z[i]);
				}
				else{
					Q = Q * (z[j] - z[i]);
				}	
			}

			// printf("Q_%i: %.10f + %.10f i\n", j, creal(Q), cimag(Q));
			
			// printf("z[j]: %.10f + %.10f i\n", creal(z[j]), cimag(z[j]));

			// deltaz = f(z[j])/Qj
			deltaz = (-(horner(z[j], coef, n)))/Q;		

// Correct up to here ----------------------------------------------------------------------------------

			
			// printf("deltaz_%i: %.10f + %.10f i\n", j, creal(deltaz), cimag(deltaz));

			if (cabs(deltaz) > zmax){
				zmax = cabs(deltaz);
			}
			// printf("zmax_%i: %.10f + %.10f i\n", j, creal(zmax), cimag(zmax));



			// for (int j = 0; j < n; j++){
			// 	printf("deltaz: %.10f + %.10f i\n", creal(deltaz), cimag(deltaz));
			// 	z[j] = z[j] + deltaz;
			// 	// printf("z[j]: %.10f + %.10f i\n", creal(z[j]), cimag(z[j]));
			// }

		}


		printIterations(z, n);
		for (int j = 0; j < n; j++){
			// printf("z[j] + deltaz = %.10f + %.10f i + ", creal(z[j]), cimag(z[j]));
			// printf(" %.10f + %.10f i\n", creal(deltaz), cimag(deltaz));
			z[j] = z[j] + deltaz;
			// printf("= z[j]: %.10f + %.10f i\n", creal(z[j]), cimag(z[j]));
		}
		
		// FIXME zmax is increasing, not decreasing! 
		// printf("zmax: %.10f + %.10f i\n", creal(zmax), cimag(zmax));
		if(zmax <= eps){
			return z; 			
		}
		
	}
	return z;
}


// Method for printing each iteration
void printIterations(double complex * z, int n){

	// For now it just prints the list
	for (int i = 0; i < n; i++){
		printf("z[%i] = %.10f + %.10f i\n", i, creal(z[i]), cimag(z[i]));		// prints 10 digits after decimal point
	}
	printf("\n");
}




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
	coef[n] = 1;

	durandKerner(coef, z, n);

	// printIterations(coef, n);
	// double horner(double complex x, double * a, int degree)
	// double complex a = horner(3 + 0 * I, coef, n);

	// printf("Horner :(%.1f + %.1f I)\n", creal(a), cimag(a));
	// double complex a = 1;
	// double complex b = 5 + 0 * I;
	// a = a*b;
	
	// 	printf("nums: %.10f + %.10f i\n", creal(a), cimag(a));
	

	free(coef);		// free the memory for the coefficient array
	free(z);

	return 0;
}


