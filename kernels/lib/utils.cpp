#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#ifndef LIVER_LOVE_LOOPS_H
#define LIVER_LOVE_LOOPS_H

#include <omp.h>
#include <iostream>
#include <sys/time.h>
#include <cmath>

#define loop 100000
#define n (1024 * 7)
#define len (n * 2)

long argument, k, l, ipnt, ipntp, i, m;
long lw, j, nl1, nl2, kx, ky, ip, kn;
long i1, i2, j2, nz, ink, kb5i;
long ii, lb, j4, ng;
int tmp, temp, sum, som;
double s, dm28, dm27, dm26, dm24, dm23, dm22, dm25, c0, expmax;
int b[len][len];
int q = 2, r = 3, t = 7;
long ir[len];
long double rx[len];
long double rh[len];
long double flx;
long double dex1[len];
long double u[len];
long double v[len];
long double w[len];
long double x[len];
long double y[len];
long double z[len];
long double g[len];
long double du1[len];
long double du2[len];
long double du3[len];
long double grd[len];
long double dex[len];
long double xi[len];
long double ex[len];
long double ex1[len];
long double vx[len];
long double xx[len];
long double vsp[len];
long double vstp[len];
long double vxne[len];
long double vxnd[len];
long double ve3[len];
long double vlr[len];
long double vlin[len];
long double b5[len];
long double plan[len];
long double d[len];
long double sa[len];
long double sb[len];
long e[len];
long f[len];
long ix[len];
long zone[len];

long double p[len][len];
long double px[len][len];
long double cx[len][len];
long double vy[len][len];
long double vh[len][len];
long double vf[len][len];
long double vg[len][len];
long double vs[len][len];
long double za[len][len];
long double zp[len][len];
long double zq[len][len];
long double zr[len][len];
long double zm[len][len];
long double zb[len][len];
long double zu[len][len];
long double zv[len][len];
long double zz[len][len];

void exeTime(void (*func)(), char *name)
{
    long mtime, seconds, useconds;
    struct timeval start
    {
    }, end{};
    gettimeofday(&start, nullptr);
    func();
    gettimeofday(&end, nullptr);

    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = (seconds * 1000 + useconds / 1000.0) + 0.5;

    std::cout << name << " elapsed time: " << mtime << " ms\n";
}

#endif

#pragma clang diagnostic pop