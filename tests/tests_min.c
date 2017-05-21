/**
 * @file tests_min.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_min);

TEST_SETUP(tests_min) {}
TEST_TEAR_DOWN(tests_min) {}


//
// nmppsMin_32f
//

TEST(tests_min, nmppsMin_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMin_32f((void*)0, 1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMin_32f((void*)0, 1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMin_32f((void*)1, 1, (void*)0));
}

TEST(tests_min, nmppsMin_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMin_32f((void*)1,  0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMin_32f((void*)1, -1, (void*)1));
}

TEST(tests_min, nmppsMin_32f_asc) {
    nmpps32f values[] = { 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f, };
    nmpps32f MinVal;

    values[4] = 7500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(7500.0f, MinVal);

    values[3] = 5000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(5000.0f, MinVal);

    values[2] = 0.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, MinVal);

    values[1] = -500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(-500.0f, MinVal);

    values[0] = -1000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, MinVal);
}

TEST(tests_min, nmppsMin_32f_dsc) {
    nmpps32f values[] = { 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f, };
    nmpps32f MinVal;

    values[0] = 5000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(5000.0f, MinVal);

    values[1] = 2000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(2000.0f, MinVal);

    values[2] = 0.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, MinVal);

    values[3] = -500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(-500.0f, MinVal);

    values[4] = -1000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, MinVal);
}

TEST(tests_min, nmppsMin_32f_one_element) {
	nmpps32f values[] = { 1234.5f, };
	nmpps32f MinVal;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_32f(values, 1, &MinVal));
	TEST_ASSERT_EQUAL_FLOAT(1234.5f, MinVal);
}

//
// nmppsMin_64f
//

TEST(tests_min, nmppsMin_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMin_64f((void*)0, 1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMin_64f((void*)0, 1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMin_64f((void*)1, 1, (void*)0));
}

TEST(tests_min, nmppsMin_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMin_64f((void*)1,  0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMin_64f((void*)1, -1, (void*)1));
}

TEST(tests_min, nmppsMin_64f_asc) {
    nmpps64f values[] = { 10000.0, 10000.0, 10000.0, 10000.0, 10000.0 };
    nmpps64f MinVal;

    values[4] = 7500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(7500.0, MinVal);

    values[3] = 5000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(5000.0, MinVal);

    values[2] = 2000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(2000.0, MinVal);

    values[1] = 0.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, MinVal);

    values[0] = -500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(-500.0, MinVal);
}

TEST(tests_min, nmppsMin_64f_dsc) {
    nmpps64f values[] = { 10000.0, 10000.0, 10000.0, 10000.0, 10000.0 };
    nmpps64f MinVal;

    values[0] = 5000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(5000.0, MinVal);

    values[1] = 2000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(2000.0, MinVal);

    values[2] = 0.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, MinVal);

    values[3] = -500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(-500.0, MinVal);

    values[4] = -1000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 5, &MinVal));
    TEST_ASSERT_EQUAL_DOUBLE(-1000.0, MinVal);
}

TEST(tests_min, nmppsMin_64f_one_element) {
	nmpps64f values[] = { 1234.5, };
	nmpps64f MinVal;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMin_64f(values, 1, &MinVal));
	TEST_ASSERT_EQUAL_FLOAT(1234.5, MinVal);
}


TEST_GROUP_RUNNER(tests_min) {
    RUN_TEST_CASE(tests_min, nmppsMin_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_min, nmppsMin_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_min, nmppsMin_32f_asc);
    RUN_TEST_CASE(tests_min, nmppsMin_32f_dsc);
    RUN_TEST_CASE(tests_min, nmppsMin_32f_one_element);

    RUN_TEST_CASE(tests_min, nmppsMin_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_min, nmppsMin_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_min, nmppsMin_64f_asc);
    RUN_TEST_CASE(tests_min, nmppsMin_64f_dsc);
    RUN_TEST_CASE(tests_min, nmppsMin_64f_one_element);
}
