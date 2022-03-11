#include "../ItemTable/ItemTable.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#ifndef LAB3_KEYSPACE1_H
#define LAB3_KEYSPACE1_H

typedef struct KeySpace1{
    char* key; // Unique key
    ItemTable* data; // Pointer to data
    struct KeySpace1* next; // Pointer to next key
} KeySpace1;

int findKey(KeySpace1*, char*); // Need for check unique keys
int compareKeys(char*, char*); // Function for compare keys
KeySpace1* addItemToKS1(KeySpace1*, ItemTable*);

#endif //LAB3_KEYSPACE1_H