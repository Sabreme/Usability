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

private slots:
    void on_btnStart_clicked();
    void updateCaption();

    void on_btnStop_clicked();

    void on_btnDone_clicked();

    void printResult(QString status);

private:
    Ui::MainWindow *ui;
    QTimer *timer ;

};

#endif // MAINWINDOW_H
