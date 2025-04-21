#include <stdio.h>

#include "matrix.h"

int main()
{
    Matrix X = {2, 2};

    Matrix Z;
    
    X.matrix = initialize_matrix(X.m, X.n);

    X.matrix[0][0] = 1;
    X.matrix[0][1] = 2;
    X.matrix[1][0] = 3;
    X.matrix[1][1] = 4;

    Z = LU(X);
    show_matrix(Z);

    printf("%d\n", Z.n);

    return 0;
}