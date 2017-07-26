//#include "unity/unity_fixture.h"
//#include "test_common.h"
//#include "nmpps.h"
//
//
//TEST_GROUP(tests_lshift_16u);
//
//TEST_SETUP(tests_lshift_16u){}
//TEST_TEAR_DOWN(tests_lshift_16u){}
//
//// nmppsLShiftC_16u
//
//// Нулевые указатели
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_null_ptr){
//
//	nmpps16u vec[2];
//
//    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16u(NULL, 2, vec, 1));
//    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsLShiftC_16u(vec, 2, NULL, 1));
//}
//
//// Некорректное знаечение длины вектора
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_err_len){
//
//	nmpps16u vec[2];
//
//    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16u(vec, 2, vec, -1));
//    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsLShiftC_16u(vec, 2, vec, 0));
//}
//
//// Нечетная длина меньше 64 слова
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_less_64_non_parity){
//	unsigned int i = 0;
//
//	nmpps16u* src = get_ptr_src_vector_16u();
//	nmpps16u* dst = get_ptr_dst_vector_16u();
//	nmpps16u* etalon = get_ptr_etalon_vector_16u();
//
//	init_vector_value_16u(src, 1, 63);
//	init_vector_value_16u(dst, 0, 63);
//	init_vector_value_16u(etalon, 1024, 63);
//
//	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 10, dst, 63));
//
//	for(i= 0; i < 63; i++){
//		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
//	}
//}
//
//// Четная длина меньше 64 слова
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_less_64_parity){
//	unsigned int i = 0;
//
//	nmpps16u* src = get_ptr_src_vector_16u();
//	nmpps16u* dst = get_ptr_dst_vector_16u();
//	nmpps16u* etalon = get_ptr_etalon_vector_16u();
//
//	init_vector_value_16u(src, 1, 62);
//	init_vector_value_16u(dst, 0, 62);
//	init_vector_value_16u(etalon, 512, 62);
//
//    TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 9, dst, 62));
//
//	for(i= 0; i < 62; i++){
//	  TEST_ASSERT_EQUAL(dst[i], etalon[i]);
//	}
//}
//
//// Кратно 64 словам
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_64){
//	unsigned int i = 0;
//
//	nmpps16u* src = get_ptr_src_vector_16u();
//	nmpps16u* dst = get_ptr_dst_vector_16u();
//	nmpps16u* etalon = get_ptr_etalon_vector_16u();
//
//	init_vector_value_16u(src, 1, 320);
//	init_vector_value_16u(dst, 0, 320);
//	init_vector_value_16u(etalon, 256, 320);
//
//	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 8, dst, 320));
//
//	for(i= 0; i < 320; i++){
//		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
//	}
//}
//
//// Нечетная длина больше 64 слов
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_over_64_non_parity){
//	unsigned int i = 0;
//
//	nmpps16u* src = get_ptr_src_vector_16u();
//	nmpps16u* dst = get_ptr_dst_vector_16u();
//	nmpps16u* etalon = get_ptr_etalon_vector_16u();
//
//	init_vector_value_16u(src, 1, 321);
//	init_vector_value_16u(dst, 0, 321);
//	init_vector_value_16u(etalon, 128, 321);
//
//	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 7, dst, 321));
//
//	for(i= 0; i < 321; i++){
//		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
//	}
//}
//
//// Четная длина больше 64 слов
//TEST(tests_lshift_16u, test_nmppsLShiftC_16u_over_64_parity){
//	unsigned int i = 0;
//
//	nmpps16u* src = get_ptr_src_vector_16u();
//	nmpps16u* dst = get_ptr_dst_vector_16u();
//	nmpps16u* etalon = get_ptr_etalon_vector_16u();
//
//	init_vector_value_16u(src, 1, 382);
//	init_vector_value_16u(dst, 0, 382);
//	init_vector_value_16u(etalon, 64, 382);
//
//	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsLShiftC_16u(src, 6, dst, 382));
//
//	for(i = 0; i < 382; i++){
//		TEST_ASSERT_EQUAL(dst[i], etalon[i]);
//	}
//}
//
//TEST_GROUP_RUNNER(tests_lshift_16u){
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_null_ptr);
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_err_len);
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_less_64_non_parity);
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_less_64_parity);
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_64);
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_over_64_non_parity);
//    RUN_TEST_CASE(tests_lshift_16u, test_nmppsLShiftC_16u_over_64_parity);
//}
