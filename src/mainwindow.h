#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "clock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setBackground(QWidget* object, QString imagePath);

private slots:
    void checkForUpdate();
private:
    Ui::MainWindow *ui;
    Clock c;
    QTimer updateTimer;
    QWidget* contentMap[5];
    QWidget* borderMap[3];

    void updateTime();
};

#endif // MAINWINDOW_H
