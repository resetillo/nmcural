#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormDiffInfTestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_normDiff_Inf_32f);
TEST_SETUP(tests_normDiff_Inf_32f) {}
TEST_TEAR_DOWN(tests_normDiff_Inf_32f) {}


nmpps32f create_normDiff_Inf_32f_vecs( nmpps32f bgn1, nmpps32f step1, nmpps32f* vec1,
		                        nmpps32f bgn2, nmpps32f step2, nmpps32f* vec2, int count ){
	int i;
	nmpps32f out = bgn1 - bgn2;
	nmpps32f tmpf;
	for (i=0; i < count; i++){
		vec1[i] = bgn1;
		vec2[i] = bgn2;
		if (i&1) {
			vec1[i] = -vec1[i];
			vec2[i] = -vec2[i];
		}
		tmpf = fabsf(vec1[i] - vec2[i]);
		if (fabsf(tmpf) > out) {
			out = tmpf;
		}
		bgn1 += step1;
		bgn2 += step2;
	}
	return out;
}

nmppsStatus test_normDiff_Inf_32f_diap(nmpps32f bgn1, nmpps32f step1, nmpps32f bgn2, nmpps32f step2, int count){
	nmpps32f Vec1[count];
	nmpps32f Vec2[count];
	nmpps32f KD;
	nmpps32f res;
	nmppsStatus stat;
	//Создаем эталонные значения
	KD = create_normDiff_Inf_32f_vecs(bgn1, step1, Vec1,
			                   bgn2, step2, Vec2, count);
	//Производим рассчеты
	stat = nmppsNormDiff_Inf_32f(Vec1, Vec2, count, &res);
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

TEST(tests_normDiff_Inf_32f, nmppsNormDiff_Inf_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-0.0777, 0.1, -0.0333, 0.01, 65));
}

TEST(tests_normDiff_Inf_32f, nmppsNormDiff_Inf_32f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-COUNT_ITERATION/2, 1.0,  -0.0333, 0.01, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-1.3e+38, 1.0e+37, -1.2e+38, 1.0e+36, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(1.3e+38, -1.0e+37, 1.2e+38, -1.0e+36, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(-1.3e-38, 1.0e-37, -1.2e-38, 1.0e-36, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_Inf_32f_diap(1.3e-38, -1.0e-37, 1.2e-38, -1.0e-36, COUNT_ITERATION));

}

//Проверка возвращаемых результатов
TEST(tests_normDiff_Inf_32f, nmppsNormDiff_Inf_32f_check_answer) {
	nmpps32f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_Inf_32f(0,   tmp, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_Inf_32f(tmp, 0,  1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_Inf_32f(tmp, tmp, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_Inf_32f(tmp, tmp, 0, tmp));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_Inf_32f(tmp, tmp, -1, tmp));
}


TEST_GROUP_RUNNER(tests_normDiff_Inf_32f){
    RUN_TEST_CASE(tests_normDiff_Inf_32f, nmppsNormDiff_Inf_32f_check_answer);
    RUN_TEST_CASE(tests_normDiff_Inf_32f, nmppsNormDiff_Inf_32f_small_vecs);
    RUN_TEST_CASE(tests_normDiff_Inf_32f, nmppsNormDiff_Inf_32f_calculation);
}

#endif

