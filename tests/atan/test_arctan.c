#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
#include "math.h"

TEST_GROUP(tests_atan32f);
TEST_SETUP(tests_atan32f) {}
TEST_TEAR_DOWN(tests_atan32f) {}

TEST_GROUP(tests_atan64f);
TEST_SETUP(tests_atan64f) {}
TEST_TEAR_DOWN(tests_atan64f) {}


#define COUNT_ITERATION (100)

double right_atan(double x);
float right_atanf(float x);

/**
 * @brief Заполнение значений тестовых векторов
 *
 * @param in вектор исходных данных
 * @param out вектор резултирующих данных
 * @param len длина векторов
 * @param bgn начальное значение для вектора исходных данных
 * @param step шаг инкрементации
 * */
void create_atan_vecs(nmpps64f* in, nmpps64f* out, unsigned int len,
					  nmpps64f bgn, nmpps64f step)
{
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		out[i] = right_atan(in[i]);
		bgn += step;
	}
}


void create_atanf_vecs(nmpps32f* in, nmpps32f* out, unsigned int len,
					  nmpps32f bgn, nmpps32f step)
{
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		out[i] = right_atanf(in[i]);
		bgn += step;
	}
}


const nmpps64f atan_critical_error = 10e-15;//<Значение максимальной погрешности для формата двойной точности
const nmpps32f atanf_critical_error = 10e-07;//<Значение максимальной погрешности для формата одинарной точности


/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_atan_diap(nmpps64f bgn, nmpps64f step, int count){
	nmpps64f in[count];
	nmpps64f res[count];
	nmpps64f kd[count];
	nmpps64f er;
	nmpps64f arg = bgn;
	nmpps64f max_err = 0;
	int i = 0;
	nmppsStatus stat;
	//Заполнение входных и эталонных данных
	create_atan_vecs(in, kd, count, arg, step);
	//Расчет проверяемых значений
	stat = nmppsArctan_64f(in, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
			arg = in[i];
			er = fabs(fabs(kd[i])-fabs(res[i]));
			if (er > max_err) {
				max_err = er;
				if (max_err > atan_critical_error) {
					return i+1;
				}
			}
	}
	return nmppsStsNoErr;
}

nmppsStatus test_atanf_diap(nmpps32f bgn, nmpps32f step, int count){
	nmpps32f in[count];
	nmpps32f res[count];
	nmpps32f kd[count];
	nmppsStatus stat;
	nmpps32f er;
	nmpps32f arg = bgn;
	nmpps32f max_err = 0;
	int i = 0;
	//Заполнение входных и эталонных данных
	create_atanf_vecs(in, kd, count, arg, step);
	//Расчет проверяемых значений
	stat = nmppsArctan_32f(in, res, count);
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
		arg = in[i];
		er = fabsf(fabsf(kd[i])-fabsf(res[i]));
		if (er > max_err) {
			max_err = er;
			if (max_err > atanf_critical_error) {
				return i + 1;
			}
		}

	}

	return nmppsStsNoErr;
}


TEST(tests_atan64f, nmppsArctan64f_check_answer){
	nmpps64f data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsArctan_64f(data, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsArctan_64f(NULL, data, 1));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsArctan_64f(data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsArctan_64f(data, data, -1));

}

TEST(tests_atan32f, nmppsArctan32f_check_answer){
	nmpps32f data[1];
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsArctan_32f(data, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsArctan_32f(NULL, data, 1));

	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsArctan_32f(data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsArctan_32f(data, data, -1));

}

TEST(tests_atan64f, nmppsArctan64f_check_rewrite){
	int i,k;
	nmpps64f data[35], original[35], out[35];
	dblint_t t;
	t.ui64 = 0xDEADBEEFDEADBEEF;

	original[0] = data[0] = out[0] = t.dbl;
	for(i=1;i<35;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.dbl;
	}

	for(i=1;i<34;i++){
		nmppsArctan_64f(&data[1], &out[1], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps64f); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0, i);
			}
		}
		if (out[0]!=t.dbl) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0, i);
		}
		if (out[i+1]!=t.dbl) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0, i);
		}
	}
}



