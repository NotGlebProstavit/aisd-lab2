#include <stdio.h>
#include "../Item/Item.h"

#ifndef LAB3_KEYSPACE1_H
#define LAB3_KEYSPACE1_H

typedef struct KeySpace1{
    int offset_key, len_key;
    Item item;
    int offset_next;
} KeySpace1;

typedef struct KeySpace1Iterator{
    KeySpace1* ptr;
    const char* filename;
} KS1Iterator;

KS1Iterator begin1(KeySpace1*, const char*);
KS1Iterator end1(KeySpace1*, const char*);
Item value1(KS1Iterator);
KS1Iterator next1(KS1Iterator);
void edit1(KS1Iterator, KS1Iterator, KS1Iterator);
int comp1(KS1Iterator, KS1Iterator);

#endif //LAB3_KEYSPACE1_H
