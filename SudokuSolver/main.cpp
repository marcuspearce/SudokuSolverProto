//
//  main.cpp
//  SudokuSolver
//
//  Created by Marcus Pearce on 12/29/19.
//  Copyright © 2019 Marcus Pearce. All rights reserved.
//

#include <iostream>
using namespace std;

// define size of 9x9 sudoku grid
#define S 9





// return true if given number satisfies row, false otherwise
bool checkRow(int board[S][S], int row, int num)
{
    for(int i = 0; i < S; i++)
    {
        if(board[row][i] == num)
            return false;
    }
    return true;
}



// return true if given number satisfies column, false otherwise
bool checkCol(int board[S][S], int col, int num)
{
    for(int i = 0; i < S; i++)
    {
        if(board[i][col] == num)
            return false;
    }
    return true;
}



// return true if given number satisfies box, false otherwise
    // note boxes are 3x3
bool checkBox(int board[S][S], int row, int col, int num)
{
    int boxSize = 3;
    
    int boxRow = row - (row % boxSize);
    int boxCol = col - (col % boxSize);
    
    for(int i = 0; i < boxSize; i++)
        for(int j = 0; j < boxSize; j++)
            if(board[i+boxRow][j+boxCol] == num)
                return false;

    return true;
}



// return true if given number satisfies current row, column, and box, false otherwise
bool validEntry(int board[S][S], int row, int col, int num)
{
    return (checkRow(board,row,num) && checkCol(board,col,num) && checkBox(board,row,col,num));
}



// look for a cell with value 0, then assign row and col to those coordinates
    // use reference to row and col to modify those variables in the recurisve solve function
// return true if found an empty cell, false otherwise
bool findEmptyCell(int board[S][S], int& row, int& col)
{
    // reset row and col here to make sure go thru all values
    for(row = 0; row < S; row++)
    {
        for(col = 0; col < S; col++)
        {
            // if empty, return true w/ current value of coordiantes (row, col)
            if(board[row][col] == 0)
                return true;
        }
    }
    return false;
}



// use backtracking algorithm -> assign a valid number to an empty cell then recursively check whether this leads to a solution or not
// return true if found a solution, false otherwise
bool solve(int board[S][S])
{
    // find the coordinates of an empty cell -> row and col
    int row;
    int col;
    
    // base case: if there are no empty cells, return true since board is solved
    if(!findEmptyCell(board, row, col))
        return true;
    
    // now row and col are updated coordiantes of empty cell
    
    // iterate thru each potential number (1-9) and put valid ones into empty cell, then recursively check if solution works
    for (int num = 1; num <= 9; num++)
    {
        // check current number is valid to be put into current spot
        if(validEntry(board, row, col, num))
        {
            // tentatively assign value to empty cell
            board[row][col] = num;
            
            // check recursively to see if this was the correct assignment
            if(solve(board))
                return true;    // yay this was the correct assignment!
            
            // if was not correct assignment, make current cell empty again and try w/ next potential value
            board[row][col] = 0;
        }
    }
    
    // if cannot find correct colution w/ current cell, need to backtrack
    return false;
}





// print soduku board
void printBoard(int board[S][S])
{
    for(int i = 0; i < S; i++)
    {
        for(int j = 0; j < S; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// testing procedure
void test(int board[S][S])
{
    cout << "Sudoku puzzle to solve:" << endl;
    printBoard(board);
    cout << endl;
    
    if(solve(board))
    {
        cout << "Solution found! yeet" << endl;
        printBoard(board);
    }
    else
        cout << "No solution found :( rip" << endl;
    
    cout << "\n\n\n";
}




// Main program -- used for testing on sample sudoku board(s)
int main()
{
    // sample sudoku puzzle to solve -> 0 means unassigned
        // use 2D arary to represent puzzle (for testing)
    // sample taken from https://dingo.sbs.arizona.edu/~sandiway/sudoku/examples.html
    int board1[S][S] = {
        {0,0,0,2,6,0,7,0,1},
        {6,8,0,0,7,0,0,9,0},
        {1,9,0,0,0,4,5,0,0},
        {8,2,0,1,0,0,0,4,0},
        {0,0,4,6,0,2,9,0,0},
        {0,5,0,0,0,3,0,2,8},
        {0,0,9,3,0,0,0,7,4},
        {0,4,0,0,5,0,0,3,6},
        {7,0,3,0,1,8,0,0,0}
    };
    
    int board2[S][S] = {
        {0,2,0,0,0,0,0,0,0},
        {0,0,0,6,0,0,0,0,3},
        {0,7,4,0,8,0,0,0,0},
        {0,0,0,0,0,3,0,0,2},
        {0,8,0,0,4,0,0,1,0},
        {6,0,0,5,0,0,0,0,0},
        {0,0,0,0,1,0,7,8,0},
        {5,0,0,0,0,9,0,0,0},
        {0,0,0,0,0,0,0,4,0}
    };
    
    
    test(board1);
    test(board2);
    
    
    
    return 0;
}




