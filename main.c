#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "gen_dun.h"
#include "distances.h"
#include "priority_queue.h"

void print_dungeon(WINDOW *win);
void move_PC(int whichDir);

char lastPosition = '.';

int main(int argc, char* argv[])
{
   int num_monsters = 0;
   //Check the argumens
   //and handle user inputs
   if(argc < 3)
   {
       printf("Insufficient arguements\n");
       return -1;
   }

   int arg_count = 1;
   while(arg_count < argc)
   {
       if(strcmp(argv[arg_count],  "--nummon") == 0)
       {
           arg_count++;
           num_monsters = atoi(argv[arg_count]);
           if(num_monsters <= 0)
           {
               printf("Incorrect argument passed\n");
               return -1;
           }

           //printf("Setting dungeon up for %d monsters\n", num_monsters);
           arg_count++;
       }
       else 
       {
           printf("incorrect argument detected: %s\n", argv[arg_count]);
           return -1;
       }
   }

   
   gen_dun();
   monster_t monsters[num_monsters];
   createMonsters(monsters, num_monsters);
   placeMonsters(monsters, num_monsters);

   WINDOW *win;
   initscr();
   noecho();
   //curs_set(FALSE);
   win = newwin(END_Y, END_X, 1, 0);
   
   
   while(1)
   {
      wclear(win);
      print_dungeon(win);
      int ch = getch();
      //wprintw(win, "%c\n", ch);
      if(ch == 'Q' || ch == 'q')
      {
         break;
      }
      else if(ch == 'y' || ch == 7)
      {
         //Move the character to the upper left
         move_PC(7);
      }
      else if(ch == 'k' || ch == 8)
      {
         //Move the character to the up
         move_PC(8);
      }
      else if(ch == 'u' || ch == 9)
      {
         //Move the character to the upper right
         move_PC(9);
      }
      else if(ch == 'l' || ch == 6)
      {
         //Move the character to the right
         move_PC(6);
      }
      else if(ch == 'n' || ch == 3)
      {
         //Move the character lower right
         move_PC(3);
      }
      else if(ch == 'j' || ch == 2)
      {
         //Move the character down
         move_PC(2);
      }
      else if(ch == 'b' || ch == 1)
      {
         //Move the character to the lower left
         move_PC(1);
      }
      else if(ch == 'h' || ch == 4)
      {
         //Move the character to the left
         move_PC(4);
      }
      else if(ch == ' ' || ch == 5)
      {
         //Don't move the character but move the monsters
      }
      else if(ch == '<')
      {
          if(lastPosition == '<')
          {
              wclear(win);
              gen_dun();
              createMonsters(monsters, num_monsters);
              placeMonsters(monsters, num_monsters);
              lastPosition = '.';
              print_dungeon(win);
          }
      }
      else if(ch == '>')
      {
          if(lastPosition == '>')
          {
            wclear(win);
            gen_dun();
            createMonsters(monsters, num_monsters);
            placeMonsters(monsters, num_monsters);
            lastPosition = '.';
            print_dungeon(win);
          }
      }

      //sleep(1);
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

void move_PC(int whichDir)
{
   if(whichDir == 7)
   {
      if(dungeon[pc_x_position-1][pc_y_position-1] != ' ')
      {
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position - 1][pc_y_position - 1];
         dungeon[pc_x_position - 1][pc_y_position - 1] = '@';
         pc_x_position = pc_x_position - 1;
         pc_y_position = pc_y_position - 1;
      }

   }
   else if(whichDir == 8)
   {
      
      if(dungeon[pc_x_position-1][pc_y_position] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position - 1][pc_y_position];
         dungeon[pc_x_position - 1][pc_y_position] = '@';
         pc_x_position = pc_x_position - 1;
      }

   }
   else if(whichDir == 9)
   {
      
      if(dungeon[pc_x_position-1][pc_y_position+1] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position - 1][pc_y_position + 1];
         dungeon[pc_x_position - 1][pc_y_position + 1] = '@';
         pc_x_position = pc_x_position - 1;
         pc_y_position = pc_y_position + 1;
      }
   }
   else if (whichDir == 6)
   {
      
      if(dungeon[pc_x_position][pc_y_position+1] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position][pc_y_position + 1];
         dungeon[pc_x_position][pc_y_position + 1] = '@';
         pc_y_position = pc_y_position + 1;
      }
   }
   else if(whichDir == 3)
   {
      
      if(dungeon[pc_x_position+1][pc_y_position+1] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position + 1][pc_y_position + 1];
         dungeon[pc_x_position + 1][pc_y_position + 1] = '@';
         pc_x_position = pc_x_position + 1;
         pc_y_position = pc_y_position + 1;
      }
   }
   else if(whichDir == 2)
   {
      
      if(dungeon[pc_x_position+1][pc_y_position] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position + 1][pc_y_position];
         dungeon[pc_x_position + 1][pc_y_position] = '@';
         pc_x_position = pc_x_position + 1;
      }
   }
   else if(whichDir == 1)
   {
      
      if(dungeon[pc_x_position+1][pc_y_position-1] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position + 1][pc_y_position - 1];
         dungeon[pc_x_position + 1][pc_y_position - 1] = '@';
         pc_x_position = pc_x_position + 1;
         pc_y_position = pc_y_position - 1;
      }
   }
   else if(whichDir == 4)
   {
      
      if(dungeon[pc_x_position][pc_y_position-1] != ' ')
      {
         
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position][pc_y_position - 1];
         dungeon[pc_x_position][pc_y_position - 1] = '@';
         pc_y_position = pc_y_position - 1;
      }
   }
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