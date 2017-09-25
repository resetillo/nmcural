#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include <math.h>

#if KaiserTestEnable

TEST_GROUP(tests_kaiser_32fc);
TEST_SETUP(tests_kaiser_32fc) {}
TEST_TEAR_DOWN(tests_kaiser_32fc) {}



extern const float kaiser_data65[65];

int test_kaiser_32fc(){
#define DATA_SIZE (sizeof(kaiser_data65)/sizeof(float))
	nmpps32fc in[DATA_SIZE];
	nmpps32fc out[DATA_SIZE];
	nmpps32fc kd[DATA_SIZE];
	float tmp, err = 0;
	int i;
	for (i=0; i<DATA_SIZE; i++) {
		in[i].re = 2*i;
		in[i].im = 2*i + 1;
		kd[i].re = in[i].re*kaiser_data65[i];
		kd[i].im = in[i].im*kaiser_data65[i];
	}
	nmppsWinKaiser_32fc(in, out, DATA_SIZE, 3.14);
	for (i=0; i<DATA_SIZE; i++) {
		err = (kd[i].re - out[i].re)/kd[i].re;
		tmp = (kd[i].im - out[i].im)/kd[i].im;
		if (fabs(tmp) > fabs(err)) err = tmp;
		err *= 100; //procents
		if (fabsf(err) > 1.0e-03) {
			TEST_ASSERT_EQUAL(0, i+1);
			return i+1;
		}
	}

	return 0;
}


TEST(tests_kaiser_32fc, kaiser_32fc_calculation){
	TEST_ASSERT_EQUAL(0, test_kaiser_32fc());
}


TEST(tests_kaiser_32fc, kaiser_32fc_check_answer) {
	nmpps32fc tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinKaiser_32fc(0, tmp, 2, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinKaiser_32fc(tmp, 0, 2, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_32fc(tmp, tmp, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_32fc(tmp, tmp, 0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_32fc(tmp, tmp, -1, 0));
}

TEST(tests_kaiser_32fc, kaiser_32fc_check_rewrite){
	int i,k;
	nmpps32fc data[68], original[68];
	nmpps32fc out[68];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0].re = data[0].re = out[0].re =
	original[0].im = data[0].im = out[0].im = t.flt;
	for(i=1;i<sizeof(data)/sizeof(nmpps32fc);i++){
		data[i].re = original[i].re=
		data[i].im = original[i].im= (nmpps32f)(i*i);
		out[i].re = out[i].im = t.flt;
	}

	for(i=1;i<=65;i++){
		nmppsWinKaiser_32fc(&data[1], &out[1], i+1, 3.3);
		for(k=0; k < sizeof(data)/sizeof(nmpps32fc); k++){
			if (data[k].re!=original[k].re ||
				data[k].im!=original[k].im) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0].re!=t.flt || out[0].im!=t.flt) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+2].re!=t.flt || out[i+2].im!=t.flt) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
	i = 0;
}

TEST_GROUP_RUNNER(tests_kaiser_32fc){
    RUN_TEST_CASE(tests_kaiser_32fc, kaiser_32fc_calculation);
    RUN_TEST_CASE(tests_kaiser_32fc, kaiser_32fc_check_answer);
    RUN_TEST_CASE(tests_kaiser_32fc, kaiser_32fc_check_rewrite);
}

#endif
