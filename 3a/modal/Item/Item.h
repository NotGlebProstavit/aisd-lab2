#include "stdlib.h"
#include "string.h"

#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

typedef struct Item_{
    char* data;
    char* key1;
    char* key2;
} Item;

void itemCopy(Item *dist, const Item *src);
void freeItem(Item*);
Item* createItem(const char*, const char*, const char*);
char* itemToString(const Item*);

#endif //LAB3_ITEM_H
