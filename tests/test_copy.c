#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_copy);

TEST_SETUP(tests_copy) {}
TEST_TEAR_DOWN(tests_copy) {}

// nmppsCopy_16sc

TEST(tests_copy, test_nmppsCopy_16sc_null_ptr){
    nmpps16sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_16sc(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_16sc(vector, NULL, 1));
}

TEST(tests_copy, test_nmppsCopy_16sc_len){
    nmpps16sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_16sc(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_16sc(vector, vector, -1));
}

TEST(tests_copy, test_nmppsCopy_16sc){
    nmpps16sc* src = get_ptr_src_vector_16sc();
    nmpps16sc* dst = get_ptr_dst_vector_16sc();
    int i = 0;

    init_vector_16sc(src, 4100);
    init_vector_zero_16sc(dst, 4100);

    // Один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 1));

    TEST_ASSERT_EQUAL(src[0].im, dst[0].im);
    TEST_ASSERT_EQUAL(src[0].re, dst[0].re);

    //Многократное заполнение векторного регистра
    init_vector_zero_16sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 1024));

    for(i = 0; i < 1024; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    //Многократное заполнение векторного регистра + неполное заполнение
    init_vector_zero_16sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 4095));

    for(i = 0; i < 4095; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    // Весь вектор
    init_vector_zero_16sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 4100));

    for(i = 0; i < 4100; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }
}

// nmppsCopy_32sc

TEST(tests_copy, test_nmppsCopy_32sc_null_ptr){
    nmpps32sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_32sc(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_32sc(vector, NULL, 1));
}

TEST(tests_copy, test_nmppsCopy_32sc_len){
    nmpps32sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_32sc(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_32sc(vector, vector, -1));
}

TEST(tests_copy, test_nmppsCopy_32sc){
    nmpps32sc* src = get_ptr_src_vector_32sc();
    nmpps32sc* dst = get_ptr_dst_vector_32sc();
    int i = 0;

    init_vector_32sc(src, 4100);
    init_vector_zero_32sc(dst, 4100);

    // Один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 1));

    TEST_ASSERT_EQUAL(src[0].im, dst[0].im);
    TEST_ASSERT_EQUAL(src[0].re, dst[0].re);

    //Многократное заполнение векторного регистра
    init_vector_zero_32sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 1024));

    for(i = 0; i < 1024; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    //Многократное заполнение векторного регистра + неполное заполнение
    init_vector_zero_32sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 4095));

    for(i = 0; i < 4095; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    // Весь вектор
    init_vector_zero_32sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 4100));

    for(i = 0; i < 4100; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }
}

// nmppsCopy_64sc

TEST(tests_copy, test_nmppsCopy_64sc_null_ptr){
    nmpps64sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_64sc(NULL, vector, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_64sc(vector, NULL, 1));
}

TEST(tests_copy, test_nmppsCopy_64sc_len){
    nmpps64sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_64sc(vector, vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_64sc(vector, vector, -1));
}

TEST(tests_copy, test_nmppsCopy_64sc){
    nmpps64sc* src = get_ptr_src_vector_64sc();
    nmpps64sc* dst = get_ptr_dst_vector_64sc();
    int i = 0;

    init_vector_64sc(src, 4100);
    init_vector_zero_64sc(dst, 4100);

    // Один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 1));

    TEST_ASSERT_EQUAL(src[0].im, dst[0].im);
    TEST_ASSERT_EQUAL(src[0].re, dst[0].re);

    //Многократное заполнение векторного регистра
    init_vector_zero_64sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 1024));

    for(i = 0; i < 1024; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    //Многократное заполнение векторного регистра + неполное заполнение
    init_vector_zero_64sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 4095));

    for(i = 0; i < 4095; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    // Весь вектор
    init_vector_zero_64sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 4100));

    for(i = 0; i < 4100; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }
}

// nmppsCopy_1u

TEST(tests_copy, test_nmppsCopy_1u_null_ptr){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_1u(NULL, 2, vector, 4, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCopy_1u(vector, 1, NULL, 2, 1));
}

TEST(tests_copy, test_nmppsCopy_1u_len){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 1, vector, 2, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 3, vector, 4, -1));
}

TEST(tests_copy, test_nmppsCopy_1u_src_shift){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 0, vector, 2, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, -1, vector, 4, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 8, vector, 4, -1));
}

TEST(tests_copy, test_nmppsCopy_1u_dst_shift){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 1, vector, 0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 4, vector, -1, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCopy_1u(vector, 5, vector, 8, -1));
}

