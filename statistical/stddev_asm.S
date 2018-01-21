#include <nmpps_asm_defs.h>

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      nmppsStdDev
//  Purpose:    compute standard deviation value of all elements of the vector
//  Parameters:
//   pSrc               pointer to the vector
//   len                length of the vector
//   pStdDev            pointer to the result
//   scaleFactor        scale factor value
//  Return:
//   nmppsStsNoErr           Ok
//   nmppsStsNullPtrErr      pointer to the vector or the result is NULL
//   nmppsStsSizeErr         length of the vector is less than 2
//  Functionality:
//         std = sqrt( sum( (x[n] - mean(x))^2, n=0..len-1 ) / (len-1) )
*/

	.text

	.extern _nmppsMean_32f		// from mean_asm.S
	.extern _square_root32f 	// from squareroot32.S
	.extern _nmppsMean_64f		// from mean_asm.S
	.extern _square_root64f	// from squareroot64.S


/**
 * @addtogroup StatisticalGroup
 * @{
 */


/**
 * @fn nmppsStatus nmppsStdDev_32f(const nmpps32f* pSrc, int len, nmpps32f* pStdDev, nmppsHintAlgorithm hint)
 *
 * @brief Вычисление стандартного отклонения элементов вектора типа nmpps32f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pStdDev Стандартное отклонение.
 * @param[in] hint Не используется.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 2.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsStdDev_32f: .global _nmppsStdDev_32f
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;

	ar4, gr4 = [--ar5];								// after read: ar4 == len, gr4 == pSrc
	ar2, gr2 = [--ar5];								//             ar2 == hint, gr2 == pStdDev

	gr3 = ar7;										// pointer to mean value
	ar3 = ar2;										// HintAlgorithm

	ar7 = ar7 + 2 with gr2;							// allocate for mean value

	// if (pStdDev == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsStdDev_32f_return;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	gr0 = ar4;										// gr0 == len
	ar0 = gr4 with gr0 - 1;							// ar0 == pSrc

	// if (len <= 1) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsStdDev_32f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	push ar3, gr3;
	push ar4, gr4;

	call _nmppsMean_32f;

	ar7 = ar7 - 4 with gr7;							// release arguments

	// if ((status = _nmppsMean_32f(...)) < 0) return status;
	if < delayed goto .LnmppsStdDev_32f_return;
	ar2 = gr3;										// delay slot: ar2 == pMean
	nul;											// delay slot

	gr4 = 64;

	ar5 = Matrix_To_Sum_2_Floats;

	// vreg0 = | 1.0 1.0 |
	// vreg1 = | 0.0 0.0 |
	// vreg7 = | 0.0 0.0 |

	fpu 0 rep 1 vreg0 = [ar5++];
	fpu 0 rep 1 vreg1 = [ar5++];
	fpu 0 rep 1 vreg7 = [ar5++];					// zero out accumulator

	gr3 = [ar2] with gr1 = gr0 - 1;					// gr1 == len - 1 (divisor in FDiv)
	[ar2 + 1] = gr3 with gr0 - gr4;					// [ Mean, Mean ]

	if < goto .LnmppsStdDev_32f_less64;

.LnmppsStdDev_32f_more_than_64:
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar2];
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	// See documentaion "rg_asm_6407_diff.doc" at "2.2.3 Команда умножения, тип .matrix"
	//
	// vreg6 (lo) = vreg5 (lo) * vreg0 (lo) + vreg5 (hi) * vreg0 (hi)
	// vreg6 (hi) = vreg5 (lo) * vreg1 (lo) + vreg5 (hi) * vreg1 (hi)
	//

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	// packer[0] (lo) := vreg6[0] (lo)
	// packer[0] (hi) := vreg6[1] (lo)
	// ...
	// packer[15] (lo) := vreg6[30] (lo)
	// packer[15] (hi) := vreg6[31] (lo)
	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 16 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 8 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 4 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 2 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 1 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

	with gr0 -= gr4 noflags;
	with gr0 - gr4;
	if > goto .LnmppsStdDev_32f_more_than_64;

	if =0 delayed goto .LnmppsStdDev_32f_get_stddev;
.LnmppsStdDev_32f_less64:
	with gr4 >>= 1;									// delay slot: gr4 = 32
	with gr0 - gr4;									// delay slot

	if < goto .LnmppsStdDev_32f_less32;

	fpu 0 rep 16 vreg2 = [ar0++];
	fpu 0 rep 16 vreg3 = [ar2];
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 8 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 4 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 2 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 1 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_32f_get_stddev;
.LnmppsStdDev_32f_less32:
	with gr4 >>= 1;									// delay slot: gr4 = 16
	with gr0 - gr4;

	if < goto .LnmppsStdDev_32f_less16;

	fpu 0 rep 8 vreg2 = [ar0++];
	fpu 0 rep 8 vreg3 = [ar2];
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 4 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 2 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 1 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_32f_get_stddev;
.LnmppsStdDev_32f_less16:
	with gr4 >>= 1;									// delay slot: gr4 = 8
	with gr0 - gr4;									// delay slot

	if < goto .LnmppsStdDev_32f_less8;

	fpu 0 rep 4 vreg2 = [ar0++];
	fpu 0 rep 4 vreg3 = [ar2];
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 2 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 1 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_32f_get_stddev;
.LnmppsStdDev_32f_less8:
	with gr4 >>= 1;									// delay slot: gr4 = 4
	with gr0 - gr4;									// delay slot

	if < goto .LnmppsStdDev_32f_less4;

	fpu 0 rep 2 vreg2 = [ar0++];
	fpu 0 rep 2 vreg3 = [ar2];
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);

	fpu 0 .packer = vreg6 with .float <= .float .in_low;
	fpu 0 rep 1 vreg5 = .packer;

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

.LnmppsStdDev_32f_less4:
	with gr4 >>= 1;									// delay slot: gr4 = 2
	with gr0 - gr4;									// delay slot

	if < goto .LnmppsStdDev_32f_the_last_one;

	fpu 0 rep 1 vreg2 = [ar0++];
	fpu 0 rep 1 vreg3 = [ar2];
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

	with gr0 -= gr4;
	if =0 goto .LnmppsStdDev_32f_get_stddev;

.LnmppsStdDev_32f_the_last_one:
	fpu rep 1 .packer = [ar0++] with .float .in_low <= .float .in_low;
	fpu 0 rep 1 vreg2 = .packer;
	fpu rep 1 .packer = [ar2] with .float .in_low <= .float .in_low;
	fpu 0 rep 1 vreg3 = .packer;
	fpu 0 .float vreg4 = vreg2 - vreg3;			// {0}:  x[n] - mean(x)
	fpu 0 .float vreg5 = vreg4 * vreg4;			// {1}: (x[n] - mean(x))^2

	fpu 0 .matrix vreg6 = vreg5 * .retrive(vreg0, vreg1);
	fpu 0 .float vreg7 = vreg7 + vreg6;

.LnmppsStdDev_32f_get_stddev:
	// vreg7 = sum( (x[n] - mean(x))^2, n=0..len-1 )
	ar0 = ar7;
	ar7 = ar7 + 4 addr;

	fpu 0 rep 1 [ar0] = vreg7;
	ar3 = [ar0];									// sum(...)

	sir = 0;
	fp_pack_exp = sir;
	[ar0] = gr1;									// len - 1

	fpu rep 1 .packer = [ar0] with .float .in_low <= .fixed_32 .in_low;
	fpu rep 1 [ar0] = .packer;

	gr3 = [ar0];									// float(len-1)

	delayed call FDiv;								// gr7 := FDiv(ar3, gr3);
	push ar3, gr3;									// delay slot
	nul;											// delay slot

	[ar0] = gr7;									// ar0 == pSrc
	ar1 = ar0 + 2 addr;								// ar1 == pDst

	delayed call _square_root32f;
	gr0 = 1;										// delay slot (x2)

	gr7 = [ar1];
	[gr2] = gr7 with gr7 = nmppsStsNoErr;

	ar7 = ar7 - 4;									// release stack

.LnmppsStdDev_32f_return:
	ar7 = ar7 - 2;

	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;


/**
 * @fn nmppsStatus nmppsStdDev_64f(const nmpps64f* pSrc, int len, nmpps64f* pStdDev)
 *
 * @brief Вычисление стандартного отклонения элементов вектора типа nmpps64f.
 *
 * @param[in] pSrc Исходный вектор.
 * @param[in] len Размер вектора.
 * @param[out] pStdDev Стандартное отклонение.
 * @param[in] hint Не используется.
 *
 * @retval nmppsStsNullPtrErr Хотя бы один из указателей имеет значение NULL.
 * @retval nmppsStsSizeErr Размер вектора меньше чем 2.
 * @retval nmppsStsNoErr Успешное выполнение.
 */
	.align
