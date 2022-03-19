#include "stdlib.h"
#include "string.h"

#ifndef LAB3_ITEMTABLE_H
#define LAB3_ITEMTABLE_H

typedef struct ItemTable{
    char* data;
    char* key1;
    char* key2;
} ItemTable;

void itemTableCopy(ItemTable*, const ItemTable*);
void freeItem(ItemTable*);

#endif //LAB3_ITEMTABLE_H
