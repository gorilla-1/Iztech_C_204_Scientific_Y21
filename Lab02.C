// Mert Korkmaz

#include <stdio.h>
#define N 3
#define Dxyz(i, j) *(Dxyz + N * i + j)
#define I(i, invA_colNum) *(I + N * i + invA_colNum)
#define A(i, j) *(A + N * i + j)

void det3x3(double *Dxyz, double *det);
void CreateIdentityMat(double *I);
void CreateDxyz_mat(double *A, double *I, int A_colNum, double *Dxyz, int invA_colNum);

void CramersRuleForInverse(double *A);

void CreateIdentityMat(double *I)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == j)      //    1   0   0
                I(i, j) = 1; //    0   1   0
            else             //    0   0   1
                I(i, j) = 0;
        }
    }
}
void CreateDxyz_mat(double *A, double *I, int invA_colNum, double *Dxyz, int A_colNum)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == invA_colNum)
                Dxyz(i, j) = I(i, A_colNum);
            else
                Dxyz(i, j) = A(i, j);
        }
    }
}

void CramersRuleForInverse(double *A)
{

    int i, j, k, l;
    double I[N * N], Dxyz[N * N], inversA[N * N], detA;

    CreateIdentityMat(I);
    det3x3(A, &detA);
    double main_det = detA;
    printf("Determinant of A matrix: %.2f\n ", detA);
    for (l = 0; l < N; l++)
    {

        printf("-------------------------------------------------\n Calculation of the Col #%d of inverse A\n", l + 1);
        for (k = 0; k < N; k++)
        {
            CreateDxyz_mat(A, I, k, Dxyz, l);
            det3x3(Dxyz, &detA);
            double trans_mat = detA;

            inversA[N * k + l] = trans_mat / main_det;
            printf("Det: %f\n", detA);

            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {

                    printf("%lf ", Dxyz(i, j));
                }
                printf("\n");
            }

            printf("\n");
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%lf\t", inversA[i * N + j]);
        }
        printf("\n");
    }
}

void det3x3(double *Dxyz, double *det)
{
    *det = 0;
    for (int i = 0; i < 3; i++)
    {
        int temp = (Dxyz(0, i)) * (Dxyz(1, (i + 1) % 3) * Dxyz(2, (i + 2) % 3) - Dxyz(1, (i + 2) % 3) * Dxyz(2, (i + 1) % 3));
        *det += temp;
    }
}

int main()
{

    double A[N * N]; // 3x3 A matrix , N=3,determinant value
    printf("Write the elements of the A matrix :");
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            scanf("%lf", &A[i * N + j]);
        }
    }
    CramersRuleForInverse(A); // Call function
}
