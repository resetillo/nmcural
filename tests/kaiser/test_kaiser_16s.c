#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include <math.h>

#if KaiserTestEnable

TEST_GROUP(tests_kaiser_16s);
TEST_SETUP(tests_kaiser_16s) {}
TEST_TEAR_DOWN(tests_kaiser_16s) {}



extern const float kaiser_data65[65];

int test_kaiser_16s(){
#define DATA_SIZE (sizeof(kaiser_data65)/sizeof(float))
	nmpps16s in[DATA_SIZE];
	nmpps16s out[DATA_SIZE];
	nmpps16s kd[DATA_SIZE];
	int i;
	for (i=0; i<DATA_SIZE; i++) {
		in[i] = i;
		kd[i] = floorf(in[i]*kaiser_data65[i]);
	}
	nmppsWinKaiser_16s(in, out, DATA_SIZE, 3.14);
	for (i=0; i<DATA_SIZE; i++) {
		if (kd[i] != out[i]) {
			TEST_ASSERT_EQUAL(0, i+1);
			return i+1;
		}
	}

	return 0;
}


TEST(tests_kaiser_16s, kaiser_16s_calculation){
	TEST_ASSERT_EQUAL(0, test_kaiser_16s());
}


TEST(tests_kaiser_16s, kaiser_16s_check_answer) {
	nmpps16s tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinKaiser_16s(0, tmp, 2, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinKaiser_16s(tmp, 0, 2, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_16s(tmp, tmp, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_16s(tmp, tmp, 0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_16s(tmp, tmp, -1, 0));
}

TEST(tests_kaiser_16s, kaiser_16s_check_rewrite){
	int i,k;
	nmpps16s data[68], original[68];
	nmpps16s out[68];
	int t = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0] = data[0] = out[0] =
	original[1] = data[1] = out[1] = t;
	for(i=2;i<sizeof(data)/sizeof(nmpps16s);i++){
		data[i] = original[i]= (nmpps16s)(i*i);
		out[i] = t;
	}

	for(i=1;i<=65;i++){
		nmppsWinKaiser_16s(&data[2], &out[2], i, 3.3);
		for(k=0; k < sizeof(data)/sizeof(nmpps16s); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0]!=t || out[1]!=t) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+2]!=t) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
	i = 0;
}

TEST_GROUP_RUNNER(tests_kaiser_16s){
    RUN_TEST_CASE(tests_kaiser_16s, kaiser_16s_calculation);
    RUN_TEST_CASE(tests_kaiser_16s, kaiser_16s_check_answer);
    RUN_TEST_CASE(tests_kaiser_16s, kaiser_16s_check_rewrite);
}

#endif
