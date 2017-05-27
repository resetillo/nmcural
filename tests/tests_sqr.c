
#include "unity/unity_fixture.h"
#include "nmpps.h"


#define ALIGNED __attribute__((aligned))


TEST_GROUP(tests_sqr);

TEST_SETUP(tests_sqr) {}
TEST_TEAR_DOWN(tests_sqr) {}


//
// nmppsSqr_8u_Sfs
//

TEST(tests_sqr, nmppsSqr_8u_Sfs_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_8u_Sfs((void*)1, (void*)1,  0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_8u_Sfs((void*)1, (void*)1, -1, 0));
}

TEST(tests_sqr, nmppsSqr_8u_Sfs_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_8u_Sfs((void*)0, (void*)0, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_8u_Sfs((void*)0, (void*)1, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_8u_Sfs((void*)1, (void*)0, 1, 0));
}

TEST(tests_sqr, nmppsSqr_8u_Sfs_scale_factor0) {
    nmpps8u src[] ALIGNED      = {  4,  12,  30,  23, 0, 255, 128 };
    nmpps8u expected[] ALIGNED = { 16, 144, 255, 255, 0, 255, 255 };
    nmpps8u dst[7] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 7, 0));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 7);
}


TEST(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_is_pos) {
    nmpps8u src[] ALIGNED      = { 4, 10,  30, 200, 0, 255, 128 };
    nmpps8u expected[] ALIGNED = { 4, 25, 225, 255, 0, 255, 255 };
    nmpps8u dst[7] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 7, 2));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 7);
}


TEST(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_is_neg) {
    nmpps8u src[] ALIGNED      = {  4,   8,  30, 200, 255, 128, 0 };
    nmpps8u expected[] ALIGNED = { 32, 128, 255, 255, 255, 255, 0 };
    nmpps8u dst[7] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 7, -1));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 7);
}


TEST(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_saturating) {
    nmpps8u src[] ALIGNED      = {   0,   8,  30,   1 };
    nmpps8u expected[] ALIGNED = {   0, 255, 255, 255 };
    nmpps8u dst[4] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 4, -50));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 4);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 4, -32));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 4);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 4, -31));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 4);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 4, -8));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 4);
}

TEST(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_for_big) {
    nmpps8u src[] ALIGNED      = {   0,   8,  30, 200, 255, 128, };
    nmpps8u expected[] ALIGNED = {   0,   0,   3, 156, 254,  64, };
    nmpps8u dst[6] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_8u_Sfs(src, dst, 6, 8));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 6);
}

//
// nmppsSqr_16s_Sfs
//

TEST(tests_sqr, nmppsSqr_16s_Sfs_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_16s_Sfs((void*)1, (void*)1,  0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_16s_Sfs((void*)1, (void*)1, -1, 0));
}

TEST(tests_sqr, nmppsSqr_16s_Sfs_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_16s_Sfs((void*)0, (void*)0, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_16s_Sfs((void*)0, (void*)1, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_16s_Sfs((void*)1, (void*)0, 1, 0));
}

TEST(tests_sqr, nmppsSqr_16s_Sfs_scale_factor0) {
    nmpps16s src[] ALIGNED      = { -2,  4,  10,  30,   200, 32767, -1, -32768 };
    nmpps16s expected[] ALIGNED = {  4, 16, 100, 900, 32767, 32767,  1, 32767 };
    nmpps16s dst[8] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 8, 0));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 8);
}


TEST(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_is_pos) {
    nmpps16s src[] ALIGNED      = { 4, 10,  30,   200, -1 };
    nmpps16s expected[] ALIGNED = { 4, 25, 225, 10000,  0 };
    nmpps16s dst[5] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 5, 2));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 5);
}


TEST(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_is_neg) {
    nmpps16s src[] ALIGNED      = {  4,   8,   30,   200, 32767, -32768, 0 };
    nmpps16s expected[] ALIGNED = { 64, 256, 3600, 32767, 32767,  32767, 0 };
    nmpps16s dst[7] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 7, -2));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 7);
}


TEST(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_saturating) {
    nmpps16s src[] ALIGNED      = { 0,     1,     4,    30, 32767,    -1 };
    nmpps16s expected[] ALIGNED = { 0, 32767, 32767, 32767, 32767, 32767 };
    nmpps16s dst[6] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 6, -50));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 6);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 6, -32));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 6);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 6, -31));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 6);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 6, -15));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 6);
}

