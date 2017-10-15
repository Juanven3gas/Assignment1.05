#include <ncurses.h>
#include <unistd.h>
#include "main.h"
#include "gen_dun.h"

void print_dungeon(WINDOW *win);

int main(int argc, char* argv[])
{
   gen_dun();
   WINDOW *win;
   initscr();
   noecho();
   curs_set(FALSE);
   win = newwin(END_Y, END_X, 0, 0);

   while(1)
   {

      wclear(win);
      print_dungeon(win);
      sleep(1);
   
      //clear the screen
      //wclear(win);
      //clear();
      
      //print_dungeon(win);

      //mvwprintw(win, y, x, "o");
      //wrefresh(win);
      //mvprintw(y, x, "o");
      //refresh();

      //usleep(DELAY);
      //x++;
   }
   
   endwin();
   return 0;
}

void print_dungeon(WINDOW *win)
{
   int i, j;
   for(i = 0; i < DUNGEON_ROWS; i++)
   {
      for(j = 0; j < DUNGEON_COLUMNS; j++)
      {
         wprintw(win, "%c", dungeon[i][j]);
      }
      wprintw(win, "\n");
   }

   wrefresh(win);
}