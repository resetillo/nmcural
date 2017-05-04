#include "nmpps.h"
#include "tests/test_proto.h"


//kd = copysign(a,b);
nmpps64f a[34] = {
		0,
		1,  -2,  3,  -4,  5,  -6,  7,  -8,
		9,  -10, 11, -12, 13, -14, 15, -16,
		17, -18, 19, -20, 21, -22, 23, -24,
		25, -26, 27, -28, 29, -30, 31, -32,
		0
};
nmpps64f b[34] = {
		0,
		-1,  1,  -1,  1,  -1,  1,  -1,  1,
		-1,  1,  -1,  1,  -1,  1,  -1,  1,
		-1,  1,  -1,  1,  -1,  1,  -1,  1,
		-1,  1,  -1,  1,  -1,  1,  -1,  1,
		0
};
nmpps64f kd[34] = {
		0,
		-1,  2,  -3,  4,  -5,  6,  -7,  8,
		-9,  10, -11, 12, -13, 14, -15, 16,
		-17, 18, -19, 20, -21, 22, -23, 24,
		-25, 26, -27, 28, -29, 30, -31, 32,
		0
};



int test_copysign(){
	int i;
	nmpps64f data[34];
	data[0] = data[33] = 0;
	nmppsCopySign_64f(&b[1], &a[1], &data[1], 32);
	for(i = 1; i<33; i++){
		if (data[i] != kd[i]) return i;
	}
	//�������� �� ������ � �������� �����
	if (data[0] != 0) return 33;
	if (data[33] != 0) return 34;
	if (a[0] != 0) return 35;
	if (a[33] != 0) return 36;
	if (b[0] != 0) return 37;
	if (b[33] != 0) return 38;
	if (kd[0] != 0) return 39;
	if (kd[33] != 0) return 40;
	return 0;
}






