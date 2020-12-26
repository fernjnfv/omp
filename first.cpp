#include "header.h"

const int N = 1000;
const int M = 1000;

void first()
{
    int i, j, k, l, timed;
    float sum;
    //float a[N][M];
    random_device rd;
    mt19937 mersenne(rd());

    int** a = new int* [N];

    for (i = 0; i < N; i++)
    {
        a[i] = new int[M];
        for (j = 0; j < M; j++)
            a[i][j] = mersenne() % 10;
    }

    double start = omp_get_wtime();
#pragma omp parallel num_threads (1)   shared(a) private(i)
    {
#pragma omp for private(j,sum,k,l,timed) schedule(guided)
        for (i = 0; i < N; i++)
        {
            sum = 0;
            for (j = 0; j < M; j++)
                for (k = 0; k < M; k++)
                {
                    if (k != j)
                    {
                        timed = a[i][j] + a[i][k];
                        if (timed % 10 == 7)
                            sum++;
                        while (timed /= 10)
                            if (timed % 10 == 7)
                                sum++;
                    }
                }
            //printf("number 7 in %d strok is %f\n", i, sum);
        }
    }
    double end = omp_get_wtime();

    double first = end - start;

    start = omp_get_wtime();
#pragma omp parallel num_threads (6) shared(a) private(i)
    {
#pragma omp for private(j,sum,k,l,timed) schedule(guided)
        for (i = 0; i < N; i++)
        {
            sum = 0;
            for (j = 0; j < M; j++)
                for (k = 0; k < M; k++)
                {
                    if (k != j)
                    {
                        timed = a[i][j] + a[i][k];
                        if (timed % 10 == 7)
                            sum++;
                        while (timed /= 10)
                            if (timed % 10 == 7)
                                sum++;
                    }
                }
            //printf("number 7 in %d strok is %f\n", i, sum);
        }
    }
    end = omp_get_wtime();
    double second = end - start;

    cout << "With paralell  " << second << endl;
    cout << "Without paralell   " << first << endl;
}
