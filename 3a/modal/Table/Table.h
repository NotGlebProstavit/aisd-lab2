#include "KeySpace1.h"
#include "KeySpace2.h"
#include "../Item/Item.h"

#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H
typedef struct Table{
    KeySpace1* keySpace1; // Pointer to KeySpace1 (list)
    KeySpace2* keySpace2; // Pointer to KeySpace2 (array)
    int size2; // Size of KeySpace2
} Table;

//Hash function
int hash(const char*, int);

// Find function
Item* findByComposeKey(const Table*, const char*, const char*);
KeySpace1* findByKey1(const Table*, const char*); // Copy table (with iterator)
KeySpace2* findByKey2(const Table*, const char*); // Copy table (with iterator)
KeySpace1* findByManyKey1(const Table*, const char**, int); // Copy table (will call Iterator)
KeySpace2* findByReleaseKey2(const Table*, const char*, int); // Copy table (will call Iterator)

// Create table
Table* createTable(int);

// Add into table
void add(Table*, Item*); // Second param - source item of table

// Delete function
void deleteByComposeKey(Table*, const char*, const char*);
void deleteByKey1(Table*, const char*);
void deleteByKey2(Table*, const char*, int);
void refreshTable(Table*);

// Output function
char* tableToString(const Table*);

// Clear table
void freeTable(Table*);

#endif //LAB3_TABLE_H
