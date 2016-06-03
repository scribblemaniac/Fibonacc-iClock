/*
    Fibonacc iClock - A fibonacci clock implementation for iOS.
    Copyright (C) 2016 Fibonacc iClock Developers (see https://github.com/scribblemaniac/Fibonacc-iClock/graphs/contributors for a complete list)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    Full license can be found in the LICENSE file in the project root.
    If you wish to contact us, please open an issue at (https://github.com/scribblemaniac/Fibonacc-iClock/issues).
*/

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
