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





template<>
unsigned char *toByteArray(unsigned char *dst, const char *src)
{
    return toByteArray(dst, src, (strlen(src) + 1)*sizeof(char));
}

template<>
unsigned char *toByteArray(unsigned char *dst, const std::string *src, const size_t srcSize)
{
    return anyToByteArray(dst, (void*) src->c_str(), srcSize);
}

template<>
unsigned char *toByteArray(unsigned char *dst, const std::string *src)
{
    return toByteArray(dst, src, src->size() + 1);
}








template<>
char *fromByteArray(char *dst, const unsigned char *src, const size_t srcSize)
{
    return (char*) anyFromByteArray((void*) dst, src, srcSize);
}

template<>
char *fromByteArray(char *dst, const unsigned char *src)
{
    return fromByteArray(dst, src, (strlen((char*) src) + 1)*sizeof(char));
}

template<>
std::string *fromByteArray(std::string *dst, const unsigned char *src, const size_t srcSize)
{
    char *tmp = new char[srcSize];

    fromByteArray((void*) tmp, src, srcSize);

    *dst = tmp;

    delete[] tmp;

    return dst;
}




template<>
std::string *fromByteArray(std::string *dst, const unsigned char *src)
{
    size_t srcSize((strlen((char*) src) + 1)*sizeof(char));

    return fromByteArray(dst, src, srcSize);
}

