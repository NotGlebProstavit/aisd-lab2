#include "stdio.h"
#include "../modal/Table/Table.h"

#ifndef LAB3_MENU_H
#define LAB3_MENU_H

// Menu function
void printMainMenu();
void printFindMenu();
void printAddMenu();
void printDeleteMenu();
void printErrorMessage();
void printTable(const Table*);
void printItem(Item, const char*);
void printLittleTable(LittleTable*, Table*);
#endif //LAB3_MENU_H
