.globl _nmppsSet_16sc
.globl _nmppsSet_32sc
.globl _nmppsSet_64sc

.text

_nmppsSet_16sc:
_nmppsSet_32sc:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  ar2 = [--ar5]; // val

  gr1 = [--ar5]; // pDst
  // Проверка на NULL
  gr1;
  if =0 delayed goto Lexit_16sc;
  gr7 = -8;
  ar1 = gr1;

  gr2 = [--ar5]; // len
  // Количество инициализируемых элементов должно быть больше 0
  gr2 - 1;
  if < delayed goto Lexit_16sc;
  gr7 = -6;
  nul;

  gr7 = 0;


  // Сколько раз можем загрузить вектор
  gr1 = gr2 >> 5;

  gr1;

  // Меньше чем 32 слова, инициализируем len элементов
  if =0 delayed goto Lless32_16sc;
  gr0 = gr2 - 1 ;
  vlen = gr0;

  fpu 0 rep 32 vreg0 = [ar2];

// Инициализация по 32 слова
Lset32_16sc:
  fpu 0 rep 32 [ar1++] = vreg0;
  gr1 = gr1 - 1;

  if > goto Lset32_16sc;

  gr0 = 31;
  gr1 = gr2 and gr0;

  // Инициализировали все элементы, выходим
  if =0 delayed goto Lexit_16sc;
  gr1 = gr1 - 1;
  vlen = gr1;

// Инициализация менее 32 слов
Lless32_16sc:
  fpu 0 rep vlen vreg0 = [ar2];
  fpu 0 rep vlen [ar1++] = vreg0;

Lexit_16sc:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;

_nmppsSet_64sc:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  ar2 = [--ar5]; // val

  gr1 = [--ar5]; // pDst
  // Проверка на NULL
  gr1;
  if =0 delayed goto Lexit_64sc;
  gr7 = -8;
  ar1 = gr1;

  gr2 = [--ar5]; // len
  // Количество инициализируемых элементов должно быть больше 0
  gr2 - 1;
  if < delayed goto Lexit_64sc;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Сколько раз можем полностью загрузить регистр
  gr1 = gr2 >> 4;

  // Меньше чем 32 слова
  gr1;
  if =0 delayed goto Lless32_64sc;
  gr0 = gr2;
  gr0 <<= 1;

  fpu 0 rep 32 vreg0 = [ar2];

// Инициализация по 32 слова
Lset32_64sc:
  fpu 0 rep 32 [ar1++] = vreg0;
  gr1 = gr1 - 1;

  if > goto Lset32_64sc;

  gr1 = 15;
  gr0 = gr2 and gr1;

  // Инициализировали все элементы, выходим
  if =0 delayed goto Lexit_64sc;
  gr0 = gr0 - 1;
  nul;

// Инициализация меньше 32 слов
Lless32_64sc:

  vlen = gr0;

  fpu 0 rep vlen vreg0 = [ar2];
  fpu 0 rep vlen [ar1++] = vreg0;

Lexit_64sc:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;
