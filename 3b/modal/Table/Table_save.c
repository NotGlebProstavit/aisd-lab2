#include "Table.h"

void saveTable(Table* table){
    FILE* buf = fopen(".buf1", "wb");

    KS1Iterator it1 = begin1(*(table->ks1), table->fn_ks1);
    if(comp1(it1, NULL_ITERATOR1) == 0) {
        fwrite(&(it1.ptr.offset_key), sizeof(long int), 1, buf);
        fwrite(&(it1.ptr.len_key), sizeof(long int), 1, buf);
        saveItem(buf, it1.ptr.item);
        fwrite(&(it1.ptr.offset_next), sizeof(long int), 1, buf);
    }
    while(comp1(it1, NULL_ITERATOR1) != 0){
        fwrite(&(it1.ptr.offset_key), sizeof(long int), 1, buf);
        fwrite(&(it1.ptr.len_key), sizeof(long int), 1, buf);
        saveItem(buf, it1.ptr.item);
        KS1Iterator next = next1(it1);
        if(comp1(next, NULL_ITERATOR1) != 0) {
            it1.ptr.offset_next = ftell(buf) + sizeof(long int);
        } else {
            it1.ptr.offset_next = -1;
        }
        fwrite(&(it1.ptr.offset_next), sizeof(long int), 1, buf);
        it1 = next;
    }
    fclose(buf);
    remove(table->fn_ks1);
    rename(".buf1", table->fn_ks1);

    buf = fopen(".buf2", "wb");

    fwrite(&(table->size), sizeof(long int), 1, buf);
    fseek(buf, sizeof(long int) + table->size * 10 * sizeof(long int), SEEK_SET);
    for(int i = 0; i < table->size; i++){
        KS2Iterator it2 = next2(begin2(table->ks2[i], table->fn_ks2));
        if(comp2(it2, NULL_ITERATOR2) != 0) {
            table->ks2[i].offset_next = ftell(buf);
        } else {
            table->ks2[i].offset_next = -1;
        }
        while(comp2(it2, NULL_ITERATOR2) != 0){
            fwrite(&(it2.ptr.offset_key), sizeof(long int), 1, buf);
            fwrite(&(it2.ptr.len_key), sizeof(long int), 1, buf);
            saveItem(buf, it2.ptr.item);
            fwrite(&(it2.ptr.release), sizeof(long int), 1, buf);
            KS2Iterator next = next2(it2);
            if(comp2(next, NULL_ITERATOR2) != 0) {
                it2.ptr.offset_next = ftell(buf) + sizeof(long int);
            } else {
                it2.ptr.offset_next = -1;
            }
            fwrite(&(it2.ptr.offset_next), sizeof(long int), 1, buf);
            it2 = next;
        }
    }
    fseek(buf, sizeof(long int), SEEK_SET);
    for(int i = 0; i < table->size; i++){
        fwrite(&(table->ks2[i].offset_key), sizeof(long int), 1, buf);
        fwrite(&(table->ks2[i].len_key), sizeof(long int), 1, buf);
        saveItem(buf, table->ks2[i].item);
        fwrite(&(table->ks2[i].release), sizeof(long int), 1, buf);
        fwrite(&(table->ks2[i].offset_next), sizeof(long int), 1, buf);
    }

    fclose(buf);
    remove(table->fn_ks2);
    rename(".buf2", table->fn_ks2);
}
