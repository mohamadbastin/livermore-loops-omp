#include "../lib/utils.cpp"

void kernel5()
{

	/*
	 *******************************************************************
	 *   Kernel 5 -- tri-diagonal elimination, below diagonal
	 *******************************************************************
	 *    DO 5 L = 1,Loop
	 *    DO 5 i = 2,n
	 *  5    X(i)= Z(i)*(Y(i) - X(i-1))
	 */

	for (l = 1; l <= loop; l++)
	{
		for (i = 1; i < n; i++)
		{
			x[i] = z[i] * (y[i] - x[i - 1]);
		}
	}
	argument = 5;
}

void kernel5_omp()
{

	omp_set_num_threads(8);
#pragma omp parallel shared(x, z, y) private(i)
	for (l = 1; l <= loop; l++)
	{
#pragma omp for
		for (i = 1; i < n; i++)
		{
			x[i] = z[i] * (y[i] - x[i - 1]);
		}
	}
	argument = 5;
}

int main()
{
	std::fill_n(x, len, 1);
	std::fill_n(y, len, 2);
	std::fill_n(z, len, 3);

	exeTime(kernel5, (char *)"kernel5");
	exeTime(kernel5_omp, (char *)"kernel5_omp");
	return 0;
}
