#include <stdio.h>

#include "matrix.h"

int main()
{
    Matrix X = {3, 3};

    Matrix Z;
    
    X.matrix = initialize_matrix(X.m, X.n);

    X.matrix[0][0] = 1;
    X.matrix[0][1] = 4;
    X.matrix[0][2] = 6;
    X.matrix[1][0] = 2;
    X.matrix[1][1] = 10;
    X.matrix[1][2] = 17;
    X.matrix[2][0] = 3;
    X.matrix[2][1] = 16;
    X.matrix[2][2] = 31;

    Z = LU(X);
    show_matrix(Z);

    printf("detX=%f\n", det(X));
    printf("trX=%f\n", tr(X));

    return 0;
}