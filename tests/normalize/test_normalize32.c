#include "unity/unity_fixture.h"
#include "nmpps.h"
#include "tests/test_proto.h"



TEST_GROUP(tests_normalize32);
TEST_SETUP(tests_normalize32) {}
TEST_TEAR_DOWN(tests_normalize32) {}

nmpps32f input32f_[100];
nmpps32f output32f_[100];
nmpps32f kd32f_[100];

#define COUNT_ITERATION (100)
const nmpps32f normalize32_critical_error = 1e-04;


void create_normalize32_vecs(nmpps32f* in, nmpps32f bgnIn, nmpps32f stepIn,
					 nmpps32f* kd32f_, unsigned int size, nmpps32f vSub, nmpps32f vDiv)
{
	int i;
	for(i=0; i<size; i++){
		in[i] = bgnIn;
		kd32f_[i] =  (in[i] - vSub)/ vDiv;
		bgnIn += stepIn;
	}
}

void create_normalize32fc_vecs(nmpps32fc* in, nmpps32fc bgnIn, nmpps32fc stepIn,
					 nmpps32fc* kd32f_, unsigned int size, nmpps32fc vSub, nmpps32f vDiv)
{
	int i;
	for(i=0; i<size; i++){
		in[i] = bgnIn;
		kd32f_[i].re =  (in[i].re - vSub.re)/ vDiv;
		kd32f_[i].im =  (in[i].im - vSub.im)/ vDiv;
		bgnIn.re += stepIn.re;
		bgnIn.im += stepIn.im;
	}
}


nmppsStatus test_normalize32_diap(nmpps32f bgnIn, nmpps32f stepIn,
		    					  unsigned int size, nmpps32f vSub, nmpps32f vDiv){
	nmppsStatus stat;
	double er, max_err;
	int i;
	//Создаем эталонные значения
	create_normalize32_vecs(input32f_, bgnIn, stepIn,
						 kd32f_, size, vSub, vDiv);
	//Производим рассчеты
	stat = nmppsNormalize_32f(input32f_, output32f_, size, vSub, vDiv);
	//Проверяем результат
	if (stat!=nmppsStsNoErr) {
		return stat;
	}
	for (i=0; i<size; i++){
		er = fabs(kd32f_[i]-output32f_[i]);
		if (kd32f_[i] != 0) er = fabs(100*er/kd32f_[i]);

		if (er > max_err) {
			max_err = er;
			if (max_err > normalize32_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}

nmppsStatus test_normalize32fc_diap(nmpps32fc bgnIn, nmpps32fc stepIn,
		    					  unsigned int size, nmpps32fc vSub, nmpps32f vDiv){
	nmpps32fc er, max_err= {0, 0};
	nmppsStatus stat;
	int i;
	nmpps32fc* input32f_fc = (nmpps32fc*)input32f_;
	nmpps32fc* output32f_fc = (nmpps32fc*)output32f_;
	nmpps32fc* kd32f_fc = (nmpps32fc*)kd32f_;
	//Создаем эталонные значения
	create_normalize32fc_vecs(input32f_fc, bgnIn, stepIn,
						 kd32f_fc, size, vSub, vDiv);
	//Производим рассчеты
	stat = nmppsNormalize_32fc(input32f_fc, output32f_fc, size, vSub, vDiv);
	//Проверяем результат
	if (stat!=nmppsStsNoErr){
		return stat;
	}
	for (i=0; i<size; i++){
		er.re = fabs(kd32f_fc[i].re-output32f_fc[i].re);
		er.im = fabs(kd32f_fc[i].im-output32f_fc[i].im);
		if (kd32f_fc[i].re != 0){
			er.re = fabs(100*er.re/kd32f_fc[i].re);
		}
		if (kd32f_fc[i].im != 0){
			er.im = fabs(100*er.im/kd32f_fc[i].im);
		}

		if (er.re > max_err.re) {
			max_err.re = er.re;
			if (max_err.re > normalize32_critical_error) {
				return i+1;
			}
		}
		if (er.im > max_err.im) {
			max_err.im = er.im;
			if (max_err.im > normalize32_critical_error) {
				return i+1;
			}
		}
	}
	return nmppsStsNoErr;
}

TEST(tests_normalize32, nmppsNormalize_32f_small_vecs) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32_diap(7.77, 0.3333,
			1, 0.777, 0.1234));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normalize32_diap(8.88, 0.1111,
			2, 0.345, 0.4321));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normalize32_diap(9.99, 0.999,
			3, 0.378, 0.777));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normalize32_diap(1.23, 0.0987,
			64, 0.45, 0.115));
	TEST_ASSERT_EQUAL(nmppsStsNoErr, test_normalize32_diap(6.66, 0.0127,
			65, 0.1937, 0.1945));

}

