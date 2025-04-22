#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include "complex.h"

typedef struct Matrix {
    int m;
    int n;
    double **matrix;
} Matrix;

double** initialize_matrix(int m, int n);
Matrix add(Matrix X, Matrix Y);
Matrix minus(Matrix X, Matrix Y);
Matrix times(Matrix X, Matrix Y);
Matrix scalar(double a, Matrix X);
Matrix direct_sum(Matrix X, Matrix Y);
Matrix unit(int n);
Matrix joint(Matrix X, Matrix Y);
Matrix gauss_jordan(Matrix X);
Matrix LU(Matrix X);
Matrix transe(Matrix X);
Matrix House(Matrix X);
Matrix QR(Matrix X);
Matrix dissenbly(Matrix X);
Matrix QR_repeat(Matrix X, int n);
Matrix echelon_form(Matrix X);
double inner(Matrix X, Matrix Y);
double det(Matrix X);
double tr(Matrix X);
double norm(Matrix X);
int range(Matrix X);

void show_matrix(Matrix X);

#endif