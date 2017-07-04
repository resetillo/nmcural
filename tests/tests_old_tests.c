#include "unity_fixture.h"

#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"

TEST_GROUP(tests_old_tests);

TEST_SETUP(tests_old_tests) {}
TEST_TEAR_DOWN(tests_old_tests) {}



TEST(tests_old_tests, test_atan) {
	TEST_ASSERT_EQUAL(0, test_atan());
}

TEST(tests_old_tests, test_atanf) {
	TEST_ASSERT_EQUAL(0, test_atanf());
}


TEST(tests_old_tests, test_vec_handler32) {
	TEST_ASSERT_EQUAL(0, test_vec_handler32());
}


TEST_GROUP_RUNNER(tests_old_tests) {
    RUN_TEST_CASE(tests_old_tests, test_vec_handler32);
    RUN_TEST_CASE(tests_old_tests, test_atan);
    RUN_TEST_CASE(tests_old_tests, test_atanf);
}
