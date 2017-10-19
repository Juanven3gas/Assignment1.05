#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "main.h"
#include "gen_dun.h"
#include "distances.h"
#include "priority_queue.h"

void print_dungeon(WINDOW *win);
void print_message(WINDOW *win, int status);
void move_PC(int whichDir, monster_t *arr, int arr_size);
int check_for_monster(int x_pos, int y_pos, monster_t *arr, int arr_size);
int check_won_status(monster_t *arr, int arr_size);
int checkForPC(monster_t m);
int move_monster(queue_t *q, int turn);

char lastPosition = '.';

int main(int argc, char* argv[])
{
   int num_monsters = 0;
   int list_monster_state = 0;
   int arg_count = 1;
   int monster_index = 0;
   int win_status = 0;
   int PC_dead_status = 0;
   int turn = 0;

   //Check the argumens
   //and handle user inputs
   if(argc < 3)
   {
       printf("Insufficient arguements\n");
       return -1;
   }

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
   queue_t *pq = (queue_t *)malloc(sizeof(queue_t));
   queue_init(pq);
   for(int i = 0; i < num_monsters; i++)
   {
       queue_add(pq,monsters[i], (EVENT_CONSTANT/monsters[i].speed));
   }

   WINDOW *win;
   WINDOW *message_win;
   initscr();
   noecho();
   curs_set(FALSE);
   keypad(stdscr, TRUE);
   win = newwin(END_Y, END_X, 1, 0);
   message_win = newwin(1, END_X, 0, 0);
   
   while(1)
   {
    win_status = check_won_status(monsters, num_monsters);
      if(win_status)
      {
          break;
      }
      wclear(win);
      //wclear(message_win);
      
      print_dungeon(win);
      wrefresh(win);
      //wrefresh(message_win);
      int ch = getch();

      if((ch == 'Q' || ch == 'q'))
      {
        win_status = -1;
         break;
      }
      else if((ch == 'y' || ch == '7') && (!list_monster_state))
      {
         //Move the character to the upper left
         move_PC(7, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'k' || ch == '8') && (!list_monster_state))
      {
         //Move the character to the up
         move_PC(8, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'u' || ch == '9') && (!list_monster_state))
      {
         //Move the character to the upper right
         move_PC(9, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'l' || ch == '6') && (!list_monster_state))
      {
         //Move the character to the right
         move_PC(6, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'n' || ch == '3') && (!list_monster_state))
      {
         //Move the character lower right
         move_PC(3, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'j' || ch == '2') && (!list_monster_state))
      {
         //Move the character down
         move_PC(2, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'b' || ch == '1') && (!list_monster_state))
      {
         //Move the character to the lower left
         move_PC(1, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == 'h' || ch == '4') && (!list_monster_state))
      {
         //Move the character to the left
         move_PC(4, monsters, num_monsters);
         PC_dead_status = move_monster(pq, turn);
      }
      else if((ch == ' ' || ch == '5') && (!list_monster_state))
      {
         //Don't move the character but move the monsters
         PC_dead_status = move_monster(pq, turn);
      }
      else if(ch == '<' && (!list_monster_state))
      {
          if(lastPosition == '<')
          {
              wclear(win);
              wclear(message_win);
              gen_dun();
              queue_empty(pq);
              createMonsters(monsters, num_monsters);
              placeMonsters(monsters, num_monsters);
              for(int i = 0; i < num_monsters; i++)
              {
                  queue_add(pq,monsters[i], (EVENT_CONSTANT/monsters[i].speed));
              }
              lastPosition = '.';
              print_dungeon(win);
          }
      }
      else if(ch == '>' && (!list_monster_state))
      {
          if(lastPosition == '>')
          {
            wclear(message_win);
            wclear(win);
            gen_dun();
            createMonsters(monsters, num_monsters);
            placeMonsters(monsters, num_monsters);
            for(int i = 0; i < num_monsters; i++)
            {
                queue_add(pq,monsters[i], (EVENT_CONSTANT/monsters[i].speed));
            }
            lastPosition = '.';
            print_dungeon(win);
          }
      }
      else if(ch == 'm')
      {
          list_monster_state = 1;
          monster_index = 0;
          wclear(message_win);
          int monsterx_pos = monsters[monster_index].x_pos;
          int monstery_pos = monsters[monster_index].y_pos;
          int difference_in_x = monsters[monster_index].x_pos - pc_x_position;
          int difference_in_y = monsters[monster_index].y_pos - pc_y_position;

          if(difference_in_x > 0 && difference_in_y > 0)
          {
            wprintw(message_win, "monster %c, is %d south and %d right", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
          }
          else if(difference_in_x < 0 && difference_in_y > 0)
          {
            wprintw(message_win, "monster %c, is %d north and %d right", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
            
          }
          else if(difference_in_x > 0 && difference_in_y < 0)
          {
            wprintw(message_win, "monster %c, is %d south and %d left", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
            
          }
          else if (difference_in_x < 0 && difference_in_y < 0)
          {
            wprintw(message_win, "monster %c, is %d north and %d left", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));  
          }
          
          wrefresh(message_win);
      }
      else if(ch == 27)
      {
          list_monster_state = 0;
          monster_index = 0;
      }
      else if((ch == KEY_UP))
      {
          monster_index++;
          if(monster_index >= num_monsters)
          {
              monster_index = num_monsters - 1;
          }
          wclear(message_win);
          monster_t mon = monsters[monster_index];
          int monsterx_pos = mon.x_pos;
          int monstery_pos = mon.y_pos;
          int difference_in_x = mon.x_pos - pc_x_position;
          int difference_in_y = mon.y_pos - pc_y_position;

          if(difference_in_x > 0 && difference_in_y > 0)
          {
              wprintw(message_win, "monster %c, is %d south and %d right", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
          }
          else if(difference_in_x < 0 && difference_in_y > 0)
          {
            wprintw(message_win, "monster %c, is %d north and %d right", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
            
          }
          else if(difference_in_x > 0 && difference_in_y < 0)
          {
            wprintw(message_win, "monster %c, is %d south and %d left", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
            
          }
          else if (difference_in_x < 0 && difference_in_y < 0)
          {
            wprintw(message_win, "monster %c, is %d north and %d left", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));  
          }

          wrefresh(message_win);
      }
      else if((ch == KEY_DOWN))
      {
          monster_index--;
          if(monster_index < 0)
          {
              monster_index = 0;
          }

          wclear(message_win);
          int monsterx_pos = monsters[monster_index].x_pos;
          int monstery_pos = monsters[monster_index].y_pos;
          int difference_in_x = monsters[monster_index].x_pos - pc_x_position;
          int difference_in_y = monsters[monster_index].y_pos - pc_y_position;

          if(difference_in_x > 0 && difference_in_y > 0)
          {
              wprintw(message_win, "monster %c, is %d south and %d right", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
          }
          else if(difference_in_x < 0 && difference_in_y > 0)
          {
            wprintw(message_win, "monster %c, is %d north and %d right", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
            
          }
          else if(difference_in_x > 0 && difference_in_y < 0)
          {
            wprintw(message_win, "monster %c, is %d south and %d left", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));
            
          }
          else if (difference_in_x < 0 && difference_in_y < 0)
          {
            wprintw(message_win, "monster %c, is %d north and %d left", dungeon[monsterx_pos][monstery_pos], abs(difference_in_x), abs(difference_in_y));  
          }

          wrefresh(message_win);
      }

      if(PC_dead_status)
      {
          win_status = 0;
          break;
      }
      turn++;
   }
   
   endwin();
   if(win_status == 1)
   {
       printf("YOU WON!!\n");
   }
   else if(win_status == 0)
   {
       printf("YOU LOST! TRY AGAIN!!\n");
   }
   else 
   {
       printf("Exiting the game\n");
   }

   queue_delete(pq);
   free(pq);
   return 0;
}

int move_monster(queue_t *q, int turn)
{
    monster_t m;
    queue_remove(q, &m);
    if(m.alive)
    {   
        int pcFound =  checkForPC(m);
    
        if(pcFound)
        {
            return 1;
        }
    
        if(m.characteristics == 0x0)
        {
            //Look in the room to find the PC and move 1 cell closer
            int room_rows = rooms[m.room][0];
            int room_cols = rooms[m.room][1];
            int room_x = rooms[m.room][2];
            int room_y = rooms[m.room][3];
    
            int startX, startY;
            int pc_x = -1;
            int pc_y = -1;
            for(startX = 0; startX < (room_x + room_rows); startX++)
            {
                for(startY = 0; startY < (room_y + room_cols); startY++)
                {
                    if(dungeon[startX][startY] == '@')
                    {
                        pc_x = startX;
                        pc_y = startY;
                    }
                }
            }
    
            if(pc_x == -1 || pc_y == -1)
            {
                //PC was not in the room and dont move
                return 0;
            }
            else
            {
                dungeon[m.x_pos][m.y_pos] = '.';
    
                if(pc_x < m.x_pos)
                {
                    m.x_pos = m.x_pos - 1;
                }
                if(pc_x > m.x_pos)
                {
                    m.x_pos = m.x_pos + 1;
                }
                if(pc_y < m.y_pos)
                {
                    m.y_pos = m.y_pos - 1;
                }
                if(pc_y > m.y_pos)
                {
                    m.y_pos = m.y_pos + 1;
                }
    
                dungeon[m.x_pos][m.y_pos] = '0';
            }
    
        }
        else if (m.characteristics == 0x1)
        {
               
        }
        else if(m.characteristics == 0x2)
        {
            
        }
        else if(m.characteristics == 0x3)
        {
            //printf("Monster has a 0x3 charicteristic\n");
            int minX = 0;
            int minY = 0;
            int min = INT_MAX;
            //Get all 8 positions and see what is available
            if(distances_non_tunnel[m.x_pos+1][m.y_pos] != ' ')
            {
                if(distances_non_tunnel[m.x_pos+1][m.y_pos] == '@')
                {
                    //move the monster over and win the game
                    dungeon[m.x_pos+1][m.y_pos] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos+1][m.y_pos];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos+1;
                    minY = m.y_pos;
                }
                
            }
            if(distances_non_tunnel[m.x_pos-1][m.y_pos] != ' ')
            {
                if(distances_non_tunnel[m.x_pos-1][m.y_pos] == '@')
                {
                    dungeon[m.x_pos-1][m.y_pos] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos-1][m.y_pos];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos-1;
                    minY = m.y_pos;
                }
                
            }
            if(distances_non_tunnel[m.x_pos][m.y_pos+1] != ' ')
            {
                if(distances_non_tunnel[m.x_pos][m.y_pos+1] == '@')
                {
                    dungeon[m.x_pos][m.y_pos+1] = '3';
                    return 1;
                }
                
                int dis = distances_non_tunn[m.x_pos][m.y_pos+1];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos;
                    minY = m.y_pos+1;
                }
            }
            if(distances_non_tunnel[m.x_pos][m.y_pos-1] != ' ')
            {
                if(distances_non_tunnel[m.x_pos][m.y_pos-1] == '@')
                {
                    dungeon[m.x_pos][m.y_pos-1] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos][m.y_pos-1];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos;
                    minY = m.y_pos-1;
                }
            }
            if(distances_non_tunnel[m.x_pos+1][m.y_pos-1] != ' ')
            {
                if(distances_non_tunnel[m.x_pos+1][m.y_pos-1] == '@')
                {
                    dungeon[m.x_pos+1][m.y_pos-1] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos+1][m.y_pos-1];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos+1;
                    minY = m.y_pos-1;
                }
            }
            if(distances_non_tunnel[m.x_pos+1][m.y_pos+1] != ' ')
            {
                if(distances_non_tunnel[m.x_pos+1][m.y_pos+1] == '@')
                {
                    dungeon[m.x_pos+1][m.y_pos+1] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos+1][m.y_pos+1];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos+1;
                    minY = m.y_pos+1;
                }
            }
            if(distances_non_tunnel[m.x_pos-1][m.y_pos+1] != ' ')
            {
                if(distances_non_tunnel[m.x_pos-1][m.y_pos+1] == '@')
                {
                    dungeon[m.x_pos-1][m.y_pos+1] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos-1][m.y_pos+1];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos-1;
                    minY = m.y_pos+1;
                }
            }
            if(distances_non_tunnel[m.x_pos-1][m.y_pos-1] != ' ')
            {
                if(distances_non_tunnel[m.x_pos-1][m.y_pos-1] == '@')
                {
                    dungeon[m.x_pos-1][m.y_pos-1] = '3';
                    return 1;
                }
                int dis = distances_non_tunn[m.x_pos-1][m.y_pos-1];
                if(dis < min)
                {
                    min = dis;
                    minX = m.x_pos-1;
                    minY = m.y_pos-1;
                }
                
            }
    
            dungeon[minX][minY] = '3';
            dungeon[m.x_pos][m.y_pos] = '.';
            m.x_pos = minX;
            m.y_pos = minY;
            return 0;
        }
        else if(m.characteristics == 0x4)
        {
            
        }
        else if(m.characteristics == 0x5)
        {
            
        }
        else if(m.characteristics == 0x6)
        {
            
        }
        else if(m.characteristics == 0x7)
        {
            
        }
        else if(m.characteristics == 0x8)
        {
            
        }
        else if(m.characteristics == 0x9)
        {
            
        }
        else if (m.characteristics == 0xa)
        {
            
        }
        else if (m.characteristics == 0xb)
        {
            
        }
        else if (m.characteristics == 0xc)
        {
            
        }
        else if (m.characteristics == 0xd)
        {
            
        }
        else if (m.characteristics == 0xe)
        {
        }
        else if (m.characteristics == 0xf)
        {
        }

        queue_add(q, m, (EVENT_CONSTANT/m.speed)+turn);
        return 0;
    }

    return 0;
}

