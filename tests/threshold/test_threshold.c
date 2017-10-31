
#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_threshold);

TEST_SETUP(tests_threshold){};
TEST_TEAR_DOWN(tests_threshold){}


/// nmppsThreshold_16s
TEST(tests_threshold, test_nmppsThreshold_16s_null_ptr){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_16s(NULL, &a, 1, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_16s(&a, NULL, 1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_16s_err_size){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_16s(&a, &a, 0, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_16s(&a, &a, -1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_16s_err_cmp_op){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsBadArgErr, nmppsThreshold_16s(&a, &a, 0, 1, nmppsCmpEq));
}


TEST(tests_threshold, test_nmppsThreshold_16s_less){
    int i = 0;
    nmpps16s src[150]    __attribute__ ((aligned (2)));
    nmpps16s dst[150]    __attribute__ ((aligned (2)));
    nmpps16s etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = 38;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[20] = 37;  etalon[20] = 38;
    src[21] = 123; etalon[21] = 123;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 38;
    src[24] = 39;  etalon[24] = 39;
    src[25] = 1;   etalon[25] = 38;
    src[26] = 100; etalon[26] = 100;
    src[27] = -3;  etalon[27] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 28, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = 38;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[20] = 37;  etalon[20] = 38;
    src[21] = 123; etalon[21] = 123;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 38;
    src[24] = 39;  etalon[24] = 39;
    src[25] = 1;   etalon[25] = 38;
    src[26] = -3;  etalon[26] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 27, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 120; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[120] = 37;  etalon[120] = 38;
    src[121] = 123; etalon[121] = 123;
    src[122] = 38;  etalon[122] = 38;
    src[123] = 0;   etalon[123] = 38;
    src[124] = 39;  etalon[124] = 39;
    src[125] = 1;   etalon[125] = 38;
    src[126] = -3;  etalon[126] = 38;
    src[127] = -38; etalon[127] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 128, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 148, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[148] = -123; etalon[148] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 149, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    src[0] = -123; etalon[0] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 1, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }
}



/// nmppsThreshold_32s
TEST(tests_threshold, test_nmppsThreshold_32s_null_ptr){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_32s(NULL, &a, 1, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_32s(&a, NULL, 1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_32s_err_size){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_32s(&a, &a, 0, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_32s(&a, &a, -1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_32s_err_cmp_op){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsBadArgErr, nmppsThreshold_32s(&a, &a, 0, 1, nmppsCmpEq));
}

TEST(tests_threshold, test_nmppsThreshold_32s_less){
    int i = 0;
    nmpps32s src[150]    __attribute__ ((aligned (2)));
    nmpps32s dst[150]    __attribute__ ((aligned (2)));
    nmpps32s etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = 38;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[20] = 37;  etalon[20] = 38;
    src[21] = 123; etalon[21] = 123;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 38;
    src[24] = 39;  etalon[24] = 39;
    src[25] = 1;   etalon[25] = 38;
    src[26] = 100; etalon[26] = 100;
    src[27] = -3;  etalon[27] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 28, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = 38;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[20] = 37;  etalon[20] = 38;
    src[21] = 123; etalon[21] = 123;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 38;
    src[24] = 39;  etalon[24] = 39;
    src[25] = 1;   etalon[25] = 38;
    src[26] = -3;  etalon[26] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 27, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 120; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[120] = 37;  etalon[120] = 38;
    src[121] = 123; etalon[121] = 123;
    src[122] = 38;  etalon[122] = 38;
    src[123] = 0;   etalon[123] = 38;
    src[124] = 39;  etalon[124] = 39;
    src[125] = 1;   etalon[125] = 38;
    src[126] = -3;  etalon[126] = 38;
    src[127] = -38; etalon[127] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 128, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 148, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i - 1111;
    	etalon[i] = -38;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 148, -38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = i + 38;
    }

    src[148] = -123; etalon[148] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 149, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    src[0] = -123; etalon[0] = 38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 1, 38, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }
}

/// nmppsThreshold_32f
TEST(tests_threshold, test_nmppsThreshold_32f_null_ptr){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_32f(NULL, &a, 1, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_32f(&a, NULL, 1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_32f_err_size){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_32f(&a, &a, 0, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_32f(&a, &a, -1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_32f_err_cmp_op){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsBadArgErr, nmppsThreshold_32f(&a, &a, 0, 1, nmppsCmpEq));
}

TEST(tests_threshold, test_nmppsThreshold_32f_less){
    int i = 0;
    nmpps32f src[150]    __attribute__ ((aligned (2)));
    nmpps32f dst[150]    __attribute__ ((aligned (2)));
    nmpps32f etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i / 3;
    	etalon[i] = i / 3;
    }

    for(; i < 20; i++){
    	src[i] = i - 138.1;
    	etalon[i] = -27.5;
    }

    src[20] = -31.1;     etalon[20] = -27.5;
    src[21] = 11234.356; etalon[21] = 11234.356;
    src[22] = 38.0;      etalon[22] = 38.0;
    src[23] = -1234.111; etalon[23] = -27.5;
    src[24] = 39.0;      etalon[24] = 39.0;
    src[25] = 0;         etalon[25] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 26, -27.5, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i * 2.3;
    	etalon[i] = 38.0;
    }

    for(; i < 20; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }

    src[20] = 37.0;  etalon[20] = 38.0;
    src[21] = 123.0; etalon[21] = 123.0;
    src[22] = 38.0;  etalon[22] = 38.0;
    src[23] = 0.0;   etalon[23] = 38.0;
    src[24] = 39.0;  etalon[24] = 39.0;
    src[25] = 1.0;   etalon[25] = 38.0;
    src[26] = -3.0;  etalon[26] = 38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 27, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38.0;
    }

    for(; i < 120; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }

    src[120] = 37.0;  etalon[120] = 38.0;
    src[121] = 123.0; etalon[121] = 123.0;
    src[122] = 38.0;  etalon[122] = 38.0;
    src[123] = 0.0;   etalon[123] = 38.0;
    src[124] = 39.0;  etalon[124] = 39.0;
    src[125] = 1.0;   etalon[125] = 38.0;
    src[126] = -3.0;  etalon[126] = 38.0;
    src[127] = -38.0; etalon[127] = 38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 128, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38.0;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 148, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }

    src[148] = -123.0; etalon[148] = 38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 149, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    src[0] = -123.0; etalon[0] = 4533535.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 1, 4533535.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }
}


/// nmppsThreshold_642f
TEST(tests_threshold, test_nmppsThreshold_64f_null_ptr){
	nmpps64f a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_64f(NULL, &a, 1, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_64f(&a, NULL, 1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_64f_err_size){
	nmpps64f a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_64f(&a, &a, 0, 1, nmppsCmpLess));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_64f(&a, &a, -1, 1, nmppsCmpLess));
}

TEST(tests_threshold, test_nmppsThreshold_64f_err_cmp_op){
	nmpps64f a;

	TEST_ASSERT_EQUAL(nmppsStsBadArgErr, nmppsThreshold_64f(&a, &a, 0, 1, nmppsCmpEq));
}


TEST(tests_threshold, test_nmppsThreshold_64f_less){
    int i = 0;
    nmpps64f src[150]    __attribute__ ((aligned (2)));
    nmpps64f dst[150]    __attribute__ ((aligned (2)));
    nmpps64f etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i / 3;
    	etalon[i] = i / 3;
    }

    for(; i < 20; i++){
    	src[i] = i - 138.1;
    	etalon[i] = -27.5;
    }

    src[20] = -31.1;     etalon[20] = -27.5;
    src[21] = 11234.356; etalon[21] = 11234.356;
    src[22] = 38.0;      etalon[22] = 38.0;
    src[23] = -1234.111; etalon[23] = -27.5;
    src[24] = 39.0;      etalon[24] = 39.0;
    src[25] = 0;         etalon[25] = 0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 26, -27.5, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_64f(dst, 0xFFFF, 150);
    init_vector_value_64f(src, 0xFFFF, 150);
    init_vector_value_64f(etalon, 0xFFFF, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i * 2.3;
    	etalon[i] = 38.0;
    }

    for(; i < 20; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }

    src[20] = 37.0;  etalon[20] = 38.0;
    src[21] = 123.0; etalon[21] = 123.0;
    src[22] = 38.0;  etalon[22] = 38.0;
    src[23] = 0.0;   etalon[23] = 38.0;
    src[24] = 39.0;  etalon[24] = 39.0;
    src[25] = 1.0;   etalon[25] = 38.0;
    src[26] = -3.0;  etalon[26] = 38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 27, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_64f(dst, 0xFFFF, 150);
    init_vector_value_64f(src, 0xFFFF, 150);
    init_vector_value_64f(etalon, 0xFFFF, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38.0;
    }

    for(; i < 120; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }

    src[120] = 37.0;  etalon[120] = 38.0;
    src[121] = 123.0; etalon[121] = 123.0;
    src[122] = 38.0;  etalon[122] = 38.0;
    src[123] = 0.0;   etalon[123] = 38.0;
    src[124] = 39.0;  etalon[124] = 39.0;
    src[125] = 1.0;   etalon[125] = 38.0;
    src[126] = -3.0;  etalon[126] = 38.0;
    src[127] = -38.0; etalon[127] = 38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 128, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_64f(dst, 0xFFFF, 150);
    init_vector_value_64f(src, 0xFFFF, 150);
    init_vector_value_64f(etalon, 0xFFFF, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38.0;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 148, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_64f(dst, 0xFFFF, 150);
    init_vector_value_64f(src, 0xFFFF, 150);
    init_vector_value_64f(etalon, 0xFFFF, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = 38;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = i + 38.0;
    }

    src[148] = -123.0; etalon[148] = 38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 149, 38.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_64f(dst, 0xFFFF, 150);
    init_vector_value_64f(src, 0xFFFF, 150);
    init_vector_value_64f(etalon, 0xFFFF, 150);

    src[0] = -123.0; etalon[0] = 4533535.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 1, 4533535.0, nmppsCmpLess));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }
}

