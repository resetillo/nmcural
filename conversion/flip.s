.globl _nmppsFlip_32f
.globl _nmppsFlip_64f


.text

_nmppsFlip_32f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;
  push ar4, gr4;

  gr0 = [--ar5]; // pSrc

  //Проверка на NULL
  gr0;
  if =0 goto err_ptr_32f;

  gr1 = [--ar5]; // pDst

  //Проверка на NULL
  gr1;
  if =0 goto err_ptr_32f;

  gr2 = [--ar5]; // len

  // Длина должна быть больше нуля
  gr2;
  if <= goto err_size_32f;

  gr7 = 0;

  // Буфер на 66 слов
  ar3 = ar7 + 2;
  ar7 = ar7 + 68;

  // Переход на конец входного вектора
  gr0 = gr0 + gr2;
  ar0 = gr0;
  ar1 = gr1;

  // Проверим четная ли длина
  gr0 = 1;
  gr3 = gr0 and gr2;

  // Сколько раз можем загрузить вектор
  gr0 = gr2 >> 6;

  // Длина вектора больше 64, загрузим весь регистр
  gr0;
  if <>0 goto over_64;

  //Длина меньше 64, загрузим сколько есть
  goto less_64;

// Сдвиг вектора вправо на 32 разряда
shift_vector:
  // Смещаем младшие слова в старшие
  fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
  ar5 = ar3;
  //выгрузка  данных в буфер для загрузки со сдвигом
  fpu rep vlen [ar5++] = .packer;

  // обнуляем последние два слова буфера
  ar5 = ar5 + 2;
  gr5 = 0;
  [--ar5] = gr5;
  [--ar5] = gr5;
  // загрузка со смещением
  ar5 = ar3 + 2;
  fpu 0 rep vlen vreg2 = [ar5++];

  // Смещаем старшие слова в младшие
  fpu 0 .packer = vreg0 with .float .in_low <= .float .in_high;
  fpu 0 rep vlen vreg1 = .packer;

  // сложение
  fpu 0 .float vreg0 = vreg1 + vreg2;

  // Возвращаемся туда, откуда пришли
  goto ar2;

// Собственно, переворачивание элементов входного вектора
flip:
  // Загружаем данные из src
  fpu 0 rep vlen vreg0 = [--ar0];

  // Далее меняем местами 32 разрядные слова в 64 разрядном слове

  // Смещаем младшие слова в старшие
  fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
  // Сохраним результат
  fpu 0 rep vlen vreg1 = .packer;
  // Смещаем старшие слова в младшие
  fpu 0 .packer = vreg0 with .float .in_low <= .float .in_high;
  // Сохраним результат
  fpu 0 rep vlen vreg2 = .packer;
  // Просуммируем 2 буфера
  fpu 0 .float vreg0 = vreg1 + vreg2;

  // Возвращаемся туда, откуда пришли
  goto ar2;

// Длина вектора больше 64 элементов
over_64:
  vlen = 31;
  // Выставляем адрес метки возвращения
  ar2 = return_from_flip;
  // Если длина четная  - ничего больше делать не нужно
  //переходим к переворачиванию
  gr3;
  if =0 goto flip;

  //Длина нечетная

  gr4 = gr2;
  // Шаг цикла. Будем копировать по 62 элемента
  gr1 = 62;
  //Сдвинемся на элемент вперед, чтобы выровнять адрес
  ar0 = ar0 + 1;

 //переходим к переворачиванию
  goto flip;

// Возвращения после переворачивания вектора
return_from_flip:
  // Если длина четная -выгрузим результат в dst и пойдем дальше по циклу
  gr3;
  if =0 goto counter_loop_parity;

  // Если длина нечетная - необходимо сдвинуть перевернутый вектор на 32 влево

  // Инициализируем метку возвращения после сдвига
  ar2 = return_from_shift_over_64;

  // Переход к сдвигу
  goto shift_vector;

