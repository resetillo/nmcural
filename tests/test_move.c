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

    nmpps8u* src = get_ptr_src_vector_8u();
    nmpps8u* etalon = get_ptr_dst_vector_8u();
    nmpps8u*  dst2 = src - _SHIFT_DST2;

    init_vector_8u(etalon, 4100);
    init_vector_8u(src, 4100);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst2, 193));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 193);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst2, 4067));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 4067);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst2, 31));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 31);

    //Полная загрузка векторного регистра
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst2, 4096));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 4096);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst2, 130));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 130);

    // Один элемент
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst2, 1));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst2, 1);
}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_8u_back){

    nmpps8u* src = get_ptr_src_vector_8u();
    nmpps8u* etalon = get_ptr_dst_vector_8u();
    nmpps8u*  dst1 = &src[_SHIFT_DST1];

    init_vector_8u(etalon, 4100);
    init_vector_8u(src, 4100);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst1, 193));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 193);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst1, 4067));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 4067);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst1, 31));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 31);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst1, 130));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 130);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst1, 130));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(etalon, dst1, 130);

    // Один элемент
    init_vector_8u(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_8u(src, dst1, 1));
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
    nmpps16s* src = get_ptr_src_vector_16s();
    nmpps16s* etalon = get_ptr_dst_vector_16s();
    nmpps16s*  dst2 = src - _SHIFT_DST2;
    int i = 0;

    init_vector_16s(etalon, 4100);
    init_vector_16s(src, 4100);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst2, 193));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 193);
