/*
Simple Snake Game
GROUP 3 SECTION 1

                        DEBRE TABOR UNIVERSITY
                          Technology faculty
                    Department of computer science


Group member                                ID number
 1	Abdulsomed Jibri                       DTU13R0024
 2	Muluken Dagne                          DTU12R1094
 3	Emran Ahmed                            DTU13R0584
 4	Ytbarek  Maru                          DTU13R1818
 5	Dawud Worku                            DTU13R0466
 6	Betelhem G/Mehdin                      DTU13R0289
 7	Timket Getachew                        DTU13R1652
 8	Sammuel Kasahun                        DTU13R1450
 9  medina feleke                          DTU13R3113
 10 Edlawit Tadega                         DTU13R0550
*/


#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

//==== struct list;

typedef struct tailpos
{
       int x;                // x cordinate of the snake
       int y;                // y cordinate of the snake
       struct tailpos *next; // pointer to next node
       struct tailpos *prev; // pointer to previous node
} tail;

// d used to set the direction
int d = 4;

/*
SNAKE CLASS
            contain variable of tailpos structure
            this class handle movement of the snake
            contain the draw function

*/
class snake
{
public:
       int wallsX, wallsY; // wall start position can be use to define wall
       int walleX, walleY; // wall end position

       int score; // keep score

       int foodx, foody; // position of the food

       HANDLE console_handle; // handle for the console
       COORD cur_cord;        // COORD struct to keep the coordinate

       /*
       tail struct ==>
                      start = pointer to first part of body
                      current = pointer to last node
                      new tail = temp node for new tail

       */

       tail *start, *current, *newtail;
       snake();                   // construct to initialize tail variable to null
       void insert(int x, int y); // insert the body of snake append to next node
       void draw();               // draw the snake
       void drawWall();           // draw the wall
       void move();               // control the movement
       bool collision();          //check snake collision with itself or wall
       void drawfood(int x = 0);  // draw food to new position if x==1
       void drawinit();           // initial setup like draw wall
       void labelDead();          // Draw when player is dead
       void menu();               // menu screen
       void help();               // menu for help
};

//prototype for loop function

void loop(snake &ob);

// implement snake class
snake::snake()
{

       score = 0; // set the initial score

       start = NULL;                                     // start node point to null
       current = NULL;                                   // same
       newtail = NULL;                                   // same
       console_handle = GetStdHandle(STD_OUTPUT_HANDLE); // getting console handle

       foodx = 12; // starting food positions
       foody = 14;

       wallsX = 2;
       wallsY = 2; // walls starting and ending position
       walleX = 70;
       walleY = 20; // draw wall of 70x50

       cur_cord.X = 152;
       cur_cord.Y = 500;
       SetConsoleScreenBufferSize(console_handle, cur_cord); // setting up screen buffer
}
/*
this method is to insert new tail of snake at the current food position when snake eat it.

*/
void snake ::insert(int x, int y)
{
       // check if start is null
       if (start == NULL)
       {
              newtail = new tail;
              newtail->x = x;
              newtail->y = y;
              newtail->next = NULL;
              newtail->prev = NULL;
              start = newtail;
              current = newtail;
       }
       else // insert new node to start node
       {
              newtail = new tail;
              newtail->x = x;
              newtail->y = y;
              newtail->next = NULL;
              newtail->prev = current;
              current->next = newtail;
              current = newtail;
       }
}

/*
move :
      contain main logic to move the snake by incrementing and decrementing
      the X or Y coordinate
      position of first part is moved to the next part. copying is done in Reverse order that
      is from last to first .
      Last node position is updated with previous node position and at last. Start node Coordinate
      X or y is inc or Dec.

*/

void snake::move()
{
       tail *tmp, *cur;

       tmp = current; // point tmp to last node

       while (tmp->prev != NULL)
       {
              tmp->x = tmp->prev->x; // copy val from previous to last
              tmp->y = tmp->prev->y;
              tmp = tmp->prev; // set tmp to previous node
       }
/*
check for the value of d in order to change its direction
increment and decrement value of x , y
*/
       if (d == 1)
              start->y--;

       if (d == 2)
              start->y++;

       if (d == 3)
              start->x--;

       if (d == 4)
              start->x++;
}

/*
draw :
      draw snake part according to their position
      traverse the node from start to end
*/
void snake::draw()
{

       // putting score label
       cur_cord.X = 2;
       cur_cord.Y = 0;

       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << "SCORE : " << score;

       tail *tmp, *last;
       tmp = start;
       last = current;

       while (tmp != NULL)
       {
              cur_cord.X = tmp->x;
              cur_cord.Y = tmp->y;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cout << (char)219; // snake character
              tmp = tmp->next;
       }
       // remove tail
       cur_cord.X = last->x;
       cur_cord.Y = last->y;
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << ' ';
       //draw the food
       cur_cord.X = foodx;
       cur_cord.Y = foody;
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << (char)15; // food character
}

