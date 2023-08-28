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

int heap_insert( Heap *tas, const void *donnee ) 
{
    void *temp;
    int ipos, ppos;
    if( (temp = (void**)realloc(tas->arbre, (heap_size(tas)+1)*sizeof(void*))) == NULL ) {
        return -1;
    } else {
        tas->arbre = temp;
    }
    tas->arbre[heap_size(tas)] = (void *)donnee;
    ipos = heap_size(tas);
    ppos = heap_parent(ipos);
    while( ipos > 0 && tas->compare(tas->arbre[ppos], tas->arbre[ipos]) < 0 ) {
        temp = tas->arbre[ppos];
        tas->arbre[ppos] = tas->arbre[ipos];
        tas->arbre[ipos] = temp;
        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    tas->taille++;
    return 0;
}

int heap_extract( Heap *tas, void **donnee ) 
{
    void *sauve, *temp;
    int ipos, lpos, rpos, mpos;
    if( heap_size(tas) == 0 ) {
        return -1;
    }
    *donnee = tas->arbre[0];
    sauve = tas->arbre[heap_size(tas)-1];
    if( heap_size(tas)-1 > 0 ) {
        if( (temp = (void**)realloc(tas->arbre, (heap_size(tas)-1)*sizeof(void*))) == NULL ) {
            return -1;
        } else {
            tas->arbre = temp;
        }
        tas->taille--;
    } else {
        free( tas->arbre );
        tas->arbre = NULL;
        tas->taille = 0;
        return 0;
    }
    tas->arbre[0] = sauve;
    ipos = 0;
    lpos = heap_left( ipos );
    rpos = heap_right( ipos );
    while(1) {
        lpos = heap_left( ipos );
        rpos = heap_right( ipos );
        if( lpos < heap_size(tas) && tas->compare(tas->arbre[lpos], tas->arbre[ipos]) > 0 ) {
            mpos = lpos;
        } else {
            mpos = ipos;
        }
        if( rpos < heap_size(tas) && tas->compare(tas->arbre[lpos], tas->arbre[ipos]) > 0 ) {
            mpos = lpos;
        } else {
            mpos = ipos;
        }
        if( mpos == ipos ) {
            break;
        } else {
            temp = tas->arbre[mpos];
            tas->arbre[mpos] = tas->arbre[ipos];
            tas->arbre[ipos] = temp;
            ipos = mpos;
        }
    }
    return 0;
}