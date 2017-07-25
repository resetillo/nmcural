/**
 * @file tests_conj.c
 *
 * @brief
 */

#include "unity/unity_fixture.h"
#include "nmpps.h"


TEST_GROUP(tests_conj);

TEST_SETUP(tests_conj) {}
TEST_TEAR_DOWN(tests_conj) {}


//
// nmppsConj_32fc
//

TEST(tests_conj, nmppsConj_32fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsConj_32fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsConj_32fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsConj_32fc((void*)1, (void*)0, 1));
}

TEST(tests_conj, nmppsConj_32fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsConj_32fc((void*)1, (void*)1,  0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsConj_32fc((void*)1, (void*)1, -1));
}

TEST(tests_conj, nmppsConj_32fc_one_element) {
	nmpps32fc src[1] = { {5.0f, -4.0f} };
	nmpps32fc dst[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsConj_32fc(src, dst, 1));

	TEST_ASSERT_EQUAL_FLOAT( 5.0f, dst[0].re);
	TEST_ASSERT_EQUAL_FLOAT( 4.0f, dst[0].im);
}

TEST(tests_conj, nmppsConj_32fc) {
	nmpps32fc src[] = { {0.0f, 0.0f}, {5.0f, -4.0f}, {-6.0f, 5.0f}, {-10.0f, -4.0f}, {8.9f, 9.8f}};
	nmpps32fc dst[5];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsConj_32fc(src, dst, 5));

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 0.0f, dst[0].re, "dst[0].re");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 0.0f, dst[0].im, "dst[0].im");

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 5.0f, dst[1].re, "dst[1].re");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 4.0f, dst[1].im, "dst[1].im");

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-6.0f, dst[2].re, "dst[2].re");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-5.0f, dst[2].im, "dst[2].im");

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-10.0f, dst[3].re, "dst[3].re");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(  4.0f, dst[3].im, "dst[3].im");

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 8.9f, dst[4].re, "dst[4].re");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-9.8f, dst[4].im, "dst[4].im");
}

TEST(tests_conj, nmppsConj_32fc_many_elements) {
	nmpps32fc src[54];
	nmpps32fc dst[54];
	int i;

	for (i = 0; i < 54; ++i) {
		src[i].re = (float)+i;
		src[i].im = (float)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsConj_32fc(src, dst, 54));

	for (i = 0; i < 54; ++i) {
		TEST_ASSERT_EQUAL_FLOAT( src[i].re, dst[i].re);
		TEST_ASSERT_EQUAL_FLOAT(-src[i].im, dst[i].im);
	}
}


//
// nmppsConj_64fc
//

TEST(tests_conj, nmppsConj_64fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsConj_64fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsConj_64fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsConj_64fc((void*)1, (void*)0, 1));
}

TEST(tests_conj, nmppsConj_64fc_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsConj_64fc((void*)1, (void*)1,  0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsConj_64fc((void*)1, (void*)1, -1));
}

TEST(tests_conj, nmppsConj_64fc_one_element) {
	nmpps64fc src[1] = { {5.0, -4.0} };
	nmpps64fc dst[1];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsConj_64fc(src, dst, 1));

	TEST_ASSERT_EQUAL_DOUBLE( 5.0, dst[0].re);
	TEST_ASSERT_EQUAL_DOUBLE( 4.0, dst[0].im);
}

TEST(tests_conj, nmppsConj_64fc) {
	nmpps64fc src[] = { {0.0, 0.0}, {5.0, -4.0}, {-6.0, 5.0}, {-10.0, -4.0}, {8.9, 9.8}};
	nmpps64fc dst[5];

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsConj_64fc(src, dst, 5));

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( 0.0, dst[0].re, "dst[0].re");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( 0.0, dst[0].im, "dst[0].im");

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( 5.0, dst[1].re, "dst[1].re");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( 4.0, dst[1].im, "dst[1].im");

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(-6.0, dst[2].re, "dst[2].re");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(-5.0, dst[2].im, "dst[2].im");

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(-10.0, dst[3].re, "dst[3].re");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(  4.0, dst[3].im, "dst[3].im");

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( 8.9, dst[4].re, "dst[4].re");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(-9.8, dst[4].im, "dst[4].im");
}

TEST(tests_conj, nmppsConj_64fc_many_elements) {
	nmpps64fc src[54];
	nmpps64fc dst[54];
	int i;

	for (i = 0; i < 54; ++i) {
		src[i].re = (double)+i;
		src[i].im = (double)-i;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsConj_64fc(src, dst, 54));

	for (i = 0; i < 54; ++i) {
		TEST_ASSERT_EQUAL_DOUBLE( src[i].re, dst[i].re);
		TEST_ASSERT_EQUAL_DOUBLE(-src[i].im, dst[i].im);
	}
}


TEST_GROUP_RUNNER(tests_conj) {
    RUN_TEST_CASE(tests_conj, nmppsConj_32fc_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_conj, nmppsConj_32fc_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_conj, nmppsConj_32fc_one_element);
    RUN_TEST_CASE(tests_conj, nmppsConj_32fc);
    RUN_TEST_CASE(tests_conj, nmppsConj_32fc_many_elements);

    RUN_TEST_CASE(tests_conj, nmppsConj_64fc_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_conj, nmppsConj_64fc_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_conj, nmppsConj_64fc_one_element);
    RUN_TEST_CASE(tests_conj, nmppsConj_64fc);
    RUN_TEST_CASE(tests_conj, nmppsConj_64fc_many_elements);
}
