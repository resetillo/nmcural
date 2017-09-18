#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if BlackmanTestEnable

TEST_GROUP(tests_blackmanOpt32fc);
TEST_SETUP(tests_blackmanOpt32fc) {}
TEST_TEAR_DOWN(tests_blackmanOpt32fc) {}


#define COUNT_ITERATION (100)


extern nmpps32f dbl_pi_flt;

extern nmpps32f float_critical_error;

/**
 * @brief Заполнение значений тестовых векторов
 *
 * @param in вектор исходных данных
 * @param out вектор резултирующих данных
 * @param len длина векторов
 * @param bgn начальное значение для вектора исходных данных
 * @param step шаг инкрементации
 * */
void create_blackmanOpt32fc_vecs(nmpps32fc* in, nmpps32fc* out, unsigned int len,
					  nmpps32fc bgn, nmpps32fc step)
{
	nmpps32f w, tmp, tmp1;
	nmpps32f alpha = -0.5f / (1.0f + cos(dbl_pi_flt/(len - 1.0f)));
	int i;

	for(i=0; i<len; i++){
		in[i].re = bgn.re;
		in[i].im = bgn.im;
		tmp = dbl_pi_flt/((nmpps32f)len-1.0f);
		tmp *= i;
		tmp1 = cos(tmp);
		w = alpha*(1-tmp1*tmp1) + 0.5f*(1-tmp1);
		out[i].re = in[i].re*w;
		out[i].im = in[i].im*w;
		bgn.re += step.re;
		bgn.im += step.im;
	}
}


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_blackmanOpt32fc_diap( nmpps32fc bgn, nmpps32fc step, int count){
	nmpps32fc in[count];
	nmpps32fc res[count];
	nmpps32fc kd[count];
	nmpps32f er, tmp;
	nmpps32f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_blackmanOpt32fc_vecs(in, kd, count, bgn, step);
	//Расчет проверяемых значений
	stat = nmppsWinBlackmanOpt_32fc(in, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
			er = fabs(kd[i].re- res[i].re);
			/*if (fabs(kd[i].re)!=0) {
				er /= fabs(kd[i].re);
				er *= 100;
			}*/
			tmp = fabs(kd[i].im- res[i].im);
			/*if (fabs(kd[i].im)!=0) {
				tmp /= fabs(kd[i].im);
				tmp *= 100;
			}*/
			if (tmp > er) er = tmp;

			if (er > max_err) {
				max_err = er;
				if (max_err > float_critical_error) {
					return i+1;
				}
			}
	}
	return nmppsStsNoErr;
}

TEST(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_check_answer){
	nmpps32fc data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinBlackmanOpt_32fc(NULL, data, 4));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinBlackmanOpt_32fc(data, NULL, 4));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32fc(data, data, 3));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32fc(data, data, 2));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32fc(data, data, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32fc(data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32fc(data, data, -1));

}

TEST(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_check_rewrite){
	int i,k;
	nmpps32fc data[68], original[68];
	nmpps32fc out[(sizeof(data)/sizeof(nmpps32fc))];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0].re = data[0].re = out[0].re =
	original[0].im = data[0].im = out[0].im =  t.flt;
	for(i=0;i<sizeof(data)/sizeof(nmpps32fc);i++){
		data[i].re = original[i].re =
		data[i].im = original[i].im = (nmpps32f)(i*i);
		out[i].re = out[i].im = t.flt;
	}

	for(i=3; i< (sizeof(data)/sizeof(nmpps32fc)) - 2; i++){
		nmppsWinBlackmanOpt_32fc(&data[1], &out[1], i);
		for(k=0; k < (sizeof(data)/sizeof(nmpps32fc)); k++){
			if (data[k].re!=original[k].re ||
					data[k].im!=original[k].im) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0].re!=t.flt || out[0].im!=t.flt) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+1].re!=t.flt || out[i+1].im!=t.flt) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
	i = 0;
}





TEST(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_small_vecs){
	nmpps32fc bgn, step;
	bgn.re = 0; bgn.re = 0;
	step.im = 0.1; step.im = 0.1;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, 4));
	step.im = 0.01; step.im = 0.01;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, 5));
	step.im = 0.001; step.im = 0.001;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, 32));
	step.im = 0.0001; step.im = 0.0001;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, 33));
	step.im = 0.00001; step.im = 0.00001;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, 64));
	step.im = 0.000001; step.im = 0.000001;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, 65));
}



TEST(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_calculation){
	nmpps32fc bgn, step;
	bgn.re = -40; bgn.re = -100;
	step.im = ((nmpps32f)80/(nmpps32f)COUNT_ITERATION);
	step.im = ((nmpps32f)200/(nmpps32f)COUNT_ITERATION);
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, COUNT_ITERATION));

	//Проверка больших значений
	bgn.re = 1.9875e+16; bgn.re = 3.12375e+16;
	step.re = 1.7937e+16; step.re = 2.01234e+16;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, COUNT_ITERATION));
	bgn.re = -1.7789e+16; bgn.re = -1.89789e+16;
	step.re = -1.3337e+16; step.re = -2.98765e+16;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, COUNT_ITERATION));

	//Проверка близких к 0 значений
	bgn.re = 3.3333e-16; bgn.re = 4.4444e-16;
	step.re = 1.3337e-16; step.re = 2.98765e-16;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, COUNT_ITERATION));
	bgn.re = -7.7777e-16; bgn.re = -5.5555e-16;
	step.re = -1.7777e-16; step.re = -3.1234e-16;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32fc_diap(bgn, step, COUNT_ITERATION));
}





TEST_GROUP_RUNNER(tests_blackmanOpt32fc){
    RUN_TEST_CASE(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_check_answer);
    RUN_TEST_CASE(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_small_vecs);
    RUN_TEST_CASE(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_check_rewrite);
    RUN_TEST_CASE(tests_blackmanOpt32fc, nmppsblackmanOpt32fc_calculation);
}





#endif
