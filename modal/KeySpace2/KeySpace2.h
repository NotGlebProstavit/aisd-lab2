#include "../ItemTable/ItemTable.h"

#ifndef LAB3_KEYSPACE2_H
#define LAB3_KEYSPACE2_H

typedef struct KeySpace2{
    char* key; // Non-unique key
    int release; // Release of key
    ItemTable* data; // Pointer to data
    struct KeySpace2* next; // Pointer to next element with same key
} KeySpace2;

KeySpace2** addItemToKS2(KeySpace2**, int, ItemTable*, int(*)(const char*, int));

#endif //LAB3_KEYSPACE2_H
