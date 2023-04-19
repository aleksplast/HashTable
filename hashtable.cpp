#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <immintrin.h>


int HashTableCtor(HashTable* hashtable, unsigned int (*func)(__m128i), int sizetable)
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

int HashTableAdd(HashTable* hashtable, __m128i input)
{
    DBG assert(hashtable != NULL);

    int hash = hashtable->function(input) % hashtable->size;
    InsertElementAfterIndex(hashtable->table[hash], hashtable->table[hash]->LISTTAIL, input);

    return NOERR;
}

SearchStatus FindByHash(HashTable* hashtable, __m128i input)
{
    DBG assert(hashtable != NULL);

    int hash = hashtable->function(input) % hashtable->size;

    Node* curelem = hashtable->table[hash]->fictelem->prev;
    Node* fictelement = hashtable->table[hash]->fictelem;

    while (curelem != fictelement)
    {
       if (_mm_testnzc_si128(curelem->val, input) == 0)
       {
           return SEARCH_SUCCESS;
       }
        curelem = curelem->prev;
    }

    return SEARCH_FAILURE;
}

int HashTableLoad(HashTable* hashtable, Words* array)
{
    DBG assert(hashtable != NULL);
    DBG assert(array != NULL);

    for (int i = 0; i < array->num; i++)
    {
        HashTableAdd(hashtable, array->words[i]);
    }

    return NOERR;
}

int inline strcmp_asm (const char* str1, const char* str2)
{
    int result = 0;
    asm(".intel_syntax noprefix\n\t"
        "mov rsi, %1\n\t"
        "mov rdi, %2\n\t"
        "Next:\n"
            "mov r11b, byte ptr [rsi]\n"
            "mov r10b, byte ptr [rdi]\n"
    	    "cmp r10b, 0\n"
    	    "je done\n"
    	    "cmp r11b, 0\n"
    	    "je done\n"
    	    "cmp r11b, r10b\n"
    	    "jne done\n"
    	    "inc rdi\n"
    	    "inc rsi\n"
    	    "jmp Next\n"
        "done:\n"
            "movzx rax, r10b\n"
            "movzx rbx, r11b\n"
    	    "sub rax, rbx\n"
        ".att_syntax"
        : "=r" (result) : "r" (str1), "r" (str2) : "rax", "rbx", "rsi", "rdi", "r10", "r11"
    );
    return result;
}
