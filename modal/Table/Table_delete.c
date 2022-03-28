#include <stdio.h>
#include "Table.h"

void deleteByComposeKey(Table* table, const char* key1, const char* key2){
    Item* item = findByComposeKey(table, key1, key2);
    if(item == NULL) return;
    // Destroy link in KeySpace1
    KeySpace1* ks1 = table->keySpace1;
    if(ks1 == NULL) return;
    if(strcmp(key1, ks1->key) == 0){
        item = ks1->data;
        free(ks1->key);
        if(ks1->next != NULL){
            KeySpace1* t = ks1->next;
            ks1->key = (char*) calloc(strlen(t->key) + 1, sizeof(char));
            strcpy(ks1->key, t->key);
            ks1->data = t->data;
            ks1->next = t->next;
            free(t->key);
            free(t);
        } else {
            ks1->key = NULL;
            ks1->data = NULL;
            free(ks1);
            table->keySpace1 = NULL;
        }
    } else {
        while(ks1->next != NULL && strcmp(ks1->next->key, key1) != 0) ks1 = ks1->next;
        printf("%s\n", ks1->key);
        KeySpace1* t = ks1->next;
        ks1->next = t->next;
        free(t->key);
        free(t);
    }

    // Destroy link in KeySpace2
    int hashKey = hash(key2, table->size2);
    KeySpace2* ks2 = table->keySpace2 + hashKey;
    if(strcmp(ks2->key, key2) == 0 && strcmp(ks2->data->key1, key1) == 0){
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
            ks2->next = t->next;
            free(t->key);
            free(t);
        }
    } else {
        while(ks2->next != NULL && (
                strcmp(key2, ks2->next->key) != 0 ||
                    strcmp(key1, ks2->next->data->key1) != 0
                )) ks2 = ks2->next;
        KeySpace2* t = ks2->next;
        if(t != NULL) {
            ks2->next = t->next;
            free(t->key);
            free(t);
        }
    }
    // Destroy item
    freeItem(item);
    free(item);
}

void deleteByKey1(Table* table, const char* key){
    KeySpace1* node = findByKey1(table, key);
    if(node == NULL) return;
    deleteByComposeKey(table, key, node->data->key2);
    freeItem(node->data);
    free(node->key);
    free(node);
}

void deleteByKey2(Table* table, const char* key, int release){
    int hashKey = hash(key, table->size2);
    KeySpace2* ks = table->keySpace2 + hashKey;
    if(ks->data == NULL) return;
    while(ks != NULL){
        if(ks->key != NULL && strcmp(ks->key, key) == 0 && (release == ks->release || release == -1)){
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

void freeTable(Table* table){
    KeySpace1* ks1 = table->keySpace1;
    while(ks1 != NULL){
        KeySpace1* t = ks1;
        ks1 = ks1->next;
        free(t->key);
        freeItem(t->data);
        free(t->data);
        free(t);
    }
    table->keySpace1 = NULL;

    for(int i = 0; i < table->size2; i++){
        KeySpace2* ks2 = table->keySpace2 + i;
        while(ks2 != NULL){
            KeySpace2* t = ks2;
            ks2 = ks2->next;
            free(t->key);
            if(t == table->keySpace2 + i){
                table->keySpace2[i].key = NULL;
                table->keySpace2[i].data = NULL;
                table->keySpace2[i].next = NULL;
                table->keySpace2[i].release = 0;
            } else {
                free(t);
            }
        }
    }
    free(table->keySpace2);
}
