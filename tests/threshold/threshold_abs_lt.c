#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_threshold_abs_lt);

TEST_SETUP(tests_threshold_abs_lt){};
TEST_TEAR_DOWN(tests_threshold_abs_lt){}


/// nmppsThreshold_LTAbs_16s
TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_16s_null_ptr){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_16s(NULL, &a, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_16s(&a, NULL, 1, 1));
}

TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_16s_err_size){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_16s(&a, &a, 0, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_16s(&a, &a, -1, 1));
}


TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_16s){
    int i = 0;
    nmpps16s src[150]    __attribute__ ((aligned (2)));
    nmpps16s dst[150]    __attribute__ ((aligned (2)));
    nmpps16s etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 5; i++){
    	src[i] = i;
    	etalon[i] = i;
    }

    for(; i < 10; i++){
    	src[i] = i - 100;
    	etalon[i] = i - 100;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_16s(src, dst, 10, -67));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 5; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 10; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 15; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 20; i++){
    	src[i] = i - 30;
    	etalon[i] = -80;
    }

    src[20] = -201; etalon[20] = -201;
    src[21] = -2;   etalon[21] = -80;
    src[22] = 0;    etalon[22] = 80;
    src[23] = 312;  etalon[23] = 312;
    src[24] = -80;  etalon[24] = -80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_16s(src, dst, 25, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Кратно 32

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 90; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 123; i++){
    	src[i] = i - 140;
    	etalon[i] = -80;
    }

    src[123] = -201; etalon[123] = -201;
    src[124] = -2;   etalon[124] = -80;
    src[125] = 0;    etalon[125] = 80;
    src[126] = 312;  etalon[126] = 312;
    src[127] = -80;  etalon[127] = -80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_16s(src, dst, 128, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, четно

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 90; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 123; i++){
    	src[i] = i - 140;
    	etalon[i] = -80;
    }

    src[123] = -201; etalon[123] = -201;
    src[124] = -2;   etalon[124] = -80;
    src[125] = 0;    etalon[125] = 80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_16s(src, dst, 126, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, нечетно

    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 90; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 123; i++){
    	src[i] = i - 140;
    	etalon[i] = -80;
    }

    src[123] = -201; etalon[123] = -201;
    src[124] = -2;   etalon[124] = -80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_16s(src, dst, 125, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_16s(dst, 0, 150);
    init_vector_value_16s(src, 0, 150);
    init_vector_value_16s(etalon, 0, 150);

    src[0] = -12; etalon[0] = -12;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_16s(src, dst, 1, -1));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }
}


/// nmppsThreshold_LTAbs_32s
TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32s_null_ptr){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_32s(NULL, &a, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_32s(&a, NULL, 1, 1));
}

TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32s_err_size){
	nmpps32s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_32s(&a, &a, 0, 1));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_32s(&a, &a, -1, 1));
}


TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32s){
    int i = 0;
    nmpps32s src[150]    __attribute__ ((aligned (2)));
    nmpps32s dst[150]    __attribute__ ((aligned (2)));
    nmpps32s etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 5; i++){
    	src[i] = i;
    	etalon[i] = i;
    }

    for(; i < 10; i++){
    	src[i] = i - 100;
    	etalon[i] = i - 100;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32s(src, dst, 10, -67));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 5; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 10; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 15; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 20; i++){
    	src[i] = i - 30;
    	etalon[i] = -80;
    }

    src[20] = -201; etalon[20] = -201;
    src[21] = -2;   etalon[21] = -80;
    src[22] = 0;    etalon[22] = 80;
    src[23] = 312;  etalon[23] = 312;
    src[24] = -80;  etalon[24] = -80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32s(src, dst, 25, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// Кратно 32

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 90; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 123; i++){
    	src[i] = i - 140;
    	etalon[i] = -80;
    }

    src[123] = -201; etalon[123] = -201;
    src[124] = -2;   etalon[124] = -80;
    src[125] = 0;    etalon[125] = 80;
    src[126] = 312;  etalon[126] = 312;
    src[127] = -80;  etalon[127] = -80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32s(src, dst, 128, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, четно

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 90; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 123; i++){
    	src[i] = i - 140;
    	etalon[i] = -80;
    }

    src[123] = -201; etalon[123] = -201;
    src[124] = -2;   etalon[124] = -80;
    src[125] = 0;    etalon[125] = 80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32s(src, dst, 126, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// больше 32, нечетно

    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i;
    	etalon[i] = 80;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000;
    	etalon[i] = i - 1000;
    }

    for(; i < 90; i++){
    	src[i] = i + 300;
    	etalon[i] = i + 300;
    }

    for(; i < 123; i++){
    	src[i] = i - 140;
    	etalon[i] = -80;
    }

    src[123] = -201; etalon[123] = -201;
    src[124] = -2;   etalon[124] = -80;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32s(src, dst, 125, 80));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_32s(dst, 0, 150);
    init_vector_value_32s(src, 0, 150);
    init_vector_value_32s(etalon, 0, 150);

    src[0] = -12; etalon[0] = -12;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32s(src, dst, 1, -1));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL(etalon[i], dst[i]);
    }
}


