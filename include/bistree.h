#ifndef BISTREE_H
#define BISTREE_H
#include "bitree.h"

#define AVL_VERS_G      1
#define AVL_EQUILIBRE   0
#define AVL_VERS_D     -1

typedef struct AvlNode_ {
    void *donnee;
    int cache;
    int facteur;
} AvlNode;

typedef BiTree BisTree;

void bistree_init(
    BisTree *arbre,
    int (*compare) (const void *cle1, const void *cle2),
    void (*detruire) (void *donnee)
);

void bistree_destroy( BisTree *arbre );

int bistree_insert( BisTree *arbre, const void *donnee );

int bistree_remove( BisTree *arbre, const void *donnee );

int bistree_lookup( BisTree *arbre, void **donnee );

#define bistree_size(arbre) ((arbre)->taille)

#endif 