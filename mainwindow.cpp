#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staffwriter.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->typeCombo->addItem("Permanent");
    ui->typeCombo->addItem("PartTime");
    ui->typeCombo->addItem("Contract");

    connect(ui->processButton, SIGNAL(clicked()), this, SLOT(process()));
    connect(ui->dynamicButton, SIGNAL(clicked()), this, SLOT(addDynamicProperty()));
    connect(ui->fileButton, SIGNAL(clicked()), this, SLOT(writeToFile()));
}

void MainWindow::process()
{
    QString name = ui->name->text();
    QDate date = ui->date->date();
    QString type = ui->typeCombo->currentText();

    Staff *staff = new Staff(name, date, type);
    list.addStaff(staff);
    QMessageBox::information(this, "Staff detail", "Staff detail added");

    ui->name->clear();
    ui->date->setDate(QDate(2000, 01, 01));
    ui->typeCombo->setCurrentIndex(0);
    ui->name->setFocus();
}

void MainWindow::addDynamicProperty()
{
    if (list.size() != 0)
    {
        bool* ok = new bool;

        QStringList staffNames;
        for (int loop=0; loop<list.size(); loop++)
            staffNames.append(list.at(loop)->property("name").toString());
        QString name = QInputDialog::getItem(this, "Dynamic Property Input", "Which staff name should be used: ", staffNames, 0, false, ok);
        if (*ok == true)
        {
            QString prop = QInputDialog::getText(this, "Dynamic Property Input", "Property name:");
            QString value = QInputDialog::getText(this, "Dynamic Property Input", "Property value:");

            int number = list.findName(name);
            if (name >= 0)
            {
                list.getStaffList().at(number)->setProperty(prop.toLatin1(), value);
                QMessageBox::information(this, "Dynamic property", "Dynamic property added");
            }
        }
        delete ok;
    }
    else
        QMessageBox::information(this, "Dynamic property", "No items in list");
}

void MainWindow::writeToFile()
{
    StaffWriter writer;
    if (writer.writeToFile(list.getStaffList()))
        QMessageBox::information(this, "Output", "Staff detail saved and written to file");
    else
        QMessageBox::information(this, "Output", "Staff detail saved and not written to file");
}

MainWindow::~MainWindow()
{
    delete ui;
}
