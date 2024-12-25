#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H

#define Q 14
#define F (1 << Q)

#define INT_TO_FP(n) ((n) << Q)
#define FP_TO_INT(x) ((x) >> Q)
#define FP_TO_NEAREST_INT(x) ((x) >= 0  ? FP_TO_INT((x) + (F >> 1)) : \
                              FP_TO_INT((x) - (F >> 1)))
#define FP_MUL(x, y) ((int) ((((int64_t) (x)) * (y)) >> Q))
#define FP_DIV(x, y) ((int) ((((int64_t) (x)) << Q) / (y)))

#endif  /* threads/fixed-point.h */
/*This code simplifies fixed-point arithmetic by abstracting common operations with macros. 
It is particularly useful in environments where precise fractional computation is needed but floating-point hardware is unavailable or undesired.*/
/*Macros:

    INT_TO_FP(n):
        Converts an integer n to fixed-point representation.
        Formula: fixed_point=n×Ffixed_point=n×F
        Implementation: ((n) << Q) shifts the integer left by 14 bits to multiply by FF.

    FP_TO_INT(x):
        Converts a fixed-point number x to an integer by discarding the fractional part.
        Formula: integer=fixed_pointFinteger=Ffixed_point​
        Implementation: ((x) >> Q) shifts right by 14 bits to divide by FF.

    FP_TO_NEAREST_INT(x):
        Converts a fixed-point number x to the nearest integer.
        Adds or subtracts F22F​ (depending on the sign) before truncating the fractional part.
        Formula:
            integer=⌊fixed_point+F2F⌋integer=⌊Ffixed_point+2F​​⌋ (for x≥0x≥0).
            integer=⌊fixed_point−F2F⌋integer=⌊Ffixed_point−2F​​⌋ (for x<0x<0).
        Implementation:

    ((x) >= 0 ? FP_TO_INT((x) + (F >> 1)) : FP_TO_INT((x) - (F >> 1)))

FP_MUL(x, y):

    Multiplies two fixed-point numbers x and y.
    Since F×F=F2F×F=F2, the result is scaled too high. To correct this, the product is shifted right by QQ bits.
    Formula: result=x⋅yFresult=Fx⋅y​
    Implementation:

    ((int) ((((int64_t) (x)) * (y)) >> Q))

    Uses int64_t for intermediate multiplication to avoid overflow.

FP_DIV(x, y):

    Divides a fixed-point number x by another fixed-point number y.
    To maintain precision, x is scaled up by FF before performing integer division.
    Formula: result=x⋅Fyresult=yx⋅F​*/