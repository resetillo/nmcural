#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormL2TestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_norm_L2_16s32f);
TEST_SETUP(tests_norm_L2_16s32f) {}
TEST_TEAR_DOWN(tests_norm_L2_16s32f) {}

double right_sqrt(double x);

nmpps32f create_norm_16s32f_L2_vecs(nmpps16s bgn, nmpps16s step, int count, nmpps16s* vec){
	int i;
	nmpps32f out = 0;
	for (i=0; i < count; i++){
		vec[i] = bgn;
		out += (nmpps32f)bgn*(nmpps32f)bgn;
		bgn += step;
	}
	return right_sqrt(out);
}

nmppsStatus test_norm_16s32f_L2_diap(nmpps16s bgn, nmpps16s step, int count){
	nmpps16s Vec[count];
	nmpps32f KD;
	nmpps32f res;
	nmppsStatus stat;
	//Создаем эталонные значения
	KD = create_norm_16s32f_L2_vecs(bgn, step, count, Vec);
	//Производим рассчеты
	stat = nmppsNorm_L2_16s32f(Vec, count, &res);
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

TEST(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-1, 1, 65));
}

TEST(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-32768, 11, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(-COUNT_ITERATION/2, 1, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32f_L2_diap(32767, -11, COUNT_ITERATION));
}

//Проверка возвращаемых результатов
TEST(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_check_answer) {
	nmpps16s tmpi[1];
	nmpps32f tmpf[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_L2_16s32f(0, 1, tmpf));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_L2_16s32f(tmpi, 1, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_L2_16s32f(tmpi, 0, tmpf));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_L2_16s32f(tmpi, -1, tmpf));
}

TEST(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_subnormal) {
	//Учитываться должны только данные в младших разрядах
	unsigned int vec[4] = {0x10002, 0x1FFFE,0x33330002,0x777FFFE};
	nmpps32f res;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsNorm_L2_16s32f(vec, 4, &res));
	TEST_ASSERT_EQUAL_FLOAT(res, 4.0);
}


TEST_GROUP_RUNNER(tests_norm_L2_16s32f){
    RUN_TEST_CASE(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_calculation);
    RUN_TEST_CASE(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_check_answer);
    RUN_TEST_CASE(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_small_vecs);
    RUN_TEST_CASE(tests_norm_L2_16s32f, nmppsNorm_L2_16s32f_subnormal);
}
#endif
