#include "../lib/utils.cpp"

void kernel1()
{

    /*
     *******************************************************************
     *   Kernel 1 -- hydro fragment
     *******************************************************************
     *       DO 1 L = 1,Loop
     *       DO 1 k = 1,n
     *  1       X(k)= Q + Y(k)*(R*ZX(k+10) + T*ZX(k+11))
     */

    for (l = 1; l <= loop; l++)
    {
        for (k = 0; k < n; k++)
        {
            x[k] = q + y[k] * (r * z[k + 10] + t * z[k + 11]);
        }
    }
    argument = 1;
}

void kernel1_omp()
{
    omp_set_num_threads(4);
#pragma omp parallel shared(x, q, y, r, z, t) private(k)
    for (l = 1; l <= loop; l++)
    {
#pragma omp for
        for (k = 0; k < n; k++)
        {
            x[k] = q + y[k] * (r * z[k + 10] + t * z[k + 11]);
        }
    }
    argument = 1;
}

int main()
{
    std::fill_n(x, len, 1);
    std::fill_n(y, len, 2);
    std::fill_n(z, len, 3);

    exeTime(kernel1, (char *)"kernel1");
    exeTime(kernel1_omp, (char *)"kernel1_omp");
    return 0;
}
