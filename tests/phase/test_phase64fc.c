#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if PhaseTestEnable

TEST_GROUP(tests_phase64fc);
TEST_SETUP(tests_phase64fc) {}
TEST_TEAR_DOWN(tests_phase64fc) {}


#define COUNT_ITERATION (100)

double right_atan(double x);


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
void create_phase_vecs(nmpps64fc* in, nmpps64f* out, unsigned int len,
					  nmpps64f bgnRe, nmpps64f stepRe, nmpps64f bgnIm, nmpps64f stepIm)
{
	int i;
	for(i=0; i<len; i++){
		in[i].re = bgnRe;
		in[i].im = bgnIm;
		out[i] = right_atan(in[i].im/in[i].re);
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

const nmpps64f phase_critical_error = 10e-15;//<Значение максимальной погрешности для формата двойной точности


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_phase64fc_diap(nmpps64f bgnRe, nmpps64f stepRe, nmpps64f bgnIm, nmpps64f stepIm, int count){
	nmpps64fc in[count];
	nmpps64f res[count];
	nmpps64f kd[count];
	nmpps64f er;
	nmpps64f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_phase_vecs(in, kd, count, bgnRe, stepRe, bgnIm, stepIm);
	//Расчет проверяемых значений
	stat = nmppsPhase_64fc(in, res, count);
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

TEST(tests_phase64fc, nmppsPhase64fc_check_answer){
	nmpps64fc data1[1];
	nmpps64f data2[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_64fc(data1, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsPhase_64fc(NULL, data2, 1));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_64fc(data1, data2, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsPhase_64fc(data1, data2, -1));

}

TEST(tests_phase64fc, nmppsPhase64fc_check_rewrite){
	int i,k;
	nmpps64fc data[35], original[35];
	nmpps64f out[35];
	dblint_t t;
	t.ui64 = 0xDEADBEEFDEADBEEF;

	original[0].re = data[0].re =
	original[0].im = data[0].im = out[0] = t.dbl;
	for(i=1;i<35;i++){
		data[i].re = original[i].re = data[i].im = original[i].im = (nmpps64f)(i*i);
		out[i] = t.dbl;
	}

	for(i=1;i<34;i++){
		nmppsPhase_64fc(&data[1], &out[1], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps64fc); k++){
			if (data[k].re!=original[k].re ||
					data[k].im!=original[k].im ) {
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





TEST(tests_phase64fc, nmppsPhase64fc_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 1, 10, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 0.1, 10, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 0.01, 10, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 0.001, 10, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 0.0001, 10, 1, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 0.0001, 10, 1, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(0, 0.0001, 10, 1, 65));
}



TEST(tests_phase64fc, nmppsPhase64fc_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(-40, ((double)87/(double)COUNT_ITERATION), 700, ((double)-1400/(double)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(1.9875e+300, 17.937, 1.7777e+300, -1.937e+300, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(-1.7789e+300, -13.337, -1.6666e+300, 0.937e+300, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(3.3333e-300, 1.3337e-300, 2.1e-300, 1.1e-300, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_phase64fc_diap(-7.7777e-300, -1.7777e-300, -1.1e-300, 0.1e-300, COUNT_ITERATION));
}


TEST(tests_phase64fc, nmppsPhase64fc_subnormal){
	nmpps64fc data[4] = {
			{0,0}, {INFINITY,INFINITY}, {-1, -INFINITY}, {-1, INFINITY}
	};
	nmpps64f kd[4] = {
			NAN, NAN, -1.5707963267948966192313216916398, 1.5707963267948966192313216916398
	};
	nmpps64f res[4];
	dblint_t t1, t2;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsPhase_64fc(data, res, 4));
	for (int i =0;i<4;i++){
		t1.dbl = kd[i];
		t2.dbl = res[i];
		if (t1.ui64 != t2.ui64){
			TEST_ASSERT_EQUAL(-1, i);
		}
	}

}



TEST_GROUP_RUNNER(tests_phase64fc){
    RUN_TEST_CASE(tests_phase64fc, nmppsPhase64fc_check_answer);
    RUN_TEST_CASE(tests_phase64fc, nmppsPhase64fc_small_vecs);
    RUN_TEST_CASE(tests_phase64fc, nmppsPhase64fc_check_rewrite);
    RUN_TEST_CASE(tests_phase64fc, nmppsPhase64fc_calculation);
    RUN_TEST_CASE(tests_phase64fc, nmppsPhase64fc_subnormal);
}





#endif
