#ifndef QUEUE_H
#define QUEUE_H

#include "./tree.h"

struct s_queue{
    struct s_node * ptrnode;
    struct s_queue * prev;
    struct s_queue * next;
};
typedef struct s_queue * QUEUE;

char verbose; /* 'v' for verbose */

/*********************************************************/
/*                    deleteNodeQueue                    */
/*********************************************************/
/* Deletes node at address q in a queue starting at      */
/* address *queue. This address can be modified if       */
/* q == *queue (so queue is passed by address)           */
/*********************************************************/
void deleteNodeQueue(QUEUE *queue, QUEUE q);

/*********************************************************/
/*                     displayQueue                      */
/*********************************************************/
void displayQueue(QUEUE q);

/*********************************************************/
/*                      sizeQueue                        */
/*********************************************************/
/* returns the number of open problems in the queue      */
/*********************************************************/
int sizeQueue(QUEUE q);

/*********************************************************/
/*                      addToQueue                       */
/*********************************************************/
void addToQueue(QUEUE *queue, TREE t);

/*********************************************************/
/*                         prune                         */
/*********************************************************/
/* This function deletes the nodes (in *q as well as in  */
/* tree) whose objective value is less than or equal to  */
/* *bestobj                                              */
/* intdata is 1 if all the costs are integer (allows to  */
/* prune at ceil(*bestobj)                               */
/*********************************************************/
void prune(QUEUE *q, double * bestobj, char intdata);


#endif