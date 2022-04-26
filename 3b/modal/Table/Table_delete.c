#include "Table.h"

void deleteByComposeKey(Table** table, const char* k1, const char* k2, KS2Iterator* iterator){
    Item item = findByComposeKey((*table), k1, k2);

    if (compItem(item, (Item) {0, 0, 0, 0, 0, 0}) == 0) return;

    long int hashKey = hash(k2, (*table)->size);

    KS1Iterator it1 = begin1(*((*table)->ks1), (*table)->fn_ks1);
    KS2Iterator it2 = begin2((*table)->ks2[hashKey], (*table)->fn_ks2);

    if (comp1(it1, NULL_ITERATOR1) == 0) return;

    char *key1 = getKey1((*table)->fn_data, it1.ptr.item);

    if (strcmp(k1, key1) == 0) {
        KS1Iterator _next1 = next1(it1);
        if (comp1(_next1, NULL_ITERATOR1) != 0) {
            *((*table)->ks1) = _next1.ptr;
        } else {
            *((*table)->ks1) = (KeySpace1) {0, 0, (Item) {0, 0, 0, 0, 0, 0}, -1};
        }
        KS1Iterator new_begin = begin1(*((*table)->ks1), (*table)->fn_ks1);
        edit1(it1, it1, new_begin);
    } else {
        KS1Iterator _next1 = next1(it1);
        while (comp1(_next1, NULL_ITERATOR1) != 0) {
            char *k = getKey1((*table)->fn_data, _next1.ptr.item);
            if (strcmp(k, k1) == 0) {
                free(k);
                break;
            } else {
                it1 = _next1;
                _next1 = next1(_next1);
            }
            free(k);
        }
        KS1Iterator new_it1 = it1;
        new_it1.ptr.offset_next = _next1.ptr.offset_next;
        if(comp1(it1, begin1(*((*table)->ks1), (*table)->fn_ks1)) == 0)
            (*table)->ks1->offset_next = new_it1.ptr.offset_next;
        edit1(begin1(*((*table)->ks1), (*table)->fn_ks1), it1, new_it1);
    }
    free(key1);

    key1 = getKey1((*table)->fn_data, it2.ptr.item);
    char *key2 = getKey2((*table)->fn_data, it2.ptr.item);

    if (strcmp(key2, k2) == 0 && strcmp(key1, k1) == 0){
        KS2Iterator _next2 = next2(it2);
        if(comp2(_next2, NULL_ITERATOR2) == 0){
            (*table)->ks2[hashKey] = (KeySpace2){0, 0, (Item){0,0,0,0,0,0}, 0, -1};
        } else {
            (*table)->ks2[hashKey] = _next2.ptr;
        }
        KS2Iterator new_begin = begin2((*table)->ks2[hashKey], (*table)->fn_ks2);
        edit2(it2, it2, new_begin, hashKey);
        free(key1);
        free(key2);
    } else {
        free(key1);
        free(key2);
        KS2Iterator _next2 = next2(it2);
        while(comp2(_next2, NULL_ITERATOR2) != 0){
            key1 = getKey1((*table)->fn_data, value2(_next2));
            key2 = getKey2((*table)->fn_data, value2(_next2));
            if(strcmp(key1, k1) == 0 && strcmp(key2, k2) == 0) {
                free(key1);
                free(key2);
                break;
            } else {
                free(key1);
                free(key2);
                it2 = _next2;
                _next2 = next2(_next2);;
            }
        }
        KS2Iterator new_it2 = it2;
        new_it2.ptr.offset_next = _next2.ptr.offset_next;
        if(comp2(it2, begin2((*table)->ks2[hashKey], (*table)->fn_ks2)) == 0)
            (*table)->ks2[hashKey].offset_next = new_it2.ptr.offset_next;
        if(iterator != NULL) iterator->ptr.offset_next = new_it2.ptr.offset_next;
        edit2(begin2((*table)->ks2[hashKey], (*table)->fn_ks2), it2, new_it2, hashKey);
    }

    saveTable((*table));
    char* fn_ks1 = (char*) calloc(strlen((*table)->fn_ks1) + 1, sizeof(char));
    strcpy(fn_ks1, (*table)->fn_ks1);
    char* fn_ks2 = (char*) calloc(strlen((*table)->fn_ks2) + 1, sizeof(char));
    strcpy(fn_ks2, (*table)->fn_ks2);
    char* fn_data = (char*) calloc(strlen((*table)->fn_data) + 1, sizeof(char));
    strcpy(fn_data, (*table)->fn_data);
    freeTable(*table);
    free(*table); *table = NULL;
    *table = downloadTable(fn_ks1, fn_ks2, fn_data);
    free(fn_data); free(fn_ks1); free(fn_ks2);
}

void deleteByKey1(Table** table, const char* k){
    LittleTable* it = findByKey1(*table, k);
    if(it == NULL) return;
    char* k2 = getKey2((*table)->fn_data, it->item);
    deleteByComposeKey(table, k, k2, NULL);
    free(k2);
    free(it);
}

void deleteByKey2(Table** table, const char* k, int release){
    LittleTable* littleTable;
    if(release != -1) littleTable = findByReleaseKey2(*table, k, release);
    else littleTable = findByKey2(*table, k);

    while(littleTable != NULL){
        LittleTable* t = littleTable;
        littleTable = t->next;
        char* k1 = getKey1((*table)->fn_data, t->item);
        char* k2 = getKey2((*table)->fn_data, t->item);
        deleteByComposeKey(table, k1, k2, NULL);
        free(k1);
        free(k2);
        free(t);
    }
}

void refreshTable(Table** table){
    for(int i = 0; i < (*table)->size; i++) {
        KS2Iterator it = begin2((*table)->ks2[i], (*table)->fn_ks2);
        KS2Iterator next = next2(it);
        while (comp2(next, NULL_ITERATOR2) != 0) {
            next = next2(it);
            char *k1 = getKey2((*table)->fn_data, value2(it));
            char *k2 = getKey2((*table)->fn_data, value2(next));
            if (strcmp(k1, k2) == 0) {
                char *key = getKey1((*table)->fn_data, value2(next));
                deleteByComposeKey(table, key, k2, &it);
                free(key);
            } else {
                it = next;
            }
            free(k1);
            free(k2);
        }
    }

    saveTable((*table));
    char* fn_ks1 = (char*) calloc(strlen((*table)->fn_ks1) + 1, sizeof(char));
    strcpy(fn_ks1, (*table)->fn_ks1);
    char* fn_ks2 = (char*) calloc(strlen((*table)->fn_ks2) + 1, sizeof(char));
    strcpy(fn_ks2, (*table)->fn_ks2);
    char* fn_data = (char*) calloc(strlen((*table)->fn_data) + 1, sizeof(char));
    strcpy(fn_data, (*table)->fn_data);
    freeTable(*table); free(*table);
    *table = downloadTable(fn_ks1, fn_ks2, fn_data);
    free(fn_data); free(fn_ks1); free(fn_ks2);
}

void freeTable(Table* table){
    free(table->ks1);
    free(table->fn_ks1);
    free(table->ks2);
    free(table->fn_ks2);
    free(table->fn_data);
    table->size = 0;
}
