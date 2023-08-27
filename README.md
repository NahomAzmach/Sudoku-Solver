# Sudoku-Solver

My solver utilizes 3 structures - box, square, and the whole sudoku puzzle - to make it more efficient to store the data and for manipulation purposes, also. I used two main algorithms to tackle this project: backtracking and a predictor algorithm. 
BACKTRACKING:
The backtracking was used to find the solution-- the puzzle fills in a cell with a number, and then it checks if the sudoku rules are violated. If not violated, then the pointer moves on to the next cell. If the pointer can't find a valid number for the cell, then it backtracks and looks for other available options.
BOX ITERATION:
I wrote a separate file for the iteration of the box. Basically, the program iterates through each box and attempts to figure out the possible numbers for that empty cell. If there is a cell with only one possible number then it is filled and the sudoku is updated.

Throughout this project, I enhanced my knowledge of "C" and was able to dive deeper into the world of dynamic memory allocation and pointers.
