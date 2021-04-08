#include "menu.h"  
#include "Backtracking.h" 


void menu (){
    FILE *entrada;    
    entrada = fopen("teste.txt","r");

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

    // for (int i=0; i < linha; i++){
    //     printf("\n");
    //     for (int j=0; j < coluna; j++){
    //         printf("%d",matrizLab[i][j]);        // acesso com sintaxe mais simples
    //     }
    // }    
    fclose(entrada);  
    
    MazePosition *initialPosition = findPosition(matrizLab, linha, coluna);  
    //MazePosition *NextPosition = allocate_position(); 
    int pre_status = False; 
    initStudent(matrizLab, linha, coluna,&qtdChave,initialPosition,&pre_status); 
    
    // code end  
    //liberaLabirinto(matrizLab,linha);  //CORRIGIR****
}

void liberaLabirinto(int **matrizLab, int linha){     
            // libera a memória da matriz
    for (int i=0; i < linha; i++){
        free (matrizLab[i]) ;
    }
    free (matrizLab) ;
    getchar();
} 