TEST(tests_threshold, test_nmppsThreshold_16s_great){
    int i = 0;
    nmpps16s src[150]    __attribute__ ((aligned (2)));
    nmpps16s dst[150]    __attribute__ ((aligned (2)));
    nmpps16s etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = i;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[20] = 37;  etalon[20] = 37;
    src[21] = 123; etalon[21] = 38;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 0;
    src[24] = 39;  etalon[24] = 38;
    src[25] = 1;   etalon[25] = 1;
    src[26] = 100; etalon[26] = 38;
    src[27] = -3;  etalon[27] = -3;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 28, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = i;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[20] = 37;  etalon[20] = 37;
    src[21] = 123; etalon[21] = 38;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 0;
    src[24] = 39;  etalon[24] = 38;
    src[25] = 1;   etalon[25] = 1;
    src[26] = -3;  etalon[26] = -3;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 27, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 120; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[120] = 37;  etalon[120] = 37;
    src[121] = 123; etalon[121] = 38;
    src[122] = 38;  etalon[122] = 38;
    src[123] = 0;   etalon[123] = 0;
    src[124] = 39;  etalon[124] = 38;
    src[125] = 1;   etalon[125] = 1;
    src[126] = -3;  etalon[126] = -3;
    src[127] = -38; etalon[127] = -38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 128, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 148, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[148] = -123; etalon[148] = -123;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 149, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    src[0] = -39; etalon[0] = -123;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_16s(src, dst, 1, -123, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }
}


