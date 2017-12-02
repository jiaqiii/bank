
compiled : function.o main.o
	gcc -o compiled function.o main.o -lssl -lcrypto -L.
function.o : function.c
	gcc -std=c99 -pedantic-errors -Wall -c function.c -I.
main.o : main.c
	gcc -std=c99 -pedantic-errors -Wall -c main.c -I.

