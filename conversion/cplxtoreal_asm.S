#include <nmpps_asm_defs.h>

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

	.text


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsCplxToReal_64fc(const nmpps64fc* pSrc, nmpps64f* pDstRe, nmpps64f* pDstIm, int len) {
*/
	.align 8
_nmppsCplxToReal_64fc: .globl _nmppsCplxToReal_64fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

	ar1, gr1 = [--ar5];								// after read: ar1 == pDstRe, gr1 == pSrc
	ar2, gr2 = [--ar5] with gr1;					//             ar2 == len, gr2 = pDstIm

	// if (pSrc == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	gr0 = ar1;
	ar0 = gr1 with gr0;								// ar0 == pSrc

	// if (pDstRe == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
	gr0 = ar2;										// delay slot: gr0 == len
	ar2 = gr2 with gr2;								// delay slot: ar2 == pDstIm

	// if (pDstIm == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return with gr0;
	gr2 = 64;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsCplxToReal_64fc_return with gr0 - gr2;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	if < goto .LnmppsCplxToReal_64fc_less64 with gr7 = nmppsStsNoErr;

.LnmppsCplxToReal_64fc_more_than_64:
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg0, vreg1) = .packer;			// vreg0 == Re, vreg1 == Im
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg2, vreg3) = .packer;			// vreg2 == Re, vreg3 == Im
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg4, vreg5) = .packer;			// vreg4 == Re, vreg5 == Im
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg6, vreg7) = .packer;			// vreg6 == Re, vreg7 == Im

	// store Re parts
	fpu 0 rep 16 [ar1++] = vreg0;
	fpu 0 rep 16 [ar1++] = vreg2;
	fpu 0 rep 16 [ar1++] = vreg4;
	fpu 0 rep 16 [ar1++] = vreg6;

	// store Im parts
	fpu 0 rep 16 [ar2++] = vreg1;
	fpu 0 rep 16 [ar2++] = vreg3;
	fpu 0 rep 16 [ar2++] = vreg5;
	fpu 0 rep 16 [ar2++] = vreg7;

	with gr0 -= gr2 noflags;
	with gr0 - gr2;
	if > goto .LnmppsCplxToReal_64fc_more_than_64;

	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
.LnmppsCplxToReal_64fc_less64:
	with gr2 >>= 1;									// delay slot: gr2 == 32
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_64fc_less32;

	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg0, vreg1) = .packer;			// vreg0 == Re, vreg1 == Im
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg2, vreg3) = .packer;			// vreg2 == Re, vreg3 == Im

	// store Re parts
	fpu 0 rep 16 [ar1++] = vreg0;
	fpu 0 rep 16 [ar1++] = vreg2;

	// store Im parts
	fpu 0 rep 16 [ar2++] = vreg1;
	fpu 0 rep 16 [ar2++] = vreg3;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
.LnmppsCplxToReal_64fc_less32:
	with gr2 >>= 1;									// delay slot: gr2 = 16
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_64fc_less16;

	fpu rep 32 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 16 (vreg0, vreg1) = .packer;			// vreg0 == Re, vreg1 == Im

	// store Re parts
	fpu 0 rep 16 [ar1++] = vreg0;

	// store Im parts
	fpu 0 rep 16 [ar2++] = vreg1;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
.LnmppsCplxToReal_64fc_less16:
	with gr2 >>= 1;									// delay slot: gr2 =  8
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_64fc_less8;

	fpu rep 16 .packer = [ar0++] with .double <= .double;
	fpu 0 rep 8 (vreg0, vreg1) = .packer;			// vreg0 == Re, vreg1 == Im

	// store Re parts
	fpu 0 rep 8 [ar1++] = vreg0;

	// store Im parts
	fpu 0 rep 8 [ar2++] = vreg1;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
.LnmppsCplxToReal_64fc_less8:
	with gr2 >>= 1;									// delay slot: gr2 =  4
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_64fc_less4;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0 == Re
	fpu 0 rep 1 vreg1 = [ar0++];					// vreg1 == Im
	fpu 0 rep 1 vreg2 = [ar0++];					// vreg2 == Re
	fpu 0 rep 1 vreg3 = [ar0++];					// vreg3 == Im
	fpu 0 rep 1 vreg4 = [ar0++];					// vreg4 == Re
	fpu 0 rep 1 vreg5 = [ar0++];					// vreg5 == Im
	fpu 0 rep 1 vreg6 = [ar0++];					// vreg6 == Re
	fpu 0 rep 1 vreg7 = [ar0++];					// vreg7 == Im

	// store Re parts
	fpu 0 rep 1 [ar1++] = vreg0;
	fpu 0 rep 1 [ar1++] = vreg2;
	fpu 0 rep 1 [ar1++] = vreg4;
	fpu 0 rep 1 [ar1++] = vreg6;

	// store Im parts
	fpu 0 rep 1 [ar2++] = vreg1;
	fpu 0 rep 1 [ar1++] = vreg3;
	fpu 0 rep 1 [ar1++] = vreg5;
	fpu 0 rep 1 [ar1++] = vreg7;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_64fc_return;
