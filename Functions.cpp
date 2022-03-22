#include "Functions.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

double Functions::relative_difference(double a, double b)
{
    double c = ABS(a);
    double d = ABS(b);

    d = MAX(c, d);

    return d == 0.0 ? 0.0 : ABS(a - b) / d;
}

bool Functions::is_equal(double a, double b)
{
    return relative_difference(a, b) < 0.000001;
}