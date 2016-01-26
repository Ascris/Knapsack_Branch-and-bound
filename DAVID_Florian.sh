#!/bin/sh

FILES_DIR="./txtfiles/"

#to edit to change student
STUDENT_NAME="DAVID_Florian"

echo "file name : "$FILES_DIR$STUDENT_NAME.txt
echo ""

./knapsack_branch-and-bound $FILES_DIR$STUDENT_NAME.txt
