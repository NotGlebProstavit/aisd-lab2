#include "Table.h"

char* tableToString(const Table* table){
    char* res = (char*) calloc(1, sizeof(char));
    for(KS1Iterator it = begin1(table->ks1, table->fn_ks1);
            comp1(it, (KS1Iterator){NULL, NULL}) != 0;
            it = next1(it)){
        char* i = itemToString(table->fn_data, value1(it));
        size_t len = strlen(res) + strlen(i) + 1;
        res = (char*) realloc(res, (len + 1) * sizeof(char));
        strcat(res, i);
        strcat(res, "\n");
        res[len] = '\0';
    }
    return res;
}