_nmppsStdDev_64f: .global _nmppsStdDev_64f
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;

	ar4, gr4 = [--ar5];								// after read: ar4 == len, gr4 == pSrc
	gr2 = [--ar5] with gr7 = false;					//             gr2 == pStdDev

	gr3 = ar7;										// pointer to mean value
	ar3 = gr7;										// empty

	ar7 = ar7 + 2 with gr2;							// allocate for mean value

	// if (pStdDev == NULL) return nmppsStsNullPtrErr;
	if =0 delayed goto .LnmppsStdDev_64f_return;
	gr7 = nmppsStsNullPtrErr;						// delay slot (x2)

	gr0 = ar4;										// gr0 == len
	ar0 = gr4 with gr0 - 1;							// ar0 == pSrc

	// if (len <= 1) return nmppsStsSizeErr;
	if <= delayed goto .LnmppsStdDev_64f_return;
	gr7 = nmppsStsSizeErr;							// delay slot (x2)

	push ar3, gr3;
	push ar4, gr4;

	// gr7 = nmppsMean_64f(pSrc, len, &mean);
	call _nmppsMean_64f;

	ar7 = ar7 - 4 with gr7;							// release arguments

	// if ((status = _nmppsMean_64f(...)) < 0) return status;
	if < delayed goto .LnmppsStdDev_64f_return;
	ar2 = gr3;										// delay slot: ar2 == pMean
	gr1 = gr0 - 1;									// delay slot: gr1 == len - 1

	gr4 = 32;
	ar5 = Zero_Double with gr0 - gr4;

	// vreg7 = | 0.0 |
	fpu 0 rep 1 vreg7 = [ar5];						// zero out accumulator

	if < goto .LnmppsStdDev_64f_less32;

	fpu 0 rep 16 vreg2 = [ar2];						// vreg2[16] = Mean

