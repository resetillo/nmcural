#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormDiffL2TestEnable

#define COUNT_ITERATION (100)

TEST_GROUP(tests_normDiff_L2_64f);
TEST_SETUP(tests_normDiff_L2_64f) {}
TEST_TEAR_DOWN(tests_normDiff_L2_64f) {}

double right_sqrt(double x);
nmpps64f create_normDiff_L2_64_vecs(nmpps64f bgn1, nmpps64f step1, nmpps64f* vec1,
		                            nmpps64f bgn2, nmpps64f step2, nmpps64f* vec2, int count ){
	int i;
	nmpps64f outf = 0;
	nmpps64f tmpf;
	for (i=0; i < count; i++){
		vec1[i] = bgn1;
		vec2[i] = bgn2;
		tmpf = bgn1 - bgn2;
		outf += tmpf*tmpf;
		bgn1 += step1;
		bgn2 += step2;
	}
	outf = right_sqrt(outf);
	return outf;
}

nmppsStatus test_normDiff_L2_64_diap(nmpps64f bgn1, nmpps64f step1, nmpps64f bgn2, nmpps64f step2, int count){
	nmpps64f Vec1[count];
	nmpps64f Vec2[count];
	nmpps64f KD;
	nmpps64f res;
	nmppsStatus stat;
	//Создаем эталонные значения
	KD = create_normDiff_L2_64_vecs(bgn1, step1, Vec1, bgn2, step2, Vec2, count );
	//Производим рассчеты
	stat = nmppsNormDiff_L2_64f(Vec1, Vec2, count, &res);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	TEST_ASSERT_EQUAL_DOUBLE(res, KD);
	return nmppsStsNoErr;
}

TEST(tests_normDiff_L2_64f, nmppsNormDiff_L2_64f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-0.0777, 0.1, 0.444, 0.222, 65));
}

TEST(tests_normDiff_L2_64f, nmppsNormDiff_L2_64f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-COUNT_ITERATION/2, 1.0, 0.123, 0.321, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-1.3e+148, 1.0e+147, -1.2e+148, 2.0e+147, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(1.3e+148, -1.0e+147, 1.2e+148, -2.0e+147, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(-1.3e-148, 1.0e-147, -1.2e-148, 2.0e-147, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_64_diap(1.3e-148, -1.0e-147, 1.2e-148, -2.0e-147, COUNT_ITERATION));

}

//Проверка возвращаемых результатов
TEST(tests_normDiff_L2_64f, nmppsNormDiff_L2_64f_check_answer) {
	nmpps64f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_64f(0, tmp, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_64f(tmp, 0, 1, tmp));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_64f(tmp, tmp, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L2_64f(tmp, tmp, 0, tmp));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L2_64f(tmp, tmp, -1, tmp));
}


TEST_GROUP_RUNNER(tests_normDiff_L2_64f){
    RUN_TEST_CASE(tests_normDiff_L2_64f, nmppsNormDiff_L2_64f_check_answer);
    RUN_TEST_CASE(tests_normDiff_L2_64f, nmppsNormDiff_L2_64f_small_vecs);
    RUN_TEST_CASE(tests_normDiff_L2_64f, nmppsNormDiff_L2_64f_calculation);
}

#endif


