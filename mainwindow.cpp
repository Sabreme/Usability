#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QStringBuilder"
#include "QTextStream"
#include "QFile"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->timeEdit->setDisplayFormat("mm:ss");
    this->ui->timeEdit->setTime(QTime(0,0,0,0));
    timer =  new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testingMode(bool testing)
{
    ///We set the frames off when we are testing and leave the stop button active
    this->ui->frame_DEVICES->setEnabled(!testing);
    this->ui->frame_TASKS->setEnabled(!testing);
    this->ui->btnStart->setEnabled(!testing);

    this->ui->btnStop->setEnabled(testing);
    this->ui->btnDone->setEnabled(testing);
}

void MainWindow::on_btnStart_clicked()
{

    connect (timer, SIGNAL(timeout()), this, SLOT(updateCaption()));

    timer->start(1000);

    /// Reset the Timer to ZERO
    this->ui->timeEdit->setTime(QTime(0,0,0,0));

    /// Dissable the various buttons and Panels
    testingMode(true);
}

void MainWindow::updateCaption()
{
    this->ui->timeEdit->setTime(this->ui->timeEdit->time().addSecs(1));
}

void MainWindow::on_btnStop_clicked()
{
    timer->stop();
    testingMode(false);

    printResult(" and Task Open");
}

void MainWindow::on_btnDone_clicked()
{
    timer->stop();
    testingMode(false);

    printResult(" and Task Done");
}

void MainWindow::loadCounterBalance(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->ui->plainTextEdit_Debug->insertPlainText("File not Found !!!");
        return;
    }
    else
    {
        QTextStream in(&file);                
        QString line = in.readLine();
        int lineNo = 0;
        while (!line.isNull())
        {
            stringConfig[lineNo] = line;
            //AddLineToConfig(line,lineNo);
            line = in.readLine();
            lineNo++;
        }
    }
}

void MainWindow::PrintConfig()
{
    for (int line = 0; line < 3; line++)
    {
        this->ui->plainTextEdit_Debug->insertPlainText(stringConfig[line] + '\n');


    }
    extractTaskOrder(stringConfig[0] + '\n');
}

void MainWindow::printResult(QString status)
{
    QString task;
    QString medium;

    ///////    METHOD RADIO BUTTONS   /////////////
    if (this->ui->radioLeap->isChecked() )
        medium = "Leap";
    if (this->ui->radioMouse->isChecked() )
        medium = "Mouse";
    if (this->ui->radioTouch->isChecked() )
        medium = "Touch";

    ///////    TASK RADIO BUTTONS   /////////////
    if (this->ui->radioTask1->isChecked() )
        task = "Task1";
    if (this->ui->radioTask2->isChecked() )
        task = "Task2";
    if (this->ui->radioTask3->isChecked() )
        task = "Task3";

    QString seconds = QString("%1").arg(this->ui->timeEdit->time().second());
    QString minutes = QString("%1").arg(this->ui->timeEdit->time().minute());
    QString result = task % " using " % medium % " took  " % minutes % ":" % seconds % status % "\n";
    this->ui->plainTextEdit_Output->insertPlainText(result);
}

void MainWindow::on_btnCounterBal_clicked()
{
    loadCounterBalance("/home/pmulumba/Projects/Usability/counterbalance.txt");
}

void MainWindow::on_btnTest_clicked()
{
    PrintConfig();
}

QString MainWindow::convertTask(char task)
{
    switch(task)
    {
        case 'a' : return "Transform";
            break;
        case 'b' : return "Sub-Volume";
            break;
        case 'c' : return "Slicing";
            break;
    }
}

QString MainWindow::convertProtOrder(char prototype)
{
    switch(prototype)
    {
        case 'M' : return "Mouse";
            break;
        case 'T' : return "Touch";
            break;
        case 'L' : return "Leap";
            break;
    }
}

void MainWindow::extractTaskOrder(QString line)
{
    //tring tasks = line.split(",",)

    QString output = "Task 1 is " + convertTask(line[5].toAscii());


    this->ui->plainTextEdit_Output->insertPlainText(output);
}

void MainWindow::extractProtOrder(QString line)
{

}
