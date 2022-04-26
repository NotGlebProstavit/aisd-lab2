#include "menu.h"

void printMainMenu(){
    printf("=======[WELCOME TO MAIN MENU]=======\n");
    printf("Enter number of following operations\n");
    printf("1) Add element into table\n");
    printf("2) Delete element from table\n");
    printf("3) Find element into table\n");
    printf("4) Print table\n");
    printf("0) End program\n");
    printf("--> ");
}

void printFindMenu(){
    printf("=======[WELCOME TO FIND MENU]=======\n");
    printf("Enter number of following points\n");
    printf("1) Find by the composition key\n");
    printf("2) Find by the key from the first key space\n");
    printf("3) Find by the key from the second key space\n");
    printf("4) Find by many keys from the first key space\n");
    printf("5) Find by the release key from the second key space\n");
    printf("0) Exit\n");
    printf("--> ");
}

void printAddMenu(){
    printf("=======[WELCOME TO ADD MENU]========\n");
    printf("  ========[!!!WARNING!!!]=========  \n");
    printf("  Table has 2 key spaces:\n");
    printf("  1)Keys in the first key space can't be repeated.\n");
    printf("    Every key is unique.\n\n");
    printf("  2)Keys in the second key space can be repeated.\n");
    printf("    Every key has own release.\n");
    printf("  ================================  \n");
    printf("1) Add element\n");
    printf("2) Exit\n");
    printf("--> ");
}

void printDeleteMenu(){
    printf("=======[WELCOME TO DELETE MENU]=======\n");
    printf("Enter number of following points\n");
    printf("1) Delete by the composition key\n");
    printf("2) Delete by the key from the first key space\n");
    printf("3) Delete by the key from the second key space\n");
    printf("4) Delete by the release key from the second key space\n");
    printf("5) Refreshing table\n");
    printf("0) Exit\n");
    printf("--> ");
}

void printErrorMessage(){
    printf("=======[This point doesn't exist]=======\n");
}

void printTable(const Table* t){
    if(t != NULL) {
        char *s = tableToString(t);
        if(s != NULL){
            printf("=======[Output table]=======\n");
            printf("%s\n", s);
            free(s);
        }
    } else {
        printf("=======[Table doesn't exist]======\n");
    }
}

void printItem(Item i, const char* fn_data){
    if(compItem(i, (Item){0,0,0,0,0,0})) {
        char *s = itemToString(fn_data, i);
        printf("%s\n", s);
        free(s);
    } else {
        printf("======[Element with this key doesn't exist]======\n");
    }
}

void printLittleTable(LittleTable* lt, Table* table){
    while(lt != NULL){
        if(lt->release != -1) printf("%ld | ", lt->release);
        printItem(lt->item, table->fn_data);
        lt = lt->next;
    }
}
