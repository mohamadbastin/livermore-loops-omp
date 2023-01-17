#include "../lib/utils.cpp"

void kernel4()
{

	/*
	 *******************************************************************
	 *   Kernel 4 -- banded linear equations
	 *******************************************************************
	 *            m= (1001-7)/2
	 *    DO 444  L= 1,Loop
	 *    DO 444  k= 7,1001,m
	 *           lw= k-6
	 *         temp= X(k-1)
	 CDIR$ IVDEP
	 *    DO   4  j= 5,n,5
	 *       temp  = temp   - XZ(lw)*Y(j)
	 *  4        lw= lw+1
	 *       X(k-1)= Y(5)*temp
	 *444 CONTINUE
	 */

	m = (1001 - 7) / 2;
	for (l = 1; l <= loop; l++)
	{
		for (k = 6; k < 1001; k = k + m)
		{
			lw = k - 6;
			temp = x[k - 1];
#pragma nohazard
			for (j = 4; j < n; j = j + 5)
			{
				temp -= x[lw] * y[j];
				lw++;
			}
			x[k - 1] = y[4] * temp;
		}
	}
	argument = 4;
}

void kernel4_omp()
{

	/*
 *******************************************************************
 *   Kernel 4 -- banded linear equations
 *******************************************************************
 *            m= (1001-7)/2
 *    DO 444  L= 1,Loop
 *    DO 444  k= 7,1001,m
 *           lw= k-6
 *         temp= X(k-1)
 CDIR$ IVDEP
 *    DO   4  j= 5,n,5
 *       temp  = temp   - XZ(lw)*Y(j)
 *  4        lw= lw+1
 *       X(k-1)= Y(5)*temp
 *444 CONTINUE
 */

	m = (1001 - 7) / 2;
	// Set the number of threads to use
	omp_set_num_threads(8);

	// Define the loop to parallelize
#pragma omp parallel shared(x, y, lw, k)
	for (l = 1; l <= loop; l++)
	{
		for (k = 6; k < 1001; k = k + m)
		{
			lw = k - 6;
			temp = x[k - 1];
#pragma omp for nowait
			for (j = 4; j < n; j = j + 5)
			{
				temp -= x[lw] * y[j];
#pragma omp critical
				lw++;
			}
#pragma omp atomic
			x[k - 1] = y[4] * temp;
		}
	}
	argument = 4;
}

int main()
{
	// fill arrays x y z v w b using fill_n
	std::fill_n(x, len, 1);
	std::fill_n(y, len, 2);
	std::fill_n(z, len, 3);
	std::fill_n(v, len, 4);
	std::fill_n(w, len, 5);
	// std::fill_n(b, n * n, 6);

	exeTime(kernel4, (char *)"kernel4");
	exeTime(kernel4_omp, (char *)"kernel4_omp");
	return 0;
}
