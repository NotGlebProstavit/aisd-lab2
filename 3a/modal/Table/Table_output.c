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
            len = strlen(i) + 1;
            s = (char*) calloc(len + 1, sizeof(char));
            strcpy(s, i);
            strcat(s, "\n");
        } else {
            size_t new_chunk = strlen(i) + 1;
            s = (char*) realloc(s, (len + new_chunk + 1) * sizeof(char));
            strcat(s, i);
            strcat(s, "\n");
            len += new_chunk+1;
        }
        free(i);
        ks = ks->next;
    }
    return s;
}
