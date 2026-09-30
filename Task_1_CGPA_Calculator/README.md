# CGPA Calculator

A simple CGPA Calculator developed as part of the CodeAlpha C++ Programming Internship.

## Project Overview

This project calculates a student's semester GPA and overall CGPA based on the grades and credit hours of their courses.

The project contains:

* A C++ console-based CGPA Calculator
* A modern web-based CGPA Calculator using HTML, CSS and JavaScript

## Features

* Enter the number of courses
* Enter course name
* Select the grade
* Enter credit hours
* Calculate grade points
* Calculate total credits
* Calculate semester GPA
* Calculate overall CGPA
* Display individual course results
* Responsive web interface

## Grading System

| Grade | Grade Point |
| ----- | ----------: |
| O     |          10 |
| A+    |           9 |
| A     |           8 |
| B+    |           7 |
| B     |           6 |
| C     |           5 |
| D     |           4 |
| F     |           0 |

## Formula

### Grade Points

```text
Grade Point = Grade Value × Credit Hours
```

### Semester GPA

```text
GPA = Total Grade Points ÷ Total Credits
```

### Overall CGPA

```text
CGPA = Total Cumulative Grade Points ÷ Total Cumulative Credits
```

## Technologies Used

* C++
* HTML
* CSS
* JavaScript

## Files

```text
Task_1_CGPA_Calculator/
│
├── main.cpp
├── index.html
└── README.md
```

## How to Run

### C++ Version

Compile the program using a C++ compiler:

```bash
g++ main.cpp -o cgpa
```

Run:

```bash
./cgpa
```

On Windows:

```bash
cgpa.exe
```

### Web Version

Open `index.html` in any modern web browser.

## Author

Abhishek Kumar

## Internship

CodeAlpha C++ Programming Internship
