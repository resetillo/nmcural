#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
// NOTE: it's possible to do some optimizations to increase the performance,
//       for example: unroll loops.
*/


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsSqr
//  Purpose:    Computes square of each element of source vector
//  Parameters:
//    pSrcDst          Pointer to the source and destination vector for in-place operations
//    pSrc             Pointer to the source vector
//    pDst             Pointer to the destination vector
//    len              Number of elements in the vector
//   scaleFactor       Scale factor
//  Return:
//    nmppsStsNullPtrErr     At least one of the pointers is NULL
//    nmppsStsSizeErr        Vectors' length is less than 1
//    nmppsStsNoErr          No error
*/

	.text

/**
 * @addtogroup ArithmeticGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsSqr_8u_Sfs(const nmpps8u* pSrc, nmpps8u* pDst, int len, int scaleFactor)
 *
 * @brief Вычисление квадрата каждого элемента вектора для типа nmpps8u c масштабированием.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 * @param[in] scaleFactor Масштаб.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_8u_Sfs: .globl _nmppsSqr_8u_Sfs
	ar5 = ar7 - 2 addr;
	push ar0, gr0;									// ar0,gr0 used to store args
	push ar1, gr1;									// ar1 used to store arg, gr1 is temp var
	push ar2, gr2;									// ar2,gr2 used for temp vars
	push ar3, gr3;									// ar3 used for item iteration, gr3 used to compare length
	push ar4, gr4;									// ar4,gr4 used to obtain shifting pair
	push ar6, gr6;									// ar6,gr6 used to choose a scale handler

	ar7 = ar7 + 256 addr; 							// allocate 128x2 words, stack grows up!

	ar1, gr1 = [--ar5];								// after read: __ ar1 == pDst __, gr1 == pSrc
	ar2, gr2 = [--ar5];								// after read: ar2 == scaleFactor, gr2 == len

	ar0 = gr1;										// __ ar0 == pSrc __
	nul;

	gr7 = nmppsStsNullPtrErr;
	ar5 = ar7 - 256 addr with gr1;					// ar5 == point to local vars

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return_err;
	gr1 = ar1 set;									// delay slot
	gr0 = gr2 with gr1;								// delay slot: __ gr0 == len __

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return_err;
	nul;											// delay slot
	gr6 = ar2 with gr0;								// delay slot: __ gr6 == scaleFactor __

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_8u_Sfs_return_err;
	gr7 = nmppsStsSizeErr;

	gr1 = 15;										// max value of positive scaleFactor, more is meaningless for 8-bits
	gr2 = -8;										// min value of negative scaleFactor, less is meaningless for 8-bits
	ar2 = nmppsSqr_8u_Sfs_FPCP_Settings;			// fixed point co-processor settings
	ar6 = Unsigned_Scale_Handlers_Table;			// table for scaling

	/* /////////////////////////////////////////////////////////////////////////////
	// IMPORTANT!
	//
	// The next code is COMMON part of nmppsSqr_8u_Sfs, nmppsSqr_16s_Sfs, nmppsSqr_16u_Sfs functions!
	//
	// The header of nmppsSqr_16s_Sfs, nmppsSqr_16u_Sfs functions MUST be same as in nmppsSqr_8u_Sfs,
	// except the next lines:
	//   1) << min/max value of scaleFactor >>;
	//   2) << fixed point co-processor settings >>;
	//   3) << table for scaling >>.
	*/

.LnmppsSqr_implementation_same_as_for_8u_Sfs:
	gr3 = gr6;										// temporarily save gr6 ...
	with gr6 - gr1;
	/*
	// analyze scaleFactor to choose handler {{{
	*/

	// if (scaleFactor > gr1) gr6 = 32;
	if > delayed goto .LnmppsSqr_8u_Sfs_choose_scale_handler with gr6 - gr2;
	gr6 = 32;										// delay slot (x2)

	// if (scaleFactor < gr2) gr6 = -31;
	if < delayed goto .LnmppsSqr_8u_Sfs_choose_scale_handler;
	gr6 = -31;										// delay slot (x2)

	// else gr6 is gr6 :)
	gr6 = gr3;										// ... and then restore

.LnmppsSqr_8u_Sfs_choose_scale_handler:
	gr1 = 31;										// the bias of the table
	// XXX: fatal error if gr6 is negative, so let's find handler through bias
	with gr6 += gr1;
	ar6 = [ar6 + gr6] with gr6 -= gr1;				// scale_handler(&x, shift) = Table[gr6 + 31];
	/*
	// }}}
	*/

	gr3 = 64;
	gr4 = 4;

	// read fixed point co-processor settings
	sir = [ar2++];
	f2cr = sir;
	sir = [ar2++];
	nb1 = sir;
	sir = [ar2++];
	sb = sir with gr0 - gr3;

	// try do for 64, 32, 16, 8, 4, 2, 1 elements ...
	if < delayed goto .LnmppsSqr_8u_Sfs_less64;
