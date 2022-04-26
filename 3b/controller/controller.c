#include "controller.h"

int getInt() {
    char *msg = "";
    while (1) {
        printf("%s", msg);
        char *input = readline("");
        msg = "======[Must be number!]======\n--> ";
        char *ptr;
        int value = (int) strtol(input, &ptr, 10);
        if (strlen(input) != 0 && ptr == input + strlen(input)) {
            free(input);
            return value;
        }
        free(input);
    }
}

int validFilename(const char* fn){
    FILE* fd = fopen(fn, "r+b");
    if(fd == NULL) return 1;
    fclose(fd);
    return 0;
}


void menu() {
    printf("Do you want:\n");
    printf("  1) Reload old table\n");
    printf("  2) Create new table\n");
    printf("--> ");
    Table *table;
    while (1) {
        int n = getInt();
        if (n == 1) {
            table = reload();
            break;
        } else if (n == 2) {
            table = create();
            break;
        } else printf("This point doesn't exist\n--> ");
    }

    while (1) {
        printMainMenu();
        int n = getInt();
        switch (n) {
            case 0: {
                saveTable(table);
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
                deleteFromTable(&table, n);
                break;
            }
            case 3: {
                printFindMenu();
                n = getInt();
                findInTable(table, n);
                break;
            }
            case 4: {
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
    char *msg = "";
    char *fn_data, *fn_ks1, *fn_ks2;
    printf("Enter name of file for data:\n");
    printf("--> ");
    while (1) {
        printf("%s", msg);
        fn_data = readline("");
        msg = "======[This file doesn't exist]======\n--> ";
        if (validFilename(fn_data) == 0) break;
        else free(fn_data);
    }
    msg = "";
    printf("Enter name of file for KeySpace1:\n");
    printf("--> ");
    while (1) {
        printf("%s", msg);
        fn_ks1 = readline("");
        msg = "======[This file doesn't exist]======\n--> ";
        if (validFilename(fn_ks1) == 0) break;
        else free(fn_ks1);
    }
    msg = "";
    printf("Enter name of file for KeySpace2:\n");
    printf("--> ");
    while (1) {
        printf("%s", msg);
        fn_ks2 = readline("");
        msg = "======[This file doesn't exist]======\n--> ";
        if (validFilename(fn_ks2) == 0) break;
        else free(fn_ks2);
    }
    msg = "";
    printf("Enter size of the second key space:\n");
    printf("--> ");
    int size;
    while (1) {
        printf("%s", msg);
        size = getInt();
        msg = "======[Size cannot be zero]======\n--> ";
        if (size != 0) break;
    }
    Table *table = createTable(fn_ks1, fn_ks2, fn_data, size);
    free(fn_data);
    free(fn_ks1);
    free(fn_ks2);
    return table;
}


Table *reload() {
    char *msg = "";
    char *fn_data, *fn_ks1, *fn_ks2;
    printf("Enter name of file for data:\n");
    printf("--> ");
    while (1) {
        printf("%s", msg);
        fn_data = readline("");
        msg = "======[This file doesn't exist]======\n--> ";
        if (validFilename(fn_data) == 0){
            FILE* fd = fopen(fn_data, "r+w");
            long int t1 = ftell(fd);
            fseek(fd, 0L, SEEK_END);
            long int t2 = ftell(fd);
            fclose(fd);
            if(t2 - t1 != 0) break;
            msg = "======[This file is empty]======";
        } else free(fn_data);
    }
    msg = "";
    printf("Enter name of file for KeySpace1:\n");
    printf("--> ");
    while (1) {
        printf("%s", msg);
        fn_ks1 = readline("");
        msg = "======[This file doesn't exist]======\n--> ";
        if (validFilename(fn_ks1) == 0){
            FILE* fd = fopen(fn_ks1, "r+w");
            long int t1 = ftell(fd);
            fseek(fd, 0L, SEEK_END);
            long int t2 = ftell(fd);
            fclose(fd);
            if(t2 - t1 != 0) break;
            msg = "======[This file is empty]======";
        } else free(fn_ks1);
    }
    msg = "";
    printf("Enter name of file for KeySpace2:\n");
    printf("--> ");
    while (1) {
        printf("%s", msg);
        fn_ks2 = readline("");
        msg = "======[This file doesn't exist]======\n--> ";
        if (validFilename(fn_ks2) == 0){
            FILE* fd = fopen(fn_ks2, "r+w");
            long int t1 = ftell(fd);
            fseek(fd, 0L, SEEK_END);
            long int t2 = ftell(fd);
            fclose(fd);
            if(t2 - t1 != 0) break;
            msg = "======[This file is empty]======";
        } else free(fn_ks2);
    }
    Table *table = downloadTable(fn_ks1, fn_ks2, fn_data);
    free(fn_data);
    free(fn_ks1);
    free(fn_ks2);
    return table;
}

void addToTable(Table *table) {
    char *msg = "";
    printf("Enter:\n");
    printf(" Data --> ");
    char *data;
    while (1) {
        printf("%s", msg);
        data = readline("");
        msg = "======[Data cannot be empty]======\n Data--> ";
        if (strlen(data) != 0) break;
        free(data);
    }
    msg = "";
    printf(" Key1 --> ");
    char *key1;
    while (1) {
        printf("%s", msg);
        key1 = readline("");
        msg = "======[Key cannot be empty]======\n Key1--> ";
        if (strlen(key1) != 0) break;
        free(key1);
    }
    msg = "";
    printf(" Key2 --> ");
    char *key2;
    while (1) {
        printf("%s", msg);
        key2 = readline("");
        msg = "======[Key cannot be empty]======\n Key2--> ";
        if (strlen(key2) != 0) break;
        free(key2);
    }
    LittleTable *ks = findByKey1(table, key1);
    if (ks != NULL) {
        free(data);
        free(key1);
        free(key2);
        free(ks);
        printf("======[The first key must be unique!]======\n");
        return;
    }
    add(table, key1, key2, data);
    free(data);
    free(key1);
    free(key2);
}

void deleteFromTable(Table **table, int mod) {
    switch (mod) {
        case 0:
            break;
        case 1: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1, *msg = "";
            while (1) {
                printf("%s", msg);
                key1 = readline("");
                msg = "======[Key cannot be empty]======\n Key1--> ";
                if (strlen(key1) != 0) break;
                free(key1);
            }
            printf(" Key2 --> ");
            char *key2;
            msg = "";
            while (1) {
                printf("%s", msg);
                key2 = readline("");
                msg = "======[Key cannot be empty]======\n Key2--> ";
                if (strlen(key2) != 0) break;
                free(key2);
            }
            deleteByComposeKey(table, key1, key2, NULL);
            free(key1);
            free(key2);
            break;
        }
        case 2: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1, *msg = "";
            while (1) {
                printf("%s", msg);
                key1 = readline("");
                msg = "======[Key cannot be empty]======\n Key1--> ";
                if (strlen(key1) != 0) break;
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
            while (1) {
                printf("%s", msg);
                key2 = readline("");
                msg = "======[Key cannot be empty]======\n Key2--> ";
                if (strlen(key2) != 0) break;
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
            Item item = findByComposeKey(table, key1, key2);
            printItem(item, table->fn_data);
            free(key1);
            free(key2);
            break;
        }
        case 2: {
            printf("Enter:\n");
            printf(" Key1 --> ");
            char *key1 = readline("");
            LittleTable *ks = findByKey1(table, key1);
            printLittleTable(ks, table);
            if (ks != NULL) {
                free(ks);
            }
            free(key1);
            break;
        }
        case 3: {
            printf("Enter:\n");
            printf(" Key2 --> ");
            char *key2 = readline("");
            LittleTable *ks = findByKey2(table, key2);
            printLittleTable(ks, table);
            while (ks != NULL) {
                LittleTable *t = ks;
                ks = ks->next;
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
            LittleTable *ks = findByManyKey1(table, (const char **) keys, n);
            printLittleTable(ks, table);
            for (int i = 0; i < n; i++) {
                free(keys[i]);
                LittleTable *t = ks;
                if (ks != NULL) {
                    ks = ks->next;
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
            LittleTable *ks = findByReleaseKey2(table, key2, release);
            printLittleTable(ks, table);
            if (ks != NULL) {
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
