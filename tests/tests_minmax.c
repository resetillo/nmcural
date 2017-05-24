/**
 * @file tests_minmax.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_minmax);

TEST_SETUP(tests_minmax) {}
TEST_TEAR_DOWN(tests_minmax) {}

//
// nmppsMinMax_16s
//

TEST(tests_minmax, nmppsMinMax_16s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_16s((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_16s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_16s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_16s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_16s((void*)1, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_16s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_16s((void*)0, 1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_16s) {
    nmpps16s values[] = { 0, 0, 0, 0, 0, };
    nmpps16s MinVal;
    nmpps16s MaxVal;

    values[4] = +7500;
    values[0] = -7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_16s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(-7500, MinVal);
    TEST_ASSERT_EQUAL(+7500, MaxVal);

    values[3] = +17500;
    values[1] = -17500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_16s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(+17500, MaxVal);

    values[2] = NMPPS_MIN_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_16s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(NMPPS_MIN_16S, MinVal);
    TEST_ASSERT_EQUAL(+17500, MaxVal);

    values[2] = NMPPS_MAX_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_16s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(NMPPS_MAX_16S, MaxVal);

}

TEST(tests_minmax, nmppsMinMax_16s_one_element) {
	nmpps16s values[] = { 1234, };
	nmpps16s MinVal;
	nmpps16s MaxVal;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_16s(values, 1, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(1234, MinVal);
    TEST_ASSERT_EQUAL(1234, MaxVal);
}

//
// nmppsMinMax_32s
//

TEST(tests_minmax, nmppsMinMax_32s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_32s((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_32s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_32s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32s((void*)1, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32s((void*)0, 1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_32s) {
    nmpps32s values[] = { 0, 0, 0, 0, 0, };
    nmpps32s MinVal;
    nmpps32s MaxVal;

    values[4] = +7500;
    values[0] = -7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(-7500, MinVal);
    TEST_ASSERT_EQUAL(+7500, MaxVal);

    values[3] = +17500;
    values[1] = -17500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(+17500, MaxVal);

    values[2] = NMPPS_MIN_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(NMPPS_MIN_32S, MinVal);
    TEST_ASSERT_EQUAL(+17500, MaxVal);

    values[2] = NMPPS_MAX_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32s(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(-17500, MinVal);
    TEST_ASSERT_EQUAL(NMPPS_MAX_32S, MaxVal);

}

TEST(tests_minmax, nmppsMinMax_32s_one_element) {
	nmpps32s values[] = { 1234, };
	nmpps32s MinVal;
	nmpps32s MaxVal;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32s(values, 1, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(1234, MinVal);
    TEST_ASSERT_EQUAL(1234, MaxVal);
}

//
// nmppsMinMax_32f
//

TEST(tests_minmax, nmppsMinMax_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_32f((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_32f((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32f((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32f((void*)1, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32f((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_32f((void*)0, 1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_32f) {
    nmpps32f values[] = { 0, 0, 0, 0, 0, };
    nmpps32f MinVal;
    nmpps32f MaxVal;

    values[4] = +7500.0f;
    values[0] = -7500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(-7500.0f, MinVal);
    TEST_ASSERT_EQUAL_FLOAT(+7500.0f, MaxVal);

    values[3] = +17500.0f;
    values[1] = -17500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(-17500.0f, MinVal);
    TEST_ASSERT_EQUAL_FLOAT(+17500.0f, MaxVal);

    values[2] = -35000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(-35000.0f, MinVal);
    TEST_ASSERT_EQUAL_FLOAT(+17500.0f, MaxVal);

    values[2] = +35000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(-17500.0f, MinVal);
    TEST_ASSERT_EQUAL_FLOAT(+35000.0f, MaxVal);

}

TEST(tests_minmax, nmppsMinMax_32f_one_element) {
	nmpps32f values[] = { 1234.0f, };
	nmpps32f MinVal;
	nmpps32f MaxVal;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_32f(values, 1, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(1234.0f, MinVal);
    TEST_ASSERT_EQUAL(1234.0f, MaxVal);
}

//
// nmppsMinMax_64f
//

TEST(tests_minmax, nmppsMinMax_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_64f((void*)1, 0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinMax_64f((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_64f((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_64f((void*)1, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_64f((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinMax_64f((void*)0, 1, (void*)1, (void*)1));
}

TEST(tests_minmax, nmppsMinMax_64f) {
    nmpps64f values[] = { 0, 0, 0, 0, 0, };
    nmpps64f MinVal;
    nmpps64f MaxVal;

    values[4] = +7500.0;
    values[0] = -7500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_64f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(-7500.0, MinVal);
    TEST_ASSERT_EQUAL_DOUBLE(+7500.0, MaxVal);

    values[3] = +17500.0;
    values[1] = -17500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_64f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(-17500.0, MinVal);
    TEST_ASSERT_EQUAL_DOUBLE(+17500.0, MaxVal);

    values[2] = -35000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_64f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(-35000.0, MinVal);
    TEST_ASSERT_EQUAL_DOUBLE(+17500.0, MaxVal);

    values[2] = +35000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_64f(values, 5, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(-17500.0, MinVal);
    TEST_ASSERT_EQUAL_DOUBLE(+35000.0, MaxVal);

}

TEST(tests_minmax, nmppsMinMax_64f_one_element) {
	nmpps64f values[] = { 1234.0, };
	nmpps64f MinVal;
	nmpps64f MaxVal;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinMax_64f(values, 1, &MinVal, &MaxVal));
    TEST_ASSERT_EQUAL(1234.0, MinVal);
    TEST_ASSERT_EQUAL(1234.0, MaxVal);
}


TEST_GROUP_RUNNER(tests_minmax) {
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_16s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_16s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_16s);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_16s_one_element);

    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32s);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32s_one_element);

    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32f);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_32f_one_element);

    RUN_TEST_CASE(tests_minmax, nmppsMinMax_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_64f);
    RUN_TEST_CASE(tests_minmax, nmppsMinMax_64f_one_element);
}
