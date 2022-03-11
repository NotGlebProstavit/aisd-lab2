#include "KeySpace2.h"

KeySpace2** addItemToKS2(KeySpace2** ks, int msize, ItemTable* item, int(*hash)(const char*, int)){
    int hash_index = hash(item->key2, msize);
    if(ks[hash_index] == NULL){
        ks[hash_index] = (KeySpace2*) malloc(sizeof(KeySpace2));
        if(ks[hash_index] == NULL) return NULL;

        ks[hash_index]->key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
        if(ks[hash_index]->key == NULL) return NULL;
        strcpy(ks[hash_index]->key, item->key2);

        ks[hash_index]->release = 0;
        ks[hash_index]->next = NULL;

        ks[hash_index]->data = item;
    } else {
        KeySpace2* newItem = (KeySpace2*) malloc(sizeof(KeySpace2));
        if(newItem == NULL) return NULL;

        newItem->data = item;

        newItem->release = ks[hash_index]->release + 1;

        newItem->key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
        if(newItem->key == NULL) return NULL;
        strcpy(newItem->key, item->key2);

        newItem->next = ks[hash_index];
        ks[hash_index] = newItem;
    }
    return ks;
}
