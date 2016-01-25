CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o knapsack_branch-and-bound main.c
stable:clean
	$(CC) $(CFLAGS) -o knapsack_branch-and-bound main.c
clean:
	rm -vfr *~ knapsack_branch-and-bound
