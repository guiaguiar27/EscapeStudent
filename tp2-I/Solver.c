#include "Solver.h"

/*-------------------------------------------------SOLVER-------------------------------------------------------------------*/
void allocate_solver(DPSolverType ** DP){ 
    *DP = (DPSolverType*)malloc(sizeof(DPSolverType)); 
    (*DP)->next = NULL;  
    
    if(*DP == NULL){  
        printf("ERROR in allocate list"); 
        exit(1);
    }     

} 

int insert_new_solution(DPSolverType **DP, position *pos){ 
    DPSolverType *Aux ; 
    int flag ;   

    while(*DP == NULL){ 
        DP = &(*DP)->next; 
    }  
    
    Aux = malloc(sizeof(DPSolverType)); 
    Aux->POS = *pos ;  
    Aux->next = NULL;  
    if(Aux != NULL) flag = True; 
    *DP = Aux;  
    return flag ; 
}   

void show_solutions(DPSolverType **DP){
    FILE *fl;                       //**P change
    fl = fopen("resultado.txt","w");        //**P change  
    while(*DP != NULL){  
        fprintf(fl,"%d %d\n",(*DP)->POS.line, (*DP)->POS.column);
        DP = &(*DP)->next;         
    } 
    fclose(fl);
}


int already_computed(position *current_position, DPSolverType *DP_solver){ 
    
    while(DP_solver != NULL){ 
        if(DP_solver->POS.line == current_position->line &&  DP_solver->POS.column == current_position->column)
            return True; 
        DP_solver = DP_solver->next ;  
    } 
    return False; 
}  

/*-------------------------------------------------POSITION-------------------------------------------------------------------*/

position *allocate_position(){ 
    position *pos =  (position*)malloc(sizeof(position));
    return pos; 
}

position *findInitialPosition(int **maze, int lines, int columns){  
    position *Initial_pos = allocate_position(); 
    for(int i = 0 ; i < lines; i++)
        for(int j = 0; j < columns; j++) 
            if(maze[i][j] == 1){ 
                Initial_pos->line = i;  
                Initial_pos->column = j; 
            }  
        
    #if DEBUG  
        printf("Initial = [%d][%d]\n",Initial_pos->line, Initial_pos->column);
    #endif
    return Initial_pos;    
} 
position *findFinalPosition(int **maze, int lines, int columns){  
    position *Final_pos =  allocate_position();
    for(int i = 0 ; i < lines; i++)
        for(int j = 0; j < columns; j++)  
            if(maze[i][j] == 2){ 
                Final_pos->line = i;  
                Final_pos->column = j;
            } 
    #if DEBUG  
        printf("Final = [%d][%d]\n",Final_pos->line, Final_pos->column);
    #endif   
    return Final_pos;    
}  

int verify_win(position *CurrentPos , position *FinalPos){ 
    if(CurrentPos->line == FinalPos->line && CurrentPos->column == FinalPos->column) return True; 
    return False; 
}  

int verify_boundaries(int lines, int columns, position *pos){ 
    
    if(pos->line < lines && pos->line >= 0 && pos->column < columns && pos->column >= 0) return True;  
    return False;   
} 

void current_position(position *pos){ 
    printf("line: %d | column: %d\n", pos->line, pos->column); 
    printf("---------------------\n");
}

// just calculate the life , don't change 
int best_position(Maze *maze , position *current_position, int life){ 
   
    int lifeToLeft, lifeToUp, next_line , next_column;   
    next_line = current_position->line - 1;  
    next_column = current_position->column; 
    lifeToUp = life + maze->Matrix_maze[next_line][next_column]; 
    
    next_line = current_position->line;  
    next_column = current_position->column-1; 
    lifeToLeft = life + maze->Matrix_maze[next_line][next_column];  

    if(lifeToLeft > lifeToUp){  
        #if DEBUG
        printf("The best way is to  LEFT\n");
        #endif // 0
        return Left;  
    }
    #if DEBUG
        printf("The best way is to  UP\n");
    #endif // 0
    
    return Up;  

}
/*-------------------------------------------------MAZE-------------------------------------------------------------------*/
Maze *allocate_maze(int **maze, int lines, int columns){  
    Maze *Mz = (Maze*)malloc(sizeof(Maze)); 
    Mz->Matrix_maze = maze; 
    Mz->Dimensions.line = lines;  
    Mz->Dimensions.column = columns;    
    return Mz; 
}   

void show_maze(Maze *maze){ 
        for(int i = 0; i < maze->Dimensions.line; i++){ 
        for(int j = 0; j < maze->Dimensions.column; j++){ 
            printf("%d\t",maze->Matrix_maze[i][j]);
        } 
        printf("\n");
    }
} 

void initSolver(int **maze, int lines, int columns, int *lifes){ 
    position *initial = findInitialPosition(maze,lines,columns);  
    position *final = findFinalPosition(maze,lines,columns);  
    DPSolverType *DP_Solver;   
    allocate_solver(&DP_Solver); 
    Maze *NewMaze = allocate_maze(maze, lines, columns);  
    // just for test
    //insert_new_solution(&DP_Solver, initial);  
    //show_solutions(&DP_Solver); 
    // CHAMAR O SOLVER  
    if(Solver(NewMaze, initial, final,DP_Solver,lifes) == True)printf("saiu!");
    show_solutions(&DP_Solver);
    /*/   
    }else{
        //fprintf(fl,"impossivel");
         while(DP_Solver != NULL){   //**P change 
            //fprintf(fl,"\n%d %d",DP_Solver->POS.line, DP_Solver->POS.column);
            //DP_Solver = DP_Solver->next;  
        }
    }*/
}   

int Solver(Maze *maze, position *CurrentPosition, position *Finalposition, DPSolverType *DP_Solver,int *lifes){ 
    
    position *Next_position = allocate_position();  
    *Next_position = *CurrentPosition;  
    int choose;    

       

    if(verify_win(CurrentPosition,Finalposition))
        return True;   
    // implementar    
    printf("Antes");
    if(already_computed(CurrentPosition, DP_Solver) == True) 
        return True; 
    printf("Depois\n");


    insert_new_solution(&DP_Solver,CurrentPosition);  
    #if DEBUG  
        show_solutions(&DP_Solver); 
    #endif
    


    if(verify_boundaries(maze->Dimensions.line,maze->Dimensions.column,CurrentPosition) == True){ 
           
        current_position(CurrentPosition);
        // up   

        // will be chosen which is the best path to follow  
    choose = best_position(maze, CurrentPosition,*lifes); 
        if(choose == Left){     
            Next_position->column -=1 ;  
             #if  DEBUG  
                printf("Next position(LEFT): %d %d\n",Next_position->line, Next_position->column);
            #endif   
            if(Solver(maze, Next_position,Finalposition, DP_Solver,lifes) == True){ 
                return True;
            } 
        } 
           
        if(choose == Up){ 
            Next_position->line -=1 ;   
            #if  DEBUG  
                printf("Next position(UP): %d %d\n",Next_position->line, Next_position->column);
            #endif  
            
            if(Solver(maze, Next_position,Finalposition, DP_Solver,lifes) == True){ 
                return True;
            }  
                 
        }
        
        // implement mark in solution structure  
        // verify death  
        if (lifes<=0) return False;         //**P change 
       
        // left 
        
       
    } 
    return False;      

} 


 