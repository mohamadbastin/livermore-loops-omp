#include "../lib/utils.cpp"

void kernel14()
{

	/*
	 *******************************************************************
	 *   Kernel 14 -- 1-D PIC (Particle In Cell)
	 *******************************************************************
	 *    DO   14   L= 1,Loop
	 *    DO   141  k= 1,n
	 *          VX(k)= 0.0
	 *          XX(k)= 0.0
	 *          IX(k)= INT(  GRD(k))
	 *          XI(k)= REAL( IX(k))
	 *         EX1(k)= EX   ( IX(k))
	 *        DEX1(k)= DEX  ( IX(k))
	 *41  CONTINUE
	 *    DO   142  k= 1,n
	 *          VX(k)= VX(k) + EX1(k) + (XX(k) - XI(k))*DEX1(k)
	 *          XX(k)= XX(k) + VX(k)  + FLX
	 *          IR(k)= XX(k)
	 *          RX(k)= XX(k) - IR(k)
	 *          IR(k)= MOD2N(  IR(k),2048) + 1
	 *          XX(k)= RX(k) + IR(k)
	 *42  CONTINUE
	 *    DO  14    k= 1,n
	 *    RH(IR(k)  )= RH(IR(k)  ) + 1.0 - RX(k)
	 *    RH(IR(k)+1)= RH(IR(k)+1) + RX(k)
	 *14  CONTINUE
	 */

	for (l = 1; l <= loop; l++)
	{
		for (k = 0; k < n; k++)
		{
			vx[k] = 0.0;
			xx[k] = 0.0;
			ix[k] = (long)grd[k];
			xi[k] = (double)ix[k];
			ex1[k] = ex[ix[k] - 1];
			dex1[k] = dex[ix[k] - 1];
		}
		for (k = 0; k < n; k++)
		{
			vx[k] = vx[k] + ex1[k] + (xx[k] - xi[k]) * dex1[k];
			xx[k] = xx[k] + vx[k] + flx;
			ir[k] = xx[k];
			rx[k] = xx[k] - ir[k];
			ir[k] = (ir[k] & 2048 - 1) + 1;
			xx[k] = rx[k] + ir[k];
		}
		for (k = 0; k < n; k++)
		{
			rh[ir[k] - 1] += 1.0 - rx[k];
			rh[ir[k]] += rx[k];
		}
	}
	argument = 14;
}

void kernel14_omp()
{
	omp_set_num_threads(4);

#pragma omp parallel
	for (l = 1; l <= loop; l++)
	{
#pragma omp for
		for (k = 0; k < n; k++)
		{
			vx[k] = 0.0;
			xx[k] = 0.0;
			ix[k] = (long)grd[k];
			xi[k] = (double)ix[k];
			ex1[k] = ex[ix[k] - 1];
			dex1[k] = dex[ix[k] - 1];
		}
#pragma omp for
		for (k = 0; k < n; k++)
		{
			vx[k] = vx[k] + ex1[k] + (xx[k] - xi[k]) * dex1[k];
			xx[k] = xx[k] + vx[k] + flx;
			ir[k] = xx[k];
			rx[k] = xx[k] - ir[k];
			ir[k] = (ir[k] & 2048 - 1) + 1;
			xx[k] = rx[k] + ir[k];
		}
#pragma omp for
		for (k = 0; k < n; k++)
		{
			rh[ir[k] - 1] += 1.0 - rx[k];
			rh[ir[k]] += rx[k];
		}
	}
	argument = 14;
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

	exeTime(kernel14, (char *)"kernel14");
	exeTime(kernel14_omp, (char *)"kernel14_omp");
	return 0;
}
