/*
Julian Keller
julian.keller@wsu.edu
dk.h contains the prototypes for the functions dk.c 
*/

#ifndef DK_H
#define DK_H

#define PI 3.14159265359

double complex horner(double complex x, double complex * a, int degree);
double complex * durandKerner(double complex * coef, double complex * z, int n);
void printIterations(double complex * coef, int n);


#endif