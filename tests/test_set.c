#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"


TEST_GROUP(tests_set);

TEST_SETUP(tests_set){}
TEST_TEAR_DOWN(tests_set){}

//nmppsSet_16sc

TEST(tests_set, test_nmppsSet_16sc_null_ptr){
	nmpps16sc val;

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSet_16sc(val, NULL, 1));
}

TEST(tests_set, test_nmppsSet_16sc_len){
    nmpps16sc vector[10];
    nmpps16sc val;

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSet_16sc(val, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSet_16sc(val, vector, -1));
}

TEST(tests_set, test_nmppsSet_16sc){
	nmpps16sc dst[70] __attribute__ ((aligned (2)));
	nmpps16sc val;
    int i = 0;

	val.im = -255;
	val.re = 55;

	// Частичная загрузка векторного регистра
	init_vector_zero_16sc(dst, 70);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_16sc(val, dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

	// Полная загрузка вектора
	val.im = 15;
	val.re = -789;

	init_vector_zero_16sc(dst, 70);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_16sc(val, dst, 64));

	for(i = 0; i < 64; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

	// Полная загрузка вектора + остаток
	val.im = 1223;
	val.re = 13789;

	init_vector_zero_16sc(dst, 70);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_16sc(val, dst, 70));

	for(i = 0; i < 70; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

}

//nmppsSet_32sc

TEST(tests_set, test_nmppsSet_32sc_null_ptr){
	nmpps32sc val;

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSet_32sc(val, NULL, 1));
}

TEST(tests_set, test_nmppsSet_32sc_len){
    nmpps32sc vector[10];
    nmpps32sc val;

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSet_32sc(val, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSet_32sc(val, vector, -1));
}

TEST(tests_set, test_nmppsSet_32sc){
	nmpps32sc dst[70] __attribute__ ((aligned (2)));;
	nmpps32sc val;
    int i = 0;

	val.im = -21255;
	val.re = 511115;

	// Частичная загрузка векторного регистра
	init_vector_zero_32sc(dst, 70);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_32sc(val, dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

	// Полная загрузка вектора
	val.im = -15321;
	val.re = 778589;

	init_vector_zero_32sc(dst, 70);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_32sc(val, dst, 64));

	for(i = 0; i < 64; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

	// Полная загрузка вектора + остаток
	val.im = 111223;
	val.re = 131789;

	init_vector_zero_32sc(dst, 70);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_32sc(val, dst, 70));

	for(i = 0; i < 70; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}
}

//nmppsSet_64sc

TEST(tests_set, test_nmppsSet_64sc_null_ptr){
	nmpps64sc val;

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSet_64sc(val, NULL, 1));
}

TEST(tests_set, test_nmppsSet_64sc_len){
    nmpps64sc vector[10];
    nmpps64sc val;

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSet_64sc(val, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSet_64sc(val, vector, -1));
}

TEST(tests_set, test_nmppsSet_64sc){
	nmpps64sc dst[40] __attribute__ ((aligned (2)));;
	nmpps64sc val;
    int i = 0;

	val.im = -21000255;
	val.re = -51001115;

	// Частичная загрузка векторного регистра
	init_vector_zero_64sc(dst, 40);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_64sc(val, dst, 12));

	for(i = 0; i < 12; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

	// Полная загрузка вектора
	val.im = -15112641;
	val.re = -1778589;

	init_vector_zero_64sc(dst, 40);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_64sc(val, dst, 32));

	for(i = 0; i < 32; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

	// Полная загрузка вектора + остаток
	val.im = 234011223;
	val.re = 131102789;

	init_vector_zero_64sc(dst, 40);
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSet_64sc(val, dst, 40));

	for(i = 0; i < 40; i++){
		TEST_ASSERT_EQUAL(val.im, dst[i].im);
		TEST_ASSERT_EQUAL(val.re, dst[i].re);
	}

}


TEST_GROUP_RUNNER(tests_set){
    RUN_TEST_CASE(tests_set, test_nmppsSet_16sc_null_ptr);
    RUN_TEST_CASE(tests_set, test_nmppsSet_16sc_len);
    RUN_TEST_CASE(tests_set, test_nmppsSet_16sc);

    RUN_TEST_CASE(tests_set, test_nmppsSet_32sc_null_ptr);
    RUN_TEST_CASE(tests_set, test_nmppsSet_32sc_len);
    RUN_TEST_CASE(tests_set, test_nmppsSet_32sc);

    RUN_TEST_CASE(tests_set, test_nmppsSet_64sc_null_ptr);
    RUN_TEST_CASE(tests_set, test_nmppsSet_64sc_len);
    RUN_TEST_CASE(tests_set, test_nmppsSet_64sc);
}
