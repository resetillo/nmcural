#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if PhaseTestEnable

TEST_GROUP(tests_phase64f);
TEST_SETUP(tests_phase64f) {}
TEST_TEAR_DOWN(tests_phase64f) {}


#define COUNT_ITERATION (100)

double right_atan(double x);
float right_atanf(float x);


extern nmpps64f pi_dbl;
/**
 * @brief Заполнение значений тестовых векторов
 *
 * @param in вектор исходных данных
 * @param out вектор резултирующих данных
 * @param len длина векторов
 * @param bgn начальное значение для вектора исходных данных
 * @param step шаг инкрементации
 * */
void create_phase64f_vecs(nmpps64f* inRe, nmpps64f* inIm, nmpps64f* out, unsigned int len,
					  nmpps64f bgnRe, nmpps64f stepRe, nmpps64f bgnIm, nmpps64f stepIm)
{
	int i;
	for(i=0; i<len; i++){
		inRe[i] = bgnRe;
		inIm[i] = bgnIm;
		out[i] = right_atan(inIm[i]/inRe[i]);
		if (bgnRe < 0){
			if (bgnIm >= 0) {
				out[i] += pi_dbl;
			} else {
				out[i] -= pi_dbl;
			}
		}
		bgnRe += stepRe;
		bgnIm += stepIm;
	}
}

extern const nmpps64f phase_critical_error;//<Значение максимальной погрешности для формата двойной точности


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_phase64f_diap(nmpps64f bgnRe, nmpps64f stepRe, nmpps64f bgnIm, nmpps64f stepIm, int count){
	nmpps64f inRe[count];
	nmpps64f inIm[count];
	nmpps64f res[count];
	nmpps64f kd[count];
	nmpps64f er;
	nmpps64f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_phase64f_vecs(inRe, inIm, kd, count, bgnRe, stepRe, bgnIm, stepIm);
	//Расчет проверяемых значений
	stat = nmppsPhase_64f(inRe, inIm, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
			er = fabs(fabs(kd[i])-fabs(res[i]));
			if (er > max_err) {
				max_err = er;
				if (max_err > phase_critical_error) {
					return i+1;
				}
			}
	}
	return nmppsStsNoErr;
}

TEST(tests_phase64f, nmppsPhase64f_check_answer){
	nmpps64f data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_64f(NULL, data, data, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_64f(data, NULL, data, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_64f(data, data, NULL, 1));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_64f(data, data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_64f(data, data, data, -1));

}

TEST(tests_phase64f, nmppsPhase64f_check_rewrite){
	int i,k;
	nmpps64f dataRe[35], dataIm[35], original[35];
	nmpps64f out[35];
	dblint_t t;
	t.ui64 = 0xDEADBEEFDEADBEEF;

	original[0] = dataRe[0] =
        dataIm[0] = out[0] = t.dbl;
	for(i=1;i<35;i++){
		dataRe[i] = dataIm[i] = original[i] = (nmpps64f)(i*i);
		out[i] = t.dbl;
	}

	for(i=1;i<34;i++){
		nmppsPhase_64f(&dataRe[1], &dataIm[1], &out[1], i);
		for(k=0; k < sizeof(dataRe)/sizeof(nmpps64f); k++){
			if (dataRe[k]!=original[k] ||
					dataIm[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0]!=t.dbl) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+1]!=t.dbl) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
}





TEST(tests_phase64f, nmppsPhase64f_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(0, 0.1, 10, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(0, 1, 10, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(0, 0.01, 10, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(0, 0.001, 10, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(0, 0.0001, 10, 1, 33));
}



TEST(tests_phase64f, nmppsPhase64f_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(-40, ((double)87/(double)COUNT_ITERATION), 700, ((double)-1400/(double)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(1.9875e+300, 17.937, 1.7777e+300, -1.937e+300, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(-1.7789e+300, -13.337, -1.6666e+300, 0.937e+300, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(3.3333e-300, 1.3337e-300, 2.1e-300, 1.1e-300, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64f_diap(-7.7777e-300, -1.7777e-300, -1.1e-300, 0.1e-300, COUNT_ITERATION));
}


TEST(tests_phase64f, nmppsPhase64f_subnormal){
	nmpps64f dataRe[4] = {
			0, INFINITY, -1, -1
	};
	nmpps64f dataIm[4] = {
			0, INFINITY, -INFINITY, INFINITY
	};
	nmpps64f kd[4] = {
			NAN, NAN, -1.5707963267948966192313216916398, 1.5707963267948966192313216916398
	};
	nmpps64f res[4];
	dblint_t t1, t2;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsPhase_64f(dataRe, dataIm, res, 4));
	for (int i =0;i<4;i++){
		t1.dbl = kd[i];
		t2.dbl = res[i];
		if (t1.ui64 != t2.ui64){
			TEST_ASSERT_EQUAL(-1, i);
		}
	}

}



TEST_GROUP_RUNNER(tests_phase64f){
    RUN_TEST_CASE(tests_phase64f, nmppsPhase64f_check_answer);
    RUN_TEST_CASE(tests_phase64f, nmppsPhase64f_small_vecs);
    RUN_TEST_CASE(tests_phase64f, nmppsPhase64f_calculation);
    RUN_TEST_CASE(tests_phase64f, nmppsPhase64f_check_rewrite);
    RUN_TEST_CASE(tests_phase64f, nmppsPhase64f_subnormal);
}





#endif
