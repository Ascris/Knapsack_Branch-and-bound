#ifndef ITEM_H
#define ITEM_H

struct s_item{
    unsigned int id;//identifier
    int a;//size
    int c;//profit
    char bestsol; /* '0' unselected, '1' selected, '?' undefined */
};
typedef struct s_item item;

char verbose; /* 'v' for verbose */

/*********************************************************/
/*                     integerProfit                     */
/*********************************************************/
char integerProfit(int n, item * it);

/*********************************************************/
/*                displayOptimalSolution                 */
/*********************************************************/
void displayOptimalSolution(int n, item * it);

/*********************************************************/
/*                      displayData                      */
/*********************************************************/
void displayData(int n, int b, item *it);

/*********************************************************/
/*                     displaySol                        */
/*********************************************************/
void displaySol(int n, int b, item *it, char *x, double objx);


#endif