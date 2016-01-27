/*********************************************************/
/*                       main                            */
/*********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <sys/timeb.h>

#include "./structures/item.h"
#include "./functions/knapsack.h"
#include "./functions/others.h"

// DEFINITION DE LA VARIABLE GLOBALE verbose
char verbose = 'v'; /* 'v' for verbose */

int main(int argc, char* argv[])
{
    int n, b;
    item *it = NULL;
    double bestobj = 0; /* objective value */
    struct timeb t0, t1;    /* Timers */
    double cpu_time;        /* Time */


    ftime(&t0);
    if(argc != 2)
    {
	fprintf(stderr, "\nPlease, call the program with an argument, that is the instance file name.\n");
	exit(EXIT_FAILURE);
    }

    loadInstance(argv[1], &n, &b, &it);
    if (it == NULL ){
	// STOP EXECUTION
	fprintf(stderr, "Error while loading data file");
	return EXIT_FAILURE;
    }
    
    if(verbose == 'v')
	displayData(n, b, it);

    BB(n, b, it, &bestobj);

//     printf("\nOptimal objective value is %lf",bestobj);
    if(verbose == 'v')
	displayOptimalSolution(n, it);
    
    printdebug("\nLe tab_items[5] est de : %d", it[5].a);
    
    /*
     * Test de la fonction comp_struct
     */
       
    qsort(it, n, sizeof(item), comp_struct);
    int i;
    for(i= 0; i < n; ++i){
	int ratio = (it[i].c / it[i].a);
	printdebug("\nid = %d with a ratio of %d", it[i].id, ratio);
    }
    
    
    /* Below, for checking that the items have been reordered by decreasing utility. */
    //displayData(n, b, it);

    ftime(&t1);
    cpu_time = (double)(t1.time - t0.time) + (double)(t1.millitm-t0.millitm)/1000.0;
    printf("\nCPU time : %f seconds.", cpu_time);

    free(it);
    printf("\n");
    return EXIT_SUCCESS;
}