TEST(tests_copy, test_nmppsCopy_1u){
    nmpps8u src[3] = {123, 55, 1};
    nmpps8u dst[3]  = {1, 15, 125};
    // Копирование с третьего разряда в пятый разряд, 10 разрядов
    nmpps8u etalon1[3] = {6, 205, 125};
    int i = 0;

    // Копирование с четвертого разряда во второй, 12 разрадов
    nmpps8u etalon2[3] = {44, 223, 125};

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_1u(src, 3, dst, 5, 10));

    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL(etalon1[i], dst[i]);
    }



}


TEST_GROUP_RUNNER(tests_copy){
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_16sc_null_ptr);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_16sc_len);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_16sc);

    RUN_TEST_CASE(tests_copy, test_nmppsCopy_32sc_null_ptr);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_32sc_len);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_32sc);

    RUN_TEST_CASE(tests_copy, test_nmppsCopy_64sc_null_ptr);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_64sc_len);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_64sc);

    RUN_TEST_CASE(tests_copy, test_nmppsCopy_1u_null_ptr);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_1u_len);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_1u_src_shift);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_1u_dst_shift);
    RUN_TEST_CASE(tests_copy, test_nmppsCopy_1u);

}


//void test_nmppsCopy_1u(){
//  nmpps8u src[10] = {1, 56, 120, 45, 12, 67, 87, 34, 78, 26};
//  nmpps8u dst[10] = { 0 };
//
//  nmpps8u* psrc = NULL;
//  nmpps8u* pdst = NULL;
//
//  nmpps8u temp = 0;
//
//
//  int src_bit_offset = 0;
//  int dst_bit_offset = 0;
//
//  int i = 0;
//
//  nmppsStatus ret =  nmppsStsNoErr;
//
//  // �������� �� ������� ���������
//  ret = nmppsCopy_1u(NULL, 3, dst, 5, 8);
//  if(ret != nmppsStsNullPtrErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsNullPtrErr, ret);
//  }
//
//  ret = nmppsCopy_1u(src, 3, NULL, 5, 8);
//  if(ret != nmppsStsNullPtrErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsNullPtrErr, ret);
//  }
//
//  // �������� �� ������������ �����
//  ret = nmppsCopy_1u(src, 8, dst, 5, 8);
//  if(ret != nmppsStsSizeErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsSizeErr, ret);
//  }
//
//  ret = nmppsCopy_1u(src, -1, dst, 5, 8);
//  if(ret != nmppsStsSizeErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsSizeErr, ret);
//  }
//
//  ret = nmppsCopy_1u(src, 3, dst, -1, 8);
//  if(ret != nmppsStsSizeErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsSizeErr, ret);
//  }
//
//  ret = nmppsCopy_1u(src, 3, dst, 8, 8);
//  if(ret != nmppsStsSizeErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsSizeErr, ret);
//  }
//
//  ret = nmppsCopy_1u(src, 3, dst, 5, 0);
//  if(ret != nmppsStsSizeErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsSizeErr, ret);
//  }
//
//  ret = nmppsCopy_1u(src, 3, dst, 5, -1);
//  if(ret != nmppsStsSizeErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsSizeErr, ret);
//  }
//
//  static const nmpps8u bit_mask[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
//
//  // ������������� �����
//  ret = nmppsCopy_1u(&src[2], 5, &dst[3], 1, 15);
//  if(ret != nmppsStsNoErr){
//    printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, nmppsStsNoErr, ret);
//  }
//
//  psrc = &src[2];
//  pdst = &dst[3];
//
//  src_bit_offset = 5;
//  dst_bit_offset = 1;
//
//  for(i = 0; i < 15; i++){
//    temp = psrc[0] & bit_mask[src_bit_offset];
//
//    if(src_bit_offset > dst_bit_offset){
//      temp <<= src_bit_offset - dst_bit_offset;
//    }
//    else{
//      temp >>= dst_bit_offset - src_bit_offset;
//    }
//
//    if( temp != (pdst[0] & bit_mask[dst_bit_offset]) ){
//      printf("[%i][%s]: test error. expected: %i, got: %i\n", __LINE__, __FUNCTION__, psrc[0] & bit_mask[src_bit_offset], pdst[0] & bit_mask[dst_bit_offset]);
//    }
//
//    psrc += (src_bit_offset + 1) >> 3;
//    pdst += (dst_bit_offset + 1) >> 3;
//
//    src_bit_offset = (src_bit_offset + 1) & 7;
//    dst_bit_offset = (dst_bit_offset + 1) & 7;
//  }
//
//}


