
#ifndef NMPPS_ASM_DEFS_H_
#define NMPPS_ASM_DEFS_H_

/* /////////////////////////////////////////////////////////////////////////////
//        The following enumerator defines a status of NMPPS operations
//                     negative value means error
//
// Values have been gotten from nmppstypes.h
*/

/* nmppsStatus type values */

/* errors */
#define nmppsStsRoundModeNotSupportedErr 	-213
#define nmppsStsHugeWinErr 				-39
#define nmppsStsShiftErr					-32
#define nmppsStsThreshNegLevelErr			-19
#define nmppsStsThresholdErr 				-18
#define nmppsStsContextMatchErr			-17
#define nmppsStsDivByZeroErr				-10
#define nmppsStsNullPtrErr					-8
#define nmppsStsRangeErr					-7
#define nmppsStsSizeErr					-6
#define nmppsStsBadArgErr					-5
#define nmppsStsNotImplemented				true
/* no errors */
#define nmppsStsNoErr						false
/* warnings  */
#define nmppsStsSqrtNegArg					3
#define nmppsStsInvZero					4
#define nmppsStsDivByZero					6
#define nmppsStsLnZeroArg					7
#define nmppsStsLnNegArg					8

#endif /* NMPPS_ASM_DEFS_H_ */
