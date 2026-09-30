# Sudoku Solver

A Sudoku Solver developed using C++ and the backtracking algorithm as part of the CodeAlpha C++ Programming Internship.

## Project Overview

This project solves a standard 9×9 Sudoku puzzle using a recursive backtracking algorithm.

The Sudoku grid is represented using a two-dimensional array. The program finds empty cells and tries numbers from 1 to 9 while checking the Sudoku rules.

## Features

* 9×9 Sudoku grid
* 2D array representation
* Backtracking algorithm
* Recursive solving
* Row validation
* Column validation
* 3×3 subgrid validation
* Invalid puzzle detection
* No-solution detection
* Console-based C++ solver
* Modern web interface

## Sudoku Rules

Every row must contain numbers 1 to 9 without repetition.

Every column must contain numbers 1 to 9 without repetition.

Every 3×3 subgrid must contain numbers 1 to 9 without repetition.

## Algorithm

The solver follows these steps:

```text
1. Find an empty cell.
2. Try numbers from 1 to 9.
3. Check the row.
4. Check the column.
5. Check the 3×3 subgrid.
6. Place the number if valid.
7. Recursively solve the remaining cells.
8. If the choice fails, remove the number.
9. Try another number.
10. Continue until the puzzle is solved.
```

## Backtracking

The key idea is to undo an incorrect choice when it leads to a dead end.

```cpp
grid[row][col] = num;

if (solve(grid))
    return true;

grid[row][col] = 0;
```

The last statement resets the cell and allows the algorithm to try another number.

## Technologies Used

* C++
* HTML
* CSS
* JavaScript

## Files

```text
Task_3_Sudoku_Solver/
│
├── main.cpp
├── index.html
└── README.md
```

## C++ Input

The program accepts 81 numbers representing the Sudoku grid.

Use:

```text
0
```

for an empty cell.

Example:

```text
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

## How to Run

Compile:

```bash
g++ main.cpp -o sudoku
```

Run on Linux/macOS:

```bash
./sudoku
```

On Windows:

```bash
sudoku.exe
```

## Web Version

Open:

```text
index.html
```

in a modern web browser.

The web version provides:

* Interactive Sudoku grid
* Example puzzle
* Clear button
* Solve button
* Invalid puzzle detection
* Responsive design

## Testing

The project was tested with:

* Valid solvable Sudoku
* Invalid Sudoku with duplicate numbers
* Sudoku with no solution
* Empty cells
* Invalid C++ input values
* Completed Sudoku grids

## Complexity

The backtracking algorithm has a worst-case exponential search space.

For a standard 9×9 Sudoku, the algorithm is practical because invalid choices are eliminated early through row, column and 3×3 subgrid checks.

## Internship

CodeAlpha C++ Programming Internship

## Author

Abhishek Kumar
