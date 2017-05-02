.globl _nmppsMove_8u
.globl _nmppsMove_16s
.globl _nmppsMove_32s
.globl _nmppsMove_64s
.globl _nmppsMove_16sc
.globl _nmppsMove_32sc
.globl _nmppsMove_64sc

.text
_nmppsMove_8u:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_8u;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_8u;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_8u;
gr7 = -6;
nul;

gr7 = 0;

// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_8u;
// �������� �����������
if < goto LBackCopy_8u;

LDirectCopy_8u:
gr0 = 63;
// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 6;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_8u;
gr4 = gr2 >> 1;
gr4 = gr4 - 1;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_8u:
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_8u;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_8u;
gr4 >>= 1;
gr4 = gr4 - 1;

// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_8u:
// ���������� ������������ 32-� ��������� �������
if < delayed goto LLastElement_8u;
vlen = gr4;
nul;

// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

// ��������� �������� len
gr4 = gr2 >> 1;
gr4 <<= 1;
gr4 - gr2;
// len �������, ����� ����������� ��������� 32-� ��������� �������
if <>0 goto LLastElement_8u;
if =0 goto LExit_8u;
// �������� �����������
LBackCopy_8u:
gr3 = 2;
gr2 - 1;

// ����� ����������� ����� ���� �������
if =0 delayed goto LLastElement_8u;
// ������� ��������� �� len
gr0 = gr0 + gr2;
gr1 = gr1 + gr2;

//���������� �������� len
gr4 = gr2 >> 1;
gr4 <<= 1;

gr2 - gr4;
// len �����, ��������� � ����������� �� 64 �������
if =0 delayed goto LBackNoLastElement_8u;
ar0 = gr0;
ar1 = gr1;

//len �� �����
//��������� �� ���� ������, ����� ����������� ��������� �������
ar0 = ar0 - 1;
ar1 = ar1 - 1;

gr0 = [ar0];
[ar1] = gr0;

//�������� �� ��� �� ������, �� ���� ����� ���������� �� 64

LBackNoLastElement_8u:
// ������� ��� ����� ��������� ��������� �������
gr0 = 63;
gr1 = 0;
gr3 = gr2 >> 6;

gr3 + gr1;
if =0 delayed goto LBackLess32_8u;
gr4 = gr2 >> 1;
gr4 = gr4 - 1;

LBackCopy32_8u:

fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_8u;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_8u;
gr4 >>= 1;
gr4 = gr4 - 1;

LBackLess32_8u:
vlen = gr4;
fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

goto LExit_8u;

LLastElement_8u:
gr0 = [ar0];
[ar1] = gr0;

LExit_8u:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;


_nmppsMove_16s:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_16s;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_16s;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_16s;
gr7 = -6;
nul;

gr7 = 0;

// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_16s;
// �������� �����������
if < goto LBackCopy_16s;

LDirectCopy_16s:
gr0 = 63;
// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 6;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_16s;
gr4 = gr2 >> 1;
gr4 = gr4 - 1;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_16s:
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_16s;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_16s;
gr4 >>= 1;
gr4 = gr4 - 1;

// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_16s:
// ���������� ������������ 32-� ��������� �������
if < delayed goto LLastElement_16s;
vlen = gr4;
nul;

// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

// ��������� �������� len
gr4 = gr2 >> 1;
gr4 <<= 1;
gr4 - gr2;
// len �������, ����� ����������� ��������� 32-� ��������� �������
if <>0 goto LLastElement_16s;
if =0 goto LExit_16s;
// �������� �����������
LBackCopy_16s:
gr3 = 2;
gr2 - 1;

// ����� ����������� ����� ���� �������
if =0 delayed goto LLastElement_16s;
// ������� ��������� �� len
gr0 = gr0 + gr2;
gr1 = gr1 + gr2;

//���������� �������� len
gr4 = gr2 >> 1;
gr4 <<= 1;

gr2 - gr4;
// len �����, ��������� � ����������� �� 64 �������
if =0 delayed goto LBackNoLastElement_16s;
ar0 = gr0;
ar1 = gr1;

//len �� �����
//��������� �� ���� ������, ����� ����������� ��������� �������
ar0 = ar0 - 1;
ar1 = ar1 - 1;

gr0 = [ar0];
[ar1] = gr0;


//�������� �� ��� �� ������, �� ���� ����� ���������� �� 64

LBackNoLastElement_16s:
gr0 = 63;
// ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 6;

gr3 + gr1;
if =0 delayed goto LBackLess32_16s;
gr4 = gr2 >> 1;
gr4 = gr4 - 1;

