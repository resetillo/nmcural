#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinMaxIndx
// Purpose:    Find element with min/max value and return the value and the index.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMin     - Pointer to min value found.
//    pMax     - Pointer to max value found.
//    pMinIndx - Pointer to index of the first minimum value.
//    pMaxIndx - Pointer to index of the first maximum value.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/

	.text


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinMaxIndx_16s(const nmpps16s* pSrc, int len, nmpps16s* pMin, int* pMinIndx, nmpps16s* pMax, int* pMaxIndx) {
*/
	.align 8
_nmppsMinMaxIndx_16s: .globl _nmppsMinMaxIndx_16s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar6, gr6;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5]; 								// 				*ar2 == pMinIndx*, gr2 == pMin
	ar3,gr3 = [--ar5] with gr1;						// 				*ar3 == pMaxIndx*, gr3 == pMax

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_16s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr0 = ar1 with gr2;								// delay slot: gr0 == len

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_16s_return;
	gr1 = ar2;										// delay slot
	gr4 = ar3 with gr1;								// delay slot

	// if (pMinIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_16s_return;
	ar5 = ar0;										// delay slot: ar5 == addr of min
	ar6, gr6 = ar0 with gr3;						// delay slot: ar6 == addr of max
													// gr6 == base of pSrc

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_16s_return;
	ar1 = gr2;										// ar1 == pMin
	ar4 = gr3 with gr4;								// ar4 == pMax

	// if (pMaxIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_16s_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMaxIndx_16s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;
	gr2 = gr1 with gr3 = gr1 noflags;						// gr2 == min, gr3 == max

	if <= delayed goto .LnmppsMinMaxIndx_16s_give_result with gr7 = nmppsStsNoErr;
.LnmppsMinMaxIndx_16s_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 - gr2;									// delay slot

	if >= goto .LnmppsMinMaxIndx_16s_find_max with gr1 - gr3;

	ar5 = ar0 - 1 with gr2 = gr1 noflags;

.LnmppsMinMaxIndx_16s_find_max:
	if <= goto .LnmppsMinMaxIndx_16s_next with gr0 = gr0 - 1;

	ar6 = ar0 - 1 with gr3 = gr1 noflags;

.LnmppsMinMaxIndx_16s_next:
	if > goto .LnmppsMinMaxIndx_16s_loop;

.LnmppsMinMaxIndx_16s_give_result:
	gr1 = ar5;
	gr4 = ar6 with gr1 -= gr6;

	[ar1] = gr2 with gr4 -= gr6;					// pMin
	[ar2] = gr1;									// pMinIndx

	[ar4] = gr3;									// pMax
	[ar3] = gr4;									// pMaxIndx

.LnmppsMinMaxIndx_16s_return:
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinMaxIndx_32s(const nmpps32s* pSrc, int len, nmpps32s* pMin, int* pMinIndx, nmpps32s* pMax, int* pMaxIndx) {
*/
	.align 8
_nmppsMinMaxIndx_32s: .globl _nmppsMinMaxIndx_32s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar6, gr6;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5]; 								// 				*ar2 == pMinIndx*, gr2 == pMin
	ar3,gr3 = [--ar5] with gr1;						// 				*ar3 == pMaxIndx*, gr3 == pMax

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr0 = ar1 with gr2;								// delay slot: gr0 == len

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32s_return;
	gr1 = ar2;										// delay slot
	gr4 = ar3 with gr1;								// delay slot

	// if (pMinIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32s_return;
	ar5 = ar0;										// delay slot: ar5 == addr of min
	ar6, gr6 = ar0 with gr3;						// delay slot: ar6 == addr of max
													// gr6 == base of pSrc

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32s_return;
	ar1 = gr2;										// ar1 == pMin
	ar4 = gr3 with gr4;								// ar4 == pMax

	// if (pMaxIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32s_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMaxIndx_32s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;
	gr2 = gr1 with gr3 = gr1 noflags;				// gr2 == min, gr3 == max

	if <= delayed goto .LnmppsMinMaxIndx_32s_give_result with gr7 = nmppsStsNoErr;
.LnmppsMinMaxIndx_32s_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 - gr2;									// delay slot

	if v>= goto .LnmppsMinMaxIndx_32s_find_max with gr1 - gr3;

	ar5 = ar0 - 1 with gr2 = gr1 noflags;

.LnmppsMinMaxIndx_32s_find_max:
	if v<= goto .LnmppsMinMaxIndx_32s_next with gr0 = gr0 - 1;

	ar6 = ar0 - 1 with gr3 = gr1 noflags;

.LnmppsMinMaxIndx_32s_next:
	if > goto .LnmppsMinMaxIndx_32s_loop;

.LnmppsMinMaxIndx_32s_give_result:
	gr1 = ar5;
	gr4 = ar6 with gr1 -= gr6;

	[ar1] = gr2 with gr4 -= gr6;					// pMin
	[ar2] = gr1;									// pMinIndx

	[ar4] = gr3;									// pMax
	[ar3] = gr4;									// pMaxIndx

