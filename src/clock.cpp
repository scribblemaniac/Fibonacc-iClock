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

#include <QtGlobal>
#include <QDebug>

#include "clock.h"

Clock::Clock() {
    bool mainS[] = { false, false, false, false, false };
    possibleMainStates[0].append(mainS);
    populateMainStates(mainS, 0);
    bool remainderS[] = { false, false, false };
    possibleRemainderStates[0].append(remainderS);
    populateRemainderStates(remainderS, 0);
}

Clock::~Clock() {
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < possibleMainStates[i].size(); j++) {
            delete[] possibleMainStates[i][j];
        }
    }
}

bool Clock::update() {
    time_t now = std::time(NULL);
    struct tm local = *std::localtime(&now);
    if(local.tm_hour == lastTime.tm_hour && local.tm_min == lastTime.tm_min) {
        return false;
    }

    bool* newHourBoxStates = possibleMainStates[local.tm_hour % 12].at(qrand() % possibleMainStates[local.tm_hour % 12].size());
    for(int i = 0; i < 5; i++) hourBoxStates[i] = newHourBoxStates[i];
    bool* newMinuteBoxStates = possibleMainStates[local.tm_min / 5].at(qrand() % possibleMainStates[local.tm_min / 5].size());
    for(int i = 0; i < 5; i++) minuteBoxStates[i] = newMinuteBoxStates[i];

    bool* newRemainderStates = possibleRemainderStates[local.tm_min % 5].at(qrand() % possibleRemainderStates[local.tm_min % 5].size());
    for(int i = 0; i < 3; i++) remainderStates[i] = newRemainderStates[i];

    lastTime = local;

    return true;
}

void Clock::populateMainStates(bool* states, int sum) {
    for(int i = 4; i >= 0; i--) {
        if(!states[i]) {
            bool* newStates = new bool[5];
            for(int j = 0; j < 5; j++) {
                newStates[j] = states[j];
            }
            newStates[i] = true;
            possibleMainStates[(sum + fibMap[i]) % 12].append(newStates);
            populateMainStates(newStates, sum + fibMap[i]);
        }
        else {
            break;
        }
    }
}

void Clock::populateRemainderStates(bool* states, int sum) {
    for(int i = 2; i >= 0; i--) {
        if(!states[i]) {
            bool* newStates = new bool[3];
            for(int j = 0; j < 3; j++) {
                newStates[j] = states[j];
            }
            newStates[i] = true;
            possibleRemainderStates[sum + fibMap[i]].append(newStates);
            populateRemainderStates(newStates, sum + fibMap[i]);
        }
        else {
            break;
        }
    }
}
