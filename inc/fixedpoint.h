#ifndef FIXEDPOINT_H_
#define FIXEDPOINT_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef uint16_t	FP;

/******************************************************************************
 * Function declarations
 *****************************************************************************/
int16_t	FP_ToInt
(
	FP	fp
);

FP	FP_FromInt
(
	int16_t	val
);

FP	FP_Add
(
	FP	a,
	FP	b
);

FP	FP_Sub
(
	FP	a,
	FP	b
);

FP	FP_Mul
(
	FP	a,
	FP	b
);

FP	FP_Div
(
	FP	a,
	FP	b
);

FP	FP_Neg
(
	FP	fp
);

// -1 = a < b, 0 = a == b, 1 = a > b
int8_t	FP_Compare
(
	FP	a,
	FP	b
);

FP	FP_Abs
(
	FP	fp
);

FP	FP_Sqrt
(
	FP	fp
);

#endif