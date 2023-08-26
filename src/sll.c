/* OREILLY : Mastering algorithm with C, 2004
 * Author  : Kyle Loudon
 * Notes   :
 * Recopie personelle des codes du livre lors de sa lecture
 */
#include <stdlib.h>
#include <string.h>

#include "sll.h"

void list_init( List *liste, void (*detruire)(void *donnee))
{
    liste->taille = 0;
    liste->detruire = detruire;
    liste->tete = NULL;
    liste->queue = NULL;
    return;
}

void list_destroy(List *liste) {
    void *donnee;
    while( list_size(liste) > 0 ) {
        if( (list_rem_next(liste, NULL, (void **)&donnee) == 0) && (liste->detruire != NULL) ) {
            liste->detruire(donnee);
        }
    }
    memset( liste, 0, sizeof(List));
}  

int list_ins_next(List *liste, ListElmt *element, const void *donnee) {
    
    ListElmt *nouvelle_element;
    if( (nouvelle_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL ) {
        return -1;
    } 
    nouvelle_element->donnee = (void *)donnee;
    
    if(element == NULL) {
        if( list_size(liste) == 0) {
            liste->queue = nouvelle_element;
        }
        nouvelle_element->suivant = liste->tete;
        liste->tete = nouvelle_element;
    } else {
        if( element->suivant == NULL) {
            liste->queue =nouvelle_element;
        }
        nouvelle_element->suivant = element->suivant;
        element->suivant = nouvelle_element;
    }
    liste->taille++;
    return 0;
}

int list_rem_next(List *liste, ListElmt *element, void **donnee) 
{
    ListElmt *ancien_element;
    if( list_size(liste) == 0 ) {
        return -1;
    }

    if( element == NULL ) {
        *donnee = liste->tete->donnee;
        ancien_element = liste->tete;
        liste->tete = liste->tete->suivant;
        if( list_size(liste) == 1 ) {
            liste->queue = NULL;
        }
    } else {
        if( element->suivant == NULL ) {
            return -1;
        }
        *donnee = element->suivant->donnee;
        ancien_element = element->suivant;
        element->suivant = element->suivant->suivant;

        if( element->suivant == NULL ) {
            liste->queue = element;
        }
    }
    free(ancien_element);
    liste->taille--;
    return 0;
}
