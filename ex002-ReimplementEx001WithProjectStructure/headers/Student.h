#ifndef STUDENT_H
#define STUDENT_H
#endif

#include "Macros.h"

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