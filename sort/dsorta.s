.global _nmppsSortAscend_64f_I


.text


_nmppsSortAscend_64f_I:
	ar5= ar7 - 2;

	push ar5,gr5;

	gr5=[--ar5];	//pSrcDst
	gr7=[--ar5]; 	//len
	gr5;
	if =0 goto dsa_err_ptr;
	gr7=gr7-1;
	if < goto dsa_err_len;
	ar5=0;
	push gr7;
	push ar5;
	push gr5;
	call _dqsort;
	pop gr5;
	pop gr7;
	pop gr7;
	gr7=0;
	goto dsa_exit;

dsa_err_ptr:
	gr7=-8;
	goto dsa_exit;
dsa_err_len:
	gr7 = -6;
	//goto dsa_exit
dsa_exit:
	pop ar5,gr5;
	return;


_dqsort:	// double* a, int l,int r
	ar5 = ar7 - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	gr0=[--ar5];	//a
	gr1=[--ar5]; 	//l
	gr3=gr1<<1;
	gr3=gr0+gr3;
	ar1=gr3;		//&a[l]
	gr2=[--ar5]; 	//r
	gr3=gr2<<1;
	gr3=gr0+gr3;
	ar2=gr3;		//&a[r]
	gr4=gr2-1;		//r-1
	gr3=gr4<<1;
	gr3=gr0+gr3;
	ar4=gr3;		//&a[r-1]

	//if (r-l <=0) return;
 	gr3 = gr2-gr1;
 	if <= goto exit;

	//if(r-l == 1)
	gr3-1;
	if <> 0 goto dqsort_l00;
	//comexch(a[l],a[r]); return;

	fpu 0 rep 1 vreg0=[ar1];//a[l]
    fpu 0 rep 1 vreg1=[ar2]; //a[r]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto exit;
	fpu 0 rep 1 [ar1]=vreg1;
    fpu 0 rep 1 [ar2]=vreg0;
	goto exit;

	//if(r-l == 2)
dqsort_l00:
	gr5=2;
	gr3-gr5;
	if <> 0 goto dqsort_l0;
	//comexch(a[l],a[r-1]);

	fpu 0 rep 1 vreg0=[ar1];//a[l]
    fpu 0 rep 1 vreg1=[ar4]; //a[r-1]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto dqsort_l001;
	fpu 0 rep 1 [ar1] = vreg1;
	fpu 0 rep 1 [ar4] = vreg0;
dqsort_l001:
	//comexch(a[l],a[r]);
	fpu 0 rep 1 vreg0=[ar1];//a[l]
    fpu 0 rep 1 vreg1=[ar2]; //a[r]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto dqsort_l002;
	fpu 0 rep 1 [ar1] = vreg1;
	fpu 0 rep 1 [ar2] = vreg0;

dqsort_l002:
	//comexch(a[r-1],a[r]);
	fpu 0 rep 1 vreg0=[ar4];//a[r-1]
    fpu 0 rep 1 vreg1=[ar2]; //a[r]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto exit;
	fpu 0 rep 1 [ar4] = vreg1;
	fpu 0 rep 1 [ar2] = vreg0;
	goto exit;

dqsort_l0:
	//(l+r)/2
	gr3=gr1+gr2;
	gr3=gr3>>1;
	gr3=gr3<<1;
	gr3=gr3+gr0; //a[(l+r)/2]

	//exch(a[(l+r)/2],a[r-1]);
	fpu 0 rep 1 vreg0=[gr3];
	fpu 0 rep 1 vreg1=[ar4];
	fpu 0 rep 1 [gr3]=vreg1;
	fpu 0 rep 1 [ar4]=vreg0;

	//comexch(a[l],a[r-1]);
	fpu 0 rep 1 vreg0=[ar1];//a[l]
    fpu 0 rep 1 vreg1=[ar4]; //a[r-1]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto dqsort_l1;
	fpu 0 rep 1 [ar1] = vreg1;
	fpu 0 rep 1 [ar4] = vreg0;

dqsort_l1:
	//comexch(a[l],a[r]);
	fpu 0 rep 1 vreg0=[ar1];//a[l]
    fpu 0 rep 1 vreg1=[ar2]; //a[r]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto dqsort_l2;
	fpu 0 rep 1 [ar1] = vreg1;
	fpu 0 rep 1 [ar2] = vreg0;
dqsort_l2:
	//comexch(a[r-1],a[r]);
	fpu 0 rep 1 vreg0=[ar4];//a[r-1]
    fpu 0 rep 1 vreg1=[ar2]; //a[r]
	fpu 0 .double vreg0-vreg1, set mask if >;

	sir = fp0_dmask;
	gr5=sir;
	gr5;
	if <= goto dqsort_l3;
	fpu 0 rep 1 [ar4] = vreg1;
	fpu 0 rep 1 [ar2] = vreg0;
dqsort_l3:

	//int i = partition16s(a,l+1,r-1);
	gr3=gr1+1;
	push gr4;
	push gr3;
	push gr0;
	call _dpart;
	//i=gr7
	pop gr0;
	pop gr3;
	pop gr4;

	gr3=gr7+1; //i+1
	gr7=gr7-1; //i-1

	//_dqsort(a,l,i-1);
	push gr7;
	push gr1;
	push gr0;
	call _dqsort;
	pop gr0;
	pop gr1;
	pop gr7;

	//_dqsort(a,i+1,r);
	push gr2;
	push gr3;
	push gr0;
	call _dqsort;
	pop gr0;
	pop gr3;
	pop gr2;

exit:
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;

_dpart:		// double* a, int l,int r :return int

	ar5 = ar7 - 2;

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	gr0=[--ar5]; //a
	gr1=[--ar5]; //l
	gr1=gr1<<1;
	gr1 = gr1+gr0; //&a[l]
	gr2=[--ar5]; //r
	gr2=gr2<<1;
	gr2=gr2+gr0; //&a[r]
	gr5=2;
	gr7=gr1-gr5;
	gr6=gr2;


_c1:	//for(;;)

	fpu 0 rep 1 vreg0=[gr2];//v=a[r]

_c2:	//while(a[++i]<v);

	gr7=gr7+gr5;

    fpu 0 rep 1 vreg1=[gr7]; //a[i]

	fpu 0 .double vreg1-vreg0, set mask if <;

	sir = fp0_dmask;
	gr3=sir;
	gr3;
	if > goto _c2;

_c3:	//while(v<a[--j]) if(j==l) break;

	gr6=gr6-gr5;

 	fpu 0 rep 1 vreg2=[gr6]; //a[j]

	fpu 0 .double vreg0-vreg2, set mask if >=;

	sir = fp0_dmask;
	gr4=sir;
	gr4;
	if > goto _c4;

	gr1-gr6;
	if =0 goto _c4;
	goto _c3;
_c4:
	//if(i>=j) break;
	gr7-gr6;
	if >= goto _c5;

	//exch(a[i],a[j]);
	fpu 0 rep 1 [gr7]=vreg2;
	fpu 0 rep 1 [gr6]=vreg1;

	goto _c1;
_c5:
	//exch(a[i],a[r]);
	fpu 0 rep 1 vreg5=[gr7]; //a[i]
	fpu 0 rep 1 vreg6=[gr2]; //a[r]
	fpu 0 rep 1 [gr7]=vreg6;
	fpu 0 rep 1 [gr2]=vreg5;

	gr7 = gr7-gr0;
	gr7=gr7>>1;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	return;
