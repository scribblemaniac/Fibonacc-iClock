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
