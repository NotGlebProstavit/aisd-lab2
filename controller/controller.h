#include "../modal/Table/Table.h"
#include "../view/menu.h"
#include "readline/readline.h"


#ifndef LAB3_CONTROLLER_H
#define LAB3_CONTROLLER_H

int getInt();

void menu();
Table* create();
void addToTable(Table*);
void deleteFromTable(Table*, int);
void findInTable(Table*, int);

#endif //LAB3_CONTROLLER_H
