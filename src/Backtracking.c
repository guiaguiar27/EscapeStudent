#include "Backtracking.h"
MazePosition *findPosition(int **maze, int line, int column){ 

    MazePosition *position = allocate_position(); 
     for (int i=0; i < line; i++){
         for (int j=0; j < column; j++){
            if(maze[i][j] == 0){ 
                position->line = i; 
                position->column = j; 
            }
         }
     }     
     //position->ExploredFlag = True;
     return position;    
} 
/*-----------------------------------------------------------------------------------------------*/
MazePosition *allocate_position(){ 
    MazePosition *Mz = (MazePosition*)malloc(sizeof(MazePosition)); 
    return Mz; 
} 
/*-----------------------------------------------------------------------------------------------*/

int **initSolution(int line, int column){  
    printf("Entrou aqui\n");
    int **sol = (int**)malloc(line*sizeof(int*)); 
    for(int i = 0 ; i < line; i++){ 
        sol[i] = (int*)malloc(column*sizeof(int));
    }   
    for(int i = 0 ; i < line; i++){ 
        for(int j = 0 ; j < column ; j++)
            sol[i][j] = 0 ;
    }
    return sol; 
}

/*-----------------------------------------------------------------------------------------------*/

int initStudent(int **maze, int line, int column,int *keys, MazePosition *position, int *status, int  **solution ){ 
     #if DEBUG
        show_position(position->line, position->column); 
     #endif 
     if(position->line == 0){ 
         *status = Finished; 
         printf("Win\n"); 
         return True; 
     }     
    if(verify_solution(solution, position->line, position->column) == False){  
         // solution don't  have this cell  
         
         mark_position_solution(solution, position->line, position->column);  

        // down up 
        if(verify_position(maze,position->line-1,position->column,keys)){ 
            #if DEBUG 
                printf("Up\n"); 
            #endif 
            position->line -=1;  
            *status = True;  
            if(initStudent(maze,line,column,keys,position,status,solution)) return True;  
        }    
        // down up
        if(verify_position(maze,position->line+1, position->column,keys)){  
            if(position->line + 1 <= line){    
                #if DEBUG
                    printf("Down\n");
                #endif
                *status = True;  
                position->line +=1;  
                if(initStudent(maze,line,column,keys,position,status,solution)) return True;
            }
        }  
        // try to right 
        if(verify_position(maze,position->line, position->column+1, keys)){  
            if(position->column+1 < column){ 
                #if DEBUG 
                    printf("Right\n"); 
                #endif
                *status = True;     
                position->column += 1;    
                if(initStudent(maze,line,column,keys,position,status,solution)) return True; 
            }
        }   
        // try to left 
        if(verify_position(maze,position->line, position->column-1, keys)){  
            if(position->column-1 >= 0){ 
                #if DEBUG 
                    printf("Left\n");
                #endif
                *status = True;     
                position->column -= 1;
                if(initStudent(maze,line,column,keys,position,status,solution)) return True;
            }
        }  
        markOFF_position_solution(solution, position->line, position->column);  
        return False; 
     } 
    return False; 
     } 




/*-----------------------------------------------------------------------------------------------*/
void show_position(int line, int column){ 
    printf("Line  |   Column\n");
    printf("  %d       %d   \n",line, column); 
    printf("-------------------\n");

} 
/*-----------------------------------------------------------------------------------------------*/
int verify_position(int **maze, int line, int column,int *keys){ 
        if(maze[line][column] == 0 || maze[line][column] == 1){ 
            #if DEBUG  
                printf("free cell\n"); 
            #endif 
            return True; 
         } 
         if(maze[line][column] == 2){   
            #if DEBUG  
                printf("wall cell\n"); 
            #endif
            return False; 
         } 
         if(maze[line][column]== 3){ 
            #if DEBUG  
                printf("door cell\n"); 
            #endif 
             if(*keys>= 1) {  
                keys -=1;   
                return True;  
             }  
             else return False;  
             
         } 
         return False;  
} 
/*-------------------------------------------------------------------------------------------------------*/  
int markOFF_position_solution(int **solution, int line, int column){ 
    #if DEBUG 
        printf("Mark off position\n"); 
    #endif
    solution[line][column] = 0 ;  
    return True;   
}
/*-------------------------------------------------------------------------------------------------------*/  

int mark_position_solution(int  **solution, int line, int column){ 
    #if DEBUG 
        printf("Mark position\n"); 
    #endif
    solution[line][column] = 1 ;  
    return True;  
}
/*-------------------------------------------------------------------------------------------------------*/  
int verify_solution(int **solution, int line, int column){ 
    #if DEBUG 
        printf("Verify position in solution\n"); 
    #endif
    if(solution[line][column] == 1) return True ; 
    
    return False;  
}   
/*-------------------------------------------------------------------------------------------------------*/  
void show_solution_maze(int **solution, int line, int column){  
    printf("----------------------------------------\n");
    for(int i = 0; i < line; i++){
        for (int j = 0; j < column; j++){
            printf(" %d ",solution[i][j]);     
        } 
    printf("\n");
    } 
     
} 
/*-------------------------------------------------------------------------------------------------------*/  

void initBacktrackingMaze(int **maze, int line, int column, int *keys){

    MazePosition *initialPosition = findPosition(maze, line , column );  
    int pre_status = False;  
    int **sol = initSolution(line,column); 
    initStudent(maze, line, column, keys,initialPosition,&pre_status,sol);     
    show_solution_maze(sol, line , column); 

}

