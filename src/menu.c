#include "menu.h" 
#include "Backtracking.h"



void menu (){
    int choice=0;
    char file[30]; 
    char FileWithPath[35] = "../EscapeStudent/data/";
    char extension[10] = ".txt";
    boolean loaded; 
    loaded=F; 
    int **matrixLab, line , columns ,keys; 
    
    do{
        printf("\n--- STUDENT MAZZE RUNNER ---\n"); 
        printf("Pick an option: \n");   
        printf("1 - Load new file. \n");
        printf("2 - Solve maze and show results. \n");
        printf("\n Anything else to QUIT.\n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("\nPlease, input file name: \n");
            scanf("%s",file);
            strcat(file,extension); 
            strcat(FileWithPath,file); 
            matrixLab = loadFile(FileWithPath,&line,&columns,&keys);     
            if(matrixLab != NULL)    
                loaded = T;
            
            #if DEBUG
                printf("%d\n",loaded);
                printf("%s\n",file);  
            #endif 
            //show_maze(matrixLab,line,columns);
                    
            break;
            

        case 2: 
            #if DEBUG 
                printf("%d\n",loaded);
            #endif 
            if (loaded){

                initBacktrackingMaze(matrixLab,line,columns,&keys);  
                 break;   
            }
            else{
                printf("\nPlease, first load a valid file \n");
                printf(" Press anything to continue... \n");
                break;
            }

        default:
            break;
        }
    }while (choice == 1 || choice==2); 
             
}
int **loadFile(char *file, int *Pline , int *Pcolumn, int *Pkeys ){       
    int line , column, keys; 
    char EntireLine[128];  
    char *source;  
    int i, j; 
    FILE *fp = fopen(file, "r");
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
            if(i >=1  && i <= line && j <= column){ 
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
        printf("(%d)\n",i);
    } 
#endif 

    fclose(fp); 
 
     
    *Pline = line; 
    *Pcolumn =column; 
    *Pkeys = keys;
    
    return MatrixLab;            
}

void freeMaze(int **MatrixLab, int line){     
    // free matrix maze 
    for (int i=0; i < line; i++){
        free (MatrixLab[i]) ;
    }
    free (MatrixLab) ;
    getchar();
}  
void show_maze(int **matrixLab, int lines, int columns){   
    printf("\n----------------------------------------\n"); 

    for(int i = 1; i < lines; i++){
        for (int j = 0; j < columns; j++){
            printf(" %d ",matrixLab[i][j]);     
        } 
    printf("\n");
    } 
    printf("\n----------------------------------------\n");
      


}