/**
 * @file bistree.c
 * @brief Implementation of an A.V.L. binary search tree.
 * @author Kyle Loudon
 * @version Florence Leroy
 * @date 2002
 */
#include "bistree.h"
#include <stdlib.h>
#include <string.h>

static void rotate_left     ( BiTreeNode **noeud );
static void rotate_right    ( BiTreeNode **noeud );
static void destroy_left    ( BisTree *arbre, BiTreeNode *noeud );
static void destroy_right   ( BisTree *arbre, BiTreeNode *noeud );
static int  insert          ( BisTree *arbre, BiTreeNode **noeud, const void *donnee, int *equilibre );
static int  hide            ( BisTree *arbre, BiTreeNode *noeud, const void *donnee );
static int  lookup          ( BisTree *arbre, BiTreeNode *noeud, void **donnee );

static void rotate_left( BiTreeNode **noeud )
{
    BiTreeNode *gauche, *petit_fils;
    gauche = (BiTreeNode *)bitree_left(*noeud);
    if ( ((AvlNode *)bitree_data(gauche))->facteur == AVL_VERS_G ) {
        // Effectue rotation GG
        bitree_left(*noeud) = bitree_right( gauche );
        bitree_right( gauche ) = (BiTreeNode *)*noeud;
        ((AvlNode*)bitree_data(*noeud))->facteur = AVL_EQUILIBRE;
        ((AvlNode*)bitree_data(gauche))->facteur = AVL_EQUILIBRE;
        *noeud = gauche;
    } else {
        // Effectue rotation GD
        petit_fils = (BiTreeNode *)bitree_right(gauche);
        bitree_right(gauche) = bitree_left(petit_fils);
        bitree_left(petit_fils) = gauche;
        bitree_left(*noeud) = bitree_right(petit_fils);
        bitree_right(petit_fils) = *noeud;

        switch(((AvlNode *)bitree_data(*noeud))->facteur = AVL_VERS_D ) {
            case AVL_VERS_G:
                ((AvlNode*)bitree_data(*noeud))->facteur = AVL_VERS_D;
                ((AvlNode*)bitree_data(gauche))->facteur = AVL_EQUILIBRE;
                break;
            case AVL_EQUILIBRE:
                ((AvlNode*)bitree_data(*noeud))->facteur = AVL_EQUILIBRE;
                ((AvlNode*)bitree_data(gauche))->facteur = AVL_EQUILIBRE;
                break;
            case AVL_VERS_D:
                ((AvlNode*)bitree_data(*noeud))->facteur = AVL_EQUILIBRE;
                ((AvlNode*)bitree_data(gauche))->facteur = AVL_VERS_G;
                break;
            default:
                return;
                break;
        }
        ((AvlNode*)bitree_data(petit_fils))->facteur = AVL_EQUILIBRE;
        *noeud = petit_fils;
    }
    return;
}

static void rotate_right( BiTreeNode **noeud )
{
    BiTreeNode *droite, *petit_fils;
    droite = bitree_right(*noeud);
    if ( ((AvlNode *)bitree_data(droite))->facteur == AVL_VERS_D ) {
        // Effectue une rotation DD 
        bitree_right(*noeud) = bitree_left(droite);
        bitree_left(droite) = *noeud;
        ((AvlNode *)bitree_data(*noeud))->facteur = AVL_EQUILIBRE;
        ((AvlNode *)bitree_data(droite))->facteur = AVL_EQUILIBRE;
    } else {
        // Effectue une rotation DG
        petit_fils = (BiTreeNode *)bitree_left(droite);
        bitree_left(droite) = bitree_right(petit_fils);
        bitree_right(petit_fils) = (BiTreeNode *)droite;
        bitree_right(*noeud) = bitree_left(petit_fils);
        bitree_left(petit_fils) = (BiTreeNode *)*noeud;
        switch( ((AvlNode *)bitree_data(petit_fils))->facteur ) {
            case AVL_VERS_G:
                ((AvlNode *)bitree_data(*noeud))->facteur = AVL_EQUILIBRE; 
                ((AvlNode *)bitree_data(droite))->facteur = AVL_VERS_D;
                break;
            case AVL_EQUILIBRE:
                ((AvlNode *)bitree_data(*noeud))->facteur = AVL_EQUILIBRE; 
                ((AvlNode *)bitree_data(droite))->facteur = AVL_EQUILIBRE;
                break;
            case AVL_VERS_D:
                ((AvlNode *)bitree_data(*noeud))->facteur = AVL_VERS_G; 
                ((AvlNode *)bitree_data(droite))->facteur = AVL_EQUILIBRE;
                break;
            default:
                return;
                break;
        }

        ((AvlNode *)bitree_data(petit_fils))->facteur = AVL_EQUILIBRE;
        *noeud = petit_fils;
    }
    return;
}

