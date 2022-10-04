#ifndef CRUD_H
#define CRUD_H
#endif

#include "Macros.h"

class CRUD {
    private:
    public:
        static void createRecord(char dataFile[LEN_NAME]);
        static void readRecord(char dataFile[LEN_NAME], char mode);
        static void updateRecord(char dataFile[LEN_NAME]);
        static void deleteRecord(char dataFile[LEN_NAME]); 
};