all: build KeySpace1.o KeySpace2.o Table_create.o Table_add.o Table_delete.o Table_find.o Table_output.o Table_save.o menu.o controller.o Item.o main
	cc -o lab3b build/*.o -std=c11 -lreadline -g

build:
	mkdir build

controller.o:
	cc -o build/controller.o -c controller/controller.c -std=c11 -g

menu.o:
	cc -o build/menu.o -c view/menu.c -std=c11 -g

KeySpace1.o KeySpace2.o Table_create.o Table_add.o Table_delete.o Table_find.o Table_output.o Table_save.o:
	cc -o build/$@ -c modal/Table/$(@:.o=.c) -std=c11 -g

Item.o:
	cc -o build/Item.o -c modal/Item/Item.c -std=c11 -g

main:
	cc -o build/main.o -c main.c -std=c11 -g

clean:
	rm -rf build lab3b
