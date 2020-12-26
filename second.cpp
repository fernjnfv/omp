#include "header.h"

const int NMAX = 300;
const int LIMIT = 299;

const int NMAX2 = 300;
const int LIMIT2 = 300;

void second()
{
    int i, j;
    float sum;
    float a[NMAX][NMAX];
    float b[NMAX2][NMAX2];

    for (i = 0; i < NMAX; i++)
        for (j = 0; j < NMAX; j++)
            a[i][j] = i + j;
    double start = omp_get_wtime();
#pragma omp parallel shared(a) if (NMAX>LIMIT)
    {
        cout << omp_get_num_threads() << endl;
#pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
            //printf("Сумма элементов строки %d равна %f\n", i, sum);
        }
    } /* Завершение параллельного фрагмента */
    double end = omp_get_wtime();
    double first = end - start;
    cout << first << endl;

    for (i = 0; i < NMAX2; i++)
        for (j = 0; j < NMAX2; j++)
            a[i][j] = i + j;
    double start2 = omp_get_wtime();
#pragma omp parallel shared(a) if (NMAX2>LIMIT2)
    {
        cout << endl << omp_get_num_threads() << endl;
#pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX2; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX2; j++)
                sum += a[i][j];
            //printf("Сумма элементов строки %d равна %f\n", i, sum);
        }

    } /* Завершение параллельного фрагмента */
    double end2 = omp_get_wtime();
    double first2 = end2 - start2;
    cout << first2 << endl;
}