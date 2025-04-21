#include <stdio.h>

#include "matrix.h"

int main()
{
    Matrix X = {3, 3};
    Matrix H;
    
    X.matrix = initialize_matrix(X.m, X.n);

    X.matrix[0][0] = 6;
    X.matrix[0][1] = -3;
    X.matrix[0][2] = 5;
    X.matrix[1][0] = -1;
    X.matrix[1][1] = 4;
    X.matrix[1][2] = -5;
    X.matrix[2][0] = -3;
    X.matrix[2][1] = 3;
    X.matrix[2][2] = -4;


    // Matrix Test = QR(X);

    // Matrix Q = {3, 3};
    // Matrix R = {3, 3};
    // Q.matrix = initialize_matrix(Q.m, Q.n);
    // R.matrix = initialize_matrix(R.m, R.n);

    // int i, j;
    // for (i = 0; i < Test.m; i++) {
    //     for (j = 0; j < Test.n; j++) {
    //         if (j < Test. n / 2) {
    //             Q.matrix[i][j] = Test.matrix[i][j];
    //         } else {
    //             R.matrix[i][j - Test.n / 2] = Test.matrix[i][j];
    //         }
    //     }
    // }
    
    // show_matrix(Test);
    // show_matrix(times(Q, R));


    // show_matrix(House(X));

    show_matrix(QR_repeat(X, 50));
    return 0;
}