.LnmppsMinMaxIndx_32s_return:
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinMaxIndx_32f(const nmpps32f* pSrc, int len, nmpps32f* pMin, int* pMinIndx, nmpps32f* pMax, int* pMaxIndx) {
*/
	.align 8
_nmppsMinMaxIndx_32f: .globl _nmppsMinMaxIndx_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar6, gr6;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5]; 								// 				*ar2 == pMinIndx*, gr2 == pMin
	ar3,gr3 = [--ar5] with gr1;						// 				*ar3 == pMaxIndx*, gr3 == pMax

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32f_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr0 = ar1 with gr2;								// delay slot: gr0 == len

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32f_return;
	gr1 = ar2;										// delay slot
	gr4 = ar3 with gr1;								// delay slot

	// if (pMinIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32f_return;
	ar5 = ar0;										// delay slot: ar5 == addr of min
	ar6, gr6 = ar0 with gr3;						// delay slot: ar6 == addr of max
													// gr6 == base of pSrc

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32f_return;
	ar1 = gr2;										// ar1 == pMin
	ar4 = gr3 with gr4;								// ar4 == pMax

	// if (pMaxIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_32f_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMaxIndx_32f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;
	gr2 = gr1 with gr3 = gr1 noflags;				// gr2 == min, gr3 == max

	if <= delayed goto .LnmppsMinMaxIndx_32f_give_result with gr7 = nmppsStsNoErr;
.LnmppsMinMaxIndx_32f_loop:
	gr1 = [ar0++];									// delay slot
	with gr1 and gr2;								// delay slot

	if >= delayed goto .LnmppsMinMaxIndx_32f_find_min;
	nul;											// delay slot
	with gr1 - gr2;									// delay slot
	with gr2 - gr1;

.LnmppsMinMaxIndx_32f_find_min:
	if v>= delayed goto .LnmppsMinMaxIndx_32f_try_find_max;
	nul;											// delay slot
	with gr1 and gr3;								// delay slot

	ar5 = ar0 - 1 with gr2 = gr1 noflags;

.LnmppsMinMaxIndx_32f_try_find_max:
	if >= delayed goto .LnmppsMinMaxIndx_32f_find_max;
	nul;											// delay slot
	with gr1 - gr3;									// delay slot
	with gr3 - gr1;

.LnmppsMinMaxIndx_32f_find_max:
	if v<= goto .LnmppsMinMaxIndx_32f_next with gr0 = gr0 - 1;

	ar6 = ar0 - 1 with gr3 = gr1 noflags;

.LnmppsMinMaxIndx_32f_next:
	if > goto .LnmppsMinMaxIndx_32f_loop;

.LnmppsMinMaxIndx_32f_give_result:
	gr1 = ar5;
	gr4 = ar6 with gr1 -= gr6;

	[ar1] = gr2 with gr4 -= gr6;					// pMin
	[ar2] = gr1;									// pMinIndx

	[ar4] = gr3;									// pMax
	[ar3] = gr4;									// pMaxIndx

.LnmppsMinMaxIndx_32f_return:
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinMaxIndx_64f(const nmpps64f* pSrc, int len, nmpps64f* pMin, int* pMinIndx, nmpps64f* pMax, int* pMaxIndx) {
*/
	.align 8
_nmppsMinMaxIndx_64f: .globl _nmppsMinMaxIndx_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar6, gr6;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5]; 								// 				*ar2 == pMinIndx*, gr2 == pMin
	ar3,gr3 = [--ar5] with gr1;						// 				*ar3 == pMaxIndx*, gr3 == pMax

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_64f_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr0 = ar1 with gr2;								// delay slot: gr0 == len

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_64f_return;
	gr1 = ar2;										// delay slot
	gr4 = ar3 with gr1;								// delay slot

	// if (pMinIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_64f_return;
	ar5 = ar0;										// delay slot: ar5 == addr of min
	ar6, gr6 = ar0 with gr3;						// delay slot: ar6 == addr of max
													// gr6 == base of pSrc

	// if (pMax == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_64f_return;
	ar1 = gr2;										// ar1 == pMin
	ar4 = gr3 with gr4;								// ar4 == pMax

	// if (pMaxIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinMaxIndx_64f_return;
	nul;											// delay slot
	with gr0;										// delay slot

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinMaxIndx_64f_return with gr0 = gr0 - 1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	if <= delayed goto .LnmppsMinMaxIndx_64f_give_result with gr7 = nmppsStsNoErr;
	fpu 0 rep 1 vreg1 = [ar0];						// delay slot: vreg1 == min
	fpu 0 rep 1 vreg2 = [ar0++];					// delay slot: vreg2 == max

.LnmppsMinMaxIndx_64f_loop:
	fpu 0 rep 1 vreg0 = [ar0++];

	fpu 0 .double vreg0 - vreg1, set mask if <;
	fpu 0 .double vreg1 = mask ? vreg0 : vreg1;

	sir = fp0_dmask;
	gr1 = sir;
	with gr1;

	if =0 goto .LnmppsMinMaxIndx_64f_find_max;

	ar5 = ar0 - 2 addr;

.LnmppsMinMaxIndx_64f_find_max:
	fpu 0 .double vreg0 - vreg2, set mask if >;
	fpu 0 .double vreg2 = mask ? vreg0 : vreg2;

	sir = fp0_dmask;
	gr2 = sir;
	with gr2;

	if =0 goto .LnmppsMinMaxIndx_64f_next with gr0 = gr0 - 1;

	ar6 = ar0 - 2 addr;

.LnmppsMinMaxIndx_64f_next:
	if > goto .LnmppsMinMaxIndx_64f_loop;

.LnmppsMinMaxIndx_64f_give_result:
	fpu 0 rep 1 [ar1] = vreg1;
	fpu 0 rep 1 [ar4] = vreg2;

	gr1 = ar5 set;
	gr2 = ar6 set with gr1 -= gr6;
	with gr2 -= gr6;
	with gr1 >>= 1;

	[ar2] = gr1 with gr2 >>= 1;
	[ar3] = gr2;

.LnmppsMinMaxIndx_64f_return:
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/
