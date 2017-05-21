#include "unity/unity_fixture.h"

void runAllTests(void) {
    RUN_TEST_GROUP(tests_old_tests);
//    RUN_TEST_GROUP(tests_sqr);
    RUN_TEST_GROUP(tests_min);
    RUN_TEST_GROUP(tests_minindx);
    RUN_TEST_GROUP(tests_max);
    RUN_TEST_GROUP(tests_maxindx);
    RUN_TEST_GROUP(tests_minmax);
    RUN_TEST_GROUP(tests_minmaxindx);
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
