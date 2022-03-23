all: model main
	cc -o lab3a build/*.o -std=c11 -lreadline -g

model: item.o create.o add.o delete.o find.o output.o

item.o:
	cc -o build/item.o -c modal/Item/Item.c -std=c11 -g

create.o:
	cc -o buld/create.o -c modal/Table/Table_create.c -std=c11 -g

add.o:
	cc -o buld/add.o -c modal/Table/Table_add.c -std=c11 -g

delete.o:
	cc -o buld/delete.o -c modal/Table/Table_delete.c -std=c11 -g

find.o:
	cc -o buld/find.o -c modal/Table/Table_find.c -std=c11 -g

output.o:
	cc -o buld/output.o -c modal/Table/Table_output.c -std=c11 -g

main:
	cc -o build/main.o -c main.c -std=c11 -g
