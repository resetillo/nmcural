.globl _nmppsThreshold_GTAbs_16s
.globl _nmppsThreshold_GTAbs_32s
.globl _nmppsThreshold_GTAbs_32f
.globl _nmppsThreshold_GTAbs_64f

.text

_nmppsThreshold_GTAbs_16s:
_nmppsThreshold_GTAbs_32s:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;

  gr0 = [--ar5]; //psrc
  gr0;
  if =0 goto err_ptr_32s;

  ar0 = gr0;

  gr0 = [--ar5]; //pdst
  gr0;
  if =0 goto err_ptr_32s;

  ar1 = gr0;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_32s;

  gr1 = [--ar5]; //level

  gr7 = 0;

  ar2 = ar7 + 2;
  ar7 = ar7 + 6;
  ar5 = ar2;

  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  gr1 = 0;
  ar5 = ar5 + 1;
  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  /// Определим кратность 32-м
  gr1 = gr0 >> 5;
  gr1;

  if =0 goto threshold_less_32_32s;

  gr2 = gr1;

  /// Инитим vreg1 значением 0
  ar5 = ar2 + 2;
  fpu rep 16 .packer = [ar5] with .double <= .fixed_32;

  fpu 0 rep 32 vreg1 = .packer;

  /// Инитим vreg2 значением level
  ar5 = ar2;
  fpu rep 16 .packer = [ar5] with .double <= .fixed_32;

  fpu 0 rep 32 vreg2 = .packer;

  ///Регистр со значением -level
  fpu 0 .double vreg3 = -vreg2;

threshold_over_32_32s:

  //call threshold_gt_abs_32s;
  /// инитим vreg0 значениями из psrc
  fpu rep 16 .packer = [ar0++] with .double <= .fixed_32;

  fpu 0 rep 32 vreg0 = .packer;

  /// Дополнительный регистр со значением level
  fpu 0 .double vreg5 = vreg2;
  /// Регистр со значением abs(psrc)
  fpu 0 .double vreg4 = /vreg0/;

  /// Формируем регистр из значений level, -level в соответствии
  /// со значениями psrc
  fpu 0 .double vreg0 - vreg1, set mask if <;
  fpu 0 .double vreg5 = mask ? vreg3 : vreg5;

  /// Формирование результата
  fpu 0 .double vreg4 - vreg2, set mask if <=;
  fpu 0 .double vreg5 = mask ? vreg0 : vreg5;

  fpu 0 .packer = vreg5 with .fixed_32 <= .double;

  fpu rep 16 [ar1++] = .packer;

  gr2 = gr2 - 1;

  if > goto threshold_over_32_32s;

  gr1 = 31;
  gr0 = gr0 and gr1;

  if =0 goto exit_32s;

threshold_less_32_32s:
  gr2 = gr0;
  gr1 = 1;
  gr0 - gr1;
  if =0 goto threshold_last_element_32s;

  gr0 and gr1;
  if =0 goto exec_threshold_less_32_32s;

  gr2 = gr2 - 1;

exec_threshold_less_32_32s:
  gr1 = gr2 >> 1;
  gr1 = gr1 - 1;
  gr2 = gr2 - 1;

  vlen = gr1;
  ar5 = ar2 + 2;
  fpu rep vlen .packer = [ar5] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg1 = .packer;

  /// Инитим vreg2 значением level
  vlen = gr1;
  ar5 = ar2;
  fpu rep vlen .packer = [ar5] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg2 = .packer;


  call threshold_gt_abs_32s;

  fpu rep vlen [ar1++] = .packer;

  gr1 = 1;
  gr0 and gr1;
  if =0 goto exit_32s;

threshold_last_element_32s:
  gr2 = 1;
  gr1 = 0;

  vlen = gr1;
  ar5 = ar2 + 2;
  fpu rep vlen .packer = [ar5] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg1 = .packer;

  /// Инитим vreg2 значением level
  vlen = gr1;
  ar5 = ar2;
  fpu rep vlen .packer = [ar5] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg2 = .packer;

  call threshold_gt_abs_32s;

  ar5 = ar2;

  fpu rep vlen [ar2] = .packer;
  gr0 = [ar2];

  [ar1] = gr0;

  goto exit_32s;
// Нулевой указатель на вектор
err_ptr_32s:
  gr7 = -8;
  goto exit_error_32s;

// Некорректное значение длины вектора
err_size_32s:
  gr7 = -6;
  goto exit_error_32s;

