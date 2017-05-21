#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinIndx
// Purpose:    Find element with min value and return the value and the index.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMin     - Pointer to min value found.
//    pIndx    - Pointer to index of the first min/max value.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/

	.text


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinIndx_16s(const nmpps16s* pSrc, int len, nmpps16s* pMin, int* pIndx) {
*/
	.align 8
_nmppsMinIndx_16s: .globl _nmppsMinIndx_16s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pIndx*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_16s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_16s_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_16s_return;
	nul;											// delay slot: ar3 == addr of min
	ar3, gr3 = ar0 with gr0;						// delay slot: gr3 == base of pSrc

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinIndx_16s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

.LnmppsMinIndx_16s_loop:
	if <= delayed goto .LnmppsMinIndx_16s_give_result;
	gr2 = [ar0++];									// delay slot
	with gr1 - gr2;									// delay slot

	if <= delayed goto .LnmppsMinIndx_16s_loop;
	nul;											// delay slot
	with gr0 = gr0 - 1;								// delay slot

	delayed goto .LnmppsMinIndx_16s_loop;
	ar3 = ar0 - 1 addr with gr1 = gr2 noflags;		// delay slot (x2)

.LnmppsMinIndx_16s_give_result:
	gr2 = ar3 set with gr7 = nmppsStsNoErr;
	[ar1] = gr1 with gr2 -= gr3 noflags;
	[ar2] = gr2;

.LnmppsMinIndx_16s_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinIndx_32s(const nmpps32s* pSrc, int len, nmpps32s* pMin, int* pIndx) {
*/
	.align 8
_nmppsMinIndx_32s: .globl _nmppsMinIndx_32s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pIndx*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_32s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_32s_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_32s_return;
	nul;											// delay slot: ar3 == addr of min
	ar3, gr3 = ar0 with gr0;						// delay slot: gr3 == base of pSrc

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinIndx_32s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

.LnmppsMinIndx_32s_loop:
	if <= delayed goto .LnmppsMinIndx_32s_give_result;
	gr2 = [ar0++];									// delay slot
	with gr1 - gr2;									// delay slot

	if v<= delayed goto .LnmppsMinIndx_32s_loop;
	nul;											// delay slot
	with gr0 = gr0 - 1;								// delay slot

	delayed goto .LnmppsMinIndx_32s_loop;
	ar3 = ar0 - 1 addr with gr1 = gr2 noflags;		// delay slot (x2)

.LnmppsMinIndx_32s_give_result:
	gr2 = ar3 set with gr7 = nmppsStsNoErr;
	[ar1] = gr1 with gr2 -= gr3 noflags;
	[ar2] = gr2;

.LnmppsMinIndx_32s_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinIndx_32f(const nmpps32f* pSrc, int len, nmpps32f* pMin, int* pIndx) {
*/
	.align 8
_nmppsMinIndx_32f: .globl _nmppsMinIndx_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pIndx*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_32f_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_32f_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_32f_return;
	nul;											// delay slot: ar3 == addr of min
	ar3, gr3 = ar0 with gr0;						// delay slot: gr3 == base of pSrc

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinIndx_32f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

.LnmppsMinIndx_32f_loop:
	if <= delayed goto .LnmppsMinIndx_32f_give_result;
	gr2 = [ar0++];									// delay slot
	with gr1 and gr2;								// delay slot

	if >= delayed goto .LnmppsMinIndx_32f_find_min;
	nul;											// delay slot
	with gr1 - gr2;									// delay slot
	with gr2 - gr1;

.LnmppsMinIndx_32f_find_min:
	if v<= goto .LnmppsMinIndx_32f_loop with gr0 = gr0 - 1;

	delayed goto .LnmppsMinIndx_32f_loop;
	ar3 = ar0 - 1 addr with gr1 = gr2 noflags;		// delay slot (x2)

.LnmppsMinIndx_32f_give_result:
	gr2 = ar3 set with gr7 = nmppsStsNoErr;
	[ar1] = gr1 with gr2 -= gr3 noflags;
	[ar2] = gr2;

.LnmppsMinIndx_32f_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinIndx_64f(const nmpps64f* pSrc, int len, nmpps64f* pMin, int* pIndx) {
*/
	.align 8
_nmppsMinIndx_64f: .globl _nmppsMinIndx_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pIndx*, gr2 == pMin

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_64f_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMin == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_64f_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMin

	// if (pIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinIndx_64f_return;
	nul;											// delay slot: ar3 == addr of min
	ar3, gr3 = ar0 with gr0;						// delay slot: gr3 == base of pSrc

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinIndx_64f_return with gr0 = gr0 - 1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	if <= delayed goto .LnmppsMinIndx_64f_give_result with gr7 = nmppsStsNoErr;
	nul;
	fpu 0 rep 1 vreg0 = [ar0++];

.LnmppsMinIndx_64f_loop:
	fpu 0 rep 1 vreg1 = [ar0++];
	fpu 0 .double vreg0 - vreg1, set mask if >;
	fpu 0 .double vreg0 = mask ? vreg1 : vreg0;

	sir = fp0_dmask;								// read FPU mask status
	gr1 = sir;
	with gr1;

	if =0 delayed goto .LnmppsMinIndx_64f_next;
	nul;
	with gr0 = gr0 - 1;

	ar3 = ar0 - 2 addr;								// update min value position

.LnmppsMinIndx_64f_next:
	if > goto .LnmppsMinIndx_64f_loop;

.LnmppsMinIndx_64f_give_result:
	gr2 = ar3 set;
	with gr2 -= gr3 noflags;
	with gr2 >>= 1;
	fpu 0 rep 1 [ar1] = vreg0;
	[ar2] = gr2;

.LnmppsMinIndx_64f_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/
