#include "ItemTable.h"

int itemcpy(ItemTable* dist, const ItemTable* src){
    dist->data = (char*) calloc(strlen(src->data) + 1, sizeof(char));
    if(dist->data == NULL) return 1;
    strcpy(dist->data, src->data);
    dist->key1 = (char*) calloc(strlen(src->key1) + 1, sizeof(char));
    if(dist->key1 == NULL) return 1;
    strcpy(dist->key1, src->key1);
    dist->key2 = (char*) calloc(strlen(src->key2) + 1, sizeof(char));
    if(dist->key2 == NULL) return 1;
    strcpy(dist->key2, src->key2);
    return 0;
}

void freeItem(ItemTable* item){
    free(item->data);
    free(item->key1);
    free(item->key2);
}
