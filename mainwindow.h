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

private slots:
    void on_btnStart_clicked();
    void updateCaption();

    void on_btnStop_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer ;

};

#endif // MAINWINDOW_H