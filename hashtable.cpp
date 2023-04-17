#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <immintrin.h>


int HashTableCtor(HashTable* hashtable, unsigned int (*func)(const char*), int sizetable)
{
    DBG assert(hashtable != NULL);

    hashtable->function = func;
    hashtable->size = sizetable;
    hashtable->table = (List**) calloc(sizetable, sizeof(List*));

    for (int i = 0; i < sizetable; i++)
    {
        hashtable->table[i] = (List*) calloc(1, sizeof(List));
        ListCtor(hashtable->table[i], "graphlog.txt");
    }

    return NOERR;
}

int HashTableDtor(HashTable* hashtable)
{
    DBG assert(hashtable != NULL);

    for (int i = 0; i < hashtable->size; i++)
    {
        ListDetor(hashtable->table[i]);
        free(hashtable->table[i]);
    }

    hashtable->size = -1;
    hashtable->function = NULL;
    free(hashtable->table);
    hashtable->table = NULL;

    return NOERR;
}

int HashTableAdd(HashTable* hashtable, const char* input)
{
    DBG assert(hashtable != NULL);
    DBG assert(input != NULL);

    int hash = hashtable->function(input) % hashtable->size;
    InsertElementAfterIndex(hashtable->table[hash], hashtable->table[hash]->LISTTAIL, input);

    return NOERR;
}

SearchStatus FindByHash(HashTable* hashtable, const char* input)
{
    DBG assert(hashtable != NULL);
    DBG assert(input != NULL);

    int hash = hashtable->function(input) % hashtable->size;

    Node* curelem = hashtable->table[hash]->fictelem->prev;
    Node* fictelement = hashtable->table[hash]->fictelem;

    while (curelem != fictelement)
    {
        if (strcmp(curelem->val, input) == 0)
            return SEARCH_SUCCESS;
        curelem = curelem->prev;
    }

    return SEARCH_FAILURE;
}

int HashTableLoad(HashTable* hashtable, char** words)
{
    DBG assert(hashtable != NULL);
    DBG assert(words != NULL);

    for (int i = 0; words[i] != NULL; i++)
    {
        HashTableAdd(hashtable, words[i]);
    }

    return NOERR;
}

SearchStatus FindByHashAVX(HashTable* hashtable, const char* input)
{
    DBG assert(hashtable != NULL);
    DBG assert(hashtable != NULL);

    int hash = hashtable->function(input) % hashtable->size;

    Node* curelem = hashtable->table[hash]->fictelem->prev;
    Node* fictelement = hashtable->table[hash]->fictelem;

    __m256i content = _mm256_loadu_si256((__m256i*) input);

    while (curelem != fictelement)
    {
        __m256i curcontent = _mm256_loadu_si256((__m256i*) curelem->val);
        __m256i cmpmask = _mm256_cmpeq_epi8(curcontent, content);

        unsigned int mask = _mm256_testnzc_si256(cmpmask);

        if (mask == 0xFFFFFFFF)
        {
//            printf("To find = %s, found = %s\n", input, curelem->val);
            return SEARCH_SUCCESS;
        }

        curelem = curelem->prev;
    }

    return SEARCH_FAILURE;
}
