main_program: main.o gen_dun.o
	gcc main.o gen_dun.o -o main_program -lncurses

main.o: main.c main.h gen_dun.h
	gcc -Wall -Werror -ggdb main.c -c 

gen_dun.o: gen_dun.c gen_dun.h
	gcc -Wall -Werror -ggdb gen_dun.c -c

clean:
	rm *.o main_program