.LnmppsSqr_8u_Sfs_more_or_equal64:
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set; 									// ar5 == base for diagonal matrices 2x2, max 128 32-bit words

	// prepare low part of diagonal
	//
	// input    mask   output
	// H F D B >| 0 |> 0 . 0 . 0 . 0
	// G E C A >| F |> A . C . E . G ... and so on
	//
	rep 32 ram = [ar2], wtw;
	rep 32 data = [ar0++] with mask ram, data, 0;
	rep 32 [ar4++gr4] = afifo;

	ar0 = ar0 - 64 addr;							// start from the beginning
	ar4 = ar5 + 2 addr;

	ar2 = Mask_HI32;

	// prepare high part of diagonal
	//
	// input    mask   output
	// H F D B >| F |> . B . D . F . H
	// G E C A >| 0 |> . 0 . 0 . 0 . 0 ... and so on
	//
	// in the result getting matrices 2x2 to load them to wfifo:
	//
	// high |B 0| |D 0| |F 0| |H 0|
	// low  |0 A| |0 C| |0 E| |0 G| ... and so on
	//
	rep 32 ram = [ar2];
	rep 32 data = [ar0++] with mask ram, data, 0;
	rep 32 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 64 addr;
	ar3 = ar5 + 128 addr;							// ar5 + 128 == base for immediate results

	// multiply one vector by matrix 2x2
	//
	// input
	//     B x | B   0 |
	//     A   | 0   A |
	//           |   |
	//          B^2 A^2  <- output
	//
	.rept 32
	rep 2 wfifo = [ar4++], ftw;						// don't load all matrices to allow handlers use co-processor as well
	wtw;											// load matrices one by one
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 32 data = [ar3++] with vsum, 0, activate data;
	rep 32 [ar1++] = afifo;

	if > goto .LnmppsSqr_8u_Sfs_more_or_equal64;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return;
.LnmppsSqr_8u_Sfs_less64:
	with gr3 >>= 1;									// delay slot: gr3 == 32 (64/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_8u_Sfs_less32;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of diagonal
	rep 16 ram = [ar2];
	rep 16 data = [ar0++] with mask ram, data, 0;
	rep 16 [ar4++gr4] = afifo;

	ar0 = ar0 - 32 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Mask_HI32;

	// prepare high part of diagonal
	rep 16 ram = [ar2];
	rep 16 data = [ar0++] with mask ram, data, 0;
	rep 16 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 32 addr;
	ar3 = ar5 + 128 addr;

	.rept 16
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;
	ar3 = ar5 + 128 addr;							// restore ar5

	// saturate the end result
	rep 16 data = [ar3++] with vsum, 0, activate data;
	rep 16 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_8u_Sfs_return;
.LnmppsSqr_8u_Sfs_less32:
	with gr3 >>= 1; 								// delay slot: gr3 == 16 (32/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_8u_Sfs_less16;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of diagonal
	rep 8 ram = [ar2];
	rep 8 data = [ar0++] with mask ram, data, 0;
	rep 8 [ar4++gr4] = afifo;

	ar0 = ar0 - 16 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Mask_HI32;

	// prepare high part of diagonal
	rep 8 ram = [ar2];
	rep 8 data = [ar0++] with mask ram, data, 0;
	rep 8 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 16 addr;
	ar3 = ar5 + 128 addr;

	.rept 8
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 8 data = [ar3++] with vsum, 0, activate data;
	rep 8 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_8u_Sfs_return;
.LnmppsSqr_8u_Sfs_less16:
	with gr3 >>= 1; 								// delay slot: gr3 == 8 (16/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_8u_Sfs_less8;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of diagonal
	rep 4 ram = [ar2];
	rep 4 data = [ar0++] with mask ram, data, 0;
	rep 4 [ar4++gr4] = afifo;

	ar0 = ar0 - 8 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Mask_HI32;

	// prepare high part of diagonal
	rep 4 ram = [ar2];
	rep 4 data = [ar0++] with mask ram, data, 0;
	rep 4 [ar4++gr4] = afifo;

	gr1 = ar5 set;									// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 8 addr;
	ar3 = ar5 + 128 addr;

	.rept 4
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 4 data = [ar3++] with vsum, 0, activate data;
	rep 4 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_8u_Sfs_return;
.LnmppsSqr_8u_Sfs_less8:
	with gr3 >>= 1;									// delay slot: gr3 == 4 (8/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_8u_Sfs_less4;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of diagonal
	rep 2 ram = [ar2];
	rep 2 data = [ar0++] with mask ram, data, 0;
	rep 2 [ar4++gr4] = afifo;

	ar0 = ar0 - 4 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Mask_HI32;

	// prepare high part of diagonal
	rep 2 ram = [ar2];
	rep 2 data = [ar0++] with mask ram, data, 0;
	rep 2 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 4 addr;
	ar3 = ar5 + 128 addr;

	.rept 2
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 2 data = [ar3++] with vsum, 0, activate data;
	rep 2 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_8u_Sfs_return;
