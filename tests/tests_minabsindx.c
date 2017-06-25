/**
 * @file tests_minabsindx.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_minabsindx);

TEST_SETUP(tests_minabsindx) {}
TEST_TEAR_DOWN(tests_minabsindx) {}

//
// nmppsMinAbsIndx_16s
//

TEST(tests_minabsindx, nmppsMinAbsIndx_16s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_16s((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_minabsindx, nmppsMinAbsIndx_16s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbsIndx_16s((void*)1,  0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbsIndx_16s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minabsindx, nmppsMinAbsIndx_16s) {
    nmpps16s values[] = { NMPPS_MAX_16S, NMPPS_MAX_16S, NMPPS_MAX_16S, NMPPS_MAX_16S, NMPPS_MAX_16S, };
    nmpps16s MinVal;
    int MinIndx;

    values[4] = 7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(7500, MinVal);
    TEST_ASSERT_EQUAL(4, MinIndx);

    values[3] = -5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(5000, MinVal);
    TEST_ASSERT_EQUAL(3, MinIndx);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[1] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[0] = NMPPS_MIN_16S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_16s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);
}

TEST(tests_minabsindx, nmppsMinAbsIndx_16s_one_element) {
	nmpps16s values[] = { 1234, };
	nmpps16s MinVal;
	int MinIndx;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_16s(values, 1, &MinVal, &MinIndx));
	TEST_ASSERT_EQUAL(1234, MinVal);
	TEST_ASSERT_EQUAL(0, MinIndx);
}

//
// nmppsMinAbsIndx_32s
//

TEST(tests_minabsindx, nmppsMinAbsIndx_32s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)0, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)0, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)0, 1, (void*)1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)0, 1, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)1, 1, (void*)0, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)1, 1, (void*)0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbsIndx_32s((void*)1, 1, (void*)1, (void*)0));
}

TEST(tests_minabsindx, nmppsMinAbsIndx_32s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbsIndx_32s((void*)1,  0, (void*)1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbsIndx_32s((void*)1, -1, (void*)1, (void*)1));
}

TEST(tests_minabsindx, nmppsMinAbsIndx_32s) {
    nmpps32s values[] = { NMPPS_MAX_32S, NMPPS_MAX_32S, NMPPS_MAX_32S, NMPPS_MAX_32S, NMPPS_MAX_32S, };
    nmpps32s MinVal;
    int MinIndx;

    values[4] = 7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(7500, MinVal);
    TEST_ASSERT_EQUAL(4, MinIndx);

    values[3] = -5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(5000, MinVal);
    TEST_ASSERT_EQUAL(3, MinIndx);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[1] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);

    values[0] = NMPPS_MIN_32S;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_32s(values, 5, &MinVal, &MinIndx));
    TEST_ASSERT_EQUAL(0, MinVal);
    TEST_ASSERT_EQUAL(2, MinIndx);
}

TEST(tests_minabsindx, nmppsMinAbsIndx_32s_one_element) {
	nmpps32s values[] = { 1234, };
	nmpps32s MinVal;
	int MinIndx;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbsIndx_32s(values, 1, &MinVal, &MinIndx));
	TEST_ASSERT_EQUAL(1234, MinVal);
	TEST_ASSERT_EQUAL(0, MinIndx);
}


TEST_GROUP_RUNNER(tests_minabsindx) {
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_16s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_16s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_16s);
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_16s_one_element);

    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_32s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_32s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_32s);
    RUN_TEST_CASE(tests_minabsindx, nmppsMinAbsIndx_32s_one_element);
}
