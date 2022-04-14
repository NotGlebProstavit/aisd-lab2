#include "Table.h"

void deleteByComposeKey(Table* table, const char* k1, const char* k2){
    Item item = findByComposeKey(table, k1, k2);
    if (compItem(item, (Item) {0, 0, 0, 0, 0, 0}) == 0) return;
    int hashKey = hash(k2, table->size);
    KS1Iterator it1 = begin1(table->ks1, table->fn_ks1);
    KS2Iterator it2 = begin2(table->ks2 + hashKey, table->fn_ks2);
    if (comp1(it1, (KS1Iterator) {NULL, NULL}) == 0) return;
    char *key1 = getKey1(table->fn_data, it1.ptr->item);
    if (strcmp(k1, key1) == 0) {
        KS1Iterator _next1 = next1(it1);
        if (comp1(_next1, (KS1Iterator) {NULL, NULL}) != 0) {
            table->ks1 = _next1.ptr;
        } else {
            *table->ks1 = (KeySpace1) {0, 0, (Item) {0, 0, 0, 0, 0, 0}, -1};
        }
    } else {
        KS1Iterator _next1 = next1(it1);
        while (comp1(_next1, (KS1Iterator) {NULL, NULL}) != 0) {
            char *k = getKey1(table->fn_data, _next1.ptr->item);
            if (strcmp(k, k1) == 0) {
                free(k);
                break;
            } else {
                it1 = _next1;
                _next1 = next1(_next1);
            }
        }
        KS1Iterator new_it1 = it1;
        new_it1.ptr->offset_next = _next1.ptr->offset_next;
        edit1(begin1(table->ks1, table->fn_ks1), it1, new_it1);
    }
    free(key1);

    key1 = getKey1(table->fn_data, it2.ptr->item);
    char *key2 = getKey2(table->fn_data, it2.ptr->item);
    if (strcmp(key2, k2) == 0 && strcmp(key1, k1) == 0){
        KS2Iterator _next2 = next2(it2);
        if(comp2(_next2, (KS2Iterator){NULL, NULL}) == 0){
            table->ks2[hashKey] = (KeySpace2){0, 0, (Item){0,0,0,0,0,0}, 0, -1};
        } else {
            table->ks2[hashKey] = *_next2.ptr;
        }
        free(key1);
        free(key2);
    } else {
        free(key1);
        free(key2);
        KS2Iterator _next2 = next2(it2);
        while(comp2(_next2, (KS2Iterator){NULL, NULL}) != 0){
            key1 = getKey1(table->fn_data, value2(_next2));
            key2 = getKey2(table->fn_data, value2(_next2));
            if(strcmp(key1, k1) == 0 && strcmp(key2, k2) == 0) {
                free(key1);
                free(key2);
                break;
            } else {
                free(key1);
                free(key2);
                it2 = _next2;
                _next2 = next2(_next2);
            }
        }
        KS2Iterator new_it2 = it2;
        new_it2.ptr->offset_next = _next2.ptr->offset_next;
        edit2(begin2(table->ks2 + hashKey, table->fn_ks2), it2, new_it2);
    }
}

void deleteByKey1(Table* table, const char* k){
    LittleTable* it = findByKey1(table, k);
    if(it == NULL) return;
    char* k2 = getKey2(table->fn_data, it->item);
    deleteByComposeKey(table, k, k2);
    free(k2);
    free(it);
}

void deleteByKey2(Table* table, const char* k, int release){
    int hashKey = hash(k, table->size);
    KS2Iterator it = begin2(table->ks2 + hashKey, table->fn_ks2);
    if(compItem(value2(it), (Item){0,0,0,0,0,0}) == 0) return;
    while(comp2(it, (KS2Iterator){NULL, NULL})){
        char* key = getKey2(table->fn_data, value2(it));
        if(strcmp(key, k) == 0 && (release == it.ptr->release || release == -1)){
            char* k1 = getKey1(table->fn_data, value2(it));
            deleteByComposeKey(table, k1, key);
            free(k1);
        } else {
            it = next2(it);
        }
        free(key);
    }
}

void refreshTable(Table* table){
    for(int i = 0; i < table->size; i++){
        KS2Iterator it = begin2(table->ks2 + i, table->fn_ks2);
        while(comp2(it, (KS2Iterator){NULL, NULL}) != 0){
            KS2Iterator next = next2(it);
            char* k1 = getKey2(table->fn_data, value2(it));
            char* k2 = getKey2(table->fn_data, value2(next));
            if(strcmp(k1, k2) == 0){
                char* key = getKey1(table->fn_data, value2(next));
                deleteByComposeKey(table, key, k2);
                free(key);
            } else {
                it = next;
            }
            free(k1);
            free(k2);
        }
    }
}

void freeTable(Table* table){
    free(table->ks1);
    free(table->fn_ks1);
    free(table->ks2);
    free(table->fn_ks2);
    free(table->fn_data);
    table->size = 0;
}
