#include "KeySpace1.h"
#include "KeySpace2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H

typedef struct LittleTable{
    Item item;
    struct LittleTable* next;
} LittleTable;

typedef struct Table{
    KeySpace1* ks1;
    char* fn_ks1;
    KeySpace2* ks2;
    int size;
    char* fn_ks2;
    char* fn_data;
} Table;

//Hash function
int hash(const char*, int);

// Find function
Item findByComposeKey(const Table*, const char*, const char*);
LittleTable* findByKey1(const Table*, const char*); // Copy table (with iterator)
LittleTable* findByKey2(const Table*, const char*); // Copy table (with iterator)
LittleTable* findByManyKey1(const Table*, const char**, int); // Copy table (will call Iterator)
LittleTable* findByReleaseKey2(const Table*, const char*, int); // Copy table (will call Iterator)

// Create table
Table* createTable(const char*, const char*, const char*, int);
Table* downloadTable(const char*, const char*, const char*);

//Save table
void saveTable(Table*);

// Add into table
void add(Table*, const char*, const char*, const char*);

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
