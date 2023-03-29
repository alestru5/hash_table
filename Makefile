table:
	gcc -w -c -g input.c
	gcc -w -c -g menu.c
	gcc -w -c main.c
	gcc -c table.c
	ar cr libtable.a table.o
	gcc -w main.o input.o menu.o -o a.out -L. -ltable
	valgrind ./a.out
clean:
	rm *.o
	rm *.a
	rm a.out
