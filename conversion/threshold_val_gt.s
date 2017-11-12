.globl _nmppsThreshold_GTVal_16s
.globl _nmppsThreshold_GTVal_32s
.globl _nmppsThreshold_GTVal_32f
.globl _nmppsThreshold_GTVal_64f

.text

_nmppsThreshold_GTVal_16s:
_nmppsThreshold_GTVal_32s:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; //psrc
  gr0;
  if =0 goto err_ptr_32s;

  ar0 = gr0;

  gr1 = [--ar5]; //pdst
  gr1;
  if =0 goto err_ptr_32s;

  ar1 = gr1;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_32s;

  gr1 = [--ar5]; //level
  gr2 = [--ar5]; //val

  gr7 = 0;

  ar2 = ar7 + 2;
  ar7 = ar7 + 6;
  ar5 = ar2;

  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  ar5 = ar5 + 1;
  [ar5] = gr2;
  ar5 = ar5 + 1;
  [ar5] = gr2;

  /// Определим кратность 64-м
  gr1 = gr0 >> 5;
  gr1;

  if =0 goto threshold_less_32_32s;

  ar5 = ar2;
  fpu rep 16 .packer = [ar5] with .double <= .fixed_32;
  fpu 0 rep 32 vreg1 = .packer;

  ar5 = ar2 + 2;
  fpu rep 16 .packer = [ar5] with .double <= .fixed_32;
  fpu 0 rep 32 vreg2 = .packer;

threshold_over_32_32s:
  //Перепаковываем входные вектора в double, чтобы иметь возможность с ними работать
  fpu rep 16 .packer = [ar0++] with .double <= .fixed_32;
  fpu 0 rep 32 vreg0 = .packer;

  fpu 0 .double vreg0 - vreg1, set mask if >;
  fpu 0 .double vreg0 = mask ? vreg2 : vreg0;

  fpu 0 .packer = vreg0 with .fixed_32 <= .double;
  fpu rep 16 [ar1++] = .packer;

  gr1 = gr1 - 1;

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
  fpu rep vlen .packer = [ar0++] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg0 = .packer;

  vlen = gr1;
  ar5 = ar2;
  fpu rep vlen .packer = [ar5] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg1 = .packer;

  vlen = gr1;
  ar5 = ar2 + 2;
  fpu rep vlen .packer = [ar5] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg2 = .packer;

  fpu 0 .double vreg0 - vreg1, set mask if >;
  fpu 0 .double vreg0 = mask ? vreg2 : vreg0;

  fpu 0 .packer = vreg0 with .fixed_32 <= .double;

  vlen = gr1;
  fpu rep vlen [ar1++] = .packer;

  gr1 = 1;
  gr0 and gr1;
  if =0 goto exit_32s;

threshold_last_element_32s:
  gr0 = [ar0];
  gr1 = [ar2];
  ar5 = ar2 + 2;
  gr2 = [ar5];

  gr0 - gr1;
  if > goto threshold_last_element1_32s;

  [ar1] = gr0;
  goto exit_32s;

threshold_last_element1_32s:
  [ar1] = gr2;

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
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;



_nmppsThreshold_GTVal_32f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; //psrc
  gr0;
  if =0 goto err_ptr_32f;

  ar0 = gr0;

  gr1 = [--ar5]; //pdst
  gr1;
  if =0 goto err_ptr_32f;

  ar1 = gr1;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_32f;

  gr1 = [--ar5]; //level
  gr2 = [--ar5]; //val

  gr7 = 0;

  ar2 = ar7 + 2;
  ar7 = ar7 + 6;
  ar5 = ar2;

  [ar5] = gr1;
  ar5 = ar5 + 1;
  [ar5] = gr1;

  ar5 = ar5 + 1;
  [ar5] = gr2;
  ar5 = ar5 + 1;
  [ar5] = gr2;

  /// Определим кратность 64-м
  gr1 = gr0 >> 6;
  gr1;

  if =0 goto threshold_less_32_32f;

  ar5 = ar2;
  fpu 0 rep 32 vreg1 = [ar5];

  ar5 = ar2 + 2;
  fpu 0 rep 32 vreg2 = [ar5];
