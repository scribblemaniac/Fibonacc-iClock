#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    c()
{
    ui->setupUi(this);

    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect;
    opacity->setOpacity(0);
    ui->wrapper8x5->setGraphicsEffect(opacity);

    contentMap[0] = ui->content1Bottom;
    contentMap[1] = ui->content1Top;
    contentMap[2] = ui->content2x2;
    contentMap[3] = ui->content3x3;
    contentMap[4] = ui->content5x5;

    borderMap[0] = ui->wrapper1Bottom;
    borderMap[1] = ui->wrapper1Top;
    borderMap[2] = ui->wrapper2x2;

    checkForUpdate();

    /*QPropertyAnimation *animation = new QPropertyAnimation(opacity, "opacity");
    animation->setDuration(750);
    animation->setStartValue(0.);
    animation->setEndValue(1.);

    animation->start();*/
    opacity->setOpacity(1);

    updateTimer.setInterval(500);
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(checkForUpdate()));
    updateTimer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackground(QWidget* object, QString imagePath) {
    QStringList styleSplit(QString(object->styleSheet()).split(';'));
    bool found = false;
    for(int i = 0; i < styleSplit.size(); i++) {
        if(styleSplit[i].trimmed().startsWith("background-image:")) {
            found = true;
            styleSplit[i] = "background-image:url('" + imagePath + "')";
        }
    }
    if(!found) {
        styleSplit.append("background-image:url('" + imagePath + "')");
    }
    object->setStyleSheet(styleSplit.join(';'));
}

void MainWindow::checkForUpdate() {
    if(c.update()) {
        updateTime();
    }
}

void MainWindow::updateTime() {
    int states[] = { 0, 0, 0, 0, 0 };
    for(int i = 0; i < 5; i++) {
        states[i] |= c.getHourStateAt(i);
    }

    for(int i = 0; i < 5; i++) {
        states[i] |= c.getMinuteStateAt(i) << 1;
    }

    for(int i = 0; i < 5; i++) {
        switch(states[i]) {
        case 0:
            setBackground(contentMap[i], ":/grey_tiles.png");
            break;
        case 1:
            setBackground(contentMap[i], ":/red_tiles.png");
            break;
        case 2:
            setBackground(contentMap[i], ":/green_tiles.png");
            break;
        case 3:
            setBackground(contentMap[i], ":/blue_tiles.png");
            break;
        }
    }

    for(int i = 0; i < 3; i++) {
        if(c.getRemainderStateAt(i)) {
            setBackground(borderMap[i], ":/white_tiles.png");
        }
        else {
            setBackground(borderMap[i], ":/black_tiles.png");
        }
    }
}
