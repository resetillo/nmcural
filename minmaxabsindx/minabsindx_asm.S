#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// Names:      nmppsMinAbsIndx
// Purpose:    Returns the min absolute value of a vector and the index of the corresponding element.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMinAbs  - Pointer to the min absolute value found.
//    pMinIndx - Pointer to index of the first minimum absolute value.
// Returns:
//    nmppsStsNoErr       - OK.
//    nmppsStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    nmppsStsSizeErr     - Error when length of the vector is less or equal 0.
*/

	.text


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinAbsIndx_16s(const nmpps16s* pSrc, int len, nmpps16s* pMinAbs, int* pIndx) {
*/
	.align 8
_nmppsMinAbsIndx_16s: .globl _nmppsMinAbsIndx_16s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pIndx*, gr2 == pMinAbs

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbsIndx_16s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMinAbs == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbsIndx_16s_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMinAbs

	// if (pIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbsIndx_16s_return;
	nul;											// delay slot: ar3 == addr of min
	ar3, gr3 = ar0 with gr0;						// delay slot: gr3 == base of pSrc

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinAbsIndx_16s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++];
	gr7 = gr1 A>> 31;
	gr1 = gr1 xor gr7;
	gr1 = gr1 - gr7;

.LnmppsMinAbsIndx_16s_loop:
	gr2 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

	if <= delayed goto .LnmppsMinAbsIndx_16s_give_result with gr7 = gr2 A>> 31;
	gr2 = gr2 xor gr7;								// delay slot
	gr2 = gr2 - gr7;								// delay slot

	with gr1 - gr2;

	if <= goto .LnmppsMinAbsIndx_16s_loop;

	delayed goto .LnmppsMinAbsIndx_16s_loop;
	ar3 = ar0 - 1 addr with gr1 = gr2 noflags;		// delay slot (x2)

.LnmppsMinAbsIndx_16s_give_result:
	gr2 = ar3 set with gr7 = nmppsStsNoErr;
	[ar1] = gr1 with gr2 -= gr3 noflags;
	[ar2] = gr2;

.LnmppsMinAbsIndx_16s_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsMinAbsIndx_32s(const nmpps32s* pSrc, int len, nmpps32s* pMinAbs, int* pIndx) {
*/
	.align 8
_nmppsMinAbsIndx_32s: .globl _nmppsMinAbsIndx_32s
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;

	gr7 = nmppsStsNullPtrErr;

	ar1,gr1 = [--ar5]; 								// after read: 	ar1 == len, gr1 == pSrc
	ar2,gr2 = [--ar5] with gr1; 					// 				*ar2 == pIndx*, gr2 == pMinAbs

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbsIndx_32s_return;
	ar0 = gr1;										// delay slot: ar0 == pSrc
	gr1 = ar2 with gr2;								// delay slot

	// if (pMinAbs == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbsIndx_32s_return;
	gr0 = ar1;										// delay slot: gr0 == len
	ar1 = gr2 with gr1;								// delay slot: ar1 == pMinAbs

	// if (pIndx == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsMinAbsIndx_32s_return;
	nul;											// delay slot: ar3 == addr of min
	ar3, gr3 = ar0 with gr0;						// delay slot: gr3 == base of pSrc

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsMinAbsIndx_32s_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr1 = [ar0++];
	gr7 = gr1 A>> 31;
	gr1 = gr1 xor gr7;
	gr1 = gr1 - gr7;

.LnmppsMinAbsIndx_32s_loop:
	gr2 = [ar0++] with gr0 = gr0 - 1;				// BUG! expr `gr0--' doesn't work

	if <= delayed goto .LnmppsMinAbsIndx_32s_give_result with gr7 = gr2 A>> 31;
	gr2 = gr2 xor gr7;								// delay slot
	gr2 = gr2 - gr7;								// delay slot

	with gr1 - gr2;

	if <= goto .LnmppsMinAbsIndx_32s_loop;

	delayed goto .LnmppsMinAbsIndx_32s_loop;
	ar3 = ar0 - 1 addr with gr1 = gr2 noflags;		// delay slot (x2)

.LnmppsMinAbsIndx_32s_give_result:
	gr2 = ar3 set with gr7 = nmppsStsNoErr;
	[ar1] = gr1 with gr2 -= gr3 noflags;
	[ar2] = gr2;

.LnmppsMinAbsIndx_32s_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
