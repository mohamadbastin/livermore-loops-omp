#include "utils.cpp"

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

    /*
     *******************************************************************
     *   Kernel 1 -- hydro fragment
     *******************************************************************
     *       DO 1 L = 1,Loop
     *       DO 1 k = 1,n
     *  1       X(k)= Q + Y(k)*(R*ZX(k+10) + T*ZX(k+11))
     */
    omp_set_num_threads(8);

    for (l = 1; l <= loop; l++)
    {
#pragma omp parallel for    
        for (k = 0; k < n; k++)
        {
            x[k] = q + y[k] * (r * z[k + 10] + t * z[k + 11]);
        }
    }
    argument = 1;
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

    exeTime(kernel1, "kernel1");
    exeTime(kernel1_omp, "kernel1_omp");
    return 0;
}
