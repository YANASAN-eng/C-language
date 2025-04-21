#include "complex.h"

// 和
Complex complex_add(Complex z1, Complex z2)
{
    Complex z3 = {0, 0};
    z3.x = z1.x + z2.x;
    z3.y = z1.y + z2.y;
    return z3;
}
// 差
Complex complex_minus(Complex z1, Complex z2)
{
    Complex z3 = {0, 0};
    z3.x = z1.x -z2.x;
    z3.y = z1.y -z2.y;
    return z3;
}
// 積
Complex complex_times(Complex z1, Complex z2)
{
    Complex z3 = {0, 0};
    z3.x = z1.x * z2.x - z1.y * z2.y;
    z3.y = z1.x * z2.y + z1.y * z2.x;
    return z3;
}
// 共役
Complex complex_conjugate(Complex z)
{
    Complex w = {0, 0};
    w.x = z.x;
    w.y = -z.y;
    return w;
}
// ノルム
double complex_norm(Complex z)
{
    return sqrt(z.x * z.x + z.y * z.y);
}
// 商
Complex complex_div(Complex z1, Complex z2)
{
    Complex w = {0, 0};
    w = complex_conjugate(z2);
    w.x = w.x / (complex_norm(z2) * complex_norm(z2));
    w.y = w.y / (complex_norm(z2) * complex_norm(z2));

    return complex_times(z1, w);
}
// スカラー倍
Complex complex_scalar(double a, Complex z)
{
    Complex w = {0, 0};
    w.x = a * z.x;
    w.y = a * z.y;

    return w;
}
// 逆数
Complex complex_reciprocal(Complex z)
{
    Complex w = {0, 0};
    w = complex_scalar(1/ (complex_norm(z) * complex_norm(z)), complex_conjugate(z));
    return w;
}
// 表示する。
void show_complex(Complex z)
{
    if (z.y < 0) {
        printf("%f-i%f", z.x, -z.y);
    } else if (z.y == 0) {
        printf("%f", z.x);
    } else {
        printf("%f+i%f", z.x, z.y);
    }
}