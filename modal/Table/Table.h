#include "../KeySpace1/KeySpace1.h"
#include "../KeySpace2/KeySpace2.h"
#include "../ItemTable/ItemTable.h"

#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H
typedef struct Table{
    KeySpace1* keySpace1; // Pointer to KeySpace1 (list)
    KeySpace2* keySpace2; // Pointer to KeySpace2 (array)
    int size2; // Size of KeySpace2
} Table;

int hash(const char*, int);

Table* addItemToTable(Table*, ItemTable*);
ItemTable* findItemByKeys(const Table*, const char*, const char*);
void deleteByKeys(Table*, const char*, const char*);
Table* findItemByKey(Table*, const char*, int);
void deleteByKey(Table*, const char*, int);
void outputTable(const Table*);

#endif //LAB3_TABLE_H
