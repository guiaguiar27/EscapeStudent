/*
   *    ============= TP0 - PAA ==============  
   *    =       Cláudio Barbosa  - 3492      =
   *    ======================================
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>



typedef enum { F, T } boolean;

void menu (); 
int **loadFile(char *file, int *Pline , int *Pcolumn, int *Pkeys ); 
void show_maze(int **matrixLab, int lines, int columns); 
void liberaLabirinto(int **matrizLab, int linha);  