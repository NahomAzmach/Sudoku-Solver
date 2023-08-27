#include "sudoku.h"

int solveSquare(Square* square) 
{
    int k;

    for (k = 0; k < SIZE_ROWS; k++) // loop through possibilities array to find a '0'
    {
       if (square->possible[k] == 0) // number we're saving
       {
            square->number = k + 1; // bc its 0 based
            square->solvable = 0;
            UNSOLVED--;  // keeps track of numbers to still solve for (goes until 1/0)
            return 1;
       } 
    }
    return 0;
}