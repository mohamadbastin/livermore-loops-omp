#include "../lib/utils.cpp"

void kernel9()
{
	/*
	 *******************************************************************
	 *   Kernel 9 -- integrate predictors
	 *******************************************************************
	 *    DO 9  L = 1,Loop
	 *    DO 9  i = 1,n
	 *    PX( 1,i)= DM28*PX(13,i) + DM27*PX(12,i) + DM26*PX(11,i) +
	 *   .          DM25*PX(10,i) + DM24*PX( 9,i) + DM23*PX( 8,i) +
	 *   .          DM22*PX( 7,i) +  C0*(PX( 5,i) +      PX( 6,i))+ PX( 3,i)
	 *  9 CONTINUE
	 */

	for (l = 1; l <= loop; l++)
	{
		for (i = 0; i < n; i++)
		{
			px[i][0] = dm28 * px[i][12] + dm27 * px[i][11] + dm26 * px[i][10] +
								 dm25 * px[i][9] + dm24 * px[i][8] + dm23 * px[i][7] +
								 dm22 * px[i][6] + c0 * (px[i][4] + px[i][5]) + px[i][2];
		}
	}
	argument = 9;
}

void kernel9_omp()
{
	omp_set_num_threads(4);

#pragma omp parallel shared(px, dm28, dm27, dm26, dm24, dm23, dm22, dm25, c0) private(i)
	for (l = 1; l <= loop; l++)
	{
#pragma omp for
		for (i = 0; i < n; i++)
		{
			px[i][0] = dm28 * px[i][12] + dm27 * px[i][11] + dm26 * px[i][10] +
								 dm25 * px[i][9] + dm24 * px[i][8] + dm23 * px[i][7] +
								 dm22 * px[i][6] + c0 * (px[i][4] + px[i][5]) + px[i][2];
		}
	}
	argument = 9;
}

int main()
{
	// fill arrays
	std::fill_n(px, len * len, 1);

	exeTime(kernel9, (char *)"kernel9");
	exeTime(kernel9_omp, (char *)"kernel9_omp");
	return 0;
}
