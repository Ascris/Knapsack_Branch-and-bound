#!/bin/sh

#to edit to change student
STUDENT_NAME="DAVID_Florian"

echo "Apply glpsol on ILP formulation on -knapsack_problem.ilp- file write in  MathProlog language"
echo ""

file="./$STUDENT_NAME.data.ilp"
if [ -e $file ]; then
	echo "Data file exists, launching glpsol ..."
else 
	echo "Data file does not exists, creating it with perl script ..."
	echo ""
	perl ./txt_to_data-ilp.pl ./txtfiles/$STUDENT_NAME.txt $STUDENT_NAME.data.ilp
	echo ""
	echo ""
	echo "Launching glpsol ..."
fi 

glpsol --math knapsack_problem.ilp --data $STUDENT_NAME.data.ilp --wlp out.cplex

#echo ""
#echo "---Display file output : ---"
#echo ""

#cat out.cplex
