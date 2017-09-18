#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if DivTestEnable

TEST_GROUP(tests_divCRev32f);
TEST_SETUP(tests_divCRev32f) {}
TEST_TEAR_DOWN(tests_divCRev32f) {}

#define COUNT_ITERATION (100)

extern const nmpps32f div32f_critical_error;

void create_divCRev32f_vecs(nmpps32f* Divisor, nmpps32f bgnDivisor, nmpps32f stepDivisor,
		             nmpps32f Divided,  nmpps32f* out, unsigned int len )
{
	int i;
	for(i=0; i<len; i++){
		Divisor[i] = bgnDivisor;
		out[i] =  Divided / Divisor[i];
		bgnDivisor += stepDivisor;
	}
}


nmppsStatus test_divCRev32f_diap(nmpps32f bgnDivisor, nmpps32f stepDivisor,
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
		create_divCRev32f_vecs(Divisor, bgnDivisor, stepDivisor,
						bgnDivided, kd, count);
		//Производим рассчеты
		stat = nmppsDivCRev_32f(Divisor, bgnDivided, res, count);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		for (i=0; i<count; i++){
			er = fabs(kd[i]-res[i]);
			if (kd[i] != 0) er = fabs(100*er/kd[i]);

			if (er > max_err) {
				max_err = er;
				if (max_err > div32f_critical_error) {
					return ((k+1) << 16) | (i+1) ;
				}
			}
		}

		bgnDivisor += stepDivisor;
	}
	return nmppsStsNoErr;
}






TEST(tests_divCRev32f, nmppsDivCRev_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32f_diap(0.1, 0.133377789,
			              1000, 777.456,  1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32f_diap(0.1, 0.133377789,
			              1000, 777.456,  2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32f_diap(0.1, 0.133377789,
			              1000, 777.456,  3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32f_diap(0.1, 0.133377789,
			              1000, 777.456,  64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_divCRev32f_diap(0.1, 0.133377789,
			              1000, 777.456,  65));

}

//Обычные значения
TEST(tests_divCRev32f, nmppsDivCRev_32f_Normal) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divCRev32f_diap(0.1, 0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divCRev32f_diap(0.1, -0.133377789,
			              1000, 777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divCRev32f_diap(0.1, 0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	stat = test_divCRev32f_diap(0.1, -0.133377789,
			              -1000, -777.456,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}

//Большие значения
TEST(tests_divCRev32f, nmppsDivCRev_32f_Big) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divCRev32f_diap(1.7789e+37, 13.337e+34,
            1e+19, 777.456e+19,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Значения, близкие к 0
TEST(tests_divCRev32f, nmppsDivCRev_32f_Small) {
	nmppsStatus stat = nmppsStsNoErr;
	stat = test_divCRev32f_diap(3.3333e-37, 1.3337e-35,
            1e-19, 777.456e+19,  COUNT_ITERATION/10);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);
}


//Проверка возвращаемых результатов
TEST(tests_divCRev32f, nmppsDivCRev_32f_check_answer) {
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

TEST(tests_divCRev32f, nmppsDivCRev_32f_check_rewrite) {
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


TEST(tests_divCRev32f, nmppsDivCRev_32f_subnormal) {
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

TEST_GROUP_RUNNER(tests_divCRev32f){
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_small_vecs);
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_Normal);
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_Small);
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_Big);
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_check_answer);
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_check_rewrite);
    RUN_TEST_CASE(tests_divCRev32f, nmppsDivCRev_32f_subnormal);
}



#endif
