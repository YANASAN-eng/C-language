#include "matrix_complex.h"

#define THRESHOLD 1e-10

Complex** initialize_matrix(int m, int n)
{
    int i;
    Complex** matrix;
    matrix = malloc(sizeof(Complex *) * m);
    for (i = 0; i < m; i++) {
        matrix[i] = malloc(sizeof(Complex) * n);
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
            Z.matrix[i][j] = complex_add(X.matrix[i][j], Y.matrix[i][j]); 
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
            Z.matrix[i][j] = complex_minus(X.matrix[i][j], Y.matrix[i][j]); 
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
    Complex sum = (Complex){0, 0};

    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            for (k = 0; k < X.n; k++) {
                sum = complex_add(sum, complex_times(X.matrix[i][k], Y.matrix[k][j]));
            }
            Z.matrix[i][j] = sum;
            sum = (Complex){0, 0};
        }
    }

    return Z;
}

Matrix scalar(Complex a, Matrix X)
{
    Matrix Z = {X.m, X.n};
    Z.matrix = initialize_matrix(Z.m, Z.n);
    int i,j;

    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            Z.matrix[i][j] = X.matrix[i][j];
        }
    }
    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            Z.matrix[i][j] = complex_times(a, Z.matrix[i][j]);
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
                Z.matrix[i][j] = (Complex){0, 0};
            } else if (X.m <= i && j < X.n) {
                Z.matrix[i][j] = (Complex){0, 0};
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
                E.matrix[i][j] = (Complex){1, 0};
            } else {
                E.matrix[i][j] = (Complex){0, 0};
            }
        }
    }
    return E;
}

