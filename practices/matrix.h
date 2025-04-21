#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct Matrix {
    int m;
    int n;
    double **matrix;
} Matrix;

double** initialize_matrix(int m, int n);
Matrix add(Matrix X, Matrix Y);
Matrix minus(Matrix X, Matrix Y);
Matrix times(Matrix X, Matrix Y);
Matrix direct_sum(Matrix X, Matrix Y);
Matrix unit(int n);
Matrix joint(Matrix X, Matrix Y);
Matrix gauss_jordan(Matrix X);
Matrix LU(Matrix X);
double norm(Matrix X);
double tr(Matrix X);
double det(Matrix X);
void show_matrix(Matrix X);

#endif