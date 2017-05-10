/**<
    Author: Zino Holwerda
    Date: 11/5/2017
*/

#include <stdio.h>

int** scanMatrix(int** current, int a, int b) {
    /**> Actual scanning*/
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++)
            scanf("%d", &current[i][j]);
    }
    return current;
}

int main() {
    /**> Introduction*/
    printf("This program will calculate the product of two matrices with dimensions provided to it.\n");
    printf("Stick to the rows and column as given and space the individual numbers with a space.\n\n");
    int m, n, p, q, sum = 0;
    printf("A's: row column (give the row and column of matrix A)\n");
    scanf("%d %d", &m, &n);
    printf("Elements of A\n");

    /**> Scans and makes the matrix A*/
    int a[m][n];
    scanMatrix(a, m, n);

    printf("B's: row column (give the row and column of matrix B)\n");
    scanf("%d %d", &p, &q);
    if (n != p) {
        printf("Don't match, try again!\n");
        main();
    }
    /**> Scans and makes the matrix B*/
    int b[p][q],ab[m][q];
    printf("Elements of B\n");
    scanMatrix(a, m, n);

    /**> Calculates AxB through matrix multiplication*/
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < q; j++) {
            for (int k = 0; k < p; k++)
                sum += a[i][k]*b[k][j];
            ab[i][j] = sum;
            sum = 0;
        }
    }

    /**> Prints the matrix AB*/
    printf("AxB:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < q; j++)
            printf("%d\t", ab[i][j]);
        printf("\n");
    }

    /**> Keeps the program from ending through bad practice*/
    while(1) {
        getchar();
    }
  return 0;
}
