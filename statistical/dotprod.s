.globl _nmppsDotProd_16s32s_Sfs
.globl _nmppsDotProd_16s32s32s_Sfs
.globl _nmppsDotProd_32s_Sfs
.global scale_f64

.text

_nmppsDotProd_16s32s_Sfs:
_nmppsDotProd_16s32s32s_Sfs:
_nmppsDotProd_32s_Sfs:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;
  push ar4, gr4;

  gr0 = [--ar5]; //psrc1
  gr0;
  if =0 goto err_ptr;

  ar0 = gr0;

  gr1 = [--ar5]; // psrc2
  gr1;
  if =0 goto err_ptr;

  ar1 = gr1;

  gr0 = [--ar5]; // len
  gr0;
  if <= goto err_size;

  gr2 = [--ar5]; // pdst
  gr2;
  if =0 goto err_ptr;

  ar2 = gr2;

  gr1 = [--ar5]; // scale_factor


  gr7 = 0;
  // Буфер для результата
  ar3 = ar7 + 2;
  ar7 = ar7 + 4;

  gr3 = 0;
  [ar3] = gr3;
  // Здесь будет копиться результат
  fpu 0 rep 1 vreg3 = [ar3];

  gr3 = gr0 >> 5;
  gr3;

  if =0 goto dotprod_less_32;

  gr2 = 32;
dotprod_over_32:
  //Перепаковываем входные вектора в double, чтобв иметь возможность с ними работать
  fpu rep 16 .packer = [ar0++] with .double <= .fixed_32;
  fpu 0 rep 32 vreg0 = .packer;

  fpu rep 16 .packer = [ar1++] with .double <= .fixed_32;
  fpu 0 rep 32 vreg1 = .packer;

  // Вычисление скалярного произведения для 32-х элементов
  call dot_prod;

  gr3 = gr3 - 1;
  if > goto dotprod_over_32;

  gr3 = 31;
  gr0 = gr0 and gr3;

  if <>0 goto dotprod_less_32;
  goto scale;

dotprod_less_32:

  // Количество повторений для загрузки в упаковщик
  gr2 = 1;

  gr0 and gr2;

  //Для четной длины загрузим на один элемент больше
  if <>0 goto len_parity;
  gr2 = gr0;
  gr2 = gr2 - 1;

len_parity:
  gr3 = gr2 >> 1;

  vlen = gr3;
  fpu rep vlen .packer = [ar0++] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg0 = .packer;

  vlen = gr3;
  fpu rep vlen .packer = [ar1++] with .double <= .fixed_32;

  vlen = gr2;
  fpu 0 rep vlen vreg1 = .packer;

  gr2 = gr0;
  // Вычисление скалярного произведения для 32-х элементов
  call dot_prod;
  goto scale;

dot_prod:
  push gr2;
  fpu 0 .double vreg2 = vreg0 * vreg1;

  loop_dot_prod:
    fpu 0 .double vreg3 = vreg3 + .retrive(vreg2);
    gr2 = gr2 - 1;
    if > goto loop_dot_prod;
  pop gr2;
  return;

scale:
  fpu 0 rep 1 [ar3] = vreg3;

  ar0 = ar3;
  ar1 = ar2;
  gr0 = gr1;

  call scale_f64;
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
  ar7 = ar7 - 4;

exit_error:
  pop ar4, gr4;
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;













