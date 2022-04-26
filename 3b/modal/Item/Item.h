#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

typedef struct Item{
    long int offset_key1, len_key1;
    long int offset_key2, len_key2;
    long int offset_data, len_data;
} Item;

char* getKey1(const char*, Item);
char* getKey2(const char*, Item);
char* getData(const char*, Item);

char* itemToString(const char*, Item);

int compItem(Item, Item);

void copyItem(Item*, Item*);

void saveItem(FILE*, Item);
void loadItem(FILE*, Item*);

#endif //LAB3_ITEM_H
