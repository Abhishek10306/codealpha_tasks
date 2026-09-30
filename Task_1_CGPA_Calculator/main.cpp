#include <iostream>
#include <iomanip>
using namespace std;

int getGradePoint(string grade) {
    if (grade == "O") return 10;
    if (grade == "A+") return 9;
    if (grade == "A") return 8;
    if (grade == "B+") return 7;
    if (grade == "B") return 6;
    if (grade == "C") return 5;
    if (grade == "D") return 4;
    return 0;
}

int main() {
    int n;
    cout << "Enter number of courses: ";
    cin >> n;

    double totalCredits = 0;
    double totalGradePoints = 0;

    for (int i = 1; i <= n; i++) {
        string grade;
        double credits;

        cout << "\nCourse " << i << endl;
        cout << "Enter grade: ";
        cin >> grade;

        cout << "Enter credit hours: ";
        cin >> credits;

        int gradePoint = getGradePoint(grade);

        totalCredits += credits;
        totalGradePoints += gradePoint * credits;

        cout << "Grade Point: " << gradePoint << endl;
    }

    double gpa = totalGradePoints / totalCredits;

    cout << "\n------------------------\n";
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << fixed << setprecision(2);
    cout << "Semester GPA: " << gpa << endl;
    cout << "CGPA: " << gpa << endl;
    cout << "------------------------\n";

    return 0;
}