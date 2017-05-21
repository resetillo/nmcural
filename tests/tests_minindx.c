/**
 * @file tests_minindx.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_minindx);

TEST_SETUP(tests_minindx) {}
TEST_TEAR_DOWN(tests_minindx) {}

//
// nmppsMinIndx_16s
//

TEST(tests_minindx, nmppsMinIndx_16s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_16s((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_minindx, nmppsMinIndx_16s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_16s((void*)1,  0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_16s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minindx, nmppsMinIndx_16s) {
    nmpps16s values[] = { NMPPS_MAX_16S, NMPPS_MAX_16S, NMPPS_MAX_16S, NMPPS_MAX_16S, NMPPS_MAX_16S, };
    nmpps16s MinVal;
    int MinIndx;

    values[4] = 7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(7500, MinVal);
    TEST_ASSERT_EQUAL(4, MinIndx);

    values[3] = 5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(5000, MinVal);
    TEST_ASSERT_EQUAL(3, MinIndx);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[1] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(-500, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);

    values[0] = NMPPS_MIN_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(NMPPS_MIN_16S, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
}

TEST(tests_minindx, nmppsMinIndx_16s_one_element) {
	nmpps16s values[] = { 1234, };
	nmpps16s MinVal;
	int MinIndx;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_16s(values, 1, &MinVal, &MinIndx));
	TEST_ASSERT_EQUAL(1234, MinVal);
	TEST_ASSERT_EQUAL(0, MinIndx);
}

//
// nmppsMinIndx_32s
//

TEST(tests_minindx, nmppsMinIndx_32s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32s((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_minindx, nmppsMinIndx_32s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_32s((void*)1,  0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_32s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minindx, nmppsMinIndx_32s) {
    nmpps32s values[] = { NMPPS_MAX_32S, NMPPS_MAX_32S, NMPPS_MAX_32S, NMPPS_MAX_32S, NMPPS_MAX_32S, };
    nmpps32s MinVal;
    int MinIndx;

    values[4] = 7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(7500, MinVal);
    TEST_ASSERT_EQUAL(4, MinIndx);

    values[3] = 5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(5000, MinVal);
    TEST_ASSERT_EQUAL(3, MinIndx);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[1] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(-500, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);

    values[0] = NMPPS_MIN_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(NMPPS_MIN_32S, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
}

TEST(tests_minindx, nmppsMinIndx_32s_one_element) {
	nmpps32s values[] = { 1234, };
	nmpps32s MinVal;
	int MinIndx;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32s(values, 1, &MinVal, &MinIndx));
	TEST_ASSERT_EQUAL(1234, MinVal);
	TEST_ASSERT_EQUAL(0, MinIndx);
}

//
// nmppsMinIndx_32f
//

TEST(tests_minindx, nmppsMinIndx_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_32f((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_minindx, nmppsMinIndx_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_32f((void*)1,  0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_32f((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minindx, nmppsMinIndx_32f) {
    nmpps32f values[] = { 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f, };
    nmpps32f MinVal;
    int MinIndx;

    values[4] = 7500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_FLOAT(7500.0f, MinVal);
    TEST_ASSERT_EQUAL(4, MinIndx);

    values[3] = 5000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_FLOAT(5000.0f, MinVal);
    TEST_ASSERT_EQUAL(3, MinIndx);

    values[2] = 0.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[1] = -500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_FLOAT(-500.0f, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);

    values[0] = -1000.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
}

TEST(tests_minindx, nmppsMinIndx_32f_one_element) {
	nmpps32f values[] = { 1234.5f, };
	nmpps32f MinVal;
	int MinIndx;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_32f(values, 1, &MinVal, &MinIndx));
	TEST_ASSERT_EQUAL(1234.5f, MinVal);
	TEST_ASSERT_EQUAL(0, MinIndx);
}

//
// nmppsMinIndx_64f
//

TEST(tests_minindx, nmppsMinIndx_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinIndx_64f((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_minindx, nmppsMinIndx_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_64f((void*)1,  0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinIndx_64f((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minindx, nmppsMinIndx_64f) {
    nmpps64f values[] = { 10000.0, 10000.0, 10000.0, 10000.0, 10000.0 };
    nmpps64f MinVal;
    int MinIndx;

    values[4] = 7500.0f;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_64f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_DOUBLE(7500.0, MinVal);
    TEST_ASSERT_EQUAL(4, MinIndx);

    values[3] = 5000.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_64f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_DOUBLE(5000.0, MinVal);
    TEST_ASSERT_EQUAL(3, MinIndx);

    values[2] = 0.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_64f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[1] = -250.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_64f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-250.0, MinVal);
    TEST_ASSERT_EQUAL(1, MinIndx);

    values[0] = -500.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_64f(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL_DOUBLE(-500.0, MinVal);
    TEST_ASSERT_EQUAL(0, MinIndx);
}

TEST(tests_minindx, nmppsMinIndx_64f_one_element) {
	nmpps64f values[] = { 1234.5, };
	nmpps64f MinVal;
	int MinIndx;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinIndx_64f(values, 1, &MinVal, &MinIndx));
	TEST_ASSERT_EQUAL(1234.5, MinVal);
	TEST_ASSERT_EQUAL(0, MinIndx);
}


TEST_GROUP_RUNNER(tests_minindx) {
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_16s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_16s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_16s);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_16s_one_element);

    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32s);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32s_one_element);

    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32f);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_32f_one_element);

    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_64f);
    RUN_TEST_CASE(tests_minindx, nmppsMinIndx_64f_one_element);
}
