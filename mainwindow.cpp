#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    QFile file("Frequency1");
    if(!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());

    QFile file1("Frequency2");
    if(!file1.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file1.errorString());

    QTextStream in1(&file1);

    ui->textBrowser_2->setText(in1.readAll());

    QFile file2("Scale1");
    if(!file2.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file2.errorString());

    QTextStream in2(&file2);

    ui->textBrowser_7->setText(in2.readAll());

    QFile file3("Scale2");
    if(!file3.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file3.errorString());

    QTextStream in3(&file3);

    ui->textBrowser_8->setText(in3.readAll());

    QFile file4("Scale3");
    if(!file4.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file4.errorString());

    QTextStream in4(&file4);

    ui->textBrowser_9->setText(in4.readAll());
}
