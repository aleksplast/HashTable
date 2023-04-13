CC := g++ -Wno-pointer-arith
SRCSIMP := simplemain.cpp SimpleList.cpp
DIR := ~/code/HashTable/lib
SRC := main.cpp hashtable.cpp hashfunc.cpp ~/code/HashTable/include/SimpleList.cpp

.PHONY: all clean

main: $(SRC)
	$(CC) $^ -o $(DIR)/$@

simplelist: $(SRCSIMP)
	$(CC) $^ -o $(DIR)/$@
