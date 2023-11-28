all: exec

run: exec
	./exec

exec: src/main.c src/aplicacao.c 
	gcc -Wall -g src/main.c src/aplicacao.c -o exec

clean: 
	rm exec 

gdb: exec
	gdb exec

valgrind: exec
	valgrind --leak-check=full --show-leak-kinds=all ./exec