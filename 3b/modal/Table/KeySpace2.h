#include <stdio.h>
#include "../Item/Item.h"

#ifndef LAB3_KEYSPACE2_H
#define LAB3_KEYSPACE2_H

typedef struct KeySpace2{
    long int offset_key, len_key;
    Item item;
    long int release;
    long int offset_next;
} KeySpace2;

typedef struct KeySpace2Iterator{
    KeySpace2 ptr;
    const char* filename;
} KS2Iterator;

KS2Iterator begin2(KeySpace2, const char*);
KS2Iterator end2(KeySpace2, const char*);
Item value2(KS2Iterator);
KS2Iterator next2(KS2Iterator);
void edit2(KS2Iterator, KS2Iterator, KS2Iterator, long int);
int comp2(KS2Iterator, KS2Iterator);

#define NULL_ITERATOR2 (KS2Iterator){{0,0,{0,0,0,0,0,0},0,-1}, NULL};

#endif //LAB3_KEYSPACE2_H
