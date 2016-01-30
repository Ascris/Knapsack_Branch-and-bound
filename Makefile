CC=gcc
CFLAGS=-Wall
CENDFLAGS=-lm
STRUCTDIR=structures/
FUNCDIR=functions/
FILES_DIR=resources/

debug:clean
	$(CC) $(CFLAGS) -g -o knapsack_branch-and-bound $(FUNCDIR)others.c $(FUNCDIR)knapsack.c $(STRUCTDIR)item.c $(STRUCTDIR)queue.c $(STRUCTDIR)tree.c main.c $(CENDFLAGS)
	
debug_full:CFLAGS += -DDEBUG=1
debug_full: clean debug

clean:
	@echo - Nettoyage de fichiers générés
	@echo 
	rm -vfr *~ knapsack_branch-and-bound $(FILES_DIR)*.data.ilp $(FILES_DIR)*.cplex
	@echo 
