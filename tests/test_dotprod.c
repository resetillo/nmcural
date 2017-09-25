#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"


TEST_GROUP(tests_dotprod);

TEST_SETUP(tests_dotprod){}
TEST_TEAR_DOWN(tests_dotprod){}


///nmppsDotProd_16s32s_Sfs

TEST(tests_dotprod, test_nmppsDotProd_16s32s_Sfs_null_ptr){
	nmpps16s a;
	nmpps32s b;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_16s32s_Sfs(NULL, &a, 1, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_16s32s_Sfs(&a, NULL, 1, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_16s32s_Sfs(&a, &a, 1, NULL, 1));
}

TEST(tests_dotprod, test_nmppsDotProd_16s32s_Sfs_err_size){
	nmpps16s a;
	nmpps32s b;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDotProd_16s32s_Sfs(&a, &a, 0, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDotProd_16s32s_Sfs(&a, &a, -1, &b, 1));
}

TEST(tests_dotprod, test_nmppsDotProd_16s32s_Sfs){

	nmpps16s src1[150]    __attribute__ ((aligned (2)));
	nmpps16s src2[150]    __attribute__ ((aligned (2)));
	nmpps32s result = 0;
	nmpps32s result_etalon = 29062500;

	init_vector_value_16s(src1, 30000, 31);
	init_vector_value_16s(src2, 32000, 31);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s_Sfs(src1, src2, 31, &result, 10));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 20000, 20);
	init_vector_value_16s(src2, 21000, 20);
	result_etalon = 262500000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s_Sfs(src1, src2, 20, &result, 5));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 30000, 128);
	init_vector_value_16s(src2, 10000, 128);
	result_etalon = 600000000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s_Sfs(src1, src2, 128, &result, 6));
	TEST_ASSERT_EQUAL(result_etalon, result);


	init_vector_value_16s(src1, 10000, 150);
	init_vector_value_16s(src2, 30000, 150);
	result_etalon = 1406250000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s_Sfs(src1, src2, 150, &result, 5));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 30000, 149);
	init_vector_value_16s(src2, 10000, 149);
	result_etalon = 349218750;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s_Sfs(src1, src2, 149, &result, 7));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 2, 1);
	init_vector_value_16s(src2, 4, 1);
	result_etalon = 8;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s_Sfs(src1, src2, 1, &result, 0));
	TEST_ASSERT_EQUAL(result_etalon, result);
}


///nmppsDotProd_16s32s32s_Sfs

TEST(tests_dotprod, test_nmppsDotProd_16s32s32s_Sfs_null_ptr){
	nmpps16s a;
	nmpps32s b;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_16s32s32s_Sfs(NULL, &b, 1, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_16s32s32s_Sfs(&a, NULL, 1, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_16s32s32s_Sfs(&a, &b, 1, NULL, 1));
}

TEST(tests_dotprod, test_nmppsDotProd_16s32s32s_Sfs_err_size){
	nmpps16s a;
	nmpps32s b;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDotProd_16s32s32s_Sfs(&a, &b, 0, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDotProd_16s32s32s_Sfs(&a, &b, -1, &b, 1));
}

TEST(tests_dotprod, test_nmppsDotProd_16s32s32s_Sfs){

	nmpps16s src1[150]    __attribute__ ((aligned (2)));
	nmpps32s src2[150]    __attribute__ ((aligned (2)));
	nmpps32s result = 0;
	nmpps32s result_etalon = 29062500;

	init_vector_value_16s(src1, 30000, 31);
	init_vector_value_32s(src2, 32000, 31);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s32s_Sfs(src1, src2, 31, &result, 10));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 20000, 20);
	init_vector_value_32s(src2, 21000, 20);
	result_etalon = 262500000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s32s_Sfs(src1, src2, 20, &result, 5));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 30000, 128);
	init_vector_value_32s(src2, 10000, 128);
	result_etalon = 600000000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s32s_Sfs(src1, src2, 128, &result, 6));
	TEST_ASSERT_EQUAL(result_etalon, result);


	init_vector_value_16s(src1, 10000, 150);
	init_vector_value_32s(src2, 30000, 150);
	result_etalon = 1406250000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s32s_Sfs(src1, src2, 150, &result, 5));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 30000, 149);
	init_vector_value_32s(src2, 10000, 149);
	result_etalon = 349218750;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s32s_Sfs(src1, src2, 149, &result, 7));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_16s(src1, 2, 1);
	init_vector_value_32s(src2, 4, 1);
	result_etalon = 8;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_16s32s32s_Sfs(src1, src2, 1, &result, 0));
	TEST_ASSERT_EQUAL(result_etalon, result);
}

///nmppsDotProd_32s_Sfs

TEST(tests_dotprod, test_nmppsDotProd_32s_Sfs_null_ptr){
	nmpps32s b;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_32s_Sfs(NULL, &b, 1, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_32s_Sfs(&b, NULL, 1, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsDotProd_32s_Sfs(&b, &b, 1, NULL, 1));
}

TEST(tests_dotprod, test_nmppsDotProd_32s_Sfs_err_size){
	nmpps32s b;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDotProd_32s_Sfs(&b, &b, 0, &b, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsDotProd_32s_Sfs(&b, &b, -1, &b, 1));
}

TEST(tests_dotprod, test_nmppsDotProd_32s_Sfs){

	nmpps32s src1[150]    __attribute__ ((aligned (2)));
	nmpps32s src2[150]    __attribute__ ((aligned (2)));
	nmpps32s result = 0;
	nmpps32s result_etalon = 29062500;

	init_vector_value_32s(src1, 30000, 31);
	init_vector_value_32s(src2, 32000, 31);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_32s_Sfs(src1, src2, 31, &result, 10));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_32s(src1, 20000, 20);
	init_vector_value_32s(src2, 21000, 20);
	result_etalon = 262500000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_32s_Sfs(src1, src2, 20, &result, 5));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_32s(src1, 30000, 128);
	init_vector_value_32s(src2, 10000, 128);
	result_etalon = 600000000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_32s_Sfs(src1, src2, 128, &result, 6));
	TEST_ASSERT_EQUAL(result_etalon, result);


	init_vector_value_32s(src1, 10000, 150);
	init_vector_value_32s(src2, 30000, 150);
	result_etalon = 1406250000;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_32s_Sfs(src1, src2, 150, &result, 5));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_32s(src1, 30000, 149);
	init_vector_value_32s(src2, 10000, 149);
	result_etalon = 349218750;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_32s_Sfs(src1, src2, 149, &result, 7));
	TEST_ASSERT_EQUAL(result_etalon, result);

	init_vector_value_32s(src1, 2, 1);
	init_vector_value_32s(src2, 4, 1);
	result_etalon = 8;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsDotProd_32s_Sfs(src1, src2, 1, &result, 0));
	TEST_ASSERT_EQUAL(result_etalon, result);
}



TEST_GROUP_RUNNER(tests_dotprod){
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_16s32s_Sfs_null_ptr);
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_16s32s_Sfs_err_size);
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_16s32s_Sfs);

	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_16s32s32s_Sfs_null_ptr);
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_16s32s32s_Sfs_err_size);
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_16s32s32s_Sfs);

	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_32s_Sfs_null_ptr);
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_32s_Sfs_err_size);
	RUN_TEST_CASE(tests_dotprod, test_nmppsDotProd_32s_Sfs);
}





















