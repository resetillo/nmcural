#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include <math.h>

#if BlackmanTestEnable

TEST_GROUP(tests_blackman16s);
TEST_SETUP(tests_blackman16s) {}
TEST_TEAR_DOWN(tests_blackman16s) {}


#define COUNT_ITERATION (100)


extern nmpps16s dbl_pi_flt;

extern nmpps16s float_critical_error;

/**
 * @brief Заполнение значений тестовых векторов
 *
 * @param in вектор исходных данных
 * @param out вектор резултирующих данных
 * @param len длина векторов
 * @param bgn начальное значение для вектора исходных данных
 * @param step шаг инкрементации
 * */
void create_blackman16s_vecs(nmpps16s* in, nmpps16s* out, unsigned int len,
					  nmpps16s bgn, nmpps16s step, nmpps32f alpha)
{
	nmpps16s w, tmp, tmp1;
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		tmp = dbl_pi_flt/((nmpps16s)len-1.0f);
		tmp *= i;
		//w = 0.5f*((alpha + 1.0f) - cosf(tmp) - alpha*cosf(2*tmp));
		w = alpha + 1.0f;
		w -= cos(tmp);
		tmp = tmp*2;
		tmp1 = cos(tmp);
		w -= alpha*tmp1;
		w *= 0.5f;
		out[i] = (nmpps16s)(in[i]*w);
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
nmppsStatus test_blackman16s_diap( nmpps16s bgn, nmpps16s step, nmpps32f alpha, int count){
	nmpps16s in[count];
	nmpps16s res[count];
	nmpps16s kd[count];
	nmpps32f er;
	nmpps32f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_blackman16s_vecs(in, kd, count, bgn, step, alpha);
	//Расчет проверяемых значений
	stat = nmppsWinBlackman_16s(in, res, count, alpha);
	if (stat!=nmppsStsNoErr) return stat;
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
			er = abs(kd[i]- res[i]);
			if (abs(kd[i])!=0) {
				er /= abs(kd[i]);
				er *= 100;
			}
			if (er > max_err) {
				max_err = er;
				if (max_err > float_critical_error) {
					return i+1;
				}
			}
	}
	return nmppsStsNoErr;
}

TEST(tests_blackman16s, nmppsblackman16s_check_answer){
	nmpps16s data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinBlackman_16s(NULL, data, 3, 3.14));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinBlackman_16s(data, NULL, 3, 3.14));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackman_16s(data, data, 2, 3.14));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackman_16s(data, data, 1, 3.14));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackman_16s(data, data, 0, 3.14));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinBlackman_16s(data, data, -1, 3.14));

}

TEST(tests_blackman16s, nmppsblackman16s_check_rewrite){
	int i,k;
	nmpps16s data[68], original[68];
	nmpps16s out[(sizeof(data)/sizeof(nmpps16s))];
	int t;
	t = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0] = data[0] = out[0] =
	original[1] = data[1] = out[1] = t;
	for(i=2;i<sizeof(data)/sizeof(nmpps16s);i++){
		data[i] = original[i]= (nmpps16s)(i*i);
		out[i] = t;
	}

	for(i=3; i< (sizeof(data)/sizeof(nmpps16s)) - 2; i++){
		nmppsWinBlackman_16s(&data[2], &out[2], i, 7.777);
		for(k=0; k < (sizeof(data)/sizeof(nmpps16s)); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0]!=t || out[1]!=t) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+2]!=t) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
	i = 0;
}





TEST(tests_blackman16s, nmppsblackman16s_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 1, 8.888, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 2, 8.888, 4));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 3, 8.888, 5));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 4, 8.888, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 5, 8.888, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 6, 8.888, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(0, 7, 8.888, 65));
}



TEST(tests_blackman16s, nmppsblackman16s_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(-40, round(((nmpps16s)80/(nmpps16s)COUNT_ITERATION)), 3.33, COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(10000, 100, 1.23, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_blackman16s_diap(-10000, -100, 9.87, COUNT_ITERATION));

}





TEST_GROUP_RUNNER(tests_blackman16s){
    RUN_TEST_CASE(tests_blackman16s, nmppsblackman16s_check_answer);
    RUN_TEST_CASE(tests_blackman16s, nmppsblackman16s_small_vecs);
    RUN_TEST_CASE(tests_blackman16s, nmppsblackman16s_check_rewrite);
    RUN_TEST_CASE(tests_blackman16s, nmppsblackman16s_calculation);
}





#endif
