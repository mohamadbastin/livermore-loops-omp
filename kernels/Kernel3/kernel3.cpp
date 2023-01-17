#include "../lib/utils.cpp"

void kernel3()
{
    /*
     *******************************************************************
     *   Kernel 3 -- inner product
     *******************************************************************
     *    DO 3 L= 1,Loop
     *         Q= 0.0
     *    DO 3 k= 1,n
     *  3      Q= Q + Z(k)*X(k)
     */

    for (l = 1; l <= loop; l++)
    {
        q = 0.0;
        for (k = 0; k < n; k++)
        {
            q += z[k] * x[k];
        }
    }
    argument = 3;
}

void kernel3_omp()
{
    omp_set_num_threads(4);
#pragma omp parallel shared(x, q, z) private(k)
    for (l = 1; l <= loop; l++)
    {
        q = 0.0;
#pragma omp for
        for (k = 0; k < n; k++)
        {
            q += z[k] * x[k];
        }
    }
    argument = 3;
}

int main()
{
    std::fill_n(x, len, 1);
    std::fill_n(z, len, 3);

    exeTime(kernel3, (char *)"kernel3");
    exeTime(kernel3_omp, (char *)"kernel3_omp");
    return 0;
}
