#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define heap_parent(npos) ((int)(((npos)-1)/2))
#define heap_left(npos) (((npos)*2)+1)
#define heap_right(npos) (((npos)*2)+1)

void heap_init( Heap *tas, int (*compare)(const void *cle1, const void *cle2), void (*detruire)(void *donnee))
{
    tas->taille = 0;
    tas->compare = compare;
    tas->detruire = detruire;
    tas->arbre = NULL;
    return;
}

void heap_destroy( Heap *tas )
{
    int i;
    if( tas->detruire != NULL ) {
        for( i = 0; i < heap_size(tas); i++ ) {
            tas->detruire(tas->arbre[i]);
        }
    }
    free(tas->arbre);
    memset(tas, 0, sizeof(Heap));
    return;
}