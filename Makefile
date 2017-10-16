main_program: main.o gen_dun.o distances.o priority_queue.o
	gcc main.o gen_dun.o distances.o priority_queue.o -o main_program -lncurses

main.o: main.c main.h gen_dun.h distances.h priority_queue.h
	gcc -Wall -Werror -ggdb main.c -c 

gen_dun.o: gen_dun.c gen_dun.h
	gcc -Wall -Werror -ggdb gen_dun.c -c

distances.o: distances.c distances.h gen_dun.h
	gcc -Wall -Werror -ggdb distances.c -c

priority_queue.o: priority_queue.c priority_queue.h
	gcc -Wall -Werror -ggdb priority_queue.c -c

clean:
	rm *.o main_program