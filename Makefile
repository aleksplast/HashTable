CC := g++ -Wno-pointer-arith
SRCSIMP := simplemain.cpp SimpleList.cpp
DIR := C:\Users\USER\Documents\HashTable
SRC := main.cpp hashtable.cpp ..\HashTable\List\simplelist.cpp

.PHONY: all clean

main: $(SRC)
	$(CC) $^ -o $(DIR)\$@

simplelist: $(SRCSIMP)
	$(CC) $^ -o $(DIR)\$@
