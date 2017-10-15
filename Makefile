main_program: main.c
	gcc -Wall -Werror -lncurses main.c -o main_program

clean:
	rm *.o main_program