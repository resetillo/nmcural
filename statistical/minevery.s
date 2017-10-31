.globl _nmppsMinEvery_16s_I
.globl _nmppsMinEvery_32s_I
.globl _nmppsMinEvery_32f_I

.text

_nmppsMinEvery_16s_I:
_nmppsMinEvery_32s_I:

  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; //psrc1
  gr0;
  if =0 goto err_ptr;

  ar0 = gr0;

  gr0 = [--ar5]; //psrcdst
  gr0;
  if =0 goto err_ptr;

  ar1 = gr0;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size;

  gr7 = 0;

  /// Определим кратность 64-м
  gr1 = gr0 >> 5;
  gr1;

  if =0 goto minevery_less_32;


minevery_over_32:
  //Перепаковываем входные вектора в double, чтобы иметь возможность с ними работать
  fpu rep 16 .packer = [ar0++] with .double <= .fixed_32;
  fpu 0 rep 32 vreg0 = .packer;

  gr2 = ar1;

  fpu rep 16 .packer = [ar1++] with .double <= .fixed_32;
  fpu 0 rep 32 vreg1 = .packer;

  fpu 0 .double vreg0 - vreg1, set mask if >;
  fpu 0 .double vreg0 = mask ? vreg1 : vreg0;

  ar1 = gr2;

  fpu 0 .packer = vreg0 with .fixed_32 <= .double;
  fpu rep 16 [ar1++] = .packer;

  gr1 = gr1 - 1;

  if > goto minevery_over_32;

  gr1 = 31;
  gr0 = gr0 and gr1;

  if =0 goto exit;

minevery_less_32:
  gr1 = 1;
  gr0 - gr1;
  if =0 goto min_every_last_element;

  gr0 and gr1;
  if =0 goto exec_min_every_less_32;

  gr0 = gr0 - 1;

exec_min_every_less_32:
  gr1 = gr0 >> 1;
  gr1 = gr1 - 1;
  gr0 = gr0 - 1;

  vlen = gr1;
  fpu rep vlen .packer = [ar0++] with .double <= .fixed_32;

  vlen = gr0;
  fpu 0 rep vlen vreg0 = .packer;

  gr2 = ar1;
  vlen = gr1;
  fpu rep vlen .packer = [ar1++] with .double <= .fixed_32;

  vlen = gr0;
  fpu 0 rep vlen vreg1 = .packer;

  fpu 0 .double vreg0 - vreg1, set mask if >;
  fpu 0 .double vreg0 = mask ? vreg1 : vreg0;

  fpu 0 .packer = vreg0 with .fixed_32 <= .double;

  ar1 = gr2;
  vlen = gr1;
  fpu rep vlen [ar1++] = .packer;

  gr1 = 1;
  gr0 and gr1;
  if =0 goto exit;

min_every_last_element:
  gr0 = [ar0];
  gr1 = [ar1];

  gr0 - gr1;
  if > goto exit;

  [ar1] = gr0;
  goto exit;
// Нулевой указатель на вектор
err_ptr:
  gr7 = -8;
  goto exit;

// Некорректное значение длины вектора
err_size:
  gr7 = -6;

exit:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


_nmppsMinEvery_32f_I:
 ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  gr0 = [--ar5]; //psrc1
  gr0;
  if =0 goto err_ptr_32f;

  ar0 = gr0;

  gr0 = [--ar5]; //psrcdst
  gr0;
  if =0 goto err_ptr_32f;

  ar1 = gr0;

  gr0 = [--ar5]; //len
  gr0;
  if <= goto err_size_32f;

  gr7 = 0;

  ar2 = ar7 + 2;
  ar7 = ar7 + 4;
  ar5 = ar2;

  /// Определим кратность 64-м
  gr1 = gr0 >> 6;
  gr1;

  if =0 goto minevery_less_32_32f;


minevery_over_32_32f:

  gr2 = ar1;
  fpu 0 rep 32 vreg0 = [ar0++];
  fpu 0 rep 32 vreg1 = [ar1++];

  fpu 0 .float vreg0 - vreg1, set mask if >;
  fpu 0 .float vreg0 = mask ? vreg1 : vreg0;

  ar1 = gr2;

  fpu 0 rep 32 [ar1++] = vreg0;

  gr1 = gr1 - 1;

  if > goto minevery_over_32_32f;

  gr1 = 63;
  gr0 = gr0 and gr1;

  if =0 goto exit_32f;

minevery_less_32_32f:
  gr1 = 1;
  gr0 - gr1;
  if =0 goto min_every_last_element_32f;

exec_min_every_less_32_32f:
  gr1 = gr0 >> 1;
  gr1 = gr1 - 1;

  gr2 = ar1;

  vlen = gr1;
  fpu 0 rep vlen vreg0 = [ar0++];
  fpu 0 rep vlen vreg1 = [ar1++];

  fpu 0 .float vreg0 - vreg1, set mask if >;
  fpu 0 .float vreg0 = mask ? vreg1 : vreg0;

  ar1 = gr2;
  fpu 0 rep vlen [ar1++] = vreg0;

  gr1 = 1;
  gr0 and gr1;
  if =0 goto exit_32f;

min_every_last_element_32f:

  fpu 0 rep 1 vreg0 = [ar0];
  fpu 0 rep 1 vreg1 = [ar1];

  fpu 0 .float vreg0 - vreg1, set mask if >;
  fpu 0 .float vreg0 = mask ? vreg1 : vreg0;

  fpu 0 rep 1 [ar5] = vreg0;

  gr0 = [ar5];
  [ar1] = gr0;

  goto exit_32f;
// Нулевой указатель на вектор
err_ptr_32f:
  gr7 = -8;
  goto exit_error32f;

// Некорректное значение длины вектора
err_size_32f:
  gr7 = -6;
  goto exit_error32f;

exit_32f:
  ar7 = ar7 - 4;
exit_error32f:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;

