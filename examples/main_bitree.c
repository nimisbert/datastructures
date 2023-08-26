/* OREILLY : Mastering algorithm with C, 2004
 * Author  : Kyle Loudon
 * Notes   :
 * Recopie personelle des codes du livre lors de sa lecture
 * Exemple page 198
 */
#include <stdio.h>  // printf()
#include <stdint.h> // uint8_t, int8_t
#include <string.h> // strtok()
#include <stdlib.h> // atof()
#include "bitree.h"
#include "sll.h"

#define Ncalc 50
typedef struct calcElement_ {
    int8_t isOperand; // -1 error ; 0 operator ; 1 operand
    char   operator;
    double operand; 
} calcElmt_t;

// ToDo
int8_t calc_string_to_list ( char *tableIn, calcElmt_t *tableOut, uint8_t size );

int8_t calc_string_to_tree ( char *tableIn ); 
int8_t calc_preorder_list_to_tree ();
int8_t calc_preorder_tree_to_list ();
int8_t calc_preorder_solve_from_list ();
int8_t calc_preorder_solve_from_tree ();

int main(void)
{
// Init
    char example0Str[Ncalc] = "* / - 74 10 32 + 23 17\0";
    printf("Solving prefix representation of : %s\r\n", example0Str);
    calcElmt_t example0Elmt[Ncalc];
// Building the Tree :
    calc_string_to_list( example0Str, example0Elmt, Ncalc );  
    return 0;
}

int8_t calc_string_to_list( char *tableIn, calcElmt_t *tableOut, uint8_t size )
{
    int8_t i = 0;
    char *tableElmt;
    tableElmt = strtok( tableIn, " ");
    while( (tableElmt != NULL) ) {
        calcElmt_t temp = {-1, 0x00, 0.0};
        switch( (char)*tableElmt ) {
            case '+':
                temp.isOperand = 0;
                temp.operator = 0x2b;
                break;
            case '-':
                temp.isOperand = 0;
                temp.operator = 0x2d;
                break;
            case '*':
                temp.isOperand = 0;
                temp.operator  = 0x2a;
                break;
            default:
                temp.isOperand = 1;
                temp.operand = atof(tableElmt);
                break;
        }
        tableElmt = strtok ( NULL, " " );
        tableOut[i] = temp;
        i++;
    }
    return 0;
}