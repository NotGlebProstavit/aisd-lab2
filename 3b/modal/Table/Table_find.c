#include "Table.h"

Item findByComposeKey(const Table* table, const char* key1, const char* key2){
    int hashKey = hash(key2, table->size);
    KeySpace2* ks = table->ks2 + hashKey;
    if(ks->release == 0) return (struct Item){0,0,0,0,0,0};
    for(KS2Iterator it = begin2(table->ks2, table->fn_ks2);
            comp2(it, (KS2Iterator){NULL, NULL}) != 0;
            it = next2(it)){
        char* i = getKey1(table->fn_data, value2(it));
        if(strcmp(key1, i) == 0){
            free(i);
            return value2(it);
        }
        free(i);
    }
    return (struct Item){0,0,0,0,0,0};
}

LittleTable* findByKey1(const Table* table, const char* key){
    LittleTable* h = NULL;
    static KS1Iterator head = {NULL, NULL};
    static KS1Iterator ks = {NULL, NULL};
    static KS1Iterator buf = {NULL, NULL};
    if(comp1(head, (KS1Iterator){NULL, NULL}) == 0){
        head = begin1(table->ks1, table->fn_ks1);
        buf = (KS1Iterator){NULL, NULL};
    }
    if(comp1(ks, (KS1Iterator){NULL, NULL}) == 0){
        ks = head;
    }
    while(comp1(ks, buf) != 0){
        char* ks_key = getKey1(table->fn_data, value1(ks));
        if(strcmp(key, ks_key) == 0){
            h = (LittleTable*) malloc(sizeof(LittleTable));
            h->next = NULL;
            h->item = value1(ks);
            buf = ks;
            ks = next1(ks);
            free(ks_key);
            return h;
        }
        free(ks_key);
        ks = next1(ks);
        if(comp1(ks, (KS1Iterator){NULL, NULL}) == 0 && comp1(buf, (KS1Iterator){NULL, NULL}) != 0) ks = head;
    }
    return NULL;
}

LittleTable* findByKey2(const Table* table, const char* key){
    LittleTable* answer = NULL;
    static int _hash = -1;
    static KS2Iterator ks = {NULL, NULL};
    static KS2Iterator buf = {NULL, NULL};
    int hashKey = hash(key, table->size);
    if(_hash == -1 || _hash != hashKey){
        _hash = hashKey;
        ks = (KS2Iterator){NULL, NULL};
        buf = (KS2Iterator){NULL, NULL};
    }
    if(comp2(ks, (KS2Iterator){NULL, NULL}) == 0){
        ks = begin2(table->ks2 + _hash, table->fn_ks2);
    }
    while(comp2(ks, buf) != 0){
        char* ks_key = getKey2(table->fn_data, value2(ks));
        if(strcmp(key, ks_key) == 0){
            if(answer == NULL){
                answer = (LittleTable*) malloc(sizeof(LittleTable));
                answer->next = NULL;
                answer->item = value2(ks);
            } else {
                LittleTable* t = (LittleTable*) malloc(sizeof(LittleTable));
                t->next = answer;
                answer = t;
                t->item = value2(ks);
            }
            KS2Iterator next = next2(ks);
            if(comp2(next, (KS2Iterator){NULL, NULL}) != 0){
                char* i = getKey2(table->fn_data, value2(next));
                if(strcmp(i, key) != 0){
                    ks = next;
                    buf = ks;
                    return answer;
                }
            } else {
                ks = next;
                buf = ks;
                return answer;
            }
        }
        ks = next2(ks);
        if(comp2(ks, (KS2Iterator){NULL, NULL}) == 0 && comp2(buf, (KS2Iterator){NULL, NULL}) != 0) {
            ks = begin2(table->ks2 + _hash, table->fn_ks2);
        }
    }
    return NULL;
}

LittleTable* findByManyKey1(const Table* table, const char** keys, int n){
    LittleTable * ks = findByKey1(table, keys[0]);
    for(int i = 1; i < n; i++){
        LittleTable* t = findByKey1(NULL, keys[i]);
        if(t != NULL) {
            t->next = ks;
            ks = t;
        }
    }
    return ks;
}

LittleTable* findByReleaseKey2(const Table* table, const char* key, int release){
    LittleTable* answer = NULL;
    static int _hash = -1;
    static KS2Iterator ks = {NULL, NULL};
    static KS2Iterator buf = {NULL, NULL};
    int hashKey = hash(key, table->size);
    if(_hash == -1 || _hash != hashKey){
        _hash = hashKey;
        ks = (KS2Iterator){NULL, NULL};
        buf = (KS2Iterator){NULL, NULL};
    }
    if(comp2(ks, (KS2Iterator){NULL, NULL}) == 0){
        ks = begin2(table->ks2 + _hash, table->fn_ks2);
    }
    while(comp2(ks, buf) != 0){
        char* ks_key = getKey2(table->fn_data, value2(ks));
        if(strcmp(key, ks_key) == 0 && ks.ptr->release == release){
            answer = (LittleTable*) malloc(sizeof(LittleTable));
            answer->next = NULL;
            answer->item = value2(ks);
            ks = next2(ks);
            buf = ks;
            return answer;
        }
        ks = next2(ks);
        if(comp2(ks, (KS2Iterator){NULL, NULL}) == 0 && comp2(buf, (KS2Iterator){NULL, NULL}) != 0) {
            ks = begin2(table->ks2 + _hash, table->fn_ks2);
        }
    }
    return NULL;
}
