MAIN = a.out


SRC = $(wildcard src/*.c)

all = comp

comp:
	gcc $(SRC) -o $(MAIN) -g
