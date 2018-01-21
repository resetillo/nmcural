#include <nmpps_asm_defs.h>

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

	.text


/**
 * @addtogroup ConversionGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsRealToCplx_64f(const nmpps64f* pSrcRe, const nmpps64f* pSrcIm, nmpps64fc* pDst, int len)
 *
 * @brief Преобразование действительного вектора в комплексный типа nmpps64f.
 *
 * @param pSrcRe[in] Исходный вектор действительных частей.
 * @param pSrcIm[in] Исходный вектор мнимых частей.
 * @param pDst[out] Получаемый вектор.
 * @param len [in] Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Указатель на выходной вектор или оба указателя действительной и мнимой частей имеют значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 *
 * @note Один из исходных векторов может иметь значение NULL, в таком случае соответствующий элемент комплексного числа получит значение 0.
 */
	.align
_nmppsRealToCplx_64f: .globl _nmppsRealToCplx_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar6, gr6;

	gr3 = [--ar5];
	gr6 = [--ar5];
	ar2, gr2 = [--ar5] with gr3 + gr6;

	// if (pSrcRe == NULL || pSrcIm == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsRealToCplx_64f_return with gr3;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsRealToCplx_64f_check_pSrcIm with gr0 = false;
	ar0 = Zero_64f;									// delay slot (x2)

	ar0 = gr3;										// ar0 == pSrcRe || Zero_64f
	gr0 = 2;

.LnmppsRealToCplx_64f_check_pSrcIm:
	with gr6;

	if =0 delayed goto .LnmppsRealToCplx_64f_after_pSrcIm with gr1 = false;
	ar1 = Zero_64f;

	ar1 = gr6;										// ar1 == pSrcIm || Zero_64f
	gr1 = 2;

.LnmppsRealToCplx_64f_after_pSrcIm:
	gr6 = ar2;										// gr6 == len
	ar2 = gr2 with gr2;								// ar2 == pDst

	// if (pDst == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsRealToCplx_64f_return with gr6;
	gr4 = 64;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsRealToCplx_64f_return with gr6 - gr4;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr2 = 4;										// element shift in complex numbers
	ar3 = ar2 + 2 addr with gr3 = gr2 noflags;		// ar2 == pDst->re, ar3 == pDst->im

	if < goto .LnmppsRealToCplx_64f_less64 with gr7 = nmppsStsNoErr;
.LnmppsRealToCplx_64f_more_than_64:
	fpu 0 rep 32 vreg0 = [ar0++gr0];
	fpu 0 rep 32 vreg1 = [ar0++gr0];
	fpu 0 rep 32 vreg2 = [ar1++gr1];
	fpu 0 rep 32 vreg3 = [ar1++gr1];

	// store Re parts
	fpu 0 rep 32 [ar2++gr2] = vreg0;
	fpu 0 rep 32 [ar2++gr2] = vreg1;
	// store Im parts
	fpu 0 rep 32 [ar3++gr3] = vreg2;
	fpu 0 rep 32 [ar3++gr3] = vreg3;

	with gr6 -= gr4;
	with gr6 - gr4;
	if > goto .LnmppsRealToCplx_64f_more_than_64 with gr6;

	if =0 delayed goto .LnmppsRealToCplx_64f_return;
.LnmppsRealToCplx_64f_less64:
	with gr4 >>= 1;									// delay slot: gr4 == 32
	with gr6 - gr4;									// delay slot

	if < goto .LnmppsRealToCplx_64f_less32;

	fpu 0 rep 32 vreg0 = [ar0++gr0];
	fpu 0 rep 32 vreg1 = [ar1++gr1];

	// store Re parts
	fpu 0 rep 32 [ar2++gr2] = vreg0;
	// store Im parts
	fpu 0 rep 32 [ar3++gr3] = vreg1;

	with gr6 -= gr4;
	if =0 delayed goto .LnmppsRealToCplx_64f_return;
.LnmppsRealToCplx_64f_less32:
	with gr6 = gr6 - 1;								// delay slot
	vlen = gr6;										// delay slot

	fpu 0 rep vlen vreg0 = [ar0++gr0];
	fpu 0 rep vlen vreg1 = [ar1++gr1];

	// store Re parts
	fpu 0 rep vlen [ar2++gr2] = vreg0;
	// store Im parts
	fpu 0 rep vlen [ar3++gr3] = vreg1;

.LnmppsRealToCplx_64f_return:
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsRealToCplx_32f(const nmpps32f* pSrcRe, const nmpps32f* pSrcIm, nmpps32fc* pDst, int len)
 *
 * @brief Преобразование действительного вектора в комплексный типа nmpps32f.
 *
 * @param pSrcRe[in] Исходный вектор действительных частей.
 * @param pSrcIm[in] Исходный вектор мнимых частей.
 * @param pDst[out] Получаемый вектор.
 * @param len [in] Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Указатель на выходной вектор или оба указателя действительной и мнимой частей имеют значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 *
 * @note Один из исходных векторов может иметь значение NULL, в таком случае соответствующий элемент комплексного числа получит значение 0.
 */
	.align
_nmppsRealToCplx_32f: .globl _nmppsRealToCplx_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar6, gr6;

	gr3 = [--ar5];
	gr6 = [--ar5];
	ar2, gr2 = [--ar5] with gr3 + gr6;

	// if (pSrcRe == NULL || pSrcIm == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsRealToCplx_32f_return with gr3;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsRealToCplx_32f_check_pSrcIm with gr0 = false;
	ar0 = Zero_32f;									// delay slot (x2)

	ar0 = gr3;										// ar0 == pSrcRe || Zero_32f
	gr0 = 2;

