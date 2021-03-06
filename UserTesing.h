#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void testingMode(bool testing);

    void PrintConfig();

    QString convertTask(QString task);

    QString convertPrototype(QString prototype);

    void SetCurrentTask(int userID);

    void SetCurrentPrototype(int userID);

    QString GetCurrentTask(int userID);

    QString GetCurrentPrototype(int userID);

    void extractProtOrder(QString line);

    void loadCounterBalance(QString filename);

    void printResult(QString status);

    void saveResult(QString result);


    void SplitAndAdd(QString line, int lineNumber);

    void initiateTest(int userID);

    enum Job  {Transformation, SubVolume, Slicing};
    enum Tasks {one = 4, two = 5, three = 6};       /// Index positions in counterbalance matrix for Tasks
    enum Prototype   {Mouse, Touch, Leap};         /// Index positions in Counterbalance matrix for Prototypes
    enum Part {first = 1, second = 2, third = 3}; /// Index position in Prototype ordering matrix for Tests



private slots:
    void on_btnStart_clicked();
    void updateCaption();

    void on_btnStop_clicked();

    void on_btnDone_clicked();



    void on_btnCounterBal_clicked();

    void on_btnTest_clicked();




private:
    Ui::MainWindow *ui;
    QTimer *timer ;

    static const int cntrBalLength = 27;

    char testConfig [7][3];
    QString stringConfig[27];

    QString counterBalance[cntrBalLength][7];
    int currentJob;     /// Variable showing which JOB to load from the Test
    int currentTask;    /// Variable showing current TASK radio button seleciton
    int currentPrototype = 0; /// Variable showing current LOCATION for prototype
    //QVector<QStringList> counterBalance(10);

};

#endif // MAINWINDOW_H