.LnmppsSqr_8u_Sfs_less4:
	with gr3 >>= 1;									// delay slot: gr3 == 2 (4/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_8u_Sfs_the_last_one;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of diagonal
	rep 1 ram = [ar2];
	rep 1 data = [ar0++] with mask ram, data, 0;
	rep 1 [ar4++gr4] = afifo;

	ar0 = ar0 - 2 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Mask_HI32;

	// prepare high part of diagonal
	rep 1 ram = [ar2];
	rep 1 data = [ar0++] with mask ram, data, 0;
	rep 1 [ar4++gr4] = afifo;

	ar4 = ar5 addr;
	ar0 = ar0 - 2 addr;
	ar3 = ar5 + 128 addr;

	gr1 = ar5;										// save ar5
	rep 2 wfifo = [ar4++], ftw, wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 1 data = [ar3++] with vsum, 0, activate data;
	rep 1 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_8u_Sfs_return;
.LnmppsSqr_8u_Sfs_the_last_one:
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set with gr3 = gr0 noflags;

	// prepare low part of diagonal
	rep 1 ram = [ar2];
	rep 1 data = [ar0++] with mask ram, data, 0;
	rep 1 [ar4++gr4] = afifo;

	ar0 = ar0 - 2 addr;
	ar4 = ar5 + 2 addr;

	// prepare high part of diagonal
	rep 1 with 0 + 0;
	rep 1 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5
	ar4 = ar5 addr;

	ar3 = ar5 + 128 addr;

	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)

	ar5 = gr1;
	ar3 = ar5 + 128 addr;
	ar4 = ar3 + 2 addr;

	// saturate the end result
	rep 1 data = [ar3] with vsum, 0, activate data;
	rep 1 [ar4] = afifo;

	gr2 = [ar4];
	[ar1++] = gr2;

.LnmppsSqr_8u_Sfs_return:
	gr7 = nmppsStsNoErr;

.LnmppsSqr_8u_Sfs_return_err:
	ar7 = ar7 - 256 addr;
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsSqr_16s_Sfs(const nmpps16s* pSrc, nmpps16s* pDst, int len, int scaleFactor)
 *
 * @brief Вычисление квадрата каждого элемента вектора для типа nmpps16s c масштабированием.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 * @param[in] scaleFactor Масштаб.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_16s_Sfs: .globl _nmppsSqr_16s_Sfs
	ar5 = ar7 - 2 addr;
	push ar0, gr0;									// ar0,gr0 used to store args
	push ar1, gr1;									// ar1 used to store arg, gr1 is temp var
	push ar2, gr2;									// ar2,gr2 used for temp vars
	push ar3, gr3;									// ar3 used for item iteration, gr3 used to compare length
	push ar4, gr4;									// ar4,gr4 used to obtain shifting pair
	push ar6, gr6;									// ar6,gr6 used to choose a scale handler

	ar7 = ar7 + 256 addr; 							// allocate 128x2 words, stack grows up!

	ar1, gr1 = [--ar5];								// after read: __ ar1 == pDst __, gr1 == pSrc
	ar2, gr2 = [--ar5];								// after read: ar2 == scaleFactor, gr2 == len

	ar0 = gr1;										// __ ar0 == pSrc __
	nul;

	gr7 = nmppsStsNullPtrErr;
	ar5 = ar7 - 256 addr with gr1;					// ar5 == point to local vars

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return_err;
	gr1 = ar1 set;									// delay slot
	gr0 = gr2 with gr1;								// delay slot: __ gr0 == len __

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return_err;
	nul;											// delay slot
	gr6 = ar2 with gr0;								// delay slot: __ gr6 == scaleFactor __

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_8u_Sfs_return_err;
	gr7 = nmppsStsSizeErr;

	gr1 = 31;										// max value of positive scaleFactor, more is meaningless for 16-bits
	gr2 = -14;										// min value of negative scaleFactor, less is meaningless for 16-bits
	ar2 = nmppsSqr_16s_Sfs_FPCP_Settings;			// fixed point co-processor settings
	ar6 = Unsigned_Scale_Handlers_Table;

	goto .LnmppsSqr_implementation_same_as_for_8u_Sfs;