.LnmppsRealToCplx_32f_check_pSrcIm:
	with gr6;

	if =0 delayed goto .LnmppsRealToCplx_32f_after_pSrcIm with gr1 = false;
	ar1 = Zero_32f;

	ar1 = gr6;										// ar1 == pSrcIm || Zero_32f
	gr1 = 2;

.LnmppsRealToCplx_32f_after_pSrcIm:
	gr6 = ar2;										// gr6 == len
	ar2 = gr2 with gr2;								// ar2 == pDst

	// if (pDst == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsRealToCplx_32f_return with gr6;
	gr4 = 64;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsRealToCplx_32f_return with gr6 - gr4;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	ar5 = Float_Concat_Lo;
	ar6 = Float_Concat_Hi;

	gr2 = 4;										// complex numbers shift
	ar3 = ar2 + 2 addr with gr3 = gr2 noflags;		// ar2 == pDst, ar3 == pDst + 2

	if < goto .LnmppsRealToCplx_32f_less64 with gr7 = nmppsStsNoErr;
													//            lo   hi
	fpu 0 rep 32 vreg6 = [ar5];						// vreg6 = | 1.0, 0.0 |
	fpu 0 rep 32 vreg7 = [ar6];						// vreg7 = | 0.0, 1.0 |

.LnmppsRealToCplx_32f_more_than_64:
	fpu 0 rep 32 vreg0 = [ar0++gr0];
	fpu 0 rep 32 vreg1 = [ar1++gr1];

	fpu 0 .matrix vreg2 = vreg6 * (vreg0, vreg1);	// vreg2 stores lo parts of pair Re, Im
	fpu 0 .matrix vreg3 = vreg7 * (vreg0, vreg1);	// vreg3 stores hi parts of pair Re, Im

	fpu 0 rep 32 [ar2++gr2] = vreg2;
	fpu 0 rep 32 [ar3++gr3] = vreg3;

	with gr6 -= gr4;
	with gr6 - gr4;
	if > goto .LnmppsRealToCplx_32f_more_than_64 with gr6;

	if =0 delayed goto .LnmppsRealToCplx_32f_return;
.LnmppsRealToCplx_32f_less64:
	with gr4 >>= 1;									// delay slot: gr4 == 32
	with gr6 - gr4;									// delay slot

	if < goto .LnmppsRealToCplx_32f_less32;
													//            lo   hi
	fpu 0 rep 16 vreg6 = [ar5];						// vreg6 = | 1.0, 0.0 |
	fpu 0 rep 16 vreg7 = [ar6];						// vreg7 = | 0.0, 1.0 |

	fpu 0 rep 16 vreg0 = [ar0++gr0];
	fpu 0 rep 16 vreg1 = [ar1++gr1];

	fpu 0 .matrix vreg2 = vreg6 * (vreg0, vreg1);	// vreg2 stores lo parts of pair Re, Im
	fpu 0 .matrix vreg3 = vreg7 * (vreg0, vreg1);	// vreg3 stores hi parts of pair Re, Im

	fpu 0 rep 16 [ar2++gr2] = vreg2;
	fpu 0 rep 16 [ar3++gr3] = vreg3;

	with gr6 -= gr4;
.LnmppsRealToCplx_32f_less32:
	if =0 delayed goto .LnmppsRealToCplx_32f_return with gr4 = gr6;
	// div len by 2 cause it stores a count of floats but vlen assignes count of doubles
	with gr6 >>= 1;									// delay slot
	with gr6 = gr6 - 1;								// delay slot

	vlen = gr6 with gr6 = true noflags;				// gr6 == 0xFFFFFFFF (-1)

	if < delayed goto .LnmppsRealToCplx_32f_last_one;
	with gr4 += gr6;								// delay slot: gr4 -= 1
	with gr4 += gr6;								// delay slot: gr4 -= 1

	fpu 0 rep vlen vreg6 = [ar5];
	fpu 0 rep vlen vreg7 = [ar6];

	fpu 0 rep vlen vreg0 = [ar0++gr0];
	fpu 0 rep vlen vreg1 = [ar1++gr1];

	fpu 0 .matrix vreg2 = vreg6 * (vreg0, vreg1);	// vreg2 stores lo parts of pair Re, Im
	fpu 0 .matrix vreg3 = vreg7 * (vreg0, vreg1);	// vreg3 stores hi parts of pair Re, Im

	fpu 0 rep vlen [ar2++gr2] = vreg2;
	fpu 0 rep vlen [ar3++gr3] = vreg3;

	if =0 goto .LnmppsRealToCplx_32f_return;
.LnmppsRealToCplx_32f_last_one:
	ar4 = [ar0++gr0];
	gr4 = [ar1++gr1];

	[ar2] = ar4, gr4;

.LnmppsRealToCplx_32f_return:
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */


/* /////////////////////////////////////////////////////////////////////////////
// Module's constants
*/
	.align 2
Zero_64f: .double 0.0
Zero_32f: .float 0.0, 0.0
Float_Concat_Lo: .float 1.0, 0.0
Float_Concat_Hi: .float 0.0, 1.0
