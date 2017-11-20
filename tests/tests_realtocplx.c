/**
 * @file tests_realtocplx.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


#undef ALIGNED
#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_realtocplx);

TEST_SETUP(tests_realtocplx) {}
TEST_TEAR_DOWN(tests_realtocplx) {}


/*
 // nmppsRealToCplx_64f
 */

TEST(tests_realtocplx, nmppsRealToCplx_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_64f((void*)0, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_64f((void*)0, (void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_64f((void*)0, (void*)1, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_64f((void*)1, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_64f((void*)1, (void*)1, (void*)0, 1));
}

TEST(tests_realtocplx, nmppsRealToCplx_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRealToCplx_64f((void*)1, (void*)1, (void*)1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRealToCplx_64f((void*)1, (void*)1, (void*)1, -1));
}

TEST(tests_realtocplx, nmppsRealToCplx_64f) {
	nmpps64f src_re[] = { 1.0, 2.0, 5.0, };
	nmpps64f src_im[] = { 3.0, 4.0, 6.0, };
	nmpps64fc dst[3];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 3));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst[0].re);
	TEST_ASSERT_EQUAL_DOUBLE(3.0, dst[0].im);

	TEST_ASSERT_EQUAL_DOUBLE(2.0, dst[1].re);
	TEST_ASSERT_EQUAL_DOUBLE(4.0, dst[1].im);

	TEST_ASSERT_EQUAL_DOUBLE(5.0, dst[2].re);
	TEST_ASSERT_EQUAL_DOUBLE(6.0, dst[2].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_64f_re_is_null) {
	nmpps64f src_im[] = { 3.0, 4.0, 6.0, };
	nmpps64fc dst[3];

	dst[0].re = -1.0;
	dst[1].re = -2.0;
	dst[2].re = -3.0;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(NULL, src_im, dst, 3));

	TEST_ASSERT_EQUAL_DOUBLE(0.0, dst[0].re);
	TEST_ASSERT_EQUAL_DOUBLE(3.0, dst[0].im);

	TEST_ASSERT_EQUAL_DOUBLE(0.0, dst[1].re);
	TEST_ASSERT_EQUAL_DOUBLE(4.0, dst[1].im);

	TEST_ASSERT_EQUAL_DOUBLE(0.0, dst[2].re);
	TEST_ASSERT_EQUAL_DOUBLE(6.0, dst[2].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_64f_im_is_null) {
	nmpps64f src_re[] = { 1.0, 2.0, 5.0, };
	nmpps64fc dst[3];

	dst[0].im = -1.0;
	dst[1].im = -2.0;
	dst[2].im = -3.0;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, NULL, dst, 3));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst[0].re);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, dst[0].im);

	TEST_ASSERT_EQUAL_DOUBLE(2.0, dst[1].re);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, dst[1].im);

	TEST_ASSERT_EQUAL_DOUBLE(5.0, dst[2].re);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, dst[2].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_64f_one_element) {
	nmpps64f src_re[] = { 1.0, };
	nmpps64f src_im[] = { 3.0, };
	nmpps64fc dst[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 1));

	TEST_ASSERT_EQUAL_DOUBLE(1.0, dst[0].re);
	TEST_ASSERT_EQUAL_DOUBLE(3.0, dst[0].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_64f_many_elements) {
	nmpps64f src_re[128];
	nmpps64f src_im[128];
	nmpps64fc dst[128];
	int i;

	for (i = 0; i < 128; ++i) {
		src_re[i] = (double)i;
		src_im[i] = (double)i + 3.0;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 128));

	for (i = 0; i < 128; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 127));

	for (i = 0; i < 127; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 64));

	for (i = 0; i < 64; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 63));

	for (i = 0; i < 63; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 32));

	for (i = 0; i < 32; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 31));

	for (i = 0; i < 31; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 16));

	for (i = 0; i < 16; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_64f(src_re, src_im, dst, 15));

	for (i = 0; i < 15; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 0.0, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE((double)i + 3.0, dst[i].im);
		dst[i].re = (double)-i;
		dst[i].im = (double)-i;
	}
}


/*
 // nmppsRealToCplx_32f
 */

