#include <stdio.h>
#include <stdlib.h>   
#define True 1 
#define False 0 
#define Finished 2  
#define DEBUG 1
#define ANALYSIS_MODE 1

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

// linked list to store the solution 
 

/**   
* \brief   
**/
MazePosition *findPosition(int **maze, int line, int column); 
/**   
* \brief   
**/
MazePosition *allocate_position(); 
/**   
* \brief   
**/
void  show_position(int line, int column); 
/**   
* \brief   
**/
int verify_position(int **maze, int line, int column,int *keys, DoorList *list); 
/**   
* \brief   
**/ 
int initStudent(int **maze, int line, int column,int *keys, MazePosition *position, int *status, int ** solution, int *count, DoorList *list);
//solution   
/**   
* \brief   
**/ 
int markOFF_position_solution(int **solution, int line, int column); 
/**   
* \brief   
**/ 
int mark_position_solution(int **solution, int line, int column); 
/**   
* \brief   
**/ 
int verify_solution(int **solution, int line, int column); 
/**   
* \brief   
**/ 
int **initSolution(int line, int column); 
/**   
* \brief   
**/ 
void show_solution_maze(int **solution, int line, int column); 
/**   
* \brief   
**/  
void initBacktrackingMaze(int **maze, int line, int column, int *keys);  
/**   
* \brief   
**/   

DoorList *allocate_list();
/**   
* \brief   
**/   

int verify_door(DoorList *D , int line , int column);  
/**   
* \brief   
**/   

int insert_door(DoorList *dl, int line, int column); 
int remove_door(DoorList *dl, int line, int column); 