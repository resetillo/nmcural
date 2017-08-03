
#include "unity/unity_fixture.h"
#include "nmpps.h"


#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_mean);

TEST_SETUP(tests_mean) {}
TEST_TEAR_DOWN(tests_mean) {}


/*
 * nmppsMean_16s_Sfs
 */

TEST(tests_mean, nmppsMean_16s_Sfs_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_16s_Sfs((void*)0, 1, (void*)0, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_16s_Sfs((void*)0, 1, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_16s_Sfs((void*)1, 1, (void*)0, 0));
}

TEST(tests_mean, nmppsMean_16s_Sfs_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_16s_Sfs((void*)1,  0, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_16s_Sfs((void*)1, -1, (void*)1, 0));
}

TEST(tests_mean, nmppsMean_16s_Sfs) {
	nmpps16s src[] ALIGNED = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	nmpps16s dst;
	nmpps16s unused = 0xBA5E;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_16s_Sfs(src, 10, &dst, -1));

	TEST_ASSERT_EQUAL(11, dst); // 5.5 (11 * 2^-1)
	TEST_ASSERT(unused == 0xBA5E);
}

TEST(tests_mean, nmppsMean_16s_Sfs_one_element) {
	nmpps16s src[] ALIGNED = { 1010 };
	nmpps16s dst;
	nmpps16s unused = 0xBA5E;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_16s_Sfs(src, 1, &dst, 0));

	TEST_ASSERT_EQUAL(1010, dst);
	TEST_ASSERT(unused == 0xBA5E);
}

TEST(tests_mean, nmppsMean_16s_Sfs_many_elements) {
	nmpps16s src[] ALIGNED = {  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,};
	nmpps16s dst;
	nmpps16s unused = 0xBA5E;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_16s_Sfs(src, 90, &dst, 1));

	TEST_ASSERT_EQUAL(4, dst);
	TEST_ASSERT(unused == 0xBA5E);
}

TEST(tests_mean, nmppsMean_16s_Sfs_over_saturate) {
	nmpps16s src[] ALIGNED = { 1010 };
	nmpps16s dst;
	nmpps16s unused = 0xBA5E;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_16s_Sfs(src, 1, &dst, -32));

	TEST_ASSERT_EQUAL(32767, dst);
	TEST_ASSERT(unused == 0xBA5E);
}

TEST(tests_mean, nmppsMean_16s_Sfs_down_saturate) {
	nmpps16s src[] ALIGNED = { 32767 };
	nmpps16s dst;
	nmpps16s unused = 0xBA5E;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_16s_Sfs(src, 1, &dst, 32));

	TEST_ASSERT_EQUAL(0, dst);
	TEST_ASSERT(unused == 0xBA5E);
}

/*
 * nmppsMean_32f
 */

TEST(tests_mean, nmppsMean_32f_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_32f((void*)0, 1, (void*)0, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_32f((void*)0, 1, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_32f((void*)1, 1, (void*)0, 0));
}

TEST(tests_mean, nmppsMean_32f_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_32f((void*)1,  0, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_32f((void*)1, -1, (void*)1, 0));
}

TEST(tests_mean, nmppsMean_32f) {
	nmpps32f src[]  ALIGNED = { 1.0f, 2.0f, 3.0f, 4.0f };
	nmpps32f dst;
	nmpps32f unused = 1.0f;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_32f(src, 4, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT(2.5f, dst);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, unused);
}

TEST(tests_mean, nmppsMean_32f_one_element) {
	nmpps32f src[]  ALIGNED = { 10.10f, };
	nmpps32f dst;
	nmpps32f unused = 1.0f;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_32f(src, 1, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT(10.10f, dst);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, unused);
}

TEST(tests_mean, nmppsMean_32f_many_elements) {
	nmpps32f src[]  ALIGNED = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
								11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
								21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f,
								31.0f, 32.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
								11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
								21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f,
								31.0f, 32.0f, 33.0f };
	nmpps32f dst;
	nmpps32f unused = 1.0f;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_32f(src, 65, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT(16.753846153846155f, dst);
	TEST_ASSERT_EQUAL_FLOAT(1.0f, unused);
}

/*
 * nmppsMean_64f
 */

TEST(tests_mean, nmppsMean_64f_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_64f((void*)0, 1, (void*)0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_64f((void*)0, 1, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_64f((void*)1, 1, (void*)0));
}

TEST(tests_mean, nmppsMean_64f_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_64f((void*)1,  0, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_64f((void*)1, -1, (void*)1));
}

TEST(tests_mean, nmppsMean_64f) {
	nmpps64f src[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
					11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
					21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
					31.0, 32.0 };
	nmpps64f dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_64f(src, 32, &dst));

	TEST_ASSERT_EQUAL_DOUBLE(16.5, dst);
}

TEST(tests_mean, nmppsMean_64f_one_element) {
	nmpps64f src[] = { 3232.32 };
	nmpps64f dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_64f(src, 1, &dst));

	TEST_ASSERT_EQUAL_DOUBLE(3232.32, dst);
}

