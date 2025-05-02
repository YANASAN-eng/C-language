#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"


Complex output(Complex z, void *params)
{
    int i;
    Complex w = {0, 0};
    Polynomial *poly = (Polynomial*)params;
    for (i = 0; i < poly->deg + 1; i++) {
        w = complex_add(w, complex_times(poly->coefficients[i], complex_power(z, i)));
    }
    return w;
}

Polynomial poly_add(Polynomial p, Polynomial q)
{
    Focuspolynomial fp;
    Polynomial r;
    fp = max_degree(p, q);
    r.deg = fp.deg;
    r.coefficients = malloc(sizeof(Complex) * (r.deg + 1));
    int i;
    for (i = 0; i < r.deg + 1; i++) {
        if (i < r.deg) {
            r.coefficients[i] = complex_add(p.coefficients[i], q.coefficients[i]);
        } else {
            r.coefficients[i] = fp.poly.coefficients[i];
        }
    }
    return r;
}

Polynomial poly_minus(Polynomial p, Polynomial q)
{
    Focuspolynomial fp;
    Polynomial r;
    fp = max_degree(p, q);
    r.deg = fp.deg;
    r.coefficients = malloc(sizeof(Complex) * (r.deg + 1));
    int i;
    for (i = 0; i < fp.deg + 1; i++) {
        if (i < fp.deg) {
            r.coefficients[i] = complex_add(p.coefficients[i], q.coefficients[i]);
        } else {
            r.coefficients[i] = fp.poly.coefficients[i];
        }
    }
    return r;
}

Polynomial poly_times(Polynomial p, Polynomial q)
{
    Polynomial r;
    r.deg = p.deg + q.deg;
    r.coefficients = malloc(sizeof(Complex) * (r.deg + 1));
    Complex temp = {0, 0};
    int i, j;
    Focuspolynomial fp1 = min_degree(p, q);
    Focuspolynomial fp2 = max_degree(p, q);
    for (i = 0; i < r.deg + 1; i++) {
        temp = (Complex){0, 0};
        for (j = 0; j < fp1.deg + 1 && j <= i; j++) {
            if (i - j < fp2.deg + 1) {
                temp = complex_add(temp, complex_times(fp1.poly.coefficients[j], fp2.poly.coefficients[i - j]));
            }
        }
        r.coefficients[i] = temp;
    }
    return r;
}

Polynomial poly_div(Polynomial p, Polynomial q)
{
    if (p.deg < q.deg) {
        Polynomial r;
        r.deg = 0;
        Complex* c = malloc(sizeof(Complex) * (r.deg + 1));
        c[0] = (Complex){0, 0};
        r.coefficients = c;
        return r;
    } else {
        Polynomial r;
        r.deg = p.deg - q.deg;
        r.coefficients = malloc(sizeof(Complex) * (r.deg + 1));
        Polynomial P, Q, R;
        P = p;
        Q = q;
        int i;
        int count = 0;
        Complex temp;
        while (P.deg >= Q.deg) {
            r.coefficients[r.deg - count] = complex_div(P.coefficients[P.deg], Q.coefficients[Q.deg]);
            for (i = 1; i < Q.deg + 1; i++) {
                temp = complex_minus(P.coefficients[r.deg - i], complex_times(complex_div(P.coefficients[P.deg], Q.coefficients[Q.deg]), Q.coefficients[Q.deg - i]));
                if (temp.x == 0 && temp.y == 0) {
                    count += 1;
                    r.coefficients[r.deg - count] = (Complex){0, 0};
                } else {
                    break;
                }
            }
            R.deg = P.deg - i;
            R.coefficients = malloc(sizeof(Complex) * (R.deg + 1));
            for (i = 0; i < R.deg + 1; i++) {
                if (i < P.deg - Q.deg) {
                    R.coefficients[i] = P.coefficients[i];
                } else {
                    R.coefficients[i] = complex_minus(P.coefficients[i], complex_times(complex_div(P.coefficients[P.deg], Q.coefficients[Q.deg]), Q.coefficients[i- P.deg + Q.deg]));
                }
            }
            count += 1;
            P = R;
        }
        return r;
    }
}

