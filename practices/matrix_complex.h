#ifndef MATRIX_COMPLEX_H_
#define MATRIX__COMPLEX_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <stdbool.h>
#include "complex.h"

/**
 * @brief structure for representing a Matrtix
 *
 */
typedef struct Matrix {
    int m;      ///< row count
    int n;      ///< column count
    Complex **matrix;       ///< a complex matrix with two dimensions
} Matrix;

/**
 * @brief structure for representing subspaces of given vector space. 
 *
 */
typedef struct Spaces {
    int n;      ///< number of space
    Matrix *spaces;     ///< subspaces of given vector space 
} Spaces;

/**
 * @brief structure for representing eigenvalues of a given matrix of representing a linear map
 * 
 */
typedef struct Eigenvalues {
    int n;      ///< number of eigenvalue
    Complex *eigenvalues;       ///< eigenvalues of a given matrix
} Eigenvalues;

/**
 * @brief initialization for a Matrix
 *
 * @param m row number of a matrix
 * @param n column number of a matrix
 * @return A pointer to the matrix data(Complex**) of resulting Matrix object.
 */
Complex** initialize_matrix(int m, int n);
/**
 * @brief sum for tow matrices
 * @param X is a Matrix
 * @param Y is a Matrix
 * @return sum of X and Y
 */
Matrix add(Matrix X, Matrix Y);
Matrix minus(Matrix X, Matrix Y);
Matrix times(Matrix X, Matrix Y);
Matrix scalar(Complex a, Matrix X);
Matrix direct_sum(Matrix X, Matrix Y);
Matrix unit(int n);
Matrix joint(Matrix X, Matrix Y);
Matrix gauss_jordan(Matrix X);
Matrix LU(Matrix X);
Matrix transe(Matrix X);
Matrix House(Matrix X);
Matrix QR(Matrix X);
Matrix dissenbly(Matrix X);
Matrix QR_repeat(Matrix X, int n);
Matrix dagger(Matrix X);
Matrix echelon_form(Matrix X);
Matrix Ker(Matrix X);
Matrix eigenspace(Matrix X, Complex lambda);
Matrix projection(Matrix B);
Matrix Im(Matrix X);
Matrix common_space(Matrix B1, Matrix B2);
Spaces complement(Spaces S);
Spaces general_eigenspace(Matrix X, Complex lambda);
Complex inner(Matrix X, Matrix Y);
Complex det(Matrix X);
Complex tr(Matrix X);
Complex norm(Matrix X);
Eigenvalues eigenvalues(Matrix X);
int range(Matrix X);
int rank(Matrix X);
void show_matrix(Matrix X);
void show_spaces(Spaces S);
void show_eigenvalues(Eigenvalues lambda);

#endif