TEST(tests_normalize32, nmppsNormalize_32fc_small_vecs) {
	nmpps32fc bgnIn = {1.77, 1.33},
			  stepIn = {0.0123456789, 0.0987654321},
			  vSub = {0.0777, 777.321};

	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, 1, vSub, 0.2001));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, 2, vSub, 0.2002));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, 3, vSub, 0.2003));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, 32, vSub, 0.2004));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, 33, vSub, 0.2005));


}


//Обычные значения
TEST(tests_normalize32, nmppsNormalize_32f_Calculation) {
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32_diap(1.3, 0.01234567,
			COUNT_ITERATION, 0.777, 0.1937));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32_diap(7.77e+37, -0.987654321e+35,
			COUNT_ITERATION, -7.771e+37, -0.1991e+19));
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32_diap(-7.77e-37, 0.987654321e-35,
			COUNT_ITERATION, 7.771e-37, 0.1991e-19));
}

TEST(tests_normalize32, nmppsNormalize_32fc_Calculation) {
	nmpps32fc bgnIn = {1.77, 1.33},
			  stepIn = {0.0123456789, 0.0987654321},
			  vSub = {0.0777, 777.321};
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, COUNT_ITERATION/2, vSub, 0.1937));

	bgnIn.re = 7.77e+35; bgnIn.im = -7.77e-35;
    stepIn.re = -0.987654321e+33; stepIn.im = 0.987654321e-33;
    vSub.re = -7.771e+32; vSub.im = 7.771e-32;
	TEST_ASSERT_EQUAL(nmppsStsNoErr,  test_normalize32fc_diap(bgnIn, stepIn, COUNT_ITERATION/2, vSub, -0.1937));
}


//Проверка возвращаемых результатов
TEST(tests_normalize32, nmppsNormalize_32f_check_answer) {
	nmppsStatus stat;

	stat = nmppsNormalize_32f(input32f_, output32f_, sizeof(input32f_)/sizeof(nmpps32f), 3.14, 0);
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_32f(NULL, output32f_, 1, 0, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_32f(input32f_, NULL, 1, 0, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_32f(input32f_, output32f_, 0, 0, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_32f(input32f_, output32f_, -1, 0, 1));
}

TEST(tests_normalize32, nmppsNormalize_32fc_check_answer) {
	nmpps32fc vSub = {1.77, 1.33};
	nmpps32fc* input32f_fc = (nmpps32fc*)input32f_;
	nmpps32fc* output32f_fc = (nmpps32fc*)output32f_;
	nmppsStatus stat;

	stat = nmppsNormalize_32fc(input32f_fc, output32f_fc, sizeof(input32f_)/sizeof(nmpps32fc), vSub, 0);
    TEST_ASSERT_EQUAL(nmppsStsDivByZeroErr, stat);

    //Проверка на NULL
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_32fc(NULL, output32f_fc, 1, vSub, 1));
    TEST_ASSERT_EQUAL(nmppsStsNullPtrErr, nmppsNormalize_32fc(input32f_fc, NULL, 1, vSub, 1));

    //Проверка реакции на некорректный размер
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_32fc(input32f_fc, output32f_fc, 0, vSub, 1));
    TEST_ASSERT_EQUAL(nmppsStsSizeErr, nmppsNormalize_32fc(input32f_fc, output32f_fc, -1, vSub, 1));
}



