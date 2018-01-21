#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsMean
//  Purpose:    compute average value of all elements of the source vector
//  Parameters:
//   pSrc                pointer to the source vector
//   pMean               pointer to the result
//   len                 length of the source vector
//   scaleFactor         scale factor value
//  Return:
//   nmppsStsNullPtrErr       pointer(s) to the vector or the result is NULL
//   nmppsStsSizeErr          length of the vector is less or equal 0
//   nmppsStsNoErr            otherwise
*/

	.text


/**
 * @addtogroup StatisticalGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsMean_16s_Sfs(const nmpps16s*  pSrc, int len, nmpps16s*  pMean, int scaleFactor)
 *
 * @brief Вычисление среднего значения элементов вектора типа nmpps16s с масштабированием.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMean Среднее значение.
 * @param[in] scaleFactor Масштаб.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMean_16s_Sfs: .globl _nmppsMean_16s_Sfs
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar6, gr6;

	ar6 = ar7;
	ar7 = ar7 + 64;									// allocate buffer[64] : int32_t

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	ar2, gr2 = [--ar5] with gr1;					//             ar2 == scaleFactor, gr2 == pMean

	if =0 delayed goto .LnmppsMean_16s_Sfs_return with gr2;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsMean_16s_Sfs_return;
	gr0 = ar1;										// delay slot
	ar0 = gr1 with gr0;								// delay slot

	if <= delayed goto .LnmppsMean_16s_Sfs_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	sir = 0;
	vr = sir;										// vr is accumulator

	sir = [nmppsMean_16s_Sfs_Conf_One_Column];		// we need only one column
	nb1 = sir;

	sir = [nmppsMean_16s_Sfs_Conf_Saturation];
	f2cr = sir;

	gr6 = 64;										// process 64 elements

	ar1 = gr2 with gr3 = gr0;
	gr1 = ar2 with gr0 - gr6;

	// Used registers:
	// ===============
	// ar0 == pSrc
	// gr0 == len (variable)
	// ar1 == pMean
	// gr1 == scaleFactor
	// ar2, gr2 == temp
	// gr3 == len (const)
	// ar6 == buffer pointer
	// gr6 == len comparator

	// if (len < 64) do for 32;
	if < delayed goto .LnmppsMean_16s_Sfs_less64;
	ar5 = nmppsMean_16s_Sfs_Big_Sum_Vector;			// delay slot (x2)

	sir = 0x00000002;
	sb  = sir;										// 2 lines

	//
	// W = | 1 |
	//     | 1 |
	rep 2 wfifo = [ar5], ftw, wtw;
	rep 32 with 0; 									// zero out afifo for accumulation

.LnmppsMean_16s_Sfs_more_than_64:
	//
	//                   +-----+
	//               Y   |     |
	//                   V     |
	//                   ..    |
	//                   EF    |
	//                   CD    |
	// 32 .. 2 1 0       AB    |
	//                  VVV    |
	//  n .. e c a | x | 1 |   |
	//  m .. f d b |   | 1 |   |
	//                  VVV    |
	//                0: AB    | -( AB = AB + (a * 1 + b * 1) )
	//      X         1: CD    |
	//                2: EF    |
	//                   ..    |
	//               32: NM ---+
	//
	rep 32 data = [ar0++] with vsum, data, afifo;

	with gr0 -= gr6;
	with gr0 - gr6;
	if > goto .LnmppsMean_16s_Sfs_more_than_64;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 32 [ar5++] = afifo;							// save afifo into buffer

	sir = 0xAAAAAAAA;								// 32 lines
	sb  = sir;

	ar5 = ar6;										// ar5 = &buffer[0];

	//
	// W = | AB | 0
	//     | CD | 1
	//     | EF | 2
	//     | .. | ..
	//     | NM | 32
	//
	rep 32 wfifo = [ar5++], ftw, wtw;				// wfifo := afifo

	ar5 = nmppsMean_16s_Sfs_Little_Sum_Vector_32;

	//
	//     |  1 | x | AB |  0
	//     |  1 |   | CD |  1
	//     |  1 |   | EF |  2
	//     | .. |   | .. | ..
	//     |  1 |   | NM | 32
	//               VVVV
	//  S = AB + CD + EF + .. + NM + vr
	//

	rep 1 data = [ar5] with vsum, data, vr;			// final sum of all elements
	rep 1 [ar6] = afifo;

	vr = [ar6] with gr0;							// save immediate sum in accumulator (vr)

	if =0 delayed goto .LnmppsMean_16s_Sfs_get_average;
.LnmppsMean_16s_Sfs_less64:
	with gr6 >>= 1;									// delay slot: gr6 = 32
	with gr0 - gr6;									// delay slot

	if < delayed goto .LnmppsMean_16s_Sfs_less32;
	ar5 = nmppsMean_16s_Sfs_Big_Sum_Vector;			// delay slot (x2)

	sir = 0x00000002;
	sb  = sir;										// 2 lines

	rep 2 wfifo = [ar5], ftw, wtw;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 16 data = [ar0++] with vsum, data, 0;
	rep 16 [ar5++] = afifo;							// save afifo into buffer

	sir = 0x22222222;
	sb  = sir;										// 16 lines

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 16 wfifo = [ar5++], ftw, wtw;

	ar5 = nmppsMean_16s_Sfs_Little_Sum_Vector_16;
	rep 1 data = [ar5] with vsum, data, vr;			// final sum of all elements

	rep 1 [ar6] = afifo;
	vr = [ar6] with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_16s_Sfs_get_average;
.LnmppsMean_16s_Sfs_less32:
	with gr6 >>= 1;									// delay slot: gr6 = 16
	with gr0 - gr6;									// delay slot

	if < delayed goto .LnmppsMean_16s_Sfs_less16;
	ar5 = nmppsMean_16s_Sfs_Big_Sum_Vector;			// delay slot (x2)

	sir = 0x00000002;
	sb  = sir;										// 2 lines

	rep 2 wfifo = [ar5], ftw, wtw;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 8 data = [ar0++] with vsum, data, 0;
	rep 8 [ar5++] = afifo;							// save afifo into buffer

	sir = 0x02020202;								// 8 lines
	sb  = sir;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 8 wfifo = [ar5++], ftw, wtw;

	ar5 = nmppsMean_16s_Sfs_Little_Sum_Vector_8;
	rep 1 data = [ar5] with vsum, data, vr;			// final sum of all elements

	rep 1 [ar6] = afifo;
	vr = [ar6] with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_16s_Sfs_get_average;
.LnmppsMean_16s_Sfs_less16:
	with gr6 >>= 1;									// delay slot: gr6 =  8
	with gr0 - gr6;									// delay slot

	if < delayed goto .LnmppsMean_16s_Sfs_less8;
	ar5 = nmppsMean_16s_Sfs_Big_Sum_Vector;			// delay slot (x2)

	sir = 0x00000002;
	sb  = sir;										// 2 lines

	rep 2 wfifo = [ar5], ftw, wtw;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 4 data = [ar0++] with vsum, data, 0;
	rep 4 [ar5++] = afifo;							// save afifo into buffer

	sir = 0x00020002;								// 4 lines
	sb  = sir;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 4 wfifo = [ar5++], ftw, wtw;

	ar5 = nmppsMean_16s_Sfs_Little_Sum_Vector_4;
	rep 1 data = [ar5] with vsum, data, vr;			// final sum of all elements

	rep 1 [ar6] = afifo;
	vr = [ar6] with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_16s_Sfs_get_average;
.LnmppsMean_16s_Sfs_less8:
	with gr6 >>= 1;									// delay slot: gr6 =  4
	with gr0 - gr6;									// delay slot

	if < delayed goto .LnmppsMean_16s_Sfs_less4;
	ar5 = nmppsMean_16s_Sfs_Big_Sum_Vector;			// delay slot (x2)

	sir = 0x00000002;
	sb  = sir;										// 2 lines

	rep 2 wfifo = [ar5], ftw, wtw;

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 2 data = [ar0++] with vsum, data, 0;
	rep 2 [ar5++] = afifo;							// save afifo into buffer

	ar5 = ar6;										// ar5 = &buffer[0];

	rep 2 wfifo = [ar5++], ftw, wtw;

	ar5 = nmppsMean_16s_Sfs_Little_Sum_Vector_2;
	rep 1 data = [ar5] with vsum, data, vr;			// final sum of all elements

	rep 1 [ar6] = afifo;
	vr = [ar6] with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_16s_Sfs_get_average;
.LnmppsMean_16s_Sfs_less4:
	with gr6 >>= 1;									// delay slot: gr6 =  2
	with gr0 - gr6;									// delay slot

	if < delayed goto .LnmppsMean_16s_Sfs_the_last_one;
	ar5 = nmppsMean_16s_Sfs_Big_Sum_Vector;			// delay slot (x2)

	sir = 0x00000002;
	sb  = sir;										// 2 lines

	rep 2 wfifo = [ar5], ftw, wtw;

	rep 1 data = [ar0++] with vsum, data, vr;
	rep 1 [ar6] = afifo;

	vr = [ar6] with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_16s_Sfs_get_average;
.LnmppsMean_16s_Sfs_the_last_one:
	sir = 0x00000002;								// delay slot
	sb  = sir;										// 2 lines

	// ar5 already has start address of nmppsMean_16s_Sfs_Big_Sum_Vector
	// from previous stage

	//
	// W = | 1 |
	//     | 0 | -( to rid off high element )-
	//
	rep 2 wfifo = [ar5++], ftw, wtw;

	rep 1 data = [ar0++] with vsum, data, vr;
	rep 1 [ar6] = afifo;

.LnmppsMean_16s_Sfs_get_average:
	ar2, gr2 = [ar6] with gr1;

	if <= goto .LnmppsMean_16s_Sfs_LShift;
.LnmppsMean_16s_Sfs_RShift:
	[ar7++] = ar2, gr2 with gr7 = gr1;
	call ARShift64;
	goto .LnmppsMean_16s_Sfs_after_cmp_scaleFactor;

.LnmppsMean_16s_Sfs_LShift:
	[ar7++] = ar2, gr2 with gr7 = -gr1;
	call LShift64;

.LnmppsMean_16s_Sfs_after_cmp_scaleFactor:
	ar2 = gr3 with gr2 = false;						// gr2, ar2 = ( 0x00000000, len ) 64bit value
	push ar2, gr2;

	call IDiv64;									// avg := (sum <<|>> scaleFactor) / len

	sir = [--ar7];
	vr = sir;

	ar7 = ar7 - 2 addr;

	rep 1 with vsum, 0, activate vr;				// saturate avg
	rep 1 [ar6] = afifo;

	gr2 = [ar6];									// save LSB
	[ar1] = gr2 with gr7 = nmppsStsNoErr;

.LnmppsMean_16s_Sfs_return:
	ar7 = ar7 - 64;
	pop ar6, gr6;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMean_32f(const nmpps32f* pSrc, int len, nmpps32f* pMean, nmppsHintAlgorithm hint)
 *
 * @brief Вычисление среднего значения элементов вектора типа nmpps32f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMean Среднее значение.
 * @param[in] hint Не используется.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMean_32f: .global _nmppsMean_32f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar6, gr6;

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	ar2, gr2 = [--ar5] with gr1;					//             ar2 == hint, gr2 == pMean

	if =0 delayed goto .LnmppsMean_32f_return with gr2;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsMean_32f_return;
	gr0 = ar1;										// delay slot
	ar0 = gr1 with gr0;								// delay slot

	if <= delayed goto .LnmppsMean_32f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr6 = 64;

	ar5 = Matrix_To_Sum_2_Floats;

	// vreg2 = | 1.0 1.0 |
	// vreg3 = | 0.0 0.0 |
	// vreg7 = | 0.0 0.0 |

	fpu 0 rep 1 vreg2 = [ar5++];
	fpu 0 rep 1 vreg3 = [ar5++];
	fpu 0 rep 1 vreg7 = [ar5++];					// zero out accumulator

	ar1 = gr2;
	gr1 = ar2 with gr0 - gr6;

	// Used registers:
	// ===============
	// ar0 == pSrc
	// gr0 == len
	// ar1 == pMean
	// gr1 == hint
	// ar2, gr2 == temp
	// ar6 == temp
	// gr6 == len comparator, temp

	if < goto .LnmppsMean_32f_less64;

.LnmppsMean_32f_more_than_64:
	fpu 0 rep 32 vreg0 = [ar0++];					// vreg0[32x2]

	// See documentaion "rg_asm_6407_diff.doc" at "2.2.3 Команда умножения, тип .matrix"
	//
	// vreg1 (lo) = vreg0 (lo) * vreg2 (lo) + vreg0 (hi) * vreg2 (hi)
	// vreg1 (hi) = vreg0 (lo) * vreg3 (lo) + vreg0 (hi) * vreg3 (hi)
	//
	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	// packer[0] (lo) := vreg1[0] (lo)
	// packer[0] (hi) := vreg1[1] (lo)
	// ...
	// packer[15] (lo) := vreg1[30] (lo)
	// packer[15] (hi) := vreg1[31] (lo)
	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 16 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 8 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 4 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 2 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 1 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);
	fpu 0 .float vreg7 = vreg7 + vreg1;

	with gr0 -= gr6 noflags;
	with gr0 - gr6;
	if > goto .LnmppsMean_32f_more_than_64 with gr0;

	if =0 delayed goto .LnmppsMean_32f_get_average;
.LnmppsMean_32f_less64:
	with gr6 >>= 1;									// delay slot: gr6 = 32
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32f_less32;

	fpu 0 rep 16 vreg0 = [ar0++];					// vreg0[16x2]
	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 8 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 4 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 2 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 1 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);
	fpu 0 .float vreg7 = vreg7 + vreg1;

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_32f_get_average;
.LnmppsMean_32f_less32:
	with gr6 >>= 1;									// delay slot: gr6 = 16
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32f_less16;

	fpu 0 rep 8 vreg0 = [ar0++];					// vreg0[8x2]
	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 4 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 2 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 1 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);
	fpu 0 .float vreg7 = vreg7 + vreg1;

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_32f_get_average;
.LnmppsMean_32f_less16:
	with gr6 >>= 1;									// delay slot: gr6 =  8
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32f_less8;

	fpu 0 rep 4 vreg0 = [ar0++];					// vreg0[4x2]
	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 2 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 1 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);
	fpu 0 .float vreg7 = vreg7 + vreg1;

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_32f_get_average;
.LnmppsMean_32f_less8:
	with gr6 >>= 1;									// delay slot: gr6 =  4
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32f_less4;

	fpu 0 rep 2 vreg0 = [ar0++];					// vreg0[2x2]
	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .packer = vreg1 with .float <= .float .in_low;
	fpu 0 rep 1 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);
	fpu 0 .float vreg7 = vreg7 + vreg1;

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_32f_get_average;
.LnmppsMean_32f_less4:
	with gr6 >>= 1;									// delay slot: gr6 =  2
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32f_the_last_one;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0[1x2]
	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);

	fpu 0 .float vreg7 = vreg7 + vreg1;

	with gr0 -= gr6;
	if =0 goto .LnmppsMean_32f_get_average;

.LnmppsMean_32f_the_last_one:
	fpu rep 1 .packer = [ar0++] with .float .in_low <= .float .in_low;
	fpu 0 rep 1 vreg0 = .packer;

	fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg2, vreg3);
	fpu 0 .float vreg7 = vreg7 + vreg1;

.LnmppsMean_32f_get_average:
	ar6 = ar7;
	ar7 = ar7 + 4 addr;								// allocate buffer
	ar5 = ar7 - 16 addr with gr7 = false;			// ATTENTION! seek addr of len from arguments

	sir = gr7;
	fp_pack_exp = sir;

	fpu 0 rep 1 [ar6++] = vreg7;					// save total summa

	// convert int32_t to float
	fpu rep 1 .packer = [ar5] with .float .in_low <= .fixed_32 .in_low;
	fpu rep 1 [ar6++] = .packer;
													// read and clean stack
	pop ar6, gr6;									// ar6 == float(len), gr6 is trash
	pop ar2, gr2;									// ar2 == summa, gr2 is trash

	delayed call FDiv;								// gr7 := FDiv(ar2, gr2)
	gr2 = ar6;										// delay slot
	push ar2, gr2;									// delay slot

	[ar1] = gr7 with gr7 = nmppsStsNoErr;

.LnmppsMean_32f_return:
	pop ar6, gr6;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMean_32fc(const nmpps32fc* pSrc, int len, nmpps32fc* pMean, nmppsHintAlgorithm hint)
 *
 * @brief Вычисление среднего комплексного значения элементов вектора типа nmpps32fc.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMean Среднее значение.
 * @param[in] hint Не используется.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMean_32fc: .global _nmppsMean_32fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar6, gr6;

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	ar2, gr2 = [--ar5] with gr1;					//             ar2 == hint, gr2 == pMean

	if =0 delayed goto .LnmppsMean_32fc_return with gr2;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsMean_32fc_return;
	gr0 = ar1;										// delay slot
	ar0 = gr1 with gr0;								// delay slot

	if <= delayed goto .LnmppsMean_32fc_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr6 = 64;

	// vreg7 = | 0.0 0.0 |
	ar5 = Zero_Double;
	fpu 0 rep 1 vreg7 = [ar5];						// zero out accumulator

	ar1 = gr2;
	gr1 = ar2 with gr0 - gr6;

	// Used registers:
	// ===============
	// ar0 == pSrc
	// gr0 == len (variable)
	// ar1 == pMean
	// gr1 == hint
	// ar2, gr2 == temp
	// ar6 == buffer pointer
	// gr6 == len comparator

	if < goto .LnmppsMean_32fc_less64;

.LnmppsMean_32fc_more_than_64:
	fpu 0 rep 32 vreg0 = [ar0++];					// vreg0[32] (Re, Im)
	fpu 0 rep 32 vreg1 = [ar0++];					// vreg0[32] (Re, Im), 64 complex numbers in total

	fpu 0 .float vreg2 = vreg0 + vreg1;			// Re + Re, Im + Im

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 16 (vreg0, vreg1) = .packer;			// vreg0[16] (Re, Im), vreg1[16] (Re, Im)

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 8 (vreg0, vreg1) = .packer;			// vreg0[8], vreg1[8]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;			// vreg0[4], vreg1[4]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .float vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6 noflags;
	with gr0 - gr6;
	if > goto .LnmppsMean_32fc_more_than_64;

	if =0 delayed goto .LnmppsMean_32fc_get_average;
.LnmppsMean_32fc_less64:
	with gr6 >>= 1;									// delay slot: gr6 = 32
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32fc_less32;

	fpu 0 rep 16 vreg0 = [ar0++];					// vreg0[16]
	fpu 0 rep 16 vreg1 = [ar0++];					// vreg1[16], 32 in total

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 8 (vreg0, vreg1) = .packer;			// vreg0[8], vreg1[8]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;			// vreg0[4], vreg1[4]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .float vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_32fc_get_average;
.LnmppsMean_32fc_less32:
	with gr6 >>= 1;									// delay slot: gr6 = 16
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32fc_less16;

	fpu 0 rep 8 vreg0 = [ar0++];					// vreg0[8]
	fpu 0 rep 8 vreg1 = [ar0++];					// vreg1[8], 16 in total

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;			// vreg0[4], vreg1[4]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .float vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_32fc_get_average;
.LnmppsMean_32fc_less16:
	with gr6 >>= 1;									// delay slot: gr6 = 8
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32fc_less8;

	fpu 0 rep 4 vreg0 = [ar0++];					// vreg0[4]
	fpu 0 rep 4 vreg1 = [ar0++];					// vreg1[4], 8 in total

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .float vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_32fc_get_average;
.LnmppsMean_32fc_less8:
	with gr6 >>= 1;									// delay slot: gr6 = 4
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32fc_less4;

	fpu 0 rep 2 vreg0 = [ar0++];					// vreg0[2]
	fpu 0 rep 2 vreg1 = [ar0++];					// vreg1[2], 4 in total

	fpu 0 .float vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .float <= .float;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .float vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_32fc_get_average;
.LnmppsMean_32fc_less4:
	with gr6 >>= 1;									// delay slot: gr6 = 2
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_32fc_the_last_one;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0[1]
	fpu 0 rep 1 vreg1 = [ar0++];					// vreg1[1], 2 in total

	fpu 0 .float vreg2 = vreg0 + vreg1;
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 goto .LnmppsMean_32fc_get_average;
.LnmppsMean_32fc_the_last_one:
	fpu 0 rep 1 vreg2 = [ar0++];					// vreg2[1], read only one value
	fpu 0 .float vreg7 = vreg7 + vreg2;			// vreg7[1]

.LnmppsMean_32fc_get_average:
	ar6 = ar7;
	ar7 = ar7 + 4 addr;
	ar5 = ar7 - 16 addr with gr7 = false;			// ATTENTION! seek addr of len from arguments

	sir = gr7;
	fp_pack_exp = sir;

	fpu 0 rep 1 [ar6++] = vreg7;					// save total complex sum
	// convert int32_t to float
	fpu rep 1 .packer = [ar5] with .float .in_high <= .fixed_32 .in_low;
	fpu rep 1 [ar6++] = .packer;
													// read from and clear stack
	pop ar6, gr6;									// ar6 = 0, gr6 = float(len)
	pop ar2, gr2;									// ar2 = sum(Re), gr2 = sum(Im)

	delayed call FDiv;								// gr7 := FDiv(sum(Re), float(len))
	ar0 = ar2 with gr0 = gr6;						// delay slot
	push ar0, gr0;									// delay slot

	[ar1++] = gr7;									// save Re average

	delayed call FDiv;								// gr7 := FDiv(sum(Im), float(len))
	ar0 = gr2 with gr0 = gr6;						// delay slot
	push ar0, gr0;									// delay slot

	[ar1++] = gr7 with gr7 = nmppsStsNoErr;			// save Im average

.LnmppsMean_32fc_return:
	pop ar6, gr6;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMean_64f(const nmpps64f*  pSrc, int len, nmpps64f*  pMean)
 *
 * @brief Вычисление среднего значения элементов вектора типа nmpps64f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMean Среднее значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMean_64f: .global _nmppsMean_64f
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar6, gr6;

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	gr2 = [--ar5] with gr1;							//             gr2 == pMean

	if =0 delayed goto .LnmppsMean_64f_return with gr2;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsMean_64f_return;
	gr0 = ar1;										// delay slot
	ar0 = gr1 with gr0;								// delay slot

	if <= delayed goto .LnmppsMean_64f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr6 = 64;

	// vreg7 = | 0.0 |
	ar5 = Zero_Double;
	fpu 0 rep 1 vreg7 = [ar5];						// zero out accumulator

	ar1 = gr2 with gr0 - gr6;

	// Used registers:
	// ===============
	// ar0 == pSrc
	// gr0 == len (variable)
	// ar1 == pMean
	// ar2, gr2 == temp
	// ar6 == buffer pointer
	// gr6 == len comparator

	// if (len < 64) do for 32;
	if < goto .LnmppsMean_64f_less64;

.LnmppsMean_64f_more_than_64:
	fpu 0 rep 32 vreg0 = [ar0++];					// vreg0[32]
	fpu 0 rep 32 vreg1 = [ar0++];					// vreg1[32], 64 in total

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 16 (vreg0, vreg1) = .packer;			// vreg0[16], vreg1[16]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 8 (vreg0, vreg1) = .packer;			// vreg0[8], vreg1[8]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;			// vreg0[4], vreg1[4]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .double vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6 noflags;
	with gr0 - gr6;
	if > goto .LnmppsMean_64f_more_than_64;

	if =0 delayed goto .LnmppsMean_64f_get_average;
.LnmppsMean_64f_less64:
	with gr6 >>= 1;									// delay slot: gr6 = 32
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64f_less32;

	fpu 0 rep 16 vreg0 = [ar0++];					// vreg0[16]
	fpu 0 rep 16 vreg1 = [ar0++];					// vreg1[16], 32 in total

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 8 (vreg0, vreg1) = .packer;			// vreg0[8], vreg1[8]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;			// vreg0[4], vreg1[4]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .double vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_64f_get_average;
.LnmppsMean_64f_less32:
	with gr6 >>= 1;									// delay slot: gr6 = 16
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64f_less16;

	fpu 0 rep 8 vreg0 = [ar0++];					// vreg0[8]
	fpu 0 rep 8 vreg1 = [ar0++];					// vreg1[8], 16 in total

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;			// vreg0[4], vreg1[4]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .double vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_64f_get_average;
.LnmppsMean_64f_less16:
	with gr6 >>= 1;									// delay slot: gr6 = 8
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64f_less8;

	fpu 0 rep 4 vreg0 = [ar0++];					// vreg0[4]
	fpu 0 rep 4 vreg1 = [ar0++];					// vreg1[4], 8 in total

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;			// vreg0[2], vreg1[2]

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .double vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_64f_get_average;
.LnmppsMean_64f_less8:
	with gr6 >>= 1;									// delay slot: gr6 = 4
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64f_less4;

	fpu 0 rep 2 vreg0 = [ar0++];					// vreg0[2]
	fpu 0 rep 2 vreg1 = [ar0++];					// vreg1[2], 4 in total

	fpu 0 .double vreg2 = vreg0 + vreg1;

	fpu 0 .packer = vreg2 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;			// vreg0[1], vreg1[1]

	fpu 0 .double vreg2 = vreg0 + vreg1;			// vreg2[1]
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 delayed goto .LnmppsMean_64f_get_average;
.LnmppsMean_64f_less4:
	with gr6 >>= 1;									// delay slot: gr6 = 2
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64f_the_last_one;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0[1]
	fpu 0 rep 1 vreg1 = [ar0++];					// vreg1[1], 2 in total

	fpu 0 .double vreg2 = vreg0 + vreg1;
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

	with gr0 -= gr6;

	if =0 goto .LnmppsMean_64f_get_average;
.LnmppsMean_64f_the_last_one:
	fpu 0 rep 1 vreg2 = [ar0++];					// vreg2[1], read only one value
	fpu 0 .double vreg7 = vreg7 + vreg2;			// vreg7[1]

.LnmppsMean_64f_get_average:
	ar6 = ar7;
	ar7 = ar7 + 4 addr;								// allocale buffer
	ar5 = ar7 - 16 addr with gr7 = false;			// ATTENTION! seek addr of len from arguments

	sir = gr7;
	fp_pack_exp = sir;

	fpu 0 rep 1 [ar6++] = vreg7;					// save total summa

	delayed call DDiv;								// DDiv(vreg7, float(len))
	// convert int32_t to double
	fpu rep 1 .packer = [ar5] with .double <= .fixed_32 .in_low;	// delay slot
	fpu rep 1 [ar6++] = .packer;									// delay slot

	pop ar2, gr2;									// get result from DDiv

	ar7 = ar7 - 2 addr;

	[ar1] = ar2, gr2 with gr7 = nmppsStsNoErr;		// pMean := DDiv(summa, len)

.LnmppsMean_64f_return:
	pop ar6, gr6;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsMean_64fc(const nmpps64fc* pSrc, int len, nmpps64fc* pMean)
 *
 * @brief Вычисление среднего комплексного значения элементов вектора типа nmpps64fc.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pMean Среднее значение.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 1.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsMean_64fc: .global _nmppsMean_64fc
	ar5 = ar7 - 2 addr;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar6, gr6;

	ar1, gr1 = [--ar5];								// after read: ar1 == len, gr1 == pSrc
	gr2 = [--ar5] with gr1;							//             gr2 == pMean

	if =0 delayed goto .LnmppsMean_64fc_return with gr2;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	if =0 delayed goto .LnmppsMean_64fc_return;
	gr0 = ar1;										// delay slot
	ar0 = gr1 with gr0;								// delay slot

	if <= delayed goto .LnmppsMean_64fc_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	gr6 = 64;

	// vreg6 = | 0.0 |
	// vreg7 = | 0.0 |
	ar5 = Zero_Double;
	fpu 0 rep 1 vreg6 = [ar5];						// zero out accumulator for Re
	fpu 0 rep 1 vreg7 = [ar5];						// zero out accumulator for Im

	ar1 = gr2 with gr0 - gr6;

	// Used registers:
	// ===============
	// ar0 == pSrc
	// gr0 == len (variable)
	// ar1 == pMean
	// ar2, gr2 == temp
	// ar6 == buffer pointer
	// gr6 == len comparator

	// if (len < 64) do for 32;
	if < goto .LnmppsMean_64fc_less64;

.LnmppsMean_64fc_more_than_64:
	fpu 0 rep 32 vreg0 = [ar0++];					// vreg0[32] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 32 vreg1 = [ar0++];					// vreg1[32] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 32 vreg2 = [ar0++];					// vreg2[32] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 32 vreg3 = [ar0++];					// vreg3[32] = { [0] = Re, [1] = Im, ... }
													// in total: 64 complex numbers
	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg4 = vreg4 + vreg2;
	fpu 0 .double vreg4 = vreg4 + vreg3;			// vreg4[32] = vreg0[32] + vreg1[32] + vreg2[32] + vreg3[32]

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 16 (vreg4, vreg5) = .packer;			// vreg4[16] = Re, vreg5[16] = Im

	/*
	// sum Re parts
	*/

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 8 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 8 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 4 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 2 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 1 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;
	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

	with gr0 -= gr6 noflags;
	with gr0 - gr6;
	if > goto .LnmppsMean_64fc_more_than_64;

	if =0 delayed goto .LnmppsMean_64fc_get_average;
