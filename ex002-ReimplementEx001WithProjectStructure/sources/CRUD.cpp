
#include <iostream>
#include <fstream>
#include <cstring>
#include "CRUD.h"
#include "Student.h"
#include "Utilities.h"

using namespace std;

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