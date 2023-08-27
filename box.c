#include "sudoku.h"

Box** createBoxes()
{
    int i, j;
    Box** boxes;
    boxes = malloc(sizeof(Box*) * 9);

    for (i = 0; i < 9; i++)
    {
        boxes[i] = malloc(sizeof(Box));
        boxes[i]->squares = malloc(sizeof(Square*) * 9);
        boxes[i]->numbers = 0;
        boxes[i]->solvable = 9; // if solvable = 1, box is solvable

        for (j = 0; j < 9; j++)
        {
            boxes[i]->possible[j] = 0;
        }
    }
    return boxes;
}

int updateBox(Square*** sudoku, int row, int col)
{
    int i;
    int number = sudoku[row][col]->number; // number found
    Box* box;
    box = sudoku[row][col]->whichBox;

    /*loop through every square in the box*/

    for (i = 0; i < 9; i++)
    {
        if (box->squares[i]->possible[number - 1] == 0)
        {
            box->squares[i]->solvable--;
            box->squares[i]->possible[number - 1] = 1;  // cant be that number so possible array is set to 1
        }
    }


}