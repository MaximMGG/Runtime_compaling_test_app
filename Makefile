MAIN = run

SRC = $(wildcard src/*.c)

all = comp

comp:
	gcc $(SRC) -o $(MAIN) -g
