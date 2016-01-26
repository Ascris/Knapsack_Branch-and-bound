#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>

#include "./structures/item.h"
#include "./structures/queue.h"
#include "./structures/tree.h"

char verbose; /* 'v' for verbose */

/*********************************************************/
/*                     loadInstance                      */
/*********************************************************/
/* This function opens file *filename, reads *n, the     */
/* number of items, *b the knapsack capacity, and        */
/* allocates memory for *it, an array of *n item data    */
/* structures.                                           */
/*********************************************************/
void loadInstance(char* filename, int *n, int *b, item **it)
{

/* TODO TO COMPLETE */

}


/*********************************************************/
/*                       comp_struct                     */
/*********************************************************/
static int comp_struct(const void* p1, const void* p2)
{

/* TODO TO COMPLETE */

} /* end of comp_struct */


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
char solveRelaxation(int n, int b, item *it, char *constraint, char *x, double *objx, int *frac_item)
{

    /* TODO TO COMPLETE */

    return '\0';

}

/*********************************************************/
/*                        BB                             */
/*********************************************************/
void BB(int n, int b, item *it, double *bestobj)
{
    char intdata; /* set to '1' if all items profits are integer */
    char *constraint; /* constraint[j] = 'F' if item j (in the index number after sorting the index by decreasing utility) is not subject to a branching constraint (free). '0' if item j is not selected, '1' if it is selected */
    char *x; /* solution returned by solveRelaxation, '0', '1', '?' */
    /* such that x[j] = '?' ie the fractional item. */
    double initial_best_obj; /* for storing *bestobj before solving an open problem, and see if its value has increased or not. If yes, we call prune() */
    TREE p, root = NULL;   /* tree node */
    QUEUE q, queue = NULL; /* queue of open problems (i.e. nodes for which */
    /* the objective value is known, and that have a fractional item)   */
    unsigned int nbTreeNodes = 0;


    constraint = (char*)calloc(n, sizeof(char));
    x = (char*)calloc(n, sizeof(char));
    if(constraint == NULL || x == NULL)
    {
	printf("\nMemory allocation problem.\nExiting...\n");
	exit(EXIT_FAILURE);
    }

    /* Setting intdata */
    intdata = integerProfit(n, it);

    /* Sorting the items by decreasing utility */
    
    /** TODO TO COMPLETE **/

    /* Branch-and-Bound starts here */

    /* creating root node */
    createNode(n, b, it, intdata, x, constraint, &root, NULL, -1, 's', -1, bestobj, &queue, &nbTreeNodes);
    //printf("\nThe queue of open problems has %d elements.", sizeQueue(queue));
    //printf("\nThe best obj is %lf", *bestobj);

    /* Here, we should decide what to do with the queue of open problems. */


    while (queue != NULL)
    {
	/* Solve the first open problem in the queue. */
	initial_best_obj = *bestobj;
	q = queue;
	createNode(n, b, it, intdata, x, constraint, &p, q->ptrnode, q->ptrnode->var_frac, '=', 0, bestobj, &queue, &nbTreeNodes);
	createNode(n, b, it, intdata, x, constraint, &p, q->ptrnode, q->ptrnode->var_frac, '=', 1, bestobj, &queue, &nbTreeNodes);
	deleteNodeQueue(&queue, q);

	/* At this point, we should check that an integer solution has not been found, because in that case, it could be advantageous to delete (from the queue and in the tree) those open problems that have a .obj value less than or equal to *bestobj */
	if(initial_best_obj < *bestobj)
	    prune(&queue, bestobj, intdata);


	/* DEBUG */
	if(verbose == 'v')
	{
	    printf("\nIn BB, this is displayTree, called for a 'root' node which address is %p.", root);
	    displayTree(root);
	    printf("\nIn BB, the size of the queue is %d", sizeQueue(queue));
	    displayQueue(queue);
	    /* DEBUG END */
	}

    } /* end while(queue != NULL) */

    printf("\nNumber of tree nodes: %u", nbTreeNodes);
    free(constraint);
    free(x);
}

