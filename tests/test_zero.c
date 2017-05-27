#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_zero);

TEST_SETUP(tests_zero){}
TEST_TEAR_DOWN(tests_zero){}


//nmppsZero_8u

TEST(tests_zero, test_nmppsZero_8u_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_8u(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_8u_len){
    nmpps8u vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_8u(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_8u(vector, -1));
}

TEST(tests_zero, test_nmppsZero_8u){
	nmpps8u* dst = get_ptr_dst_vector_8u();
    int i = 0;

	// Один элемент
	dst[0] = 124;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_8u(dst, 1));
	TEST_ASSERT_EQUAL(0, dst[0]);

	// Частичная загрузка векторного регистра
	init_vector_8u(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_8u(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i]);
	}

    // Полная загрузка вектора
    init_vector_8u(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_8u(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + один элемент
    init_vector_8u(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_8u(dst, 3521));
    for(i = 0; i < 3521; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_8u(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_8u(dst, 664));
    for(i = 0; i < 3521; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_8u(dst, 665);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_8u(dst, 665));
    for(i = 0; i < 3521; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }
}

//nmppsZero_16s

TEST(tests_zero, test_nmppsZero_16s_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_16s(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_16s_len){
    nmpps16s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_16s(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_16s(vector, -1));
}

TEST(tests_zero, test_nmppsZero_16s){
	nmpps16s* dst = get_ptr_dst_vector_16s();
    int i = 0;

	// Один элемент
	dst[0] = 124;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16s(dst, 1));
	TEST_ASSERT_EQUAL(0, dst[0]);

	// Частичная загрузка векторного регистра
	init_vector_16s(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16s(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i]);
	}

    // Полная загрузка вектора
    init_vector_16s(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16s(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + один элемент
    init_vector_16s(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16s(dst, 3521));
    for(i = 0; i < 3521; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_16s(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16s(dst, 664));
    for(i = 0; i < 3521; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_16s(dst, 665);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16s(dst, 665));
    for(i = 0; i < 665; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }
}


//nmppsZero_32s

TEST(tests_zero, test_nmppsZero_32s_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_32s(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_32s_len){
    nmpps32s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_32s(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_32s(vector, -1));
}

TEST(tests_zero, test_nmppsZero_32s){
	nmpps32s* dst = get_ptr_dst_vector_32s();
    int i = 0;

	// Один элемент
	dst[0] = 124;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32s(dst, 1));
	TEST_ASSERT_EQUAL(0, dst[0]);

	// Частичная загрузка векторного регистра
	init_vector_32s(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32s(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i]);
	}

    // Полная загрузка вектора
    init_vector_32s(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32s(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + один элемент
    init_vector_32s(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32s(dst, 3521));
    for(i = 0; i < 3521; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_32s(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32s(dst, 664));
    for(i = 0; i < 664; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка + один элемент
    init_vector_32s(dst, 665);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32s(dst, 665));
    for(i = 0; i < 665; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }
}

//nmppsZero_64s

TEST(tests_zero, test_nmppsZero_64s_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_64s(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_64s_len){
    nmpps64s vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_64s(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_64s(vector, -1));
}

TEST(tests_zero, test_nmppsZero_64s){
	nmpps64s* dst = get_ptr_dst_vector_64s();
    int i = 0;

	// Частичная загрузка векторного регистра
	init_vector_64s(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_64s(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i]);
	}

    // Полная загрузка вектора
    init_vector_64s(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_64s(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_64s(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_64s(dst, 664));
    for(i = 0; i < 664; i++){
    	TEST_ASSERT_EQUAL(0, dst[i]);
    }

}

//nmppsZero_16sc

TEST(tests_zero, test_nmppsZero_16sc_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_16sc(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_16sc_len){
    nmpps16sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_16sc(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_16sc(vector, -1));
}

TEST(tests_zero, test_nmppsZero_16sc){
	nmpps16sc* dst = get_ptr_dst_vector_16sc();
    int i = 0;

	// Частичная загрузка векторного регистра
	init_vector_16sc(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16sc(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i].im);
		TEST_ASSERT_EQUAL(0, dst[i].re);
	}

    // Полная загрузка вектора
    init_vector_16sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16sc(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i].im);
        TEST_ASSERT_EQUAL(0, dst[i].re);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_16sc(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_16sc(dst, 664));
    for(i = 0; i < 664; i++){
    	TEST_ASSERT_EQUAL(0, dst[i].im);
    	TEST_ASSERT_EQUAL(0, dst[i].re);
    }

}

//nmppsZero_32sc

TEST(tests_zero, test_nmppsZero_32sc_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_32sc(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_32sc_len){
    nmpps32sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_32sc(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_32sc(vector, -1));
}

TEST(tests_zero, test_nmppsZero_32sc){
	nmpps32sc* dst = get_ptr_dst_vector_32sc();
    int i = 0;

	// Частичная загрузка векторного регистра
	init_vector_32sc(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32sc(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i].im);
		TEST_ASSERT_EQUAL(0, dst[i].re);
	}

    // Полная загрузка вектора
    init_vector_32sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32sc(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i].im);
        TEST_ASSERT_EQUAL(0, dst[i].re);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_32sc(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_32sc(dst, 664));
    for(i = 0; i < 664; i++){
    	TEST_ASSERT_EQUAL(0, dst[i].im);
    	TEST_ASSERT_EQUAL(0, dst[i].re);
    }

}

//nmppsZero_64sc

TEST(tests_zero, test_nmppsZero_64sc_null_ptr){

    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsZero_64sc(NULL, 1));
}

TEST(tests_zero, test_nmppsZero_64sc_len){
    nmpps64sc vector[10];

    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_64sc(vector, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsZero_64sc(vector, -1));
}

TEST(tests_zero, test_nmppsZero_64sc){
	nmpps64sc* dst = get_ptr_dst_vector_64sc();
    int i = 0;

	// Частичная загрузка векторного регистра
	init_vector_64sc(dst, 4100);

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_64sc(dst, 23));

	for(i = 0; i < 23; i++){
		TEST_ASSERT_EQUAL(0, dst[i].im);
		TEST_ASSERT_EQUAL(0, dst[i].re);
	}

    // Полная загрузка вектора
    init_vector_64sc(dst, 4100);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_64sc(dst, 3520));
    for(i = 0; i < 3520; i++){
    	TEST_ASSERT_EQUAL(0, dst[i].im);
        TEST_ASSERT_EQUAL(0, dst[i].re);
    }

    // Полная загрузка векторного регистра + частичная загрузка
    init_vector_64sc(dst, 664);

    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsZero_64sc(dst, 664));
    for(i = 0; i < 664; i++){
    	TEST_ASSERT_EQUAL(0, dst[i].im);
    	TEST_ASSERT_EQUAL(0, dst[i].re);
    }

}


TEST_GROUP_RUNNER(tests_zero){
    RUN_TEST_CASE(tests_zero, test_nmppsZero_8u_null_ptr);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_8u_len);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_8u);

    RUN_TEST_CASE(tests_zero, test_nmppsZero_16s_null_ptr);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_16s_len);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_16s);

    RUN_TEST_CASE(tests_zero, test_nmppsZero_32s_null_ptr);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_32s_len);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_32s);

    RUN_TEST_CASE(tests_zero, test_nmppsZero_16sc_null_ptr);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_16sc_len);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_16sc);

    RUN_TEST_CASE(tests_zero, test_nmppsZero_32sc_null_ptr);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_32sc_len);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_32sc);

    RUN_TEST_CASE(tests_zero, test_nmppsZero_64sc_null_ptr);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_64sc_len);
    RUN_TEST_CASE(tests_zero, test_nmppsZero_64sc);

}


