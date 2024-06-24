CC=gcc 
FLAGS=-Wall -Wextra -Werror
LIBS=-lncurses

all: pong pong_ineractive pong_cringe

pong: pong.c
	$(CC) $(FLAGS) pong.c -o pong

pong_interactive: pong_interactive.c
	$(CC) $(FLAGS) $(LIBS) pong_interactive.c -o pong_interactive

pong_cringe: pong_cringe.c
	$(CC) $(FLAGS) $(LIBS) pong_cringe.c -o pong_cringe

run_pong: pong
	./pong

run_pong_interactive: pong_interactive
	./pong_interactive

run_pong_cringe: pong_cringe
	./pong_cringe

celan:
	rm -rf pong
	rm -rf pong_interactive
	rm -rf pong_cringe
