#include "Table.h"

void saveTable(Table* table){
    FILE* fd = fopen(table->fn_ks2, "w+b");
    fwrite(&(table->size), sizeof(int), 1, fd);
    fwrite(table->ks2, sizeof(KeySpace2), table->size, fd);
    fclose(fd);
    fd = fopen(table->fn_ks1, "w+b");
    fwrite(table->ks1, sizeof(KeySpace1), 1, fd);
    fclose(fd);
}