TEST(tests_threshold, test_nmppsThreshold_32s_great){
    int i = 0;
    nmpps32s src[150]    __attribute__ ((aligned (2)));
    nmpps32s dst[150]    __attribute__ ((aligned (2)));
    nmpps32s etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = i;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[20] = 37;  etalon[20] = 37;
    src[21] = 123; etalon[21] = 38;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 0;
    src[24] = 39;  etalon[24] = 38;
    src[25] = 1;   etalon[25] = 1;
    src[26] = 100; etalon[26] = 38;
    src[27] = -3;  etalon[27] = -3;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 28, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i;
    	etalon[i] = i;
    }

    for(; i < 20; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[20] = 37;  etalon[20] = 37;
    src[21] = 123; etalon[21] = 38;
    src[22] = 38;  etalon[22] = 38;
    src[23] = 0;   etalon[23] = 0;
    src[24] = 39;  etalon[24] = 38;
    src[25] = 1;   etalon[25] = 1;
    src[26] = -3;  etalon[26] = -3;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 27, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 120; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[120] = 37;  etalon[120] = 37;
    src[121] = 123; etalon[121] = 38;
    src[122] = 38;  etalon[122] = 38;
    src[123] = 0;   etalon[123] = 0;
    src[124] = 39;  etalon[124] = 38;
    src[125] = 1;   etalon[125] = 1;
    src[126] = -3;  etalon[126] = -3;
    src[127] = -38; etalon[127] = -38;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 128, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 148, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -38;
    }

    for(; i < 148; i++){
    	src[i] = i - 1111;
    	etalon[i] = i - 1111;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 148, -38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38;
    	etalon[i] = 38;
    }

    src[148] = -123; etalon[148] = -123;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 149, 38, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    src[0] = -123; etalon[0] = -123;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32s(src, dst, 1, -7, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }
}



