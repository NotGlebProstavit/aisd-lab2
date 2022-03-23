#include "Table.h"

void deleteByComposeKey(Table* table, const char* key1, const char* key2){
    Item* item;
    if(findByComposeKey(table, key1, key2) == NULL) return;
    // Destroy link in KeySpace1
    KeySpace1* ks1 = table->keySpace1;
    if(ks1 == NULL) return;
    if(strcmp(key1, ks1->key) == 0){
        item = ks1->data;
        free(ks1->key);
        table->keySpace1 = ks1->next;
        free(ks1);
    } else {
        while(ks1->next != NULL && strcmp(ks1->next->key, key1) != 0) ks1 = ks1->next;
        item = ks1->next->data;
        free(ks1->next->key);
        KeySpace1* t = ks1->next;
        ks1->next = t->next;
        free(t);
    }

    // Destroy link in KeySpace2
    int hashKey = hash(key2, table->size2);
    KeySpace2* ks2 = table->keySpace2 + hashKey;
    if(strcmp(ks2->key, key2) == 0 && strcmp(ks2->data->key1, key2) == 0){
        free(ks2->key);
        if(ks2->next == NULL) {
            ks2->key = NULL;
            ks2->release = 0;
            ks2->data = NULL;
        } else {
            ks2->key = (char*) calloc(strlen(ks2->next->key) + 1, sizeof(char));
            strcpy(ks2->key, ks2->next->key);
            ks2->release = ks2->next->release;
            ks2->data = ks2->next->data;
            KeySpace2* t = ks2->next;
            free(t->key);
            free(t);
        }
    } else {
        while(ks2->next != NULL && (
                strcmp(key2, ks2->next->key) != 0 ||
                    strcmp(key1, ks2->next->data->key1) != 0
                )) ks2 = ks2->next;
        KeySpace2* t = ks2->next;
        ks2->next = t->next;
        free(t->key);
        free(t);
    }
    // Destroy item
    freeItem(item);
    free(item);
}

void deleteByKey1(Table* table, const char* key){
    KeySpace1* node = findByKey1(table, key);
    if(node == NULL) return;
    deleteByComposeKey(table, key, node->data->key2);
}

void deleteByKey2(Table* table, const char* key, int release){
    int hashKey = hash(key, table->size2);
    KeySpace2* ks = table->keySpace2 + hashKey;
    if(ks->data == NULL) return;
    while(ks != NULL){
        if(strcmp(ks->key, key) == 0 && (release == ks->release || release == -1)){
            KeySpace2* t = ks;
            ks = ks->next;
            deleteByComposeKey(table, t->data->key1, t->key);
        } else ks = ks->next;
    }
}

void refreshTable(Table* table){
    for(int i = 0; i < table->size2; i++){
        KeySpace2* ks = table->keySpace2 + i;
        while(ks != NULL){
            if(ks->next != NULL && strcmp(ks->key, ks->next->key) == 0){
                deleteByKey2(table, ks->key, ks->next->release);
            } else ks = ks->next;
        }
    }
}