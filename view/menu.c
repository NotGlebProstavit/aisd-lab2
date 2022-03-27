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

void printItem(const Item* i){
    if(i != NULL) {
        char *s = itemToString(i);
        printf("%s\n", s);
        free(s);
    } else {
        printf("======[Element with this key doesn't exist]======\n");
    }
}

void printKS1(const KeySpace1* ks){
    if(ks == NULL){
        printf("======[The first key space if empty]=======\n");
        return;
    }
    while(ks != NULL){
        printItem(ks->data);
        ks = ks->next;
    }
}

void printKS2(const KeySpace2* ks){
    if(ks == NULL){
        printf("======[The second key space if empty]=======\n");
        return;
    }
    while(ks != NULL){
        printf("%d | ", ks->release);
        printItem(ks->data);
        ks = ks->next;
    }
}