TEST(tests_mean, nmppsMean_64f_many_elements) {
	nmpps64f src[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
					11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
					21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
					31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
					11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
					21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
					31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
					11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
					21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
					31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
					11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
					21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
					31.0, 32.0, 33.0, 34.0, 36.0};
	nmpps64f dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_64f(src, 131, &dst));

	TEST_ASSERT_EQUAL_DOUBLE(16.908396946564885, dst);
}


/*
 * nmppsMean_32fc
 */

TEST(tests_mean, nmppsMean_32fc_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_32fc((void*)0, 1, (void*)0, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_32fc((void*)0, 1, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_32fc((void*)1, 1, (void*)0, 0));
}

TEST(tests_mean, nmppsMean_32fc_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_32fc((void*)1,  0, (void*)1, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_32fc((void*)1, -1, (void*)1, 0));
}

TEST(tests_mean, nmppsMean_32fc) {
	nmpps32fc src[]  ALIGNED = { {1.0f, 2.0f}, {3.0f, 4.0f}, {1.0f, 2.0f}, {3.0f, 4.0f} };
	nmpps32fc dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_32fc(src, 4, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.0f, dst.re, "Real");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(3.0f, dst.im, "Image");
}

TEST(tests_mean, nmppsMean_32fc_one_element) {
	nmpps32fc src[]  ALIGNED = { {9.9f, 12.1f}, };
	nmpps32fc dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_32fc(src, 1, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(9.9f, dst.re, "Real");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(12.10f, dst.im, "Image");
}

TEST(tests_mean, nmppsMean_32fc_many_elements) {
	nmpps32fc src[]  ALIGNED = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f},
								{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.9f, 12.1f},};
	nmpps32fc dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_32fc(src, 65, &dst, 0));

	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(5.013846153846154f, dst.re, "Real");
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE(6.032307692307692f, dst.im, "Image");
}

/*
 * nmppsMean_64fc
 */

TEST(tests_mean, nmppsMean_64fc_nmppsStsNullPtrErr) {
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_64fc((void*)0, 1, (void*)0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_64fc((void*)0, 1, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMean_64fc((void*)1, 1, (void*)0));
}

TEST(tests_mean, nmppsMean_64fc_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_64fc((void*)1,  0, (void*)1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMean_64fc((void*)1, -1, (void*)1));
}

TEST(tests_mean, nmppsMean_64fc) {
	nmpps64fc src[] = { {1.0, 2.0}, {3.0, 4.0}, {1.0, 2.0}, {3.0, 4.0} };
	nmpps64fc dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_64fc(src, 4, &dst));

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(2.0, dst.re, "Real");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.0, dst.im, "Image");
}

TEST(tests_mean, nmppsMean_64fc_one_element) {
	nmpps64fc src[]  ALIGNED = { {9.9, 12.1}, };
	nmpps64fc dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_64fc(src, 1, &dst));

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(9.9, dst.re, "Real");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(12.10, dst.im, "Image");
}

TEST(tests_mean, nmppsMean_64fc_many_elements) {
	nmpps64fc src[] = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0},
						{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.9, 12.1},};
	nmpps64fc dst;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMean_64fc(src, 65, &dst));

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(5.013846153846154, dst.re, "Real");
	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(6.032307692307692, dst.im, "Image");
}


TEST_GROUP_RUNNER(tests_mean) {
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs);
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs_one_element);
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs_many_elements);
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs_over_saturate);
	RUN_TEST_CASE(tests_mean, nmppsMean_16s_Sfs_down_saturate);

	RUN_TEST_CASE(tests_mean, nmppsMean_32f_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_32f_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_32f);
	RUN_TEST_CASE(tests_mean, nmppsMean_32f_one_element);
	RUN_TEST_CASE(tests_mean, nmppsMean_32f_many_elements);

	RUN_TEST_CASE(tests_mean, nmppsMean_64f_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_64f_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_64f);
	RUN_TEST_CASE(tests_mean, nmppsMean_64f_one_element);
	RUN_TEST_CASE(tests_mean, nmppsMean_64f_many_elements);

	RUN_TEST_CASE(tests_mean, nmppsMean_32fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_32fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_32fc);
	RUN_TEST_CASE(tests_mean, nmppsMean_32fc_one_element);
	RUN_TEST_CASE(tests_mean, nmppsMean_32fc_many_elements);

	RUN_TEST_CASE(tests_mean, nmppsMean_64fc_nmppsStsNullPtrErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_64fc_nmppsStsSizeErr);
	RUN_TEST_CASE(tests_mean, nmppsMean_64fc);
	RUN_TEST_CASE(tests_mean, nmppsMean_64fc_one_element);
	RUN_TEST_CASE(tests_mean, nmppsMean_64fc_many_elements);
}