.LnmppsMean_64fc_less64:
	with gr6 >>= 1;									// delay slot: gr6 = 32
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64fc_less32;

	fpu 0 rep 16 vreg0 = [ar0++];					// vreg0[16] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 16 vreg1 = [ar0++];					// vreg1[16] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 16 vreg2 = [ar0++];					// vreg2[16] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 16 vreg3 = [ar0++];					// vreg3[16] = { [0] = Re, [1] = Im, ... }
													// in total: 32 complex numbers
	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg4 = vreg4 + vreg2;
	fpu 0 .double vreg4 = vreg4 + vreg3;			// vreg4[16] = vreg0[16] + vreg1[16] + vreg2[16] + vreg3[16]

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 8 (vreg4, vreg5) = .packer;			// vreg4[8] = Re, vreg5[8] = Im

	/*
	// sum Re parts
	*/

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 4 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 4 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 2 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 1 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;
	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_64fc_get_average;
.LnmppsMean_64fc_less32:
	with gr6 >>= 1;									// delay slot: gr6 = 16
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64fc_less16;

	fpu 0 rep 8 vreg0 = [ar0++];					// vreg0[8] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 8 vreg1 = [ar0++];					// vreg1[8] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 8 vreg2 = [ar0++];					// vreg2[8] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 8 vreg3 = [ar0++];					// vreg3[8] = { [0] = Re, [1] = Im, ... }
													// in total: 16 complex numbers
	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg4 = vreg4 + vreg2;
	fpu 0 .double vreg4 = vreg4 + vreg3;			// vreg4[8] = vreg0[8] + vreg1[8] + vreg2[8] + vreg3[8]

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 4 (vreg4, vreg5) = .packer;			// vreg4[4] = Re, vreg5[4] = Im

	/*
	// sum Re parts
	*/

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 2 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 2 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 1 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;
	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_64fc_get_average;
