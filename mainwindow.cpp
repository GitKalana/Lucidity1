#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("EmployeeManagement");
    db.setUserName("kalana");
    db.setPassword("11223344");

    if (db.open()) {
        QMessageBox::information(this, "Success", "Database connection successful: " + db.lastError().text());
    } else {
        QMessageBox::critical(this, "Error", "Database connection failed: " + db.lastError().text());
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->SEmpID->text().toInt();
    QString Name = ui->SEmpName->text();
    int Age = ui->SEmpAge->text().toInt();
    QString Address = ui->SEmpAddress->text();
    int Contact = ui->lineEdit->text().toInt();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("EmployeeManagement");
    db.setUserName("kalana");
    db.setPassword("11223344");

    if (!db.open()) {
        qDebug() << "Database connection failed: " << db.lastError().text();
        return;
    }


    QSqlQuery query(db);


    query.exec("CREATE TABLE IF NOT EXISTS Details ("
               "id INT PRIMARY KEY,"
               "name VARCHAR(50) NOT NULL,"
               "age INT,"
               "qualifications VARCHAR(50),"
               "contact INT"
               ")");

    query.prepare("INSERT INTO Data (EmployeeId, EmployeeName, EmployeeAge, EmployeeAddress, EmployeeContact) "
                  "VALUES (:EmployeeId, :EmployeeName, :EmployeeAge, :EmployeeAddress, :EmployeeContact)");


    query.bindValue(":EmployeeId", id);
    query.bindValue(":EmployeeName", Name);
    query.bindValue(":EmployeeAge", Age);
    query.bindValue(":EmployeeAddress", Address);
    query.bindValue(":EmployeeContact", Contact);

    if (query.exec()) {

        qDebug() << "Record added to database.";
    } else {

        qDebug() << "Error adding record to database:" << query.lastError().text();
    }

    db.close();
}


void MainWindow::on_pushButton_2_clicked()
{

    int id = ui->lineEdit_11->text().toInt();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("EmployeeManagement");
    db.setUserName("kalana");
    db.setPassword("11223344");

    if (!db.open()) {
        qDebug() << "Database connection failed: " << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT EmployeeId, EmployeeName, EmployeeAge, EmployeeAddress, EmployeeContact FROM Data WHERE EmployeeId = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {

            QString employeeName = query.value("EmployeeName").toString();
            int employeeAge = query.value("EmployeeAge").toInt();
            QString employeeAddress = query.value("EmployeeAddress").toString();
            int employeeContact = query.value("EmployeeContact").toInt();


            ui->EmpNameOut->setText(employeeName);
            ui->EmpAgeOut->setText(QString::number(employeeAge));
            ui->EmpAddressout->setText(employeeAddress);
            ui->EmpContactOut->setText(QString::number(employeeContact));

            qDebug() << "Values retrieved successfully.";
        } else {
            qDebug() << "No record found for ID" << id;
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    db.close();
}

