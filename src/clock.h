#ifndef CLOCKSTATE_H
#define CLOCKSTATE_H

#include <ctime>

#include <QList>
#include <QVector>

class Clock
{
public:
    Clock();
    ~Clock();
    bool update();
    bool getHourStateAt(int i) { return hourBoxStates[i]; }
    bool getMinuteStateAt(int i) { return minuteBoxStates[i]; }
    bool getRemainderStateAt(int i) { return remainderStates[i]; }

private:
    void populateMainStates(bool *states, int sum);
    void populateRemainderStates(bool* states, int sum);

    struct tm lastTime;

    QVector<bool*> possibleMainStates[12];
    QVector<bool*> possibleRemainderStates[5];

    bool hourBoxStates[5], minuteBoxStates[5], remainderStates[3];

    const int fibMap[5] = {1, 1, 2, 3, 5};
};

#endif // CLOCKSTATE_H
