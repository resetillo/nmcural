#include "unity/unity_fixture.h"
#include "nmpps.h"


#undef ALIGNED
#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_stddev);

TEST_SETUP(tests_stddev) {}
TEST_TEAR_DOWN(tests_stddev) {}


TEST(tests_stddev, nmppsStdDev_32f_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsStdDev_32f((void*)1, -1, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsStdDev_32f((void*)1,  0, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsStdDev_32f((void*)1,  1, (void*)1, 0));
}

TEST(tests_stddev, nmppsStdDev_32f_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsStdDev_32f((void*)0,  2, (void*)0, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsStdDev_32f((void*)0,  2, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsStdDev_32f((void*)1,  2, (void*)0, 0));
}

TEST(tests_stddev, nmppsStdDev_32f) {
	nmpps32f src[] ALIGNED = { 1.0f, 2.0f, 3.0f };
	nmpps32f dst ALIGNED;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsStdDev_32f(src, 3, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst);
}

TEST(tests_stddev, nmppsStdDev_32f_two_elements) {
	nmpps32f src[] ALIGNED = { 32.0f, 15.0f };
	nmpps32f dst ALIGNED;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsStdDev_32f(src, 2, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT(12.0208152801713f, dst);
}

TEST(tests_stddev, nmppsStdDev_32f_many_elements) {
	nmpps32f src[80] ALIGNED;
	nmpps32f dst ALIGNED;
	int i;

	for (i = 0; i < 80; ++i)
		src[i] = 2.0f * (i + 1);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsStdDev_32f(src, 80, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT(46.475800154489f, dst);
}


TEST(tests_stddev, nmppsStdDev_64f_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsStdDev_64f((void*)1, -1, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsStdDev_64f((void*)1,  0, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsStdDev_64f((void*)1,  1, (void*)1));
}

TEST(tests_stddev, nmppsStdDev_64f_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsStdDev_64f((void*)0,  2, (void*)0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsStdDev_64f((void*)0,  2, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsStdDev_64f((void*)1,  2, (void*)0));
}

TEST(tests_stddev, nmppsStdDev_64f) {
	nmpps64f src[] = { 1.0, 2.0, 3.0 };
	nmpps64f dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsStdDev_64f(src, 3, &dst));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst);
}

TEST(tests_stddev, nmppsStdDev_64f_two_elements) {
	nmpps64f src[] = { 32.0, 15.0 };
	nmpps64f dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsStdDev_64f(src, 2, &dst));

	TEST_ASSERT_EQUAL_DOUBLE(12.0208152801713, dst);
}

TEST(tests_stddev, nmppsStdDev_64f_many_elements) {
	nmpps64f src[80];
	nmpps64f dst;
	int i;

	for (i = 0; i < 80; ++i)
		src[i] = 2.0 * (i + 1);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsStdDev_64f(src, 80, &dst));

	TEST_ASSERT_EQUAL_DOUBLE(46.475800154489, dst);
}


TEST_GROUP_RUNNER(tests_stddev) {
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_32f_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_32f_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_32f);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_32f_two_elements);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_32f_many_elements);

	RUN_TEST_CASE(tests_stddev, nmppsStdDev_64f_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_64f_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_64f);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_64f_two_elements);
	RUN_TEST_CASE(tests_stddev, nmppsStdDev_64f_many_elements);
}
