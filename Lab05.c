//Mert Korkmaz
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define e 2.71828182845904523536
#define initial 0.0
#define end 30.0
#define phase(i) *(phase + i)
double f1(double x)
{
    double ans = pow(e, -0.1 * x * x);
    return ans;
}
double f2(double x)
{
    double ans = 2 * pow(e, -0.2 * x);
    return ans;
}
double trapezoidal(double (*f)(double), int n)
{
    int i;
    double x, h, sum = 0, integral;
    h = (end - initial) / n;
    for (i = 1; i < n; i++)
    {
        x = initial + i * h;
        sum = sum + f(x);
    }
    integral = (h / 2) * (f(initial) + f(end) + 2 * sum);
    return integral;
}

double rectangular(double (*f)(double), int n) //left rectangular
{
    double x, i, sum = 0, h;
    h = (end - initial) / n;
    for (i = 0; i < n; i++)
    {
        x = i * h; //didn't add initial because already starts from initial
        sum += f(x);
    }
    return (sum * h);
}
int *number_of_panels_generator()
{
    int step, i;
    int *phase = malloc(sizeof(int) * 20);
    for (step = 50, i = 0; step <= 1000; step = step + 50, i++)
        phase(i) = step;

    return phase;
}

int main()
{
    int i, n;
    double rec_f1, trap_f1, rec_f2, trap_f2, rec_area, trap_area;
    printf("\t\t    Rect. f1\tTrap f.1\tRect. f2\tTrap. f2\tRect Area\tTrap Area\n");
    int *phase = number_of_panels_generator();
    for (i = 0; i <= 20; i++)
    {
        n = phase(i);

        rec_f1 = rectangular(f1, n);
        rec_f2 = rectangular(f2, n);
        trap_f1 = trapezoidal(f1, n);
        trap_f2 = trapezoidal(f2, n);
        rec_area = rec_f2 - rec_f1;
        trap_area = trap_f2 - trap_f1;
        if (n > 0)
            printf("Number of panels:%d  %lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", n, rec_f1, trap_f1, rec_f2, trap_f2, rec_area, trap_area);
    }
}
