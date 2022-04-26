#include "Item.h"

void freeItem(Item* item){
    free(item->data);
    free(item->key1);
    free(item->key2);
}

void itemCopy(Item* dist, const Item* src) {
    dist->data = (char *) calloc(strlen(src->data) + 1, sizeof(char));
    strcpy(dist->data, src->data);
    dist->key1 = (char *) calloc(strlen(src->key1) + 1, sizeof(char));
    strcpy(dist->key1, src->key1);
    dist->key2 = (char *) calloc(strlen(src->key2) + 1, sizeof(char));
    strcpy(dist->key2, src->key2);
}

Item* createItem(const char* data, const char* key1, const char* key2){
    Item* item = (Item*) malloc(sizeof(Item));
    item->data = (char *) calloc(strlen(data) + 1, sizeof(char));
    strcpy(item->data, data);
    item->key1 = (char *) calloc(strlen(key1) + 1, sizeof(char));
    strcpy(item->key1, key1);
    item->key2 = (char *) calloc(strlen(key2) + 1, sizeof(char));
    strcpy(item->key2, key2);
    return item;
}

char* itemToString(const Item* item){
    size_t key1 = strlen(item->key1), key2 = strlen(item->key2), data = strlen(item->data);
    char* s = (char*) calloc(key1 + 3 + key2 + 3 + data + 1, sizeof(char));
    strcpy(s, item->key1);
    strcat(s, " | ");
    strcat(s, item->key2);
    strcat(s, " | ");
    strcat(s, item->data);
    return s;
}
