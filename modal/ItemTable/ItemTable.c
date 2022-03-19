#include "ItemTable.h"

void freeItem(ItemTable* item){
    free(item->data);
    free(item->key1);
    free(item->key2);
}

void itemTableCopy(ItemTable* dist, const ItemTable* src) {
    dist->data = (char *) calloc(strlen(src->data) + 1, sizeof(char));
    strcpy(dist->data, src->data);
    dist->key1 = (char *) calloc(strlen(src->key1) + 1, sizeof(char));
    strcpy(dist->key1, src->key1);
    dist->key2 = (char *) calloc(strlen(src->key2) + 1, sizeof(char));
    strcpy(dist->key2, src->key2);
}