Polynomial poly_remainder(Polynomial p, Polynomial q)
{
    if (p.deg < q.deg) {
        return q;
    } else {
        int deg;
        Polynomial P, Q, R;
        P = p;
        Q = q;
        int i;
        Complex temp;
        while (P.deg >= Q.deg) {
            deg = P.deg - Q.deg;
            for (i = 1; i < Q.deg + 1; i++) {
                temp = complex_minus(P.coefficients[P.deg - i], complex_times(complex_div(P.coefficients[P.deg], Q.coefficients[Q.deg]), Q.coefficients[Q.deg - i]));
                if (temp.x != 0 || temp.y != 0) {
                    break;
                }
            }
            R.deg = P.deg - i;
            R.coefficients = malloc(sizeof(Complex) * (R.deg + 1));
            for (i = 0; i < R.deg + 1; i++) {
                if (i < P.deg - Q.deg) {
                    R.coefficients[i] = P.coefficients[i];
                } else {
                    R.coefficients[i] = complex_minus(P.coefficients[i], complex_times(complex_div(P.coefficients[P.deg], Q.coefficients[Q.deg]), Q.coefficients[i- P.deg + Q.deg]));
                }
            }
            P = R;
        }
        return P;
    }
}

Polynomial Euclid(Polynomial p, Polynomial q)
{
    Polynomial P, Q, Temp;
    P = p;
    Q = q;
    if (P.deg < Q.deg) {
        Temp = P;
        P = Q;
        Q = Temp;
    }
    
    while (poly_remainder(P, Q).deg >= 0) {
        Temp = Q;
        Q = poly_remainder(P, Q);
        P = Temp;
    }
    if (Q.coefficients[0].x == 0 && Q.coefficients[0].y == 0) {
        return P;
    } else {
        return Q;
    }
}

Polynomial poly_shift(Polynomial p, int N)
{
    Polynomial q;
    q.deg = p.deg;
    q.coefficients = malloc(sizeof(Complex) * (q.deg + 1));
    int i, j;
    Complex temp;
    for (i = 0; i < q.deg + 1; i++) {
        temp = (Complex){0, 0};
        for (j = i; j < q.deg + 1; j++) {
            temp = complex_add(temp, complex_times(p.coefficients[j], complex_scalar(combination(j, i), complex_power((Complex){N, 0}, j - i))));
        }
        q.coefficients[i] = temp;
    }
    return q;
}

Focuspolynomial max_degree(Polynomial p, Polynomial q)
{
    Focuspolynomial fp;
    if (p.deg < q.deg) {
        fp.deg = q.deg;
        fp.poly = q;
    } else {
        fp.deg = p.deg;
        fp.poly = p;
    }
    return fp;
}

Focuspolynomial min_degree(Polynomial p, Polynomial q)
{
    Focuspolynomial fp;
    if (p.deg < q.deg) {
        fp.deg = p.deg;
        fp.poly = p;
    } else {
        fp.deg = q.deg;
        fp.poly = q;
    }
    return fp;
}

void show_polynomial(Polynomial p)
{
    int i;
    for (i = p.deg; 0 <= i; i--) {
        if (i != 0) {
            if (p.coefficients[i].y < 0) {
                printf("(%f-i%f)x**%d + ", p.coefficients[i].x, -p.coefficients[i].y, i);
            } else {
                printf("(%f+i%f)x**%d + ", p.coefficients[i].x, p.coefficients[i].y, i);
            }
        } else {
            if (p.coefficients[i].y < 0) {
                printf("(%f-i%f)\n", p.coefficients[i].x, -p.coefficients[i].y);
            } else {
                printf("(%f+i%f)\n", p.coefficients[i].x, p.coefficients[i].y);
            }
        }
    }
    if (p.deg < 0) {
        printf("0\n");
    }
} 