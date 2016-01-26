#ifndef TREE_H
#define TREE_H

#include "./item.h"

struct s_node{
    int var_id;  /* local constraint: x[var_ir] sign rhs */
    char sign;   /* local constraint: x[var_ir] sign rhs */
    int rhs;     /* local constraint: x[var_ir] sign rhs */
    char status; /* 'n' new (=unsolved), 'f' fractional, 'i' integer 'u' unfeasible */
    double obj;  /* Objective value of the corresponding node */
    int var_frac;/* index of the fractional item (vaiable) is status == 'f' */ 
    struct s_node *pred;
    struct s_node *suc0;
    struct s_node *suc1;
};
typedef struct s_node * TREE;

char verbose; /* 'v' for verbose */

/*********************************************************/
/*                    deleteNodeTree                     */
/*********************************************************/
/* Deletes node at address *tree as well as all the      */
/* successors of that node in the arborescence.          */
/* Also updates suc0 or suc1 in its parent node by       */
/* setting it to NULL. Finally, memory is freed and      */
/* *tree is set to NULL                                  */
/*********************************************************/
void deleteNodeTree(TREE *tree);

/*********************************************************/
/*                      displayNode                      */
/*********************************************************/
void displayNode(TREE t);

/*********************************************************/
/*                      displayTree                      */
/*********************************************************/
void displayTree(TREE t);

/*********************************************************/
/*                  generateConstraint                   */
/*********************************************************/
/* returns an already dimensioned array constraints      */
/* by backtraking up to the root node                    */
/* p is a pointer to the current node                    */
/*********************************************************/
void generateConstraint(int n, TREE p, char *constraint);

#endif