/**
 * @fn nmppsStatus nmppsSqr_16u_Sfs(const nmpps16u* pSrc, nmpps16u* pDst, int len, int scaleFactor)
 *
 * @brief Вычисление квадрата каждого элемента вектора для типа nmpps16u c масштабированием.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 * @param[in] scaleFactor Масштаб.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_16u_Sfs: .globl _nmppsSqr_16u_Sfs
	ar5 = ar7 - 2 addr;
	push ar0, gr0;									// ar0,gr0 used to store args
	push ar1, gr1;									// ar1 used to store arg, gr1 is temp var
	push ar2, gr2;									// ar2,gr2 used for temp vars
	push ar3, gr3;									// ar3 used for item iteration, gr3 used to compare length
	push ar4, gr4;									// ar4,gr4 used to obtain shifting pair
	push ar6, gr6;									// ar6,gr6 used to choose a scale handler

	ar7 = ar7 + 256 addr; 							// allocate 128x2 words, stack grows up!

	ar1, gr1 = [--ar5];								// after read: __ ar1 == pDst __, gr1 == pSrc
	ar2, gr2 = [--ar5];								// after read: ar2 == scaleFactor, gr2 == len

	ar0 = gr1;										// __ ar0 == pSrc __
	nul;

	gr7 = nmppsStsNullPtrErr;
	ar5 = ar7 - 256 addr with gr1;					// ar5 == point to local vars

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return_err;
	gr1 = ar1 set;									// delay slot
	gr0 = gr2 with gr1;								// delay slot: __ gr0 == len __

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_8u_Sfs_return_err;
	nul;											// delay slot
	gr6 = ar2 with gr0;								// delay slot: __ gr6 == scaleFactor __

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_8u_Sfs_return_err;
	gr7 = nmppsStsSizeErr;

	gr1 = 31;										// max value of positive scaleFactor, more is meaningless for 16-bits
	gr2 = -15;										// min value of negative scaleFactor, less is meaningless for 16-bits
	ar2 = nmppsSqr_16u_Sfs_FPCP_Settings;			// fixed point co-processor settings
	ar6 = Unsigned_Scale_Handlers_Table;

	goto .LnmppsSqr_implementation_same_as_for_8u_Sfs;


/**
 * @fn nmppsStatus nmppsSqr_32f(const nmpps32f* pSrc, nmpps32f* pDst, int len)
 *
 * @brief Вычисление квадрата каждого элемента вектора для типа nmpps32f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_32f: .globl _nmppsSqr_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// after read: ar1 == pDst, gr1 == pSrc
	ar0 = gr1 set with gr1;							// ar0 == pSrc

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_32f_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_32f_return with gr0;
	gr1 = 64; 										// delay slot (x2)

	gr7 = nmppsStsSizeErr;

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_32f_return with gr2 = gr0 >> 1;
	with gr2 = gr2 << 1;							// delay slot: gr0 ==  odd length
	with gr2;										// delay slot: gr2 == even length

	// if even length is 0 then odd length is 1
	if =0 delayed goto .LnmppsSqr_32f_the_last_one with gr7 = nmppsStsNoErr noflags;
	nul;
	with gr2 - gr1;

	// if (len < 64) ...
	if < goto .LnmppsSqr_32f_remainder;

.LnmppsSqr_32f_loop:
	// one iteration allows to take 64 floats for calculation
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 .float vreg0 = vreg0 * vreg0;
	fpu 0 rep 32 [ar1++] = vreg0;

	with gr2 -= gr1 noflags;
	with gr2 - gr1;
	if > goto .LnmppsSqr_32f_loop with gr0 -= gr1;

.LnmppsSqr_32f_remainder:
	if =0 delayed goto .LnmppsSqr_32f_return with gr1 = gr2 >> 1;
	with gr1 = gr1 - 1 noflags;						// delay slot
	vlen = gr1 set with gr0 -= gr2;					// delay slot

	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .float vreg0 = vreg0 * vreg0;
	fpu 0 rep vlen [ar1++] = vreg0;

	if =0 goto .LnmppsSqr_32f_return;

.LnmppsSqr_32f_the_last_one:
	ar7 = ar7 + 2 addr;								// reserve 2 words in stack for aligned store
	ar5 = ar7 - 2 addr;

	fpu 0 rep 1 vreg0 = [ar0];						// LSB of vreg0 stores a source number
	fpu 0 .float vreg0 = vreg0 * vreg0;
	fpu 0 rep 1 [ar5] = vreg0;

	pop ar2, gr2;									// ar2 is LSB of vreg0
	[ar1] = ar2;

.LnmppsSqr_32f_return:
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsSqr_64f(const nmpps64f* pSrc, nmpps64f* pDst, int len)
 *
 * @brief Вычисление квадрата каждого элемента вектора для типа nmpps64f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_64f: .globl _nmppsSqr_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// ar1 == pDst, gr1 == pSrc
	ar0 = gr1 with gr1;								// ar0 == pSrc

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_64f_return;
	gr1 = ar1;										// delay slot
	gr0 = [--ar5] with gr1;							// gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_64f_return with gr0;
	gr1 = 32;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_64f_return with gr0 - gr1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	// if (len < 32) ...
	if < goto .LnmppsSqr_64f_remainder with gr7 = nmppsStsNoErr noflags;

.LnmppsSqr_64f_loop:
	// one iteration allows to take 32 doubles for calculation
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 .double vreg0 = vreg0 * vreg0;
	fpu 0 rep 32 [ar1++] = vreg0;

	with gr0 -= gr1 noflags;
	with gr0 - gr1;
	if > goto .LnmppsSqr_64f_loop;

	if =0 delayed goto .LnmppsSqr_64f_return;
.LnmppsSqr_64f_remainder:
	with gr1 = gr0 - 1 noflags;						// delay slot
	vlen = gr1 set;									// delay slot

	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .double vreg0 = vreg0 * vreg0;
	fpu 0 rep vlen [ar1++] = vreg0;

.LnmppsSqr_64f_return:
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/* /////////////////////////////////////////////////////////////////////////////
// Complex numbers
//
// (re + im*i)^2 = re^2 + 2re*im*i + (im*i)^2
// re^2 = re^2 - im^2
// im^2 = 2re*im
*/


