#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if DivTestEnable

TEST_GROUP(tests_div32);
TEST_SETUP(tests_div32) {}
TEST_TEAR_DOWN(tests_div32) {}

TEST_GROUP(tests_divC32);
TEST_SETUP(tests_divC32) {}
TEST_TEAR_DOWN(tests_divC32) {}

TEST_GROUP(tests_divCRev32);
TEST_SETUP(tests_divCRev32) {}
TEST_TEAR_DOWN(tests_divCRev32) {}

#define COUNT_ITERATION (100)

/**
 * @brief Создание тестовых для деления векторов
 *
 * @param Divided Входной вектор, делимое
 * @param bgnDivided Начальное значение для делимых
 * @param stepDivided Приращение для делимых
 * @param Divisor Входной вектор, делитель
 * @param bgnDivisor Начальное значение для делителей
 * @param stepDivisor Приращение для делителей
 * @param out Выходной вектор
 * @param len Длина векторов
 * */
void create_div32_vecs(nmpps32f* Divided, nmpps32f bgnDivided, nmpps32f stepDivided,
		             nmpps32f* Divisor,  nmpps32f bgnDivisor, nmpps32f stepDivisor,
					 nmpps32f* out, unsigned int len )
{
	int i;
	for(i=0; i<len; i++){
		Divided[i] = bgnDivided;
		Divisor[i] = bgnDivisor;
		out[i] =  Divided[i] / Divisor[i];
		bgnDivided += stepDivided;
		bgnDivisor += stepDivisor;
	}
}

void create_divC32_vecs(nmpps32f* Divided, nmpps32f bgnDivided, nmpps32f stepDivided,
		             nmpps32f Divisor,  nmpps32f* out, unsigned int len )
{
	int i;
	for(i=0; i<len; i++){
		Divided[i] = bgnDivided;
		out[i] =  Divided[i] / Divisor;
		bgnDivided += stepDivided;
	}
}

void create_divCRev32_vecs(nmpps32f* Divisor, nmpps32f bgnDivisor, nmpps32f stepDivisor,
		             nmpps32f Divided,  nmpps32f* out, unsigned int len )
{
	int i;
	for(i=0; i<len; i++){
		Divisor[i] = bgnDivisor;
		out[i] =  Divided / Divisor[i];
		bgnDivisor += stepDivisor;
	}
}


const nmpps32f div32_critical_error = 1e-04;

/**
 * @brief Тестирование деление диапазонов
 *
 * @param bgnDivided Начальное значение для делимых
 * @param stepDivided Приращение для делимых
 * @param bgnDivisor Начальное значение для делителей
 * @param stepDivisor Приращение для делителей
 * @param count Длина тестируемых векторов
 * */

float max_errf = 0;

