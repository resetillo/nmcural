#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if DivTestEnable


TEST_GROUP(tests_div32fc);
TEST_SETUP(tests_div32fc) {}
TEST_TEAR_DOWN(tests_div32fc) {}


#define COUNT_ITERATION (100)


extern const nmpps32f div32f_critical_error;

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


void create_div32fc_vecs(nmpps32fc* Divided, nmpps32fc bgnDivided, nmpps32fc stepDivided,
		             nmpps32fc* Divisor,  nmpps32fc bgnDivisor, nmpps32fc stepDivisor,
					 nmpps32fc* out, unsigned int len )
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



nmppsStatus test_div32fc_diap(nmpps32fc bgnDivided, nmpps32fc stepDivided,
		                  nmpps32fc bgnDivisor, nmpps32fc stepDivisor, int count){
	nmpps32fc Divided[count];
	nmpps32fc Divisor[count];
	nmpps32fc kd[count];
	nmpps32fc res[count];
	nmpps32f max_err;
	nmppsStatus stat;
	double er, tmp;
	int i;
	//Создаем эталонные значения
	create_div32fc_vecs(Divided, bgnDivided, stepDivided,
					Divisor, bgnDivisor, stepDivisor,
					kd, count);
	//Производим рассчеты
	stat = nmppsDiv_32fc(Divided, Divisor, res, count);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<count; i++){
		er = fabsf(kd[i].re-res[i].re);
		if (kd[i].re != 0) er = fabsf(100*er/kd[i].re);

		tmp = fabsf(kd[i].im-res[i].im);
		if (kd[i].im != 0) tmp = fabsf(100*tmp/kd[i].im);
		if (tmp > er) er = tmp;

		if (er > max_err) {
			max_err = er;
			if (max_err > div32f_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}




TEST(tests_div32fc, nmppsDiv_32fc_calculation) {
	nmpps32fc bgnDivided, stepDivided,
			                  bgnDivisor, stepDivisor;
	nmppsStatus stat;

	//Обычные значения
	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = 0.133377789; stepDivided.im = 0.77123;
	bgnDivisor.re = 1000; bgnDivisor.im = 777;
	stepDivisor.re = 333.133377789; stepDivisor.im = 111.77123;
	stat = test_div32fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = -0.133377789; stepDivided.im = -0.77123;
	bgnDivisor.re = 1000; bgnDivisor.im = 777;
	stepDivisor.re = 333.133377789; stepDivisor.im = 111.77123;
	stat = test_div32fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = 0.133377789; stepDivided.im = 0.77123;
	bgnDivisor.re = -1000; bgnDivisor.im = -777;
	stepDivisor.re = -333.133377789; stepDivisor.im = -111.77123;
	stat = test_div32fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

	bgnDivided.re = 0; bgnDivided.im = 0;
	stepDivided.re = -0.133377789; stepDivided.im = -0.77123;
	bgnDivisor.re = -1000; bgnDivisor.im = -777;
	stepDivisor.re = -333.133377789; stepDivisor.im = -111.77123;
	stat = test_div32fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);


    //Большие значения
	bgnDivided.re = 1.7789e+10; bgnDivided.im = 1.334679e+10;
	stepDivided.re = 13.337e+10; stepDivided.im = 18.99965e+10;
	bgnDivisor.re = 1e+5; bgnDivisor.im = 1.3e+5;
	stepDivisor.re = 777.456e+4; stepDivisor.im = -111.77123e+4;
	stat = test_div32fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);


    //Значения, близкие к 0
	bgnDivided.re = 3.3333e-10; bgnDivided.im = 2.8337e-10;
	stepDivided.re = 1.3337e-10; stepDivided.im = 0.1537e-10;
	bgnDivisor.re = 1e-5; bgnDivisor.im = 7.77e-4;
	stepDivisor.re = 333.133e-5; stepDivisor.im = 12.971e-3;
	stat = test_div32fc_diap(bgnDivided, stepDivided, bgnDivisor, stepDivisor,  COUNT_ITERATION);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, stat);

}



//Проверка возвращаемых результатов
TEST(tests_div32fc, nmppsDiv_32fc_check_answer) {
	nmpps32fc data_div32fc_zero[] = {
			{4,4},  {-1.37,8}, {6.777,7}, {0,0}
	};
	nmpps32fc data[sizeof(data_div32fc_zero)/sizeof(nmpps32fc)];
	nmppsStatus stat;

	stat = nmppsDiv_32fc(data_div32fc_zero, data_div32fc_zero, data, sizeof(data_div32fc_zero)/sizeof(nmpps32fc));
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_32fc(data, data, NULL, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_32fc(data, NULL, data, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDiv_32fc(NULL, data, data, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_32fc(data, data, data, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDiv_32fc(data, data, data, -1));
}


TEST(tests_div32fc, nmppsDiv_32fc_check_rewrite) {
	int i,k;
	//nmppsStatus stat;
	nmpps32fc data[68], original[68], out[68];
	#define DATA_SIZE (sizeof(data)/sizeof(nmpps32fc))
	fltint_t t, t1;

	t.ui32 = 0xDEADBEEF;
	original[0].re = data[0].re = out[0].re =
			original[0].im = data[0].im = out[0].im =t.flt;
	for(i=1;i<DATA_SIZE;i++){
		original[i].re = data[i].re =
				original[i].im = data[i].im =i*i;
		out[i].re = out[i].im = t.flt;
	}

	for(i=0;i<DATA_SIZE-2;i++){
		nmppsDiv_32fc(&data[1], &data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps32fc); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_FLOAT(data[k].re, original[k].re);
			TEST_ASSERT_EQUAL_FLOAT(data[k].im, original[k].im);
		}
		//Запись перед началом
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[0].re);
		TEST_ASSERT_EQUAL_FLOAT(t.flt, out[0].im);
		//Запись после окончания векторов
		//TEST_ASSERT_EQUAL_DOUBLE(t.dbl, out[i+2]);
		t1.flt = out[i+2].re;
		if (t.ui32 != t1.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
		t1.flt = out[i+2].im;
		if (t.ui32 != t1.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}


TEST_GROUP_RUNNER(tests_div32fc){
    RUN_TEST_CASE(tests_div32fc, nmppsDiv_32fc_calculation);
    RUN_TEST_CASE(tests_div32fc, nmppsDiv_32fc_check_answer);
    RUN_TEST_CASE(tests_div32fc, nmppsDiv_32fc_check_rewrite);

}





#endif

