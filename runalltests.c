#include "unity/unity_fixture.h"
#include "include/nmpps.h"

#include "tests/test_proto.h"


void runAllTests(void) {

#if PhaseTestEnable
    RUN_TEST_GROUP(tests_phase32f);
    RUN_TEST_GROUP(tests_phase32fc);
    RUN_TEST_GROUP(tests_phase64f);
    RUN_TEST_GROUP(tests_phase64fc);
#endif

#if DivTestEnable
    RUN_TEST_GROUP(tests_div32);
    RUN_TEST_GROUP(tests_divC32);
    RUN_TEST_GROUP(tests_div64);
    RUN_TEST_GROUP(tests_divC64);
#endif

#if NormInfTestEnable
    RUN_TEST_GROUP(tests_norm_Inf_32f);
    RUN_TEST_GROUP(tests_norm_Inf_64f);
	RUN_TEST_GROUP(tests_norm_Inf_16s32f);
	RUN_TEST_GROUP(tests_norm_Inf_16s32s_Sfs);
#endif

#if NormL1TestEnable
    RUN_TEST_GROUP(tests_norm_L1_32f);
    RUN_TEST_GROUP(tests_norm_L1_64f);
	RUN_TEST_GROUP(tests_norm_L1_16s32f);
	RUN_TEST_GROUP(tests_norm_L1_16s32s_Sfs);
#endif

#if NormL2TestEnable
	RUN_TEST_GROUP(tests_norm_L2_16s32f);
	RUN_TEST_GROUP(tests_norm_L2_16s32s_Sfs);
#endif

#if NormDiffInfTestEnable
    RUN_TEST_GROUP(tests_normDiff_Inf_32f);
    RUN_TEST_GROUP(tests_normDiff_Inf_64f);
#endif

#if NormDiffL1TestEnable
    RUN_TEST_GROUP(tests_normDiff_L1_32f);
    RUN_TEST_GROUP(tests_normDiff_L1_64f);
	RUN_TEST_GROUP(tests_normDiff_L1_16s32f);
	RUN_TEST_GROUP(tests_normDiff_L1_16s32s_Sfs);
#endif

#if NormDiffL2TestEnable
	RUN_TEST_GROUP(tests_normDiff_L2_32f);
	RUN_TEST_GROUP(tests_normDiff_L2_64f);
	RUN_TEST_GROUP(tests_normDiff_L2_16s32s_Sfs);
	RUN_TEST_GROUP(tests_normDiff_L2_16s32f);
#endif

#if AtanTestEnable
    RUN_TEST_GROUP(tests_atan32f);
    RUN_TEST_GROUP(tests_atan64f);
#endif
#if SqrtTestEnable
    RUN_TEST_GROUP(tests_sqrt32f);
    RUN_TEST_GROUP(tests_sqrt64f);
#endif
#if NormalizeTestEnable
    RUN_TEST_GROUP(tests_normalize32);
    RUN_TEST_GROUP(tests_normalize64);
#endif

    RUN_TEST_GROUP(tests_mean);    RUN_TEST_GROUP(tests_conj);
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
    RUN_TEST_GROUP(tests_lshift);
    RUN_TEST_GROUP(tests_rshift);
	RUN_TEST_GROUP(tests_dotprod);
	RUN_TEST_GROUP(tests_sum);
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
