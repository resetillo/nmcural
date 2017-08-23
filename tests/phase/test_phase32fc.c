#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if PhaseTestEnable

TEST_GROUP(tests_phase32fc);
TEST_SETUP(tests_phase32fc) {}
TEST_TEAR_DOWN(tests_phase32fc) {}


#define COUNT_ITERATION (100)

float right_atanf(float x);


extern nmpps32f pi_flt;
/**
 * @brief Заполнение значений тестовых векторов
 *
 * @param in вектор исходных данных
 * @param out вектор резултирующих данных
 * @param len длина векторов
 * @param bgn начальное значение для вектора исходных данных
 * @param step шаг инкрементации
 * */
void create_phase32fc_vecs(nmpps32fc* in, nmpps32f* out, unsigned int len,
					  nmpps32f bgnRe, nmpps32f stepRe, nmpps32f bgnIm, nmpps32f stepIm)
{
	int i;
	for(i=0; i<len; i++){
		in[i].re = bgnRe;
		in[i].im = bgnIm;
		out[i] = right_atanf(in[i].im/in[i].re);
		if (bgnRe < 0){
			if (bgnIm >= 0) {
				out[i] += pi_flt;
			} else {
				out[i] -= pi_flt;
			}
		}
		bgnRe += stepRe;
		bgnIm += stepIm;
	}
}

const nmpps32f phasef_critical_error = 10e-07;//<Значение максимальной погрешности для формата одинарной точности


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_phase32fc_diap(nmpps32f bgnRe, nmpps32f stepRe, nmpps32f bgnIm, nmpps32f stepIm, int count){
	nmpps32fc in[count];
	nmpps32f res[count];
	nmpps32f kd[count];
	nmpps32f er;
	nmpps32f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_phase32fc_vecs(in, kd, count, bgnRe, stepRe, bgnIm, stepIm);
	//Расчет проверяемых значений
	stat = nmppsPhase_32fc(in, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
			er = fabs(fabs(kd[i])-fabs(res[i]));
			if (er > max_err) {
				max_err = er;
				if (max_err > phasef_critical_error) {
					return i+1;
				}
			}
	}
	return nmppsStsNoErr;
}

TEST(tests_phase32fc, nmppsPhase32fc_check_answer){
	nmpps32fc data1[1];
	nmpps32f data2[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_32fc(data1, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_32fc(NULL, data2, 1));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_32fc(data1, data2, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_32fc(data1, data2, -1));

}

TEST(tests_phase32fc, nmppsPhase32fc_check_rewrite){
	int i,k;
	nmpps32fc data[36], original[36];
	nmpps32f out[36];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0].re = data[0].re =
	original[0].im = data[0].im = out[0] = out[1] = t.flt;
	for(i=1;i<sizeof(data)/sizeof(nmpps32fc);i++){
		data[i].re = original[i].re = data[i].im = original[i].im = (nmpps32f)(i*i);
		out[i] = t.flt;
	}

	for(i=1;i<34;i++){
		nmppsPhase_32fc(&data[1], &out[2], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps32fc); k++){
			if (data[k].re!=original[k].re ||
					data[k].im!=original[k].im ) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0]!=t.flt || out[1]!=t.flt) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+2]!=t.flt) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
	i = 0;
}





TEST(tests_phase32fc, nmppsPhase32fc_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(0, 1, 10, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(0, 0.1, 10, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(0, 0.01, 10, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(0, 0.001, 10, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(0, 0.0001, 10, 1, 33));
}



TEST(tests_phase32fc, nmppsPhase32fc_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(-40, ((nmpps32f)87/(nmpps32f)COUNT_ITERATION), 700, ((nmpps32f)-1400/(nmpps32f)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(1.9875e+35, 1.7937e+35, 1.7777e+35, -1.937e+35, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(-1.7789e+35, -1.3337e+35, -1.6666e+35, 0.937e+35, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(3.3333e-35, 1.3337e-35, 2.1e-35, 1.1e-35, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32fc_diap(-7.7777e-35, -1.7777e-35, -1.1e-35, 0.1e-35, COUNT_ITERATION));
}


TEST(tests_phase32fc, nmppsPhase32fc_subnormal){
	nmpps32fc data[4] = {
			{0,0}, {INFINITY,INFINITY}, {-1, -INFINITY}, {-1, INFINITY}
	};
	nmpps32f kd[4] = {
			NAN, NAN, -1.57079633, 1.57079633
	};
	nmpps32f res[4];
	fltint_t t1, t2;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsPhase_32fc(data, res, 4));
	for (int i =0;i<4;i++){
		t1.flt = kd[i];
		t2.flt = res[i];
		if (t1.ui32 != t2.ui32){
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
	t1.flt = 0;
}



TEST_GROUP_RUNNER(tests_phase32fc){
    RUN_TEST_CASE(tests_phase32fc, nmppsPhase32fc_check_answer);
    RUN_TEST_CASE(tests_phase32fc, nmppsPhase32fc_small_vecs);
    RUN_TEST_CASE(tests_phase32fc, nmppsPhase32fc_check_rewrite);
    RUN_TEST_CASE(tests_phase32fc, nmppsPhase32fc_calculation);
    RUN_TEST_CASE(tests_phase32fc, nmppsPhase32fc_subnormal);
}





#endif
