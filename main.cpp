#include <stdio.h>
#include "hashtable.h"


int main()
{
    HashTable table1 = {};
    HashTableCtor(&table1, *HashReturn1, 5);

    return 0;
}
