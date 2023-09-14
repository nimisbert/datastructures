#ifndef SORT_H
#define SORT_H


int issort( void *donnee, int nb_elts, int taille_elt, int(*compare)(const void *cle1, const void *cle2) );

int qksort( void *donnee, int nb_elts, int taille_elt, int(*compare)(const void *cle1, const void *cle2) );

#endif