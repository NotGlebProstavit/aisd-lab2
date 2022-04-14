#include "controller.h"

int getInt(){
    char* msg = "";
    while(1){
        printf("%s", msg);
        char* input = readline("");
        msg = "======[Must be number!]======\n--> ";
        char* ptr;
        int value = (int) strtol(input, &ptr, 10);
        if(strlen(input) != 0 && ptr == input + strlen(input)) {
            free(input);
            return value;
        }
        free(input);
    }
}

void menu() {
    Table *table = create();
    while (1) {
        printMainMenu();
        int n = getInt();
        switch (n) {
            case 0: {
                freeTable(table);
                free(table);
                return;
            }
            case 1: {
                printAddMenu();
                n = getInt();
                if (n == 1) addToTable(table);
                else if (n != 0) printErrorMessage();
                break;
            }
            case 2: {
                printDeleteMenu();
                n = getInt();
                deleteFromTable(table, n);
                break;
            }
            case 3: {
                printFindMenu();
                n = getInt();
                findInTable(table, n);
                break;
            }
            case 4:{
                printTable(table);
                break;
            }
            default: {
                printErrorMessage();
                break;
            }
        }
    }
}

Table *create() {
    printf("Enter size of the second key space:\n");
    printf("--> ");
    char* msg = "";
    int size;
    while(1){
	printf("%s", msg);
	size = getInt();
	msg = "======[Size cannot be zero]======\n--> ";
	if(size != 0) break;
    }
    Table *table = createTable(size);
    return table;
}

void addToTable(Table *table) {
    char* msg = "";
    printf("Enter:\n");
    printf(" Data --> ");
    char *data;
    while(1){
	printf("%s", msg);
	data = readline("");
	msg = "======[Data cannot be empty]======\n Data--> ";
	if(strlen(data) != 0) break;
	free(data);
    }
    msg = "";
    printf(" Key1 --> ");
    char *key1;
    while(1){
        printf("%s", msg);
        key1 = readline("");
        msg = "======[Key cannot be empty]======\n Key1--> ";
        if(strlen(key1) != 0) break;
        free(key1);
    }
    msg = "";
    printf(" Key2 --> ");
    char *key2;
    while(1){
        printf("%s", msg);
        key2 = readline("");
        msg = "======[Key cannot be empty]======\n Key2--> ";
        if(strlen(key2) != 0) break;
        free(key2);
    }
    KeySpace1* ks = findByKey1(table, key1);
    if(ks != NULL){
        free(data);
        free(key1);
        free(key2);
        free(ks->key);
        freeItem(ks->data);
        free(ks->data);
        free(ks);
        printf("======[The first key must be unique!]======\n");
        return;
    }
    Item *item = createItem(data, key1, key2);
    free(data);
    free(key1);
    free(key2);
    add(table, item);
}

void deleteFromTable(Table *table, int mod) {
    switch (mod) {
        case 0:
            break;
        case 1: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1, *msg = "";
            while(1){
                printf("%s", msg);
                key1 = readline("");
                msg = "======[Key cannot be empty]======\n Key1--> ";
                if(strlen(key1) != 0) break;
                free(key1);
            }
            printf(" Key2 --> ");
            char *key2; msg = "";
            while(1){
                printf("%s", msg);
                key2 = readline("");
                msg = "======[Key cannot be empty]======\n Key2--> ";
                if(strlen(key2) != 0) break;
                free(key2);
            }
            deleteByComposeKey(table, key1, key2);
            free(key1);
            free(key2);
            break;
        }
        case 2: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1, *msg = "";
            while(1){
                printf("%s", msg);
                key1 = readline("");
                msg = "======[Key cannot be empty]======\n Key1--> ";
                if(strlen(key1) != 0) break;
                free(key1);
            }
            deleteByKey1(table, key1);
            free(key1);
            break;
        }
        case 3: {
            printf("Enter:\n");
            printf(" Key2 --> ");
            char *key2, *msg = "";
            while(1){
                printf("%s", msg);
                key2 = readline("");
                msg = "======[Key cannot be empty]======\n Key2--> ";
                if(strlen(key2) != 0) break;
                free(key2);
            }
            deleteByKey2(table, key2, -1);
            free(key2);
            break;
        }
        case 4: {
            printf("Enter:\n");
            printf(" Key2 --> ");
            char *key2 = readline("");
            printf(" Release --> ");
            int release = getInt();
            deleteByKey2(table, key2, release);
            free(key2);
            break;
        }
        case 5: {
            refreshTable(table);
            break;
        }
        default:
            printErrorMessage();
            break;
    }
}

void findInTable(Table *table, int mod) {
    switch (mod) {
        case 0:
            break;
        case 1: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1 = readline("");
            printf(" Key2 --> ");
            char *key2 = readline("");
            Item *item = findByComposeKey(table, key1, key2);
            printItem(item);
            free(key1);
            free(key2);
            break;
        }
        case 2: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1 = readline("");
            KeySpace1 *ks = findByKey1(table, key1);
            printKS1(ks);
            if(ks != NULL) {
		free(ks->key);
                freeItem(ks->data);
                free(ks->data);
                free(ks);
            }
            free(key1);
            break;
        }
        case 3: {
            printf("Enter:\n");
            printf(" Key2 --> ");
            char *key2 = readline("");
            KeySpace2 *ks = findByKey2(table, key2);
            printKS2(ks);
            while (ks != NULL) {
                KeySpace2 *t = ks;
                ks = ks->next;
                free(t->key);
                freeItem(t->data);
                free(t->data);
                free(t);
            }
            free(key2);
            break;
        }
        case 4: {
            printf("How many keys dou you want enter from the first key space?\n");
            int n = getInt();
            char **keys = (char **) malloc(n * sizeof(char *));
            for (int i = 0; i < n; i++) {
                keys[i] = readline("--> ");
            }
            KeySpace1 *ks = findByManyKey1(table, (const char **) keys, n);
            printKS1(ks);
            for(int i = 0; i < n; i++){
                free(keys[i]);
                KeySpace1 *t = ks;
                if(ks != NULL){
                    ks = ks->next;
                    free(t->key);
                    freeItem(t->data);
		    free(t->data);
                    free(t);
                }
            }
            free(keys);
            break;
        }
        case 5: {
            printf("Enter:\n");
            printf(" Key2 --> ");
            char *key2 = readline("");
            printf(" Release --> ");
            int release = getInt();
            KeySpace2 *ks = findByReleaseKey2(table, key2, release);
            printKS2(ks);
            if(ks != NULL) {
                free(ks->key);
                freeItem(ks->data);
                free(ks->data);
                free(ks);
            }
            free(key2);
            break;
        }
        default:
            printErrorMessage();
            break;
    }
}
