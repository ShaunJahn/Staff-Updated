#ifndef STAFFWRITER_H
#define STAFFWRITER_H
#include "staff.h"

class StaffWriter
{
public:
    StaffWriter();
    bool writeToFile(QList<Staff*> list) const;
};

#endif // STAFFWRITER_H
