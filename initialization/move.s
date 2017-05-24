.globl _nmppsMove_8u
.globl _nmppsMove_16s
.globl _nmppsMove_32s
.globl _nmppsMove_64s
.globl _nmppsMove_16sc
.globl _nmppsMove_32sc
.globl _nmppsMove_64sc

.text
_nmppsMove_8u:
_nmppsMove_16s:
_nmppsMove_32s:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;
  push ar4, gr4;

  gr0 = [--ar5]; // pSrc
  gr0;
  // Проверка на NULL
  if =0 delayed goto LExit_8u;
  gr7 = -8;
  nul;

  gr1 = [--ar5]; // pDst
  gr1;
  // Проверка на NULL
  if =0 delayed goto LExit_8u;
  gr7 = -8;
  nul;

  gr2 = [--ar5]; // len
  //Количестов копируемых элементов должно быть больше 0
  gr2 - 1;
  if < delayed goto LExit_8u;
  gr7 = -6;
  nul;

  gr7 = 0;

  //Определение смещения векторов относительно друг друга
  gr0 - gr1;

  // Прямое копирование
  if > goto LDirectCopy_8u;
  // Обратное копирование
  if < goto LBackCopy_8u;

// Прямое копирование
LDirectCopy_8u:
  ar0 = gr0;
  ar1 = gr1;

  gr0 = 63;
  // Сколько раз можем полностью загрузить регистр
  gr3 = gr2 >> 6;

  gr3;
  // Ни разу не можем, копируем сколько есть
  if =0 delayed goto LDirectLess32_8u;
  gr4 = gr2 >> 1;
  gr4 = gr4 - 1;

// Копирование по 32 слова
LDirectCopy32_8u:
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 rep 32 [ar1++] = vreg0;
  gr3 = gr3 - 1;
  if > goto LDirectCopy32_8u;

  // Определяем все ли скопировали
  gr4 = gr0 and gr2;

  if =0 delayed goto LExit_8u;
  gr4 >>= 1;
  gr4 = gr4 - 1;

// Копирование меньше чем 32 слова
LDirectLess32_8u:
  // Копирование последнего 32-х разрядного элемента
  if < goto LLastElement_8u;

  vlen = gr4;

  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen [ar1++] = vreg0;

  // Определим четность len
  gr4 = 1;
  gr4 and gr2;
  // len нечетно, копируем последний 32-х разрядный элемент
  if <>0 goto LLastElement_8u;
  // len четно, выходим
  if =0 goto LExit_8u;

// Обратное копирование
LBackCopy_8u:
  gr3 = 2;
  gr2 - 1;

  // Нужно скопировать всего один элемент
  if =0 delayed goto LLastElement_8u;
  // Сдвигаем указатели на len
  gr0 = gr0 + gr2;
  gr1 = gr1 + gr2;

  //Определяем четность len
  gr4 = 1;
  gr2 and gr4;
  // len четно, переходим к копированию по 32 слова
  if =0 delayed goto LBackNoLastElement_8u;
  ar0 = gr0;
  ar1 = gr1;

  //len не четно
  // Двигаемся на один вперед, чтобы скопировать последний элемент
  ar0 = ar0 - 1;
  ar1 = ar1 - 1;

  gr0 = [ar0];
  [ar1] = gr0;

  // Остаемся на том же адресе, от него будем копировать по 64 разряда

LBackNoLastElement_8u:
  // Сколько раз можем полностью загрузить регистр
  gr0 = 63;
  gr3 = gr2 >> 6;

  gr3;
  if =0 delayed goto LBackLess32_8u;
  gr4 = gr2 >> 1;
  gr4 = gr4 - 1;

// Копирование по 32 слова
LBackCopy32_8u:

  fpu 0 rep 32 vreg0 = [--ar0];
  fpu 0 rep 32 [--ar1] = vreg0;
  gr3 = gr3 - 1;
  if > goto LBackCopy32_8u;

  // Проверяем все ли скопировали
  gr4 = gr0 and gr2;

  if =0 delayed goto LExit_8u;
  gr4 >>= 1;
  gr4 = gr4 - 1;

// Копирование меньше, чем по 32 слова
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


_nmppsMove_64s:
_nmppsMove_16sc:
_nmppsMove_32sc:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;
  push ar4, gr4;

  gr0 = [--ar5]; // pSrc
  gr0;
  // Проверка на NULL
  if =0 delayed goto LExit_64s;
  gr7 = -8;
  nul;

  gr1 = [--ar5]; // pDst
  gr1;
  // Проверка на NULL
  if =0 delayed goto LExit_64s;
  gr7 = -8;
  nul;

  gr2 = [--ar5]; // len
  //Количестов копируемых элемнтов должно быть больше 0
  gr2 - 1;
  if < delayed goto LExit_64s;
  gr7 = -6;
  nul;

  gr7 = 0;

  //Определение смещения векторов относительно друг друга
  gr0 - gr1;

  // Прямое копирование
  if > goto LDirectCopy_64s;
  // Обратное копирование
  if < goto LBackCopy_64s;


