#include "queue.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*********************************************************/
/*                    deleteNodeQueue                    */
/*********************************************************/
/* Deletes node at address q in a queue starting at      */
/* address *queue. This address can be modified if       */
/* q == *queue (so queue is passed by address)           */
/*********************************************************/
void deleteNodeQueue(QUEUE *queue, QUEUE q)
{
    if(q == NULL || *queue == NULL) return;
    
    if((*queue)->next == NULL && q == *queue)
    {
	/* Deletion of a queue having a single element */
	free(q);
	*queue = NULL;
	return;
    }
    if(q == *queue)
    {
	/* Deletion of the first element of the queue having at least 2 elements */
	*queue = q->next;
	q->next->prev = *queue;
	(*queue)->prev = NULL;
	free(q);
	return ;
    }
    if(q->next == NULL)
    {
	/* Deletion of the last element of the queue having at least 2 elements */
	q->prev->next = NULL;
	free(q);
	return;
    }
    /* Deletion of an element that is neither the first one, nor the last one of the queue. */
    /* ie the queue has at least 3 elements */
    q->prev->next = q->next;
    q->next->prev = q->prev;
    free(q);
}

/*********************************************************/
/*                     displayQueue                      */
/*********************************************************/
void displayQueue(QUEUE q)
{
    printf("\nThis is displayQueue");
    while(q != NULL)
    {
	displayNode(q->ptrnode);
	q = q->next;
    }
    printf("\n**** end of displayQueue ****");
}

/*********************************************************/
/*                      sizeQueue                        */
/*********************************************************/
/* returns the number of open problems in the queue      */
/*********************************************************/
int sizeQueue(QUEUE q)
{
    int size_queue = 0;
    while(q != NULL)
    {
	q = q->next;
	size_queue++;
    }
    return size_queue;
}


/*********************************************************/
/*                      addToQueue                       */
/*********************************************************/
void addToQueue(QUEUE *queue, TREE t)
{
    QUEUE q, tmp, pred;
    q = (QUEUE)malloc(sizeof(struct s_queue));
    if(q == NULL)
    {
	printf("\nMemory allocation problem with the queue.\nEXITING.\n");exit(EXIT_FAILURE);
    }
    
    q->ptrnode = t;
    if(*queue == NULL)
    {
	/* the queue is empty, add the node as the head of the queue */
	q->prev = NULL;
	q->next = NULL;
	*queue = q;
    }
    else if(q->ptrnode->obj > (*queue)->ptrnode->obj) /* CHANGED SIGN TO > */
    {
	/* q becomes the first element of the queue */
	/* pointers settings */
	(*queue)->prev = q;
	q->prev = NULL;
	q->next = *queue;
	/* swapping q and *queue */
	tmp = q;
	q = *queue;
	*queue = tmp;
    }
    else
    {
	/* tmp browses the queue, searching for a node having an obj value */
	/* < q->ptrnode->obj if there exist one. */
	pred = NULL;
	tmp = (*queue);
	while(tmp != NULL && tmp->ptrnode->obj >= q->ptrnode->obj)
	{
	    pred = tmp;
	    tmp = tmp->next;
	}
	/* if tmp == NULL, q is the last element of the queue */
	/* otherwise, q must be inserted before tmp */
	if(tmp != NULL)
	{
	    pred->next = q;
	    q->prev = pred;
	    tmp->prev = q;
	    q->next = tmp;
	}
	else
	{
	    /* q is the last element of the queue */
	    /* pred is the current last element of the queue */
	    pred->next = q;
	    q->next = NULL;
	    q->prev = pred;
	}
   }

}


/*********************************************************/
/*                         prune                         */
/*********************************************************/
/* This function deletes the nodes (in *q as well as in  */
/* tree) whose objective value is less than or equal to  */
/* *bestobj                                              */
/* intdata is 1 if all the costs are integer (allows to  */
/* prune at ceil(*bestobj)                               */
/*********************************************************/
void prune(QUEUE *q, double * bestobj, char intdata)
{
    QUEUE tmp, qlast = *q;
    if(verbose == 'v')
	printf("\n\n\nPRUNE with *bestobj = %lf\n\n\n",*bestobj);

    if(verbose == 'v')
    {
	printf("\nBeginning of prune(), dispaying queue.");
	displayQueue(*q);
    }


    if(*q == NULL) return;
    while(qlast->next != NULL)
	qlast = qlast->next;
    /* q last is the last open problem, i.e the open problem */
    /* with the smallest objective value */


    while(qlast != NULL && (intdata=='1'?floor(qlast->ptrnode->obj):qlast->ptrnode->obj) <= *bestobj)
    {
	//printf("\nNODE %p (obj = %lf) PRUNED", qlast->ptrnode, qlast->ptrnode->obj);
	tmp = qlast -> prev;   
	deleteNodeTree(&(qlast->ptrnode));
	deleteNodeQueue(q, qlast);
	qlast = tmp;
    }
    if(verbose == 'v')
    {
	printf("\nEnd of prune(), dispaying queue.");
	displayQueue(*q);
    }
}


