#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"

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



int test_atan_check_answer(){
	int i,k;
	nmpps64f data[33], original[33], out[33];

	original[0] = data[0] = out[0] = 0;
	for(i=1;i<33;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = 0;
	}

	for(i=0;i<31;i++){
		nmppsArctan_64f(&data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps64f); k++){
			if (data[k]!=original[k]) {
				return 3;//Произошло искажение входных данных
			}
		}
		if (out[0]!=0) {
			return 4;//Затерты данные перед выходным вектором
		}
		if (out[i+2]!=0) {
			return 5;//Затерты данные после выходного вектора
		}
	}


	if (nmppsArctan_64f(data, NULL, 1) != nmppsStsNullPtrErr ||
			nmppsArctan_64f(NULL, out, 1) != nmppsStsNullPtrErr	){
		return 6; //не прошла проверка на NULL
	}

	if (nmppsArctan_64f(data, out, 0) != nmppsStsSizeErr ||
			nmppsArctan_64f(data, out, -1) != nmppsStsSizeErr	){
		return 7; //не прошла проверка на некорректную длину вектора
	}


	return 0;
}



int test_atanf_check_answer(){
	int i,k;
	nmpps32f data[66], original[66], out[66];

	original[0] = data[0] = out[0] = 0;
	for(i=1;i<66;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = 0;
	}

	for(i=0;i<63;i++){
		nmppsArctan_32f(&data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			if (data[k]!=original[k]) {
				return 3;//Произошло искажение входных данных
			}
		}
		if (out[0]!=0) {
			return 4;//Затерты данные перед выходным вектором
		}
		if (out[i+2]!=0) {
			return 5;//Затерты данные после выходного вектора
		}
	}


	if (nmppsArctan_32f(data, NULL, 1) != nmppsStsNullPtrErr ||
			nmppsArctan_32f(NULL, out, 1) != nmppsStsNullPtrErr	){
		return 6; //не прошла проверка на NULL
	}

	if (nmppsArctan_32f(data, out, 0) != nmppsStsSizeErr ||
			nmppsArctan_32f(data, out, -1) != nmppsStsSizeErr	){
		return 7; //не прошла проверка на некорректную длину вектора
	}


	return 0;
}

int test_atan(){
	nmppsStatus stat;
	//Проверка нормальных значений
	stat = test_atan_diap(-40, ((double)87/(double)COUNT_ITERATION), COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 1;
	}

	//Проверка больших значений
	stat = test_atan_diap(1.9875e+300, 17.937, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 2;
	}
	stat = test_atan_diap(-1.7789e+300, -13.337, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 3;
	}

	//Проверка близких к 0 значений
	stat = test_atan_diap(3.3333e-300, 1.3337e-300, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 4;
	}
	stat = test_atan_diap(-7.7777e-300, -1.7777e-300, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 5;
	}

	stat = test_atan_check_answer();
	if (stat!=0){
		return 6;
	}

	return 0;
}

int test_atanf(){
	nmppsStatus stat;

	//Проверка нормальных значений
	stat = test_atanf_diap(-50, ((float)87/(float)COUNT_ITERATION), COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 1;
	}

	//Проверка больших значений
	stat = test_atanf_diap(1.9875e+38, 17.937, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 2;
	}
	stat = test_atanf_diap(-1.7789e+38, -13.337, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 3;
	}

	//Проверка близких к 0 значений
	stat = test_atanf_diap(3.3333e-38, 1.3337e-38, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 4;
	}
	stat = test_atanf_diap(-7.7777e-38, -1.7777e-38, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 5;
	}

	stat = test_atanf_check_answer();
	if (stat != 0){
		return 6;
	}

	return 0;
}


