#include "Table.h"

char* tableToString(const Table* table){
    char* s = NULL;
    size_t len = 0;
    KeySpace1* ks = table->keySpace1;
    if(ks == NULL) return NULL;
    while(ks != NULL){
        Item* item = ks->data;
        char* i = itemToString(item);
        if(s == NULL){
            len = strlen(i);
            s = (char*) calloc(len + 2, sizeof(char));
            strcpy(s, i);
            strcpy(s + len, "\n");
        } else {
            size_t new_chunk = strlen(i);
            s = (char*) realloc(s, (len + new_chunk + 2) * sizeof(char));
            strcpy(s + len, i);
            len += new_chunk;
            strcpy(s + len, "\n");
        }
        ks = ks->next;
    }
    return s;
}
