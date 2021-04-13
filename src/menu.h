/*
   *    ============= TP0 - PAA ==============  
   *    =       Cláudio Barbosa  - 3492      = 
   *    =       Guilherme Aguiar - 3496      =
   *    ======================================
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 




typedef enum { F, T } boolean;
/**   
* \brief  init the menu    
**/
void menu (); 
/**   
* \brief  load the file and fill the maze's matrix 
**/
int **loadFile(char *file, int *Pline , int *Pcolumn, int *Pkeys ); 
/**   
* \brief  show filled  matrix
**/

void show_maze(int **matrixLab, int lines, int columns); 
/**
* \brief deallocate the already used matrix
**/
void liberaLabirinto(int **matrizLab, int linha);  