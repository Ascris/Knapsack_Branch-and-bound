#include "item.h"

#include <math.h>
#include <stdio.h>

char integerProfit(int n, item * it)
{
    int j = 0;
    while(j < n)
    {
	if(it[j].c != floor(it[j].c))
	    return '0';
	j++;
    }
    return '1';
}

void displayOptimalSolution(int n, item * it)
{
    int j;
    for(j = 0; j < n; j++)
    {
	if(it[j].bestsol == '1')
	{
	    printf("\nItem %d which id is %d, size = %d and profit %d is selected.", j, it[j].id, it[j].a, it[j].c);
	}
   }

}

void displayData(int n, int b, item *it)
{
    int j;
    printf("\nLoaded data:");
    printf("\nThere are n = %d items, and the knapsack capacity is b = %d.", n, b);
    for(j = 0; j < n; j++)
	printf("\nItem %d has id %u, its size is %d and its profit is %d", j, it[j].id, it[j].a, it[j].c);
}

void displaySol(int n, int b, item *it, char *x, double objx)
{
    int j, load = 0;;
    printf("\nDisplaying a solution with objx = %lg",objx);
    for(j = 0; j < n; j++)
    {
	if(x[j] == '1')
	{
	    printf("\n  Item with id = %u, size = %d and profit = %d, selected.", it[j].id, it[j].a, it[j].c);
	    load += it[j].a;
	}
	else if(x[j] == '?')
	{
	    printf("\n  Item with id = %u, size = %d and profit = %d, PARTIALLY selected.", it[j].id, it[j].a, it[j].c);
	    load = b;
	}
    }
    printf("\nKnapsack capacity %d, solution load = %d", b, load);

}

