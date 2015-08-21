#include "UserTesing.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QStringBuilder"
#include "QStringList"
#include "QTextStream"
#include "QFile"
#include "QTextStream"

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

    initiateTest(this->ui->spinBoxUSERID->value() -1);
    SetCurrentTask(this->ui->spinBoxUSERID->value() -1);
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
        this->ui->plainTextEdit_Debug->insertPlainText(tokens.at(index));
    }
    QString lineNo = QString("%1").arg(lineNumber);
    QString tokenSize = QString("%1").arg(tokens.length());


    this->ui->plainTextEdit_Debug->insertPlainText("\n");
    tokens.clear();

}

///
/// \brief MainWindow::initiateTest
/// \param sessionID
/// \param userNumber
///  1. We look for the row with both the session ID and User ID,
///     Using an Optimised search parameter because the counterbalance
///     file is organised into Sessions in groups of 3 and users in order 1,2,3
///  2. We then extract the ordering of Tasks to a Local collection
///  3. We then Extract the ordering of Prototypes to a local collection
void MainWindow::initiateTest(int userID)
{
    QString task ;

    if (this->ui->radioTask1->isChecked() )
        task = convertTask(counterBalance[userID][one]);
    if (this->ui->radioTask2->isChecked() )
        task = convertTask(counterBalance[userID][two]);
    if (this->ui->radioTask3->isChecked() )
        task = convertTask(counterBalance[userID][three]);

///    this->ui->plainTextEdit_Debug->insertPlainText("Task = " + task );
}

