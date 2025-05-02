#include "gosper.h"

#define upper 100 

Polynomials gosper(Polynomial f, Polynomial g)
{
    Polynomials polys;
    polys.num = 3;
    polys.polynomials = malloc(sizeof(Polynomial) * polys.num);
    Polynomial p, q, r, d;
    p.deg = 0;
    p.coefficients = malloc(sizeof(Complex) * (p.deg + 1));
    p.coefficients[0] = (Complex){1, 0};
    q = f;
    r = g;
    int N = 0;
    int i;
    while (N < upper) {
        d = Euclid(q, poly_shift(r, N));
        if (d.deg != 0) {
            for (i = 0; i < N; i ++) {
                p = poly_times(p, poly_shift(r, i + 1));
            }
            q = poly_div(q, d);
            r = poly_div(poly_shift(r, N), d);
            N = 0;
        } else {
            N += 1;
        } 
    }
    polys.polynomials[0] = p;
    polys.polynomials[1] = q;
    polys.polynomials[2] = r;
    return polys;
}

// Polynomial gosper_equation(Polynomial p, Polynomial q, Polynomial r)
// {
//     if (q.deg == r.deg) {
        
//     } else if (q.deg > r.deg) {

//     } else {

//     }
// }

void show_gosper(Polynomials polys)
{
    int i;
    for (i = 0; i < polys.num; i++) {
        show_polynomial(polys.polynomials[i]);
    }
}