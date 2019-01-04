#include "staffwriter.h"
#include <QFile>
#include <QTextStream>
#include <QMetaObject>
#include <QMetaProperty>

StaffWriter::StaffWriter()
{
}

bool StaffWriter::writeToFile(QList<Staff *> list) const
{
    QFile file("staffFile.txt");
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream toFile(&file);
    Staff temp;
    QStringList enumNames = temp.staffTypes();

    for (int loop=0; loop<list.size(); loop++)
    {
        const QMetaObject *meta = list.at(loop)->metaObject();
        QString result;

        // for fixed properties
        for (int count=meta->propertyOffset(); count<meta->propertyCount(); count++)
        {
            const QMetaProperty prop = meta->property(count);
            QString name = prop.name();
            QVariant value = prop.read(list.at(loop));
            QString val = value.toString();
            if (prop.isEnumType())
                val = enumNames.at(val.toInt());
            result += QString(name + ": " + val + "; ");
        }


        //for dynamic properties
        foreach(QByteArray propname, list.at(loop)->dynamicPropertyNames())
        {
            QString name = QString::fromLocal8Bit(propname);
            QString value = list.at(loop)->property(propname).toString();
            result += QString(name + ": " + value + "; ");
        }

        toFile << result << '\n';
    }
    file.close();

    return true;
}
