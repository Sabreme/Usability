#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QStringBuilder"
#include "QStringList"
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

            SplitAndAdd(line,lineNo);
            //counterBalance

            //AddLineToConfig(line,lineNo);
            line = in.readLine();
            lineNo++;
        }
    }
}

void MainWindow::SplitAndAdd(QString line, int lineNumber)
{
    QStringList tokens ;

    tokens = line.split(",");

    for (int index = 0; index < tokens.length(); index++)
    {
        counterBalance[lineNumber][index] = tokens.at(index);
        this->ui->plainTextEdit_Output->insertPlainText(tokens.at(index));
    }
    QString lineNo = QString("%1").arg(lineNumber);
    QString tokenSize = QString("%1").arg(tokens.length());


    this->ui->plainTextEdit_Output->insertPlainText(" --- LineNumber " + lineNo +
                                                     " has " + tokenSize +
                                                     "\n");
    tokens.clear();

}

void MainWindow::PrintConfig()
{
    QString output, word ;

    for (int line = 0; line < 3; line++)
    {
        output = "";
        for (int pos=0; pos < 8; pos++)
        {
            word = counterBalance[line][pos];
           switch (pos)
           {
               case 0: output += "Session " + word ;
                   break;
               case 1: output += ", User " + word ;
                   break;
               case 2: output += " does [" + convertProtOrder(word) ;
                   break;
               case 3: output += "] >> [ " + convertProtOrder(word) ;
                   break;
               case 4: output += "] >> [ " + convertProtOrder(word) ;
                   break;
               case 5: output += " With Task Order [" + convertTask(word) ;
                   break;
               case 6: output += "] >> [ " + convertTask(word) ;
                   break;
               case 7: output += "] >> [ " + convertTask(word) ;
                   break;
               default:\
                output += "\n";
           }

        }
         this->ui->plainTextEdit_Debug->insertPlainText(output);
    }

//    for (int i = 0; i < 3 ; i ++)
//    {
//        for (int j = 0; j < 8; j++)
//        {
//             this->ui->plainTextEdit_Debug->insertPlainText(counterBalance[i][j]);
//        }
//         this->ui->plainTextEdit_Debug->insertPlainText("\n");

//    }
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

QString MainWindow::convertTask(QString task)
{
    if (task.compare("a")==0)
            return "Transform";
    if (task.compare("b")==0)
            return "Sub-Volume";
    if (task.compare("c")==0)
            return "Slicing";
}

QString MainWindow::convertProtOrder(QString prototype)
{
    if (prototype.compare("L")==0)
            return "Leap";
    if (prototype.compare("M")==0)
            return "Mouse";
    if (prototype.compare("T")==0)
            return "Touch";
}

void MainWindow::extractTaskOrder(QString line)
{
}

void MainWindow::extractProtOrder(QString line)
{
}