LBackCopy32_16s:
fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_16s;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_16s;
gr4 >>= 1;
gr4 = gr4 - 1;

LBackLess32_16s:
vlen = gr4;
fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

goto LExit_16s;

LLastElement_16s:
gr0 = [ar0];
[ar1] = gr0;

LExit_16s:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;



_nmppsMove_32s:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_32s;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_32s;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_32s;
gr7 = -6;
nul;

gr7 = 0;

// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_32s;
// �������� �����������
if < goto LBackCopy_32s;

LDirectCopy_32s:
gr0 = 63;
// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 6;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_32s;
gr4 = gr2 >> 1;
gr4 = gr4 - 1;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_32s:
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_32s;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_32s;
gr4 >>= 1;
gr4 = gr4 - 1;

// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_32s:
// ���������� ������������ 32-� ��������� �������
if < delayed goto LLastElement_32s;
vlen = gr4;
nul;

// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

// ��������� �������� len
gr4 = gr2 >> 1;
gr4 <<= 1;
gr4 - gr2;
// len �������, ����� ����������� ��������� 32-� ��������� �������
if <>0 goto LLastElement_32s;
if =0 goto LExit_32s;
// �������� �����������
LBackCopy_32s:
gr3 = 2;
gr2 - 1;

// ����� ����������� ����� ���� �������
if =0 delayed goto LLastElement_32s;
// ������� ��������� �� len
gr0 = gr0 + gr2;
gr1 = gr1 + gr2;

//���������� �������� len
gr4 = gr2 >> 1;
gr4 <<= 1;

gr2 - gr4;
// len �����, ��������� � ����������� �� 64 �������
if =0 delayed goto LBackNoLastElement_32s;
ar0 = gr0;
ar1 = gr1;

//len �� �����
//��������� �� ���� ������, ����� ����������� ��������� �������
ar0 = ar0 - 1;
ar1 = ar1 - 1;

gr0 = [ar0];
[ar1] = gr0;

//�������� �� ��� �� ������, �� ���� ����� ���������� �� 64

LBackNoLastElement_32s:
// ������� ��� ����� ��������� ��������� �������
gr0 = 63;
gr1 = 0;
gr3 = gr2 >> 6;

gr3 + gr1;
if =0 delayed goto LBackLess32_32s;
gr4 = gr2 >> 1;
gr4 = gr4 - 1;

LBackCopy32_32s:

fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_32s;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_32s;
gr4 >>= 1;
gr4 = gr4 - 1;
LBackLess32_32s:
vlen = gr4;
fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

goto LExit_32s;

LLastElement_32s:
gr0 = [ar0];
[ar1] = gr0;

LExit_32s:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;

_nmppsMove_64s:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_64s;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_64s;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_64s;
gr7 = -6;
nul;

gr7 = 0;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_64s;
// �������� �����������
if < goto LBackCopy_64s;

LDirectCopy_64s:
// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_64s;
gr4 = gr2 - 1;
vlen = gr4;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_64s:
gr0 = 31;
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_64s;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_64s;
gr4 = gr4 - 1;
vlen = gr4;
// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_64s:

// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

goto LExit_64s;
// �������� �����������
LBackCopy_64s:
gr3 = gr2 << 1;
// ������� ��������� �� len
gr0 = gr0 + gr3;
gr1 = gr1 + gr3;

ar0 = gr0;
ar1 = gr1;

// ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;
if =0 delayed goto LBackLess32_64s;
gr4 = gr2 - 1;
vlen = gr4;

LBackCopy32_64s:
gr0 = 31;
fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_64s;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_64s;
gr4 = gr4 - 1;
vlen = gr4;
LBackLess32_64s:

fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

LExit_64s:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;

_nmppsMove_16sc:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_16sc;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_16sc;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_16sc;
gr7 = -6;
nul;

gr7 = 0;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_16sc;
// �������� �����������
if < goto LBackCopy_16sc;

LDirectCopy_16sc:
// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_16sc;
gr4 = gr2 - 1;
vlen = gr4;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_16sc:
gr0 = 31;
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_16sc;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_16sc;
gr4 = gr4 - 1;
vlen = gr4;
// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_16sc:

// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

goto LExit_16sc;
// �������� �����������
LBackCopy_16sc:
gr3 = gr2 << 1;
// ������� ��������� �� len
gr0 = gr0 + gr3;
gr1 = gr1 + gr3;

ar0 = gr0;
ar1 = gr1;

// ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;
if =0 delayed goto LBackLess32_16sc;
gr4 = gr2 - 1;
vlen = gr4;

