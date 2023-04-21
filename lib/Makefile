CC := gcc -O1 -mavx2 -Wno-pointer-arith
SRCSIMP := simplemain.cpp SimpleList.cpp
DIR := ~/code/HashTable/lib
SRC := ~/code/HashTable/main.cpp ~/code/HashTable/hashtable.cpp ~/code/HashTable/hashfunc.cpp ~/code/HashTable/include/SimpleList.cpp ~/code/HashTable/include/text-sort.cpp

.PHONY: all clean

main: main.o hashtable.o hashfunc.o hashfunc.o SimpleList.o text-sort.o MurMur.o
	gcc -no-pie $^ -o main

main.o: ~/code/HashTable/main.cpp
	$(CC) -c $^ -o $(DIR)/$@

hashtable.o: ~/code/HashTable/hashtable.cpp
	$(CC) -c $^ -o $(DIR)/$@

hashfunc.o: ~/code/HashTable/hashfunc.cpp
	$(CC) -c $^ -o $(DIR)/$@

SimpleList.o: ~/code/HashTable/include/SimpleList.cpp
	$(CC) -c $^ -o $(DIR)/$@

text-sort.o: ~/code/HashTable/include/text-sort.cpp
	$(CC) -c $^ -o $(DIR)/$@

MurMur.o : ~/code/HashTable/MurMur.asm
	sudo nasm -f elf64 -g $^ -o MurMur.o

simplelist: $(SRCSIMP)
	$(CC) $^ -o $(DIR)/$@

clear: *.o
	sudo rm -rf *.o
