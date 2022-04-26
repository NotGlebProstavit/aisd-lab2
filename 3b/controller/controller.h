#include "../modal/Table/Table.h"
#include "../view/menu.h"
#include "readline/readline.h"


#ifndef LAB3_CONTROLLER_H
#define LAB3_CONTROLLER_H

int getInt();
int validFilename(const char*);

void menu();
Table* create();
Table* reload();
void addToTable(Table*);
void deleteFromTable(Table**, int);
void findInTable(Table*, int);

#endif //LAB3_CONTROLLER_H
