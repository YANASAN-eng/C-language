#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <stdlib.h>
#include "complex.h"
#include "functions.h"

typedef struct Polynomial {
    int deg;
    Complex* coefficients;
} Polynomial;

typedef struct Focuspolynomial {
    int deg;
    Polynomial poly;
} Focuspolynomial;

Complex output(Complex z, void *params);
Polynomial poly_add(Polynomial p, Polynomial q);
Polynomial poly_minus(Polynomial p, Polynomial q);
Polynomial poly_times(Polynomial p, Polynomial q);
Polynomial Euclid(Polynomial p, Polynomial q);
Polynomial poly_div(Polynomial p, Polynomial q);
Polynomial poly_remainder(Polynomial p, Polynomial q);
Polynomial poly_shift(Polynomial p, int N);
Focuspolynomial max_degree(Polynomial p, Polynomial q);
Focuspolynomial min_degree(Polynomial p, Polynomial q);
void show_polynomial(Polynomial p);
#endif