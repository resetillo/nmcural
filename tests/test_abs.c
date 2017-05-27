#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

//const nmpps32f right_limit_deviation_32f = 10e-05;
//const nmpps32f left_limit_deviation_32f = -10e-05;
//
//const nmpps64f right_limit_deviation_64f = 10e-14;
//const nmpps64f left_limit_deviation_64f = -10e-14;

void init_vector_32f_abs(nmpps32f* vector, unsigned int size){
  int i = 0;

  for(i = 0; i < size; i++){
    if( (i % 2) ) vector[i] = (nmpps32f)(i / 3.0);
    else          vector[i] = (nmpps32f)(-i / 3.0);
  }
}

void init_vector_64f_abs(nmpps64f* vector, unsigned int size){
  int i = 0;

  for(i = 0; i < size; i++){
    if( (i % 2) ) vector[i] = (nmpps64f)(i / 3.0);
    else          vector[i] = (nmpps64f)(-i / 3.0);
  }
}

TEST_GROUP(tests_abs);

TEST_SETUP(tests_abs){}
TEST_TEAR_DOWN(tests_abs){}

// nmppsAbs_32f

TEST(tests_abs, test_nmppsAbs_32f_null_ptr){
	nmpps32f vector[10];

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsAbs_32f(NULL, vector, 5));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsAbs_32f(vector, NULL, 5));
}

TEST(tests_abs, test_nmppsAbs_32f_len){
	nmpps32f vector[10];

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsAbs_32f(vector, vector, -1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsAbs_32f(vector, vector, 0));
}


TEST(tests_abs, test_nmppsAbs_32f){
	nmpps32f* src = get_ptr_src_vector_32f();
	nmpps32f* dst = get_ptr_dst_vector_32f();
	nmpps32f* etalon = get_ptr_etalon_vector_32f();

    //Один элемент
	etalon[0] = 123.45678;
	src[0] = -123.45678;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 1));
	TEST_ASSERT_EQUAL_FLOAT(etalon[0], dst[0]);

	// Частичная загрузка векторного регистра
	init_vector_32f_abs(src, 4100);
	init_vector_32f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 63));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 63);

	// Полная загрузка векторного регистра
	init_vector_32f_abs(src, 4100);
	init_vector_32f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 512));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 512);

	// Полная загрузка векторного регистра + один элемент
	init_vector_32f_abs(src, 4100);
	init_vector_32f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 513));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 513);

	// Полная загрузка векторного регистра + частичная загрузка + один элемент
	init_vector_32f_abs(src, 4100);
	init_vector_32f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 2753));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 2753);
}


// nmppsAbs_64f

TEST(tests_abs, test_nmppsAbs_64f_null_ptr){
	nmpps64f vector[10];

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsAbs_64f(NULL, vector, 5));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsAbs_64f(vector, NULL, 5));
}

TEST(tests_abs, test_nmppsAbs_64f_len){
	nmpps64f vector[10];

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsAbs_64f(vector, vector, -1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsAbs_64f(vector, vector, 0));
}


TEST(tests_abs, test_nmppsAbs_64f){
	nmpps64f* src = get_ptr_src_vector_64f();
	nmpps64f* dst = get_ptr_dst_vector_64f();
	nmpps64f* etalon = get_ptr_etalon_vector_64f();

	// Частичная загрузка векторного регистра
	init_vector_64f_abs(src, 4100);
	init_vector_64f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_64f(src, dst, 63));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(etalon, dst, 63);

	// Полная загрузка векторного регистра
	init_vector_64f_abs(src, 4100);
	init_vector_64f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_64f(src, dst, 512));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(etalon, dst, 512);

	// Полная загрузка векторного регистра + частичная загрузка
	init_vector_64f_abs(src, 4100);
	init_vector_64f(etalon, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_64f(src, dst, 2753));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(etalon, dst, 2753);
}

TEST_GROUP_RUNNER(tests_abs){
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_32f_null_ptr);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_32f_len);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_32f);

    RUN_TEST_CASE(tests_abs, test_nmppsAbs_64f_null_ptr);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_64f_len);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_64f);}
