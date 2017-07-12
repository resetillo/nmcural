#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
//#include "stdlib.h"

float right_sqrtf(float x);
double right_sqrt(double x);

TEST_GROUP(tests_sqrt32f);
TEST_SETUP(tests_sqrt32f) {}
TEST_TEAR_DOWN(tests_sqrt32f) {}

TEST_GROUP(tests_sqrt64f);
TEST_SETUP(tests_sqrt64f) {}
TEST_TEAR_DOWN(tests_sqrt64f) {}


#define COUNT_ITERATION (100)

/**
 * @brief Заполнение значений тестовых векторов
 *
 * @param in вектор исходных данных
 * @param out вектор резултирующих данных
 * @param len длина векторов
 * @param bgn начальное значение для вектора исходных данных
 * @param step шаг инкрементации
 * */
void create_sqrt_vecs(nmpps64f* in, nmpps64f* out, unsigned int len,
					  nmpps64f bgn, nmpps64f step)
{
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		out[i] = right_sqrt(in[i]);
		bgn += step;
	}
}

void create_sqrtf_vecs(nmpps32f* in, nmpps32f* out, unsigned int len,
					  nmpps32f bgn, nmpps32f step)
{
	int i;
	for(i=0; i<len; i++){
		in[i] = bgn;
		out[i] = right_sqrtf(in[i]);
		bgn += step;
	}
}



const nmpps64f sqrt_critical_error = 10e-14;//<Значение максимальной погрешности для формата двойной точности в %
const nmpps32f sqrtf_critical_error = 10e-05;//<Значение максимальной погрешности для формата одинарной точности в %

/**
 * @brief Проверка диапазона тестовых значений
 *
 * @param bgn начальное значение
 * @param step шаг инкрементации
 * @param count количество проверяемых значений
 * */
nmppsStatus test_sqrt_diap(nmpps64f bgn, nmpps64f step, int count){
	nmpps64f in[count];
	nmpps64f res[count];
	nmpps64f kd[count];
	nmppsStatus stat;
	double er;
	double arg = bgn;
	double max_err = 0;
	int i;
	//Заполнение входных и эталонных данных
	create_sqrt_vecs(in, kd, count, arg, step);
	//Расчет проверяемых значений
	stat = nmppsSqrt_64f(in, res, count);
	//Проверка полученных данных с эталоном
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<count; i++){
		arg = in[i];
		er = fabs(fabs(kd[i])-fabs(res[i]));
		if (kd[i] != 0) er = fabs(100*er/kd[i]);
		if (er > max_err) {
			max_err = er;
			if (max_err > sqrt_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}

nmppsStatus test_sqrtf_diap(nmpps32f bgn, nmpps32f step, int count){
	nmpps32f in[count];
	nmpps32f res[count];
	nmpps32f kd[count];
	nmppsStatus stat;
	nmpps32f er;
	nmpps32f arg = bgn;
	nmpps32f max_err = 0;
	int i = 0;
	//Заполнение входных и эталонных данных
	create_sqrtf_vecs(in, kd, count, arg, step);
	//Расчет проверяемых значений
	stat = nmppsSqrt_32f(in, res, count);
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	//Проверка полученных данных с эталоном
	for(i=0;i<count;i++){
		arg = in[i];
		er = fabsf(kd[i]-res[i]);
		if (kd[i] != 0) er = fabsf(100*er/kd[i]);
		if (er > max_err) {
			max_err = er;
			//max_err_arg = arg;
			if (max_err > sqrtf_critical_error) {
				return i+1;
			}
		}

	}

	return nmppsStsNoErr;
}


TEST(tests_sqrt64f, nmppsSqrt64f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(0.133377,
			              0.123, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(133.377,
			              12.3, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(1.77789,
			              0.197, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(337.7789,
			              12.3, 32));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(189.133,
			              0.123, 33));
}

TEST(tests_sqrt32f, nmppsSqrt32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(1.77789,
			              0.197, 3));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(0.133377,
			              0.123, 1));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(133.377,
			              12.3, 2));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(337.7789,
			              12.3, 64));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(189.133,
			              0.123, 65));
}


TEST(tests_sqrt64f, nmppsSqrt64f_calculation){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(0, 0.133377789, COUNT_ITERATION));

	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(1.7789e+300, 13.337e+300, COUNT_ITERATION));

	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrt_diap(3.3333e-300, 1.3337e-300, COUNT_ITERATION));
}

