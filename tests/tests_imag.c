/**
 * @file tests_imag.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"

#undef ALIGNED
#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_imag);

TEST_SETUP(tests_imag) {}
TEST_TEAR_DOWN(tests_imag) {}


TEST(tests_imag, nmppsImag_64fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsImag_64fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsImag_64fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsImag_64fc((void*)1, (void*)0, 1));
}

TEST(tests_imag, nmppsImag_64fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsImag_64fc((void*)1, (void*)1,  0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsImag_64fc((void*)1, (void*)1, -1));
}

TEST(tests_imag, nmppsImag_64fc) {
	nmpps64fc src[] = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
	nmpps64f dst_im[3];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsImag_64fc(src, dst_im, 3));

	TEST_ASSERT_EQUAL_DOUBLE(2.0, dst_im[0]);
	TEST_ASSERT_EQUAL_DOUBLE(4.0, dst_im[1]);
	TEST_ASSERT_EQUAL_DOUBLE(6.0, dst_im[2]);
}

TEST(tests_imag, nmppsImag_64fc_one_element) {
	nmpps64fc src[] = { {1.0, 2.0}, };
	nmpps64f dst_im[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsImag_64fc(src, dst_im, 1));

	TEST_ASSERT_EQUAL_DOUBLE(2.0, dst_im[0]);
}


TEST(tests_imag, nmppsImag_32fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsImag_32fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsImag_32fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsImag_32fc((void*)1, (void*)0, 1));
}

TEST(tests_imag, nmppsImag_32fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsImag_32fc((void*)1, (void*)1,  0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsImag_32fc((void*)1, (void*)1, -1));
}

TEST(tests_imag, nmppsImag_32fc) {
	nmpps32fc src[] ALIGNED = { {1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f} };
	nmpps32f dst_im[4] ALIGNED = { 0, 0, 0, 0 };

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsImag_32fc(src, dst_im, 3));

	TEST_ASSERT_EQUAL_FLOAT(2.0f, dst_im[0]);
	TEST_ASSERT_EQUAL_FLOAT(4.0f, dst_im[1]);
	TEST_ASSERT_EQUAL_FLOAT(6.0f, dst_im[2]);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst_im[3]);
}

TEST(tests_imag, nmppsImag_32fc_one_element) {
	nmpps32fc src[] ALIGNED = { {1.0f, 2.0f}, };
	nmpps32f dst_im[2] ALIGNED = { 0, 0 };

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsImag_32fc(src, dst_im, 1));

	TEST_ASSERT_EQUAL_FLOAT(2.0f, dst_im[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst_im[1]);
}


TEST_GROUP_RUNNER(tests_imag) {
	RUN_TEST_CASE(tests_imag, nmppsImag_64fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_imag, nmppsImag_64fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_imag, nmppsImag_64fc);
	RUN_TEST_CASE(tests_imag, nmppsImag_64fc_one_element);

	RUN_TEST_CASE(tests_imag, nmppsImag_32fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_imag, nmppsImag_32fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_imag, nmppsImag_32fc);
	RUN_TEST_CASE(tests_imag, nmppsImag_32fc_one_element);
}