TEST(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_for_big) {
    nmpps16s src[] ALIGNED      = { 0, 32767, 16384, };
    nmpps16s expected[] ALIGNED = { 0, 16383,  4096, };
    nmpps16s dst[3] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16s_Sfs(src, dst, 3, 16));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 3);
}

//
// nmppsSqr_16u_Sfs
//

TEST(tests_sqr, nmppsSqr_16u_Sfs_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_16u_Sfs((void*)1, (void*)1,  0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_16u_Sfs((void*)1, (void*)1, -1, 0));
}

TEST(tests_sqr, nmppsSqr_16u_Sfs_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_16u_Sfs((void*)0, (void*)0, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_16u_Sfs((void*)0, (void*)1, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_16u_Sfs((void*)1, (void*)0, 1, 0));
}

TEST(tests_sqr, nmppsSqr_16u_Sfs_scale_factor0) {
    nmpps16u src[] ALIGNED      = {  0, 2,  4,  10,  30,   200, 65535 };
    nmpps16u expected[] ALIGNED = {  0, 4, 16, 100, 900, 40000, 65535 };
    nmpps16u dst[7] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 7, 0));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 7);
}


TEST(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_is_pos) {
    nmpps16u src[] ALIGNED      = { 0, 4, 10,  30,   200 };
    nmpps16u expected[] ALIGNED = { 0, 4, 25, 225, 10000 };
    nmpps16u dst[5] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 5, 2));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 5);
}


TEST(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_is_neg) {
    nmpps16u src[] ALIGNED      = {  4,   8,   30,   200, 0 };
    nmpps16u expected[] ALIGNED = { 32, 128, 1800, 65535, 0 };
    nmpps16u dst[5] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 5, -1));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 5);
}


TEST(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_saturating) {
    nmpps16u src[] ALIGNED      = {     1,     4,    30, 0, 65535, 32768, };
    nmpps16u expected[] ALIGNED = { 65535, 65535, 65535, 0, 65535, 65535, };
    nmpps16u dst[6] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 6, -50));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 6);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 6, -32));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 6);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 6, -31));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 6);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 6, -16));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, dst, 6);
}

TEST(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_for_big) {
    nmpps16u src[] ALIGNED      = { 0, 65535, 16384, };
    nmpps16u expected[] ALIGNED = { 0, 65534,  4096, };
    nmpps16u dst[3] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16u_Sfs(src, dst, 3, 16));
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected, dst, 3);
}

//
// nmppsSqr_32f
//

TEST(tests_sqr, nmppsSqr_32f_nmppsStsSizeErr) {
	// negative case
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_32f((void*)1, (void*)1, -1));
	// zero case
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_32f((void*)1, (void*)1, 0));
}

TEST(tests_sqr, nmppsSqr_32f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_32f((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_32f((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_32f((void*)1, (void*)0, 1));
}

TEST(tests_sqr, nmppsSqr_32f) {
    nmpps32f src[] ALIGNED      = {   -224.75f,        3104.89f,       1222.991f, 		  0.0f   };
    nmpps32f expected[] ALIGNED = {  50512.5625f,   9640341.9121f,  1495706.986081f,  777777.777f };
    nmpps32f dst[4] ALIGNED     = { 777777.777f,     777777.777f,    777777.777f,     777777.777f };

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32f(src, dst, 3));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, dst, 4);
}

TEST(tests_sqr, nmppsSqr_32f_one_element) {
    nmpps32f src[] ALIGNED      = {   -224.75f,   };
    nmpps32f expected[] ALIGNED = {  50512.5625f, };
    nmpps32f dst[1] ALIGNED     = { 777777.777f,  };

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32f(src, dst, 1));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, dst, 1);
}

TEST(tests_sqr, nmppsSqr_32f_many_elements) {
    nmpps32f src[80] ALIGNED;
    nmpps32f expected[80] ALIGNED;
    nmpps32f dst[80] ALIGNED;
    int i;

    for (i = 0; i < 80; ++i) {
    	src[i] = (nmpps32f)i;
    	expected[i] = src[i] * src[i];
    	dst[i] = 77777.7;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32f(src, dst, 16));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, dst, 16);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32f(src, dst, 32));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, dst, 32);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32f(src, dst, 79));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, dst, 79);
}

