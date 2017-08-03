#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"


#define _SHIFT_DST1 2
#define _SHIFT_DST2 2
#define _SHIFT_DST1_64 8

TEST_GROUP(tests_move);

TEST_SETUP(tests_move){}
TEST_TEAR_DOWN(tests_move){}

// nmppsMove_8u

TEST(tests_move, test_nmppsMove_8u_null_ptr){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_8u(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_8u(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_8u_len){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_8u(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_8u(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_8u_direct){

	struct {
		nmpps8u mem[10];
	    nmpps8u src[150]   __attribute__ ((aligned (2)));
	}for_test_move;

    nmpps8u etalon[150]__attribute__ ((aligned (2)));
    nmpps8u*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_8u(etalon, 131);
    init_vector_8u(for_test_move.src, 131);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst2, 129));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 129);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_8u(for_test_move.src, 131);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst2, 137));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 131);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_8u(for_test_move.src, 131);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst2, 31));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 31);

    //Полная загрузка векторного регистра
    init_vector_8u(for_test_move.src, 131);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst2, 128));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 128);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_8u(for_test_move.src, 131);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst2, 130));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 130);

    // Один элемент
    init_vector_8u(for_test_move.src, 131);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst2, 1));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 1);
}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_8u_back){

	struct {
		nmpps8u src[150]   __attribute__ ((aligned (2)));
		nmpps8u mem[10];
	}for_test_move;

    nmpps8u etalon[150] __attribute__ ((aligned (2)));
    nmpps8u*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_8u(etalon, 150);
    init_vector_8u(for_test_move.src, 150);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst1, 129));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 129);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_8u(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst1, 137));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 137);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_8u(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst1, 63));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 63);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_8u(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst1, 130));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 130);

    // Один элемент
    init_vector_8u(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(for_test_move.src, dst1, 1));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 1);
}

// nmppsMove_16s

TEST(tests_move, test_nmppsMove_16s_null_ptr){
    nmpps16s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_16s(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_16s(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_16s_len){
    nmpps16s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_16s(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_16s(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_16s_direct){

	struct {
		nmpps16s mem[10];
		nmpps16s src[150]   __attribute__ ((aligned (2)));
	}for_test_move;

    nmpps16s etalon[150] __attribute__ ((aligned (2)));
    nmpps16s*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_16s(etalon, 150);
    init_vector_16s(for_test_move.src, 150);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst2, 65));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 65);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst2, 131));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 131);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst2, 63));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 63);

    //Полная загрузка векторного регистра
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst2, 128));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 128);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst2, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 130);

    // Один элемент
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst2, 1));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 1);
}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_16s_back){

	struct {
		nmpps16s src[150]   __attribute__ ((aligned (2)));
		nmpps16s mem[10];
	}for_test_move;

    nmpps16s etalon[150] __attribute__ ((aligned (2)));
    nmpps16s*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_16s(etalon, 150);
    init_vector_16s(for_test_move.src, 150);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst1, 65));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 65);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst1, 131));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 131);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst1, 63));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 63);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst1, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 130);

    // Один элемент
    init_vector_16s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(for_test_move.src, dst1, 1));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 1);
}

// nmppsMove_32s

TEST(tests_move, test_nmppsMove_32s_null_ptr){
    nmpps32s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_32s(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_32s(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_32s_len){
    nmpps32s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_32s(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_32s(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_32s_direct){

	struct {
		nmpps32s mem[10];
		nmpps32s src[150]   __attribute__ ((aligned (2)));
	}for_test_move;

    nmpps32s etalon[150] __attribute__ ((aligned (2)));
    nmpps32s*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_32s(etalon, 150);
    init_vector_32s(for_test_move.src, 150);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst2, 65));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 65);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst2, 137));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 137);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst2, 63));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 63);

    //Полная загрузка векторного регистра
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst2, 128));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 128);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst2, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 130);

    // Один элемент
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst2, 1));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 1);
}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_32s_back){

	struct {
		nmpps32s src[150]   __attribute__ ((aligned (2)));
		nmpps32s mem[10];
	}for_test_move;

    nmpps32s etalon[150] __attribute__ ((aligned (2)));
    nmpps32s*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_32s(etalon, 150);
    init_vector_32s(for_test_move.src, 150);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst1, 129));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 129);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst1, 137));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 137);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst1, 63));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 63);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst1, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 130);

    // Один элемент
    init_vector_32s(for_test_move.src, 150);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(for_test_move.src, dst1, 1));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 1);
}

// nmppsMove_64s

TEST(tests_move, test_nmppsMove_64s_null_ptr){
    nmpps64s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_64s(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_64s(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_64s_len){
    nmpps64s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_64s(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_64s(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_64s_direct){

	struct {
		nmpps64s mem[4];
		nmpps64s src[70]   __attribute__ ((aligned (2)));
	}for_test_move;

    nmpps64s etalon[70] __attribute__ ((aligned (2)));
    nmpps64s*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_64s(etalon, 70);
    init_vector_64s(for_test_move.src, 70);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64s(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(for_test_move.src, dst2, 40));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst2, 40);

    //Частичная загрузка векторного регистра
    init_vector_64s(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(for_test_move.src, dst2, 31));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst2, 31);

    //Полная загрузка векторного регистра
    init_vector_64s(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(for_test_move.src, dst2, 64));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst2, 64);

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_64s_back){

	struct {
		nmpps64s src[70]   __attribute__ ((aligned (2)));
		nmpps64s mem[4];
	}for_test_move;

    nmpps64s etalon[70] __attribute__ ((aligned (2)));
    nmpps64s*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_64s(etalon, 70);
    init_vector_64s(for_test_move.src, 70);

    //Частичная загрузка векторного регистра
    init_vector_64s(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(for_test_move.src, dst1, 31));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 31);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64s(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(for_test_move.src, dst1, 66));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 66);

    //Полная загрузка векторного регистра
    init_vector_64s(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(for_test_move.src, dst1, 64));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 64);
}

