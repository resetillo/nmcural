#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

#if BlackmanTestEnable

TEST_GROUP(tests_blackmanOpt32f);
TEST_SETUP(tests_blackmanOpt32f) {}
TEST_TEAR_DOWN(tests_blackmanOpt32f) {}


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
void create_blackmanOpt32f_vecs(nmpps32f* in, nmpps32f* out, unsigned int len,
					  nmpps32f bgn, nmpps32f step)
{
	nmpps32f w, tmp, tmp1, alpha;

	alpha = -0.5f / (1.0f + cos(dbl_pi_flt/(len - 1.0f)));
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		tmp = dbl_pi_flt/((nmpps32f)len-1.0f);
		tmp *= i;
		tmp1 = cos(tmp);
		w = alpha*(1-tmp1*tmp1) + 0.5f*(1-tmp1);
		out[i] = in[i]*w;
		bgn += step;
	}
}


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_blackmanOpt32f_diap( nmpps32f bgn, nmpps32f step, int count){
	nmpps32f in[count];
	nmpps32f res[count];
	nmpps32f kd[count];
	nmpps32f er;
	nmpps32f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_blackmanOpt32f_vecs(in, kd, count, bgn, step);
	//Расчет проверяемых значений
	stat = nmppsWinBlackmanOpt_32f(in, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
			er = fabs(kd[i]- res[i]);
			/*if (fabs(kd[i])!=0) {
				er /= fabs(kd[i]);
				er *= 100;
			}*/
			if (er > max_err) {
				max_err = er;
				if (max_err > float_critical_error) {
					return i+1;
				}
			}
	}
	return nmppsStsNoErr;
}

TEST(tests_blackmanOpt32f, nmppsblackmanOpt32f_check_answer){
	nmpps32f data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinBlackmanOpt_32f(NULL, data, 4));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinBlackmanOpt_32f(data, NULL, 4));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32f(data, data, 3));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32f(data, data, 2));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32f(data, data, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32f(data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackmanOpt_32f(data, data, -1));

}

TEST(tests_blackmanOpt32f, nmppsblackmanOpt32f_check_rewrite){
	int i,k;
	nmpps32f data[68], original[68];
	nmpps32f out[(sizeof(data)/sizeof(nmpps32f))];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0] = data[0] = out[0] =
	original[1] = data[1] = out[1] = t.flt;
	for(i=2;i<sizeof(data)/sizeof(nmpps32f);i++){
		data[i] = original[i]= (nmpps32f)(i*i);
		out[i] = t.flt;
	}

	for(i=3; i< (sizeof(data)/sizeof(nmpps32f)) - 2; i++){
		nmppsWinBlackmanOpt_32f(&data[2], &out[2], i);
		for(k=0; k < (sizeof(data)/sizeof(nmpps32f)); k++){
			if (data[k]!=original[k]) {
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





TEST(tests_blackmanOpt32f, nmppsblackmanOpt32f_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(0, 0.1, 4));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(0, 0.01, 5));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(0, 0.001, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(0, 0.0001, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(0, 0.00001, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(0, 0.000001, 65));
}



TEST(tests_blackmanOpt32f, nmppsblackmanOpt32f_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(-40, ((nmpps32f)80/(nmpps32f)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(1.9875e+35, 1.7937e+35, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(-1.7789e+35, -1.3337e+35, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(3.3333e-35, 1.3337e-35, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackmanOpt32f_diap(-7.7777e-35, -1.7777e-35, COUNT_ITERATION));
}





TEST_GROUP_RUNNER(tests_blackmanOpt32f){
    RUN_TEST_CASE(tests_blackmanOpt32f, nmppsblackmanOpt32f_small_vecs);
    RUN_TEST_CASE(tests_blackmanOpt32f, nmppsblackmanOpt32f_check_answer);
    RUN_TEST_CASE(tests_blackmanOpt32f, nmppsblackmanOpt32f_check_rewrite);
    RUN_TEST_CASE(tests_blackmanOpt32f, nmppsblackmanOpt32f_calculation);
}





#endif
