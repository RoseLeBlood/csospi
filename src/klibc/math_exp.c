
#include <math.h>

double                  frexp(double x, int* exp) ;
float                   frexpf(float x, int* exp) ;
long double             frexpl(long double x, int* exp) ;
double 					log10(double x) ;
float					log10f(float x) ;
long double 			log10l(long double x) ;


double exp(double x) 
{
	return __builtin_exp(x);
}

float expf(float x) 
{
	return __builtin_expf(x);
}

long double expl(long double x) 
{
	return __builtin_expl(x);
}

double exp2(double x)
{
	return __builtin_exp2(x);
}

float exp2f(float x) 
{
	return __builtin_exp2f(x);
}

long double exp2l(long double x) 
{
	return __builtin_exp2l(x);
}

double expm1(double x) 
{
	return __builtin_expm1(x);
}

float expm1f(float x) 
{
	return __builtin_expm1f(x);
}

long double expm1l(long double x) 
{
	return __builtin_expm1l(x);
}



int                     ilogb(double x) 
{
	return __builtin_ilogb(x);
}

int                     ilogbf(float x) 
{
	return __builtin_ilogbf(x);
}

int                     ilogbl(long double x) 
{
	return __builtin_ilogbl(x);
}


double ldexp(double x, int exp) 
{
        return x * (1 << exp);
}

float ldexpf(float x, int exp) 
{
        return x * (1 << exp);
}

long double ldexpl(long double x, int exp) 
{
        return x * (1 << exp);
}

double log(double x) 
{
	return __builtin_log(x);
}

float logf(float x) 
{
	return __builtin_logf(x);
}

long double logl(long double x) 
{
	return __builtin_logl(x);
}



double log1p(double x) 
{
	return __builtin_log1p(x);
}

float log1pf(float x) 
{
   return logf(1 + x);
}

long double log1pl(long double x) 
{
	return logl(1 + x);
}

double log2(double x) 
{
	return __builtin_log2(x);
}

float log2f(float x) 
{
	return __builtin_log2f(x);
}

long double log2l(long double x)
{
	return __builtin_log2l(x);
}

double                  logb(double x)
{
	return __builtin_logb(x);
}
float                           logbf(float x)
{
	return __builtin_logbf(x);
}
long double             logbl(long double x)
{
	return __builtin_logbl(x);
}
double                  modf(double value, double* iptr)
{
	return __builtin_modf(value, iptr);
}
float                   modff(float value, float* iptr)
{
	return __builtin_modff(value, iptr);
}
long double             modfl(long double value, long double* iptr)
{
	return __builtin_modfl(value, iptr);
}
double                  scalbn(double x, int n)
{
	return __builtin_scalbn(x, n);
}
float                   scalbnf(float x, int n)
{
	return __builtin_scalbnf(x, n);
}
long double             scalbnl(long double x, int n)
{
	return __builtin_scalbnl(x, n);
}
double                  scalbln(double x, long int n)
{
	return __builtin_scalbln(x, n);
}
float                   scalblnf(float x, long int n)
{
	return __builtin_scalblnf(x, n);
}
long double             scalblnl(long double x, long int n)
{
	return __builtin_scalblnl(x, n);
}
