#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "astar.h"
#include <QMainWindow>
#include <QFileDialog>

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
    void on_openMap_clicked();
    void on_start_clicked();

    void on_stop_clicked();

private:
     Ui::MainWindow *ui;
     int m, n;
     QString input;
     Astar *astar;
};

#endif // MAINWINDOW_H
