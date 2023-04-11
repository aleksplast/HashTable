#include "hashtable.h"

int HashTableCtor(HashTable* hashtable, int (*func)(const char*), int sizetable)
{
    hashtable->function = func;
    hashtable->size = sizetable;
    hashtable->table = (List*) calloc(sizetable, sizeof(List));

    for (int i = 0; i < sizetable; i++)
    {
        ListCtor(&hashtable->table[i], "graphlog.txt");
    }

    return NOERR;
}

int HashReturn1(const char* input)
{
    return 1;
}

int HashReturnFirstASCII(const char* input)
{
    return input[0];
}

int HashReturnLen(const char* input)
{
    return strlen(input);
}

int HashReturnSumASCII(const char* input)
{
    int sum = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        sum += input[i];
    }

    return sum;
}

