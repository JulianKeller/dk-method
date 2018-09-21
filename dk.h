/*
Durand-Kerner Method
Written by: Julian Keller
Contact: julian.keller@wsu.edu
Last Updated: Sept 21, 2018

dk.h contains the prototypes for the functions dk.c
*/

#ifndef DK_H
#define DK_H

#define PI 3.14159265358979323846264338327950288

double complex horner(double complex x, double complex * a, int degree);
double complex * durandKerner(double complex * coef, double complex * z, int n);
void printIterations(double complex * coef, int n);

#endif
