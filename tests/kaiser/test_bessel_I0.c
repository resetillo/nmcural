#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include <math.h>

#if KaiserTestEnable

TEST_GROUP(tests_bessel_I0_32f);
TEST_SETUP(tests_bessel_I0_32f) {}
TEST_TEAR_DOWN(tests_bessel_I0_32f) {}

static const nmpps32f z[] = {0, 0.2, 0.4, 0.6, 0.8, 1.0,
		   0.100000024703283e-316,
		   10.1,
		   57.1,
		   100.1

};

static const nmpps32f ans[] = {
		   1.000000000000000,
		   1.010025027795146,
		   1.040401782229341,
		   1.092045364317339,
		   1.166514922869803,
		   1.266065877752008,

		   1.0,
		   3.095975670788983e+03,
		   3.324804716307880e+23,
		   1.186084768843771e+42

};

#define DATA_SIZE (sizeof(z) / sizeof(nmpps32f))

nmppsStatus bessel_I0_32f(const nmpps32f* pSrc, nmpps32f* pDst, int len);


int test1_bessel_I0_32f(){
	float res[DATA_SIZE];
	float err = 0;
	int i;
	bessel_I0_32f(z,res, DATA_SIZE);
	for (i=0; i<DATA_SIZE - 1; i++) {
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

int test2_bessel_I0_32f(){
	float in[100];
	float out[100];
	float err = 0;
	int i;
	for (i=0; i<sizeof(in)/sizeof(float); i++) {
		in[i] = z[1];
	}
	bessel_I0_32f(in,out, sizeof(in)/sizeof(float));
	for (i=0; i<sizeof(in)/sizeof(float); i++) {
		err = ans[1] - out[i];
		err /= ans[1];
		err *= 100; //procents

		if (fabsf(err) > 1.0e-03) {
			TEST_ASSERT_EQUAL(0, i+1);
			return i+1;
		}
	}

	return 0;
}



static const float besdata1_70[70] = {
	1.266066E+00,   2.279585E+00,   4.880793E+00,   1.130192E+01,
	2.723987E+01,   6.723441E+01,   1.685939E+02,   4.275641E+02,
	1.093588E+03,   2.815717E+03,   7.288489E+03,   1.894893E+04,
	4.944449E+04,   1.294186E+05,   3.396494E+05,   8.934462E+05,
	2.354970E+06,   6.218412E+06,   1.644619E+07,   4.355828E+07,
	1.155140E+08,   3.066930E+08,   8.151421E+08,   2.168619E+09,
	5.774561E+09,   1.538898E+10,   4.104201E+10,   1.095346E+11,
	2.925206E+11,   7.816723E+11,   2.089963E+12,   5.590908E+12,
	1.496380E+13,   4.006858E+13,   1.073388E+14,   2.876668E+14,
	7.712455E+14,   2.068505E+15,   5.549743E+15,   1.489477E+16,
	3.998826E+16,   1.073895E+17,   2.884803E+17,   7.751560E+17,
	2.083414E+18,   5.601065E+18,   1.506154E+19,   4.051050E+19,
	1.089836E+20,   2.932554E+20,   7.892574E+20,   2.124593E+21,
	5.720234E+21,   1.540388E+22,   4.148790E+22,   1.117597E+23,
	3.011057E+23,   8.113724E+23,   2.186687E+24,   5.894077E+24,
	1.588934E+25,   4.284053E+25,   1.155210E+26,   3.115458E+26,
	8.403040E+26,   2.266746E+27,   6.115322E+27,   1.650003E+28,
	4.452432E+28,   1.201589E+29
};

int test3_bessel_I0_32f(){
	float in[sizeof(besdata1_70)/sizeof(float)];
	float out[sizeof(in)/sizeof(float)];
	float err = 0;
	int i,k;
	//init input data [1;70]]
	for (i=0; i<sizeof(in)/sizeof(float); i++) {
		in[i] = i+1;
	}
	for (k=1; k <= sizeof(in)/sizeof(float); k++){
		bessel_I0_32f(in,out, k);
		for (i=0; i<k; i++) {
			err = besdata1_70[i] - out[i];
			err /= besdata1_70[i];
			err *= 100; //procents

			if (fabsf(err) > 1.0e-03) {
				TEST_ASSERT_EQUAL(0, i+1);
				return i+1;
			}
		}
	}

	return 0;
}


TEST(tests_bessel_I0_32f, bessel_I0_32f_calculation){
	TEST_ASSERT_EQUAL(0, test3_bessel_I0_32f());
	TEST_ASSERT_EQUAL(0, test1_bessel_I0_32f());
	TEST_ASSERT_EQUAL(0, test2_bessel_I0_32f());
}


TEST(tests_bessel_I0_32f, bessel_I0_32f_check_answer) {
	nmpps32f tmp[1];

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, bessel_I0_32f(0, tmp, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, bessel_I0_32f(tmp, 0, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, bessel_I0_32f(tmp, tmp, 0));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, bessel_I0_32f(tmp, tmp, -1));
}

TEST(tests_bessel_I0_32f, bessel_I0_32f_check_rewrite){
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
		bessel_I0_32f(&data[2], &out[2], i);
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

TEST_GROUP_RUNNER(tests_bessel_I0_32f){
    RUN_TEST_CASE(tests_bessel_I0_32f, bessel_I0_32f_calculation);
    RUN_TEST_CASE(tests_bessel_I0_32f, bessel_I0_32f_check_answer);
    RUN_TEST_CASE(tests_bessel_I0_32f, bessel_I0_32f_check_rewrite);
}



#endif
