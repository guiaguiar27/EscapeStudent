#include <stdio.h>
#include <stdlib.h>   
#define True 1 
#define False 0 
#define Finished 2  

typedef struct MazePosition{ 
   int line;  
   int column;  
   //int ExploredFlag; 
}MazePosition;  

MazePosition *findPosition(int **maze, int line, int column); 
int initStudent(int **maze, int line, int column,int *keys, MazePosition *position,int *status);  
MazePosition *allocate_position(); 
void show_position(int line, int column);  
