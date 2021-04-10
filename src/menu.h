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


typedef enum { F, T } boolean;

void menu ();
void loadFile (char *file, FILE *input); 
void montaLabirinto(FILE *input); 
void liberaLabirinto(int **matrizLab, int linha); 