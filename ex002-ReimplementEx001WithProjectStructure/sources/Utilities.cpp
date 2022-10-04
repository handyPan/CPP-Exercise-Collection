#include <iostream>
#include <iomanip>
#include "Utilities.h"

using namespace std;

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