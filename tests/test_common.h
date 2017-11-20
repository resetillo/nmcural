
#ifndef TEST_COMMON_H_
#define TEST_COMMON_H_

#include "nmpps.h"



void init_vector_16sc(nmpps16sc* vector, unsigned int size);
void init_vector_32sc(nmpps32sc* vector, unsigned int size);
void init_vector_64sc(nmpps64sc* vector, unsigned int size);
void init_vector_8u(nmpps8u* vector, unsigned int size);
void init_vector_16s(nmpps16s* vector, unsigned int size);
void init_vector_32s(nmpps32s* vector, unsigned int size);
void init_vector_64s(nmpps64s* vector, unsigned int size);
void init_vector_32f(nmpps32f* vector, unsigned int size);
void init_vector_64f(nmpps64f* vector, unsigned int size);

void init_vector_zero_16sc(nmpps16sc* vector, unsigned int size);
void init_vector_zero_32sc(nmpps32sc* vector, unsigned int size);
void init_vector_zero_64sc(nmpps64sc* vector, unsigned int size);


void init_vector_value_8u(nmpps8u* vector, nmpps8u value, unsigned int size);
void init_vector_value_16u(nmpps16u* vector, nmpps16u value, unsigned int size);
void init_vector_value_16s(nmpps16s* vector, nmpps16s value, unsigned int size);
void init_vector_value_32s(nmpps32s* vector, nmpps32s value, unsigned int size);
void init_vector_value_32f(nmpps32f* vector, nmpps32f value, unsigned int size);
void init_vector_value_64f(nmpps64f* vector, nmpps64f value, unsigned int size);

#endif /* TEST_COMMON_H_ */
