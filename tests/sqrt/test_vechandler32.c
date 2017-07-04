#include "nmpps.h"
#include "tests/test_proto.h"


//int vec_handler32(int*, int* in, int* out, int len);
void _test_func_vh32();


int vec[148];
int outvector[148];

void fuck_stack(){
	int mass[512];
	for (int i=0; i< sizeof(mass); i++){
		mass[i] = 0xDEADBEEF;
	}
}

void init_mass(int* one, int* two, int size){
	for (int k=1; k<= size+2; k++){
		one[k-1] = k | (k<<24);
		two[k-1] = (255-k) | ((255-k)<<24);
	}
}

int subtest_vh32(int* vec, int* result, int size){
	//Инитим массивы
	init_mass(vec, result, size);

	vec_handler32((nmppsStatus*)_test_func_vh32, &vec[1], &result[1], size);


	if (vec[0]!= (1 | (1<<24))){
		return -1;

	}
	if (vec[size+1]!= ((size+2) | ((size+2)<<24))){
		return -2;

	}
	if (result[0]!= (254 | (254<<24))){
		return -3;

	}
	if (result[size+1]!= ((255-(size+2)) | ((255-(size+2))<<24))){
		return -4;

	}

	for (int k=1;k<size+1;k++){
		if (vec[k] != result[k] ) {
			return k;
		}
	}
	return 0;
}

int subtest2_vh32(int* vec, int* outvector, int size){
	int res = 0;
	res = subtest_vh32(vec, outvector, size);
	if (res!=0) {
		return 1;
	}
	res = subtest_vh32(vec, &outvector[1], size);
	if (res!=0) {
		return 2;
	}
	res = subtest_vh32(&vec[1], outvector, size);
	if (res!=0) {
		return 3;
	}
	res = subtest_vh32(&vec[1], &outvector[1], size);
	if (res!=0) {
		return 4;
	}
	return 0;
}

int test_vec_handler32(){
	int res = 0;

	//Портим стэк
	fuck_stack();

	res = subtest2_vh32(vec, outvector, 1);
	if (res!=0) {
		return 1;
	}

	res = subtest2_vh32(vec, outvector, 2);
	if (res!=0) {
		return 2;
	}
	res = subtest2_vh32(vec, outvector, 3);
	if (res!=0) {
		return 3;
	}

	res = subtest2_vh32(vec, outvector, 4);
	if (res!=0) {
		return 4;
	}
	res = subtest2_vh32(vec, outvector, 8);
	if (res!=0) {
		return 5;
	}
	res = subtest2_vh32(vec, outvector, 63);
	if (res!=0) {
		return 6;
	}
	res = subtest2_vh32(vec, outvector, 64);
	if (res!=0) {
		return 7;
	}
	res = subtest2_vh32(vec, outvector, 65);
	if (res!=0) {
		return 8;
	}
	res = subtest2_vh32(vec, outvector, 66);
	if (res!=0) {
		return 9;
	}
	res = subtest2_vh32(vec, outvector, 67);
	if (res!=0) {
		return 10;
	}
	res = subtest2_vh32(vec, outvector, 126);
	if (res!=0) {
		return 11;
	}
	res = subtest2_vh32(vec, outvector, 127);
	if (res!=0) {
		return 12;
	}
	res = subtest2_vh32(vec, outvector, 128);
	if (res!=0) {
		return 13;
	}
	res = subtest2_vh32(vec, outvector, 129);
	if (res!=0) {
		return 14;
	}
	/*res = subtest2_vh32(vec, outvector, 130);
	if (res!=0) {
		return 12;
	}*/
	res = subtest2_vh32(vec, outvector, 140);
	if (res!=0) {
		return 15;
	}



	return 0;
}