TEST(tests_realtocplx, nmppsRealToCplx_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_32f((void*)0, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_32f((void*)0, (void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_32f((void*)0, (void*)1, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_32f((void*)1, (void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsRealToCplx_32f((void*)1, (void*)1, (void*)0, 1));
}

TEST(tests_realtocplx, nmppsRealToCplx_32f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRealToCplx_32f((void*)1, (void*)1, (void*)1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsRealToCplx_32f((void*)1, (void*)1, (void*)1, -1));
}

TEST(tests_realtocplx, nmppsRealToCplx_32f) {
	nmpps32f src_re[] ALIGNED = { 1.0f, 2.0f, 5.0f, };
	nmpps32f src_im[] ALIGNED = { 3.0f, 4.0f, 6.0f, };
	nmpps32fc dst[3] ALIGNED;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 3));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst[0].re);
	TEST_ASSERT_EQUAL_FLOAT(3.0f, dst[0].im);

	TEST_ASSERT_EQUAL_FLOAT(2.0f, dst[1].re);
	TEST_ASSERT_EQUAL_FLOAT(4.0f, dst[1].im);

	TEST_ASSERT_EQUAL_FLOAT(5.0f, dst[2].re);
	TEST_ASSERT_EQUAL_FLOAT(6.0f, dst[2].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_32f_re_is_null) {
	nmpps32f src_im[] ALIGNED = { 3.0f, 4.0f, 6.0f, };
	nmpps32fc dst[3] ALIGNED;

	dst[0].re = -1.0f;
	dst[1].re = -2.0f;
	dst[2].re = -3.0f;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(NULL, src_im, dst, 3));

	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst[0].re);
	TEST_ASSERT_EQUAL_FLOAT(3.0f, dst[0].im);

	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst[1].re);
	TEST_ASSERT_EQUAL_FLOAT(4.0f, dst[1].im);

	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst[2].re);
	TEST_ASSERT_EQUAL_FLOAT(6.0f, dst[2].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_32f_im_is_null) {
	nmpps32f src_re[] = { 1.0f, 2.0f, 5.0f, };
	nmpps32fc dst[3];

	dst[0].im = -1.0f;
	dst[1].im = -2.0f;
	dst[2].im = -3.0f;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, NULL, dst, 3));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst[0].re);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst[0].im);

	TEST_ASSERT_EQUAL_FLOAT(2.0f, dst[1].re);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst[1].im);

	TEST_ASSERT_EQUAL_FLOAT(5.0f, dst[2].re);
	TEST_ASSERT_EQUAL_FLOAT(0.0f, dst[2].im);
}

TEST(tests_realtocplx, nmppsRealToCplx_32f_one_element) {
	nmpps32f src_re[] = { 1.0f, };
	nmpps32f src_im[] = { 3.0f, };
	nmpps32fc dst[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 1));

	TEST_ASSERT_EQUAL_FLOAT(1.0f, dst[0].re);
	TEST_ASSERT_EQUAL_FLOAT(3.0f, dst[0].im);
}


TEST(tests_realtocplx, nmppsRealToCplx_32f_many_elements) {
	nmpps32f src_re[128] ALIGNED;
	nmpps32f src_im[128] ALIGNED;
	nmpps32fc dst[128] ALIGNED;
	int i;

	for (i = 0; i < 128; ++i) {
		src_re[i] = (float)i;
		src_im[i] = (float)i + 3.0f;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 128));

	for (i = 0; i < 128; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 127));

	for (i = 0; i < 127; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 64));

	for (i = 0; i < 64; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 63));

	for (i = 0; i < 63; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 32));

	for (i = 0; i < 32; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 31));

	for (i = 0; i < 31; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 16));

	for (i = 0; i < 16; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsRealToCplx_32f(src_re, src_im, dst, 15));

	for (i = 0; i < 15; ++i) {
		TEST_ASSERT_EQUAL_FLOAT((float)i + 0.0f, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT((float)i + 3.0f, dst[i].im);
		dst[i].re = (float)-i;
		dst[i].im = (float)-i;
	}
}


TEST_GROUP_RUNNER(tests_realtocplx) {
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f_re_is_null);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f_im_is_null);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f_one_element);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_64f_many_elements);

	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f_re_is_null);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f_im_is_null);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f_one_element);
	RUN_TEST_CASE(tests_realtocplx, nmppsRealToCplx_32f_many_elements);
}
