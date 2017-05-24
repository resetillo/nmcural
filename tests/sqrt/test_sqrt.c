#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"
//#include "stdlib.h"

float right_sqrtf(float x);
double right_sqrt(double x);

#define COUNT_ITERATION (100)

/**
 * @brief �������� �������� ��������
 *
 * @param in ��������� �� ������ ����������
 * @param out ��������� �� ������ ������
 * @param len ����� �������
 * @param bgn ��������� ��������
 * @param step ��� ���������
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
	if (len>32) len = 32;
	for(i=0; i<len; i++){
		in[i] = bgn;
		out[i] = right_sqrtf(in[i]);
		bgn += step;
	}
}



const nmpps64f sqrt_critical_error = 10e-14;//������ ������������� � %
const nmpps32f sqrtf_critical_error = 10e-05;//������ ������������� � %
/**
 * @brief ������������ ���������� ����������� ����� ��� ��������� ��������
 *
 * @param bgn ��������� ��������
 * @param step ��� ���������
 * @param count ���-�� ��������
 * */
nmppsStatus test_sqrt_diap(nmpps64f bgn, nmpps64f step, int count){
	nmpps64f in[COUNT_ITERATION];
	nmpps64f res[COUNT_ITERATION];
	nmpps64f kd[COUNT_ITERATION];
	nmppsStatus stat;
	double er;
	double arg = bgn;
	//double step = 1.3333777e-1;
	double max_err = 0;
	//double max_err_arg;
	int i;
	//������� ��
	create_sqrt_vecs(in, kd, count, arg, step);
	//���������� �������
	stat = nmppsSqrt_64f(in, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	for (i=0; i<count; i++){
		arg = in[i];
		er = fabs(kd[i]-res[i]);
		if (kd[i] != 0) er = 100*er/kd[i];
		if (er > max_err) {
			max_err = er;
			//max_err_arg = arg;
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
	//double step = 1.3333777e-1;
	nmpps32f max_err = 0;
	//nmpps32f max_err_arg = 0;
	int i = 0;
	//������� ��
	create_sqrtf_vecs(in, kd, count, arg, step);
	//���������� �������
	stat = nmppsSqrt_32f(in, res, count);
	if (stat!=nmppsStsNoErr) return stat;
	for(i=0;i<count;i++){
		arg = in[i];
		er = fabsf(kd[i]-res[i]);
		if (kd[i] != 0) er = 100*er/kd[i];
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

nmpps64f data_sqrt_neg[] = {
		4,  9, -4, -9
};
nmpps32f data_sqrtf_neg[] = {
		4,  9, -4, -9
};

int test_sqrt_check_answer(){
	int i,k;
	nmppsStatus stat;
	nmpps64f data[33], original[33], out[33];

	stat = nmppsSqrt_64f(data_sqrt_neg, data, sizeof(data_sqrt_neg)/sizeof(nmpps64f));
	if (stat!=nmppsStsSqrtNegArg) return 1;
	if (100*fabs(2-data[0])/2 > sqrt_critical_error ||
			100*fabs(3-data[1])/3 > sqrt_critical_error) return 2;

	original[0] = data[0] = out[0] = 0;
	for(i=1;i<33;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = 0;
	}

	for(i=0;i<31;i++){
		nmppsSqrt_64f(&data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps64f); k++){
			if (data[k]!=original[k]) {
				return 3;//������� ������� ������
			}
		}
		if (out[0]!=0) {
			return 4;//������������� ����� �������� ��������
		}
		if (out[i+2]!=0) {
			return 5;//������������� �� �������� ��������� �������
		}
	}


	if (nmppsSqrt_64f(data, NULL, 1) != nmppsStsNullPtrErr ||
		nmppsSqrt_64f(NULL, out, 1) != nmppsStsNullPtrErr	){
		return 6; //�� ��������� �������� �� NULL
	}

	if (nmppsSqrt_64f(data, out, 0) != nmppsStsSizeErr ||
		nmppsSqrt_64f(data, out, -1) != nmppsStsSizeErr	){
		return 7; //�� ��������� �������� �� ����� �������
	}


	return 0;
}


int test_sqrtf_check_answer(){
	int i,k;
	nmppsStatus stat;
	nmpps32f data[33], original[33], out[33];

	stat = nmppsSqrt_32f(data_sqrtf_neg, data, sizeof(data_sqrtf_neg)/sizeof(nmpps32f));
	if (stat!=nmppsStsSqrtNegArg) return 1;
	if (100*fabsf(2-data[0])/2 > sqrtf_critical_error ||
			100*fabsf(3-data[1])/3 > sqrtf_critical_error) return 2;

	original[0] = data[0] = out[0] = 0;
	for(i=1;i<33;i++){
		original[i] = i*i;
		data[i] = original[i];
		out[i] = 0;
	}

	for(i=0;i<31;i++){
		nmppsSqrt_32f(&data[1], &out[1], i+1);
		for(k=0; k < sizeof(data)/sizeof(nmpps32f); k++){
			if (data[k]!=original[k]) {
				return 3;//������� ������� ������
			}
		}
		if (out[0]!=0) {
			return 4;//������������� ����� �������� ��������
		}
		if (out[i+2]!=0) {
			return 5;//������������� �� �������� ��������� �������
		}
	}


	if (nmppsSqrt_32f(data, NULL, 1) != nmppsStsNullPtrErr ||
		nmppsSqrt_32f(NULL, out, 1) != nmppsStsNullPtrErr	){
		return 6; //�� ��������� �������� �� NULL
	}

	if (nmppsSqrt_32f(data, out, 0) != nmppsStsSizeErr ||
		nmppsSqrt_32f(data, out, -1) != nmppsStsSizeErr	){
		return 7; //�� ��������� �������� �� ����� �������
	}


	return 0;
}

int test_sqrt(){
	//fabs(-1);
	nmppsStatus stat;
	stat = test_sqrt_diap(0, 0.133377789, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 1;
	}

	stat = test_sqrt_diap(1.7789e+300, 13.337, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 2;
	}

	stat = test_sqrt_diap(3.3333e-300, 1.3337e-300, COUNT_ITERATION);
	if (stat!=nmppsStsNoErr) {
		return 3;
	}

	stat = test_sqrt_check_answer();
	if (stat != 0) {
		return 4;
	}

	return 0;
}


int test_sqrtf(){

	nmppsStatus stat;
	stat = test_sqrtf_diap(0, 0.133377789, 1000);
	if (stat!=nmppsStsNoErr) {
		return 1;
	}

	stat = test_sqrtf_diap(1.7789e+38, -13.337, 1000);
	if (stat!=nmppsStsNoErr) {
		return 2;
	}

	stat = test_sqrtf_diap(3.3333e-38, 1.3337e-300, 1000);
	if (stat!=nmppsStsNoErr) {
		return 3;
	}

	if (test_sqrtf_check_answer()!=0) return 4;

	return 0;
}

