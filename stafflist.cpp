#include "stafflist.h"
#include <QVariant>

StaffList::StaffList()
{
}

void StaffList::addStaff(Staff *s)
{
    staffList.append(s);
}

QList<Staff *> StaffList::getStaffList() const
{
    return staffList;
}

StaffList::~StaffList()
{
    qDeleteAll(staffList);
}

int StaffList::size() const
{
    return staffList.size();
}

Staff* StaffList::at(int i) const
{
    return staffList.at(i);
}

int StaffList::findName(QString n) const
{
    int count = 0;
    while (count < staffList.size())
    {
        if (staffList.at(count)->property("name").toString() == n )
            return count;
        count++;
    }
    return -1;
}
