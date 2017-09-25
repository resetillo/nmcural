.globl _nmppsLShiftC_8u
.globl _nmppsLShiftC_16u
.globl _nmppsLShiftC_16s
.globl _nmppsLShiftC_32s
.globl _nmppsLShiftC_8u_I
.globl _nmppsLShiftC_16u_I
.globl _nmppsLShiftC_16s_I
.globl _nmppsLShiftC_32s_I


.globl _arrShiftlData

_nmppsLShiftC_8u_I:
_nmppsLShiftC_16u_I:
_nmppsLShiftC_16s_I:
_nmppsLShiftC_32s_I:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;


  gr0 = [--ar5]; // val

  gr1 = [--ar5]; // pSrc

  //Проверка на NULL
  gr1;
  if =0 goto err_ptr;

  ar1 = gr1;
  ar0 = ar1;

  gr1= [--ar5];
  // Длина должна быть больше нуля
  gr1;
  if <= goto err_size;

  goto shift_left;

_nmppsLShiftC_8u:
_nmppsLShiftC_16u:
_nmppsLShiftC_16s:
_nmppsLShiftC_32s:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;


  gr0 = [--ar5]; // pSrc

  //Проверка на NULL
  gr0;
  if =0 goto err_ptr;

  ar0 = gr0;

  gr0 = [--ar5]; // val

  //[1 ... 63]
  //FIXME: контролировать ли величину сдвига в зависимости от разрядности типа данных?
  //gr2 = 63;
  //gr1;
  //if <= goto err_size_32;
  //gr1 - gr2;
  //if > goto err_size_32;

  gr1 = [--ar5]; // pDst

  // Проверка на NULL
  gr1;
  if =0 goto err_ptr;

  ar1 = gr1;

  gr1= [--ar5];
  // Длина должна быть больше нуля
  gr1;
  if <= goto err_size;


shift_left:
  // Буфер на 64 слова
  ar3 = ar7 + 2;
  ar7 = ar7 + 66;
  ar5 = ar3;

  gr7 = 0;

  ar2 = _arrShiftlData;

  // Разбиение рабочей матрицы: 2 х 2
  sir = 80000000h;
  nb1 = sir;
  sir = 03h;
  sb = sir;

  gr2 = gr0 << 1;
  gr3 = 2;
  gr2 = gr2 - gr3;
  gr2 = gr2 << 1;

  ar2 = ar2 + gr2;

  /// Загрузка матрицы
  rep 2 wfifo = [ar2++], ftw, wtw;

  /// Количество итераций
  gr2 = gr1 >> 6;
  gr2;

  if =0 delayed goto shift_less_64;
  gr3 = gr1 >> 1;
  gr3 = gr3 - 1;

/// Двигаем по 64 слова
shift64:
  /// Сдвиг через взвешенное суммирование
  rep 32 data = [ar0++] with vsum, data, 0;
  /// Выгрузка в выходной вектор
  rep 32 [ar1++] = afifo;

  gr2 = gr2 - 1;
  if > goto shift64;

  /// Определим все ли сдвинули
  gr2 = 63;
  gr3 = gr2 and gr1;

  if =0 delayed goto exit;
  gr3 = gr3 >> 1;
  gr3 = gr3 - 1;

shift_less_64:

  /// Сдвиг через взвешенное суммирование
  rep 32 data = [ar0++] with vsum, data, 0;
  /// Выгрузка в буфер
  rep 32 [ar5++] = afifo;

  ar5 = ar3;

  vlen = gr3;

  /// Из буфера выгружаем необходимое количество слов
  fpu 0 rep vlen vreg0 = [ar5++];
  fpu 0 rep vlen [ar1++] = vreg0;

  /// Проверим четность len
  gr2 = 1;
  gr2 and gr1;

  if =0 goto exit;

  gr2 = [ar5];
  [ar1] = gr2;

  goto exit;

// Нулевой указатель на вектор
err_ptr:
  gr7 = -8;
  goto exit_error;

// Некорректное значение длины вектора
err_size:
  gr7 = -6;
  goto exit_error;

exit:
  ar7 = ar7 - 66;

exit_error:
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;
