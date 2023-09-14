/**
 * @file qksort.c
 * @brief Quicksort
 * @author Kyle Loudon
 * @version O'REILLY, 2004
 * @date 14/09/2023
 */
#include <stdlib.h>
#include <string.h>
#include "sort.h"

static int compare_int( const void *int1, const void *int2 )
{
    if( *(const int*)int1 > *(const int*)int2 ) {
        return 1;
    } else if( *(const int*)int1 < *(const int*)int2 ) {
        return -1;
    } else {
        return 0;
    }
}

static int partition( void *donnee, int taille_elt, int i, int k, int (*compare)(const void *cle1, const void *cle2) ) 
{
    char *tab = donnee;
    void *pivot, *temp;
    int r[3];

    if( (pivot = malloc(taille_elt)) == NULL ) {
        return -1;
    }
    if( (temp = malloc(taille_elt)) == NULL ) {
        return -1;
    }
    r[0] = (rand() % (k-i+1)) + i;
    r[1] = (rand() % (k-i+1)) + i;
    r[2] = (rand() % (k-i+1)) + i;
    issort( r, 3, &tab[r[1]*taille_elt], taille_elt );
    memcpy( pivot, &tab[r[1]*taille_elt], taille_elt );
    i--;
    k++;
    while( 1 ) { // p.307

    }
    free(pivot);
    free(temp);
    return k;
}