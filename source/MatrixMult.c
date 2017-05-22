/**<
    Author: Zino Holwerda
    Date: 11/5/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
Struct that defines a matrix.
*/
typedef struct {
    int rows;
    int columns;
    float** data;
} Matrix;

/*
Determines if two matrices are compatible for multiplication.
*/
int matricesCompatible(Matrix a, Matrix b){
    if (a.columns == b.rows){
        return 1;
    }
    return 0;
}

/*
Creates a newly allocated matrix.
*/
Matrix newMatrix(int rows, int columns){
    Matrix result;
    result.rows = rows;
    result.columns = columns;
    result.data = malloc(rows*sizeof(float*));
    assert(result.data != NULL);
    for (int row = 0; row < rows; row++){
        result.data[row] = malloc(columns*sizeof(float));
        assert(result.data[row] != NULL);
    }
}

/*
Frees a matrix.
*/
void freeMatrix(Matrix m){
    for (int row = 0; row < m.rows; row++){
        free(m.data[row]);
    }
    free(m.data);
}

/*
Prints a matrix.
*/
void printMatrix(Matrix m){
    printf("Matrix: %d x %d\n", m.rows, m.columns);
    for (int col = 0; col < m.columns; col++){
        for (int row = 0; row < m.rows; row++){
            printf("\t%f", m.data[row][col]);
        }
        printf("\n");
    }
}

/*
Multiplies two matricies. SEGMENTATION FAULT!!! FIX THIS!!!
*/
Matrix matrixMultiply(Matrix a, Matrix b){
    if (matricesCompatible(a, b)){
        Matrix result = newMatrix(a.rows, b.columns);
        for (int row = 0; row < a.rows; row++){
            for (int col = 0; col < b.columns; col++){
                int sum = 0;
                for (int rowB = 0; rowB < b.rows; rowB++){
                    sum += a.data[row][rowB]*b.data[rowB][col];
                }
                result.data[row][col] = sum;
            }
        }
        return result;
    } else {
        printf("Matrices are not compatible for multiplication.\nA: %d x %d, B: %d x %d\n", a.rows, a.columns, b.rows, b.columns);
        exit(-1);
        Matrix m;
        return m;
    }
}

/*
Reads a matrix from input, where numbers are separated by spaces.
*/
Matrix scanMatrix() {
    Matrix m;
    printf("Enter the dimensions of the matrix:\n");
    scanf("%d %d", &(m.rows), &(m.columns));
    getchar();//Absorb newline.
    printf("Enter the elements of the matrix, row by row, separated by spaces.\n");
    m.data = malloc(m.rows*sizeof(float*));
    assert(m.data != NULL);
    for (int row = 0; row < m.rows; row++){
        m.data[row] = malloc(m.columns*sizeof(float));
        assert(m.data[row] != NULL);
        for (int col = 0; col < m.columns; col++){
            float input;
            scanf("%f", &input);
            m.data[row][col] = input;
            getchar();//Absorb space or newline after number.
        }
    }
    return m;
}

int main() {
    /**> Introduction*/
    printf("This program will calculate the product of two matrices with dimensions provided to it.\n");
    printf("When inputting multiple values, separate them by a space.\n\n");

    Matrix A = scanMatrix();
    Matrix B = scanMatrix();

    Matrix result = matrixMultiply(A, B);

    printMatrix(result);
    
    
  return 0;
}