#include <stdio.h>
#include "functions.h"
#include "newton.h"

int main()
{
    double x = 5;
    double coeffs[] = {-2, 0, 1};
    Polynomial poly = make_polynomial(3, coeffs);

    // 多項式に対してNewton法を実行する。
    // double result = differentiation(poly, poly.eval, x, 0.001);
    double result = newton_method(poly, poly.eval, x, 100, 0.000000001);

    printf("%f\n", poly.eval(x, &poly));
    printf("√2=%f\n", result);
    return 0;
}