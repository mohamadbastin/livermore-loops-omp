#include "../lib/utils.cpp"

void kernel18()
{

	/*
	 *******************************************************************
	 *   Kernel 18 - 2-D explicit hydrodynamics fragment
	 *******************************************************************
	 *       DO 75  L= 1,Loop
	 *              T= 0.0037
	 *              S= 0.0041
	 *             KN= 6
	 *             JN= n
	 *       DO 70  k= 2,KN
	 *       DO 70  j= 2,JN
	 *        ZA(j,k)= (ZP(j-1,k+1)+ZQ(j-1,k+1)-ZP(j-1,k)-ZQ(j-1,k))
	 *   .            *(ZR(j,k)+ZR(j-1,k))/(ZM(j-1,k)+ZM(j-1,k+1))
	 *        ZB(j,k)= (ZP(j-1,k)+ZQ(j-1,k)-ZP(j,k)-ZQ(j,k))
	 *   .            *(ZR(j,k)+ZR(j,k-1))/(ZM(j,k)+ZM(j-1,k))
	 * 70    CONTINUE
	 *       DO 72  k= 2,KN
	 *       DO 72  j= 2,JN
	 *        ZU(j,k)= ZU(j,k)+S*(ZA(j,k)*(ZZ(j,k)-ZZ(j+1,k))
	 *   .                    -ZA(j-1,k) *(ZZ(j,k)-ZZ(j-1,k))
	 *   .                    -ZB(j,k)   *(ZZ(j,k)-ZZ(j,k-1))
	 *   .                    +ZB(j,k+1) *(ZZ(j,k)-ZZ(j,k+1)))
	 *        ZV(j,k)= ZV(j,k)+S*(ZA(j,k)*(ZR(j,k)-ZR(j+1,k))
	 *   .                    -ZA(j-1,k) *(ZR(j,k)-ZR(j-1,k))
	 *   .                    -ZB(j,k)   *(ZR(j,k)-ZR(j,k-1))
	 *   .                    +ZB(j,k+1) *(ZR(j,k)-ZR(j,k+1)))
	 * 72    CONTINUE
	 *       DO 75  k= 2,KN
	 *       DO 75  j= 2,JN
	 *        ZR(j,k)= ZR(j,k)+T*ZU(j,k)
	 *        ZZ(j,k)= ZZ(j,k)+T*ZV(j,k)
	 * 75    CONTINUE
	 */

	for (l = 1; l <= loop; l++)
	{
		t = 0.0037;
		s = 0.0041;
		kn = 6;
		for (k = 1; k < kn; k++)
		{
#pragma nohazard
			for (j = 1; j < n; j++)
			{
				za[k][j] = (zp[k + 1][j - 1] + zq[k + 1][j - 1] - zp[k][j - 1] - zq[k][j - 1]) *
									 (zr[k][j] + zr[k][j - 1]) / (zm[k][j - 1] + zm[k + 1][j - 1]);
				zb[k][j] = (zp[k][j - 1] + zq[k][j - 1] - zp[k][j] - zq[k][j]) *
									 (zr[k][j] + zr[k - 1][j]) / (zm[k][j] + zm[k][j - 1]);
			}
		}
		for (k = 1; k < kn; k++)
		{
#pragma nohazard
			for (j = 1; j < n; j++)
			{
				zu[k][j] += s * (za[k][j] * (zz[k][j] - zz[k][j + 1]) -
												 za[k][j - 1] * (zz[k][j] - zz[k][j - 1]) -
												 zb[k][j] * (zz[k][j] - zz[k - 1][j]) +
												 zb[k + 1][j] * (zz[k][j] - zz[k + 1][j]));
				zv[k][j] += s * (za[k][j] * (zr[k][j] - zr[k][j + 1]) -
												 za[k][j - 1] * (zr[k][j] - zr[k][j - 1]) -
												 zb[k][j] * (zr[k][j] - zr[k - 1][j]) +
												 zb[k + 1][j] * (zr[k][j] - zr[k + 1][j]));
			}
		}

		for (k = 1; k < kn; k++)
		{
#pragma nohazard
			for (j = 1; j < n; j++)
			{
				zr[k][j] = zr[k][j] + t * zu[k][j];
				zz[k][j] = zz[k][j] + t * zv[k][j];
			}
		}
	}
	argument = 18;
}

void kernel18_omp()
{
	omp_set_num_threads(4);

#pragma omp parallel shared(t, s, kn)
	for (l = 1; l <= loop; l++)
	{
		t = 0.0037;
		s = 0.0041;
		kn = 6;

#pragma omp for
		for (k = 1; k < kn; k++)
		{
			for (j = 1; j < n; j++)
			{
				za[k][j] = (zp[k + 1][j - 1] + zq[k + 1][j - 1] - zp[k][j - 1] - zq[k][j - 1]) *
									 (zr[k][j] + zr[k][j - 1]) / (zm[k][j - 1] + zm[k + 1][j - 1]);
				zb[k][j] = (zp[k][j - 1] + zq[k][j - 1] - zp[k][j] - zq[k][j]) *
									 (zr[k][j] + zr[k - 1][j]) / (zm[k][j] + zm[k][j - 1]);
			}
		}

#pragma omp for
		for (k = 1; k < kn; k++)
		{
			for (j = 1; j < n; j++)
			{
				zu[k][j] += s * (za[k][j] * (zz[k][j] - zz[k][j + 1]) -
												 za[k][j - 1] * (zz[k][j] - zz[k][j - 1]) -
												 zb[k][j] * (zz[k][j] - zz[k - 1][j]) +
												 zb[k + 1][j] * (zz[k][j] - zz[k + 1][j]));
				zv[k][j] += s * (za[k][j] * (zr[k][j] - zr[k][j + 1]) -
												 za[k][j - 1] * (zr[k][j] - zr[k][j - 1]) -
												 zb[k][j] * (zr[k][j] - zr[k - 1][j]) +
												 zb[k + 1][j] * (zr[k][j] - zr[k + 1][j]));
			}
		}

#pragma omp for
		for (k = 1; k < kn; k++)
		{
			for (j = 1; j < n; j++)
			{
				zr[k][j] = zr[k][j] + t * zu[k][j];
				zz[k][j] = zz[k][j] + t * zv[k][j];
			}
		}
	}
	argument = 18;
}

int main()
{
	// fill arrays x y z v w b using fill_n
	std::fill_n(x, n, 1);
	std::fill_n(y, n, 2);
	std::fill_n(z, n, 3);
	std::fill_n(v, n, 4);
	std::fill_n(w, n, 5);
	// std::fill_n(b, n * n, 6);

	exeTime(kernel18, (char *)"kernel18");
	exeTime(kernel18_omp, (char *)"kernel18_omp");
	return 0;
}