Matrix joint(Matrix X, Matrix Y)
{
    Matrix Z;
    
    int i,j;

    if (X.m != 0 && X.n != 0 && Y.m != 0 && Y.n != 0) {
        Z = (Matrix){X.m, X.n + Y.n};
        Z.matrix = initialize_matrix(Z.m, Z.n);
        for (i = 0; i < Z.m; i++) {
            for (j = 0; j < Z.n; j++) {
                if (j < X.n) {
                    Z.matrix[i][j] = X.matrix[i][j];
                } else {
                    Z.matrix[i][j] = Y.matrix[i][j-X.n];
                }
            }
        }
    } else if (X.m != 0 && X.n != 0 && Y.m == 0 && Y.n == 0){
        Z = (Matrix){X.m, X.n};
        Z.matrix = initialize_matrix(Z.m, Z.n);
        for (i = 0; i < Z.m; i++) {
            for (j = 0; j < Z.n; j++) {
                Z.matrix[i][j] = X.matrix[i][j];
            }
        }
    } else if (X.m == 0 && X.n == 0 && Y.m != 0 && Y.n != 0) {
        Z = (Matrix){Y.m, Y.n};
        Z.matrix = initialize_matrix(Z.m, Z.n);
        for (i = 0; i < Z.m; i++) {
            for (j = 0; j < Z.n; j++) {
                Z.matrix[i][j] = Y.matrix[i][j];
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
        if (Z.matrix[i][i].x == 0 && Z.matrix[i][i].y == 0) {
            for (j = i + 1; j < Z.m; j++) {
                if (Z.matrix[j][i].x != 0 || Z.matrix[j][i].y != 0) {
                    Complex *temp = malloc(sizeof(Complex) * Z.n);
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
        Complex temp = Z.matrix[i][i];
        for (k = 0; k < Z.n; k++) {
            Z.matrix[i][k] = complex_div(Z.matrix[i][k], temp);
        }
        for (j = 0; j < Z.m; j++) {
            temp = Z.matrix[j][i];
            for (k = 0; k < Z.n; k++) {
                if (j != i) {
                    Z.matrix[j][k] = complex_minus(Z.matrix[j][k], complex_times(temp, Z.matrix[i][k]));
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
    Complex sum = (Complex){0, 0};
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            if (i == 0) {
                if (i == j) {
                    L.matrix[i][j] = (Complex){1, 0};
                    U.matrix[i][j] = X.matrix[i][j];
                } else {
                    L.matrix[i][j] = (Complex){0, 0};
                    U.matrix[i][j] = X.matrix[i][j];
                }
            } else if (i > j) {
                sum = (Complex){0, 0};
                for (k = 0; k < j; k++) {
                    sum = complex_add(sum, complex_times(L.matrix[i][k], U.matrix[k][j]));
                }
                L.matrix[i][j] = complex_div(complex_minus(X.matrix[i][j], sum), U.matrix[j][j]);
                U.matrix[i][j] = (Complex){0, 0};
            } else if (i == j) {
                sum = (Complex){0, 0};
                L.matrix[i][j] = (Complex){1, 0};
                for (k = 0; k < i; k++) {
                    sum = complex_add(sum, complex_times(L.matrix[i][k], U.matrix[k][j])); 
                }
                U.matrix[i][j] = complex_minus(X.matrix[i][j], sum);
            } else {
                sum = (Complex){0, 0};
                L.matrix[i][j] = (Complex){0, 0};
                for (k = 0; k < i; k++) {
                    sum = complex_add(sum, complex_times(L.matrix[i][k], U.matrix[k][j])); 
                }
                U.matrix[i][j] = complex_minus(X.matrix[i][j], sum);
            }
        }
    }

    Matrix result = joint(L, U);
    return result;
}

Complex det(Matrix X)
{
    Matrix lu = LU(X);
    Complex det = {1, 0};
    int i;
    for (i = 0; i < X.n; i++) {
        det = complex_times(det, lu.matrix[i][i + X.n]);
    }
    return det;
}

Complex tr(Matrix X) {
    Complex tr = {0, 0};
    int i;
    for (i = 0; i < X.n; i++) {
        tr = complex_add(tr, X.matrix[i][i]);
    }
    return tr;
}

Complex norm(Matrix X)
{
    int i,j;
    Complex sum = (Complex){0, 0};
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            sum = complex_add(sum, complex_times(complex_conjugate(X.matrix[i][j]), X.matrix[i][j]));
        }
    }
    return (Complex){sqrt(sum.x), 0};
}

Complex inner(Matrix X, Matrix Y)
{
    Complex sum = (Complex){0, 0};
    int i;
    for (i = 0; i < X.m; i++) {
        sum = complex_add(sum, complex_times(complex_conjugate(X.matrix[i][0]), Y.matrix[i][0]));
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

Matrix dagger(Matrix X)
{
    Matrix Z = transe(X);
    int i,j;
    for (i = 0; i < Z.m; i++) {
        for (j = 0; j < Z.n; j++) {
            Z.matrix[i][j] = complex_conjugate(Z.matrix[i][j]);
        }
    }
    return Z;
}

Matrix House(Matrix X)
{
    Matrix H = {X.m, X.m};
    H.matrix = initialize_matrix(H.m, H.n);
    Matrix E = unit(H.m);

    H = minus(E, scalar(complex_scalar(2, complex_reciprocal(inner(X, X))), times(X, dagger(X))));

    return H;
}

Matrix QR(Matrix X)
{
    Matrix R = {X.m, X.n};
    Matrix H = unit(X.m);
    Matrix Temp = {X.m, X.n};
    Temp.matrix = initialize_matrix(Temp.m, Temp.n);
    Matrix E;
    
    int i,j;

    R.matrix = initialize_matrix(R.m, R.n);
    for (i = 0; i < R.m; i++) {
        for (j = 0; j < R.n; j++) {
            R.matrix[i][j] = X.matrix[i][j];
        }
    }

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
                temp1.matrix[j - i][0] = (Complex){0, 0};
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
    Matrix Y = {X.m, X.n};
    Y.matrix = initialize_matrix(Y.m, Y.n);
    Matrix Temp_QR;
    int i, j, k;
    for (i = 0; i < Y.m; i++) {
        for (j = 0; j < Y.n; j++) {
            Y.matrix[i][j] = X.matrix[i][j];
        }
    }
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
int range(Matrix X)
{
    int r = 0;
    if (X.m <= X.n) {
        r = X.m;
    } else {
        r = X.n;
    }
    return r;
}

Matrix echelon_form(Matrix X)
{
    Matrix Z = {X.m, X.n};
    Z.matrix = initialize_matrix(Z.m, Z.n);

    int row = 0; 
    bool flag = true;

    int i,j,k;
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            Z.matrix[i][j] = X.matrix[i][j];
        }
    }

    for (i = 0; i < Z.n; i++) {
        if (Z.matrix[row][i].x == 0 && Z.matrix[row][i].y == 0) {
            for (j = row; j < Z.m; j++) {
                if (Z.matrix[j][i].x != 0 || Z.matrix[j][i].y != 0) {
                    Complex *temp = malloc(sizeof(Complex) * Z.n);
                    for (k = 0; k < Z.n; k++) {
                        temp[k] = Z.matrix[row][k];
                    }
                    for (k = 0; k < Z.n; k++) {
                        Z.matrix[row][k] = Z.matrix[j][k];
                        Z.matrix[j][k] = temp[k];
                    }
                    break;
                } else if (j == Z.m - 1){
                    flag = false;
                }
            }
        }
        if (flag) {
            Complex temp = Z.matrix[row][i];
            if (fabsf(temp.x) < THRESHOLD && fabsf(temp.y) < THRESHOLD) {
                break;
            } else {
                for (k = 0; k < Z.n; k++) {
                    Z.matrix[row][k] = complex_div(Z.matrix[row][k], temp);
                    
                }
                for (j = 0; j < Z.m; j++) {
                    temp = Z.matrix[j][i];
                    if (j != row) {
                        for (k = 0; k < Z.n; k++) {
                            Z.matrix[j][k] = complex_minus(Z.matrix[j][k], complex_times(temp, Z.matrix[row][k]));
                        }
                    }
                }
            }
            row += 1;
        } else {
            flag = true;
        }
    }
    return Z;
}

Matrix Ker(Matrix X)
{
    Matrix b, B, Y;
    Y = echelon_form(X);
    B = (Matrix){0, 0};
    b = (Matrix){Y.n, 1};
    b.matrix = initialize_matrix(b.m, b.n);
    int temp[range(X)];
    int i, j, k, delta;

    delta = 0;

    for (i = 0; i < range(X); i++) {
        temp[i] = -1;
    }

    for (j = 0; j < Y.n; j++) {    
        for (i = j - delta; i < Y.m; i++) {
            if (Y.matrix[i][j].x != 0 || Y.matrix[i][j].y != 0) {
                temp[j] = i;
                break;
            } else if (i == Y.m -1) {
                delta += 1;
            }
        }
    }

    for (j = 0; j < Y.n; j++) {
        if (temp[j] == -1) {
            for (i = 0; i < Y.n; i++) {
                if (j == i) {
                    b.matrix[i][0] = (Complex){1,0};
                } else if (temp[i] != -1 && i <= j) {
                    b.matrix[i][0] = complex_scalar(-1, complex_div(Y.matrix[i][j], Y.matrix[i][temp[i]]));
                } else {
                    b.matrix[i][0] = (Complex){0, 0};
                }
            }
            B = joint(B, b);
        }
    }
    return B;
}

Matrix eigenspace(Matrix X, Complex lambda)
{
    Matrix B = Ker(minus(X, scalar(lambda ,unit(X.m))));
    return B;
}

Spaces general_eigenspace(Matrix X, Complex lambda)
{
    int N = 0;
    bool flag = false;
    Matrix Y = minus(X, scalar(lambda, unit(X.m)));
    int i, j, k;
    for (i = 0; i < Y.m; i++) {
        for (j = 0; j < Y.n; j++) {
            if (Y.matrix[i][j].x != 0 || Y.matrix[i][j].y != 0) {
                flag = true;
                break;
            }
        }
    }
    while(flag && N < X.m) {
        flag = false;
        Y = times(Y, Y);
        N += 1;
        for (i = 0; i < Y.m; i++) {
            for (j = 0; j < Y.n; j++) {
                if (Y.matrix[i][j].x != 0 || Y.matrix[i][j].y != 0) {
                    flag = true;
                    break;
                }
            }
        }
    }
    Spaces S = {N};
    S.spaces = malloc(sizeof(Matrix) * N);

    Y = minus(X, scalar(lambda ,unit(X.m)));
    for (i = 0; i < N; i++) {
        S.spaces[i] = (Matrix){Ker(Y).m, Ker(Y).n};
        S.spaces[i].matrix = initialize_matrix(Ker(Y).m, Ker(Y).n);
        for(j = 0; j < Ker(Y).m; j++) {
            for (k = 0; k < Ker(Y).n; k++) {
                S.spaces[i].matrix[j][k] = Ker(Y).matrix[j][k];
            }
        }
        Y = times(Y, Y);
    }
    return S;
}

Matrix projection(Matrix B)
{
    Matrix E, Z;
    E = unit(B.m);
    Z =minus(E, times(B, times(gauss_jordan(times(dagger(B), B)), dagger(B))));
    return Z;
}

Matrix Im(Matrix X)
{
    Matrix b, B, Y;
    Y = echelon_form(X);
    B = (Matrix){0, 0};
    b = (Matrix){Y.m, 1};
    b.matrix = initialize_matrix(b.m, b.n);
    int temp[range(X)];
    int i, j, k, row;

    row = 0;

    for (i = 0; i < range(X); i++) {
        temp[i] = -1;
    }

    for (j = 0; j < Y.n; j++) {    
        for (i = row; i < Y.m; i++) {
            if (Y.matrix[i][j].x != 0 || Y.matrix[i][j].y != 0) {
                temp[j] = i;
                row += 1;
                break;
            }
        }
    }

    for (j = 0; j < Y.n; j++) {
        if (temp[j] != -1) {
            for (i = 0; i < Y.m; i++) {
                b.matrix[i][0] = Y.matrix[i][j];
            }
            B = joint(B, b);
        }
    }
    return B;
}

Spaces complement(Spaces S)
{
    int i, j, k;
    Matrix P, W;
    Spaces T = {S.n};
    T.spaces = malloc(sizeof(Matrix) * S.n);
    for (i = 0; i < S.n; i++) {
        P = projection(S.spaces[i]);
        W = Im(P);
        T.spaces[i] = (Matrix){W.m, W.n};
        T.spaces[i].matrix = initialize_matrix(W.m, W.n);
        for (j = 0; j < W.m; j++) {
            for (k = 0; k < W.n; k++) {
                T.spaces[i].matrix[j][k] = W.matrix[j][k];
            }
        }
    }
    return T;

}

void show_matrix(Matrix X)
{
    int i, j;
    for (i = 0; i < X.m; i++) {
        for (j = 0; j < X.n; j++) {
            show_complex(X.matrix[i][j]);
            printf(" ");
            if (j == X.n - 1) {
                printf("\n");
            }
        }
    }
}

void show_spaces(Spaces S)
{
    int i, j, k;
    for (i = 0; i < S.n; i++) {
        printf("space number: %d--------------------------------------------------\n", i + 1);
        show_matrix(S.spaces[i]);
        printf("--------------------------------------------------\n");
    }
}