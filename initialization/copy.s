.globl _nmppsCopy_16sc
.globl _nmppsCopy_32sc
.globl _nmppsCopy_64sc
.globl _nmppsCopy_1u


.text

_nmppsCopy_16sc:
_nmppsCopy_32sc:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; // pSrc
  // Проверка на NULL
  gr0;
  if =0 delayed goto Lexit_16sc;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // pDst
  gr1;
  // Проверка на NULL
  if =0 delayed goto Lexit_16sc;
  gr7 = -8;
  ar1 = gr1;

  gr2 = [--ar5]; // len
  // Проверка корректности значения количества копируемыых элементов
  gr2;
  if <= delayed goto Lexit_16sc;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Сколько раз можем полностью загрузить векторный регистр
  gr1 = gr2 >> 5;

  gr1;
  if =0 delayed goto Lless32_16sc;
  gr0 = gr2 - 1 ;
  vlen = gr0;

// Копирование по 32 слова
Lcopy32_16sc:
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 rep 32 [ar1++] = vreg0;

  gr1 = gr1 - 1;
  if > goto Lcopy32_16sc;

  // Проверим все ли скопировали
  gr0 = 31;
  gr1 = gr2 and gr0;

  if =0 delayed goto Lexit_16sc;
  gr1 = gr1 - 1;
  vlen = gr1;

// Копирование меньше 32 слов
Lless32_16sc:

  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen [ar1++] = vreg0;

Lexit_16sc:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;

_nmppsCopy_64sc:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; // pSrc
  // Проверка на NULL
  gr0;
  if =0 delayed goto Lexit_64sc;
  gr7 = -8;
  ar0 = gr0;

  gr1 = [--ar5]; // pDst
  // Проверка на NULL
  gr1;
  if =0 delayed goto Lexit_64sc;
  gr7 = -8;
  ar1 = gr1;

  gr2 = [--ar5]; // len
  // Проверка корректности значения количества копируемыых элементов
  gr2;
  if <= delayed goto Lexit_64sc;
  gr7 = -6;
  nul;

  gr7 = 0;

  // Сколько раз можем полностью загрузить векторный регистр
  gr1 = gr2 >> 4;

  gr3;

  if =0 delayed goto Lless32_64sc;
  gr0 = gr2;
  gr0 <<= 1;

// Копирование по 32 слова
Lcopy32_64sc:
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 rep 32 [ar1++] = vreg0;
  gr1 = gr1 - 1;

  if > goto Lcopy32_64sc;

  // Проверим все ли скопировали
  gr1 = 15;
  gr0 = gr2 and gr1;

  if =0 delayed goto Lexit_64sc;
  gr0 <<= 1;
  nul;

// Копирование меньше 32 слов
Lless32_64sc:
  gr0 = gr0 - 1;
  vlen = gr0;
  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen [ar1++] = vreg0;

Lexit_64sc:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


_nmppsCopy_1u:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;
  push ar4, gr4;
  push ar5, gr5;
  push ar6, gr6;

  gr0 = [--ar5]; // pSrc
  gr0;
  if =0 goto Lerr_ptr_1u;
  ar0 = gr0;

  gr1 = [--ar5]; // srcBitOffset
  gr0 = 7;
  gr1 - gr0;
  if > goto Lerr_size_1u;
  gr1;
  if < goto Lerr_size_1u;


  gr2 = [--ar5]; // pDst
  gr2;
  if =0 goto Lerr_ptr_1u;
  ar2 = gr2;

  gr3 = [--ar5]; // dstBitOffset
  gr3 - gr0;
  if > goto Lerr_size_1u;
  gr3;
  if < goto Lerr_size_1u;

  gr0 = [--ar5]; // len
  gr0;
  if <= goto Lerr_size_1u;

  //Выделение места для массивов масок

  /*
   * ar1 ... ar1 + 8 - массив масок входного вектора
   * ar1 + 9 ... ar1 + 16 - массив масок выходного вектора
   */

  ar1 = ar7 + 2;
  ar7 = ar7 + 18;


  //Инициализация масок входного вектора
  //значения: 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
  ar5 = ar1;
  gr4 = 0x80;
  gr2 = 8;

  Linit_loop1:

  [ar5++] = gr4;
  gr4 = gr4 >> 1;
  gr2 = gr2 - 1;
  if > goto Linit_loop1;

  //Инициализация масок выходного вектора
  //значения: 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE
  gr4 = 0x80;
  gr2 = 8;
  gr5 = 0xFF;
Lloop_init2:

  gr6 = gr4 xor gr5;
  [ar5++] = gr6;
  gr4 = gr4 >> 1;

  gr2 = gr2 - 1;
  if > goto Lloop_init2;

  //Указатель на входной вектор для перемещения по нему
  ar4 = ar0;
  //Указатель на выходной вектор для перемещения по нему
  ar6 = ar2;

  //Цикл копирования
Lloop:

  // Выделяем копируемый разряд
  gr2 = [ar4];
  gr5 = [ar1 + gr1];
  gr6 = gr2 and gr5;

  // Определяем направление сдвига
  gr2 = gr1 - gr3;

  gr2;
  if > goto Lleft_shift_data;

// Сдвиг копироваемого разряда вправо на разность dstBitOffset - srcBitOffset
gr2 = gr3 - gr1;
Lright_shift_data:
  gr6 >>= 1;
  gr2 = gr2 - 1;
  if > goto Lright_shift_data;

  goto Lcontinue_loop;

// Сдвиг копироваемого разряда вправо на разность srcBitOffset - dstBitOffset
Lleft_shift_data:

  gr6 <<= 1;
  gr2 = gr2 - 1;
  if > goto Lleft_shift_data;

//Продолжение копирования
Lcontinue_loop:

  // выделяем разяряд в который копируем
  gr2 = gr1;
  gr1 = 8;
  gr1 = gr1 + gr3;
  gr5 = [ar1 + gr1];
  gr1 = gr2;

  // Формирование копируемого слова
  gr2 = [ar6];
  gr2 = gr2 and gr5;
  gr2 = gr2 or gr6;

  /// Копирование
  [ar6] = gr2;

  // Перемещение на одни разряд по входному вектору
  gr4 = gr1 + 1;
  gr4 = gr4 >> 3;
  ar4 = ar4 + gr4;

  // Перемещение на один разряд по выходному вектору
  gr6 = gr3 + 1;
  gr6 = gr6 >> 3;
  ar6 = ar6 + gr6;

  gr6 = 7;

  // Инкремент srcBitOffset
  gr1 = gr1 + 1;
  gr1 = gr1 and gr6;

  // Инкремент dstBitOffset
  gr3 = gr3 + 1;
  gr3 = gr3 and gr6;

  // Счетчик цикла копирования
  gr0 = gr0 - 1;
  if > goto Lloop;

  goto Lexit_1u;
Lerr_ptr_1u:
    gr7 = -8;
    goto Lexit_with_err_1u;

Lerr_size_1u:
    gr7 = -6;
    goto Lexit_with_err_1u;

Lexit_1u:
  ar7 = ar7 - 18;

Lexit_with_err_1u:
  pop ar6, gr6;
  pop ar5, gr5;
  pop ar4, gr4;
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;

