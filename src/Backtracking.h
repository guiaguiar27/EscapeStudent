/*
   *    ============= TP0 - PAA ==============  
   *    =       Cláudio Barbosa  - 3492      = 
   *    =       Guilherme Aguiar - 3496      =
   *    ======================================
*/

#include <stdio.h>
#include <stdlib.h>   
#define True 1 
#define False 0 
#define Finished 2  
#define DEBUG 1
#define ANALYSIS_MODE  1
#define DEBUG_DOOR 0  
#define L 3 
#define R 4  
#define U 5
#define D 6

typedef struct MazePosition{ 
   int line;  
   int column;  
   //int ExploredFlag; 
}MazePosition;   

typedef struct Node{ 
   int line; 
   int column; 
   struct Node *next;  
}Node_t; 
typedef Node_t DoorList; 

 

/**   
* \brief  find the initial position   
**/
MazePosition *findPosition(int **maze, int line, int column); 
/**   
* \brief   allocate memory to position Data structure 
**/
MazePosition *allocate_position(); 
/**   
* \brief   show the current position
**/
void  show_position(int line, int column); 
/**   
* \brief   checks if the position is reachable
**/
int verify_position(int **maze, int line, int column,int *keys, DoorList *list, int Tline, int Tcolumn); 
/**   
* \brief   the main function, adopt backtracking solution  
**/ 
int initStudent(int **maze, int line, int column,int *keys, MazePosition *position,  int ** solution, int *count, DoorList *list,int *direction);
//solution   
/**   
* \brief   mark off the position  in the matrix solution 
**/ 
int markOFF_position_solution(int **solution, int line, int column); 
/**   
* \brief   mark the current position in the matrix solution   
**/ 
int mark_position_solution(int **solution, int line, int column); 
/**   
* \brief   checks if the position is already computed in the solution
**/ 
int verify_solution(int **solution, int line, int column); 
/**   
* \brief   init the solution matrix 
**/ 
int **initSolution(int line, int column); 
/**   
* \brief   show the final solution 1 indicate the path 
**/ 
void show_solution_maze(int **solution, int line, int column); 
/**   
* \brief   pre function to start the maze solution
**/  
void initBacktrackingMaze(int **maze, int line, int column, int *keys);  
/**   
* \brief   allocate the door list 
**/   
void allocate_list(DoorList **d);
/**   
* \brief checks if the current door is already computed in the list    
**/   
int verify_door(DoorList *Dl , int line , int column);  
/**   
* \brief   show the next studdent direction 
**/   
void show_direction(int *dir);
/**   
* \brief   insert a new door 
**/   
int insert_door(DoorList **dl, int line, int column); 
/**   
* \brief   remove a door from the list 
**/   
int remove_door(DoorList **dl, int line, int column);   
/**   
* \brief   show all listed doors
**/  
void show_doors(DoorList **DL);