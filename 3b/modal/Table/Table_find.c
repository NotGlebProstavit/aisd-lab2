#include "Table.h"

Item findByComposeKey(const Table* table, const char* key1, const char* key2){
    long int hashKey = hash(key2, table->size);
    KeySpace2 ks = table->ks2[hashKey];
    if(ks.release == 0) return (struct Item){0,0,0,0,0,0};
    for(KS2Iterator it = begin2(table->ks2[hashKey], table->fn_ks2);
            comp2(it, NULL_ITERATOR2) != 0;
            it = next2(it)){
        char* i = getKey1(table->fn_data, value2(it));
        printf("FIND_BY_COMP: %s - %s\n", key1, i);
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
    KS1Iterator ks = begin1(*(table->ks1), table->fn_ks1);
    while(comp1(ks, NULL_ITERATOR1) != 0){
        char* ks_key = getKey1(table->fn_data, value1(ks));
        if(strcmp(key, ks_key) == 0){
            h = (LittleTable*) malloc(sizeof(LittleTable));
            h->release = -1;
            h->next = NULL;
            h->item = ks.ptr.item;
            free(ks_key);
            return h;
        }
        free(ks_key);
        ks = next1(ks);
    }
    return NULL;
}

LittleTable* findByKey2(const Table* table, const char* key){
    LittleTable* answer = NULL;
    long int _hash = hash(key, table->size);
    KS2Iterator ks = begin2(table->ks2[_hash], table->fn_ks2);
    while(comp2(ks, NULL_ITERATOR2) != 0){
        char* ks_key = getKey2(table->fn_data, value2(ks));
        if(strcmp(key, ks_key) == 0){
            if(answer == NULL){
                answer = (LittleTable*) malloc(sizeof(LittleTable));
                answer->next = NULL;
                answer->item = ks.ptr.item;
                answer->release = ks.ptr.release;
            } else {
                LittleTable* t = (LittleTable*) malloc(sizeof(LittleTable));
                t->release = ks.ptr.release;
                t->next = answer;
                answer = t;
                t->item = ks.ptr.item;
            }
            KS2Iterator next = next2(ks);
            if(comp2(next, NULL_ITERATOR2) != 0){
                char* i  = getKey2(table->fn_data, next.ptr.item);
                if(strcmp(i, key) != 0){
                    free(ks_key);
                    free(i);
                    return answer;
                }
                free(i);
            } else {
                free(ks_key);
                return answer;
            }
        }
        free(ks_key);
        ks = next2(ks);
    }
    return NULL;
}

LittleTable* findByManyKey1(const Table* table, const char** keys, int n){
    LittleTable * ks = findByKey1(table, keys[0]);
    for(int i = 1; i < n; i++){
        LittleTable* t = findByKey1(table, keys[i]);
        if(t != NULL) {
            t->next = ks;
            ks = t;
        }
    }
    return ks;
}

LittleTable* findByReleaseKey2(const Table* table, const char* key, int release){
    LittleTable* answer = NULL;
    static long int _hash = -1;
    static KS2Iterator ks = {{0,0,(Item){0,0,0,0,0,0}, 0,-1}, NULL};
    static KS2Iterator buf = {{0,0,(Item){0,0,0,0,0,0}, 0,-1}, NULL};
    long int hashKey = hash(key, table->size);
    if(_hash == -1 || _hash != hashKey){
        _hash = hashKey;
        ks = NULL_ITERATOR2;
        buf = NULL_ITERATOR2;
    }
    if(comp2(ks, NULL_ITERATOR2) == 0){
        ks = begin2(table->ks2[_hash], table->fn_ks2);
    }
    while(comp2(ks, buf) != 0){
        char* ks_key = getKey2(table->fn_data, value2(ks));
        if(strcmp(key, ks_key) == 0 && ks.ptr.release == release){
            answer = (LittleTable*) malloc(sizeof(LittleTable));
            answer->next = NULL;
            answer->release = ks.ptr.release;
            answer->item = value2(ks);
            ks = next2(ks);
            buf = ks;
            free(ks_key);
            return answer;
        }
        free(ks_key);
        ks = next2(ks);
        if(comp2(ks, NULL_ITERATOR2) == 0 && comp2(buf, NULL_ITERATOR2) != 0) {
            ks = begin2(table->ks2[_hash], table->fn_ks2);
        }
    }
    return NULL;
}