/*********************************************************/
/*                    createNode                         */
/*********************************************************/
void createNode(int n, int b, item *it, char intdata, char *x, char *constraint, TREE *newnode, TREE pred, int var_id, char sign, int rhs, double *bestobj, QUEUE *queue, unsigned int *nbnode)
{
    int frac_item; /* index (not the id) in array it[] of the item j */
    char status;   /* solveRelaxation status: 'i', 'u', or 'f'       */
    double objx;   /* solution value associated with solution x      */
    int j;

    *newnode = (TREE)calloc(1, sizeof(struct s_node));
    if(*newnode == NULL)
    {
    printf("\nMemory allocation problem, failing to create a tree newnode.\nExiting...\n");
    exit(EXIT_FAILURE);
    }
    (*newnode)->pred = pred;
    (*newnode)->var_id = var_id;
    (*newnode)->sign = sign;
    (*newnode)->rhs = rhs;
    (*newnode)->var_frac = -1; /* fracional variable unidentified yet */
    (*newnode)->status = 'n';

    /* Solving the node, for the purpose of determining its objective value: */
    /* (*newnode)->obj */

    generateConstraint(n, *newnode, constraint);

    status = solveRelaxation(n, b, it, constraint, x, &objx, &frac_item);
    if(verbose == 'v')
    {
	switch(status)
	{
	    case 'i': printf("\nsolveRelaxation solution is feasible (integer), with objx = %lf", objx);
	    break;
	    case 'u': printf("\nsolveRelaxation is unfeasible");
	    break;
	    case 'f': printf("\nsolveRelaxation solution is fractional with objx = %lf.\nItem %d having id %d, size %d and cost %d is used PARTIALLY in the solution, so branching is required.", objx, frac_item, it[frac_item].id, it[frac_item].a, it[frac_item].c);
	    break;
	    default: printf("\n\nUNEXPECTED CHAR VALUE RETURNED BY solveRelaxation: \"%c\"\n\n",status);
	}
    }
    (*newnode)->status = status;
    (*newnode)->obj = objx;

    //displaySol(n, b, it, x, objx);
    //char integerProfit(int n, item * it)


    /* A new node is created only if its status is 'f' and its objective is stricly larger than *bestobj */
    if(status == 'f' && *bestobj < (intdata == '1'?floor(objx):objx))
    {
	(*nbnode)++;
	(*newnode)->var_frac = frac_item;
	/* Updating the parent node too */
	if((*newnode)->pred != NULL)
	    {
	    if((*newnode)->rhs == 0)
		(*newnode)->pred->suc0 = (*newnode);
	    else if((*newnode)->rhs == 1)
		(*newnode)->pred->suc1 = (*newnode);
	    else
		{
		printf("\nError in createNode(): cannot update the parent node because the passed rhs = %d whereas it should be 0 or 1.\n", rhs);
		}
	    }
	if(verbose == 'v')
	    displayNode(*newnode);
	/* Insert the current node in the queue, at the correct location */
	addToQueue(queue, *newnode);
	//printf("\nSize of queue = %d elements", sizeQueue(*queue));
    }
    else
    {
	if(verbose == 'v')
	    printf("\nNo node creation (status is '%c')", (*newnode)->status);
	if(status == 'f')
	    {
	    if(verbose == 'v')
		printf("\nDespite its status 'f', this node is pruned because its objective value is %lf, whereas the objective value of the best feasible solution found so far is %lf.", objx, *bestobj);
	    }
	else if(status == 'u')
	    {
	    /* Delete node, update its parent too. */
	    if(pred == NULL)
		{
		/* The root node is unfeasible */
		printf("\nThis knapsack problem instance is unfeasible.");
		}
	    }
	else if(status == 'i')
	    {
	    /* Compare objx to the best available integer solution,      */
	    /* and update it if necessary. The best solution is directly */
	    /* coded in the item structure, see char bestsol.            */
	    /* Delete node, update its parent too.                       */
	    if(objx > *bestobj)
		{
		*bestobj = objx;
		for(j = 0; j < n; j++)
		    it[j].bestsol = x[j];
		}
	    }
	
	/* Updating the parent node pred, if it exists */
	if(pred != NULL)
	{
	    if(rhs == 0)
		pred->suc0 = NULL;
	    else if(rhs == 1)
		pred->suc1 = NULL;
	    else
		printf("\nError with rhs, that is %d while it should be either 0 or 1.\n", rhs);
	}
	/* Current node deletion */
	free(*newnode);
   }
}


