#ifndef _FLOAT_H
#define	_FLOAT_H

#ifdef	__cplusplus
extern "C" {
#endif

extern int __flt_rounds;
#define	FLT_ROUNDS	__flt_rounds

int __fltrounds();

#define	FLT_RADIX	2
#define	FLT_MANT_DIG	24
#define	FLT_EPSILON	1.192092896E-07F
#define	FLT_DIG		6
#define	FLT_MIN_EXP	(-125)
#define	FLT_MIN		1.175494351E-38F
#define	FLT_MIN_10_EXP	(-37)
#define	FLT_MAX_EXP	(+128)
#define	FLT_MAX		3.402823466E+38F
#define	FLT_MAX_10_EXP	(+38)

#define	DBL_MANT_DIG	53
#define	DBL_EPSILON	2.2204460492503131E-16
#define	DBL_DIG		15
#define	DBL_MIN_EXP	(-1021)
#define	DBL_MIN		2.2250738585072014E-308
#define	DBL_MIN_10_EXP	(-307)
#define	DBL_MAX_EXP	(+1024)
#define	DBL_MAX		1.7976931348623157E+308
#define	DBL_MAX_10_EXP	(+308)

#define	LDBL_MANT_DIG	64
#define	LDBL_EPSILON	1.0842021724855044340075E-19L
#define	LDBL_DIG	18
#define	LDBL_MIN_EXP	(-16381)
#define	LDBL_MIN	3.3621031431120935062627E-4932L
#define	LDBL_MIN_10_EXP	(-4931)
#define	LDBL_MAX_EXP	(+16384)
#define	LDBL_MAX	1.1897314953572317650213E+4932L
#define	LDBL_MAX_10_EXP	(+4932)

#ifdef	__cplusplus
}
#endif

#endif
