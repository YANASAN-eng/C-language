#ifndef TWO_POLYNOMIAL_H_
#define TWO_POLYNOMIAL_H_

#include <stdlib.h>
#include <stdio.h>

#include "complex.h"
#include "functions.h"

typedef struct TwoPolynomial {
    int deg1;
    int deg2;
    Complex** coefficients;
} TwoPolynomial;

TwoPolynomial two_poly_add(TwoPolynomial p, TwoPolynomial q);
TwoPolynomial two_poly_minus(TwoPolynomial p, TwoPolynomial q);
TwoPolynomial two_poly_times(TwoPolynomial p, TwoPolynomial q);
TwoPolynomial two_poly_div(TwoPolynomial p, TwoPolynomial q);

Complex** initialize_two_poly(TwoPolynomial p);

void show_two_polynomial(TwoPolynomial p);

#endif 