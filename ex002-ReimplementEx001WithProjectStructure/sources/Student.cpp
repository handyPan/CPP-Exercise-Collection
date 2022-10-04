
#include <iostream>
#include <iomanip>
#include "Student.h"

using namespace std;

char * Student::getId() {
    return id;
}

void Student::setName(char newName[LEN_NAME]) {
    // clear the original char array
    for(int i=0;i<LEN_NAME;i++) {
        name[i]='\0';
    }
    // copy each char from newName to name
    int i=0;
    while (newName[i]!='\0') {
        name[i] = newName[i];
        i++;
    }
}

char * Student::getCourses() {
    return courses[0];
}

void Student::setCourses(int idx, char newCourseName[LEN_NAME]) {
    // clear the original char array
    for(int i=0;i<LEN_NAME;i++) {
        courses[idx][i]='\0';
    }
    // copy each char from newCourseName to courses[idx]
    int i=0;
    while (newCourseName[i]!='\0') {
        courses[idx][i] = newCourseName[i];
        i++;
    }
}

// this can be easily implemented by grades[idx], here to practice the use of pointer
int * Student::getGrades() {
    return grades;
}

void Student::setGrades(int idx, int newCourseGrade) {
    grades[idx] = newCourseGrade;
}

void Student::setAvg() {
    int sum = 0;
    for(int i=0;i<COURSE_AMOUNT;i++) {
        sum += grades[i];
    }
    avg = sum / COURSE_AMOUNT;
}

void Student::setPassed() {
    passed = avg >= 50 ? true : false;
}

void Student::inputStudentRecord() {
    cout << "Enter student id: ";
    cin.get(id, sizeof(id));
    cin.sync();
    cout << "Enter student name: ";
    cin.get(name, sizeof(name));
    cin.sync();
    for(int i=0;i<COURSE_AMOUNT;i++) {
        cout << "Enter course " << i+1 << " name: ";
        cin.get(courses[i], sizeof(courses[i]));
        cin.sync();
        cout << "Enter course " << i+1 << " grade: ";
        cin >> grades[i];
        cin.sync();
    }

    // update "avg" and "passed"

    setAvg();
    setPassed();
}

void Student::outputStudentRecord() {
    cout << setw(6) << left << id
        << setw(15) << left << name 
        << setw(15) << left << courses[0]
        << setw(11) << right << grades[0] 
        << " " << " " << " "
        << setw(15) << left << courses[1] 
        << setw(11) << right << grades[1] 
        << " " << " " << " "
        << setw(15) << left << courses[2] 
        << setw(11) << right << grades[2] 
        << setw(11) << right << avg 
        << setw(11) << right << passed 
        << endl;  
}