.LnmppsStdDev_64f_more_than_32:
	fpu 0 rep 16 vreg0 = [ar0++];					// vreg0[16] = Src[ 0..15]
	fpu 0 rep 16 vreg1 = [ar0++];					// vreg1[16] = Src[16..31]

	fpu 0 .double vreg3 = vreg0 - vreg2;			// vreg3[16] = Src[ 0..15] - Mean
	fpu 0 .double vreg4 = vreg1 - vreg2;			// vreg4[16] = Src[16..31] - Mean

	fpu 0 .double vreg5 = vreg3 * vreg3;			// vreg5[16] = (Src[ 0..15] - Mean)^2
	fpu 0 .double vreg6 = vreg4 * vreg4;			// vreg6[16] = (Src[16..31] - Mean)^2

	// now find up the sum
	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 8 (vreg5, vreg6) = .packer;			// vreg5[8], vreg6[8]

	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 4 (vreg5, vreg6) = .packer;			// vreg5[4], vreg6[4]

	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 2 (vreg5, vreg6) = .packer;			// vreg5[2], vreg6[2]

	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 1 (vreg5, vreg6) = .packer;			// vreg5[1], vreg6[1]

	fpu 0 .double vreg3 = vreg5 + vreg6;
	fpu 0 .double vreg7 = vreg7 + vreg3;

	with gr0 -= gr4 noflags;
	with gr0 - gr4;
	if > goto .LnmppsStdDev_64f_more_than_32;

	if =0 delayed goto .LnmppsStdDev_64f_get_stddev;
