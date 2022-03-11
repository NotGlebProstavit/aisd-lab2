#include "KeySpace1.h"

int findKey(KeySpace1* ks1, char* key){
    for(KeySpace1* t = ks1; t != NULL; t=t->next){
        if(compareKeys(t->key, key) == 0) return 1;
    }
    return 0;
}

inline int compareKeys(char* key1, char* key2){
    return strcmp(key1, key2);
}

KeySpace1* addItemToKS1(KeySpace1* ks, ItemTable* item){
    if(findKey(ks, item->key1) != 0) return NULL;
    KeySpace1* newKey = (KeySpace1*) malloc(sizeof(KeySpace1));
    if(newKey == NULL) return NULL;

    newKey->key = (char*) calloc(strlen(item->key1) + 1, sizeof(char));
    if(newKey->key == NULL) return NULL;
    strcpy(newKey->key, item->key1);

    newKey->data = item;

    newKey->next = ks;
    ks = newKey;
    return ks;
}