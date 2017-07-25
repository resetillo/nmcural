#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"



TEST_GROUP(tests_normalize64);
TEST_SETUP(tests_normalize64) {}
TEST_TEAR_DOWN(tests_normalize64) {}

nmpps64f input[100];
nmpps64f output[100];
nmpps64f kd[100];

#define COUNT_ITERATION (100)
const nmpps64f normalize64_critical_error = 1e-13;


void create_normalize64_vecs(nmpps64f* in, nmpps64f bgnIn, nmpps64f stepIn,
					 nmpps64f* kd, unsigned int size, nmpps64f vSub, nmpps64f vDiv)
{
	int i;
	for(i=0; i<size; i++){
		in[i] = bgnIn;
		kd[i] =  (in[i] - vSub)/ vDiv;
		bgnIn += stepIn;
	}
}

void create_normalize64fc_vecs(nmpps64fc* in, nmpps64fc bgnIn, nmpps64fc stepIn,
					 nmpps64fc* kd, unsigned int size, nmpps64fc vSub, nmpps64f vDiv)
{
	int i;
	for(i=0; i<size; i++){
		in[i] = bgnIn;
		kd[i].re =  (in[i].re - vSub.re)/ vDiv;
		kd[i].im =  (in[i].im - vSub.im)/ vDiv;
		bgnIn.re += stepIn.re;
		bgnIn.im += stepIn.im;
	}
}


nmppsStatus test_normalize64_diap(nmpps64f bgnIn, nmpps64f stepIn,
		    					  unsigned int size, nmpps64f vSub, nmpps64f vDiv){
	nmppsStatus stat;
	double er, max_err;
	int i;
	//Создаем эталонные значения
	create_normalize64_vecs(input, bgnIn, stepIn,
						 kd, size, vSub, vDiv);
	//Производим рассчеты
	stat = nmppsNormalize_64f(input, output, size, vSub, vDiv);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<size; i++){
		er = fabs(kd[i]-output[i]);
		if (kd[i] != 0) er = fabs(100*er/kd[i]);

		if (er > max_err) {
			max_err = er;
			if (max_err > normalize64_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}

nmppsStatus test_normalize64fc_diap(nmpps64fc bgnIn, nmpps64fc stepIn,
		    					  unsigned int size, nmpps64fc vSub, nmpps64f vDiv){
	nmpps64fc er, max_err= {0, 0};
	nmppsStatus stat;
	int i;
	nmpps64fc* inputfc = (nmpps64fc*)input;
	nmpps64fc* outputfc = (nmpps64fc*)output;
	nmpps64fc* kdfc = (nmpps64fc*)kd;
	//Создаем эталонные значения
	create_normalize64fc_vecs(inputfc, bgnIn, stepIn,
						 kdfc, size, vSub, vDiv);
	//Производим рассчеты
	stat = nmppsNormalize_64fc(inputfc, outputfc, size, vSub, vDiv);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<size; i++){
		er.re = fabs(kdfc[i].re-outputfc[i].re);
		er.im = fabs(kdfc[i].im-outputfc[i].im);
		if (kdfc[i].re != 0){
			er.re = fabs(100*er.re/kdfc[i].re);
		}
		if (kdfc[i].im != 0){
			er.im = fabs(100*er.im/kdfc[i].im);
		}

		if (er.re > max_err.re) {
			max_err.re = er.re;
			if (max_err.re > normalize64_critical_error) {
				return i+1;
			}
		}
		if (er.im > max_err.im) {
			max_err.im = er.im;
			if (max_err.im > normalize64_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}


//Обычные значения
TEST(tests_normalize64, nmppsNormalize_64f_Calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize64_diap(1.3, 0.01234567,
			COUNT_ITERATION, 0.777, 0.1937));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize64_diap(7.77e+300, -0.987654321e+300,
			COUNT_ITERATION, -7.771e+300, -0.1991e+126));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize64_diap(-7.77e-300, 0.987654321e-300,
			COUNT_ITERATION, 7.771e-300, 0.1991e-126));
}

TEST(tests_normalize64, nmppsNormalize_64fc_Calculation) {
	nmpps64fc bgnIn = {1.77, 1.33},
			  stepIn = {0.0123456789, 0.0987654321},
			  vSub = {0.0777, 777.321};
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize64fc_diap(bgnIn, stepIn, COUNT_ITERATION/2, vSub, 0.1937));

	bgnIn.re = 7.77e+300; bgnIn.im = -7.77e-300;
    stepIn.re = -0.987654321e+300; stepIn.im = 0.987654321e-300;
    vSub.re = -7.771e+300; vSub.im = 7.771e-300;
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize64fc_diap(bgnIn, stepIn, COUNT_ITERATION/2, vSub, -0.1991e+126));
}


