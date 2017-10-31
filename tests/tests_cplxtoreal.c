/**
 * @file tests_cplxtoreal.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


#undef ALIGNED
#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_cplxtoreal);

TEST_SETUP(tests_cplxtoreal) {}
TEST_TEAR_DOWN(tests_cplxtoreal) {}


TEST(tests_cplxtoreal, nmppsCplxToReal_64fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)0, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)0, (void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)0, (void*)1, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)0, (void*)1, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)1, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)1, (void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_64fc((void*)1, (void*)1, (void*)0, 1));
}

TEST(tests_cplxtoreal, nmppsCplxToReal_64fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCplxToReal_64fc((void*)1, (void*)1, (void*)1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCplxToReal_64fc((void*)1, (void*)1, (void*)1, -1));
}

TEST(tests_cplxtoreal, nmppsCplxToReal_64fc) {
	nmpps64fc src[] = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
	nmpps64f dst_re[3];
	nmpps64f dst_im[3];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCplxToReal_64fc(src, dst_re, dst_im, 3));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst_re[0]);
	TEST_ASSERT_EQUAL_DOUBLE(3.0, dst_re[1]);
	TEST_ASSERT_EQUAL_DOUBLE(5.0, dst_re[2]);

	TEST_ASSERT_EQUAL_DOUBLE(2.0, dst_im[0]);
	TEST_ASSERT_EQUAL_DOUBLE(4.0, dst_im[1]);
	TEST_ASSERT_EQUAL_DOUBLE(6.0, dst_im[2]);
}

TEST(tests_cplxtoreal, nmppsCplxToReal_64fc_one_element) {
	nmpps64fc src[] = { {8.8, 2.2}, };
	nmpps64f dst_re[1];
	nmpps64f dst_im[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCplxToReal_64fc(src, dst_re, dst_im, 1));

	TEST_ASSERT_EQUAL_DOUBLE(8.8, dst_re[0]);
	TEST_ASSERT_EQUAL_DOUBLE(2.2, dst_im[0]);
}

TEST(tests_cplxtoreal, nmppsCplxToReal_64fc_many_elements) {
	nmpps64fc src[256];
	nmpps64f dst_re[256];
	nmpps64f dst_im[256];
	int i;

	for (i = 0; i < 256; ++i) {
		src[i].re = (double)i;
		src[i].im = (double)i + 3.0;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCplxToReal_64fc(src, dst_re, dst_im, 233));

	for (i = 0; i < 233; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst_re[i]);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst_im[i]);
	}

	TEST_ASSERT_EQUAL_DOUBLE(134.0, dst_re[134]);
	TEST_ASSERT_EQUAL_DOUBLE(137.0, dst_im[134]);
}


TEST(tests_cplxtoreal, nmppsCplxToReal_32fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)0, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)0, (void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)0, (void*)1, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)0, (void*)1, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)1, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)1, (void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsCplxToReal_32fc((void*)1, (void*)1, (void*)0, 1));
}

TEST(tests_cplxtoreal, nmppsCplxToReal_32fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCplxToReal_32fc((void*)1, (void*)1, (void*)1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsCplxToReal_32fc((void*)1, (void*)1, (void*)1, -1));
}

TEST(tests_cplxtoreal, nmppsCplxToReal_32fc) {
	nmpps32fc src[] ALIGNED = { {1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f} };
	nmpps32f dst_re[3] ALIGNED;
	nmpps32f dst_im[3] ALIGNED;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCplxToReal_32fc(src, dst_re, dst_im, 3));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst_re[0]);
	TEST_ASSERT_EQUAL_FLOAT(3.0f, dst_re[1]);
	TEST_ASSERT_EQUAL_FLOAT(5.0f, dst_re[2]);

	TEST_ASSERT_EQUAL_FLOAT(2.0f, dst_im[0]);
	TEST_ASSERT_EQUAL_FLOAT(4.0f, dst_im[1]);
	TEST_ASSERT_EQUAL_FLOAT(6.0f, dst_im[2]);
}

TEST(tests_cplxtoreal, nmppsCplxToReal_32fc_one_element) {
	nmpps32fc src[] ALIGNED = { {8.8f, 2.2f}, };
	nmpps32f dst_re[1] ALIGNED;
	nmpps32f dst_im[1] ALIGNED;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCplxToReal_32fc(src, dst_re, dst_im, 1));

	TEST_ASSERT_EQUAL_FLOAT(8.8f, dst_re[0]);
	TEST_ASSERT_EQUAL_FLOAT(2.2f, dst_im[0]);
}

TEST(tests_cplxtoreal, nmppsCplxToReal_32fc_many_elements) {
	nmpps32fc src[256] ALIGNED;
	nmpps32f dst_re[256] ALIGNED;
	nmpps32f dst_im[256] ALIGNED;
	int i;

	for (i = 0; i < 256; ++i) {
		src[i].re = (float)i;
		src[i].im = (float)i + 3.0f;
		dst_re[i] = -1.0f;
		dst_im[i] = -2.0f;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsCplxToReal_32fc(src, dst_re, dst_im, 233));

	for (i = 0; i < 233; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst_re[i]);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst_im[i]);
	}

	TEST_ASSERT_EQUAL_FLOAT(134.0f, dst_re[134]);
	TEST_ASSERT_EQUAL_FLOAT(137.0f, dst_im[134]);
}


TEST_GROUP_RUNNER(tests_cplxtoreal) {
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_64fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_64fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_64fc);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_64fc_one_element);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_64fc_many_elements);

	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_32fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_32fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_32fc);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_32fc_one_element);
	RUN_TEST_CASE(tests_cplxtoreal, nmppsCplxToReal_32fc_many_elements);
}
