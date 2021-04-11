#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h>
void main(){  
    srand(time(NULL));  
    char maze[20];     
    int index; 
    int possibilities[3] = {1,2,3};
    int value, line, column, keys,lim = 50, lim_keys = 10;  
    line = rand()%lim + 5 ;    
    column = rand()%lim + 5;  
    keys =  rand()%lim_keys + 0;      
    sprintf(maze, "maze%d%d.txt",line,column);
    printf("%s\n",maze); 
    
    FILE *file; 
    file = fopen(maze,"w");   
    char *fline; 
    if(file == NULL){ 
        printf("ERROR!\n"); 
        exit(1); 
    }   
    fprintf(file, "%d %d %d\n", line, column, keys);  
    int ZeroPosline = line ;  
    int ZeroPosColumn = rand()%column;  
    for(int i = 0; i < line; i++){ 
        for(int j = 0; j < column; j++){   
            if(i+1 == ZeroPosline && j == ZeroPosColumn){ 
                value = 0; 
                fprintf(file,"%d",value);
            } 
            else{  
                index  = rand()%3; 
                value = possibilities[index]; 
                fprintf(file,"%d",value);

            }
        } 
        fprintf(file,"\n");
    }
     

}