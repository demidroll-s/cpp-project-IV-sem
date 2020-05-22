#include "matlib.h"

using namespace std;

vector<double> lin_space(double from, double to, int num_points)
{
    ASSERT(num_points >= 2);
    vector<double> ret(num_points, 0.0);
    double step = (to - from)/(num_points - 1);
    double current = from;
    for (int i = 0; i < num_points; i++)
    {
        ret[i] = current;
        current += step;
    }
    return ret;
}

double sum(const std::vector<double>& v)
{
    double total = 0.0;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        total += v[i];
    }
    return total;
}

double mean(const vector<double>& v)
{
    int n = v.size();
    ASSERT(n > 0);
    return sum(v)/n;
}

double standard_deviation(const vector<double>& v, bool population)
{
    int n = v.size();
    double total = 0.0;
    double total_sq = 0.0;
    for (int i = 0; i < n; i++)
    {
        total += v[i];
        total_sq += v[i]*v[i];
    }
    if (population)
    {
        ASSERT(n > 0);
        return sqrt((total_sq - total * total/n)/n);
    }
    else
    {
        ASSERT(n > 1);
        return sqrt((total_sq - total*total/n)/(n-1));
    }
}

double min(const vector<double>& v)
{
    int n = v.size();
    ASSERT(n > 0);
    double min = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] < min)
            min=v[i];
    return min;
}

double max(const vector<double>& v)
{
    int n = v.size();
    ASSERT(n > 0);
    double max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max=v[i];
    return max;
}

vector<double> rand_uniform_old(int n)
{
    vector<double> ret(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        int rand_int = rand();
        ret[i] = (rand_int + 0.5)/(RAND_MAX + 1.0);
    }
    return ret;
}

static mt19937 Mersenne_twister;

void rng(const string& description)
{
    ASSERT(description == "default");
    Mersenne_twister.seed(mt19937::default_seed);
}

vector<double> rand_uniform(int n)
{
    vector<double> ret(n, 0.0);
    for(int i = 0; i <n; i++)
        ret[i] = (Mersenne_twister() + 0.5)/(Mersenne_twister.max() + 1.0);
    return ret;
}

vector<double> rand_n(int n)
{
    vector<double> v = rand_uniform(n);
    for(int i = 0; i < n; i++)
        v[i] = norminv(v[i]);
    return v;
}

std::vector<double> sort(const std::vector<double>& v)
{
    std::vector<double> copy(v);
    std::sort(copy.begin(), copy.end());
    return copy;
}

double prctile(const std::vector<double>& v, double percentage) 
{
    ASSERT(percentage >= 0.0);
    ASSERT(percentage <= 100.0);

    int n = v.size();
    vector<double> sorted = sort(v);
 
    int index_below = (int)(n * percentage/100.0 - 0.5);
    int index_above = index_below + 1;

    if (index_above > n - 1)     
        return sorted[n - 1];
    if (index_below < 0)
        return sorted[0];

    double value_below = sorted[index_below];
    double value_above = sorted[index_above];
    double percentage_below = 100.0 * (index_below + 0.5)/n;
    double percentage_above = 100.0 * (index_above + 0.5)/n;
    if (percentage <= percentage_below)
        return value_below;
    if (percentage >= percentage_above)
        return value_above;
    double correction = (percentage - percentage_below) * (value_above - value_below)/(percentage_above-percentage_below);
    return value_below + correction;
}

static inline double Horner(double x, double a0, double a1)
{
    return a0 + x * a1;
}

static inline double Horner(double x, double a0, double a1, double a2)
{
    return a0 + x * Horner(x, a1, a2);
}

static inline double Horner(double x, double a0, double a1, double a2, double a3)
{
    return a0 + x * Horner(x, a1, a2, a3);
}

static inline double Horner(double x, double a0, double a1, double a2, double a3, double a4)
{
    return a0 + x * Horner(x, a1, a2, a3, a4);
}

static inline double Horner(double x, double a0, double a1, double a2, double a3, double a4, double a5)
{
    return a0 + x * Horner(x, a1, a2, a3, a4, a5);
}

static inline double Horner(double x, double a0, double a1, double a2, double a3, double a4, double a5, double a6)
{
    return a0 + x * Horner(x, a1, a2, a3, a4, a5, a6);
}

static inline double Horner(double x, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7)
{
    return a0 + x * Horner(x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double Horner(double x, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
    return a0 + x * Horner(x, a1, a2, a3, a4, a5, a6, a7, a8);
}

double normcdf(double x)
{
    if (x < 0)
        return 1 - normcdf(-x);
    double k = 1/(1 + 0.2316419 * x);
    double poly = Horner(k, 0.0, 0.319381530, -0.356563782, 1.781477937, -1.821255978, 1.330274429);
    double approx = 1.0 - 1.0/sqrt(2 * M_PI) * exp(-0.5 * x * x) * poly;
    return approx;
}

/* Constants required for Moro's algorithm */
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;
 
double norminv(double x)
{
    // We use Moro's algorithm
    double y = x - 0.5;
    if (y < 0.42 && y > -0.42)
    {
        double r = y * y;
        return y * Horner(r, a0, a1, a2, a3)/Horner(r, 1.0, b1, b2, b3, b4);
    }
    else
    {
        double r;
        if (y < 0.0)
            r = x;
        else 
            r = 1.0 - x;
        double s = log(-log(r));
        double t = Horner(s, c0, c1, c2, c3 ,c4 ,c5 ,c6 ,c7 ,c8);
        if (x > 0.5)
            return t;
        else
            return -t;
    }
}
