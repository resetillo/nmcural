#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"


TEST_GROUP(tests_rshift);

TEST_SETUP(tests_rshift){}
TEST_TEAR_DOWN(tests_rshift){}

// nmppsRShiftC_8u

// Нулевые указатели
TEST(tests_rshift, test_nmppsRShiftC_8u_null_ptr){

	nmpps8u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_8u(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_8u(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_8u_err_len){

	nmpps8u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_8u(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_8u(vec, 2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_8u){
	unsigned int i = 0;

	nmpps8u src[150]    __attribute__ ((aligned (2)));
	nmpps8u dst[150]    __attribute__ ((aligned (2)));
	nmpps8u etalon[150] __attribute__ ((aligned (2)));

	init_vector_value_8u(src, 255, 63);
	init_vector_value_8u(dst, 0, 63);
	init_vector_value_8u(etalon, 127, 63);

	// Нечетная длина меньше 64 слова

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u(src, 1, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова

	init_vector_value_8u(src, 255, 62);
	init_vector_value_8u(dst, 0, 62);
	init_vector_value_8u(etalon, 63, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u(src, 2, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_8u(src, 255, 128);
	init_vector_value_8u(dst, 0, 128);
	init_vector_value_8u(etalon, 31, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u(src, 3, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


    // Нечетная длина больше 64 слов
	init_vector_value_8u(src, 255, 69);
	init_vector_value_8u(dst, 0, 69);
	init_vector_value_8u(etalon, 15, 69);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u(src, 4, dst, 69));

	for(i= 0; i < 69; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

   // Четная длина больше 64 слов
	init_vector_value_8u(src, 255, 150);
	init_vector_value_8u(dst, 0, 150);
	init_vector_value_8u(etalon, 7, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u(src, 5, dst, 150));

	for(i= 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}

// nmppsRShiftC_16s

// Нулевые указатели
TEST(tests_rshift, test_nmppsRShiftC_16s_null_ptr){

	nmpps16s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_16s(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_16s(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_16s_err_len){

	nmpps16s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16s(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16s(vec, 2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_16s){
	unsigned int i = 0;

	nmpps16s src[150]    __attribute__ ((aligned (2)));
	nmpps16s dst[150]    __attribute__ ((aligned (2)));
	nmpps16s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16s(src, -32767, 63);
	init_vector_value_16s(dst, 0, 63);
	init_vector_value_16s(etalon, 0x00FFFF80, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s(src, 8, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16s(src, 32767, 62);
	init_vector_value_16s(dst, 0, 62);
	init_vector_value_16s(etalon, 63, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s(src, 9, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16s(src, 32767, 128);
	init_vector_value_16s(dst, 0, 128);
	init_vector_value_16s(etalon, 31, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s(src, 10, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16s(src, 32767, 149);
	init_vector_value_16s(dst, 0, 149);
	init_vector_value_16s(etalon, 15, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s(src, 11, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16s(src, 32767, 150);
	init_vector_value_16s(dst, 0, 150);
	init_vector_value_16s(etalon, 7, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s(src, 12, dst, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}


// nmppsRShiftC_16u

// Нулевые указатели
TEST(tests_rshift, test_nmppsRShiftC_16u_null_ptr){

	nmpps16u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_16u(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_16u(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_16u_err_len){

	nmpps16u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16u(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16u(vec, 2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_16u){
	unsigned int i = 0;

	nmpps16u src[150]    __attribute__ ((aligned (2)));
	nmpps16u dst[150]    __attribute__ ((aligned (2)));
	nmpps16u etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16u(src, 32767, 63);
	init_vector_value_16u(dst, 0, 63);
	init_vector_value_16u(etalon, 3, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u(src, 13, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16u(src, 32767, 62);
	init_vector_value_16u(dst, 0, 62);
	init_vector_value_16u(etalon, 1, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u(src, 14, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16u(src, 32767, 128);
	init_vector_value_16u(dst, 0, 128);
	init_vector_value_16u(etalon, 31, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u(src, 10, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16u(src, 32767, 149);
	init_vector_value_16u(dst, 0, 149);
	init_vector_value_16u(etalon, 15, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u(src, 11, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16u(src, 32767, 150);
	init_vector_value_16u(dst, 0, 150);
	init_vector_value_16u(etalon, 255, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u(src, 7, dst, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}


/// nmppsRShiftC_32s

TEST(tests_rshift, test_nmppsRShiftC_32s_null_ptr){

	nmpps32s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_32s(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_32s(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_32s_err_len){

	nmpps32s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_32s(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_32s(vec, 2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_32s){
	unsigned int i = 0;

	nmpps32s src[150]    __attribute__ ((aligned (2)));
	nmpps32s dst[150]    __attribute__ ((aligned (2)));
	nmpps32s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_32s(src, 0xFFFFFFFF, 63);
	init_vector_value_32s(dst, 0, 63);
	init_vector_value_32s(etalon, 1, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s(src, 31, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_32s(src, 0xFFFFFFFF, 62);
	init_vector_value_32s(dst, 0, 62);
	init_vector_value_32s(etalon, 3, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s(src, 30, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_32s(src, 0xFFFFFFFF, 128);
	init_vector_value_32s(dst, 0, 128);
	init_vector_value_32s(etalon, 7, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s(src, 29, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_32s(src, 0xFFFFFFFF, 149);
	init_vector_value_32s(dst, 0, 149);
	init_vector_value_32s(etalon, 15, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s(src, 28, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_32s(src, 0xFFFFFFFF, 150);
	init_vector_value_32s(dst, 0, 150);
	init_vector_value_32s(etalon, 31, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s(src, 27, dst, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}




// nmppsRShiftC_8u_I

// Нулевые указатели
TEST(tests_rshift, test_nmppsRShiftC_8u_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_8u_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_8u_i_err_len){

	nmpps8u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_8u_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_8u_I(2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_8u_i){
	unsigned int i = 0;

	nmpps8u src[150]    __attribute__ ((aligned (2)));
	nmpps8u etalon[150] __attribute__ ((aligned (2)));

	init_vector_value_8u(src, 255, 63);
	init_vector_value_8u(etalon, 3, 63);

	// Нечетная длина меньше 64 слова

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u_I(6, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова

	init_vector_value_8u(src, 255, 62);
	init_vector_value_8u(etalon, 1, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u_I(7, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_8u(src, 255, 128);
	init_vector_value_8u(etalon, 127, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u_I(1, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


    // Нечетная длина больше 64 слов
	init_vector_value_8u(src, 255, 69);
	init_vector_value_8u(etalon, 31, 69);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u_I(3, src, 69));

	for(i= 0; i < 69; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

   // Четная длина больше 64 слов
	init_vector_value_8u(src, 255, 150);
	init_vector_value_8u(etalon, 15, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_8u_I(4, src, 150));

	for(i= 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}

// nmppsRShiftC_16s_I

// Нулевые указатели
TEST(tests_rshift, test_nmppsRShiftC_16s_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_16s_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_16s_i_err_len){

	nmpps16s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16s_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16s_I(2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_16s_i){
	unsigned int i = 0;

	nmpps16s src[150]    __attribute__ ((aligned (2)));
	nmpps16s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16s(src, -2, 63);
	init_vector_value_16s(etalon, 0x1FFFF, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s_I(15, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16s(src, -12341, 62);
	init_vector_value_16s(etalon, 0x7FFFE7E5, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s_I(1, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16s(src, -124, 128);
	init_vector_value_16s(etalon, 0x3FFFFFE1, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s_I(2, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16s(src, -1, 149);
	init_vector_value_16s(etalon, 0x1FFFFFFF, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s_I(3, src, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16s(src, -4821, 150);
	init_vector_value_16s(etalon, 0x0FFFFED2, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16s_I(4, src, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}


// nmppsRShiftC_16u

// Нулевые указатели
TEST(tests_rshift, test_nmppsRShiftC_16u_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_16u_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_16u_i_err_len){

	nmpps16u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16u_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_16u_I(2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_16u_i){
	unsigned int i = 0;

	nmpps16u src[150]    __attribute__ ((aligned (2)));
	nmpps16u etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16u(src, 65535, 63);
	init_vector_value_16u(etalon, 8191, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u_I(3, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16u(src, 65535, 62);
	init_vector_value_16u(etalon, 511, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u_I(7, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16u(src, 65535, 128);
	init_vector_value_16u(etalon, 63, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u_I(10, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16u(src, 65535, 149);
	init_vector_value_16u(etalon, 32767, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u_I(1, src, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16u(src, 65535, 150);
	init_vector_value_16u(etalon, 15, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_16u_I(12, src, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}


// nmppsRShiftC_32s

TEST(tests_rshift, test_nmppsRShiftC_32s_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRShiftC_32s_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_rshift, test_nmppsRShiftC_32s_i_err_len){

	nmpps32s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_32s_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRShiftC_32s_I(2, vec, 0));
}

TEST(tests_rshift, test_nmppsRShiftC_32s_i){
	unsigned int i = 0;

	nmpps32s src[150]    __attribute__ ((aligned (2)));
	nmpps32s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_32s(src, 0xFFFFFFFF, 63);
	init_vector_value_32s(etalon, 63, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s_I(26, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_32s(src, 0xFFFFFFFF, 62);
	init_vector_value_32s(etalon, 127, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s_I(127, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_32s(src, 0xFFFFFFFF, 128);
	init_vector_value_32s(etalon, 255, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s_I(26, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_32s(src, 0xFFFFFFFF, 149);
	init_vector_value_32s(etalon, 511, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s_I(25, src, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_32s(src, 0xFFFFFFFF, 150);
	init_vector_value_32s(etalon, 1023, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRShiftC_32s_I(24, src, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}
TEST_GROUP_RUNNER(tests_rshift){
	RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_8u_null_ptr);
	RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_8u_err_len);
	RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_8u);
	RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16s_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16s_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16s);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16u_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16u_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16u);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_32s_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_32s_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_32s);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_8u_i_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_8u_i_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_8u_i);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16s_i_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16s_i_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16s_i);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16u_i_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16u_i_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_16u_i);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_32s_null_ptr);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_32s_err_len);
    RUN_TEST_CASE(tests_rshift, test_nmppsRShiftC_32s);

}
