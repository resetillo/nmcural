.globl _nmppsZero_8u
.globl _nmppsZero_16s
.globl _nmppsZero_32s
.globl _nmppsZero_64s
.globl _nmppsZero_16sc
.globl _nmppsZero_32sc
.globl _nmppsZero_64sc

.text

_nmppsZero_8u:
_nmppsZero_16s:
_nmppsZero_32s:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;


  gr0 = [--ar5]; // pDst
  // Проверка на NULL
  gr0;
  if =0 delayed goto Lerror_exit_8u;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // len
  // Количество инициализируемых элементов должно быть больше 0
  gr1 - 1;
  if < delayed goto Lerror_exit_8u;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Выделение в места для записи 64-х разярдного нуля
  ar1 = ar7 + 2;
  ar7 = ar7 + 4;

  // Запись в стек 64-х разярдного нуля
  gr0 = 0;
  ar5 = ar1;
  [ar5] = gr0;
  ar5 = ar5 + 1;
  [ar5] = gr0;

  // Сколько раз можем инициализировать по 32 слова
  gr0 = gr1 >> 6;

  gr0;

  // Ниодного раза
  if  =0 delayed goto Lless32_8u;
  gr2 = gr1 >> 1 ;
  gr2 = gr2 - 1;

  // Загрузка нулей
  fpu 0 rep 32 vreg0 = [ar1];

// Инициализация по 32 слова
Lzero32_8u:
  fpu 0 rep 32 [ar0++] = vreg0;
  gr0 = gr0 - 1;
  if > goto Lzero32_8u;

  gr0 = 63;
  gr2 = gr0 and gr1;

  // Инициализировали все элементы, выходим
  if =0 delayed goto Lexit_8u;
  gr2 >>= 1;
  gr2 = gr2 - 1;

// Инициализация менее 32 слов
Lless32_8u:
  // Необходимо инициализировать 32-разрядный остаток
  if < delayed goto LlastElement_8u;
  vlen = gr2;
  nul;

  fpu 0 rep vlen vreg0 = [ar1];
  fpu 0 rep vlen [ar0++] = vreg0;

  //Проверяем четность len
  gr0 = 1;
  gr0 and gr1;

  // len четно, выходим
  if =0 goto Lexit_8u;

// len нечетно, доинициализируем 32-разрядный остаток
LlastElement_8u:
  gr0 = 0;
  [ar0] = gr0;

Lexit_8u:
  ar7 = ar7 - 4;

Lerror_exit_8u:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;



_nmppsZero_64s:
_nmppsZero_16sc:
_nmppsZero_32sc:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;


  gr0 = [--ar5]; // pDst
  // Проверка на NULL
  gr0;
  if =0 delayed goto Lerror_exit_64s;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // len
  // Количество инициализируемых элементов должно быть больше 0
  gr1 - 1;
  if < delayed goto Lerror_exit_64s;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Выделение в места для записи 64-х разярдного нуля
 ar1 = ar7 + 2;
 ar7 = ar7 + 4;

  // Запись в стек 64-х разярдного нуля
  gr0 = 0;
  ar5 = ar1;
  [ar5] = gr0;
  ar5 = ar5 + 1;
  [ar5] = gr0;

  // Сколько раз можем инициализировать по 32 слова
  gr0 = gr1 >> 5;

  gr0;

  // Ни одного раза
  if =0 delayed goto Lless32_64s;
  gr2 = gr1 - 1 ;
  vlen = gr2;

  // Загрузка нулей
  fpu 0 rep 32 vreg0 = [ar1];

// Инициализация по 32 слова
Lzero32_64s:
  fpu 0 rep 32 [ar0++] = vreg0;
  gr0 = gr0 - 1;
  if > goto Lzero32_64s;

  gr0 = 31;
  gr2 = gr0 and gr1;

  // Инициализировали все элементы, выходим
  if =0 delayed goto Lexit_64s;
  gr2 = gr2 - 1;
  vlen = gr2;

// Инициализация менее 32 слов
Lless32_64s:

  fpu 0 rep vlen vreg0 = [ar1];
  fpu 0 rep vlen [ar0++] = vreg0;

Lexit_64s:
  ar7 = ar7 - 4;

Lerror_exit_64s:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


_nmppsZero_64sc:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; // pDst
  // Проверка на NULL
  gr0;
  if =0 delayed goto Lerror_exit_64sc;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // len
  // Количество инициализируемых элементов должно быть больше 0
  gr1;
  if < delayed goto Lerror_exit_64sc;
  gr7 = -6;
  nul;

  gr7 = 0;

  //Выделение в места для записи 64-х разярдного нуля
  ar1 = ar7 + 2;
  ar7 = ar7 + 4;

  // Запись в стек 64-х разярдного нуля
  gr0 = 0;
  ar5 = ar1;
  [ar5] = gr0;
  ar5 = ar5 + 1;
  [ar5] = gr0;

  // Сколько раз можем инициализировать по 32 слова
  gr0 = gr1 >> 4;

  gr0;

  // Ни одного раза
  if =0 delayed goto Lless32_64sc;
  gr2 = gr1 << 1 ;
  gr2 = gr2 - 1;

  // Загрузка нулей
  fpu 0 rep 32 vreg0 = [ar1];

// Инициализация по 32 слова
Lzero32_64sc:
  fpu 0 rep 32 [ar0++] = vreg0;
  gr0 = gr0 - 1;
  if > goto Lzero32_64sc;

  gr0 = 15;
  gr2 = gr0 and gr1;

  // Инициализировали все элементы, выходим
  if =0 delayed goto Lexit_64sc;
  gr2 <<= 1;
  gr2 = gr2 - 1;


// Инициализация менее 32 слов
Lless32_64sc:
  vlen = gr2;

  fpu 0 rep vlen vreg0 = [ar1];
  fpu 0 rep vlen [ar0++] = vreg0;

Lexit_64sc:
  ar7 = ar7 - 4;

Lerror_exit_64sc:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;







