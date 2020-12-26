#include <iostream>
#include "header.h"
#include <math.h>
#include <time.h>

using namespace std;

const int N = 15000000;

void sixth (){
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
    #pragma omp parallel private(timed2) num_threads(3)
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

    composition2 = 0;

    start = omp_get_wtime();
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel private(timed2) num_threads(3)
    {
        #pragma omp for
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
            omp_set_lock (&lock);
            composition2 += timed2;
            omp_unset_lock (&lock);
        }
    }
    omp_destroy_lock (&lock);
    finish = omp_get_wtime();
    cout << finish - start << "s with lock ";
    cout << composition2 << endl;


    composition2 = 0;
    double sum[3] = {0,0,0};
    start = omp_get_wtime();
    #pragma omp parallel private(timed2) num_threads(3)
    {
        #pragma omp for nowait
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
            sum[omp_get_thread_num()]+=timed2;
        }
        #pragma omp barrier
        composition2 = sum[0] + sum[1] + sum[2];
    }
    finish = omp_get_wtime();
    cout << finish - start << "s with barrier ";
    cout << composition2 << endl;
}
