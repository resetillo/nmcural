#include "test_common.h"


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


void init_vector_value_8u(nmpps8u* vector, nmpps8u value, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = value;
  }
}

void init_vector_value_16u(nmpps16u* vector, nmpps16u value, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = value;
  }
}

void init_vector_value_16s(nmpps16s* vector, nmpps16s value, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = value;
  }
}


void init_vector_value_32u(nmpps32u* vector, nmpps32u value, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = value;
  }
}

void init_vector_value_32s(nmpps32s* vector, nmpps32s value, unsigned int size){
  unsigned int i = 0;

  for(i = 0; i < size; i++){
    vector[i] = value;
  }
}


