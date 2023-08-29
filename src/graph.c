#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "sll.h"
#include "set.h"

void graph_init( Graph *graphe, int (*corresp)(const void *cle1, const void *cle2), void (*detruire)(void *donnee) )
{
    graphe->nb_s = 0;
    graphe->nb_a = 0;
    graphe->corresp = corresp;
    graphe->detruire = detruire;
    list_init( &graphe->listes_adj, NULL );
    return;
}

void graph_destroy( Graph *graphe )
{
    AdjList *liste_adj;
    while( list_size(&graphe->listes_adj) > 0 ) {
        if( list_rem_next( &graphe->listes_adj, NULL, (void**)&liste_adj) == 0 ) {
            set_destroy( &liste_adj->adjacent );
            if( graphe->detruire != NULL ) {
                graphe->detruire( liste_adj->sommet );
            }
            free(liste_adj);
        }
    }
    list_destroy( &graphe->listes_adj );
    memset( graphe, 0, sizeof(Graph) );
    return;
}

int graph_ins_vertex( Graph *graphe, const void *donnee )
{
    ListElmt *element;
    AdjList *liste_adj;
    int val_ret;
    for( element = list_head(&graphe->listes_adj); element != NULL; element = list_next(element) ) {
        if( graphe->corresp(donnee, ((AdjList*)list_data(element))->sommet) ) {
            return 1;
        }
    }
    if( (liste_adj = (AdjList*)malloc(sizeof(AdjList))) == NULL ) {
        return -1;
    }
    liste_adj->sommet = (void*)donnee;
    set_init( &liste_adj->adjacent, graphe->corresp, NULL );
    if( (val_ret = list_ins_next( &graphe->listes_adj, list_tail(&graphe->listes_adj), liste_adj)) != 0 ) {
        return val_ret;
    }
    graphe->nb_s++;
    return 0;
}

int graph_ins_edge( Graph *graphe, const void *donnee1, const void *donnee2 ) 
{
    ListElmt *element;
    int val_ret;
    for( element = list_head(&graphe->listes_adj); element != NULL; element = list_next(element) ) {
        if( graphe->corresp(donnee2, ((AdjList*)list_data(element))->sommet)) {
            break;
        }
    }
    if( element == NULL ) {
        return -1;
    } 
    for( element = list_head(&graphe->listes_adj); element != NULL; element = list_next(element) ) {
        if( graphe->corresp(donnee1, ((AdjList*)list_data(element))->sommet) ) {
            break;
        }
    }
    if( element == NULL ) {
        return -1;
    }
    if( (val_ret = set_insert(&((AdjList*)list_data(element))->adjacent, donnee2)) != 0 ) {
        return val_ret;
    }
    graphe->nb_a++;
    return 0;
}

int graph_rem_vertex( Graph *graphe, void **donnee )
{
    ListElmt *element, *temp, *prec;
    AdjList *liste_adj;
    int trouve;
    prec = NULL;
    trouve = 0;

    for( element = list_head( &graphe->listes_adj ); element != NULL; element = list_next(element) ) {
        if( set_is_member(&((AdjList*)list_data(element))->adjacent, *donnee) ) {
            return -1;
        }
        if( graphe->corresp(*donnee, ((AdjList*)list_data(element))->sommet) ) {
            temp = element;
            trouve = 1;
        }
        if( !trouve ) {
            prec = element;
        }
    }
    if( !trouve ) {
        return -1;
    }
    if( set_size(&((AdjList*)list_data(temp))->adjacent) > 0 ) {
        return -1;
    }
    if( list_rem_next( &graphe->listes_adj, prec, (void**)&liste_adj) != 0 ) {
        return -1;
    }
    *donnee = liste_adj->sommet;
    free(liste_adj);
    graphe->nb_s--;
    return 0;
}

int graph_rem_edge( Graph *graphe, void *donnee1, void **donnee2 ) 
{
    ListElmt *element;
    for( element = list_head(&graphe->listes_adj); element != NULL; element = list_next(element) ) {
        if( graphe->corresp( donnee1, ((AdjList*)list_data(element))->sommet) ) {
            break;
        }
    }
    if( element == NULL ) {
        return -1;
    }
    if( set_remove( &((AdjList*)list_data(element))->adjacent, donnee2) != 0 ) {
        return -1;
    }
    graphe->nb_a--;
    return 0;
}

int graph_adjlist( const Graph *graphe, const void *donnee, AdjList **liste_adj )
{
    ListElmt *element, *prec;
    prec = NULL;
    for( element = list_head(&graphe->listes_adj); element != NULL; element = list_next(element) ) {
        if( graphe->corresp( donnee, ((AdjList *)list_data(element))->sommet) ) {
            break;
        }
        prec = element;
    }
    if( element == NULL ) {
        return -1;
    }
    *liste_adj = list_data(element);
    return 0;
}

int graph_is_adjacent( const Graph *graphe, const void *donnee1, const void *donnee2 ) 
{
    ListElmt *element, *prec;
    prec = NULL;
    for( element = list_head(&graphe->listes_adj); element != NULL; element = list_next(element) ) {
        if( graphe->corresp( donnee1, ((AdjList*)list_data(element))->sommet) ) {
            break;
        }
        prec = element;
    }
    if( element == NULL ) {
        return 0;
    }
    return set_is_member(&((AdjList*)list_data(element))->adjacent, donnee2 );
}