#include <stdio.h>
//Mert Korkmaz
void matTra(int nRow, int nCol)
{
    double A[nRow][nCol]; // the first operand matrix
    double T[nCol][nRow];
    for (int i = 0; i < nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            printf("Element A[%d][%d] :", i + 1, j + 1);
            scanf("%le", &A[i][j]);
            T[j][i] = A[i][j];
        }
    }
    for (int i = 0; i < nCol; i++)
    {
        for (int j = 0; j < nRow; j++)
        {
            printf("%.2f ", T[i][j]);
        }
        printf("\n");
    }
}
void matMul(int nRow1, int nCol1, int nRow2, int nCol2)
{

    double A[nRow1][nCol1]; // the first operand matrix
    if (nCol1 != nRow2)
        printf("The sizes doesn't match up");
    else
    {

        for (int i = 0; i < nRow1; i++)
        {
            for (int j = 0; j < nCol1; j++)
            {
                printf("Element A[%d][%d] :", i + 1, j + 1);
                scanf("%le", &A[i][j]);
            }
        }

        double B[nRow2][nCol2]; // the second operand matrix
        double C[nRow1][nCol2];
        for (int i = 0; i < nCol2; i++)
        {
            for (int j = 0; j < nRow2; j++)
            {
                printf("Element B[%d][%d] :", i + 1, j + 1);
                scanf("%le", &B[i][j]);
            }
        }

        for (int i = 0; i < nRow1; i++)
        {
            for (int j = 0; j < nCol2; j++)
            {
                for (int k = 0; k < nCol1; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        for (int i = 0; i < nRow1; i++)
        {
            for (int j = 0; j < nCol2; j++)
            {
                printf("%.2f ", C[i][j]);
            }
            printf("\n");
        }
    }
}
void matAdd(int n, int m)
{
    int a_size = n * m;
    int l = 0, j = 0;
    double A[a_size]; // the first operand matrix
    double B[a_size]; // the second operand matrix
    double C[a_size];
    printf("Content of the first operand matrix\n");

    for (int i = 0; i < a_size; i++)
    {

        printf("Element A[%d][%d] :", l + 1, j + 1);
        scanf("%le", &A[i]);
        j++;
        if (i % m == m - 1)
        {
            l++;
            j = 0;
        }
    }
    printf("Content of the second operand matrix\n");
    j = l = 0;
    for (int i = 0; i < a_size; i++)
    {
        printf("Element B[%d][%d] :", l + 1, j + 1);
        scanf("%le", &B[i]);
        j++;
        if (i % m == m - 1)
        {
            l++;
            j = 0;
        }
    }
    if (sizeof(A) != sizeof(B))
    {
        printf("Matrices don't match up!!!");
    }
    else
    {
        for (int i = 0; i < a_size; i++)
        {

            C[i] = A[i] + B[i];
        }
        for (int i = 0; i < a_size; i++)
        {
            if (i % m == 0)
                printf("\n");
            printf("%.2f ", C[i]);
        }
    }
}
int main()
{
    int n, m, choice, nRow2, nCol2;
    printf("1\t Matrices Addition\n2\t Matrices Multiplication\n3\tMatrices Trasnpose:\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

        printf("Enter the row (n) index value of the matrix :");
        scanf("%d", &n);
        printf("Enter the column (m) index value of the matrix :");
        scanf("%d", &m);
        matAdd(n, m);
        break;
    case 2:

        printf("Enter the row (n) index value of the matrix :");
        scanf("%d", &n);
        printf("Enter the column (m) index value of the matrix :");
        scanf("%d", &m);
        printf("Enter the row index (n) of second matrix :");
        scanf("%d", &nRow2);
        printf("Enter the index (m) of second matrix :");
        scanf("%d", &nCol2);
        matMul(n, m, nRow2, nCol2);
        break;
    case 3:
        printf("Enter the row (n) index value of the matrix :");
        scanf("%d", &n);
        printf("Enter the column (m) index value of the matrix :");
        scanf("%d", &m);
        matTra(n, m);
        break;
    default:
        printf("LOL No Way\n");
        break;
    }
}
