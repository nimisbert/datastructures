#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "sll.h"

typedef struct BfsVertex_ {
    unsigned char donnee;
    VertexColor couleur;
    int         hops;
} BfsVertex;

int bfs( Graph *graphe, BfsVertex *debut, List *hops );
int graph_corresp( const void *cle1, const void *cle2 );

int main( void ) 
{
    int ret;
    Graph network;
    List hops;
    graph_init( &network, graph_corresp, free );
    BfsVertex noeuds[6];
    // Init Vertex & insert in Graph
    for( int i = 0; i < 6; i++) {
        noeuds[i].couleur = blanc;
        noeuds[i].hops = 0;
        noeuds[i].donnee = i;
        ret = graph_ins_vertex( &network, &(noeuds[i]) );
    }
    ret = graph_ins_edge( &network, &(noeuds[0]), &(noeuds[1]) );
    ret = graph_ins_edge( &network, &(noeuds[0]), &(noeuds[2]) );
    ret = graph_ins_edge( &network, &(noeuds[1]), &(noeuds[2]) );
    ret = graph_ins_edge( &network, &(noeuds[2]), &(noeuds[4]) );
    ret = graph_ins_edge( &network, &(noeuds[1]), &(noeuds[3]) );
    ret = graph_ins_edge( &network, &(noeuds[3]), &(noeuds[4]) );
    ret = graph_ins_edge( &network, &(noeuds[4]), &(noeuds[5]) );

    bfs( &network, &(noeuds[0]), &hops );

    ListElmt *element;
    for( element = list_head(&hops); element != NULL; element = list_next(element) ) {
        BfsVertex *vertex = (BfsVertex *)(element->donnee);
        printf("%d hops from 1 to %d\r\n", vertex->hops, vertex->donnee+1 );
    }
//    graph_destroy( &network );
    return 0;
}

int bfs( Graph *graphe, BfsVertex *debut, List *hops )
{
    Queue file;
    AdjList *liste_adj, *liste_adj_clr;
    BfsVertex *sommet_clr, *sommet_adj;
    ListElmt *element, *membre;

    for( element = list_head(&graph_adjlists(graphe)); element != NULL; element = list_next(element) ) {
        sommet_clr = ((AdjList*)list_data(element))->sommet;
        if( graphe->corresp(sommet_clr, debut) ) {
            sommet_clr->couleur = gris;
            sommet_clr->hops = 0;
        } else {
            sommet_clr->couleur = blanc;
            sommet_clr->hops = -1;
        }
    }

    queue_init( &file, NULL );
    if( graph_adjlist( graphe, debut, &liste_adj_clr) != 0 ) {
        queue_destroy(&file);
        return -1;
    }

    if( queue_enqueue(&file, liste_adj_clr) != 0 ) {
        queue_destroy(&file);
        return -1;
    }

    while( queue_size(&file) > 0 ) {
        liste_adj = queue_peek(&file);
        for( membre = list_head(&liste_adj->adjacent); membre != NULL; membre = list_next(membre) ) {
            sommet_adj = list_data(membre);
            if( graph_adjlist( graphe, sommet_adj, &liste_adj_clr) != 0 ) {
                queue_destroy(&file);
                return -1;
            }
            sommet_clr = liste_adj_clr->sommet;
            if( sommet_clr->couleur == blanc ) {
                sommet_clr->couleur = gris;
                sommet_clr->hops = ((BfsVertex *)liste_adj->sommet)->hops+1;
                if( queue_enqueue(&file, liste_adj_clr) != 0 ) {
                    queue_destroy(&file);
                    return -1;
                }
            }
        }
        if( queue_dequeue(&file, (void**)&liste_adj) == 0 ) {
            ((BfsVertex *)liste_adj->sommet)->couleur = noir;
        } else {
            queue_destroy(&file);
            return -1;
        }
    }
    queue_destroy( &file );
    list_init(hops, NULL);
    for( element = list_head(&graph_adjlists(graphe)); element != NULL; element = list_next(element) ) {
        sommet_clr = ((AdjList *)list_data(element))->sommet;
        if( sommet_clr->hops != -1 ) {
            if( list_ins_next(hops, list_tail(hops), sommet_clr) != 0 ) {
                list_destroy(hops);
                return -1;
            }
        }
    }
    return 0;
}

int graph_corresp( const void *cle1, const void *cle2 )
{
    unsigned char dataNode1 = ((BfsVertex*)cle1)->donnee;
    unsigned char dataNode2 = ((BfsVertex*)cle2)->donnee;
    if( dataNode1 == dataNode2 ) {
        return 1;
    } else {
        return 0;
    }
}