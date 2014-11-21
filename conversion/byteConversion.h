#ifndef BYTECONVERSION_H
#define BYTECONVERSION_H

#include <iostream>
#include <string>


#include <stdint.h>



unsigned char *toByteArray(unsigned char* dst, const void* src, const size_t srcSize);



unsigned char *charToByteArray(unsigned char* dst, const char* src);

unsigned char *charToByteArray(unsigned char* dst, const char* src, const size_t srcSize);

unsigned char *stringToByteArray(unsigned char* dst, const std::string& src);



unsigned char *int64ToByteArray(unsigned char* dst, const int64_t *src);

unsigned char *int32ToByteArray(unsigned char* dst, const int32_t *src);

unsigned char *int16ToByteArray(unsigned char* dst, const int16_t *src);

unsigned char *int8ToByteArray(unsigned char* dst, const int8_t *src);

unsigned char *longToByteArray(unsigned char* dst, const long *src);

unsigned char *intToByteArray(unsigned char* dst, const int *src);

unsigned char *shortToByteArray(unsigned char* dst, const short *src);




unsigned char *uint64ToByteArray(unsigned char* dst, const uint64_t *src);

unsigned char *uint32ToByteArray(unsigned char* dst, const uint32_t *src);

unsigned char *uint16ToByteArray(unsigned char* dst, const uint16_t *src);

unsigned char *uint8ToByteArray(unsigned char* dst, const uint8_t *src);

unsigned char *ulongToByteArray(unsigned char* dst, const unsigned long *src);

unsigned char *uintToByteArray(unsigned char* dst, const unsigned int *src);

unsigned char *ushortToByteArray(unsigned char* dst, const unsigned short *src);



unsigned char *floatToByteArray(unsigned char* dst, const float *src);

unsigned char *doubleToByteArray(unsigned char* dst, const double *src);

unsigned char *longDoubleToByteArray(unsigned char* dst, const long double *src);




void *fromByteArray(void *dst, const unsigned char *src, const size_t srcSize);



char *charFromByteArray(char *dst, const unsigned char *src, const size_t srcSize);

std::string& stringFromByteArray(std::string& dst, const unsigned char *src, const size_t srcSize);



int64_t *int64FromByteArray(int64_t* dst, const unsigned char *src);

int32_t *int32FromByteArray(int32_t* dst, const unsigned char *src);

int16_t *int16FromByteArray(int16_t* dst, const unsigned char *src);

int8_t *int8FromByteArray(int8_t* dst, const unsigned char *src);

long *longFromByteArray(long* dst, const unsigned char *src);

int *intFromByteArray(int* dst, const unsigned char *src);

short *shortFromByteArray(short* dst, const unsigned char *src);




uint64_t *uint64FromByteArray(uint64_t* dst, const unsigned char *src);

uint32_t *uint32FromByteArray(uint32_t* dst, const unsigned char *src);

uint16_t *uint16FromByteArray(uint16_t* dst, const unsigned char *src);

uint8_t *uint8FromByteArray(uint8_t* dst, const unsigned char *src);

unsigned long *longFromByteArray(unsigned long* dst, const unsigned char *src);

unsigned int *intFromByteArray(unsigned int* dst, const unsigned char *src);

unsigned  short *shortFromByteArray(unsigned short* dst, const unsigned char *src);



float *floatFromByteArray(float* dst, const unsigned char *src);

double *doubleFromByteArray(double* dst, const unsigned char *src);

long double *longDoubleFromByteArray(long double* dst, const unsigned char *src);

#endif // BYTECONVERSION_H
