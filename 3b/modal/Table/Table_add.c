#include "Table.h"

void add(Table* table, const char* k1, const char* k2, const char* data){
    Item item = {0,0,0,0,0,0};
    item.len_key1 = strlen(k1);
    item.len_key2 = strlen(k2);
    item.len_data = strlen(data);
    // Save data
    FILE* fdata = fopen(table->fn_data, "r+b");
    fseek(fdata, 0L, SEEK_END);
    item.offset_key1 = ftell(fdata);
    fwrite(k1, sizeof(char), item.len_key1, fdata);
    item.offset_key2 = ftell(fdata);
    fwrite(k2, sizeof(char), item.len_key2, fdata);
    item.offset_data = ftell(fdata);
    fwrite(data, sizeof(char), item.len_data, fdata);
    fclose(fdata);
    // Save in KeySpace1
    if(compItem(table->ks1->item, (Item){0,0,0,0,0,0}) == 0){
        table->ks1->offset_key = item.offset_key1;
        table->ks1->len_key = item.len_key1;
        table->ks1->item = item;
        table->ks1->offset_next = -1;
        FILE* fd = fopen(table->fn_ks1, "w+b");
        fwrite(&(table->ks1->offset_key), sizeof(long int), 1, fd);
        fwrite(&(table->ks1->len_key), sizeof(long int), 1, fd);
        saveItem(fd, table->ks1->item);
        fwrite(&(table->ks1->offset_next), sizeof(long int), 1, fd);
        fclose(fd);
    } else if(table->ks1->offset_next == -1) {
        FILE* fd = fopen(table->fn_ks1, "r+b");
        fseek(fd, 0L, SEEK_END);
        table->ks1->offset_next = ftell(fd);
        fseek(fd, 8*sizeof(long int), SEEK_SET);
        fwrite(&(table->ks1->offset_next), sizeof(long int), 1, fd);
        KeySpace1 ks = {item.offset_key1, item.len_key1, item, -1};
        fwrite(&(ks.offset_key), sizeof(long int), 1, fd);
        fwrite(&(ks.len_key), sizeof(long int), 1, fd);
        saveItem(fd, ks.item);
        fwrite(&(ks.offset_next), sizeof(long int), 1, fd);
        fclose(fd);
    } else {
        KS1Iterator end = end1(*(table->ks1), table->fn_ks1), new_end = end;
        FILE* fd = fopen(table->fn_ks1, "r+b");
        fseek(fd, 0L, SEEK_END);
        new_end.ptr.offset_next = ftell(fd);
        fclose(fd);
        edit1(begin1(*(table->ks1), table->fn_ks1), end, new_end);
        fd = fopen(table->fn_ks1, "r+b");
        fseek(fd, 0L, SEEK_END);
        KeySpace1 ks = {item.offset_key1, item.len_key1, item, -1};
        fwrite(&(ks.offset_key), sizeof(long int), 1, fd);
        fwrite(&(ks.len_key), sizeof(long int), 1, fd);
        saveItem(fd, ks.item);
        fwrite(&(ks.offset_next), sizeof(long int), 1, fd);
        fclose(fd);
    }
    // Save in KeySpace2
    long int hashKey = hash(k2, table->size);
    if(compItem(table->ks2[hashKey].item, (Item){0,0,0,0,0,0}) == 0){
        copyItem(&(table->ks2[hashKey].item), &item);
        table->ks2[hashKey].release = 1;
        table->ks2[hashKey].offset_next = -1;
        table->ks2[hashKey].offset_key = item.offset_key2;
        table->ks2[hashKey].len_key = item.len_key2;

        FILE* fd = fopen(table->fn_ks2, "r+b");
        fseek(fd, sizeof(long int) + hashKey*10*sizeof(long int), SEEK_SET);
        fwrite(&(table->ks2[hashKey].offset_key), sizeof(long int), 1, fd);
        fwrite(&(table->ks2[hashKey].len_key), sizeof(long int), 1, fd);
        saveItem(fd, table->ks2[hashKey].item);
        fwrite(&(table->ks2[hashKey].release), sizeof(long int), 1, fd);
        fwrite(&(table->ks2[hashKey].offset_next), sizeof(long int), 1, fd);
        fclose(fd);
    } else {
        char* key2 = getKey2(table->fn_data, table->ks2[hashKey].item);
        if (strcmp(key2, k2) == 0) {
            KeySpace2 ks = table->ks2[hashKey];

            FILE* fd = fopen(table->fn_ks2, "r+b");
            fseek(fd, 0L, SEEK_END);

            table->ks2[hashKey].offset_next = ftell(fd);
            table->ks2[hashKey].offset_key = item.offset_key2;
            table->ks2[hashKey].len_key = item.len_key2;
            copyItem(&(table->ks2[hashKey].item), &item);
            table->ks2[hashKey].release = ks.release + 1;

            fwrite(&(ks.offset_key), sizeof(long int), 1, fd);
            fwrite(&(ks.len_key), sizeof(long int), 1, fd);
            saveItem(fd, ks.item);
            fwrite(&(ks.release), sizeof(long int), 1, fd);
            fwrite(&(ks.offset_next), sizeof(long int), 1, fd);

            fseek(fd, (1 + 10*hashKey)*sizeof(long int), SEEK_SET);

            fwrite(&(table->ks2[hashKey].offset_key), sizeof(long int), 1, fd);
            fwrite(&(table->ks2[hashKey].len_key), sizeof(long int), 1, fd);
            saveItem(fd, table->ks2[hashKey].item);
            fwrite(&(table->ks2[hashKey].release), sizeof(long int), 1, fd);
            fwrite(&(table->ks2[hashKey].offset_next), sizeof(long int), 1, fd);

            fclose(fd);
        } else {
            KS2Iterator it = begin2(table->ks2[hashKey], table->fn_ks2), next = next2(it);

            while(comp2(next, NULL_ITERATOR2) != 0){
                char* next_key = getKey2(table->fn_data, next.ptr.item);
                if(strcmp(next_key, k2) == 0 ){
                    free(next_key);
                    break;
                } else {
                    free(next_key);
                    it = next;
                    next = next2(it);
                }
            }
            if(comp2(next, NULL_ITERATOR2) == 0) {
                FILE* fd = fopen(table->fn_ks2, "r+b");
                fseek(fd, 0L, SEEK_END);
                KS2Iterator new_it = it;
                new_it.ptr.offset_next = ftell(fd);
                fclose(fd);
                edit2(begin2(table->ks2[hashKey], table->fn_ks2), it, new_it, hashKey);
                if(comp2(it, begin2(table->ks2[hashKey], table->fn_ks2)) == 0)
                    table->ks2[hashKey].offset_next = new_it.ptr.offset_next;
                fd = fopen(table->fn_ks2, "r+b");
                fseek(fd, 0L, SEEK_END);
                KeySpace2 ks = {item.offset_key2, item.len_key2, item, 1, -1};
                fwrite(&(ks.offset_key), sizeof(long int), 1, fd);
                fwrite(&(ks.len_key), sizeof(long int), 1, fd);
                saveItem(fd, ks.item);
                fwrite(&(ks.release), sizeof(long int), 1, fd);
                fwrite(&(ks.offset_next), sizeof(long int), 1, fd);
                fclose(fd);
            } else {
                FILE* fd = fopen(table->fn_ks2, "r+b");
                fseek(fd, 0L, SEEK_END);
                KS2Iterator new_it = it;
                new_it.ptr.offset_next = ftell(fd);
                long int offset = it.ptr.offset_next;
                fclose(fd);
                edit2(begin2(table->ks2[hashKey], table->fn_ks2), it, new_it, hashKey);
                if(comp2(it, begin2(table->ks2[hashKey], table->fn_ks2)) == 0)
                    table->ks2[hashKey].offset_next = new_it.ptr.offset_next;
                fd = fopen(table->fn_ks2, "r+b");
                fseek(fd, 0L, SEEK_END);
                KeySpace2 ks = {item.offset_key2, item.len_key2, item, it.ptr.release + 1, offset};
                fwrite(&(ks.offset_key), sizeof(long int), 1, fd);
                fwrite(&(ks.len_key), sizeof(long int), 1, fd);
                saveItem(fd, ks.item);
                fwrite(&(ks.release), sizeof(long int), 1, fd);
                fwrite(&(ks.offset_next), sizeof(long int), 1, fd);
                fclose(fd);
            }
        }
        free(key2);
    }
}