.LnmppsMean_64fc_less16:
	with gr6 >>= 1;									// delay slot: gr6 = 8
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64fc_less8;

	fpu 0 rep 4 vreg0 = [ar0++];					// vreg0[4] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 4 vreg1 = [ar0++];					// vreg1[4] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 4 vreg2 = [ar0++];					// vreg2[4] = { [0] = Re, [1] = Im, ... }
	fpu 0 rep 4 vreg3 = [ar0++];					// vreg3[4] = { [0] = Re, [1] = Im, ... }
													// in total: 8 complex numbers
	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg4 = vreg4 + vreg2;
	fpu 0 .double vreg4 = vreg4 + vreg3;			// vreg4[4] = vreg0[4] + vreg1[4] + vreg2[4] + vreg3[4]

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 2 (vreg4, vreg5) = .packer;			// vreg4[2] = Re, vreg5[2] = Im

	/*
	// sum Re parts
	*/

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 1 (vreg0, vreg1) = .packer;

	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .packer = vreg5 with .double <= .double;
	fpu 0 rep 1 (vreg2, vreg3) = .packer;

	fpu 0 .double vreg5 = vreg2 + vreg3;
	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_64fc_get_average;
.LnmppsMean_64fc_less8:
	with gr6 >>= 1;									// delay slot: gr6 = 4
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64fc_less4;

	fpu 0 rep 2 vreg0 = [ar0++];					// vreg0[2] = { [0] = Re, [1] = Im }
	fpu 0 rep 2 vreg1 = [ar0++];					// vreg1[2] = { [0] = Re, [1] = Im }
	fpu 0 rep 2 vreg2 = [ar0++];					// vreg2[2] = { [0] = Re, [1] = Im }
	fpu 0 rep 2 vreg3 = [ar0++];					// vreg3[2] = { [0] = Re, [1] = Im }
													// in total: 4 complex numbers
	fpu 0 .double vreg4 = vreg0 + vreg1;
	fpu 0 .double vreg4 = vreg4 + vreg2;
	fpu 0 .double vreg4 = vreg4 + vreg3;			// vreg4[2] = vreg0[2] + vreg1[2] + vreg2[2] + vreg3[2]

	fpu 0 .packer = vreg4 with .double <= .double;
	fpu 0 rep 1 (vreg4, vreg5) = .packer;			// vreg4[1] = Re, vreg5[1] = Im

	/*
	// sum Re parts
	*/

	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

	with gr0 -= gr6;
	if =0 delayed goto .LnmppsMean_64fc_get_average;
