#include "sudoku.h"

int boxIterator(Square*** sudoku, Box** boxes)
{
    int i, j, k;
    int count;
    int temp;

    /* Loop through boxes */
    for (i = 0; i < 9; i++)
    {
        /* Loop through possible array */
        for (j = 0; j < 9; j++)
        {
            count = 0;
            /* loop through square */

            for (k = 0; k < 9; k++)
            {
                if (boxes[i]->squares[k]->number != 0) // it has a 1 meaning we dont care about that square
                {
                    continue;
                }
                if (boxes[i]->squares[k]->possible[j] == 0)
                {
                    count++;
                    temp = k;
                }
                if (count == 2)
                {
                    // Unsolvable!
                    break;
                }
                if (count == 1)
                {
                    // solvable (we've gone through the entire box and this is where it goes)
                    boxes[i]->squares[temp]->number = j + 1;
                    UNSOLVED--;
                    boxes[i]->squares[temp]->solvable = 0;

                    updateSudoku(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->col);

                    return 1;  // solved something
                }
            }
        }
    }

    return 0;
}

Sudoku* createSudoku(Square*** squares, Box** boxes)
{
    Sudoku* sudoku;
    sudoku = malloc(sizeof(sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
}

Sudoku* setPuzzle(int** puzzle)
{
    Square*** sudoku;
    Box** boxes;  // array of boxes
    int i,j,x;
    int currBox = 0;

    sudoku = (Square***)malloc(sizeof(Square**) * SIZE_ROWS); //sets up dynamic allocation
    boxes = createBoxes();

    //loop through puzzle and store values into square field
    for (i = 0; i < SIZE_ROWS; i++) 
    {
        sudoku[i] = (Square**)malloc(sizeof(Square*) * 9); // each array

        // assign row and col number to each square
        for (j = 0; j < SIZE_COLS; j++) 
        {
            // malloc space for each row
            sudoku[i][j] = (Square*)malloc(sizeof(Square) * 9);
            sudoku[i][j]->number = puzzle[i][j]; 
            sudoku[i][j]->row = i;
            sudoku[i][j]->col = j;
            sudoku[i][j]->solvable = 9;

            boxes[currBox]->squares[boxes[currBox]->numbers] = sudoku[i][j];  //  box points to square
            sudoku[i][j]->whichBox = boxes[currBox];  // square points to box
            boxes[currBox]->numbers++;


            /*initialize possible array to 0*/
            for (x = 0; x < SIZE_ROWS; x++)
            {
                sudoku[i][j]->possible[x] = 0;
            }

            if (j == 2)
            {
                currBox++;  //moving from one of the boxes in the first column to the next
            }
            if (j == 5)
            {
                currBox++;  //moving from one of the boxes in the second column to the third
            }
        }
        currBox -= 2; //moving from one of the boxes in the third column to the first
        if (i == 2)
        {
            currBox = 3;  //moving from first row to next
        }
        if (i == 5)
        {
            currBox = 6; 
        }

    }

    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLS; j++)
        {
            if (sudoku[i][j]->number != 0) // has a number
            {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBox(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, boxes);
}

int updateSudoku(Square*** sudoku, int row, int col)
{
    int x;

    int number = sudoku[row][col]->number;

    for (x = 0; x < SIZE_ROWS; x++) /* loops through column */
    {
        if (sudoku[x][col]->possible[number - 1] == 0) // if it has no value
        {
            sudoku[x][col]->solvable--;
        }
        sudoku[x][col]->possible[number - 1] = 1;
    }

    for (x = 0; x < SIZE_COLS; x++)
    {
        if (sudoku[row][x]->possible[number - 1] == 0) // if it has no value
        {
            sudoku[row][x]->solvable--;
        }
        sudoku[row][x]->possible[number - 1] = 1;
    }

    return 1;
}

int checkPuzzle(Square*** sudoku, Box** boxes) 
{
    int i, j, k;


    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLS; j++)
        {
            if (sudoku[i][j]->solvable == 1)   // is the designated square solvable?
            {
                solveSquare(sudoku[i][j]);   // figure out what number goes in square
                updateSudoku(sudoku, i, j);    // because we know that the specified number cant go anywhere in row i or col j
                updateBox(sudoku, i, j);

                return 1;
            }
        }
    }

   return boxIterator(sudoku, boxes);
}

int** createPuzzle()
{
    int** puzzle;
    int i,j;   // loop counters
    int arr[9][9] = { 0, 5, 0,    8, 0, 2,    6, 0, 0,
                    3, 0, 0,    7, 0, 0,    8, 1, 0,
                    2, 8, 0,    1, 0, 0,    0, 0, 7,
                    0, 0, 0,    3, 0, 0,    0, 6, 0,
                    0, 0, 0,    5, 6, 0,    0, 0, 3,
                    7, 0, 0,    0, 0, 0,    0, 0, 1,
                    0, 0, 9,    0, 0, 0,    7, 2, 8,
                    8, 3, 1,    0, 0, 0,    0, 4, 0,
                    0, 0, 0,    9, 0, 4,    0, 3, 0};

    puzzle = (int**) malloc(sizeof(int*) * 9); // created 9 array

    for (i = 0; i < SIZE_ROWS; i++) // loop through each of the arrays made above
    {
        puzzle[i] = (int*)malloc(sizeof(int) *9); // allocate space for the arrays

        for (j = 0; j < SIZE_COLS; j++) 
        {
            puzzle[i][j] = arr[i][j];  // copies the hardcoded array into puzzle
        } 
    }

    return puzzle;
}

void printPuzzle(Square*** puzzle)
{
    int i, j;

    printf(" -----------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++)
    {
        printf("|");
        /*print each row*/
        for (j = 0; j < SIZE_COLS; j++) 
        {
            printf(" %d ", puzzle[i][j]->number);

            if ((j + 1) % 3 == 0) 
            {
                printf("|");
            }
        }
        printf("\n");
        /* adds divider for every 3 rows */
        if ((i + 1) % 3 == 0)
        {
            printf(" -----------------------------\n");
        }
    }
}