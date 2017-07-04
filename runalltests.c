#include "unity/unity_fixture.h"
#include "include/nmpps.h"



void runAllTests(void) {
    RUN_TEST_GROUP(tests_sqrt32f);
    RUN_TEST_GROUP(tests_sqrt64f);
    RUN_TEST_GROUP(tests_normalize32);
    RUN_TEST_GROUP(tests_normalize64);
    RUN_TEST_GROUP(tests_div32);
    RUN_TEST_GROUP(tests_divC32);
    RUN_TEST_GROUP(tests_div64);
    RUN_TEST_GROUP(tests_divC64);
    RUN_TEST_GROUP(tests_old_tests);

    RUN_TEST_GROUP(tests_sqr);
    RUN_TEST_GROUP(tests_min);
    RUN_TEST_GROUP(tests_minabs);
    RUN_TEST_GROUP(tests_minindx);
    RUN_TEST_GROUP(tests_minabsindx);
    RUN_TEST_GROUP(tests_max);
    RUN_TEST_GROUP(tests_maxindx);
    RUN_TEST_GROUP(tests_minmax);
    RUN_TEST_GROUP(tests_minmaxindx);
    RUN_TEST_GROUP(tests_move);
    RUN_TEST_GROUP(tests_copy);
    RUN_TEST_GROUP(tests_set);
    RUN_TEST_GROUP(tests_zero);
    RUN_TEST_GROUP(tests_abs);
    RUN_TEST_GROUP(tests_flip);

}

int main(void) {
	static const char *argv[] = {
			"runalltests.exe",
#if defined(UNITY_VERBOSE)
			"-v",
#endif
#if defined(UNITY_RETRIES)
			"-r",
			"2"
#endif
	};
	static const int argc = sizeof(argv) / sizeof(char*);

    return UnityMain(argc, argv, runAllTests);


}
