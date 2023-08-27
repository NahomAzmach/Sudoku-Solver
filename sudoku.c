#include <stdio.h>
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9; 
int SIZE_COLS = 9;


int main () 
{
    int** puzzle;
    int loading;
    Sudoku* sudoku;

    puzzle = createPuzzle();

    sudoku = setPuzzle(puzzle);

    printPuzzle(sudoku->squares);

    while (UNSOLVED > 0)
    {

        loading = checkPuzzle(sudoku->squares, sudoku->boxes);

        if (loading == 0)
        {
            printf("Failed to solve puzzle \n\n");
            break;
        }

    }
    
    printf("\n\n");

    printPuzzle(sudoku->squares);

    return 0;
}