// nmppsMove_16sc

TEST(tests_move, test_nmppsMove_16sc_null_ptr){
    nmpps16sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_16sc(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_16sc(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_16sc_len){
    nmpps16sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_16sc(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_16sc(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_16sc_direct){
    int i = 0;

    struct {
    	nmpps16sc mem[4];
    	nmpps16sc src[70]   __attribute__ ((aligned (2)));
    }for_test_move;

    nmpps16sc etalon[70] __attribute__ ((aligned (2)));
    nmpps16sc*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_16sc(etalon, 70);
    init_vector_16sc(for_test_move.src, 70);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(for_test_move.src, dst2, 66));

    for(i = 0; i < 66; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_16sc(for_test_move.src, 70);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(for_test_move.src, dst2, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_16sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(for_test_move.src, dst2, 64));

    for(i = 0; i < 64; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_16sc_back){
    int i = 0;

    struct {
    	nmpps16sc src[70]   __attribute__ ((aligned (2)));
    	nmpps16sc mem[4];
    }for_test_move;

    nmpps16sc etalon[70] __attribute__ ((aligned (2)));
    nmpps16sc*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_16sc(etalon, 70);
    init_vector_16sc(for_test_move.src, 70);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(for_test_move.src, dst1, 66));

    for(i = 0; i < 66; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_16sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(for_test_move.src, dst1, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_16sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(for_test_move.src, dst1, 64));

    for(i = 0; i < 64; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }
}

// nmppsMove_32sc

TEST(tests_move, test_nmppsMove_32sc_null_ptr){
    nmpps32sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_32sc(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_32sc(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_32sc_len){
    nmpps32sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_32sc(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_32sc(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_32sc_direct){
    int i = 0;

    struct {
    	nmpps32sc mem[4];
    	nmpps32sc src[70]   __attribute__ ((aligned (2)));
    }for_test_move;

    nmpps32sc etalon[70] __attribute__ ((aligned (2)));
    nmpps32sc*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_32sc(etalon, 70);
    init_vector_32sc(for_test_move.src, 70);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(for_test_move.src, dst2, 66));

    for(i = 0; i < 66; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_32sc(for_test_move.src, 70);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(for_test_move.src, dst2, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_32sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(for_test_move.src, dst2, 64));

    for(i = 0; i < 64; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_32sc_back){
    int i = 0;

    struct {
    	nmpps32sc src[70]   __attribute__ ((aligned (2)));
    	nmpps32sc mem[4];
    }for_test_move;

    nmpps32sc etalon[70] __attribute__ ((aligned (2)));
    nmpps32sc*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_32sc(etalon, 70);
    init_vector_32sc(for_test_move.src, 70);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(for_test_move.src, dst1, 66));

    for(i = 0; i < 66; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_32sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(for_test_move.src, dst1, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_32sc(for_test_move.src, 70);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(for_test_move.src, dst1, 64));

    for(i = 0; i < 64; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }
}

// nmppsMove_64sc

TEST(tests_move, test_nmppsMove_64sc_null_ptr){
    nmpps64sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_64sc(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMove_64sc(vector, NULL, 1));
}

TEST(tests_move, test_nmppsMove_64sc_len){
    nmpps64sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_64sc(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMove_64sc(vector, vector, -1));
}

// Адрес источника больше адреса приемника
TEST(tests_move, test_nmppsMove_64sc_direct){
    int i = 0;

    struct {
    	nmpps64sc mem[4];
    	nmpps64sc src[40]   __attribute__ ((aligned (2)));
    }for_test_move;

    nmpps64sc etalon[40] __attribute__ ((aligned (2)));
    nmpps64sc*  dst2 = for_test_move.src - _SHIFT_DST2;

    init_vector_64sc(etalon, 40);
    init_vector_64sc(for_test_move.src, 40);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64sc(for_test_move.src, 40);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(for_test_move.src, dst2, 34));

    for(i = 0; i < 34; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_64sc(for_test_move.src, 40);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(for_test_move.src, dst2, 12));

    for(i = 0; i < 12; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_64sc(for_test_move.src, 40);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(for_test_move.src, dst2, 32));

    for(i = 0; i < 32; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_64sc_back){
    int i = 0;

    struct {
    	nmpps64sc src[40]   __attribute__ ((aligned (2)));
    	nmpps64sc mem[4];
    }for_test_move;

    nmpps64sc etalon[40] __attribute__ ((aligned (2)));
    nmpps64sc*  dst1 = &(for_test_move.src[_SHIFT_DST1]);

    init_vector_64sc(etalon, 40);
    init_vector_64sc(for_test_move.src, 40);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64sc(for_test_move.src, 40);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(for_test_move.src, dst1, 34));

    for(i = 0; i < 34; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_64sc(for_test_move.src, 3);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(for_test_move.src, dst1, 3));

    for(i = 0; i < 3; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_64sc(for_test_move.src, 40);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(for_test_move.src, dst1, 32));

    for(i = 0; i < 32; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }
}

TEST_GROUP_RUNNER(tests_move){
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_back);
//
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_back);
//
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_back);
//
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_back);
//
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_back);
//
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_back);
}







