all:
	gcc main.c rb.c avl.c set.c -std=c99 -Wall -o projeto

run:
	./projeto