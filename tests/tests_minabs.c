/**
 * @file tests_minabs.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_minabs);

TEST_SETUP(tests_minabs) {}
TEST_TEAR_DOWN(tests_minabs) {}


//
// nmppsMinAbs_16s
//

TEST(tests_minabs, nmppsMinAbs_16s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbs_16s((void*)0, 1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbs_16s((void*)0, 1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbs_16s((void*)1, 1, (void*)0));
}

TEST(tests_minabs, nmppsMinAbs_16s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbs_16s((void*)1,  0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbs_16s((void*)1, -1, (void*)1));
}

TEST(tests_minabs, nmppsMinAbs_16s_asc) {
    nmpps16s values[] = { 10000, 10000, 10000, 10000, 10000, };
    nmpps16s MinVal;

    values[4] = 7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(7500, MinVal);

    values[3] = -5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(5000, MinVal);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[1] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[0] = -1000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);
}

TEST(tests_minabs, nmppsMinAbs_16s_dsc) {
    nmpps16s values[] = { 10000, 10000, 10000, 10000, 10000, };
    nmpps16s MinVal;

    values[0] = 5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(5000, MinVal);

    values[1] = -2000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(2000, MinVal);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[3] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[4] = -1000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);
}

TEST(tests_minabs, nmppsMinAbs_16s_one_element) {
	nmpps16s values[] = { 1234, };
	nmpps16s MinVal;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_16s(values, 1, &MinVal));
	TEST_ASSERT_EQUAL(1234, MinVal);
}

//
// nmppsMinAbs_32s
//

TEST(tests_minabs, nmppsMinAbs_32s_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbs_32s((void*)0, 1, (void*)0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbs_32s((void*)0, 1, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMinAbs_32s((void*)1, 1, (void*)0));
}

TEST(tests_minabs, nmppsMinAbs_32s_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbs_32s((void*)1,  0, (void*)1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMinAbs_32s((void*)1, -1, (void*)1));
}

TEST(tests_minabs, nmppsMinAbs_32s_asc) {
    nmpps32s values[] = { 10000.0, 10000.0, 10000.0, 10000.0, 10000.0 };
    nmpps32s MinVal;

    values[4] = 7500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(7500, MinVal);

    values[3] = -5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(5000, MinVal);

    values[2] = 2000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(2000, MinVal);

    values[1] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[0] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);
}

TEST(tests_minabs, nmppsMinAbs_32s_dsc) {
    nmpps32s values[] = { 10000, 10000, 10000, 10000, 10000 };
    nmpps32s MinVal;

    values[0] = 5000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(5000, MinVal);

    values[1] = -2000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(2000, MinVal);

    values[2] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[3] = -500;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);

    values[4] = -1000;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 5, &MinVal));
    TEST_ASSERT_EQUAL(0, MinVal);
}

TEST(tests_minabs, nmppsMinAbs_32s_one_element) {
	nmpps32s values[] = { 1234, };
	nmpps32s MinVal;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMinAbs_32s(values, 1, &MinVal));
	TEST_ASSERT_EQUAL(1234, MinVal);
}


TEST_GROUP_RUNNER(tests_minabs) {
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_16s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_16s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_16s_asc);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_16s_dsc);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_16s_one_element);

    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_32s_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_32s_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_32s_asc);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_32s_dsc);
    RUN_TEST_CASE(tests_minabs, nmppsMinAbs_32s_one_element);
}