int checkForPC(monster_t m)
{
    if(dungeon[m.x_pos +1][m.y_pos] == '@')
    {
        //dungeon[m.x_pos+1][m.y_pos] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos -1][m.y_pos] == '@')
    {
        //dungeon[m.x_pos-1][m.y_pos] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos][m.y_pos+1] == '@')
    {
        //dungeon[m.x_pos][m.y_pos+1] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos][m.y_pos-1] == '@')
    {
        //dungeon[m.x_pos][m.y_pos-1] = intToChar(m.characteristics);
       // dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos +1][m.y_pos+1] == '@')
    {
        //dungeon[m.x_pos+1][m.y_pos+1] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos +1][m.y_pos-1] == '@')
    {
        //dungeon[m.x_pos+1][m.y_pos-1] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos -1][m.y_pos+1] == '@')
    {
        //dungeon[m.x_pos-1][m.y_pos+1] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos -1][m.y_pos-1] == '@')
    {
        //dungeon[m.x_pos-1][m.y_pos-1] = intToChar(m.characteristics);
        //dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }

    return 0;
}

int check_won_status(monster_t *arr, int arr_size)
{
    int index = 0;
    for(index = 0; index < arr_size; index++)
    {
        if(arr[index].alive == 1)
        {
            return 0;
        }
    }
    return 1;
}

int check_for_monster(int x_pos, int y_pos, monster_t *arr, int arr_size)
{
    int i = 0;
    for(i = 0; i < arr_size; i++)
    {
        //If there is a monster at that position and it is alive then return index
        if((arr[i].x_pos == x_pos) && (arr[i].y_pos == y_pos) && (arr[i].alive == 1))
        {
            return i;
        }
    }

    return -1;
}

void print_message(WINDOW *win, int status)
{
    if(status == 7)
    {
        wprintw(win, "character moved to the upper left\r");
    }
    else if(status == 8)
    {
        wprintw(win, "character moved up\r");
    }
    else if(status == 9)
    {
        wprintw(win, "character moved to the upper right\r");
    }
    else if(status == 6)
    {
        wprintw(win, "character moved to the right\r");   
    }
    else if(status == 3)
    {
        wprintw(win, "character moved to the lower right\r");
    }
    else if(status == 2)
    {
        wprintw(win, "character moved down\r");   
    }
    else if(status == 1)
    {
        wprintw(win, "character moved to the lower left\r");
    }
    else if(status == 4)
    {
        wprintw(win, "character moved to the left\r");
    }
    else if(status == 5)
    {
        wprintw(win, "character did not move\r");
    }

    wrefresh(win);
}

void move_PC(int whichDir, monster_t *arr, int arr_size)
{
   if(whichDir == 7)
   {
      if(dungeon[pc_x_position-1][pc_y_position-1] != ' ' && dungeon[pc_x_position-1][pc_y_position-1] != '|' && dungeon[pc_x_position-1][pc_y_position-1] != '-')
      {
          int monster_found = check_for_monster(pc_x_position-1, pc_y_position-1, arr, arr_size);
          //Monster has been found, we need to make him unalive, and update the pc & monster information
          if(monster_found != -1)
          {
              arr[monster_found].alive = 0;
              dungeon[pc_x_position][pc_y_position] = lastPosition;
              lastPosition = '.';
              dungeon[pc_x_position - 1][pc_y_position - 1] = '@';
              pc_x_position = pc_x_position - 1;
              pc_y_position = pc_y_position - 1;
              
          }
          else
          {
              
            dungeon[pc_x_position][pc_y_position] = lastPosition;
            lastPosition = dungeon[pc_x_position - 1][pc_y_position - 1];
            dungeon[pc_x_position - 1][pc_y_position - 1] = '@';
            pc_x_position = pc_x_position - 1;
            pc_y_position = pc_y_position - 1;
          }
      }

   }
   else if(whichDir == 8)
   {
      
      if(dungeon[pc_x_position-1][pc_y_position] != ' ' && dungeon[pc_x_position-1][pc_y_position] != '|' && dungeon[pc_x_position-1][pc_y_position] != '-')
      {
        int monster_found = check_for_monster(pc_x_position-1, pc_y_position, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            dungeon[pc_x_position][pc_y_position] = lastPosition;
            lastPosition = '.';
            dungeon[pc_x_position - 1][pc_y_position] = '@';
            pc_x_position = pc_x_position - 1;

        }
         else{
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position - 1][pc_y_position];
         dungeon[pc_x_position - 1][pc_y_position] = '@';
         pc_x_position = pc_x_position - 1;
         }
      }

   }
   else if(whichDir == 9)
   {
      
      if(dungeon[pc_x_position-1][pc_y_position+1] != ' ' && dungeon[pc_x_position-1][pc_y_position+1] != '|' && dungeon[pc_x_position-1][pc_y_position+1] != '-')
      {
        int monster_found = check_for_monster(pc_x_position-1, pc_y_position+1, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position - 1][pc_y_position + 1] = '@';
         pc_x_position = pc_x_position - 1;
         pc_y_position = pc_y_position + 1;

        }
         else{
             
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position - 1][pc_y_position + 1];
         dungeon[pc_x_position - 1][pc_y_position + 1] = '@';
         pc_x_position = pc_x_position - 1;
         pc_y_position = pc_y_position + 1;
         }
      }
   }
   else if (whichDir == 6)
   {
      
      if(dungeon[pc_x_position][pc_y_position+1] != ' ' && dungeon[pc_x_position][pc_y_position+1] != '|' && dungeon[pc_x_position][pc_y_position+1] != '-')
      {

        int monster_found = check_for_monster(pc_x_position, pc_y_position+1, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position][pc_y_position + 1] = '@';
         pc_y_position = pc_y_position + 1;
        }
         else{
             
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position][pc_y_position + 1];
         dungeon[pc_x_position][pc_y_position + 1] = '@';
         pc_y_position = pc_y_position + 1;
         }
      }
   }
   else if(whichDir == 3)
   {
      
      if(dungeon[pc_x_position+1][pc_y_position+1] != ' ' && dungeon[pc_x_position+1][pc_y_position+1] != '|' && dungeon[pc_x_position+1][pc_y_position+1] != '-')
      {
        int monster_found = check_for_monster(pc_x_position+1, pc_y_position+1, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position + 1][pc_y_position + 1];
         dungeon[pc_x_position + 1][pc_y_position + 1] = '@';
         pc_x_position = pc_x_position + 1;
         pc_y_position = pc_y_position + 1;
        }
         else{
             
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position + 1][pc_y_position + 1] = '@';
         pc_x_position = pc_x_position + 1;
         pc_y_position = pc_y_position + 1;
         }
      }
   }
   else if(whichDir == 2)
   {
      
      if(dungeon[pc_x_position+1][pc_y_position] != ' ' && dungeon[pc_x_position+1][pc_y_position] != '|' && dungeon[pc_x_position+1][pc_y_position] != '-')
      {
        int monster_found = check_for_monster(pc_x_position+1, pc_y_position, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position + 1][pc_y_position] = '@';
         pc_x_position = pc_x_position + 1;
        }
         else{
             
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position + 1][pc_y_position];
         dungeon[pc_x_position + 1][pc_y_position] = '@';
         pc_x_position = pc_x_position + 1;
         }
      }
   }
   else if(whichDir == 1)
   {
      
      if(dungeon[pc_x_position+1][pc_y_position-1] != ' ' && dungeon[pc_x_position+1][pc_y_position-1] != '|' && dungeon[pc_x_position+1][pc_y_position-1] != '-')
      {
        int monster_found = check_for_monster(pc_x_position+1, pc_y_position-1, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position + 1][pc_y_position - 1] = '@';
         pc_x_position = pc_x_position + 1;
         pc_y_position = pc_y_position - 1;
        }
         else
         {
             
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position + 1][pc_y_position - 1] = '@';
         pc_x_position = pc_x_position + 1;
         pc_y_position = pc_y_position - 1;
         }
      }
   }
   else if(whichDir == 4)
   {
      
      if(dungeon[pc_x_position][pc_y_position-1] != ' ' && dungeon[pc_x_position][pc_y_position-1] != '|' && dungeon[pc_x_position][pc_y_position-1] != '-')
      {
        int monster_found = check_for_monster(pc_x_position, pc_y_position-1, arr, arr_size);
        if(monster_found != -1)
        {
            arr[monster_found].alive = 0;
            
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = '.';
         dungeon[pc_x_position][pc_y_position - 1] = '@';
         pc_y_position = pc_y_position - 1;
        }
         else{
             
         dungeon[pc_x_position][pc_y_position] = lastPosition;
         lastPosition = dungeon[pc_x_position][pc_y_position - 1];
         dungeon[pc_x_position][pc_y_position - 1] = '@';
         pc_y_position = pc_y_position - 1;
         }
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