.global _nmppsSortDescend_16s_I
.global _nmppsSortDescend_32s_I

.text

_nmppsSortDescend_16s_I:
_nmppsSortDescend_32s_I:
	ar5= ar7 - 2;

	push ar5,gr5;

	gr5=[--ar5];	//pSrcDst
	gr7=[--ar5]; 	//len
	gr5;
	if =0 goto sd_err_ptr;
	gr7=gr7-1;
	if < goto sd_err_len;
	ar5=0;
	push gr7;
	push ar5;
	push gr5;
	call _iqsortd;
	pop gr5;
	pop gr7;
	pop gr7;
	gr7=0;
	goto  sd_exit;

sd_err_ptr:
	gr7=-8;
	goto sd_exit;
sd_err_len:
	gr7 = -6;
	//goto sa_exit
sd_exit:
	pop ar5,gr5;
	return;


_iqsortd: // int* a, int l,int r
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
	gr3=gr0+gr1;
	ar1=gr3;
	gr2=[--ar5]; 	//r
	gr3=gr0+gr2;
	ar2=gr3;
	gr4=gr2-1;		//r-1
	gr3=gr0+gr4;
	ar4=gr3;

	//if (r-l <=0) return;
 	gr3 = gr2-gr1;
 	if <= goto exit;

	//if(r-l == 1)
	gr3-1;
	if <> 0 goto iqsort_l00;
	//comexch(a[l],a[r]); return;
	gr5=[ar1];
	gr6=[ar2];
	gr5-gr6;
	if >= goto exit;
	[ar1] = gr6;
	[ar2] = gr5;
	goto exit;

	//if(r-l == 2)
iqsort_l00:
	gr5=2;
	gr3-gr5;
	if <> 0 goto iqsort_l0;
	//comexch(a[l],a[r-1]);
	gr5=[ar1]; //a[l]
	gr6=[ar4]; //a[r-1]
	gr5-gr6;
	if >= goto iqsort_l001;
	[ar1] = gr6;
	[ar4] = gr5;
iqsort_l001:
	//comexch(a[l],a[r]);
	gr5 = [ar1];
	gr6 = [ar2];
	gr5-gr6;
	if >= goto iqsort_l002;
	[ar1] = gr6;
	[ar2] = gr5;
iqsort_l002:
	//comexch(a[r-1],a[r]);
	gr5 = [ar4];
	gr6 = [ar2];
	gr5-gr6;
	if >= goto exit;
	[ar2] = gr5;
	[ar4] = gr6;
	goto exit;

iqsort_l0:
	//(l+r)/2
	gr3=gr1+gr2;
	gr3=gr3>>1;
	gr3=gr3+gr0; //a[(l+r)/2]

	//exch(a[(l+r)/2],a[r-1]);
	gr5=[gr3];
	gr6=[ar4];
	[ar4]=gr5;
	[gr3]=gr6;

	//comexch(a[l],a[r-1]);
	gr5=[ar1];
	gr6=[ar4];
	gr5-gr6;
	if >= goto iqsort_l1;
	[ar1] = gr6;
	[ar4] = gr5;

iqsort_l1:
	//comexch(a[l],a[r]);
	gr6=[ar2]; //a[r]
	gr5=[ar1];
	gr5-gr6;
	if >= goto iqsort_l2;
	[ar2] = gr5;
	[ar1] = gr6;
iqsort_l2:
	//comexch(a[r-1],a[r]);
	gr5 = [ar4]; //a[r-1]
	gr6 = [ar2]; //a[r]
	gr5-gr6;
	if >= goto iqsort_l3;
	[ar4] = gr6;
	[ar2] = gr5;
iqsort_l3:

	//int i = partition16s(a,l+1,r-1);
	gr3=gr1+1;
	push gr4;
	push gr3;
	push gr0;
	call _ipartd;
	//i=gr7
	pop gr0;
	pop gr3;
	pop gr4;

	gr3=gr7+1; //i+1
	gr7=gr7-1; //i-1

	//_iqsortd(a,l,i-1);
	push gr7;
	push gr1;
	push gr0;
	call _iqsortd;
	pop gr0;
	pop gr1;
	pop gr7;

	//_iqsortd(a,i+1,r);
	push gr2;
	push gr3;
	push gr0;
	call _iqsortd;
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


_ipartd: //int *a, int l,int r.  return int
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
	gr1 = gr1+gr0; //&a[l]
	gr2=[--ar5]; //r
	gr2=gr2+gr0; //&a[r]
	gr7=gr1-1;
	gr6=gr2;

	gr5=[gr2]; //v=a[r]

_c1:	//for(;;)

_c2:	//while(a[++i]>v);
	gr7=gr7+1;
    gr3=[gr7];
	gr3-gr5;
	if > goto _c2;

_c3:	//while(v>a[--j]) if(j==l) break;
	gr6=gr6-1;
	gr4=[gr6];
	gr5-gr4;
	if <= goto _c4;
	gr1-gr6;
	if =0 goto _c4;
	goto _c3;
_c4:
	//if(i>=j) break;
	gr7-gr6;
	if >= goto _c5;

	//exch(a[i],a[j]);
	[gr7] = gr4;
	[gr6] = gr3;
	goto _c1;
_c5:
	//exch(a[i],a[r]);
	[gr7] = gr5;
	[gr2] = gr3;

	gr7 = gr7-gr0;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	return;