//
//    for(i = 0; i < 193; i++){
//    	TEST_ASSERT_EQUAL(etalon[i], dst2[i]);
//    }

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst2, 4067));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 4067);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst2, 31));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 31);

    //Полная загрузка векторного регистра
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst2, 4096));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 4096);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst2, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 130);

    // Один элемент
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst2, 1));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 1);
}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_16s_back){

    nmpps16s* src = get_ptr_src_vector_16s();
    nmpps16s* etalon = get_ptr_dst_vector_16s();
    nmpps16s*  dst1 = &src[_SHIFT_DST1];

    init_vector_16s(etalon, 4100);
    init_vector_16s(src, 4100);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst1, 193));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 193);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst1, 4067));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 4067);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst1, 31));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 31);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst1, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 130);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst1, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 130);

    // Один элемент
    init_vector_16s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16s(src, dst1, 1));
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

    nmpps32s* src = get_ptr_src_vector_32s();
    nmpps32s* etalon = get_ptr_dst_vector_32s();
    nmpps32s*  dst2 = src - _SHIFT_DST2;

    init_vector_32s(etalon, 4100);
    init_vector_32s(src, 4100);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst2, 193));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 193);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst2, 4067));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 4067);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst2, 31));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 31);

    //Полная загрузка векторного регистра
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst2, 4096));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 4096);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst2, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 130);

    // Один элемент
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst2, 1));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst2, 1);
}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_32s_back){

    nmpps32s* src = get_ptr_src_vector_32s();
    nmpps32s* etalon = get_ptr_dst_vector_32s();
    nmpps32s*  dst1 = &src[_SHIFT_DST1];

    init_vector_32s(etalon, 4100);
    init_vector_32s(src, 4100);

    //Полная загрузка векторного регистра + один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst1, 193));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 193);

    //Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst1, 4067));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 4067);

    //Частичная загрузка векторного регистра + один элемент
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst1, 31));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 31);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst1, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 130);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst1, 130));
    TEST_ASSERT_EQUAL_INT8_ARRAY(etalon, dst1, 130);

    // Один элемент
    init_vector_32s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32s(src, dst1, 1));
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

    nmpps64s* src = get_ptr_src_vector_64s();
    nmpps64s* etalon = get_ptr_dst_vector_64s();
    nmpps64s*  dst2 = src - _SHIFT_DST2;

    init_vector_64s(etalon, 4100);
    init_vector_64s(src, 4100);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst2, 4067));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst2, 4067);

    //Частичная загрузка векторного регистра
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst2, 31));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst2, 31);

    //Полная загрузка векторного регистра
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst2, 4096));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst2, 4096);

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_64s_back){

    nmpps64s* src = get_ptr_src_vector_64s();
    nmpps64s* etalon = get_ptr_dst_vector_64s();
    nmpps64s*  dst1 = &src[_SHIFT_DST1];

    init_vector_64s(etalon, 4100);
    init_vector_64s(src, 4100);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst1, 4067));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 4067);

    //Частичная загрузка векторного регистра
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst1, 31));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 31);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst1, 130));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 130);

    //Полная загрузка векторного регистра
    init_vector_64s(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64s(src, dst1, 4096));
    TEST_ASSERT_EQUAL_INT16_ARRAY(etalon, dst1, 4096);
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

    nmpps16sc* src = get_ptr_src_vector_16sc();
    nmpps16sc* etalon = get_ptr_dst_vector_16sc();
    nmpps16sc*  dst2 = src - _SHIFT_DST2;

    init_vector_16sc(etalon, 4100);
    init_vector_16sc(src, 4100);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(src, dst2, 4067));

    for(i = 0; i < 4067; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_16sc(src, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(src, dst2, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_16sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(src, dst2, 4096));

    for(i = 0; i < 4096; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_16sc_back){
    int i = 0;

    nmpps16sc* src = get_ptr_src_vector_16sc();
    nmpps16sc* etalon = get_ptr_dst_vector_16sc();
    nmpps16sc*  dst1 = &src[_SHIFT_DST1];

    init_vector_16sc(etalon, 4100);
    init_vector_16sc(src, 4100);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_16sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(src, dst1, 4067));

    for(i = 0; i < 4067; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_16sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(src, dst1, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_16sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_16sc(src, dst1, 4096));

    for(i = 0; i < 4096; i++){
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

    nmpps32sc* src = get_ptr_src_vector_32sc();
    nmpps32sc* etalon = get_ptr_dst_vector_32sc();
    nmpps32sc*  dst2 = src - _SHIFT_DST2;

    init_vector_32sc(etalon, 4100);
    init_vector_32sc(src, 4100);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(src, dst2, 4067));

    for(i = 0; i < 4067; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_32sc(src, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(src, dst2, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_32sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(src, dst2, 4096));

    for(i = 0; i < 4096; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_32sc_back){
    int i = 0;

    nmpps32sc* src = get_ptr_src_vector_32sc();
    nmpps32sc* etalon = get_ptr_dst_vector_32sc();
    nmpps32sc*  dst1 = &src[_SHIFT_DST1];

    init_vector_32sc(etalon, 4100);
    init_vector_32sc(src, 4100);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_32sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(src, dst1, 4067));

    for(i = 0; i < 4067; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_32sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(src, dst1, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_32sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_32sc(src, dst1, 4096));

    for(i = 0; i < 4096; i++){
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

    nmpps64sc* src = get_ptr_src_vector_64sc();
    nmpps64sc* etalon = get_ptr_dst_vector_64sc();
    nmpps64sc*  dst2 = src - _SHIFT_DST2;

    init_vector_64sc(etalon, 4100);
    init_vector_64sc(src, 4100);

    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(src, dst2, 4067));

    for(i = 0; i < 4067; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_64sc(src, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(src, dst2, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_64sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(src, dst2, 4096));

    for(i = 0; i < 4096; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst2[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst2[i].re);
    }

}

// Адрес источника меньше адреса приемника
TEST(tests_move, test_nmppsMove_64sc_back){
    int i = 0;

    nmpps64sc* src = get_ptr_src_vector_64sc();
    nmpps64sc* etalon = get_ptr_dst_vector_64sc();
    nmpps64sc*  dst1 = &src[_SHIFT_DST1];

    init_vector_64sc(etalon, 4100);
    init_vector_64sc(src, 4100);


    //Полная загрузка векторного регистра + частичная загрузка
    init_vector_64sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(src, dst1, 4067));

    for(i = 0; i < 4067; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Частичная загрузка векторного регистра
    init_vector_64sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(src, dst1, 31));

    for(i = 0; i < 31; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }

    //Полная загрузка векторного регистра
    init_vector_64sc(src, 4100);
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMove_64sc(src, dst1, 4096));

    for(i = 0; i < 4096; i++){
    	TEST_ASSERT_EQUAL(etalon[i].im, dst1[i].im);
    	TEST_ASSERT_EQUAL(etalon[i].re, dst1[i].re);
    }
}

TEST_GROUP_RUNNER(tests_move){
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_8u_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16s_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32s_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64s_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_16sc_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_32sc_back);

    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_null_ptr);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_len);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_direct);
    RUN_TEST_CASE(tests_move, test_nmppsMove_64sc_back);
}