nmppsStatus test_div32_diap(nmpps32f bgnDivided, nmpps32f stepDivided,
		                  nmpps32f bgnDivisor, nmpps32f stepDivisor, int count){
	nmpps32f Divided[count];
	nmpps32f Divisor[count];
	nmpps32f kd[count];
	nmpps32f res[count];
	nmppsStatus stat;
	float er;
	int i;
	//Создаем эталонные значения
	create_div32_vecs(Divided, bgnDivided, stepDivided,
					Divisor, bgnDivisor, stepDivisor,
					kd, count);
	//Производим рассчеты
	stat = nmppsDiv_32f(Divided, Divisor, res, count);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	//max_errf = 0;
	for (i=0; i<count; i++){
		er = fabs(kd[i]-res[i]);
		if (kd[i] != 0) er = fabs(100*er/kd[i]);

		if (er > max_errf) {
			max_errf = er;
			if (max_errf > div32_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}


nmppsStatus test_divC32_diap(nmpps32f bgnDivided, nmpps32f stepDivided,
		                  nmpps32f bgnDivisor, nmpps32f stepDivisor, int count){
	nmpps32f Divided[count];
	nmpps32f kd[count];
	nmpps32f res[count];
	nmppsStatus stat;
	float er;
	float max_err;
	int i, k;
	for (k=0; k < count; k++) {
		//Создаем эталонные значения
		create_divC32_vecs(Divided, bgnDivided, stepDivided,
						bgnDivisor, kd, count);
		//Производим рассчеты
		stat = nmppsDivC_32f(Divided, bgnDivisor, res, count);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		for (i=0; i<count; i++){
			er = fabs(kd[i]-res[i]);
			if (kd[i] != 0) er = fabs(100*er/kd[i]);

			if (er > max_err) {
				max_err = er;
				if (max_err > div32_critical_error) {
					return ((k+1) << 16) | (i+1) ;
				}
			}
		}

		bgnDivisor += stepDivisor;
	}
	return nmppsStsNoErr;
}

nmppsStatus test_divCRev32_diap(nmpps32f bgnDivisor, nmpps32f stepDivisor,
		                  nmpps32f bgnDivided, nmpps32f stepDivided, int count){
	nmpps32f Divisor[count];
	nmpps32f kd[count];
	nmpps32f res[count];
	nmppsStatus stat;
	float er;
	float max_err;
	int i, k;
	for (k=0; k < count; k++) {
		//Создаем эталонные значения
		create_divC32_vecs(Divisor, bgnDivisor, stepDivisor,
						bgnDivided, kd, count);
		//Производим рассчеты
		stat = nmppsDivC_32f(Divisor, bgnDivided, res, count);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		for (i=0; i<count; i++){
			er = fabs(kd[i]-res[i]);
			if (kd[i] != 0) er = fabs(100*er/kd[i]);

			if (er > max_err) {
				max_err = er;
				if (max_err > div32_critical_error) {
					return ((k+1) << 16) | (i+1) ;
				}
			}
		}

		bgnDivisor += stepDivisor;
	}
	return nmppsStsNoErr;
}


TEST(tests_div32, nmppsDiv_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_div32_diap(0, 0.133377789,
			              1000, 777.456,  1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_div32_diap(0, 0.133377789,
			              1000, 777.456,  2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_div32_diap(0, 0.133377789,
			              1000, 777.456,  3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_div32_diap(0, 0.133377789,
			              1000, 777.456,  64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_div32_diap(0, 0.133377789,
			              1000, 777.456,  65));

}

//Обычные значения
TEST(tests_div32, nmppsDiv_32f_Normal) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_div32_diap(0, 0.133377789,
			              1000, 777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_div32_diap(0, -0.133377789,
			              1000, 777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_div32_diap(0, 0.133377789,
			              -1000, -777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_div32_diap(0, -0.133377789,
			              -1000, -777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}

//Большие значения
TEST(tests_div32, nmppsDiv_32f_Big) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_div32_diap(1.7789e+38, 13.337e+35,
            1e+19, 777.456e+19,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Значения, близкие к 0
TEST(tests_div32, nmppsDiv_32f_Small) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_div32_diap(3.3333e-38, 1.3337e-35,
            1e-19, 777.456e+19,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Проверка возвращаемых результатов
TEST(tests_div32, nmppsDiv_32f_check_answer) {
	nmpps32f data_div_zero[] = {
			4,  -1.37, 6.777, 0
	};
	nmpps32f data[sizeof(data_div_zero)/sizeof(nmpps32f)];
	nmppsStatus stat;

	stat = nmppsDiv_32f(data_div_zero, data_div_zero, data, sizeof(data_div_zero)/sizeof(nmpps32f));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_32f(data, data, NULL, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_32f(data, NULL, data, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_32f(NULL, data, data, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_32f(data, data, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_32f(data, data, data, -1));
}


TEST(tests_div32, nmppsDiv_32f_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps32f data[67], original[67], out[67];
	fltint_t t, t1;

	t.ui32 = 0xDEADBEEF;
	original[0] = data[0] = out[0] = t.flt;
	original[1] = data[1] = out[1] = t.flt;
	for(i=2; i < sizeof(data)/sizeof(nmpps32f); i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.flt;
	}

	for(i=0;i<64;i++){
		nmppsDiv_32f(&data[2], &data[2], &out[2], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_FLOAT(data[k], original[k]);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[0]);
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[1]);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_float(t.flt, out[i+2]);
		t1.flt = out[i+3];
		if (t.ui32 != t1.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}

TEST(tests_div32, nmppsDiv_32f_subnormal) {
	float divided[29] = {
	   -NAN,       NAN,       NAN,       1,        NAN, //NaN среди операндов
	   0.0L,       -0.0L,     -0.0L,     0.0L,          // 0 делим на 0
	   1,          -1,        1,         -1,            // число делим на 0
	   0,          -0.0L,     0,         -0.0L,         // 0 делим на бесконечность
	   1,          -1,        1,         -1,            // число делим на бесконечность
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,     // бесконечность делим на число
	   INFINITY,   -INFINITY,  INFINITY, -INFINITY     // бесконечность делим на бесконечность
	};
	float divisor[29] = {
	   NAN,        -NAN,      NAN,       NAN,      -1,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   100,        -100,      100,       -100,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY
	};
	float kd[29] = {
	  -NAN,       -NAN,       NAN,       NAN,      -NAN,
	   NAN,       -NAN,       NAN,       -NAN,
	   INFINITY,  -INFINITY,  -INFINITY, INFINITY,
	   NAN,       -NAN,       -NAN,      NAN,
	   0.0L,      -0.0L,      -0.0L,     0.0L,
	   INFINITY,   -INFINITY,  -INFINITY, INFINITY,
	   NAN,        -NAN,      -NAN,       NAN
	};
	float out[sizeof(divided)/sizeof(float)];
	fltint_t t1, t2;
	nmppsDiv_32f(divided, divisor, out, sizeof(out)/sizeof(float));
	for (int i =0; i < sizeof(out)/sizeof(float); i++) {
		t1.flt = out[i];
		t2.flt = kd[i];
		if (t1.ui32 != t2.ui32){
		  TEST_ASSERT_EQUAL(t1.ui32, t2.ui32);
		}
	}

}

TEST_GROUP_RUNNER(tests_div32){

    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_small_vecs);
    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_Normal);
    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_Big);
    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_Small);
    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_check_answer);
    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_check_rewrite);
    RUN_TEST_CASE(tests_div32, nmppsDiv_32f_subnormal);

}



TEST(tests_divC32, nmppsDivC_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divC32_diap(0, 0.133377789,
			              1000, 777.456,  1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divC32_diap(0, 0.133377789,
			              1000, 777.456,  2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divC32_diap(0, 0.133377789,
			              1000, 777.456,  3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divC32_diap(0, 0.133377789,
			              1000, 777.456,  64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divC32_diap(0, 0.133377789,
			              1000, 777.456,  65));

}

//Обычные значения
TEST(tests_divC32, nmppsDivC_32f_Normal) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divC32_diap(0, 0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divC32_diap(0, -0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divC32_diap(0, 0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divC32_diap(0, -0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}

//Большие значения
TEST(tests_divC32, nmppsDivC_32f_Big) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divC32_diap(1.7789e+38, 13.337e+35,
            1e+19, 777.456e+19,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Значения, близкие к 0
TEST(tests_divC32, nmppsDivC_32f_Small) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divC32_diap(3.3333e-38, 1.3337e-35,
            1e-19, 777.456e+19,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Проверка возвращаемых результатов
TEST(tests_divC32, nmppsDivC_32f_check_answer) {
	nmpps32f data_div_zero[] = {
			4,  -1.37, 6.777, 0
	};
	nmpps32f data[sizeof(data_div_zero)/sizeof(nmpps32f)];
	nmppsStatus stat;

	stat = nmppsDivC_32f(data_div_zero, 0, data, sizeof(data_div_zero)/sizeof(nmpps32f));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDivC_32f(data, 1, NULL, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDivC_32f(NULL, 1, data, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDivC_32f(data, 1, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDivC_32f(data, 1, data, -1));
}

TEST(tests_divC32, nmppsDivC_32f_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps32f data[68], original[68], out[68];
	fltint_t t, t1;

	t.ui32 = 0xDEADBEEF;
	original[0] = data[0] = out[0] = t.flt;
	original[1] = data[1] = out[1] = t.flt;
	for(i=2; i < sizeof(data)/sizeof(nmpps32f); i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.flt;
	}

	for(i=1;i<=65;i++){
		nmppsDivC_32f(&data[2], 1, &out[2], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_FLOAT(data[k], original[k]);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[0]);
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[1]);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_float(t.flt, out[i+2]);
		t1.flt = out[i+2];
		if (t.ui32 != t1.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}


TEST(tests_divC32, nmppsDivC_32f_subnormal) {
	float divided[29] = {
	   -NAN,       NAN,       NAN,       1,        NAN, //NaN среди операндов
	   0.0L,       -0.0L,     -0.0L,     0.0L,          // 0 делим на 0
	   1,          -1,        1,         -1,            // число делим на 0
	   0,          -0.0L,     0,         -0.0L,         // 0 делим на бесконечность
	   1,          -1,        1,         -1,            // число делим на бесконечность
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,     // бесконечность делим на число
	   INFINITY,   -INFINITY,  INFINITY, -INFINITY     // бесконечность делим на бесконечность
	};
	float divisor[29] = {
	   NAN,        -NAN,      NAN,       NAN,      -1,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   100,        -100,      100,       -100,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY
	};
	float kd[29] = {
	  -NAN,       -NAN,       NAN,       NAN,      -NAN,
	   NAN,       -NAN,       NAN,       -NAN,
	   INFINITY,  -INFINITY,  -INFINITY, INFINITY,
	   NAN,       -NAN,       -NAN,      NAN,
	   0.0L,      -0.0L,      -0.0L,     0.0L,
	   INFINITY,   -INFINITY,  -INFINITY, INFINITY,
	   NAN,        -NAN,      -NAN,       NAN
	};
	float out[sizeof(divided)/sizeof(float)];
	fltint_t t1, t2;
	for (int i =0; i < sizeof(out)/sizeof(float); i++) {
		nmppsDivC_32f(divided, divisor[i], out,  sizeof(out)/sizeof(float));
		t1.flt = out[i];
		t2.flt = kd[i];
		if (t1.ui32 != t2.ui32){
		  TEST_ASSERT_EQUAL(t1.ui32, t2.ui32);
		}
	}

}



TEST_GROUP_RUNNER(tests_divC32){
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_small_vecs);
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_Normal);
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_Big);
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_Small);
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_check_answer);
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_check_rewrite);
    RUN_TEST_CASE(tests_divC32, nmppsDivC_32f_subnormal);

}




TEST(tests_divCRev32, nmppsDivCRev_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32_diap(0, 0.133377789,
			              1000, 777.456,  1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32_diap(0, 0.133377789,
			              1000, 777.456,  2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32_diap(0, 0.133377789,
			              1000, 777.456,  3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32_diap(0, 0.133377789,
			              1000, 777.456,  64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32_diap(0, 0.133377789,
			              1000, 777.456,  65));

}

//Обычные значения
TEST(tests_divCRev32, nmppsDivCRev_32f_Normal) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divCRev32_diap(0, 0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divCRev32_diap(0, -0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divCRev32_diap(0, 0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divCRev32_diap(0, -0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}

//Большие значения
TEST(tests_divCRev32, nmppsDivCRev_32f_Big) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divCRev32_diap(1.7789e+38, 13.337e+35,
            1e+19, 777.456e+19,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Значения, близкие к 0
TEST(tests_divCRev32, nmppsDivCRev_32f_Small) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divCRev32_diap(3.3333e-38, 1.3337e-35,
            1e-19, 777.456e+19,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Проверка возвращаемых результатов
TEST(tests_divCRev32, nmppsDivCRev_32f_check_answer) {
	nmpps32f data_div_zero[] = {
			4,  -1.37, 6.777, 0
	};
	nmpps32f data[sizeof(data_div_zero)/sizeof(nmpps32f)];
	nmppsStatus stat;

	stat = nmppsDivCRev_32f(data_div_zero, 1, data, sizeof(data_div_zero)/sizeof(nmpps32f));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDivC_32f(data, 1, NULL, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDivC_32f(NULL, 1, data, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDivC_32f(data, 1, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDivC_32f(data, 1, data, -1));
}

TEST(tests_divCRev32, nmppsDivCRev_32f_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps32f data[68], original[68], out[68];
	fltint_t t, t1;

	t.ui32 = 0xDEADBEEF;
	original[0] = data[0] = out[0] = t.flt;
	original[1] = data[1] = out[1] = t.flt;
	for(i=2; i < sizeof(data)/sizeof(nmpps32f); i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.flt;
	}

	for(i=1;i<=65;i++){
		nmppsDivCRev_32f(&data[2], 1, &out[2], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_FLOAT(data[k], original[k]);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[0]);
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[1]);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_float(t.flt, out[i+2]);
		t1.flt = out[i+2];
		if (t.ui32 != t1.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
	i = 0;
}


TEST(tests_divCRev32, nmppsDivCRev_32f_subnormal) {
	float divided[29] = {
	   -NAN,       NAN,       NAN,       1,        NAN, //NaN среди операндов
	   0.0L,       -0.0L,     -0.0L,     0.0L,          // 0 делим на 0
	   1,          -1,        1,         -1,            // число делим на 0
	   0,          -0.0L,     0,         -0.0L,         // 0 делим на бесконечность
	   1,          -1,        1,         -1,            // число делим на бесконечность
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,     // бесконечность делим на число
	   INFINITY,   -INFINITY,  INFINITY, -INFINITY     // бесконечность делим на бесконечность
	};
	float divisor[29] = {
	   NAN,        -NAN,      NAN,       NAN,      -1,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   100,        -100,      100,       -100,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY
	};
	float kd[29] = {
	  -NAN,       -NAN,       NAN,       NAN,      -NAN,
	   NAN,       -NAN,       NAN,       -NAN,
	   INFINITY,  -INFINITY,  -INFINITY, INFINITY,
	   NAN,       -NAN,       -NAN,      NAN,
	   0.0L,      -0.0L,      -0.0L,     0.0L,
	   INFINITY,   -INFINITY,  -INFINITY, INFINITY,
	   NAN,        -NAN,      -NAN,       NAN
	};
	float out[sizeof(divided)/sizeof(float)];
	fltint_t t1, t2;
	for (int i =0; i < sizeof(out)/sizeof(float); i++) {
		nmppsDivCRev_32f(divisor, divided[i], out,  sizeof(out)/sizeof(float));
		t1.flt = out[i];
		t2.flt = kd[i];
		if (t1.ui32 != t2.ui32){
		  TEST_ASSERT_EQUAL(t1.ui32, t2.ui32);
		}
	}

}

TEST_GROUP_RUNNER(tests_divCRev32){
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_small_vecs);
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_Normal);
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_Big);
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_Small);
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_check_answer);
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_check_rewrite);
    RUN_TEST_CASE(tests_divCRev32, nmppsDivCRev_32f_subnormal);
}

#endif
