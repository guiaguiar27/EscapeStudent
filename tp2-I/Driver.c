#include "Solver.h"

int main(int argc, char *argv[]){  
    FILE *fl=NULL;  //**P change     
    fl = fopen(argv[1],"r"); //**P change 
    int lifes, line,column,i,j;   
    char EntireLine[128];   
    char *buf = malloc(sizeof(char)); 
    char *source = malloc(sizeof(char)); 


    if ( fl == NULL){//**P change 
        printf("File not found!");//**P change 
        return 1 ;//**P change 
    }//**P change 

    fscanf(fl,"%d %d %d", &line, &column, &lifes); 
    printf("%d %d %d\n",line,column,lifes); 
    int ** MatrixLab = (int **)malloc(line*sizeof(int*)) ; 
    for(i=0; i < line ; i++)
         MatrixLab[i] = (int*)malloc(column*sizeof(int)) ; 
    i = 0;  
    j = 0 ;     
    int aux; 
    while(fscanf(fl, "%s", buf) != EOF )
		{ 
            if(strcmp(buf,"F") == 0){  
                aux = 2;   
                MatrixLab[i][j] = aux; 
            } 
            else if( strcmp(buf,"I") == 0){ 
                aux = 1;
                MatrixLab[i][j] = aux;  
            }  
            else {  
                aux = atoi(buf); 
                MatrixLab[i][j] = aux;  
            }                
            j++;  
            if(j == column){ 
                i++;      
                j = 0; 
            } 
            if(i == line) break;           
		} 

    initSolver(MatrixLab, line, column, &lifes);  
    return 0 ;
}