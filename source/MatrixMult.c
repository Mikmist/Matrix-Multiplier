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
Prints a matrix.
*/
void printMatrix(Matrix m){
    printf("Matrix: %d x %d\n", m.rows, m.columns);
    for (int row = 0; row < m.rows; row++){
        for (int col = 0; col < m.columns; col++){
            if (col == 0)
				printf("|");
			printf("\t%f", m.data[row][col]);
			if (col == m.columns - 1)
				printf("|");
        }
        printf("\n");
    }
	printf("\n");
}

/*
Determines if a matrix is just one number.
*/
int isScalar(Matrix m){
	return (m.rows == 1 && m.columns == 1);
}

/*
Multiplies the matrix by a scalar.
*/
void scaleMatrix(Matrix m, float scalar){
	for (int row = 0; row < m.rows; row++){
		for (int col = 0; col < m.columns; col++){
			m.data[row][col] *= scalar;
		}
	}
}

/*
Determines if two matrices are compatible for multiplication.
Returns 1 if the matrices are compatible, and returns 2 if the matrices need to swap placed to be compatible.
*/
int matricesCompatible(Matrix a, Matrix b){
    if (a.columns == b.rows || isScalar(a) || isScalar(b)){
        return 1;
    } else if (b.columns = a.rows){
		return 2;
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
	return result;
}

/*
Frees a matrix.
*/
void freeMatrix(Matrix m){
	if (m.data == NULL)
		return;
    for (int row = 0; row < m.rows; row++){
        free(m.data[row]);
    }
    free(m.data);
}

/*
Swaps two matrices.
*/
void swapMatrices(Matrix *a, Matrix *b){
	Matrix temp = *a;
	*a = *b;
	*b = temp;
}

/*
Multiplies two matricies. It will swap them if that is needed.
The matrices must be freed outside of this function.
*/
Matrix matrixMultiply(Matrix a, Matrix b){
	//First test if the matrices can be multiplied.
    if (matricesCompatible(a, b) > 0){
		//If either matrix is a scalar, then multiplication is ez.
		if (isScalar(a)){
			scaleMatrix(b, a.data[0][0]);
			return b;
		} else if (isScalar(b)){
			scaleMatrix(a, b.data[0][0]);
			return a;
		}
		//Test if a and b need to be swapped to allow multiplication.
		if (matricesCompatible(a, b) == 2){
			swapMatrices(&a, &b);
		}
        Matrix result = newMatrix(a.rows, b.columns);
        for (int i = 0; i < a.rows; i++){
			for (int j = 0; j < b.columns; j++){
				float sum = 0;
				for (int k = 0; k < a.columns; k++){
					sum += a.data[i][k]*b.data[k][j];
				}
				result.data[i][j] = sum;
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
	printf("<Matrix Entry:>\n");
    printf("\tEnter the dimensions of the matrix:\n");
    scanf("%d %d", &(m.rows), &(m.columns));
    getchar();//Absorb newline.
    printf("\tEnter the elements of the matrix, row by row, separated by spaces.\n");
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
	printf("<Matrix recorded>\n");
    return m;
}

/*
Independent function to interact with the user for matrix multiplication.
*/
void userMultiply(){
	printf("Matrix Multiplication Assistant:\n");
	printf("\nEnter matrix A:\n\n");
    Matrix A = scanMatrix();
	printf("\nEnter matrix B:\n\n");
    Matrix B = scanMatrix();

	printf("\nResult of A x B:\n");
    Matrix result = matrixMultiply(A, B);

    printMatrix(result);
	freeMatrix(A);
	freeMatrix(B);
	freeMatrix(result);
}

int main(int argc, char* argv[]) {
    
    userMultiply();
    
	return 0;
}