TEST(tests_threshold, test_nmppsThreshold_32f_great){
    int i = 0;
    nmpps32f src[150]    __attribute__ ((aligned (2)));
    nmpps32f dst[150]    __attribute__ ((aligned (2)));
    nmpps32f etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i / 3;
    	etalon[i] = -27.5;
    }

    for(; i < 20; i++){
    	src[i] = i - 138.1;
    	etalon[i] = i - 138.1;
    }

    src[20] = -31.1;     etalon[20] = -31.1;
    src[21] = 11234.356; etalon[21] = -27.5;
    src[22] = 38.0;      etalon[22] = -27.5;
    src[23] = -1234.111; etalon[23] = -1234.111;
    src[24] = 39.0;      etalon[24] = -27.5;
    src[25] = 0;         etalon[25] = -27.5;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 26, -27.5, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i * 2.3;
    	etalon[i] = i * 2.3;
    }

    for(; i < 20; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }

    src[20] = 37.0;  etalon[20] = 37.0;
    src[21] = 123.0; etalon[21] = 38.0;
    src[22] = 38.0;  etalon[22] = 38.0;
    src[23] = 0.0;   etalon[23] = 0.0;
    src[24] = 39.0;  etalon[24] = 38.0;
    src[25] = 1.0;   etalon[25] = 1.0;
    src[26] = -3.0;  etalon[26] = -3.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 27, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 120; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }

    src[120] = 37.0;  etalon[120] = 37.0;
    src[121] = 123.0; etalon[121] = 38.0;
    src[122] = 38.0;  etalon[122] = 38.0;
    src[123] = 0.0;   etalon[123] = 0.0;
    src[124] = 39.0;  etalon[124] = 38.0;
    src[125] = 1.0;   etalon[125] = 1.0;
    src[126] = -3.0;  etalon[126] = -3.0;
    src[127] = -38.0; etalon[127] = -38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 128, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 148, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }

    src[148] = -123.0; etalon[148] = -123.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 149, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    src[0] = -123.0; etalon[0] = -123.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_32f(src, dst, 1, 4533535.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }
}


TEST(tests_threshold, test_nmppsThreshold_64f_great){
    int i = 0;
    nmpps64f src[150]    __attribute__ ((aligned (2)));
    nmpps64f dst[150]    __attribute__ ((aligned (2)));
    nmpps64f etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i / 3;
    	etalon[i] = -27.5;
    }

    for(; i < 20; i++){
    	src[i] = i - 138.1;
    	etalon[i] = i - 138.1;
    }

    src[20] = -31.1;     etalon[20] = -31.1;
    src[21] = 11234.356; etalon[21] = -27.5;
    src[22] = 38.0;      etalon[22] = -27.5;
    src[23] = -1234.111; etalon[23] = -1234.111;
    src[24] = 39.0;      etalon[24] = -27.5;
    src[25] = 0;         etalon[25] = -27.5;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 26, -27.5, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32
    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = i * 2.3;
    	etalon[i] = i * 2.3;
    }

    for(; i < 20; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }

    src[20] = 37.0;  etalon[20] = 37.0;
    src[21] = 123.0; etalon[21] = 38.0;
    src[22] = 38.0;  etalon[22] = 38.0;
    src[23] = 0.0;   etalon[23] = 0.0;
    src[24] = 39.0;  etalon[24] = 38.0;
    src[25] = 1.0;   etalon[25] = 1.0;
    src[26] = -3.0;  etalon[26] = -3.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 27, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Кратно 32
    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 120; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }

    src[120] = 37.0;  etalon[120] = 37.0;
    src[121] = 123.0; etalon[121] = 38.0;
    src[122] = 38.0;  etalon[122] = 38.0;
    src[123] = 0.0;   etalon[123] = 0.0;
    src[124] = 39.0;  etalon[124] = 38.0;
    src[125] = 1.0;   etalon[125] = 1.0;
    src[126] = -3.0;  etalon[126] = -3.0;
    src[127] = -38.0; etalon[127] = -38.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 128, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 148, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, кратно 2
    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 10; i++){
    	src[i] = -i;
    	etalon[i] = -i;
    }

    for(; i < 148; i++){
    	src[i] = i + 38.0;
    	etalon[i] = 38.0;
    }

    src[148] = -123.0; etalon[148] = -123.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 149, 38.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    src[0] = -123.0; etalon[0] = -123.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_64f(src, dst, 1, 4533535.0, nmppsCmpGreater));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }
}
TEST_GROUP_RUNNER(tests_threshold){
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_16s_null_ptr);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_16s_err_size);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_16s_err_cmp_op);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_16s_less);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_16s_great);

	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32s_null_ptr);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32s_err_size);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32s_err_cmp_op);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32s_less);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32s_great);

	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32f_null_ptr);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32f_err_size);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32f_err_cmp_op);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32f_less);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_32f_great);

	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_64f_null_ptr);
    RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_64f_err_size);
    RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_64f_err_cmp_op);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_64f_less);
	RUN_TEST_CASE(tests_threshold, test_nmppsThreshold_64f_great);


}



