.LnmppsStdDev_64f_less32:
	with gr4 >>= 1;									// delay slot: gr4 = 16
	with gr0 - gr4;

	if < goto .LnmppsStdDev_64f_less16;

	fpu 0 rep 8 vreg2 = [ar2];						// vreg2[8] = Mean

	fpu 0 rep 8 vreg0 = [ar0++];					// vreg0[8] = Src[ 0..7]
	fpu 0 rep 8 vreg1 = [ar0++];					// vreg1[8] = Src[ 8..15]

	fpu 0 .double vreg3 = vreg0 - vreg2;			// vreg3[8] = Src[ 0..7] - Mean
	fpu 0 .double vreg4 = vreg1 - vreg2;			// vreg4[8] = Src[ 8..15] - Mean

	fpu 0 .double vreg5 = vreg3 * vreg3;			// vreg5[8] = (Src[ 0..7] - Mean)^2
	fpu 0 .double vreg6 = vreg4 * vreg4;			// vreg6[8] = (Src[ 8..15] - Mean)^2

	// now find up the sum
	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 4 (vreg5, vreg6) = .packer;			// vreg5[4], vreg6[4]

	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 2 (vreg5, vreg6) = .packer;			// vreg5[2], vreg6[2]

	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 1 (vreg5, vreg6) = .packer;			// vreg5[1], vreg6[1]

	fpu 0 .double vreg3 = vreg5 + vreg6;
	fpu 0 .double vreg7 = vreg7 + vreg3;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_64f_get_stddev;
.LnmppsStdDev_64f_less16:
	with gr4 >>= 1;									// delay slot: gr4 = 8
	with gr0 - gr4;

	if < goto .LnmppsStdDev_64f_less8;

	fpu 0 rep 4 vreg2 = [ar2];						// vreg2[4] = Mean

	fpu 0 rep 4 vreg0 = [ar0++];					// vreg0[4] = Src[0..3]
	fpu 0 rep 4 vreg1 = [ar0++];					// vreg1[4] = Src[4..7]

	fpu 0 .double vreg3 = vreg0 - vreg2;			// vreg3[4] = Src[0..3] - Mean
	fpu 0 .double vreg4 = vreg1 - vreg2;			// vreg4[4] = Src[4..7] - Mean

	fpu 0 .double vreg5 = vreg3 * vreg3;			// vreg5[4] = (Src[0..3] - Mean)^2
	fpu 0 .double vreg6 = vreg4 * vreg4;			// vreg6[4] = (Src[4..7] - Mean)^2

	// now find up the sum
	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 2 (vreg5, vreg6) = .packer;			// vreg5[2], vreg6[2]

	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 1 (vreg5, vreg6) = .packer;			// vreg5[1], vreg6[1]

	fpu 0 .double vreg3 = vreg5 + vreg6;
	fpu 0 .double vreg7 = vreg7 + vreg3;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_64f_get_stddev;
