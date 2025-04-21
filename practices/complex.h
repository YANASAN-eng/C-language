#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <math.h>

// 複素数
typedef struct Complex {
    double x; // 実部
    double y; // 虚部
} Complex;

// 和
Complex add(Complex, Complex);
// 差
Complex minus(Complex, Complex);
// 積
Complex times(Complex, Complex);
// 共役
Complex conjugate(Complex);
// ノルム
double norm(Complex);
#endif