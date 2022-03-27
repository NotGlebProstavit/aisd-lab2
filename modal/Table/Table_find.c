#include "Table.h"

Item* findByComposeKey(const Table* table, const char* key1, const char* key2){
    int hashKey = hash(key2, table->size2);
    KeySpace2* ks = table->keySpace2 + hashKey;
    if(ks->data == NULL) return NULL;
    while(ks != NULL){
        if(strcmp(key1, ks->data->key1) == 0) return ks->data;
        ks = ks->next;
    }
    return NULL;
}

KeySpace1* findByKey1(const Table* table, const char* key){
    static KeySpace1* head = NULL;
    static KeySpace1* ks = NULL;
    static KeySpace1* buf = NULL;
    if(table != NULL) {
        head = table->keySpace1;
        buf = NULL;
    }
    if(ks == NULL){
        ks = head;
    }
    if(buf != NULL && strlen((char*) buf) == 0) buf = NULL;
    while(ks != buf){
        if(strcmp(ks->key, key) == 0){
            Item* item = (Item*) malloc(sizeof(Item));
            itemCopy(item, ks->data);
            KeySpace1* elem = (KeySpace1*) malloc(sizeof(KeySpace1));
            elem->data = item;
            elem->next = NULL;
            elem->key = (char*) calloc(strlen(item->key1) + 1, sizeof(char));
            strcpy(elem->key, item->key1);
            buf = ks;
            ks = ks->next;
            return elem;
        }
        ks = ks->next;
        if(ks == NULL && buf != NULL) ks = head;
    }
    return NULL;
}

KeySpace2* findByKey2(const Table* table, const char* key){
    static KeySpace2* ks = NULL, *buf = NULL;
    static int _hash = -1;
    int hashKey = hash(key, table->size2);
    if(_hash == -1 || _hash != hashKey){
        _hash = hashKey;
        buf = NULL;
        ks = NULL;
    }
    if(ks == NULL){
        ks = table->keySpace2 + _hash;
    }
    if(buf != NULL && strlen((char*) buf) == 0) buf = NULL;
    KeySpace2* answer = NULL;
    while(ks != buf){
        if(ks != NULL && ks->key != NULL && strcmp(key, ks->key) == 0){
            if(answer == NULL){
                answer = (KeySpace2*) malloc(sizeof(KeySpace2));
                answer->next = NULL;
                answer->release = ks->release;
                answer->data = (Item*) malloc(sizeof(Item));
                itemCopy(answer->data, ks->data);
                answer->key = (char*) calloc(strlen(key)+1,sizeof(char));
                strcpy(answer->key, key);
            } else {
                KeySpace2* t = (KeySpace2*) malloc(sizeof(KeySpace2));
                t->release = ks->release;
                t->data = (Item*) malloc(sizeof(Item));
                itemCopy(t->data, ks->data);
                t->key = (char*) calloc(strlen(key)+1,sizeof(char));
                strcpy(t->key, key);
                t->next = answer;
                answer = t;
            }
            if(ks->next == NULL || strcmp(ks->next->key, key) != 0){
                ks = ks->next;
                buf = ks;
                return answer;
            }
        }
        ks = ks->next;
        if(ks == NULL && buf != NULL){
            ks = table->keySpace2 + _hash;
        }
    }
    return NULL;
}

KeySpace1* findByManyKey1(const Table* table, const char** keys, int n){
    KeySpace1* ks = findByKey1(table, keys[0]);
    for(int i = 1; i < n; i++){
        KeySpace1* t = findByKey1(NULL, keys[i]);
        if(t != NULL) {
            t->next = ks;
            ks = t;
        }
    }
    return ks;
}

KeySpace2* findByReleaseKey2(const Table* table, const char* key, int release){
    static KeySpace2* ks = NULL, *buf = NULL;
    static int _hash = -1;
    int hashKey = hash(key, table->size2);
    if(_hash == -1 || _hash != hashKey){
        _hash = hashKey;
        buf = NULL;
    }
    if(ks == NULL){
        ks = table->keySpace2 + _hash;
    }
    while(ks != buf){
        if(ks != NULL && ks->key != NULL && strcmp(key, ks->key) == 0 && ks->release == release){
            KeySpace2* answer = (KeySpace2 *) malloc(sizeof(KeySpace2));
            answer->next = NULL;
            answer->release = ks->release;
            answer->data = (Item *) malloc(sizeof(Item));
            itemCopy(answer->data, ks->data);
            answer->key = (char *) calloc(strlen(key) + 1, sizeof(char));
            strcpy(answer->key, key);
            ks = ks->next;
            buf = ks;
            return answer;
        }
        ks = ks->next;
        if(ks == NULL && buf != NULL){
            ks = table->keySpace2 + _hash;
        }
    }
    return NULL;
}