.LnmppsStdDev_64f_less8:
	with gr4 >>= 1;									// delay slot: gr4 = 4
	with gr0 - gr4;

	if < goto .LnmppsStdDev_64f_less4;

	fpu 0 rep 2 vreg2 = [ar2];						// vreg2[2] = Mean

	fpu 0 rep 2 vreg0 = [ar0++];					// vreg0[2] = Src[0..1]
	fpu 0 rep 2 vreg1 = [ar0++];					// vreg1[2] = Src[2..3]

	fpu 0 .double vreg3 = vreg0 - vreg2;			// vreg3[2] = Src[0..1] - Mean
	fpu 0 .double vreg4 = vreg1 - vreg2;			// vreg4[2] = Src[2..3] - Mean

	fpu 0 .double vreg5 = vreg3 * vreg3;			// vreg5[2] = (Src[0..1] - Mean)^2
	fpu 0 .double vreg6 = vreg4 * vreg4;			// vreg6[2] = (Src[2..3] - Mean)^2

	// now find up the sum
	fpu 0 .double vreg3 = vreg5 + vreg6;

	fpu 0 .packer = vreg3 with .double <= .double;
	fpu 0 rep 1 (vreg5, vreg6) = .packer;			// vreg5[1], vreg6[1]

	fpu 0 .double vreg3 = vreg5 + vreg6;
	fpu 0 .double vreg7 = vreg7 + vreg3;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_64f_get_stddev;
.LnmppsStdDev_64f_less4:
	with gr4 >>= 1;									// delay slot: gr4 = 2
	with gr0 - gr4;

	fpu 0 rep 1 vreg2 = [ar2];						// load Mean value for two and one elements

	if < goto .LnmppsStdDev_64f_the_last_one;

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0[1] = Src[0..1]
	fpu 0 rep 1 vreg1 = [ar0++];					// vreg1[1] = Src[2..3]

	fpu 0 .double vreg3 = vreg0 - vreg2;			// vreg3[1] = Src[0..1] - Mean
	fpu 0 .double vreg4 = vreg1 - vreg2;			// vreg4[1] = Src[2..3] - Mean

	fpu 0 .double vreg5 = vreg3 * vreg3;			// vreg5[1] = (Src[0..1] - Mean)^2
	fpu 0 .double vreg6 = vreg4 * vreg4;			// vreg6[1] = (Src[2..3] - Mean)^2

	// now find up the sum
	fpu 0 .double vreg3 = vreg5 + vreg6;
	fpu 0 .double vreg7 = vreg7 + vreg3;

	with gr0 -= gr4;
	if =0 delayed goto .LnmppsStdDev_64f_get_stddev;

.LnmppsStdDev_64f_the_last_one:

	// vreg2 already has the Mean value

	fpu 0 rep 1 vreg0 = [ar0++];					// vreg0[1] = Src[0]

	fpu 0 .double vreg1 = vreg0 - vreg2;
	fpu 0 .double vreg3 = vreg1 * vreg1;
	fpu 0 .double vreg7 = vreg7 + vreg3;

.LnmppsStdDev_64f_get_stddev:
	// vreg7 = sum( (x[n] - mean(x))^2, n=0..len-1 )
	ar0 = ar7;
	ar1 = ar7;
	ar7 = ar7 + 4 addr;

	fpu 0 rep 1 [ar0++] = vreg7;

	sir = 0;
	fp_pack_exp = sir;								// fp_pack_exp = sir = 0
	[ar0] = gr1;

	fpu rep 1 .packer = [ar0] with .double <= .fixed_32 .in_low;
	fpu rep 1 [ar0] = .packer;

	call DDiv;										// [temp] = DDiv(sum(...), double(len - 1))

	// ar0 == pSrc [temp]
	// ar1 == pDst
	// gr0 == len
	delayed call _square_root64f;
	gr0 = 1;										// delay slot (x2)

	ar0, gr0 = [--ar1];

	[gr2] = ar0, gr0 with gr7 = nmppsStsNoErr;

	ar7 = ar7 - 4;

.LnmppsStdDev_64f_return:
	ar7 = ar7 - 2;

	pop ar4, gr4;
	pop ar3, gr3;
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
	// DONT CHANGE THE ORDER AND NUMBER FOR BELOW STATEMENTS {{{
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
