#include "../lib/utils.cpp"

void kernel22()
{

	/*
	 *******************************************************************
	 *   Kernel 22 -- Planckian distribution
	 *******************************************************************
	 *     EXPMAX= 20.0
	 *       U(n)= 0.99*EXPMAX*V(n)
	 *    DO 22 L= 1,Loop
	 *    DO 22 k= 1,n
	 *                                          Y(k)= U(k)/V(k)
	 *       W(k)= X(k)/( EXP( Y(k)) -1.0)
	 * 22 CONTINUE
	 */

#pragma intrinsic exp
	expmax = 20.0;
	u[n - 1] = 0.99 * expmax * v[n - 1];
	for (l = 1; l <= loop; l++)
	{
		for (k = 0; k < n; k++)
		{
			y[k] = u[k] / v[k];
			w[k] = x[k] / (exp(y[k]) - 1.0);
		}
	}
	argument = 22;
}

void kernel22_omp()
{
	omp_set_num_threads(4);

#pragma intrinsic exp
	expmax = 20.0;
	u[n - 1] = 0.99 * expmax * v[n - 1];
#pragma omp parallel
	for (l = 1; l <= loop; l++)
	{
#pragma omp for
		for (k = 0; k < n; k++)
		{
			y[k] = u[k] / v[k];
			w[k] = x[k] / (exp(y[k]) - 1.0);
		}
	}
	argument = 22;
}

int main()
{
	std::fill_n(vx, len, 1);
	std::fill_n(xx, len, 1);
	std::fill_n(ir, len, 1);
	std::fill_n(rx, len, 1);
	std::fill_n(rh, len, 1);
	std::fill_n(grd, len, 1);
	std::fill_n(ex1, n, 2);
	std::fill_n(xi, n, 3);
	std::fill_n(dex1, n, 4);
	std::fill_n(ix, n, 5);

	exeTime(kernel22, (char *)"kernel22");
	exeTime(kernel22_omp, (char *)"kernel22_omp");
	return 0;
}
