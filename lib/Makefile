CC := g++ -O1 -Wno-pointer-arith
SRCSIMP := simplemain.cpp SimpleList.cpp
DIR := ~/code/HashTable/lib
SRC := ~/code/HashTable/main.cpp ~/code/HashTable/hashtable.cpp ~/code/HashTable/hashfunc.cpp ~/code/HashTable/include/SimpleList.cpp ~/code/HashTable/include/text-sort.cpp

.PHONY: all clean

main: $(SRC)
	$(CC) $^ -o $(DIR)/$@ -fsanitize=address

simplelist: $(SRCSIMP)
	$(CC) $^ -o $(DIR)/$@
