
#include <stdio.h>
#include <math.h>

int main()
{
    int n, i, j, iter, max_iter;
    float a[10][10], b[10], x[10], x_new[10];
    float sum, error, tolerance;

    printf("Enter the number of variables: ");
    scanf("%d", &n);

    printf("Enter the coefficients of the matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%f", &a[i][j]);
        }
    }

    printf("Enter the constants:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%f", &b[i]);
    }

    printf("Enter initial guesses:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%f", &x[i]);
    }

    printf("Enter tolerance: ");
    scanf("%f", &tolerance);

    printf("Enter maximum iterations: ");
    scanf("%d", &max_iter);

    for(iter = 1; iter <= max_iter; iter++)
    {
        error = 0;

        for(i = 0; i < n; i++)
        {
            sum = b[i];

            for(j = 0; j < n; j++)
            {
                if(i != j)
                    sum -= a[i][j] * x[j];
            }

            x_new[i] = sum / a[i][i];
        }

        for(i = 0; i < n; i++)
        {
            if(fabs(x_new[i] - x[i]) > error)
                error = fabs(x_new[i] - x[i]);

            x[i] = x_new[i];
        }

        if(error < tolerance)
            break;
    }

    printf("\nSolution:\n");

    for(i = 0; i < n; i++)
    {
        printf("x%d = %.4f\n", i + 1, x[i]);
    }

    printf("\nNumber of iterations = %d\n", iter);

    return 0;
}
