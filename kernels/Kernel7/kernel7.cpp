#include "../lib/utils.cpp"

void kernel7()
{
	/*
	 *******************************************************************
	 *   Kernel 7 -- equation of state fragment
	 *******************************************************************
	 *    DO 7 L= 1,Loop
	 *    DO 7 k= 1,n
	 *      X(k)=     U(k  ) + R*( Z(k  ) + R*Y(k  )) +
	 *   .        T*( U(k+3) + R*( U(k+2) + R*U(k+1)) +
	 *   .        T*( U(k+6) + R*( U(k+5) + R*U(k+4))))
	 *  7 CONTINUE
	 */

	for (l = 1; l <= loop; l++)
	{
#pragma nohazard
		for (k = 0; k < n; k++)
		{
			x[k] = u[k] + r * (z[k] + r * y[k]) +
						 t * (u[k + 3] + r * (u[k + 2] + r * u[k + 1]) +
									t * (u[k + 6] + r * (u[k + 5] + r * u[k + 4])));
		}
	}
	argument = 7;
}

void kernel7_omp()
{
	omp_set_num_threads(4);

#pragma omp parallel shared(x, u, r, z, y, t) private(k)
	for (l = 1; l <= loop; l++)
	{
#pragma omp for
		for (k = 0; k < n; k++)
		{
			x[k] = u[k] + r * (z[k] + r * y[k]) +
						 t * (u[k + 3] + r * (u[k + 2] + r * u[k + 1]) +
									t * (u[k + 6] + r * (u[k + 5] + r * u[k + 4])));
		}
	}
	argument = 7;
}

int main()
{
	// fill arrays
	std::fill_n(x, len, 1);
	std::fill_n(u, len, 2);
	std::fill_n(z, len, 3);
	std::fill_n(y, len, 1);

	exeTime(kernel7, (char *)"kernel7");
	exeTime(kernel7_omp, (char *)"kernel7_omp");
	return 0;
}
