#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_sum);

TEST_SETUP(tests_sum){}
TEST_TEAR_DOWN(tests_sum){}

/// nmppsSum_16s_Sfs

TEST(tests_sum, test_nmppsSum_16s_Sfs_null_ptr){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSum_16s_Sfs(NULL, 1, &a, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSum_16s_Sfs(NULL, 1, &a, 1));
}

TEST(tests_sum, test_nmppsSum_16s_Sfs_err_size){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSum_16s_Sfs(&a, 0, &a, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSum_16s_Sfs(&a, -1, &a, 1));
}

TEST(tests_sum, test_nmppsSum_16s_Sfs){

	nmpps16s src[150]    __attribute__ ((aligned (2)));
	nmpps16s result = 0;
	nmpps16s result_etalon = 14532;

	init_vector_value_16s(src, 30001, 31);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_16s_Sfs(src, 31, &result, 6));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = 124;
	init_vector_value_16s(src, 2, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_16s_Sfs(src, 62, &result, 0));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = 2007;
	init_vector_value_16s(src, 32111, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_16s_Sfs(src, 128, &result, 11));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = 1176;
	init_vector_value_16s(src, 32111, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_16s_Sfs(src, 150, &result, 12));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = 16;
	init_vector_value_16s(src, 3614, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_16s_Sfs(src, 149, &result, 15));
	TEST_ASSERT_EQUAL(result_etalon, result);
}

/// nmppsSum_32s_Sfs

TEST(tests_sum, test_nmppsSum_32s_Sfs_null_ptr){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSum_32s_Sfs(NULL, 1, &a, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSum_32s_Sfs(NULL, 1, &a, 1));
}

TEST(tests_sum, test_nmppsSum_32s_Sfs_err_size){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSum_32s_Sfs(&a, 0, &a, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSum_32s_Sfs(&a, -1, &a, 1));
}

TEST(tests_sum, test_nmppsSum_32s_Sfs){

	nmpps32s src[150]    __attribute__ ((aligned (2)));
	nmpps32s result = 0;
	nmpps32s result_etalon = 3650;

	init_vector_value_32s(src, 123456789, 31);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_32s_Sfs(src, 31, &result, 20));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = 121;
	init_vector_value_32s(src, 2100000000, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_32s_Sfs(src, 62, &result, 30));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = -8;
	init_vector_value_32s(src, -2147483648, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_32s_Sfs(src, 128, &result, 35));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = -2;
	init_vector_value_32s(src, -2147483648, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_32s_Sfs(src, 150, &result, 37));
	TEST_ASSERT_EQUAL(result_etalon, result);

	result_etalon = 149000;
	init_vector_value_32s(src, 1000, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSum_32s_Sfs(src, 149, &result, 0));
	TEST_ASSERT_EQUAL(result_etalon, result);
}

TEST_GROUP_RUNNER(tests_sum){
	RUN_TEST_CASE(tests_sum, test_nmppsSum_16s_Sfs_null_ptr);
	RUN_TEST_CASE(tests_sum, test_nmppsSum_16s_Sfs_err_size);
	RUN_TEST_CASE(tests_sum, test_nmppsSum_16s_Sfs);

	RUN_TEST_CASE(tests_sum, test_nmppsSum_32s_Sfs_null_ptr);
    RUN_TEST_CASE(tests_sum, test_nmppsSum_32s_Sfs_err_size);
    RUN_TEST_CASE(tests_sum, test_nmppsSum_32s_Sfs);
}
















