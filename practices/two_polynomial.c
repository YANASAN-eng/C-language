#include "two_polynomial.h"


Complex** initialize_two_poly(TwoPolynomial p)
{
    Complex ** coefficients;
    coefficients = malloc(sizeof(Complex*) * (p.deg1 + 1));
    int i;
    for (i = 0; i < p.deg1 + 1; i ++) {
        coefficients[i] = malloc(sizeof(Complex) * (p.deg2 + 1));
    }
    return coefficients;
}


TwoPolynomial two_poly_add(TwoPolynomial p, TwoPolynomial q)
{
    TwoPolynomial r;
    if (p.deg1 < q.deg1) {
        r.deg1 = q.deg1;
    } else {
        r.deg1 = p.deg1;
    }
    if (p.deg2 < q.deg2) {
        r.deg2 = q.deg2;
    } else {
        r.deg2 = p.deg2;
    }
    r.coefficients = initialize_two_poly(r);
    int i, j;
    for (i = 0; i < r.deg1 + 1; i++) {
        for (j = 0; j < r.deg2 + 1; j++) {
            if ((i < p.deg1 + 1 && j < p.deg2 + 1) && (i < q.deg1 + 1 && j < q.deg2 + 1)) {
                r.coefficients[i][j] = complex_add(p.coefficients[i][j], q.coefficients[i][j]);
            } else if ((i < p.deg1 + 1 && j < p.deg2 + 1) && (q.deg1 + 1 <= i || q.deg2 + 1 <= j)) {
                r.coefficients[i][j] = p.coefficients[i][j];
            } else if ((p.deg1 + 1 <= i || p.deg2 + 1 <= j) && (i < q.deg1 + 1 && j < q.deg2 + 1)) {
                q.coefficients[i][j] = p.coefficients[i][j];
            }
        }
    }
    return r;
}

TwoPolynomial two_poly_minus(TwoPolynomial p, TwoPolynomial q)
{
    TwoPolynomial r;
    if (p.deg1 < q.deg1) {
        r.deg1 = q.deg1;
    } else {
        r.deg1 = p.deg1;
    }
    if (p.deg2 < q.deg2) {
        r.deg2 = q.deg2;
    } else {
        r.deg2 = p.deg2;
    }
    r.coefficients = initialize_two_poly(r);
    int i, j;
    for (i = 0; i < r.deg1 + 1; i++) {
        for (j = 0; j < r.deg2 + 1; j++) {
            if ((i < p.deg1 + 1 && j < p.deg2 + 1) && (i < q.deg1 + 1 && j < q.deg2 + 1)) {
                r.coefficients[i][j] = complex_minus(p.coefficients[i][j], q.coefficients[i][j]);
            } else if ((i < p.deg1 + 1 && j < p.deg2 + 1) && (q.deg1 + 1 <= i || q.deg2 + 1 <= j)) {
                r.coefficients[i][j] = p.coefficients[i][j];
            } else if ((p.deg1 + 1 <= i || p.deg2 + 1 <= j) && (i < q.deg1 + 1 && j < q.deg2 + 1)) {
                q.coefficients[i][j] = complex_scalar(-1, p.coefficients[i][j]);
            }
        }
    }
    return r;
}

TwoPolynomial two_poly_times(TwoPolynomial p, TwoPolynomial q)
{
    TwoPolynomial r;
    r.deg1 = p.deg1 + q.deg1;
    r.deg2 = p.deg2 + q.deg2;
    r.coefficients = initialize_two_poly(r);
    int i, j, k, l;
    Complex temp;
    for (i = 0; i < r.deg1 + 1; i++) {
        for (j = 0; j < r.deg2 + 1; j++) {
            temp = (Complex){0, 0};
            for (k = 0; k < i; k++) {
                for (l = 0; l < j; l++) {
                    if (k < p.deg1 + 1 && i - k < q.deg1 + 1 && l < p.deg2 + 1 && j - l < q.deg2 + 1) {
                        temp = complex_add(temp, complex_times(p.coefficients[k][l], q.coefficients[i-k][j-l]));
                    }
                }
            }
            r.coefficients[i][j] = temp;
        }
    }
    return r;
}

