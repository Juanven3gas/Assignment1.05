#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "distances.h"
#include "gen_dun.h"

int findAllVertices(void);
int calc_distances(void);

//For non tunneling monsters
void init_non_tunnel_arr(void);
void print_non_tunnel_arr(void);
void init_distances_arr(int *arr, int size);
void init_positions_arr(int *arr, int* arr2);
void init_bool_arr(bool *arr, int size);

//For tunneling monsters
void init_tunnel_arr(void);
void init_tunnel_positions(int* arr1, int*arr2);
void init_all_arrs(int *arr1, int *arr2, int *arr3, bool *set);
void print_tunnel_arr(void);

//for djikstra's
char int_to_char(int i);
int min_distance(int *arr, bool *set, int size);
int find_index(int *arr, int *arr2, int size, int xpos, int ypos);
char intToChar(int i);

int calc_distances(void)
{
   //gen_dun();
   //place_PC();
   //print_dungeon();
   init_non_tunnel_arr();
   init_tunnel_arr();

   int array_size = findAllVertices();
   int distances[array_size + 1];
   int x_position[array_size + 1];
   int y_position[array_size + 1];
   bool set[array_size + 1];
   int vertex_count;
   /**
   * Initialize all arrays for dijkstras
   *
   */

   init_distances_arr(distances, array_size);
   init_positions_arr(x_position, y_position);
   init_bool_arr(set, array_size + 1);

   x_position[array_size] = pc_x_position;
   y_position[array_size] = pc_y_position;
   distances[array_size] = 0;

   //find the shortes path for non tunneling monsters

   for(vertex_count = 0; vertex_count < (array_size + 1); vertex_count++)
   {
       int min_v = min_distance(distances, set, array_size + 1);
       //printf("min vertex found: x: %d, y:%d, distance: %d\n", x_position[min_v], y_position[min_v], distances[min_v]);

       set[min_v] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       // Update dist[v] only if is not in sptSet, there is an edge from 
        // u to v, and total weight of path from src to  v through u is 
        // smaller than current value of dist[v]

           int x_pos = x_position[min_v];
           int y_pos = y_position[min_v];
           char toAdd = int_to_char(distances[min_v] % 10);

           distances_non_tunnel[x_pos][y_pos] = toAdd;
           distances_non_tunn[x_pos][y_pos] = distances[min_v];

           if(dungeon[x_pos + 1][y_pos] == '.' || dungeon[x_pos + 1][y_pos] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos + 1, y_pos);
               
               if(index == -1)
               {
                   printf("line 71 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

              if(!set[index] && distances[min_v] != INT_MAX && distances[min_v] + 1 < distances[index])
              {
                  distances[index] = distances[min_v] + 1;
                 
              }
           }
           if(dungeon[x_pos][y_pos + 1] == '.' || dungeon[x_pos][y_pos + 1] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos, y_pos + 1);

               if(index == -1)
               {
                   printf("line 86 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

               if((!set[index]) && (distances[min_v] != INT_MAX) && (distances[min_v] + 1 < distances[index]))
               {
                   distances[index] = distances[min_v] + 1;
                   
               }
           }
           if(dungeon[x_pos - 1][y_pos] == '.' || dungeon[x_pos - 1][y_pos] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos - 1, y_pos);
               if(index == -1)
               {
                   printf("line 100 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

               if((!set[index]) && (distances[min_v] != INT_MAX) && (distances[min_v] + 1 < distances[index]))
               {
                   distances[index] = distances[min_v] + 1;
                   
               }
           }
           if(dungeon[x_pos][y_pos - 1] == '.' || dungeon[x_pos][y_pos -1] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos, y_pos - 1);
               
               if(index == -1)
               {
                   printf("line 114 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

               if((!set[index]) && (distances[min_v] != INT_MAX) && (distances[min_v] + 1 < distances[index]))
               {
                   distances[index] = distances[min_v] + 1;
                   
               }
           }
           if(dungeon[x_pos + 1][y_pos + 1] == '.' || dungeon[x_pos + 1][y_pos + 1] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos + 1, y_pos +1);
               
               if(index == -1)
               {
                   printf("line 133 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

              if(!set[index] && distances[min_v] != INT_MAX && distances[min_v] + 1 < distances[index])
              {
                  distances[index] = distances[min_v] + 1;
                 
              }
           }
           if(dungeon[x_pos + 1][y_pos - 1] == '.' || dungeon[x_pos + 1][y_pos -1 ] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos + 1, y_pos -1);
               
               if(index == -1)
               {
                   printf("line 148 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

              if(!set[index] && distances[min_v] != INT_MAX && distances[min_v] + 1 < distances[index])
              {
                  distances[index] = distances[min_v] + 1;
                 
              }
           }
           if(dungeon[x_pos - 1][y_pos + 1] == '.' || dungeon[x_pos - 1][y_pos + 1] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos - 1, y_pos + 1);
               
               if(index == -1)
               {
                   printf("line 163 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

              if(!set[index] && distances[min_v] != INT_MAX && distances[min_v] + 1 < distances[index])
              {
                  distances[index] = distances[min_v] + 1;
                 
              }
           }
           if(dungeon[x_pos - 1][y_pos - 1] == '.' || dungeon[x_pos - 1][y_pos - 1] == '#')
           {
               int index = find_index(x_position, y_position, array_size + 1, x_pos - 1, y_pos - 1);
               
               if(index == -1)
               {
                   printf("line 178 index is negative! For xpos: %d ypos:%d\n", x_position[min_v], y_position[min_v]);
               }

              if(!set[index] && distances[min_v] != INT_MAX && distances[min_v] + 1 < distances[index])
              {
                  distances[index] = distances[min_v] + 1;
                 
              }
           }
   }
   
   distances_non_tunnel[pc_x_position][pc_y_position] = '@';
   //print_non_tunnel_arr();

   //begin djisktras for tunneling monsters
   //does everything except for the outtermost row & column
   array_size = (DUNGEON_ROWS -2) * (DUNGEON_COLUMNS - 2);
   int tunnel_distances[array_size];
   int tunnel_x_position[array_size];
   int tunnel_y_position[array_size];
   bool tunnel_set[array_size];

   init_distances_arr(tunnel_distances, array_size - 1);
   init_tunnel_positions(tunnel_x_position, tunnel_y_position);
   init_bool_arr(tunnel_set, array_size);

   tunnel_distances[array_size -  1] = 0;
   tunnel_x_position[array_size - 1] = pc_x_position;
   tunnel_y_position[array_size - 1] = pc_y_position;

   //init_all_arrs(tunnel_x_position, tunnel_y_position, tunnel_distances, tunnel_set);

   //find shortest path for tunneling monsters
   for(vertex_count = 0; vertex_count < (array_size); vertex_count++)
   {
       int min_v = min_distance(tunnel_distances, tunnel_set, array_size);
       tunnel_set[min_v] = true;

       int x_pos = tunnel_x_position[min_v];
       int y_pos = tunnel_y_position[min_v];
       char toAdd = int_to_char(tunnel_distances[min_v] % 10);
       int index;
       int weight;

       distances_tunnel[x_pos][y_pos] = toAdd;

       //Check below if possible
       if(x_pos + 1 < 20)
       {
        index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos + 1, y_pos);
        
               if(index == -1)
               {
                   printf("line 238 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
                   break;
               }
        
               weight = hardness[x_pos+1][y_pos];
        
               if(weight == 0)
               {
                   weight = 1;
               }
               else
               {
                   weight = weight / 85;
               }
        
              if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
              {
                tunnel_distances[index] = tunnel_distances[min_v] + weight;
                //printf("new ditance for %d, %d is %d\n", x_pos + 1, y_pos, tunnel_distances[index]);
              }    
       }
       

      //check above if possible
      if(x_pos - 1 > 0)
      {
        index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos - 1, y_pos);
        
          if(index == -1)
          {
              printf("line 266 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
              break;
          }
        
           weight = hardness[x_pos - 1][y_pos];
          if(weight == 0)
          {
              weight = 1;
          }
          else
          {
              weight = weight / 85;
          }
        
          if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
          {
             tunnel_distances[index] = tunnel_distances[min_v] + weight;
              //printf("new ditance for %d, %d is %d\n", x_pos - 1, y_pos, tunnel_distances[index]);
          }
      }
      

      //check left if possible 
      if(y_pos - 1 > 0)
      {
            index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos, y_pos - 1);
            
              if(index == -1)
              {
                  printf("line 291 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
                  break;
              }
            
               weight = hardness[x_pos][y_pos - 1];
              if(weight == 0)
              {
                  weight = 1;
              }
              else
              {
                  weight = weight / 85;
              }
            
              if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
              {
                 tunnel_distances[index] = tunnel_distances[min_v] + weight;
                  //printf("new ditance for %d, %d is %d\n", x_pos, y_pos - 1, tunnel_distances[index]);
              }
    
      }
        
      //check right if possible
      if(y_pos + 1 < 79)
      {

            index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos, y_pos + 1);
            
              if(index == -1)
              {
                  printf("line 316 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
                  break;
              }
  
              weight = hardness[x_pos][y_pos + 1];
              if(weight == 0)
              {
                  weight = 1;
              }
              else
              {
                  weight = weight / 85;
              }
            
              if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
              {
                 tunnel_distances[index] = tunnel_distances[min_v] + weight;
                  //printf("new ditance for %d, %d is %d\n", x_pos, y_pos+1, tunnel_distances[index]);
              }
      }

      //check upper right if possible
      if(x_pos - 1 > 0 && y_pos + 1< 79)
      {
        index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos - 1, y_pos + 1);
        
          if(index == -1)
          {
              printf("line 358 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
              break;
          }

          weight = hardness[x_pos - 1][y_pos + 1];
          if(weight == 0)
          {
              weight = 1;
          }
          else
          {
              weight = weight / 85;
          }
        
          if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
          {
             tunnel_distances[index] = tunnel_distances[min_v] + weight;
              //printf("new ditance for %d, %d is %d\n", x_pos, y_pos+1, tunnel_distances[index]);
          }
      }

      //CHeck upper left if possible
      if(x_pos - 1 > 0 && y_pos - 1 < 0)
      {
        index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos - 1, y_pos - 1);
        
          if(index == -1)
          {
              printf("line 316 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
              break;
          }

          weight = hardness[x_pos - 1][y_pos - 1];
          if(weight == 0)
          {
              weight = 1;
          }
          else
          {
              weight = weight / 85;
          }
        
          if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
          {
             tunnel_distances[index] = tunnel_distances[min_v] + weight;
              //printf("new ditance for %d, %d is %d\n", x_pos, y_pos+1, tunnel_distances[index]);
          }
      }
      
      //Check lower right if possible
      if(x_pos + 1 < 20 && y_pos + 1 < 79)
      {
        index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos + 1, y_pos + 1);
        
          if(index == -1)
          {
              printf("line 316 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
              break;
          }

          weight = hardness[x_pos + 1][y_pos + 1];
          if(weight == 0)
          {
              weight = 1;
          }
          else
          {
              weight = weight / 85;
          }
        
          if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
          {
             tunnel_distances[index] = tunnel_distances[min_v] + weight;
              //printf("new ditance for %d, %d is %d\n", x_pos, y_pos+1, tunnel_distances[index]);
          }
      }

      //Check lower left if possible
      if(x_pos + 1  > 0 && y_pos - 1 < 0)
      {
        index = find_index(tunnel_x_position, tunnel_y_position, array_size, x_pos + 1, y_pos + 1);
        
          if(index == -1)
          {
              printf("line 316 index is negative! For xpos: %d ypos:%d\n", tunnel_x_position[min_v], tunnel_y_position[min_v]);
              break;
          }

          weight = hardness[x_pos + 1][y_pos + 1];
          if(weight == 0)
          {
              weight = 1;
          }
          else
          {
              weight = weight / 85;
          }
        
          if((!tunnel_set[index]) && (tunnel_distances[min_v] != INT_MAX) && (tunnel_distances[min_v] + weight < tunnel_distances[index]))
          {
             tunnel_distances[index] = tunnel_distances[min_v] + weight;
              //printf("new ditance for %d, %d is %d\n", x_pos, y_pos+1, tunnel_distances[index]);
          }
      }
        
   }

   //print the tunneling monsters array
   distances_tunnel[pc_x_position][pc_y_position] = '@';
   //print_tunnel_arr();
   //printf("INT_MAX mod 10 = %d", INT_MAX % 10);
   return 0;
}

void init_all_arrs(int *arr1, int *arr2, int *arr3, bool *set)
{
    int rows;
    int cols;
    int arr_index = 0;
    for(rows = 1; rows < (DUNGEON_ROWS -1 ); rows++)
    {
        for(cols = 1; cols < (DUNGEON_COLUMNS - 1); cols++)
        {
            if(dungeon[rows][cols] == '@')
            {
                arr1[arr_index] = rows;
                arr2[arr_index] = cols;
                arr3[arr_index] = 0;
                set[arr_index] = false;
            }
            else
            {
                arr1[arr_index] = rows;
                arr2[arr_index] = cols;
                arr3[arr_index] = INT_MAX;
                set[arr_index] = false;
            
            }
        }
    }
}

void print_tunnel_arr(void)
{
    int rows, cols;
    for(rows = 0; rows < DUNGEON_ROWS; rows++)
    {
        for(cols = 0; cols < DUNGEON_COLUMNS; cols++)
        {
            printf("%c", distances_tunnel[rows][cols]);
        }

        printf("\n");
    }
}

void init_tunnel_positions(int *arr1, int* arr2)
{
    int rows, cols;
    int arr_index = 0;
    for(rows = 1; rows < (DUNGEON_ROWS - 1); rows++)
    {
        for(cols = 1; cols < (DUNGEON_COLUMNS - 1); cols++)
        {
            if(dungeon[rows][cols] != '@')
            {
                arr1[arr_index] = rows;
                arr2[arr_index] = cols;
                //printf("%d, %d\n", rows, cols);
                arr_index++;
               
            }
        }
    }
}

char int_to_char(int i)
{
    switch (i)
    {
        case 0:
        return '0';

        case 1:
        return '1';

        case 2:
        return '2';
        
        case 3:
        return '3';
        
        case 4:
        return '4';
        
        case 5:
        return '5';
        
        case 6:
        return '6';
        
        case 7:
        return '7';
        
        case 8:
        return '8';
        
        case 9:
        return '9';
        
        default:
        return ' ';
    }

    return ' ';
}

void init_tunnel_arr(void)
{
    int rows, cols;
    for(rows = 0; rows < DUNGEON_ROWS; rows++)
    {
        for(cols = 0; cols < DUNGEON_COLUMNS; cols++)
        {
            distances_tunnel[rows][cols] = ' ';
        }
    }
}

void init_non_tunnel_arr(void)
{
    int row, col;
    for(row = 0; row < DUNGEON_ROWS; row++)
    {
        for(col = 0; col < DUNGEON_COLUMNS; col++)
        {
            distances_non_tunnel[row][col] = ' ';
            distances_non_tunn[row][col] = 0;
        }
    }
}

void print_non_tunnel_arr(void)
{
    int row, col;
    for(row = 0; row < DUNGEON_ROWS; row++)
    {
        for(col = 0; col < DUNGEON_COLUMNS; col++)
        {
                printf("%c", distances_non_tunnel[row][col]);
        }

        printf("\n");
    }
}

int find_index(int *arr, int *arr2, int size, int xpos, int ypos)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if((arr[i] == xpos) && (arr2[i] == ypos))
        {
            return i;
        }
    }

    return -1;
}

int min_distance(int *arr, bool *set, int size)
{
    int min = INT_MAX;
    int min_indx;
    int i;

    for(i = 0; i < size; i++)
    {
        if((set[i] == false) && (arr[i] <= min))
        {
            min = arr[i];
            min_indx = i;
        }
    }

    return min_indx;
}

void init_bool_arr(bool *arr, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        arr[i] = false;
    }
}

void init_distances_arr(int *arr, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        arr[i] = INT_MAX;
    }
}

void init_positions_arr(int *arr, int* arr2)
{
    int rows, cols;
    int array_index = 0;
    for(rows = 0; rows < DUNGEON_ROWS; rows++)
    {
        for(cols = 0; cols < DUNGEON_COLUMNS; cols++)
        {
            if(dungeon[rows][cols] == '.' || dungeon[rows][cols] == '#')
            {
                arr[array_index] = rows;
                arr2[array_index] = cols;
                array_index++;
            }
        }
    }
}

int findAllVertices(void)
{
    int rows, cols;
    int vertices_found = 0;
    for(rows = 0; rows < DUNGEON_ROWS; rows++)
    {
        for(cols = 0; cols < DUNGEON_COLUMNS; cols++)
        {
            if(dungeon[rows][cols] == '.' || dungeon[rows][cols] == '#')
            {
                vertices_found++;
            }
        }
    }

    return vertices_found;
}

char intToChar(int i)
{
    switch(i)
    {
        case 0:
        return '0';
        case 1:
        return '1';
        case 2:
        return '2';
        case 3:
        return '3';
        case 4:
        return '4';
        case 5:
        return '5';
        case 6:
        return '6';
        case 7:
        return '7';
        case 8:
        return '8';
        case 9:
        return '9';
        case 10:
        return 'a';
        case 11:
        return 'b';
        case 12:
        return 'c';
        case 13:
        return 'd';
        case 14:
        return 'e';
        case 15:
        return 'f';
    }

    return '0';
}