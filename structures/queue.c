#include "queue.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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


