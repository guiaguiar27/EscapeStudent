#include <time.h>
int *findPosition(int **maze, int line, int column){ 

    int *position = (int*)malloc(2*sizeof(int)); 
     for (int i=0; i < line; i++){
         for (int j=0; j < column; j++){
            if(maze[i][j] == 0){ 
                position[0] = i; 
                position[1] = j; 
            }
         }
     }  
     return position;   
}
int initStudent(int **maze, int line, int column,int *keys, int *position){ 
     
      srand(time(NULL)); 
     int i = 0, j = 0, aux_line , aux_column, choose;  
     
     printf("Line: %d - Column: %d\n",position[0], position[1]);
   
     if(position[0] == 0) return 1; // win  

     else if(maze[position[0]][position[1]] == 2){ 
         // wall       

        // boundaries   
        if(position[0] == line - 1 ||  
           position[1] == column - 1 
        ){ 
            position[1] -= 1;  
            position[0] +=1 ;     
        } 
        else if(position[0] == line - 1 ||  
                position[1] == 0  
        ){ 
           position[1] += 1; 
           position[0] +=1; 
        } 
            position[0] +=1; 
        
        // if(explored[position[0]][position[1]] == 2) 
        
        initStudent(maze,line,column,keys,position); 
     
     } 

     else if(maze[position[0]][position[1]] == 3){ 
        if(*keys >= 1){ 
            choose = rand() % 2;  
            if(choose == 0) 
                position[choose] -=1 ;  
            else 
                position[choose] -=1 ;  
            initStudent(maze,line,column,keys,position); 
        } 
        else{ 
            position[0] +=1;  
            if(position[0] == line - 1) position[1] += 1; 
            if(position[1] == column - 1) position[1] -= 1;
        initStudent(maze,line,column,keys,position); 
        }   
    }
      

     else if(maze[position[0]][position[1]] == 1 || maze[position[0]][position[1]] == 0 ){ 
        
        position[0] -=1 ;   
        initStudent(maze,line,column,keys,position); 
     } 
    
    return 0; 

} 



/* 
choose = rand() % 2;  
        if(choose == 0) 
            position[choose] +=1 ;  
        else 
            position[choose] +=1 ;   
*/ 
