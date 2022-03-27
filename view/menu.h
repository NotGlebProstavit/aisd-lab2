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
void printItem(const Item*);
void printKS1(const KeySpace1*);
void printKS2(const KeySpace2*);
#endif //LAB3_MENU_H
