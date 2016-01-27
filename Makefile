CC=gcc
CFLAGS="-Wall"
CENDFLAGS="-lm"
OBJDIR=./obj/
STRUCTDIR=structures/
FUNCDIR=functions/

debug:clean
	$(CC) $(CFLAGS) -g -o knapsack_branch-and-bound $(FUNCDIR)knapsack.c $(STRUCTDIR)item.c $(STRUCTDIR)queue.c $(STRUCTDIR)tree.c main.c $(CENDFLAGS)
stable:clean
	$(CC) $(CFLAGS) -o knapsack_branch-and-bound knapsack.c
clean:
	rm -vfr *~ knapsack_branch-and-bound

cleanobj:
	@echo - Nettoyage de fichiers Objets
	@echo 
	rm -rf $(OBJDIR)*
	@echo 