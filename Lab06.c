#include <stdio.h>
#include <math.h>
/*Mert Korkmaz 270206029*/
#define start 0.0
#define end 10.0
#define pi 3.142857

double phi(double t)
{
    double value = sin(4 * pi * t);
    return value;
}
double phi_diff(double t, double h)
{
    double value = (phi(t + h) - phi(t)) / h;
    return value;
    //return(phi(t + h) - phi(t)) / h);
}

double xt(double t, double h)
{
    double value = 0.5 * cos(20 * pi * t + phi_diff(t, h)) + 1;
    return value;
}
double simpson(double (*f)(double, double), int n)
{
    double result, h, x;
    int i;

    result = f(start, n);
    h = (end - start) / n;
    for (i = 0; i <= n; i++)
    {
        x = start + i * h;
        result += 4 * f(x - h / 2, n) + 2 * f(x, n);
    }
    result -= f(end, n);
    return (h * result / 6);
}
double adaptive_simpson(double (*f)(double, double), int n0, double tol)
{
    double check = tol + 1.0;
    double lowval, val;
    lowval = simpson(f, n0);
    while (check > tol)
    {
        n0 = 2 * n0;
        val = simpson(f, n0);
        check = (fabs(val - lowval) / val);
        lowval = val;
    }
    return val;
}

void main()
{
    int i, panel;
    double tol = 0.0001;
    printf("Number of panels\tSimpson's\t Adaptive Simpons's\n");
    printf("---------------------------------------------------------------------\n");
    for (i = 0; i < 20; i++)
    {
        panel = 10 * (i + 1);

        printf("\t%d\t%lf\t%lf\n", panel, simpson(xt, panel), adaptive_simpson(xt, panel, tol));
    }
}