LBackCopy32_16sc:
gr0 = 31;
fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_16sc;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_16sc;
gr4 = gr4 - 1;
vlen = gr4;
LBackLess32_16sc:

fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

LExit_16sc:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;

_nmppsMove_32sc:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_32sc;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_32sc;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_32sc;
gr7 = -6;
nul;

gr7 = 0;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_32sc;
// �������� �����������
if < goto LBackCopy_32sc;

LDirectCopy_32sc:
// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_32sc;
gr4 = gr2 - 1;
vlen = gr4;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_32sc:
gr0 = 31;
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_32sc;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_32sc;
gr4 = gr4 - 1;
vlen = gr4;
// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_32sc:

// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

goto LExit_32sc;
// �������� �����������
LBackCopy_32sc:
gr3 = gr2 << 1;
// ������� ��������� �� len
gr0 = gr0 + gr3;
gr1 = gr1 + gr3;

ar0 = gr0;
ar1 = gr1;

// ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 5;

gr3 + gr1;
if =0 delayed goto LBackLess32_32sc;
gr4 = gr2 - 1;
vlen = gr4;

LBackCopy32_32sc:
gr0 = 31;
fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_32sc;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_32sc;
gr4 = gr4 - 1;
vlen = gr4;
LBackLess32_32sc:

fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

LExit_32sc:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;

_nmppsMove_64sc:
ar5 = ar7 - 2;
push ar0, gr0;
push ar1, gr1;
push ar2, gr2;
push ar3, gr3;
push ar4, gr4;

gr3 = 0;

gr0 = [--ar5]; // pSrc
gr0 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_64sc;
gr7 = -8;
nul;

gr1 = [--ar5]; // pDst
gr1 - gr3;
// �������� �� NULL
if =0 delayed goto LExit_64sc;
gr7 = -8;
nul;

gr2 = [--ar5]; // len
//������ ������ ���� ������ 0
gr2 - 1;
if < delayed goto LExit_64sc;
gr7 = -6;
nul;

gr7 = 0;

//��������� �������� �������� ������������ ���� �����
gr0 - gr1;

// ������ ������������
if > goto LDirectCopy_64sc;
// �������� �����������
if < goto LBackCopy_64sc;

LDirectCopy_64sc:
// ������������� ��������� ���������
ar0 = gr0;
ar1 = gr1;

// ���������� ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 4;

gr3 + gr1;
// �� ���� �� �����, �������� ������� ����
if =0 delayed goto LDirectLess32_64sc;
gr4 = gr2 << 1;
gr4 = gr4 - 1;

// �������� �� 32 64-� ��������� �����
LDirectCopy32_64sc:
gr0 = 31;
fpu 0 rep 32 vreg0 = [ar0++];
fpu 0 rep 32 [ar1++] = vreg0;
gr3 = gr3 - 1;
if > goto LDirectCopy32_64sc;

// ���������� ��� �� �����������
gr4 = gr0 and gr2;
// ����������� ��� ��������
if =0 delayed goto LExit_64sc;
gr4 = gr4 << 1;
gr4 = gr4 - 1;

// �������� ������ ��� �� 32 64-� ��������� �����
LDirectLess32_64sc:
vlen = gr4;
// ����������� 64-� ��������� ��������
fpu 0 rep vlen vreg0 = [ar0++];
fpu 0 rep vlen [ar1++] = vreg0;

goto LExit_64sc;
// �������� �����������
LBackCopy_64sc:
gr3 = gr2 << 2;
// ������� ��������� �� len
gr0 = gr0 + gr3;
gr1 = gr1 + gr3;

ar0 = gr0;
ar1 = gr1;

// ������� ��� ����� ��������� ��������� �������
gr1 = 0;
gr3 = gr2 >> 4;

gr3 + gr1;
if =0 delayed goto LBackLess32_64sc;
gr4 = gr2 << 1;
gr4 = gr4 - 1;

LBackCopy32_64sc:
gr0 = 31;
fpu 0 rep 32 vreg0 = [--ar0];
fpu 0 rep 32 [--ar1] = vreg0;
gr3 = gr3 - 1;
if > goto LBackCopy32_64sc;

gr4 = gr0 and gr2;

// ����������� ��� ��������
if =0 delayed goto LExit_64sc;
gr4 = gr4 << 1;
gr4 = gr4 - 1;
LBackLess32_64sc:
vlen = gr4;
fpu 0 rep vlen vreg0 = [--ar0];
fpu 0 rep vlen [--ar1] = vreg0;

LExit_64sc:
pop ar4, gr4;
pop ar3, gr3;
pop ar2, gr2;
pop ar1, gr1;
pop ar0, gr0;

return;



