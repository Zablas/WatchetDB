#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDebug>
#include <thread>
#include <fstream>

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

    // Get the strings
    QString hostName = ui->inputHostName->text();
    QString dbName = ui->inputDbName->text();
    QString username = ui->inputUsername->text();
    QString password = ui->inputPassword->text();
    int port = ui->inputPort->text().toInt();

    // Thread separation
    std::thread connThread([&]{
        // Set up the connection
        QSqlDatabase qdb = QSqlDatabase::addDatabase("QMYSQL");
        qdb.setHostName(hostName);
        qdb.setDatabaseName(dbName);
        qdb.setUserName(username);
        qdb.setPassword(password);
        qdb.setPort(port);

        // Check if it's open
        bool isOpen = qdb.open();
        if(isOpen) ui->label_5->setText("Connection success!");
        else ui->label_5->setText(qdb.lastError().text());
        if(ui->chkSaveInfo->isChecked())
        {
            QFile cachedDbFile("dblist.csv");
            cachedDbFile.open(QFile::WriteOnly);
            std::ofstream f("dblist.csv");
            f << "LMAO\n";
        }
    });
    connThread.join();
}