/**
 * @fn nmppsStatus nmppsSqr_16sc_Sfs(const nmpps16sc* pSrc, nmpps16sc* pDst, int len, int scaleFactor)
 *
 * @brief Вычисление квадрата каждого элемента вектора для комплексного типа nmpps16sc c масштабированием.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 * @param[in] scaleFactor Масштаб.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_16sc_Sfs: .globl _nmppsSqr_16sc_Sfs
	ar5 = ar7 - 2 addr;
	push ar0, gr0;									// ar0,gr0 used to store args
	push ar1, gr1;									// ar1 used to store arg, gr1 is temp var
	push ar2, gr2;									// ar2,gr2 used for temp vars
	push ar3, gr3;									// ar3 used for item iteration, gr3 used to compare length
	push ar4, gr4;									// ar4,gr4 used to obtain shifting pair
	push ar6, gr6;									// ar6,gr6 used to choose a scale handler

	ar7 = ar7 + 256 addr; 							// allocate 128x2 words, stack grows up!

	ar1, gr1 = [--ar5];								// after read: __ ar1 == pDst __, gr1 == pSrc
	ar2, gr2 = [--ar5];								// after read: ar2 == scaleFactor, gr2 == len

	ar0 = gr1;										// __ ar0 == pSrc __
	nul;

	gr7 = nmppsStsNullPtrErr;
	ar5 = ar7 - 256 addr with gr1;					// ar5 == point to local vars

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return_err;
	gr1 = ar1 set;									// delay slot
	gr0 = gr2 with gr1;								// delay slot: __ gr0 == len __

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return_err;
	nul;											// delay slot
	gr6 = ar2 with gr0;								// delay slot: __ gr6 == scaleFactor __

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_16sc_Sfs_return_err;
	gr7 = nmppsStsSizeErr;

	gr1 = 31;												// max value of positive scaleFactor, more is meaningless for 16-bits
	gr2 = -31;												// min value of negative scaleFactor, less is meaningless for 16-bits
	ar2 = nmppsSqr_16sc_Sfs_FPCP_Settings with gr3 = gr6;	// fixed point co-processor settings, temporarily save gr6
	ar6 = Signed_Scale_Handlers_Table with gr6 - gr1;		// table for scaling

	/*
	// analyze scaleFactor to choose handler {{{
	*/

	// if (scaleFactor > gr1) gr6 = 32;
	if > delayed goto .LnmppsSqr_16sc_Sfs_choose_scale_handler with gr6 - gr2;
	gr6 = 32;										// delay slot (x2)

	// if (scaleFactor < gr2) gr6 = -31;
	if < delayed goto .LnmppsSqr_16sc_Sfs_choose_scale_handler;
	gr6 = -31;										// delay slot (x2)

	// else gr6 is gr6 :)
	gr6 = gr3;										// ... and then restore

.LnmppsSqr_16sc_Sfs_choose_scale_handler:
	gr1 = 31;										// the bias of the table
	// XXX: fatal error if gr6 is negative, so let's find handler through bias
	with gr6 += gr1;
	ar6 = [ar6 + gr6] with gr6 -= gr1;				// scale_handler(&x, shift) = Table[gr6 + 31];
	/*
	// }}}
	*/

	gr3 = 32;
	gr4 = 4;

	// read fixed point co-processor settings
	sir = [ar2++];
	f2cr = sir;
	sir = [ar2++];
	nb1 = sir;
	sir = [ar2++];
	sb = sir with gr0 - gr3;

	// try do for 32, 16, 8, 4, 2, 1 complex numbers ...
	if < delayed goto .LnmppsSqr_16sc_Sfs_less32;
