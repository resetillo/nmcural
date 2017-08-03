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
	nmpps32f src[131]    __attribute__ ((aligned (2)));
	nmpps32f dst[131]    __attribute__ ((aligned (2)));
	nmpps32f etalon[131] __attribute__ ((aligned (2)));

    //Один элемент
	etalon[0] = 123.45678;
	src[0] = -123.45678;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 1));
	TEST_ASSERT_EQUAL_FLOAT(etalon[0], dst[0]);

	// Частичная загрузка векторного регистра
	init_vector_32f_abs(src, 63);
	init_vector_32f(etalon, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 63));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 63);

	// Полная загрузка векторного регистра
	init_vector_32f_abs(src, 128);
	init_vector_32f(etalon, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 128));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 128);

	// Полная загрузка векторного регистра + один элемент
	init_vector_32f_abs(src, 65);
	init_vector_32f(etalon, 65);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 65));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 65);

	// Полная загрузка векторного регистра + частичная загрузка + один элемент
	init_vector_32f_abs(src, 131);
	init_vector_32f(etalon, 131);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_32f(src, dst, 131));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(etalon, dst, 131);
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
	nmpps64f src[70] __attribute__ ((aligned (2)));
	nmpps64f dst[70] __attribute__ ((aligned (2)));
	nmpps64f etalon[70] __attribute__ ((aligned (2)));

	// Частичная загрузка векторного регистра
	init_vector_64f_abs(src, 20);
	init_vector_64f(etalon, 20);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_64f(src, dst, 20));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(etalon, dst, 20);

	// Полная загрузка векторного регистра
	init_vector_64f_abs(src, 64);
	init_vector_64f(etalon, 64);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_64f(src, dst, 64));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(etalon, dst, 64);

	// Полная загрузка векторного регистра + частичная загрузка
	init_vector_64f_abs(src, 70);
	init_vector_64f(etalon, 70);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsAbs_64f(src, dst, 70));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(etalon, dst, 70);
}

TEST_GROUP_RUNNER(tests_abs){
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_32f_null_ptr);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_32f_len);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_32f);

    RUN_TEST_CASE(tests_abs, test_nmppsAbs_64f_null_ptr);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_64f_len);
    RUN_TEST_CASE(tests_abs, test_nmppsAbs_64f);
}
