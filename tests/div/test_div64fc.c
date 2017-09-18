#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if DivTestEnable


TEST_GROUP(tests_div64fc);
TEST_SETUP(tests_div64fc) {}
TEST_TEAR_DOWN(tests_div64fc) {}


#define COUNT_ITERATION (100)

extern const nmpps64f div_critical_error;

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


void create_div64fc_vecs(nmpps64fc* Divided, nmpps64fc bgnDivided, nmpps64fc stepDivided,
		             nmpps64fc* Divisor,  nmpps64fc bgnDivisor, nmpps64fc stepDivisor,
					 nmpps64fc* out, unsigned int len )
{
	nmpps64f tmp;
	int i;
	for(i=0; i<len; i++){
		Divided[i] = bgnDivided;
		Divisor[i] = bgnDivisor;
		tmp = (Divisor[i].re*Divisor[i].re + Divisor[i].im*Divisor[i].im);
		tmp = 1.0 / tmp;
		out[i].re =  (Divided[i].re*Divisor[i].re + Divided[i].im*Divisor[i].im) * tmp;
		out[i].im = (Divisor[i].re*Divided[i].im - Divided[i].re*Divisor[i].im) * tmp;
		bgnDivided.re += stepDivided.re;
		bgnDivided.im += stepDivided.im;
		bgnDivisor.re += stepDivisor.re;
		bgnDivisor.im += stepDivisor.im;
	}
}



nmppsStatus test_div64fc_diap(nmpps64fc bgnDivided, nmpps64fc stepDivided,
		                  nmpps64fc bgnDivisor, nmpps64fc stepDivisor, int count){
	nmpps64fc Divided[count];
	nmpps64fc Divisor[count];
	nmpps64fc kd[count];
	nmpps64fc res[count];
	nmpps64f max_err;
	nmppsStatus stat;
	double er, tmp;
	int i;
	//Создаем эталонные значения
	create_div64fc_vecs(Divided, bgnDivided, stepDivided,
					Divisor, bgnDivisor, stepDivisor,
					kd, count);
	//Производим рассчеты
	stat = nmppsDiv_64fc(Divided, Divisor, res, count);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<count; i++){
		er = fabs(kd[i].re-res[i].re);
		if (kd[i].re != 0) er = fabs(100*er/kd[i].re);

		tmp = fabs(kd[i].im-res[i].im);
		if (kd[i].im != 0) tmp = fabs(100*tmp/kd[i].im);
		if (tmp > er) er = tmp;

		if (er > max_err) {
			max_err = er;
			if (max_err > div_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}




TEST(tests_div64fc, nmppsDiv_64fc_calculation) {
	nmpps64fc bgnDivided, stepDivided,
			                  bgnDivisor, stepDivisor;
	nmppsStatus stat;

	//Обычные значения
	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = 0.133377789; stepDivided.im = 0.77123;
	bgnDivisor.re = 1000; bgnDivisor.im = 777;
	stepDivisor.re = 333.133377789; stepDivisor.im = 111.77123;
	stat = test_div64fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = -0.133377789; stepDivided.im = -0.77123;
	bgnDivisor.re = 1000; bgnDivisor.im = 777;
	stepDivisor.re = 333.133377789; stepDivisor.im = 111.77123;
	stat = test_div64fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = 0.133377789; stepDivided.im = 0.77123;
	bgnDivisor.re = -1000; bgnDivisor.im = -777;
	stepDivisor.re = -333.133377789; stepDivisor.im = -111.77123;
	stat = test_div64fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = -0.133377789; stepDivided.im = -0.77123;
	bgnDivisor.re = -1000; bgnDivisor.im = -777;
	stepDivisor.re = -333.133377789; stepDivisor.im = -111.77123;
	stat = test_div64fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);


    //Большие значения
	bgnDivided.re = 1.7789e+100; bgnDivided.im = 1.334679e+100;
	stepDivided.re = 13.337e+100; stepDivided.im = 18.99965e+100;
	bgnDivisor.re = 1e+57; bgnDivisor.im = 1.3e+57;
	stepDivisor.re = 777.456e+47; stepDivisor.im = -111.77123e+47;
	stat = test_div64fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);


    //Значения, близкие к 0
	bgnDivided.re = 3.3333e-100; bgnDivided.im = 2.8337e-100;
	stepDivided.re = 1.3337e-100; stepDivided.im = 0.1537e-100;
	bgnDivisor.re = 1e-57; bgnDivisor.im = 7.77e-47;
	stepDivisor.re = 333.133e-56; stepDivisor.im = 12.971e-36;
	stat = test_div64fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

}



//Проверка возвращаемых результатов
TEST(tests_div64fc, nmppsDiv_64fc_check_answer) {
	nmpps64fc data_div64fc_zero[] = {
			{4,4},  {-1.37,8}, {6.777,7}, {0,0}
	};
	nmpps64fc data[sizeof(data_div64fc_zero)/sizeof(nmpps64fc)];
	nmppsStatus stat;

	stat = nmppsDiv_64fc(data_div64fc_zero, data_div64fc_zero, data, sizeof(data_div64fc_zero)/sizeof(nmpps64fc));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_64fc(data, data, NULL, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_64fc(data, NULL, data, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_64fc(NULL, data, data, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_64fc(data, data, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_64fc(data, data, data, -1));
}


TEST(tests_div64fc, nmppsDiv_64fc_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps64fc data[33], original[33], out[33];
	dblint_t t, t1;

	t.ui64 = 0xDEADBEEFDEADBEEF;
	original[0].re = data[0].re = out[0].re =
			original[0].im = data[0].im = out[0].im =t.dbl;
	for(i=1;i<33;i++){
		original[i].re = data[i].re =
				original[i].im = data[i].im =i*i;
		out[i].re = out[i].im = t.dbl;
	}

	for(i=0;i<31;i++){
		nmppsDiv_64fc(&data[1], &data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps64fc); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_DOUBLE(data[k].re, original[k].re);
			TEST_ASSERT_EQUAL_DOUBLE(data[k].im, original[k].im);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[0].re);
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[0].im);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[i+2]);
		t1.dbl = out[i+2].re;
		if (t.ui64 != t1.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
		t1.dbl = out[i+2].im;
		if (t.ui64 != t1.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}


TEST_GROUP_RUNNER(tests_div64fc){
    RUN_TEST_CASE(tests_div64fc, nmppsDiv_64fc_calculation);
    RUN_TEST_CASE(tests_div64fc, nmppsDiv_64fc_check_answer);
    RUN_TEST_CASE(tests_div64fc, nmppsDiv_64fc_check_rewrite);

}





#endif