/// nmppsThreshold_LTAbs_32f
TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32f_null_ptr){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_32f(NULL, &a, 1, 1.0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_32f(&a, NULL, 1, 1.0));
}

TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32f_err_size){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_32f(&a, &a, 0, 1.0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_32f(&a, &a, -1, 1.0));
}


TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32f){
    int i = 0;
    nmpps32f src[150]    __attribute__ ((aligned (2)));
    nmpps32f dst[150]    __attribute__ ((aligned (2)));
    nmpps32f etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_32f(dst, 0.0, 150.0);
    init_vector_value_32f(src, 0.0, 150.0);
    init_vector_value_32f(etalon, 0.0, 150.0);

    for(i = 0; i < 5; i++){
    	src[i] = i * 1.1;
    	etalon[i] = i * 1.1;
    }

    for(; i < 10; i++){
    	src[i] = i - 100.1;
    	etalon[i] = i - 100.1;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32f(src, dst, 10, -67.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32

    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 5; i++){
    	src[i] = i * 1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 10; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 15; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 20; i++){
    	src[i] = i - 30.0;
    	etalon[i] = -80.0;
    }

    src[20] = -201.0; etalon[20] = -201.0;
    src[21] = -2.0;   etalon[21] = -80.0;
    src[22] = 0.0;    etalon[22] = 80.0;
    src[23] = 312.0;  etalon[23] = 312.0;
    src[24] = -80.0;  etalon[24] = -80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32f(src, dst, 25, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// Кратно 32

    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i*1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 90; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 123; i++){
    	src[i] = i - 140.0;
    	etalon[i] = -80.0;
    }

    src[123] = -201.0; etalon[123] = -201.0;
    src[124] = -2.0;   etalon[124] = -80.0;
    src[125] = 0.0;    etalon[125] = 80.0;
    src[126] = 312.0;  etalon[126] = 312.0;
    src[127] = -80.0;  etalon[127] = -80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32f(src, dst, 128, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, четно

    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i * 1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 90; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 123; i++){
    	src[i] = i - 140.0;
    	etalon[i] = -80.0;
    }

    src[123] = -201.0; etalon[123] = -201.0;
    src[124] = -2.0;   etalon[124] = -80.0;
    src[125] = 0.0;    etalon[125] = 80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32f(src, dst, 126, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// больше 32, нечетно

    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i * 1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 90; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 123; i++){
    	src[i] = i - 140.0;
    	etalon[i] = -80.0;
    }

    src[123] = -201.0; etalon[123] = -201.0;
    src[124] = -2.0;   etalon[124] = -80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32f(src, dst, 125, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_32f(dst, 0.0, 150);
    init_vector_value_32f(src, 0.0, 150);
    init_vector_value_32f(etalon, 0.0, 150);

    src[0] = -12.0; etalon[0] = -12.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_32f(src, dst, 1, -1.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_FLOAT(etalon[i], dst[i]);
    }
}

/// nmppsThreshold_LTAbs_64f
TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_64f_null_ptr){
	nmpps64f a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_64f(NULL, &a, 1, 1.0));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsThreshold_LTAbs_64f(&a, NULL, 1, 1.0));
}

TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_64f_err_size){
	nmpps64f a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_64f(&a, &a, 0, 1.0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsThreshold_LTAbs_64f(&a, &a, -1, 1.0));
}


TEST(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_64f){
    int i = 0;
    nmpps64f src[150]    __attribute__ ((aligned (2)));
    nmpps64f dst[150]    __attribute__ ((aligned (2)));
    nmpps64f etalon[150] __attribute__ ((aligned (2)));

    /// Четное количество элементов, < 32

    init_vector_value_64f(dst, 0.0, 150.0);
    init_vector_value_64f(src, 0.0, 150.0);
    init_vector_value_64f(etalon, 0.0, 150.0);

    for(i = 0; i < 5; i++){
    	src[i] = i * 1.1;
    	etalon[i] = i * 1.1;
    }

    for(; i < 10; i++){
    	src[i] = i - 100.1;
    	etalon[i] = i - 100.1;
    }

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_64f(src, dst, 10, -67.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// Нечетное количество элементов, < 32

    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 5; i++){
    	src[i] = i * 1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 10; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 15; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 20; i++){
    	src[i] = i - 30.0;
    	etalon[i] = -80.0;
    }

    src[20] = -201.0; etalon[20] = -201.0;
    src[21] = -2.0;   etalon[21] = -80.0;
    src[22] = 0.0;    etalon[22] = 80.0;
    src[23] = 312.0;  etalon[23] = 312.0;
    src[24] = -80.0;  etalon[24] = -80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_64f(src, dst, 25, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// Кратно 32

    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i*1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 90; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 123; i++){
    	src[i] = i - 140.0;
    	etalon[i] = -80.0;
    }

    src[123] = -201.0; etalon[123] = -201.0;
    src[124] = -2.0;   etalon[124] = -80.0;
    src[125] = 0.0;    etalon[125] = 80.0;
    src[126] = 312.0;  etalon[126] = 312.0;
    src[127] = -80.0;  etalon[127] = -80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_64f(src, dst, 128, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// больше 32, четно

    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i * 1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 90; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 123; i++){
    	src[i] = i - 140.0;
    	etalon[i] = -80.0;
    }

    src[123] = -201.0; etalon[123] = -201.0;
    src[124] = -2.0;   etalon[124] = -80.0;
    src[125] = 0.0;    etalon[125] = 80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_64f(src, dst, 126, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// больше 32, нечетно

    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    for(i = 0; i < 30; i++){
    	src[i] = i * 1.1;
    	etalon[i] = 80.0;
    }

    for(; i < 60; i++){
    	src[i] = i - 1000.0;
    	etalon[i] = i - 1000.0;
    }

    for(; i < 90; i++){
    	src[i] = i + 300.0;
    	etalon[i] = i + 300.0;
    }

    for(; i < 123; i++){
    	src[i] = i - 140.0;
    	etalon[i] = -80.0;
    }

    src[123] = -201.0; etalon[123] = -201.0;
    src[124] = -2.0;   etalon[124] = -80.0;


    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_64f(src, dst, 125, 80.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }

    /// 1
    init_vector_value_64f(dst, 0.0, 150);
    init_vector_value_64f(src, 0.0, 150);
    init_vector_value_64f(etalon, 0.0, 150);

    src[0] = -12.0; etalon[0] = -12.0;

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsThreshold_LTAbs_64f(src, dst, 1, -1.0));
    for(i = 0; i < 150;i++){
    	TEST_ASSERT_EQUAL_DOUBLE(etalon[i], dst[i]);
    }
}

TEST_GROUP_RUNNER(tests_threshold_abs_lt){
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_16s_null_ptr);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_16s_err_size);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_16s);

	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32s_null_ptr);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32s_err_size);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32s);

	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32f_null_ptr);
    RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32f_err_size);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_32f);

	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_64f_null_ptr);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_64f_err_size);
	RUN_TEST_CASE(tests_threshold_abs_lt, test_nmppsThreshold_LTAbs_64f);
}

