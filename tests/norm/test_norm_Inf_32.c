#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormInfTestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_norm_Inf_32f);
TEST_SETUP(tests_norm_Inf_32f) {}
TEST_TEAR_DOWN(tests_norm_Inf_32f) {}


nmpps32f create_norm32Inf_vecs(nmpps32f bgn, nmpps32f step, int count, nmpps32f* vec){
	int i;
	nmpps32f out = 0;
	for (i=0; i < count; i++){
		vec[i] = bgn;
		if (i&1) {
			vec[i] = -vec[i];
		}
		if (fabsf(vec[i]) > out) {
			out = fabsf(vec[i]);
		}
		bgn += step;
	}
	return out;
}

nmppsStatus test_norm32Inf_diap(nmpps32f bgn, nmpps32f step, int count){
	nmpps32f Vec[count];
	nmpps32f KD;
	nmpps32f res;
	nmppsStatus stat;
	//Создаем эталонные значения
	KD = create_norm32Inf_vecs(bgn, step, count, Vec);
	//Производим рассчеты
	stat = nmppsNorm_Inf_32f(Vec, count, &res);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	if (res != KD) {
		TEST_ASSERT_EQUAL_FLOAT(res, KD);
		return -1;
	}
	return nmppsStsNoErr;
}

TEST(tests_norm_Inf_32f, nmppsNorm_Inf_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-0.0777, 0.1, 65));
}

TEST(tests_norm_Inf_32f, nmppsNorm_Inf_32f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-COUNT_ITERATION/2, 1.0, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-1.3e+38, 1.0e+37, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(1.3e+38, -1.0e+37, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(-1.3e-38, 1.0e-37, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm32Inf_diap(1.3e-38, -1.0e-37, COUNT_ITERATION));

}

//Проверка возвращаемых результатов
TEST(tests_norm_Inf_32f, nmppsNorm_Inf_32f_check_answer) {
	nmpps32f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_Inf_32f(0, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_Inf_32f(tmp, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_Inf_32f(tmp, 0, tmp));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_Inf_32f(tmp, -11, tmp));
}


TEST_GROUP_RUNNER(tests_norm_Inf_32f){
    RUN_TEST_CASE(tests_norm_Inf_32f, nmppsNorm_Inf_32f_check_answer);
    RUN_TEST_CASE(tests_norm_Inf_32f, nmppsNorm_Inf_32f_small_vecs);
    RUN_TEST_CASE(tests_norm_Inf_32f, nmppsNorm_Inf_32f_calculation);
}
#endif