// Прямое копирование
LDirectCopy_64s:
  ar0 = gr0;
  ar1 = gr1;

  // Сколько раз можем полностью загрузить регистр
  gr3 = gr2 >> 5;

  gr3;
  // Ни разу не можем, копируем сколько есть
  if =0 delayed goto LDirectLess32_64s;
  gr4 = gr2 - 1;
  vlen = gr4;

// Копирование по 32 слова
LDirectCopy32_64s:
  gr0 = 31;
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 rep 32 [ar1++] = vreg0;
  gr3 = gr3 - 1;
  if > goto LDirectCopy32_64s;

  // Определяем все ли скопировали
  gr4 = gr0 and gr2;

  if =0 delayed goto LExit_64s;
  gr4 = gr4 - 1;
  vlen = gr4;

// Копирование меньше чем 32 слова
LDirectLess32_64s:

  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen [ar1++] = vreg0;

  goto LExit_64s;

// Обратное копирование
LBackCopy_64s:
  gr3 = gr2 << 1;
  //Сдвигаем указатели на len * 2
  gr0 = gr0 + gr3;
  gr1 = gr1 + gr3;

  ar0 = gr0;
  ar1 = gr1;

  // Сколько раз можем полностью загрузить регистр
  gr3 = gr2 >> 5;

  gr3;
  if =0 delayed goto LBackLess32_64s;
  gr4 = gr2 - 1;
  vlen = gr4;

// Копирование по 32 слова
LBackCopy32_64s:
  gr0 = 31;
  fpu 0 rep 32 vreg0 = [--ar0];
  fpu 0 rep 32 [--ar1] = vreg0;
  gr3 = gr3 - 1;
  if > goto LBackCopy32_64s;

  gr4 = gr0 and gr2;

  // Проверяем все ли скопировали
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


_nmppsMove_64sc:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;
  push ar4, gr4;

  gr0 = [--ar5]; // pSrc
  gr0;
  // Проверка на NULL
  if =0 delayed goto LExit_64sc;
  gr7 = -8;
  nul;

  gr1 = [--ar5]; // pDst
  gr1;
  // Проверка на NULL
  if =0 delayed goto LExit_64sc;
  gr7 = -8;
  nul;

  gr2 = [--ar5]; // len
  //Количестов копируемых элементов должно быть больше 0
  gr2 - 1;
  if < delayed goto LExit_64sc;
  gr7 = -6;
  nul;

  gr7 = 0;

  //Определение смещения векторов относительно друг друга
  gr0 - gr1;

  // Прямое копирование
  if > goto LDirectCopy_64sc;
  // Обратное копирование
  if < goto LBackCopy_64sc;

LDirectCopy_64sc:
  ar0 = gr0;
  ar1 = gr1;

  // Сколько раз можем полностью загрузить регистр
  gr3 = gr2 >> 4;

  gr3;
  // Ни разу не можем, копируем сколько есть
  if =0 delayed goto LDirectLess32_64sc;
  gr4 = gr2 << 1;
  gr4 = gr4 - 1;

// Копирование по 32 слова
LDirectCopy32_64sc:
  gr0 = 15;
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 rep 32 [ar1++] = vreg0;
  gr3 = gr3 - 1;
  if > goto LDirectCopy32_64sc;

  // Определяем все ли скопировал
  gr4 = gr0 and gr2;

  if =0 delayed goto LExit_64sc;
  gr4 = gr4 << 1;
  gr4 = gr4 - 1;

// Копирование меньше чем 32 слова
LDirectLess32_64sc:
  vlen = gr4;
  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen [ar1++] = vreg0;

  goto LExit_64sc;

// Обратное копирование
LBackCopy_64sc:
  gr3 = gr2 << 2;
  // Сдвигаем указатели на len / 2
  gr0 = gr0 + gr3;
  gr1 = gr1 + gr3;

  ar0 = gr0;
  ar1 = gr1;

  // Сколько раз можем полностью загрузить регистр
  gr3 = gr2 >> 4;

  gr3;
  if =0 delayed goto LBackLess32_64sc;
  gr4 = gr2 << 1;
  gr4 = gr4 - 1;

// Копирование по 32 слова
LBackCopy32_64sc:
  gr0 = 15;
  fpu 0 rep 32 vreg0 = [--ar0];
  fpu 0 rep 32 [--ar1] = vreg0;
  gr3 = gr3 - 1;
if > goto LBackCopy32_64sc;

  // Проверяем все ли скопировали
  gr4 = gr0 and gr2;

  if =0 delayed goto LExit_64sc;
  gr4 = gr4 << 1;
  gr4 = gr4 - 1;

// Копирование меньше, чем по 32 слова
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



