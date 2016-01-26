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

void deleteNodeTree(TREE *tree);
void displayNode(TREE t);
void displayTree(TREE t);
void generateConstraint(int n, TREE p, char *constraint);


#endif