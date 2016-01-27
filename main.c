/*********************************************************/
/*                       main                            */
/*********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <sys/timeb.h>

#include "./structures/item.h"
#include "./knapsack.h"


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
	printf("\nPlease, call the program with an argument, that is the instance file name.\n");
	exit(EXIT_FAILURE);
    }

    loadInstance(argv[1], &n, &b, &it);
    if(verbose == 'v')
	displayData(n, b, it);

    BB(n, b, it, &bestobj);

//     printf("\nOptimal objective value is %lf",bestobj);
    if(verbose == 'v')
	displayOptimalSolution(n, it);
    
    /*
     * Test de la fonction comp_struct
     */
    /*
    item* i1 = (item*)malloc(sizeof(item));
    item* i2 = (item*)malloc(sizeof(item));
    i1->a = 1; i1->c = 2; i1->id = 1;
    i2->a = 2; i2->c = 6; i2->id = 2;
    
    void* item1 = (item *)i1;
    void* item2 = (item *)i2;
    
    int testComp = comp_struct(item1, item2);
    printf("testComp = %d", testComp);
    
//     qsort(Ensemble des items (struct TREE t?), nb_elem dans t , sizeof(item), comp_struct);
    */
    
    
    /* Below, for checking that the items have been reordered by decreasing utility. */
    //displayData(n, b, it);

    ftime(&t1);
    cpu_time = (double)(t1.time - t0.time) + (double)(t1.millitm-t0.millitm)/1000.0;
    printf("\nCPU time : %f seconds.", cpu_time);

    free(it);
    printf("\n");
    return EXIT_SUCCESS;
}