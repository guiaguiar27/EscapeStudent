#include "headers\Backtracking.h"



void menu (){
    
    char choice;
    char file[30];
    char extension[30] = ".txt";
    //bool lFile = false;   
    
    do{
        printf("\n--- STUDENT MAZZE RUNNER ---\n"); 
        printf("\t Pick an option: \n");   
        printf("\t 1 - Load new file. \n");
        printf("\t 2 - Solve maze and show results. \n");
        printf("\t\n Anything else to QUIT.  \n");
        scanf("%c",&choice);

        switch (choice)
        {
        case '1':            
            printf("\t Please, input file name: \n");
            scanf("%s",file);
            strcat(file,extension);
                                                        //printf("%s", file);
            loadFile(file);
            break;
        
        default:
            break;
        }
        
    }while (choice=='1' || choice=='2');

   
             
}

void loadFile (char *file){
    FILE *entrada;    
    entrada = fopen(file,"r");

        //Verifica se arquivo é valido
    if (entrada == NULL){
        printf("Erro na abertura do arquivo.\n");
        return;
    }
    else{
        printf("Arquivo valido.\n");
    }
    montaLabirinto(entrada);
             
}

void montaLabirinto(FILE *entrada){
    int linha, coluna, qtdChave;
    int **matrizLab;        
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
     
    
    int *initialPosition = findPosition(matrizLab, linha, coluna); 
    if(initStudent(matrizLab, linha, coluna,&qtdChave,initialPosition)) printf("Venceu!") ; 

    liberaLabirinto(matrizLab,linha);
    
    fclose(entrada); 
    
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
