
#include <stdio.h>
#include <math.h>

int main()
{
    int n, i, j, iter, max_iter;
    float a[10][10], x[10], y[10];
    float max, error, tolerance;

    printf("Enter order of matrix: ");
    scanf("%d", &n);

    printf("Enter matrix elements:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%f", &a[i][j]);
        }
    }

    printf("Enter initial eigenvector:\n");
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
        for(i = 0; i < n; i++)
        {
            y[i] = 0;

            for(j = 0; j < n; j++)
            {
                y[i] += a[i][j] * x[j];
            }
        }

        max = fabs(y[0]);

        for(i = 1; i < n; i++)
        {
            if(fabs(y[i]) > max)
            {
                max = fabs(y[i]);
            }
        }

        error = 0;

        for(i = 0; i < n; i++)
        {
            y[i] = y[i] / max;

            if(fabs(y[i] - x[i]) > error)
            {
                error = fabs(y[i] - x[i]);
            }

            x[i] = y[i];
        }

        if(error < tolerance)
        {
            break;
        }
    }

    printf("\nDominant Eigenvalue = %.4f\n", max);

    printf("Dominant Eigenvector:\n");
    for(i = 0; i < n; i++)
    {
        printf("%.4f\n", x[i]);
    }

    printf("Number of iterations = %d\n",
           iter <= max_iter ? iter : max_iter);

    return 0;
}
