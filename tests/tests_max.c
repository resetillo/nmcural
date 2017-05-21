/**
 * @file tests_max.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_max);

TEST_SETUP(tests_max) {}
TEST_TEAR_DOWN(tests_max) {}


//
// nmppsMax_32f
//

TEST(tests_max, nmppsMax_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMax_32f((void*)0, 1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMax_32f((void*)0, 1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMax_32f((void*)1, 1, (void*)0));
}

TEST(tests_max, nmppsMax_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMax_32f((void*)1,  0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMax_32f((void*)1, -1, (void*)1));
}

TEST(tests_max, nmppsMax_32f) {
    nmpps32f values[] = { -10000.0f, -10000.0f, -10000.0f, -10000.0f, -10000.0f, };
    nmpps32f MaxVal;

    values[4] = -5000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_32f(values, 5, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(-5000.0f, MaxVal);

    values[3] = -1000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_32f(values, 5, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, MaxVal);

    values[2] = 0.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_32f(values, 5, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, MaxVal);

    values[1] = 10000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_32f(values, 5, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(10000.0f, MaxVal);

    values[0] = 50000000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_32f(values, 5, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(50000000.0f, MaxVal);
}

TEST(tests_max, nmppsMax_32f_one_element) {
	nmpps32f values[] = { 1234.5f, };
	nmpps32f MaxVal;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_32f(values, 1, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(1234.5f, MaxVal);
}

//
// nmppsMax_64f
//

TEST(tests_max, nmppsMax_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMax_64f((void*)0, 1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMax_64f((void*)0, 1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMax_64f((void*)1, 1, (void*)0));
}

TEST(tests_max, nmppsMax_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMax_64f((void*)1,  0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMax_64f((void*)1, -1, (void*)1));
}

TEST(tests_max, nmppsMax_64f) {
    nmpps64f values[] = { -10000.0, -10000.0, -10000.0, -10000.0, -10000.0 };
    nmpps64f MaxVal;

    values[4] = -7500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_64f(values, 5, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(-7500.0, MaxVal);

    values[3] = -5000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_64f(values, 4, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(-5000.0, MaxVal);

    values[2] = 0.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_64f(values, 4, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, MaxVal);

    values[1] = 1000000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_64f(values, 4, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(1000000.0, MaxVal);

    values[0] = 50000000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_64f(values, 4, &MaxVal));
    TEST_ASSERT_EQUAL_DOUBLE(50000000.0, MaxVal);
}

TEST(tests_max, nmppsMax_64f_one_element) {
	nmpps64f values[] = { 1234.5, };
	nmpps64f MaxVal;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMax_64f(values, 1, &MaxVal));
    TEST_ASSERT_EQUAL_FLOAT(1234.5, MaxVal);
}


TEST_GROUP_RUNNER(tests_max) {
    RUN_TEST_CASE(tests_max, nmppsMax_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_max, nmppsMax_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_max, nmppsMax_32f);
    RUN_TEST_CASE(tests_max, nmppsMax_32f_one_element);

    RUN_TEST_CASE(tests_max, nmppsMax_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_max, nmppsMax_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_max, nmppsMax_64f);
    RUN_TEST_CASE(tests_max, nmppsMax_64f_one_element);
}
