#include "matrix.h"

double** initialize_matrix(int m, int n)
{
    int i;
    double** matrix;
    matrix = malloc(sizeof(double *) * m);
    for (i = 0; i < m; i++) {
        matrix[i] = malloc(sizeof(double) * n);
    }
    return matrix;
}

Matrix add(Matrix X, Matrix Y)
{
    int i,j;
    Matrix Z;
    Z.m = X.m;
    Z.n = X.n;
    Z.matrix = initialize_matrix(Z.m, Z.n);
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            Z.matrix[i][j] = X.matrix[i][j] + Y.matrix[i][j]; 
        }
    }
    return Z;
}

Matrix minus(Matrix X, Matrix Y)
{
    int i,j;
    Matrix Z;
    Z.m = X.m;
    Z.n = X.n;
    Z.matrix = initialize_matrix(Z.m, Z.n);
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            Z.matrix[i][j] = X.matrix[i][j] - Y.matrix[i][j]; 
        }
    }
    return Z;
}

Matrix times(Matrix X, Matrix Y)
{
    Matrix Z;
    Z.m = X.m;
    Z.n = Y.n;
    Z.matrix = initialize_matrix(Z.m, Z.n);
    
    int i, j, k;
    double sum = 0;

    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            for (k = 0; k < X.n; k++) {
                sum += X.matrix[i][k] * Y.matrix[k][j];
            }
            Z.matrix[i][j] = sum;
            sum = 0;
        }
    }

    return Z;
}

Matrix direct_sum(Matrix X, Matrix Y)
{
    Matrix Z = {X.m + Y.m, X.n + Y.n};
    Z.matrix = initialize_matrix(Z.m, Z.n);

    int i,j;
    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            if (i < X.m && j < X.n) {
                Z.matrix[i][j] = X.matrix[i][j];
            } else if (i < X.m && X.n <= j) {
                Z.matrix[i][j] = 0;
            } else if (X.m <= i && j < X.n) {
                Z.matrix[i][j] = 0;
            } else {
                Z.matrix[i][j] = Y.matrix[i-X.m][j-X.n];
            }
        }
    }

    return Z;
}

Matrix unit(int n)
{
    Matrix E = {n, n};
    E.matrix = initialize_matrix(E.m, E.n);

    int i,j;

    for (i = 0; i < E.m; i++) {
        for (j = 0; j < E.n; j++) {
            if (i == j) {
                E.matrix[i][j] = 1;
            } else {
                E.matrix[i][j] = 0;
            }
        }
    }
    return E;
}

Matrix joint(Matrix X, Matrix Y)
{
    Matrix Z = {X.m, X.n + Y.n};
    Z.matrix = initialize_matrix(Z.m, Z.n);
    
    int i,j;

    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            if (j < X.n) {
                Z.matrix[i][j] = X.matrix[i][j];
            } else {
                Z.matrix[i][j] = Y.matrix[i][j-X.n];
            }
        }
    }
    return Z;
}

Matrix gauss_jordan(Matrix X)
{
    Matrix E = unit(X.m);

    Matrix Z = joint(X, E);

    int i,j,k;
    for (i = 0; i < Z.m; i++) {
        if (Z.matrix[i][i] == 0) {
            for (j = i + 1; j < Z.m; j++) {
                if (Z.matrix[j][i] != 0) {
                    double *temp = malloc(sizeof(double) * Z.n);
                    for (k = 0; k < Z.n; k++) {
                        temp[k] = Z.matrix[i][k];
                    }
                    for (k = 0; k < Z.n; k++) {
                        Z.matrix[i][k] = Z.matrix[j][k];
                        Z.matrix[j][k] = temp[k]; 
                    }
                    break;
                }
            }
        }
        double temp = Z.matrix[i][i];
        for (k = 0; k < Z.n; k++) {
            Z.matrix[i][k] = Z.matrix[i][k] / temp;
        }
        for (j = 0; j < Z.m; j++) {
            temp = Z.matrix[j][i];
            for (k = 0; k < Z.n; k++) {
                if (j != i) {
                    Z.matrix[j][k] -= temp * Z.matrix[i][k];
                }
            }
        }
    }

    Matrix result = {X.m, X.n};
    result.matrix = initialize_matrix(result.m, result.n);

    for (i = 0; i < X.m; i ++) {
        for (j = 0; j < X.n; j++) {
            result.matrix[i][j] = Z.matrix[i][j + X.n];
        }
    }
    return result;
}

Matrix LU(Matrix X)
{
    Matrix L = {X.m, X.n};
    Matrix U = {X.m, X.n};

    L.matrix = initialize_matrix(L.m, L.n);
    U.matrix = initialize_matrix(U.m, U.n);

    int i, j, k;
    double sum = 0;
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            if (i == 0) {
                if (i == j) {
                    L.matrix[i][j] = 1;
                    U.matrix[i][j] = X.matrix[i][j];
                } else {
                    L.matrix[i][j] = 0;
                    U.matrix[i][j] = X.matrix[i][j];
                }
            } else if (i > j) {
                sum = 0;
                for (k = 0; k < j - 1; k++) {
                    sum += L.matrix[i][k] * U.matrix[k][j];
                }
                L.matrix[i][j] = (X.matrix[i][j] - sum) / U.matrix[j][j];
                U.matrix[i][j] = 0;
            } else if (i == j) {
                sum = 0;
                L.matrix[i][j] = 1;
                for (k = 0; k < i; k++) {
                    sum += L.matrix[i][k] * U.matrix[k][j]; 
                }
                U.matrix[i][j] = X.matrix[i][j] - sum;
            } else {
                sum = 0;
                L.matrix[i][j] = 0;
                for (k = 0; k < i; k++) {
                    sum += L.matrix[i][k] * U.matrix[k][j]; 
                }
                U.matrix[i][j] = X.matrix[i][j] - sum;
            }
        }
    }

    Matrix result = joint(L, U);
    return result;
}
void show_matrix(Matrix X)
{
    int i, j;
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            printf("%f ", X.matrix[i][j]);
            if (j == X.n - 1) {
                printf("\n");
            }
        }
    }
}