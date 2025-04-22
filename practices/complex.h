#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <math.h>
#include <stdio.h>

// 複素数
typedef struct Complex {
    double x; // 実部
    double y; // 虚部
} Complex;

// 和
Complex complex_add(Complex, Complex);
// 差
Complex complex_minus(Complex, Complex);
// 積
Complex complex_times(Complex, Complex);
// 共役
Complex complex_conjugate(Complex);
// 商
Complex complex_div(Complex, Complex);
// ノルム
double complex_norm(Complex);
// スカラー積
Complex complex_scalar(double a, Complex z);
// 逆数
Complex complex_reciprocal(Complex c);
void show_complex(Complex);

#endif