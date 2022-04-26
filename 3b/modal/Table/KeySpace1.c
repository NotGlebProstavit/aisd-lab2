#include "KeySpace1.h"

KS1Iterator begin1(KeySpace1 ks, const char *filename) {
    return (KS1Iterator) {ks, filename};
}

KS1Iterator next1(KS1Iterator it) {
    if (it.ptr.offset_next == -1) {
        return NULL_ITERATOR1;
    }
    FILE *fd = fopen(it.filename, "rb");
    fseek(fd, it.ptr.offset_next, SEEK_SET);

    fread(&(it.ptr.offset_key), sizeof(long int), 1, fd);
    fread(&(it.ptr.len_key), sizeof(long int), 1, fd);
    loadItem(fd, &(it.ptr.item));
    fread(&(it.ptr.offset_next), sizeof(long int), 1, fd);

    fclose(fd);
    return it;
}

Item value1(KS1Iterator it) {
    return it.ptr.item;
}

KS1Iterator end1(KeySpace1 ks, const char *filename) {
    KS1Iterator it = begin1(ks, filename);
    while (it.ptr.offset_next != -1) it = next1(it);
    return (KS1Iterator) {.ptr = it.ptr, .filename = filename};
}

int comp1(KS1Iterator it1, KS1Iterator it2) {
    if(it1.ptr.offset_key != it2.ptr.offset_key) return 1;
    if(it1.ptr.len_key != it2.ptr.len_key) return 1;
    if(compItem(value1(it1), value1(it2)) != 0) return 1;
//    if(it1.ptr.offset_next != it2.ptr.offset_next) return 1;
    return 0;
}

void edit1(KS1Iterator base, KS1Iterator it1, KS1Iterator it2) {
    KS1Iterator it = base, next = next1(it);

    if(comp1(base, it1) == 0){
        FILE* fd = fopen(base.filename, "r+b");
        fwrite(&(it2.ptr.offset_key), sizeof(long int), 1, fd);
        fwrite(&(it2.ptr.len_key), sizeof(long int), 1, fd);
        saveItem(fd, it2.ptr.item);
        fwrite(&(it2.ptr.offset_next), sizeof(long int), 1, fd);

        fclose(fd);
        return;
    }

    while(comp1(next, NULL_ITERATOR1) != 0 && comp1(next, it1) != 0){
        it = next;
        next = next1(it);
    }
    FILE* fd = fopen(base.filename, "r+b");
    fseek(fd, it.ptr.offset_next, SEEK_SET);

    fwrite(&(it2.ptr.offset_key), sizeof(long int), 1, fd);
    fwrite(&(it2.ptr.len_key), sizeof(long int), 1, fd);
    saveItem(fd, it2.ptr.item);
    fwrite(&(it2.ptr.offset_next), sizeof(long int), 1, fd);

    fclose(fd);
}