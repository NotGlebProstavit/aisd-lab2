#include "Table.h"

int hash(const char* str, int mod){
    int sum = 0;
    int p = 31, p_pow = 1;
    for(int i = 0; i < strlen(str); i++){
        sum = (sum + (str[i] - 'a' + 1) * p_pow) % mod;
        p_pow = (p_pow * p) % mod;
    }
    return sum;
}

void* addItemToTable(Table* table, ItemTable* itemTable){
    KeySpace1* ks1 = addItemToKS1(table->keySpace1, itemTable);
    if(ks1 == NULL) return NULL;
    table->keySpace1 = ks1;
    KeySpace2** ks2 = addItemToKS2(table->keySpace2, table->msize2, itemTable, hash);
    if(ks2 == NULL) return NULL;
    table->keySpace2 = ks2;
    return table;
}
