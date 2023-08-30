#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "sll.h"

typedef struct DfsVertex_ {
    unsigned char donnee;
    char name[6];
    VertexColor couleur;
} DfsVertex;

int dfs_main( Graph *graphe, AdjList *liste_adj, List *ordonne );
int dfs(Graph *graphe, List *ordonne );
int graph_corresp( const void *cle1, const void *cle2 );

int main( void ) 
{
    Graph courses; 
    List toposort;
    graph_init( &courses, graph_corresp, free );
    DfsVertex course[7];
    for( int i = 0; i < 7; i++ ) {
        course[i].couleur = blanc;
        course[i].donnee = i;
        graph_ins_vertex( &courses, &(course[i]) );
    }
    sprintf((course[0].name), "CS100");
    sprintf((course[1].name), "CS200");
    sprintf((course[2].name), "CS300");
    sprintf((course[3].name), "MA100");
    sprintf((course[4].name), "MA200");
    sprintf((course[5].name), "MA300");
    sprintf((course[6].name), "CS150");

    graph_ins_edge( &courses, &(course[0]), &(course[1]) );    
    graph_ins_edge( &courses, &(course[1]), &(course[2]) );
    graph_ins_edge( &courses, &(course[2]), &(course[5]) );
    graph_ins_edge( &courses, &(course[3]), &(course[2]) );
    graph_ins_edge( &courses, &(course[3]), &(course[4]) );
    graph_ins_edge( &courses, &(course[4]), &(course[5]) ); 

    dfs( &courses, &toposort );

    printf("Topological sort of the courses :\r\n");
    for( ListElmt *element = list_head(&toposort); element != NULL; element = list_next(element) ) {
        DfsVertex *vertex = (DfsVertex *)(element->donnee);
        printf("Course %d, %.5s\r\n", (vertex->donnee), (vertex->name) );
    }

    return 0;
}

int dfs_main( Graph *graphe, AdjList *liste_adj, List *ordonne )
{
    AdjList *liste_adj_clr;
    DfsVertex *sommet_clr, *sommet_adj;
    ListElmt *membre;

    ((DfsVertex *)liste_adj->sommet)->couleur = gris;
    for( membre = list_head(&liste_adj->adjacent); membre != NULL; membre = list_next(membre) ) {
        sommet_adj = list_data( membre );
        if( graph_adjlist(graphe, sommet_adj, &liste_adj_clr) != 0 ) {
            return -1;
        }
        sommet_clr = liste_adj_clr->sommet;
        if( sommet_clr->couleur == blanc ) {
            if( dfs_main( graphe, liste_adj_clr, ordonne ) != 0 ) {
                return -1;
            }
        }
    }

    ((DfsVertex *)liste_adj->sommet)->couleur = noir;
    if( list_ins_next( ordonne, NULL, (DfsVertex *)liste_adj->sommet) != 0 ) {
        return -1;
    }
    return 0;
}

int dfs(Graph *graphe, List *ordonne )
{
    DfsVertex *sommet;
    ListElmt  *element;

    for( element = list_head( &graph_adjlists(graphe) ); element != NULL; element = list_next(element) ) {
        sommet = ((AdjList *)list_data(element))->sommet;
        sommet->couleur = blanc;
    }

    list_init( ordonne, NULL );
    for( element = list_head( &graph_adjlists(graphe) ); element != NULL; element = list_next(element) ) {
        sommet = ((AdjList*)list_data(element))->sommet;
        if( sommet->couleur == blanc ) {
            if( dfs_main( graphe, (AdjList*)list_data(element), ordonne ) != 0 ) {
                list_destroy( ordonne );
                return -1;
            }
        }
    }
    return 0;
}

int graph_corresp( const void *cle1, const void *cle2 )
{
    unsigned char dataNode1 = ((DfsVertex*)cle1)->donnee;
    unsigned char dataNode2 = ((DfsVertex*)cle2)->donnee;
    if( dataNode1 == dataNode2 ) {
        return 1;
    } else {
        return 0;
    }
}