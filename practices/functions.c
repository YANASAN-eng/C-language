#include "functions.h"

double exponentiation(double x, int n)
{
    int i;
    double y = 1;
    for (i = 0; i < n; i++) {
        y *= x;
    }
    return y;
}
 
double polynomial_eval(double x, void *params)
{
    int i;
    double y = 0;
    Polynomial *poly = (Polynomial*)params;
    for (i = 0; i < poly->degree; i++) {
        y += poly->coefficients[i] * exponentiation(x, i);
    }
    return y;

}
Polynomial make_polynomial(int deg, double *params)
{
    Polynomial poly;
    poly.degree = deg;
    poly.coefficients = params;
    poly.eval = polynomial_eval;
    return poly;
}