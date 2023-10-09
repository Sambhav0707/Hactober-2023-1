#include <iostream>
#include <vector>

const int N = 9; // Size of the Sudoku grid (9x9)

// Function to print the Sudoku grid
void printGrid(std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if it's safe to place a number in the given row and column
bool isSafe(std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check if the number is already present in the row or column
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number is already present in the 3x3 subgrid
    int subgridStartRow = row - row % 3;
    int subgridStartCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[subgridStartRow + i][subgridStartCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;
    bool foundEmptyCell = false;

    // Find the first empty cell (cell with value 0)
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                foundEmptyCell = true;
                break;
            }
        }
        if (foundEmptyCell) {
            break;
        }
    }

    // If there are no empty cells, the Sudoku is solved
    if (!foundEmptyCell) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to solve the rest of the puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If the current placement doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed in this cell, the puzzle has no solution
    return false;
}

int main() {
    std::vector<std::vector<int>> sudokuGrid(N, std::vector<int>(N));

    std::cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            std::cin >> sudokuGrid[row][col];
        }
    }

    if (solveSudoku(sudokuGrid)) {
        std::cout << "\nSolution:\n";
        printGrid(sudokuGrid);
    } else {
        std::cout << "No solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}
