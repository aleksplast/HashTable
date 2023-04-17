#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "./include/SimpleList.h"
#include "./include/text-sort.h"

#define LISTTAIL fictelem->prev
#define LISTHEAD fictelem->next

struct HashTable
{
    List** table;
    int size;
    unsigned int (*function)(const char*);
};

enum SearchStatus
{
    SEARCH_FAILURE,
    SEARCH_SUCCESS,
};

//-------------- MAIN HASH TABLE FUNC --------------//

int HashTableCtor(HashTable* hashtable, unsigned int (*func)(const char*), int sizetable);

int HashTableDtor(HashTable* hashtable);

int HashTableAdd(HashTable* hashtable, const char* input);

SearchStatus FindByHash(HashTable* hashtable, const char* input);

int HashTableLoad(HashTable* hashtable, char** words);

SearchStatus FindByHashAVX(HashTable* hashtable, const char* input);

//-------------- HASH FUNC --------------//

unsigned int HashReturn1(const char* input);

unsigned int HashReturnFirstASCII(const char* input);

unsigned int HashReturnSumASCII(const char* input);

unsigned int HashReturnLen(const char* input);

unsigned int MurMurHash(const char* data);

unsigned int RolHash(const char* input);

unsigned int RolFunc(int input, int shift);

unsigned int RorHash(const char* input);

unsigned int RorFunc(int input, int shift);

extern "C" inline uint32_t MurMurHashAsm (const char* key);

#endif //HASHTABLE_H
