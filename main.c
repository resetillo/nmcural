#include "nmpps.h"
#include "tests/test_proto.h"
#include "tests/test_math.h"

int main(){
	int res = 0;

	// res = test_sqrt();
	// res = test_sqrtf();
	// res = test_atan();
	 res = test_atanf();
	// res = test_copysign();
	// res = test_vec_handler32();
	if (res){
		printf("ERROR TEST is %i", res);
	}
	else {
		printf("TEST SUCCEFUL");
	}
	return res;
}
