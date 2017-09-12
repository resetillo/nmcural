#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include <math.h>

#if KaiserTestEnable

TEST_GROUP(tests_kaiser_32f);
TEST_SETUP(tests_kaiser_32f) {}
TEST_TEAR_DOWN(tests_kaiser_32f) {}

static nmpps32f z[8] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
};

static nmpps32f ans[8] = {
		0.135534, 0.429046, 0.755146, 0.970290,
		0.970290, 0.755146, 0.429046, 0.135534
};

#define DATA_SIZE (sizeof(z) / sizeof(nmpps32f))

int test1_kaiser_32f(){
	float res[DATA_SIZE];
	float err = 0;
	int i;
	nmppsWinKaiser_32f(z,res, DATA_SIZE, 3.5);
	for (i=0; i<DATA_SIZE; i++) {
		err = ans[i] - res[i];
		if (ans[i] > 0 && isnormal(ans[i])) {
			err /= fabs(ans[i]);
			err *= 100; //procents
		}
		if (fabsf(err) > 1.0e-03) {
			TEST_ASSERT_EQUAL(0, i+1);
			return i+1;
		}
	}

	return 0;
}



static const float kaiser_data65[65] =
{
1.827921E-01,   2.115811E-01,   2.415615E-01,   2.726264E-01,
3.046600E-01,   3.375375E-01,   3.711265E-01,   4.052872E-01,
4.398737E-01,   4.747341E-01,   5.097124E-01,   5.446485E-01,
5.793798E-01,   6.137421E-01,   6.475704E-01,   6.807001E-01,
7.129682E-01,   7.442141E-01,   7.742807E-01,   8.030157E-01,
8.302721E-01,   8.559095E-01,   8.797951E-01,   9.018044E-01,
9.218221E-01,   9.397426E-01,   9.554715E-01,   9.689251E-01,
9.800319E-01,   9.887328E-01,   9.949811E-01,   9.987436E-01,
1.000000E+00,   9.987436E-01,   9.949811E-01,   9.887328E-01,
9.800319E-01,   9.689251E-01,   9.554715E-01,   9.397426E-01,
9.218221E-01,   9.018044E-01,   8.797951E-01,   8.559095E-01,
8.302721E-01,   8.030157E-01,   7.742807E-01,   7.442141E-01,
7.129682E-01,   6.807001E-01,   6.475704E-01,   6.137421E-01,
5.793798E-01,   5.446485E-01,   5.097124E-01,   4.747341E-01,
4.398737E-01,   4.052872E-01,   3.711265E-01,   3.375375E-01,
3.046600E-01,   2.726264E-01,   2.415615E-01,   2.115811E-01,
1.827921E-01
};

int test2_kaiser_32f(){
	float in[sizeof(kaiser_data65)/sizeof(float)];
	float out[sizeof(in)/sizeof(float)];
	float err = 0;
	int i;
	for (i=0; i<sizeof(in)/sizeof(float); i++) {
		in[i] = 1;
	}
	nmppsWinKaiser_32f(in, out, sizeof(in)/sizeof(float), 3.14);
	for (i=0; i<sizeof(in)/sizeof(float); i++) {
		err = kaiser_data65[i] - out[i];
		err /= kaiser_data65[i];
		err *= 100; //procents
		if (fabsf(err) > 1.0e-03) {
			TEST_ASSERT_EQUAL(0, i+1);
			return i+1;
		}
	}

	return 0;
}


TEST(tests_kaiser_32f, kaiser_32f_calculation){
	TEST_ASSERT_EQUAL(0, test1_kaiser_32f());
	TEST_ASSERT_EQUAL(0, test2_kaiser_32f());
}


TEST(tests_kaiser_32f, kaiser_32f_check_answer) {
	nmpps32f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinKaiser_32f(0, tmp, 2, 0));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsWinKaiser_32f(tmp, 0, 2, 0));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_32f(tmp, tmp, 1, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_32f(tmp, tmp, 0, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsWinKaiser_32f(tmp, tmp, -1, 0));
}

TEST(tests_kaiser_32f, kaiser_32f_check_rewrite){
	int i,k;
	nmpps32f data[68], original[68];
	nmpps32f out[68];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;


	//TEST_ASSERT_EQUAL(0, 1);

	original[0] = data[0] = out[0] =
	original[1] = data[1] = out[1] = t.flt;
	for(i=2;i<sizeof(data)/sizeof(nmpps32f);i++){
		data[i] = original[i]= (nmpps32f)(i*i);
		out[i] = t.flt;
	}

	for(i=1;i<=65;i++){
		nmppsWinKaiser_32f(&data[2], &out[2], i, 3.3);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0]!=t.flt || out[1]!=t.flt) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+2]!=t.flt) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
	i = 0;
}

TEST_GROUP_RUNNER(tests_kaiser_32f){
    RUN_TEST_CASE(tests_kaiser_32f, kaiser_32f_calculation);
    RUN_TEST_CASE(tests_kaiser_32f, kaiser_32f_check_answer);
    RUN_TEST_CASE(tests_kaiser_32f, kaiser_32f_check_rewrite);
}

#endif
