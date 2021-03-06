#include "unity/unity_fixture.h"
#include "test_common.h"
#include "nmpps.h"

TEST_GROUP(tests_maxevery);

TEST_SETUP(tests_maxevery){}
TEST_TEAR_DOWN(tests_maxevery){}

///_nmppsMaxEvery_16s_I
//_nmppsMaxEvery_32s_I

TEST(tests_maxevery, test_nmppsMaxEvery_16s_I_null_ptr){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxEvery_16s_I(NULL, &a, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxEvery_16s_I(&a, NULL, 1));
}

TEST(tests_maxevery, test_nmppsMaxEvery_16s_I_err_size){
	nmpps16s a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxEvery_16s_I(&a, &a, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxEvery_16s_I(&a, &a, -1));
}

TEST(tests_maxevery, test_nmppsMaxEvery_16s_I){
	int i = 0;
	nmpps16s src[150]    __attribute__ ((aligned (2)));
	nmpps16s srcdst[150]    __attribute__ ((aligned (2)));
	nmpps16s etalon[150]    __attribute__ ((aligned (2)));

	init_vector_value_16s(srcdst, 0, 150);
	init_vector_value_16s(src, 0, 150);
	init_vector_value_16s(etalon, 0, 150);

	for(i = 0; i < 31; i++){
		src[i] = i + 1;
		srcdst[i] = i;
		etalon[i] = i + 1;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_16s_I(src, srcdst, 31));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL(etalon[i], srcdst[i]);
	}

	init_vector_value_16s(srcdst, 0, 150);
	init_vector_value_16s(src, 0, 150);
	init_vector_value_16s(etalon, 0, 150);

	for(i = 0; i < 30; i++){
		src[i] = i;
		srcdst[i] = i + 1;
		etalon[i] = i + 1;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_16s_I(src, srcdst, 30));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL(etalon[i], srcdst[i]);
	}

	init_vector_value_16s(srcdst, 0, 150);
	init_vector_value_16s(src, 0, 150);
	init_vector_value_16s(etalon, 0, 150);

	for(i = 0; i < 128; i++){
		src[i] = i - 50;
		srcdst[i] = i - 100;
		etalon[i] = i - 50;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_16s_I(src, srcdst, 128));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL(etalon[i], srcdst[i]);
	}

	init_vector_value_16s(srcdst, 0, 150);
	init_vector_value_16s(src, 0, 150);
	init_vector_value_16s(etalon, 0, 150);

	for(i = 0; i < 150; i++){
		src[i] = i - 50;
		srcdst[i] = i - 100;
		etalon[i] = i - 50;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_16s_I(src, srcdst, 150));
	for(i = 0; i < 150;i++){
			TEST_ASSERT_EQUAL(etalon[i], srcdst[i]);
		}

	init_vector_value_16s(srcdst, 0, 150);
	init_vector_value_16s(src, 0, 150);
	init_vector_value_16s(etalon, 0, 150);

	for(i = 0; i < 149; i++){
		src[i] = i + 100;
		srcdst[i] = i - 50;
		etalon[i] = i + 100;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_16s_I(src, srcdst, 149));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL(etalon[i], srcdst[i]);
	}

	init_vector_value_16s(srcdst, 0, 150);
	init_vector_value_16s(src, 0, 150);
	init_vector_value_16s(etalon, 0, 150);

	src[0] = 10;
	srcdst[0] = -3;
	etalon[0] = 10;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_16s_I(src, srcdst, 1));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL(etalon[i], srcdst[i]);
	}
}

///nmppsMaxEvery_32f_I

TEST(tests_maxevery, test_nmppsMaxEvery_32f_I_null_ptr){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxEvery_32f_I(NULL, &a, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsMaxEvery_32f_I(&a, NULL, 1));
}

TEST(tests_maxevery, test_nmppsMaxEvery_32f_I_err_size){
	nmpps32f a;

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxEvery_32f_I(&a, &a, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsMaxEvery_32f_I(&a, &a, -1));
}

TEST(tests_maxevery, test_nmppsMaxEvery_32f_I){
	int i = 0;
	nmpps32f src[150]    __attribute__ ((aligned (2)));
	nmpps32f srcdst[150]    __attribute__ ((aligned (2)));
	nmpps32f etalon[150]    __attribute__ ((aligned (2)));

	init_vector_value_32f(srcdst, 0, 150);
	init_vector_value_32f(src, 0, 150);
	init_vector_value_32f(etalon, 0, 150);

	for(i = 0; i < 31; i++){
		src[i] = i * 2.3;
		srcdst[i] = i / 3.0;
		etalon[i] = i * 2.3;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_32f_I(src, srcdst, 31));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL_FLOAT(etalon[i], srcdst[i]);
	}

	init_vector_value_32f(srcdst, 0, 150);
	init_vector_value_32f(src, 0, 150);
	init_vector_value_32f(etalon, 0, 150);

	for(i = 0; i < 30; i++){
		src[i] = i + 0.5;
		srcdst[i] = i + 1.6;
		etalon[i] = i + 1.6;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_32f_I(src, srcdst, 30));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL_FLOAT(etalon[i], srcdst[i]);
	}

	init_vector_value_32f(srcdst, 0, 150);
	init_vector_value_32f(src, 0, 150);
	init_vector_value_32f(etalon, 0, 150);

	for(i = 0; i < 128; i++){
		src[i] = i - 50.0;
		srcdst[i] = i - 100.0;
		etalon[i] = i - 50.0;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_32f_I(src, srcdst, 128));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL_FLOAT(etalon[i], srcdst[i]);
	}

	init_vector_value_32f(srcdst, 0, 150);
	init_vector_value_32f(src, 0, 150);
	init_vector_value_32f(etalon, 0, 150);

	for(i = 0; i < 150; i++){
		src[i] = i - 50.1;
		srcdst[i] = i - 100.5;
		etalon[i] = i - 50.1;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_32f_I(src, srcdst, 150));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL_FLOAT(etalon[i], srcdst[i]);
    }

	init_vector_value_32f(srcdst, 0, 150);
	init_vector_value_32f(src, 0, 150);
	init_vector_value_32f(etalon, 0, 150);

	for(i = 0; i < 149; i++){
		src[i] = i - 50.78;
		srcdst[i] = i + 100.78;
		etalon[i] = i + 100.78;
	}

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_32f_I(src, srcdst, 149));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL_FLOAT(etalon[i], srcdst[i]);
	}

	init_vector_value_32f(srcdst, 0, 150);
	init_vector_value_32f(src, 0, 150);
	init_vector_value_32f(etalon, 0, 150);

	src[0] = 10.2;
	srcdst[0] = -3.1;
	etalon[0] = 10.2;

	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsMaxEvery_32f_I(src, srcdst, 1));
	for(i = 0; i < 150;i++){
		TEST_ASSERT_EQUAL_FLOAT(etalon[i], srcdst[i]);
	}
}
TEST_GROUP_RUNNER(tests_maxevery){
	RUN_TEST_CASE(tests_maxevery, test_nmppsMaxEvery_16s_I_null_ptr);
	RUN_TEST_CASE(tests_maxevery, test_nmppsMaxEvery_16s_I_err_size);
	RUN_TEST_CASE(tests_maxevery, test_nmppsMaxEvery_16s_I);

	RUN_TEST_CASE(tests_maxevery, test_nmppsMaxEvery_32f_I_null_ptr);
	RUN_TEST_CASE(tests_maxevery, test_nmppsMaxEvery_32f_I_err_size);
	RUN_TEST_CASE(tests_maxevery, test_nmppsMaxEvery_32f_I);
}
