.global _nmppsMagnitude_32fc

.text

//nmppsStatus nmppsMagnitude_32fc(const nmpps32fc*  pSrc, nmpps32fc* pDst, int len);
_nmppsMagnitude_32fc:
	ar5 = ar7 - 2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;

	ar0=[--ar5]; //src
	ar2=[--ar5]; //dst
	gr0=[--ar5]; //len
	ar3=ar2;
	gr3=1;
	gr3=gr0 and gr3;

	if =0 goto _mag32fc_nosave;
	gr4=ar2;
	gr4=gr4+gr0;
	ar4 = gr4;
	gr4 = [ar4];

_mag32fc_nosave:
	gr7=ar0;
	gr7;
	if =0 goto _mag32fc_null_ptr;
	gr7=ar2;
	gr7;
	if =0 goto _mag32fc_null_ptr;
	gr0;
	if <= goto _mag32fc_err_size;

	gr7 = gr0>>5 ;
	if =0 goto _mag32fc_end_cicl;

_mag32fc_start_cicl:
	fpu 0 rep 32 vreg0=[ar0++];
	fpu 0 .float vreg0=vreg0*vreg0;
	fpu 0 .float vreg1=vreg0;
	fpu 0 .packer=vreg0 with .float <= .float .in_high;
	fpu 0 rep 16 vreg2=.packer;
	//fpu 0 rep 2 [ar2++]=vreg2;
	fpu 0 .packer=vreg1 with .float <= .float .in_low;
	fpu 0 rep 16 vreg3=.packer;
	fpu 0 .float vreg4=vreg2+vreg3;
	fpu 0 rep 16 [ar2++]=vreg4;

	gr7=gr7-1;
	if > goto _mag32fc_start_cicl;

_mag32fc_end_cicl:
	gr2=0x001F;
	gr1 = gr0 and gr2;

	if =0 delayed goto  _mag32fc_exit;
	gr7=0;
	nul;

	gr2=gr1-1;
	vlen = gr2;
	fpu 0 rep vlen vreg0=[ar0++];
	fpu 0 .float vreg0=vreg0*vreg0;
	fpu 0 .float vreg1=vreg0;
	fpu 0 .packer=vreg0 with .float <= .float .in_high;
	gr1=gr1+1;
	gr1=gr1>>1;
	gr1=gr1-1;
	vlen=gr1;
	fpu 0 rep vlen vreg2=.packer;
	fpu 0 .packer=vreg1 with .float <= .float .in_low;
	fpu 0 rep vlen vreg3=.packer;
	fpu 0 .float vreg4=vreg2+vreg3;
	fpu 0 rep vlen [ar2++]=vreg4;

	push gr0; //len
	push ar3; //dst
	push ar3; //src
	call _nmppsSqrt_32f;
	ar7 = ar7 - 3;

	gr3;
	if =0 goto _mag32fc_noreload;
	[ar4] = gr4;
_mag32fc_noreload:
	gr7=0;
	goto _mag32fc_exit;

_mag32fc_null_ptr:
	gr7=-8;
	goto _mag32fc_exit;
_mag32fc_err_size:
	gr7=-6;
	//goto _mag32fc_exit
_mag32fc_exit:
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;

