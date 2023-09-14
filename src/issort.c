/**
 * @file issort.c
 * @brief Sort by insertion
 * @author Kyle Loudon
 * @version O'REILLY, 2004
 * @date 14/09/2023
 */
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int issort( void *donnee, int nb_elts, int taille_elt, int(*compare)(const void *cle1, const void *cle2) )
{
    char *tab = donnee;
    void *cle;
    int i,j;
    if( (cle = (char*)malloc(taille_elt)) == NULL ) {
        return -1;
    }
    for( j = 1; j < nb_elts; j++ ) {
        memcpy( cle, &tab[j*taille_elt], taille_elt );
        i = j - 1;
        while( i >= 0 && compare(&tab[i*taille_elt], cle) > 0 ) {
            memcpy( &tab[(i+1)*taille_elt], &tab[i*taille_elt], taille_elt );
            i--;
        }
        memcpy( &tab[(i+1)*taille_elt], cle, taille_elt );
    } 
    free(cle);
    return 0;
}