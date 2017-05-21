/**
 * @file tests_maxindx.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_maxindx);

TEST_SETUP(tests_maxindx) {}
TEST_TEAR_DOWN(tests_maxindx) {}

//
// nmppsMaxIndx_16s
//

TEST(tests_maxindx, nmppsMaxIndx_16s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_16s((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_maxindx, nmppsMaxIndx_16s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_16s((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_16s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_maxindx, nmppsMaxIndx_16s) {
    nmpps16s values[] = { NMPPS_MIN_16S, NMPPS_MIN_16S, NMPPS_MIN_16S, NMPPS_MIN_16S, NMPPS_MIN_16S, };
    nmpps16s MaxVal;
    int MaxIndx;

    values[4] = -7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_16s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-7500, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = -1500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_16s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-1500, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_16s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(0, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

    values[1] = 30000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_16s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(30000, MaxVal);
    TEST_ASSERT_EQUAL(1, MaxIndx);

    values[0] = NMPPS_MAX_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_16s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(NMPPS_MAX_16S, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

TEST(tests_maxindx, nmppsMaxIndx_16s_one_element) {
    nmpps16s values[] = { 1234, };
    nmpps16s MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_16s(values, 1, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

//
// nmppsMaxIndx_32s
//

TEST(tests_maxindx, nmppsMaxIndx_32s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32s((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_maxindx, nmppsMaxIndx_32s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_32s((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_32s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_maxindx, nmppsMaxIndx_32s) {
    nmpps32s values[] = { NMPPS_MIN_32S, NMPPS_MIN_32S, NMPPS_MIN_32S, NMPPS_MIN_32S, NMPPS_MIN_32S, };
    nmpps32s MaxVal;
    int MaxIndx;

    values[4] = -7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-7500, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = -1500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-1500, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(0, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

    values[1] = 50000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(50000, MaxVal);
    TEST_ASSERT_EQUAL(1, MaxIndx);

    values[0] = NMPPS_MAX_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32s(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(NMPPS_MAX_32S, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

TEST(tests_maxindx, nmppsMaxIndx_32s_one_element) {
    nmpps32s values[] = { 1234, };
    nmpps32s MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32s(values, 1, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

//
// nmppsMaxIndx_32f
//

TEST(tests_maxindx, nmppsMaxIndx_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_32f((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_maxindx, nmppsMaxIndx_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_32f((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_32f((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_maxindx, nmppsMaxIndx_32f) {
    nmpps32f values[] = { -10000.0f, -10000.0f, -10000.0f, -10000.0f, -10000.0f, };
    nmpps32f MaxVal;
    int MaxIndx;

    values[4] = -1000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = -500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(-500.0f, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = 0.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

    values[1] = 1000000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(1000000.0f, MaxVal);
    TEST_ASSERT_EQUAL(1, MaxIndx);

    values[0] = 50000000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(50000000.0f, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

TEST(tests_maxindx, nmppsMaxIndx_32f_one_element) {
    nmpps32f values[] = { 1234.5f, };
    nmpps32f MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_32f(values, 1, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234.5f, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

//
// nmppsMaxIndx_64f
//

TEST(tests_maxindx, nmppsMaxIndx_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxIndx_64f((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_maxindx, nmppsMaxIndx_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_64f((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxIndx_64f((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_maxindx, nmppsMaxIndx_64f) {
    nmpps64f values[] = { -10000.0, -10000.0, -10000.0, -10000.0, -10000.0 };
    nmpps64f MaxVal;
    int MaxIndx;

    values[4] = -500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_64f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-500.0, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = -250.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_64f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-250.0, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = 0.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_64f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

    values[1] = 1000000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_64f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(1000000.0, MaxVal);
    TEST_ASSERT_EQUAL(1, MaxIndx);

    values[0] = 50000000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_64f(values, 5, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(50000000.0, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

TEST(tests_maxindx, nmppsMaxIndx_64f_one_element) {
    nmpps64f values[] = { 1234.5, };
    nmpps64f MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxIndx_64f(values, 1, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234.5, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}


TEST_GROUP_RUNNER(tests_maxindx) {
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_16s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_16s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_16s);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_16s_one_element);

    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32s);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32s_one_element);

    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32f);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_32f_one_element);

    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_64f);
    RUN_TEST_CASE(tests_maxindx, nmppsMaxIndx_64f_one_element);
}
