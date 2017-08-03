#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if DivTestEnable

TEST_GROUP(tests_div64);
TEST_SETUP(tests_div64) {}
TEST_TEAR_DOWN(tests_div64) {}

TEST_GROUP(tests_divC64);
TEST_SETUP(tests_divC64) {}
TEST_TEAR_DOWN(tests_divC64) {}


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
void create_div_vecs(nmpps64f* Divided, nmpps64f bgnDivided, nmpps64f stepDivided,
		             nmpps64f* Divisor,  nmpps64f bgnDivisor, nmpps64f stepDivisor,
					 nmpps64f* out, unsigned int len )
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

void create_divC_vecs(nmpps64f* Divided, nmpps64f bgnDivided, nmpps64f stepDivided,
		             nmpps64f Divisor,  nmpps64f* out, unsigned int len )
{
	int i;
	for(i=0; i<len; i++){
		Divided[i] = bgnDivided;
		out[i] =  Divided[i] / Divisor;
		bgnDivided += stepDivided;
	}
}

const nmpps64f div_critical_error = 1e-13;

/**
 * @brief Тестирование деление диапазонов
 *
 * @param bgnDivided Начальное значение для делимых
 * @param stepDivided Приращение для делимых
 * @param bgnDivisor Начальное значение для делителей
 * @param stepDivisor Приращение для делителей
 * @param count Длина тестируемых векторов
 * */

double max_err = 0;

