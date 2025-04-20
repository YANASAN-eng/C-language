#include "complex.h"

// 和
Complex add(Complex z1, Complex z2)
{
    Complex z3 = {0, 0};
    z3.x = z1.x + z2.x;
    z3.y = z1.y + z2.y;
    return z3;
}
// 差
Complex minus(Complex z1, Complex z2)
{
    Complex z3 = {0, 0};
    z3.x = z1.x -z2.x;
    z3.y = z1.y -z2.y;
    return z3;
}
// 積
Complex times(Complex z1, Complex z2)
{
    Complex z3 = {0, 0};
    z3.x = z1.x * z2.x - z1.y * z2.y;
    z3.y = z1.x * z2.y + z2.y * z1.x;
    return z3;
}