TEST(tests_sqrt32f, nmppsSqrt32f_calculation){
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(0, 0.133377789, COUNT_ITERATION));

	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(1.7789e+38, -1.3337e+38*(1/COUNT_ITERATION), COUNT_ITERATION));

	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_sqrtf_diap(3.3333e-38, -1.7777e-38*(1/COUNT_ITERATION), COUNT_ITERATION));
}


nmpps64f data_sqrt_neg[] = {
		4,  9, -4, -9
};

TEST(tests_sqrt64f, nmppsSqrt64f_check_answer){
	nmpps64f data[sizeof(data_sqrt_neg)/sizeof(nmpps64f)];
	TEST_ASSERT_EQUAL(nmppsStsSqrtNegArg, nmppsSqrt_64f(data_sqrt_neg, data, sizeof(data_sqrt_neg)/sizeof(nmpps64f)));

	//не прошла проверка на NULL
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqrt_64f(data, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqrt_64f(NULL, data, 1));

	//не прошла проверка на некорректную длину вектора
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqrt_64f(data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqrt_64f(data, data, -1));
}

nmpps32f data_sqrtf_neg[] = {
		4,  9, -4, -9
};

TEST(tests_sqrt32f, nmppsSqrt32f_check_answer){
	nmpps32f data[sizeof(data_sqrtf_neg)/sizeof(nmpps32f)];
	TEST_ASSERT_EQUAL(nmppsStsSqrtNegArg, nmppsSqrt_32f(data_sqrtf_neg, data, sizeof(data_sqrtf_neg)/sizeof(nmpps32f)));

	//не прошла проверка на NULL
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqrt_32f(data, NULL, 1));
	TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsSqrt_32f(NULL, data, 1));

	//не прошла проверка на некорректную длину вектора
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqrt_32f(data, data, 0));
	TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsSqrt_32f(data, data, -1));
}


TEST(tests_sqrt64f, nmppsSqrt64f_check_rewrite){
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
		nmppsSqrt_64f(&data[1], &out[1], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps64f); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL_DOUBLE(data[k], original[k]);
			}
		}
		if (out[0]!=t.dbl) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL_DOUBLE(0, i);
		}
		if (out[i+1]!=t.dbl) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL_DOUBLE(0, i);
		}
	}

}


TEST(tests_sqrt32f, nmppsSqrt32f_check_rewrite){
	int i,k;
	nmpps32f data[68], original[68], out[68];
	fltint_t t;
	t.ui32 = 0xDEADBEEF;
	original[0] = data[0] = out[0] = t.flt;
	original[1] = data[1] = out[1] = t.flt;
	for(i=1;i<68;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = t.flt;
	}

	for(i=1;i<=65;i++){
		nmppsSqrt_32f(&data[2], &out[2], i);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			if (data[k]!=original[k]) {
				//Произошло искажение входных данных
				TEST_ASSERT_EQUAL_FLOAT(data[k], original[k]);
			}
		}
		if (out[0]!=t.flt || out[1]!=t.flt) {
			//Затерты данные перед выходным вектором
			TEST_ASSERT_EQUAL(i, -1);
		}
		if (out[i+2]!=t.flt) {
			//Затерты данные после выходного вектора
			TEST_ASSERT_EQUAL(i, -1);
		}
	}

}

TEST_GROUP_RUNNER(tests_sqrt64f){
    RUN_TEST_CASE(tests_sqrt64f, nmppsSqrt64f_check_answer);
    RUN_TEST_CASE(tests_sqrt64f, nmppsSqrt64f_check_rewrite);
    RUN_TEST_CASE(tests_sqrt64f, nmppsSqrt64f_small_vecs);
    RUN_TEST_CASE(tests_sqrt64f, nmppsSqrt64f_calculation);
}

TEST_GROUP_RUNNER(tests_sqrt32f){
    RUN_TEST_CASE(tests_sqrt32f, nmppsSqrt32f_check_answer);
    RUN_TEST_CASE(tests_sqrt32f, nmppsSqrt32f_check_rewrite);
    RUN_TEST_CASE(tests_sqrt32f, nmppsSqrt32f_small_vecs);
    RUN_TEST_CASE(tests_sqrt32f, nmppsSqrt32f_calculation);
}


