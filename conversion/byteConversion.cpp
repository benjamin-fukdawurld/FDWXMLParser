#include "byteConversion.h"

#include <cstring>

using namespace std;

unsigned char *toByteArray(unsigned char *dst, const void *src, const size_t srcSize)
{
    if(dst == 0 ||  srcSize <= 0)
    return 0;

    memcpy((void*) dst, src, srcSize);

    return dst;
}


unsigned char *charToByteArray(unsigned char *dst, const char *src)
{
    return charToByteArray(dst, src, strlen(src));
}


unsigned char *charToByteArray(unsigned char *dst, const char *src, const size_t srcSize)
{
    return toByteArray(dst, (void*) src, srcSize);
}


unsigned char *stringToByteArray(unsigned char *dst, const string &src)
{
    return toByteArray(dst, (void*) src.c_str(), sizeof(char)*src.size());
}






unsigned char *int64ToByteArray(unsigned char *dst, const int64_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(int64_t));
}


unsigned char *int32ToByteArray(unsigned char *dst, const int32_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(int32_t));
}


unsigned char *int16ToByteArray(unsigned char *dst, const int16_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(int16_t));
}


unsigned char *int8ToByteArray(unsigned char *dst, const int8_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(int8_t));
}


unsigned char *longToByteArray(unsigned char *dst, const long *src)
{
    return toByteArray(dst, (void*) src, sizeof(long));
}


unsigned char *intToByteArray(unsigned char *dst, const int *src)
{
    return toByteArray(dst, (void*) src, sizeof(int));
}


unsigned char *shortToByteArray(unsigned char *dst, const short *src)
{
    return toByteArray(dst, (void*) src, sizeof(short));
}






unsigned char *uint64ToByteArray(unsigned char *dst, const uint64_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(uint64_t));
}


unsigned char *uint32ToByteArray(unsigned char *dst, const uint32_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(uint32_t));
}


unsigned char *uint16ToByteArray(unsigned char *dst, const uint16_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(uint16_t));
}


unsigned char *uint8ToByteArray(unsigned char *dst, const uint8_t *src)
{
    return toByteArray(dst, (void*) src, sizeof(uint8_t));
}


unsigned char *ulongToByteArray(unsigned char *dst, const unsigned long *src)
{
    return toByteArray(dst, (void*) src, sizeof(unsigned long));
}


unsigned char *uintToByteArray(unsigned char *dst, const unsigned int *src)
{
    return toByteArray(dst, (void*) src, sizeof(unsigned int));
}


unsigned char *ushortToByteArray(unsigned char *dst, const unsigned short *src)
{
    return toByteArray(dst, (void*) src, sizeof(unsigned short));
}





unsigned char *floatToByteArray(unsigned char *dst, const float *src)
{
    return toByteArray(dst, (void*) src, sizeof(float));
}


unsigned char *doubleToByteArray(unsigned char *dst, const double *src)
{
    return toByteArray(dst, (void*) src, sizeof(double));
}


unsigned char *longDoubleToByteArray(unsigned char *dst, const long double *src)
{
    return toByteArray(dst, (void*) src, sizeof(long double));
}




void *fromByteArray(void *dst, const unsigned char *src, const size_t srcSize)
{
    if(dst == 0 ||  srcSize <= 0)
    return 0;

    memcpy(dst, (void*) src, srcSize);

    return dst;
}



char *charFromByteArray(char *dst, const unsigned char *src, const size_t srcSize)
{
    return (char*) fromByteArray((void*) dst, src, srcSize);
}



std::string& stringFromByteArray(std::string& dst, const unsigned char *src, const size_t srcSize)
{
    char *tmp = new char[srcSize];

    fromByteArray((void*) tmp, src, srcSize);

    dst = tmp;

    delete[] tmp;

    return dst;
}


int64_t *int64FromByteArray(int64_t* dst, const unsigned char *src)
{
    return (int64_t*) fromByteArray((void*) dst, src, sizeof(int64_t));
}

int32_t *int32FromByteArray(int32_t* dst, const unsigned char *src)
{
    return (int32_t*) fromByteArray((void*) dst, src, sizeof(int32_t));
}

int16_t *int16FromByteArray(int16_t* dst, const unsigned char *src)
{
    return (int16_t*) fromByteArray((void*) dst, src, sizeof(int16_t));
}

int8_t *int8FromByteArray(int8_t* dst, const unsigned char *src)
{
    return (int8_t*) fromByteArray((void*) dst, src, sizeof(int8_t));
}

long *longFromByteArray(long* dst, const unsigned char *src)
{
    return (long*) fromByteArray((void*) dst, src, sizeof(long));
}

int *intFromByteArray(int* dst, const unsigned char *src)
{
    return (int*) fromByteArray((void*) dst, src, sizeof(int));
}

short *shortFromByteArray(short* dst, const unsigned char *src)
{
    return (short*) fromByteArray((void*) dst, src, sizeof(short));
}




uint64_t *uint64FromByteArray(uint64_t* dst, const unsigned char *src)
{
    return (uint64_t*) fromByteArray((void*) dst, src, sizeof(uint64_t));
}

uint32_t *uint32FromByteArray(uint32_t* dst, const unsigned char *src)
{
    return (uint32_t*) fromByteArray((void*) dst, src, sizeof(uint32_t));
}

uint16_t *uint16FromByteArray(uint16_t* dst, const unsigned char *src)
{
    return (uint16_t*) fromByteArray((void*) dst, src, sizeof(uint16_t));
}

uint8_t *uint8FromByteArray(uint8_t* dst, const unsigned char *src)
{
    return (uint8_t*) fromByteArray((void*) dst, src, sizeof(uint8_t));
}

unsigned long *longFromByteArray(unsigned long* dst, const unsigned char *src)
{
    return (unsigned long*) fromByteArray((void*) dst, src, sizeof(unsigned long));
}

unsigned int *intFromByteArray(unsigned int* dst, const unsigned char *src)
{
    return (unsigned int*) fromByteArray((void*) dst, src, sizeof(unsigned int));
}

unsigned  short *shortFromByteArray(unsigned short* dst, const unsigned char *src)
{
    return (unsigned short*) fromByteArray((void*) dst, src, sizeof(unsigned short));
}


float *floatFromByteArray(float* dst, const unsigned char *src)
{
    return (float*) fromByteArray((void*) dst, src, sizeof(float));
}

double *doubleFromByteArray(double* dst, const unsigned char *src)
{
    return (double*) fromByteArray((void*) dst, src, sizeof(double));
}

long double *longDoubleFromByteArray(long double* dst, const unsigned char *src)
{
    return (long double*) fromByteArray((void*) dst, src, sizeof(long double));
}