.LnmppsMean_64fc_less4:
	with gr6 >>= 1;									// delay slot: gr6 = 2
	with gr0 - gr6;									// delay slot

	if < goto .LnmppsMean_64fc_the_last_one;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0[1] = { [0] = Re, }
	fpu 0 rep 1 vreg1 = [ar0++];					// vreg1[1] = { [0] = Im, }
	fpu 0 rep 1 vreg2 = [ar0++];					// vreg2[1] = { [0] = Re, }
	fpu 0 rep 1 vreg3 = [ar0++];					// vreg3[1] = { [0] = Im, }
													// in total: 2 complex numbers

	fpu 0 .double vreg4 = vreg0 + vreg2;			// vreg4[1] = vreg0[1] + vreg2[1] (Re)
	fpu 0 .double vreg5 = vreg1 + vreg3;			// vreg5[1] = vreg0[1] + vreg2[1] (Im)

	/*
	// sum Re parts
	*/

	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

	with gr0 -= gr6;
	if =0 goto .LnmppsMean_64fc_get_average;

.LnmppsMean_64fc_the_last_one:
	fpu 0 rep 1 vreg4 = [ar0++];					// vreg4[1] = Re
	fpu 0 rep 1 vreg5 = [ar0++];					// vreg5[1] = Im

	/*
	// sum Re parts
	*/

	fpu 0 .double vreg6 = vreg6 + vreg4;			// accumulate Re

	/*
	// sum Im parts
	*/

	fpu 0 .double vreg7 = vreg7 + vreg5;			// accumulate Im

