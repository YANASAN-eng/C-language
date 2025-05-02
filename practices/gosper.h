#ifndef GOSPER_H_
#define GOSPER_H_

#include "complex.h"
#include "matrix.h"
#include "polynomial.h"

typedef struct Polynomials {
    int num;
    Polynomial* polynomials;
} Polynomials;

Polynomials gosper(Polynomial f, Polynomial g);
Polynomials gosper_equation(Polynomial p, Polynomial q, Polynomial r);

void show_gosper(Polynomials polys);
#endif