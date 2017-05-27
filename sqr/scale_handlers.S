

/* /////////////////////////////////////////////////////////////////////////////
// Names:      Scale_Handlers
// Purpose:    Computes scaling for signed and unsigned 8-bit, 16-bit numbers
// Parameters:
//   pSrc              (ar2) Pointer to source and destination scalar number
//   scaleFactor       (gr2) Scale factor
// Return:
//   nothing
*/

	.text


	.align 2
Scale_Handler_Left_Shift_Unsigned: .globl Scale_Handler_Left_Shift_Unsigned
	push ar0, gr0 with gr2 = -gr2;
	push ar1, gr1 with gr0 = gr2;

	ar0 = LShift_OV_Table;
	gr0 = [ar0 + gr0];
	gr1 = [ar2];

	ar1 = ar2 addr with gr1 - gr0;
	if u>= delayed goto .LScale_Handler_Left_Shift_Unsigned_try_shift_next;
	gr7 = 0x7FFFFFFF;								// delay slot (x2)

	delayed call LShift32;
	ar2 = gr1;										// delay slot
	push ar2, gr2;									// delay slot

.LScale_Handler_Left_Shift_Unsigned_try_shift_next:
	[ar1++] = gr7;

	gr1 = [ar1];
	with gr1 - gr0;
	if u>= delayed goto .LScale_Handler_Left_Shift_Unsigned_the_end;
	gr7 = 0x7FFFFFFF;								// delay slot (x2)

	delayed call LShift32;
	ar2 = gr1;										// delay slot
	push ar2, gr2;									// delay slot

.LScale_Handler_Left_Shift_Unsigned_the_end:
	[ar1] = gr7;

	pop ar1, gr1;
	pop ar0, gr0;
	return;


	.align 2
Scale_Handler_Right_Shift_Unsigned: .globl Scale_Handler_Right_Shift_Unsigned
	ar5 = [ar2] with gr5 = gr2;

	delayed call RShift32;
	push ar5, gr5;									// delay slot
	nul;											// delay slot

	[ar2++] = gr7;

	ar5 = [ar2] with gr5 = gr2;

	delayed call RShift32;
	push ar5, gr5;									// delay slot
	nul;											// delay slot

	[ar2++] = gr7;

	return;


	.align 2
Scale_Handler_Wipe_Bits: .globl Scale_Handler_Wipe_Bits
	delayed return with gr5 = false;
	ar5 = gr5;										// delay slot
	[ar2] = ar5, gr5;								// delay slot
	nul;											// delay slot


/* /////////////////////////////////////////////////////////////////////////////
// Module constants
*/

	.align 8
LShift_OV_Table:
	.irp sh, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
	.long (0x7FFFFFFF >> \sh)
	.endr
	.long 0x00000001 // for zero case
