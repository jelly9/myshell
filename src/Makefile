INCLUDE=../include 
BIN=myshell
SRC=main.c parser.c
OBJ=$(shell echo $(SRC) |sed s/\.c/\.o/g)
FLAGS=-wall -g
CC=gcc

$(BIN):$(OBJ)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $< -o $@ -I$(INCLUDE)

.PHONY:clean
clean:
	rm $(OBJ) $(BIN)

.PHONY:debug
debug:
	echo $(ROOT)
	echo $(LIB)
	echo $(INCLUDE)
