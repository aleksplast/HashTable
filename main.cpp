#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "hashtable.h"

struct Words
{
    char** words;
    int num;
};

int SplitTextIntoWords(Words* array, char* text);
int WordsCount(char* text);
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
    char* amongus1 = "AMONGUS";
    char* amongus2 = "AMONGUS";
    char* bebra = "BEBRA";

    Text input = {};
    Words text = {};
    TextReader(filename, &input, "r");
    SplitTextIntoWords(&text, input.ptr);

    HashTable table = {};
    HashTableCtor(&table, *MurMur, 1000);

    HashTableLoad(&table, text.words);
    Statistics(&table, statfile8);

    clock_t start = clock();
    StressTable(&text, &table);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time = %lg\n", time);

    HashTableDtor(&table);
    free(text.words);

    return 0;
}

int SplitTextIntoWords(Words* array, char* text)
{
    DBG assert(text != NULL);
    array->num = WordsCount(text);

    array->words = (char**) calloc(array->num + 1, sizeof(char*));        // last pointer will be NULL for easier use later
    int cur = 0;
    if (text[0] != ' ')
    {
        array->words[cur++] = text;
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            text[i] = '\0';
            array->words[cur++] = text + i + 1;
        }
    }

    array->words[cur] = NULL;

    return NOERR;
}

int WordsCount(char* text)
{
    DBG assert(text != NULL);

    int num = 0;
    if (text[0] != ' ')
        num += 1;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
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
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < array->num; j++)
        {
//            printf("Expected = %d, Gain = %d\n", MurMurHash(array->words[j]), MurMur(array->words[j]));
            FindByHash(table, array->words[j]);
        }
    }

    return NOERR;
}