.LnmppsSqr_16sc_Sfs_more_or_equal32:
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set; 									// ar5 == base for diagonal matrices 2x2, max 128 32-bit words

	// prepare low part of Re
	//
	// input    mask   output
	// H F D B >| 0 |> 0 . 0 . 0 . 0 (high32)
	// G E C A >| F |> A . C . E . G (low32) ... and so on
	//
	rep 32 ram = [ar2], wtw;
	rep 32 data = [ar0++] with mask ram, data, 0;
	rep 32 [ar4++gr4] = afifo;

	ar0 = ar0 - 64 addr;							// start from the beginning
	ar4 = ar5 + 2 addr;

	ar2 = Matrix2x2_2re_minus_im;

	// prepare high part of pair 2re and -im, thus:
	//
	// input    matrix
	// H F D B >| 0 -1 |
	// G E C A >| 2  0 |
	//          -------- output
	//            .  . :0
	//           2A -B :1
	//            .  . :2
	//           2C -D :3
	//           ... and so on
	rep 2 wfifo = [ar2++], ftw, wtw;
	rep 32 data = [ar0++] with vsum, data, 0;
	rep 32 [ar4++gr4] = afifo;

	// in the result getting matrices 2x2 to load them to wfifo:
	//
	// high |2A -B| |2C -D| |2E -F| |2G -H|
	// low  |0   A| |0   C| |0   E| |0   G| ... and so on
	//

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 64 addr;
	ar3 = ar5 + 128 addr;							// ar5 + 128 == base for immediate results

	// multiply one vector by matrix 2x2
	//
	// input
	//     B x | 2A       -B |
	//     A   | 0         A |
	//           |         |
	//      Im: 2AB Re: A^2-B^2  <- output
	//
	.rept 32
	rep 2 wfifo = [ar4++], ftw;						// don't load all matrices to allow handlers use co-processor as well
	wtw;											// load matrices one by one
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 32 data = [ar3++] with vsum, 0, activate data;
	rep 32 [ar1++] = afifo;

	if > goto .LnmppsSqr_16sc_Sfs_more_or_equal32;
	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return;
.LnmppsSqr_16sc_Sfs_less32:
	with gr3 >>= 1;									// delay slot: gr3 == 16 (32/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_16sc_Sfs_less16;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of re
	rep 16 ram = [ar2];
	rep 16 data = [ar0++] with mask ram, data, 0;
	rep 16 [ar4++gr4] = afifo;

	ar0 = ar0 - 32 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Matrix2x2_2re_minus_im;

	// prepare high part of pair 2re, -im
	rep 2 wfifo = [ar2++], ftw, wtw;
	rep 16 data = [ar0++] with vsum, data, 0;
	rep 16 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 32 addr;
	ar3 = ar5 + 128 addr;

	.rept 16
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;
	ar3 = ar5 + 128 addr;							// restore ar5

	// saturate the end result
	rep 16 data = [ar3++] with vsum, 0, activate data;
	rep 16 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return;
.LnmppsSqr_16sc_Sfs_less16:
	with gr3 >>= 1; 								// delay slot: gr3 == 8 (16/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_16sc_Sfs_less8;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of re
	rep 8 ram = [ar2];
	rep 8 data = [ar0++] with mask ram, data, 0;
	rep 8 [ar4++gr4] = afifo;

	ar0 = ar0 - 16 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Matrix2x2_2re_minus_im;

	// prepare high part of 2re, -im
	rep 2 wfifo = [ar2++], ftw, wtw;
	rep 8 data = [ar0++] with vsum, data, 0;
	rep 8 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 16 addr;
	ar3 = ar5 + 128 addr;

	.rept 8
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 8 data = [ar3++] with vsum, 0, activate data;
	rep 8 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return;
.LnmppsSqr_16sc_Sfs_less8:
	with gr3 >>= 1; 								// delay slot: gr3 == 4 (8/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_16sc_Sfs_less4;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of re
	rep 4 ram = [ar2];
	rep 4 data = [ar0++] with mask ram, data, 0;
	rep 4 [ar4++gr4] = afifo;

	ar0 = ar0 - 8 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Matrix2x2_2re_minus_im;

	// prepare high part of pair 2re, -im
	rep 2 wfifo = [ar2++], ftw, wtw;
	rep 4 data = [ar0++] with vsum, data, 0;
	rep 4 [ar4++gr4] = afifo;

	gr1 = ar5 set;									// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 8 addr;
	ar3 = ar5 + 128 addr;

	.rept 4
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 4 data = [ar3++] with vsum, 0, activate data;
	rep 4 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return;
.LnmppsSqr_16sc_Sfs_less4:
	with gr3 >>= 1;									// delay slot: gr3 == 2 (4/2)
	with gr0 - gr3;									// delay slot

	if < delayed goto .LnmppsSqr_16sc_Sfs_the_last_one;
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set;

	// prepare low part of re
	rep 2 ram = [ar2];
	rep 2 data = [ar0++] with mask ram, data, 0;
	rep 2 [ar4++gr4] = afifo;

	ar0 = ar0 - 4 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Matrix2x2_2re_minus_im;

	// prepare high part of pair 2re, -im
	rep 2 wfifo = [ar2++], ftw, wtw;
	rep 2 data = [ar0++] with vsum, data, 0;
	rep 2 [ar4++gr4] = afifo;

	gr1 = ar5;										// save ar5

	ar4 = ar5 addr;
	ar0 = ar0 - 4 addr;
	ar3 = ar5 + 128 addr;

	.rept 2
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)
	.endr

	ar5 = gr1 with gr0 -= gr3;						// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 2 data = [ar3++] with vsum, 0, activate data;
	rep 2 [ar1++] = afifo;

	if =0 delayed goto .LnmppsSqr_16sc_Sfs_return;