TEST(tests_atan32f, nmppsArctan32f_check_rewrite){
	int i,k;
	nmpps32f data[70], original[70], out[70];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;
	original[0] = data[0] = out[0] = t.flt;
	original[1] = data[1] = out[1] = t.flt;
	for(i=2;i<sizeof(data)/sizeof(nmpps32f);i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.flt;
	}

	for(i=1;i<66;i++){
		nmppsArctan_32f(&data[2], &out[2], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL(0,i);
			}
		}
		if (out[0]!=t.flt || out[1]!=t.flt) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(0,i);
		}
		if (out[i+2]!=t.flt) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(0,i);
		}
	}

}

TEST(tests_atan64f, nmppsArctan64f_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(0, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(0, 0.1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(0, 0.01, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(0, 0.001, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(0, 0.0001, 33));
}

TEST(tests_atan32f, nmppsArctan32f_small_vecs){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(0, 1, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(0, 0.1, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(0, 0.01, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(0, 0.001, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(0, 0.0001, 65));
}

TEST(tests_atan64f, nmppsArctan64f_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(-40, ((double)87/(double)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(1.9875e+300, 17.937, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(-1.7789e+300, -13.337, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(3.3333e-300, 1.3337e-300, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atan_diap(-7.7777e-300, -1.7777e-300, COUNT_ITERATION));
}

TEST(tests_atan32f, nmppsArctan32f_calculation){
	//Проверка нормальных значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(-50, ((float)87/(float)COUNT_ITERATION), COUNT_ITERATION));

	//Проверка больших значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(1.9875e+38, 17.937, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(-1.7789e+38, -13.337, COUNT_ITERATION));

	//Проверка близких к 0 значений
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(3.3333e-38, 1.3337e-38, COUNT_ITERATION));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_atanf_diap(-7.7777e-38, -1.7777e-38, COUNT_ITERATION));
}

TEST(tests_atan64f, nmppsArctan64f_subnormal){
	nmpps64f data[4] = {
			NAN, -NAN, INFINITY, -INFINITY
	};
	nmpps64f kd[4] = {
			NAN, -NAN, 1.5707963267948966192313216916398, -1.5707963267948966192313216916398
	};
	nmpps64f res[4];
	dblint_t t1, t2;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsArctan_64f(&data, &res, 4));
	for (int i =0;i<4;i++){
		t1.dbl = kd[i];
		t2.dbl = res[i];
		if (t1.ui64 != t2.ui64){
			TEST_ASSERT_EQUAL(-1, i);
		}
	}

}

TEST(tests_atan32f, nmppsArctan32f_subnormal){
	nmpps32f data[4] = {
			NAN, -NAN, INFINITY, -INFINITY
	};
	nmpps32f kd[4] = {
			NAN, -NAN, 1.57079633, -1.57079633
	};
	nmpps32f res[4];
	fltint_t t1, t2;
	TEST_ASSERT_EQUAL(nmppsStsNoErr, nmppsArctan_32f(&data, &res, 4));
	for (int i =0;i<4;i++){
		t1.flt = kd[i];
		t2.flt = res[i];
		if (t1.ui32!= t2.ui32){
			TEST_ASSERT_EQUAL(-1, i);
		}
	}

}

TEST_GROUP_RUNNER(tests_atan64f){
    RUN_TEST_CASE(tests_atan64f, nmppsArctan64f_check_answer);
    RUN_TEST_CASE(tests_atan64f, nmppsArctan64f_check_rewrite);
    RUN_TEST_CASE(tests_atan64f, nmppsArctan64f_small_vecs);
    RUN_TEST_CASE(tests_atan64f, nmppsArctan64f_calculation);
    RUN_TEST_CASE(tests_atan64f, nmppsArctan64f_subnormal);
}


TEST_GROUP_RUNNER(tests_atan32f){
    RUN_TEST_CASE(tests_atan32f, nmppsArctan32f_check_answer);
    RUN_TEST_CASE(tests_atan32f, nmppsArctan32f_check_rewrite);
    printf("LABEL 0");
    RUN_TEST_CASE(tests_atan32f, nmppsArctan32f_small_vecs);
    printf("LABEL 1");
    RUN_TEST_CASE(tests_atan32f, nmppsArctan32f_calculation);
    printf("LABEL 2");
    RUN_TEST_CASE(tests_atan32f, nmppsArctan32f_subnormal);
    printf("LABEL 3");
}
