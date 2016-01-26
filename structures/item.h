#ifndef ITEM_H
#define ITEM_H

struct s_item{
    unsigned int id;
    int a;
    int c;
    char bestsol; /* '0' unselected, '1' selected, '?' undefined */
};
typedef struct s_item item;

char verbose; /* 'v' for verbose */

char integerProfit(int n, item * it);
void displayOptimalSolution(int n, item * it);
void displayData(int n, int b, item *it);
void displaySol(int n, int b, item *it, char *x, double objx);



#endif