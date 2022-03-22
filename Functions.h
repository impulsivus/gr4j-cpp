#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

class Functions
{
public:
    double relative_difference(double a, double b);

    bool is_equal(double a, double b);
};