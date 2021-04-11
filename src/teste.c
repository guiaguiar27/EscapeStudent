#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int main(void) { 
    int line , column, keys; 
    char EntireLine[128];  
    char *source;  
    int i, j; 
    FILE *fp = fopen("/Users/Macbook/Documents/EscapeStudent/src/maze4339.txt", "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    fscanf(fp,"%d %d %d",&line, &column,&keys);  
    printf("%d %d %d \n",line, column,keys); 
      
    int ** MatrixLab = (int**)malloc(line*sizeof(int*)) ; 
    line +=1 ; 
    for(i=0; i < line ; i++)
         MatrixLab[i] = (int*)malloc(column*sizeof(int)) ; 
    
   
   
    i = 0;  
    while(fgets(EntireLine, sizeof(EntireLine), fp) != NULL) { 
        
        source = EntireLine; 
        j = 0 ; 
        while ( *source!= '\0' ) {
            if(i > 0 && i <= line && j <= column){ 
                MatrixLab[i][j] = *source - '0'; 
                }               
            source++ ; // move p to point to next position
            j++;  

        } 
        i++; 
    } 
#if DEBUG 
    for(i = 1; i < line; i++){
        for ( j = 0; j < column; j++){
            printf("%d",MatrixLab[i][j]);     
        } 
        printf("\n");
    } 
#endif 

    fclose(fp);
}