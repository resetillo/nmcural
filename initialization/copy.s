.globl _nmppsCopy_16sc
.globl _nmppsCopy_32sc
.globl _nmppsCopy_64sc

.text

_nmppsCopy_16sc:
_nmppsCopy_32sc:

ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
if =0 delayed goto Lexit_16sc;
gr7 = -8;
ar0 = gr0;

gr1 = [--ar5]; // pDst
gr1 - gr3;
if =0 delayed goto Lexit_16sc;
gr7 = -8;
ar1 = gr1;

gr2 = [--ar5]; // len
gr2 - 1;
if < delayed goto Lexit_16sc;
gr7 = -6;
nul;

gr7 = 0;

// —колько раз можем полностью загрузить регистр
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;

if =0 delayed goto Lless32_16sc;
gr0 = gr2 - 1 ;
vlen = gr0;

Lcopy32_16sc:
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;

if > delayed goto Lcopy32_16sc;
gr0 = 31;
gr1 = gr2 and gr0;

if =0 delayed goto Lexit_16sc;
gr1 = gr1 - 1;
vlen = gr1;
Lless32_16sc:
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;
Lexit_16sc:
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;



_nmppsCopy_64sc:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
if =0 delayed goto Lexit_64sc;
gr7 = -8;
ar0 = gr0;

gr1 = [--ar5]; // pDst
gr1 - gr3;
if =0 delayed goto Lexit_64sc;
gr7 = -8;
ar1 = gr1;

gr2 = [--ar5]; // len
gr2 - 1;
if < delayed goto Lexit_64sc;
gr7 = -6;
nul;

gr7 = 0;

// —колько раз можем полностью загрузить регистр
gr1 = 0;
gr3 = gr2 >> 4;

gr3 + gr1;

if =0 delayed goto Lless32_64sc;
gr0 = gr2;
gr0 <<= 1;

Lcopy32_64sc:
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;

if > delayed goto Lcopy32_64sc;
gr1 = 31;
gr0 = gr2 and gr1;

if =0 delayed goto Lexit_64sc;
gr0 <<= 1;
nul;
Lless32_64sc:
vlen = gr0;
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;
Lexit_64sc:
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;
