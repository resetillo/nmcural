.globl _nmppsAbs_32f
.globl _nmppsAbs_64f

.data
SIGN_BIT:
  .quad 0x7fffffff

.text

_nmppsAbs_32f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; // pSrc
  // Проверка на NULL
  gr0;
  if =0 delayed goto LExit_32f;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // pDst
   // Проверка на NULL
  gr1;
  if =0 delayed goto LExit_32f;
  gr7 = -8;
  ar1 = gr1;

  gr2 = [--ar5]; // len
  //Количество элементов должно быть больше 0
  gr2 - 1;
  if < delayed goto LExit_32f;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Сколько раз можем полностью загрузить вектор
  gr0 = gr2 >> 6;

  gr0;
  if =0 delayed goto LLess32_32f;
  gr1 = gr2;
  nul;

// Вычисление модуля по 32 слова
LAbs32_32f:
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 .float vreg0 = /vreg0/;
  fpu 0 rep 32 [ar1++] = vreg0;

  gr0 = gr0 - 1;
  if > goto LAbs32_32f;

  gr0 = 63;
  gr1 = gr0 and gr2;

  // Вычислили для всех элементов, выходим
  if =0 goto LExit_32f;

// Вычисление модуля меньшее чем для 32 слов
LLess32_32f:
  gr1 >>= 1;

  gr1;
  // Вычисление модуля для последнего элемента
  if =0 delayed goto LLastElement_32f;
  gr1 = gr1 - 1;
  vlen = gr1;

  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 .float vreg0 = /vreg0/;
  fpu 0 rep vlen [ar1++] = vreg0;

  // проверяем четность len
  gr0 = 1;
  gr0 and gr2;
  // len четно, выходим
  if =0 goto LExit_32f;

// Модуль для последнего элемента
LLastElement_32f:
  gr1 = [SIGN_BIT];
  gr0 = [ar0];
  gr0 = gr0 and gr1;
  [ar1] = gr0;
LExit_32f:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;



_nmppsAbs_64f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; // pSrc
  // Проверка на NULL
  gr0;
  if =0 delayed goto LExit_64f;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // pDst
  // Проверка на NULL
  gr1;
  if =0 delayed goto LExit_64f;
  gr7 = -8;
  ar1 = gr1;

  gr2 = [--ar5]; // len
  //Количество элементов должно быть больше 0
  gr2 - 1;
  if < delayed goto LExit_64f;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Сколько раз можем полностью загрузить вектор
  gr0 = gr2 >> 5;

  gr0;
  if =0 delayed goto LLess32_64f;
  gr1 = gr2;
  nul;

// Вычисление модуля по 32 слова
LAbs32_64f:
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 .double vreg0 = /vreg0/;
  fpu 0 rep 32 [ar1++] = vreg0;

  gr0 = gr0 - 1;
  if > goto LAbs32_64f;

  gr0 = 63;
  gr1 = gr0 and gr2;

  // Вычислили для всех элементов, выходим
  if =0 goto LExit_64f;

// Вычисление модуля меньшее чем для 32 слов
LLess32_64f:

  gr1 = gr1 - 1;
  vlen = gr1;

  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 .double vreg0 = /vreg0/;
  fpu 0 rep vlen [ar1++] = vreg0;

LExit_64f:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;
