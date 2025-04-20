#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef struct Polynomial{
    int degree;
    double *coefficients;
    double (*eval)(double x, void *params);
} Polynomial;

double exponentiation(double x, int n);
double polynomial_eval(double x, void *params);
Polynomial make_polynomial(int deg, double *params);

#endif