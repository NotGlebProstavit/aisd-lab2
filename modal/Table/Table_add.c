#include "Table.h"

void add(Table* table, Item* item){
    // Add to KeySpace1
    KeySpace1* node = (KeySpace1*) malloc(sizeof(KeySpace1));
    node->key = (char*) calloc(strlen(item->key1) + 1, sizeof(char));
    strcpy(node->key, item->key1);
    node->data = item;
    node->next = table->keySpace1;
    table->keySpace1 = node;

    // Add to KeySpace2
    int hashKey = hash(item->key2, table->size2);
    if(table->keySpace2[hashKey].data == NULL){
        table->keySpace2[hashKey].data = item;
        table->keySpace2[hashKey].key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
        strcpy(table->keySpace2[hashKey].key, item->key2);
    } else {
        KeySpace2* ks = table->keySpace2 + hashKey;
        while(ks->next != NULL && strcmp(ks->next->key, item->key2) != 0) ks = ks->next;
        KeySpace2* elem = (KeySpace2*) malloc(sizeof(KeySpace2));
        elem->next = ks->next;
        ks->next = elem;
        elem->key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
        strcpy(elem->key, item->key2);
        elem->data = item;
        if(elem->next != NULL) elem->release = elem->next->release + 1;
    }
}