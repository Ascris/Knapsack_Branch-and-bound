#include "knapsack.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include <string.h>

char verbose; /* 'v' for verbose */

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
/* TODO a verifier a l'execution */
item i1 = *( (item*) p1);
item i2 = *( (item*) p2);

int isGreaterThan= compItem(i1, i2);
printf("L'item %d est plus grand que l'item %d", i1.id, i2.id);

return isGreaterThan;
} /* end of comp_struct */

/*********************************************************/
/*                   solveRelaxation                     */
/*********************************************************/
/*                                                       */
/* The items in it[] are expected to be sorted by        */
/* decreasing utility BEFORE calling solveRelaxation     */
/* this function returns 'u' if problem is unfeasible    */
/*                       'i' if solution is integer      */
/*                       'f' if it is fractional         */
/* In the last case only, frac_item contains the index   */
/* of the item in the sorted list (not the id), that is  */
/* partially selected.                                   */
/* Input variables:                                      */
/* n is the number of items                              */
/* b is the knapsack capacity                            */
/* it is an array of items                               */
/* constraint is an array of n char, where constraint[j] */
/* is '1' if item j (in the sorted list) has to be       */
/* selected, '0' is not.                                 */
/* Output variables:                                     */
/* x is an array of n char, where x[j] is '1' if item j  */
/* is selected, '0' otherwise                            */
/* objx is a pointeur to a double containing the         */
/* objective value of solution x.                        */
/* frac_item is a pointeur to the item that is only      */
/* partially inserted in the knapsack, *frac_item = -1   */
/* if the solution is feasible (no fractional items)     */
/*********************************************************/
char solveRelaxation(int n, int b, item *it, char *constraint, char *x, double *objx, int *frac_item)
{
    /* TODO TO COMPLETE */
    
    //on prend en compte constraint avant de commencer
    constraint = x;
    
    //si tous les items qui sont dans constraint dépassent la taille du sac, le problem est infaisable
    int nbConstraints, totalPoidsItems = 0;
    for(nbConstraints= 0; nbConstraints < n; ++nbConstraints){
	if(constraint[nbConstraints] == '1'){
	    totalPoidsItems+= it[nbConstraints].a;
	    if(totalPoidsItems < b) return 'u';
	}
    }
    //si on arrive ici, il reste encore de la place dans le sac
    
    
    int remplissageSac = 0;
    while(remplissageSac < b)
    {
	int indiceIt;
	for(indiceIt= 0; indiceIt < n; ++indiceIt){
	    if(it[indiceIt].c < (b-remplissageSac)){
		//l'item peut etre ajoute au Sac
		remplissageSac+= it[indiceIt].a;
		//l'item ajoute au Sac DEVIENDRA une condition a verifier
		x[indiceIt] = '1';
	    } else{
		//on doit fractionner l'item car il n'y a pas la place pour l'inserer en entier
		x[indiceIt] = '0';
		(*frac_item) = indiceIt;
	    }
	}
    }//le sac est plein
    //calcul de la valeur de l'objectif actuel TODO fonction à faire pour calculer ceci
    double valObjectif= 0.0;
    int itemPresent;
    for(itemPresent= 0; itemPresent < n; ++itemPresent){
	if(x[itemPresent] == '1'){
	    //item present = ajout au total de l'objectif
	    valObjectif+= it[itemPresent].c;
	}
    }
    (*objx) = valObjectif;
	
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

