/**
 * Author: Handy Pan
 * email: pxp.on.ca@gmail.com
 * Description: This system implements the CRUD of student grade. The records are stored in a .bin document by file write and read operations.
 */

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#define LEN_ID 5        // the length of id
#define LEN_NAME 10     // the length of student name, course name
#define COURSE_AMOUNT 3        // the length of number of courses, grades

class Student {
    private:
        char id[LEN_ID];
        char name[LEN_NAME];
        char courses[COURSE_AMOUNT][LEN_NAME];
        int grades[COURSE_AMOUNT];
        int avg;
        bool passed;
    public:
        char * getId();    
        void setName(char newName[LEN_NAME]);
        char * getCourses();
        void setCourses(int idx, char newCourseName[LEN_NAME]);
        int * getGrades();
        void setGrades(int idx, int newCourseGrade);
        void setAvg();
        void setPassed();    
        void inputStudentRecord();
        void outputStudentRecord();
};

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

class Utilities {
    private:
    public:
        static void printTitle();
};

void Utilities::printTitle() {
    cout << setw(6) << left << "ID" 
        << setw(15) << left << "Name"
        << setw(15) << left << "Course - 1" 
        << setw(11) << right << "Grade - 1" 
        << " " << " " << " "
        << setw(15) << left << "Course - 2" 
        << setw(11) << right << "Grade - 2" 
        << " " << " " << " "
        << setw(15) << left << "Course - 3" 
        << setw(11) << right << "Grade - 3"
        << setw(11) << right << "Average" 
        << setw(11) << right <<"Passed" 
        << endl;
}

class CRUD {
    private:
    public:
        static void createRecord(char dataFile[LEN_NAME]);
        static void readRecord(char dataFile[LEN_NAME], char mode);
        static void updateRecord(char dataFile[LEN_NAME]);
        static void deleteRecord(char dataFile[LEN_NAME]); 
};

void CRUD::createRecord(char dataFile[LEN_NAME]) {
    fstream fs;
    fs.open(dataFile, ios::app|ios::binary);
    while(true) {
        Student st;
        char op;
        st.inputStudentRecord();
        fs.write((char*)&st, sizeof(st));
        cout << "Continue adding records? (y/N): ";
        cin >> op;
        cin.sync();
        while(op!='y'&&op!='Y'&&op!='n'&&op!='N'&&op!=' ') {
            cout << "Input error! Continue adding records? (y/N): ";
            cin >> op;
            cin.sync();
        }
        op = op==' '?'N':op;
        if (op=='n'|| op== 'N') {
            break;
        }
    }
    fs.close();
}

void CRUD::readRecord(char dataFile[LEN_NAME], char mode) {
    fstream fs;
    fs.open(dataFile, ios::in | ios::binary);
    if (!fs) {
        cout << "File not found.";
        return;
    } else {
        Student st;
        if (mode=='a') {
            // show all records            
            // print the title
            Utilities::printTitle();
            fs.read((char*)&st, sizeof(st));
            while(!fs.eof()) {
                st.outputStudentRecord();
                fs.read((char*)&st, sizeof(st));
            }
        } else if (mode=='o') {
            // show one specific record
            char idToSearch[LEN_ID];
            bool idFound = false;
            cout << "Enter the student id to search: ";
            cin.get(idToSearch, sizeof(idToSearch)); 
            cin.sync();
            fs.read((char*)&st, sizeof(st));
            while(!fs.eof()) {
                // compare the two ids
                if(strcmp(st.getId(), idToSearch) == 0) {
                    idFound = true;
                    // print the title
                    Utilities::printTitle();
                    st.outputStudentRecord();
                    break;
                }
                fs.read((char*)&st, sizeof(st));
            }
            if(!idFound) {
                cout << "Record with id = " << idToSearch << " not found." << endl;
            }
        } else {

        }
        fs.close();
    }
}

