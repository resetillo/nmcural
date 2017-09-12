.globl _nmppsSum_16s_Sfs
.globl _nmppsSum_32s_Sfs

_nmppsSum_16s_Sfs:
_nmppsSum_32s_Sfs:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; //psrc1
  gr0;
  if =0 goto err_ptr;

  ar0 = gr0;

  gr0 = [--ar5]; // len
  gr0;
  if <= goto err_size;

  gr1 = [--ar5]; // sum
  gr1;
  if =0 goto err_ptr;

  ar1 = gr1;

  gr1 = [--ar5]; // scale_factor

  //gr7 = 0;

  //gr0 - 1;
  //if =0 goto exit_one_element;

  // Буфер
  ar2 = ar7 + 2;
  ar7 = ar7 + 66;

  // Формирование в буфере 64-разрядной единицы для загрузки в матрицу
  ar5 = ar2;
  gr2 = 1;
  [ar5] = gr2;
  ar5 = ar5 + 1;
  gr2 = 0;
  [ar5] = gr2;

  // Разбиение рабочей матрицы: 2 х 1
  sir = 0;
  nb1 = sir;
  sir = 03h;
  sb = sir;

  rep 2 wfifo = [ar2], ftw, wtw;

  // Количество итераций суммирования по 32 элемента
  gr2 = gr0 >> 6;
  if =0 goto sum_less_32;

sum_over_32:

  rep 32 data = [ar0++] with vsum, data, afifo;

  gr2 = gr2 - 1;

  if > goto sum_over_32;

  gr2 = 63;
  gr0 = gr2 and gr0;

  if =0 goto upload_result;

sum_less_32:

  gr2 = 0;
  [ar2] = gr2;
  ar2 = ar2 + 1;
  [ar2] = gr2;
  ar2 = ar2 - 1;

  fpu 0 rep 32 vreg0 = [ar2];

  ar5 = ar2;
  fpu 0 rep 32 [ar5++] = vreg0;

  gr2 = gr0 >> 1;
  gr2 = gr2 - 1;
  vlen = gr2;

  ar5 = ar2;
  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen [ar5++] = vreg0;

  gr2 = 1;
  gr0 and gr2;
  if =0 goto go_sum_less_32;

  gr0 = [ar0];
  [ar5] = gr0;

go_sum_less_32:
  ar5 = ar2;
  rep 31 data = [ar5++] with vsum, data, afifo;

upload_result:
  /// Сохраняем результат в буфер
  rep 1 [ar2] = afifo;

scale:

  /// Перед масшатибированием преобразуем в double
  fpu rep 1 .packer = [ar2] with .double <= .fixed_64;
  fpu rep 1 [ar2] = .packer;

  ar0 = ar2;
  gr0 = gr1;

  call scale_f64;
  goto exit;


exit_one_element:
  gr0 = [ar0];
  [ar1] = gr0;

  goto exit_error;

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
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;





















