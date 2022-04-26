#include "KeySpace2.h"

KS2Iterator begin2(KeySpace2 ks, const char* filename){
    return (KS2Iterator){ks, filename};
}

KS2Iterator next2(KS2Iterator it){
    if(it.ptr.offset_next == -1){
        return NULL_ITERATOR2;
    }
    FILE* fd = fopen(it.filename, "r+b");
    fseek(fd, it.ptr.offset_next, SEEK_SET);
    fread(&(it.ptr.offset_key), sizeof(long int), 1, fd);
    fread(&(it.ptr.len_key), sizeof(long int), 1, fd);
    loadItem(fd, &(it.ptr.item));
    fread(&(it.ptr.release), sizeof(long int), 1, fd);
    fread(&(it.ptr.offset_next), sizeof(long int), 1, fd);
    fclose(fd);
    return (KS2Iterator){.ptr = it.ptr, .filename = it.filename};
}

Item value2(KS2Iterator it){
    return it.ptr.item;
}

KS2Iterator end2(KeySpace2 ks, const char* filename){
    KS2Iterator it = begin2(ks, filename);
    while(it.ptr.offset_next != -1) it = next2(it);
    return (KS2Iterator){.ptr = it.ptr, .filename = filename};
}

int comp2(KS2Iterator it1, KS2Iterator it2){
    if(it1.ptr.offset_key != it2.ptr.offset_key) return 1;
    if(it1.ptr.len_key != it2.ptr.len_key) return 1;
    if(compItem(it1.ptr.item, it2.ptr.item) != 0)  return 1;
    if(it1.ptr.release != it2.ptr.release) return 1;
//    if(it1.ptr.offset_next != it2.ptr.offset_next) return 1;
    return 0;
}

void edit2(KS2Iterator base, KS2Iterator it1, KS2Iterator it2, long int hashKey){
    KS2Iterator it = base, next = next2(it);
    FILE* fd = fopen(base.filename, "r+b");
    if(comp2(base, it1) == 0){
        fseek(fd, sizeof(long int) + hashKey*(10*sizeof(long int)), SEEK_SET);
        fwrite(&(it2.ptr.offset_key), sizeof(long int), 1, fd);
        fwrite(&(it2.ptr.len_key), sizeof(long int), 1, fd);
        saveItem(fd, it2.ptr.item);
        fwrite(&(it2.ptr.release), sizeof(long int), 1, fd);
        fwrite(&(it2.ptr.offset_next), sizeof(long int), 1, fd);
    } else {
        while (comp2(next, NULL_ITERATOR2) != 0 && comp2(next, it1) != 0) {
            it = next;
            next = next2(it);
        }
        fseek(fd, it.ptr.offset_next, SEEK_SET);
        fwrite(&(it2.ptr.offset_key), sizeof(long int), 1, fd);
        fwrite(&(it2.ptr.len_key), sizeof(long int), 1, fd);
        saveItem(fd, it2.ptr.item);
        fwrite(&(it2.ptr.release), sizeof(long int), 1, fd);
        fwrite(&(it2.ptr.offset_next), sizeof(long int), 1, fd);
    }
    fclose(fd);
}