.LnmppsMean_64fc_get_average:
	ar5 = ar7;
	ar7 = ar7 + 4 addr;								// allocate buffer
	ar6 = ar7 - 16 addr with gr7 = false;			// ATTENTION! seek addr of len from arguments

	sir = gr7;
	fp_pack_exp = sir;

	fpu 0 rep 1 [ar5++] = vreg6;					// save sum of Re

	delayed call DDiv;								// Re_avg := DDiv(sum(Re), float(len))
	// convert int32_t to double
	fpu rep 1 .packer = [ar6] with .double <= .fixed_32 .in_low;	// delay slot
	fpu rep 1 [ar5++] = .packer;									// delay slot

	ar5 = ar7;
	ar2, gr2 = [--ar5];

	[ar1++] = ar2, gr2;								// store average Re

	ar5 = ar7 - 4 addr;

	fpu 0 rep 1 [ar5++] = vreg7;					// save sum of Im

	delayed call DDiv;								// Im_avg := DDiv(sum(Im), float(len))
	// convert int32_t to double
	fpu rep 1 .packer = [ar6] with .double <= .fixed_32 .in_low;	// delay slot
	fpu rep 1 [ar5++] = .packer;									// delay slot

	ar5 = ar7;
	ar2, gr2 = [--ar5];

	[ar1++] = ar2, gr2;								// store average Im

	// release buffer and return Ok status
	ar7 = ar7 - 4 addr with gr7 = nmppsStsNoErr;

