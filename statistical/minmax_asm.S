#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinMax
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

	.text


/**
 * @addtogroup StatisticalGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsMinMax_16s(const nmpps16s* pSrc, int len, nmpps16s* pMin, nmpps16s* pMax)
 *
 * @brief Определение минимального и максимального значений среди элементов вектора типа nmpps16s.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMin Минимальное значение.
 * @param[out] pMax Максимальное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMinMax_16s: .globl _nmppsMinMax_16s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pMax*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_16s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_16s_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_16s_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMax_16s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;
	gr2 = gr1 with gr3 = gr1 noflags;				// gr2 - min, gr3 - max

	if <= delayed goto .LnmppsMinMax_16s_give_result with gr7 = nmppsStsNoErr;
.LnmppsMinMax_16s_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 - gr2;									// delay slot

	if >= goto .LnmppsMinMax_16s_find_max with gr1 - gr3;

	gr2 = gr1 set;									// min found

.LnmppsMinMax_16s_find_max:
	if <= goto .LnmppsMinMax_16s_next with gr0 = gr0 - 1;

	gr3 = gr1 set;									// max found

.LnmppsMinMax_16s_next:
	if > delayed goto .LnmppsMinMax_16s_loop;

.LnmppsMinMax_16s_give_result:
	[ar1] = gr2;									// delay slot
	[ar2] = gr3;									// delay slot

.LnmppsMinMax_16s_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMinMax_32s(const nmpps32s* pSrc, int len, nmpps32s* pMin, nmpps32s* pMax)
 *
 * @brief Определение минимального и максимального значений среди элементов вектора типа nmpps32s.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMin Минимальное значение.
 * @param[out] pMax Максимальное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMinMax_32s: .globl _nmppsMinMax_32s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pMax*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_32s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_32s_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_32s_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMax_32s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;
	gr2 = gr1 with gr3 = gr1 noflags;				// gr2 - min, gr3 - max

	if <= delayed goto .LnmppsMinMax_32s_give_result with gr7 = nmppsStsNoErr;
.LnmppsMinMax_32s_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 - gr2;									// delay slot

	if v>= goto .LnmppsMinMax_32s_find_max with gr1 - gr3;

	gr2 = gr1 set;									// min found

.LnmppsMinMax_32s_find_max:
	if v<= goto .LnmppsMinMax_32s_next with gr0 = gr0 - 1;

	gr3 = gr1 set;									// max found

.LnmppsMinMax_32s_next:
	if > delayed goto .LnmppsMinMax_32s_loop;

.LnmppsMinMax_32s_give_result:
	[ar1] = gr2;									// delay slot
	[ar2] = gr3;									// delay slot

.LnmppsMinMax_32s_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMinMax_32f(const nmpps32f* pSrc, int len, nmpps32f* pMin, nmpps32f* pMax)
 *
 * @brief Определение минимального и максимального значений среди элементов вектора типа nmpps32f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMin Минимальное значение.
 * @param[out] pMax Максимальное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMinMax_32f: .globl _nmppsMinMax_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pMax*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_32f_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_32f_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_32f_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMax_32f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;
	gr2 = gr1 with gr3 = gr1 noflags;				// gr2 - min, gr3 - max

	if <= delayed goto .LnmppsMinMax_32f_give_result with gr7 = nmppsStsNoErr;
.LnmppsMinMax_32f_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 and gr2;								// delay slot

	if >= delayed goto .LnmppsMinMax_32f_find_min;
	nul;											// delay slot
	with gr1 - gr2;									// delay slot
	with gr2 - gr1;

.LnmppsMinMax_32f_find_min:
	if v>= delayed goto .LnmppsMinMax_32f_try_find_max;
	nul;											// delay slot
	with gr1 and gr3;								// delay slot

	gr2 = gr1 set;

.LnmppsMinMax_32f_try_find_max:
	if >= delayed goto .LnmppsMinMax_32f_find_max;
	nul;											// delay slot
	with gr1 - gr3;									// delay slot
	with gr3 - gr1;

.LnmppsMinMax_32f_find_max:
	if v<= goto .LnmppsMinMax_32f_next with gr0 = gr0 - 1;

	gr3 = gr1 set;

.LnmppsMinMax_32f_next:
	if > goto .LnmppsMinMax_32f_loop;

.LnmppsMinMax_32f_give_result:
	[ar1] = gr2;
	[ar2] = gr3;

.LnmppsMinMax_32f_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMinMax_64f(const nmpps64f* pSrc, int len, nmpps64f* pMin, nmpps64f* pMax)
 *
 * @brief Определение минимального и максимального значений среди элементов вектора типа nmpps64f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMin Минимальное значение.
 * @param[out] pMax Максимальное значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMinMax_64f: .globl _nmppsMinMax_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pMax*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_64f_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_64f_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMax_64f_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMax_64f_return with gr0 = gr0 - 1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	fpu 0 rep 1 vreg1 = [ar0];						// vreg1 = min
	fpu 0 rep 1 vreg2 = [ar0++];					// vreg2 = max

	if <= goto .LnmppsMinMax_64f_give_result with gr7 = nmppsStsNoErr;

.LnmppsMinMax_64f_loop:
	fpu 0 rep 1 vreg0 = [ar0++];

	fpu 0 .double vreg0 - vreg1, set mask if <;
	fpu 0 .double vreg1 = mask ? vreg0 : vreg1;
	fpu 0 .double vreg0 - vreg2, set mask if >;
	fpu 0 .double vreg2 = mask ? vreg0 : vreg2;

	with gr0 = gr0 - 1;
	if > goto .LnmppsMinMax_64f_loop;

.LnmppsMinMax_64f_give_result:
	fpu 0 rep 1 [ar1] = vreg1;
	fpu 0 rep 1 [ar2] = vreg2;

.LnmppsMinMax_64f_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */
