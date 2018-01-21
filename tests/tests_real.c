/**
 * @file tests_real.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"

#undef ALIGNED
#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_real);

TEST_SETUP(tests_real) {}
TEST_TEAR_DOWN(tests_real) {}


TEST(tests_real, nmppsReal_64fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsReal_64fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsReal_64fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsReal_64fc((void*)1, (void*)0, 1));
}

TEST(tests_real, nmppsReal_64fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsReal_64fc((void*)1, (void*)1,  0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsReal_64fc((void*)1, (void*)1, -1));
}

TEST(tests_real, nmppsReal_64fc) {
	nmpps64fc src[] = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
	nmpps64f dst_re[3];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsReal_64fc(src, dst_re, 3));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst_re[0]);
	TEST_ASSERT_EQUAL_DOUBLE(3.0, dst_re[1]);
	TEST_ASSERT_EQUAL_DOUBLE(5.0, dst_re[2]);
}

TEST(tests_real, nmppsReal_64fc_one_element) {
	nmpps64fc src[] = { {1.0, 2.0}, };
	nmpps64f dst_re[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsReal_64fc(src, dst_re, 1));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst_re[0]);
}


TEST(tests_real, nmppsReal_32fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsReal_32fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsReal_32fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsReal_32fc((void*)1, (void*)0, 1));
}

TEST(tests_real, nmppsReal_32fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsReal_32fc((void*)1, (void*)1,  0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsReal_32fc((void*)1, (void*)1, -1));
}

TEST(tests_real, nmppsReal_32fc) {
	nmpps32fc src[] ALIGNED = { {1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f} };
	nmpps32f dst_re[4] ALIGNED = { 0, 0, 0, 0 };

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsReal_32fc(src, dst_re, 3));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst_re[0]);
	TEST_ASSERT_EQUAL_FLOAT(3.0f, dst_re[1]);
	TEST_ASSERT_EQUAL_FLOAT(5.0f, dst_re[2]);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst_re[3]);
}

TEST(tests_real, nmppsReal_32fc_one_element) {
	nmpps32fc src[] ALIGNED = { {1.0f, 2.0f}, };
	nmpps32f dst_re[2] ALIGNED = { 0, 0 };

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsReal_32fc(src, dst_re, 1));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst_re[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst_re[1]);
}


TEST_GROUP_RUNNER(tests_real) {
	RUN_TEST_CASE(tests_real, nmppsReal_64fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_real, nmppsReal_64fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_real, nmppsReal_64fc);
	RUN_TEST_CASE(tests_real, nmppsReal_64fc_one_element);

	RUN_TEST_CASE(tests_real, nmppsReal_32fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_real, nmppsReal_32fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_real, nmppsReal_32fc);
	RUN_TEST_CASE(tests_real, nmppsReal_32fc_one_element);
}
