#include "unity/unity_fixture.h"
#include "nmpps.h"

#define COUNT_ITERATION (100)

TEST_GROUP(tests_norm_L1_64f);
TEST_SETUP(tests_norm_L1_64f) {}
TEST_TEAR_DOWN(tests_norm_L1_64f) {}


nmpps64f create_norm_L1_64_vecs(nmpps64f bgn, nmpps64f step, int count, nmpps64f* vec){
	int i;
	nmpps64f out = 0;
	for (i=0; i < count; i++){
		vec[i] = bgn;
		out += fabs(bgn);
		bgn += step;
	}
	return out;
}

nmppsStatus test_norm_L1_64_diap(nmpps64f bgn, nmpps64f step, int count){
	nmpps64f Vec[count];
	nmpps64f KD;
	nmpps64f res;
	nmppsStatus stat;
	//Создаем эталонные значения
	KD = create_norm_L1_64_vecs(bgn, step, count, Vec);
	//Производим рассчеты
	stat = nmppsNorm_L1_64f(Vec, count, &res);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	TEST_ASSERT_EQUAL_FLOAT(res, KD);
	return nmppsStsNoErr;
}

TEST(tests_norm_L1_64f, nmppsNorm_L1_64f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-0.0777, 0.1, 65));
}

TEST(tests_norm_L1_64f, nmppsNorm_L1_64f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-COUNT_ITERATION/2, 1.0, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-1.3e+300, 1.0e+299, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(1.3e+300, -1.0e+299, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(-1.3e-300, 1.0e-299, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_L1_64_diap(1.3e-300, -1.0e-299, COUNT_ITERATION));

}

//Проверка возвращаемых результатов
TEST(tests_norm_L1_64f, nmppsNorm_L1_64f_check_answer) {
	nmpps64f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_L1_64f(0, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_L1_64f(tmp, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_L1_64f(tmp, 0, tmp));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_L1_64f(tmp, -11, tmp));
}


TEST_GROUP_RUNNER(tests_norm_L1_64f){
    RUN_TEST_CASE(tests_norm_L1_64f, nmppsNorm_L1_64f_check_answer);
    RUN_TEST_CASE(tests_norm_L1_64f, nmppsNorm_L1_64f_small_vecs);
    RUN_TEST_CASE(tests_norm_L1_64f, nmppsNorm_L1_64f_calculation);
}
