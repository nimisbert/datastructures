#ifndef HEAP_H
#define HEAP_H

typedef struct Heap_ {
    int  taille;
    int  (*compare)(const void *cle1, const void *cle2);
    void (*detruire)(void *donnee);
    void **arbre;
} Heap;

void heap_init      ( Heap *tas, int (*compare)(const void *cle1, const void *cle2), void (*detruire)(void *donnee) );
void heap_destroy   ( Heap *tas );
int  heap_insert    ( Heap *tas, const void *donnee );
int  heap_extract   ( Heap *tas, void **donnee );

#define heap_size(tas) ((tas)->taille)

#endif 