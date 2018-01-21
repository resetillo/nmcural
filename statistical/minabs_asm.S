#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinAbs
// Purpose:    Returns the minimum absolute value of a vector.
// Parameters:
//    pSrc     - Pointer to the source vector.
//    len      - Length of the vector.
//    pMinAbs  - Pointer to the result.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/

	.text


/**
 * @addtogroup StatisticalGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsMinAbs_16s(const nmpps16s* pSrc, int len, nmpps16s* pMinAbs)
 *
 * @brief Определение минимального абсолютного значения среди элементов вектора типа nmpps16s.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMinAbs Минимальное абсолютное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMinAbs_16s: .globl _nmppsMinAbs_16s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	gr2 = [--ar5] with gr1;							// gr2 == pMinAbs

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbs_16s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr0 = ar1 with gr2;								// delay slot: gr0 == len

	// if (pMinAbs == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbs_16s_return;
	nul;											// delay slot
	ar1 = gr2 with gr0;								// delay slot: ar1 == pMinAbs

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinAbs_16s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++];
	gr7 = gr1 A>> 31;
	gr1 = gr1 xor gr7;
	gr1 = gr1 - gr7;

.LnmppsMinAbs_16s_loop:
	gr2 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

	if <= delayed goto .LnmppsMinAbs_16s_give_result with gr7 = gr2 A>> 31;
	gr2 = gr2 xor gr7;								// delay slot
	gr2 = gr2 - gr7;								// delay slot

	with gr1 - gr2;

	if <= goto .LnmppsMinAbs_16s_loop;
	goto .LnmppsMinAbs_16s_loop with gr1 = gr2 noflags;

.LnmppsMinAbs_16s_give_result:
	[ar1] = gr1 with gr7 = nmppsStsNoErr;

.LnmppsMinAbs_16s_return:
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMinAbs_32s(const nmpps32s* pSrc, int len, nmpps32s* pMinAbs)
 *
 * @brief Определение минимального абсолютного значения среди элементов вектора типа nmpps32s.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMinAbs Минимальное абсолютное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMinAbs_32s: .globl _nmppsMinAbs_32s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	gr2 = [--ar5] with gr1;							// gr2 == pMinAbs

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbs_32s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr0 = ar1 with gr2;								// delay slot: gr0 == len

	// if (pMinAbs == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbs_32s_return;
	nul;											// delay slot
	ar1 = gr2 with gr0;								// delay slot: ar1 == pMinAbs

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinAbs_32s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++];
	gr7 = gr1 A>> 31;
	gr1 = gr1 xor gr7;
	gr1 = gr1 - gr7;

.LnmppsMinAbs_32s_loop:
	gr2 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

	if <= delayed goto .LnmppsMinAbs_32s_give_result with gr7 = gr2 A>> 31;
	gr2 = gr2 xor gr7;								// delay slot
	gr2 = gr2 - gr7;								// delay slot

	with gr1 - gr2;

	if <= goto .LnmppsMinAbs_32s_loop;
	goto .LnmppsMinAbs_32s_loop with gr1 = gr2 noflags;

.LnmppsMinAbs_32s_give_result:
	[ar1] = gr1 with gr7 = nmppsStsNoErr;

.LnmppsMinAbs_32s_return:
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */
