#include <stdio.h>
#include <math.h>

#define d 0.5
#define L 1.4
#define pi 3.141592
#define lamb 3.6
#define a 2.28
#define TRUE 1
#define FALSE 0

double f(double x);                                         // f(x): it should take x as an input argument
double f_prime(double x);                                   // f'(x): it should take x as an input argument
double K_();                                                // since the variables are globally defined, it has no need an argument
double e_r(double x);                                       // it needs the final form of x, not the iterative on
void degree_to_radian(double *x);                           //takes degree and converts it to radian
double *newtonsAlg(double initial_guess, double tolerance); //calculate the root
double *tolerance_value_generator();                        //returns 6 different tolerance value with a single pointer: 10^-6, 10^-5, ..., 10^-1

double e_r(double x)
{
    double er;
    er = (pow(a / d, 2) * pow(x / pi, 2) + 1) / (pow(2 * a / lamb, 2) + 1);
    return er;
}
double K_()
{
    double k = tan((2 * pi * (d + L)) / lamb) / (2 * pi * (d / lamb));
    return k;
}
double f(double e_r)
{
    double f;
    f = tan(e_r) - K_();
    return f;
}

void degree_to_radian(double *x)
{
    *x = -tan(*x * pi / 180);
}

double f_prime(double e_r)
{
    double prime;
    prime = pow(1 / cos(e_r), 2) - K_();
    return prime;
}

double *tolerance_value_generator()
{
    int i = 6;
    static double count;
    count = pow(10, -i);
    i--;

    return &count;
}
double *newtonsAlg(double initial_guess, double tolerance)
{
    int *error;
    double deltax;
    deltax = 2.0 * tolerance;
    *error = FALSE;
    while (!(*error) && fabs(deltax) > tolerance)
    {
        deltax = f(initial_guess) / f_prime(initial_guess);
        initial_guess = initial_guess - deltax;
    }
}
int main()
{
    int i;
    double x = 0, p[6], *newton, *p1;
    while ((x < 90) || (x > 270))
    {
        printf("Initial point in degrees (between 90 and 270) :");
        scanf("%lf", &x);
    }

    degree_to_radian(&x);
    // double tol[6];
    for (i = 0; i < 6; i++)
    {
        p1 = *tolerance_value_generator;

        printf("%lf", x);
        printf("\nTolerance: %lf", p1);
        printf("\nDielectric constant (e_r): %lf", e_r(x));
        printf("\nRoot of f(x) where x is in radians: %lf ", *newton);
    }
}
