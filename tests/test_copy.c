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
    nmpps16sc src[130] __attribute__ ((aligned (2)));
    nmpps16sc dst[130] __attribute__ ((aligned (2)));
    int i = 0;

    init_vector_16sc(src, 130);
    init_vector_zero_16sc(dst, 130);

    // Один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 1));

    TEST_ASSERT_EQUAL(src[0].im, dst[0].im);
    TEST_ASSERT_EQUAL(src[0].re, dst[0].re);

    //Многократное заполнение векторного регистра
    init_vector_zero_16sc(dst, 130);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 128));

    for(i = 0; i < 128; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    //Многократное заполнение векторного регистра + неполное заполнение
    init_vector_zero_16sc(dst, 130);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_16sc(src, dst, 130));

    for(i = 0; i < 130; i++){
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
    nmpps32sc src[130] __attribute__ ((aligned (2)));
    nmpps32sc dst[130] __attribute__ ((aligned (2)));
    int i = 0;

    init_vector_32sc(src, 130);
    init_vector_zero_32sc(dst, 130);

    // Один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 1));

    TEST_ASSERT_EQUAL(src[0].im, dst[0].im);
    TEST_ASSERT_EQUAL(src[0].re, dst[0].re);

    //Многократное заполнение векторного регистра
    init_vector_zero_32sc(dst, 130);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 128));

    for(i = 0; i < 128; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    //Многократное заполнение векторного регистра + неполное заполнение
    init_vector_zero_32sc(dst, 130);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_32sc(src, dst, 130));

    for(i = 0; i < 130; i++){
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
    nmpps64sc src[36] __attribute__ ((aligned (2)));
    nmpps64sc dst[36] __attribute__ ((aligned (2)));
    int i = 0;

    init_vector_64sc(src, 36);
    init_vector_zero_64sc(dst, 36);

    // Один элемент
    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 1));

    TEST_ASSERT_EQUAL(src[0].im, dst[0].im);
    TEST_ASSERT_EQUAL(src[0].re, dst[0].re);

    //Многократное заполнение векторного регистра
    init_vector_zero_64sc(dst, 36);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 32));

    for(i = 0; i < 32; i++){
        TEST_ASSERT_EQUAL(src[i].im, dst[i].im);
        TEST_ASSERT_EQUAL(src[i].re, dst[i].re);
    }

    //Многократное заполнение векторного регистра + неполное заполнение
    init_vector_zero_64sc(dst, 36);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_64sc(src, dst, 36));

    for(i = 0; i < 36; i++){
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
    nmpps8u etalon[3] = {6, 205, 125};
    int i = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCopy_1u(src, 3, dst, 5, 10));

    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL(etalon[i], dst[i]);
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


