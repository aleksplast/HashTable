#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "hashtable.h"

int SplitTextIntoWords(Words* array, Text* text);
int WordsCount(Text* text);
int Statistics(HashTable* hashtable, char* filename);
int StressTable(Words* array, HashTable* table);

int main()
{
    char filename[50] = "HamletFormated.txt";
    char statfile1[50] = "Return1Stat.csv";
    char statfile2[50] = "FirstASCIIstat.csv";
    char statfile3[50] = "ASCIIsumstat.csv";
    char statfile4[50] = "Strlenstat.csv";
    char statfile5[50] = "Rolstat.csv";
    char statfile6[50] = "Rorstat.csv";
    char statfile7[50] = "MurMurstat.csv";
    char statfile8[50] = "MurMurAsm.csv";
    char statfile9[50] = "MurMurAsm.csv";

    Text input = {};
    Words text = {};
    TextReader(filename, &input, "r");
    SplitTextIntoWords(&text, &input);

    HashTable table = {};
    HashTableCtor(&table, *MurMur, 1000);

    HashTableLoad(&table, &text);
    Statistics(&table, statfile8);

    clock_t start = clock();
    StressTable(&text, &table);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time = %lg\n", time);

    HashTableDtor(&table);
    free(input.ptr);
    free(input.Strings);
    free(text.words);

    return 0;
}

int SplitTextIntoWords(Words* array, Text* text)
{
    DBG assert(text != NULL);
    array->num = WordsCount(text);

    array->words = (char**) calloc(array->num, sizeof(char*));        // last pointer will be NULL for easier use later
    int cur = 0;
    if (text->ptr[0] != ' ')
    {
        array->words[cur++] = text->ptr;
    }

    for (int i = 0; i < text->size; i++)
    {
        if (text->ptr[i] == ' ')
        {
            text->ptr[i] = '\0';
            array->words[cur++] = text->ptr + i + 1;
        }
    }

    return NOERR;
}

int WordsCount(Text* text)
{
    DBG assert(text != NULL);

    int num = 0;
    if (text->ptr[0] != ' ')
        num += 1;

    for (int i = 0; i < text->size; i++)
    {
        if (text->ptr[i] == ' ')
            num++;
    }

    return num;
}

int Statistics(HashTable* hashtable, char* filename)
{
    DBG assert(hashtable != NULL);
    DBG assert(filename != NULL);

    FILE* file = fopen(filename, "w");

    for (int i = 0; i < hashtable->size; i++)
    {
        fprintf(file, "%d;", hashtable->table[i]->size);
    }

    fclose(file);

    return NOERR;
}

int StressTable(Words* array, HashTable* table)
{
    for (int i = 0; i < 9500; i++)
    {
        for (int j = 0; j < array->num; j++)
        {
//            printf("Expected = %d, Gain = %d\n", MurMurHash(array->words[j]), MurMur(array->words[j]));
            if (array->words[j] != NULL)
                FindByHash(table, array->words[j]);
        }
    }

    return NOERR;
}
