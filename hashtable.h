#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../List/Simplelist.h"

struct HashTable
{
    List* table;
    int size;
    int (*function)(const char*);
};

int HashTableCtor(HashTable* hashtable, int (*func)(const char*), int sizetable);

int HashReturn1(const char* input);

#endif //HASHTABLE_H
