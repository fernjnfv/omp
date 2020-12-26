#include "header.h"
#include <algorithm>
#include <time.h>

using namespace std;

const int N = 150000000;

void five() {
    //srand(time(NULL));

    int i;
    double composition2 = 0;
    double timed2 = 0;
    double finish, start;
    int* A = new int[N];
    double* B = new double[N];
    double* C = new double[N];
    random_device rd;
    mt19937 mersenne(rd());
    for (i = 0; i < N; i++)
    {
        A[i] = (mersenne() % 100000)+1;
        B[i] = 1+(mersenne() % 100000);
        C[i] = 1+(mersenne() % 100000);
    }

    start = omp_get_wtime();
    #pragma omp parallel private(timed2) num_threads(1)
    {
        #pragma omp for reduction(+:composition2)
        for (int i = 0; i < N; i++)
        {
            if ((A[i] % 2) == 0)
            {
                timed2 = B[i] / C[i];
            }
            else
            {
                timed2 = B[i] + A[i];
            }
            composition2 += timed2;
        }
    }
    finish = omp_get_wtime();
    cout << finish - start << "s without paralel ";
    cout << composition2 << endl;

    composition2 = 0;
    start = omp_get_wtime();
    #pragma omp parallel private(timed2) num_threads(2)
    {
        #pragma omp for reduction(+:composition2)
        for (int i = 0; i < N; i++)
        {
            if ((A[i] % 2) == 0)
            {
                timed2 = B[i] / C[i];
            }
            else
            {
                timed2 = B[i] + A[i];
            }
            composition2 += timed2;
        }
    }
    finish = omp_get_wtime();
    cout << finish - start << "s with reduction ";
    cout << composition2 << endl;


    omp_set_num_threads(12);
    double* sum = new double[2];
    sum[0]=0;
    sum[1]=0;
    composition2 = 0;
    start = omp_get_wtime();
    #pragma omp  parallel sections private(timed2) num_threads(12)
    {
        #pragma omp section
        {
            for (int i = 0; i < N/2; i++)
            {
                if ((A[i] % 2) == 0)
                {
                    timed2 = B[i] / C[i];
                }
                else
                {
                    timed2 = B[i] + A[i];
                }
                sum[0] += timed2;
            }
        }
        #pragma omp section
        {
            for (int i = N/2; i < N; i++)
            {
                if ((A[i] % 2) == 0)
                {
                    timed2 = B[i] / C[i];
                }
                else
                {
                    timed2 = B[i] + A[i];
                }
                sum[1] += timed2;
            }
        }
    }
    composition2 = sum[0] + sum[1];
    finish = omp_get_wtime();
    cout << finish - start << "s with 2 section ";
    cout << composition2 << endl;


    sum = new double[4];
    composition2 = 0;
    sum[0]=0;
    sum[1]=0;
    sum[2]=0;
    sum[3]=0;
    start = omp_get_wtime();
    #pragma omp parallel sections private(timed2) num_threads(12)
    {
        #pragma omp section
        {
            for (int i = 0; i < N/4; i++)
            {
                if ((A[i] % 2) == 0)
                {
                    timed2 = B[i] / C[i];
                }
                else
                {
                    timed2 = B[i] + A[i];
                }
                sum[0] += timed2;
            }
        }
        #pragma omp section
        {
            for (int i = N/4; i < N/4*2; i++)
            {
                if ((A[i] % 2) == 0)
                {
                    timed2 = B[i] / C[i];
                }
                else
                {
                    timed2 = B[i] + A[i];
                }
                sum[1] += timed2;
            }
        }
        #pragma omp section
        {
            for (int i = N/4*2; i < N/4*3; i++)
            {
                if ((A[i] % 2) == 0)
                {
                    timed2 = B[i] / C[i];
                }
                else
                {
                    timed2 = B[i] + A[i];
                }
                    sum[2] += timed2;
            }
        }
        #pragma omp section
        {
            for (int i = N/4*3; i < N; i++)
            {
                if ((A[i] % 2) == 0)
                {
                    timed2 = B[i] / C[i];
                }
                else
                {
                    timed2 = B[i] + A[i];
                }
                    sum[3] += timed2;
            }
        }
    }
    composition2 = sum[0] + sum[1]+sum[2]+sum[3];
    finish = omp_get_wtime();
    cout << finish - start << "s with 4 section ";
    cout << composition2 << endl;

    system("pause");
}
