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

TEST(tests_lshift, test_nmppsLShiftC_16s){
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

// nmppsLShiftC_16u

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_16u_null_ptr){

	nmpps16u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16u(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16u(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_16u_err_len){

	nmpps16u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16u(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16u(vec, 2, vec, 0));
}

TEST(tests_lshift, test_nmppsLShiftC_16u){
	unsigned int i = 0;

	nmpps16u src[150]    __attribute__ ((aligned (2)));
	nmpps16u dst[150]    __attribute__ ((aligned (2)));
	nmpps16u etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16u(src, 3, 63);
	init_vector_value_16u(dst, 0, 63);
	init_vector_value_16u(etalon, 3072, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 10, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16u(src, 5, 62);
	init_vector_value_16u(dst, 0, 62);
	init_vector_value_16u(etalon, 2560, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 9, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16u(src, 100, 128);
	init_vector_value_16u(dst, 0, 128);
	init_vector_value_16u(etalon, 25600, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 8, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16u(src, 78, 149);
	init_vector_value_16u(dst, 0, 149);
	init_vector_value_16u(etalon, 9984, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 7, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16u(src, 36, 150);
	init_vector_value_16u(dst, 0, 150);
	init_vector_value_16u(etalon, 2304, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 6, dst, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}

// nmppsLShiftC_32s

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_32s_null_ptr){

	nmpps32s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_32s(NULL, 2, vec, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_32s(vec, 2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_32s_err_len){

	nmpps32s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_32s(vec, 2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_32s(vec, 2, vec, 0));
}

TEST(tests_lshift, test_nmppsLShiftC_32s){
	unsigned int i = 0;

	nmpps32s src[150]    __attribute__ ((aligned (2)));
	nmpps32s dst[150]    __attribute__ ((aligned (2)));
	nmpps32s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_32s(src, -1, 63);
	init_vector_value_32s(dst, 0, 63);
	init_vector_value_32s(etalon, 0x80000000, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 31, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_32s(src, 2, 62);
	init_vector_value_32s(dst, 0, 62);
	init_vector_value_32s(etalon, 0x80000000, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 30, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_32s(src, 3, 128);
	init_vector_value_32s(dst, 0, 128);
	init_vector_value_32s(etalon, 0x60000000, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 29, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_32s(src, 4, 149);
	init_vector_value_32s(dst, 0, 149);
	init_vector_value_32s(etalon, 0x40000000, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 28, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_32s(src, 15, 150);
	init_vector_value_32s(dst, 0, 150);
	init_vector_value_32s(etalon, 0x78000000, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 27, dst, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}
}

// nmppsLShiftC_8u_I

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_8u_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_8u_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_8u_i_err_len){

	nmpps8u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_8u_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_8u_I(2, vec, 0));
}


TEST(tests_lshift, test_nmppsLShiftC_8u_i){
	unsigned int i = 0;

	nmpps8u src[150]    __attribute__ ((aligned (2)));
	nmpps8u etalon[150] __attribute__ ((aligned (2)));

	init_vector_value_8u(src, 1, 63);
	init_vector_value_8u(etalon, 4, 63);

	// Нечетная длина меньше 64 слова

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u_I(2, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова

	init_vector_value_8u(src, 1, 62);
	init_vector_value_8u(etalon, 2, 62);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u_I(1, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_8u(src, 1, 128);
	init_vector_value_8u(etalon, 128, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u_I(7, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


    // Нечетная длина больше 64 слов
	init_vector_value_8u(src, 1, 69);
	init_vector_value_8u(etalon, 64, 69);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u_I(6, src, 69));

	for(i= 0; i < 69; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

   // Четная длина больше 64 слов
	init_vector_value_8u(src, 1, 150);
	init_vector_value_8u(etalon, 32, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_8u_I(5, src, 150));

	for(i= 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}

// nmppsLShiftC_16s_i

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_16s_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16s_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_16s_i_err_len){

	nmpps16s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16s_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16s_I(2, vec, 0));
}

TEST(tests_lshift, test_nmppsLShiftC_16s_i){
	unsigned int i = 0;

	nmpps16s src[150]    __attribute__ ((aligned (2)));
	nmpps16s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16s(src, -1, 63);
	init_vector_value_16s(etalon, -32768, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s_I(15, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16s(src, 1, 62);
	init_vector_value_16s(etalon, 16384, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s_I(14, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16s(src, 1, 128);
	init_vector_value_16s(etalon, 8, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s_I(3, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16s(src, 1, 149);
	init_vector_value_16s(etalon, 4, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s_I(2, src, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16s(src, 1, 150);
	init_vector_value_16s(etalon, 2, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16s_I(1, src, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}

// nmppsLShiftC_16u_i

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_16u_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16u_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_16u_i_err_len){

	nmpps16u vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16u_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16u_I(2, vec, 0));
}

TEST(tests_lshift, test_nmppsLShiftC_16u_i){
	unsigned int i = 0;

	nmpps16u src[150]    __attribute__ ((aligned (2)));
	nmpps16u etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_16u(src, 3, 63);
	init_vector_value_16u(etalon, 3072, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u_I(10, src, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_16u(src, 5, 62);
	init_vector_value_16u(etalon, 2560, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u_I(9, src, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_16u(src, 100, 128);
	init_vector_value_16u(etalon, 25600, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u_I(8, src, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_16u(src, 78, 149);
	init_vector_value_16u(etalon, 9984, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u_I(7, src, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_16u(src, 36, 150);
	init_vector_value_16u(etalon, 2304, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u_I(6, src, 150));

	for(i = 0; i < 150; i++){
		TEST_ASSERT_EQUAL(src[i], etalon[i]);
	}
}


// nmppsLShiftC_32s_I

// Нулевые указатели
TEST(tests_lshift, test_nmppsLShiftC_32s_i_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_32s_I(2, NULL, 1));
}

// Некорректное знаечение длины вектора
TEST(tests_lshift, test_nmppsLShiftC_32s_i_err_len){

	nmpps32s vec[2];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_32s_I(2, vec, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_32s_I(2, vec, 0));
}

TEST(tests_lshift, test_nmppsLShiftC_32s_i){
	unsigned int i = 0;

	nmpps32s src[150]    __attribute__ ((aligned (2)));
	nmpps32s dst[150]    __attribute__ ((aligned (2)));
	nmpps32s etalon[150] __attribute__ ((aligned (2)));

	// Нечетная длина меньше 64 слова
	init_vector_value_32s(src, 1, 63);
	init_vector_value_32s(dst, 0, 63);
	init_vector_value_32s(etalon, 0x04000000, 63);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 26, dst, 63));

	for(i= 0; i < 63; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

    // Четная длина меньше 64 слова
	init_vector_value_32s(src, 1, 62);
	init_vector_value_32s(dst, 0, 62);
	init_vector_value_32s(etalon, 0x02000000, 62);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 25, dst, 62));

	for(i= 0; i < 62; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	// Кратно 64 словам
	init_vector_value_32s(src, 1, 128);
	init_vector_value_32s(dst, 0, 128);
	init_vector_value_32s(etalon, 0x01000000, 128);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 24, dst, 128));

	for(i= 0; i < 128; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}

	//Нечетная длина больше 64 слов
	init_vector_value_32s(src, 1, 149);
	init_vector_value_32s(dst, 0, 149);
	init_vector_value_32s(etalon, 0x00800000, 149);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 23, dst, 149));

	for(i= 0; i < 149; i++){
		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
	}


	// Четная длина больше 64 слов
	init_vector_value_32s(src, 1, 150);
	init_vector_value_32s(dst, 0, 150);
	init_vector_value_32s(etalon, 0x00400000, 150);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_32s(src, 22, dst, 150));

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
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16u_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16u_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16u);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_32s_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_32s_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_32s);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_8u_i_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_8u_i_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_8u_i);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s_i_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s_i_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16s_i);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16u_i_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16u_i_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_16u_i);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_32s_i_null_ptr);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_32s_i_err_len);
    RUN_TEST_CASE(tests_lshift, test_nmppsLShiftC_32s_i);

}



