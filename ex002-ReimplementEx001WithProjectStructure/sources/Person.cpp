#include <iostream>
#include "Person.h"

using namespace std;

Person::Person() {
    cout << "Person class constructor Person() invoked." << endl;
}

void Person::whatYouGot() {
    cout << "I got a million" << endl;
}