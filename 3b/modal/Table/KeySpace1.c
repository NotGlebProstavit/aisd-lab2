#include "KeySpace1.h"

KS1Iterator begin1(KeySpace1* ks, const char* filename){
    return (KS1Iterator){ks, filename};
}

KS1Iterator next1(KS1Iterator it){
    if(it.ptr->offset_next == -1){
        return (KS1Iterator){NULL, NULL};
    }
    FILE* fd = fopen(it.filename, "r+b");
    fseek(fd, it.ptr->offset_next, SEEK_SET);
    fread(it.ptr, sizeof(KeySpace1), 1, fd);
    fclose(fd);
    return it;
}

Item value1(KS1Iterator it){
    return it.ptr->item;
}

KS1Iterator end1(KeySpace1* ks, const char* filename){
    KS1Iterator it = begin1(ks, filename);
    while(it.ptr->offset_next != -1) it = next1(it);
    return (KS1Iterator){.ptr = it.ptr, .filename = filename};
}

int comp1(KS1Iterator it1, KS1Iterator it2){
    if(it1.ptr->offset_key != it2.ptr->offset_key) return 1;
    if(it1.ptr->len_key != it2.ptr->len_key) return 1;
    return 0;
}

void edit1(KS1Iterator base, KS1Iterator it1, KS1Iterator it2){
    KS1Iterator it = base, next = next1(it);
    while(comp1(next, it1) != 0){
        it = next;
        next = next1(it);
    }
    FILE* fd = fopen(base.filename, "w+b");
    fseek(fd, it.ptr->offset_next, SEEK_SET);
    fwrite(it2.ptr, sizeof(KeySpace1), 1, fd);
}