TEST(tests_normalize32, nmppsNormalize_32f_check_rewrite) {
	int i;
	fltint_t t, t1;

	t.ui32 = 0xDEADBEEF;
	input32f_[0] = output32f_[0] = kd32f_[0] =
			input32f_[1] = output32f_[1] = kd32f_[1] = t.flt;
	for(i=2;i<100;i++){
		input32f_[i] = kd32f_[i] = i*i;
		output32f_[i] = t.flt;
	}

	for(i=0;i < (sizeof(output32f_) / sizeof(nmpps32f))-2;i++){
		nmppsNormalize_32f(&input32f_[2], &output32f_[2], i+1, 1, 777);
		/*for(k=0; k < (sizeof(output32f_) / sizeof(nmpps32f)); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_FLOAT(input32f_[k], kd32f_[k]);
		}*/
		TEST_ASSERT_EQUAL_FLOAT_ARRAY(input32f_, kd32f_, sizeof(output32f_) / sizeof(nmpps32f));
		//Запись перед началом
		TEST_ASSERT_EQUAL_FLOAT(t.flt, output32f_[0]);
		TEST_ASSERT_EQUAL_FLOAT(t.flt, output32f_[1]);
		//Запись после окончания векторов
		t1.flt = output32f_[i+3];
		if (t.ui32 != t1.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}

TEST(tests_normalize32, nmppsNormalize_32fc_check_rewrite) {
	int i;
	fltint_t t, t1, t2;
	nmpps32fc* input32f_fc = (nmpps32fc*)input32f_;
	nmpps32fc* output32f_fc = (nmpps32fc*)output32f_;
	nmpps32fc* kd32f_fc = (nmpps32fc*)kd32f_;

	nmpps32fc vSub = {0.1, -0.1};

	t.ui32 = 0xDEADBEEF;
	input32f_fc[0].re = output32f_fc[0].re = kd32f_fc[0].re =
			input32f_fc[0].im = output32f_fc[0].im = kd32f_fc[0].im = t.flt;
	for(i=1;i<50;i++){
		input32f_fc[i].re = kd32f_fc[i].re = input32f_fc[i].im = kd32f_fc[i].im = i*i;
		output32f_fc[i].re = output32f_fc[i].im = t.flt;
	}

	for(i=0;i < (sizeof(output32f_) / sizeof(nmpps32fc))-2;i++){
		nmppsNormalize_32fc(&input32f_fc[1], &output32f_fc[1], i+1, vSub, 777);
		/*for(k=0; k < (sizeof(output32f_) / sizeof(nmpps32f)); k++){
			//Перезапись входных векторов
			TEST_ASSERT_EQUAL_FLOAT(input32f_[k], kd32f_[k]);
		}*/
		TEST_ASSERT_EQUAL_FLOAT_ARRAY(input32f_fc, kd32f_fc, sizeof(output32f_) / sizeof(nmpps32f));
		//Запись перед началом
		TEST_ASSERT_EQUAL_FLOAT(t.flt, output32f_fc[0].re);
		TEST_ASSERT_EQUAL_FLOAT(t.flt, output32f_fc[0].im);
		//Запись после окончания векторов
		t1.flt = output32f_fc[i+2].re;
		t2.flt = output32f_fc[i+2].im;
		if (t.ui32 != t1.ui32 || t.ui32 != t2.ui32) {
			TEST_ASSERT_EQUAL(-1, i);
		}
	}
}


TEST_GROUP_RUNNER(tests_normalize32){

    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32f_small_vecs);
    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32f_Calculation);
    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32f_check_answer);
    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32f_check_rewrite);

    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32fc_small_vecs);
    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32fc_Calculation);
    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32fc_check_answer);
    RUN_TEST_CASE(tests_normalize32, nmppsNormalize_32fc_check_rewrite);

}