.LnmppsMean_64fc_return:
	pop ar6, gr6;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
/**
 * @}
 */


/* /////////////////////////////////////////////////////////////////////////////
// Module's constants
*/
	.align 2
	// DONT CHANGE THE ORDER AND COUNT FOR BELOW STATEMENTS {{{
Matrix_To_Sum_2_Floats:
	.float 1.0 // vregx (lo)
	.float 1.0 // vregx (hi)
	.float 0.0 // vregy (lo)
	.float 0.0 // vregy (hi)
Zero_Float:
	.float 0.0
	.float 0.0
Zero_Double:
	.double 0.0
	// }}}

	.align 2
nmppsMean_16s_Sfs_Conf_One_Column:
	.quad 0x8000000000000000						// 1 column x 64bit (nb1)
nmppsMean_16s_Sfs_Big_Sum_Vector:
	.quad 0x0000000000000001
	.quad 0x0000000000000000
nmppsMean_16s_Sfs_Little_Sum_Vector_32:
	.quad 0x5555555555555555						// 32 elements with value 1
nmppsMean_16s_Sfs_Little_Sum_Vector_16:
	.quad 0x1111111111111111						// 16 elements with value 1
nmppsMean_16s_Sfs_Little_Sum_Vector_8:
	.quad 0x0101010101010101						//  8 elements with value 1
nmppsMean_16s_Sfs_Little_Sum_Vector_4:
	.quad 0x0001000100010001						//  4 elements with value 1
nmppsMean_16s_Sfs_Little_Sum_Vector_2:
	.quad 0x0000000100000001						//  2 elements with value 1
nmppsMean_16s_Sfs_Little_Sum_Vector_1:
	.quad 0x0000000000000001						//  1  element with value 1
nmppsMean_16s_Sfs_Conf_Saturation:
	.quad 0xFFFFFFFFFFFF8000						// to saturate int16
