//2017 Module Signal Processing 

#ifndef  	__NMPPSS_H__
#define 	__NMPPSS_H__

#include "nmppsbase.h"
#include "nmppstypes.h"

#define   NMPPSAPI( type,name,arg )        type name arg;

/* /////////////////////////////////////////////////////////////////////////////
//                   Vector Initialization functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsCopy
//  Purpose:    Copy data from source to destination vector
//  Parameters:
//    pSrc        Pointer to input vector
//    pDst        Pointer to output vector
//    len         Length of vectors in elements
//  Returns:
//    nmppsStsNullPtrErr        One of the pointers is NULL
//    nmppsStsSizeErr           Vector length is less than 1
//    nmppsStsNoErr             Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsCopy_8u,   (const nmpps8u*   pSrc, nmpps8u*   pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_16s,  (const nmpps16s*  pSrc, nmpps16s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_16sc, (const nmpps16sc* pSrc, nmpps16sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_32f,  (const nmpps32f*  pSrc, nmpps32f*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_32fc, (const nmpps32fc* pSrc, nmpps32fc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_64f,  (const nmpps64f*  pSrc, nmpps64f*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_64fc, (const nmpps64fc* pSrc, nmpps64fc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_32s,  (const nmpps32s*  pSrc, nmpps32s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_32sc, (const nmpps32sc* pSrc, nmpps32sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_64s,  (const nmpps64s*  pSrc, nmpps64s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_64sc, (const nmpps64sc* pSrc, nmpps64sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsCopy_1u,   (const nmpps8u* pSrc, int srcBitOffset, nmpps8u* pDst, int dstBitOffset, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsMove
//  Purpose:    nmppsMove function copies "len" elements from src to dst.
//              If some regions of source and destination areas overlap,
//              nmppsMove ensures that original source bytes in overlapping
//              region are copied before being overwritten.
//
//  Parameters:
//    pSrc        Pointer to input vector
//    pDst        Pointer to output vector
//    len         Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr        One of pointers is NULL
//    nmppsStnmppseErr           Vectors' length is less than 1
//    nmppsStsNoErr             Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsMove_8u,   (const nmpps8u*   pSrc, nmpps8u*   pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMove_16s,  (const nmpps16s*  pSrc, nmpps16s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMove_16sc, (const nmpps16sc* pSrc, nmpps16sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMove_32s,  (const nmpps32s*  pSrc, nmpps32s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMove_32sc, (const nmpps32sc* pSrc, nmpps32sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMove_64s,  (const nmpps64s*  pSrc, nmpps64s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMove_64sc, (const nmpps64sc* pSrc, nmpps64sc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsSet
//  Purpose:    Set elements of destination vector to defined value
//  Parameters:
//    val        Value to set for all vector's elements
//    pDst       Pointer to destination vector
//    len        Vectors' length
//  Return:
//    nmppsStsNullPtrErr        Pointer to vector is NULL
//    nmppsStsSizeErr           Vector length is less than 1
//    nmppsStsNoErr             Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsSet_16sc, (nmpps16sc val, nmpps16sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsSet_32sc, (nmpps32sc val, nmpps32sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsSet_64sc, (nmpps64sc val, nmpps64sc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsZero
//  Purpose:    Reset all vector elements
//  Parameters:
//    pDst       Pointer to destination vector
//    len        Vector length
//  Return:
//    nmppsStsNullPtrErr        Pointer to vector is NULL
//    nmppsStsSizeErr           Vector length is less than 1
//    nmppsStsNoErr             Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsZero_8u,   (nmpps8u*   pDst, int len))
NMPPSAPI(nmppsStatus, nmppsZero_16s,  (nmpps16s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsZero_16sc, (nmpps16sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsZero_32s,  (nmpps32s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsZero_32sc, (nmpps32sc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsZero_64s,  (nmpps64s*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsZero_64sc, (nmpps64sc* pDst, int len))



/* /////////////////////////////////////////////////////////////////////////
// Name:            nmppsRandUniform
// Purpose:         Initialize vector with uniformly distributed values
// Parameters:
//    pDst          Pointer to vector
//    len           Vector length
//    pRandUniState Pointer to RandUniState structure
// Returns:
//    nmppsStsNullPtrErr       One of pointers is NULL
//	  nmppsStsSizeErr		   length of the vector is less 1
//    nmppsStsContextMatchErr  State structure has invalid content
//    nmppsStsNoErr            No errors
*/
NMPPSAPI(nmppsStatus, nmppsRandUniform_8u,  (nmpps8u* pDst,  int len))
NMPPSAPI(nmppsStatus, nmppsRandUniform_16s, (nmpps16s* pDst, int len))


/* /////////////////////////////////////////////////////////////////////////////
//                      Vector logical functions
///////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Names:              nmppsLShiftC, nmppsRShiftC
//  Purpose:            logical operations and vector shifts
//  Parameters:
//   val                1) value to be ANDed/ORed/XORed with each element of the vector (And, Or, Xor);
//                      2) position`s number which vector elements to be SHIFTed on (ShiftC)
//   pSrc               pointer to input vector
//   pSrcDst            pointer to input/output vector
//   pSrc1              pointer to first input vector
//   pSrc2              pointer to second input vector
//   pDst               pointer to output vector
//   len                vector's length
//  Return:
//   nmppsStsNullPtrErr      pointer(s) to the data is NULL
//   nmppsStsSizeErr         vector`s length is less or equal zero
//   nmppsStsShiftErr        shift`s value is less zero
//   nmppsStsNoErr           otherwise
*/

