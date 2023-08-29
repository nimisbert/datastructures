#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "sll.h"

typedef struct BfsVertex_ {
    void        *donnee;
    VertexColor couleur;
    int         hops;
} BfsVertex;

int bfs( Graph *graphe, BfsVertex *debut, List *hops );

int main( void ) 
{
    return 0;
}

