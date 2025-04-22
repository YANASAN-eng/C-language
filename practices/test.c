#include <stdio.h>

#include "complex.h"
#include "matrix_complex.h"

int main()
{
    Matrix X = {3, 3};
    Matrix H;
    
    X.matrix = initialize_matrix(X.m, X.n);

    X.matrix[0][0] = (Complex){1, 0};
    X.matrix[0][1] = (Complex){2, 0};
    X.matrix[0][2] = (Complex){-3, 0};
    X.matrix[1][0] = (Complex){1, 0};
    X.matrix[1][1] = (Complex){2, 0};
    X.matrix[1][2] = (Complex){-3, 0};
    X.matrix[2][0] = (Complex){1, 0};
    X.matrix[2][1] = (Complex){2, 0};
    X.matrix[2][2] = (Complex){-3, 0};

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
    
    // printf("--------------------------------------------------\n");
    // show_matrix(Test);
    // printf("--------------------------------------------------\n");
    // show_matrix(times(Q, R));
    // printf("--------------------------------------------------\n");
    // show_matrix(House(X));
    // printf("--------------------------------------------------\n");
    // show_matrix(QR_repeat(X, 10000));
    // printf("--------------------------------------------------\n");
    // show_matrix(echelon_form(X));
    // printf("--------------------------------------------------\n");
    // show_matrix(Ker(X));
    // printf("--------------------------------------------------\n");
    // show_matrix(X);
    printf("--------------------------------------------------\n");
    show_matrix(Ker(X));
    printf("--------------------------------------------------\n");
    show_matrix(projection(Ker(X)));
    printf("--------------------------------------------------\n");
    show_matrix(echelon_form(projection(Ker(X))));
    return 0;
}