exit_32s:
  ar7 = ar7 - 6;

exit_error_32s:
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


 threshold_gt_abs_32s:
  /// инитим vreg0 значениями из psrc
  vlen = gr1;
  fpu rep vlen .packer = [ar0++] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg0 = .packer;

  ///Регистр со значением -level
  fpu 0 .double vreg3 = -vreg2;
  /// Дополнительный регистр со значением level
  fpu 0 .double vreg5 = vreg2;
  /// Регистр со значением abs(psrc)
  fpu 0 .double vreg4 = /vreg0/;

  /// Формируем регистр из значений level, -level в соответствии
  /// со значениями psrc
  fpu 0 .double vreg0 - vreg1, set mask if <;
  fpu 0 .double vreg5 = mask ? vreg3 : vreg5;

  /// Формирование результата
  fpu 0 .double vreg4 - vreg2, set mask if <=;
  fpu 0 .double vreg5 = mask ? vreg0 : vreg5;


  fpu 0 .packer = vreg5 with .fixed_32 <= .double;

  vlen = gr1;


  return;



_nmppsThreshold_GTAbs_32f:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; //psrc
  gr0;
  if =0 goto err_ptr_32f;

  ar0 = gr0;

  gr0 = [--ar5]; //pdst
  gr0;
  if =0 goto err_ptr_32f;

  ar1 = gr0;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_32f;

  gr1 = [--ar5]; //level

  gr7 = 0;

  ar2 = ar7 + 2;
  ar7 = ar7 + 6;
  ar5 = ar2;

  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  gr1 = 0;
  ar5 = ar5 + 1;
  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  /// Определим кратность 64-м
  gr1 = gr0 >> 6;
  gr1;

  if =0 goto threshold_less_32_32f;

  /// Инитим vreg1 значением 0
  ar5 = ar2 + 2;
  fpu 0 rep 32 vreg1 = [ar5];

  /// Инитим vreg2 значением level
  ar5 = ar2;
  fpu 0 rep 32 vreg2 = [ar5];

  ///Регистр со значением -level
  fpu 0 .float vreg3 = -vreg2;

  gr2 = gr1;
threshold_over_32_32f:

  fpu 0 rep 32 vreg0 = [ar0++];
  /// Дополнительный регистр со значением level
  fpu 0 .float vreg5 = vreg2;
  /// Регистр со значением abs(psrc)
  fpu 0 .float vreg4 = /vreg0/;

  /// Формируем регистр из значений level, -level в соответствии
  /// со значениями psrc
  fpu 0 .float vreg0 - vreg1, set mask if <;
  fpu 0 .float vreg5 = mask ? vreg3 : vreg5;

  /// Формирование результата
  fpu 0 .float vreg4 - vreg2, set mask if <=;
  fpu 0 .float vreg5 = mask ? vreg0 : vreg5;

  fpu 0 rep 32 [ar1++] = vreg5;

  gr2 = gr2 - 1;

  if > goto threshold_over_32_32f;

  gr1 = 63;
  gr0 = gr0 and gr1;

  if =0 goto exit_32f;

threshold_less_32_32f:
  gr1 = 1;
  gr0 - gr1;
  if =0 goto threshold_last_element_32f;

exec_threshold_less_32_32f:
  gr1 = gr0 >> 1;
  gr1 = gr1 - 1;

  call threshold_gt_abs_32f;

  fpu 0 rep vlen [ar1++] = vreg2;

  gr1 = 1;
  gr0 and gr1;
  if =0 goto exit_32f;

threshold_last_element_32f:
  gr1 = 0;

  call threshold_gt_abs_32f;

  ar5 = ar2;

  fpu 0 rep vlen [ar2] = vreg2;
  gr0 = [ar2];

  [ar1] = gr0;

  goto exit_32f;
// Нулевой указатель на вектор
err_ptr_32f:
  gr7 = -8;
  goto exit_error_32f;

// Некорректное значение длины вектора
err_size_32f:
  gr7 = -6;
  goto exit_error_32f;

exit_32f:
  ar7 = ar7 - 6;