//
// nmppsSqr_64f
//

TEST(tests_sqr, nmppsSqr_64f_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_64f((void*)1, (void*)1, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_64f((void*)1, (void*)1, 0));
}

TEST(tests_sqr, nmppsSqr_64f_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_64f((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_64f((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_64f((void*)1, (void*)0, 1));
}

TEST(tests_sqr, nmppsSqr_64f) {
    nmpps64f src[3]      = {  -224.75,        3104.89,       1222.991,    };
    nmpps64f expected[3] = { 50512.5625,   9640341.9121,  1495706.986081, };
    nmpps64f dst[3];

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64f(src, dst, 3));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, dst, 3);
}

TEST(tests_sqr, nmppsSqr_64f_one_element) {
    nmpps64f src[1]      = { 3104.89,      };
    nmpps64f expected[1] = { 9640341.9121, };
    nmpps64f dst[1];

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64f(src, dst, 1));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, dst, 1);
}

TEST(tests_sqr, nmppsSqr_64f_many_elements) {
    nmpps64f src[80];
    nmpps64f expected[80];
    nmpps64f dst[80];
    int i;

    for (i = 0; i < 80; ++i) {
    	src[i] = (nmpps64f)i;
    	expected[i] = src[i] * src[i];
    	dst[i] = 77777.7;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64f(src, dst, 16));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, dst, 16);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64f(src, dst, 32));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, dst, 32);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64f(src, dst, 79));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, dst, 79);
}

//
// nmppsSqr_16sc_Sfs
//

TEST(tests_sqr, nmppsSqr_16sc_Sfs_nmppsStsSizeErr) {
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_16sc_Sfs((void*)1, (void*)1,  0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_16sc_Sfs((void*)1, (void*)1, -1, 0));
}

