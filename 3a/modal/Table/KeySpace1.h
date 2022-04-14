#include "../Item/Item.h"

#ifndef LAB3_KEYSPACE1_H
#define LAB3_KEYSPACE1_H

typedef struct KeySpace1{
    char* key; // Unique key
    Item* data; // Pointer to Data
    struct KeySpace1* next; // Pointer to next1 key
} KeySpace1;

#endif //LAB3_KEYSPACE1_H
