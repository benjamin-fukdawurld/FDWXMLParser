#ifndef BYTECONVERSION_H
#define BYTECONVERSION_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>


#include <stdint.h>
#include <cstring>


unsigned char *anyToByteArray(unsigned char *dst, const void *src, const size_t srcSize);

void *anyFromByteArray(void *dst, const unsigned char *src, const size_t srcSize);






template<typename T>
unsigned char *toByteArray(unsigned char *dst, const T *src, const size_t srcSize)
{
    return anyToByteArray(dst, (void*) src, srcSize);
}

template<typename T>
unsigned char *toByteArray(unsigned char *dst, const T *src)
{
    return toByteArray(dst, src, sizeof(T));
}



template<>
unsigned char *toByteArray(unsigned char *dst, const char *src, const size_t srcSize);

template<>
unsigned char *toByteArray(unsigned char *dst, const char *src);

template<>
unsigned char *toByteArray(unsigned char *dst, const std::string *src, const size_t srcSize);

template<>
unsigned char *toByteArray(unsigned char *dst, const std::string *src);


template<typename T>
T *fromByteArray(T *dst, const unsigned char *src, const size_t dstSize)
{
    return (T*) anyFromByteArray((void*) dst, src, dstSize);
}



template<typename T>
T *fromByteArray(T *dst, const unsigned char *src)
{
    return fromByteArray(dst, src, sizeof(T));
}



template<>
char *fromByteArray(char *dst, const unsigned char *src, const size_t srcSize);

template<>
char *fromByteArray(char *dst, const unsigned char *src);



std::string *fromByteArray(std::string *dst, const unsigned char *src, const size_t srcSize);


std::string *fromByteArray(std::string *dst, const unsigned char *src);




template<typename T, typename OUT>
OUT &toOtherBase(OUT &out, T src, const char *base, int width, char c)
{
    if(strcmp(base, "dec") == 0)
    out << std::dec;
    else if(strcmp(base, "oct") == 0)
    out << std::oct;
    else if(strcmp(base, "hex") == 0)
    out << std::hex;

    if(width > 1)
    out << std::setw(width) << std::setfill(c);

    out << src;

    return out;
}



#endif // BYTECONVERSION_H
