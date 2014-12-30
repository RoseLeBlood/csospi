#include <math.h>

double cbrt(double x) 
{
        return pow(x, 1. / 3.);
}

float cbrtf(float x) 
{
        return powf(x, 1. / 3.);
}

long double cbrtl(long double x) 
{
        return powl(x, 1. / 3.);
}

double fabs(double x)
{
	return __builtin_fabs(x);
}

float fabsf(float x) 
{
	return __builtin_fabsf(x);
}

long double fabsl(long double x)
{
	return __builtin_fabsl(x);
}

double hypot(double x, double y) 
{
        return sqrt(x*x + y*y);
}

float hypotf(float x, float y) 
{
        return sqrt(x*x + y*y);
}

long double hypotl(long double x, long double y) 
{
        return sqrt(x*x + y*y);
}

double pow(double x, double y) 
{
        return exp(y * log(x));
}

float powf(float x, float y) 
{
        return exp(y * log(x));
}

long double powl(long double x, long double y) 
{
        return exp(y * log(x));
}

double sqrt(double x) 
{
     return __builtin_sqrt(x);
}
long double sqrtl(long double x) 
{
     return __builtin_sqrtl(x);
}
float sqrtf(float x)
{
	return __builtin_sqrtf(x);
}