NMPPSAPI(nmppsStatus, nmppsLShiftC_8u_I,  (                    int val, nmpps8u*  pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_8u,    (const nmpps8u*  pSrc, int val, nmpps8u*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_16u_I, (                    int val, nmpps16u* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_16u,   (const nmpps16u* pSrc, int val, nmpps16u* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_16s_I, (                    int val, nmpps16s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_16s,   (const nmpps16s* pSrc, int val, nmpps16s* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_32s_I, (                    int val, nmpps32s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsLShiftC_32s,   (const nmpps32s* pSrc, int val, nmpps32s* pDst,    int len))

NMPPSAPI(nmppsStatus, nmppsRShiftC_8u_I,  (                    int val, nmpps8u*  pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_8u,    (const nmpps8u*  pSrc, int val, nmpps8u*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_16u_I, (                    int val, nmpps16u* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_16u,   (const nmpps16u* pSrc, int val, nmpps16u* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_16s_I, (                    int val, nmpps16s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_16s,   (const nmpps16s* pSrc, int val, nmpps16s* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_32s_I, (                    int val, nmpps32s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsRShiftC_32s,   (const nmpps32s* pSrc, int val, nmpps32s* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//                  Arithmetic functions
///////////////////////////////////////////////////////////////////////////// */


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsAdd
//  Purpose:    Adds elements of two vectors
//  Arguments:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrc                 Pointer to source vector for in-place operations
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vectors' length is less than 1
//    nmppsStsNoErr          No error
//  Note:
//    Add(X,Y)       :  Y[n] = Y[n] + X[n]
//    Add(X,Y,Z)     :  Z[n] = Y[n] + X[n]
*/
NMPPSAPI(nmppsStatus, nmppsAdd_8u_Sfs,    (const nmpps8u*   pSrc1, const nmpps8u*   pSrc2, nmpps8u*   pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsAdd_8u16u,     (const nmpps8u*   pSrc1, const nmpps8u*   pSrc2, nmpps16u*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsAdd_16s_Sfs,   (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsAdd_16u,       (const nmpps16u*  pSrc1, const nmpps16u*  pSrc2, nmpps16u*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsAdd_32s_Sfs,   (const nmpps32s*  pSrc1, const nmpps32s*  pSrc2, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsAdd_32u,       (const nmpps32u*  pSrc1, const nmpps32u*  pSrc2, nmpps32u*  pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsAddProductC
//  Purpose:    multiplies elements of of a vector by a constant and adds product to
//              the accumulator vector
//  Parameters:
//    pSrc                 pointer to the source vector
//    val                  constant value
//    pSrcDst              pointer to the source/destination (accumulator) vector
//    len                  length of the vectors
//  Return:
//    nmppsStsNullPtrErr     pointer to the vector is NULL
//    nmppsStsSizeErr        length of the vectors is less or equal zero
//    nmppsStsNoErr          otherwise
//
//  Notes:                 pSrcDst[n] = pSrcDst[n] + pSrc[n] * val, n=0,1,2,..len-1.
*/
NMPPSAPI(nmppsStatus, nmppsAddProductC_32f, (const nmpps32f* pSrc, const nmpps32f val, nmpps32f* pSrcDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsAddProduct
//  Purpose:    multiplies elements of two source vectors and adds product to
//              the accumulator vector
//  Parameters:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrcDst              Pointer to destination accumulator vector
//    len                  Number of elements in  vectors
//    scaleFactor          scale factor value
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vectors' length is less than 1
//    nmppsStsNoErr          No error
//  Notes:                 pSrcDst[n] = pSrcDst[n] + pSrc1[n] * pSrc2[n], n=0,1,2,..len-1.
*/
NMPPSAPI(nmppsStatus, nmppsAddProduct_16s_Sfs,    (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps16s*  pSrcDst, int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsAddProduct_16s32s_Sfs, (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps32s*  pSrcDst, int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsAddProduct_32s_Sfs,    (const nmpps32s*  pSrc1, const nmpps32s*  pSrc2, nmpps32s*  pSrcDst, int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsAddProduct_32f,        (const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, nmpps32f*  pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsAddProduct_32fc,       (const nmpps32fc* pSrc1, const nmpps32fc* pSrc2, nmpps32fc* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsAddProduct_64f,        (const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, nmpps64f*  pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsAddProduct_64fc,       (const nmpps64fc* pSrc1, const nmpps64fc* pSrc2, nmpps64fc* pSrcDst, int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       nmppsMulC
//  Purpose:     Multiplies each element of a vector by a constant value 
//  Arguments:
//    pSrc             Pointer to source vector
//    pSrcDst          Pointer to source and destination vector for in-place operation
//    pDst             Pointer to destination vector
//    val              The scalar value used to multiply each element of source vector
//    len              Number of elements in vector
//    scaleFactor      Scale factor
//  Return:
//    nmppsStsNullPtrErr At least one of the pointers is NULL
//    nmppsStsSizeErr    Vectors' length is less than 1
//    nmppsStsNoErr      No error
//  Note:
//    MulC(X,v,Y)    :  Y[n] = X[n] * v
*/
NMPPSAPI(nmppsStatus, nmppsMulC_16s_Sfs,     (const nmpps16s*  pSrc, nmpps16s  val, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMulC_32s_Sfs,     (const nmpps32s*  pSrc, nmpps32s  val, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMulC_32sc_Sfs,    (const nmpps32sc* pSrc, nmpps32sc val, nmpps32sc* pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMulC_32f,         (const nmpps32f*  pSrc, nmpps32f  val, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsMulC_32fc,        (const nmpps32fc* pSrc, nmpps32fc val, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsMulC_64f,         (const nmpps64f*  pSrc, nmpps64f  val, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsMulC_64fc,        (const nmpps64fc* pSrc, nmpps64fc val, nmpps64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsMul
//  Purpose:    Multiplies elements of two vectors
//  Arguments:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrc                 Pointer to source vector for in-place operations
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vectors' length is less than 1
//    nmppsStsNoErr          No error
//  Note:
//    Mul(X,Y)       :  Y[n] = Y[n] * X[n]
//    Mul(X,Y,Z)     :  Z[n] = Y[n] * X[n]
*/
NMPPSAPI(nmppsStatus, nmppsMul_8u_Sfs,    (const nmpps8u*   pSrc1, const nmpps8u*   pSrc2, nmpps8u*   pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMul_8u16u,     (const nmpps8u*   pSrc1, const nmpps8u*   pSrc2, nmpps16u*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsMul_16s,       (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps16s*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsMul_16s_Sfs,   (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMul_16s32s_Sfs,(const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMul_16u_Sfs,   (const nmpps16u*  pSrc1, const nmpps16u* pSrc2,  nmpps16u*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMul_32s_Sfs,   (const nmpps32s*  pSrc1, const nmpps32s*  pSrc2, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMul_32sc_Sfs,  (const nmpps32sc* pSrc1, const nmpps32sc* pSrc2, nmpps32sc* pDst,    int len, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       nmppsSubC
//  Purpose:     Subtracts constant value from each element of vector
//  Arguments:
//    pSrc             Pointer to source vector
//    pSrcDst          Pointer to source and destination vector for in-place operation
//    pDst             Pointer to destination vector
//    val              Scalar value used to decrement each element of the source vector
//    len              Number of elements in vector
//    scaleFactor      Scale factor
//  Return:
//    nmppsStsNullPtrErr At least one of the pointers is NULL
//    nmppsStsSizeErr    Vectors' length is less than 1
//    nmppsStsNoErr      No error
//  Note:
//    SubC(X,v,Y)    :  Y[n] = X[n] - v
*/
NMPPSAPI(nmppsStatus, nmppsSubC_8u_Sfs,    (const nmpps8u*   pSrc, nmpps8u   val, nmpps8u*   pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSubC_16s_Sfs,   (const nmpps16s*  pSrc, nmpps16s  val, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSubC_32s_Sfs,   (const nmpps32s*  pSrc, nmpps32s  val, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSubC_32f,       (const nmpps32f*  pSrc, nmpps32f  val, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSubC_32fc,      (const nmpps32fc* pSrc, nmpps32fc val, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSubC_64f,       (const nmpps64f*  pSrc, nmpps64f  val, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSubC_64fc,      (const nmpps64fc* pSrc, nmpps64fc val, nmpps64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       nmppsSubCRev
//  Purpose:     Subtracts each element of vector from constant value 
//  Arguments:
//    pSrc             Pointer to source vector
//    pSrcDst          Pointer to source and destination vector for in-place operation
//    pDst             Pointer to destination vector
//    val              Scalar value from which vector elements are subtracted
//    len              Number of elements in vector
//    scaleFactor      Scale factor
//  Return:
//    nmppsStsNullPtrErr At least one of the pointers is NULL
//    nmppsStsSizeErr    Vectors' length is less than 1
//    nmppsStsNoErr      No error
//  Note:
//    SubCRev(X,v,Y) :  Y[n] = v - X[n]
*/
NMPPSAPI(nmppsStatus, nmppsSubCRev_16s_Sfs,   (const nmpps16s*  pSrc, nmpps16s  val, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSubCRev_32s_Sfs,   (const nmpps32s*  pSrc, nmpps32s  val, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSubCRev_32sc_Sfs,  (const nmpps32sc* pSrc, nmpps32sc val, nmpps32sc* pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSubCRev_32f,       (const nmpps32f*  pSrc, nmpps32f  val, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSubCRev_32fc,      (const nmpps32fc* pSrc, nmpps32fc val, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSubCRev_64f,       (const nmpps64f*  pSrc, nmpps64f  val, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSubCRev_64fc,      (const nmpps64fc* pSrc, nmpps64fc val, nmpps64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSub
//  Purpose:    Subtracts elements of two vectors
//  Arguments:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrc                 Pointer to source vector for in-place operations
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vectors' length is less than 1
//    nmppsStsNoErr          No error
//  Note:
//    Sub(X,Y)       :  Y[n] = Y[n] - X[n]
//    Sub(X,Y,Z)     :  Z[n] = Y[n] - X[n]
*/
NMPPSAPI(nmppsStatus, nmppsSub_16s_Sfs,   (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSub_32s_Sfs,   (const nmpps32s*  pSrc1, const nmpps32s*  pSrc2, nmpps32s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSub_32sc_Sfs,  (const nmpps32sc* pSrc1, const nmpps32sc* pSrc2, nmpps32sc* pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSub_32f,       (const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSub_32fc,      (const nmpps32fc* pSrc1, const nmpps32fc* pSrc2, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSub_64f,       (const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSub_64fc,      (const nmpps64fc* pSrc1, const nmpps64fc* pSrc2, nmpps64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsDivC
//  Purpose:    Divides each element of a vector by a constant value
//  Arguments:
//    val               Scalar value used as a divisor
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    pSrcDst           Pointer to the source and destination vector for in-place operation
//    len               Number of elements in the vector
//    scaleFactor       Scale factor
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vector length is less than 1
//    nmppsStsDivByZeroErr   Indicates an error when val is equal to 0
//    nmppsStsNoErr          No error
//  Note:
//    DivC(v,X,Y)  :    Y[n] = X[n] / v
//    DivC(v,X)    :    X[n] = X[n] / v
*/
NMPPSAPI(nmppsStatus, nmppsDivC_8u_Sfs,   (const nmpps8u*   pSrc, nmpps8u   val, nmpps8u*   pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsDivC_16s_Sfs,  (const nmpps16s*  pSrc, nmpps16s  val, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsDivC_16sc_Sfs, (const nmpps16sc* pSrc, nmpps16sc val, nmpps16sc* pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsDivC_32f,      (const nmpps32f*  pSrc, nmpps32f  val, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsDivC_32fc,     (const nmpps32fc* pSrc, nmpps32fc val, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsDivC_64f,      (const nmpps64f*  pSrc, nmpps64f  val, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsDivC_64fc,     (const nmpps64fc* pSrc, nmpps64fc val, nmpps64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsDivCRev
//  Purpose:    Divides a constant value by each element of a vector
//  Arguments:
//    val               Constant value used as a dividend in the operation
//    pSrc              Pointer to the source vector whose elements are used as divisors
//    pDst              Pointer to the destination vector
//    pSrcDst           Pointer to the source and destination vector for in-place operation
//    len               Number of elements in the vector
//    scaleFactor       Scale factor
//  Return:
//    nmppsStsNullPtrErr  At least one of the pointers is NULL
//    nmppsStsSizeErr     Vector length is less than 1
//    nmppsStsDivByZero   Warning status if any element of vector is zero. IF the dividend is zero
//                      than result is NaN, if the dividend is not zero than result is Infinity 
//                      with correspondent sign. Execution is not aborted. 
//                      For the integer operation zero instead of NaN and the corresponding 
//                      bound values instead of Infinity
//    nmppsStsNoErr       No error
//  Note:
//    DivCRev(v,X,Y)  :    Y[n] = v / X[n]
//    DivCRev(v,X)    :    X[n] = v / X[n]
*/
NMPPSAPI(nmppsStatus, nmppsDivCRev_32f,   (const nmpps32f* pSrc, nmpps32f val, nmpps32f* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsDiv
//  Purpose:    Divides the elements of two vectors
//  Arguments:
//    pSrc1             Pointer to the divisor vector. 
//    pSrc2             Pointer to the dividend vector. 
//    pDst              Pointer to the destination vector
//    pSrc              Pointer to the divisor vector for in-place operations
//    pSrcDst           Pointer to the source and destination vector for in-place operation
//    len               Number of elements in the vector
//    scaleFactor       Scale factor
//  Return:
//    nmppsStsNullPtrErr  At least one of the pointers is NULL
//    nmppsStsSizeErr     Vector length is less than 1
//    nmppsStsDivByZero   Warning status if any element of vector is zero. IF the dividend is zero
//                      than result is NaN, if the dividend is not zero than result is Infinity 
//                      with correspondent sign. Execution is not aborted. 
//                      For the integer operation zero instead of NaN and the corresponding 
//                      bound values instead of Infinity
//    nmppsStsNoErr       No error
//  Note:
//    Div(X,Y)     :    Y[n] = Y[n] / X[n]
//    Div(X,Y,Z)   :    Z[n] = Y[n] / X[n]
*/
NMPPSAPI(nmppsStatus, nmppsDiv_32f,       (const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsDiv_32fc,      (const nmpps32fc* pSrc1, const nmpps32fc* pSrc2, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsDiv_64f,       (const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsDiv_64fc,      (const nmpps64fc* pSrc1, const nmpps64fc* pSrc2, nmpps64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsAbs
//  Purpose:    compute absolute value of each element of the source vector
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                length of the vector(s), number of items
//  Return:
//   nmppsStsNullPtrErr      pointer(s) to data vector is NULL
//   nmppsStsSizeErr         length of a vector is less or equal 0
//   nmppsStsNoErr           otherwise
*/
NMPPSAPI(nmppsStatus, nmppsAbs_32f,   (const nmpps32f* pSrc, nmpps32f* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsAbs_64f,   (const nmpps64f* pSrc, nmpps64f* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSqr
//  Purpose:    Computes square of each element of source vector
//  Parameters:
//    pSrcDst          Pointer to the source and destination vector for in-place operations
//    pSrc             Pointer to the source vector
//    pDst             Pointer to the destination vector
//    len              Number of elements in the vector
//   scaleFactor       Scale factor
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vectors' length is less than 1
//    nmppsStsNoErr          No error
*/
NMPPSAPI(nmppsStatus, nmppsSqr_8u_Sfs,    (const nmpps8u*   pSrc, nmpps8u*   pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSqr_16s_Sfs,   (const nmpps16s*  pSrc, nmpps16s*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSqr_16sc_Sfs,  (const nmpps16sc* pSrc, nmpps16sc* pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSqr_16u_Sfs,   (const nmpps16u*  pSrc, nmpps16u*  pDst,    int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSqr_32f,       (const nmpps32f*  pSrc, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSqr_32fc,      (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSqr_64f,       (const nmpps64f*  pSrc, nmpps64f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSqr_64fc,      (const nmpps64fc* pSrc, nmpps64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSqrt
//  Purpose:    compute square root value for every element of the source vector
//   pSrc                 pointer to the source vector
//   pDst                 pointer to the destination vector
//   pSrcDst              pointer to the source/destination vector
//   len                  length of the vector(s), number of items
//   scaleFactor          scale factor value
//  Return:
//   nmppsStsNullPtrErr        pointer to vector is NULL
//   nmppsStsSizeErr           length of the vector is less or equal zero
//   nmppsStsSqrtNegArg        negative value in real sequence
//   nmppsStsNoErr             otherwise
*/
nmppsStatus square_root32f(); //–í—ã–∑—ã–≤–∞–µ—Ç—Å—è —á–µ—Ä–µ–∑ –æ–±—Ä–∞–±–æ—Ç—á–∏–∫ vec_handler32
NMPPSAPI(nmppsStatus, vec_handler32,       (nmppsStatus* func, const nmpps32f*  pSrc, nmpps32f*  pDst,    int len))

#define nmppsSqrt_32f(arg...)   vec_handler32( (nmppsStatus*)square_root32f, arg)

//NMPPSAPI(nmppsStatus, nmppsSqrt_32f,       (const nmpps32f*  pSrc, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsSqrt_64f,       (const nmpps64f*  pSrc, nmpps64f*  pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsArctan
//
//  Purpose: compute arctangent value for all elements of the source vector
//
//  Return:
//   stsNoErr           Ok
//   stsNullPtrErr      Some of pointers to input or output data are NULL
//   stsBadSizeErr      The length of the arrays is less or equal zero
//
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                a length of the array
//
*/
nmppsStatus arctan32f(); //¬˚Á˚‚‡ÂÚÒˇ ˜ÂÂÁ Ó·‡·ÓÚ˜ËÍ vec_handler32
#define nmppsArctan_32f(arg...)   vec_handler32( (nmppsStatus*)arctan32f, arg)
//NMPPSAPI(nmppsStatus, nmppsArctan_32f,   (const nmpps32f* pSrc, nmpps32f* pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsArctan_64f,   (const nmpps64f* pSrc, nmpps64f* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:   nmppsNormalize
//  Purpose: Normalizes elements of a real or complex vector using offset and division operations
//  Parameters:
//    pSrcDst     - Pointer to the source and destination vector for the in-place operation
//    pSrc        - Pointer to the source vector
//    pDst        - Pointer to the destination vector
//    len         - Number of elements in the vector
//    vSub        - Subtrahend value
//    vDiv        - Denominator value
//    scaleFactor - Scale factor
//  Return:
//    nmppsStsNoErr          No error
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vector length is less than 1
//    nmppsStsDivByZeroErr   Indicates an error when vDivis equal to 0 or less than the
//                         minimum floating-point positive number
//  Note:
//      pDst[n] = (pSrc[n] - vSub)/vDiv
*/
NMPPSAPI(nmppsStatus, nmppsNormalize_32f,      (const nmpps32f*  pSrc, nmpps32f* pDst,     int len, nmpps32f  vSub, nmpps32f vDiv))
NMPPSAPI(nmppsStatus, nmppsNormalize_32fc,     (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len, nmpps32fc vSub, nmpps32f vDiv))
NMPPSAPI(nmppsStatus, nmppsNormalize_64f,      (const nmpps64f*  pSrc, nmpps64f* pDst,     int len, nmpps64f  vSub, nmpps64f vDiv))
NMPPSAPI(nmppsStatus, nmppsNormalize_64fc,     (const nmpps64fc* pSrc, nmpps64fc* pDst,    int len, nmpps64fc vSub, nmpps64f vDiv))

/* /////////////////////////////////////////////////////////////////////////////
//                   Convert functions
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSortAscend, nmppsSortDescend
//
//  Purpose:    Execute sorting of all elemens of the vector.
//              nmppsSortAscend  is sorted in increasing order.
//              nmppsSortDescend is sorted in decreasing order.
//  Arguments:
//    pSrcDst              pointer to the source/destination vector
//    len                  length of the vector
//  Return:
//    nmppsStsNullPtrErr     pointer to the data is NULL
//    nmppsStsSizeErr        length of the vector is less or equal zero
//    nmppsStsNoErr          otherwise
*/
NMPPSAPI(nmppsStatus, nmppsSortAscend_16s_I, (nmpps16s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsSortAscend_32s_I, (nmpps32s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsSortAscend_32f_I, (nmpps32f* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsSortAscend_64f_I, (nmpps64f* pSrcDst, int len))

NMPPSAPI(nmppsStatus, nmppsSortDescend_16s_I, (nmpps16s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsSortDescend_32s_I, (nmpps32s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsSortDescend_32f_I, (nmpps32f* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsSortDescend_64f_I, (nmpps64f* pSrcDst, int len))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsConvert
//  Purpose:    Converts vector data type
//  Parameters:
//    pSrc        Pointer to input vector
//    pDst        Pointer to output vector
//    len         Vectors' length in elements
//    rndMode     Round mode - ippRndZero, ippRndNear or ippRndFinancial
//    scaleFactor Scale factor (for some integer outputs)
//  Return:
//    nmppsStsNullPtrErr               One of pointers is NULL
//    nmppsStsSizeErr                  Vectors' length is less than 1
//    nmppsStsRoundModeNotSupportedErr Specified round mode is not supported
//    nmppsStsNoErr                    No error
//  Note:
//    all out-of-range result are saturated
*/
NMPPSAPI(nmppsStatus, nmppsConvert_32s32f,     (const nmpps32s* pSrc, nmpps32f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsConvert_32s32f_Sfs, (const nmpps32s* pSrc, nmpps32f* pDst, int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsConvert_32s64f,     (const nmpps32s* pSrc, nmpps64f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsConvert_32s64f_Sfs, (const nmpps32s* pSrc, nmpps64f* pDst, int len, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsConvert_64s32s_Sfs, (const nmpps64s* pSrc, nmpps32s* pDst, int len, nmppsRoundMode rndMode, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsConvert_32f64f,     (const nmpps32f* pSrc, nmpps64f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsConvert_64f32s_Sfs, (const nmpps64f* pSrc, nmpps32s* pDst, int len, nmppsRoundMode rndMode, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsConvert_64f32f,     (const nmpps64f* pSrc, nmpps32f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:       nmppsConj, nmppsConjFlip, nmppsConjCcs, nmppsConjPerm, nmppsConjPack
//  Purpose:     Complex conjugate input vector; 
//               Ccs, Perm and Pack versions - in corresponding packed format
//  Parameters:
//    pSrc               Pointer to input complex vector
//    pDst               Pointer to output complex vector
//    len                Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr      One of pointers is NULL
//    nmppsStsSizeErr         Vectors' length is less than 1
//    nmppsStsNoErr           Otherwise
//  Notes:
//    ConjFlip version conjugates and stores result in reverse order
*/
NMPPSAPI(nmppsStatus, nmppsConj_32fc,       (const nmpps32fc* pSrc, nmpps32fc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsConj_64fc,       (const nmpps64fc* pSrc, nmpps64fc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsMagnitude
//  Purpose:    compute magnitude of every complex element of the source
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                length of the vector(s), number of items
//   scaleFactor        scale factor value
//  Return:
//   nmppsStsNullPtrErr      pointer(s) to data vector is NULL
//   nmppsStsSizeErr         length of a vector is less or equal 0
//   nmppsStsNoErr           otherwise
//  Notes:
//         dst = sqrt( src.re^2 + src.im^2 )
*/
NMPPSAPI(nmppsStatus, nmppsMagnitude_32f,      (const nmpps32f*  pSrcRe, const nmpps32f* pSrcIm, nmpps32f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMagnitude_32fc,     (const nmpps32fc* pSrc,                         nmpps32f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMagnitude_64f,      (const nmpps64f*  pSrcRe, const nmpps64f* pSrcIm, nmpps64f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsMagnitude_64fc,     (const nmpps64fc* pSrc,                         nmpps64f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//    nmppsPhase
//  Purpose:
//    Compute the phase (in radians) of complex vector elements.
//  Parameters:
//    pSrcRe    - an input complex vector
//    pDst      - an output vector to store the phase components;
//    len       - a length of the arrays.
//    scaleFactor   - a scale factor of output results (only for integer data)
//  Return:
//    nmppsStsNoErr               Ok
//    nmppsStsNullPtrErr          Some of pointers to input or output data are NULL
//    nmppsStsBadSizeErr          The length of the arrays is less or equal zero
*/
NMPPSAPI(nmppsStatus, nmppsPhase_64fc,     (const nmpps64fc* pSrc, nmpps64f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsPhase_32fc,     (const nmpps32fc* pSrc, nmpps32f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//    nmppsPhase_64f
//    nmppsPhase_32f
//    nmppsPhase_16s_Sfs
//    nmppsPhase_16s32f
//  Purpose:
//    Compute the phase of complex data formed as two real vectors.
//  Parameters:
//    pSrcRe    - an input vector containing a real part of complex data
//    pSrcIm    - an input vector containing an imaginary part of complex data
//    pDst      - an output vector to store the phase components
//    len       - a length of the arrays.
//    scaleFactor   - a scale factor of output results (only for integer data)
//  Return:
//    nmppsStsNoErr               Ok
//    nmppsStsNullPtrErr          Some of pointers to input or output data are NULL
//    nmppsStsBadSizeErr          The length of the arrays is less or equal zero
*/
NMPPSAPI(nmppsStatus, nmppsPhase_64f,     (const nmpps64f* pSrcRe, const nmpps64f* pSrcIm, nmpps64f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsPhase_32f,     (const nmpps32f* pSrcRe, const nmpps32f* pSrcIm, nmpps32f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        nmppsPowerSpectr
//  Purpose:      Compute the power spectrum of complex vector
//  Parameters:
//    pSr       - pointer to the complex input vector.
//    pSrcIm    - pointer to the image part of input vector.
//    pDst      - pointer to the result.
//    len       - vector length.
//    scaleFactor   - scale factor for rezult (only for integer data).
//  Return:
//   nmppsStsNullPtrErr  indicates that one or more pointers to the data is NULL.
//   nmppsStsSizeErr     indicates that vector length is less or equal zero.
//   nmppsStsNoErr       otherwise.
*/
NMPPSAPI(nmppsStatus, nmppsPowerSpectr_32f,    (const nmpps32f* pSrcRe, const nmpps32f* pSrcIm, nmpps32f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsPowerSpectr_64f,    (const nmpps64f* pSrcRe, const nmpps64f* pSrcIm, nmpps64f* pDst, int len))

NMPPSAPI(nmppsStatus, nmppsPowerSpectr_32fc,    (const nmpps32fc* pSrc, nmpps32f* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsPowerSpectr_64fc,    (const nmpps64fc* pSrc, nmpps64f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsReal
//  Purpose:    Extract real part of input complex vector
//  Parameters:
//    pSrc       Pointer to input complex vector
//    pDstRe     Pointer to output real vector
//    len        Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr       One of pointers is NULL
//    nmppsStsSizeErr          Vectors' length is less than 1
//    nmppsStsNoErr            Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsReal_64fc, (const nmpps64fc* pSrc, nmpps64f* pDstRe, int len))
NMPPSAPI(nmppsStatus, nmppsReal_32fc, (const nmpps32fc* pSrc, nmpps32f* pDstRe, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsImag
//  Purpose:    Extract imaginary part of input complex vector
//  Parameters:
//    pSrc       Pointer to input complex vector
//    pDstRe     Pointer to output imaginary vector
//    len        Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr       One of pointers is NULL
//    nmppsStsSizeErr          Vectors' length is less than 1
//    nmppsStsNoErr            Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsImag_64fc, (const nmpps64fc* pSrc, nmpps64f* pDstIm, int len))
NMPPSAPI(nmppsStatus, nmppsImag_32fc, (const nmpps32fc* pSrc, nmpps32f* pDstIm, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsRealToCplx
//  Purpose:    Compose complex vector from real and imaginary parts
//  Parameters:
//    pSrcRe     Pointer to input real vector, may be NULL
//    pSrcIm     Pointer to input imaginary vector, may be NULL
//    pDst       Pointer to output complex vector
//    len        Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr        Pointer to output vector is NULL, or both pointers
//                            to real and imaginary parts are NULL
//    nmppsStsSizeErr           Vectors' length is less than 1
//    nmppsStsNoErr             Otherwise
//
//  Notes:      One of two input pointers may be NULL. In this case
//              corresponding values of output complex elements are 0
*/
NMPPSAPI(nmppsStatus, nmppsRealToCplx_64f, (const nmpps64f* pSrcRe, const nmpps64f* pSrcIm, nmpps64fc* pDst, int len))
NMPPSAPI(nmppsStatus, nmppsRealToCplx_32f, (const nmpps32f* pSrcRe, const nmpps32f* pSrcIm, nmpps32fc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsCplxToReal
//  Purpose:    Extract real and imaginary parts of input complex vector
//  Parameters:
//    pSrc       Pointer to input complex vector
//    pDstRe     Pointer to output real vector
//    pDstIm     Pointer to output imaginary vector
//    len        Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr        One of pointers is NULL
//    nmppsStsSizeErr           Vectors' length is less than 1
//    nmppsStsNoErr             Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsCplxToReal_64fc, (const nmpps64fc* pSrc, nmpps64f* pDstRe, nmpps64f* pDstIm, int len))
NMPPSAPI(nmppsStatus, nmppsCplxToReal_32fc, (const nmpps32fc* pSrc, nmpps32f* pDstRe, nmpps32f* pDstIm, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsThreshold
//  Purpose:    Performs threshold operation on vector's elements by limiting 
//              element values by specified value. 
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst.
//               This parameter must always be real. For complex versions, 
//               it must be positive and represent magnitude
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    relOp      Values of this argument specify which relational operator 
//               to use and whether level is an upper or lower bound for input.
//               relOp must have one of the following values: 
//               - ippCmpLess specifies "less than" operator and level is lower bound
                 - ippCmpGreater specifies "greater than" operator and level is upper bound. 
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThreshNegLevelErr   Negative level value for complex operation
//    nmppsStsBadArgErr           relOp has invalid value
//    nmppsStsNoErr               No error
//  Notes:
//  real data
//    cmpLess    : pDst[n] = pSrc[n] < level ? level : pSrc[n];
//    cmpGreater : pDst[n] = pSrc[n] > level ? level : pSrc[n];
//  complex data
//    cmpLess    : pDst[n] = abs(pSrc[n]) < level ? pSrc[n]*k : pSrc[n];
//    cmpGreater : pDst[n] = abs(pSrc[n]) > level ? pSrc[n]*k : pSrc[n];
//    where k = level / abs(pSrc[n]);
*/

NMPPSAPI(nmppsStatus, nmppsThreshold_16s_I,  (      nmpps16s*  pSrcDst,             int len, nmpps16s level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_16sc_I, (      nmpps16sc* pSrcDst,             int len, nmpps16s level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_32f_I,  (      nmpps32f*  pSrcDst,             int len, nmpps32f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_32fc_I, (      nmpps32fc* pSrcDst,             int len, nmpps32f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_64f_I,  (      nmpps64f*  pSrcDst,             int len, nmpps64f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_64fc_I, (      nmpps64fc* pSrcDst,             int len, nmpps64f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_16s,    (const nmpps16s*  pSrc, nmpps16s*  pDst, int len, nmpps16s level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_16sc,   (const nmpps16sc* pSrc, nmpps16sc* pDst, int len, nmpps16s level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst, int len, nmpps32f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len, nmpps64f level, nmppsCmpOp relOp))
NMPPSAPI(nmppsStatus, nmppsThreshold_64fc,   (const nmpps64fc* pSrc, nmpps64fc* pDst, int len, nmpps64f level, nmppsCmpOp relOp))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsThreshold_LT, nmppsThreshold_GT
//  Purpose:    Performs threshold operation on elements of vector by limiting
//              element values by specified value
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst.
//               This parameter must always be real. For complex versions, 
//               it must be positive and represent magnitude
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThreshNegLevelErr   Negative level value for complex operation
//    nmppsStsNoErr               No error
*/
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_16s_I,  (      nmpps16s*  pSrcDst,             int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_16sc_I, (      nmpps16sc* pSrcDst,             int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_32s_I,  (      nmpps32s*  pSrcDst,             int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_32f_I,  (      nmpps32f*  pSrcDst,             int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_32fc_I, (      nmpps32fc* pSrcDst,             int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_64f_I,  (      nmpps64f*  pSrcDst,             int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_64fc_I, (      nmpps64fc* pSrcDst,             int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_16s,    (const nmpps16s*  pSrc, nmpps16s*  pDst, int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_16sc,   (const nmpps16sc* pSrc, nmpps16sc* pDst, int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_32s,    (const nmpps32s*  pSrc, nmpps32s*  pDst, int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LT_64fc,   (const nmpps64fc* pSrc, nmpps64fc* pDst, int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_16s_I,  (      nmpps16s*  pSrcDst,             int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_16sc_I, (      nmpps16sc* pSrcDst,             int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_32s_I,  (      nmpps32s*  pSrcDst,             int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_32f_I,  (      nmpps32f*  pSrcDst,             int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_32fc_I, (      nmpps32fc* pSrcDst,             int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_64f_I,  (      nmpps64f*  pSrcDst,             int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_64fc_I, (      nmpps64fc* pSrcDst,             int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_16s,    (const nmpps16s*  pSrc, nmpps16s*  pDst, int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_16sc,   (const nmpps16sc* pSrc, nmpps16sc* pDst, int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_32s,    (const nmpps32s*  pSrc, nmpps32s*  pDst, int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GT_64fc,   (const nmpps64fc* pSrc, nmpps64fc* pDst, int len, nmpps64f level))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsThreshold_LTAbs
//  Purpose:    Performs threshold operation on absolute values of elements of vector
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst.
//               This parameter must be positive
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThreshNegLevelErr   Negative level value
//    nmppsStsNoErr               No error
*/
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_16s,   (const nmpps16s* pSrc, nmpps16s *pDst, int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_32s,   (const nmpps32s* pSrc, nmpps32s *pDst, int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_32f,   (const nmpps32f* pSrc, nmpps32f *pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_64f,   (const nmpps64f* pSrc, nmpps64f *pDst, int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_16s_I, (      nmpps16s *pSrcDst,            int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_32s_I, (      nmpps32s *pSrcDst,            int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_32f_I, (      nmpps32f *pSrcDst,            int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbs_64f_I, (      nmpps64f *pSrcDst,            int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_16s,   (const nmpps16s* pSrc, nmpps16s *pDst, int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_32s,   (const nmpps32s* pSrc, nmpps32s *pDst, int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_32f,   (const nmpps32f* pSrc, nmpps32f *pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_64f,   (const nmpps64f* pSrc, nmpps64f *pDst, int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_16s_I, (      nmpps16s *pSrcDst,            int len, nmpps16s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_32s_I, (      nmpps32s *pSrcDst,            int len, nmpps32s level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_32f_I, (      nmpps32f *pSrcDst,            int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTAbs_64f_I, (      nmpps64f *pSrcDst,            int len, nmpps64f level))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsThreshold_LTAbsVal
//  Purpose:    Performs threshold operation on absolute values of elements
//              of vector by limiting element values by specified level and 
//              substituting with specified value:
//              if( ABS(x[i]) < level ) y[i] = value;
//              else y[i] = x[i];
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst. This argument
//               must always be positive
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    value      Value to be assigned to vector elements which are "less than" 
//               by absolute value than level
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThreshNegLevelErr   Negative level value
//    nmppsStsNoErr               No error
*/
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_16s,   (const nmpps16s* pSrc, nmpps16s *pDst, int len, nmpps16s level, nmpps16s value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_32s,   (const nmpps32s* pSrc, nmpps32s *pDst, int len, nmpps32s level, nmpps32s value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_32f,   (const nmpps32f* pSrc, nmpps32f *pDst, int len, nmpps32f level, nmpps32f value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_64f,   (const nmpps64f* pSrc, nmpps64f *pDst, int len, nmpps64f level, nmpps64f value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_16s_I, (      nmpps16s *pSrcDst,            int len, nmpps16s level, nmpps16s value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_32s_I, (      nmpps32s *pSrcDst,            int len, nmpps32s level, nmpps32s value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_32f_I, (      nmpps32f *pSrcDst,            int len, nmpps32f level, nmpps32f value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTAbsVal_64f_I, (      nmpps64f *pSrcDst,            int len, nmpps64f level, nmpps64f value))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsThreshold_LTVal, nmppsThreshold_GTVal
//  Purpose:    Performs threshold operation on elements of vector by limiting
//              element values by specified level and substituting with 
//              specified value
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst. This argument
//               must always be real. For complex versions, it must be positive and
//               represent magnitude
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    value      Value to be assigned to vector elements which are "less than" or
//               "greater than" level.
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThreshNegLevelErr   Negative level value for complex operation
//    nmppsStsNoErr               No error
*/
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_16s_I,  (      nmpps16s*  pSrcDst,             int len, nmpps16s level, nmpps16s  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_16sc_I, (      nmpps16sc* pSrcDst,             int len, nmpps16s level, nmpps16sc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_32f_I,  (      nmpps32f*  pSrcDst,             int len, nmpps32f level, nmpps32f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_32fc_I, (      nmpps32fc* pSrcDst,             int len, nmpps32f level, nmpps32fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_64f_I,  (      nmpps64f*  pSrcDst,             int len, nmpps64f level, nmpps64f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_64fc_I, (      nmpps64fc* pSrcDst,             int len, nmpps64f level, nmpps64fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_16s,    (const nmpps16s*  pSrc, nmpps16s*  pDst, int len, nmpps16s level, nmpps16s  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_16sc,   (const nmpps16sc* pSrc, nmpps16sc* pDst, int len, nmpps16s level, nmpps16sc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f level, nmpps32f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst, int len, nmpps32f level, nmpps32fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len, nmpps64f level, nmpps64f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTVal_64fc,   (const nmpps64fc* pSrc, nmpps64fc* pDst, int len, nmpps64f level, nmpps64fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_16s_I,  (      nmpps16s*  pSrcDst,             int len, nmpps16s level, nmpps16s  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_16sc_I, (      nmpps16sc* pSrcDst,             int len, nmpps16s level, nmpps16sc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_32f_I,  (      nmpps32f*  pSrcDst,             int len, nmpps32f level, nmpps32f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_32fc_I, (      nmpps32fc* pSrcDst,             int len, nmpps32f level, nmpps32fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_64f_I,  (      nmpps64f*  pSrcDst,             int len, nmpps64f level, nmpps64f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_64fc_I, (      nmpps64fc* pSrcDst,             int len, nmpps64f level, nmpps64fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_16s,    (const nmpps16s*  pSrc, nmpps16s*  pDst, int len, nmpps16s level, nmpps16s  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_16sc,   (const nmpps16sc* pSrc, nmpps16sc* pDst, int len, nmpps16s level, nmpps16sc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f level, nmpps32f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst, int len, nmpps32f level, nmpps32fc value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len, nmpps64f level, nmpps64f  value))
NMPPSAPI(nmppsStatus, nmppsThreshold_GTVal_64fc,   (const nmpps64fc* pSrc, nmpps64fc* pDst, int len, nmpps64f level, nmpps64fc value))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsThreshold_LTValGTVal
//  Purpose:    Performs threshold operation on elements of vector by limiting
//              element values by specified level and substituting with 
//              specified values for LT and GT cases respectively
//  Parameters:
//    levelLT    Value used to limit each element of pSrc or pSrcDst for "less than" 
//    levelGT    Value used to limit each element of pSrc or pSrcDst for "greater than" 
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    valueLT    Value to be assigned to vector elements which are "less than" levelLT
//    valueGT    Value to be assigned to vector elements which are "greater than" levelGT
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThresholdErr        levelGT < levelLT
//    nmppsStsNoErr               No error
*/
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_16s_I, (      nmpps16s* pSrcDst,            int len, nmpps16s levelLT, nmpps16s valueLT, nmpps16s levelGT, nmpps16s valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_16s,   (const nmpps16s* pSrc, nmpps16s* pDst, int len, nmpps16s levelLT, nmpps16s valueLT, nmpps16s levelGT, nmpps16s valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_32s_I, (      nmpps32s* pSrcDst,            int len, nmpps32s levelLT, nmpps32s valueLT, nmpps32s levelGT, nmpps32s valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_32s,   (const nmpps32s* pSrc, nmpps32s* pDst, int len, nmpps32s levelLT, nmpps32s valueLT, nmpps32s levelGT, nmpps32s valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_32f_I, (      nmpps32f* pSrcDst,            int len, nmpps32f levelLT, nmpps32f valueLT, nmpps32f levelGT, nmpps32f valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_32f,   (const nmpps32f* pSrc, nmpps32f* pDst, int len, nmpps32f levelLT, nmpps32f valueLT, nmpps32f levelGT, nmpps32f valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_64f_I, (      nmpps64f* pSrcDst,            int len, nmpps64f levelLT, nmpps64f valueLT, nmpps64f levelGT, nmpps64f valueGT))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTValGTVal_64f,   (const nmpps64f* pSrc, nmpps64f* pDst, int len, nmpps64f levelLT, nmpps64f valueLT, nmpps64f levelGT, nmpps64f valueGT))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsThresholdLTInv
//  Purpose:    Computes inverse of vector elements after limiting
//              their magnitudes by given lower bound
//    level      Value used to limit each element of pSrc or pSrcDst
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//  Return:
//    nmppsStsNullPtrErr          One of pointers is NULL
//    nmppsStsSizeErr             Vectors' length is less than 1
//    nmppsStsThreshNegLevelErr   Negative level value
//    nmppsStsInvZero             level and source element values are zero
//    nmppsStsNoErr               No error
*/
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_32f_I,  (      nmpps32f*  pSrcDst,             int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_32fc_I, (      nmpps32fc* pSrcDst,             int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_64f_I,  (      nmpps64f*  pSrcDst,             int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_64fc_I, (      nmpps64fc* pSrcDst,             int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst, int len, nmpps32f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len, nmpps64f level))
NMPPSAPI(nmppsStatus, nmppsThreshold_LTInv_64fc,   (const nmpps64fc* pSrc, nmpps64fc* pDst, int len, nmpps64f level))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsCartToPolar
//  Purpose:    Converts elements of complex vector to polar coordinate form
//  Parameters:
//    pSrc             Pointer to source vector
//    pSrcRe           Pointer to source vector which stores real components of
//                     Cartesian X,Y pairs
//    pSrcIm           Pointer to source vector which stores imaginary components
//                     of Cartesian X,Y pairs
//    pDstMagn         Pointer to vector which stores magnitude (radius)
//                     component of elements of vector pSrc
//    pDstPhase        Pointer to vector which stores phase (angle) component of
//                     elements of vector pSrc in radians. Phase values are in
//                     range (-Pi, Pi]
//    len              Number of elements in vector
//    magnScaleFactor  Integer scale factor for magnitude component
//    phaseScaleFactor Integer scale factor for phase component
//  Return:
//   nmppsStsNoErr           Indicates no error
//   nmppsStsNullPtrErr      At least one of specified pointers is NULL
//   nmppsStsSizeErr         Vectors' length is less than 1
*/
NMPPSAPI(nmppsStatus, nmppsCartToPolar_32f,  (const nmpps32f* pSrcRe, const nmpps32f* pSrcIm, nmpps32f* pDstMagn, nmpps32f* pDstPhase, int len))
NMPPSAPI(nmppsStatus, nmppsCartToPolar_64f,  (const nmpps64f* pSrcRe, const nmpps64f* pSrcIm, nmpps64f* pDstMagn, nmpps64f* pDstPhase, int len))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsPolarToCart
//  Purpose:    Converts polar form magnitude/phase pairs stored
//              in input vectors to Cartesian coordinate form
//  Parameters:
//    pSrcMagn  Pointer to source vector which stores magnitude (radius)
//              components of elements in polar coordinate form
//    pSrcPhase Pointer to vector which stores phase (angle) components of
//              elements in polar coordinate form in radians
//    pDst      Pointer to  resulting vector which stores complex pairs in
//              Cartesian coordinates (X + iY)
//    pDstRe    Pointer to resulting vector which stores real components of
//              Cartesian X,Y pairs
//    pDstIm    Pointer to resulting vector which stores imaginary
//              components of Cartesian X,Y pairs
//    len       Number of elements in vectors
//  Return:
//   nmppsStsNoErr           Indicates no error
//   nmppsStsNullPtrErr      At least one of specified pointers is NULL
//   nmppsStsSizeErr         Vectors' length is less than 1
*/

NMPPSAPI(nmppsStatus, nmppsPolarToCart_32f,  (const nmpps32f* pSrcMagn, const nmpps32f* pSrcPhase, nmpps32f* pDstRe, nmpps32f* pDstIm, int len))
NMPPSAPI(nmppsStatus, nmppsPolarToCart_64f,  (const nmpps64f* pSrcMagn, const nmpps64f* pSrcPhase, nmpps64f* pDstRe, nmpps64f* pDstIm, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsFlip
//  Purpose:    dst[i] = src[len-i-1], i=0..len-1
//  Parameters:
//    pSrc      Pointer to input vector
//    pDst      Pointer to the output vector
//    pSrcDst   Pointer to source and destination vector for in-place operation
//    len       Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr        At least one pointer is NULL
//    nmppsStsSizeErr           Vectors' length is less than 1
//    nmppsStsNoErr             Otherwise
*/
NMPPSAPI(nmppsStatus, nmppsFlip_32f,    (const nmpps32f*  pSrc, nmpps32f*  pDst, int len))
NMPPSAPI(nmppsStatus, nmppsFlip_64f,    (const nmpps64f*  pSrc, nmpps64f*  pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//                  Windowing functions
//  Note: to create the window coefficients you have to make two calls
//        Set(1,x,n) and Win(x,n)
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:            nmppsWinBartlett
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//  Return:
//   nmppsStsNullPtrErr    pointer to the vector is NULL
//   nmppsStsSizeErr       length of the vector is less 3
//   nmppsStsNoErr         otherwise
*/
NMPPSAPI(nmppsStatus, nmppsWinBartlett_16s,   (const nmpps16s*  pSrc, nmpps16s* pDst,     int len))
NMPPSAPI(nmppsStatus, nmppsWinBartlett_32f,   (const nmpps32f*  pSrc, nmpps32f* pDst,     int len))
NMPPSAPI(nmppsStatus, nmppsWinBartlett_32fc,  (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            nmppsWinHann
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//  Return:
//   nmppsStsNullPtrErr    pointer to the vector is NULL
//   nmppsStsSizeErr       length of the vector is less 3
//   nmppsStsNoErr         otherwise
//  Functionality:    0.5*(1-cos(2*pi*n/(N-1)))
*/
NMPPSAPI(nmppsStatus, nmppsWinHann_16s,   (const nmpps16s* pSrc,  nmpps16s* pDst,     int len))
NMPPSAPI(nmppsStatus, nmppsWinHann_32f,   (const nmpps32f* pSrc,  nmpps32f* pDst,     int len))
NMPPSAPI(nmppsStatus, nmppsWinHann_32fc,  (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            nmppsWinHamming
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//  Return:
//   nmppsStsNullPtrErr    pointer to the vector is NULL
//   nmppsStsSizeErr       length of the vector is less 3
//   nmppsStsNoErr         otherwise
*/
NMPPSAPI(nmppsStatus, nmppsWinHamming_16s,   (const nmpps16s* pSrc,  nmpps16s*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsWinHamming_32f,   (const nmpps32f* pSrc,  nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsWinHamming_32fc,  (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            nmppsWinBlackman
//  Purpose:          multiply vector by Blackman windowing function
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//   alpha            adjustable parameter associated with the
//                    Blackman windowing equation
//   alphaQ15         scaled (scale factor 15) version of the alpha
//   scaleFactor      scale factor of the output signal
//  Return:
//   nmppsStsNullPtrErr    pointer to the vector is NULL
//   nmppsStsSizeErr       length of the vector is less 3, for Opt it's 4
//   nmppsStsNoErr         otherwise
//  Notes:
//     parameter alpha value
//         WinBlackmaStd   : -0.16
//         WinBlackmaOpt   : -0.5 / (1+cos(2*pi/(len-1)))
*/
NMPPSAPI(nmppsStatus, nmppsWinBlackman_16s,    (const nmpps16s*  pSrc, nmpps16s*  pDst,    int len, nmpps32f alpha))
NMPPSAPI(nmppsStatus, nmppsWinBlackman_32f,    (const nmpps32f* pSrc,  nmpps32f*  pDst,    int len, nmpps32f alpha))
NMPPSAPI(nmppsStatus, nmppsWinBlackman_32fc,   (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len, nmpps32f alpha))

NMPPSAPI(nmppsStatus, nmppsWinBlackmanStd_32f,   (const nmpps32f*  pSrc, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsWinBlackmanStd_32fc,  (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len))

NMPPSAPI(nmppsStatus, nmppsWinBlackmanOpt_32f,   (const nmpps32f*  pSrc, nmpps32f*  pDst,    int len))
NMPPSAPI(nmppsStatus, nmppsWinBlackmanOpt_32fc,  (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            nmppsWinKaiser
//  Purpose:          multiply vector by Kaiser windowing function
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//   alpha            adjustable parameter associated with the
//                    Kaiser windowing equation
//   alphaQ15         scaled (scale factor 15) version of the alpha
//  Return:
//   nmppsStsNullPtrErr    pointer to the vector is NULL
//   nmppsStsSizeErr       length of the vector is less 1
//   nmppsStsHugeWinErr    window in function is huge
//   nmppsStsNoErr         otherwise
*/
NMPPSAPI(nmppsStatus, nmppsWinKaiser_16s,   (const nmpps16s*  pSrc, nmpps16s*  pDst,    int len, nmpps32f alpha))
NMPPSAPI(nmppsStatus, nmppsWinKaiser_32f,   (const nmpps32f*  pSrc, nmpps32f*  pDst,    int len, nmpps32f alpha))
NMPPSAPI(nmppsStatus, nmppsWinKaiser_32fc,  (const nmpps32fc* pSrc, nmpps32fc* pDst,    int len, nmpps32f alpha))

/* /////////////////////////////////////////////////////////////////////////////
//                  Statistical functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSum
//  Purpose:    sum all elements of the source vector
//  Parameters:
//   pSrc                pointer to the source vector
//   pSum                pointer to the result
//   len                 length of the vector
//   scaleFactor         scale factor value
//  Return:
//   nmppsStsNullPtrErr       pointer to the vector or result is NULL
//   nmppsStsSizeErr          length of the vector is less or equal 0
//   nmppsStsNoErr            otherwise
*/
NMPPSAPI(nmppsStatus, nmppsSum_16s_Sfs,     (const nmpps16s*  pSrc, int len, nmpps16s*  pSum, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsSum_32s_Sfs,     (const nmpps32s*  pSrc, int len, nmpps32s*  pSum, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMin, nmppsMax, nmppsMinMax
// Purpose:    Find minimum/maximum value among all elements of the source vector
// Parameters:
//    pSrc     - Pointer to the source vector.
//    len      - Length of the vector.
//    pMax     - Pointer to the result.
//    pMin     - Pointer to the result.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/
NMPPSAPI(nmppsStatus, nmppsMin_32f, (const nmpps32f* pSrc, int len, nmpps32f* pMin))
NMPPSAPI(nmppsStatus, nmppsMin_64f, (const nmpps64f* pSrc, int len, nmpps64f* pMin))

NMPPSAPI(nmppsStatus, nmppsMax_32f, (const nmpps32f* pSrc, int len, nmpps32f* pMax))
NMPPSAPI(nmppsStatus, nmppsMax_64f, (const nmpps64f* pSrc, int len, nmpps64f* pMax))

NMPPSAPI(nmppsStatus, nmppsMinMax_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMin, nmpps16s* pMax))
NMPPSAPI(nmppsStatus, nmppsMinMax_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMin, nmpps32s* pMax))
NMPPSAPI(nmppsStatus, nmppsMinMax_32f, (const nmpps32f* pSrc, int len, nmpps32f* pMin, nmpps32f* pMax))
NMPPSAPI(nmppsStatus, nmppsMinMax_64f, (const nmpps64f* pSrc, int len, nmpps64f* pMin, nmpps64f* pMax))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinAbs, nmppsMaxAbs
// Purpose:    Returns the minimum/maximum absolute value of a vector.
// Parameters:
//    pSrc     - Pointer to the source vector.
//    len      - Length of the vector.
//    pMinAbs  - Pointer to the result.
//    pMaxAbs  - Pointer to the result.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/
NMPPSAPI(nmppsStatus, nmppsMinAbs_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMinAbs))
NMPPSAPI(nmppsStatus, nmppsMinAbs_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMinAbs))

NMPPSAPI(nmppsStatus, nmppsMaxAbs_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMaxAbs))
NMPPSAPI(nmppsStatus, nmppsMaxAbs_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMaxAbs))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinIndx, nmppsMaxIndx, nmppsMinMaxIndx
// Purpose:    Find element with min/max value and return the value and the index.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMin     - Pointer to min value found.
//    pMax     - Pointer to max value found.
//    pIndx    - Pointer to index of the first min/max value.
//    pMinIndx - Pointer to index of the first minimum value.
//    pMaxIndx - Pointer to index of the first maximum value.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/
NMPPSAPI(nmppsStatus, nmppsMinIndx_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMin, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMinIndx_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMin, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMinIndx_32f, (const nmpps32f* pSrc, int len, nmpps32f* pMin, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMinIndx_64f, (const nmpps64f* pSrc, int len, nmpps64f* pMin, int* pIndx))

NMPPSAPI(nmppsStatus, nmppsMaxIndx_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMax, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMaxIndx_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMax, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMaxIndx_32f, (const nmpps32f* pSrc, int len, nmpps32f* pMax, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMaxIndx_64f, (const nmpps64f* pSrc, int len, nmpps64f* pMax, int* pIndx))

NMPPSAPI(nmppsStatus, nmppsMinMaxIndx_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMin, int* pMinIndx, nmpps16s* pMax, int* pMaxIndx))
NMPPSAPI(nmppsStatus, nmppsMinMaxIndx_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMin, int* pMinIndx, nmpps32s* pMax, int* pMaxIndx))
NMPPSAPI(nmppsStatus, nmppsMinMaxIndx_32f, (const nmpps32f* pSrc, int len, nmpps32f* pMin, int* pMinIndx, nmpps32f* pMax, int* pMaxIndx))
NMPPSAPI(nmppsStatus, nmppsMinMaxIndx_64f, (const nmpps64f* pSrc, int len, nmpps64f* pMin, int* pMinIndx, nmpps64f* pMax, int* pMaxIndx))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinAbsIndx, nmppsMaxAbsIndx
// Purpose:    Returns the min/max absolute value of a vector and the index of the corresponding element.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMinAbs  - Pointer to the min absolute value found.
//    pMaxAbs  - Pointer to the max absolute value found.
//    pMinIndx - Pointer to index of the first minimum absolute value.
//    pMaxIndx - Pointer to index of the first maximum absolute value.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/
NMPPSAPI(nmppsStatus, nmppsMinAbsIndx_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMinAbs, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMinAbsIndx_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMinAbs, int* pIndx))

NMPPSAPI(nmppsStatus, nmppsMaxAbsIndx_16s, (const nmpps16s* pSrc, int len, nmpps16s* pMaxAbs, int* pIndx))
NMPPSAPI(nmppsStatus, nmppsMaxAbsIndx_32s, (const nmpps32s* pSrc, int len, nmpps32s* pMaxAbs, int* pIndx))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsMean
//  Purpose:    compute average value of all elements of the source vector
//  Parameters:
//   pSrc                pointer to the source vector
//   pMean               pointer to the result
//   len                 length of the source vector
//   scaleFactor         scale factor value
//  Return:
//   nmppsStsNullPtrErr       pointer(s) to the vector or the result is NULL
//   nmppsStsSizeErr          length of the vector is less or equal 0
//   nmppsStsNoErr            otherwise
*/
NMPPSAPI(nmppsStatus, nmppsMean_16s_Sfs, (const nmpps16s*  pSrc, int len, nmpps16s*  pMean, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsMean_32f,     (const nmpps32f*  pSrc, int len, nmpps32f*  pMean, nmppsHintAlgorithm hint))
NMPPSAPI(nmppsStatus, nmppsMean_32fc,    (const nmpps32fc* pSrc, int len, nmpps32fc* pMean, nmppsHintAlgorithm hint))
NMPPSAPI(nmppsStatus, nmppsMean_64f,     (const nmpps64f*  pSrc, int len, nmpps64f*  pMean))
NMPPSAPI(nmppsStatus, nmppsMean_64fc,    (const nmpps64fc* pSrc, int len, nmpps64fc* pMean))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsStdDev
//  Purpose:    compute standard deviation value of all elements of the vector
//  Parameters:
//   pSrc               pointer to the vector
//   len                length of the vector
//   pStdDev            pointer to the result
//   scaleFactor        scale factor value
//  Return:
//   nmppsStsNoErr           Ok
//   nmppsStsNullPtrErr      pointer to the vector or the result is NULL
//   nmppsStsSizeErr         length of the vector is less than 2
//  Functionality:
//         std = sqrt( sum( (x[n] - mean(x))^2, n=0..len-1 ) / (len-1) )
*/
NMPPSAPI(nmppsStatus, nmppsStdDev_16s32s_Sfs,(const nmpps16s* pSrc, int len, nmpps32s* pStdDev, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsStdDev_32f,       (const nmpps32f* pSrc, int len, nmpps32f* pStdDev, nmppsHintAlgorithm hint))
NMPPSAPI(nmppsStatus, nmppsStdDev_64f,       (const nmpps64f* pSrc, int len, nmpps64f* pStdDev))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:            nmppsNorm
//  Purpose:         calculate norm of vector
//     Inf   - calculate C-norm of vector:  n = MAX |src1|
//     L1    - calculate L1-norm of vector: n = SUM |src1|
//     L2    - calculate L2-norm of vector: n = SQRT(SUM |src1|^2)
//     L2Sqr - calculate L2-norm of vector: n = SUM |src1|^2
//  Parameters:
//    pSrc           source data pointer
//    len            length of vector
//    pNorm          pointer to result
//    scaleFactor    scale factor value
//  Returns:
//    nmppsStsNoErr       Ok
//    nmppsStsNullPtrErr  Some of pointers to input or output data are NULL
//    nmppsStsSizeErr     The length of vector is less or equal zero
//  Notes:
*/
NMPPSAPI(nmppsStatus, nmppsNorm_Inf_16s32s_Sfs,  (const nmpps16s*  pSrc, int len, nmpps32s* pNorm, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsNorm_Inf_16s32f,      (const nmpps16s*  pSrc, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNorm_Inf_32f,         (const nmpps32f*  pSrc, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNorm_Inf_64f,         (const nmpps64f*  pSrc, int len, nmpps64f* pNorm))

NMPPSAPI(nmppsStatus, nmppsNorm_L1_16s32s_Sfs,   (const nmpps16s*  pSrc, int len, nmpps32s* pNorm, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsNorm_L1_16s32f,       (const nmpps16s*  pSrc, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNorm_L1_32f,          (const nmpps32f*  pSrc, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNorm_L1_64f,          (const nmpps64f*  pSrc, int len, nmpps64f* pNorm))

NMPPSAPI(nmppsStatus, nmppsNorm_L2_16s32s_Sfs,   (const nmpps16s*  pSrc, int len, nmpps32s* pNorm, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsNorm_L2_16s32f,       (const nmpps16s*  pSrc, int len, nmpps32f* pNorm))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:            nmppsNormDiff
//  Purpose:         calculate norm of vectors
//     Inf   - calculate C-norm of vectors:  n = MAX |src1-src2|
//     L1    - calculate L1-norm of vectors: n = SUM |src1-src2|
//     L2    - calculate L2-norm of vectors: n = SQRT(SUM |src1-src2|^2)
//     L2Sqr - calculate L2-norm of vectors: n = SUM |src1-src2|^2
//  Parameters:
//    pSrc1, pSrc2   source data pointers
//    len            length of vector
//    pNorm          pointer to result
//    scaleFactor    scale factor value
//  Returns:
//    nmppsStsNoErr       Ok
//    nmppsStsNullPtrErr  Some of pointers to input or output data are NULL
//    nmppsStsSizeErr     The length of vector is less or equal zero
//  Notes:
*/
NMPPSAPI(nmppsStatus, nmppsNormDiff_Inf_32f,         (const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNormDiff_Inf_64f,         (const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, int len, nmpps64f* pNorm))

NMPPSAPI(nmppsStatus, nmppsNormDiff_L1_16s32s_Sfs,   (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, int len, nmpps32s* pNorm, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsNormDiff_L1_16s32f,       (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNormDiff_L1_32f,          (const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNormDiff_L1_64f,          (const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, int len, nmpps64f* pNorm))

NMPPSAPI(nmppsStatus, nmppsNormDiff_L2_16s32s_Sfs,   (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, int len, nmpps32s* pNorm, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsNormDiff_L2_16s32f,       (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNormDiff_L2_32f,          (const nmpps32f*  pSrc1, const nmpps32f*  pSrc2, int len, nmpps32f* pNorm))
NMPPSAPI(nmppsStatus, nmppsNormDiff_L2_64f,          (const nmpps64f*  pSrc1, const nmpps64f*  pSrc2, int len, nmpps64f* pNorm))

/* /////////////////////////////////////////////////////////////////////////////
//                  Dot Product Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       nmppsDotProd
//  Purpose:    compute Dot Product value
//  Arguments:
//     pSrc1               pointer to the source vector
//     pSrc2               pointer to the another source vector
//     len                 vector's length, number of items
//     pDp                 pointer to the result
//     scaleFactor         scale factor value
//  Return:
//     nmppsStsNullPtrErr       pointer(s) pSrc pDst is NULL
//     nmppsStsSizeErr          length of the vectors is less or equal 0
//     nmppsStsNoErr            otherwise
//  Notes:
//     the functions don't conjugate one of the source vectors
*/
NMPPSAPI(nmppsStatus, nmppsDotProd_16s32s_Sfs,   (const nmpps16s*  pSrc1, const nmpps16s*  pSrc2, int len, nmpps32s*  pDp, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsDotProd_16s32s32s_Sfs,(const nmpps16s*  pSrc1, const nmpps32s*  pSrc2, int len, nmpps32s*  pDp, int scaleFactor))
NMPPSAPI(nmppsStatus, nmppsDotProd_32s_Sfs,      (const nmpps32s*  pSrc1, const nmpps32s*  pSrc2, int len, nmpps32s*  pDp, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinEvery, nmppsMaxEvery
// Purpose:    Calculation min/max value for every element of two vectors.
// Parameters:
//    pSrc     - Pointer to the first input vector.
//    pSrcDst  - Pointer to the second input vector which stores the result.
//    pSrc1    - Pointer to the first input vector.
//    pSrc2    - Pointer to the second input vector.
//    pDst     - Pointer to the destination vector.
//    len      - Length of the vector.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/
NMPPSAPI(nmppsStatus, nmppsMinEvery_16s_I, (const nmpps16s* pSrc, nmpps16s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsMinEvery_32s_I, (const nmpps32s* pSrc, nmpps32s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsMinEvery_32f_I, (const nmpps32f* pSrc, nmpps32f* pSrcDst, int len))

NMPPSAPI(nmppsStatus, nmppsMaxEvery_16s_I, (const nmpps16s* pSrc, nmpps16s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsMaxEvery_32s_I, (const nmpps32s* pSrc, nmpps32s* pSrcDst, int len))
NMPPSAPI(nmppsStatus, nmppsMaxEvery_32f_I, (const nmpps32f* pSrc, nmpps32f* pSrcDst, int len))


#endif /* __NMPPSS_H__ */
