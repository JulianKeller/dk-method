# dk-method
This project in an implementation of the Durand-Kerner root finding method. Passing in the coefficients of a normalized polynomial the program will print out the roots of the polynomial as well as each iterative result on the way.It is written as part of Numerical Computing (CS 330) at Washington State University Vancouver. 

## Getting Started

These instructions will get you a copy of the project running on your local machine.

### Prerequisites

C and GCC, it is recommended to run the program on a Mac or Linux machine.

### Installing

Download the program and navigate to the source folder via command terminal. 
Compile with:
```
gcc -g -std=c99 -Wall dk.c -o dk -lm
```

## Running the program

Run with:
```
./dk
```

The function f(x) = z^3 - 3z^2 + 3z - 5 would be entered as a set of complex floating point pairs:
```
-5 0
3 0
-3 0
```
Please note that the polynomial is normalized and the first coefficient of z^3 (which is 1) does not need to be passed in.

## Details

The program will run until the root is computed with 6 digits of precision or 50 iterations, whichever comes first.
 
## Author

* **Julian Keller**  - [JulianKeller](https://github.com/JulianKeller)


