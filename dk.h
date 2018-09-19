/*
Julian Keller
julian.keller@wsu.edu
dk.h contains the prototypes for the functions dk.c 
*/

#ifndef DK_H
#define DK_H

double horner(double complex x, double * a, int degree);
int durandKerner(double * coef, double * z, int n);
void printIterations(double * coef, int n);


#endif