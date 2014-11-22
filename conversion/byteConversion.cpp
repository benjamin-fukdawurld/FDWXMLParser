#include "byteConversion.h"

using namespace std;


unsigned char *anyToByteArray(unsigned char *dst, const void *src, const size_t srcSize)
{
    if(dst == 0 ||  srcSize <= 0)
    return 0;

    memcpy((void*) dst, src, srcSize);

    return dst;
}



void *anyFromByteArray(void *dst, const unsigned char *src, const size_t srcSize)
{
    if(dst == 0 ||  srcSize <= 0)
    return 0;

    memcpy(dst, (void*) src, srcSize);

    return dst;
}



unsigned char *cstrToByteArray(unsigned char *dst, const char *src, const size_t srcSize)
{
    return anyToByteArray(dst, src, srcSize);
}


unsigned char *cstrToByteArray(unsigned char *dst, const char *src)
{
    return cstrToByteArray(dst, src, (strlen(src) + 1)*sizeof(char));
}

unsigned char *strToByteArray(unsigned char *dst, const std::string *src, const size_t srcSize)
{
    return anyToByteArray(dst, (void*) src->c_str(), srcSize);
}

unsigned char *strToByteArray(unsigned char *dst, const std::string *src)
{
    return strToByteArray(dst, src, src->size() + 1);
}








char *cstrFromByteArray(char *dst, const unsigned char *src, const size_t srcSize)
{
    return (char*) anyFromByteArray((void*) dst, src, srcSize);
}

char *cstrFromByteArray(char *dst, const unsigned char *src)
{
    return cstrFromByteArray(dst, src, (strlen((char*) src) + 1)*sizeof(char));
}

std::string *strFromByteArray(std::string *dst, const unsigned char *src, const size_t srcSize)
{
    char *tmp = new char[srcSize];

    cstrFromByteArray(tmp, src, srcSize);

    *dst = tmp;

    delete[] tmp;

    return dst;
}


std::string *strFromByteArray(std::string *dst, const unsigned char *src)
{
    size_t srcSize((strlen((char*) src) + 1)*sizeof(char));

    return strFromByteArray(dst, src, srcSize);
}


