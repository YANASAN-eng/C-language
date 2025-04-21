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

Matrix scalar(double a, Matrix X)
{
    Matrix Z = X;
    int i,j;

    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            Z.matrix[i][j] *= a;
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
                for (k = 0; k < j; k++) {
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

double det(Matrix X)
{
    Matrix lu = LU(X);
    double det = 1;
    int i;
    for (i = 0; i < X.n; i++) {
        det *= lu.matrix[i][i + X.n];
    }
    return det;
}

double tr(Matrix X) {
    double tr = 0;
    int i;
    for (i = 0; i < X.n; i++) {
        tr += X.matrix[i][i];
    }
    return tr;
}

double norm(Matrix X)
{
    int i,j;
    double sum = 0;
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            sum += X.matrix[i][j] * X.matrix[i][j];
        }
    }
    return sqrt(sum);
}

double inner(Matrix X, Matrix Y)
{
    double sum = 0;
    int i;
    for (i = 0; i < X.m; i++) {
        sum += X.matrix[i][0] * Y.matrix[i][0];
    }
    return sum;
}

Matrix transe(Matrix X)
{
    Matrix Z = {X.n, X.m};
    Z.matrix = initialize_matrix(Z.m, Z.n);

    int i,j;
    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            Z.matrix[i][j] = X.matrix[j][i];
        }
    }
    return Z;
}

Matrix House(Matrix X)
{
    Matrix H = {X.m, X.m};
    H.matrix = initialize_matrix(H.m, H.n);
    Matrix E = unit(H.m);

    H = minus(E, scalar(2 / inner(X, X), times(X, transe(X))));

    return H;
}

Matrix QR(Matrix X)
{
    Matrix R = X;
    Matrix H = unit(X.m);
    Matrix Temp = {X.m, X.n};
    Temp.matrix = initialize_matrix(Temp.m, Temp.n);
    Matrix E;
    
    int i,j;

    for (i = 0; i < X.m - 1; i++) {
        Matrix temp0 = {X.m - i, 1};
        temp0.matrix = initialize_matrix(temp0.m, temp0.n);
        
        Matrix temp1 = {X.m - i, 1};
        temp1.matrix = initialize_matrix(temp1.m, temp1.n);
        
        for (j = i; j < X.n; j++) {
            temp0.matrix[j - i][0] = R.matrix[j][i];
        }
        for (j = i; j < X.n; j++) {
            if (j == i) {
                temp1.matrix[j - i][0] = norm(temp0); 
            } else {
                temp1.matrix[j - i][0] = 0;
            }
        }
        if (i == 0) {
            Temp = House(minus(temp0, temp1));
            H = Temp;
            R = times(H, R);
        } else {
            E = unit(i);
            Temp = direct_sum(E,House(minus(temp0, temp1)));
            R = times(Temp, R);
            H = times(Temp, H);
        }
    }
    return joint(gauss_jordan(H), R);
}

Matrix QR_repeat(Matrix X, int n)
{
    Matrix Q = {X.m, X.n};
    Q.matrix = initialize_matrix(Q.m, Q.n);
    Matrix R = {X.m, X.n};
    R.matrix = initialize_matrix(R.m, R.n);
    Matrix Y = X;
    Matrix Temp_QR;
    int i, j, k;
    for (i = 0; i < n; i++) {
        Temp_QR = QR(Y);
        for (j = 0; j < Temp_QR.m; j++) {
            for (k = 0; k < Temp_QR.n; k++) {
                if (k < Temp_QR.n / 2) {
                    Q.matrix[j][k] = Temp_QR.matrix[j][k];
                } else {
                    R.matrix[j][k - Temp_QR.n / 2] = Temp_QR.matrix[j][k];
                }
            }
        }
        Y = times(R, Q);
    }
    return Y;
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