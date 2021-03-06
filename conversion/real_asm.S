#include <nmpps_asm_defs.h>

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

	.text


/**
 * @addtogroup ConversionGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsReal_64fc(const nmpps64fc* pSrc, nmpps64f* pDstRe, int len)
 *
 * @brief Преобразование комплексного вектора в действительную часть типа nmpps64fc.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDstRe Вектор действительных частей.
 * @param[in] len Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsReal_64fc: .globl _nmppsReal_64fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// ar1 == pDst, gr1 == pSrc
	ar2 = gr1 with gr1;								// ar2 == pSrc

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsReal_64fc_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsReal_64fc_return with gr0;
	gr1 = 32;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsReal_64fc_return with gr0 - gr1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	// if (len < 32) ...
	if < delayed goto .LnmppsReal_64fc_remainder with gr7 = nmppsStsNoErr noflags;
	gr2 = 4;										// delay slot (x2)

.LnmppsReal_64fc_loop:
	fpu 0 rep 32 vreg0 = [ar2++gr2];
	fpu 0 rep 32 [ar1++] = vreg0;

	with gr0 -= gr1;
	with gr0 - gr1;

	if > goto .LnmppsReal_64fc_loop with gr0;

	if =0 delayed goto .LnmppsReal_64fc_return;
.LnmppsReal_64fc_remainder:
	with gr0 = gr0 - 1 noflags;						// delay slot
	vlen = gr0;										// delay slot

	fpu 0 rep vlen vreg0 = [ar2++gr2];
	fpu 0 rep vlen [ar1++] = vreg0;

.LnmppsReal_64fc_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsReal_32fc(const nmpps32fc* pSrc, nmpps32f* pDstRe, int len)
 *
 * @brief Преобразование комплексного вектора в действительную часть типа nmpps32fc.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDstRe Вектор действительных частей.
 * @param[in] len Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
_nmppsReal_32fc: .globl _nmppsReal_32fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// ar1 == pDst, gr1 == pSrc
	ar2 = gr1 with gr1;								// ar2 == pSrc

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsReal_32fc_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsReal_32fc_return with gr0;
	gr1 = 32;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsReal_32fc_return with gr0 - gr1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	// if (len < 32) ...
	if < delayed goto .LnmppsReal_32fc_less32 with gr7 = nmppsStsNoErr noflags;
	gr2 = 2;										// delay slot (x2)

.LnmppsReal_32fc_more_than_32:
	fpu rep 32 .packer = [ar2++] with .float <= .float .in_low;	// packer[16] = (re, re) <= mem[32] = (complex)
	fpu rep 16 [ar1++] = .packer;

	with gr0 -= gr1;
	with gr0 - gr1;
	if > goto .LnmppsReal_32fc_more_than_32 with gr0;

.LnmppsReal_32fc_less32:
	if =0 delayed goto .LnmppsReal_32fc_return with gr1 = gr0 >> 1;
	with gr1 <<= 1;									// delay slot
	with gr0 -= gr1;								// delay slot

	with gr1 = gr1 - 1;
	vlen = gr1;

	if < delayed goto .LnmppsReal_32fc_last_one;
	with gr1 >>= 1;									// delay slot
	with gr0;										// delay slot

	fpu rep vlen .packer = [ar2++] with .float <= .float .in_low;

	if =0 delayed goto .LnmppsReal_32fc_return;
	vlen = gr1;										// delay slot
	fpu rep vlen [ar1++] = .packer;					// delay slot

.LnmppsReal_32fc_last_one:
	ar3, gr3 = [ar2++];
	[ar1++] = ar3;

.LnmppsReal_32fc_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */
