SOURCESMODAL = Table_create.c Table_add.c Table_delete.c Table_find.c Table_output.c
OBJECTSMODAL = Table_create.o Table_add.o Table_delete.o Table_find.o Table_output.o

all: build Table_create.o Table_add.o Table_delete.o Table_find.o Table_output.o menu.o controller.o item.o main
	cc -o lab3a build/*.o -std=c11 -lreadline -g

build:
	mkdir build

controller.o:
	cc -o build/controller.o -c controller/controller.c -std=c11 -g

menu.o:
	cc -o build/menu.o -c view/menu.c -std=c11 -g

Table_create.o Table_add.o Table_delete.o Table_find.o Table_output.o:
	cc -o build/$@ -c modal/Table/$(@:.o=.c) -std=c11 -g

item.o:
	cc -o build/item.o -c modal/Item/Item.c -std=c11 -g

main:
	cc -o build/main.o -c main.c -std=c11 -g

clean:
	rm -rf build lab3a
