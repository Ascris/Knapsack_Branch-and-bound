#!/bin/sh

echo "Apply glpsol on ILP formulation on -knapsack_problem.ilp- file write in  MathProlog language"
echo ""

glpsol --math knapsack_problem.ilp --wlp out.cplex

echo ""
echo "---Display file output : ---"
echo ""

cat out.cplex
