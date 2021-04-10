#include "menu.h"



void menu (){
    
    FILE *input;
    int choice=0;
    char file[30];
    char extension[10] = ".txt";
    boolean loaded; 
    loaded=F; 
    int **matrizLab; 
    
    do{
        system("cls"); 
        printf("\n--- STUDENT MAZZE RUNNER ---\n"); 
        printf("\t Pick an option: \n");   
        printf("\t 1 - Load new file. \n");
        printf("\t 2 - Solve maze and show results. \n");
        printf("\t\n Anything else to QUIT.  \n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            system("cls");            
            printf("\n\t Please, input file name: \n");
            scanf("%s",file);
            strcat(file,extension);            
            input = fopen(file,"r");
            loadFile(file, input);
            loaded = T;
            printf("\n%d",loaded);
            break;
            

        case 2:
            system("cls");
            printf("\n%d",loaded);
            if (loaded){

                //CODIGO BACKTRACKING 
                //****************************************************************************
                void initBacktrackingMaze(int **maze, int line, int column, int *keys);  
                
                //****************************************************************************
                break;   
            }
            else{
                printf("\n\t Please, first load a valid file \n");
                printf(" Press anything to continue... \n");
                system("pause");
                break;
            }
           
            

        default:
            break;
        }
        
    }while (choice == 1 || choice==2);   
             
}

void loadFile (char *file, FILE *input){       

        //Verifica se arquivo é valido
    if (input == NULL){
        printf("Cannot open requested file!\n");
        return;
    }
    else{
        printf("File Openned!\n");
    }
    montaLabirinto(input);
             
}

void montaLabirinto(FILE *entrada, int **matrizLab){ //adicionar parametros
    int linha, coluna, qtdChave;           
        //Leitura dados labirinto
    fscanf(entrada,"%d %d %d",&linha,&coluna,&qtdChave);

        // aloca um vetor para linhas
    matrizLab = malloc (linha * sizeof (int*)) ;

        // aloca cada uma das linhas (vetores de COL inteiros)
    for (int i=0; i < linha; i++)
        matrizLab[i] = malloc (coluna * sizeof (int)) ;

    while (!feof(entrada)){
        // percorre a matriz
        for (int i=0; i < linha; i++){
            for (int j=0; j < coluna; j++)
                fscanf(entrada, "%d",&matrizLab[i][j]); // acesso com sintaxe mais simples
        }
    }  
     
    
    
    //liberaLabirinto(matrizLab,linha);   
   
    // code end 
    
}

void liberaLabirinto(int **matrizLab, int linha){     
            // libera a memória da matriz
    for (int i=0; i < linha; i++){
        free (matrizLab[i]) ;
    }
    free (matrizLab) ;
    getchar();
} 