static void destroy_left( BisTree *arbre, BiTreeNode *noeud )
{
    BiTreeNode **position;
    // Ne peut pas detruire arbre vide 
    if( bitree_size(arbre) == 0 ) {
        return;
    }
    // Determine noeud a detruire
    if( noeud == NULL ) {
        position = (BiTreeNode **)&arbre->racine;
    } else {
        position = (BiTreeNode **)&noeud->gauche;
    }
    // Detruit 
    if( *position != NULL ) {
        destroy_left( arbre, *position );
        destroy_right( arbre, *position );
        if( arbre->detruire != NULL ) {
            arbre->detruire(((AvlNode *)(*position)->donnee)->donnee);
        }
        free((*position)->donnee);
        free(*position);
        *position = NULL;
        arbre->taille--;
    }
    return;
}

static void destroy_right( BisTree *arbre, BiTreeNode *noeud )
{
    BiTreeNode **position;
    if( bitree_size(arbre) == 0 ) {
        return;
    }
    if( noeud == NULL ) {
        position = (BiTreeNode **)&arbre->racine;
    } else {
        position = (BiTreeNode **)&noeud->droite;
    }

    if( *position != NULL ) {
        destroy_left( arbre, *position );
        destroy_right( arbre, *position );
        if( arbre->detruire != NULL ) {
            arbre->detruire(((AvlNode*)(*position)->donnee)->donnee);
        }
        free((*position)->donnee);
        free(*position);
        *position = NULL;
        arbre->taille--;
    }
    return;
}

static int insert( BisTree *arbre, BiTreeNode **noeud, const void *donnee, int *equilibre ) 
{
    AvlNode *donnee_avl;
    int val_cmp, val_ret;
    if( bitree_is_eob(*noeud) ) {
        if( (donnee_avl = (AvlNode *)malloc(sizeof(AvlNode))) == NULL ) {
            return -1;
        }
        donnee_avl->facteur = AVL_EQUILIBRE;
        donnee_avl->cache = 0;
        donnee_avl->donnee = (void *)donnee;
        return bitree_ins_left( arbre, *noeud, donnee_avl );
    } else {
        val_cmp = arbre->compare(donnee, ((AvlNode *)bitree_data(*noeud))->donnee);
        if( val_cmp < 0 ) {
            if( bitree_is_eob(bitree_left(*noeud)) ) {
                if( (donnee_avl = (AvlNode *)malloc(sizeof(AvlNode))) == NULL ) {
                    return -1;
                }
                donnee_avl->facteur = AVL_EQUILIBRE;
                donnee_avl->cache = 0;
                donnee_avl->donnee = (void *)donnee;
                if( bitree_ins_left(arbre, *noeud, donnee_avl) != 0 ) {
                    return -1;
                }
                *equilibre = 0;
            } else {
                if( (val_ret = insert(arbre, (BiTreeNode **)&bitree_left(*noeud), donnee, equilibre)) != 0 ) {
                    return val_ret;
                }
            }
            if( !(*equilibre)) {
                switch(((AvlNode *)bitree_data(*noeud))->facteur) {
                    case AVL_VERS_G:
                        rotate_left(noeud);
                        *equilibre = 1;
                        break;
                    case AVL_EQUILIBRE:
                        ((AvlNode *)bitree_data(*noeud))->facteur = AVL_VERS_G;
                        break;
                    case AVL_VERS_D:
                        ((AvlNode *)bitree_data(*noeud))->facteur = AVL_EQUILIBRE;
                        *equilibre = 1;
                        break;
                    default:
                        return -1;
                        break;
                }
            }            
        } else if( val_cmp > 0 ) {
            if( bitree_is_eob(bitree_right(*noeud))) {
                if( (donnee_avl = (AvlNode *)malloc(sizeof(AvlNode))) == NULL ) {
                    return -1;
                }
                donnee_avl->facteur = AVL_EQUILIBRE;
                donnee_avl->cache = 0;
                donnee_avl->donnee = (void *)donnee;
                if( bitree_ins_right(arbre, *noeud, donnee_avl) != 0 ) {
                    return -1;
                }
                *equilibre = 0;
            } else {
                if( (val_ret = insert(arbre, (BiTreeNode **)&bitree_right(*noeud), donnee, equilibre)) != 0 ) {
                    return val_ret;
                }
            }
            if( !(*equilibre) ) {
                switch( ((AvlNode *)bitree_data(*noeud))->facteur ) {
                    case AVL_VERS_G:
                        ((AvlNode *)bitree_data(*noeud))->facteur = AVL_EQUILIBRE;
                        *equilibre = 1;
                        break;
                    case AVL_EQUILIBRE:
                        ((AvlNode *)bitree_data(*noeud))->facteur = AVL_VERS_D;
                        break;
                    case AVL_VERS_D:
                        rotate_right(noeud);
                        *equilibre = 1;
                        break;
                    default:
                        return -1;
                }
            }
        } else {
            if( !((AvlNode *)bitree_data(*noeud))->cache ) {
                return 1;
            } else {
                if( arbre->detruire != NULL ) {
                    arbre->detruire(((AvlNode *)bitree_data(*noeud))->donnee);
                }
                ((AvlNode *)bitree_data(*noeud))->donnee = (void *)donnee;
                ((AvlNode *)bitree_data(*noeud))->cache = 0;
                *equilibre = 1;
            }
        }
    }
    return 0;
}

