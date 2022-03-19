#include "../ItemTable/ItemTable.h"

#ifndef LAB3_KEYSPACE2_H
#define LAB3_KEYSPACE2_H

typedef struct KeySpace2{
    char* key; // Non-unique key
    int release; // Release of key
    ItemTable* data; // Pointer to data
    struct KeySpace2* next; // Pointer to next element with same hash(key)
} KeySpace2;

KeySpace2* addItemToKS2(KeySpace2*, int, ItemTable*, int(*)(const char*, int));
KeySpace2* findByKey2(KeySpace2*, int, const char*, int(*)(const char*, int));
KeySpace2* findByKey2Release(KeySpace2*, int, const char*, int(*)(const char*, int), int);
KeySpace2* cleanUpKS2(KeySpace2*, int);
#endif //LAB3_KEYSPACE2_H
