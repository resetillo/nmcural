#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormDiffL1TestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_normDiff_L1_32f);
TEST_SETUP(tests_normDiff_L1_32f) {}
TEST_TEAR_DOWN(tests_normDiff_L1_32f) {}


nmpps32f create_normDiff_L1_32f_vecs(nmpps32f bgn1, nmpps32f step1, nmpps32f* vec1,
		                             nmpps32f bgn2, nmpps32f step2, nmpps32f* vec2, int count){
	int i;
	nmpps32f out = 0;
	for (i=0; i < count; i++){
		vec1[i] = bgn1;
		vec2[i] = bgn2;
		out += fabsf(bgn1 -bgn2);
		bgn1 += step1;
		bgn2 += step2;
	}
	return out;
}

nmppsStatus test_normDiff_L1_32f_diap(nmpps32f bgn1, nmpps32f step1, nmpps32f bgn2, nmpps32f step2, int count){
	nmpps32f Vec1[count];
	nmpps32f Vec2[count];
	nmpps32f KD;
	nmpps32f res;
	nmppsStatus stat;
	//float er;
	int i;
	//Создаем эталонные значения
	KD = create_normDiff_L1_32f_vecs(bgn1, step1,  Vec1, bgn2, step2,  Vec2, count);
	//Производим рассчеты
	stat = nmppsNormDiff_L1_32f(Vec1, Vec2, count, &res);
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

TEST(tests_normDiff_L1_32f, nmppsNormDiff_L1_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-0.0777, 0.1, -0.333, 0.22, 65));
}

TEST(tests_normDiff_L1_32f, nmppsNormDiff_L1_32f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-COUNT_ITERATION/2, 1.0, 1.23, 0.987, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-1.3e+38, 1.0e+37, -1.2e+38, 1.0e+36, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(1.3e+38, -1.0e+37, 1.2e+38, -1.0e+36, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(-1.3e-38, 1.0e-37, -1.2e-38, 1.0e-36, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L1_32f_diap(1.3e-38, -1.0e-37, 1.2e-38, -1.0e-36, COUNT_ITERATION));

}

//Проверка возвращаемых результатов
TEST(tests_normDiff_L1_32f, nmppsNormDiff_L1_32f_check_answer) {
	nmpps32f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L1_32f(0, tmp, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L1_32f(tmp, 0, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L1_32f(tmp, tmp, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L1_32f(tmp, tmp, 0, tmp));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L1_32f(tmp, tmp,-1, tmp));
}


TEST_GROUP_RUNNER(tests_normDiff_L1_32f){
    RUN_TEST_CASE(tests_normDiff_L1_32f, nmppsNormDiff_L1_32f_check_answer);
    RUN_TEST_CASE(tests_normDiff_L1_32f, nmppsNormDiff_L1_32f_small_vecs);
    RUN_TEST_CASE(tests_normDiff_L1_32f, nmppsNormDiff_L1_32f_calculation);
}
#endif

