#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


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

SearchStatus FindByHash(HashTable* hashtable, int hash, const char* input)
{
    DBG assert(hashtable != NULL);
    DBG assert(input != NULL);

    Node* curelem = hashtable->table[hash]->LISTTAIL;
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
