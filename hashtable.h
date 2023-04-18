#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "./include/SimpleList.h"
#include "./include/text-sort.h"
#include <immintrin.h>

#define LISTTAIL fictelem->prev
#define LISTHEAD fictelem->next

struct HashTable
{
    List** table;
    int size;
    unsigned int (*function)(__m128i);
};

enum SearchStatus
{
    SEARCH_FAILURE,
    SEARCH_SUCCESS,
};

struct Words
{
    __m128i* words;
    int num;
};

//-------------- MAIN HASH TABLE FUNC --------------//

int HashTableCtor(HashTable* hashtable, unsigned int (*func)(__m128i), int sizetable);

int HashTableDtor(HashTable* hashtable);

int HashTableAdd(HashTable* hashtable, __m128i input);

SearchStatus FindByHash(HashTable* hashtable, __m128i input);

int HashTableLoad(HashTable* hashtable, Words* array);

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

unsigned int MurMur(__m128i input);

extern "C" inline unsigned int MurMurHashAsm (char* input, int len);

int strcmp_asm (const char* str1, const char* str2);

#endif //HASHTABLE_H
