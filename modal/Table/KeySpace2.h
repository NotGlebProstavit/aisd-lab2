#include "../Item/Item.h"

#ifndef LAB3_KEYSPACE2_H
#define LAB3_KEYSPACE2_H

typedef struct KeySpace2{
    char* key; // Non-unique key
    int release; // Release of key
    Item* data; // Pointer to data
    struct KeySpace2* next; // Pointer to next element with same hash(key)
} KeySpace2; // Vector

#endif //LAB3_KEYSPACE2_H
