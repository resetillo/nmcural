#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormDiffL2TestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_normDiff_L2_16s32f);
TEST_SETUP(tests_normDiff_L2_16s32f) {}
TEST_TEAR_DOWN(tests_normDiff_L2_16s32f) {}

double right_sqrt(double x);

nmpps32f create_normDiff_L2_16s32f_vecs(nmpps16s bgn1, nmpps16s step1, nmpps16s* vec1,
		                                nmpps16s bgn2, nmpps16s step2, nmpps16s* vec2, int count ){
	int i;
	nmpps32f outf = 0;
	nmpps32f tmpf;
	for (i=0; i < count; i++){
		vec1[i] = bgn1;
		vec2[i] = bgn2;
		tmpf = (nmpps32f)(bgn1-bgn2);
		outf += tmpf*tmpf;
		bgn1 += step1;
		bgn2 += step2;
	}
	return right_sqrt(outf);
}

nmppsStatus test_normDiff_L2_16s32f_diap(nmpps16s bgn1, nmpps16s step1, nmpps16s bgn2, nmpps16s step2, int count){
	nmpps16s Vec1[count];
	nmpps16s Vec2[count];
	nmpps32f KD;
	nmpps32f res;
	nmppsStatus stat;
	//Создаем эталонные значения
	KD = create_normDiff_L2_16s32f_vecs(bgn1, step1, Vec1, bgn2, step2, Vec2, count);
	//Производим рассчеты
	stat = nmppsNormDiff_L2_16s32f(Vec1, Vec2, count, &res);
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

TEST(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-1, 1, 22, 2, 65));
}

TEST(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-COUNT_ITERATION/2, 1, -777, -2, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(-32768, 11,  -22, -2, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32f_diap(32767, -11,  22, 2, COUNT_ITERATION));
}

//Проверка возвращаемых результатов
TEST(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_check_answer) {
	nmpps16s tmpi[1];
	nmpps32f tmpf[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_16s32f(0, tmpi, 1, tmpf));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_16s32f(tmpi, 0, 1, tmpf));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_16s32f(tmpi, tmpi, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L2_16s32f(tmpi, tmpi, 0, tmpf));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L2_16s32f(tmpi, tmpi, -1, tmpf));
}

TEST(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_subnormal) {
	//Учитываться должны только данные в младших разрядах
	unsigned int vec1[4] = {0x10004, 0x1FFFC,0x33330004,0x777FFFC};
	unsigned int vec2[4] = {0x80002, 0x2FFFE,0x77770002,0x333FFFE};
	nmpps32f res;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsNormDiff_L2_16s32f(vec1, vec2, 4, &res));
	TEST_ASSERT_EQUAL_FLOAT(res, 4.0);
}


TEST_GROUP_RUNNER(tests_normDiff_L2_16s32f){
    RUN_TEST_CASE(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_calculation);
    RUN_TEST_CASE(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_check_answer);
    RUN_TEST_CASE(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_small_vecs);
    RUN_TEST_CASE(tests_normDiff_L2_16s32f, nmppsNormDiff_L2_16s32f_subnormal);
}

#endif


