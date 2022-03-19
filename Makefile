all: model view controller main
	cc -o lab3a build/*.o -std=c11 -lreadline -g

model: ItemTable.o KeySpace1.o KeySpace2.o

ItemTable.o:
	cc -o build/ItemTable.o -c modal/ItemTable/ItemTable.c -std=c11 -g

KeySpace1.o:
	cc -o build/KeySpace1.o -c modal/KeySpace1.c -std=c11 -g

KeySpace2.o:
	cc -o build/KeySpace2.o -c modal/KeySpace2.c -std=c11 -g

view:
	echo ""

controller:
	echo ""

main:
	cc -o build/main.o -c main.c -std=c11 -g
