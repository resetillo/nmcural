/**
 * @file tests_minmaxindx.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_minmaxindx);

TEST_SETUP(tests_minmaxindx) {}
TEST_TEAR_DOWN(tests_minmaxindx) {}

//
// nmppsMinMaxIndx_16s
//

TEST(tests_minmaxindx, nmppsMinMaxIndx_16s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_16s((void*)1, 0, (void*)1, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_16s((void*)1, -1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_16s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_16s((void*)0, 1, (void*)0, (void*)0, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_16s((void*)1, 1, (void*)1, (void*)1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_16s((void*)1, 1, (void*)1, (void*)1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_16s((void*)1, 1, (void*)1, (void*)0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_16s((void*)1, 1, (void*)0, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_16s((void*)0, 1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_16s) {
    nmpps16s values[] = { 0, 0, 0, 0, 0, };
    nmpps16s MinVal;
    int MinIndx;
    nmpps16s MaxVal;
    int MaxIndx;

    values[4] = +7500;
    values[0] = -7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_16s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-7500, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL(+7500, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = +17500;
    values[1] = -17500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_16s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL(+17500, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = NMPPS_MIN_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_16s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(NMPPS_MIN_16S, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);
    TEST_ASSERT_EQUAL(+17500, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = NMPPS_MAX_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_16s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL(NMPPS_MAX_16S, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

}

TEST(tests_minmaxindx, nmppsMinMaxIndx_16s_one_element) {
    nmpps16s values[] = { 1234, };
    nmpps16s MinVal;
    int MinIndx;
    nmpps16s MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_16s(values, 1, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL(1234, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

//
// nmppsMinMaxIndx_32s
//

TEST(tests_minmaxindx, nmppsMinMaxIndx_32s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_32s((void*)1, 0, (void*)1, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_32s((void*)1, -1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_32s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32s((void*)0, 1, (void*)0, (void*)0, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32s((void*)1, 1, (void*)1, (void*)1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32s((void*)1, 1, (void*)1, (void*)1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32s((void*)1, 1, (void*)1, (void*)0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32s((void*)1, 1, (void*)0, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32s((void*)0, 1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_32s) {
    nmpps32s values[] = { 0, 0, 0, 0, 0, };
    nmpps32s MinVal;
    int MinIndx;
    nmpps32s MaxVal;
    int MaxIndx;

    values[4] = +7500;
    values[0] = -7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-7500, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL(+7500, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = +17500;
    values[1] = -17500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL(+17500, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = NMPPS_MIN_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(NMPPS_MIN_32S, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);
    TEST_ASSERT_EQUAL(+17500, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = NMPPS_MAX_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32s(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL(NMPPS_MAX_32S, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

}

TEST(tests_minmaxindx, nmppsMinMaxIndx_32s_one_element) {
    nmpps32s values[] = { 1234, };
    nmpps32s MinVal;
    int MinIndx;
    nmpps32s MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32s(values, 1, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL(1234, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

//
// nmppsMinMaxIndx_32f
//

TEST(tests_minmaxindx, nmppsMinMaxIndx_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_32f((void*)1, 0, (void*)1, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_32f((void*)1, -1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32f((void*)0, 1, (void*)0, (void*)0, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32f((void*)1, 1, (void*)1, (void*)1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32f((void*)1, 1, (void*)1, (void*)1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32f((void*)1, 1, (void*)1, (void*)0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32f((void*)1, 1, (void*)0, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_32f((void*)0, 1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_32f) {
    nmpps32f values[] = { 0, 0, 0, 0, 0, };
    nmpps32f MinVal;
    int MinIndx;
    nmpps32f MaxVal;
    int MaxIndx;

    values[4] = +7500.0f;
    values[0] = -7500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(-7500.0f, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL_FLOAT(+7500.0f, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = +17500.0f;
    values[1] = -17500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(-17500.0f, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL_FLOAT(+17500.0f, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = -35000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(-35000.0f, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);
    TEST_ASSERT_EQUAL_FLOAT(+17500.0f, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = +35000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_FLOAT(-17500.0f, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL_FLOAT(+35000.0f, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

}

TEST(tests_minmaxindx, nmppsMinMaxIndx_32f_one_element) {
    nmpps32f values[] = { 1234.5f, };
    nmpps32f MinVal;
    int MinIndx;
    nmpps32f MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_32f(values, 1, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234.5f, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL(1234.5f, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

//
// nmppsMinMaxIndx_64f
//

TEST(tests_minmaxindx, nmppsMinMaxIndx_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_64f((void*)1, 0, (void*)1, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMaxIndx_64f((void*)1, -1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_64f((void*)0, 1, (void*)0, (void*)0, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_64f((void*)1, 1, (void*)1, (void*)1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_64f((void*)1, 1, (void*)1, (void*)1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_64f((void*)1, 1, (void*)1, (void*)0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_64f((void*)1, 1, (void*)0, (void*)1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMaxIndx_64f((void*)0, 1, (void*)1, (void*)1, (void*)1, (void*)1));
}

TEST(tests_minmaxindx, nmppsMinMaxIndx_64f) {
    nmpps64f values[] = { 0, 0, 0, 0, 0, };
    nmpps64f MinVal;
    int MinIndx;
    nmpps64f MaxVal;
    int MaxIndx;

    values[4] = +7500.0;
    values[0] = -7500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_64f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-7500.0, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL_DOUBLE(+7500.0, MaxVal);
    TEST_ASSERT_EQUAL(4, MaxIndx);

    values[3] = +17500.0;
    values[1] = -17500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_64f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-17500.0, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL_DOUBLE(+17500.0, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = -35000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_64f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-35000.0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);
    TEST_ASSERT_EQUAL_DOUBLE(+17500.0, MaxVal);
    TEST_ASSERT_EQUAL(3, MaxIndx);

    values[2] = +35000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_64f(values, 5, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-17500.0, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);
    TEST_ASSERT_EQUAL_DOUBLE(+35000.0, MaxVal);
    TEST_ASSERT_EQUAL(2, MaxIndx);

}

TEST(tests_minmaxindx, nmppsMinMaxIndx_64f_one_element) {
    nmpps64f values[] = { 1234.5, };
    nmpps64f MinVal;
    int MinIndx;
    nmpps64f MaxVal;
    int MaxIndx;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMaxIndx_64f(values, 1, &MinVal, &MinIndx, &MaxVal, &MaxIndx));
    TEST_ASSERT_EQUAL(1234.5, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
    TEST_ASSERT_EQUAL(1234.5, MaxVal);
    TEST_ASSERT_EQUAL(0, MaxIndx);
}

TEST_GROUP_RUNNER(tests_minmaxindx) {
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_16s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_16s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_16s);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_16s_one_element);

    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32s);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32s_one_element);

    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32f);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_32f_one_element);

    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_64f);
    RUN_TEST_CASE(tests_minmaxindx, nmppsMinMaxIndx_64f_one_element);
}