TwoPolynomial two_poly_div(TwoPolynomial p, TwoPolynomial q)
{
    TwoPolynomial r, P;
    int i, num1, num2, pdeg1, pdeg2;
    Complex temp;
    if (p.deg1 < q.deg1 || p.deg2 < q.deg2) {
        r.deg1 = 0;
        r.deg2 = 0;
        r.coefficients = initialize_two_poly(r);
        return r;
    } else {
        r.deg1 = p.deg1 - q.deg1;
        r.deg2 = p.deg2 - q.deg2;
        r.coefficients = initialize_two_poly(r);
        P = p;
        pdeg1 = P.deg1;
        pdeg2 = P.deg2;
        num1 = r.deg1;
        num2 = r.deg2;
        while (num1 >= 0) {
            pdeg2 = P.deg2;
            temp = complex_div(P.coefficients[pdeg1][pdeg2], q.coefficients[q.deg1][q.deg2]);
            if (num1 == r.deg1 && temp.x == 0 && temp.y == 0) {
                for (i = 0; i < pdeg2; i++) {
                    pdeg2 -= 1; 
                    temp = complex_div(P.coefficients[pdeg1][pdeg2], q.coefficients[q.deg1][q.deg2]);
                    if (temp.x != 0 || temp.y != 0) {
                        num2 -= 1;
                        break;
                    }
                }
            }
            r.coefficients[num1][num2] = temp;

            num2 = r.deg2 - 1;
            for (i = 0; i < r.deg2 - P.deg2 + q.deg2; i++) {
                num2 -= 1;
                r.coefficients[num1][num2] = (Complex){0, 0};
            }
            while (0 < num2) {
                temp = complex_minus(P.coefficients[P.deg1][num2 - q.deg2], complex_times(complex_div(P.coefficients[pdeg1][pdeg2], q.coefficients[q.deg1][q.deg2]), q.coefficients[q.deg2][num2 - pdeg2 + 2 * q.deg2]));
                if (temp.x == 0 && temp.y == 0) {
                    num2 -= 1;
                    r.coefficients[num1][num2] = (Complex){0, 0};
                } else {
                    for (i = 0; i < P.deg2; i++) {
                        if (P.deg2 - q.deg2 < i) {
                            P.coefficients[pdeg1][i] = complex_minus(P.coefficients[pdeg1][i], complex_times(complex_div(P.coefficients[pdeg1][pdeg2], q.coefficients[q.deg1][q.deg2]), q.coefficients[q.deg2][i - pdeg2 + q.deg2]));
                        }
                    }
                    pdeg2 = num2 - q.deg2;
                    r.coefficients[num1][num2] = complex_div(P.coefficients[pdeg1][pdeg2], q.coefficients[q.deg1][q.deg2]);
                    num2 -= 1;
                }
            }
            num1 -= 1;
            P.deg1 -= 1;
            pdeg1 = P.deg1;
        }
    }
    return r;
}

void show_two_polynomial(TwoPolynomial p)
{
    int i, j;
    for (i = 0; i < p.deg1 + 1; i++) {
        for (j = 0; j < p.deg2 + 1; j++) {
            if (i != p.deg1) {
                if (j != p.deg2) {
                    if (p.coefficients[i][j].y < 0) {
                        printf("(%f-i%f)x^{%d}y^{%d} + ",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    } else {
                        printf("(%f+i%f)x^{%d}y^{%d} + ",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    }
                } else {
                    if (p.coefficients[i][j].y < 0) {
                        printf("(%f-i%f)x^{%d}y^{%d} + \n",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    } else {
                        printf("(%f+i%f)x^{%d}y^{%d} + \n",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    }
                }
            } else {
                if (j != p.deg2) {
                    if (p.coefficients[i][j].y < 0) {
                        printf("(%f-i%f)x^{%d}y^{%d} + ",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    } else {
                        printf("(%f+i%f)x^{%d}y^{%d} + ",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    }
                } else {
                    if (p.coefficients[i][j].y < 0) {
                        printf("(%f-i%f)x^{%d}y^{%d}\n",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    } else {
                        printf("(%f+i%f)x^{%d}y^{%d}\n",p.coefficients[i][j].x, -p.coefficients[i][j].y, i, j);
                    }
                }
            }
        }
    }
}