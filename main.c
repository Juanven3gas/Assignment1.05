#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
   printf("Practicing Ncurses\n");
   
   WINDOW *win;
   initscr();
   noecho();
   curs_set(FALSE);

   sleep(1);

   endwin();
   return 0;
}