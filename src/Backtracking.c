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

int initStudent(int **maze, int line, int column,int *keys, MazePosition *position, int *status, int  **solution,  int *count, DoorList *Dlist){  
    (*count)++;  
    #if ANALYSIS_MODE
    printf("Called %d times\n",*count);  
    #endif 
    show_position(position->line, position->column); 
     
     if(position->line == 1){ 
         *status = Finished; 
         printf("Win\n"); 
         return True; 
     }     
    if(verify_solution(solution, position->line, position->column) == False){  
         // solution don't  have this cell  
         
         mark_position_solution(solution, position->line, position->column);  

        //go  down 
        if(verify_position(maze,position->line-1,position->column,keys,Dlist)){ 
            #if DEBUG 
                printf("Up\n"); 
            #endif 
            position->line -=1;  
            *status = True;  
            if(initStudent(maze,line,column,keys,position,status,solution,count,Dlist)) return True;  
        }    
        // go up
    if(position->line + 1 < line){
        if(verify_position(maze,position->line+1, position->column,keys,Dlist)){  
                
                #if DEBUG
                    printf("Down\n");
                #endif
                *status = True;  
                position->line +=1;  
                if(initStudent(maze,line,column,keys,position,status,solution,count,Dlist)) return True;
            }
        }  
        // try to right 
    if(position->column+1 < column){ 
        if(verify_position(maze,position->line, position->column+1, keys,Dlist)){  
                #if DEBUG 
                    printf("Right\n"); 
                #endif
                *status = True;     
                position->column += 1;    
                if(initStudent(maze,line,column,keys,position,status,solution,count,Dlist)) return True; 
            }
        }   
        // try to left 
    if(position->column-1 >= 0){
        if(verify_position(maze,position->line, position->column-1, keys,Dlist)){  
            
                #if DEBUG 
                    printf("Left\n");
                #endif
                *status = True;     
                position->column -= 1;
                if(initStudent(maze,line,column,keys,position,status,solution,count,Dlist)) return True;
            }
        } 
        else{ 
            printf("No way to get out! SAD\n"); 
            return False; 
        }  
        markOFF_position_solution(solution, position->line, position->column);  
        return False; 
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
int verify_position(int **maze, int line, int column, int *keys, DoorList *Dlist){ 
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
             // key recovery must be implemented
            #if DEBUG  
                printf("door cell\n"); 
            #endif   

            if(verify_door(Dlist, line, column) == True){ 
                if(remove_door(Dlist,line,column) == True)(*keys)++; 
                #if DEBUG  
                    printf("Door listed, recovery key\n"); 

                #endif
            } 
            else{ 
                if(*keys>= 1) {   
                    if(insert_door(Dlist,line,column)){   
                        (*keys)--;    
                         #if DEBUG  
                            printf("Door not listed\n");
                        #endif
                        return True;   
                    }
                }  
                else return False; 
            }  
             
         } 
         return False;  
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
    printf("\n----------------------------------------\n");
    for(int i = 0; i < line; i++){
        for (int j = 0; j < column; j++){
            printf(" %d ",solution[i][j]);     
        } 
    printf("\n");
    } 
     
}  
/*--------------------------------------------------DOOR-----------------------------------------------------*/  

DoorList *allocate_list(){ 
    DoorList *d = (DoorList*)malloc(sizeof(DoorList));  
    d->next = NULL; 
    return d; 
}
/*-------------------------------------------------------------------------------------------------------*/  
int verify_door(DoorList *D , int line , int column){  
    DoorList *current = D;  
     #if DEBUG
            printf("DORR SEARCHED %d %d\n",line,column);
    #endif 
    while(current != NULL){  
       
        if(current->line == line && current->column == column){   
            #if DEBUG
                printf("DORR %d %d\n",current->line,current->column);
            #endif 
            
            return True; 
        } 
        current = current->next;  
    } 
    return False; 
}
/*-------------------------------------------------------------------------------------------------------*/  
int insert_door(DoorList *dl, int line, int column){ 
    // insertion working  
    DoorList* current = dl;
    while (current->next != NULL) {
        current = current->next;
    }
    dl = (DoorList*)malloc(sizeof(DoorList)); 
    dl->line = line;  
    dl->column = column;  
    dl->next = NULL;    
    return 1; 
} 
/*-------------------------------------------------------------------------------------------------------*/  
int remove_door(DoorList *dl, int line, int column){ 
    DoorList *current = dl;   
    DoorList *temp = NULL; 
    while( current != NULL & current->line != line && current->column != column){ 
        current = current->next; 
    }
    if(current == NULL){ 
        #if DEBUG 
            printf("This door doesn't exists!\n"); 
        #endif  
        return False ; 
    }  

    temp = current->next;
    current->next = temp->next;
    free(temp); 

    return True;  

}

/*------------------------------------------------DRIVE-------------------------------------------------------*/  

void initBacktrackingMaze(int **maze, int line, int column, int *keys){
    
    printf("Lines: %d columns: %d keys: %d\n",line,column,*keys);
    MazePosition *initialPosition = findPosition(maze, line , column);  
    int pre_status = False;  
    int **sol = initSolution(line,column);  
    int count = 1 ;  
    DoorList *Dl = allocate_list();
    initStudent(maze, line, column, keys,initialPosition,&pre_status,sol,&count,Dl);  
    #if ANALYSIS_MODE  
        printf("Called %d times", count);
    #endif //       
    show_solution_maze(sol, line , column); 

}

/*-------------------------------------------------------------------------------------------------------*/  
