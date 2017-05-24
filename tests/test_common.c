#include "test_common.h"

nmpps16sc src_16sc[4100] __attribute__ ((aligned (2)));
nmpps16sc dst_16sc[4100] __attribute__ ((aligned (2)));

nmpps32sc src_32sc[4100] __attribute__ ((aligned (2)));
nmpps32sc dst_32sc[4100] __attribute__ ((aligned (2)));

nmpps64sc src_64sc[4100] __attribute__ ((aligned (2)));
nmpps64sc dst_64sc[4100] __attribute__ ((aligned (2)));

nmpps8u src_8u[4100] __attribute__ ((aligned (2)));
nmpps8u dst_8u[4100] __attribute__ ((aligned (2)));

nmpps16s src_16s[4100] __attribute__ ((aligned (2)));
nmpps16s dst_16s[4100] __attribute__ ((aligned (2)));


nmpps32s src_32s[4100] __attribute__ ((aligned (2)));
nmpps32s dst_32s[4100] __attribute__ ((aligned (2)));

nmpps64s src_64s[4100] __attribute__ ((aligned (2)));
nmpps64s dst_64s[4100] __attribute__ ((aligned (2)));

nmpps32f src_32f[4100];
nmpps32f dst_32f[4100];
nmpps32f etalon_32f[4100];

nmpps64f src_64f[4100];
nmpps64f dst_64f[4100];
nmpps64f etalon_64f[4100];

nmpps32f* get_ptr_src_vector_32f(){
  return src_32f;
}

nmpps32f* get_ptr_dst_vector_32f(){
  return dst_32f;
}

nmpps32f* get_ptr_etalon_vector_32f(){
  return etalon_32f;
}

nmpps64f* get_ptr_src_vector_64f(){
  return src_64f;
}

nmpps64f* get_ptr_dst_vector_64f(){
  return dst_64f;
}

nmpps64f* get_ptr_etalon_vector_64f(){
  return etalon_64f;
}

nmpps8u* get_ptr_src_vector_8u(){
  return src_8u;
}

nmpps8u* get_ptr_dst_vector_8u(){
  return dst_8u;
}

nmpps16s* get_ptr_src_vector_16s(){
  return src_16s;
}

nmpps16s* get_ptr_dst_vector_16s(){
  return dst_16s;
}

nmpps32s* get_ptr_src_vector_32s(){
  return src_32s;
}

nmpps32s* get_ptr_dst_vector_32s(){
  return dst_32s;
}

nmpps64s* get_ptr_src_vector_64s(){
  return src_64s;
}

nmpps64s* get_ptr_dst_vector_64s(){
  return dst_64s;
}

nmpps16sc* get_ptr_dst_vector_16sc(){
  return dst_16sc;
}

nmpps16sc* get_ptr_src_vector_16sc(){
  return src_16sc;
}

nmpps32sc* get_ptr_src_vector_32sc(){
  return src_32sc;
}

nmpps32sc* get_ptr_dst_vector_32sc(){
  return dst_32sc;
}

nmpps64sc* get_ptr_src_vector_64sc(){
  return src_64sc;
}

nmpps64sc* get_ptr_dst_vector_64sc(){
  return dst_64sc;
}

void init_vector_32f(nmpps32f* vector, unsigned int size){
  int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = (nmpps32f)(i / 3.0);
  }
}

void init_vector_64f(nmpps64f* vector, unsigned int size){
  int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = (nmpps64f)(i / 3.0);
  }
}


void init_vector_zero_16sc(nmpps16sc* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i].im = 0;
    vector[i].re = 0;
  }
}

void init_vector_zero_32sc(nmpps32sc* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i].im = 0;
    vector[i].re = 0;
  }
}

void init_vector_zero_64sc(nmpps64sc* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i].im = 0;
    vector[i].re = 0;
  }
}


void init_vector_16sc(nmpps16sc* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i].im = i;
    vector[i].re = i + 2;
  }
}

void init_vector_32sc(nmpps32sc* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i].im = i;
    vector[i].re = i + 2;
  }
}

void init_vector_64sc(nmpps64sc* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i].im = i;
    vector[i].re = i + 2;
  }
}

void init_vector_8u(nmpps8u* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = i & 0xFF;
  }
}

void init_vector_16s(nmpps16s* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = i;
  }
}

void init_vector_32s(nmpps32s* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = i * 11111;
  }
}

void init_vector_64s(nmpps64s* vector, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = i * 1111111;
  }
}
