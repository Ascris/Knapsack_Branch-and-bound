#ifndef QUEUE_H
#define QUEUE_H

#include "./item.h"
#include "./tree.h"

struct s_queue{
    struct s_node * ptrnode;
    struct s_queue * prev;
    struct s_queue * next;
};
typedef struct s_queue * QUEUE;

char verbose; /* 'v' for verbose */

void deleteNodeQueue(QUEUE *queue, QUEUE q);
void displayQueue(QUEUE q);
int sizeQueue(QUEUE q);
void addToQueue(QUEUE *queue, TREE t);
void prune(QUEUE *q, double * bestobj, char intdata);
void createNode(int n, int b, item *it, char intdata, char *x, char *constraint, TREE *newnode, TREE pred, int var_id, char sign, int rhs, double *bestobj, QUEUE *queue, unsigned int *nbnode);


#endif