.LnmppsCplxToReal_64fc_less4:
	with gr2 >>= 1;									// delay slot: gr2 =  2
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_64fc_the_last_one;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0 == Re
	fpu 0 rep 1 vreg1 = [ar0++];					// vreg1 == Im
	fpu 0 rep 1 vreg2 = [ar0++];					// vreg2 == Re
	fpu 0 rep 1 vreg3 = [ar0++];					// vreg3 == Im

	// store Re parts
	fpu 0 rep 1 [ar1++] = vreg0;
	fpu 0 rep 1 [ar1++] = vreg2;

	// store Im parts
	fpu 0 rep 1 [ar2++] = vreg1;
	fpu 0 rep 1 [ar2++] = vreg3;

	with gr0 -= gr2;
	if =0 goto .LnmppsCplxToReal_64fc_return;
.LnmppsCplxToReal_64fc_the_last_one:
	fpu 0 rep 1 vreg0 = [ar0++];
	fpu 0 rep 1 vreg1 = [ar0++];

	fpu 0 rep 1 [ar1++] = vreg0;
	fpu 0 rep 1 [ar2++] = vreg1;

.LnmppsCplxToReal_64fc_return:
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/* /////////////////////////////////////////////////////////////////////////////
// nmppsStatus nmppsCplxToReal_32fc(const nmpps32fc* pSrc, nmpps32f* pDstRe, nmpps32f* pDstIm, int len) {
*/
	.align 8
_nmppsCplxToReal_32fc: .globl _nmppsCplxToReal_32fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;									// to fetch a pair

	ar1, gr1 = [--ar5];								// after read: ar1 == pDstRe, gr1 == pSrc
	ar2, gr2 = [--ar5] with gr1;					//             ar2 == len, gr2 = pDstIm

	// if (pSrc == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	gr0 = ar1;
	ar0 = gr1 with gr0;								// ar0 == pSrc

	// if (pDstRe == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
	gr0 = ar2;										// delay slot: gr0 == len
	ar2 = gr2 with gr2;								// delay slot: ar2 == pDstIm

	// if (pDstIm == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return with gr0;
	gr2 = 64;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsCplxToReal_32fc_return with gr0 - gr2;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	if < goto .LnmppsCplxToReal_32fc_less64 with gr7 = nmppsStsNoErr;
.LnmppsCplxToReal_32fc_more_than_64:
	fpu 0 rep 32 vreg6 = [ar0++];					// 32 complex numbers
	fpu 0 rep 32 vreg7 = [ar0++];					// 32 complex numbers

	// store Re parts
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu rep 16 [ar1++] = .packer;
	fpu 0 .packer = vreg7 with .float <= .float .in_low;
	fpu rep 16 [ar1++] = .packer;

	// store Im parts
	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu rep 16 [ar2++] = .packer;
	fpu 0 .packer = vreg7 with .float <= .float .in_high;
	fpu rep 16 [ar2++] = .packer;

	with gr0 -= gr2 noflags;
	with gr0 - gr2;
	if > goto .LnmppsCplxToReal_32fc_more_than_64;

	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
.LnmppsCplxToReal_32fc_less64:
	with gr2 >>= 1;									// delay slot: gr2 == 32
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_32fc_less32;

	fpu 0 rep 32 vreg6 = [ar0++];					// 32 complex numbers

	// store Re parts
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu rep 16 [ar1++] = .packer;

	// store Im parts
	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu rep 16 [ar2++] = .packer;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
.LnmppsCplxToReal_32fc_less32:
	with gr2 >>= 1;									// delay slot: gr2 = 16
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_32fc_less16;

	fpu 0 rep 16 vreg6 = [ar0++];					// 16 complex numbers

	// store Re parts
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu rep 8 [ar1++] = .packer;

	// store Im parts
	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu rep 8 [ar2++] = .packer;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
.LnmppsCplxToReal_32fc_less16:
	with gr2 >>= 1;									// delay slot: gr2 =  8
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_32fc_less8;

	fpu 0 rep 8 vreg6 = [ar0++];					// 8 complex numbers

	// store Re parts
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu rep 4 [ar1++] = .packer;

	// store Im parts
	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu rep 4 [ar2++] = .packer;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
.LnmppsCplxToReal_32fc_less8:
	with gr2 >>= 1;									// delay slot: gr2 =  4
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_32fc_less4;

	fpu 0 rep 4 vreg6 = [ar0++];					// 4 complex numbers

	// store Re parts
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu rep 2 [ar1++] = .packer;

	// store Im parts
	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu rep 2 [ar2++] = .packer;

	with gr0 -= gr2;
	if =0 delayed goto .LnmppsCplxToReal_32fc_return;
.LnmppsCplxToReal_32fc_less4:
	with gr2 >>= 1;									// delay slot: gr2 =  2
	with gr0 - gr2;									// delay slot

	if < goto .LnmppsCplxToReal_32fc_the_last_one;

	fpu 0 rep 2 vreg6 = [ar0++];					// 2 complex numbers

	// store Re parts
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu rep 1 [ar1++] = .packer;

	// store Im parts
	fpu 0 .packer = vreg6 with .float <= .float .in_high;
	fpu rep 1 [ar2++] = .packer;

	with gr0 -= gr2;
	if =0 goto .LnmppsCplxToReal_32fc_return;
.LnmppsCplxToReal_32fc_the_last_one:
	ar3, gr3 = [ar0++];								// read one complex number
													// ar3 == Re, gr3 == Im
	[ar1++] = ar3;
	[ar2++] = gr3;

.LnmppsCplxToReal_32fc_return:
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/
