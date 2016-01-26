#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include <string.h>

#include "./structures/item.h"
#include "./structures/queue.h"
#include "./structures/tree.h"

char verbose; /* 'v' for verbose */

int get_file_size(char *filename)
{
   FILE *fp;
   int file_size;
   file_size = 0;
   if ((fp = fopen(filename, "rb" )) == NULL) {
      fprintf(stderr, "Cannot open %s.\n", filename);
      return(file_size);
   }
   char ligne[30];
   while(fgets(ligne, 30,fp) != NULL)
    {
	    file_size++;
    }
   fclose(fp);
   return(file_size);
}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result =(char**) malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}

char** loadFile(char* filename)
{
    int size= get_file_size(filename);
    char ** text= NULL;
    
    FILE *file;
    file= fopen(filename,"r");
    
    if (file != NULL){
	text=(char**)malloc(sizeof(char*)*size);
	char ligne[30];
	int num_ligne;
	for(num_ligne=0; fgets(ligne, 30, file) != NULL;
	    ++num_ligne)
	{
	    text[num_ligne]=(char*)malloc(sizeof(char)*(strlen(ligne)+1));
	    strcpy(text[num_ligne],ligne);
	    #if DEBUG
	    printf("DEBUG : num_ligne du fichier : %d/%d de valeur %s", num_ligne, size ,text[num_ligne]);
	    #endif
	}
	#if DEBUG
	printf("\nNUMERO DE LIGNE A LA SORTIE : %d\n", num_ligne);
	#endif
	fclose(file);
    
    } else {
	// On affiche un message d'erreur si on veut
	fprintf(stderr, "%s\n","Impossible d'ouvrir le fichier \n");
    }

    return text;
}

void loadInstance(char* filename, int *n, int *b, item **it)
{

/* TODO TO COMPLETE */
    char** text= loadFile(filename);
    
    char **ligne1=str_split(text[0],' ');
    int item_nb=atoi(ligne1[0]);
    
// 		init_size_vertices(&(graphe->vertices), nb_noeuds);
    *it= (item*)malloc(item_nb*sizeof(item)); // TODO vérifier
    
    free(ligne1);
    
    int i;
    for(i= 1; i < item_nb +1; i++)
    {
	char **ligne1=str_split(text[i],' ');
	int coord_x=atoi(ligne1[0]); // TODO USE
	int coord_y=atoi(ligne1[1]); // TODO USE
	    
// 	    add_vertice(&(graphe->vertices), coord_x,coord_y,i-1); TODO changer
	    free(ligne1);
    }
    
    // TODO faire suppression de text
    // (on ne peut pas car on a pas size)
    // -> utiliser variable globale ou changer loadFile
//     for (i= 0; i < size; ++i){
// 	free(text[i]);
//     }
    free(text);
#if DEBUG
    printf("Je sors de loadInstance\n");
#endif
}


/*********************************************************/
/*                       comp_struct                     */
/*********************************************************/
static int comp_struct(const void* p1, const void* p2)
{

/* TODO TO COMPLETE */
    return 0;
} /* end of comp_struct */

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

