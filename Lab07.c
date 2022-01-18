#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define e 2.718281

double fY(double x)
{
    return (pow(e, (-pow(x, 5) / 5 + pow(x, 3) / 3 - pow(x, 2) / 2)));
}

double fYdx(double x, double y)
{
    return (y * (-pow(x, 4) + pow(x, 2) - x));
}

double euler(double (*fYdx1)(double, double), double xFirst, double yFirst, double xLast, double step)
{
    int i;
    for (i = 0, xFirst <= xLast; xFirst += step; i++)
        yFirst += step * fYdx1(xFirst, yFirst);

    return yFirst;
}
double midpoint(double (*fYdx2)(double, double), double xfirst, double yfirst, double xlast, double step)
{
    double tmp = 0;
    int i;
    for (i = 0; xfirst <= xlast; xfirst = xfirst + step, i++)
    {
        tmp = step * fYdx2(xfirst, yfirst);
        yfirst += step * fYdx2(xfirst + step / 2.0, yfirst + tmp / 2.0);
    }
    return yfirst;
}

double RK4(double (*fYdx3)(double, double), double xfirst, double yfirst, double xlast, double step)
{
    double k, k1, k2, k3, k4;
    int i;
    for (i = 0; xfirst <= xlast; xfirst = xfirst + step, i++)
    {
        k1 = fYdx3(xfirst, yfirst);
        k2 = fYdx3(xfirst + step / 2.0, yfirst + (step / 2.0) * k1);
        k3 = fYdx3(xfirst + step / 2.0, yfirst + (step / 2.0) * k2);
        k4 = fYdx3(xfirst + step, yfirst + step * k3);
        k = (step * (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0);
        yfirst = yfirst + k;
    }
    return yfirst;
}

int main()
{
    int i;
    double x0, y0, xLast, step;
    double eu = 0, mid = 0, rk = 0;

    printf("Please enter xfirst, yfirst, xlast, step \n\n");
    scanf("%lf", &x0);
    scanf("%lf", &y0);
    scanf("%lf", &xLast);
    scanf("%lf", &step);
    printf("Trial: y=%lf g=%lf\n ", fY(0.1), fYdx(-0.1, 0.5));

    printf(" \t \t \t Euler \t Midpoint  KR4 \t    Exact\n");
    for (i = 0; x0 <= xLast + step; x0 += step, i++)
    {
        eu = euler(fYdx, x0, y0, xLast, step);
        mid = midpoint(fYdx, x0, y0, xLast, step);
        rk = RK4(fYdx, x0, y0, xLast, step);
        printf("Step %d-y(%lf)---%lf---%lf---%lf---%lf \n", i, x0, eu, mid, rk, fY(x0));
    }
    return 0;
}
