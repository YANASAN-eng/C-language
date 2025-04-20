#include "newton.h"

double differentiation(Polynomial poly, double (*func)(double, void *poly), double x, double delta)
{
    double d = (func(x + delta, &poly) - func(x, &poly)) / delta;
    return d;
}

double newton_method(Polynomial poly, double (*func)(double, void *poly), double start, int n, double delta)
{
    double end = start;
    int i;
    for (i = 0; i < n; i++) {
        end -= func(end, &poly) / differentiation(poly, func, end, delta);
    }
    return end;
}
