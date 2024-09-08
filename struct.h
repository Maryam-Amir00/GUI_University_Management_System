#ifndef STRUCT_H
#define STRUCT_H

#include <QDate>

struct Student {
    char firstName[26];
    char lastName[26];
    int rollNo;
    char department[15];
    QDate dateOfBirth;
};

#endif // STRUCT_H
