#include "../lib/utils.cpp"

void kernel6()
{ /*
	 *******************************************************************
	 *   Kernel 6 -- general linear recurrence equations
	 *******************************************************************
	 *    DO  6  L= 1,Loop
	 *    DO  6  i= 2,n
	 *    DO  6  k= 1,i-1
	 *        W(i)= W(i)  + B(i,k) * W(i-k)
	 *  6 CONTINUE
	 */

	// Define the loop to parallelize
	for (l = 1; l <= loop; l++)
	{
		for (i = 1; i < n; i++)
		{
			for (k = 0; k < i; k++)
			{
				w[i] += b[k][i] * w[(i - k) - 1];
			}
		}
	}
	argument = 6;
}

void kernel6_omp()
{
	omp_set_num_threads(4);

#pragma omp parallel shared(k, w, b) private(i)
	for (l = 1; l <= loop; l++)
	{
#pragma omp for
		for (i = 1; i < n; i++)
		{
			for (k = 0; k < i; k++)
			{
				w[i] += b[k][i] * w[(i - k) - 1];
			}
		}
	}
	argument = 6;
}

int main()
{
	// fill arrays
	std::fill_n(w, len, 5);
	std::fill_n(b, len * len, 6);

	exeTime(kernel6, (char *)"kernel6");
	exeTime(kernel6_omp, (char *)"kernel6_omp");
	return 0;
}
