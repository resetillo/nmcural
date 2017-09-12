#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include <math.h>

#if KaiserTestEnable

TEST_GROUP(tests_exp_32f);
TEST_SETUP(tests_exp_32f) {}
TEST_TEAR_DOWN(tests_exp_32f) {}


#define COUNT_ITERATION (100)

const nmpps32f critical_error_f32 = 1.0e-06;//<Значение максимальной погрешности для формата одинарной точности
nmppsStatus exp_32f(const nmpps32f* pSrc, nmpps32f* pDst, int len);

//float right_expf(float x);

void create_exp_32f_vecs(nmpps32f* in, nmpps32f* out, unsigned int len,
					  nmpps32f bgn, nmpps32f step)
{
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		out[i] = expf(bgn);
		bgn += step;
	}
}

nmppsStatus test_exp_32f_diap(nmpps32f bgn, nmpps32f step, int count) {
	nmpps32f in[count];
	nmpps32f res[count];
	nmpps32f kd[count];
	nmppsStatus stat;
	nmpps32f er;
	nmpps32f arg = bgn;
	nmpps32f max_err = 0;
	int i = 0;
	//Заполнение входных и эталонных данных
	create_exp_32f_vecs(in, kd, count, arg, step);
	//Расчет проверяемых значений
	stat = exp_32f(in, res, count);
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
		arg = in[i];
		er = fabsf(fabsf(kd[i])-fabsf(res[i]));
		if (er > max_err) {
			max_err = er;
			if (max_err > critical_error_f32) {
				return i + 1;
			}
		}

	}

	return nmppsStsNoErr;
}


TEST(tests_exp_32f, exp_32f_check_answer) {
	nmpps32f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, exp_32f(0, tmp, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, exp_32f(tmp, 0, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, exp_32f(tmp, tmp, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, exp_32f(tmp, tmp, -1));
}

TEST(tests_exp_32f, exp_32f_check_rewrite){
	int i,k;
	nmpps32f data[68], original[68];
	nmpps32f out[68];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0] = data[0] = out[0] =
	original[1] = data[1] = out[1] = t.flt;
	for(i=2;i<sizeof(data)/sizeof(nmpps32f);i++){
		data[i] = original[i]= (nmpps32f)(i*i);
		out[i] = t.flt;
	}

	for(i=1;i<=65;i++){
		exp_32f(&data[2], &out[2], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
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

TEST(tests_exp_32f, exp_32f_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(0, 0.1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(0, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(0, 0.01, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(0, 0.001, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(0, 0.0001, 65));
}

TEST(tests_exp_32f, exp_32f_calculation){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(0, ((float)0.5/(float)COUNT_ITERATION), COUNT_ITERATION));
	/*TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(-50, ((float)87/(float)COUNT_ITERATION), COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_exp_32f_diap(-80, ((float)160/(float)COUNT_ITERATION), COUNT_ITERATION));*/
}

TEST_GROUP_RUNNER(tests_exp_32f){
    RUN_TEST_CASE(tests_exp_32f, exp_32f_small_vecs);
    RUN_TEST_CASE(tests_exp_32f, exp_32f_check_answer);
    RUN_TEST_CASE(tests_exp_32f, exp_32f_check_rewrite);
    RUN_TEST_CASE(tests_exp_32f, exp_32f_calculation);
}

#endif
