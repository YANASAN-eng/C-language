#ifndef MATRIX_COMPLEX_H_
#define MATRIX__COMPLEX_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <stdbool.h>
#include "complex.h"

typedef struct Matrix {
    int m;
    int n;
    Complex **matrix;
} Matrix;

typedef struct Spaces {
    int n;
    Matrix *spaces;
} Spaces;

Complex** initialize_matrix(int m, int n);
Matrix add(Matrix X, Matrix Y);
Matrix minus(Matrix X, Matrix Y);
Matrix times(Matrix X, Matrix Y);
Matrix scalar(Complex a, Matrix X);
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
Matrix dagger(Matrix X);
Matrix echelon_form(Matrix X);
Matrix Ker(Matrix X);
Matrix eigenspace(Matrix X, Complex lambda);
Matrix projection(Matrix B);
Matrix Im(Matrix X);
Matrix independent(Matrix B1, Matrix B2);
Spaces complement(Spaces S);
Spaces general_eigenspace(Matrix X, Complex lambda);
Complex inner(Matrix X, Matrix Y);
Complex det(Matrix X);
Complex tr(Matrix X);
Complex norm(Matrix X);
int range(Matrix X);
int rank(Matrix X);
void show_matrix(Matrix X);
void show_spaces(Spaces S);

#endif