void CRUD::updateRecord(char dataFile[LEN_NAME]) {
    fstream fs;
    fs.open(dataFile, ios::in | ios::out | ios::binary);
    if (!fs) {
        cout << "File not found.";
        return;
    } else {
        Student st;
        // search the record
        char idToUpdate[LEN_ID];
        bool idFound = false;
        cout << "Enter the student id to update: ";
        cin.get(idToUpdate, sizeof(idToUpdate));
        cin.sync();
        while(fs.read((char*)&st, sizeof(st))) {
            // compare the two ids
            if(strcmp(st.getId(), idToUpdate)==0) {
                idFound = true;
                // print out the current record
                Utilities::printTitle();
                st.outputStudentRecord();
                // ask for the update
                while (true) {
                    char op1;
                    cout << "Select the fields to be modified." << endl;
                    cout << "1. Name" << endl;
                    cout << "2. Course Names" << endl;
                    cout << "3. Course Grades" << endl;
                    cin >> op1;
                    cin.sync();
                    switch(op1) {
                        case '1':
                            cout << "Enter the new name: ";
                            char newName[LEN_NAME];
                            cin.get(newName, sizeof(newName));
                            st.setName(newName);
                            cin.sync();
                            cout << "Name updated." << endl;
                            break;
                        case '2':
                            char op2;
                            cout << "Select the course name no. to update: " << endl;
                            cout << "1. " << st.getCourses() << endl;
                            cout << "2. " << st.getCourses() + LEN_NAME * 1 << endl;
                            cout << "3. " << st.getCourses() + LEN_NAME * 2 << endl;
                            cin >> op2;
                            cin.sync();
                            cout << "Enter the new name for course " << op2 << ": ";
                            char newCourseName[LEN_NAME];
                            cin.get(newCourseName, sizeof(newCourseName));
                            st.setCourses(op2 - '0' - 1, newCourseName);
                            cin.sync();
                            cout << "Course " << op2 << " name updated." << endl;
                            break;
                        case '3':
                            char op3;
                            cout << "Enter the course grade no. to update: " << endl;
                            cout << "1. " << st.getCourses() << "-" << *(st.getGrades()) << endl;
                            cout << "2. " << st.getCourses() + LEN_NAME * 1 << "-" << *(st.getGrades() + 1) << endl;
                            cout << "3. " << st.getCourses() + LEN_NAME * 2 << "-" << *(st.getGrades() + 2) << endl;
                            cin >> op3;
                            cin.sync();
                            cout << "Enter the new grade for course " << op3 << ": ";
                            int newCourseGrade;
                            cin >> newCourseGrade;
                            st.setGrades(op3 - '0' - 1, newCourseGrade);
                            st.setAvg();
                            st.setPassed();
                            cin.sync();
                            cout << "Course " << op3 << " grade updated." << endl;
                            break;
                        default:
                            cout << "Incorrect Option, select again.";
                    }

                    // write to data file
                    int pos = sizeof(st);
                    fs.seekp(-pos, ios::cur);
                    fs.write((char*)&st, sizeof(st));

                    // ask whether to continue editing another record
                    cout << "Continue updating this record? (y/N): ";
                    char op;
                    cin >> op;
                    cin.sync();
                    while(op!='y'&&op!='Y'&&op!='n'&&op!='N'&&op!=' ') {
                        cout << "Input error! Continue updating this record? (y/N): ";
                        cin >> op;
                        cin.sync();
                    }
                    op = op==' '?'N':op;
                    if (op=='n'|| op== 'N') {
                        break;
                    }
                }
                // display the updated record
                cout << "Record with id = " << idToUpdate << " is updated to: " << endl;
                Utilities::printTitle();
                st.outputStudentRecord();
                break;
            }
        }
        fs.close();
        if(!idFound) {
            cout << "Record with id = " << idToUpdate << " not found." << endl;
        }
    }
}

void CRUD::deleteRecord(char dataFile[LEN_NAME]) {
    fstream fs, fs2;
    fs2.open("tmp.bin", ios::out | ios::binary);
    fs.open(dataFile, ios::in | ios::binary);
    if (!fs) {
        cout << "File not found.";
        return;
    } else {
        Student st;
        // search the record
        char idToDelete[LEN_ID];
        bool idFound = false;
        cout << "Enter the student id to delete: ";
        cin.get(idToDelete, sizeof(idToDelete));
        cin.sync();
        fs.read((char*)&st, sizeof(st));
        while(!fs.eof()) {
            // copy the other records to tmp.bin
            if(strcmp(st.getId(), idToDelete) != 0) {
                fs2.write((char*)&st, sizeof(st));
            } else {
                idFound = true;
                // print out the record to delete
                cout << "To delete below record: " << endl;
                Utilities::printTitle();
                st.outputStudentRecord();
            }
            fs.read((char*)&st, sizeof(st));
        }
        fs2.close();
        fs.close();
        if(!idFound) {
            cout << "Record with id = " << idToDelete << " not found." << endl;
        }
        remove(dataFile);
        rename("tmp.bin", dataFile);
        cout << "Above record deleted successfully!" << endl;
    }
}

int main() {
    char op;
    while(true) {
        system("cls");
        cout << "   Welcome to Grade Management System   " << endl;
        cout << "==================MENU==================" << endl;
        cout << "1. Add New Record" << endl;
        cout << "2. Display All Records" << endl;
        cout << "3. Display Particular Record" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter an option to proceed: ";
        cin >> op;
        cin.sync();
        while(true) {
            if(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='5'&&op!='6') {
                cout << "Input error! Enter one option in 1-6 again: ";
                cin >> op;
                cin.sync();
            } else {
                break;
            }
        }

        char dataFile[LEN_NAME] = "data.bin";

        switch(op) {
            case '1':
                CRUD::createRecord(dataFile);
                break;
            case '2':
                CRUD::readRecord(dataFile, 'a');
                break;
            case '3':
                CRUD::readRecord(dataFile, 'o');
                break;
            case '4':
                CRUD::updateRecord(dataFile);
                break;
            case '5':
                CRUD::deleteRecord(dataFile);
                break;
            case '6':
                cout << "Exited the system. Bye!";
                exit(0);
            default:
                break;
        }

        cout << "Continue running the system? (y/N): ";
        char op2;
        cin >> op2;
        cin.sync();
        while(op2!='y'&&op2!='Y'&&op2!='n'&&op2!='N'&&op2!=' ') {
            cout << "Input error! Input again. (y/N): ";
            cin >> op2;
            cin.sync();
        }
        op2 = op2==' '?'Y':op2;
        if (op2=='n'|| op2== 'N') {
            cout << "Exited the system. Bye!";
            exit(0);
        }        
    }

    return 0;
}