nmppsStatus test_div_diap(nmpps64f bgnDivided, nmpps64f stepDivided,
		                  nmpps64f bgnDivisor, nmpps64f stepDivisor, int count){
	nmpps64f Divided[count];
	nmpps64f Divisor[count];
	nmpps64f kd[count];
	nmpps64f res[count];
	nmppsStatus stat;
	double er;
	int i;
	//Создаем эталонные значения
	create_div_vecs(Divided, bgnDivided, stepDivided,
					Divisor, bgnDivisor, stepDivisor,
					kd, count);
	//Производим рассчеты
	stat = nmppsDiv_64f(Divided, Divisor, res, count);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<count; i++){
		er = fabs(kd[i]-res[i]);
		if (kd[i] != 0) er = fabs(100*er/kd[i]);

		if (er > max_err) {
			max_err = er;
			if (max_err > div_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}


nmppsStatus test_divC_diap(nmpps64f bgnDivided, nmpps64f stepDivided,
		                  nmpps64f bgnDivisor, nmpps64f stepDivisor, int count){
	nmpps64f Divided[count];
	nmpps64f kd[count];
	nmpps64f res[count];
	nmppsStatus stat;
	double er;
	int i, k;
	for (k=0; k < count; k++) {
		//Создаем эталонные значения
		create_divC_vecs(Divided, bgnDivided, stepDivided,
						bgnDivisor, kd, count);
		//Производим рассчеты
		stat = nmppsDivC_64f(Divided, bgnDivisor, res, count);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		for (i=0; i<count; i++){
			er = fabs(kd[i]-res[i]);
			if (kd[i] != 0) er = fabs(100*er/kd[i]);

			if (er > max_err) {
				max_err = er;
				if (max_err > div_critical_error) {
					return ((k+1) << 16) | (i+1) ;
				}
			}
		}

		bgnDivisor += stepDivisor;
	}
	return nmppsStsNoErr;
}


//Обычные значения
TEST(tests_div64, nmppsDiv_64f_Normal) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_div_diap(0, 0.133377789,
			              1000, 777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_div_diap(0, -0.133377789,
			              1000, 777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_div_diap(0, 0.133377789,
			              -1000, -777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_div_diap(0, -0.133377789,
			              -1000, -777.456,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}

//Большие значения
TEST(tests_div64, nmppsDiv_64f_Big) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_div_diap(1.7789e+300, 13.337e+300,
            1e+157, 777.456e+157,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Значения, близкие к 0
TEST(tests_div64, nmppsDiv_64f_Small) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_div_diap(3.3333e-300, 1.3337e-300,
            1e-157, 777.456e+157,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Проверка возвращаемых результатов
TEST(tests_div64, nmppsDiv_64f_check_answer) {
	nmpps64f data_div_zero[] = {
			4,  -1.37, 6.777, 0
	};
	nmpps64f data[sizeof(data_div_zero)/sizeof(nmpps64f)];
	nmppsStatus stat;

	stat = nmppsDiv_64f(data_div_zero, data_div_zero, data, sizeof(data_div_zero)/sizeof(nmpps64f));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_64f(data, data, NULL, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_64f(data, NULL, data, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_64f(NULL, data, data, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_64f(data, data, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_64f(data, data, data, -1));
}


TEST(tests_div64, nmppsDiv_64f_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps64f data[33], original[33], out[33];
	dblint_t t, t1;

	t.ui64 = 0xDEADBEEFDEADBEEF;
	original[0] = data[0] = out[0] = t.dbl;
	for(i=1;i<33;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.dbl;
	}

	for(i=0;i<31;i++){
		nmppsDiv_64f(&data[1], &data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps64f); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_DOUBLE(data[k], original[k]);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[0]);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[i+2]);
		t1.dbl = out[i+2];
		if (t.ui64 != t1.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}

TEST(tests_div64, nmppsDiv_64f_subnormal) {
	double divided[29] = {
	   -NAN,       NAN,       NAN,       1,        NAN, //NaN среди операндов
	   0.0L,       -0.0L,     -0.0L,     0.0L,          // 0 делим на 0
	   1,          -1,        1,         -1,            // число делим на 0
	   0,          -0.0L,     0,         -0.0L,         // 0 делим на бесконечность
	   1,          -1,        1,         -1,            // число делим на бесконечность
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,     // бесконечность делим на число
	   INFINITY,   -INFINITY,  INFINITY, -INFINITY     // бесконечность делим на бесконечность
	};
	double divisor[29] = {
	   NAN,        -NAN,      NAN,       NAN,      -1,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   100,        -100,      100,       -100,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY
	};
	double kd[29] = {
	  -NAN,       -NAN,       NAN,       NAN,      -NAN,
	   NAN,       -NAN,       NAN,       -NAN,
	   INFINITY,  -INFINITY,  -INFINITY, INFINITY,
	   NAN,       -NAN,       -NAN,      NAN,
	   0.0L,      -0.0L,      -0.0L,     0.0L,
	   INFINITY,   -INFINITY,  -INFINITY, INFINITY,
	   NAN,        -NAN,      -NAN,       NAN
	};
	double out[sizeof(divided)/sizeof(double)];
	dblint_t t1, t2;
	nmppsDiv_64f(divided, divisor, out, sizeof(out)/sizeof(double));
	for (int i =0; i < sizeof(out)/sizeof(double); i++) {
		t1.dbl = out[i];
		t2.dbl = kd[i];
		TEST_ASSERT_EQUAL(t1.ui64, t2.ui64);
	}

}

TEST_GROUP_RUNNER(tests_div64){
    RUN_TEST_CASE(tests_div64, nmppsDiv_64f_Normal);
    RUN_TEST_CASE(tests_div64, nmppsDiv_64f_Big);
    RUN_TEST_CASE(tests_div64, nmppsDiv_64f_Small);
    RUN_TEST_CASE(tests_div64, nmppsDiv_64f_check_answer);
    RUN_TEST_CASE(tests_div64, nmppsDiv_64f_check_rewrite);
    RUN_TEST_CASE(tests_div64, nmppsDiv_64f_subnormal);

}


//Обычные значения
TEST(tests_divC64, nmppsDivC_64f_Normal) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divC_diap(0, 0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divC_diap(0, -0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divC_diap(0, 0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divC_diap(0, -0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}

//Большие значения
TEST(tests_divC64, nmppsDivC_64f_Big) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divC_diap(1.7789e+300, 13.337e+300,
            1e+157, 777.456e+157,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Значения, близкие к 0
TEST(tests_divC64, nmppsDivC_64f_Small) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divC_diap(3.3333e-300, 1.3337e-300,
            1e-157, 777.456e+157,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Проверка возвращаемых результатов
TEST(tests_divC64, nmppsDivC_64f_check_answer) {
	nmpps64f data_divC_zero[] = {
			4,  -1.37, 6.777, 0
	};
	nmpps64f data[sizeof(data_divC_zero)/sizeof(nmpps64f)];
	nmppsStatus stat;

	stat = nmppsDivC_64f(data_divC_zero, 0.0L, data, sizeof(data_divC_zero)/sizeof(nmpps64f));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDivC_64f(NULL, 1, data, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDivC_64f(data, 1, NULL, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDivC_64f(data, 1, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDivC_64f(data, 1, data, -1));
}

TEST(tests_divC64, nmppsDivC_64f_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps64f data[33], original[33], out[33];
	dblint_t t, t1;

	t.ui64 = 0xDEADBEEFDEADBEEF;
	original[0] = data[0] = out[0] = t.dbl;
	for(i=1;i<33;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.dbl;
	}

	for(i=0;i<31;i++){
		nmppsDivC_64f(&data[1], data[i], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps64f); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_DOUBLE(data[k], original[k]);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[0]);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[i+2]);
		t1.dbl = out[i+2];
		if (t.ui64 != t1.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}


TEST(tests_divC64, nmppsDivC_64f_subnormal) {
	double divided[29] = {
	   -NAN,       NAN,       NAN,       1,        NAN, //NaN среди операндов
	   0.0L,       -0.0L,     -0.0L,     0.0L,          // 0 делим на 0
	   1,          -1,        1,         -1,            // число делим на 0
	   0,          -0.0L,     0,         -0.0L,         // 0 делим на бесконечность
	   1,          -1,        1,         -1,            // число делим на бесконечность
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,     // бесконечность делим на число
	   INFINITY,   -INFINITY,  INFINITY, -INFINITY     // бесконечность делим на бесконечность
	};
	double divisor[29] = {
	   NAN,        -NAN,      NAN,       NAN,      -1,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   0.0L,       0.0L,      -0.0L,     -0.0L,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY,
	   100,        -100,      100,       -100,
	   INFINITY,   INFINITY,  -INFINITY, -INFINITY
	};
	double kd[29] = {
	  -NAN,       -NAN,       NAN,       NAN,      -NAN,
	   NAN,       -NAN,       NAN,       -NAN,
	   INFINITY,  -INFINITY,  -INFINITY, INFINITY,
	   NAN,       -NAN,       -NAN,      NAN,
	   0.0L,      -0.0L,      -0.0L,     0.0L,
	   INFINITY,   -INFINITY,  -INFINITY, INFINITY,
	   NAN,        -NAN,      -NAN,       NAN
	};
	double out[sizeof(divided)/sizeof(double)];
	dblint_t t1, t2;
	for (int i =0; i < sizeof(out)/sizeof(double); i++) {
		nmppsDivC_64f(&divided[i], divisor[i], &out[i], 1);
		t1.dbl = out[i];
		t2.dbl = kd[i];
		if (t1.ui64 != t2.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}

}



TEST_GROUP_RUNNER(tests_divC64){
    RUN_TEST_CASE(tests_divC64, nmppsDivC_64f_Normal);
    RUN_TEST_CASE(tests_divC64, nmppsDivC_64f_Big);
    RUN_TEST_CASE(tests_divC64, nmppsDivC_64f_Small);
    RUN_TEST_CASE(tests_divC64, nmppsDivC_64f_check_answer);
    RUN_TEST_CASE(tests_divC64, nmppsDivC_64f_check_rewrite);
    RUN_TEST_CASE(tests_divC64, nmppsDivC_64f_subnormal);

}

#endif