void MainWindow::PrintConfig()
{
    QString output, word ;

    for (int line = 0; line < 3; line++)
    {
        output = "";
        for (int pos=0; pos < 7; pos++)
        {
            word = counterBalance[line][pos];
           switch (pos)
           {
               case 0: output += "User " + word ;
                   break;               
               case 1: output += " does [" + convertPrototype(word) ;
                   break;
               case 2: output += "] -> [ " + convertPrototype(word) ;
                   break;
               case 3: output += "] -> [ " + convertPrototype(word) ;
                   break;
               case 4: output += "] With Tasks [" + convertTask(word) ;
                   break;
               case 5: output += "] -> [ " + convertTask(word) ;
                   break;
               case 6: output += "] -> [ " + convertTask(word) ;
                   break;          
           }
        }
         output += "\n";
         this->ui->plainTextEdit_Output->insertPlainText(output);
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
    QString taskNo;

    ///////    METHOD RADIO BUTTONS   /////////////
    if (this->ui->radioLeap->isChecked() )
        medium = "Leap";
    if (this->ui->radioMouse->isChecked() )
        medium = "Mouse";
    if (this->ui->radioTouch->isChecked() )
        medium = "Touch";

    ///////    TASK RADIO BUTTONS   /////////////
    if (this->ui->radioTask1->isChecked() )
        taskNo = "1";
    if (this->ui->radioTask2->isChecked() )
        taskNo = "2";
    if (this->ui->radioTask3->isChecked() )
        taskNo = "3";

    task = GetCurrentTask(this->ui->spinBoxUSERID->value() - 1);


    int seconds = this->ui->timeEdit->time().second();
    int minutes = this->ui->timeEdit->time().minute();

    int userID = this->ui->spinBoxUSERID->value();
    int sessionID = userID / 3 ;
    if (userID % 3 != 0)
        sessionID++;
    QString result =    QString("UserID: %1 ,TaskNo: %2 ,Task: %3, Prototype: %4 ,Time: %5:%6" + status % "\n")
                                .arg(userID).arg(taskNo).arg(task).arg(medium).arg(minutes).arg(seconds);

    saveResult(result);

    //this->ui->plainTextEdit_Output->insertPlainText(result);
}

void MainWindow::saveResult(QString result)
{
    QString taskNo;

    ///////    TASK RADIO BUTTONS   /////////////
    if (this->ui->radioTask1->isChecked() )
        taskNo = "1";
    if (this->ui->radioTask2->isChecked() )
        taskNo = "2";
    if (this->ui->radioTask3->isChecked() )
        taskNo = "3";

    int userID = this->ui->spinBoxUSERID->value();

     QString output = QString("TESTS/UserID_%1_Task_%2.txt").arg(userID).arg(taskNo);

    QFile file(output);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << result;
    file.close();
}

void MainWindow::on_btnCounterBal_clicked()
{    
    loadCounterBalance("counterbalance.txt");
}

void MainWindow::on_btnTest_clicked()
{
    //PrintConfig();
//    QString taskNo;

    SetCurrentPrototype(this->ui->spinBoxUSERID->value()-1);

//    ///////    TASK RADIO BUTTONS   /////////////
//    if (this->ui->radioTask1->isChecked() )
//        taskNo = "1";
//    if (this->ui->radioTask2->isChecked() )
//        taskNo = "2";
//    if (this->ui->radioTask3->isChecked() )
//        taskNo = "3";

//    int userID = this->ui->spinBoxUSERID->value();

//    QString output = QString("TESTS/UserID_%1_Task_%2.txt").arg(userID).arg(taskNo);

//    QFile file(output);
//    file.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream out(&file);
//    out << "This file is generated by QT\n";
//    file.close();


    //this->ui->plainTextEdit_Output->insertPlainText(QString("User: %1 , Session: %2 \n").arg(userID).arg(sessionID));
}

QString MainWindow::convertTask(QString task)
{
    QString selectedTast = "";

    if (task.compare("a")==0)
            selectedTast =  "Transform";
    if (task.compare("b")==0)
             selectedTast = "Sub-Volume";
    if (task.compare("c")==0)
            selectedTast = "Slicing";

    return selectedTast;
}

QString MainWindow::convertPrototype(QString prototype)
{
    QString selectedPrototype = "";

    if (prototype.compare("L")==0)
            selectedPrototype = "Leap";
    if (prototype.compare("M")==0)
            selectedPrototype = "Mouse";
    if (prototype.compare("T")==0)
            selectedPrototype = "Touch";

    return selectedPrototype;

}

void MainWindow::SetCurrentTask(int userID)
{

    if (this->ui->radioTask1->isChecked() )
        currentTask = one;
    if (this->ui->radioTask2->isChecked() )
        currentTask = two;
    if (this->ui->radioTask3->isChecked() )
        currentTask = three;

    QString task = counterBalance[userID][currentTask];

    if (task.compare("a")==0)
            currentJob = Transformation;
    if (task.compare("b")==0)
             currentJob = SubVolume;
    if (task.compare("c")==0)
            currentJob = Slicing;
}

void MainWindow::SetCurrentPrototype(int userID)
{
    int part = this->ui->spinBoxPARTProto->value();

    if (part == 1)
        currentPrototype = first;

    if (part == 2)
        currentPrototype = second;

    if (part == 3)
        currentPrototype = third;

    QString prototype = counterBalance[userID][currentPrototype];

    if (prototype.compare("L")==0)
            this->ui->radioLeap->setChecked(true);
    if (prototype.compare("M")==0)
            this->ui->radioMouse->setChecked(true);
    if (prototype.compare("T")==0)
            this->ui->radioTouch->setChecked(true);
}

QString MainWindow::GetCurrentTask(int userID)
{
    QString task;

    switch (currentTask)
    {
        case one: task = convertTask(counterBalance[userID][one]);
        break;
        case two: task = convertTask(counterBalance[userID][two]);
        break;
        case three: task = convertTask(counterBalance[userID][three]);
        break;
    }
    return task;
}

QString MainWindow::GetCurrentPrototype(int userID)
{
    QString prototype;

    switch (currentPrototype)
    {
        case first: prototype = convertPrototype(counterBalance[userID][first]);
        break;
        case second: prototype = convertPrototype(counterBalance[userID][second]);
        break;
        case third: prototype = convertPrototype(counterBalance[userID][third]);
        break;
    }
    return prototype;
}

void MainWindow::extractProtOrder(QString line)
{
}