.LnmppsSqr_16sc_Sfs_the_last_one:
	ar2 = Mask_LO32;								// delay slot (x2)

	ar4 = ar5 set with gr3 = gr0 noflags;

	// prepare low part of re
	rep 1 ram = [ar2];
	rep 1 data = [ar0++] with mask ram, data, 0;
	rep 1 [ar4++gr4] = afifo;

	ar0 = ar0 - 2 addr;
	ar4 = ar5 + 2 addr;

	ar2 = Matrix2x2_2re_minus_im;

	// prepare high part of pair 2re, -im
	rep 2 wfifo = [ar2++], ftw, wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar4++gr4] = afifo;

	ar4 = ar5 addr;
	ar0 = ar0 - 2 addr;
	ar3 = ar5 + 128 addr;

	gr1 = ar5;										// save ar5
	rep 2 wfifo = [ar4++], ftw, wtw;
	rep 1 data = [ar0++] with vsum, data, 0;
	rep 1 [ar3++] = afifo;
	delayed call ar6 + 0;							// invoke scale handler (MUST BE ALIGNED!), do `+ 0' to remove one delay slot
	ar2 = ar3 - 2 addr with gr2 = gr6;				// delay slot (x2)

	ar5 = gr1;										// restore ar5
	ar3 = ar5 + 128 addr;

	// saturate the end result
	rep 1 data = [ar3++] with vsum, 0, activate data;
	rep 1 [ar1++] = afifo;

.LnmppsSqr_16sc_Sfs_return:
	gr7 = nmppsStsNoErr;

.LnmppsSqr_16sc_Sfs_return_err:
	ar7 = ar7 - 256 addr;
	pop ar6, gr6;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsSqr_32fc(const nmpps16sc* pSrc, nmpps16sc* pDst, int len)
 *
 * @brief Вычисление квадрата каждого элемента вектора для комплексного типа nmpps32fc.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_32fc: .globl _nmppsSqr_32fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5];								// ar1 == pDst, gr1 == pSrc
	ar0 = gr1 set with gr1;							// ar0 == pSrc

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_32fc_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_32fc_return with gr0;
	gr1 = 32;										// delay slot (x2)

	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_32fc_return with gr0 - gr1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	// if (len < 32) ...
	if < goto .LnmppsSqr_32fc_remainder with gr7 = nmppsStsNoErr noflags;

.LnmppsSqr_32fc_loop:
	// one iteration allows to take 32 complex numbers (float) for calculation
	fpu rep 32 .packer = [ar0++] with .double <= .float;
	fpu 0 rep 32 (vreg0,vreg1) = .packer;

	fpu 0 .double vreg2 = vreg1 * vreg1;			// vreg2 = im^2
	fpu 0 .double vreg3 = vreg0 * vreg1;			// vreg3 = re * im
	fpu 0 .double vreg4 = vreg0 * vreg0 - vreg2;	// vreg4 = re^2 - im^2   (Re)
	fpu 0 .double vreg5 = vreg3 + vreg3;			// vreg5 = 2.0 * re * im (Im)

	fpu 0 .packer = (vreg4,vreg5) with .float <= .double;
	fpu rep 32 [ar1++] = .packer;

	with gr0 -= gr1;
	with gr0 - gr1;

	if > goto .LnmppsSqr_32fc_loop with gr0;

	if =0 delayed goto .LnmppsSqr_32fc_return;
.LnmppsSqr_32fc_remainder:
	with gr0 = gr0 - 1 noflags;						// delay slot
	vlen = gr0;										// delay slot

	fpu rep vlen .packer = [ar0++] with .double <= .float;
	fpu 0 rep vlen (vreg0, vreg1) = .packer;

	fpu 0 .double vreg2 = vreg1 * vreg1;			// vreg2 = im^2
	fpu 0 .double vreg3 = vreg0 * vreg1;			// vreg3 = re * im
	fpu 0 .double vreg4 = vreg0 * vreg0 - vreg2;	// vreg4 = re^2 - im^2   (Re)
	fpu 0 .double vreg5 = vreg3 + vreg3;			// vreg5 = 2.0 * re * im (Im)

	fpu 0 .packer = (vreg4,vreg5) with .float <= .double;
	fpu rep vlen [ar1++] = .packer;

.LnmppsSqr_32fc_return:
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/*
// }
*/


