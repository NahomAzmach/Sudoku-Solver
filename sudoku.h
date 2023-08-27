#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLS;


typedef struct Sudoku
{
  struct Square*** squares;
  struct Box** boxes;
} Sudoku;

typedef struct Box
{
  struct Square** squares; // array
  int numbers;
  int possible[9];
  int solvable;
  struct Box* next;
} Box;

typedef struct Square
{
    int number;
    
    // If number at the current box is possible for the current position possible[index] = 0, if not its = 1.
    /*
      [1] [1] [1] [1] [1] [1] [1] [1] [1]
      [9] [8] [7] [6] [5] [4] [3] [2] [1] index */
    
    int possible[9];
    int solvable;
    Box * whichBox;
    int row;
    int col;
} Square;

// array of ints
int** createPuzzle();
// prints puzzle with format
void printPuzzle(Square*** puzzle);

//sets up the sudoku field
Sudoku* setPuzzle(int** puzzle);
Sudoku* createSudoku(Square*** puzzle, Box** boxes);


int checkPuzzle(Square*** sudoku, Box** boxes);
int solveSquare(Square* square);
int updateSudoku(Square*** sudoku, int row, int col);

Box** createBoxes();
int updateBox(Square*** sudoku, int row, int col);



#endif