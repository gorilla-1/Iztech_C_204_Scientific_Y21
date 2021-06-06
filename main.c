#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} Vector;

typedef struct
{
    double mass1, mass2, mass12;
    Vector planet1, planet2;
    double u[4];
} Twobodymodel;

typedef struct
{
    double eccentricity, mass_ratio, dt;
    int period;
} Twobodycontroller;

void initiate(Twobodymodel *model, Twobodycontroller *controller);
void comp_euler(Twobodycontroller *controller, Twobodymodel *model);
void runge_kutta(Twobodycontroller *controller, Twobodymodel *model);
void comp_rungekutta(Twobodymodel *model, Twobodycontroller *controller);
double *derivative(Twobodymodel *model, Twobodycontroller *controller);
void euler(Twobodycontroller *controller, Twobodymodel *model);
void newPosition(Twobodymodel *model);

void initiate(Twobodymodel *model, Twobodycontroller *controller)
{ //masses
    model->mass1 = 1.0;
    model->mass2 = controller->mass_ratio * model->mass1;
    model->mass12 = model->mass1 + model->mass2;
    //locations
    model->planet1.x = 0;
    model->planet1.y = 0;
    model->planet2.x = 0;
    model->planet2.y = 0;
    //velocities: based on having a stable orbit
    model->u[0] = 1;
    model->u[1] = model->u[2] = 0;
    model->u[3] = sqrt((1 + controller->mass_ratio) * (1 + controller->eccentricity));
}
void comp_rungekutta(Twobodymodel *model, Twobodycontroller *controller)
{
    double t;
    FILE *fileptr;
    fileptr = fopen("c_Locations_runge.txt", "w");
    for (t = 0; t < controller->period; t += controller->dt)
    {
        runge_kutta(controller, model);
        newPosition(model);
        fprintf(fileptr, "Time: %.2lf Planet 1:%lf , %lf\n", t, model->planet1.x, model->planet1.y);
        fprintf(fileptr, "Time: %.2lf Planet 2:%lf , %lf\n\n", t, model->planet2.x, model->planet2.y);
    }
}
double *derivative(Twobodymodel *model, Twobodycontroller *controller)
{
    double *du, *r;
    du = (double *)malloc(4 * sizeof(double));
    r = (double *)malloc(4 * sizeof(double));
    r[0] = model->u[0];
    r[1] = model->u[1];
    double r_val = sqrt(pow(r[0], 2) + pow(r[1], 2));
    int i;
    for (i = 0; i < 2; i++)
    {
        du[i] = model->u[i + 2];
        du[i + 2] = -((1 + controller->mass_ratio) * r[i]) / pow(r_val, 3);
    }

    free(r);
    return du;
}

void runge_kutta(Twobodycontroller *controller, Twobodymodel *model)
{
    int i, j, k, length;
    length = sizeof(model->u) / sizeof(model->u[0]);
    double a[4] = {controller->dt / 2, controller->dt / 2, controller->dt, 0},
           b[4] = {controller->dt / 6, controller->dt / 3, controller->dt / 3, controller->dt / 6},
           u0[4] = {0, 0, 0, 0},
           ut[4] = {0, 0, 0, 0},
           *du = (double *)malloc(4 * sizeof(double));

    for (i = 0; i < length; i++)
    {
        u0[i] = model->u[i];
        ut[i] = 0;
    }
    for (j = 0; j < length; j++)
    {
        du = derivative(model, controller);
        for (k = 0; k < length; k++)
        {
            model->u[k] = u0[k] + a[j] * du[k];
            ut[k] += b[j] * du[k];
        }
    }
    for (i = 0; i < length; i++)
        model->u[i] = ut[i] + u0[i];
    free(du);
}

void comp_euler(Twobodycontroller *controller, Twobodymodel *model)
{
    double t;
    FILE *fileptr;
    fileptr = fopen("c_Locations_euler.txt", "w");
    for (t = 0; t < controller->period; t += controller->dt)
    {
        euler(controller, model);
        newPosition(model);
        fprintf(fileptr, "Time:%.2lf Planet 1:%lf , %lf\n", t, model->planet1.x, model->planet1.y);
        fprintf(fileptr, "Time:%.2lf Planet 2:%lf , %lf\n\n", t, model->planet2.x, model->planet2.y);
    }
}
void euler(Twobodycontroller *controller, Twobodymodel *model)
{
    double x_init, y_init, velocity_x, velocity_y;
    x_init = model->u[0];
    y_init = model->u[1];
    velocity_x = model->u[2];
    velocity_y = model->u[3];
    int i;
    for (i = 0; i < 2; i++)
        model->u[i] += model->u[i + 2] * controller->dt;

    model->u[2] = velocity_x + (-x_init / sqrt(pow(pow(x_init, 2) + pow(y_init, 2), 3)));
    model->u[3] = velocity_y + (-y_init / sqrt(pow(pow(x_init, 2) + pow(y_init, 2), 3)));
}
void newPosition(Twobodymodel *model)
{
    double p1, p2;
    p1 = (model->mass2 / model->mass12);
    p2 = (model->mass1 / model->mass12);

    model->planet1.x = -p2 * model->u[0]; //updating the location of bodies each cycle
    model->planet1.y = -p2 * model->u[1];

    model->planet2.x = p1 * model->u[2];
    model->planet2.y = p1 * model->u[3];
}
int main()
{
    Twobodymodel model;
    Twobodycontroller controller;
    int choice;
    printf("Enter mass ratio: ");
    scanf("%lf", &controller.mass_ratio);
    printf("Enter eccentricity: ");
    scanf("%lf", &controller.eccentricity);
    printf("Enter period: ");
    scanf("%u", &controller.period);
    printf("Enter stepsize: ");
    scanf("%lf", &controller.dt);
    initiate(&model, &controller);
    printf("Choose method\n1:RungeKutta\n2:Euler\n\t:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        comp_rungekutta(&model, &controller);
        break;

    case 2:
        comp_euler(&controller, &model);
        break;

    default:
        break;
    }
}
