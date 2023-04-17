#include "hashtable.h"
#include <string.h>

unsigned int HashReturn1(const char* input)
{
    return 1;
}

unsigned int HashReturnFirstASCII(const char* input)
{
    return input[0];
}

unsigned int HashReturnLen(const char* input)
{
    return strlen(input);
}

unsigned int HashReturnSumASCII(const char* input)
{
    unsigned int sum = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        sum += input[i];
    }

    return sum;
}

unsigned int RolHash(const char* input)
{
    unsigned int hash = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        hash = RolFunc(hash, 1) ^ input[i];
    }

    return hash;
}

unsigned int RolFunc(int input, int shift)
{
    return (input << shift) | (input >> (sizeof (int) - shift));
}

unsigned int RorHash(const char* input)
{
    unsigned int hash = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        hash = RorFunc(hash, 1) ^ input[i];
    }

    return hash;
}

unsigned int RorFunc(int input, int shift)
{
    return (input >> shift) | (input << (sizeof (int) - shift));
}

unsigned int MurMurHash(const char* data)
{
    int lenght = strlen(data);
    unsigned int seed = 0;
    const int shift = 24;
    const unsigned int base = 0x5bd1e995;

    unsigned int hash = seed ^ lenght;

    const unsigned char* buffer = (const unsigned char*) data;

    while (lenght >= 4)
    {
        unsigned int curr = *(unsigned int*) buffer;

        curr *= base;
        curr ^= curr >> shift;
        curr *= base;

        hash *= base;
        hash ^= curr;

        buffer += 4;
        lenght -= 4;
    }

    switch (lenght)
    {
        case 3:
            hash ^= buffer[2] << 16;
        case 2:
            hash ^= buffer[1] << 8;
        case 1:
            hash ^= buffer[0];
            hash *= base;
    };

    hash ^= hash >> 13;
    hash *= base;
    hash ^= hash >> 15;

    return hash;
}

unsigned int MurMur(const char* input)
{
    int len = strlen(input);

    unsigned int hash = MurMurHashAsm(input, len);

    return hash;
}
