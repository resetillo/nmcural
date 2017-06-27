#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_flip);

TEST_SETUP(tests_flip){}
TEST_TEAR_DOWN(tests_flip){}



//nmppsFlip_32f

// Нулевые указатели
TEST(tests_flip, test_nmppsFlip_32f_null_ptr){

	nmpps32f vec;

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsFlip_32f(NULL, &vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsFlip_32f(&vec, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_flip, test_nmppsFlip_32f_len){
    nmpps32f vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsFlip_32f(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsFlip_32f(vector, vector, -1));
}

// Нечетная длина меньше 64
TEST(tests_flip, test_nmppsFlip_32f_less_64_non_parity){
	nmpps32f src[63]  __attribute__ ((aligned (2)));
	nmpps32f dst[63]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_32f(src, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_32f(src, dst, 63));

	for(i = 0; i < 63; i++){
		TEST_ASSERT_EQUAL_FLOAT(src[i], dst[62 - i]);
	}
}

// Четная длина меньше 64
TEST(tests_flip, test_nmppsFlip_32f_less_64_parity){
	nmpps32f src[62]  __attribute__ ((aligned (2)));
	nmpps32f dst[62]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_32f(src, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_32f(src, dst, 62));

	for(i = 0; i < 62; i++){
		TEST_ASSERT_EQUAL_FLOAT(src[i], dst[61 - i]);
	}
}

// Нечетная длина больше 64
TEST(tests_flip, test_nmppsFlip_32f_over_64_non_parity_1){
	nmpps32f src[449]  __attribute__ ((aligned (2)));
	nmpps32f dst[449]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_32f(src, 449);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_32f(src, dst, 449));

	for(i = 0; i < 449; i++){
		TEST_ASSERT_EQUAL_FLOAT(src[i], dst[448 - i]);
	}
}

TEST(tests_flip, test_nmppsFlip_32f_over_64_non_parity_2){

	int i = 0;

	nmpps32f src[127]  __attribute__ ((aligned (2)));
	nmpps32f dst[127]  __attribute__ ((aligned (2)));

	init_vector_32f(src, 127);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_32f(src, dst, 127));

	for(i = 0; i < 127; i++){
		TEST_ASSERT_EQUAL_FLOAT(src[i], dst[126 - i]);
	}
}

// Четная длина больше 64

TEST(tests_flip, test_nmppsFlip_32f_over_64_parity_1){

	int i = 0;

	nmpps32f src[192]  __attribute__ ((aligned (2)));
	nmpps32f dst[192]  __attribute__ ((aligned (2)));

	init_vector_32f(src, 192);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_32f(src, dst, 192));

	for(i = 0; i < 192; i++){
		TEST_ASSERT_EQUAL_FLOAT(src[i], dst[191 - i]);
	}
}

TEST(tests_flip, test_nmppsFlip_32f_over_64_parity_2){

	int i = 0;

	nmpps32f src[190]  __attribute__ ((aligned (2)));
	nmpps32f dst[190]  __attribute__ ((aligned (2)));

	init_vector_32f(src, 190);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_32f(src, dst, 190));

	for(i = 0; i < 190; i++){
		TEST_ASSERT_EQUAL_FLOAT(src[i], dst[189 - i]);
	}
}


//nmppsFlip_64f

// Нулевые указатели
TEST(tests_flip, test_nmppsFlip_64f_null_ptr){

	nmpps64f vec;

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsFlip_64f(NULL, &vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsFlip_64f(&vec, NULL, 1));
}

// Некорректное значение длины вектора
TEST(tests_flip, test_nmppsFlip_64f_len){
    nmpps64f vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsFlip_64f(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsFlip_64f(vector, vector, -1));
}

// Длина меньше 32
TEST(tests_flip, test_nmppsFlip_64f_less_32){
	nmpps64f src[31]  __attribute__ ((aligned (2)));
	nmpps64f dst[31]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_64f(src, 31);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_64f(src, dst, 31));

	for(i = 0; i < 31; i++){
		TEST_ASSERT_EQUAL_DOUBLE(src[i], dst[30 - i]);
	}
}

// Длина кратна 64
TEST(tests_flip, test_nmppsFlip_64f_x64){
	nmpps64f src[192]  __attribute__ ((aligned (2)));
	nmpps64f dst[192]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_64f(src, 192);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_64f(src, dst, 192));

	for(i = 0; i < 192; i++){
		TEST_ASSERT_EQUAL_DOUBLE(src[i], dst[191 - i]);
	}
}

// Длина кратна 64 + некратный остаток
TEST(tests_flip, test_nmppsFlip_64f_over64_1){
	nmpps64f src[193]  __attribute__ ((aligned (2)));
	nmpps64f dst[193]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_64f(src, 193);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_64f(src, dst, 193));

	for(i = 0; i < 193; i++){
		TEST_ASSERT_EQUAL_DOUBLE(src[i], dst[192 - i]);
	}
}

TEST(tests_flip, test_nmppsFlip_64f_over64_2){
	nmpps64f src[191]  __attribute__ ((aligned (2)));
	nmpps64f dst[191]  __attribute__ ((aligned (2)));
	int i = 0;

	init_vector_64f(src, 191);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsFlip_64f(src, dst, 191));

	for(i = 0; i < 191; i++){
		TEST_ASSERT_EQUAL_DOUBLE(src[i], dst[190 - i]);
	}
}


TEST_GROUP_RUNNER(tests_flip){
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_null_ptr);
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_len);
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_less_64_non_parity);
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_less_64_parity);
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_over_64_non_parity_1);
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_over_64_non_parity_2);
	RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_over_64_parity_1);
    RUN_TEST_CASE(tests_flip, test_nmppsFlip_32f_over_64_parity_2);

    RUN_TEST_CASE(tests_flip, test_nmppsFlip_64f_null_ptr);
    RUN_TEST_CASE(tests_flip, test_nmppsFlip_64f_len);
    RUN_TEST_CASE(tests_flip, test_nmppsFlip_64f_less_32);
    RUN_TEST_CASE(tests_flip, test_nmppsFlip_64f_x64);
    RUN_TEST_CASE(tests_flip, test_nmppsFlip_64f_over64_1);
    RUN_TEST_CASE(tests_flip, test_nmppsFlip_64f_over64_2);

}