//Проверка возвращаемых результатов
TEST(tests_normalize64, nmppsNormalize_64f_check_answer) {
	nmppsStatus stat;

	stat = nmppsNormalize_64f(input, output, sizeof(input)/sizeof(nmpps64f), 3.14, 0);
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_64f(NULL, output, 1, 0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_64f(input, NULL, 1, 0, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_64f(input, output, 0, 0, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_64f(input, output, -1, 0, 1));
}

TEST(tests_normalize64, nmppsNormalize_64fc_check_answer) {
	nmpps64fc vSub = {1.77, 1.33};
	nmpps64fc* inputfc = (nmpps64fc*)input;
	nmpps64fc* outputfc = (nmpps64fc*)output;
	nmppsStatus stat;

	stat = nmppsNormalize_64fc(inputfc, outputfc, sizeof(input)/sizeof(nmpps64fc), vSub, 0);
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_64fc(NULL, outputfc, 1, vSub, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_64fc(inputfc, NULL, 1, vSub, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_64fc(inputfc, outputfc, 0, vSub, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_64fc(inputfc, outputfc, -1, vSub, 1));
}



TEST(tests_normalize64, nmppsNormalize_64f_check_rewrite) {
	int i;
	dblint_t t, t1;

	t.ui64 = 0xDEADBEEFDEADBEEF;
	input[0] = output[0] = kd[0] = t.dbl;
	for(i=1;i<100;i++){
		input[i] = kd[i] = i*i;
		output[i] = t.dbl;
	}

	for(i=0;i < (sizeof(output) / sizeof(nmpps64f))-2;i++){
		nmppsNormalize_64f(&input[1], &output[1], i+1, 1, 777);
		/*for(k=0; k < (sizeof(output) / sizeof(nmpps64f)); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_DOUBLE(input[k], kd[k]);
		}*/
		TEST_ASSERT_EQUAL_DOUBLE_ARRAY(input, kd, sizeof(output) / sizeof(nmpps64f));
		//Запись перед началом
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, output[0]);
		//Запись после окончания векторов
		t1.dbl = output[i+2];
		if (t.ui64 != t1.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}

TEST(tests_normalize64, nmppsNormalize_64fc_check_rewrite) {
	int i;
	dblint_t t, t1, t2;
	nmpps64fc* inputfc = (nmpps64fc*)input;
	nmpps64fc* outputfc = (nmpps64fc*)output;
	nmpps64fc* kdfc = (nmpps64fc*)kd;

	nmpps64fc vSub = {0.1, -0.1};

	t.ui64 = 0xDEADBEEFDEADBEEF;
	inputfc[0].re = outputfc[0].re = kdfc[0].re =
			inputfc[0].im = outputfc[0].im = kdfc[0].im = t.dbl;
	for(i=1;i<50;i++){
		inputfc[i].re = kdfc[i].re = inputfc[i].im = kdfc[i].im = i*i;
		outputfc[i].re = outputfc[i].im = t.dbl;
	}

	for(i=0;i < (sizeof(output) / sizeof(nmpps64fc))-2;i++){
		nmppsNormalize_64fc(&inputfc[1], &outputfc[1], i+1, vSub, 777);
		/*for(k=0; k < (sizeof(output) / sizeof(nmpps64f)); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_DOUBLE(input[k], kd[k]);
		}*/
		TEST_ASSERT_EQUAL_DOUBLE_ARRAY(inputfc, kdfc, sizeof(output) / sizeof(nmpps64f));
		//Запись перед началом
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, outputfc[0].re);
		TEST_ASSERT_EQUAL_DOUBLE(t.dbl, outputfc[0].im);
		//Запись после окончания векторов
		t1.dbl = outputfc[i+2].re;
		t2.dbl = outputfc[i+2].im;
		if (t.ui64 != t1.ui64 || t.ui64 != t2.ui64) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}


TEST_GROUP_RUNNER(tests_normalize64){
    RUN_TEST_CASE(tests_normalize64, nmppsNormalize_64f_Calculation);
    RUN_TEST_CASE(tests_normalize64, nmppsNormalize_64f_check_answer);
    RUN_TEST_CASE(tests_normalize64, nmppsNormalize_64f_check_rewrite);

    RUN_TEST_CASE(tests_normalize64, nmppsNormalize_64fc_Calculation);
    RUN_TEST_CASE(tests_normalize64, nmppsNormalize_64fc_check_answer);
    RUN_TEST_CASE(tests_normalize64, nmppsNormalize_64fc_check_rewrite);

}
