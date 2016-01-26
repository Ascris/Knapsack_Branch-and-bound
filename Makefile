CC=gcc
CFLAGS="-Wall"
OBJDIR=./obj/

debug:clean
	$(CC) $(CFLAGS) -g -o knapsack_branch-and-bound knapsack.c main.c
stable:clean
	$(CC) $(CFLAGS) -o knapsack_branch-and-bound knapsack.c
clean:
	rm -vfr *~ knapsack_branch-and-bound

cleanobj:
	@echo - Nettoyage de fichiers Objets
	@echo 
	rm -rf $(OBJDIR)*
	@echo 