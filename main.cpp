#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"

char** SplitTextIntoWords(char* text);
int WordsCount(char* text);
int Statistics(HashTable* hashtable, char* filename);

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
    char statfile8[50] = "CRCstat.csv";

    Text input = {};
    TextReader(filename, &input, "r");
    char** words = SplitTextIntoWords(input.ptr);

    HashTable table = {};
    HashTableCtor(&table, *HashReturnSumASCII, 1000);

    HashTableLoad(&table, words);
    Statistics(&table, statfile3);

    HashTableDtor(&table);
    free(words);
    free(input.ptr);
    free(input.Strings);
    printf("DONE\n");
    return 0;
}

char** SplitTextIntoWords(char* text)
{
    DBG assert(text != NULL);
    int wordsnum = WordsCount(text);

    char** words = (char**) calloc(wordsnum + 1, sizeof(char*));        // last pointer will be NULL for easier use later
    int cur = 0;
    if (text[0] != ' ')
    {
        words[cur++] = text;
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            text[i] = '\0';
            words[cur++] = text + i + 1;
        }
    }

    words[cur] = NULL;

    return words;
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
