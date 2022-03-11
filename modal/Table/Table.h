#include "../KeySpace1/KeySpace1.h"
#include "../KeySpace2/KeySpace2.h"
#include "../ItemTable/ItemTable.h"

#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H
typedef struct Table{
    KeySpace1* keySpace1; // Pointer to KeySpace1 (list)

    KeySpace2** keySpace2; // Pointer to KeySpace2 (array)
    int msize2; // Max size of array of item in KeySpace2
} Table;

int hash(const char*, int);
void* addItemToTable(Table*, ItemTable*);

#endif //LAB3_TABLE_H