void snake::drawWall()
{
/*
for drawing wall you can use variables to store wall starting and ending position
*/

       // draw left column
       cur_cord.X = wallsX;
       for (int y = wallsY; y <= walleY; y++)
       {
              cur_cord.Y = y;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cout << '#';
       }
       // draw top row
       cur_cord.Y = wallsY;
       for (int x = wallsX; x <= walleX; x++)
       {
              cur_cord.X = x;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cout << '#';
       }
       // draw right column
       cur_cord.X = walleX;
       for (int y = wallsY; y <= walleY; y++)
       {
              cur_cord.Y = y;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cout << '#';
       }

       // draw bottom row
       cur_cord.Y = walleY;
       for (int x = wallsX; x <= walleX; x++)
       {
              cur_cord.X = x;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cout << '#';
       }
}

void snake::drawfood(int x) // no use of int x here
{
       tail *tmp;
       tmp = start;
       if (x == 1) // draw new food
       {
              foodx = rand() % 2 + 39; // rand number between 2-39
              foody = rand() % 2 + 16; // it will better to use wall ends position walleX,Y

              while (tmp->next != NULL)
              {
                     if (foodx == tmp->x && foody == tmp->y)
                     {
                            drawfood(1);
                            cout << "drawn";
                     }

                     tmp = tmp->next;
              }
       }
}

void snake::drawinit()
{
       drawWall();
}

/*
detect if snake collided with it self or wall or food
*/
bool snake::collision()
{
       tail *tmp;
       tmp = start->next;
       //check collision with itself
       while (tmp->next != NULL)
       {
              if (start->x == tmp->x && start->y == tmp->y)
                     return true;

              tmp = tmp->next;
       }
       //check collision with food
       if (start->x == foodx && start->y == foody)
       {
              insert(foodx, foody); // insert new tail
              drawfood(1);          // get new food position
              score++;              // update score
       }

       //check collision with wall
       //collision top row
       for (int x = wallsX; x <= walleX; x++)          // getting x coordinate
       {                                               // y coordinate remain same y=0 because in row x increase in same y
              if (start->x == x && start->y == wallsY) // getting y coordinate to get complete x,y coordinate
              {
                     return true;
              }
       }
       //collision left column
       for (int y = wallsY; y <= walleY; y++)
       {
              if (start->x == wallsX && start->y == y) // x same y change x=0
              {
                     return true;
              }
       }
       //collision right column
       for (int y = wallsY; y <= walleY; y++)
       {
              if (start->x == walleX && start->y == y) // right column therefore x ending point(same) with y changing
              {
                     return true;
              }
       }
       //collision bottom row
       for (int x = wallsX; x <= walleX; x++)
       {
              if (start->x == x && start->y == walleY)
              {
                     return true;
              }
       }

       return false; // return false no collision
}
/*
draw thing when player is dead
*/
void snake::labelDead()
{

       cur_cord.X = (walleX / 2);
       cur_cord.Y = (walleY / 2);

       SetConsoleCursorPosition(console_handle, cur_cord);

       cout << "YOU ARE DEAD\n";

       cur_cord.Y = (walleY / 2) + 1;
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << "YOUR HIGH SCORE IS " << score;
}

/*
menu screen of the game
*/

void snake::menu()
{
       char word;
       ifstream iFile("menu.txt");
       word = iFile.get();
       while (iFile)
       {

              cout << word;
              word = iFile.get();
       }
       iFile.close();
       // get the menu
}

/*
help menu for snake
*/
void snake::help()
{
       char word;
       ifstream iFile("help.txt");
       word = iFile.get();
       while (iFile)
       {

              cout << word;
              word = iFile.get();
       }
       iFile.close();

       getch(); // wait for key to press
}

//===== main function
int main()
{
       // displaying the menu
       snake obc;
       obc.menu();
       switch (getch())
       {
       case 'n':
              system("CLS");
              loop(obc);
              break;
       case 'h':
              system("CLS");
              obc.help();
              system("CLS");
              main();
              break;
       case 'q':
              break;
       default:
              system("CLS");
              main();
       }

       return 0;
}

// loop controls the game
void loop(snake &ob)
{
       ob.insert(10, 6); // first is head  snake drawn from first to last
       ob.insert(10, 7);
       ob.insert(10, 8);
       ob.insert(10, 9);

       ob.drawinit(); // this will just draw wall
       int dir = 1;
       while (1)
       {
              ob.draw();
              Sleep(200); // waiting time
                          //system("CLS");
                          //clearScreen();

              if (ob.collision()) // check if collision with wall or itself occur
              {
                     ob.labelDead(); // do when snake is dead
                     break;
              }

              if (kbhit()) // check if keyboard key is pressed
              {
                     switch (getch())
                     {
                     case 'w':
                            d = 1;
                            break;
                     case 's':
                            d = 2;
                            break;
                     case 'a':
                            d = 3;
                            break;
                     case 'd':
                            d = 4;
                            break;
                     case 'm':
                            ob.insert(10, 7);
                            break;
                     }
                    // not needed
              }

              ob.move();
       }
       int x;
       cin >> x;
}
