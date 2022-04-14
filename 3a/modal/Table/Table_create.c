#include "Table.h"

Table* createTable(int size){
    Table* table = (Table*) malloc(sizeof(Table));
    table->size2 = size;
    table->keySpace1 = NULL;
    table->keySpace2 = (KeySpace2*) malloc(table->size2 * sizeof(KeySpace2));
    for(int i = 0; i < table->size2; i++){
        table->keySpace2[i].data = NULL;
        table->keySpace2[i].key = NULL;
        table->keySpace2[i].next = NULL;
        table->keySpace2[i].release = 0;
    }
    return table;
}

int hash(const char* s, int n){
    int h = 5381 % n;
    for(int i = 0; i < strlen(s); i++){
        h = ((h << 5) + h + s[i]) % n;
    }
    return h % n;
}
