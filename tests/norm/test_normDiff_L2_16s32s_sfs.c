#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"

#if NormDiffL2TestEnable
#define COUNT_ITERATION (100)

TEST_GROUP(tests_normDiff_L2_16s32s_Sfs);
TEST_SETUP(tests_normDiff_L2_16s32s_Sfs) {}
TEST_TEAR_DOWN(tests_normDiff_L2_16s32s_Sfs) {}

double right_sqrt(double x);
nmpps32s create_normDiff_L2_16s32sfs_vecs(nmpps16s bgn1, nmpps16s step1, nmpps16s* vec1,
										  nmpps16s bgn2, nmpps16s step2, nmpps16s* vec2,
										  int count, int sfs)
{
	int i;
	nmpps64f outf = 0;
	nmpps64f tmpf;
	dblint_t shift;
	shift.dbl = 1.0;
	for (i=0; i < count; i++){
		vec1[i] = bgn1;
		vec2[i] = bgn2;
		tmpf =  (nmpps64f)(bgn1 - bgn2);
		outf += tmpf*tmpf;
		bgn1 += step1;
		bgn2 += step2;
	}

	outf = right_sqrt(outf);

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

nmppsStatus test_normDiff_L2_16s32sfs_diap(nmpps16s bgn1, nmpps16s step1, nmpps16s bgn2, nmpps16s step2, int count){
	nmpps16s Vec1[count];
	nmpps16s Vec2[count];
	nmpps32s KD;
	nmpps32s res;
	nmppsStatus stat;
	int i;
	for (i= -16; i <= 16; i++){
		//Создаем эталонные значения
		KD = create_normDiff_L2_16s32sfs_vecs(bgn1, step1, Vec1, bgn2, step2, Vec2, count, i);
		//Производим рассчеты
		stat = nmppsNormDiff_L2_16s32s_Sfs(Vec1, Vec2, count, &res, i);
		//Проверяем результат
		if (stat!=nmppsStsNoErr) {
			return stat;
		}
		if (abs(res - KD) > 1) {
			TEST_ASSERT_EQUAL(res, KD);
			return -1;
		}
	}
	return nmppsStsNoErr;
}

TEST(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 33));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-1, 1, 10, 22, 65));
}

TEST(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-COUNT_ITERATION/2, 1, -11, -2, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(-32768, 11, -13, -2, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normDiff_L2_16s32sfs_diap(32767, -11, 13, 2, COUNT_ITERATION));
}

//Проверка возвращаемых результатов
TEST(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_check_answer) {
	nmpps16s tmp1[1];
	nmpps32s tmp2[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_16s32s_Sfs(0,    tmp1, 1, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_16s32s_Sfs(tmp1, 0,    1, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormDiff_L2_16s32s_Sfs(tmp1, tmp1, 1, 0,    1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L2_16s32s_Sfs(tmp1, tmp1, 0, tmp2, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormDiff_L2_16s32s_Sfs(tmp1, tmp1,-1, tmp2, 1));
}

TEST(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_subnormal) {
	//Учитываться должны только данные в младших разрядах
	nmpps16s vec1[4] = {0x10004, 0x1FFFC,0x33330004,0x777FFFC};
	nmpps16s vec2[4] = {0x30002, 0x8FFFe,0x77770002,0x222FFFe};
	nmpps32s res;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsNormDiff_L2_16s32s_Sfs(vec1, vec2, 4, &res, 0));
	TEST_ASSERT_EQUAL_FLOAT(res, 4.0);
}


TEST_GROUP_RUNNER(tests_normDiff_L2_16s32s_Sfs){
    RUN_TEST_CASE(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_calculation);
    RUN_TEST_CASE(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_small_vecs);
    RUN_TEST_CASE(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_check_answer);
    RUN_TEST_CASE(tests_normDiff_L2_16s32s_Sfs, nmppsNormDiff_L2_16s32s_Sfs_subnormal);
}
#endif

