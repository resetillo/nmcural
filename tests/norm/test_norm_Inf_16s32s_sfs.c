#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormInfTestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_norm_Inf_16s32s_Sfs);
TEST_SETUP(tests_norm_Inf_16s32s_Sfs) {}
TEST_TEAR_DOWN(tests_norm_Inf_16s32s_Sfs) {}


nmpps32s create_norm_16s32sfs_Inf_vecs(nmpps16s bgn, nmpps16s step, int count, nmpps16s* vec, int sfs){
	int i;
	nmpps64f tmpf, outf = 0;
	dblint_t shift;
	shift.dbl = 1.0;
	for (i=0; i < count; i++){
		vec[i] = bgn;
		if (i&1) {
			vec[i] = -vec[i];
		}
		tmpf = fabs((nmpps64f)vec[i]);
		if (tmpf > outf) {
			outf = tmpf;
		}
		bgn += step;
	}

	i = sfs<<20;
	shift.i32[1] -= i;
	shift.ui32[1] &= 0x7FFFFFFF;

	outf *= shift.dbl;

	if (outf > 2147483647) {
		outf = 2147483647;
	} else if (outf < -2147483648){
		outf = -2147483648;
	}

	return (nmpps32s)outf;
}

nmppsStatus test_norm_16s32sfs_Inf_diap(nmpps16s bgn, nmpps16s step, int count){
	nmpps16s Vec[count];
	nmpps32s KD;
	nmpps32s res;
	nmppsStatus stat;
	int i;
	for (i= 1; i <= 16; i++){
		//Создаем эталонные значения
		KD = create_norm_16s32sfs_Inf_vecs(bgn, step, count, Vec, i);
		//Производим рассчеты
		stat = nmppsNorm_Inf_16s32s_Sfs(Vec, count, &res, i);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		if (abs(res - KD) > 1) {
			TEST_ASSERT_EQUAL_FLOAT(res, KD);
			return -1;
		}
	}
	return nmppsStsNoErr;
}

TEST(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-1, 1, 65));
}

TEST(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-COUNT_ITERATION/2, 1, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(-32768, 11, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_norm_16s32sfs_Inf_diap(32767, -11, COUNT_ITERATION));
}

//Проверка возвращаемых результатов
TEST(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_check_answer) {
	nmpps16s tmp1[1];
	nmpps32s tmp2[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_Inf_16s32s_Sfs(0, 1, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNorm_Inf_16s32s_Sfs(tmp1, 1, 0, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_Inf_16s32s_Sfs(tmp1, 0, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNorm_Inf_16s32s_Sfs(tmp1, -1, tmp2, 1));
}

TEST(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_subnormal) {
	//Учитываться должны только данные в младших разрядах
	nmpps16s vec[4] = {0x10005, 0x1FFFF,0x33330001,0x777FFFF};
	nmpps32s res;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsNorm_Inf_16s32s_Sfs(vec, 4, &res, 0));
	TEST_ASSERT_EQUAL_FLOAT(res, 5.0);
}


TEST_GROUP_RUNNER(tests_norm_Inf_16s32s_Sfs){
    RUN_TEST_CASE(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_small_vecs);
    RUN_TEST_CASE(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_check_answer);
    RUN_TEST_CASE(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_calculation);
    RUN_TEST_CASE(tests_norm_Inf_16s32s_Sfs, nmppsNorm_Inf_16s32s_Sfs_subnormal);
}
#endif
