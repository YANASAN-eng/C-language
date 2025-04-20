#ifndef NEWTON_H_
#define NEWTON_H_

#include "functions.h"

// differntation
double differentiation(Polynomial poly, double (*func)(double, void *param), double x, double delta);
// Newton's method
double newton_method(Polynomial poly, double (*func)(double, void *param), double start, int n, double delta);
#endif