static int hide( BisTree *arbre, BiTreeNode *noeud, const void *donnee ) 
{
    int val_cmp, val_ret;
    if( bitree_is_eob(noeud) ) {
        return -1;
    }
    val_cmp = arbre->compare( donnee, ((AvlNode *)bitree_data(noeud))->donnee );
    if( val_cmp < 0 ) {
        val_ret = hide(arbre, bitree_left(noeud), donnee);
    } else if ( val_cmp > 0 ) {
        val_ret = hide( arbre, bitree_right(noeud), donnee );
    } else {
        ((AvlNode *)bitree_data(noeud))->cache = 1;
        val_ret = 0;
    }
    return val_ret;
}

static int lookup( BisTree *arbre, BiTreeNode *noeud, void **donnee )
{
    int val_cmp, val_ret;
    if( bitree_is_eob(noeud) ) {
        return -1;
    }
    val_cmp = arbre->compare(*donnee, ((AvlNode *)bitree_data(noeud))->donnee );
    if( val_cmp < 0 ) {
        val_ret = lookup( arbre, bitree_left(noeud), donnee );
    } else if ( val_cmp > 0 ) {
        val_ret = lookup( arbre, bitree_right(noeud), donnee );
    } else {
        if( !((AvlNode *)bitree_data(noeud))->cache ) {
            *donnee = ((AvlNode *)bitree_data(noeud))->donnee;
            val_ret = 0;
        } else {
            return -1;
        }
    }
    return val_ret;
}

void bistree_init( BisTree *arbre, int (*compare)(const void *cle1, const void *cle2), void (*detruire)(void *donnee))
{
    bitree_init( arbre, detruire );
    arbre->compare = compare;
    return;
}

void bistree_destroy( BisTree *arbre )
{
    destroy_left( arbre, NULL );
    memset( arbre, 0, sizeof(BisTree) );
    return;
}

int bistree_insert( BisTree *arbre, const void *donnee ) 
{
    int equilibre = 0;
    return insert( arbre, &bitree_root(arbre), donnee, &equilibre );
}

int bistree_remove( BisTree *arbre, const void *donnee )
{
    return hide( arbre, bitree_root(arbre), donnee );
}

int bistree_lookup( BisTree *arbre, void **donnee ) 
{
    return lookup(arbre, bitree_root(arbre), donnee );
}