TEST(tests_sqr, nmppsSqr_16sc_Sfs_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr,  nmppsSqr_16sc_Sfs((void*)0, (void*)0, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr,  nmppsSqr_16sc_Sfs((void*)0, (void*)1, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr,  nmppsSqr_16sc_Sfs((void*)1, (void*)0, 1, 0));
}

TEST(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor0) {
    nmpps16sc src[] ALIGNED        = {{0, 0}, { +7,  +3}, {-3,  +4}};
    nmpps16sc expected[] ALIGNED   = {{0, 0}, {+40, +42}, {-7, -24}};
    nmpps16sc dst[3] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16sc_Sfs(src, dst, 3, 0));

    TEST_ASSERT_EQUAL_INT16(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_INT16(expected[0].im, dst[0].im);

    TEST_ASSERT_EQUAL_INT16(expected[1].re, dst[1].re);
    TEST_ASSERT_EQUAL_INT16(expected[1].im, dst[1].im);

    TEST_ASSERT_EQUAL_INT16(expected[2].re, dst[2].re);
    TEST_ASSERT_EQUAL_INT16(expected[2].im, dst[2].im);
}

TEST(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor_is_pos) {
    nmpps16sc src[] ALIGNED        = {{ +7,  +3}, {-3,  +4}, { 2000,   120}, {   120,  -2000}, {   120,   2000}};
    nmpps16sc expected[] ALIGNED   = {{+20, +21}, {-4, -12}, {32767, 32767}, {-32768, -32768}, {-32768, +32767}};
    nmpps16sc dst[5] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16sc_Sfs(src, dst, 5, 1));

    TEST_ASSERT_EQUAL_INT16(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_INT16(expected[0].im, dst[0].im);

    TEST_ASSERT_EQUAL_INT16(expected[1].re, dst[1].re);
    TEST_ASSERT_EQUAL_INT16(expected[1].im, dst[1].im);

    TEST_ASSERT_EQUAL_INT16(expected[2].re, dst[2].re);
    TEST_ASSERT_EQUAL_INT16(expected[2].im, dst[2].im);

    TEST_ASSERT_EQUAL_INT16(expected[3].re, dst[3].re);
    TEST_ASSERT_EQUAL_INT16(expected[3].im, dst[3].im);

    TEST_ASSERT_EQUAL_INT16(expected[4].re, dst[4].re);
    TEST_ASSERT_EQUAL_INT16(expected[4].im, dst[4].im);
}

TEST(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor_is_neg) {
    nmpps16sc src[] ALIGNED        = {{ +7,  +3}, { -3,  +4}, { 2000,   120}, {   120,  -2000}, {   120,   2000}};
    nmpps16sc expected[] ALIGNED   = {{+80, +84}, {-14, -48}, {32767, 32767}, {-32768, -32768}, {-32768, +32767}};
    nmpps16sc dst[5] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16sc_Sfs(src, dst, 5, -1));

    TEST_ASSERT_EQUAL_INT16(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_INT16(expected[0].im, dst[0].im);

    TEST_ASSERT_EQUAL_INT16(expected[1].re, dst[1].re);
    TEST_ASSERT_EQUAL_INT16(expected[1].im, dst[1].im);

    TEST_ASSERT_EQUAL_INT16(expected[2].re, dst[2].re);
    TEST_ASSERT_EQUAL_INT16(expected[2].im, dst[2].im);

    TEST_ASSERT_EQUAL_INT16(expected[3].re, dst[3].re);
    TEST_ASSERT_EQUAL_INT16(expected[3].im, dst[3].im);

    TEST_ASSERT_EQUAL_INT16(expected[4].re, dst[4].re);
    TEST_ASSERT_EQUAL_INT16(expected[4].im, dst[4].im);
}

TEST(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor_saturating) {
    nmpps16sc src[] ALIGNED        = {  { +7,    +3}, {    -3,     +4}, { 2000,   120}, {   120,  -2000}, {   120,   2000}};
    nmpps16sc expected[] ALIGNED   = {{32767, 32767}, {-32768, -32768}, {32767, 32767}, {-32768, -32768}, {-32768, +32767}};
    nmpps16sc dst[5] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_16sc_Sfs(src, dst, 5, -16));

    TEST_ASSERT_EQUAL_INT16(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_INT16(expected[0].im, dst[0].im);

    TEST_ASSERT_EQUAL_INT16(expected[1].re, dst[1].re);
    TEST_ASSERT_EQUAL_INT16(expected[1].im, dst[1].im);

    TEST_ASSERT_EQUAL_INT16(expected[2].re, dst[2].re);
    TEST_ASSERT_EQUAL_INT16(expected[2].im, dst[2].im);

    TEST_ASSERT_EQUAL_INT16(expected[3].re, dst[3].re);
    TEST_ASSERT_EQUAL_INT16(expected[3].im, dst[3].im);

    TEST_ASSERT_EQUAL_INT16(expected[4].re, dst[4].re);
    TEST_ASSERT_EQUAL_INT16(expected[4].im, dst[4].im);
}

//
// nmppsSqr_32fc
//

TEST(tests_sqr, nmppsSqr_32fc_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_32fc((void*)1, (void*)1, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_32fc((void*)1, (void*)1, 0));
}

TEST(tests_sqr, nmppsSqr_32fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_32fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_32fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_32fc((void*)1, (void*)0, 1));
}

TEST(tests_sqr, nmppsSqr_32fc) {
    nmpps32fc src[] ALIGNED        = {{ +7.0f,  +3.0f}, { -5.0f,  +8.0f}};
    nmpps32fc expected[] ALIGNED   = {{+40.0f, +42.0f}, {-39.0,  -80.0}};
    nmpps32fc dst[2] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32fc(src, dst, 2));

    TEST_ASSERT_EQUAL_FLOAT(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_FLOAT(expected[0].im, dst[0].im);

    TEST_ASSERT_EQUAL_FLOAT(expected[1].re, dst[1].re);
    TEST_ASSERT_EQUAL_FLOAT(expected[1].im, dst[1].im);
}

TEST(tests_sqr, nmppsSqr_32fc_one_element) {
    nmpps32fc src[] ALIGNED        = {{ +7.0f,  +3.0f}, };
    nmpps32fc expected[] ALIGNED   = {{+40.0f, +42.0f}, };
    nmpps32fc dst[1] ALIGNED;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32fc(src, dst, 1));

    TEST_ASSERT_EQUAL_FLOAT(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_FLOAT(expected[0].im, dst[0].im);
}

