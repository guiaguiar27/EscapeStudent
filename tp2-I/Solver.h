#include <stdlib.h> 
#include <stdio.h>   
#include <string.h> 
#include <ctype.h>   

#define True 1  
#define False 0  
#define DEBUG 2 
#define Up 3  
#define Left 4 


// each position will be represented by this array 
typedef struct{ 
    int line;  
    int column; 
 }position;     
 
 // to achieve the solution 
 typedef struct DPSolverType{  
    position POS;  
    struct DPSolverType *next;       
 }DPSolverType; 

// maze construction structure, contains the dimensions and the own maze grid
typedef struct{ 
    position Dimensions;  
    int **Matrix_maze; 
}Maze; 


int Solver(Maze *maze, position *CurrentPosition, position *FinalPosition, DPSolverType *DP_Solver,int *lifes);  
void initSolver(int **maze, int lines, int columns, int *lifes);  
position *findFinalPosition(int **maze, int lines, int columns); 
position *findInitialPosition(int **maze, int lines, int columns);   

void allocate_solver(DPSolverType ** DP);

Maze *allocate_maze(int **maze, int lines, int columns); 
int verify_win(position *CurrentPos , position *FinalPos); 
int verify_boundaries(int lines, int columns, position *pos); 

void show_maze(Maze *maze);  
void current_position(position *pos);  
position *allocate_position(); 

int best_choose(position *pos,int *lifes);  
int already_computed(position *current_position, DPSolverType *DP_solver);  
int best_position(Maze *maze , position *current_position, int life); 

