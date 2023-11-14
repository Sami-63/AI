#include <iostream>
#include <array>

using namespace std;

const int N = 9;

// GPT

// Function to print the Sudoku grid
void printSudoku(const array<array<int, N>, N>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed at a given position
bool isSafe(const array<array<int, N>, N>& grid, int row, int col, int num) {
    // Check if 'num' is not present in the current row and column
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(array<array<int, N>, N>& grid) {
    int row, col;

    // Find an empty position in the grid
    bool isEmpty = false;
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If there is no empty position, the Sudoku is solved
    if (!isEmpty) {
        return true;
    }

    // Try placing a number from 1 to 9 at the current position
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to solve the remaining Sudoku
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing 'num' does not lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed at the current position, backtrack
    return false;
}

int main() {
    // Example Sudoku grid (0 represents empty cells)
    array<array<int, N>, N> sudokuGrid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Sudoku before solving:" << endl;
    printSudoku(sudokuGrid);

    if (solveSudoku(sudokuGrid)) {
        cout << "\nSudoku solution:" << endl;
        printSudoku(sudokuGrid);
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}
