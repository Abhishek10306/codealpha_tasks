#include <iostream>
using namespace std;

class SudokuSolver {
private:

    bool isSafe(int grid[9][9], int row, int col, int num) {

        for (int i = 0; i < 9; i++) {
            if (grid[row][i] == num)
                return false;

            if (grid[i][col] == num)
                return false;
        }

        int startRow = row - row % 3;
        int startCol = col - col % 3;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[startRow + i][startCol + j] == num)
                    return false;
            }
        }

        return true;
    }

    bool isValidInitialGrid(int grid[9][9]) {

        int copy[9][9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                copy[i][j] = grid[i][j];
            }
        }

        for (int row = 0; row < 9; row++) {

            for (int col = 0; col < 9; col++) {

                int num = copy[row][col];

                if (num != 0) {

                    copy[row][col] = 0;

                    if (!isSafe(copy, row, col, num))
                        return false;

                    copy[row][col] = num;
                }
            }
        }

        return true;
    }

    bool solve(int grid[9][9]) {

        for (int row = 0; row < 9; row++) {

            for (int col = 0; col < 9; col++) {

                if (grid[row][col] == 0) {

                    for (int num = 1; num <= 9; num++) {

                        if (isSafe(grid, row, col, num)) {

                            grid[row][col] = num;

                            if (solve(grid))
                                return true;

                            grid[row][col] = 0;
                        }
                    }

                    return false;
                }
            }
        }

        return true;
    }

public:

    bool solveSudoku(int grid[9][9]) {

        if (!isValidInitialGrid(grid))
            return false;

        return solve(grid);
    }

    void printGrid(int grid[9][9]) {

        for (int i = 0; i < 9; i++) {

            for (int j = 0; j < 9; j++) {

                cout << grid[i][j] << " ";

                if (j == 2 || j == 5)
                    cout << "| ";
            }

            cout << endl;

            if (i == 2 || i == 5)
                cout << "------+-------+------" << endl;
        }
    }
};


int main() {

    int grid[9][9];

    cout << "Enter Sudoku grid." << endl;
    cout << "Use 0 for empty cells." << endl;
    cout << endl;

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            cin >> grid[i][j];

            if (cin.fail() ||
                grid[i][j] < 0 ||
                grid[i][j] > 9) {

                cout << "Invalid input." << endl;
                cout << "Enter only numbers from 0 to 9."
                     << endl;

                return 0;
            }
        }
    }

    SudokuSolver solver;

    if (solver.solveSudoku(grid)) {

        cout << endl;
        cout << "Solved Sudoku:" << endl;
        cout << endl;

        solver.printGrid(grid);

    } else {

        cout << endl;
        cout << "No solution exists for this Sudoku."
             << endl;
    }

    return 0;
}