
#include <iostream>

#include "Person.h"
#include "CRUD.h"

using namespace std;

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


