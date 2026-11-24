
#include <stdio.h>
#include <math.h>

int main()
{
    int n, i, j, iter, max_iter;
    float a[10][10], b[10], x[10], old[10];
    float sum, error, tolerance;

    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter coefficients of the matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%f", &a[i][j]);
        }
    }

    printf("Enter constants:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%f", &b[i]);
    }

    printf("Enter initial guesses:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%f", &x[i]);
    }

    printf("Enter maximum iterations: ");
    scanf("%d", &max_iter);

    printf("Enter tolerance: ");
    scanf("%f", &tolerance);

    for(iter = 1; iter <= max_iter; iter++)
    {
        error = 0;

        for(i = 0; i < n; i++)
        {
            old[i] = x[i];
        }

        for(i = 0; i < n; i++)
        {
            sum = b[i];

            for(j = 0; j < n; j++)
            {
                if(i != j)
                {
                    sum -= a[i][j] * x[j];
                }
            }

            x[i] = sum / a[i][i];
        }

        for(i = 0; i < n; i++)
        {
            if(fabs(x[i] - old[i]) > error)
            {
                error = fabs(x[i] - old[i]);
            }
        }

        if(error < tolerance)
        {
            break;
        }
    }

    printf("\nSolution:\n");
    for(i = 0; i < n; i++)
    {
        printf("x%d = %.4f\n", i + 1, x[i]);
    }

    printf("Iterations = %d\n", iter <= max_iter ? iter : max_iter);

    return 0;
}