TEST(tests_sqr, nmppsSqr_32fc_many_elements) {
    nmpps32fc src[80] ALIGNED;
    nmpps32fc expected[80] ALIGNED;
    nmpps32fc dst[80] ALIGNED;
    int i;

    for (i = 0; i < 80; ++i) {
    	src[i].re = (nmpps32f)i;
    	src[i].im = (nmpps32f)i + i % 12;
    	expected[i].re = (src[i].re * src[i].re) - (src[i].im * src[i].im);
    	expected[i].im = 2.0 * src[i].re * src[i].im;
    	dst[i].re = 777777.7f;
    	dst[i].im = 777777.7f;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32fc(src, dst, 16));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY((void*)expected, (void*)dst, 32);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32fc(src, dst, 32));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY((void*)expected, (void*)dst, 64);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_32fc(src, dst, 80));
	TEST_ASSERT_EQUAL_FLOAT_ARRAY((void*)expected, (void*)dst, 160);
}

//
// nmppsSqr_64fc
//

TEST(tests_sqr, nmppsSqr_64fc_nmppsStsSizeErr) {
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_64fc((void*)1, (void*)1, -1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqr_64fc((void*)1, (void*)1, 0));
}

TEST(tests_sqr, nmppsSqr_64fc_nmppsStsNullPtrErr) {
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_64fc((void*)0, (void*)0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_64fc((void*)0, (void*)1, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqr_64fc((void*)1, (void*)0, 1));
}

TEST(tests_sqr, nmppsSqr_64fc) {
    nmpps64fc src[]         = {{ +7.0,  +3.0}, { -5.0,  +8.0}};
    nmpps64fc expected[]    = {{+40.0, +42.0}, {-39.0, -80.0}};
    nmpps64fc dst[2];

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64fc(src, dst, 2));

    TEST_ASSERT_EQUAL_DOUBLE(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_DOUBLE(expected[0].im, dst[0].im);

    TEST_ASSERT_EQUAL_DOUBLE(expected[1].re, dst[1].re);
    TEST_ASSERT_EQUAL_DOUBLE(expected[1].im, dst[1].im);
}

TEST(tests_sqr, nmppsSqr_64fc_one_element) {
    nmpps64fc src[]         = {{ -5.0,  +8.0}, };
    nmpps64fc expected[]    = {{-39.0, -80.0}, };
    nmpps64fc dst[1];

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64fc(src, dst, 1));

    TEST_ASSERT_EQUAL_DOUBLE(expected[0].re, dst[0].re);
    TEST_ASSERT_EQUAL_DOUBLE(expected[0].im, dst[0].im);
}

TEST(tests_sqr, nmppsSqr_64fc_many_elements) {
    nmpps64fc src[80];
    nmpps64fc expected[80];
    nmpps64fc dst[80];
    int i;

    for (i = 0; i < 80; ++i) {
    	src[i].re = (nmpps64f)i;
    	src[i].im = (nmpps64f)i + i % 12;
    	expected[i].re = (src[i].re * src[i].re) - (src[i].im * src[i].im);
    	expected[i].im = 2.0 * src[i].re * src[i].im;
    	dst[i].re = 777777.7;
    	dst[i].im = 777777.7;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64fc(src, dst, 16));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY((void*)expected, (void*)dst, 32);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64fc(src, dst, 41));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY((void*)expected, (void*)dst, 82);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsSqr_64fc(src, dst, 80));
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY((void*)expected, (void*)dst, 160);
}


TEST_GROUP_RUNNER(tests_sqr) {
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_scale_factor0);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_is_pos);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_is_neg);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_saturating);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_8u_Sfs_scale_factor_for_big);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_scale_factor0);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_is_pos);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_is_neg);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_saturating);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16s_Sfs_scale_factor_for_big);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_scale_factor0);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_is_pos);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_is_neg);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_saturating);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16u_Sfs_scale_factor_for_big);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_32f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32f);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32f_one_element);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32f_many_elements);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_64f_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64f_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64f);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64f_one_element);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64f_many_elements);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_16sc_Sfs_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16sc_Sfs_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor0);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor_is_pos);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor_is_neg);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_16sc_Sfs_scale_factor_saturating);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_32fc_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32fc_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32fc);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32fc_one_element);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_32fc_many_elements);

    RUN_TEST_CASE(tests_sqr, nmppsSqr_64fc_nmppsStsSizeErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64fc_nmppsStsNullPtrErr);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64fc);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64fc_one_element);
    RUN_TEST_CASE(tests_sqr, nmppsSqr_64fc_many_elements);
}
