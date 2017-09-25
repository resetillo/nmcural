#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if PhaseTestEnable

TEST_GROUP(tests_phase32f);
TEST_SETUP(tests_phase32f) {}
TEST_TEAR_DOWN(tests_phase32f) {}


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
void create_phase32f_vecs(nmpps32f* inRe, nmpps32f* inIm, nmpps32f* out, unsigned int len,
					  nmpps32f bgnRe, nmpps32f stepRe, nmpps32f bgnIm, nmpps32f stepIm)
{
	int i;
	for(i=0; i<len; i++){
		inRe[i] = bgnRe;
		inIm[i] = bgnIm;
		out[i] = right_atanf(bgnIm/bgnRe);
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

extern const nmpps32f phasef_critical_error;//<Значение максимальной погрешности для формата одинарной точности


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_phase32f_diap(nmpps32f bgnRe, nmpps32f stepRe, nmpps32f bgnIm, nmpps32f stepIm, int count){
	nmpps32f inRe[count];
	nmpps32f inIm[count];
	nmpps32f res[count];
	nmpps32f kd[count];
	nmpps32f er;
	nmpps32f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_phase32f_vecs(inRe, inIm, kd, count, bgnRe, stepRe, bgnIm, stepIm);
	//Расчет проверяемых значений
	stat = nmppsPhase_32f(inRe, inIm, res, count);
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

TEST(tests_phase32f, nmppsPhase32f_check_answer){
	nmpps32f data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_32f(data, data, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_32f(data, NULL, data, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_32f(NULL, data, data, 1));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_32f(data, data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_32f(data, data, data, -1));

}

TEST(tests_phase32f, nmppsPhase32f_check_rewrite){
	int i,k;
	nmpps32f dataRe[36], dataIm[36], original[36];
	nmpps32f out[36];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0] = dataRe[0] = dataIm[0] = out[0] =
	original[1] = dataRe[1] = dataIm[1] = out[1] = t.flt;
	for(i=1;i<sizeof(dataRe)/sizeof(nmpps32f);i++){
		dataRe[i] = dataIm[i] = original[i]= (nmpps32f)(i*i);
		out[i] = t.flt;
	}

	for(i=1;i<34;i++){
		nmppsPhase_32f(&dataRe[2], &dataIm[2], &out[2], i);
		for(k=0; k < sizeof(dataRe)/sizeof(nmpps32f); k++){
			if (dataRe[k]!=original[k] || dataIm[k]!=original[k]) {
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





TEST(tests_phase32f, nmppsPhase32f_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(0, 1, 10, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(0, 0.1, 10, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(0, 0.01, 10, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(0, 0.001, 10, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(0, 0.0001, 10, 1, 33));
}



TEST(tests_phase32f, nmppsPhase32f_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(-40, ((nmpps32f)87/(nmpps32f)COUNT_ITERATION), 700, ((nmpps32f)-1400/(nmpps32f)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(1.9875e+35, 1.7937e+35, 1.7777e+35, -1.937e+35, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(-1.7789e+35, -1.3337e+35, -1.6666e+35, 0.937e+35, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(3.3333e-35, 1.3337e-35, 2.1e-35, 1.1e-35, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase32f_diap(-7.7777e-35, -1.7777e-35, -1.1e-35, 0.1e-35, COUNT_ITERATION));
}


TEST(tests_phase32f, nmppsPhase32f_subnormal){
	nmpps32f dataRe[4] = {
			0, INFINITY, -1, -1
	};
	nmpps32f dataIm[4] = {
			0, INFINITY, -INFINITY, INFINITY
	};
	nmpps32f kd[4] = {
			NAN, NAN, -1.57079633, 1.57079633
	};
	nmpps32f res[4];
	fltint_t t1, t2;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsPhase_32f(dataRe, dataIm, res, 4));
	for (int i =0;i<4;i++){
		t1.flt = kd[i];
		t2.flt = res[i];
		if (t1.ui32 != t2.ui32){
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
	t1.flt = 0;
}



TEST_GROUP_RUNNER(tests_phase32f){
    RUN_TEST_CASE(tests_phase32f, nmppsPhase32f_check_answer);
    RUN_TEST_CASE(tests_phase32f, nmppsPhase32f_small_vecs);
    RUN_TEST_CASE(tests_phase32f, nmppsPhase32f_check_rewrite);
    RUN_TEST_CASE(tests_phase32f, nmppsPhase32f_calculation);
    RUN_TEST_CASE(tests_phase32f, nmppsPhase32f_subnormal);
}





#endif
