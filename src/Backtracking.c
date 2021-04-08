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

int  initStudent(int **maze, int line, int column,int *keys, MazePosition *position, int *status){ 
     show_position(position->line, position->column); 
     if(position->line == 0){ 
         *status = Finished; 
         printf("Win\n"); 
         return True; 
     }   

    /*11011*/ 

    // reflect about put this part inside a while loop, like the one another

     for(int j = position->column ; j < column ; j++){ 
         if(maze[position->line-1][j] == 0 || maze[position->line-1][j] == 1){ 
              
            position->line -= 1;   
            position->column = j; 
             // try to find the path here
             *status = True; 
             if(initStudent(maze,line,column,keys,position,status)) return True;  
             else {  
                 *status = False; 
                 position->line +=1 ; 
             } 
         } 
         if(maze[position->line-1][j] == 2){   
            return False; 
         } 
         if(maze[position->line-1][j] == 3){ 
             if(*keys>= 1) {  
                position->line -= 1;   
                position->column = j;   
                *status = True; 
                if(initStudent(maze,line,column,keys,position,status)) return True;  
                else { 
                    position->line +=1 ; 
                }
             } 
             else return False;  
             
         }
     } 
     while(*status == False){  
         for(int j = position->column; j >= 0 ; j--){  
            if(maze[position->line-1][j] == 0 || maze[position->line][j] == 1){ 
             position->line -= 1;  
             position->column = j;   
             // try to find the path here
             *status = True; 
             if(initStudent(maze,line,column,keys,position,status)) return True; 
             else{   
                *status = False; 
                position->line +=1 ; 
             }  
            } 
             
             
         } 
        //  if(*status == False) {   
        //      position->line+=1;  
        //      break; 
        // implement the wall and the doors. 
     } 

} 



/*-----------------------------------------------------------------------------------------------*/
void show_position(int line, int column){ 
    printf("Line  |   Column\n");
    printf("  %d       %d   \n",line, column); 
    printf("-------------------\n");

} 
/*-----------------------------------------------------------------------------------------------*/
