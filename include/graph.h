#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "sll.h"
#include "set.h"

typedef struct AdjList_ {
    void *sommet;
    Set adjacent;
} AdjList;

typedef struct Graph_ {
    int  nb_s;
    int  nb_a;
    int  (*corresp)(const void *cle1, const void *cle2);
    void (*detruire)(void *donnee);
    List listes_adj;
} Graph;

typedef enum VertexColor_ {
      blanc
    , gris
    , noir
} VertexColor;

void graph_init( Graph *graphe, int (*corresp)(const void *cle1, const void *cle2), void (*detruire)(void *donnee) );
void graph_destroy( Graph *graphe );

int graph_ins_vertex( Graph *graphe, const void *donnee );
int graph_ins_edge( Graph *graphe, const void *donnee1, const void *donnee2 );

int graph_rem_vertex( Graph *graphe, void **donnee );
int graph_rem_edge( Graph *graphe, void *donnee1, void **donnee2 );

int graph_adjlist( const Graph *graphe, const void *donnee, AdjList **liste_adj );
int graph_is_adjlist( const Graph *graphe, const void *donnee1, const void *donnee2 );

#define graph_adjlists(graphe) ((graphe)->listes_adj)
#define graph_vcount(graphe) ((graphe)->nb_s)
#define graph_ecount(graphe) ((graphe)->nb_a)

#endif