#include <stdio.h>

#define N 3

void multiply(int A[][N], int B[][N], int C[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int A[N][N] = {{3,3,3}, {3,3,3},{3,3,3}}; 
    int B[N][N] = {{3,3,3}, {3,3,3},{3,3,3}}; 
    int C[N][N]; 

    multiply(A, B, C);

    printf("Resultant Matrix C:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}