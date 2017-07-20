#include "unity/unity_fixture.h"
#include "nmpps.h"

#define COUNT_ITERATION (100)

TEST_GROUP(tests_norm_L1_16s32s_Sfs);
TEST_SETUP(tests_norm_L1_16s32s_Sfs) {}
TEST_TEAR_DOWN(tests_norm_L1_16s32s_Sfs) {}


nmpps32s create_norm_16s32sfs_L1_vecs(nmpps16s bgn, nmpps16s step, int count, nmpps16s* vec, int sfs){
	int i;
	nmpps32s out = 0;
	for (i=0; i < count; i++){
		vec[i] = bgn;
		out += fabsf(bgn);
		bgn += step;
	}

	if (sfs>0) {
		out = out >> sfs;
	}
	else if (sfs<0){
		out = out << -sfs;
	}

	return out;
}

nmppsStatus test_norm_16s32sfs_L1_diap(nmpps16s bgn, nmpps16s step, int count){
	nmpps16s Vec[count];
	nmpps32s KD;
	nmpps32s res;
	nmppsStatus stat;
	int i;
	for (i= -16; i <= 16; i++){
		//Создаем эталонные значения
		KD = create_norm_16s32sfs_L1_vecs(bgn, step, count, Vec, i);
		//Производим рассчеты
		stat = nmppsNorm_L1_16s32s_Sfs(Vec, count, &res, i);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		if (res != KD) {
			TEST_ASSERT_EQUAL_FLOAT(res, KD);
			return -1;
		}
	}
	return nmppsStsNoErr;
}

TEST(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-1, 1, 65));
}

TEST(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-COUNT_ITERATION/2, 1, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(-32768, 11, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_L1_diap(32767, -11, COUNT_ITERATION));
}

//Проверка возвращаемых результатов
TEST(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_check_answer) {
	nmpps16s tmp1[1];
	nmpps32s tmp2[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_L1_16s32s_Sfs(0, 1, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_L1_16s32s_Sfs(tmp1, 1, 0, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_L1_16s32s_Sfs(tmp1, 0, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_L1_16s32s_Sfs(tmp1, -1, tmp2, 1));
}

TEST(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_subnormal) {
	//Учитываться должны только данные в младших разрядах
	nmpps16s vec[4] = {0x10001, 0x1FFFF,0x33330001,0x777FFFF};
	nmpps32s res;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsNorm_L1_16s32s_Sfs(vec, 4, &res, 0));
	TEST_ASSERT_EQUAL_FLOAT(res, 4.0);
}


TEST_GROUP_RUNNER(tests_norm_L1_16s32s_Sfs){
    RUN_TEST_CASE(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_small_vecs);
    RUN_TEST_CASE(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_check_answer);
    RUN_TEST_CASE(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_calculation);
    RUN_TEST_CASE(tests_norm_L1_16s32s_Sfs, nmppsNorm_L1_16s32s_Sfs_subnormal);
}
