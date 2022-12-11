#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#ifndef LIVER_LOVE_LOOPS_H
#define LIVER_LOVE_LOOPS_H

#include <omp.h>
#include <iostream>
#include <sys/time.h>

#define loop 100000
#define n (1024 * 7)

long argument, k, l, ipnt, ipntp, i;
long lw, j, nl1, nl2, kx, ky, ip, kn;
long i1, j1, i2, j2, nz, ink, jn, kb5i;
long ii, lb, j4, ng;
int tmp, temp, sum, som;
char name[8];
int x[n * 2];
int y[n * 2];
int z[n * 2];
int v[n * 2];
int w[n * 2];
int b[n * 2][n * 2];
int q = 2, r = 3, t = 7;

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