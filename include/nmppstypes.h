//  2017 Module Derivative Types and Macro Definitions

#ifndef __NMPPSTYPES_H__
#define __NMPPSTYPES_H__


#define NMPPS_TRUNC(a,b) ((a)&~((b)-1))
#define NMPPS_APPEND(a,b) (((a)+(b)-1)&~((b)-1))


/* /////////////////////////////////////////////////////////////////////////////
//        The following enumerator defines a status of NMPPS operations
//                     negative value means error
*/
typedef enum {
    /* errors */

    nmppsStsRoundModeNotSupportedErr  = -213, /* Rounding mode is not supported. */
    nmppsStsHugeWinErr            = -39,   /* Kaiser window is too big.                                             */
    nmppsStsShiftErr              = -32,   /* Shift value is less than zero.                                                */
    nmppsStsThreshNegLevelErr     = -19,   /* Negative value of the level in the threshold operation.    */
    nmppsStsThresholdErr          = -18,   /* Invalid threshold bounds. */
    nmppsStsContextMatchErr       = -17,   /* Context parameter does not match the operation. */
    nmppsStsDivByZeroErr          = -10,   /* An attempt to divide by zero. */
    nmppsStsNullPtrErr            = -8,    /* Null pointer error. */
    nmppsStsRangeErr              = -7,    /* Incorrect values for bounds: the lower bound is greater than the upper bound. */
    nmppsStsSizeErr               = -6,    /* Incorrect value for data size. */
    nmppsStsBadArgErr             = -5,    /* Incorrect arg/param of the function.  */

     /* no errors */
    nmppsStsNoErr                 =   0,   /* No errors. */

     /* warnings  */
    nmppsStsSqrtNegArg        =   3,       /* Negative value(s) for the argument in the Sqrt function. */
    nmppsStsInvZero           =   4,       /* INF result. Zero value was met by InvThresh with zero level. */    
    nmppsStsDivByZero         =   6,       /* Zero value(s) for the divisor in the Div function. */
    nmppsStsLnZeroArg         =   7,       /* Zero value(s) for the argument in the Ln function.     */
    nmppsStsLnNegArg          =   8,       /* Negative value(s) for the argument in the Ln function. */
    
} nmppsStatus;

#define nmppsStsOk nmppsStsNoErr

typedef enum {
    nmppsRndZero,
    nmppsRndNear,
    nmppsRndFinancial,
    nmppsRndHintAccurate=0x10
} nmppsRoundMode;


typedef enum {
    nmppsAlgHintNone,
    nmppsAlgHintFast,
    nmppsAlgHintAccurate
} nmppsHintAlgorithm;

typedef enum {
    nmppsCmpLess,
    nmppsCmpLessEq,
    nmppsCmpEq,
    nmppsCmpGreaterEq,
    nmppsCmpGreater
} nmppsCmpOp;

typedef struct RandUniState_8u nmppsRandUniState_8u;
typedef struct RandUniState_16s nmppsRandUniState_16s;
typedef struct RandUniState_32f nmppsRandUniState_32f;
typedef struct RandUniState_64f nmppsRandUniState_64f;


#endif /* __NMPPSTYPES_H__ */