//Цикл для четной длины вектора
counter_loop_parity:
  ar2 = return_from_flip;
  //загрузим 64 элемента в dst
  fpu 0 rep 32 [ar1++] = vreg0;

  // Счетчик цикла
  gr0 = gr0 - 1;
  if > goto flip;

  // Проверим все ли перевернули
  gr1 = 63;
  gr0 = gr1 and gr2;
  //есть остаток - перевернем его
  if > delayed goto go_flip_less_64;
  gr0 = gr0 >> 1;
  gr0 = gr0 - 1;

  //Перевернули все - выход
  goto exit_32f;

// Возвращение после сдвига
return_from_shift_over_64:
  ar2 = return_from_flip;
  //загрузим 62 элемента в dst
  fpu 0 rep 31 [ar1++] = vreg0;

  // Откатимся на два элемента чтобы ничего не пропустить.
  //если этого не сдлеать - один элемент пропустится
  ar0 = ar0 + 2;
  //Счетчик цикла. Уменьшаем на 62
  gr4 = gr4 - gr1;

  gr4 - gr1;
  if > goto flip;
  // Все перевернуди - выходим
  if =0 goto exit_32f;

  // Есть остаток - перевернем его
  gr0 = gr4 >> 1;

  goto go_flip_less_64;

// Длина вектора меньше 64
less_64:

  gr0 = gr2 >> 1;

  // Длина нечетная - выровняем адрес
  gr3;
  if <>0 goto less_non_parity;

  // Длина четная
  gr0 = gr0 - 1;

  goto go_flip_less_64;

less_non_parity:
  ar0 = ar0 + 1;

//Переход к переворачиванию
go_flip_less_64:
  vlen = gr0;

  // Инициализация метки возращения после переворачивания
  ar2 = return_flip_less_64;

  goto flip;

//Возвращение с flip
return_flip_less_64:
  //Длина нечетная - надо сдвинуть
  gr3;
  if =0 goto return_from_shift_less_64;

  // Инициализация метки возращения после сдвига
  ar2 = return_from_shift_less_64;

  goto shift_vector;

//Возвращения после сдвига
return_from_shift_less_64:
  // Выгрузка в dst
  fpu 0 rep vlen [ar1++] = vreg0;

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
  ar7 = ar7 - 68;
exit_error_32f:
  pop ar4, gr4;
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


_nmppsFlip_64f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;


  gr0 = [--ar5]; // pSrc

  //Проверка на NULL
  gr0;
  if =0 goto err_ptr_64f;

  gr1 = [--ar5]; // pDst

  //Проверка на NULL
  gr1;
  if =0 goto err_ptr_64f;

  gr2 = [--ar5]; // len

  // Длина должна быть больше нуля
  gr2;
  if <= goto err_size_64f;

  gr7 = 0;

  // Перейдем в конец src
  ar1 = gr1;
  gr1 = gr2 << 1;
  gr0 = gr0 + gr1;
  ar0 = gr0;


  // Сколько раз можем полностью загрузить векторный регистр
  gr1 = gr2 >> 5;

  gr1;
  if =0 delayed goto less32_64f;
  gr0 = gr2 - 1 ;
  vlen = gr0;

// Переворачиваем по 32 слова
over32_64f:
  fpu 0 rep 32 vreg0 = [--ar0];
  fpu 0 rep 32 [ar1++] = vreg0;

  gr1 = gr1 - 1;
  if > goto over32_64f;

  // Проверим все ли скопировали
  gr0 = 31;
  gr1 = gr2 and gr0;

  if =0 delayed goto exit_64f;
  gr1 = gr1 - 1;
  vlen = gr1;

// Копирование меньше 32 слов
less32_64f:

  fpu 0 rep vlen vreg0 = [--ar0];
  fpu 0 rep vlen [ar1++] = vreg0;

  goto exit_64f;
// Нулевой указатель на вектор
err_ptr_64f:
  gr7 = -8;
  goto exit_64f;

// Некорректное значение длины вектора
err_size_64f:
  gr7 = -6;

exit_64f:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;





