#!/bin/sh

DATA_FILES="DAVID_Florian_data.ilp"

echo "Apply glpsol on ILP formulation on -knapsack_problem.ilp- file write in  MathProlog language"
echo ""

glpsol --math knapsack_problem.ilp --data $DATA_FILES --wlp out.cplex

#echo ""
#echo "---Display file output : ---"
#echo ""

#cat out.cplex
