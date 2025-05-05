#ifndef GOSPER_H_
#define GOSPER_H_

#include "complex.h"
#include "matrix_complex.h"
#include "polynomial.h"

typedef struct Polynomials {
    int num;
    Polynomial* polynomials;
} Polynomials;

Polynomials gosper_transformation(Polynomial f, Polynomial g);
Polynomial gosper_equation(Polynomials polys);
Matrix poly_matrix(Polynomial p, int m, int n);
Matrix shift_matrix(int d, int N);

void show_gosper(Polynomials polys);
#endif