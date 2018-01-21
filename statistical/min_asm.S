#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMin
// Purpose:    Find minimum value among all elements of the source vector
// Parameters:
//    pSrc     - Pointer to the source vector.
//    len      - Length of the vector.
//    pMin     - Pointer to the result.
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
 * @fn nmppsStatus nmppsMin_32f(const nmpps32f* pSrc, int len, nmpps32f* pMin)
 *
 * @brief Определение минимального значения среди элементов вектора типа nmpps32f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMin Минимальное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMin_32f: .globl _nmppsMin_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

	ar0 = [--ar5];									// ar0 == pSrc
	gr0 = [--ar5];									// gr0 == len
	ar1 = [--ar5] with gr0;							// ar1 == pMin

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMin_32f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = ar0;
	gr2 = ar1 with gr1;

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMin_32f_return with gr2;
	gr7 = nmppsStsNullPtrErr; 						// delay slot (x2)

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMin_32f_return;
	gr1 = [ar0++] with gr0 = gr0 - 1;				// delay slot: BUG! expr `gr0--' doesn't work
	gr2 = gr1 set;									// delay slot

	if <= delayed goto .LnmppsMin_32f_give_result with gr7 = nmppsStsNoErr;
.LnmppsMin_32f_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 and gr2;								// delay slot

	if >= delayed goto .LnmppsMin_32f_find_min;
	nul;											// delay slot
	with gr1 - gr2;									// delay slot
	with gr2 - gr1;

.LnmppsMin_32f_find_min:
	if v>= goto .LnmppsMin_32f_next with gr0 = gr0 - 1;

	gr2 = gr1 set;

.LnmppsMin_32f_next:
	if > goto .LnmppsMin_32f_loop;

.LnmppsMin_32f_give_result:
	[ar1] = gr2;

.LnmppsMin_32f_return:
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMin_64f(const nmpps64f* pSrc, int len, nmpps64f* pMin)
 *
 * @brief Определение минимального значения среди элементов вектора типа nmpps64f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMin Минимальное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMin_64f: .globl _nmppsMin_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

	ar0 = [--ar5];									// ar0 == pSrc
	gr0 = [--ar5];									// gr0 == len
	ar1 = [--ar5] with gr0;							// ar1 == pMin

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMin_64f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = ar0;
	gr2 = ar1 with gr1;

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMin_64f_return with gr2;
	gr7 = nmppsStsNullPtrErr; 						// delay slot (x2)

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMin_64f_return;
	ar2,gr2 = [ar0++];								// delay slot
	[ar1] = ar2,gr2 with gr0 = gr0 - 1;				// delay slot

	if <= goto .LnmppsMin_64f_return with gr7 = nmppsStsNoErr;

	fpu 0 rep 1 vreg0 = [ar1];

.LnmppsMin_64f_loop:
	fpu 0 rep 1 vreg1 = [ar0++];

	fpu 0 .double vreg0 - vreg1, set mask if >;
	fpu 0 .double vreg0 = mask ? vreg1 : vreg0;

	with gr0 = gr0 - 1;
	if > goto .LnmppsMin_64f_loop;

	fpu 0 rep 1 [ar1] = vreg0;

.LnmppsMin_64f_return:
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */
