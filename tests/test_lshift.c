#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"


TEST_GROUP(tests_lshift);

TEST_SETUP(tests_lshift){}
TEST_TEAR_DOWN(tests_lshift){}





// nmppsLShiftC_8u

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_8u_null_ptr){

	nmpps8u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_8u(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_8u(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_8u_err_len){

	nmpps8u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_8u(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_8u(vec, 2, vec, 0));
}


TEST(tests_lshift, test_nmppsLShiftC_8u){
	unsigned int i = 0;

	nmpps8u src[150]    __attribute__ ((aligned (2)));
	nmpps8u dst[150]    __attribute__ ((aligned (2)));
	nmpps8u etalon[150] __attribute__ ((aligned (2)));

	init_vector_value_8u(src, 1, 63);
	init_vector_value_8u(dst, 0, 63);
	init_vector_value_8u(etalon, 128, 63);

	// Нечетная длина меньше 64 слова

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u(src, 7, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова

	init_vector_value_8u(src, 1, 62);
	init_vector_value_8u(dst, 0, 62);
	init_vector_value_8u(etalon, 32, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u(src, 5, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_8u(src, 1, 128);
	init_vector_value_8u(dst, 0, 128);
	init_vector_value_8u(etalon, 64, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u(src, 6, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


    // Нечетная длина больше 64 слов
	init_vector_value_8u(src, 1, 69);
	init_vector_value_8u(dst, 0, 69);
	init_vector_value_8u(etalon, 16, 69);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u(src, 4, dst, 69));

	for(i= 0; i < 69; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

   // Четная длина больше 64 слов
	init_vector_value_8u(src, 1, 150);
	init_vector_value_8u(dst, 0, 150);
	init_vector_value_8u(etalon, 8, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u(src, 3, dst, 150));

	for(i= 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}

// nmppsLShiftC_16s

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_16s_null_ptr){

	nmpps16s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16s(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16s(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_16s_err_len){

	nmpps16s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16s(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16s(vec, 2, vec, 0));
}

TEST(tests_lshift, test_nmppsLShiftC_16s_less_64){
	unsigned int i = 0;

	nmpps16s src[150]    __attribute__ ((aligned (2)));
	nmpps16s dst[150]    __attribute__ ((aligned (2)));
	nmpps16s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16s(src, -1, 63);
	init_vector_value_16s(dst, 0, 63);
	init_vector_value_16s(etalon, -32768, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s(src, 15, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16s(src, 1, 62);
	init_vector_value_16s(dst, 0, 62);
	init_vector_value_16s(etalon, 16384, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s(src, 14, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16s(src, 1, 128);
	init_vector_value_16s(dst, 0, 128);
	init_vector_value_16s(etalon, 8192, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s(src, 13, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16s(src, 1, 149);
	init_vector_value_16s(dst, 0, 149);
	init_vector_value_16s(etalon, 4096, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s(src, 12, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16s(src, 1, 150);
	init_vector_value_16s(dst, 0, 150);
	init_vector_value_16s(etalon, 2048, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s(src, 11, dst, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}


TEST_GROUP_RUNNER(tests_lshift){
	RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_8u_null_ptr);
	RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_8u_err_len);
	RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_8u);
	RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s_less_64);

}



