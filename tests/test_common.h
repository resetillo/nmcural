
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

nmpps8u* get_ptr_src_vector_8u();
nmpps8u* get_ptr_dst_vector_8u();

nmpps32f* get_ptr_src_vector_32f();
nmpps32f* get_ptr_dst_vector_32f();
nmpps32f* get_ptr_etalon_vector_32f();

nmpps64f* get_ptr_src_vector_64f();
nmpps64f* get_ptr_dst_vector_64f();
nmpps64f* get_ptr_etalon_vector_64f();

nmpps16s* get_ptr_src_vector_16s();
nmpps16s* get_ptr_dst_vector_16s();

nmpps32s* get_ptr_src_vector_32s();
nmpps32s* get_ptr_dst_vector_32s();

nmpps64s* get_ptr_src_vector_64s();
nmpps64s* get_ptr_dst_vector_64s();

nmpps16sc* get_ptr_src_vector_16sc();
nmpps16sc* get_ptr_dst_vector_16sc();

nmpps32sc* get_ptr_src_vector_32sc();
nmpps32sc* get_ptr_dst_vector_32sc();

nmpps64sc* get_ptr_src_vector_64sc();
nmpps64sc* get_ptr_dst_vector_64sc();
#endif /* TEST_COMMON_H_ */
