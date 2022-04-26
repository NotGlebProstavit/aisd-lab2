#include "Table.h"

long int hash(const char* s, long int n){
    long int h = 5381 % n;
    for(int i = 0; i < strlen(s); i++){
        h = ((h << 5) + h + s[i]) % n;
    }
    return h % n;
}

Table* createTable(const char* fn_1, const char* fn_2, const char* fn_d, int size){
    Table* table = (Table*) malloc(sizeof(Table));
    table->size = size;

    table->fn_ks1 = (char*) calloc(strlen(fn_1) + 1, sizeof(char));
    strcpy(table->fn_ks1, fn_1);
    table->fn_ks2 = (char*) calloc(strlen(fn_2) + 1, sizeof(char));
    strcpy(table->fn_ks2, fn_2);
    table->fn_data = (char*) calloc(strlen(fn_d) + 1, sizeof(char));
    strcpy(table->fn_data, fn_d);

    table->ks1 = (KeySpace1*) malloc(sizeof(KeySpace1));
    table->ks1->offset_key = 0;
    table->ks1->len_key = 0;
    table->ks1->offset_next = -1;
    table->ks1->item = (Item){0,0,0,0,0,0};
    table->ks2 = (KeySpace2*) malloc(table->size * sizeof(KeySpace2));
    for(int i = 0; i < size; i++){
        table->ks2[i].offset_key = 0;
        table->ks2[i].len_key = 0;
        table->ks2[i].release = 0;
        table->ks2[i].offset_next = -1;
        table->ks2[i].item.len_key1 = 0;
        table->ks2[i].item.len_key2 = 0;
        table->ks2[i].item.offset_key1 = 0;
        table->ks2[i].item.offset_key2 = 0;
        table->ks2[i].item.len_data = 0;
        table->ks2[i].item.offset_data = 0;
    }

    FILE* fd = fopen(table->fn_ks2, "w+b");
    long int* zero = (long int*) calloc(1 + 10 * table->size, sizeof(long int));
    fwrite(zero, sizeof(long int), 1+10*table->size, fd);
    fclose(fd);
    free(zero);

    return table;
}

Table* downloadTable(const char* fn_1, const char* fn_2, const char* fn_d){
    FILE* fd = fopen(fn_2, "rb");
    Table* table = (Table*) malloc(sizeof(Table));
    fread(&(table->size), sizeof(long int), 1, fd);
    table->fn_ks1 = (char*) calloc(strlen(fn_1) + 1, sizeof(char));
    strcpy(table->fn_ks1, fn_1);
    table->fn_ks2 = (char*) calloc(strlen(fn_2) + 1, sizeof(char));
    strcpy(table->fn_ks2, fn_2);
    table->fn_data = (char*) calloc(strlen(fn_d) + 1, sizeof(char));
    strcpy(table->fn_data, fn_d);
    table->ks2 = (KeySpace2*) malloc(table->size * sizeof(KeySpace2));
    for(int i = 0; i < table->size; i++){
        fread(&(table->ks2[i].offset_key), sizeof(long int), 1, fd);
        fread(&(table->ks2[i].len_key), sizeof(long int), 1, fd);
        loadItem(fd, &(table->ks2[i].item));
        fread(&(table->ks2[i].release), sizeof(long int), 1, fd);
        fread(&(table->ks2[i].offset_next), sizeof(long int), 1, fd);
    }
    fclose(fd);
    table->ks1 = (KeySpace1*) malloc(sizeof(KeySpace1));
    fd = fopen(fn_1, "rb");
    fread(&(table->ks1->offset_key), sizeof(long int), 1, fd);
    fread(&(table->ks1->len_key), sizeof(long int), 1, fd);
    loadItem(fd, &(table->ks1->item));
    fread(&(table->ks1->offset_next), sizeof(long int), 1, fd);
    fclose(fd);
    return table;
}

