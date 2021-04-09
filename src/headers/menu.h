/*
   *    ============= TP0 - PAA ==============  
   *    =       Cláudio Barbosa  - 3492      =
   *    ======================================
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define DEBUG 1 

void menu ();
void loadFile (char *file); 
void montaLabirinto(FILE *entrada); 
void liberaLabirinto(int **matrizLab, int linha); 
