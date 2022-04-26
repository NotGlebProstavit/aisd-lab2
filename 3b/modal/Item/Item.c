#include "Item.h"

char* getKey1(const char* filename, Item item){
    FILE* fd = fopen(filename, "rb");
    char* res = (char*) calloc(item.len_key1 + 1, sizeof(char));
    fseek(fd, item.offset_key1, SEEK_SET);
    fread(res, sizeof(char), item.len_key1, fd);
    fclose(fd);
    return res;
}

char* getKey2(const char* filename, Item item){
    FILE* fd = fopen(filename, "rb");
    char* res = (char*) calloc(item.len_key2 + 1, sizeof(char));
    fseek(fd, item.offset_key2, SEEK_SET);
    fread(res, sizeof(char), item.len_key2, fd);
    fclose(fd);
    return res;
}

char* getData(const char* filename, Item item){
    FILE* fd = fopen(filename, "rb");
    char* res = (char*) calloc(item.len_data + 1, sizeof(char));
    fseek(fd, item.offset_data, SEEK_SET);
    fread(res, sizeof(char), item.len_data, fd);
    fclose(fd);
    return res;
}

char* itemToString(const char* filename, Item item){
    char* key1 = getKey1(filename, item);
    char* key2 = getKey2(filename, item);
    char* data = getData(filename, item);

    char* res = (char*) calloc(strlen(key1) + 3 + strlen(key2) + 3 + strlen(data) + 1, sizeof(char));
    strcat(res, key1);
    strcat(res, " | ");
    strcat(res, key2);
    strcat(res, " | ");
    strcat(res, data);

    free(key1); free(key2); free(data);

    return res;
}

int compItem(Item i1, Item i2){
    if(i1.offset_data != i2.offset_data) return 1;
    if(i1.len_data != i2.len_data) return 1;
    if(i1.offset_key1 != i2.offset_key1) return 1;
    if(i1.len_key1 != i2.len_key1) return 1;
    if(i1.offset_key2 != i2.offset_key2) return 1;
    if(i1.len_key2 != i2.len_key2) return 1;
    return 0;
}

void copyItem(Item* i1, Item* i2){
    i1->offset_data = i2->offset_data;
    i1->len_data = i2->len_data;
    i1->offset_key1 = i2->offset_key1;
    i1->len_key1 = i2->len_key1;
    i1->offset_key2 = i2->offset_key2;
    i1->len_key2 = i2->len_key2;
}

void saveItem(FILE* fd, Item i){
    fwrite(&(i.offset_key1), sizeof(long int), 1,fd);
    fwrite(&(i.len_key1), sizeof(long int), 1,fd);
    fwrite(&(i.offset_key2), sizeof(long int), 1,fd);
    fwrite(&(i.len_key2), sizeof(long int), 1,fd);
    fwrite(&(i.offset_data), sizeof(long int), 1,fd);
    fwrite(&(i.len_data), sizeof(long int), 1,fd);
}

void loadItem(FILE* fd, Item* i){
    fread(&(i->offset_key1), sizeof(long int), 1,fd);
    fread(&(i->len_key1), sizeof(long int), 1,fd);
    fread(&(i->offset_key2), sizeof(long int), 1,fd);
    fread(&(i->len_key2), sizeof(long int), 1,fd);
    fread(&(i->offset_data), sizeof(long int), 1,fd);
    fread(&(i->len_data), sizeof(long int), 1,fd);
}
