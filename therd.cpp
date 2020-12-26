#include "header.h"
using namespace std;

const int N = 150000000;

void therd()
{
	int i;
	double composition = 0;
	double composition2 = 0;
	double timed = 0;
	double timed2 = 0;
	double finish, finish2, start, start2;
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


#pragma omp parallel shared(A, B, C, composition)
	{
		start2 = omp_get_wtime();
		omp_set_num_threads(1);
#pragma omp for private(timed2,i) reduction(+: composition2)
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

		finish2 = omp_get_wtime();


		start = omp_get_wtime();
        omp_set_num_threads(8);
#pragma omp  for private(timed,i) reduction(+: composition)
		for (int i = 0; i < N; i++)
		{
			if ((A[i] % 2) == 0)
			{
				timed = B[i] / C[i];
			}
			else
			{
				timed = B[i] + A[i];
			}
			composition += timed;
		}

		finish = omp_get_wtime();

		
		

	}

	

	cout << composition << "   " << finish - start << endl;

	cout << composition2 << "    " << finish2 - start2 << endl;

	

}