/**
 * @fn nmppsStatus nmppsSqr_64fc(const nmpps64fc* pSrc, nmpps64fc* pDst, int len)
 *
 * @brief Вычисление квадрата каждого элемента вектора для комплексного типа nmpps64fc.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[out] pDst Получаемый вектор.
 * @param[in] len Размер вектора.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsSqr_64fc: .globl _nmppsSqr_64fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;

	gr7 = nmppsStsNullPtrErr;

	ar1, gr1 = [--ar5]; 							// ar1 == pDst, gr1 == pSrc
	ar0 = gr1 with gr1;

	// if (pSrc == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_64fc_return;
	gr1 = ar1 set;									// delay slot
	gr0 = [--ar5] with gr1;							// delay slot: gr0 == len

	// if (pDst == 0) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsSqr_64fc_return with gr0;
	gr1 = 32;										// delay slot (x2)

	// the length has been multipled by 2 in order to load a pair of doubles (Re and Im parts)
	// if (len <= 0) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsSqr_64fc_return with gr0 <<= 1;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	with gr0 - gr1;

	if < goto .LnmppsSqr_64fc_remainder with gr7 = nmppsStsNoErr noflags;

.LnmppsSqr_64fc_loop:
	// one iteration allows to take 16 complex numbers (double) for calculation
	fpu rep 32 .packer = [ar0++] with .double <= .double;
	// rep is divided by 2 cause 32 doubles are going to 2 vectors (Re vector, Im vector)
	fpu 0 rep 16 (vreg0,vreg1) = .packer; 			// vreg0 = re
													// vreg1 = im
	fpu 0 .double vreg2 = vreg1 * vreg1;			// vreg2 = im^2
	fpu 0 .double vreg3 = vreg0 * vreg1;			// vreg3 = re*im
	fpu 0 .double vreg4 = vreg0 * vreg0 - vreg2;	// vreg4 = re^2 - im^2 (Re)
	fpu 0 .double vreg5 = vreg3 + vreg3;			// vreg5 = 2.0*re*im   (Im)

	fpu 0 .packer = (vreg4,vreg5) with .double <= .double;
	fpu rep 32 [ar1++] = .packer;

	with gr0 -= gr1 noflags;
	with gr0 - gr1;

	// while (len > 32)
	if > goto .LnmppsSqr_64fc_loop with gr0;
	// if (len == 0) return nmppsStsNoErr;
	if =0 delayed goto .LnmppsSqr_64fc_return;

.LnmppsSqr_64fc_remainder:
	with gr0 = gr0 - 1;
	vlen = gr0 with gr1 = gr0 >> 1;

	fpu rep vlen .packer = [ar0++] with .double <= .double;

	vlen = gr1;

	fpu 0 rep vlen (vreg0, vreg1) = .packer;
	fpu 0 .double vreg2 = vreg1 * vreg1;			// vreg2 = im^2
	fpu 0 .double vreg3 = vreg0 * vreg1;			// vreg3 = re*im
	fpu 0 .double vreg4 = vreg0 * vreg0 - vreg2;	// vreg4 = re^2 - im^2 (Re)
	fpu 0 .double vreg5 = vreg3 + vreg3;			// vreg5 = 2.0*re*im   (Im)

	vlen = gr0;

	fpu 0 .packer = (vreg4,vreg5) with .double <= .double;
	fpu rep vlen [ar1++] = .packer;

.LnmppsSqr_64fc_return:
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */


/* /////////////////////////////////////////////////////////////////////////////
// Module constants
*/

	.text
	.align 2

Mask_LO32:
	.quad 0x00000000FFFFFFFF
Mask_HI32:
	.quad 0xFFFFFFFF00000000

Matrix2x2_2re_minus_im:
	.quad 0x0000000200000000 // 0: 2  0
	.quad 0x00000000FFFFFFFF // 1: 0 -1

nmppsSqr_8u_Sfs_FPCP_Settings:
	.quad 0xFFFFFF00FFFFFF00
	.quad 0x8000000080000000
	.quad 0x0000000300000003

nmppsSqr_16sc_Sfs_FPCP_Settings:
nmppsSqr_16s_Sfs_FPCP_Settings:
	.quad 0xFFFF8000FFFF8000
	.quad 0x8000000080000000
	.quad 0x0000000300000003

nmppsSqr_16u_Sfs_FPCP_Settings:
	.quad 0xFFFF0000FFFF0000
	.quad 0x8000000080000000
	.quad 0x0000000300000003

Unsigned_Scale_Handlers_Table:
	.rept 31
	.int Scale_Handler_Left_Shift_Unsigned
	.endr
	.int Scale_Handler_Left_Shift_Unsigned
	.rept 31
	.int Scale_Handler_Right_Shift_Unsigned
	.endr
	.int Scale_Handler_Wipe_Bits

Signed_Scale_Handlers_Table:
	.rept 31
	.int Scale_Handler_Left_Shift_Signed
	.endr
	.int Scale_Handler_Left_Shift_Signed
	.rept 31
	.int Scale_Handler_Right_Shift_Signed
	.endr
	.int Scale_Handler_Right_Shift_Signed
