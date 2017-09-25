#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
//  Names:       nmppsConj
//  Purpose:     Complex conjugate input vector
//  Parameters:
//    pSrc               Pointer to input complex vector
//    pDst               Pointer to output complex vector
//    len                Vectors' length in elements
//  Return:
//    nmppsStsNullPtrErr      One of pointers is NULL
//    nmppsStsSizeErr         Vectors' length is less than 1
//    nmppsStsNoErr           Otherwise
*/
	.text


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsConj_32fc(const nmpps32fc* pSrc, nmpps32fc* pDst, int len) {
*/
	.align 8
_nmppsConj_32fc: .global _nmppsConj_32fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// ar1 == pDst, gr1 == pSrc
	ar0 = gr1 with gr1;								// ar0 == pSrc

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsConj_32fc_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsConj_32fc_return with gr0;
	gr1 = 32;										// delau slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsConj_32fc_return with gr0 - gr1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	ar5 = Conj_Complex_Matrix_2x2_32f;

	// if (len < 32) ...
	if < delayed goto .LnmppsConj_32fc_remainder with gr7 = nmppsStsNoErr noflags;
	// prepare matrix
	//
	// (vreg0, vreg1) = | 1  0 |
	//                  | 0 -1 |
	//
	fpu 0 rep 1 vreg0 = [ar5++];					// delay slot
	fpu 0 rep 1 vreg1 = [ar5++];					// delay slot

.LnmppsConj_32fc_loop:
	// one iteration allows to take 32 complex numbers (float) for calculation
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 .matrix vreg3 = vreg2 * .retrive (vreg0, vreg1);
	fpu 0 rep 32 [ar1++] = vreg3;

	with gr0 -= gr1;
	with gr0 - gr1;

	if > goto .LnmppsConj_32fc_loop with gr0;

	if =0 delayed goto .LnmppsConj_32fc_return;
.LnmppsConj_32fc_remainder:
	with gr0 = gr0 - 1 noflags;						// delay slot
	vlen = gr0;										// delay slot

	fpu 0 rep vlen vreg2 = [ar0++];
	fpu 0 .matrix vreg3 = vreg2 * .retrive (vreg0, vreg1);
	fpu 0 rep vlen [ar1++] = vreg3;

.LnmppsConj_32fc_return:
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsConj_64fc(const nmpps64fc* pSrc, nmpps64fc* pDst, int len) {
*/
	.align 8
_nmppsConj_64fc: .global _nmppsConj_64fc
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5]; 							// ar1 == pDst, gr1 == pSrc
	ar0 = gr1 with gr1;

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsConj_64fc_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsConj_64fc_return with gr0;
	gr1 = 32;										// delay slot (x2)

	// the length has been multipled by 2 in order to load a pair of doubles (Re and Im parts)
	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsConj_64fc_return with gr0 <<= 1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	with gr0 - gr1;

	if < goto .LnmppsConj_64fc_remainder with gr7 = nmppsStsNoErr noflags;

.LnmppsConj_64fc_loop:
	// one iteration allows to take 16 complex numbers (double) for calculation
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	// rep is divided by 2 cause 32 doubles are going to 2 vectors (Re vector, Im vector)
	fpu 0 rep 16 (vreg0,vreg1) = .packer; 			// vreg0 = re
													// vreg1 = im

													// vreg0 =  vreg0; (Re)
	fpu 0 .double vreg1 = -vreg1;					// vreg1 = -vreg1; (Im)

	fpu 0 .packer = (vreg0,vreg1) with .double <= .double;
	fpu rep 32 [ar1++] = .packer;

	with gr0 -= gr1 noflags;
	with gr0 - gr1;

	// while (len > 32)
	if > goto .LnmppsConj_64fc_loop with gr0;

	// if (len == 0) return nmppsStsNoErr;
	if =0 delayed goto .LnmppsConj_64fc_return;
.LnmppsConj_64fc_remainder:
	with gr0 = gr0 - 1;								// delay slot
	vlen = gr0 with gr1 = gr0 >> 1;					// delay slot

	fpu rep vlen .packer = [ar0++] with .double <= .double;

	vlen = gr1;
	// rep is divided by 2 cause 32 doubles are going to 2 vectors (Re vector, Im vector)
	fpu 0 rep vlen (vreg0,vreg1) = .packer; 		// vreg0 = re
													// vreg1 = im

													// vreg0 =  vreg0; (Re)
	fpu 0 .double vreg1 = -vreg1;					// vreg1 = -vreg1; (Im)

	vlen = gr0;

	fpu 0 .packer = (vreg0,vreg1) with .double <= .double;
	fpu rep vlen [ar1++] = .packer;

.LnmppsConj_64fc_return:
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// Module constants
*/

	.align 2
Conj_Complex_Matrix_2x2_32f:
	.float +1.0
	.float +0.0
	.float +0.0
	.float -1.0