exit_error_32f:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


 threshold_gt_abs_32f:
  /// инитим vreg0 значениями из psrc
  vlen = gr1;

  fpu 0 rep vlen vreg0 = [ar0++];

  /// Инитим vreg1 значением 0
  ar5 = ar2 + 2;
  fpu 0 rep vlen vreg1 = [ar5];

  /// Инитим vreg2 значением level

  ar5 = ar2;
  fpu 0 rep vlen vreg2 = [ar5];

  ///Регистр со значением -level
  fpu 0 .float vreg3 = -vreg2;
  /// Дополнительный регистр со значением level
  fpu 0 .float vreg5 = vreg2;
  /// Регистр со значением abs(psrc)
  fpu 0 .float vreg4 = /vreg0/;

  /// Формируем регистр из значений level, -level в соответствии
  /// со значениями psrc
  fpu 0 .float vreg0 - vreg1, set mask if <;
  fpu 0 .float vreg2 = mask ? vreg3 : vreg2;

  /// Формирование результата
  fpu 0 .float vreg4 - vreg5, set mask if <=;
  fpu 0 .float vreg2 = mask ? vreg0 : vreg2;

  return;




_nmppsThreshold_GTAbs_64f:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;

  gr0 = [--ar5]; //psrc
  gr0;
  if =0 goto err_ptr_64f;

  ar0 = gr0;

  gr0 = [--ar5]; //pdst
  gr0;
  if =0 goto err_ptr_64f;

  ar1 = gr0;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_64f;

  ar3, gr3 = [--ar5]; //level

  gr7 = 0;

  ar2 = ar7 + 2;
  ar7 = ar7 + 6;
  ar5 = ar2;

  [ar5] = ar3,gr3;

  ar5 = ar5 + 2;
  gr1 = 0;
  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  /// Определим кратность 32-м
  gr1 = gr0 >> 5;
  gr1;

  if =0 goto threshold_less_32_64f;

  /// Инитим vreg1 значением 0
  ar5 = ar2 + 2;
  fpu 0 rep 32 vreg1 = [ar5];

  /// Инитим vreg2 значением level

  ar5 = ar2;
  fpu 0 rep 32 vreg2 = [ar5];

  ///Регистр со значением -level
  fpu 0 .double vreg3 = -vreg2;

threshold_over_32_64f:

  //call threshold_gt_abs_64f;
  /// инитим vreg0 значениями из psrc

  fpu 0 rep 32 vreg0 = [ar0++];

  /// Дополнительный регистр со значением level
  fpu 0 .double vreg5 = vreg2;
  /// Регистр со значением abs(psrc)
  fpu 0 .double vreg4 = /vreg0/;

  /// Формируем регистр из значений level, -level в соответствии
  /// со значениями psrc
  fpu 0 .double vreg0 - vreg1, set mask if <;
  fpu 0 .double vreg5 = mask ? vreg3 : vreg5;

  /// Формирование результата
  fpu 0 .double vreg4 - vreg2, set mask if <=;
  fpu 0 .double vreg5 = mask ? vreg0 : vreg5;

  fpu 0 rep 32 [ar1++] = vreg5;

  gr1 = gr1 - 1;

  if > goto threshold_over_32_64f;

  gr1 = 31;
  gr0 = gr0 and gr1;

  if =0 goto exit_64f;

threshold_less_32_64f:
  gr1 = gr0 - 1;

  vlen = gr1;

  /// Инитим vreg1 значением 0
  ar5 = ar2 + 2;
  fpu 0 rep vlen vreg1 = [ar5];

  /// Инитим vreg2 значением level

  ar5 = ar2;
  fpu 0 rep vlen vreg2 = [ar5];

  ///Регистр со значением -level
  fpu 0 .double vreg3 = -vreg2;

  /// инитим vreg0 значениями из psrc
  fpu 0 rep vlen vreg0 = [ar0++];

  /// Дополнительный регистр со значением level
  fpu 0 .double vreg5 = vreg2;
  /// Регистр со значением abs(psrc)
  fpu 0 .double vreg4 = /vreg0/;

  /// Формируем регистр из значений level, -level в соответствии
  /// со значениями psrc
  fpu 0 .double vreg0 - vreg1, set mask if <;
  fpu 0 .double vreg5 = mask ? vreg3 : vreg5;

  /// Формирование результата
  fpu 0 .double vreg4 - vreg2, set mask if <=;
  fpu 0 .double vreg5 = mask ? vreg0 : vreg5;

  fpu 0 rep vlen [ar1++] = vreg5;

  goto exit_64f;

// Нулевой указатель на вектор
err_ptr_64f:
  gr7 = -8;
  goto exit_error_64f;

// Некорректное значение длины вектора
err_size_64f:
  gr7 = -6;
  goto exit_error_64f;

exit_64f:
  ar7 = ar7 - 6;

exit_error_64f:
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;
