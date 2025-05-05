#include "gosper.h"

#define upper 100 

Polynomials gosper_transformation(Polynomial f, Polynomial g)
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

Polynomial gosper_equation(Polynomials polys)
{
    Matrix P, Q, R, S, S_shift, Temp;
    Polynomial p, q, r, s;
    p = polys.polynomials[0];
    q = polys.polynomials[1];
    r = polys.polynomials[2];

    P = poly_matrix(p, p.deg + 1, 1);
    Q = poly_matrix(poly_shift(q, 1), p.deg + 1, p.deg - q.deg + 1);
    R = poly_matrix(r, p.deg + 1, p.deg - r.deg + 1);
    S_shift = shift_matrix(p.deg - q.deg + 1, 1);
    Temp = solution(minus(times(Q, S_shift), R), P);
    s.deg = Temp.m - 1;
    int i;
    s.coefficients = malloc(sizeof(Complex) * (s.deg + 1));
    for (i = 0; i < s.deg + 1; i++) {
        s.coefficients[i] = Temp.matrix[i][0];
    }
    return s;
}

Matrix poly_matrix(Polynomial p, int m, int n)
{
    Matrix P;
    P.m = m;
    P.n = n;
    P.matrix = initialize_matrix(P.m, P.n);
    int d = p.deg;
    int i, j;
    for (i = 0; i < P.m; i++) {
        for (j = 0; j < P.n; j++) {
            if (0 <= i - j && i - j <= d) {
                P.matrix[i][j] = p.coefficients[i - j];
            } else {
                P.matrix[i][j] = (Complex){0, 0};
            }
        }
    }
    return P;
}

Matrix shift_matrix(int d, int N)
{
    Matrix S;
    S.m = d;
    S.n = d;
    S.matrix = initialize_matrix(S.m, S.n);
    int i, j;
    for (i = 0; i < S.m; i++) {
        for (j = 0; j < S.n; j++) {
            if(i <= j) {
                S.matrix[i][j] = complex_scalar(combination(j, i), complex_power((Complex){N, 0}, j - i));
            } else {
                S.matrix[i][j] = (Complex){0, 0};
            }
        }
    }
    return S;
}


void show_gosper(Polynomials polys)
{
    int i;
    for (i = 0; i < polys.num; i++) {
        show_polynomial(polys.polynomials[i]);
    }
}