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

private slots:
    void on_btnStart_clicked();
    void updateCaption();

    void on_btnStop_clicked();

    void on_btnDone_clicked();

    void loadCounterBalance(QString filename);


    void printResult(QString status);

    void on_btnCounterBal_clicked();

    void on_btnTest_clicked();

    QString convertTask(char task);

    QString convertProtOrder(char prototype);

    void extractTaskOrder(QString line);

    void extractProtOrder(QString line);


private:
    Ui::MainWindow *ui;
    QTimer *timer ;
    char testConfig [8][3];
    QString stringConfig[3];

};

#endif // MAINWINDOW_H
