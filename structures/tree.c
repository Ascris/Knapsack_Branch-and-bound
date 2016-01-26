#include "tree.h"

#include <stdlib.h>
#include <stdio.h>

void deleteNodeTree(TREE *tree)
{
    if(*tree == NULL) return ;
    /* Deletion of the tree leaves first */
    if ((*tree)->suc0 != NULL)
    deleteNodeTree(&(*tree)->suc0);
    if ((*tree)->suc1 != NULL)
    deleteNodeTree(&(*tree)->suc1);
    /* At this point, *tree is the address of a leaf */
    /* So its parent must be updated before *tree is deleted */
    if((*tree)->pred != NULL)
    {
	if((*tree)->rhs == 0)
	    (*tree)->pred->suc0 = NULL;
	else if((*tree)->rhs == 1)
	    (*tree)->pred->suc1 = NULL;
	else
	    printf("\nError in deleteNodeTree : (*tree)->rhs = %d while it should be 0 or 1.\n", (*tree)->rhs);
    }
    free(*tree);
    *tree = NULL;
}


void displayNode(TREE t)
{
printf("\nThis is displayNode, called for a node which address is %p.", t);
    if(t != NULL)
    {
	printf("\n  Status: '%c'   obj = %lf", t->status, t->obj);
	printf("\n  Local constraint: x[%d] %c %d", t->var_id, t->sign, t->rhs);
	printf("\n  Fractional variable: x[%d] (applicable for status='f' only)", t->var_frac);
	printf("\n  predecessor at address %p", t->pred);
	printf("\n  suc0 at address %p and suc1 at address %p", t->suc0, t->suc1);
   }
}

void displayTree(TREE t)
{
    //printf("\nThis is displayTree, called for a 'root' node which address is %p.", t);
    if(t != NULL)
    {
	if(t->suc0 != NULL)
	    displayTree(t->suc0);
	if(t->suc1 != NULL)
	    displayTree(t->suc1);
	displayNode(t);
   }
}

void generateConstraint(int n, TREE p, char *constraint)
{
    int j;
    /* Initializing the constraints to 'F' : all the items are free */
    for(j = 0; j < n; j++)
    constraint[j] = 'F';

    while(p->pred != NULL)
    {
	if(p->sign == '=')
	{
	    if(p->rhs == 0)
		constraint[p->var_id] = '0';
	    else if (p->rhs == 1)
		constraint[p->var_id] = '1';
	    else
		printf("\nUnable to update array constraint because p->rhs is neither 0, nor 1.\n");
	}
	else
	    printf("\nUnable to update array constraint because p->sign is not '='.\n");

	p = p->pred;
    }

    /* Printing the constraints at the current node */
    if(verbose == 'v')
    {
    printf("\n");
    for(j = 0; j < n; j++)
	printf("%c",constraint[j]);
   }
}