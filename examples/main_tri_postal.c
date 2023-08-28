#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"

typedef struct Colis_ {
    int numero;
    int prioritee;
} Colis;

int get_colis( PQueue *paquets, Colis *paquet );
int put_colis( PQueue *paquets, const Colis *paquet );
int priority_colis( const void* colis1 , const void *colis2 );

int main( void )
{
    // Init 
    Colis colis_0 = { 0, 99 }, 
          colis_1 = { 1, 1  },
          colis_2 = { 2, 30 };
    PQueue triPostal;
    pqueue_init( &triPostal, priority_colis, free );
    // Empile les paquets 
    put_colis( &triPostal, &colis_0 );
    put_colis( &triPostal, &colis_1 );
    put_colis( &triPostal, &colis_2 );
    // Depile les paquets 
    Colis temp;
    get_colis( &triPostal, &temp);
    printf("Colis 0 : {%d,%d}\r\n", temp.numero, temp.prioritee);
    get_colis( &triPostal, &temp);
    printf("Colis 1 : {%d,%d}\r\n", temp.numero, temp.prioritee);
    get_colis( &triPostal, &temp);
    printf("Colis 2 : {%d,%d}\r\n", temp.numero, temp.prioritee);

    pqueue_destroy( &triPostal );
    return 0;
}

int get_colis( PQueue *paquets, Colis *paquet )
{
    Colis *donnee;
    if( pqueue_size(paquets) == 0 ) {
        return -1;
    } else {
        if( pqueue_extract(paquets,(void**)&donnee) != 0 ) {
            return -1;
        } else {
            memcpy(paquet, donnee, sizeof(Colis));
            free(donnee);
        }
    }
    return 0;
}

int put_colis( PQueue *paquets, const Colis *paquet ) 
{
    Colis *donnee;
    if( (donnee =(Colis*)malloc(sizeof(Colis))) == NULL ) {
        return -1;
    }
    memcpy( donnee, paquet, sizeof(Colis) );
    if( pqueue_insert(paquets, donnee) != 0 ) {
        return -1;
    }
    return 0;
}

int priority_colis( const void* colis1 , const void *colis2 )
{
    Colis colis_1 = *(Colis*)colis1;
    Colis colis_2 = *(Colis*)colis2;
    if( colis_1.prioritee > colis_2.prioritee ) {
        return 1;
    } else if( colis_1.prioritee < colis_2.prioritee ) {
        return -1;
    } else {
        return 0;
    }
}