threshold_over_32_32f:
  //Перепаковываем входные вектора в double, чтобы иметь возможность с ними работать
  fpu 0 rep 32 vreg0 = [ar0++];

  fpu 0 .float vreg0 - vreg1, set mask if >;
  fpu 0 .float vreg0 = mask ? vreg2 : vreg0;

  fpu 0 rep 32 [ar1++] = vreg0;

  gr1 = gr1 - 1;

  if > goto threshold_over_32_32f;

  gr1 = 63;
  gr0 = gr0 and gr1;

  if =0 goto exit_32f;

threshold_less_32_32f:
  gr2 = gr0;
  gr1 = 1;
  gr0 - gr1;
  if =0 goto threshold_last_element_32f;

  gr0 and gr1;
  if =0 goto exec_threshold_less_32_32f;

  gr2 = gr2 - 1;

exec_threshold_less_32_32f:
  gr1 = gr2 >> 1;
  gr1 = gr1 - 1;

  vlen = gr1;
  fpu 0 rep vlen vreg0 = [ar0++];

  ar5 = ar2;
  fpu 0 rep vlen vreg1 =[ar5];

  ar5 = ar2 + 2;
  fpu 0 rep vlen vreg2 = [ar5];

  fpu 0 .float vreg0 - vreg1, set mask if >;
  fpu 0 .float vreg0 = mask ? vreg2 : vreg0;

  fpu 0 rep vlen [ar1++] = vreg0;

  gr1 = 1;
  gr0 and gr1;
  if =0 goto exit_32f;

threshold_last_element_32f:
  gr0 = 0;

  vlen = gr0;
  fpu 0 rep vlen vreg0 = [ar0];

  ar5 = ar2;
  fpu 0 rep vlen vreg1 =[ar5];

  ar5 = ar2 + 2;
  fpu 0 rep vlen vreg2 = [ar5];

  fpu 0 .float vreg0 - vreg1, set mask if >;
  fpu 0 .float vreg0 = mask ? vreg2 : vreg0;

  fpu 0 rep vlen [ar2] = vreg0;

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




_nmppsThreshold_GTVal_64f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;

  gr0 = [--ar5]; //psrc
  gr0;
  if =0 goto err_ptr_64f;

  ar0 = gr0;

  gr1 = [--ar5]; //pdst
  gr1;
  if =0 goto err_ptr_64f;

  ar1 = gr1;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_64f;

  gr7 = 0;

  ar3, gr3 = [--ar5]; //level

  ar2 = ar7 + 2;
  ar7 = ar7 + 6;

  [ar2] = ar3, gr3;

  ar3, gr3 = [--ar5]; //val

  ar2 = ar2 + 2;
  [ar2] = ar3, gr3;
  ar2 = ar2 - 2;

  /// Определим кратность 64-м
  gr1 = gr0 >> 5;
  gr1;

  if =0 goto threshold_less_32_64f;

  ar5 = ar2;
  fpu 0 rep 32 vreg1 = [ar5];

  ar5 = ar2 + 2;
  fpu 0 rep 32 vreg2 = [ar5];
threshold_over_32_64f:
  //Перепаковываем входные вектора в double, чтобы иметь возможность с ними работать
  fpu 0 rep 32 vreg0 = [ar0++];

  fpu 0 .double vreg0 - vreg1, set mask if >;
  fpu 0 .double vreg0 = mask ? vreg2 : vreg0;

  fpu 0 rep 32 [ar1++] = vreg0;

  gr1 = gr1 - 1;

  if > goto threshold_over_32_64f;

  gr1 = 31;
  gr0 = gr0 and gr1;

  if =0 goto exit_64f;

threshold_less_32_64f:
  gr1 = gr0 - 1;

  vlen = gr1;
  fpu 0 rep vlen vreg0 = [ar0++];

  ar5 = ar2;
  fpu 0 rep vlen vreg1 =[ar5];

  ar5 = ar2 + 2;
  fpu 0 rep vlen vreg2 = [ar5];

  fpu 0 .double vreg0 - vreg1, set mask if >;
  fpu 0 .double vreg0 = mask ? vreg2 : vreg0;

  fpu 0 rep vlen [ar1++] = vreg0;

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
