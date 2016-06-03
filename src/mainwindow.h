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
