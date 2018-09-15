/*
Julian Keller
julian.keller@wsu.edu
Durand-Kerner Method

Press ctrl+D once you are finished entering input
*/

// Remember how to use debugger and visual debugger 


#include <stdio.h>
#include <complex.h>	// complex numbers
#include "dk.h"	

int main(){

	// TODO Readin numbers from stdin using scanf as ASCII floating point

	// DO i need to use double?
	float i ='\0'; 		// integer and decimal
	float d ='\0'; 

	// how do I want to store the coefficients?
	// use %lf for reading in doubles
	while(scanf("%f %f", &i, &d) == 2){
		printf("Result %f %f\n", i, d);
	}


	printf("%f %f\n", i, d);


	return 0;
}

