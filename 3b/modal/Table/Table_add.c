#include "Table.h"

void add(Table* table, const char* k1, const char* k2, const char* data){
    Item item = {0,0,0,0,0};
    item.len_key1 = strlen(k1);
    item.len_key2 = strlen(k2);
    item.len_data = strlen(data);
    // Save data
    FILE* fdata = fopen(table->fn_data, "w+b");
    fseek(fdata, 0L, SEEK_END);
    item.offset_key1 = ftell(fdata);
    fwrite(k1, sizeof(char), item.len_key1, fdata);
    item.offset_key2 = ftell(fdata);
    fwrite(k2, sizeof(char), item.len_key2, fdata);
    item.offset_data = ftell(fdata);
    fwrite(data, sizeof(char), item.len_data, fdata);
    fclose(fdata);
    // Save in KeySpace1
    KS1Iterator e1 = end1(table->ks1, table->fn_ks1);
    FILE* fd = fopen(table->fn_ks1, "w+b");
    fseek(fd, 0L, SEEK_END);
    KS1Iterator new_e1 = e1;
    new_e1.ptr->offset_next = ftell(fd);
    int offset_end = -1;
    fwrite(&(item.offset_key1), sizeof(int), 1, fd);
    fwrite(&(item.len_key1), sizeof(int), 1, fd);
    fwrite(&(item), sizeof(Item), 1, fd);
    fwrite(&(offset_end), sizeof(int), 1, fd);
    fclose(fd);
    edit1((KS1Iterator){table->ks1, table->fn_ks2}, e1, new_e1);
    e1 = next1(e1);
    table->ks1 = e1.ptr;
    // Save in KeySpace2
    int hashKey = hash(k2, table->size);
    if(compItem(table->ks2[hashKey].item, (Item){0,0,0,0,0,0})){
        copyItem(&(table->ks2[hashKey].item), &item);
        table->ks2[hashKey].release = 0;
        table->ks2[hashKey].offset_next = -1;
        table->ks2[hashKey].offset_key = item.offset_key2;
        table->ks2[hashKey].len_key = item.len_key2;

        fd = fopen(table->fn_ks2, "w+b");
        fseek(fd, sizeof(int) + hashKey*sizeof(KeySpace2), SEEK_SET);
        fwrite(table->ks2 + hashKey, sizeof(KeySpace2), 1, fd);
        fclose(fd);
    } else {
        char* key2 = getKey2(table->fn_data, table->ks2[hashKey].item);
        if(strcmp(key2, k2) == 0){
            fd = fopen(table->fn_ks2, "w+b");
            fseek(fd, 0L, SEEK_END);
            int offset = ftell(fd);
            fwrite(&(table->ks2[hashKey]), sizeof(KeySpace2), 1, fd);
            table->ks2[hashKey].offset_next = offset;
            table->ks2[hashKey].offset_key = item.offset_key2;
            table->ks2[hashKey].len_key = item.len_key2;
            table->ks2[hashKey].release++;
            copyItem(&(table->ks2[hashKey].item), &item);
            fseek(fd, sizeof(int)+ hashKey*sizeof(KeySpace2), SEEK_SET);
            fwrite(table->ks2 + hashKey, sizeof(KeySpace2), 1, fd);
            fclose(fd);
        } else {
            KS2Iterator it = begin2(table->ks2 + hashKey, table->fn_ks2);
            KS2Iterator next = next2(it);
            while(comp2(next, (KS2Iterator){NULL, NULL}) != 0){
                char* k = getKey2(table->fn_data, value2(next));
                if(strcmp(k, key2) != 0){
                    it = next;
                    next = next2(it);
                    free(k);
                } else {
                    free(k);
                    break;
                }
            }
            fd = fopen(table->fn_ks2, "w+b");
            fseek(fd, 0L, SEEK_END);
            int offset = ftell(fd);
            KeySpace2 ks = {item.offset_key2, item.len_key2, item, 0, -1};
            if(comp2(next, (KS2Iterator){NULL, NULL}) == 0){
                ks.release = 1;
            } else {
                ks.release = next.ptr->release + 1;
                ks.offset_next = it.ptr->offset_next;
            }
            fwrite(&ks, sizeof(KeySpace2), 1, fd);
            fclose(fd);
            KS2Iterator new_it = it;
            it.ptr->offset_next = offset;
            edit2((KS2Iterator){table->ks2 + hashKey, table->fn_ks2}, it, new_it);
        }
        free(key2);
    }
}
