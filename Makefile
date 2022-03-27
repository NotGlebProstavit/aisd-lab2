MODEL = item create add delete find output

all: model view controller main
	cc -o lab3a build/*.o -std=c11 -lreadline -g

model: $(MODEL).o item.o

view: menu.o

controller: controller.o

controller.o:
	cc -o build/controller.o -c controller/controller.c -std=c11 -g

menu.o:
	cc -o build/menu.o -c view/menu.c -std=c11 -g

$(MODEL).o:
	cc -o build/$(MODEL).o -c model/Table/$(MODEL).c -std=c11 -g

item.o:
	cc -o build/item.o -c model/Item/item.c -std=c11 -g

main:
	cc -o build/main.o -c main.c -std=c11 -g
