#include "Backtracking.h" 

/*------------------------------------------------------BACKTRACKING----------------------------------------------------------------------------*/
MazePosition *findPosition(int **maze, int line, int column){ 
    MazePosition *position = allocate_position(); 
     for (int i=1; i < line; i++){
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
/*----------------------------------------------------------------------------------------------------------------------------------*/
MazePosition *allocate_position(){ 
    MazePosition *Mz = (MazePosition*)malloc(sizeof(MazePosition)); 
    return Mz; 
} 
/*---------------------------------------------------------------------------------------------------------------------------------*/

int **initSolution(int line, int column){  
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

/*-------------------------------------------------------------------------------------------------------------------------------------*/

int moveStudent(int **maze, int line, int column,int *keys, MazePosition *position, int  **solution,  int *count, DoorList *Dlist, int *direction, int *mov){  
    (*count)++;   
    MazePosition *next_position = allocate_position(); 
    #if DEBUG
        printf("Called %d times\n",*count);  
    #endif  
    if(position->line == 1){ 
         mark_position_solution(solution, position->line, position->column);  
         printf("Win\n");   

        printf("---------------------------------------------------------------------------------------\n"); 
        printf("The student moved %d times and reached column %d of the first row\n",(*mov), position->column); 
        printf("---------------------------------------------------------------------------------------\n"); 
         return True; 
    }        

    

    // stop in wall 
    if(verify_position(maze,position->line,position->column,line,column) == True){  
       
        (*mov)++; 
         // solution don't  have this cell   
        
        
        if(verify_solution(solution, position->line, position-> column) == False){   
        
        
        // at this point  i have  already guaranted that this cell is free 
         
            
            mark_position_solution(solution,position->line, position->column);   
            show_position(position->line, position->column);    
        
            #if DEBUG 
                show_direction(direction);
            #endif  
            //show_position(position->line, position->column);    
        
            //go  up     
            
            if(Move_through_door(maze,position->line,position->column,keys,Dlist) == True){
                next_position->line = position->line - 1;  
                next_position->column = position->column;  
                *direction = U; 
                if(moveStudent(maze,line,column,keys,next_position,solution,count,Dlist,direction,mov) == True) return True;  
            }
            // go down     

            if(Move_through_door(maze,position->line,position->column,keys,Dlist) == True){
                next_position->line = position->line + 1;  
                next_position->column = position->column; 
                *direction = D; 
                if(moveStudent(maze,line,column,keys,next_position,solution,count,Dlist,direction,mov) == True) return True;
            }
            // try to right 
            if(Move_through_door(maze,position->line,position->column,keys,Dlist) == True){ 
                next_position->line = position->line;  
                next_position->column = position->column +1; 
                *direction = R;     
                if(moveStudent(maze,line,column,keys,next_position,solution,count,Dlist,direction,mov) == True) return True; 
            }
            // try to left 
            if(Move_through_door(maze,position->line,position->column,keys,Dlist) == True){
                next_position->line = position->line;  
                next_position->column = position->column - 1; 
                *direction = L; 
                if(moveStudent(maze,line,column,keys,next_position, solution,count,Dlist,direction,mov) == True) return True; 
            }
            markOFF_position_solution(solution, position->line, position->column);
            show_position(position->line, position->column);
            }
        } 
     

     
    return False; 
    } 




/*--------------------------------------------------POSITION----------------------------------------------------------------*/
void show_position(int line, int column){ 
    printf("Line  |   Column\n");
    printf("  %d       %d   \n",line, column); 
    printf("-------------------\n");

}  
/*-----------------------------------------------------------------------------------------------------------------------*/

void show_direction(int *dir){ 
    if(*dir == L) printf("Left\n"); 
    else if(*dir == R) printf("Right\n"); 
    else if(*dir == U) printf("Up\n"); 
    else if(*dir == D) printf("Down\n");
    
}
/*-----------------------------------------------------------------------------------------------------------------------*/
int verify_position(int **maze, int line, int column, int Tline, int Tcolumn){   
        // inside,  the number of lines is bigger than the column 
        if(line < Tline && line >= 1 && column < Tcolumn && column >= 0){  
            if(maze[line][column] == 0 || maze[line][column] == 1 || maze[line][column] == 3){ 
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
        }            
         return False;  
 
}   
/*-----------------------------------------------------------------------------------------------------------------------*/

int Move_through_door(int **maze, int line, int column, int *keys, DoorList *Dlist){ 
    
    if(maze[line][column] == 3){  
                // key recovery must be implemented
                #if DEBUG 
                    printf("door cell\n"); 
                #endif    
                #if DEBUG_DOOR 
                    show_doors(&Dlist);  
                #endif  
                // doc 
                if(verify_door(Dlist, line, column) == True){ 
                    if(remove_door(&Dlist,line,column) == True)(*keys)++; 
                    #if DEBUG_DOOR  
                        printf("Door listed, recovery key. KEYS = %d\n",(*keys));     
                    #endif 
                    return True; 
                } 

                else{ 
                    if(*keys>= 1){   
                            insert_door(&Dlist,line,column); 
                            (*keys)--;    
                            #if DEBUG_DOOR  
                                printf("Door not listed. KEYS = %d\n",(*keys));
                            #endif
                            return True;   
                        
                    }  
                    else return False; 
                }  
                
            } 
            return True;         
}
/*-------------------------------------------------SOLUTION------------------------------------------------------*/  
int markOFF_position_solution(int **solution, int line, int column){ 
    #if DEBUG 
        printf("Mark off position\n"); 
    #endif
    solution[line][column] = 0 ;  
    return True;   
}
/*-------------------------------------------------------------------------------------------------------*/  

int mark_position_solution(int **solution, int line, int column){ 
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
    printf("\n----------------------------------------\n");
    for(int i = 1; i < line; i++){
        for (int j = 0; j < column; j++){
            printf(" %d ",solution[i][j]);     
        } 
    printf("\n");
    } 
     
}  
/*--------------------------------------------------DOOR-----------------------------------------------------*/  

void allocate_list(DoorList **d){ 
    *d = (DoorList*)malloc(sizeof(DoorList));  
    (*d)->next = NULL;  
    if(*d == NULL){ 
        printf("ERROR in door list"); 
        exit(1);
    } 
}
/*-------------------------------------------------------------------------------------------------------*/  
int verify_door(DoorList *Dl , int line , int column){  
    #if DEBUG_DOOR
            printf("DORR SEARCHED %d %d\n",line,column);
    #endif  

    while(Dl != NULL){ 
        if(Dl->line == line && Dl->column == column)  
            return True;             
        Dl = Dl->next ; 
    }
    return False; 
}
/*-------------------------------------------------------------------------------------------------------*/  
int insert_door(DoorList **dl, int line, int column){ 
   
   DoorList *new_door = malloc(sizeof(DoorList));
    int success = new_door != NULL;

    if ( success )
    {
        new_door->line = line; 
        new_door->column = column; 
        new_door->next = NULL;
        while( *dl != NULL ) dl = &( *dl )->next;

        *dl = new_door; 
    }

    return success;
}
/*-------------------------------------------------------------------------------------------------------*/  
int remove_door(DoorList **dl, int line, int column){  
    DoorList *temp = NULL; 
    while( *dl != NULL & (*dl)->line != line && (*dl)->column!= column){ 
        dl = &(*dl)->next;  
    }
    if(*dl == NULL){ 
        #if DEBUG_DOOR 
            printf("This door doesn't exists!\n"); 
        #endif  
        return False ; 
    }  

    temp = *dl;
    *dl = temp->next; 
    temp->next = NULL ; 
    free(temp); 

    return True;  

}  

/*-------------------------------------------------------------------------------------------------------*/ 
void show_doors(DoorList **DL){ 
    DoorList * current = *DL;
    printf("Show doors: \n");
    while (current != NULL) { 
        printf("DOOR %d %d\n",current->line,current->column);
        current = current->next;
    
} 
}
/*------------------------------------------------DRIVE-------------------------------------------------------*/  

void initBacktrackingMaze(int **maze, int line, int column, int *keys){
    
    printf("Lines: %d columns: %d keys: %d\n",line-1,column,*keys);
    MazePosition *initialPosition = findPosition(maze, line , column);    
    int **sol = initSolution(line,column);  
    int count = 0 ;  
    int mov = 0 ;  
    DoorList *Dl;  
    allocate_list(&Dl); 
    int dir = 0; 
    if(moveStudent(maze, line, column, keys,initialPosition,sol,&count,Dl, &dir,&mov) == False) {
        printf("---------------------------------------------------------------------------------------\n"); 
        printf("The student moved around %d times and realized that the maze has no way out.\n",mov);       
        printf("---------------------------------------------------------------------------------------\n"); 
    }
    #if ANALYSIS_MODE  

        printf("---------------------------------------------------------------------------------------\n"); 
        printf("Total recursive call was %d\n",count);  
        printf("---------------------------------------------------------------------------------------\n"); 
    #endif  


    #if DEBUG 
        show_solution_maze(sol, line , column); 
    #endif 

}

/*-------------------------------------------------------------------------------------------------------*/  
