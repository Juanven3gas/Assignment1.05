# Assignment1.05
Dungeon Game using NCurses
This assignment is built by calling the make command. To Run the game
you must run main_program file as such: ./main_program --nummon n where n is the number of monster you want in the dungeon.
Note that the assignment functionality(just for assignment 1.05) is entirely implemented but it is very buggy. At the moment
the PC can move freely through the dungeon and can eliminate monsters. If all the monstera are eliminated then the game is won and the program closes. The monsters can also attack the PC if the PC is close enough and it is the monster's turn, but the monsters still do not move freely. If the monsters manage to kill the PC then the game is over and program closes. If the user goes up or
down stairs then a new dungeon is generated as well as monsters. If the m button is clicked then the list of monsters is propagated.
NOTE this functionality is buggy in that monster positions can still be revealed even if they were killed and no longer visible.
