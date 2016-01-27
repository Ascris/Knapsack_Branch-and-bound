#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <stdio.h>

#include "../structures/item.h"
#include "../structures/queue.h"
#include "../structures/tree.h"

typedef char boolean;

typedef item* tab_items;

char verbose; /* 'v' for verbose */


void createNode(int n, int b, item *it, char intdata, char *x, char *constraint, TREE *newnode, TREE pred, int var_id, char sign, int rhs, double *bestobj, QUEUE *queue, unsigned int *nbnode);

/**
 */
boolean read_first_line(FILE* file, int* items_nb, int* capacity_nb);

/**
 */
tab_items init_items(FILE* file, int items_nb);

/*********************************************************/
/*                     loadInstance                      */
/*********************************************************/
/* This function opens file *filename, reads *n, the     */
/* number of items, *b the knapsack capacity, and        */
/* allocates memory for *it, an array of *n item data    */
/* structures.                                           */
/*********************************************************/
void loadInstance(char* filename, int *n, int *b, item **it);

/*********************************************************/
/*                       comp_struct                     */
/*********************************************************/
// TODO FLORIAN : à voir si on garde le static
int comp_struct(const void* p1, const void* p2);

/*********************************************************/
/*                   solveRelaxation                     */
/*********************************************************/
/*                                                       */
/* The items in it[] are expected to be sorted by        */
/* decreasing utility BEFORE calling solveRelaxation     */
/* this function returns 'u' if problem is unfeasible    */
/*                       'i' if solution is integer      */
/*                       'f' if it is fractional         */
/* In the last case only, frac_item contains the index   */
/* of the item in the sorted list (not the id), that is  */
/* partially selected.                                   */
/* Input variables:                                      */
/* n is the number of items                              */
/* b is the knapsack capacity                            */
/* it is an array of items                               */
/* constraint is an array of n char, where constraint[j] */
/* is '1' if item j (in the sorted list) has to be       */
/* selected, '0' is not.                                 */
/* Output variables:                                     */
/* x is an array of n char, where x[j] is '1' if item j  */
/* is selected, '0' otherwise                            */
/* objx is a pointeur to a double containing the         */
/* objective value of solution x.                        */
/* frac_item is a pointeur to the item that is only      */
/* partially inserted in the knapsack, *frac_item = -1   */
/* if the solution is feasible (no fractional items)     */
/*********************************************************/
char solveRelaxation(int n, int b, item *it, char *constraint, char *x, double *objx, int *frac_item);

/*********************************************************/
/*                        BB                             */
/*********************************************************/
void BB(int n, int b, item *it, double *bestobj);

#endif
