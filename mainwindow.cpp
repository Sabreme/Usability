#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QStringBuilder"

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

void MainWindow::on_btnStart_clicked()
{
    this->ui->timeEdit->setDisplayFormat("mm:ss");
    this->ui->timeEdit->setTime(QTime(0,0,0,0));

    timer =  new QTimer(this);
    connect (timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(1000);
}

void MainWindow::updateCaption()
{
    this->ui->timeEdit->setTime(this->ui->timeEdit->time().addSecs(1));
}

void MainWindow::on_btnStop_clicked()
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



    timer->stop();

    QString seconds = QString("%1").arg(this->ui->timeEdit->time().second());

    QString result = task % " using " % medium % " took  "  % seconds % "\n ";
    this->ui->plainTextEdit_Output->insertPlainText(result);
}
